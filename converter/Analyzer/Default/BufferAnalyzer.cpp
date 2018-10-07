// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Analyzer/Default/BufferAnalyzer.h"
#include "Analyzer/Default/MemoryObjAnalyzer.h"
#include "Parser/AppTrace.h"

namespace VTC
{

/*
=================================================
	constructor
=================================================
*/
	BufferAnalyzer::BufferAnalyzer ()
	{
	}
	
/*
=================================================
	PreProcess
=================================================
*/
	void BufferAnalyzer::PreProcess (const AppTrace &appTrace)
	{
		_memoryObjAnalyzer = appTrace.GetAnalyzer< MemoryObjAnalyzer >();

		CHECK( _memoryObjAnalyzer );
	}
	
/*
=================================================
	Process
=================================================
*/
	void BufferAnalyzer::Process (const TraceRange::Iterator &pos)
	{
		switch( pos->packet_id )
		{
			// CmdWaitEvents
			case VKTRACE_TPI_VK_vkCmdWaitEvents : {
				auto&	packet = pos.Cast<packet_vkCmdWaitEvents>();

				CHECK( _ProcessBufferMemoryBarriers( pos.GetBookmark(), packet.srcStageMask, packet.dstStageMask,
												     { packet.pBufferMemoryBarriers, packet.bufferMemoryBarrierCount } ));
				break;
			}

			// CmdPipelineBarrier
			case VKTRACE_TPI_VK_vkCmdPipelineBarrier : {
				packet_vkCmdPipelineBarrier const&	packet = pos.Cast<packet_vkCmdPipelineBarrier>();
				
				CHECK( _ProcessBufferMemoryBarriers( pos.GetBookmark(), packet.srcStageMask, packet.dstStageMask,
												     { packet.pBufferMemoryBarriers, packet.bufferMemoryBarrierCount } ));
				break;
			}

			//
			case VKTRACE_TPI_VK_vkUpdateDescriptorSets :
				CHECK( _OnUpdateDescriptorSets( pos ));
				break;
		}
	}

/*
=================================================
	AddResourceUsage
=================================================
*/
	void BufferAnalyzer::AddResourceUsage (const TraceRange::Iterator &pos, EResourceType type, ResourceID id, FrameID, EResOp op)
	{
		switch ( type )
		{
			case VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT :		CHECK( _ProcessBufferUsage( pos, id, op ));		break;
			case VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_VIEW_EXT :	CHECK( _ProcessBufferViewUsage( pos, id, op ));	break;
		}
	}
	
/*
=================================================
	_ProcessBufferUsage
=================================================
*/
	bool BufferAnalyzer::_ProcessBufferUsage (const TraceRange::Iterator &pos, ResourceID id, EResOp op)
	{
		if ( pos->packet_id == VKTRACE_TPI_VK_vkCreateBuffer )
			return _OnCreateBuffer( pos, id );
		
		BuffersMap_t::iterator	buffer;
		CHECK_ERR( _buffers.AddResourceUsage( OUT buffer, pos, id, op ));

		auto&	info = buffer->second.back();

		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkBindBufferMemory :				CHECK( _OnBindBufferMemory( pos, info ));				break;
			case VKTRACE_TPI_VK_vkBindBufferMemory2 :
			case VKTRACE_TPI_VK_vkBindBufferMemory2KHR :			CHECK( _OnBindBufferMemory2( pos, info ));				break;

			case VKTRACE_TPI_VK_vkGetBufferMemoryRequirements :		CHECK( _OnGetBufferMemoryRequirements( pos, info ));	break;
			case VKTRACE_TPI_VK_vkGetBufferMemoryRequirements2 :
			case VKTRACE_TPI_VK_vkGetBufferMemoryRequirements2KHR :	CHECK( _OnGetBufferMemoryRequirements2( pos, info ));	break;
				
			case VKTRACE_TPI_VK_vkCmdCopyBuffer :					CHECK( _OnCopyBuffer( pos, info ));						break;
			case VKTRACE_TPI_VK_vkCmdDispatchIndirect :				CHECK( _OnDispatchIndirect( pos, info ));				break;
			case VKTRACE_TPI_VK_vkCmdDrawIndirect :					CHECK( _OnDrawIndirect( pos, info ));					break;
			case VKTRACE_TPI_VK_vkCmdDrawIndirectCountAMD :			CHECK( _OnDrawIndirectCountAMD( pos, info ));			break;
			case VKTRACE_TPI_VK_vkCmdDrawIndexedIndirect :			CHECK( _OnDrawIndexedIndirect( pos, info ));			break;
			case VKTRACE_TPI_VK_vkCmdDrawIndexedIndirectCountAMD :	CHECK( _OnDrawIndexedIndirectCountAMD( pos, info ));	break;

			case VKTRACE_TPI_VK_vkCmdCopyBufferToImage :
				_AddBufferUsage( info, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_ACCESS_TRANSFER_READ_BIT );
				_AddBufferAccess( info, pos.GetBookmark() );
				break;

			case VKTRACE_TPI_VK_vkCmdCopyImageToBuffer :
			case VKTRACE_TPI_VK_vkCmdCopyQueryPoolResults :
			case VKTRACE_TPI_VK_vkCmdFillBuffer :
			case VKTRACE_TPI_VK_vkCmdUpdateBuffer :
				_AddBufferUsage( info, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_ACCESS_TRANSFER_WRITE_BIT );
				_AddBufferAccess( info, pos.GetBookmark() );
				break;

			case VKTRACE_TPI_VK_vkCmdBindIndexBuffer :
				_AddBufferUsage( info, VK_PIPELINE_STAGE_VERTEX_INPUT_BIT, VK_ACCESS_INDEX_READ_BIT );
				_AddBufferAccess( info, pos.GetBookmark() );
				break;

			case VKTRACE_TPI_VK_vkCmdBindVertexBuffers :
				_AddBufferUsage( info, VK_PIPELINE_STAGE_VERTEX_INPUT_BIT, VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT );
				_AddBufferAccess( info, pos.GetBookmark() );
				break;

			case VKTRACE_TPI_VK_vkCreateBufferView :
			case VKTRACE_TPI_VK_vkDestroyBuffer :
			case VKTRACE_TPI_VK_vkAllocateMemory :
			case VKTRACE_TPI_VK_vkUpdateDescriptorSets :
			case VKTRACE_TPI_VK_vkCmdPipelineBarrier :
			case VKTRACE_TPI_VK_vkCmdWaitEvents :
				break;

			// vertex / index / indirect buffer usage
			case VKTRACE_TPI_VK_vkCmdDraw :
			case VKTRACE_TPI_VK_vkCmdDrawIndexed :
				break;

			default :
				ASSERT(false);		// unknown usage
				break;
		}
		return true;
	}
	
/*
=================================================
	_OnCreateBuffer
=================================================
*/
	bool BufferAnalyzer::_OnCreateBuffer (const TraceRange::Iterator &pos, ResourceID id)
	{
		auto&	packet = pos.Cast< packet_vkCreateBuffer >();
		CHECK_ERR( packet.pCreateInfo );
		CHECK_ERR( id == ResourceID(*packet.pBuffer) );
		//ASSERT( packet.pCreateInfo->pNext == null );	// add support if triggered

		BuffersMap_t::iterator	buffer;
		CHECK_ERR( _buffers.AddResourceUsage( OUT buffer, pos, id, EResOp::Construct ));

		auto&	info = buffer->second.back();

		info.id			= ResourceID(*packet.pBuffer);
		info.createInfo	= *packet.pCreateInfo;
		info.deviceId	= ResourceID(packet.device);

		return true;
	}
	
/*
=================================================
	_OnBindBufferMemory
=================================================
*/
	bool BufferAnalyzer::_OnBindBufferMemory (const TraceRange::Iterator &pos, BufferInfo_t &buffer)
	{
		auto&	packet = pos.Cast< packet_vkBindBufferMemory >();
		CHECK_ERR( buffer.id == ResourceID(packet.buffer) );

		buffer.memId = ResourceID(packet.memory);
		return true;
	}
	
/*
=================================================
	_OnBindBufferMemory2
=================================================
*/
	bool BufferAnalyzer::_OnBindBufferMemory2 (const TraceRange::Iterator &pos, BufferInfo_t &buffer)
	{
		STATIC_ASSERT( sizeof(packet_vkBindBufferMemory2) == sizeof(packet_vkBindBufferMemory2KHR) );

		auto&	packet = pos.Cast< packet_vkBindBufferMemory2 >();
		
		for (uint i = 0; i < packet.bindInfoCount; ++i)
		{
			if ( buffer.id == ResourceID(packet.pBindInfos[i].buffer) )
			{
				ASSERT( packet.pBindInfos[i].pNext == null );	// add support if triggered

				buffer.memId = ResourceID(packet.pBindInfos[i].memory);
				break;
			}
		}
		return true;
	}
	
/*
=================================================
	_OnGetBufferMemoryRequirements
=================================================
*/
	bool BufferAnalyzer::_OnGetBufferMemoryRequirements (const TraceRange::Iterator &pos, BufferInfo_t &buffer)
	{
		auto&	packet = pos.Cast< packet_vkGetBufferMemoryRequirements >();
		CHECK_ERR( buffer.id == ResourceID(packet.buffer) );

		buffer.memRequirements = *packet.pMemoryRequirements;
		return true;
	}
	
/*
=================================================
	_OnGetBufferMemoryRequirements2
=================================================
*/
	bool BufferAnalyzer::_OnGetBufferMemoryRequirements2 (const TraceRange::Iterator &pos, BufferInfo_t &buffer)
	{
		STATIC_ASSERT( sizeof(packet_vkGetBufferMemoryRequirements2) == sizeof(packet_vkGetBufferMemoryRequirements2KHR) );

		auto&	packet = pos.Cast< packet_vkGetBufferMemoryRequirements2 >();
		CHECK_ERR( buffer.id == ResourceID(packet.pInfo->buffer) );
		ASSERT( packet.pInfo->pNext == null );					// add support if triggered
		ASSERT( packet.pMemoryRequirements->pNext == null );	// add support if triggered

		buffer.memRequirements = packet.pMemoryRequirements->memoryRequirements;
		return true;
	}
	
/*
=================================================
	_OnCopyBuffer
=================================================
*/
	bool BufferAnalyzer::_OnCopyBuffer (const TraceRange::Iterator &pos, BufferInfo_t &buffer)
	{
		auto&	packet = pos.Cast< packet_vkCmdCopyBuffer >();

		if ( ResourceID(packet.srcBuffer) == buffer.id ) {
			_AddBufferUsage( buffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_ACCESS_TRANSFER_READ_BIT );
			_AddBufferAccess( buffer, pos.GetBookmark() );
		}
		if ( ResourceID(packet.dstBuffer) == buffer.id ) {
			_AddBufferUsage( buffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_ACCESS_TRANSFER_WRITE_BIT );
			_AddBufferAccess( buffer, pos.GetBookmark() );
		}
		return true;
	}
	
/*
=================================================
	_OnDispatchIndirect
=================================================
*/
	bool BufferAnalyzer::_OnDispatchIndirect (const TraceRange::Iterator &pos, BufferInfo_t &buffer)
	{
		auto&	packet = pos.Cast< packet_vkCmdDispatchIndirect >();

		if ( ResourceID(packet.buffer) == buffer.id ) {
			_AddBufferUsage( buffer, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_ACCESS_INDEX_READ_BIT );
			_AddBufferAccess( buffer, pos.GetBookmark() );
		}
		return true;
	}
	
/*
=================================================
	_OnDrawIndirect
=================================================
*/
	bool BufferAnalyzer::_OnDrawIndirect (const TraceRange::Iterator &pos, BufferInfo_t &buffer)
	{
		auto&	packet = pos.Cast< packet_vkCmdDrawIndirect >();

		if ( ResourceID(packet.buffer) == buffer.id ) {
			_AddBufferUsage( buffer, VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT, VK_ACCESS_INDEX_READ_BIT );
			_AddBufferAccess( buffer, pos.GetBookmark() );
		}
		return true;
	}
	
/*
=================================================
	_OnDrawIndirectCountAMD
=================================================
*/
	bool BufferAnalyzer::_OnDrawIndirectCountAMD (const TraceRange::Iterator &pos, BufferInfo_t &buffer)
	{
		auto&	packet = pos.Cast< packet_vkCmdDrawIndirectCountAMD >();

		if ( ResourceID(packet.buffer) == buffer.id ) {
			_AddBufferUsage( buffer, VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT, VK_ACCESS_INDEX_READ_BIT );
			_AddBufferAccess( buffer, pos.GetBookmark() );
		}
		return true;
	}
	
/*
=================================================
	_OnDrawIndexedIndirect
=================================================
*/
	bool BufferAnalyzer::_OnDrawIndexedIndirect (const TraceRange::Iterator &pos, BufferInfo_t &buffer)
	{
		auto&	packet = pos.Cast< packet_vkCmdDrawIndexedIndirect >();

		if ( ResourceID(packet.buffer) == buffer.id ) {
			_AddBufferUsage( buffer, VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT, VK_ACCESS_INDEX_READ_BIT );
			_AddBufferAccess( buffer, pos.GetBookmark() );
		}
		return true;
	}
	
/*
=================================================
	_OnDrawIndexedIndirectCountAMD
=================================================
*/
	bool BufferAnalyzer::_OnDrawIndexedIndirectCountAMD (const TraceRange::Iterator &pos, BufferInfo_t &buffer)
	{
		auto&	packet = pos.Cast< packet_vkCmdDrawIndexedIndirectCountAMD >();

		if ( ResourceID(packet.buffer) == buffer.id ) {
			_AddBufferUsage( buffer, VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT, VK_ACCESS_INDEX_READ_BIT );
			_AddBufferAccess( buffer, pos.GetBookmark() );
		}
		return true;
	}

/*
=================================================
	_ProcessBufferViewUsage
=================================================
*/
	bool BufferAnalyzer::_ProcessBufferViewUsage (const TraceRange::Iterator &pos, ResourceID id, EResOp op)
	{
		if ( pos->packet_id == VKTRACE_TPI_VK_vkCreateBufferView )
			return _OnCreateBufferView( pos, id );
		
		BufferViewsMap_t::iterator	view;
		CHECK_ERR( _bufferViews.AddResourceUsage( OUT view, pos, id, op ));

		//auto&	info = view->second.back();

		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkDestroyBufferView :		break;

			default :
				ASSERT(false);		// unknown usage
				break;
		}
		return true;
	}
	
/*
=================================================
	_OnCreateBufferView
=================================================
*/
	bool BufferAnalyzer::_OnCreateBufferView (const TraceRange::Iterator &pos, ResourceID id)
	{
		auto&	packet = pos.Cast< packet_vkCreateBufferView >();
		CHECK_ERR( packet.pCreateInfo );
		CHECK_ERR( id == ResourceID(*packet.pView) );
		ASSERT( packet.pCreateInfo->pNext == null );	// add support if triggered

		auto*	buffer = _buffers.FindIn( ResourceID(packet.pCreateInfo->buffer), pos );
		CHECK_ERR( buffer );

		BufferViewsMap_t::iterator	view;
		CHECK_ERR( _bufferViews.AddResourceUsage( OUT view, pos, id, EResOp::Construct ));

		auto&	info = view->second.back();

		info.id			= id;
		info.buffer		= buffer;
		info.createInfo	= *packet.pCreateInfo;

		buffer->bufferViews.insert({ id, pos.GetBookmark() });
		return true;
	}
	
/*
=================================================
	_ProcessBufferMemoryBarriers
=================================================
*/
	bool BufferAnalyzer::_ProcessBufferMemoryBarriers (TraceRange::Bookmark pos, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask,
													   ArrayView<VkBufferMemoryBarrier> barriers)
	{
		for (auto& bar : barriers)
		{
			auto*	buffer = _buffers.FindIn( ResourceID(bar.buffer), pos );
			CHECK_ERR( buffer );

			CHECK_ERR( _AddBufferUsage( *buffer, srcStageMask, bar.srcAccessMask ));
			CHECK_ERR( _AddBufferUsage( *buffer, dstStageMask, bar.dstAccessMask ));
			
			_AddBufferAccess( *buffer, pos );
		}
		return true;
	}
	
/*
=================================================
	_OnUpdateDescriptorSets
=================================================
*/
	bool BufferAnalyzer::_OnUpdateDescriptorSets (const TraceRange::Iterator &pos)
	{
		auto&	packet = pos.Cast< packet_vkUpdateDescriptorSets >();

		for (uint i = 0; i < packet.descriptorWriteCount; ++i)
		{
			auto&	write = packet.pDescriptorWrites[i];
			ASSERT( write.pNext == null );				// add support if triggered
			ASSERT( write.pTexelBufferView == null );	// not supported, yet

			if ( not write.pBufferInfo )
				continue;

			VkAccessFlags			access	= 0;
			VkPipelineStageFlags	stage	= 0;	// TODO
			
			if ( write.descriptorType == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER or
				 write.descriptorType == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC )
				access = VK_ACCESS_UNIFORM_READ_BIT;

			if ( write.descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_BUFFER or
				 write.descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC )
				access = VK_ACCESS_SHADER_READ_BIT;

			for (uint j = 0; j < write.descriptorCount; ++j)
			{
				auto&	buf		= write.pBufferInfo[j];
				auto*	info	= _buffers.FindIn( ResourceID(buf.buffer), pos );
				CHECK_ERR( info );

				_AddBufferUsage( *info, stage, access );
				_AddBufferAccess( *info, pos.GetBookmark() );
			}
		}
		return true;
	}

/*
=================================================
	ConvertToBufferUsage
=================================================
*/
	ND_ static VkBufferUsageFlags  ConvertToBufferUsage (VkPipelineStageFlags, VkAccessFlags access)
	{
		VkBufferUsageFlags	usage = 0;

		if ( EnumEq( access, VK_ACCESS_INDIRECT_COMMAND_READ_BIT ) )
			usage |= VK_BUFFER_USAGE_INDEX_BUFFER_BIT;

		if ( EnumEq( access, VK_ACCESS_INDEX_READ_BIT ) )
			usage |= VK_BUFFER_USAGE_INDEX_BUFFER_BIT;

		if ( EnumEq( access, VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT ) )
			usage |= VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;

		if ( EnumEq( access, VK_ACCESS_UNIFORM_READ_BIT ) )
			usage |= VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;		// TODO: VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT

		if ( access & (VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT) )
			usage |= VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;		// TODO: VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT

		if ( EnumEq( access, VK_ACCESS_TRANSFER_READ_BIT ) )
			usage |= VK_BUFFER_USAGE_TRANSFER_SRC_BIT;

		if ( EnumEq( access, VK_ACCESS_TRANSFER_WRITE_BIT ) )
			usage |= VK_BUFFER_USAGE_TRANSFER_DST_BIT;

		if ( EnumEq( access, VK_ACCESS_CONDITIONAL_RENDERING_READ_BIT_EXT ) )
			usage |= VK_BUFFER_USAGE_CONDITIONAL_RENDERING_BIT_EXT;

		return usage;
	}

/*
=================================================
	_AddBufferUsage
=================================================
*/
	bool BufferAnalyzer::_AddBufferUsage (BufferInfo_t &buffer, VkPipelineStageFlags stage, VkAccessFlags access)
	{
		buffer.allAccessFlags	|= access;
		buffer.allStageFlags	|= stage;
		buffer.usage			|= ConvertToBufferUsage( stage, access );
		return true;
	}
	
/*
=================================================
	_AddBufferAccess
=================================================
*/
	void BufferAnalyzer::_AddBufferAccess (BufferInfo_t &buffer, TraceRange::Bookmark pos)
	{
		if ( buffer.firstAccess == TraceRange::Bookmark() )
			buffer.firstAccess = buffer.lastAccess = pos;
		else
			buffer.lastAccess = std::max( buffer.lastAccess, pos );
	}


}	// VTC
