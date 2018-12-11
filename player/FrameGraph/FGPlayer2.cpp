// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "FGPlayer.h"
#include "FGUnpacker.h"
#include "stl/Algorithms/StringUtils.h"
#include "FGPack/FgStructUnpacker.h"

namespace VTPlayer
{

/*
=================================================
	_CreateFrameGraphThread
----
	see packer in 'FrameGraphConverter::_PackCreateThreads'
=================================================
*/
	bool FGPlayer_v100::_CreateFrameGraphThread (FGUnpacker &unpacker)
	{
		const auto	index = unpacker.Get<uint>();

		ThreadDesc	desc;
		auto&		frame_graph	= _frameGraphThreads[index].thread;

		desc.usage << unpacker;

		frame_graph = _frameGraphInst->CreateThread( desc );
		CHECK_ERR( frame_graph );

		if ( EnumEq( desc.usage, EThreadUsage::Present ) )
		{
			FrameGraphThread::SwapchainCreateInfo	swapchain_info;
			VulkanSwapchainCreateInfo				swapchain_ci;

			swapchain_ci.surface		= BitCast<SurfaceVk_t>( _vulkan.GetVkSurface() );
			swapchain_ci.surfaceSize	= _window->GetSize();
			swapchain_info				= swapchain_ci;

			CHECK_ERR( frame_graph->Initialize( &swapchain_info ));
		}
		return true;
	}

/*
=================================================
	_CreateShaderModule
----
	see packer in 'FrameGraphConverter::PipelineConverter::_PackShaderModule'
=================================================
*/
	bool FGPlayer_v100::_CreateShaderModule (FGUnpacker &unpacker)
	{
		const auto	shader_idx	= unpacker.Get<Index_t>();
		const auto	data		= _LoadData( unpacker.Get<DataID>() );

		CHECK_ERR( not _resources.shaders[shader_idx] );

		VkShaderModuleCreateInfo	info = {};
		info.sType		= VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		info.pCode		= Cast<uint>( data.data() );
		info.codeSize	= uint(data.size());

		VkShaderModule	module;
		VK_CHECK( _vulkan.vkCreateShaderModule( _vulkan.GetVkDevice(), &info, null, OUT &module ));

		_resources.shaders[shader_idx] = MakeShared<ShaderModule>( module, "main" );
		return true;
	}
	
/*
=================================================
	_UnpackPipelineLayout
----
	see packer in 'FrameGraphConverter::PipelineConverter::_PackPipelineLayout'
=================================================
*/
	bool FGPlayer_v100::_UnpackPipelineLayout (OUT PipelineDescription::PipelineLayout &layout, FGUnpacker &unpacker) const
	{
		using UniformTypes = TypeList< PipelineDescription::UniformData_t >;

		const uint	ds_count = unpacker.Get<uint>();
		layout.descriptorSets.resize( ds_count );

		for (auto& ds : layout.descriptorSets)
		{
			PipelineDescription::UniformMap_t	uniforms;

			ds.id << unpacker;
			ds.bindingIndex << unpacker;
			const uint	un_count = unpacker.Get<uint>();

			for (uint i = 0; i < un_count; ++i)
			{
				PipelineDescription::Uniform	un;
				UniformID						name;

				name << unpacker;
				un.index = BindingIndex{ ~0u, unpacker.Get<uint>() };
				un.stageFlags << unpacker;

				const uint	un_index = unpacker.Get<uint>();

				switch ( un_index )
				{
					case UniformTypes::Index< PipelineDescription::Texture > : {
						const auto	state	= unpacker.Get<EResourceState>();
						const auto	type	= unpacker.Get<EImage>();

						un.data = PipelineDescription::Texture{ state, type };
						break;
					}
					case UniformTypes::Index< PipelineDescription::Sampler > : {
						un.data = PipelineDescription::Sampler{};
						break;
					}
					case UniformTypes::Index< PipelineDescription::SubpassInput > : {
						const auto	state	= unpacker.Get<EResourceState>();
						const auto	index	= unpacker.Get<uint>();
						const auto	is_ms	= unpacker.Get<bool>();

						un.data = PipelineDescription::SubpassInput{ state, index, is_ms };
						break;
					}
					case UniformTypes::Index< PipelineDescription::Image > : {
						const auto	state	= unpacker.Get<EResourceState>();
						const auto	type	= unpacker.Get<EImage>();
						const auto	fmt		= unpacker.Get<EPixelFormat>();
						un.data = PipelineDescription::Image{ state, type, fmt };
						break;
					}
					case UniformTypes::Index< PipelineDescription::UniformBuffer > : {
						const auto	state	= unpacker.Get<EResourceState>();
						const auto	off_idx	= unpacker.Get<uint>();
						const auto	size	= BytesU{unpacker.Get<uint64_t>()};
						un.data = PipelineDescription::UniformBuffer{ state, off_idx, size };
						break;
					}	
					case UniformTypes::Index< PipelineDescription::StorageBuffer > : {
						const auto	state	= unpacker.Get<EResourceState>();
						const auto	off_idx	= unpacker.Get<uint>();
						const auto	st_size	= BytesU{unpacker.Get<uint64_t>()};
						const auto	stride	= BytesU{unpacker.Get<uint64_t>()};
						un.data = PipelineDescription::StorageBuffer{ state, off_idx, st_size, stride };
						break;
					}
					case UniformTypes::Index< PipelineDescription::RayTracingScene > : {
						un.data = PipelineDescription::RayTracingScene{};
						break;
					}
					default :
						ASSERT(false);
						break;
				}

				uniforms.insert_or_assign( std::move(name), std::move(un) );
			}

			ds.uniforms = MakeShared<PipelineDescription::UniformMap_t>( std::move(uniforms) );
		}

		const uint	pc_count = unpacker.Get<uint>();

		for (uint i = 0; i < pc_count; ++i)
		{
			PushConstantID						id;
			PipelineDescription::PushConstant	pc;

			id << unpacker;
			pc.stageFlags << unpacker;
			pc.offset	= Bytes<uint16_t>{unpacker.Get<uint16_t>()};
			pc.size		= Bytes<uint16_t>{unpacker.Get<uint16_t>()};

			layout.pushConstants.insert({ id, pc });
		}

		return true;
	}

/*
=================================================
	_CreateGraphicsPipeline
----
	see packer in 'FrameGraphConverter::PipelineConverter::_PackGraphicsPipeline'
=================================================
*/
	bool FGPlayer_v100::_CreateGraphicsPipeline (FGUnpacker &unpacker)
	{
		auto&		frame_graph	= _frameGraphThreads[ unpacker.Get<uint>() ].thread;
		const auto	gppln_idx	= unpacker.Get<Index_t>();

		CHECK_ERR( not _resources.gpipelines[gppln_idx] );

		GraphicsPipelineDesc	desc;

		const uint	sh_count = unpacker.Get<uint>();

		for (uint i = 0; i < sh_count; ++i)
		{
			const uint		shader_id	= unpacker.Get<uint>();
			const EShader	shader_type	= unpacker.Get<EShader>();
			CHECK_ERR( _resources.shaders[shader_id] );

			desc.AddShader( shader_type, EShaderLangFormat::VkShader_110, _resources.shaders[shader_id] );
		}

		const uint	fo_count = unpacker.Get<uint>();
		desc._fragmentOutput.resize( fo_count );

		for (auto& frag : desc._fragmentOutput) {
			frag.id << unpacker;
			frag.index << unpacker;
			frag.type << unpacker;
		}

		const uint	va_count = unpacker.Get<uint>();
		desc._vertexAttribs.resize( va_count );

		for (auto& attr : desc._vertexAttribs) {
			attr.id << unpacker;
			attr.index << unpacker;
			attr.type << unpacker;
		}

		desc._supportedTopology = GraphicsPipelineDesc::TopologyBits_t{ unpacker.Get<uint>() };
		desc._patchControlPoints << unpacker;
		desc._earlyFragmentTests << unpacker;

		CHECK_ERR( _UnpackPipelineLayout( OUT desc._pipelineLayout, unpacker ));

		_resources.gpipelines[gppln_idx] = frame_graph->CreatePipeline( std::move(desc) );
		CHECK_ERR( _resources.gpipelines[gppln_idx] );

		return true;
	}
	
/*
=================================================
	_CreateComputePipeline
----
	see packer in 'FrameGraphConverter::PipelineConverter::_PackComputePipeline'
=================================================
*/
	bool FGPlayer_v100::_CreateComputePipeline (FGUnpacker &)
	{
		return false;
	}
	
/*
=================================================
	_CreateMeshPipeline
=================================================
*/
	bool FGPlayer_v100::_CreateMeshPipeline (FGUnpacker &)
	{
		return false;
	}
	
/*
=================================================
	_CreateRayTracingPipeline
=================================================
*/
	bool FGPlayer_v100::_CreateRayTracingPipeline (FGUnpacker &)
	{
		return false;
	}

/*
=================================================
	_CreateSampler
=================================================
*/
	bool FGPlayer_v100::_CreateSampler (FGUnpacker &unpacker)
	{
		auto&		frame_graph	= _frameGraphThreads[ unpacker.Get<uint>() ].thread;
		const auto	sampler_idx	= unpacker.Get<Index_t>();

		CHECK_ERR( not _resources.samplers[sampler_idx] );

		SamplerDesc		desc;
		FGUnpack_SamplerDesc( OUT desc, unpacker );

		_resources.samplers[sampler_idx] = frame_graph->CreateSampler( desc );
		CHECK_ERR( _resources.samplers[sampler_idx] );

		return true;
	}
	
/*
=================================================
	_CreateImage
----
	see packer in 'FrameGraphConverter::ImageConverter::OnBeginFrame'
=================================================
*/
	bool FGPlayer_v100::_CreateImage (FGUnpacker &unpacker)
	{
		auto&		frame_graph	= _frameGraphThreads[ unpacker.Get<uint>() ].thread;
		const auto	image_idx	= unpacker.Get<Index_t>();

		CHECK_ERR( not _resources.images[image_idx] );

		MemoryDesc	mem;
		ImageDesc	desc;
		FGUnpack_ImageDesc( OUT desc, unpacker );
		FGUnpack_MemoryDesc( OUT mem, unpacker );

		_resources.images[image_idx] = frame_graph->CreateImage( desc, mem );
		CHECK_ERR( _resources.images[image_idx] );

		return true;
	}
	
/*
=================================================
	_DestroyImage
----
	see packer in 'FrameGraphConverter::BufferConverter::OnEndFrame'
=================================================
*/
	bool FGPlayer_v100::_DestroyImage (FGUnpacker &unpacker)
	{
		auto&		frame_graph	= _frameGraphThreads[ unpacker.Get<uint>() ].thread;
		const auto	image_idx	= unpacker.Get<Index_t>();

		CHECK_ERR( not _resources.images[image_idx] );

		frame_graph->ReleaseResource( INOUT _resources.images[image_idx] );
		return true;
	}
	
/*
=================================================
	_CreateBuffer
----
	see packer in 'FrameGraphConverter::BufferConverter::OnBeginFrame'
=================================================
*/
	bool FGPlayer_v100::_CreateBuffer (FGUnpacker &unpacker)
	{
		auto&		frame_graph	= _frameGraphThreads[ unpacker.Get<uint>() ].thread;
		const auto	buffer_idx	= unpacker.Get<Index_t>();

		CHECK_ERR( not _resources.buffers[buffer_idx] );
		
		MemoryDesc	mem;
		BufferDesc	desc;
		FGUnpack_BufferDesc( OUT desc, unpacker );
		FGUnpack_MemoryDesc( OUT mem, unpacker );
		
		_resources.buffers[buffer_idx] = frame_graph->CreateBuffer( desc, mem );
		CHECK_ERR( _resources.buffers[buffer_idx] );

		return true;
	}
	
/*
=================================================
	_DestroyBuffer
----
	see packer in 'FrameGraphConverter::BufferConverter::OnEndFrame'
=================================================
*/
	bool FGPlayer_v100::_DestroyBuffer (FGUnpacker &unpacker)
	{
		auto&		frame_graph	= _frameGraphThreads[ unpacker.Get<uint>() ].thread;
		const auto	buffer_idx	= unpacker.Get<Index_t>();

		CHECK_ERR( _resources.buffers[buffer_idx] );
		
		frame_graph->ReleaseResource( INOUT _resources.buffers[buffer_idx] );
		return true;
	}
	
/*
=================================================
	_DestroyGraphicsPipeline
=================================================
*/
	bool FGPlayer_v100::_DestroyGraphicsPipeline (FGUnpacker &)
	{
		return false;
	}
	
/*
=================================================
	_DestroyComputePipeline
=================================================
*/
	bool FGPlayer_v100::_DestroyComputePipeline (FGUnpacker &)
	{
		return false;
	}
	
/*
=================================================
	_DestroyMeshPipeline
=================================================
*/
	bool FGPlayer_v100::_DestroyMeshPipeline (FGUnpacker &)
	{
		return false;
	}
	
/*
=================================================
	_DestroyRayTracingPipeline
=================================================
*/
	bool FGPlayer_v100::_DestroyRayTracingPipeline (FGUnpacker &)
	{
		return false;
	}
	
/*
=================================================
	_DestroySampler
=================================================
*/
	bool FGPlayer_v100::_DestroySampler (FGUnpacker &)
	{
		return false;
	}
	
/*
=================================================
	_CreateRenderPass
----
	see packer in 'FrameGraphConverter::DrawCallConverter::_PackRenderPass'
=================================================
*/
	bool FGPlayer_v100::_CreateRenderPass (FGUnpacker &unpacker)
	{
		using ClearValues = TypeList< RenderPassDesc::ClearValue_t >;
		
		auto&		frame_graph	= _frameGraphThreads[ unpacker.Get<uint>() ].thread;
		const auto	index		= unpacker.Get<Index_t>();

		CHECK( not _resources.logicalPasses[index] );

		RenderPassDesc	desc;
		FGUnpack_ColorBuffersState( OUT desc.colorState, unpacker );
		FGUnpack_DepthBufferState( OUT desc.depthState, unpacker );
		FGUnpack_StencilBufferState( OUT desc.stencilState, unpacker );
		FGUnpack_MultisampleState( OUT desc.multisampleState, unpacker );


		const auto	rt_count = unpacker.Get<uint>();
		for (uint i = 0; i < rt_count; ++i)
		{
			RenderPassDesc::RT	rt;
			RenderTargetID		id;			id << unpacker;
			const auto			img_index	= unpacker.Get<uint>();

			rt.image = _resources.images[img_index].Get();

			rt.desc.emplace();
			FGUnpack_ImageViewDesc( OUT *rt.desc, unpacker );

			const auto	clear_val_idx = unpacker.Get<uint>();

			switch ( clear_val_idx )
			{
				case ClearValues::Index<RGBA32f> : {
					rt.clearValue = RGBA32f{};
					FGUnpack_RGBAColor( OUT std::get<RGBA32f>(rt.clearValue), unpacker );
					break;
				}
				case ClearValues::Index<RGBA32i> : {
					rt.clearValue = RGBA32i{};
					FGUnpack_RGBAColor( OUT std::get<RGBA32i>(rt.clearValue), unpacker );
					break;
				}
				case ClearValues::Index<RGBA32u> : {
					rt.clearValue = RGBA32u{};
					FGUnpack_RGBAColor( OUT std::get<RGBA32u>(rt.clearValue), unpacker );
					break;
				}
				case ClearValues::Index<DepthStencil> : {
					rt.clearValue = DepthStencil{};
					FGUnpack_DepthStencil( OUT std::get<DepthStencil>(rt.clearValue), unpacker );
					break;
				}
				case ClearValues::Index<std::monostate> :
					break;

				default :
					CHECK( !"not supported" );
			}

			rt.loadOp << unpacker;
			rt.storeOp << unpacker;

			desc.renderTargets.insert({ id, rt });
		}
		CHECK( rt_count == desc.renderTargets.size() );


		desc.viewports.resize( unpacker.Get<uint>() );
		for (auto& vp : desc.viewports) {
			FGUnpack_RenderPassViewport( OUT vp, unpacker );
		}

		FGUnpack_Rectangle( OUT desc.area, unpacker );
		desc.parallelExecution << unpacker;
		desc.canBeMerged << unpacker;

		_resources.logicalPasses[index] = frame_graph->CreateRenderPass( desc );
		CHECK_ERR( _resources.logicalPasses[index] );
		return true;
	}
	
/*
=================================================
	_SubmitRenderPass
----
	see packer in 'FrameGraphConverter::DrawCallConverter::_PackSubmitRenderPass'
=================================================
*/
	bool FGPlayer_v100::_SubmitRenderPass (FGUnpacker &unpacker)
	{
		auto&		fg		= _frameGraphThreads[ unpacker.Get<uint>() ];
		const auto	index	= unpacker.Get<Index_t>();

		CHECK_ERR( _resources.logicalPasses[index] );

		fg.task = fg.thread->AddTask( SubmitRenderPass{ _resources.logicalPasses[index] }.DependsOn( fg.task ));
		return true;
	}
	
/*
=================================================
	_DispatchCompute
----
	see packer in 'FrameGraphConverter::DrawCallConverter::CmdDispatch'
=================================================
*/
	bool FGPlayer_v100::_DispatchCompute (FGUnpacker &)
	{
		return false;
	}
	
/*
=================================================
	_DispatchComputeIndirect
----
	see packer in 'FrameGraphConverter::DrawCallConverter::CmdDispatchIndirect'
=================================================
*/
	bool FGPlayer_v100::_DispatchComputeIndirect (FGUnpacker &)
	{
		return false;
	}
	
/*
=================================================
	_CopyBuffer
----
	see packer in 'FrameGraphConverter::DrawCallConverter::CmdCopyBuffer'
=================================================
*/
	bool FGPlayer_v100::_CopyBuffer (FGUnpacker &unpacker)
	{
		auto&		fg			= _frameGraphThreads[ unpacker.Get<uint>() ];
		const auto	src_index	= unpacker.Get<Index_t>();
		const auto	dst_index	= unpacker.Get<Index_t>();
		const auto	count		= unpacker.Get<uint>();

		CHECK_ERR( _resources.buffers[src_index] and _resources.buffers[dst_index] );

		CopyBuffer	copy;
		copy.srcBuffer	= _resources.buffers[src_index].Get();
		copy.dstBuffer	= _resources.buffers[dst_index].Get();

		for (uint i = 0; i < count; ++i)
		{
			const auto	src_offset	= BytesU{ unpacker.Get<uint64_t>() };
			const auto	dst_offset	= BytesU{ unpacker.Get<uint64_t>() };
			const auto	size		= BytesU{ unpacker.Get<uint64_t>() };

			copy.AddRegion( src_offset, dst_offset, size );
		}
		
		fg.task = fg.thread->AddTask( copy.DependsOn( fg.task ));
		return true;
	}
	
/*
=================================================
	_CopyImage
----
	see packer in 'FrameGraphConverter::DrawCallConverter::CmdCopyImage'
=================================================
*/
	bool FGPlayer_v100::_CopyImage (FGUnpacker &unpacker)
	{
		auto&		fg			= _frameGraphThreads[ unpacker.Get<uint>() ];
		const auto	src_index	= unpacker.Get<Index_t>();
		const auto	dst_index	= unpacker.Get<Index_t>();
		const auto	count		= unpacker.Get<uint>();
		
		CHECK_ERR( _resources.images[src_index] and _resources.images[dst_index] );

		CopyImage	copy;
		copy.srcImage	= _resources.images[src_index].Get();
		copy.dstImage	= _resources.images[dst_index].Get();

		for (uint i = 0; i < count; ++i)
		{
			CopyImage::Region	reg;
			FGUnpack_CopyImage_Region( OUT reg, unpacker );
			copy.regions.push_back( reg );
		}
		
		fg.task = fg.thread->AddTask( copy.DependsOn( fg.task ));
		return true;
	}
	
/*
=================================================
	_CopyBufferToImage
----
	see packer in 'FrameGraphConverter::DrawCallConverter::CmdCopyBufferToImage'
=================================================
*/
	bool FGPlayer_v100::_CopyBufferToImage (FGUnpacker &unpacker)
	{
		auto&		fg			= _frameGraphThreads[ unpacker.Get<uint>() ];
		const auto	src_index	= unpacker.Get<Index_t>();
		const auto	dst_index	= unpacker.Get<Index_t>();
		const auto	count		= unpacker.Get<uint>();
		
		CHECK_ERR( _resources.buffers[src_index] and _resources.images[dst_index] );

		CopyBufferToImage	copy;
		copy.srcBuffer	= _resources.buffers[src_index].Get();
		copy.dstImage	= _resources.images[dst_index].Get();

		for (uint i = 0; i < count; ++i)
		{
			CopyBufferToImage::Region	reg;
			FGUnpack_BufferImageCopy_Region( OUT reg, unpacker );
			copy.regions.push_back( reg );
		}
		
		fg.task = fg.thread->AddTask( copy.DependsOn( fg.task ));
		return true;
	}
	
/*
=================================================
	_CopyImageToBuffer
----
	see packer in 'FrameGraphConverter::DrawCallConverter::CmdCopyImageToBuffer'
=================================================
*/
	bool FGPlayer_v100::_CopyImageToBuffer (FGUnpacker &unpacker)
	{
		auto&		fg			= _frameGraphThreads[ unpacker.Get<uint>() ];
		const auto	src_index	= unpacker.Get<Index_t>();
		const auto	dst_index	= unpacker.Get<Index_t>();
		const auto	count		= unpacker.Get<uint>();
		
		CHECK_ERR( _resources.images[src_index] and _resources.buffers[dst_index] );

		CopyImageToBuffer	copy;
		copy.srcImage	= _resources.images[src_index].Get();
		copy.dstBuffer	= _resources.buffers[dst_index].Get();
		
		for (uint i = 0; i < count; ++i)
		{
			CopyImageToBuffer::Region	reg;
			FGUnpack_BufferImageCopy_Region( OUT reg, unpacker );
			copy.regions.push_back( reg );
		}
		
		fg.task = fg.thread->AddTask( copy.DependsOn( fg.task ));
		return true;
	}
	
/*
=================================================
	_BlitImage
----
	see packer in 'FrameGraphConverter::DrawCallConverter::CmdBlitImage'
=================================================
*/
	bool FGPlayer_v100::_BlitImage (FGUnpacker &unpacker)
	{
		auto&		fg			= _frameGraphThreads[ unpacker.Get<uint>() ];
		const auto	src_index	= unpacker.Get<Index_t>();
		const auto	dst_index	= unpacker.Get<Index_t>();
		const auto	filter		= unpacker.Get<EFilter>();
		const auto	count		= unpacker.Get<uint>();
		
		CHECK_ERR( _resources.images[src_index] and _resources.images[dst_index] );

		BlitImage	blit;
		blit.srcImage	= _resources.images[src_index].Get();
		blit.dstImage	= _resources.images[dst_index].Get();
		blit.filter		= filter;

		for (uint i = 0; i < count; ++i)
		{
			BlitImage::Region	reg;
			FGUnpack_BlitImage_Region( OUT reg, unpacker );
			blit.regions.push_back( reg );
		}
		
		fg.task = fg.thread->AddTask( blit.DependsOn( fg.task ));
		return true;
	}
	
/*
=================================================
	_ResolveImage
----
	see packer in 'FrameGraphConverter::DrawCallConverter::CmdResolveImage'
=================================================
*/
	bool FGPlayer_v100::_ResolveImage (FGUnpacker &unpacker)
	{
		auto&		fg			= _frameGraphThreads[ unpacker.Get<uint>() ];
		const auto	src_index	= unpacker.Get<Index_t>();
		const auto	dst_index	= unpacker.Get<Index_t>();
		const auto	count		= unpacker.Get<uint>();
		
		CHECK_ERR( _resources.images[src_index] and _resources.images[dst_index] );

		ResolveImage	resolve;
		resolve.srcImage	= _resources.images[src_index].Get();
		resolve.dstImage	= _resources.images[dst_index].Get();

		for (uint i = 0; i < count; ++i)
		{
			ResolveImage::Region	reg;
			FGUnpack_ResolveImage_Region( OUT reg, unpacker );
			resolve.regions.push_back( reg );
		}
		
		fg.task = fg.thread->AddTask( resolve.DependsOn( fg.task ));
		return true;
	}
	
/*
=================================================
	_FillBuffer
----
	see packer in 'FrameGraphConverter::DrawCallConverter::CmdFillBuffer'
=================================================
*/
	bool FGPlayer_v100::_FillBuffer (FGUnpacker &unpacker)
	{
		auto&		fg		= _frameGraphThreads[ unpacker.Get<uint>() ];
		const auto	index	= unpacker.Get<Index_t>();
		const auto	offset	= BytesU{ unpacker.Get<uint64_t>() };
		const auto	size	= BytesU{ unpacker.Get<uint64_t>() };
		const auto	pattern	= unpacker.Get<uint>();
		
		CHECK( _resources.buffers[index] );

		fg.task = fg.thread->AddTask( FillBuffer{}.SetBuffer( _resources.buffers[index], offset, size ).SetPattern( pattern ).DependsOn( fg.task ));
		return true;
	}
	
/*
=================================================
	_ClearColorImage
----
	see packer in 'FrameGraphConverter::DrawCallConverter::CmdClearColorImage'
=================================================
*/
	bool FGPlayer_v100::_ClearColorImage (FGUnpacker &unpacker)
	{
		auto&		fg		= _frameGraphThreads[ unpacker.Get<uint>() ];
		const auto	index	= unpacker.Get<Index_t>();
		const auto	count	= unpacker.Get<uint>();
		
		CHECK( _resources.images[index] );

		ClearColorImage		clear;
		clear.dstImage	= _resources.images[index].Get();

		for (uint i = 0; i < count; ++i)
		{
			ClearColorImage::Range	range;
			FGUnpack_ClearColorImage_Range( OUT range, unpacker );
			clear.ranges.push_back( range );
		}

		FGUnpack_ClearColor( OUT clear.clearValue, unpacker );
		
		fg.task = fg.thread->AddTask( clear.DependsOn( fg.task ));
		return true;
	}
	
/*
=================================================
	_ClearDepthStencilImage
----
	see packer in 'FrameGraphConverter::DrawCallConverter::CmdClearDepthStencilImage'
=================================================
*/
	bool FGPlayer_v100::_ClearDepthStencilImage (FGUnpacker &unpacker)
	{
		auto&		fg		= _frameGraphThreads[ unpacker.Get<uint>() ];
		const auto	index	= unpacker.Get<Index_t>();
		const auto	count	= unpacker.Get<uint>();
		
		CHECK( _resources.images[index] );

		ClearDepthStencilImage	clear;
		clear.dstImage	= _resources.images[index].Get();
		
		for (uint i = 0; i < count; ++i)
		{
			ClearDepthStencilImage::Range	range;
			FGUnpack_ClearColorImage_Range( OUT range, unpacker );
			clear.ranges.push_back( range );
		}

		clear.clearValue.depth << unpacker;
		clear.clearValue.stencil << unpacker;

		fg.task = fg.thread->AddTask( clear.DependsOn( fg.task ));
		return true;
	}
	
/*
=================================================
	_UpdateBuffer
----
	see packer in 'FrameGraphConverter::DrawCallConverter::CmdUpdateBuffer'
=================================================
*/
	bool FGPlayer_v100::_UpdateBuffer (FGUnpacker &unpacker)
	{
		auto&		fg		= _frameGraphThreads[ unpacker.Get<uint>() ];
		const auto	index	= unpacker.Get<Index_t>();
		const auto	offset	= BytesU{ unpacker.Get<uint64_t>() };
		const auto	size	= BytesU{ unpacker.Get<uint64_t>() };
		const auto	data	= _LoadData( unpacker.Get<uint>() );

		CHECK( _resources.buffers[index] );
		ASSERT( size <= data.size() );

		fg.task = fg.thread->AddTask( UpdateBuffer{}.SetBuffer( _resources.buffers[index], offset ).SetData( data ).DependsOn( fg.task ));
		return true;
	}
	
/*
=================================================
	_ReadBuffer
=================================================
*/
	bool FGPlayer_v100::_ReadBuffer (FGUnpacker &)
	{
		return false;
	}
	
/*
=================================================
	_UpdateImage
----
	see packer in 'FrameGraphConverter::DrawCallConverter::_UpdateImage '
=================================================
*/
	bool FGPlayer_v100::_UpdateImage (FGUnpacker &unpacker)
	{
		auto&		fg		= _frameGraphThreads[ unpacker.Get<uint>() ];
		const auto	index	= unpacker.Get<Index_t>();
		
		CHECK( _resources.images[index] );

		UpdateImage	task;

		task.dstImage		= _resources.images[index].Get();
		FGUnpack_Vec( OUT task.imageOffset, unpacker );
		FGUnpack_Vec( OUT task.imageSize, unpacker );
		task.arrayLayer		= ImageLayer{ unpacker.Get<uint>() };
		task.mipmapLevel	= MipmapLevel{ unpacker.Get<uint>() };
		task.dataRowPitch	= BytesU{ unpacker.Get<uint64_t>() };
		task.dataSlicePitch	= BytesU{ unpacker.Get<uint64_t>() };
		task.aspectMask		<< unpacker;
		task.data			= _LoadData( unpacker.Get<DataID>() );
		
		fg.task = fg.thread->AddTask( task.DependsOn( fg.task ));
		return true;
	}
	
/*
=================================================
	_ReadImage
=================================================
*/
	bool FGPlayer_v100::_ReadImage (FGUnpacker &)
	{
		return false;
	}
	
/*
=================================================
	_Present
----
	see packer in 'FrameGraphConverter::DrawCallConverter::QueuePresent'
=================================================
*/
	bool FGPlayer_v100::_Present (FGUnpacker &unpacker)
	{
		auto&		fg		= _frameGraphThreads[ unpacker.Get<uint>() ];
		const auto	index	= unpacker.Get<Index_t>();
		const auto	layer	= unpacker.Get<uint>();
		
		CHECK( _resources.images[index] );

		Present		task;
		task.srcImage	= _resources.images[index].Get();
		task.layer		= ImageLayer{ layer };
		
		fg.task = fg.thread->AddTask( task.DependsOn( fg.task ));
		return true;
	}
	
/*
=================================================
	_PresentVR
=================================================
*/
	bool FGPlayer_v100::_PresentVR (FGUnpacker &)
	{
		return false;
	}
	
/*
=================================================
	_UnpackBaseDrawVertices
----
	see packer in 'FrameGraphConverter::DrawCallConverter::_PackBaseDrawVertices'
=================================================
*/
	template <typename TaskType>
	bool FGPlayer_v100::_UnpackBaseDrawVertices (OUT _fg_hidden_::BaseDrawVertices<TaskType> &task, FrameData &data, FGUnpacker &unpacker) const
	{
		auto	ppln_idx = unpacker.Get<Index_t>();
		auto&	pipeline = _resources.gpipelines[ppln_idx];
		task.pipeline = pipeline.Get();
		
		CHECK_ERR( _UnpackBaseDrawCall( task, data, pipeline, unpacker ));

		FGUnpack_VertexInputState( OUT task.vertexInput, unpacker );

		// unpack vertex buffers
		const auto	vb_count	= unpacker.Get<uint>();

		for (uint i = 0; i < vb_count; ++i)
		{
			VertexBufferID	id;		id << unpacker;
			const auto&		buf_id	= _resources.buffers[ unpacker.Get<Index_t>() ];
			const auto		offset	= BytesU{ unpacker.Get<uint64_t>() };

			task.AddBuffer( id, buf_id, offset );
		}

		task.topology << unpacker;
		task.primitiveRestart << unpacker;

		return true;
	}
	
/*
=================================================
	_UnpackBaseDrawCall
----
	see packer in 'FrameGraphConverter::DrawCallConverter::_PackBaseDrawCall'
=================================================
*/
	template <typename TaskType, typename PipelineID>
	bool FGPlayer_v100::_UnpackBaseDrawCall (OUT _fg_hidden_::BaseDrawCall<TaskType> &task, FrameData &data,
											 const PipelineID &pipeline, FGUnpacker &unpacker) const
	{
		// unpack descriptor sets (pipeline resources)
		CHECK_ERR( _UnpackDescriptors( OUT task.resources, data, pipeline, unpacker ));

		// unpack push constants
		const auto	pc_count = unpacker.Get<uint>();
		for (uint i = 0; i < pc_count; ++i)
		{
			PushConstantID	id;		id << unpacker;
			const auto		size	= unpacker.Get<uint>();
			const auto		ptr		= unpacker.GetArray<uint8_t>( size );

			task.AddPushConstant( id, ptr, BytesU{size} );
		}

		// unpack dynamic states
		const auto	dyn_st = unpacker.Get<EPipelineDynamicState>();

		// unpack scissors
		const auto	sc_count = unpacker.Get<uint>();
		ASSERT( sc_count == 0 );

		// unpack color buffers
		const auto	cb_count = unpacker.Get<uint>();
		ASSERT( cb_count == 0 );

		// unpack stencil state
		task.stencilState.reference.x << unpacker;
		task.stencilState.reference.y << unpacker;
		task.stencilState.writeMask.x << unpacker;
		task.stencilState.writeMask.y << unpacker;
		task.stencilState.compareMask.x << unpacker;
		task.stencilState.compareMask.y << unpacker;

		return true;
	}
	
/*
=================================================
	_UnpackDescriptors
----
	see packer in 'FrameGraphConverter::DrawCallConverter::_PackDescriptors'
=================================================
*/
	template <typename PipelineID>
	bool FGPlayer_v100::_UnpackDescriptors (OUT PipelineResourceSet &outResources, FrameData &data, const PipelineID &pipeline, FGUnpacker &unpacker) const
	{
		const auto	ds_count = unpacker.Get<uint>();
		data.descriptors.resize( ds_count );
		
		for (uint i = 0; i < ds_count; ++i)
		{
			const auto		ds_index	= unpacker.Get<uint>();
			const auto		un_count	= unpacker.Get<uint>();
			auto &			res			= data.descriptors[ds_index];

			RawDescriptorSetLayoutID	ds_layout;
			uint						ds_binding = ds_index;
			CHECK( data.thread->GetDescriptorSet( pipeline, DescriptorSetID{ToString(ds_index)}, OUT ds_layout, OUT ds_binding ));
			CHECK( data.thread->InitPipelineResources( ds_layout, OUT res ));

			outResources[ds_binding] = &res;

			for (uint j = 0; j < un_count; ++j)
			{
				UniformID	un_id;		un_id << unpacker;
				const auto	type_idx	= unpacker.Get<uint>();

				switch ( type_idx )
				{
					case 1 :	// BindSampler
					{
						const auto&		sampler_id = _resources.samplers[ unpacker.Get<Index_t>() ];
						res.BindSampler( un_id, sampler_id );
						break;
					}

					case 2 :	// BindTexture
					{
						ImageViewDesc	desc;
						const auto&		image_id	= _resources.images[ unpacker.Get<Index_t>() ];
						const auto&		sampler_id	= _resources.samplers[ unpacker.Get<Index_t>() ];
						FGUnpack_ImageViewDesc( OUT desc, unpacker );

						res.BindTexture( un_id, image_id, sampler_id, desc );
						break;
					}

					case 3 :	// BindImage
					{
						ImageViewDesc	desc;
						const auto&		image_id	= _resources.images[ unpacker.Get<Index_t>() ];
						FGUnpack_ImageViewDesc( OUT desc, unpacker );

						res.BindImage( un_id, image_id, desc );
						break;
					}

					case 4 :	// BindBuffer
					{
						const auto&		buf_id	= _resources.buffers[ unpacker.Get<Index_t>() ];
						const auto		offset	= BytesU{ unpacker.Get<uint64_t>() };
						const auto		size	= BytesU{ unpacker.Get<uint64_t>() };
						const auto		dyn_off	= BytesU{ unpacker.Get<uint>() };

						//res.SetBufferBase( un_id, dyn_off );
						res.BindBuffer( un_id, buf_id, offset, size );
						break;
					}

					default :
						RETURN_ERR( "unknown uniform type" );
				}
			}
		}

		return true;
	}

/*
=================================================
	_DrawVertices
----
	see packer in 'FrameGraphConverter::DrawCallConverter::CmdDraw'
=================================================
*/
	bool FGPlayer_v100::_DrawVertices (FGUnpacker &unpacker)
	{
		auto&			fg		= _frameGraphThreads[ unpacker.Get<uint>() ];
		const auto&		pass_id	= _resources.logicalPasses[ unpacker.Get<Index_t>() ];

		DrawVertices	task;
		CHECK_ERR( _UnpackBaseDrawVertices( task, fg, unpacker ));
		
		// commands
		const auto		cmd_count	= unpacker.Get<uint>();
		ASSERT( cmd_count > 0 );

		for (uint i = 0; i < cmd_count; ++i)
		{
			DrawVertices::DrawCmd	cmd;
			cmd.vertexCount		<< unpacker;
			cmd.instanceCount	<< unpacker;
			cmd.firstVertex		<< unpacker;
			cmd.firstInstance	<< unpacker;
			task.commands.push_back( cmd );
		}

		fg.thread->AddTask( pass_id, task );
		return true;
	}
	
/*
=================================================
	_DrawIndexed
----
	see packer in 'FrameGraphConverter::DrawCallConverter::CmdDrawIndexed'
=================================================
*/
	bool FGPlayer_v100::_DrawIndexed (FGUnpacker &unpacker)
	{
		auto&			fg		= _frameGraphThreads[ unpacker.Get<uint>() ];
		const auto&		pass_id	= _resources.logicalPasses[ unpacker.Get<Index_t>() ];

		DrawIndexed		task;
		CHECK_ERR( _UnpackBaseDrawVertices( task, fg, unpacker ));
		
		// index buffer
		task.indexBuffer		= _resources.buffers[ unpacker.Get<Index_t>() ].Get();
		task.indexBufferOffset	= BytesU{ unpacker.Get<uint64_t>() };
		task.indexType			<< unpacker;
		
		// commands
		const auto		cmd_count	= unpacker.Get<uint>();
		ASSERT( cmd_count > 0 );

		for (uint i = 0; i < cmd_count; ++i)
		{
			DrawIndexed::DrawCmd	cmd;
			cmd.indexCount		<< unpacker;
			cmd.instanceCount	<< unpacker;
			cmd.firstIndex		<< unpacker;
			cmd.vertexOffset	<< unpacker;
			cmd.firstInstance	<< unpacker;
			task.commands.push_back( cmd );
		}

		fg.thread->AddTask( pass_id, task );
		return true;
	}
	
/*
=================================================
	_DrawMeshes
=================================================
*/
	bool FGPlayer_v100::_DrawMeshes (FGUnpacker &)
	{
		return false;
	}
	
/*
=================================================
	_DrawVerticesIndirect
----
	see packer in 'FrameGraphConverter::DrawCallConverter::CmdDrawIndirect'
=================================================
*/
	bool FGPlayer_v100::_DrawVerticesIndirect (FGUnpacker &)
	{
		return false;
	}
	
/*
=================================================
	_DrawIndexedIndirect
----
	see packer in 'FrameGraphConverter::DrawCallConverter::CmdDrawIndexedIndirect'
=================================================
*/
	bool FGPlayer_v100::_DrawIndexedIndirect (FGUnpacker &)
	{
		return false;
	}
	
/*
=================================================
	_DrawMeshesIndirect
=================================================
*/
	bool FGPlayer_v100::_DrawMeshesIndirect (FGUnpacker &)
	{
		return false;
	}
	
/*
=================================================
	_ClearAttachments
=================================================
*/
	bool FGPlayer_v100::_ClearAttachments (FGUnpacker &)
	{
		return false;
	}


}	// VTPlayer
