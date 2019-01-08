// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Converters/FrameGraph/DrawCallConverter.h"
#include "Converters/FrameGraph/BufferConverter.h"
#include "Converters/FrameGraph/ImageConverter.h"
#include "Converters/FrameGraph/SamplerConverter.h"
#include "Converters/FrameGraph/FGEnumCast.h"
#include "Converters/Utils/TracePacker.h"
#include "FGPack/FgStructPacker.h"
#include "Generated/VkFormatHelpers.h"
#include "framegraph/Vulkan/Utils/VEnumCast.h"

namespace VTC
{

/*
=================================================
	constructor
=================================================
*/
	FrameGraphConverter::DrawCallConverter::DrawCallConverter (FrameGraphConverter &fgConv) : _fgConv{fgConv}
	{
	}

/*
=================================================
	CreateCommandPool
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CreateCommandPool (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCreateCommandPool>();

		_cmdPools.insert_or_assign( ResourceID(*packet.pCommandPool), CommandPoolInfo{} );
		return true;
	}

/*
=================================================
	DestroyCommandPool
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::DestroyCommandPool (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkDestroyCommandPool>();
		auto	iter	= _cmdPools.find( ResourceID(packet.commandPool) );
		CHECK_ERR( iter != _cmdPools.end() );
		
		for (auto& cmd : iter->second.cmdBuffers)
		{
			CHECK( _cmdBuffers.erase( cmd ) == 1 );
		}

		_cmdPools.erase( iter );
		return true;
	}
	
/*
=================================================
	ResetCommandPool
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::ResetCommandPool (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkResetCommandPool>();
		auto	iter	= _cmdPools.find( ResourceID(packet.commandPool) );
		CHECK_ERR( iter != _cmdPools.end() );

		for (auto& cmd : iter->second.cmdBuffers)
		{
			CHECK( _cmdBuffers.erase( cmd ) == 1 );
		}

		iter->second.cmdBuffers.clear();
		return true;
	}
	
/*
=================================================
	AllocateCommandBuffers
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::AllocateCommandBuffers (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkAllocateCommandBuffers>();
		auto	iter	= _cmdPools.insert({ ResourceID(packet.pAllocateInfo->commandPool), CommandPoolInfo{} }).first;

		for (uint i = 0; i < packet.pAllocateInfo->commandBufferCount; ++i)
		{
			iter->second.cmdBuffers.insert( ResourceID(packet.pCommandBuffers[i]) );
		}
		return true;
	}

/*
=================================================
	FreeCommandBuffers
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::FreeCommandBuffers (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkFreeCommandBuffers>();
		auto	iter	= _cmdPools.find( ResourceID(packet.commandPool) );
		CHECK_ERR( iter != _cmdPools.end() );

		for (uint i = 0; i < packet.commandBufferCount; ++i)
		{
			iter->second.cmdBuffers.erase( ResourceID(packet.pCommandBuffers[i]) );
		}
		return true;
	}
	
/*
=================================================
	BeginCommandBuffer
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::BeginCommandBuffer (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkBeginCommandBuffer>();
		auto	cmd		= _cmdBuffers.insert_or_assign( ResourceID(packet.commandBuffer), CommandBufferState{} ).first;
		auto&	state	= cmd->second;
		
		CHECK( not cmd->second.isRecording );

		state.usageFlags	= packet.pBeginInfo->flags;
		state.isRecording	= true;
		state.threadPacker.reset( new TracePacker{} );
		
		// enable all dynamic states until first pipeline binding
		state.dynamicStates.current.insert( VK_DYNAMIC_STATE_VIEWPORT );
		state.dynamicStates.current.insert( VK_DYNAMIC_STATE_SCISSOR );
		state.dynamicStates.current.insert( VK_DYNAMIC_STATE_LINE_WIDTH );
		state.dynamicStates.current.insert( VK_DYNAMIC_STATE_DEPTH_BIAS );
		state.dynamicStates.current.insert( VK_DYNAMIC_STATE_BLEND_CONSTANTS );
		state.dynamicStates.current.insert( VK_DYNAMIC_STATE_DEPTH_BOUNDS );
		state.dynamicStates.current.insert( VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK );
		state.dynamicStates.current.insert( VK_DYNAMIC_STATE_STENCIL_WRITE_MASK );
		state.dynamicStates.current.insert( VK_DYNAMIC_STATE_STENCIL_REFERENCE );
		state.dynamicStates.current.insert( VK_DYNAMIC_STATE_VIEWPORT_W_SCALING_NV );
		state.dynamicStates.current.insert( VK_DYNAMIC_STATE_DISCARD_RECTANGLE_EXT );
		state.dynamicStates.current.insert( VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_EXT );
		state.dynamicStates.current.insert( VK_DYNAMIC_STATE_VIEWPORT_SHADING_RATE_PALETTE_NV );
		state.dynamicStates.current.insert( VK_DYNAMIC_STATE_VIEWPORT_COARSE_SAMPLE_ORDER_NV );
		state.dynamicStates.current.insert( VK_DYNAMIC_STATE_EXCLUSIVE_SCISSOR_NV );

		return true;
	}
	
/*
=================================================
	EndCommandBuffer
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::EndCommandBuffer (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkEndCommandBuffer>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );

		CHECK( cmd->second.isRecording );

		// reset states
		cmd->second.isRecording		= false;
		cmd->second.computePpln		= Default;
		cmd->second.graphicsPpln	= Default;
		cmd->second.dynamicStates	= Default;
		cmd->second.indexBuffer		= Default;
		cmd->second.vertexBuffers	= Default;

		return true;
	}
	
/*
=================================================
	ResetCommandBuffer
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::ResetCommandBuffer (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkResetCommandBuffer>();

		CHECK( _cmdBuffers.erase( ResourceID(packet.commandBuffer) ) == 1 );
		return true;
	}
	
/*
=================================================
	DestroyDescriptorPool
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CreateDescriptorPool (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCreateDescriptorPool>();
		
		_descriptorPools.insert_or_assign( ResourceID(*packet.pDescriptorPool), DescriptorPoolInfo{} );
		return true;
	}

/*
=================================================
	DestroyDescriptorPool
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::DestroyDescriptorPool (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkDestroyDescriptorPool>();
		auto	iter	= _descriptorPools.find( ResourceID(packet.descriptorPool) );
		CHECK_ERR( iter != _descriptorPools.end() );

		for (auto& set : iter->second.descriptorSets)
		{
			CHECK( _descriptorSets.erase( set ) == 1 );
		}

		_descriptorPools.erase( iter );
		return true;
	}
	
/*
=================================================
	ResetDescriptorPool
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::ResetDescriptorPool (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkResetDescriptorPool>();
		auto	iter	= _descriptorPools.find( ResourceID(packet.descriptorPool) );
		CHECK_ERR( iter != _descriptorPools.end() );
		
		for (auto& set : iter->second.descriptorSets)
		{
			CHECK( _descriptorSets.erase( set ) == 1 );
		}

		iter->second.descriptorSets.clear();
		return true;
	}
	
/*
=================================================
	AllocateDescriptorSets
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::AllocateDescriptorSets (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkAllocateDescriptorSets>();
		auto	iter	= _descriptorPools.insert({ ResourceID(packet.pAllocateInfo->descriptorPool), {} }).first;

		for (uint i = 0; i < packet.pAllocateInfo->descriptorSetCount; ++i)
		{
			iter->second.descriptorSets.insert( ResourceID(packet.pDescriptorSets[i]) );

			auto&	ds = _descriptorSets.insert_or_assign( ResourceID(packet.pDescriptorSets[i]),
											DescriptorSetInfo{ ResourceID(packet.pAllocateInfo->pSetLayouts[i]) }).first->second;

			auto*	layout	= _fgConv._pipelineConv->FindDescriptorSetLayout( ds.layout );
			CHECK_ERR( layout );

			// initialize descriptor set
			ds.descriptors.resize( layout->descriptors.size() );

			for (size_t j = 0; j < ds.descriptors.size(); ++j)
			{
				auto&	src = layout->descriptors[j];
				auto&	dst = ds.descriptors[j];

				dst.descriptorType	= src.descriptorType;
				dst.stageFlags		= src.stageFlags;
			}
		}
		return true;
	}
	
/*
=================================================
	FreeDescriptorSets
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::FreeDescriptorSets (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkFreeDescriptorSets>();
		auto	iter	= _descriptorPools.find( ResourceID(packet.descriptorPool) );
		CHECK_ERR( iter != _descriptorPools.end() );

		for (uint i = 0; i < packet.descriptorSetCount; ++i)
		{
			CHECK( _descriptorSets.erase( ResourceID(packet.pDescriptorSets[i]) ) == 1 );
			CHECK( iter->second.descriptorSets.erase( ResourceID(packet.pDescriptorSets[i]) ) == 1 );
		}
		return true;
	}
	
/*
=================================================
	UpdateDescriptorSets
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::UpdateDescriptorSets (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkUpdateDescriptorSets>();

		for (uint i = 0; i < packet.descriptorWriteCount; ++i)
		{
			auto&	src		= packet.pDescriptorWrites[i];
			auto	ds_iter	= _descriptorSets.find( ResourceID(src.dstSet) );
			
			CHECK_ERR( ds_iter != _descriptorSets.end() );
			CHECK_ERR( src.dstBinding + src.descriptorCount <= ds_iter->second.descriptors.size() );

			// TODO check
			CHECK( src.descriptorCount == 1 );
			CHECK( src.dstArrayElement == 0 );
			CHECK( src.pNext == null );

			for (uint j = 0; j < src.descriptorCount; ++j)
			{
				auto&	dst = ds_iter->second.descriptors[ src.dstBinding + j ];
				CHECK_ERR( dst.descriptorType == src.descriptorType );

				ENABLE_ENUM_CHECKS();
				switch ( dst.descriptorType )
				{
					case VK_DESCRIPTOR_TYPE_SAMPLER :
						CHECK_ERR( src.pImageInfo );
						dst.image.sampler = src.pImageInfo->sampler;
						break;

					case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER :
						CHECK_ERR( src.pImageInfo );
						dst.image.sampler	= src.pImageInfo->sampler;
						dst.image.layout	= src.pImageInfo->imageLayout;
						dst.image.view		= src.pImageInfo->imageView;
						break;

					case VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE :
					case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE :
					case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT :
						CHECK_ERR( src.pImageInfo );
						dst.image.layout	= src.pImageInfo->imageLayout;
						dst.image.view		= src.pImageInfo->imageView;
						break;

					case VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER :
					case VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER :
						CHECK_ERR( src.pTexelBufferView );
						dst.bufferView		= *src.pTexelBufferView;
						break;

					case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER :
					case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER :
					case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC :
					case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC :
						CHECK_ERR( src.pBufferInfo );
						dst.buffer.handle	= src.pBufferInfo->buffer;
						dst.buffer.offset	= src.pBufferInfo->offset;
						dst.buffer.range	= src.pBufferInfo->range;
						break;

					case VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK_EXT :
					case VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV :
					case VK_DESCRIPTOR_TYPE_RANGE_SIZE :
					case VK_DESCRIPTOR_TYPE_MAX_ENUM :
						CHECK(false);
						break;
				}
				DISABLE_ENUM_CHECKS();
			}
		}

		// TODO
		CHECK( packet.descriptorCopyCount == 0 );

		return true;
	}

/*
=================================================
	CmdBindPipeline
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdBindPipeline (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCmdBindPipeline>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK( cmd->second.isRecording );

		ENABLE_ENUM_CHECKS();
		switch ( packet.pipelineBindPoint )
		{
			case VK_PIPELINE_BIND_POINT_GRAPHICS :
			{
				auto	new_ppln = _fgConv._pipelineConv->FindGraphicsPipeline( ResourceID(packet.pipeline) );
				CHECK_ERR( new_ppln );

				_UpdateGraphicsPipelineDynamicStates( INOUT cmd->second.dynamicStates, new_ppln->dynamicStates,
													  uint(new_ppln->viewports.size()), uint(new_ppln->scissors.size()) );

				CHECK_ERR( _UpdateDescriptorSet( INOUT cmd->second.graphicsPpln, new_ppln->layout ));
				CHECK_ERR( _UpdatePushConstants( INOUT cmd->second.graphicsPpln, new_ppln->layout ));

				cmd->second.graphicsPpln.pipelineId = ResourceID(packet.pipeline);
				break;
			}

			case VK_PIPELINE_BIND_POINT_COMPUTE :
			{
				auto	new_ppln = _fgConv._pipelineConv->FindComputePipeline( ResourceID(packet.pipeline) );
				CHECK_ERR( new_ppln );
				
				CHECK_ERR( _UpdateDescriptorSet( INOUT cmd->second.computePpln, new_ppln->layout ));
				CHECK_ERR( _UpdatePushConstants( INOUT cmd->second.computePpln, new_ppln->layout ));

				cmd->second.computePpln.pipelineId = ResourceID(packet.pipeline);
				break;
			}

			case VK_PIPELINE_BIND_POINT_RAY_TRACING_NV :
			case VK_PIPELINE_BIND_POINT_RANGE_SIZE :
			case VK_PIPELINE_BIND_POINT_MAX_ENUM :
				ASSERT(false);
				break;
		}
		DISABLE_ENUM_CHECKS();

		return true;
	}
	
/*
=================================================
	_UpdateDescriptorSet
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_UpdateDescriptorSet (INOUT PipelineState &state, ResourceID pplnLayout) const
	{
		auto	layout_ptr	= _fgConv._pipelineConv->FindPipelineLayout( pplnLayout );
		CHECK_ERR( layout_ptr );

		for (size_t i = 0; i < state.descriptors.size(); ++i)
		{
			auto&	ds = state.descriptors[i];

			if ( i >= layout_ptr->dslayouts.size() )
				ds = DescriptorSetInfo{};
			else
			if ( ds.layout != layout_ptr->dslayouts[i] )
				ds = DescriptorSetInfo( layout_ptr->dslayouts[i] );
		}

		return true;
	}
	
/*
=================================================
	_UpdatePushConstants
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_UpdatePushConstants (INOUT PipelineState &state, ResourceID pplnLayout) const
	{
		if ( state.pipelineId == 0 )
			return true;

		PipelineConverter::PipelineLayoutInfo const*	old_layout	= null;
		PipelineConverter::PipelineLayoutInfo const*	new_layout	= _fgConv._pipelineConv->FindPipelineLayout( pplnLayout );
		{
			auto*	curr_ppln = _fgConv._pipelineConv->FindGraphicsPipeline( ResourceID(state.pipelineId) );
			if ( curr_ppln )
				old_layout = _fgConv._pipelineConv->FindPipelineLayout( curr_ppln->layout );
		}{
			auto*	curr_ppln = _fgConv._pipelineConv->FindComputePipeline( ResourceID(state.pipelineId) );
			if ( curr_ppln )
				old_layout = _fgConv._pipelineConv->FindPipelineLayout( curr_ppln->layout );
		}
		CHECK_ERR( new_layout and old_layout );

		if ( not new_layout->IsCompatiblePushConstants( *old_layout ) )
			state.pushConstants.clear();

		return true;
	}
	
/*
=================================================
	_CheckPipeline
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_CheckPipeline (const PipelineState &state) const
	{
		CHECK_ERR( state.pipelineId );

		PipelineConverter::PipelineLayoutInfo const*	ppln_layout	= null;
		{
			auto*	curr_ppln = _fgConv._pipelineConv->FindGraphicsPipeline( state.pipelineId );
			if ( curr_ppln )
				ppln_layout = _fgConv._pipelineConv->FindPipelineLayout( curr_ppln->layout );
		}{
			auto*	curr_ppln = _fgConv._pipelineConv->FindComputePipeline( state.pipelineId );
			if ( curr_ppln )
				ppln_layout = _fgConv._pipelineConv->FindPipelineLayout( curr_ppln->layout );
		}
		CHECK_ERR( ppln_layout );


		// check if all descriptor sets presents
		for (size_t i = 0; i < state.descriptors.size(); ++i)
		{
			if ( i < ppln_layout->dslayouts.size() )
				CHECK_ERR( _CompareDescriptorLayouts( state.descriptors[i].layout, ppln_layout->dslayouts[i] ))
			else
				CHECK_ERR( state.descriptors[i].layout == 0 );
		}


		// check if all push constants presents
		CHECK_ERR( state.pushConstants.size() == ppln_layout->pushConstantRanges.size() );

		for (auto& pc : ppln_layout->pushConstantRanges)
		{
			auto	iter = state.pushConstants.find( pc.first );
			CHECK_ERR( iter != state.pushConstants.end() );
		}

		return true;
	}
	
/*
=================================================
	_CompareDescriptorLayouts
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_CompareDescriptorLayouts (ResourceID lhs, ResourceID rhs) const
	{
		if ( lhs == rhs )
			return true;

		auto*	ds1 = _fgConv._pipelineConv->FindDescriptorSetLayout( lhs );
		auto*	ds2 = _fgConv._pipelineConv->FindDescriptorSetLayout( rhs );
		CHECK_ERR( ds1 and ds2 );

		if ( ds1->descriptors.size() != ds2->descriptors.size() )
			return false;

		for (size_t i = 0; i < ds1->descriptors.size(); ++i)
		{
			auto&	desc1 = ds1->descriptors[i];
			auto&	desc2 = ds2->descriptors[i];

			if ( desc1.descriptorType != desc2.descriptorType or
				 desc1.stageFlags != desc2.stageFlags )
				return false;
		}
		return true;
	}

/*
=================================================
	_UpdateGraphicsPipelineDynamicStates
=================================================
*/
	void FrameGraphConverter::DrawCallConverter::_UpdateGraphicsPipelineDynamicStates (INOUT DynamicStates &dynamicStates, const HashSet<VkDynamicState> &pplnDynamicStates,
																					   uint viewportCount, uint scissorCount) const
	{
		// VK_DYNAMIC_STATE_VIEWPORT
		if ( pplnDynamicStates.count( VK_DYNAMIC_STATE_VIEWPORT ) )
		{
			if ( dynamicStates.current.count( VK_DYNAMIC_STATE_VIEWPORT ) and
				 dynamicStates.viewportCount.value_or(viewportCount) == viewportCount )
				{}	// keep
			else
				dynamicStates.viewports.fill( std::nullopt );	// undefined
			
			dynamicStates.viewportCount = viewportCount;
		}
		else {
			dynamicStates.viewports.fill( std::nullopt );
			dynamicStates.viewportCount.reset();	// override
		}

		// VK_DYNAMIC_STATE_SCISSOR
		if ( pplnDynamicStates.count( VK_DYNAMIC_STATE_SCISSOR ) )
		{
			if ( dynamicStates.current.count( VK_DYNAMIC_STATE_SCISSOR ) and
				 dynamicStates.scissorCount.value_or(scissorCount) == scissorCount )
				{}	// keep
			else
				dynamicStates.scissors.fill( std::nullopt );	// undefined
			
			dynamicStates.scissorCount = scissorCount;
		}
		else {
			dynamicStates.scissors.fill( std::nullopt );// override
			dynamicStates.scissorCount.reset();
		}

		// VK_DYNAMIC_STATE_LINE_WIDTH
		if ( pplnDynamicStates.count( VK_DYNAMIC_STATE_LINE_WIDTH ) )
		{
			if ( dynamicStates.current.count( VK_DYNAMIC_STATE_LINE_WIDTH ) )
				{}	// keep
			else
				dynamicStates.lineWidth.reset();	// undefined
		}
		else
			dynamicStates.lineWidth.reset();	// override

		// VK_DYNAMIC_STATE_DEPTH_BIAS
		if ( pplnDynamicStates.count( VK_DYNAMIC_STATE_DEPTH_BIAS ) )
		{
			if ( dynamicStates.current.count( VK_DYNAMIC_STATE_DEPTH_BIAS ) )
				{}	// keep
			else
				dynamicStates.depthBias.reset();	// undefined
		}
		else
			dynamicStates.depthBias.reset();	// override

		// VK_DYNAMIC_STATE_BLEND_CONSTANTS
		if ( pplnDynamicStates.count( VK_DYNAMIC_STATE_BLEND_CONSTANTS ) )
		{
			if ( dynamicStates.current.count( VK_DYNAMIC_STATE_BLEND_CONSTANTS ) )
				{}	// keep
			else
				dynamicStates.blendConstants.reset();	// undefined
		}
		else
			dynamicStates.blendConstants.reset();	// override

		// VK_DYNAMIC_STATE_DEPTH_BOUNDS
		if ( pplnDynamicStates.count( VK_DYNAMIC_STATE_DEPTH_BOUNDS ) )
		{
			if ( dynamicStates.current.count( VK_DYNAMIC_STATE_DEPTH_BOUNDS ) )
				{}	// keep
			else
				dynamicStates.depthBounds.reset();	// undefined
		}
		else
			dynamicStates.depthBounds.reset();	// override

		// VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK
		if ( pplnDynamicStates.count( VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK ) )
		{
			if ( dynamicStates.current.count( VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK ) )
				{}	// keep
			else
				dynamicStates.stencilCompareMask = Default;	// undefined
		}
		else
			dynamicStates.stencilCompareMask = Default;	// override

		// VK_DYNAMIC_STATE_STENCIL_WRITE_MASK
		if ( pplnDynamicStates.count( VK_DYNAMIC_STATE_STENCIL_WRITE_MASK ) )
		{
			if ( dynamicStates.current.count( VK_DYNAMIC_STATE_STENCIL_WRITE_MASK ) )
				{}	// keep
			else
				dynamicStates.stencilWriteMask = Default;	// undefined
		}
		else
			dynamicStates.stencilWriteMask = Default;	// override

		// VK_DYNAMIC_STATE_STENCIL_REFERENCE
		if ( pplnDynamicStates.count( VK_DYNAMIC_STATE_STENCIL_REFERENCE ) )
		{
			if ( dynamicStates.current.count( VK_DYNAMIC_STATE_STENCIL_REFERENCE ) )
				{}	// keep
			else
				dynamicStates.stencilReference = Default;	// undefined
		}
		else
			dynamicStates.stencilReference = Default;	// override

		dynamicStates.current = pplnDynamicStates;
	}

/*
=================================================
	CmdSetViewport
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdSetViewport (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCmdSetViewport>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK( cmd->second.isRecording );

		auto&	dynamic_states = cmd->second.dynamicStates;
		CHECK_ERR( dynamic_states.current.count( VK_DYNAMIC_STATE_VIEWPORT ));

		CHECK_ERR( (packet.firstViewport + packet.viewportCount) <= dynamic_states.viewports.size() );

		for (uint i = 0; i < packet.viewportCount; ++i)
		{
			dynamic_states.viewports[packet.firstViewport + i] = packet.pViewports[i];
		}
		return true;
	}
	
/*
=================================================
	CmdSetScissor
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdSetScissor (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCmdSetScissor>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK( cmd->second.isRecording );

		auto&	dynamic_states = cmd->second.dynamicStates;
		CHECK_ERR( dynamic_states.current.count( VK_DYNAMIC_STATE_SCISSOR ));

		CHECK_ERR( (packet.firstScissor + packet.scissorCount) <= dynamic_states.scissors.size() );

		for (uint i = 0; i < packet.scissorCount; ++i)
		{
			dynamic_states.scissors[packet.firstScissor + i] = packet.pScissors[i];
		}
		return true;
	}
	
/*
=================================================
	CmdSetLineWidth
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdSetLineWidth (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCmdSetLineWidth>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK( cmd->second.isRecording );
		
		auto&	dynamic_states = cmd->second.dynamicStates;
		CHECK_ERR( dynamic_states.current.count( VK_DYNAMIC_STATE_LINE_WIDTH ));

		dynamic_states.lineWidth = packet.lineWidth;
		return true;
	}
	
/*
=================================================
	CmdSetDepthBias
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdSetDepthBias (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCmdSetDepthBias>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK( cmd->second.isRecording );
		
		auto&	dynamic_states = cmd->second.dynamicStates;
		CHECK_ERR( dynamic_states.current.count( VK_DYNAMIC_STATE_DEPTH_BIAS ));

		dynamic_states.depthBias = DynamicStates::DepthBias{ packet.depthBiasConstantFactor, packet.depthBiasClamp, packet.depthBiasSlopeFactor };
		return true;
	}
	
/*
=================================================
	CmdSetBlendConstants
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdSetBlendConstants (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCmdSetBlendConstants>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK( cmd->second.isRecording );
		
		auto&	dynamic_states = cmd->second.dynamicStates;
		CHECK_ERR( dynamic_states.current.count( VK_DYNAMIC_STATE_BLEND_CONSTANTS ));

		dynamic_states.blendConstants = float4{ packet.blendConstants[0], packet.blendConstants[1],
												packet.blendConstants[2], packet.blendConstants[3] };
		return true;
	}
	
/*
=================================================
	CmdSetDepthBounds
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdSetDepthBounds (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCmdSetDepthBounds>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK( cmd->second.isRecording );
		
		auto&	dynamic_states = cmd->second.dynamicStates;
		CHECK_ERR( dynamic_states.current.count( VK_DYNAMIC_STATE_DEPTH_BOUNDS ));

		dynamic_states.depthBounds = DynamicStates::DepthBounds{ packet.minDepthBounds, packet.maxDepthBounds };
		return true;
	}
	
/*
=================================================
	CmdSetStencilCompareMask
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdSetStencilCompareMask (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCmdSetStencilCompareMask>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK( cmd->second.isRecording );
		
		auto&	dynamic_states = cmd->second.dynamicStates;
		CHECK_ERR( dynamic_states.current.count( VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK ));

		if ( EnumEq( packet.faceMask, VK_STENCIL_FACE_FRONT_BIT ) )
			dynamic_states.stencilCompareMask[0] = packet.compareMask;
		
		if ( EnumEq( packet.faceMask, VK_STENCIL_FACE_BACK_BIT ) )
			dynamic_states.stencilCompareMask[1] = packet.compareMask;

		return true;
	}
	
/*
=================================================
	CmdSetStencilWriteMask
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdSetStencilWriteMask (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCmdSetStencilWriteMask>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK( cmd->second.isRecording );
		
		auto&	dynamic_states = cmd->second.dynamicStates;
		CHECK_ERR( dynamic_states.current.count( VK_DYNAMIC_STATE_STENCIL_WRITE_MASK ));

		if ( EnumEq( packet.faceMask, VK_STENCIL_FACE_FRONT_BIT ) )
			dynamic_states.stencilWriteMask[0] = packet.writeMask;
		
		if ( EnumEq( packet.faceMask, VK_STENCIL_FACE_BACK_BIT ) )
			dynamic_states.stencilWriteMask[1] = packet.writeMask;

		return true;
	}
	
/*
=================================================
	CmdSetStencilReference
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdSetStencilReference (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCmdSetStencilReference>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK( cmd->second.isRecording );
		
		auto&	dynamic_states = cmd->second.dynamicStates;
		CHECK_ERR( dynamic_states.current.count( VK_DYNAMIC_STATE_STENCIL_REFERENCE ));

		if ( EnumEq( packet.faceMask, VK_STENCIL_FACE_FRONT_BIT ) )
			dynamic_states.stencilReference[0] = packet.reference;
		
		if ( EnumEq( packet.faceMask, VK_STENCIL_FACE_BACK_BIT ) )
			dynamic_states.stencilReference[1] = packet.reference;

		return true;
	}
	
/*
=================================================
	CmdBindDescriptorSets
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdBindDescriptorSets (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCmdBindDescriptorSets>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK( cmd->second.isRecording );
		
		ENABLE_ENUM_CHECKS();
		switch ( packet.pipelineBindPoint )
		{
			case VK_PIPELINE_BIND_POINT_GRAPHICS :
			{
				if ( cmd->second.graphicsPpln.pipelineId )
				{
					auto	curr_ppln = _fgConv._pipelineConv->FindGraphicsPipeline( cmd->second.graphicsPpln.pipelineId );
					CHECK_ERR( curr_ppln );
					CHECK_ERR( curr_ppln->layout == ResourceID(packet.layout) );
				}
				CHECK_ERR( _BindDescriptorSet( INOUT cmd->second.graphicsPpln.descriptors, packet ));
				break;
			}

			case VK_PIPELINE_BIND_POINT_COMPUTE :
			{
				if ( cmd->second.computePpln.pipelineId )
				{
					auto	curr_ppln = _fgConv._pipelineConv->FindComputePipeline( cmd->second.computePpln.pipelineId );
					CHECK_ERR( curr_ppln );
					CHECK_ERR( curr_ppln->layout == ResourceID(packet.layout) );
				}
				CHECK_ERR( _BindDescriptorSet( INOUT cmd->second.computePpln.descriptors, packet ));
				break;
			}

			case VK_PIPELINE_BIND_POINT_RAY_TRACING_NV :
			case VK_PIPELINE_BIND_POINT_RANGE_SIZE :
			case VK_PIPELINE_BIND_POINT_MAX_ENUM :
				ASSERT(false);
				break;
		}
		DISABLE_ENUM_CHECKS();

		return true;
	}
	
/*
=================================================
	_BindDescriptorSet
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_BindDescriptorSet (INOUT DestriptorStates_t &descriptors, const packet_vkCmdBindDescriptorSets &packet) const
	{
		const uint *	dynamic_offsets	= packet.pDynamicOffsets;
		uint			offset_count	= packet.dynamicOffsetCount;

		CHECK_ERR( (dynamic_offsets != null) == (offset_count != 0) );

		for (uint i = 0; i < packet.descriptorSetCount; ++i)
		{
			auto	ds_iter = _descriptorSets.find( ResourceID(packet.pDescriptorSets[i]) );
			CHECK_ERR( ds_iter != _descriptorSets.end() );

			auto&	ds = descriptors[ packet.firstSet + i ];
			
			ds = ds_iter->second;

			for (auto& desc : ds.descriptors)
			{
				if ( desc.descriptorType == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC or
					 desc.descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC )
				{
					CHECK_ERR( offset_count > 0 );

					desc.buffer.dynamicOffset = *dynamic_offsets;

					++dynamic_offsets;
					--offset_count;
				}
			}
		}

		CHECK( offset_count == 0 );
		return true;
	}

/*
=================================================
	CmdBindIndexBuffer
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdBindIndexBuffer (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCmdBindIndexBuffer>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK( cmd->second.isRecording );

		cmd->second.indexBuffer = IndexBufferState{ ResourceID(packet.buffer), packet.offset, FGEnumCast(packet.indexType) };
		return true;
	}
	
/*
=================================================
	CmdBindVertexBuffers
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdBindVertexBuffers (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCmdBindVertexBuffers>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK( cmd->second.isRecording );

		CHECK_ERR( packet.firstBinding + packet.bindingCount <= cmd->second.vertexBuffers.size() );

		for (uint i = 0; i < packet.bindingCount; ++i)
		{
			cmd->second.vertexBuffers[ packet.firstBinding + i ] = VertexBufferState{ ResourceID(packet.pBuffers[i]), packet.pOffsets[i] };
		}
		return true;
	}
	
/*
=================================================
	_PackDescriptors
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_PackDescriptors (const PipelineDescription::DescriptorSets_t &fgDescriptors,
																   const FrameGraphConverter::PipelineConverter::PipelineLayoutInfo &pplnLayout,
																   const DestriptorStates_t &allDescriptors, Ptr<RenderPass> renderPass,
																   TraceRange::Bookmark pos, TracePacker &packer) const
	{
		const auto	ConvertImageView = [this] (const ImageAnalyzer::ImageViewInfo_t &view, INOUT ImageViewDesc &desc) -> bool
									{
										CHECK_ERR( _ConvertImageView( view, OUT desc ));
										if ( desc.aspectMask == EImageAspect::DepthStencil )
											desc.aspectMask = EImageAspect::Depth;
										return true;
									};

		const auto	ds_count		= uint(Min( pplnLayout.dslayouts.size(), fgDescriptors.size() ));
		const auto	descriptors		= ArrayView<DescriptorSetInfo>{ allDescriptors.data(), ds_count };

		packer << uint(descriptors.size());

		for (size_t i = 0; i < descriptors.size(); ++i)
		{
			auto&	set = descriptors[i];
			auto&	fg_ds = fgDescriptors[i];
			CHECK( set.descriptors.size() >= fg_ds.uniforms->size() );

			packer << uint(i);
			packer << uint(fg_ds.uniforms->size());

			for (size_t j = 0; j < set.descriptors.size(); ++j)
			{
				UniformID	name	{ "un"s << ToString(j) };
				auto&		desc	= set.descriptors[j];
				auto		fg_desc	= (*fg_ds.uniforms).find( name );

				if ( fg_desc == fg_ds.uniforms->end() )
					continue;

				CHECK( fg_desc->second.index.VKBinding() == j );

				packer << name;

				switch ( desc.descriptorType )
				{
					case VK_DESCRIPTOR_TYPE_SAMPLER :
					{
						CHECK( std::holds_alternative<PipelineDescription::Sampler>(fg_desc->second.data) );

						if ( desc.image.sampler == VK_NULL_HANDLE ) {
							packer << uint(0);	// unused
							break;
						}

						packer << uint(1);	// BindSampler
						packer << _fgConv._samplerConv->Remap( desc.image.sampler, pos ).Index();
						break;
					}

					case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER :
					{
						CHECK( std::holds_alternative<PipelineDescription::Texture>(fg_desc->second.data) );

						if ( desc.image.view == VK_NULL_HANDLE ) {
							packer << uint(0);	// unused
							break;
						}

						packer << uint(2);	// BindTexture

						auto*	view = _fgConv._imageAnalyzer->GetImageView( ResourceID(desc.image.view), pos );
						CHECK_ERR( view );

						ImageViewDesc	view_desc;
						CHECK_ERR( ConvertImageView( *view, INOUT view_desc ));

						auto	image_id = _fgConv._imageConv->Remap( view->image->id, pos );

						packer << image_id.Index();
						packer << _fgConv._samplerConv->Remap( desc.image.sampler, pos ).Index();
						FGPack_ImageViewDesc( view_desc, packer );
						break;
					}

					case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE :
					case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT :
					{
						CHECK( std::holds_alternative<PipelineDescription::Image>(fg_desc->second.data) or
							   std::holds_alternative<PipelineDescription::SubpassInput>(fg_desc->second.data) );
						
						if ( desc.image.view == VK_NULL_HANDLE ) {
							packer << uint(0);	// unused
							break;
						}

						packer << uint(3);	// BindImage

						auto*	view = _fgConv._imageAnalyzer->GetImageView( ResourceID(desc.image.view), pos );
						CHECK_ERR( view );

						ImageViewDesc	view_desc;
						CHECK_ERR( ConvertImageView( *view, OUT view_desc ));
						
						auto	image_id = _fgConv._imageConv->Remap( view->image->id, pos );

						packer << image_id.Index();
						FGPack_ImageViewDesc( view_desc, packer );
						break;
					}

					case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER :
					case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER :
					case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC :
					case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC :
					{
						CHECK( std::holds_alternative<PipelineDescription::UniformBuffer>(fg_desc->second.data) or
							   std::holds_alternative<PipelineDescription::StorageBuffer>(fg_desc->second.data) );

						if ( desc.buffer.handle == VK_NULL_HANDLE ) {
							packer << uint(0);	// unused
							break;
						}

						packer << uint(4);	// BindBuffer
						packer << _fgConv._bufferConv->Remap( desc.buffer.handle, pos ).Index();
						packer << desc.buffer.offset;
						packer << desc.buffer.range;
						packer << desc.buffer.dynamicOffset;
						break;
					}
																	 
					//case VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER :
					//case VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER :
					default :
						RETURN_ERR( "not supported" );
				}
			}
		}

		return true;
	}

/*
=================================================
	_PackBaseDrawCall
----
	see unpacker in 'FGPlayer_v100::_UnpackBaseDrawCall'
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_PackBaseDrawCall (const CommandBufferState &cmd, TraceRange::Bookmark pos, TracePacker &packer) const
	{
		CHECK_ERR( _CheckPipeline( cmd.graphicsPpln ));
		
		auto*	curr_ppln	= _fgConv._pipelineConv->FindGraphicsPipeline( cmd.graphicsPpln.pipelineId );

		// pack descriptor sets (pipeline resources)
		CHECK_ERR( _PackDescriptors( curr_ppln->fgPipeline->first.layout.descriptorSets,
									 *_fgConv._pipelineConv->FindPipelineLayout( curr_ppln->layout ),
									 cmd.graphicsPpln.descriptors, cmd.renderPass, pos, packer ));

		// pack push constants
		packer << uint(cmd.graphicsPpln.pushConstants.size());

		for (auto& pc : cmd.graphicsPpln.pushConstants) {
			FGPack_PushConstantData( pc.second, packer );
		}

		CHECK_ERR( _PackScissors( cmd, packer ));
		CHECK_ERR( _PackColorBuffers( cmd, packer ));
		CHECK_ERR( _PackDynamicStates( cmd, packer ));

		return true;
	}
	
/*
=================================================
	_PackDynamicStates
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_PackDynamicStates (const CommandBufferState &cmd, TracePacker &packer) const
	{
		auto*	curr_ppln	= _fgConv._pipelineConv->FindGraphicsPipeline( cmd.graphicsPpln.pipelineId );
		auto&	ppln_rs		= curr_ppln->fgPipeline->first.renderState;
		auto&	pass_desc	= cmd.renderPass->desc;
		auto&	cmd_ds		= cmd.dynamicStates;

		uint2	stencil_reference		= { ppln_rs.stencil.front.reference, ppln_rs.stencil.back.reference };
		uint2	stencil_write_mask		= { ppln_rs.stencil.front.writeMask, ppln_rs.stencil.back.writeMask };
		uint2	stencil_compare_mask	= { ppln_rs.stencil.front.compareMask, ppln_rs.stencil.back.compareMask };

		if ( ppln_rs.stencil.enabled and curr_ppln->dynamicStates.count( VK_DYNAMIC_STATE_STENCIL_REFERENCE ) )
		{
			CHECK_ERR( cmd_ds.stencilReference[0].has_value() and cmd_ds.stencilReference[1].has_value() );
			stencil_reference[0] = cmd_ds.stencilReference[0].value();
			stencil_reference[1] = cmd_ds.stencilReference[1].value();
		}

		if ( ppln_rs.stencil.enabled and curr_ppln->dynamicStates.count( VK_DYNAMIC_STATE_STENCIL_WRITE_MASK ) )
		{
			CHECK_ERR( cmd_ds.stencilWriteMask[0].has_value() and cmd_ds.stencilWriteMask[1].has_value() );
			stencil_write_mask[0] = cmd_ds.stencilWriteMask[0].value();
			stencil_write_mask[1] = cmd_ds.stencilWriteMask[1].value();
		}

		if ( ppln_rs.stencil.enabled and curr_ppln->dynamicStates.count( VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK ) )
		{
			CHECK_ERR( cmd_ds.stencilCompareMask[0].has_value() and cmd_ds.stencilCompareMask[1].has_value() );
			stencil_compare_mask[0] = cmd_ds.stencilCompareMask[0].value();
			stencil_compare_mask[1] = cmd_ds.stencilCompareMask[1].value();
		}

		// separate dynamic stencil states is not supported
		if ( ppln_rs.stencil.enabled )
		{
			CHECK_ERR( stencil_reference[0] == stencil_reference[1] );
			CHECK_ERR( stencil_write_mask[0] == stencil_write_mask[1] );
			CHECK_ERR( stencil_compare_mask[0] == stencil_compare_mask[1] );
		}

		_fg_hidden_::DynamicStates	dyn_states;

		using StencilValue_t = decltype(dyn_states.stencilReference);

		dyn_states.hasStencilTest			= (ppln_rs.stencil.enabled != pass_desc.stencilState.enabled);
		dyn_states.hasStencilFailOp			= ppln_rs.stencil.enabled ? (ppln_rs.stencil.front.failOp != pass_desc.stencilState.front.failOp) : Default;
		dyn_states.hasStencilDepthFailOp	= ppln_rs.stencil.enabled ? (ppln_rs.stencil.front.depthFailOp != pass_desc.stencilState.front.depthFailOp) : Default;
		dyn_states.hasStencilPassOp			= ppln_rs.stencil.enabled ? (ppln_rs.stencil.front.passOp != pass_desc.stencilState.front.passOp) : Default;
		dyn_states.hasStencilReference		= ppln_rs.stencil.enabled ? (stencil_reference[0] != pass_desc.stencilState.front.reference) : 0;
		dyn_states.hasStencilWriteMask		= ppln_rs.stencil.enabled ? (stencil_write_mask[0] != pass_desc.stencilState.front.writeMask) : 0;
		dyn_states.hasStencilCompareMask	= ppln_rs.stencil.enabled ? (stencil_compare_mask[0] != pass_desc.stencilState.front.compareMask) : 0;
		
		dyn_states.hasDepthTest				= (ppln_rs.depth.test != pass_desc.depthState.test);
		dyn_states.hasDepthWrite			= (ppln_rs.depth.write != pass_desc.depthState.write);
		dyn_states.hasDepthCompareOp		= (ppln_rs.depth.compareOp != pass_desc.depthState.compareOp);
		dyn_states.hasCullMode				= (ppln_rs.rasterization.cullMode != pass_desc.rasterizationState.cullMode);

		dyn_states.hasRasterizedDiscard		= (ppln_rs.rasterization.rasterizerDiscard != pass_desc.rasterizationState.rasterizerDiscard);
		dyn_states.hasFrontFaceCCW			= (ppln_rs.rasterization.frontFaceCCW != pass_desc.rasterizationState.frontFaceCCW);

		dyn_states.stencilFailOp			= ppln_rs.stencil.front.failOp;
		dyn_states.stencilDepthFailOp		= ppln_rs.stencil.front.depthFailOp;
		dyn_states.stencilPassOp			= ppln_rs.stencil.front.passOp;
		dyn_states.stencilReference			= StencilValue_t( stencil_reference[0] );
		dyn_states.stencilWriteMask			= StencilValue_t( stencil_write_mask[0] );
		dyn_states.stencilCompareMask		= StencilValue_t( stencil_compare_mask[0] );
		dyn_states.stencilTest				= ppln_rs.stencil.enabled;

		dyn_states.depthCompareOp			= ppln_rs.depth.compareOp;
		dyn_states.depthTest				= ppln_rs.depth.test;
		dyn_states.depthWrite				= ppln_rs.depth.write;
		
		dyn_states.cullMode					= ppln_rs.rasterization.cullMode;
		dyn_states.rasterizerDiscard		= ppln_rs.rasterization.rasterizerDiscard;
		dyn_states.frontFaceCCW				= ppln_rs.rasterization.frontFaceCCW;

		CHECK_ERR( not dyn_states.hasStencilFailOp      or (ppln_rs.stencil.front.failOp == ppln_rs.stencil.back.failOp) );
		CHECK_ERR( not dyn_states.hasStencilDepthFailOp or (ppln_rs.stencil.front.depthFailOp == ppln_rs.stencil.back.depthFailOp) );
		CHECK_ERR( not dyn_states.hasStencilPassOp      or (ppln_rs.stencil.front.passOp == ppln_rs.stencil.back.passOp) );

		FGPack_DrawTaskDynamicStates( dyn_states, packer );
		return true;
	}
	
/*
=================================================
	_PackColorBuffers
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_PackColorBuffers (const CommandBufferState &cmd, TracePacker &packer) const
	{
		auto	pipeline	= _fgConv._pipelineConv->FindGraphicsPipeline( cmd.graphicsPpln.pipelineId );
		CHECK_ERR( pipeline );
		CHECK_ERR( cmd.renderPass->isInitialized );

		auto&	pass_cb		= cmd.renderPass->desc.colorState.buffers;
		auto&	ppln_cb		= pipeline->fgPipeline->first.renderState.color.buffers;
		bool	is_equal	= true;

		for (auto& lhs : ppln_cb)
		{
			auto	rhs = pass_cb.find( lhs.first );
			CHECK_ERR( rhs != pass_cb.end() );

			is_equal &= (lhs.second == rhs->second);
		}

		if ( is_equal )
		{
			packer << uint(0);	// color buffer count
			return true;
		}
		
		packer << uint(ppln_cb.size());
		for (auto& lhs : ppln_cb)
		{
			packer << lhs.first;
			FGPack_ColorBuffer( lhs.second, packer );
		}

		return true;
	}

/*
=================================================
	_PackScissors
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_PackScissors (const CommandBufferState &cmd, TracePacker &packer) const
	{
		const uint		cnt		= Min( cmd.dynamicStates.viewportCount.value_or(0), cmd.dynamicStates.scissorCount.value_or(0) );
		BitSet<32>		diff	{0};

		for (uint i = 0; i < cnt; ++i)
		{
			if ( not (cmd.dynamicStates.viewports[i].has_value() and cmd.dynamicStates.scissors[i].has_value()) )
				continue;
			
			auto&	vp	= cmd.dynamicStates.viewports[i].value();
			auto&	sc	= cmd.dynamicStates.scissors[i].value();

			RectI	r1, r2;
			r1.right = int(vp.width + 0.5f);				r1.bottom = int(vp.height + 0.5f);

			r2.left  = sc.offset.x;							r2.top    = sc.offset.y;
			r2.right = sc.offset.x + int(sc.extent.width);	r2.bottom = sc.offset.y + int(sc.extent.height);

			diff[i] = not All( r1 == r2 );
		}

		if ( diff.none() )
		{
			packer << uint(0);	// scissor count
			return true;
		}


		packer << cnt;

		for (uint i = 0; i < cnt; ++i)
		{
			ASSERT( cmd.dynamicStates.viewports[i].has_value() );
			
			auto&	vp	= cmd.dynamicStates.viewports[i].value();

			if ( cmd.dynamicStates.scissors[i].has_value() )
			{
				auto&	sc	= cmd.dynamicStates.scissors[i].value();
				RectI	r2;
				r2.left  = sc.offset.x;							r2.top    = sc.offset.y;
				r2.right = sc.offset.x + int(sc.extent.width);	r2.bottom = sc.offset.y + int(sc.extent.height);

				FGPack_Rectangle( r2, packer );
			}
			else
			{
				RectI	r1;
				r1.right  = int(vp.width + 0.5f);
				r1.bottom = int(vp.height + 0.5f);

				FGPack_Rectangle( r1, packer );
			}
		}

		return true;
	}

/*
=================================================
	_PackBaseDrawVertices
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_PackBaseDrawVertices (const CommandBufferState &cmd, TraceRange::Bookmark pos, TracePacker &packer) const
	{
		auto*	ppln	= _fgConv._pipelineConv->FindGraphicsPipeline( cmd.graphicsPpln.pipelineId );
		CHECK_ERR( ppln );

		// pipeline
		packer << ppln->fgPipeline->second.Index();

		CHECK_ERR( _PackBaseDrawCall( cmd, pos, packer ));

		// vertex input
		FGPack_VertexInputState( ppln->vertexInput, packer );

		// pack vertex buffers
		const uint	vb_count = uint(ppln->vertexInput.BufferBindings().size());
		CHECK_ERR( vb_count >= 0 and vb_count <= cmd.vertexBuffers.size() );
		packer << vb_count;

		for (uint i = 0; i < vb_count; ++i)
		{
			auto&			vb = cmd.vertexBuffers[i];
			VertexBufferID	id{ "vb"s << ToString(i) };

			packer << id;
			packer << _fgConv._bufferConv->Remap( vb.buffer, pos ).Index();
			packer << vb.offset;
		}

		// topology
		packer << ppln->topology;
		packer << ppln->primitiveRestart;

		return true;
	}

/*
=================================================
	CmdDraw
----
	see unpacker in 'FGPlayer_v100::_DrawVertices'
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdDraw (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCmdDraw>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK_ERR( cmd->second.renderPass );
		CHECK( cmd->second.isRecording );
		
		CHECK_ERR( _MergeRenderPassStates( cmd->second ));
		cmd->second.renderPass->drawCallCount++;

		auto&	packer = *cmd->second.renderpassPacker;
		packer.Begin( EPacketID::FgDrawVertices );
		packer << uint(0);	// TODO: thread id
		packer << cmd->second.renderPass->index;

		CHECK_ERR( _PackBaseDrawVertices( cmd->second, pos.GetBookmark(), packer ));

		// commands
		packer << uint(1);
		packer << uint(packet.vertexCount);
		packer << uint(packet.instanceCount);
		packer << uint(packet.firstVertex);
		packer << uint(packet.firstInstance);

		packer.End( EPacketID::FgDrawVertices );
		return true;
	}
	
/*
=================================================
	CmdDrawIndexed
----
	see unpacker in 'FGPlayer_v100::_DrawIndexed'
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdDrawIndexed (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCmdDrawIndexed>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK( cmd->second.isRecording );
		
		CHECK_ERR( _MergeRenderPassStates( cmd->second ));
		cmd->second.renderPass->drawCallCount++;

		auto&	packer = *cmd->second.renderpassPacker;
		packer.Begin( EPacketID::FgDrawIndexed );
		packer << uint(0);	// TODO: thread id
		packer << cmd->second.renderPass->index;
		
		CHECK_ERR( _PackBaseDrawVertices( cmd->second, pos.GetBookmark(), packer ));

		// index buffer
		packer << _fgConv._bufferConv->Remap( cmd->second.indexBuffer.buffer, pos.GetBookmark() ).Index();
		packer << cmd->second.indexBuffer.offset;
		packer << cmd->second.indexBuffer.indexType;

		// commands
		packer << uint(1);
		packer << uint(packet.indexCount);
		packer << uint(packet.instanceCount);
		packer << uint(packet.firstIndex);
		packer << int(packet.vertexOffset);
		packer << uint(packet.firstInstance);

		packer.End( EPacketID::FgDrawIndexed );
		return true;
	}
	
/*
=================================================
	CmdDrawIndirect
----
	see unpacker in 'FGPlayer_v100::_DrawVerticesIndirect'
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdDrawIndirect (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCmdDrawIndirect>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK( cmd->second.isRecording );
		
		CHECK_ERR( _MergeRenderPassStates( cmd->second ));
		cmd->second.renderPass->drawCallCount++;

		auto&	packer = *cmd->second.renderpassPacker;
		packer.Begin( EPacketID::FgDrawVerticesIndirect );
		packer << uint(0);	// TODO: thread id
		packer << cmd->second.renderPass->index;
		
		CHECK_ERR( _PackBaseDrawVertices( cmd->second, pos.GetBookmark(), packer ));

		// commands
		packer << uint(1);
		packer << uint64_t(packet.offset);
		packer << uint(packet.drawCount);
		packer << uint(packet.stride);

		// indirect buffer
		packer << _fgConv._bufferConv->Remap( packet.buffer, pos.GetBookmark() ).Index();
		
		packer.End( EPacketID::FgDrawVerticesIndirect );
		return true;
	}
	
/*
=================================================
	CmdDrawIndexedIndirect
----
	see unpacker in 'FGPlayer_v100::_DrawIndexedIndirect'
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdDrawIndexedIndirect (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCmdDrawIndirect>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK( cmd->second.isRecording );
		
		CHECK_ERR( _MergeRenderPassStates( cmd->second ));
		cmd->second.renderPass->drawCallCount++;

		auto&	packer = *cmd->second.renderpassPacker;
		packer.Begin( EPacketID::FgDrawIndexedIndirect );
		packer << uint(0);	// TODO: thread id
		packer << cmd->second.renderPass->index;
		
		CHECK_ERR( _PackBaseDrawVertices( cmd->second, pos.GetBookmark(), packer ));
		
		// index buffer
		packer << _fgConv._bufferConv->Remap( cmd->second.indexBuffer.buffer, pos.GetBookmark() ).Index();
		packer << cmd->second.indexBuffer.offset;
		packer << cmd->second.indexBuffer.indexType;
		
		// commands
		packer << uint(1);
		packer << uint64_t(packet.offset);
		packer << uint(packet.drawCount);
		packer << uint(packet.stride);
		
		// indirect buffer
		packer << _fgConv._bufferConv->Remap( packet.buffer, pos.GetBookmark() ).Index();
		
		packer.End( EPacketID::FgDrawIndexedIndirect );
		return true;
	}
	
/*
=================================================
	CmdDispatch
----
	see unpacker in 'FGPlayer_v100::_DispatchCompute'
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdDispatch (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCmdDispatch>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK_ERR( cmd->second.computePpln.pipelineId );
		CHECK( cmd->second.isRecording );

		cmd->second.dispatchCount++;

		auto&	packer = *cmd->second.threadPacker;
		packer.Begin( EPacketID::FgDispatchCompute );
		packer << uint(0);	// TODO: thread id
		
		auto*	curr_ppln	= _fgConv._pipelineConv->FindComputePipeline( cmd->second.computePpln.pipelineId );
		CHECK_ERR( curr_ppln );

		auto*	ppln_layout	= _fgConv._pipelineConv->FindPipelineLayout( curr_ppln->layout );
		CHECK_ERR( ppln_layout );

		// pipeline
		packer << curr_ppln->fgPipeline->second.Index();

		// pack descriptor sets (pipeline resources)
		CHECK_ERR( _PackDescriptors( curr_ppln->fgPipeline->first.layout.descriptorSets,
									 *_fgConv._pipelineConv->FindPipelineLayout( curr_ppln->layout ),
									 cmd->second.computePpln.descriptors, null, pos.GetBookmark(), packer ));
		
		// pack push constants
		packer << uint(cmd->second.computePpln.pushConstants.size());

		for (auto& pc : cmd->second.computePpln.pushConstants) {
			FGPack_PushConstantData( pc.second, packer );
		}

		// groupCount
		packer << packet.groupCountX;
		packer << packet.groupCountY;
		packer << packet.groupCountZ;

		// localGroupSize
		packer << bool(false);	// localGroupSize is undefined

		packer.End( EPacketID::FgDispatchCompute );

		return true;
	}
	
/*
=================================================
	CmdDispatchIndirect
----
	see unpacker in 'FGPlayer_v100::_DispatchComputeIndirect'
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdDispatchIndirect (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCmdCopyBuffer>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK( cmd->second.isRecording );
		
		cmd->second.dispatchCount++;

		auto&	packer = *cmd->second.threadPacker;
		packer.Begin( EPacketID::FgDispatchComputeIndirect );
		packer << uint(0);	// TODO: thread id
		
		packer.End( EPacketID::FgDispatchComputeIndirect );

		ASSERT(false);	// not supported
		return false;
	}
	
/*
=================================================
	CmdDispatchBase
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdDispatchBase (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCmdCopyBuffer>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK( cmd->second.isRecording );
		
		cmd->second.dispatchCount++;

		ASSERT(false);	// not supported
		return false;
	}
	
/*
=================================================
	CmdCopyBuffer
----
	see unpacker in 'FGPlayer_v100::_CopyBuffer'
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdCopyBuffer (const TraceRange::Iterator &pos, FrameID frameId)
	{
		auto&	packet	= pos.Cast<packet_vkCmdCopyBuffer>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK( cmd->second.isRecording );

		bool	is_from_host	= _BufferHasHostAccess( ResourceID(packet.srcBuffer), pos.GetBookmark() );
		bool	is_to_host		= _BufferHasHostAccess( ResourceID(packet.dstBuffer), pos.GetBookmark() );
		
		if ( not is_from_host and not is_to_host )
		{}	// copy between device local memory
		else
		if ( is_from_host and not is_to_host )
			return _UpdateBuffer( cmd->second, packet, pos.GetBookmark(), frameId );
		else
		if ( not is_from_host and is_to_host )
			return _ReadBuffer( cmd->second, packet, pos.GetBookmark() );
		else
			RETURN_ERR( "copy between host visible memory is not supported yet" );

		
		auto*	src_info = _fgConv._bufferAnalyzer->GetBuffer( ResourceID(packet.srcBuffer), pos.GetBookmark() );
		auto*	dst_info = _fgConv._bufferAnalyzer->GetBuffer( ResourceID(packet.dstBuffer), pos.GetBookmark() );
		CHECK_ERR( src_info and dst_info );

		auto&	packer = *cmd->second.threadPacker;
		packer.Begin( EPacketID::FgCopyBuffer );
		packer << uint(0);	// TODO: thread id
		
		packer << _fgConv._bufferConv->Remap( packet.srcBuffer, pos.GetBookmark() ).Index();
		packer << _fgConv._bufferConv->Remap( packet.dstBuffer, pos.GetBookmark() ).Index();
		packer << packet.regionCount;

		for (uint i = 0; i < packet.regionCount; ++i)
		{
			auto&	reg = packet.pRegions[i];

			// pack 'CopyBuffer::Region'
			packer << reg.srcOffset;
			packer << reg.dstOffset;
			packer << reg.size;

			CHECK( reg.srcOffset < src_info->createInfo.size	and
				   reg.srcOffset + reg.size <= src_info->createInfo.size );
			CHECK( reg.dstOffset < dst_info->createInfo.size	and
				   reg.dstOffset + reg.size <= dst_info->createInfo.size );
		}
		
		packer.End( EPacketID::FgCopyBuffer );
		return true;
	}
	
/*
=================================================
	CmdCopyImage
----
	see unpacker in 'FGPlayer_v100::_CopyImage'
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdCopyImage (const TraceRange::Iterator &pos, FrameID frameId)
	{
		auto&	packet	= pos.Cast<packet_vkCmdCopyImage>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK( cmd->second.isRecording );

		bool	is_from_host	= _ImageHasHostAccess( ResourceID(packet.srcImage), pos.GetBookmark() );
		bool	is_to_host		= _ImageHasHostAccess( ResourceID(packet.dstImage), pos.GetBookmark() );
		
		if ( not is_from_host and not is_to_host )
		{}	// copy between device local memory
		else
		if ( is_from_host and not is_to_host )
			return _UpdateImage( cmd->second, packet, pos.GetBookmark(), frameId );
		else
		if ( not is_from_host and is_to_host )
			return _ReadImage( cmd->second, packet, pos.GetBookmark() );
		else
			RETURN_ERR( "copy between host visible memory is not supported yet" );


		auto&	packer = *cmd->second.threadPacker;
		packer.Begin( EPacketID::FgCopyImage );
		packer << uint(0);	// TODO: thread id

		packer << _fgConv._imageConv->Remap( packet.srcImage, pos.GetBookmark() ).Index();
		packer << _fgConv._imageConv->Remap( packet.dstImage, pos.GetBookmark() ).Index();
		packer << packet.regionCount;

		for (uint i = 0; i < packet.regionCount; ++i)
		{
			FGPack_CopyImage_Region( packet.pRegions[i], INOUT packer );
		}
		
		packer.End( EPacketID::FgCopyImage );
		return true;
	}
	
/*
=================================================
	CmdBlitImage
----
	see unpacker in 'FGPlayer_v100::_BlitImage'
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdBlitImage (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCmdBlitImage>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK( cmd->second.isRecording );
		
		auto&	packer = *cmd->second.threadPacker;
		packer.Begin( EPacketID::FgBlitImage );
		packer << uint(0);	// TODO: thread id
		
		packer << _fgConv._imageConv->Remap( packet.srcImage, pos.GetBookmark() ).Index();
		packer << _fgConv._imageConv->Remap( packet.dstImage, pos.GetBookmark() ).Index();
		packer << FGEnumCast( packet.filter );
		packer << packet.regionCount;

		for (uint i = 0; i < packet.regionCount; ++i)
		{
			FGPack_BlitImage_Region( packet.pRegions[i], packer );
		}
			
		packer.End( EPacketID::FgBlitImage );
		return true;
	}
	
/*
=================================================
	CmdCopyBufferToImage
----
	see unpacker in 'FGPlayer_v100::_CopyBufferToImage'
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdCopyBufferToImage (const TraceRange::Iterator &pos, FrameID frameId)
	{
		auto&	packet	= pos.Cast<packet_vkCmdCopyBufferToImage>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK( cmd->second.isRecording );
		
		bool	is_from_host	= _BufferHasHostAccess( ResourceID(packet.srcBuffer), pos.GetBookmark() );
		bool	is_to_host		= _ImageHasHostAccess( ResourceID(packet.dstImage), pos.GetBookmark() );

		if ( not is_from_host and not is_to_host )
		{}	// copy between device local memory
		else
		if ( is_from_host and not is_to_host )
			return _UpdateImage( cmd->second, packet, pos.GetBookmark(), frameId );
		else
		if ( not is_from_host and is_to_host )
			return _ReadImage( cmd->second, packet, pos.GetBookmark() );
		else
			RETURN_ERR( "copy between host visible memory is not supported yet" );


		auto&	packer = *cmd->second.threadPacker;
		packer.Begin( EPacketID::FgCopyBufferToImage );
		packer << uint(0);	// TODO: thread id

		packer << _fgConv._bufferConv->Remap( packet.srcBuffer, pos.GetBookmark() ).Index();
		packer << _fgConv._imageConv->Remap( packet.dstImage, pos.GetBookmark() ).Index();
		packer << packet.regionCount;

		for (uint i = 0; i < packet.regionCount; ++i)
		{
			FGPack_BufferImageCopy_Region( packet.pRegions[i], packer );
		}
		
		packer.End( EPacketID::FgCopyBufferToImage );
		return true;
	}
	
/*
=================================================
	CmdCopyImageToBuffer
----
	see unpacker in 'FGPlayer_v100::_CopyImageToBuffer'
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdCopyImageToBuffer (const TraceRange::Iterator &pos, FrameID frameId)
	{
		auto&	packet	= pos.Cast<packet_vkCmdCopyImageToBuffer>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK( cmd->second.isRecording );
		
		bool	is_from_host	= _ImageHasHostAccess( ResourceID(packet.srcImage), pos.GetBookmark() );
		bool	is_to_host		= _BufferHasHostAccess( ResourceID(packet.dstBuffer), pos.GetBookmark() );
		
		if ( not is_from_host and not is_to_host )
		{}	// copy between device local memory
		else
		if ( is_from_host and not is_to_host )
			return _UpdateBuffer( cmd->second, packet, pos.GetBookmark(), frameId );
		else
		if ( not is_from_host and is_to_host )
			return _ReadBuffer( cmd->second, packet, pos.GetBookmark() );
		else
			RETURN_ERR( "copy between host visible memory is not supported yet" );


		auto&	packer = *cmd->second.threadPacker;
		packer.Begin( EPacketID::FgCopyImageToBuffer );
		packer << uint(0);	// TODO: thread id

		packer << _fgConv._imageConv->Remap( packet.srcImage, pos.GetBookmark() ).Index();
		packer << _fgConv._bufferConv->Remap( packet.dstBuffer, pos.GetBookmark() ).Index();
		packer << packet.regionCount;

		for (uint i = 0; i < packet.regionCount; ++i)
		{
			FGPack_BufferImageCopy_Region( packet.pRegions[i], packer );
		}
		
		packer.End( EPacketID::FgCopyImageToBuffer );
		return true;
	}
	
/*
=================================================
	CmdUpdateBuffer
----
	see unpacker in 'FGPlayer_v100::_UpdateBuffer'
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdUpdateBuffer (const TraceRange::Iterator &pos, FrameID frameId)
	{
		auto&	packet	= pos.Cast<packet_vkCmdUpdateBuffer>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK( cmd->second.isRecording );
		
		CHECK( not _BufferHasHostAccess( ResourceID(packet.dstBuffer), pos.GetBookmark() ));

		DataID		data_id = _fgConv._RequestData( pos, packet.header, packet.pData, packet.dataSize, frameId );
		CHECK_ERR( data_id != UMax );

		auto&	packer = *cmd->second.threadPacker;
		packer.Begin( EPacketID::FgUpdateBuffer );
		packer << uint(0);	// TODO: thread id

		packer << _fgConv._bufferConv->Remap( packet.dstBuffer, pos.GetBookmark() ).Index();
		packer << uint(1);	// count
		packer << packet.dstOffset;
		packer << packet.dataSize;
		packer << data_id;
		
		packer.End( EPacketID::FgUpdateBuffer );
		return true;
	}
	
/*
=================================================
	CmdFillBuffer
----
	see unpacker in 'FGPlayer_v100::_FillBuffer'
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdFillBuffer (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCmdFillBuffer>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK( cmd->second.isRecording );
		
		CHECK( not _BufferHasHostAccess( ResourceID(packet.dstBuffer), pos.GetBookmark() ));

		auto&	packer = *cmd->second.threadPacker;
		packer.Begin( EPacketID::FgFillBuffer );
		packer << uint(0);	// TODO: thread id

		packer << _fgConv._bufferConv->Remap( packet.dstBuffer, pos.GetBookmark() ).Index();
		packer << packet.dstOffset;
		packer << packet.size;
		packer << packet.data;
		
		packer.End( EPacketID::FgFillBuffer );
		return true;
	}
	
/*
=================================================
	CmdClearColorImage
----
	see unpacker in 'FGPlayer_v100::_ClearColorImage'
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdClearColorImage (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCmdClearColorImage>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK( cmd->second.isRecording );
		
		CHECK( not _ImageHasHostAccess( ResourceID(packet.image), pos.GetBookmark() ));

		auto*	image = _fgConv._imageAnalyzer->GetImage( ResourceID(packet.image), pos.GetBookmark() );
		CHECK_ERR( image );
		
		auto&	packer = *cmd->second.threadPacker;
		packer.Begin( EPacketID::FgClearColorImage );
		packer << uint(0);	// TODO: thread id

		packer << _fgConv._imageConv->Remap( packet.image, pos.GetBookmark() ).Index();
		packer << packet.rangeCount;

		for (uint i = 0; i < packet.rangeCount; ++i)
		{
			FGPack_ClearColorImage_Range( packet.pRanges[i], packer );
		}

		FGPack_ClearColor( *packet.pColor, image->createInfo.format, packer );
		
		packer.End( EPacketID::FgClearColorImage );
		return true;
	}
	
/*
=================================================
	CmdClearDepthStencilImage
----
	see unpacker in 'FGPlayer_v100::_ClearDepthStencilImage'
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdClearDepthStencilImage (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCmdClearDepthStencilImage>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK( cmd->second.isRecording );

		CHECK( not _ImageHasHostAccess( ResourceID(packet.image), pos.GetBookmark() ));

		auto*	image = _fgConv._imageAnalyzer->GetImage( ResourceID(packet.image), pos.GetBookmark() );
		CHECK_ERR( image );
		
		auto&	packer = *cmd->second.threadPacker;
		packer.Begin( EPacketID::FgClearDepthStencilImage );
		packer << uint(0);	// TODO: thread id
		
		packer << _fgConv._imageConv->Remap( packet.image, pos.GetBookmark() ).Index();
		packer << packet.rangeCount;

		for (uint i = 0; i < packet.rangeCount; ++i)
		{
			FGPack_ClearColorImage_Range( packet.pRanges[i], packer );
		}

		packer << packet.pDepthStencil->depth;
		packer << packet.pDepthStencil->stencil;

		packer.End( EPacketID::FgClearDepthStencilImage );
		return true;
	}
	
/*
=================================================
	CmdClearAttachments
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdClearAttachments (const TraceRange::Iterator &)
	{
		ASSERT(false);	// not supported
		return false;
	}
	
/*
=================================================
	CmdResolveImage
----
	see unpacker in 'FGPlayer_v100::_ResolveImage'
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdResolveImage (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCmdResolveImage>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK( cmd->second.isRecording );
		
		CHECK( not _ImageHasHostAccess( ResourceID(packet.srcImage), pos.GetBookmark() ));
		CHECK( not _ImageHasHostAccess( ResourceID(packet.dstImage), pos.GetBookmark() ));
		
		auto&	packer = *cmd->second.threadPacker;
		packer.Begin( EPacketID::FgResolveImage );
		packer << uint(0);	// TODO: thread id
		
		packer << _fgConv._imageConv->Remap( packet.srcImage, pos.GetBookmark() ).Index();
		packer << _fgConv._imageConv->Remap( packet.dstImage, pos.GetBookmark() ).Index();
		packer << packet.regionCount;

		for (uint i = 0; i < packet.regionCount; ++i)
		{
			FGPack_ResolveImage_Region( packet.pRegions[i], packer );
		}
		
		packer.End( EPacketID::FgResolveImage );
		return true;
	}
	
/*
=================================================
	CmdPushConstants
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdPushConstants (const TraceRange::Iterator &pos)
	{
		const VkShaderStageFlags	graphics_stages =	VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT |
														VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT | VK_SHADER_STAGE_GEOMETRY_BIT |
														VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_TASK_BIT_NV | VK_SHADER_STAGE_MESH_BIT_NV;

		const VkShaderStageFlags	compute_stages	=	VK_SHADER_STAGE_COMPUTE_BIT;

		const VkShaderStageFlags	raytracing_stages =	VK_SHADER_STAGE_RAYGEN_BIT_NV | VK_SHADER_STAGE_ANY_HIT_BIT_NV | VK_SHADER_STAGE_CLOSEST_HIT_BIT_NV |
														VK_SHADER_STAGE_MISS_BIT_NV | VK_SHADER_STAGE_INTERSECTION_BIT_NV | VK_SHADER_STAGE_CALLABLE_BIT_NV;

		auto&	packet	= pos.Cast<packet_vkCmdPushConstants>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK( cmd->second.isRecording );

		auto	pc_layout = _fgConv._pipelineConv->FindPipelineLayout( ResourceID(packet.layout) );
		CHECK_ERR( pc_layout );

		PushConstantID		id;
		VkPushConstantRange	range = {};
		
		for (auto& pc : pc_layout->pushConstantRanges)
		{
			if ( pc.second.stageFlags == packet.stageFlags and
				 IsIntersects( pc.second.offset, pc.second.offset + pc.second.size, packet.offset, packet.offset + packet.size ))
			{
				id    = pc.first;
				range = pc.second;
				break;
			}
		}

		CHECK_ERR( id.IsDefined() );
		CHECK_ERR( packet.offset >= range.offset );
		CHECK_ERR( packet.offset + packet.size <= range.offset + range.size );
		CHECK_ERR( not EnumAny( packet.stageFlags, raytracing_stages ) );	// not supported

		auto&	curr_pc =	EnumAny( packet.stageFlags, graphics_stages ) ? cmd->second.graphicsPpln.pushConstants :
							/*EnumAny( packet.stageFlags, compute_stages )  ?*/ cmd->second.computePpln.pushConstants;
		
		auto&	pc_data	= curr_pc.insert({ id, {} }).first->second;

		pc_data.id   = id;
		pc_data.size = Bytes<uint16_t>{uint16_t( range.size )};
		
		MemCopy( pc_data.data + BytesU{packet.offset - range.offset}, BytesU::SizeOf(pc_data.data), packet.pValues, BytesU{packet.size} );
		return true;
	}
	
/*
=================================================
	CmdBeginRenderPass
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdBeginRenderPass (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCmdBeginRenderPass>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK_ERR( cmd->second.renderPass == null );
		CHECK( cmd->second.isRecording );

		cmd->second.currRenderPass	= ResourceID(packet.pRenderPassBegin->renderPass);
		cmd->second.currFramebuffer	= ResourceID(packet.pRenderPassBegin->framebuffer);
		cmd->second.subpassIndex	= 0;

		auto*	renderpass	= _fgConv._renderPassAnalyzer->GetRenderPass( cmd->second.currRenderPass, pos.GetBookmark() );
		auto*	framebuffer	= _fgConv._renderPassAnalyzer->GetFramebuffer( cmd->second.currFramebuffer, pos.GetBookmark() );
		CHECK_ERR( renderpass and framebuffer );

		RenderPass	rp;
		rp.desc.area  = RectI{0, 0, int(packet.pRenderPassBegin->renderArea.extent.width), int(packet.pRenderPassBegin->renderArea.extent.height)};
		rp.desc.area += int2{packet.pRenderPassBegin->renderArea.offset.x, packet.pRenderPassBegin->renderArea.offset.y};
		rp.index	  = uint(_renderPasses.size());

		CHECK_ERR( _AddRenderPass( *renderpass, *framebuffer, cmd->second.subpassIndex, packet.pRenderPassBegin, pos.GetBookmark(), OUT rp ));

		_renderPasses.push_back( std::move(rp) );
		cmd->second.renderPass = &_renderPasses.back();
		cmd->second.renderpassPacker.reset( new TracePacker{} );
		
		return true;
	}
	
/*
=================================================
	CmdNextSubpass
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdNextSubpass (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCmdNextSubpass>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK_ERR( cmd->second.renderPass );
		CHECK( cmd->second.isRecording );

		CHECK_ERR( _PackRenderPass( cmd->second ));
		
		cmd->second.subpassIndex++;
		
		auto*	renderpass	= _fgConv._renderPassAnalyzer->GetRenderPass( cmd->second.currRenderPass, pos.GetBookmark() );
		auto*	framebuffer	= _fgConv._renderPassAnalyzer->GetFramebuffer( cmd->second.currFramebuffer, pos.GetBookmark() );
		CHECK_ERR( renderpass and framebuffer );

		RenderPass	rp;
		rp.desc.area = cmd->second.renderPass->desc.area;
		rp.index	 = uint(_renderPasses.size());

		CHECK_ERR( _AddRenderPass( *renderpass, *framebuffer, cmd->second.subpassIndex, null, pos.GetBookmark(), OUT rp ));

		_renderPasses.push_back( std::move(rp) );
		cmd->second.renderPass = &_renderPasses.back();
		cmd->second.renderpassPacker.reset( new TracePacker{} );

		return true;
	}

/*
=================================================
	CmdEndRenderPass
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::CmdEndRenderPass (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast<packet_vkCmdEndRenderPass>();
		auto	cmd		= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd != _cmdBuffers.end() );
		CHECK_ERR( cmd->second.renderPass );
		CHECK( cmd->second.isRecording );
		
		CHECK_ERR( _PackRenderPass( cmd->second ));

		cmd->second.renderPass		= null;
		cmd->second.currRenderPass	= 0;
		cmd->second.currFramebuffer	= 0;
		cmd->second.subpassIndex	= UMax;

		return true;
	}
	
/*
=================================================
	CmdNextSubpass
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_AddRenderPass (const RenderPassAnalyzer::RenderPassInfo_t &renderpass,
																 const RenderPassAnalyzer::FramebufferInfo_t &framebuffer,
																 const uint subpassIndex, const VkRenderPassBeginInfo *beginInfo,
																 TraceRange::Bookmark pos, OUT RenderPass &outRP) const
	{
		CHECK_ERR( subpassIndex < renderpass.subpasses.size() );
		CHECK( (beginInfo != null) == (subpassIndex == 0) );

		auto&	subpass = renderpass.subpasses[subpassIndex];

		// convert color attachments
		for (auto& rt : subpass.colorAttachments)
		{
			CHECK_ERR( rt.attachment < framebuffer.imageViews.size() );

			auto*	view = _fgConv._imageAnalyzer->GetImageView( framebuffer.imageViews[rt.attachment], pos );
			CHECK_ERR( view and view->image );

			ImageID			image{ _fgConv._imageConv->Remap( view->image->id, pos )};
			ImageViewDesc	desc;
			CHECK_ERR( _ConvertImageView( *view, OUT desc ));
			desc.swizzle = Default;

			EAttachmentLoadOp	load_op		= EAttachmentLoadOp::Load;
			EAttachmentStoreOp	store_op	= EAttachmentStoreOp::Store;
			
			if ( subpassIndex+1 == renderpass.subpasses.size() )
				store_op = FGEnumCast( renderpass.attachments[rt.attachment].storeOp );

			if ( subpassIndex == 0 )
				load_op = FGEnumCast( renderpass.attachments[rt.attachment].loadOp );

			if ( load_op == EAttachmentLoadOp::Clear )
			{
				CHECK_ERR( beginInfo );

				VkClearColorValue	clear_val	= {};
				EClearValueType		val_type	= VkFormatToClearValueType( renderpass.attachments[rt.attachment].format );

				if ( beginInfo->clearValueCount )
					clear_val = beginInfo->pClearValues[ rt.attachment ].color;
				
				switch ( val_type )
				{
					case EClearValueType::Int :
						outRP.desc.AddTarget( RenderTargetID("rt"s << ToString(rt.attachment)), image, desc,
											  RGBA32i{clear_val.int32[0], clear_val.int32[1], clear_val.int32[2], clear_val.int32[3]},
											  store_op );
						break;

					case EClearValueType::UInt :
						outRP.desc.AddTarget( RenderTargetID("rt"s << ToString(rt.attachment)), image, desc,
											  RGBA32u{clear_val.uint32[0], clear_val.uint32[1], clear_val.uint32[2], clear_val.uint32[3]},
											  store_op );
						break;

					case EClearValueType::Float :
						outRP.desc.AddTarget( RenderTargetID("rt"s << ToString(rt.attachment)), image, desc,
											  RGBA32f{clear_val.float32[0], clear_val.float32[1], clear_val.float32[2], clear_val.float32[3]},
											  store_op );
						break;

					default :
						RETURN_ERR( "unsupported format for clearing color value" );
				}
			}
			else
				outRP.desc.AddTarget( RenderTargetID("rt"s << ToString(rt.attachment)), image, desc, load_op, store_op );

			FG_UNUSED( image.Release() );
		}

		// convert depth attachment
		if ( subpass.depthStencilAttachment.has_value() and
			 subpass.depthStencilAttachment->attachment < renderpass.attachments.size() )
		{
			auto&	rt = subpass.depthStencilAttachment.value();
			CHECK_ERR( rt.attachment < framebuffer.imageViews.size() );

			auto*	view = _fgConv._imageAnalyzer->GetImageView( framebuffer.imageViews[rt.attachment], pos );
			CHECK_ERR( view and view->image );

			ImageID			image{ _fgConv._imageConv->Remap( view->image->id, pos )};
			ImageViewDesc	desc;
			CHECK_ERR( _ConvertImageView( *view, OUT desc ));
			desc.swizzle = Default;
			
			EAttachmentLoadOp	load_op		= EAttachmentLoadOp::Load;
			EAttachmentStoreOp	store_op	= EAttachmentStoreOp::Store;
			
			if ( subpassIndex+1 == renderpass.subpasses.size() )
				store_op = FGEnumCast( renderpass.attachments[rt.attachment].storeOp );

			if ( subpassIndex == 0 )
				load_op = FGEnumCast( renderpass.attachments[rt.attachment].loadOp );
			
			if ( load_op == EAttachmentLoadOp::Clear )
			{
				CHECK_ERR( beginInfo );

				VkClearDepthStencilValue	clear_val = {};

				if ( beginInfo->clearValueCount )
					clear_val = beginInfo->pClearValues[ rt.attachment ].depthStencil;

				outRP.desc.AddTarget( RenderTargetID("depth"), image, desc,
										DepthStencil{clear_val.depth, clear_val.stencil},
										store_op );
			}
			else
				outRP.desc.AddTarget( RenderTargetID("depth"), image, desc, load_op, store_op );

			FG_UNUSED( image.Release() );
		}

		return true;
	}
	
/*
=================================================
	_ConvertImageView
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_ConvertImageView (const ImageAnalyzer::ImageViewInfo_t &view, OUT FG::ImageViewDesc &desc) const
	{
		// map VkComponentSwizzle to FG swizzle value
		const auto	SwizzleMapping = [] (VkComponentSwizzle comp, uint index) -> uint
		{
			switch ( comp ) {
				case VK_COMPONENT_SWIZZLE_ZERO :		return 5;
				case VK_COMPONENT_SWIZZLE_ONE :			return 6;
				case VK_COMPONENT_SWIZZLE_R :			return 1;
				case VK_COMPONENT_SWIZZLE_G :			return 2;
				case VK_COMPONENT_SWIZZLE_B :			return 3;
				case VK_COMPONENT_SWIZZLE_A :			return 4;
				case VK_COMPONENT_SWIZZLE_IDENTITY :	break;
			}
			return index+1;
		};

		ASSERT( view.createInfo.flags == 0 );

		desc.viewType	= FGEnumCast( view.createInfo.viewType );
		desc.format		= FGEnumCast( view.createInfo.format );
		desc.baseLevel	= MipmapLevel{ view.createInfo.subresourceRange.baseMipLevel };
		desc.levelCount	= view.createInfo.subresourceRange.levelCount;
		desc.baseLayer	= ImageLayer{ view.createInfo.subresourceRange.baseArrayLayer };
		desc.layerCount	= view.createInfo.subresourceRange.layerCount;
		desc.swizzle	= ImageSwizzle{uint4{ SwizzleMapping( view.createInfo.components.r, 0 ), SwizzleMapping( view.createInfo.components.g, 1 ),
											  SwizzleMapping( view.createInfo.components.b, 2 ), SwizzleMapping( view.createInfo.components.a, 3 ) }};
		desc.aspectMask	= FGEnumCast( VkImageAspectFlagBits(view.createInfo.subresourceRange.aspectMask) );
		return true;
	}
	
/*
=================================================
	_MergeRenderPassStates
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_MergeRenderPassStates (CommandBufferState &cmd) const
	{
		auto	pipeline = _fgConv._pipelineConv->FindGraphicsPipeline( cmd.graphicsPpln.pipelineId );
		CHECK_ERR( pipeline );

		auto&	render_pass	= *cmd.renderPass;
		auto&	rs			= pipeline->fgPipeline->first.renderState;

		if ( not render_pass.isInitialized )
		{
			render_pass.desc.colorState			= rs.color;
			render_pass.desc.depthState			= rs.depth;
			render_pass.desc.stencilState		= rs.stencil;
			render_pass.desc.rasterizationState	= rs.rasterization;
			render_pass.desc.multisampleState	= rs.multisample;
			render_pass.isInitialized			= true;
			return true;
		}
		
		// check color buffer states
		{
			for (auto& cb : rs.color.buffers) {
				CHECK_ERR( render_pass.desc.colorState.buffers.count( cb.first ));
			}
			CHECK_ERR( rs.color.logicOp == render_pass.desc.colorState.logicOp );
			CHECK_ERR( rs.color.blendColor == render_pass.desc.colorState.blendColor );
		}
		
		// check depth stencil states
		{
			//CHECK_ERR( rs.depth.compareOp == render_pass.desc.depthState.compareOp );
			CHECK_ERR( rs.depth.boundsEnabled == render_pass.desc.depthState.boundsEnabled );

			if ( rs.depth.boundsEnabled )
				CHECK_ERR(All(Equals( rs.depth.bounds, render_pass.desc.depthState.bounds )));

			/*CHECK_ERR( rs.stencil.front.failOp == render_pass.desc.stencilState.front.failOp );
			CHECK_ERR( rs.stencil.back.failOp == render_pass.desc.stencilState.back.failOp );
			CHECK_ERR( rs.stencil.front.depthFailOp == render_pass.desc.stencilState.front.depthFailOp );
			CHECK_ERR( rs.stencil.back.depthFailOp == render_pass.desc.stencilState.back.depthFailOp );
			CHECK_ERR( rs.stencil.front.passOp == render_pass.desc.stencilState.front.passOp );
			CHECK_ERR( rs.stencil.back.passOp == render_pass.desc.stencilState.back.passOp );
			CHECK_ERR( rs.stencil.front.compareOp == render_pass.desc.stencilState.front.compareOp );
			CHECK_ERR( rs.stencil.back.compareOp == render_pass.desc.stencilState.back.compareOp );*/
		}

		// check rasterization states
		/*{
			CHECK_ERR( rs.rasterization.polygonMode == render_pass.desc.rasterizationState.polygonMode );
			CHECK_ERR( rs.rasterization.lineWidth == render_pass.desc.rasterizationState.lineWidth );
			CHECK_ERR( rs.rasterization.depthBiasConstFactor == render_pass.desc.rasterizationState.depthBiasConstFactor );
			CHECK_ERR( rs.rasterization.depthBiasClamp == render_pass.desc.rasterizationState.depthBiasClamp );
			CHECK_ERR( rs.rasterization.depthBiasSlopeFactor == render_pass.desc.rasterizationState.depthBiasSlopeFactor );
			CHECK_ERR( rs.rasterization.depthBias == render_pass.desc.rasterizationState.depthBias );
			CHECK_ERR( rs.rasterization.depthClamp == render_pass.desc.rasterizationState.depthClamp );
		}*/

		// check multisample states
		{
			CHECK_ERR( rs.multisample == render_pass.desc.multisampleState );
		}
		
		return true;
	}
	
/*
=================================================
	_PackRenderPass
----
	see unpacker in 'FGPlayer_v100::_CreateRenderPass'
	see unpacker in 'FGPlayer_v100::_SubmitRenderPass'
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_PackRenderPass (CommandBufferState &cmd) const
	{
		CHECK( cmd.renderpassPacker );

		auto&	rp		= *cmd.renderPass;
		auto&	packer	= *cmd.threadPacker;

		if ( not rp.isInitialized )
		{
			for (auto& rt : rp.desc.renderTargets)
			{
				if ( rt.second.loadOp == EAttachmentLoadOp::Clear	and
					 rt.second.storeOp == EAttachmentStoreOp::Store )
				{
					cmd.renderTargetClear.insert_or_assign( rt.second.image, rt.second.clearValue );
				}
				else
				if ( rt.second.loadOp == EAttachmentLoadOp::Load	and
					 rt.second.storeOp == EAttachmentStoreOp::Store )
				{}
				else
					cmd.renderTargetClear.erase( rt.second.image );
			}

			ASSERT( rp.drawCallCount == 0 );
			return true;
		}

		cmd.drawCallCount += rp.drawCallCount;
		cmd.renderPassCount++;

		// setup render pass
		packer.Begin( EPacketID::FgCreateRenderPass );
		packer << uint(0);	// TODO: thread id

		packer << rp.index;

		// render states
		FGPack_ColorBuffersState( rp.desc.colorState, packer );
		FGPack_DepthBufferState( rp.desc.depthState, packer );
		FGPack_StencilBufferState( rp.desc.stencilState, packer );
		FGPack_RasterizationState( rp.desc.rasterizationState, packer );
		FGPack_MultisampleState( rp.desc.multisampleState, packer );

		// render targets
		packer << uint(rp.desc.renderTargets.size());
		for (auto& rt : rp.desc.renderTargets)
		{
			packer << rt.first;

			if ( rt.second.loadOp == EAttachmentLoadOp::Load )
			{
				auto	cv_iter = cmd.renderTargetClear.find( rt.second.image );
				if ( cv_iter != cmd.renderTargetClear.end() )
				{
					rt.second.clearValue = cv_iter->second;
					rt.second.loadOp	 = EAttachmentLoadOp::Clear;
				}
			}

			FGPack_RenderPassTraget( rt.second, packer );

			cmd.renderTargetClear.erase( rt.second.image );
		}

		// viewport
		packer << uint(rp.desc.viewports.size());
		for (auto& vp : rp.desc.viewports) {
			FGPack_RenderPassViewport( vp, packer );
		}

		// area, ...
		FGPack_Rectangle( rp.desc.area, packer );
		packer << rp.desc.parallelExecution;
		packer << rp.desc.canBeMerged;

		packer.End( EPacketID::FgCreateRenderPass );


		// add draw calls
		packer.Append( *cmd.renderpassPacker );
		cmd.renderpassPacker.reset();


		// submit render pass
		packer.Begin( EPacketID::FgSubmitRenderPass );
		packer << uint(0);	// TODO: thread id
		packer << rp.index;
		packer.End( EPacketID::FgSubmitRenderPass );

		return true;
	}

	bool FrameGraphConverter::DrawCallConverter::CmdExecuteCommands (const TraceRange::Iterator &)
	{
		ASSERT(false);	// not supported
		return false;
	}

	bool FrameGraphConverter::DrawCallConverter::CmdPushDescriptorSet (const TraceRange::Iterator &)
	{
		ASSERT(false);	// not supported
		return false;
	}

	bool FrameGraphConverter::DrawCallConverter::CmdPushDescriptorSetWithTemplate (const TraceRange::Iterator &)
	{
		ASSERT(false);	// not supported
		return false;
	}

/*
=================================================
	QueueSubmit
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::QueueSubmit (const TraceRange::Iterator &pos, FrameID frameId, INOUT TracePacker &packer)
	{
		auto&	packet	= pos.Cast<packet_vkQueueSubmit>();

		for (uint i = 0; i < packet.submitCount; ++i)
		{
			auto&	submit = packet.pSubmits[i];

			for (uint j = 0; j < submit.commandBufferCount; ++j)
			{
				auto	cmd		= _cmdBuffers.find( ResourceID(submit.pCommandBuffers[j]) );
				CHECK_ERR( cmd != _cmdBuffers.end() );
				CHECK_ERR( cmd->second.threadPacker );
				CHECK( not cmd->second.isRecording );

				cmd->second.lastSubmission = frameId;
				cmd->second.submissionCount++;

				packer.Append( *cmd->second.threadPacker );

				if ( EnumEq( cmd->second.usageFlags, VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT ) )
					_cmdBuffers.erase( cmd );
			}
		}

		return true;
	}
	
/*
=================================================
	QueuePresent
----
	see unpacker in 'FGPlayer_v100::_Present'
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::QueuePresent (const TraceRange::Iterator &pos, FrameID frameId, INOUT TracePacker &packer)
	{
		auto&	packet = pos.Cast<packet_vkQueuePresentKHR>();

		for (uint i = 0; i < packet.pPresentInfo->swapchainCount; ++i)
		{
			auto	index		= packet.pPresentInfo->pImageIndices[i];
			auto	swapchain	= packet.pPresentInfo->pSwapchains[i];
			auto*	sw_info		= _fgConv._swapchainAnalyzer->GetSwapchain( ResourceID(swapchain), pos.GetBookmark() );
			CHECK_ERR( sw_info );
			CHECK_ERR( index < sw_info->images.size() );

			auto&	image = sw_info->images[index];

			packer.Begin( EPacketID::FgPresent );
			packer << uint(0);	// TODO: thread id
			packer << _fgConv._imageConv->Remap( image.id, pos.GetBookmark() ).Index();
			packer << uint(0);	// layer
			packer.End( EPacketID::FgPresent );
		}

		_maxRenderPasses = Max( _maxRenderPasses, uint(_renderPasses.size()) );
		_renderPasses.clear();

		return true;
	}

/*
=================================================
	_BufferHasHostAccess
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_BufferHasHostAccess (ResourceID id, TraceRange::Bookmark pos) const
	{
		auto*	buf = _fgConv._bufferAnalyzer->GetBuffer( id, pos );
		CHECK_ERR( buf );

		auto*	mem = _fgConv._memoryObjAnalyzer->GetMemoryObj( buf->memId, pos );
		CHECK_ERR( mem );

		return EnumAny( mem->usage, EMemoryUsage::HostRead | EMemoryUsage::HostWrite );
	}
	
/*
=================================================
	_ImageHasHostAccess
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_ImageHasHostAccess (ResourceID id, TraceRange::Bookmark pos) const
	{
		auto*	img = _fgConv._imageAnalyzer->GetImage( id, pos );
		CHECK_ERR( img );

		auto*	mem = _fgConv._memoryObjAnalyzer->GetMemoryObj( img->memId, pos );
		CHECK_ERR( mem );

		return EnumAny( mem->usage, EMemoryUsage::HostRead | EMemoryUsage::HostWrite );
	}
	
/*
=================================================
	_UpdateImage
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_UpdateImage (CommandBufferState &cmd, const packet_vkCmdCopyBufferToImage &packet,
															   const TraceRange::Bookmark pos, FrameID frameId)
	{
		Array<VkBufferImageCopy>	regions{ packet.pRegions, packet.pRegions + packet.regionCount };

		auto*	cmdbuf = _fgConv._queueAnalyzer->GetCommandBufferInfo( ResourceID(packet.commandBuffer), pos );
		CHECK_ERR( cmdbuf );

		// find the next submit
		TraceRange::Bookmark	submit_pos = _fgConv._appTrace->FullTrace().LastBookmark();

		for (auto& bm : cmdbuf->bookmarks)
		{
			if ( pos < bm.pos and bm.packetId == VKTRACE_TPI_VK_vkQueueSubmit )
			{
				submit_pos = bm.pos;
				break;
			}
		}


		// find last memory usage before submitting commands
		auto*	src_buf = _fgConv._bufferAnalyzer->GetBuffer( ResourceID(packet.srcBuffer), pos );
		CHECK_ERR( src_buf );

		auto*	mem = _fgConv._memoryObjAnalyzer->GetMemoryObj( src_buf->memId, pos );
		CHECK_ERR( mem );

		auto*	dst_img = _fgConv._imageAnalyzer->GetImage( ResourceID(packet.dstImage), pos );
		CHECK_ERR( dst_img );

		const auto	fg_format		= FGEnumCast( dst_img->createInfo.format );
		const auto&	fmt_info		= EPixelFormat_GetInfo( fg_format );
		const auto&	texel_block_dim	= fmt_info.blockSize;
		const auto	texel_size		= fmt_info.bitsPerBlock;

		size_t	mem_last_bm = 0;

		for (size_t i = 0; i < mem->bookmarks.size(); ++i)
		{
			auto&	bm = mem->bookmarks[i];

			if ( bm.pos >= submit_pos )
				break;

			mem_last_bm = i;
		}


		// find memory transfer to buffer
		for (size_t i = mem_last_bm; i < mem->bookmarks.size() and regions.size(); --i)
		{
			auto&	bm = mem->bookmarks[i];

			if ( bm.packetId != VKTRACE_TPI_VK_vkFlushMappedMemoryRanges )
				continue;
			
			auto*	info = _fgConv._memTransferAnalyzer->GetTransfer( mem->id, bm.pos );
			CHECK_ERR( info );

			for (auto& block : info->blocks)
			{
				for (auto iter = regions.begin(); iter != regions.end();)
				{
					const auto	reg = *iter;

					if ( reg.imageExtent.width  < texel_block_dim.x or
						 reg.imageExtent.height < texel_block_dim.y )
					{
						iter = regions.erase( iter );
						continue;
					}

					CHECK( reg.imageOffset.x % texel_block_dim.x == 0 );
					CHECK( reg.imageOffset.y % texel_block_dim.y == 0 );
					CHECK( reg.imageExtent.width % texel_block_dim.x == 0 );
					CHECK( reg.imageExtent.height % texel_block_dim.y == 0 );
					CHECK( reg.imageSubresource.layerCount == 1 );	// TODO
					CHECK( reg.imageExtent.depth == 1 );	// TODO

					// check intersection
					const uint64_t	row_pitch	= (((reg.imageExtent.width + texel_block_dim.x-1) / texel_block_dim.x) * texel_size) / 8;
					const uint64_t	slice_pitch	= ((reg.imageExtent.height + texel_block_dim.y-1) / texel_block_dim.y) * row_pitch;
					//const uint64_trow_pitch	= Max( reg.bufferRowLength * texel_size) / 8, row_pitch1 );
					//const uint64_tslice_pitch	= Max( reg.bufferImageHeight * row_pitch, slice_pitch1 );
					const uint		dim_z		= Max( reg.imageSubresource.layerCount, reg.imageExtent.depth );
					const uint64_t	max_size	= slice_pitch * dim_z;
					const uint64_t	buf_begin	= reg.bufferOffset + src_buf->memOffset;
					const uint64_t	buf_end		= buf_begin + max_size;
					uint64_t		data_begin, data_end;

					if ( GetIntersection( block.memOffset, block.memOffset + block.dataSize, buf_begin, buf_end,
										  OUT data_begin, OUT data_end ) )
					{
									data_begin	 = AlignToLarger( data_begin - buf_begin, row_pitch ) + buf_begin;
						uint64_t	data_size	 = AlignToSmaller( data_end - data_begin, row_pitch );
						uint64_t	block_offset = data_begin - block.memOffset;
						int3		img_offset	 = { reg.imageOffset.x, reg.imageOffset.y, reg.imageOffset.z };
						uint3		img_size	 = { reg.imageExtent.width, reg.imageExtent.height, reg.imageExtent.depth };

						if ( data_size == 0 )
							break;

						img_offset.y += int(((data_begin - buf_begin) / row_pitch) * texel_block_dim.y);
						img_size.y   = uint((data_size / row_pitch) * texel_block_dim.y);

						CHECK( block_offset < block.dataSize and block_offset + data_size <= block.dataSize );
						CHECK( img_offset.y % texel_block_dim.y == 0 );
						CHECK( img_size.y % texel_block_dim.y == 0 );
						CHECK( img_size.y <= reg.imageExtent.height );
						
						DataID		data_id = _fgConv._RequestData( block.fileOffset + block_offset, data_size, frameId );
						CHECK_ERR( data_id != UMax );

						auto&	packer = *cmd.threadPacker;
						packer.Begin( EPacketID::FgUpdateImage );
						packer << uint(0);	// TODO: thread id
						packer << _fgConv._imageConv->Remap( packet.dstImage, pos ).Index();
						FGPack_Vec( img_offset, packer );
						FGPack_Vec( img_size, packer );
						packer << reg.imageSubresource.baseArrayLayer;
						packer << reg.imageSubresource.mipLevel;
						packer << row_pitch;
						packer << uint64_t(0);	//slice_pitch;
						packer << FGEnumCast( reg.imageSubresource.aspectMask );
						packer << data_id;
						packer.End( EPacketID::FgUpdateImage );

						iter = regions.erase( iter );

						if ( max_size == data_size )
						{
							ASSERT( img_offset.y == reg.imageOffset.y and img_size.y == reg.imageExtent.height );
							continue;
						}

						if ( buf_begin != data_begin )
						{
							VkBufferImageCopy	range = reg;
							range.imageExtent.height  = img_offset.y - reg.imageOffset.y;
							regions.push_back( range );
						}

						if ( data_size != max_size )
						{
							VkBufferImageCopy	range = reg;
							range.bufferOffset			= data_begin + data_size - src_buf->memOffset;
							range.imageOffset.y			= img_offset.y + int(img_size.y);
							range.imageExtent.height	= reg.imageOffset.y + reg.imageExtent.height - range.imageOffset.y;
							regions.push_back( range );
						}

						iter = regions.begin();
					}
					else
						++iter;
				}
			}
		}

		//CHECK_ERR( regions.empty() );
		return true;
	}
	
/*
=================================================
	_UpdateImage
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_UpdateImage (CommandBufferState &cmd, const packet_vkCmdCopyImage &packet,
															   const TraceRange::Bookmark pos, FrameID frameId)
	{
		Array<VkImageCopy>	regions{ packet.pRegions, packet.pRegions + packet.regionCount };

		auto*	cmdbuf = _fgConv._queueAnalyzer->GetCommandBufferInfo( ResourceID(packet.commandBuffer), pos );
		CHECK_ERR( cmdbuf );

		// find the next submit
		TraceRange::Bookmark	submit_pos = _fgConv._appTrace->FullTrace().LastBookmark();

		for (auto& bm : cmdbuf->bookmarks)
		{
			if ( pos < bm.pos and bm.packetId == VKTRACE_TPI_VK_vkQueueSubmit )
			{
				submit_pos = bm.pos;
				break;
			}
		}

		
		// find last memory usage before submitting commands
		auto*	src_img = _fgConv._imageAnalyzer->GetImage( ResourceID(packet.srcImage), pos );
		CHECK_ERR( src_img );

		auto*	mem = _fgConv._memoryObjAnalyzer->GetMemoryObj( src_img->memId, pos );
		CHECK_ERR( mem );

		auto*	dst_img = _fgConv._imageAnalyzer->GetImage( ResourceID(packet.dstImage), pos );
		CHECK_ERR( dst_img );
		
		const auto	src_fmt_info = EPixelFormat_GetInfo( FGEnumCast( src_img->createInfo.format ));
		const auto	dst_fmt_info = EPixelFormat_GetInfo( FGEnumCast( dst_img->createInfo.format ));

		size_t		mem_last_bm	= 0;

		for (size_t i = 0; i < mem->bookmarks.size(); ++i)
		{
			auto&	bm = mem->bookmarks[i];

			if ( bm.pos >= submit_pos )
				break;

			mem_last_bm = i;
		}

		
		// find memory transfer to buffer
		for (size_t i = mem_last_bm; i < mem->bookmarks.size() and regions.size(); --i)
		{
			auto&	bm = mem->bookmarks[i];

			if ( bm.packetId != VKTRACE_TPI_VK_vkFlushMappedMemoryRanges )
				continue;
			
			auto*	info = _fgConv._memTransferAnalyzer->GetTransfer( mem->id, bm.pos );
			CHECK_ERR( info );

			for (auto& block : info->blocks)
			{
				for (auto iter = regions.begin(); iter != regions.end();)
				{
					auto&	reg = *iter;
					
					// check intersection
					const uint3	src_img_dim	= Max( uint3(src_img->createInfo.extent.width, src_img->createInfo.extent.height, src_img->createInfo.extent.depth) >> reg.srcSubresource.mipLevel, 1u );
					const uint3	dst_img_dim	= Max( uint3(dst_img->createInfo.extent.width, dst_img->createInfo.extent.height, dst_img->createInfo.extent.depth) >> reg.dstSubresource.mipLevel, 1u );
					
					CHECK( src_img_dim.x % src_fmt_info.blockSize.x == 0 );
					CHECK( src_img_dim.y % src_fmt_info.blockSize.y == 0 );
					CHECK( dst_img_dim.x % dst_fmt_info.blockSize.x == 0 );
					CHECK( dst_img_dim.y % dst_fmt_info.blockSize.y == 0 );
					CHECK( reg.srcSubresource.layerCount == 1 );
					CHECK( reg.dstSubresource.layerCount == 1 );

					uint64_t	src_row_pitch		= ((src_img_dim.x / src_fmt_info.blockSize.x) * src_fmt_info.bitsPerBlock) / 8;
					uint64_t	src_slice_pitch		= (src_img_dim.y / src_fmt_info.blockSize.y) * src_row_pitch;
					uint64_t	dst_row_pitch		= ((dst_img_dim.x / dst_fmt_info.blockSize.x) * dst_fmt_info.bitsPerBlock) / 8;
					uint64_t	dst_slice_pitch		= (dst_img_dim.y / dst_fmt_info.blockSize.y) * dst_row_pitch;
					uint64_t	src_mem_offset		= src_img->memOffset;
					auto		src_layout			= src_img->subresLayouts.find(ImageAnalyzer::ImageSubresource{ reg.srcSubresource });
					auto		dst_layout			= dst_img->subresLayouts.find(ImageAnalyzer::ImageSubresource{ reg.dstSubresource });

					if ( src_layout != src_img->subresLayouts.end() ) {
						src_row_pitch	= src_layout->second.rowPitch;
						src_slice_pitch	= src_layout->second.arrayPitch;	// TODO
						src_mem_offset	= src_layout->second.offset + src_img->memOffset;
					}
					if ( dst_layout != dst_img->subresLayouts.end() ) {
						dst_row_pitch	= dst_layout->second.rowPitch;
						dst_slice_pitch	= dst_layout->second.arrayPitch;	// TODO
					}

					// solid memory
					if ( reg.srcOffset.x == 0 and reg.srcOffset.y == 0 and reg.srcOffset.z == 0 and
						 reg.dstOffset.x == 0 and reg.dstOffset.y == 0 and reg.dstOffset.z == 0 and
						 reg.extent.width == src_img_dim.x and reg.extent.height == src_img_dim.y and
						 reg.extent.width == dst_img_dim.x and reg.extent.height == dst_img_dim.y )
					{
						uint64_t	data_size = src_slice_pitch * src_img_dim.z;
						uint64_t	data_begin, data_end;
						
						if ( GetIntersection( block.memOffset, block.memOffset + block.dataSize, src_mem_offset, src_mem_offset + data_size,
											  OUT data_begin, OUT data_end ) )
						{
							CHECK( data_begin == src_mem_offset );
							CHECK( data_end == src_mem_offset + data_size );
							
										data_size	 = data_end - data_begin;
							uint64_t	block_offset = data_begin - block.memOffset;
							int3		img_offset	 = { reg.dstOffset.x, reg.dstOffset.y, reg.dstOffset.z };
							uint3		img_size	 = { reg.extent.width, reg.extent.height, reg.extent.depth };

							DataID		data_id = _fgConv._RequestData( block.fileOffset + block_offset, data_size, frameId );
							CHECK_ERR( data_id != UMax );

							auto&	packer = *cmd.threadPacker;
							packer.Begin( EPacketID::FgUpdateImage );
							packer << uint(0);	// TODO: thread id
							packer << _fgConv._imageConv->Remap( packet.dstImage, pos ).Index();
							FGPack_Vec( img_offset, packer );
							FGPack_Vec( img_size, packer );
							packer << reg.dstSubresource.baseArrayLayer;
							packer << reg.dstSubresource.mipLevel;
							packer << uint64_t(0);	// TODO
							packer << uint64_t(0);
							packer << FGEnumCast( reg.dstSubresource.aspectMask );
							packer << data_id;
							packer.End( EPacketID::FgUpdateImage );

							iter = regions.erase( iter );
						}
						else
							++iter;
					}
					else
					// separate memory blocks
					{
						CHECK(false);
					}
				}
			}
		}

		CHECK_ERR( regions.empty() );
		return true;
	}
	
/*
=================================================
	_ReadImage
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_ReadImage (CommandBufferState &cmd, const packet_vkCmdCopyBufferToImage &packet, const TraceRange::Bookmark pos)
	{
		FG_UNUSED( cmd, packet, pos );
		return true;
	}
	
/*
=================================================
	_ReadImage
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_ReadImage (CommandBufferState &cmd, const packet_vkCmdCopyImage &packet, const TraceRange::Bookmark pos)
	{
		FG_UNUSED( cmd, packet, pos );
		return true;
	}
	
/*
=================================================
	_UpdateBuffer
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_UpdateBuffer (CommandBufferState &cmd, const packet_vkCmdCopyBuffer &packet,
																const TraceRange::Bookmark pos, FrameID frameId)
	{
		Array<VkBufferCopy>		regions{ packet.pRegions, packet.pRegions + packet.regionCount };

		auto*	cmdbuf = _fgConv._queueAnalyzer->GetCommandBufferInfo( ResourceID(packet.commandBuffer), pos );
		CHECK_ERR( cmdbuf );

		auto*	dst_buf = _fgConv._bufferAnalyzer->GetBuffer( ResourceID(packet.dstBuffer), pos );
		CHECK_ERR( dst_buf );

		// find the next submit
		TraceRange::Bookmark	submit_pos = _fgConv._appTrace->FullTrace().LastBookmark();

		for (auto& bm : cmdbuf->bookmarks)
		{
			if ( pos < bm.pos and bm.packetId == VKTRACE_TPI_VK_vkQueueSubmit )
			{
				submit_pos = bm.pos;
				break;
			}
		}


		// find last memory usage before submitting commands
		auto*	src_buf = _fgConv._bufferAnalyzer->GetBuffer( ResourceID(packet.srcBuffer), pos );
		CHECK_ERR( src_buf );

		auto*	mem = _fgConv._memoryObjAnalyzer->GetMemoryObj( src_buf->memId, pos );
		CHECK_ERR( mem );

		size_t	mem_last_bm = 0;

		for (size_t i = 0; i < mem->bookmarks.size(); ++i)
		{
			auto&	bm = mem->bookmarks[i];

			if ( bm.pos >= submit_pos )
				break;

			mem_last_bm = i;
		}


		// find memory transfer to buffer
		for (size_t i = mem_last_bm; i < mem->bookmarks.size() and regions.size(); --i)
		{
			auto&	bm = mem->bookmarks[i];

			if ( bm.packetId != VKTRACE_TPI_VK_vkFlushMappedMemoryRanges )
				continue;
			
			auto*	info = _fgConv._memTransferAnalyzer->GetTransfer( mem->id, bm.pos );
			CHECK_ERR( info );

			//   |========================= memory ===============================|
			//   |          |========== block ==========|
			//   |          |    |============= src_buffer ===============|
			//   |          |    |      |=== reg ====|
			//   |<-------->|    |<---->|
			//   |<---|--------->|     \
			//        |         \      reg.srcOffset
			//  block.memOffset  src_buffer.memOffset

			for (auto& block : info->blocks)
			{
				for (auto iter = regions.begin(); iter != regions.end();)
				{
					const auto	reg = *iter;

					const uint64_t	max_size	= Min( reg.size, dst_buf->createInfo.size - reg.dstOffset, src_buf->createInfo.size - reg.srcOffset );
					const uint64_t	buf_begin	= reg.srcOffset + src_buf->memOffset;
					const uint64_t	buf_end		= buf_begin + max_size;
					uint64_t		data_begin, data_end;
					
					if ( GetIntersection( block.memOffset, block.memOffset + block.dataSize, buf_begin, buf_end,
										  OUT data_begin, OUT data_end ) )
					{
						uint64_t	data_size	 = data_end - data_begin;
						uint64_t	block_offset = buf_begin - block.memOffset;
						uint64_t	buf_offset	 = reg.dstOffset + (data_begin - buf_begin);

						CHECK( block_offset < block.dataSize	and
							   block_offset + data_size <= block.dataSize );

						DataID	data_id = _fgConv._RequestData( block.fileOffset + block_offset, data_size, frameId );
						CHECK_ERR( data_id != UMax );
						
						CHECK( buf_offset < dst_buf->createInfo.size	and
							   buf_offset + data_size <= dst_buf->createInfo.size );

						auto&	packer = *cmd.threadPacker;
						packer.Begin( EPacketID::FgUpdateBuffer );
						packer << uint(0);	// TODO: thread id
						packer << _fgConv._bufferConv->Remap( packet.dstBuffer, pos ).Index();
						packer << uint(1);	// count
						packer << buf_offset;
						packer << data_size;
						packer << data_id;
						packer.End( EPacketID::FgUpdateBuffer );

						iter = regions.erase( iter );

						if ( data_size == max_size )
							continue;
						
						if ( data_begin != buf_begin )
							regions.push_back({ reg.srcOffset, reg.dstOffset, data_begin - buf_begin });

						if ( data_end != buf_end )
							regions.push_back({ reg.srcOffset + data_size, reg.dstOffset + data_size, buf_end - data_end });

						iter = regions.begin();
					}
					else
						++iter;
				}
			}
		}

		//CHECK_ERR( regions.empty() );
		return true;
	}
	
/*
=================================================
	_UpdateBuffer
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_UpdateBuffer (CommandBufferState &cmd, const packet_vkCmdCopyImageToBuffer &packet,
																const TraceRange::Bookmark pos, FrameID frameId)
	{
		FG_UNUSED( cmd, packet, pos, frameId );
		ASSERT(false);
		return false;
	}
	
/*
=================================================
	_ReadBuffer
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_ReadBuffer (CommandBufferState &cmd, const packet_vkCmdCopyBuffer &packet, const TraceRange::Bookmark pos)
	{
		FG_UNUSED( cmd, packet, pos );
		return true;
	}
	
/*
=================================================
	_ReadBuffer
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_ReadBuffer (CommandBufferState &cmd, const packet_vkCmdCopyImageToBuffer &packet, const TraceRange::Bookmark pos)
	{
		FG_UNUSED( cmd, packet, pos );
		return true;
	}


}	// VTC
