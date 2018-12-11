// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Converters/FrameGraph/PipelineConverter.h"
#include "Converters/FrameGraph/FGEnumCast.h"
#include "Converters/Utils/TracePacker.h"
#include "framegraph/Shared/EnumUtils.h"

#ifdef VTC_ENABLE_SPIRVREFLECT
#	include "spirv_reflect.h"
#endif

namespace VTC
{

/*
=================================================
	FG_GraphicsPipelineHash::operator ()
=================================================
*/
	size_t  FrameGraphConverter::PipelineConverter::FG_GraphicsPipelineHash::operator () (const FG_GraphicsPipeline &x) const noexcept
	{
		HashVal	result;
		result	<< HashOf( x.renderState );

		for (auto& stage : x.shaders) {
			result << HashOf( stage.code ) << HashOf( stage.entry ) << HashOf( stage.shaderType ) << HashOf( stage.specConstants );
		}

		for (auto& frag : x.fragOutput) {
			result << HashOf( frag.id ) << HashOf( frag.index ) << HashOf( frag.type );
		}

		for (auto& attr : x.attribs) {
			result << HashOf( attr.id ) << HashOf( attr.index ) << HashOf( attr.type );
		}

		result	<< HashOf( x.supportedTopology )
				<< HashOf( x.patchControlPoints )
				<< HashOf( x.earlyFragmentTests );

		result << HashOf( x.layout.descriptorSets.size() );

		for (auto& ds : x.layout.descriptorSets)
		{
			ASSERT( ds.uniforms );
			result << HashOf( ds.id ) << HashOf( ds.bindingIndex ) << HashOf( ds.uniforms->size() );

			for (auto& un : *ds.uniforms)
			{
				result	<< HashOf( un.first ) << HashOf( un.second.index ) << HashOf( un.second.stageFlags )
						<< HashOf( un.second.data.index() );

				Visit( un.second.data,
						[&result] (const PipelineDescription::Texture &tex) {
							result << HashOf( tex.state ) << HashOf( tex.textureType );
						},
						[&result] (const PipelineDescription::SubpassInput &spi) {
							result << HashOf( spi.state ) << HashOf( spi.attachmentIndex ) << HashOf( spi.isMultisample );
						},
						[&result] (const PipelineDescription::Image &img) {
							result << HashOf( img.state ) << HashOf( img.imageType ) << HashOf( img.format );
						},
						[&result] (const PipelineDescription::UniformBuffer &ubuf) {
							result << HashOf( ubuf.state ) << HashOf( ubuf.size ) << HashOf( ubuf.dynamicOffsetIndex );
						},
						[&result] (const PipelineDescription::StorageBuffer &sbuf) {
							result	<< HashOf( sbuf.state ) << HashOf( sbuf.staticSize )
									<< HashOf( sbuf.dynamicOffsetIndex ) << HashOf( sbuf.arrayStride );
						},
						[&result] (const PipelineDescription::Sampler &) {},
						[&result] (const PipelineDescription::RayTracingScene &) {
							ASSERT(false);
						},
						[] (const std::monostate &) {
							ASSERT(false);
						}
					  );
			}
		}

		result << HashOf( x.layout.pushConstants.size() );

		for (auto& pc : x.layout.pushConstants)
		{
			result	<< HashOf( pc.first ) << HashOf( pc.second.stageFlags )
					<< HashOf( pc.second.offset ) << HashOf( pc.second.size );
		}

		return size_t(result);
	}
	
/*
=================================================
	FG_GraphicsPipeline::operator ==
=================================================
*/
	bool  FrameGraphConverter::PipelineConverter::FG_GraphicsPipeline::operator == (const FG_GraphicsPipeline &rhs) const
	{
		if ( this->renderState			!= rhs.renderState			or
			 this->supportedTopology	!= rhs.supportedTopology	or
			 this->patchControlPoints	!= rhs.patchControlPoints	or
			 this->earlyFragmentTests	!= rhs.earlyFragmentTests	or
			 this->shaders.size()		!= rhs.shaders.size()		or
			 this->fragOutput			!= rhs.fragOutput			or
			 this->attribs				!= rhs.attribs )
			return false;

		for (size_t i = 0; i < this->shaders.size(); ++i)
		{
			if ( this->shaders[i].code			!= rhs.shaders[i].code			or
				 this->shaders[i].entry			!= rhs.shaders[i].entry			or
				 this->shaders[i].shaderType	!= rhs.shaders[i].shaderType	or
				 this->shaders[i].specConstants	!= rhs.shaders[i].specConstants )
				return false;
		}

		if ( this->layout.descriptorSets.size() != rhs.layout.descriptorSets.size() or
			 this->layout.pushConstants.size() != rhs.layout.pushConstants.size() )
			return false;

		for (size_t i = 0; i < this->layout.descriptorSets.size(); ++i)
		{
			auto&	lhs_ds	= this->layout.descriptorSets[i];
			auto&	rhs_ds	= rhs.layout.descriptorSets[i];

			if ( lhs_ds.bindingIndex		!= rhs_ds.bindingIndex	or
				 lhs_ds.uniforms			!= rhs_ds.uniforms		or
				 lhs_ds.uniforms->size()	!= rhs_ds.uniforms->size() )
				return false;

			for (auto lhs_un = lhs_ds.uniforms->begin(), rhs_un = rhs_ds.uniforms->begin();
				 lhs_un != lhs_ds.uniforms->end() and rhs_un != rhs_ds.uniforms->end();
				 ++lhs_un, ++rhs_un)
			{
				if ( lhs_un->first						!= rhs_un->first					or
					 lhs_un->second.index.VKBinding()	!= rhs_un->second.index.VKBinding()	or
					 lhs_un->second.stageFlags			!= rhs_un->second.stageFlags		or
					 lhs_un->second.data.index()		!= rhs_un->second.data.index() )
					return false;

				bool	eq = Visit( lhs_un->second.data,
						[rhs_un] (const PipelineDescription::Texture &lhs_tex)
						{
							auto&	rhs_tex = std::get<PipelineDescription::Texture>( rhs_un->second.data );
							return	lhs_tex.state		== rhs_tex.state	and
									lhs_tex.textureType	== rhs_tex.textureType;
						},

						[rhs_un] (const PipelineDescription::SubpassInput &lhs_spi)
						{
							auto&	rhs_spi = std::get<PipelineDescription::SubpassInput>( rhs_un->second.data );
							return	lhs_spi.state			== rhs_spi.state			and
									lhs_spi.attachmentIndex	== rhs_spi.attachmentIndex	and
									lhs_spi.isMultisample	== rhs_spi.isMultisample;
						},

						[rhs_un] (const PipelineDescription::Image &lhs_img)
						{
							auto&	rhs_img = std::get<PipelineDescription::Image>( rhs_un->second.data );
							return	lhs_img.state		== rhs_img.state		and
									lhs_img.imageType	== rhs_img.imageType	and
									lhs_img.format		== rhs_img.format;
						},

						[rhs_un] (const PipelineDescription::UniformBuffer &lhs_ubuf)
						{
							auto&	rhs_ubuf = std::get<PipelineDescription::UniformBuffer>( rhs_un->second.data );
							return	lhs_ubuf.state				== rhs_ubuf.state				and
									lhs_ubuf.dynamicOffsetIndex	== rhs_ubuf.dynamicOffsetIndex	and
									lhs_ubuf.size				== rhs_ubuf.size;
						},

						[rhs_un] (const PipelineDescription::StorageBuffer &lhs_sbuf)
						{
							auto&	rhs_sbuf = std::get<PipelineDescription::StorageBuffer>( rhs_un->second.data );
							return	lhs_sbuf.state				== rhs_sbuf.state				and
									lhs_sbuf.dynamicOffsetIndex	== rhs_sbuf.dynamicOffsetIndex	and
									lhs_sbuf.staticSize			== rhs_sbuf.staticSize			and
									lhs_sbuf.arrayStride		== rhs_sbuf.arrayStride;
						},

						[rhs_un] (const PipelineDescription::RayTracingScene &) {
							ASSERT(false);
							return false;	// TODO
						},

						[rhs_un] (const PipelineDescription::Sampler &) {
							return true;
						},

						[] (const std::monostate &) {
							return false;
						}
					  );

				if ( not eq )
					return false;
			}
		}

		return true;
	}
//-----------------------------------------------------------------------------


	
/*
=================================================
	ConvertPipelines
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::Convert (INOUT TracePacker &packer) const
	{
		for (auto& shader : _shaderDataCache) {
			CHECK_ERR( _PackShaderModule( shader.second, INOUT packer ));
		}

		for (auto& ppln : _gpipelineCache) {
			CHECK_ERR( _PackGraphicsPipeline( ppln.first, ppln.second, INOUT packer ));
		}

		for (auto& ppln : _cpipelineCache) {
			CHECK_ERR( _PackComputePipeline( ppln.first, ppln.second, INOUT packer ));
		}

		return true;
	}
	
/*
=================================================
	_PackShaderModule
----
	see unpacker in 'FGPlayer_v100::_CreateShaderModule'
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::_PackShaderModule (const ShaderDataInfo &info, INOUT TracePacker &packer) const
	{
		packer.Begin( EPacketID::FgCreateShaderModule );
		
		packer << info.uid;
		packer << info.dataId;

		packer.End( EPacketID::FgCreateShaderModule );
		return true;
	}
	
/*
=================================================
	_PackPipelineLayout
----
	see unpacker in 'FGPlayer_v100::_UnpackPipelineLayout'
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::_PackPipelineLayout (const FG_PipelineLayout &layout, INOUT TracePacker &packer) const
	{
		packer << uint(layout.descriptorSets.size());

		for (auto& ds : layout.descriptorSets)
		{
			ASSERT( ds.id.IsDefined() );
			ASSERT( ds.bindingIndex < FG_MaxDescriptorSets );

			packer << ds.id;
			packer << ds.bindingIndex;
			packer << uint(ds.uniforms->size());

			for (auto& un : *ds.uniforms)
			{
				ASSERT( un.first.IsDefined() );

				packer << un.first;
				packer << un.second.index.VKBinding();
				packer << un.second.stageFlags;
				packer << uint(un.second.data.index());

				Visit( un.second.data,
						[&packer] (const PipelineDescription::Texture &tex)
						{
							packer << tex.state;
							packer << tex.textureType;
						},
						[] (const PipelineDescription::Sampler &)
						{
						},
						[&packer] (const PipelineDescription::SubpassInput &spi)
						{
							packer << spi.state;
							packer << spi.attachmentIndex;
							packer << spi.isMultisample;
						},
						[&packer] (const PipelineDescription::Image &img)
						{
							packer << img.state;
							packer << img.imageType;
							packer << img.format;
						},
						[&packer] (const PipelineDescription::UniformBuffer &ubuf)
						{
							packer << ubuf.state;
							packer << ubuf.dynamicOffsetIndex;
							packer << uint64_t(ubuf.size);
						},
						[&packer] (const PipelineDescription::StorageBuffer &sbuf)
						{
							packer << sbuf.state;
							packer << sbuf.dynamicOffsetIndex;
							packer << uint64_t(sbuf.staticSize);
							packer << uint64_t(sbuf.arrayStride);
						},
						[&packer] (const PipelineDescription::RayTracingScene &)
						{
							ASSERT(false);
						},
						[] (const std::monostate &) { ASSERT(false); }
					);
			}
		}

		packer << uint(layout.pushConstants.size());

		for (auto& pc : layout.pushConstants)
		{
			packer << pc.first;
			packer << pc.second.stageFlags;
			packer << uint16_t(pc.second.offset);
			packer << uint16_t(pc.second.size);
		}

		return true;
	}

/*
=================================================
	_PackGraphicsPipeline
----
	see unpacker in 'FGPlayer_v100::_CreateGraphicsPipeline'
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::_PackGraphicsPipeline (const FG_GraphicsPipeline &ppln, RawGPipelineID id, INOUT TracePacker &packer) const
	{
		packer.Begin( EPacketID::FgCreateGraphicsPipeline );

		packer << uint(0);	// TODO: thread id
		packer << id.Index();

		packer << uint(ppln.shaders.size());
		for (auto& shader : ppln.shaders)
		{
			packer << shader.code->second.uid;
			packer << shader.shaderType;
		}

		packer << uint(ppln.fragOutput.size());
		for (auto& frag : ppln.fragOutput)
		{
			packer << frag.id;
			packer << frag.index;
			packer << frag.type;
		}

		packer << uint(ppln.attribs.size());
		for (auto& attr : ppln.attribs)
		{
			packer << attr.id;
			packer << attr.index;
			packer << attr.type;
		}

		packer << uint(ppln.supportedTopology.to_ulong());
		packer << ppln.patchControlPoints;
		packer << ppln.earlyFragmentTests;

		CHECK_ERR( _PackPipelineLayout( ppln.layout, packer ));

		packer.End( EPacketID::FgCreateGraphicsPipeline );
		return true;
	}
	
/*
=================================================
	_PackComputePipeline
----
	see unpacker in 'FGPlayer_v100::_CreateComputePipeline'
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::_PackComputePipeline (const FG_ComputePipeline &ppln, RawCPipelineID id, INOUT TracePacker &packer) const
	{
		packer.Begin( EPacketID::FgCreateGraphicsPipeline );
		
		packer << uint(0);	// TODO: thread id
		// TODO
		
		CHECK_ERR( _PackPipelineLayout( ppln.layout, packer ));

		packer.End( EPacketID::FgCreateGraphicsPipeline );
		return true;
	}

/*
=================================================
	CreateShaderModule
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::CreateShaderModule (const TraceRange::Iterator &pos)
	{
		auto const&		packet	= pos.Cast<packet_vkCreateShaderModule>();
		Array<uint>		data	{ packet.pCreateInfo->pCode, packet.pCreateInfo->pCode + (packet.pCreateInfo->codeSize / sizeof(uint)) };

		auto	data_iter = _shaderDataCache.find( data );
		
		if ( data_iter == _shaderDataCache.end() )
		{
			DataID		data_id = _fgConv._RequestData( pos, packet.header, packet.pCreateInfo->pCode, packet.pCreateInfo->codeSize, FrameID(0) );
			CHECK_ERR( data_id != ~DataID(0) );

			ShaderDataInfo		info;
			info.dataId			= data_id;
			info.uid			= _shaderCounter++;
			info.dataSize		= uint(data.size());
			info.glslSource		= _ConvertToGLSL( data );

			data_iter = _shaderDataCache.insert_or_assign( std::move(data), std::move(info) ).first;
		}

		_shaderMap.insert_or_assign( ResourceID(*packet.pShaderModule), data_iter.operator->() );
		return true;
	}
	
/*
=================================================
	_ConvertToGLSL
=================================================
*/
	String  FrameGraphConverter::PipelineConverter::_ConvertToGLSL (const Array<uint> &spv) const
	{
#	ifdef VTC_ENABLE_SPIRVCROSS
		spirv_cross::CompilerGLSL			compiler{ spv.data(), spv.size() };
		spirv_cross::CompilerGLSL::Options	opt;

		opt.version						= 460;
		opt.es							= false;
		opt.vulkan_semantics			= true;
		opt.separate_shader_objects		= true;
		opt.enable_420pack_extension	= true;

		opt.vertex.fixup_clipspace					= false;
		opt.vertex.flip_vert_y						= false;
		opt.vertex.support_nonzero_base_instance	= false;

		opt.fragment.default_float_precision	= spirv_cross::CompilerGLSL::Options::Precision::Highp;
		opt.fragment.default_int_precision		= spirv_cross::CompilerGLSL::Options::Precision::Highp;

		compiler.set_common_options( opt );

		return compiler.compile();
#	else
		return "";
#	endif
	}

/*
=================================================
	DestroyShaderModule
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::DestroyShaderModule (const TraceRange::Iterator &pos)
	{
		auto const&		packet	= pos.Cast<packet_vkDestroyShaderModule>();

		CHECK( _shaderMap.erase( ResourceID(packet.shaderModule) ) == 1 );
		return true;
	}
	
/*
=================================================
	CreateDescriptorSetLayout
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::CreateDescriptorSetLayout (const TraceRange::Iterator &pos)
	{
		auto const&		packet	= pos.Cast<packet_vkCreateDescriptorSetLayout>();
		auto			iter	= _dsLayouts.insert({ ResourceID(*packet.pSetLayout), {} }).first;
		auto&			desc	= iter->second.descriptors;

		ASSERT( packet.pCreateInfo->pNext == null );

		for (uint i = 0; i < packet.pCreateInfo->bindingCount; ++i)
		{
			auto&	src = packet.pCreateInfo->pBindings[i];
			
			desc.resize( Max( desc.size(), src.binding + src.descriptorCount ));

			// TODO: check
			ASSERT( src.descriptorCount == 1 );

			for (uint j = 0; j < src.descriptorCount; ++j)
			{
				auto&	dst = desc[ src.binding + j ];

				ASSERT( dst.descriptorType == VK_DESCRIPTOR_TYPE_MAX_ENUM or
						dst.descriptorType == src.descriptorType );

				dst.descriptorType	 = src.descriptorType;
				dst.stageFlags		|= src.stageFlags;
			}
		}
		return true;
	}
	
/*
=================================================
	DestroyDescriptorSetLayout
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::DestroyDescriptorSetLayout (const TraceRange::Iterator &pos)
	{
		auto const&		packet	= pos.Cast<packet_vkDestroyDescriptorSetLayout>();

		CHECK( _dsLayouts.erase( ResourceID(packet.descriptorSetLayout) ) == 1 );
		return true;
	}
	
/*
=================================================
	CreatePipelineLayout
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::CreatePipelineLayout (const TraceRange::Iterator &pos)
	{
		auto const&			packet	= pos.Cast<packet_vkCreatePipelineLayout>();
		PipelineLayoutInfo	info;

		info.dslayouts.resize( packet.pCreateInfo->setLayoutCount );

		for (uint i = 0; i < packet.pCreateInfo->setLayoutCount; ++i)
		{
			info.dslayouts[i] = ResourceID(packet.pCreateInfo->pSetLayouts[i]);
		}

		for (uint i = 0; i < packet.pCreateInfo->pushConstantRangeCount; ++i)
		{
			info.pushConstantRanges.insert({ PushConstantID(ToString(i)), packet.pCreateInfo->pPushConstantRanges[i] });
		}

		_pipelineLayouts.insert_or_assign( ResourceID(*packet.pPipelineLayout), info );
		return true;
	}
	
/*
=================================================
	DestroyPipelineLayout
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::DestroyPipelineLayout (const TraceRange::Iterator &pos)
	{
		/*auto const&		packet	= pos.Cast<packet_vkDestroyPipelineLayout>();

		CHECK( _pipelineLayouts.erase( ResourceID(packet.pipelineLayout) ) == 1 );*/
		return true;
	}
	
/*
=================================================
	CreateGraphicsPipelines
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::CreateGraphicsPipelines (const TraceRange::Iterator &pos)
	{
		auto const&		packet	= pos.Cast<packet_vkCreateGraphicsPipelines>();

		for (uint i = 0; i < packet.createInfoCount; ++i)
		{
			ASSERT( packet.pCreateInfos[i].pNext == null );

			const auto&		src  = packet.pCreateInfos[i];
			auto&			dst  = _graphicsPipelines.insert_or_assign( ResourceID(packet.pPipelines[i]), GraphicsPipelineInfo{} ).first->second;

			if ( src.pViewportState )
			{
				dst.viewports.resize( src.pViewportState->viewportCount );
				dst.scissors.resize( src.pViewportState->scissorCount );

				for (uint j = 0; src.pViewportState->pViewports and j < src.pViewportState->viewportCount; ++j) {
					dst.viewports[j] = src.pViewportState->pViewports[j];
				}

				for (uint j = 0; src.pViewportState->pScissors and j < src.pViewportState->scissorCount; ++j) {
					dst.scissors[j] = src.pViewportState->pScissors[j];
				}
			}

			if ( src.pDynamicState )
			{
				ASSERT( src.pDynamicState->pNext == null );
				for (uint j = 0; j < src.pDynamicState->dynamicStateCount; ++j) {
					dst.dynamicStates.insert( src.pDynamicState->pDynamicStates[j] );
				}
			}
			
			FG_GraphicsPipeline		info;
			CHECK_ERR( _ConvertGraphicsPipeline( OUT info, src ));

			auto[iter, inserted] = _gpipelineCache.insert({ info, RawGPipelineID{} });
			if ( inserted )
				iter->second = RawGPipelineID{ _graphicsPplnCounter++, 0 };

			dst.fgPipeline	= iter.operator->();
			dst.layout		= ResourceID(src.layout);

			if ( src.pInputAssemblyState )
			{
				dst.topology		= FGEnumCast( src.pInputAssemblyState->topology );
				dst.primitiveRestart= src.pInputAssemblyState->primitiveRestartEnable;
			}

			CHECK_ERR( _ConvertVertexInput( src, OUT dst.vertexInput ));
		}
		return true;
	}
	
/*
=================================================
	CreateComputePipelines
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::_ConvertGraphicsPipeline (OUT FG_GraphicsPipeline &result, const VkGraphicsPipelineCreateInfo &info) const
	{
		if ( info.pVertexInputState )
		{
			for (uint i = 0; i < info.pVertexInputState->vertexAttributeDescriptionCount; ++i)
			{
				auto&							src = info.pVertexInputState->pVertexAttributeDescriptions[i];
				VertexInputState::VertexAttrib	dst;

				dst.id		= VertexID( "attr"s << ToString(src.location) );
				dst.index	= src.location;
				dst.type	= FGEnumCastAttrib( src.format );

				result.attribs.push_back( dst );
			}
		}

		if ( info.pInputAssemblyState )
		{
			result.renderState.inputAssembly.topology			= FGEnumCast( info.pInputAssemblyState->topology );
			result.renderState.inputAssembly.primitiveRestart	= info.pInputAssemblyState->primitiveRestartEnable;
		}

		if ( info.pTessellationState )
		{
			result.patchControlPoints	= info.pTessellationState->patchControlPoints;
		}

		if ( info.pColorBlendState )
		{
			auto&	cs = *info.pColorBlendState;

			for (uint i = 0; i < cs.attachmentCount; ++i)
			{
				RenderTargetID							id{ "rt"s << ToString(i) };
				RenderState::ColorBuffer				cb;
				GraphicsPipelineDesc::FragmentOutput	frag;

				frag.id		= id;
				frag.index	= i;
				frag.type	= EFragOutput::Float4;	// TODO

				cb.blend	= cs.pAttachments[i].blendEnable;

				if ( cb.blend )
				{
					cb.blendOp.color		= FGEnumCast( cs.pAttachments[i].colorBlendOp );
					cb.blendOp.alpha		= FGEnumCast( cs.pAttachments[i].alphaBlendOp );
					cb.colorMask.x			= EnumEq( cs.pAttachments[i].colorWriteMask, VK_COLOR_COMPONENT_R_BIT );
					cb.colorMask.y			= EnumEq( cs.pAttachments[i].colorWriteMask, VK_COLOR_COMPONENT_G_BIT );
					cb.colorMask.z			= EnumEq( cs.pAttachments[i].colorWriteMask, VK_COLOR_COMPONENT_B_BIT );
					cb.colorMask.w			= EnumEq( cs.pAttachments[i].colorWriteMask, VK_COLOR_COMPONENT_A_BIT );
					cb.srcBlendFactor.color	= FGEnumCast( cs.pAttachments[i].srcColorBlendFactor );
					cb.srcBlendFactor.alpha	= FGEnumCast( cs.pAttachments[i].srcAlphaBlendFactor );
					cb.dstBlendFactor.color	= FGEnumCast( cs.pAttachments[i].dstColorBlendFactor );
					cb.dstBlendFactor.alpha	= FGEnumCast( cs.pAttachments[i].dstAlphaBlendFactor );
				}

				result.renderState.color.buffers.insert_or_assign( id, cb );
				result.fragOutput.push_back( frag );
			}

			if ( cs.logicOpEnable )
				result.renderState.color.logicOp = FGEnumCast( cs.logicOp );

			result.renderState.color.blendColor = { cs.blendConstants[0], cs.blendConstants[1], cs.blendConstants[2], cs.blendConstants[3] };
		}

		if ( info.pViewportState )
		{
			ASSERT( info.pViewportState->viewportCount == result.renderState.color.buffers.size() );
			ASSERT( info.pViewportState->viewportCount == result.fragOutput.size() );
		}

		if ( info.pRasterizationState )
		{
			result.renderState.rasterization.polygonMode			= FGEnumCast( info.pRasterizationState->polygonMode );
			result.renderState.rasterization.lineWidth				= info.pRasterizationState->lineWidth;
			result.renderState.rasterization.depthBiasConstFactor	= info.pRasterizationState->depthBiasConstantFactor;
			result.renderState.rasterization.depthBiasClamp			= info.pRasterizationState->depthBiasClamp;
			result.renderState.rasterization.depthBiasSlopeFactor	= info.pRasterizationState->depthBiasSlopeFactor;
			result.renderState.rasterization.depthBias				= info.pRasterizationState->depthBiasEnable;
			result.renderState.rasterization.depthClamp				= info.pRasterizationState->depthClampEnable;
			result.renderState.rasterization.rasterizerDiscard		= info.pRasterizationState->rasterizerDiscardEnable;
			result.renderState.rasterization.frontFaceCCW			= info.pRasterizationState->frontFace == VK_FRONT_FACE_COUNTER_CLOCKWISE;
			result.renderState.rasterization.cullMode				= FGEnumCast( info.pRasterizationState->cullMode );
		}

		if ( info.pMultisampleState )
		{
			result.renderState.multisample.samples				= MultiSamples{ uint(info.pMultisampleState->rasterizationSamples) };
			result.renderState.multisample.minSampleShading		= info.pMultisampleState->minSampleShading;
			result.renderState.multisample.sampleShading		= info.pMultisampleState->sampleShadingEnable;
			result.renderState.multisample.alphaToCoverage		= info.pMultisampleState->alphaToCoverageEnable;
			result.renderState.multisample.alphaToOne			= info.pMultisampleState->alphaToOneEnable;

			ASSERT( info.pMultisampleState->pSampleMask == null );

			//if ( info.pMultisampleState->pSampleMask )
			//	result.renderState.SetSampleMask( ArrayView{ info.pMultisampleState->pSampleMask, (result.renderState.multisample.samples.Get()+3/4) });
		}

		if ( info.pDepthStencilState )
		{
			result.renderState.depth.test			= info.pDepthStencilState->depthTestEnable;
			result.renderState.depth.write			= info.pDepthStencilState->depthWriteEnable;
			result.renderState.depth.boundsEnabled	= info.pDepthStencilState->depthBoundsTestEnable;
			result.renderState.stencil.enabled		= info.pDepthStencilState->stencilTestEnable;

			if ( info.pDepthStencilState->depthTestEnable )
				result.renderState.depth.compareOp = FGEnumCast( info.pDepthStencilState->depthCompareOp );

			if ( info.pDepthStencilState->depthBoundsTestEnable ) {
				result.renderState.depth.bounds.x = info.pDepthStencilState->minDepthBounds;
				result.renderState.depth.bounds.y = info.pDepthStencilState->maxDepthBounds;
			}

			if ( info.pDepthStencilState->stencilTestEnable )
			{
				result.renderState.stencil.front.failOp			= FGEnumCast( info.pDepthStencilState->front.failOp );
				result.renderState.stencil.front.depthFailOp	= FGEnumCast( info.pDepthStencilState->front.depthFailOp );
				result.renderState.stencil.front.passOp			= FGEnumCast( info.pDepthStencilState->front.passOp );
				result.renderState.stencil.front.compareOp		= FGEnumCast( info.pDepthStencilState->front.compareOp );
				result.renderState.stencil.front.compareMask	= info.pDepthStencilState->front.compareMask;
				result.renderState.stencil.front.writeMask		= info.pDepthStencilState->front.writeMask;
				result.renderState.stencil.front.reference		= info.pDepthStencilState->front.reference;
				
				result.renderState.stencil.back.failOp			= FGEnumCast( info.pDepthStencilState->back.failOp );
				result.renderState.stencil.back.depthFailOp		= FGEnumCast( info.pDepthStencilState->back.depthFailOp );
				result.renderState.stencil.back.passOp			= FGEnumCast( info.pDepthStencilState->back.passOp );
				result.renderState.stencil.back.compareOp		= FGEnumCast( info.pDepthStencilState->back.compareOp );
				result.renderState.stencil.back.compareMask		= info.pDepthStencilState->back.compareMask;
				result.renderState.stencil.back.writeMask		= info.pDepthStencilState->back.writeMask;
				result.renderState.stencil.back.reference		= info.pDepthStencilState->back.reference;
			}
		}
		
		if ( info.pStages )
		{
			for (uint i = 0; i < info.stageCount; ++i)
			{
				auto&			src = info.pStages[i];
				ShaderStage		dst;

				ASSERT( src.pNext == null );

				auto	sh_iter = _shaderMap.find( ResourceID(src.module) );
				CHECK_ERR( sh_iter != _shaderMap.end() );

				dst.code		= sh_iter->second;
				dst.entry		= src.pName;
				dst.shaderType	= FGEnumCast( src.stage );

				ASSERT( src.pSpecializationInfo == null );

				/*for (uint j = 0; src.pSpecializationInfo and j < src.pSpecializationInfo->mapEntryCount; ++j)
				{
					dst.specConstants.insert_or_assign( SpecializationID(""),  );
				}*/

				CHECK_ERR( _GetReflection( dst.code->first, INOUT result.fragOutput, INOUT result.attribs, INOUT result.layout ));

				result.shaders.push_back( std::move(dst) );
			}
		}

		result.supportedTopology[ uint(result.renderState.inputAssembly.topology) ] = true;
		return true;
	}
	
/*
=================================================
	_ConvertVertexInput
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::_ConvertVertexInput (const VkGraphicsPipelineCreateInfo &info, OUT VertexInputState &vertexInput) const
	{
		if ( not info.pVertexInputState )
			return true;

		for (uint i = 0; i < info.pVertexInputState->vertexBindingDescriptionCount; ++i)
		{
			auto&	bind = info.pVertexInputState->pVertexBindingDescriptions[i];

			vertexInput.Bind( VertexBufferID{ToString(bind.binding)}, BytesU{bind.stride}, bind.binding, FGEnumCast(bind.inputRate) );
		}

		for (uint i = 0; i < info.pVertexInputState->vertexAttributeDescriptionCount; ++i)
		{
			auto&	vert = info.pVertexInputState->pVertexAttributeDescriptions[i];

			vertexInput.Add( VertexID{ToString(vert.location)}, FGEnumCastVertex(vert.format), BytesU{vert.offset}, VertexBufferID{ToString(vert.binding)} );
		}

		return true;
	}

/*
=================================================
	FGEnumCast (SpvReflectShaderStageFlagBits)
=================================================
*/
	ND_ static EShaderStages  FGEnumCast (SpvReflectShaderStageFlagBits value)
	{
		ENABLE_ENUM_CHECKS();
		switch ( value )
		{
			case SPV_REFLECT_SHADER_STAGE_VERTEX_BIT :					return EShaderStages::Vertex;
			case SPV_REFLECT_SHADER_STAGE_TESSELLATION_CONTROL_BIT :	return EShaderStages::TessControl;
			case SPV_REFLECT_SHADER_STAGE_TESSELLATION_EVALUATION_BIT :	return EShaderStages::TessEvaluation;
			case SPV_REFLECT_SHADER_STAGE_GEOMETRY_BIT :				return EShaderStages::Geometry;
			case SPV_REFLECT_SHADER_STAGE_FRAGMENT_BIT :				return EShaderStages::Fragment;
			case SPV_REFLECT_SHADER_STAGE_COMPUTE_BIT :					return EShaderStages::Compute;
		}
		DISABLE_ENUM_CHECKS();
		RETURN_ERR( "unknown shader stage!" );
	}

/*
=================================================
	_GetReflection
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::_GetReflection (const Array<uint> &spvShader, INOUT FragmentOutputs_t &fragOutput,
																 INOUT VertexAttribs_t &attribs, INOUT FG_PipelineLayout &layout) const
	{
		SpvReflectShaderModule	module = {};
		CHECK_ERR( spvReflectCreateShaderModule( size_t(ArraySizeOf(spvShader)), spvShader.data(), OUT &module ) == SPV_REFLECT_RESULT_SUCCESS );

		if ( module.shader_stage == SPV_REFLECT_SHADER_STAGE_VERTEX_BIT ) {
			CHECK_ERR( _GetVertexInputReflection( module, INOUT attribs ));
		}

		if ( module.shader_stage == SPV_REFLECT_SHADER_STAGE_FRAGMENT_BIT ) {
			CHECK_ERR( _GetFragmentOutputReflection( module, INOUT fragOutput ));
		}

		for (uint i = 0; i < module.descriptor_set_count; ++i) {
			CHECK_ERR( _GetDescriptorSetLayoutReflection( module.descriptor_sets[i], FGEnumCast(module.shader_stage), INOUT layout ));
		}

		for (uint i = 0; i < module.push_constant_block_count; ++i) {
			CHECK_ERR( _GetPushConstantReflection( module.push_constant_blocks[i], FGEnumCast(module.shader_stage), INOUT layout ));
		}

		return true;
	}
	
/*
=================================================
	FGEnumCast (SpvReflectImageTraits)
=================================================
*/
	ND_ static EImage  FGEnumCast (const SpvReflectImageTraits &value)
	{
		ENABLE_ENUM_CHECKS();
		switch ( value.dim )
		{
			case SpvDim1D :		return value.arrayed ? EImage::Tex1DArray : EImage::Tex1D;
			case SpvDim2D :		return value.ms ?
										(value.arrayed ? EImage::Tex2DMSArray : EImage::Tex2DMS) :
										(value.arrayed ? EImage::Tex2DArray : EImage::Tex2D);
			case SpvDim3D :		return EImage::Tex3D;
			case SpvDimCube :	return value.arrayed ? EImage::TexCubeArray : EImage::TexCube;
			case SpvDimRect :
			case SpvDimBuffer :
			case SpvDimSubpassData :
			case SpvDimMax :	break;
		}
		DISABLE_ENUM_CHECKS();
		RETURN_ERR( "unsupported image dimension type" );
	}
	
/*
=================================================
	FGEnumCast (SpvImageFormat)
=================================================
*/
	ND_ static EPixelFormat  FGEnumCast (SpvImageFormat value)
	{
		ENABLE_ENUM_CHECKS();
		switch ( value )
		{
			case SpvImageFormatUnknown :		break;
			case SpvImageFormatRgba32f :		return EPixelFormat::RGBA32F;
			case SpvImageFormatRgba16f :		return EPixelFormat::RGBA16F;
			case SpvImageFormatR32f :			return EPixelFormat::R32F;
			case SpvImageFormatRgba8 :			return EPixelFormat::RGBA8_UNorm;
			case SpvImageFormatRgba8Snorm :		return EPixelFormat::RGBA8_SNorm;
			case SpvImageFormatRg32f :			return EPixelFormat::RG32F;
			case SpvImageFormatRg16f :			return EPixelFormat::RG16F;
			case SpvImageFormatR11fG11fB10f :	return EPixelFormat::RGB_11_11_10F;
			case SpvImageFormatR16f :			return EPixelFormat::R16F;
			case SpvImageFormatRgba16 :			return EPixelFormat::RGBA16_UNorm;
			case SpvImageFormatRgb10A2 :		return EPixelFormat::RGB10_A2_UNorm;
			case SpvImageFormatRg16 :			return EPixelFormat::RG16_UNorm;
			case SpvImageFormatRg8 :			return EPixelFormat::RG8_UNorm;
			case SpvImageFormatR16 :			return EPixelFormat::R16_UNorm;
			case SpvImageFormatR8 :				return EPixelFormat::R8_UNorm;
			case SpvImageFormatRgba16Snorm :	return EPixelFormat::RGBA16_SNorm;
			case SpvImageFormatRg16Snorm :		return EPixelFormat::RG16_SNorm;
			case SpvImageFormatRg8Snorm :		return EPixelFormat::RG8_SNorm;
			case SpvImageFormatR16Snorm :		return EPixelFormat::R16_SNorm;
			case SpvImageFormatR8Snorm :		return EPixelFormat::R8_SNorm;
			case SpvImageFormatRgba32i :		return EPixelFormat::RGBA32I;
			case SpvImageFormatRgba16i :		return EPixelFormat::RGBA16I;
			case SpvImageFormatRgba8i :			return EPixelFormat::RGBA8I;
			case SpvImageFormatR32i :			return EPixelFormat::R32I;
			case SpvImageFormatRg32i :			return EPixelFormat::RG32I;
			case SpvImageFormatRg16i :			return EPixelFormat::RG16I;
			case SpvImageFormatRg8i :			return EPixelFormat::RG8I;
			case SpvImageFormatR16i :			return EPixelFormat::R16I;
			case SpvImageFormatR8i :			return EPixelFormat::R8I;
			case SpvImageFormatRgba32ui :		return EPixelFormat::RGBA32U;
			case SpvImageFormatRgba16ui :		return EPixelFormat::RGBA16U;
			case SpvImageFormatRgba8ui :		return EPixelFormat::RGBA8U;
			case SpvImageFormatR32ui :			return EPixelFormat::R32U;
			case SpvImageFormatRgb10a2ui :		return EPixelFormat::RGB10_A2U;
			case SpvImageFormatRg32ui :			return EPixelFormat::RG32U;
			case SpvImageFormatRg16ui :			return EPixelFormat::RG16U;
			case SpvImageFormatRg8ui :			return EPixelFormat::RG8U;
			case SpvImageFormatR16ui :			return EPixelFormat::R16U;
			case SpvImageFormatR8ui :			return EPixelFormat::R8U;
			case SpvImageFormatMax :			break;
		}
		DISABLE_ENUM_CHECKS();
		RETURN_ERR( "unsupported pixel format!" );
	}
	
/*
=================================================
	MergeShaderAccess
=================================================
*/
	static void MergeShaderAccess (const EResourceState srcAccess, INOUT EResourceState &dstAccess)
	{
		if ( srcAccess == dstAccess )
			return;

		dstAccess |= srcAccess;

		if ( EnumEq( dstAccess, EResourceState::InvalidateBefore ) and
			 EnumEq( dstAccess, EResourceState::ShaderRead ) )
		{
			dstAccess &= ~EResourceState::InvalidateBefore;
		}
	}

/*
=================================================
	MergeUniforms
=================================================
*/
	static bool MergeUniforms (const PipelineDescription::UniformMap_t &srcUniforms, INOUT PipelineDescription::UniformMap_t &dstUniforms)
	{
		for (auto& un : srcUniforms)
		{
			auto	iter = dstUniforms.find( un.first );

			// add new uniform
			if ( iter == dstUniforms.end() )
			{
				dstUniforms.insert( un );
				continue;
			}

			bool	type_missmatch = true;

			Visit( un.second.data,
				[&] (const PipelineDescription::Texture &lhs)
				{
					if ( auto* rhs = std::get_if<PipelineDescription::Texture>( &iter->second.data ) )
					{
						ASSERT( lhs.textureType	== rhs->textureType );
						ASSERT( un.second.index	== iter->second.index );

						if ( lhs.textureType	== rhs->textureType and
							 un.second.index	== iter->second.index )
						{
							iter->second.stageFlags |= un.second.stageFlags;
							rhs->state				|= EResourceState_FromShaders( iter->second.stageFlags );
							type_missmatch			 = false;
						}
					}
				},
				   
				[&] (const PipelineDescription::Sampler &)
				{
					if ( auto* rhs = std::get_if<PipelineDescription::Sampler>( &iter->second.data ) )
					{
						ASSERT( un.second.index == iter->second.index );

						if ( un.second.index == iter->second.index )
						{
							iter->second.stageFlags |= un.second.stageFlags;
							type_missmatch			 = false;
						}
					}
				},
				
				[&] (const PipelineDescription::SubpassInput &lhs)
				{
					if ( auto* rhs = std::get_if<PipelineDescription::SubpassInput>( &iter->second.data ) )
					{
						ASSERT( lhs.attachmentIndex	== rhs->attachmentIndex );
						ASSERT( lhs.isMultisample	== rhs->isMultisample );
						ASSERT( un.second.index		== iter->second.index );
						
						if ( lhs.attachmentIndex	== rhs->attachmentIndex	and
							 lhs.isMultisample		== rhs->isMultisample	and
							 un.second.index		== iter->second.index )
						{
							iter->second.stageFlags |= un.second.stageFlags;
							rhs->state				|= EResourceState_FromShaders( iter->second.stageFlags );
							type_missmatch			 = false;
						}
					}
				},
				
				[&] (const PipelineDescription::Image &lhs)
				{
					if ( auto* rhs = std::get_if<PipelineDescription::Image>( &iter->second.data ) )
					{
						ASSERT( lhs.imageType	== rhs->imageType );
						ASSERT( lhs.format		== rhs->format );
						ASSERT( un.second.index	== iter->second.index );
						
						if ( lhs.imageType		== rhs->imageType	and
							 lhs.format			== rhs->format		and
							 un.second.index	== iter->second.index )
						{
							MergeShaderAccess( lhs.state, INOUT rhs->state );

							iter->second.stageFlags |= un.second.stageFlags;
							rhs->state				|= EResourceState_FromShaders( iter->second.stageFlags );
							type_missmatch			 = false;
						}
					}
				},
				
				[&] (const PipelineDescription::UniformBuffer &lhs)
				{
					if ( auto* rhs = std::get_if<PipelineDescription::UniformBuffer>( &iter->second.data ) )
					{
						ASSERT( lhs.size		== rhs->size );
						ASSERT( un.second.index	== iter->second.index );

						if ( lhs.size			== rhs->size	and
							 un.second.index	== iter->second.index )
						{
							iter->second.stageFlags |= un.second.stageFlags;
							rhs->state				|= EResourceState_FromShaders( iter->second.stageFlags );
							type_missmatch			 = false;
						}
					}
				},
				
				[&] (const PipelineDescription::StorageBuffer &lhs)
				{
					if ( auto* rhs = std::get_if<PipelineDescription::StorageBuffer>( &iter->second.data ) )
					{
						ASSERT( lhs.staticSize	== rhs->staticSize );
						ASSERT( lhs.arrayStride	== rhs->arrayStride );
						ASSERT( un.second.index	== iter->second.index );
						
						if ( lhs.staticSize		== rhs->staticSize	and
							 lhs.arrayStride	== rhs->arrayStride	and
							 un.second.index	== iter->second.index )
						{
							MergeShaderAccess( lhs.state, INOUT rhs->state );

							iter->second.stageFlags |= un.second.stageFlags;
							rhs->state				|= EResourceState_FromShaders( iter->second.stageFlags );
							type_missmatch			 = false;
						}
					}
				},
					
				[&] (const PipelineDescription::RayTracingScene &lhs)
				{
					if ( auto* rhs = std::get_if<PipelineDescription::RayTracingScene>( &iter->second.data ) )
					{
						ASSERT( lhs.state == rhs->state );

						if ( lhs.state == rhs->state )
						{
							iter->second.stageFlags |= un.second.stageFlags;
							type_missmatch			 = false;
						}
					}
				},

				[] (const std::monostate &) { ASSERT(false); }
			);

			CHECK_ERR( not type_missmatch );
		}
		return true;
	}

/*
=================================================
	_GetDescriptorSetLayoutReflection
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::_GetDescriptorSetLayoutReflection (const SpvReflectDescriptorSet &srcDS,
																					EShaderStages shaderStage, INOUT FG_PipelineLayout &layout) const
	{
		PipelineDescription::DescriptorSet	dst_ds;
		PipelineDescription::UniformMap_t	uniforms;
		EResourceState						rs_stages	= EResourceState_FromShaders( shaderStage );

		dst_ds.id = DescriptorSetID( ToString(srcDS.set) );
		dst_ds.bindingIndex = srcDS.set;

		for (uint i = 0; i < srcDS.binding_count; ++i)
		{
			auto&							src = *(srcDS.bindings[i]);
			PipelineDescription::Uniform	dst;
			const UniformID					name { ToString(src.set) << "." << ToString(src.binding) };

			//ASSERT( src.name and strlen(src.name) > 0 );
			//UniformID	name{ src.name };

			dst.index		= BindingIndex{ ~0u, src.binding };
			dst.stageFlags	= shaderStage;

			ENABLE_ENUM_CHECKS();
			switch ( src.descriptor_type )
			{
				case SPV_REFLECT_DESCRIPTOR_TYPE_SAMPLER :
					dst.data = PipelineDescription::Sampler{};
					break;

				case SPV_REFLECT_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER :
					dst.data = PipelineDescription::Texture{ rs_stages | EResourceState::ShaderSample, FGEnumCast(src.image) };
					break;

				case SPV_REFLECT_DESCRIPTOR_TYPE_STORAGE_IMAGE :
					dst.data = PipelineDescription::Image{ rs_stages | EResourceState::ShaderReadWrite, FGEnumCast(src.image), FGEnumCast(src.image.image_format) };
					break;

				case SPV_REFLECT_DESCRIPTOR_TYPE_INPUT_ATTACHMENT :
					dst.data = PipelineDescription::SubpassInput{ rs_stages | EResourceState::InputAttachment, src.input_attachment_index, !!src.image.ms };
					break;

				case SPV_REFLECT_DESCRIPTOR_TYPE_UNIFORM_BUFFER :
					dst.data = PipelineDescription::UniformBuffer{ rs_stages | EResourceState::UniformRead, ~0u, BytesU(src.block.size) };
					break;

				case SPV_REFLECT_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC :
					dst.data = PipelineDescription::UniformBuffer{ rs_stages | EResourceState::UniformRead, 0, BytesU(src.block.size) };
					break;
					
				case SPV_REFLECT_DESCRIPTOR_TYPE_STORAGE_BUFFER :
					dst.data = PipelineDescription::StorageBuffer{ rs_stages | EResourceState::ShaderReadWrite, ~0u, BytesU(src.block.size), 0_b };
					break;

				case SPV_REFLECT_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC :
					dst.data = PipelineDescription::StorageBuffer{ rs_stages | EResourceState::ShaderReadWrite, 0, BytesU(src.block.size), 0_b };
					break;

				case SPV_REFLECT_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER :
				case SPV_REFLECT_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER :
				case SPV_REFLECT_DESCRIPTOR_TYPE_SAMPLED_IMAGE :
				default :
					RETURN_ERR( "unsupported descriptor type" );
			}
			DISABLE_ENUM_CHECKS();

			uniforms.insert_or_assign( name, std::move(dst) );
		}

		dst_ds.uniforms = MakeShared< PipelineDescription::UniformMap_t >( std::move(uniforms) );
		
		// merge descriptor sets
		for (auto& ds : layout.descriptorSets)
		{
			if ( ds.id == dst_ds.id )
			{
				CHECK_ERR( ds.bindingIndex == dst_ds.bindingIndex );
				CHECK_ERR( MergeUniforms( *dst_ds.uniforms, INOUT const_cast<PipelineDescription::UniformMap_t &>(*ds.uniforms) ));
				return true;
			}
		}

		// add new descriptor set
		layout.descriptorSets.push_back( dst_ds );
		return true;
	}
	
/*
=================================================
	_GetPushConstantReflection
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::_GetPushConstantReflection (const SpvReflectBlockVariable &srcPC, EShaderStages stageFlags,
																			 INOUT FG_PipelineLayout &layout) const
	{
		PushConstantID	id		{ "0" };	//{ srcPC.name };
		BytesU			offset	{ srcPC.offset };
		BytesU			size	{ srcPC.padded_size };

		ASSERT( srcPC.size <= size );
		ASSERT( srcPC.absolute_offset == offset );	// TODO

		auto	iter = layout.pushConstants.find( id );

		// merge
		if ( iter != layout.pushConstants.end() )
		{
			CHECK_ERR( offset == uint(iter->second.offset) );
			CHECK_ERR( size == uint(iter->second.size) );

			iter->second.stageFlags |= stageFlags;
			return true;
		}

		// add new push constant
		layout.pushConstants.insert({ id, {stageFlags, offset, size} });
		return true;
	}

/*
=================================================
	FGEnumCastToVertexType
=================================================
*/
	ND_ static EVertexType  FGEnumCastToVertexType (SpvReflectFormat value)
	{
		ENABLE_ENUM_CHECKS();
		switch ( value )
		{
			case SPV_REFLECT_FORMAT_UNDEFINED :				break;
			case SPV_REFLECT_FORMAT_R32_UINT :				return EVertexType::UInt;
			case SPV_REFLECT_FORMAT_R32_SINT :				return EVertexType::Int;
			case SPV_REFLECT_FORMAT_R32_SFLOAT :			return EVertexType::Float;
			case SPV_REFLECT_FORMAT_R32G32_UINT :			return EVertexType::UInt2;
			case SPV_REFLECT_FORMAT_R32G32_SINT :			return EVertexType::Int2;
			case SPV_REFLECT_FORMAT_R32G32_SFLOAT :			return EVertexType::Float2;
			case SPV_REFLECT_FORMAT_R32G32B32_UINT :		return EVertexType::UInt3;
			case SPV_REFLECT_FORMAT_R32G32B32_SINT :		return EVertexType::Int3;
			case SPV_REFLECT_FORMAT_R32G32B32_SFLOAT :		return EVertexType::Float3;
			case SPV_REFLECT_FORMAT_R32G32B32A32_UINT :		return EVertexType::UInt4;
			case SPV_REFLECT_FORMAT_R32G32B32A32_SINT :		return EVertexType::Int4;
			case SPV_REFLECT_FORMAT_R32G32B32A32_SFLOAT :	return EVertexType::Float4;
		}
		DISABLE_ENUM_CHECKS();
		RETURN_ERR( "unknown vertex fromat!" );
	}

/*
=================================================
	FGEnumCastToFragOutput
=================================================
*/
	ND_ static EFragOutput  FGEnumCastToFragOutput (SpvReflectFormat value)
	{
		ENABLE_ENUM_CHECKS();
		switch ( value )
		{
			case SPV_REFLECT_FORMAT_UNDEFINED :				break;
			case SPV_REFLECT_FORMAT_R32_UINT :
			case SPV_REFLECT_FORMAT_R32G32_UINT :
			case SPV_REFLECT_FORMAT_R32G32B32_UINT :
			case SPV_REFLECT_FORMAT_R32G32B32A32_UINT :		return EFragOutput::UInt4;
			case SPV_REFLECT_FORMAT_R32_SINT :
			case SPV_REFLECT_FORMAT_R32G32_SINT :
			case SPV_REFLECT_FORMAT_R32G32B32_SINT :
			case SPV_REFLECT_FORMAT_R32G32B32A32_SINT :		return EFragOutput::Int4;
			case SPV_REFLECT_FORMAT_R32_SFLOAT :
			case SPV_REFLECT_FORMAT_R32G32_SFLOAT :
			case SPV_REFLECT_FORMAT_R32G32B32_SFLOAT :
			case SPV_REFLECT_FORMAT_R32G32B32A32_SFLOAT :	return EFragOutput::Float4;
		}
		DISABLE_ENUM_CHECKS();
		RETURN_ERR( "unknown vertex fromat!" );
	}
	
/*
=================================================
	_GetVertexInputReflection
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::_GetVertexInputReflection (const SpvReflectShaderModule &module, INOUT VertexAttribs_t &attribs) const
	{
		const auto	GetAttrib = [&attribs] (uint location) -> VertexInputState::VertexAttrib*
								{
									for (auto& attr : attribs) {
										if ( attr.index == location )
											return &attr;
									}
									return null;
								};

		for (uint i = 0; i < module.input_variable_count; ++i)
		{
			auto&	src = module.input_variables[i];
			auto*	dst = GetAttrib( src.location );

			if ( not dst )
				continue;

			//ASSERT( dst->type == FGEnumCastToVertexType( src.format ));
			dst->id = VertexID( ToString(src.location) );
		}
		return true;
	}
	
/*
=================================================
	_GetFragmentOutputReflection
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::_GetFragmentOutputReflection (const SpvReflectShaderModule &module, INOUT FragmentOutputs_t &fragOutput) const
	{
		const auto	GetFragOutput = [&fragOutput] (uint location) -> GraphicsPipelineDesc::FragmentOutput*
									{
										for (auto& frag : fragOutput) {
											if ( frag.index == location )
												return &frag;
										}
										return null;
									};

		for (uint i = 0; i < module.output_variable_count; ++i)
		{
			auto&	src = module.output_variables[i];
			auto*	dst = GetFragOutput( src.location );

			if ( not dst )
				continue;

			ASSERT( dst->type == FGEnumCastToFragOutput( src.format ));
			dst->id = RenderTargetID( ToString(src.location) );
		}
		return true;
	}

/*
=================================================
	CreateComputePipelines
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::CreateComputePipelines (const TraceRange::Iterator &)
	{
		ASSERT(false);
		return true;
	}
	
/*
=================================================
	DestroyPipeline
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::DestroyPipeline (const TraceRange::Iterator &pos)
	{
		//auto const&		packet	= pos.Cast<packet_vkDestroyPipeline>();

		//CHECK( _graphicsPipelines.erase(ResourceID(packet.pipeline)) + _computePipelines.erase(ResourceID(packet.pipeline)) == 1 );
		return true;
	}
//-----------------------------------------------------------------------------

	
/*
=================================================
	IsCompatiblePushConstants
=================================================
*/
	bool FrameGraphConverter::PipelineConverter::PipelineLayoutInfo::IsCompatiblePushConstants (const PipelineLayoutInfo &other) const
	{
		if ( pushConstantRanges.size() != other.pushConstantRanges.size() )
			return false;

		for (auto& lhs : pushConstantRanges)
		{
			auto	rhs = other.pushConstantRanges.find( lhs.first );

			if ( rhs					== other.pushConstantRanges.end()	or
				 lhs.second.offset		!= rhs->second.offset				or
				 lhs.second.size		!= rhs->second.size					or
				 lhs.second.stageFlags	!= rhs->second.stageFlags )
				return false;
		}
		return true;
	}


}	// VTC

#ifdef VTC_ENABLE_SPIRVREFLECT
#	include "spirv_reflect.c"
#endif
