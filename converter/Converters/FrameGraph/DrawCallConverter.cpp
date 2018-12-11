// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Converters/FrameGraph/DrawCallConverter.h"
#include "Converters/FrameGraph/BufferConverter.h"
#include "Converters/FrameGraph/ImageConverter.h"
#include "Converters/FrameGraph/SamplerConverter.h"
#include "Converters/FrameGraph/FGEnumCast.h"
#include "Converters/Utils/TracePacker.h"
#include "FGPack/FgStructPacker.h"
#include "Types/VkHelpers.h"
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
		state.tracePacker.reset( new TracePacker{ null, true });
		
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
			ASSERT( src.descriptorCount == 1 );
			ASSERT( src.dstArrayElement == 0 );
			ASSERT( src.pNext == null );

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
						ASSERT(false);
						break;
				}
				DISABLE_ENUM_CHECKS();
			}
		}

		// TODO
		ASSERT( packet.descriptorCopyCount == 0 );

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
		ASSERT( cmd->second.isRecording );

		ENABLE_ENUM_CHECKS();
		switch ( packet.pipelineBindPoint )
		{
			case VK_PIPELINE_BIND_POINT_GRAPHICS :
			{
				auto	new_ppln = _fgConv._pipelineConv->FindGraphicsPipeline( ResourceID(packet.pipeline) );
				CHECK_ERR( new_ppln );
				CHECK_ERR( cmd->second.renderPass );

				CHECK_ERR( _MergeRenderPassStates( *cmd->second.renderPass, *new_ppln ));

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
				CHECK_ERR( state.descriptors[i].layout == ppln_layout->dslayouts[i] )
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
		ASSERT( cmd->second.isRecording );

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
		ASSERT( cmd->second.isRecording );

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
		ASSERT( cmd->second.isRecording );
		
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
		ASSERT( cmd->second.isRecording );
		
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
		ASSERT( cmd->second.isRecording );
		
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
		ASSERT( cmd->second.isRecording );
		
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
		ASSERT( cmd->second.isRecording );
		
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
		ASSERT( cmd->second.isRecording );
		
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
		ASSERT( cmd->second.isRecording );
		
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
		ASSERT( cmd->second.isRecording );
		
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
		ASSERT( cmd->second.isRecording );

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
		ASSERT( cmd->second.isRecording );

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
	bool FrameGraphConverter::DrawCallConverter::_PackDescriptors (ArrayView<DescriptorSetInfo> descriptors, TraceRange::Bookmark pos, TracePacker &packer) const
	{
		packer << uint(descriptors.size());

		for (size_t i = 0; i < descriptors.size(); ++i)
		{
			auto&	set = descriptors[i];

			//packer << DescriptorSetID( ToString(i) );
			packer << uint(i);
			packer << uint(set.descriptors.size());

			for (size_t j = 0; j < set.descriptors.size(); ++j)
			{
				auto&	desc = set.descriptors[j];
				
				packer << UniformID{ ToString(i) << "." << ToString(j) };

				switch ( desc.descriptorType )
				{
					case VK_DESCRIPTOR_TYPE_SAMPLER : {
						packer << uint(1);	// BindSampler
						packer << _fgConv._samplerConv->Remap( desc.image.sampler, pos ).Index();
						break;
					}

					case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER : {
						packer << uint(2);	// BindTexture

						auto*	view = _fgConv._imageAnalyzer->GetImageView( ResourceID(desc.image.view), pos );
						CHECK_ERR( view );

						ImageViewDesc	view_desc;
						CHECK_ERR( _ConvertImageView( *view, OUT view_desc ));

						packer << _fgConv._imageConv->Remap( view->image->id, pos ).Index();
						packer << _fgConv._samplerConv->Remap( desc.image.sampler, pos ).Index();
						FGPack_ImageViewDesc( view_desc, packer );
						break;
					}

					case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE :
					case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT : {
						packer << uint(3);	// BindImage

						auto*	view = _fgConv._imageAnalyzer->GetImageView( ResourceID(desc.image.view), pos );
						CHECK_ERR( view );

						ImageViewDesc	view_desc;
						CHECK_ERR( _ConvertImageView( *view, OUT view_desc ));

						packer << _fgConv._imageConv->Remap( view->image->id, pos ).Index();
						FGPack_ImageViewDesc( view_desc, packer );
						break;
					}

					case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER :
					case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER : {
						packer << uint(4);	// BindBuffer
						packer << _fgConv._bufferConv->Remap( desc.buffer.handle, pos ).Index();
						packer << desc.buffer.offset;
						packer << desc.buffer.range;
						packer << desc.buffer.dynamicOffset;
						ASSERT( desc.buffer.dynamicOffset == 0 );
						break;
					}

					case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC :
					case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC : {
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
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_PackBaseDrawCall (const CommandBufferState &cmd, TraceRange::Bookmark pos) const
	{
		using StencilValue_t = _fg_hidden_::StencilState::Value_t;

		CHECK_ERR( _CheckPipeline( cmd.graphicsPpln ));
		
		auto*	curr_ppln	= _fgConv._pipelineConv->FindGraphicsPipeline( cmd.graphicsPpln.pipelineId );
		auto*	ppln_layout	= _fgConv._pipelineConv->FindPipelineLayout( curr_ppln->layout );

		auto&	packer = *cmd.tracePacker;

		// pack descriptor sets (pipeline resources)
		const uint	ds_count = uint(ppln_layout->dslayouts.size());
		_PackDescriptors(ArrayView<DescriptorSetInfo>{ cmd.graphicsPpln.descriptors.data(), ds_count }, pos, packer );

		// pack push constants
		packer << uint(cmd.graphicsPpln.pushConstants.size());

		for (auto& pc : cmd.graphicsPpln.pushConstants) {
			FGPack_PushConstantData( pc.second, packer );
		}

		// pack dynamic states
		packer << FGEnumCast( cmd.dynamicStates.current );

		// pack scissors
		packer << uint(0);	// TODO

		// pack color buffers
		packer << uint(0);	// TODO

		// pack stencil state
		packer << StencilValue_t(cmd.dynamicStates.stencilReference[0].value_or( 0 ));	// TODO
		packer << StencilValue_t(cmd.dynamicStates.stencilReference[1].value_or( 0 ));
		packer << StencilValue_t(cmd.dynamicStates.stencilWriteMask[0].value_or( ~0u ));
		packer << StencilValue_t(cmd.dynamicStates.stencilWriteMask[1].value_or( ~0u ));
		packer << StencilValue_t(cmd.dynamicStates.stencilCompareMask[0].value_or( ~0u ));
		packer << StencilValue_t(cmd.dynamicStates.stencilCompareMask[1].value_or( ~0u ));

		return true;
	}
	
/*
=================================================
	_PackBaseDrawVertices
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_PackBaseDrawVertices (const CommandBufferState &cmd, TraceRange::Bookmark pos) const
	{
		auto&	packer	= *cmd.tracePacker;
		auto*	ppln	= _fgConv._pipelineConv->FindGraphicsPipeline( cmd.graphicsPpln.pipelineId );
		CHECK_ERR( ppln );

		// pipeline
		packer << ppln->fgPipeline->second.Index();

		CHECK_ERR( _PackBaseDrawCall( cmd, pos ));

		// vertex input
		FGPack_VertexInputState( ppln->vertexInput, packer );

		// pack vertex buffers
		const uint	vb_count = uint(ppln->vertexInput.BufferBindings().size());
		CHECK_ERR( vb_count > 0 and vb_count <= cmd.vertexBuffers.size() );
		packer << vb_count;

		for (uint i = 0; i < vb_count; ++i)
		{
			auto&			vb = cmd.vertexBuffers[i];
			VertexBufferID	id{ ToString(i) };

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
		ASSERT( cmd->second.isRecording );

		auto&	packer = *cmd->second.tracePacker;
		packer.Begin( EPacketID::FgDrawVertices );
		packer << uint(0);	// TODO: thread id
		packer << cmd->second.renderPass->index;

		CHECK_ERR( _PackBaseDrawVertices( cmd->second, pos.GetBookmark() ));

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
		ASSERT( cmd->second.isRecording );
		
		auto&	packer = *cmd->second.tracePacker;
		packer.Begin( EPacketID::FgDrawIndexed );
		packer << uint(0);	// TODO: thread id
		packer << cmd->second.renderPass->index;
		
		CHECK_ERR( _PackBaseDrawVertices( cmd->second, pos.GetBookmark() ));

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
		ASSERT( cmd->second.isRecording );
		
		auto&	packer = *cmd->second.tracePacker;
		packer.Begin( EPacketID::FgDrawVerticesIndirect );
		packer << uint(0);	// TODO: thread id
		packer << cmd->second.renderPass->index;
		
		CHECK_ERR( _PackBaseDrawVertices( cmd->second, pos.GetBookmark() ));

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
		ASSERT( cmd->second.isRecording );
		
		auto&	packer = *cmd->second.tracePacker;
		packer.Begin( EPacketID::FgDrawVerticesIndirect );
		packer << uint(0);	// TODO: thread id
		packer << cmd->second.renderPass->index;
		
		CHECK_ERR( _PackBaseDrawVertices( cmd->second, pos.GetBookmark() ));
		
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
		
		packer.End( EPacketID::FgDrawVerticesIndirect );
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
		ASSERT( cmd->second.isRecording );

		auto&	packer = *cmd->second.tracePacker;
		packer.Begin( EPacketID::FgDispatchCompute );
		packer << uint(0);	// TODO: thread id
		
		packer.End( EPacketID::FgDispatchCompute );

		ASSERT(false);	// not supported
		return false;
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
		ASSERT( cmd->second.isRecording );
		
		auto&	packer = *cmd->second.tracePacker;
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
		ASSERT( cmd->second.isRecording );

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
		ASSERT( cmd->second.isRecording );

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

		auto&	packer = *cmd->second.tracePacker;
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

			ASSERT( reg.srcOffset < src_info->createInfo.size	and
				    reg.srcOffset + reg.size <= src_info->createInfo.size );
			ASSERT( reg.dstOffset < dst_info->createInfo.size	and
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
		ASSERT( cmd->second.isRecording );

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


		auto&	packer = *cmd->second.tracePacker;
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
		ASSERT( cmd->second.isRecording );
		
		auto&	packer = *cmd->second.tracePacker;
		packer.Begin( EPacketID::FgBlitImage );
		packer << uint(0);	// TODO: thread id
		
		packer << _fgConv._imageConv->Remap( packet.srcImage, pos.GetBookmark() ).Index();
		packer << _fgConv._imageConv->Remap( packet.dstImage, pos.GetBookmark() ).Index();
		packer << FGEnumCast( packet.filter );
		packer << packet.regionCount;

		for (uint i = 0; i < packet.regionCount; ++i)
		{
			FGPacket_BlitImage_Region( packet.pRegions[i], packer );
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
		ASSERT( cmd->second.isRecording );
		
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


		auto&	packer = *cmd->second.tracePacker;
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
		ASSERT( cmd->second.isRecording );
		
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


		auto&	packer = *cmd->second.tracePacker;
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
		ASSERT( cmd->second.isRecording );
		
		CHECK( not _BufferHasHostAccess( ResourceID(packet.dstBuffer), pos.GetBookmark() ));

		DataID		data_id = _fgConv._RequestData( pos, packet.header, packet.pData, packet.dataSize, frameId );
		CHECK_ERR( data_id != ~DataID(0) );

		auto&	packer = *cmd->second.tracePacker;
		packer.Begin( EPacketID::FgUpdateBuffer );
		packer << uint(0);	// TODO: thread id

		packer << _fgConv._bufferConv->Remap( packet.dstBuffer, pos.GetBookmark() ).Index();
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
		ASSERT( cmd->second.isRecording );
		
		CHECK( not _BufferHasHostAccess( ResourceID(packet.dstBuffer), pos.GetBookmark() ));

		auto&	packer = *cmd->second.tracePacker;
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
		ASSERT( cmd->second.isRecording );
		
		CHECK( not _ImageHasHostAccess( ResourceID(packet.image), pos.GetBookmark() ));

		auto*	image = _fgConv._imageAnalyzer->GetImage( ResourceID(packet.image), pos.GetBookmark() );
		CHECK_ERR( image );
		
		auto&	packer = *cmd->second.tracePacker;
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
		ASSERT( cmd->second.isRecording );

		CHECK( not _ImageHasHostAccess( ResourceID(packet.image), pos.GetBookmark() ));

		auto*	image = _fgConv._imageAnalyzer->GetImage( ResourceID(packet.image), pos.GetBookmark() );
		CHECK_ERR( image );
		
		auto&	packer = *cmd->second.tracePacker;
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
		ASSERT( cmd->second.isRecording );
		
		CHECK( not _ImageHasHostAccess( ResourceID(packet.srcImage), pos.GetBookmark() ));
		CHECK( not _ImageHasHostAccess( ResourceID(packet.dstImage), pos.GetBookmark() ));
		
		auto&	packer = *cmd->second.tracePacker;
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
		ASSERT( cmd->second.isRecording );

		auto	pc_layout = _fgConv._pipelineConv->FindPipelineLayout( ResourceID(packet.layout) );
		CHECK_ERR( pc_layout );

		PushConstantID	id;
		
		for (auto& pc : pc_layout->pushConstantRanges)
		{
			if ( pc.second.offset		== packet.offset	and
				 pc.second.size			== packet.size		and
				 pc.second.stageFlags	== packet.stageFlags )
			{
				id = pc.first;
				break;
			}
		}
		CHECK_ERR( id.IsDefined() );

		_fg_hidden_::PushConstantData	pc_data;
		pc_data.id		= id;
		pc_data.size	= Bytes<uint16_t>{ uint16_t(packet.size) };
		MemCopy( pc_data.data, BytesU::SizeOf(pc_data.data), packet.pValues, BytesU{packet.size} );

		if ( EnumAny( packet.stageFlags, graphics_stages ) )
		{
			cmd->second.graphicsPpln.pushConstants.insert({ id, pc_data });
		}
		else
		if ( EnumAny( packet.stageFlags, compute_stages ) )
		{
			cmd->second.graphicsPpln.pushConstants.insert({ id, pc_data });
		}
		else
		if ( EnumAny( packet.stageFlags, raytracing_stages ) )
		{
			ASSERT(false);
			return false;
		}
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
		ASSERT( cmd->second.isRecording );

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
		
		CHECK_ERR( _PackRenderPass( cmd->second ));
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
		ASSERT( cmd->second.isRecording );

		CHECK_ERR( _PackSubmitRenderPass( cmd->second ));
		
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

		CHECK_ERR( _PackRenderPass( cmd->second ));
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
		ASSERT( (beginInfo != null) == (subpassIndex == 0) );

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
						outRP.desc.AddTarget( RenderTargetID(ToString(rt.attachment)), image, desc,
											  RGBA32i{clear_val.int32[0], clear_val.int32[1], clear_val.int32[2], clear_val.int32[3]},
											  store_op );
						break;

					case EClearValueType::UInt :
						outRP.desc.AddTarget( RenderTargetID(ToString(rt.attachment)), image, desc,
											  RGBA32u{clear_val.uint32[0], clear_val.uint32[1], clear_val.uint32[2], clear_val.uint32[3]},
											  store_op );
						break;

					case EClearValueType::Float :
						outRP.desc.AddTarget( RenderTargetID(ToString(rt.attachment)), image, desc,
											  RGBA32f{clear_val.float32[0], clear_val.float32[1], clear_val.float32[2], clear_val.float32[3]},
											  store_op );
						break;

					default :
						RETURN_ERR( "unsupported format for clearing color value" );
				}
			}
			else
				outRP.desc.AddTarget( RenderTargetID(ToString(rt.attachment)), image, desc, load_op, store_op );

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
		return true;
	}
	
/*
=================================================
	_MergeRenderPassStates
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_MergeRenderPassStates (INOUT RenderPass &renderPass, const PipelineConverter::GraphicsPipelineInfo &pipeline) const
	{
		auto&	rs = pipeline.fgPipeline->first.renderState;

		if ( not renderPass.isInitialized )
		{
			renderPass.desc.colorState			= rs.color;
			renderPass.desc.depthState			= rs.depth;
			renderPass.desc.stencilState		= rs.stencil;
			renderPass.desc.rasterizationState	= rs.rasterization;
			renderPass.desc.multisampleState	= rs.multisample;
			renderPass.isInitialized			= true;
			return true;
		}

		// check color buffer states
		{
			for (auto& cb : rs.color.buffers) {
				CHECK_ERR( renderPass.desc.colorState.buffers.count( cb.first ));
			}
			CHECK_ERR( rs.color.logicOp == renderPass.desc.colorState.logicOp );
			CHECK_ERR( rs.color.blendColor == renderPass.desc.colorState.blendColor );
		}

		// check depth stencil states
		{
			CHECK_ERR( rs.depth == renderPass.desc.depthState );
			CHECK_ERR( rs.stencil.front.failOp == renderPass.desc.stencilState.front.failOp );
			CHECK_ERR( rs.stencil.back.failOp == renderPass.desc.stencilState.back.failOp );
			CHECK_ERR( rs.stencil.front.depthFailOp == renderPass.desc.stencilState.front.depthFailOp );
			CHECK_ERR( rs.stencil.back.depthFailOp == renderPass.desc.stencilState.back.depthFailOp );
			CHECK_ERR( rs.stencil.front.passOp == renderPass.desc.stencilState.front.passOp );
			CHECK_ERR( rs.stencil.back.passOp == renderPass.desc.stencilState.back.passOp );
			CHECK_ERR( rs.stencil.front.compareOp == renderPass.desc.stencilState.front.compareOp );
			CHECK_ERR( rs.stencil.back.compareOp == renderPass.desc.stencilState.back.compareOp );
		}

		// check rasterization states
		{
			CHECK_ERR( rs.rasterization == renderPass.desc.rasterizationState );
		}

		// check multisample states
		{
			CHECK_ERR( rs.multisample == renderPass.desc.multisampleState );
		}

		return true;
	}
	
/*
=================================================
	_PackRenderPass
----
	see unpacker in 'FGPlayer_v100::_CreateRenderPass'
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_PackRenderPass (const CommandBufferState &cmd) const
	{
		auto&	rp		= *cmd.renderPass;
		auto&	packer	= *cmd.tracePacker;

		packer.Begin( EPacketID::FgCreateRenderPass );
		packer << uint(0);	// TODO: thread id

		packer << rp.index;
		FGPack_ColorBuffersState( rp.desc.colorState, packer );
		FGPack_DepthBufferState( rp.desc.depthState, packer );
		FGPack_StencilBufferState( rp.desc.stencilState, packer );
		FGPack_MultisampleState( rp.desc.multisampleState, packer );

		packer << uint(rp.desc.renderTargets.size());
		for (auto& rt : rp.desc.renderTargets) {
			packer << rt.first;
			FGPack_RenderPassTraget( rt.second, packer );
		}

		packer << uint(rp.desc.viewports.size());
		for (auto& vp : rp.desc.viewports) {
			FGPack_RenderPassViewport( vp, packer );
		}

		FGPack_Rectangle( rp.desc.area, packer );
		packer << rp.desc.parallelExecution;
		packer << rp.desc.canBeMerged;

		packer.End( EPacketID::FgCreateRenderPass );
		return true;
	}
	
/*
=================================================
	_PackSubmitRenderPass
----
	see unpacker in 'FGPlayer_v100::_SubmitRenderPass'
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_PackSubmitRenderPass (const CommandBufferState &cmd) const
	{
		auto&	rp		= *cmd.renderPass;
		auto&	packer	= *cmd.tracePacker;

		packer.Begin( EPacketID::FgSubmitRenderPass );
		packer << uint(0);	// TODO: thread id
		packer << rp.index;
		packer.End( EPacketID::FgSubmitRenderPass );

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
		ASSERT( cmd->second.isRecording );
		
		CHECK_ERR( _PackSubmitRenderPass( cmd->second ));

		cmd->second.renderPass		= null;
		cmd->second.currRenderPass	= 0;
		cmd->second.currFramebuffer	= 0;
		cmd->second.subpassIndex	= ~0u;

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
	bool FrameGraphConverter::DrawCallConverter::QueueSubmit (const TraceRange::Iterator &pos, INOUT TracePacker &packer)
	{
		auto&	packet	= pos.Cast<packet_vkQueueSubmit>();

		for (uint i = 0; i < packet.submitCount; ++i)
		{
			auto&	submit = packet.pSubmits[i];

			for (uint j = 0; j < submit.commandBufferCount; ++j)
			{
				auto	cmd		= _cmdBuffers.find( ResourceID(submit.pCommandBuffers[i]) );
				CHECK_ERR( cmd != _cmdBuffers.end() );
				CHECK_ERR( cmd->second.tracePacker );
				ASSERT( not cmd->second.isRecording );

				packer.Append( *cmd->second.tracePacker );

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
	bool FrameGraphConverter::DrawCallConverter::QueuePresent (const TraceRange::Iterator &pos, INOUT TracePacker &packer)
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
		TraceRange::Bookmark	submit_pos;

		for (auto& bm : cmdbuf->bookmarks)
		{
			if ( pos < bm.pos and bm.packetId == VKTRACE_TPI_VK_vkQueueSubmit )
			{
				submit_pos = bm.pos;
				break;
			}
		}
		CHECK_ERR( submit_pos != TraceRange::Bookmark() );


		// find last memory usage before submitting commands
		auto*	src_buf = _fgConv._bufferAnalyzer->GetBuffer( ResourceID(packet.srcBuffer), pos );
		CHECK_ERR( src_buf );

		auto*	mem = _fgConv._memoryObjAnalyzer->GetMemoryObj( src_buf->memId, pos );
		CHECK_ERR( mem );

		auto*	dst_img = _fgConv._imageAnalyzer->GetImage( ResourceID(packet.dstImage), pos );
		CHECK_ERR( dst_img );

		const uint	bpp = GetImageFormatBitPerPixel( dst_img->createInfo.format );

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
					auto&	reg = *iter;

					// check intersection
					const uint64_t	row_pitch	= (Max(reg.bufferRowLength, reg.imageExtent.width) * bpp) / 8;
					const uint64_t	slice_pitch	= Max(reg.bufferImageHeight, reg.imageExtent.height) * row_pitch;
					const uint		dim_z		= Max( reg.imageSubresource.layerCount, reg.imageExtent.depth );
					const uint64_t	data_size	= slice_pitch * dim_z;
					const uint64_t	buf_begin	= reg.bufferOffset + src_buf->memOffset;
					const uint64_t	buf_end		= buf_begin + data_size;
					uint64_t		data_begin, data_end;

					if ( GetIntersection( block.memOffset, block.memOffset + block.dataSize, buf_begin, buf_end,
										  OUT data_begin, OUT data_end ) )
					{
						ASSERT( data_begin == buf_begin and data_end == buf_end );
						ASSERT( reg.imageSubresource.layerCount == 1 );	// TODO
						
						uint64_t	block_offset = buf_begin - block.memOffset;
						ASSERT( block_offset < block.dataSize	and
								block_offset + data_size <= block.dataSize );
						
						DataID	data_id = _fgConv._RequestData( block.fileOffset + block_offset, data_size, frameId );
						CHECK_ERR( data_id != ~DataID(0) );

						auto&	packer = *cmd.tracePacker;
						packer.Begin( EPacketID::FgUpdateImage );
						packer << uint(0);	// TODO: thread id
						packer << _fgConv._imageConv->Remap( packet.dstImage, pos ).Index();
						FGPack_Offset3D( reg.imageOffset, packer );
						FGPack_Extent3D( reg.imageExtent, packer );
						packer << reg.imageSubresource.baseArrayLayer;
						packer << reg.imageSubresource.mipLevel;
						packer << row_pitch;
						packer << slice_pitch;
						packer << FGEnumCast( reg.imageSubresource.aspectMask );
						packer << data_id;
						packer.End( EPacketID::FgUpdateImage );

						iter = regions.erase( iter );
					}
					else
						++iter;
				}
			}
		}

		CHECK_ERR( regions.empty() );
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
		FG_UNUSED( cmd, packet, pos, frameId );
		ASSERT(false);
		return false;
	}
	
/*
=================================================
	_ReadImage
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_ReadImage (CommandBufferState &cmd, const packet_vkCmdCopyBufferToImage &packet, const TraceRange::Bookmark pos)
	{
		FG_UNUSED( cmd, packet, pos );
		ASSERT(false);
		return false;
	}
	
/*
=================================================
	_ReadImage
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_ReadImage (CommandBufferState &cmd, const packet_vkCmdCopyImage &packet, const TraceRange::Bookmark pos)
	{
		FG_UNUSED( cmd, packet, pos );
		ASSERT(false);
		return false;
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
		TraceRange::Bookmark	submit_pos;

		for (auto& bm : cmdbuf->bookmarks)
		{
			if ( pos < bm.pos and bm.packetId == VKTRACE_TPI_VK_vkQueueSubmit )
			{
				submit_pos = bm.pos;
				break;
			}
		}
		CHECK_ERR( submit_pos != TraceRange::Bookmark() );


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
			//   |          |    |      |=== reg= ===|
			//   |<-------->|    |<---->|
			//   |<---|--------->|     \
			//        |         \      reg.srcOffset
			//  block.memOffset  src_buffer.memOffset

			for (auto& block : info->blocks)
			{
				for (auto iter = regions.begin(); iter != regions.end();)
				{
					auto&	reg = *iter;

					const uint64_t	data_size	= Min( reg.size, dst_buf->createInfo.size - reg.dstOffset );
					const uint64_t	buf_begin	= reg.srcOffset + src_buf->memOffset;
					const uint64_t	buf_end		= buf_begin + data_size;
					uint64_t		data_begin, data_end;
					
					ASSERT( block.dataSize >= data_size );

					if ( GetIntersection( block.memOffset, block.memOffset + block.dataSize, buf_begin, buf_end,
										  OUT data_begin, OUT data_end ) )
					{
						ASSERT( data_begin == buf_begin and data_end == buf_end );

						uint64_t	block_offset = buf_begin - block.memOffset;
						ASSERT( block_offset < block.dataSize	and
								block_offset + data_size <= block.dataSize );

						DataID	data_id = _fgConv._RequestData( block.fileOffset + block_offset, data_size, frameId );
						CHECK_ERR( data_id != ~DataID(0) );
						
						ASSERT( reg.dstOffset < dst_buf->createInfo.size	and
								reg.dstOffset + data_size <= dst_buf->createInfo.size );

						auto&	packer = *cmd.tracePacker;
						packer.Begin( EPacketID::FgUpdateBuffer );
						packer << uint(0);	// TODO: thread id
						packer << _fgConv._bufferConv->Remap( packet.dstBuffer, pos ).Index();
						packer << reg.dstOffset;
						packer << data_size;
						packer << data_id;
						packer.End( EPacketID::FgUpdateBuffer );

						iter = regions.erase( iter );
					}
					else
						++iter;
				}
			}
		}

		CHECK_ERR( regions.empty() );
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
		ASSERT(false);
		return false;
	}
	
/*
=================================================
	_ReadBuffer
=================================================
*/
	bool FrameGraphConverter::DrawCallConverter::_ReadBuffer (CommandBufferState &cmd, const packet_vkCmdCopyImageToBuffer &packet, const TraceRange::Bookmark pos)
	{
		FG_UNUSED( cmd, packet, pos );
		ASSERT(false);
		return false;
	}


}	// VTC
