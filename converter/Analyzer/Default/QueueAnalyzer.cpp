// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Analyzer/Default/QueueAnalyzer.h"
#include "Analyzer/Default/DeviceAnalyzer.h"
#include "Analyzer/AnalyzerUtils.h"
#include "Parser/AppTrace.h"

namespace VTC
{

/*
=================================================
	constructor
=================================================
*/
	QueueAnalyzer::QueueAnalyzer ()
	{
	}
	
/*
=================================================
	PreProcess
=================================================
*/
	void QueueAnalyzer::PreProcess (const AppTrace &appTrace)
	{
		_deviceAnalyzer = appTrace.GetAnalyzer< DeviceAnalyzer >();

		CHECK( _deviceAnalyzer );
	}

/*
=================================================
	AddResourceUsage
=================================================
*/
	void QueueAnalyzer::AddResourceUsage (const TraceRange::Iterator &pos, EResourceType type, ResourceID id, FrameID, EResOp op)
	{
		switch ( type )
		{
			case VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT :			CHECK( _ProcessQueueUsage( pos, id, op ));			break;
			case VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_POOL_EXT :		CHECK( _ProcessCommandPoolUsage( pos, id, op ));	break;
			case VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT :	CHECK( _ProcessCommandBufferUsage( pos, id, op ));	break;
		}
	}
	
/*
=================================================
	_ProcessQueueUsage
=================================================
*/
	bool QueueAnalyzer::_ProcessQueueUsage (const TraceRange::Iterator &pos, ResourceID id, EResOp op)
	{
		if ( op == EResOp::Construct )
			return _OnGetDeviceQueue( pos, id );
	
		QueuesMap_t::iterator	queue;
		CHECK( _queues.AddResourceUsage( OUT queue, pos, id, op ));

		auto&	info = queue->second.back();

		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkQueuePresentKHR :			info.usedForPresent = true;							break;
			case VKTRACE_TPI_VK_vkQueueBindSparse :			info.usageFlags |= VK_QUEUE_SPARSE_BINDING_BIT;		break;
			case VKTRACE_TPI_VK_vkQueueSubmit :				CHECK( _OnQueueSubmit( pos, id, info ));			break;

			case VKTRACE_TPI_VK_vkDestroyDevice :
			case VKTRACE_TPI_VK_vkQueueWaitIdle :
				break;

			default :
				ASSERT(false);	// unknown usage
				break;
		}
		return true;
	}
/*
=================================================
	_OnGetDeviceQueue
=================================================
*/
	bool QueueAnalyzer::_OnGetDeviceQueue (const TraceRange::Iterator &pos, ResourceID id)
	{
		auto&	packet = pos.Cast< packet_vkGetDeviceQueue >();
		CHECK_ERR( ResourceID(*packet.pQueue) == id );
		
		QueuesMap_t::iterator	queue;
		CHECK_ERR( _queues.AddResourceUsage( OUT queue, pos, ResourceID(*packet.pQueue), EResOp::Construct ));

		auto&	info = queue->second.back();

		info.id				= id;
		info.familyIndex	= packet.queueFamilyIndex;
		info.queueIndex		= packet.queueIndex;
		info.logicalDevice	= ResourceID(packet.device);
		info.physicalDevice	= ResourceID(0);
		info.usageFlags		= 0;


		if ( _deviceAnalyzer )
		{
			auto*	dev = _deviceAnalyzer->GetLogicalDeviceInfo( ResourceID(packet.device), pos.GetBookmark() );
			if ( dev )
			{
				info.physicalDevice = dev->physicalDevice;

				// find queue create info
				bool	found	= false;
				for (auto& ci : dev->queues)
				{
					if ( ci.queueFamilyIndex == packet.queueFamilyIndex )
					{
						CHECK_ERR( packet.queueIndex < ci.instances.size() );

						found				= true;
						info.createFlags	= ci.flags;
						info.priority		= ci.instances[ info.queueIndex ].priority;

						ASSERT( id == ci.instances[ info.queueIndex ].id );
						break;
					}
				}
				CHECK_ERR( found );
			}
		}
		return true;
	}
	
/*
=================================================
	_OnQueueSubmit
=================================================
*/
	bool QueueAnalyzer::_OnQueueSubmit (const TraceRange::Iterator &pos, ResourceID id, QueueInfo &queue)
	{
		auto&	packet = pos.Cast< packet_vkQueueSubmit >();
		CHECK( ResourceID(packet.queue) == id );

		for (uint i = 0; i < packet.submitCount; ++i)
		{
			// check for 'VK_QUEUE_PROTECTED_BIT' flag
			auto*	protect = FindVkStruct<VkProtectedSubmitInfo>( packet.pSubmits[i].pNext );
			if ( protect and protect->protectedSubmit )
				queue.usageFlags |= VK_QUEUE_PROTECTED_BIT;


			// add dependent command buffers & pools
			for (uint j = 0; j < packet.pSubmits[i].commandBufferCount; ++j)
			{
				CHECK_ERR( _QueueSubmitCommand( pos.GetBookmark(), queue, ResourceID(packet.pSubmits[i].pCommandBuffers[j]) ));
			}
		}
		return true;
	}
	
/*
=================================================
	_QueueSubmitCommand
=================================================
*/
	bool QueueAnalyzer::_QueueSubmitCommand (TraceRange::Bookmark pos, QueueInfo &queue, ResourceID cmdBufferId)
	{
		auto	cmdbuf = _cmdBuffers.find( cmdBufferId );
		CHECK_ERR( cmdbuf != _cmdBuffers.end() );
		CHECK_ERR( not cmdbuf->second.recording );

		queue.usageFlags |= cmdbuf->second.queueUsageFlags;

		// update command pool usage in queue
		{
			auto	inserted = queue.commandPools.insert({ cmdbuf->second.commandPool, {} });

			if ( inserted.second )
				inserted.first->second.push_back({ cmdbuf->second.commandPool, pos, pos });
			else
				inserted.first->second.back().last = pos;
		}

		// merge image usage
		for (auto& image : cmdbuf->second.imageUsage)
		{
			queue.imageUsage.insert({ image.first, {} }).first->second.push_back( image.second );
		}

		// merge buffer usage
		for (auto& buffer : cmdbuf->second.bufferUsage)
		{
			queue.bufferUsage.insert({ buffer.first, {} }).first->second.push_back( buffer.second );
		}

		// submit secondary command buffers
		for (auto& secondary : cmdbuf->second.secondaryBuffers)
		{
			CHECK_ERR( _QueueSubmitCommand( secondary.second, queue, secondary.first ));
		}

		if ( cmdbuf->second.oneTimeSubmit )
		{
			cmdbuf->second.bufferUsage.clear();
			cmdbuf->second.imageUsage.clear();
			cmdbuf->second.secondaryBuffers.clear();
		}
		return true;
	}
	
/*
=================================================
	_ProcessCommandPoolUsage
=================================================
*/
	bool QueueAnalyzer::_ProcessCommandPoolUsage (const TraceRange::Iterator &pos, ResourceID id, EResOp op)
	{
		if ( op == EResOp::Construct )
		{
			CHECK_ERR( pos->packet_id == VKTRACE_TPI_VK_vkCreateCommandPool );

			auto&	packet = pos.Cast< packet_vkCreateCommandPool >();
			CHECK_ERR( ResourceID(*packet.pCommandPool) == id );

			for (auto& q : _queues)
			{
				auto&	q_info = q.second.back();

				if ( q_info.familyIndex == packet.pCreateInfo->queueFamilyIndex )
				{
					q_info.commandPools.insert({ id, {} }).first->second.push_back({ id, pos.GetBookmark(), pos.GetBookmark() });
				}
			}
			return true;
		}

		return true;
	}

/*
=================================================
	_ProcessCommandBufferUsage
=================================================
*/
	bool QueueAnalyzer::_ProcessCommandBufferUsage (const TraceRange::Iterator &pos, ResourceID id, EResOp op)
	{
		if ( op == EResOp::Construct )
		{
			CHECK_ERR( pos->packet_id == VKTRACE_TPI_VK_vkAllocateCommandBuffers );

			auto&	packet	= pos.Cast< packet_vkAllocateCommandBuffers >();
			CHECK_ERR( packet.pAllocateInfo );

			auto	cmdbuf = _cmdBuffers.insert({ id, CommandBufferState() }).first;

			cmdbuf->second.commandPool	= ResourceID(packet.pAllocateInfo->commandPool);
			cmdbuf->second.isSecondary	= (packet.pAllocateInfo->level != VK_COMMAND_BUFFER_LEVEL_PRIMARY);
			return true;
		}

		if ( op == EResOp::Destruct )
		{
			CHECK_ERR(	pos->packet_id == VKTRACE_TPI_VK_vkFreeCommandBuffers or
						pos->packet_id == VKTRACE_TPI_VK_vkDestroyCommandPool );

			CHECK( _cmdBuffers.erase( id ) == 1 );
			return true;
		} 
		
		auto	cmdbuf = _cmdBuffers.find( id );
		CHECK_ERR( cmdbuf != _cmdBuffers.end() );

		switch ( pos->packet_id )
		{
			// Begin
			case VKTRACE_TPI_VK_vkBeginCommandBuffer :
			{
				auto&	packet = pos.Cast< packet_vkBeginCommandBuffer >();
				CHECK_ERR( packet.pBeginInfo );
				CHECK_ERR( ResourceID(packet.commandBuffer) == id );

				cmdbuf->second.oneTimeSubmit	= EnumEq( packet.pBeginInfo->flags, VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT );
				cmdbuf->second.recording		= true;
				cmdbuf->second.bufferUsage.clear();
				cmdbuf->second.imageUsage.clear();
				cmdbuf->second.secondaryBuffers.clear();
				break;
			}

			// End
			case VKTRACE_TPI_VK_vkEndCommandBuffer :
			{
				auto&	packet = pos.Cast< packet_vkEndCommandBuffer >();
				CHECK_ERR( ResourceID(packet.commandBuffer) == id );

				CHECK_ERR( cmdbuf->second.recording );
				cmdbuf->second.recording = false;
				break;
			}

			// Reset
			case VKTRACE_TPI_VK_vkResetCommandBuffer :
			case VKTRACE_TPI_VK_vkResetCommandPool :
			{
				CHECK_ERR( not cmdbuf->second.recording );
				
				cmdbuf->second.bufferUsage.clear();
				cmdbuf->second.imageUsage.clear();
				cmdbuf->second.secondaryBuffers.clear();
				break;
			}

			// ExecuteCommands
			case VKTRACE_TPI_VK_vkCmdExecuteCommands :
			{
				auto&	packet = pos.Cast< packet_vkCmdExecuteCommands >();
				if ( ResourceID(packet.commandBuffer) != id )
					return true; // skip secondary buffers
				
				CHECK_ERR( cmdbuf->second.recording );

				for (uint i = 0; i < packet.commandBufferCount; ++i) {
					cmdbuf->second.secondaryBuffers.insert({ ResourceID(packet.pCommandBuffers[i]), pos.GetBookmark() });
				}
				break;
			}
			
			// WaitEvents
			case VKTRACE_TPI_VK_vkCmdWaitEvents :
			{
				auto& packet = pos.Cast< packet_vkCmdWaitEvents >();

				CHECK_ERR( _OnCmdPipelineBarrier( { packet.pBufferMemoryBarriers, packet.bufferMemoryBarrierCount },
												  { packet.pImageMemoryBarriers, packet.imageMemoryBarrierCount },
												  id, pos.GetBookmark() ));
				break;
			}

			// PipelineBarrier
			case VKTRACE_TPI_VK_vkCmdPipelineBarrier :
			{
				auto&	packet = pos.Cast< packet_vkCmdPipelineBarrier >();

				CHECK_ERR( _OnCmdPipelineBarrier( { packet.pBufferMemoryBarriers, packet.bufferMemoryBarrierCount },
												  { packet.pImageMemoryBarriers, packet.imageMemoryBarrierCount },
												  id, pos.GetBookmark() ));
				break;
			}
			
			case VKTRACE_TPI_VK_vkCmdDraw :
			case VKTRACE_TPI_VK_vkCmdDrawIndexed :
			case VKTRACE_TPI_VK_vkCmdDrawIndirect :
			case VKTRACE_TPI_VK_vkCmdDrawIndexedIndirect :
			case VKTRACE_TPI_VK_vkCmdClearAttachments :
			case VKTRACE_TPI_VK_vkCmdBeginRenderPass :
			case VKTRACE_TPI_VK_vkCmdNextSubpass :
			case VKTRACE_TPI_VK_vkCmdEndRenderPass :
			case VKTRACE_TPI_VK_vkCmdDrawIndirectCountAMD :
			case VKTRACE_TPI_VK_vkCmdDrawIndexedIndirectCountAMD :
			case VKTRACE_TPI_VK_vkCmdClearDepthStencilImage :
			case VKTRACE_TPI_VK_vkCmdBlitImage :
			case VKTRACE_TPI_VK_vkCmdResolveImage :
				cmdbuf->second.queueUsageFlags |= VK_QUEUE_GRAPHICS_BIT;
				break;
				
			case VKTRACE_TPI_VK_vkCmdDispatch :
			case VKTRACE_TPI_VK_vkCmdDispatchIndirect :
			case VKTRACE_TPI_VK_vkCmdDispatchBase :
				cmdbuf->second.queueUsageFlags |= VK_QUEUE_COMPUTE_BIT;
				break;
				
			// graphics and/or compute
			case VKTRACE_TPI_VK_vkCmdClearColorImage :
			case VKTRACE_TPI_VK_vkCmdProcessCommandsNVX :
			case VKTRACE_TPI_VK_vkCmdReserveSpaceForCommandsNVX : {
				auto&	flags = cmdbuf->second.queueUsageFlags;
				if ( (flags & (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT)) == 0 )
					flags |= (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT);
				break;
			}

			case VKTRACE_TPI_VK_vkCmdCopyBuffer :
			case VKTRACE_TPI_VK_vkCmdCopyImage :
			case VKTRACE_TPI_VK_vkCmdCopyBufferToImage :
			case VKTRACE_TPI_VK_vkCmdCopyImageToBuffer :
			case VKTRACE_TPI_VK_vkCmdUpdateBuffer :
			case VKTRACE_TPI_VK_vkCmdFillBuffer :
				cmdbuf->second.queueUsageFlags |= VK_QUEUE_TRANSFER_BIT;
				break;
		}
		return true;
	}
	
/*
=================================================
	CheckQueueAcquireReleaseOp
=================================================
*/
	template <typename T>
	void CheckQueueAcquireReleaseOp (const T &barrier)
	{
		if ( barrier.srcQueueFamilyIndex == barrier.dstQueueFamilyIndex )
			return;

		ASSERT( barrier.srcQueueFamilyIndex != VK_QUEUE_FAMILY_IGNORED and
				barrier.dstQueueFamilyIndex != VK_QUEUE_FAMILY_IGNORED );

		if ( barrier.srcAccessMask == 0 and barrier.dstAccessMask == 0 )
		{
			ASSERT(false);	// unknown operation
		}
		else
		// release operation
		if ( barrier.dstAccessMask == 0 )
		{
			// TODO ?
		}
		else
		// acquire operation
		if ( barrier.srcAccessMask == 0 )
		{
			// TODO ?
		}
		else
		{
			ASSERT(false);	// unknown operation
		}
	}

/*
=================================================
	_OnCmdPipelineBarrier
=================================================
*/
	bool QueueAnalyzer::_OnCmdPipelineBarrier (ArrayView<VkBufferMemoryBarrier> bufferBarriers, ArrayView<VkImageMemoryBarrier> imageBarriers,
												ResourceID id, TraceRange::Bookmark pos)
	{
		auto	cmdbuf = _cmdBuffers.find( id );
		CHECK_ERR( cmdbuf != _cmdBuffers.end() );
		CHECK_ERR( cmdbuf->second.recording );

		for (auto& bufbar : bufferBarriers)
		{
			auto	result = cmdbuf->second.bufferUsage.insert({ ResourceID(bufbar.buffer), {} });

			if ( result.second ) {
				result.first->second.first	= pos;
				result.first->second.id		= ResourceID(bufbar.buffer);
			}

			result.first->second.last = pos;

			CheckQueueAcquireReleaseOp( bufbar );
		}

		for (auto& imgbar : imageBarriers)
		{
			auto	result = cmdbuf->second.imageUsage.insert({ ResourceID(imgbar.image), {} });

			if ( result.second ) {
				result.first->second.first	= pos;
				result.first->second.id		= ResourceID(imgbar.image);
			}

			result.first->second.last = pos;

			CheckQueueAcquireReleaseOp( imgbar );
		}

		return true;
	}
	
/*
=================================================
	AddQueueID
=================================================
*/
	inline void AddQueueID (INOUT Array<ResourceID> &queueIDs, ResourceID id)
	{
		for (auto& q : queueIDs) {
			if ( q == id )
				return;
		}
		queueIDs.push_back( id );
	}
	
/*
=================================================
	GetCommandPoolQueues
=================================================
*/
	void QueueAnalyzer::GetCommandPoolQueues (ResourceID id, TraceRange::Bookmark begin, TraceRange::Bookmark end, OUT Array<ResourceID> &queueIDs) const
	{
		queueIDs.clear();

		for (auto& q : _queues)
		for (auto& q_inst : q.second)
		{
			if ( IsIntersects( q_inst.FirstBookmark().pos, q_inst.LastBookmark().pos, begin, end ))
				continue;
				
			auto	pool = q_inst.commandPools.find( id );
			if ( pool == q_inst.commandPools.end() )
				continue;

			AddQueueID( queueIDs, q_inst.id );
		}
	}
	
/*
=================================================
	GetImageQueues
=================================================
*/
	void QueueAnalyzer::GetImageQueues (ResourceID id, TraceRange::Bookmark begin, TraceRange::Bookmark end, OUT Array<ResourceID> &queueIDs) const
	{
		queueIDs.clear();

		for (auto& q : _queues)
		for (auto& q_inst : q.second)
		{
			if ( IsIntersects( q_inst.FirstBookmark().pos, q_inst.LastBookmark().pos, begin, end ))
				continue;
				
			auto	img = q_inst.imageUsage.find( id );
			if ( img == q_inst.imageUsage.end() )
				continue;

			AddQueueID( queueIDs, q_inst.id );
		}
	}
	
/*
=================================================
	GetBufferQueues
=================================================
*/
	void QueueAnalyzer::GetBufferQueues (ResourceID id, TraceRange::Bookmark begin, TraceRange::Bookmark end, OUT Array<ResourceID> &queueIDs) const
	{
		queueIDs.clear();

		for (auto& q : _queues)
		for (auto& q_inst : q.second)
		{
			if ( IsIntersects( q_inst.FirstBookmark().pos, q_inst.LastBookmark().pos, begin, end ))
				continue;
				
			auto	buf = q_inst.bufferUsage.find( id );
			if ( buf == q_inst.bufferUsage.end() )
				continue;

			AddQueueID( queueIDs, q_inst.id );
		}
	}
	
/*
=================================================
	GetDeviceQueues
=================================================
*/
	Array<QueueAnalyzer::QueueInfo_t const*>  QueueAnalyzer::GetDeviceQueues (ResourceID deviceId, TraceRange::Bookmark pos) const
	{
		Array<QueueInfo_t const*>	result;

		auto*	dev_info = _deviceAnalyzer->GetLogicalDeviceInfo( deviceId, pos );
		CHECK_ERR( dev_info );

		for (auto& q : _queues)
		for (auto& q_inst : q.second)
		{
			if ( IsIntersects( q_inst.FirstBookmark().pos, q_inst.LastBookmark().pos,
							   dev_info->FirstBookmark().pos, dev_info->LastBookmark().pos ))
			{
				result.push_back( &q_inst );
			}
		}

		return result;
	}


}	// VTC
