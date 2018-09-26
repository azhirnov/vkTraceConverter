// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Analyzer/Ext/SynchronizationsAnalyzer.h"
#include "Analyzer/Default/ImageAnalyzer.h"
#include "Parser/AppTrace.h"

namespace VTC
{

/*
=================================================
	constructor
=================================================
*/
	SynchronizationsAnalyzer::SynchronizationsAnalyzer ()
	{
	}
	
/*
=================================================
	PreProcess
=================================================
*/
	void SynchronizationsAnalyzer::PreProcess (const AppTrace &appTrace)
	{
		_cmdBuffers.clear();
		_queues.clear();
		_uidCounter = 0;

		_renderPassAnalyzer = appTrace.GetAnalyzer< RenderPassAnalyzer >();
		_imageAnalyzer		= appTrace.GetAnalyzer< ImageAnalyzer >();

		CHECK( _renderPassAnalyzer and _imageAnalyzer );
	}
	
/*
=================================================
	PostProcess
=================================================
*/
	void SynchronizationsAnalyzer::PostProcess ()
	{
	}

/*
=================================================
	AddResourceUsage
=================================================
*/
	void SynchronizationsAnalyzer::AddResourceUsage (const TraceRange::Iterator &pos, EResourceType type, ResourceID id, FrameID frameId, EResOp op)
	{
		switch ( type )
		{
			case VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT :			CHECK( _ProcessDevice( pos, id, frameId, op ));		break;
			case VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT :			CHECK( _ProcessQueue( pos, id, frameId, op ));		break;
			case VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT :	CHECK( _ProcessSwapchain( pos, id, frameId, op ));	break;
			case VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT :	CHECK( _ProcessCommandBuffer( pos, id, op ));		break;
			case VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT :		CHECK( _ProcessSemaphore( pos, id, op ));			break;
			case VK_DEBUG_REPORT_OBJECT_TYPE_EVENT_EXT :			CHECK( _ProcessEvent( pos, id, op ));				break;
			case VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT :			CHECK( _ProcessImage( pos, id, frameId, op ));		break;
		}
	}
	
/*
=================================================
	_ProcessDevice
=================================================
*/
	bool SynchronizationsAnalyzer::_ProcessDevice (const TraceRange::Iterator &pos, ResourceID id, FrameID frameId, EResOp op)
	{
		if ( op == EResOp::Construct )
		{
			Devices_t::iterator		dev;
			CHECK_ERR( _devices.AddResourceUsage( OUT dev, pos, id, op ));
			
			dev->second.back().id = id;
			return true;
		}

		if ( op == EResOp::Destruct )
		{
			CHECK_ERR( _devices.AddResourceUsage( pos, id, op ));
			return true;
		}

		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkDeviceWaitIdle :			CHECK_ERR( _OnDeviceWaitIdle( pos, id, frameId ));		break;
			case VKTRACE_TPI_VK_vkWaitForFences :			CHECK_ERR( _OnWaitForFences( pos, id, frameId ));		break;
			case VKTRACE_TPI_VK_vkResetFences :				CHECK_ERR( _OnResetFences( pos, id, frameId ));			break;
		}

		return true;
	}
	
/*
=================================================
	_OnDeviceWaitIdle
=================================================
*/
	bool SynchronizationsAnalyzer::_OnDeviceWaitIdle (const TraceRange::Iterator &pos, ResourceID id, FrameID frameId)
	{
		auto&	packet = pos.Cast< packet_vkDeviceWaitIdle >();
		CHECK_ERR( id == ResourceID(packet.device) );
		
		Devices_t::iterator		dev;
		CHECK_ERR( _devices.AddResourceUsage( OUT dev, pos, id, EResOp::Access ));

		// add host sync
		auto&	bm = dev->second.back().bookmarks.back();
		bm.uid		= ++_uidCounter;
		bm.frameId	= frameId;
		bm.threadId	= ThreadID(pos->thread_id);
		bm.data		= HostWaitForDeviceIdle{};
		
		// add queue sync
		for (auto& q : _queues)
		{
			auto&	q_info = q.second.back();

			if ( q_info.deviceId == id )
			{
				Queues_t::iterator	queue;
				CHECK_ERR( _queues.AddResourceUsage( OUT queue, pos, q_info.id, EResOp::Access ));
		
				auto&	qbm = queue->second.back().bookmarks.back();
				qbm.uid		= ++_uidCounter;
				qbm.frameId	= frameId;
				
				CHECK_ERR( _BuildCommandDependencies( qbm.uid, queue->second.back() ));
				CHECK_ERR( _BuildQueueWaitDependencies( qbm.uid, queue->second.back() ));
				qbm.data = QueueWaitIdle{};

				bm.input.push_back( qbm.uid );
				qbm.output.push_back( bm.uid );
			}
		}
		return true;
	}

/*
=================================================
	_OnWaitForFences
=================================================
*/
	bool SynchronizationsAnalyzer::_OnWaitForFences (const TraceRange::Iterator &pos, ResourceID id, FrameID frameId)
	{
		auto&	packet = pos.Cast< packet_vkWaitForFences >();
		CHECK_ERR( id == ResourceID(packet.device) );

		Devices_t::iterator		dev;
		CHECK_ERR( _devices.AddResourceUsage( OUT dev, pos, id, EResOp::Access ));

		auto&	bm = dev->second.back().bookmarks.back();
		bm.uid		= ++_uidCounter;
		bm.frameId	= frameId;
		bm.threadId	= ThreadID(pos->thread_id);

		HostWaitForFences	sync;
		sync.waitAll	= packet.waitAll;
		sync.fences.reserve( packet.fenceCount );

		for (uint i = 0; i < packet.fenceCount; ++i)
		{
			sync.fences.push_back( ResourceID(packet.pFences[i]) );

			UID		uid = 0;
			CHECK_ERR( _FindSignaledFence( dev->second.back(), ResourceID(packet.pFences[i]), bm.uid, OUT uid ));
			bm.input.push_back( uid );
		}
		
		bm.data = std::move(sync);
		return true;
	}
	
/*
=================================================
	_OnResetFences
=================================================
*/
	bool SynchronizationsAnalyzer::_OnResetFences (const TraceRange::Iterator &pos, ResourceID id, FrameID frameId)
	{
		auto&	packet = pos.Cast< packet_vkResetFences >();
		CHECK_ERR( id == ResourceID(packet.device) );
		
		Devices_t::iterator		dev;
		CHECK_ERR( _devices.AddResourceUsage( OUT dev, pos, id, EResOp::Access ));

		auto&	bm = dev->second.back().bookmarks.back();
		bm.uid		= ++_uidCounter;
		bm.frameId	= frameId;
		bm.threadId	= ThreadID(pos->thread_id);

		HostResetFences		sync;
		sync.fences.reserve( packet.fenceCount );

		for (uint i = 0; i < packet.fenceCount; ++i) {
			sync.fences.push_back( ResourceID(packet.pFences[i]) );
		}
		
		bm.data = std::move(sync);
		return true;
	}

/*
=================================================
	_ProcessQueue
=================================================
*/
	bool SynchronizationsAnalyzer::_ProcessQueue (const TraceRange::Iterator &pos, ResourceID id, FrameID frameId, EResOp op)
	{
		if ( op == EResOp::Construct )
		{
			Queues_t::iterator	queue;
			CHECK_ERR( _queues.AddResourceUsage( OUT queue, pos, id, op ));

			queue->second.back().id = id;

			if ( pos->packet_id == VKTRACE_TPI_VK_vkGetDeviceQueue )
			{
				queue->second.back().deviceId = ResourceID(pos.Cast< packet_vkGetDeviceQueue >().device);
			}
			if ( pos->packet_id == VKTRACE_TPI_VK_vkGetDeviceQueue2 )
			{
				queue->second.back().deviceId = ResourceID(pos.Cast< packet_vkGetDeviceQueue2 >().device);
			}
			return true;
		}

		if ( op == EResOp::Destruct )
		{
			CHECK_ERR( _queues.AddResourceUsage( pos, id, op ));
			return true;
		}

		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkQueueSubmit :			CHECK_ERR( _OnQueueSubmit( pos, id, frameId ));			break;
			case VKTRACE_TPI_VK_vkQueueWaitIdle :		CHECK_ERR( _OnQueueWaitIdle( pos, id, frameId ));		break;
			case VKTRACE_TPI_VK_vkQueueBindSparse :		CHECK_ERR( _OnQueueBindSparse( pos, id, frameId ));		break;
			case VKTRACE_TPI_VK_vkQueuePresentKHR :		CHECK_ERR( _OnQueuePresent( pos, id, frameId ));		break;
		}

		return true;
	}
	
/*
=================================================
	_OnQueueSubmit
=================================================
*/
	bool SynchronizationsAnalyzer::_OnQueueSubmit (const TraceRange::Iterator &pos, ResourceID id, FrameID frameId)
	{
		auto&	packet = pos.Cast< packet_vkQueueSubmit >();
		CHECK_ERR( id == ResourceID(packet.queue) );

		const UID	submit_uid	= ++_uidCounter;
		const UID	first_uid	= ++_uidCounter;
		const UID	fence_uid	= packet.fence ? first_uid + packet.submitCount*2 : 0;

		_uidCounter = first_uid + packet.submitCount*2 + uint(packet.fence != 0);

		for (uint i = 0; i < packet.submitCount; ++i)
		{
			CHECK_ERR( _SubmitCommands( packet.pSubmits[i], pos, id, frameId, first_uid + i*2, fence_uid, submit_uid ));
		}
		
		// add host sync
		{
			auto*	queue = _queues.FindIn( id, pos.GetBookmark() );
			CHECK_ERR( queue );

			Devices_t::iterator		dev;
			CHECK_ERR( _devices.AddResourceUsage( OUT dev, pos, queue->deviceId, EResOp::Access ));
			
			auto&	bm = dev->second.back().bookmarks.back();
			bm.uid		= submit_uid;
			bm.frameId	= frameId;
			bm.threadId	= ThreadID(pos->thread_id);
			bm.data		= HostQueueSubmit{ ResourceID(packet.fence), fence_uid };
				
			// add dependency on execution start
			for (UID i = first_uid; i < fence_uid; i += 2) {
				bm.output.push_back( i );
			}
		}

		if ( packet.fence )
		{
			Queues_t::iterator	queue;
			CHECK_ERR( _queues.AddResourceUsage( OUT queue, pos, id, EResOp::Access ));
			
			// add queue sync
			{
				auto&	bm = queue->second.back().bookmarks.back();
				bm.frameId	= frameId;
				bm.uid		= fence_uid;
				bm.data		= QueueFenceSignal{ ResourceID(packet.fence) };

				// add dependency on execution complete
				for (UID i = first_uid+1; i < fence_uid; i += 2) {
					bm.input.push_back( i );
				}
			}
		}
		return true;
	}
	
/*
=================================================
	_SubmitCommands
=================================================
*/
	bool SynchronizationsAnalyzer::_SubmitCommands (const VkSubmitInfo &src, const TraceRange::Iterator &pos, ResourceID id, FrameID frameId,
													UID uid, UID fenceUID, UID hostSubmitUID)
	{
		// start command execution
		{
			Queues_t::iterator	queue;
			CHECK_ERR( _queues.AddResourceUsage( OUT queue, pos, id, EResOp::Access ));

			auto&				bm	= queue->second.back().bookmarks.back();
			QueueExecutionStart	dst;

			// add wait semaphores
			for (uint j = 0; j < src.waitSemaphoreCount; ++j)
			{
				dst.waitSemaphores.push_back({ ResourceID(src.pWaitSemaphores[j]), src.pWaitDstStageMask[j] });

				CHECK_ERR( _WaitSemaphore( ResourceID(src.pWaitSemaphores[j]), [&bm](ResourceID, UID uid) { bm.input.push_back( uid ); } ));
			}

			// add command buffers
			for (uint j = 0; j < src.commandBufferCount; ++j)
			{
				auto	cmdbuf = _cmdBuffers.find( ResourceID(src.pCommandBuffers[j]) );
				CHECK_ERR( cmdbuf != _cmdBuffers.end() );
				CHECK_ERR( cmdbuf->second.state == ECmdBufferState::Recorded );

				if ( EnumEq( cmdbuf->second.flags, VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT ) )
				{
					dst.syncQueues.push_back( std::move(cmdbuf->second.syncQueue) );

					cmdbuf->second.state		= ECmdBufferState::Initial;
					cmdbuf->second.syncQueue	= {};
				}
				else
				{
					SyncQueue	temp;
					_MergeSyncQueues( INOUT temp, cmdbuf->second.syncQueue );

					dst.syncQueues.push_back( std::move(temp) );
				}
			}

			bm.frameId	= frameId;
			bm.uid		= uid;
			bm.data		= std::move(dst);
			//bm.output.push_back( uid+1 );
			bm.input.push_back( hostSubmitUID );

			if ( src.signalSemaphoreCount )
				CHECK_ERR( _BuildCommandDependencies( uid+1, queue->second.back() ));
		}

		// finish execution
		{
			Queues_t::iterator	queue;
			CHECK_ERR( _queues.AddResourceUsage( OUT queue, pos, id, EResOp::Access ));

			auto&					bm	= queue->second.back().bookmarks.back();
			QueueExecutionFinish	dst;

			// add signal semaphores
			for (uint j = 0; j < src.signalSemaphoreCount; ++j)
			{
				dst.signalSemaphores.push_back( ResourceID(src.pSignalSemaphores[j]) );

				CHECK_ERR( _SignalSemaphore( pos.GetBookmark(), ResourceID(src.pSignalSemaphores[j]), uid+1 ));
			}
				
			bm.frameId	= frameId;
			bm.uid		= uid + 1;
			bm.data		= std::move(dst);
			//bm.input.push_back( uid );

			if ( fenceUID )
				bm.output.push_back( fenceUID );
		}
		return true;
	}

/*
=================================================
	_OnQueueWaitIdle
=================================================
*/
	bool SynchronizationsAnalyzer::_OnQueueWaitIdle (const TraceRange::Iterator &pos, ResourceID id, FrameID frameId)
	{
		auto&	packet = pos.Cast< packet_vkQueueWaitIdle >();
		CHECK_ERR( id == ResourceID(packet.queue) );

		Queues_t::iterator	queue;
		CHECK_ERR( _queues.AddResourceUsage( OUT queue, pos, ResourceID(packet.queue), EResOp::Access ));
		auto&	q_info = queue->second.back();

		// add queue sync
		{
			auto&	bm = q_info.bookmarks.back();
			bm.uid		= ++_uidCounter;
			bm.frameId	= frameId;

			CHECK_ERR( _BuildCommandDependencies( bm.uid, queue->second.back() ));
			CHECK_ERR( _BuildQueueWaitDependencies( bm.uid, queue->second.back() ));
			bm.data = QueueWaitIdle{};
			
			bm.output.push_back( bm.uid + 1 );
		}

		// add host sync
		{
			Devices_t::iterator		dev;
			CHECK_ERR( _devices.AddResourceUsage( OUT dev, pos, q_info.deviceId, EResOp::Access ));

			auto&	bm = dev->second.back().bookmarks.back();
			bm.uid		= ++_uidCounter;
			bm.frameId	= frameId;
			bm.threadId	= ThreadID(pos->thread_id);
			bm.data		= HostWaitForQueueIdle{ q_info.id };

			bm.input.push_back( bm.uid - 1 );
		}
		return true;
	}
	
/*
=================================================
	_OnQueueBindSparse
=================================================
*/
	bool SynchronizationsAnalyzer::_OnQueueBindSparse (const TraceRange::Iterator &pos, ResourceID id, FrameID)
	{
		auto&	packet = pos.Cast< packet_vkQueueBindSparse >();
		CHECK_ERR( id == ResourceID(packet.queue) );

		ASSERT(false);	// TODO
		return true;
	}
	
/*
=================================================
	_OnQueueBindSparse
=================================================
*/
	bool SynchronizationsAnalyzer::_OnQueuePresent (const TraceRange::Iterator &pos, ResourceID id, FrameID frameId)
	{
		auto&	packet = pos.Cast< packet_vkQueuePresentKHR >();
		CHECK_ERR( id == ResourceID(packet.queue) );
		
		for (uint j = 0; j < packet.pPresentInfo->swapchainCount; ++j)
		{
			Swapchains_t::iterator		swapchain;
			CHECK_ERR( _swapchains.AddResourceUsage( OUT swapchain, pos, ResourceID(packet.pPresentInfo->pSwapchains[j]), EResOp::Access ));

			SwapchainPresent	sync;
			auto&				bm = swapchain->second.back().bookmarks.back();
			bm.uid		= ++_uidCounter;
			bm.frameId	= frameId;

			for (uint i = 0; i < packet.pPresentInfo->waitSemaphoreCount; ++i)
			{
				sync.waitSemaphores.push_back( ResourceID(packet.pPresentInfo->pWaitSemaphores[i]) );

				CHECK_ERR( _WaitSemaphore( ResourceID(packet.pPresentInfo->pWaitSemaphores[i]),
										   [&bm] (ResourceID, UID uid) { bm.input.push_back( uid ); } ));
			}
			bm.data = std::move(sync);
		}
		return true;
	}
	
/*
=================================================
	_ProcessSwapchain
=================================================
*/
	bool SynchronizationsAnalyzer::_ProcessSwapchain (const TraceRange::Iterator &pos, ResourceID id, FrameID frameId, EResOp op)
	{
		if ( op == EResOp::Construct )
		{
			CHECK_ERR( pos->packet_id == VKTRACE_TPI_VK_vkCreateSwapchainKHR );

			auto&	packet = pos.Cast< packet_vkCreateSwapchainKHR >();
			CHECK_ERR( id == ResourceID(*packet.pSwapchain) );

			Swapchains_t::iterator	swapchain;
			CHECK_ERR( _swapchains.AddResourceUsage( OUT swapchain, pos, id, op ));

			swapchain->second.back().id			= id;
			swapchain->second.back().deviceId	= ResourceID(packet.device);
			return true;
		}

		if ( op == EResOp::Destruct )
		{
			CHECK_ERR( _swapchains.AddResourceUsage( pos, id, op ));
			return true;
		}

		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkAcquireNextImageKHR :		CHECK_ERR( _OnAcquireNextImage( pos, id, frameId ));	break;
			case VKTRACE_TPI_VK_vkAcquireNextImage2KHR :	CHECK_ERR( _OnAcquireNextImage2( pos, id, frameId ));	break;
		}
		return true;
	}
	
/*
=================================================
	_OnAcquireNextImage
=================================================
*/
	bool SynchronizationsAnalyzer::_OnAcquireNextImage (const TraceRange::Iterator &pos, ResourceID id, FrameID frameId)
	{
		auto&	packet = pos.Cast< packet_vkAcquireNextImageKHR >();
		CHECK_ERR( id == ResourceID(packet.swapchain) );

		Swapchains_t::iterator		swapchain;
		CHECK_ERR( _swapchains.AddResourceUsage( OUT swapchain, pos, id, EResOp::Access ));

		// add to swapchain
		{
			auto&	bm = swapchain->second.back().bookmarks.back();
			bm.uid		= ++_uidCounter;
			bm.frameId	= frameId;
			bm.data		= SwapchainAcquireImage{ packet.semaphore != 0 };
			
			if ( packet.fence )
				bm.output.push_back( bm.uid + 1 );

			if ( packet.semaphore )
				CHECK_ERR( _SignalSemaphore( pos.GetBookmark(), ResourceID(packet.semaphore), bm.uid ));
		}

		// add to device
		if ( packet.fence )
		{
			Devices_t::iterator		dev;
			CHECK_ERR( _devices.AddResourceUsage( OUT dev, pos, swapchain->second.back().deviceId, EResOp::Access ));

			auto&	bm = dev->second.back().bookmarks.back();
			bm.uid		= ++_uidCounter;
			bm.frameId	= frameId;
			bm.data		= HostAcquireNextImage{ ResourceID(packet.fence) };
			bm.input.push_back( bm.uid - 1 );
		}
		return true;
	}
	
/*
=================================================
	_OnAcquireNextImage2
=================================================
*/
	bool SynchronizationsAnalyzer::_OnAcquireNextImage2 (const TraceRange::Iterator &pos, ResourceID id, FrameID frameId)
	{
		auto&	packet = pos.Cast< packet_vkAcquireNextImage2KHR >();
		CHECK_ERR( id == ResourceID(packet.pAcquireInfo->swapchain) );
		
		Swapchains_t::iterator		swapchain;
		CHECK_ERR( _swapchains.AddResourceUsage( OUT swapchain, pos, id, EResOp::Access ));

		// add to swapchain
		{
			auto&	bm = swapchain->second.back().bookmarks.back();
			bm.uid		= ++_uidCounter;
			bm.frameId	= frameId;
			bm.data		= SwapchainAcquireImage{ packet.pAcquireInfo->semaphore != 0 };

			if ( packet.pAcquireInfo->fence )
				bm.output.push_back( bm.uid + 1 );

			if ( packet.pAcquireInfo->semaphore )
				CHECK_ERR( _SignalSemaphore( pos.GetBookmark(), ResourceID(packet.pAcquireInfo->semaphore), bm.uid ));
		}

		// add to device
		if ( packet.pAcquireInfo->fence )
		{
			Devices_t::iterator		dev;
			CHECK_ERR( _devices.AddResourceUsage( OUT dev, pos, swapchain->second.back().deviceId, EResOp::Access ));

			auto&	bm = dev->second.back().bookmarks.back();
			bm.uid		= ++_uidCounter;
			bm.frameId	= frameId;
			bm.data		= HostAcquireNextImage{ ResourceID(packet.pAcquireInfo->fence) };
			bm.input.push_back( bm.uid - 1 );
		}
		return true;
	}

/*
=================================================
	_ProcessCommandBuffer
=================================================
*/
	bool SynchronizationsAnalyzer::_ProcessCommandBuffer (const TraceRange::Iterator &pos, ResourceID id, EResOp op)
	{
		if ( op == EResOp::Destruct )
		{
			_cmdBuffers.erase( id );
			return true;
		}

		if ( pos->packet_id == VKTRACE_TPI_VK_vkBeginCommandBuffer )
		{
			auto&	packet = pos.Cast< packet_vkBeginCommandBuffer >();
			CHECK_ERR( ResourceID(packet.commandBuffer) == id );

			auto	cmdbuf	= _cmdBuffers.insert({ id, {} });
			auto&	info	= cmdbuf.first->second;
			CHECK_ERR( info.state != ECmdBufferState::Recording );

			info.id				= id;
			info.state			= ECmdBufferState::Recording;
			info.flags			= packet.pBeginInfo->flags;
			info.cmdBufferUID	= ++_uidCounter;

			return true;
		}

		auto	cmdbuf = _cmdBuffers.find( id );
		if ( cmdbuf == _cmdBuffers.end() )
			return true;


		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkCmdWaitEvents :			CHECK( _OnCmdWaitEvents( pos, cmdbuf->second ));		break;
			case VKTRACE_TPI_VK_vkCmdSetEvent :				CHECK( _OnCmdSetEvent( pos, cmdbuf->second ));			break;
			case VKTRACE_TPI_VK_vkCmdResetEvent :			CHECK( _OnCmdResetEvent( pos, cmdbuf->second ));		break;
			case VKTRACE_TPI_VK_vkCmdPipelineBarrier :		CHECK( _OnCmdPipelineBarrier( pos, cmdbuf->second ));	break;
			case VKTRACE_TPI_VK_vkCmdBeginRenderPass :		CHECK( _OnCmdBeginRenderPass( pos, cmdbuf->second ));	break;
			case VKTRACE_TPI_VK_vkCmdNextSubpass :			CHECK( _OnCmdNextSubpass( pos, cmdbuf->second ));		break;
			case VKTRACE_TPI_VK_vkCmdEndRenderPass :		CHECK( _OnCmdEndRenderPass( pos, cmdbuf->second ));		break;
			case VKTRACE_TPI_VK_vkCmdExecuteCommands :		CHECK( _OnCmdExecuteCommands( pos, cmdbuf->second ));	break;

			case VKTRACE_TPI_VK_vkResetCommandBuffer :
			case VKTRACE_TPI_VK_vkResetCommandPool :
				cmdbuf->second.state		= ECmdBufferState::Initial;
				cmdbuf->second.syncQueue	= {};
				break;

			case VKTRACE_TPI_VK_vkEndCommandBuffer :
				cmdbuf->second.state = ECmdBufferState::Recorded;
				break;
		}
		return true;
	}
	
/*
=================================================
	_OnCmdWaitEvents
=================================================
*/
	bool SynchronizationsAnalyzer::_OnCmdWaitEvents (const TraceRange::Iterator &pos, CommandBufferState &state) const
	{
		auto&	packet = pos.Cast< packet_vkCmdWaitEvents >();
		CHECK_ERR( state.id == ResourceID(packet.commandBuffer) );
		CHECK_ERR( state.state == ECmdBufferState::Recording );

		state.funcUID = ++_uidCounter;

		//ASSERT(false);	// TODO
		return true;
	}
	
/*
=================================================
	_OnCmdSetEvent
=================================================
*/
	bool SynchronizationsAnalyzer::_OnCmdSetEvent (const TraceRange::Iterator &, CommandBufferState &) const
	{
		//ASSERT(false);	// TODO
		return true;
	}
	
/*
=================================================
	_OnCmdResetEvent
=================================================
*/
	bool SynchronizationsAnalyzer::_OnCmdResetEvent (const TraceRange::Iterator &, CommandBufferState &) const
	{
		//ASSERT(false);	// TODO
		return true;
	}
	
/*
=================================================
	_OnCmdPipelineBarrier
=================================================
*/
	bool SynchronizationsAnalyzer::_OnCmdPipelineBarrier (const TraceRange::Iterator &pos, CommandBufferState &state) const
	{
		auto&	packet = pos.Cast< packet_vkCmdPipelineBarrier >();
		CHECK_ERR( state.id == ResourceID(packet.commandBuffer) );
		CHECK_ERR( state.state == ECmdBufferState::Recording );
		ASSERT( packet.srcStageMask != 0 );
		ASSERT( packet.dstStageMask != 0 );
		
		state.funcUID = ++_uidCounter;

		if ( packet.pMemoryBarriers == null and
			 packet.pImageMemoryBarriers == null and
			 packet.pBufferMemoryBarriers == null )
		{
			CHECK_ERR( _ProcessExecutionBarrier( packet.srcStageMask, packet.dstStageMask, packet.dependencyFlags,
												 pos.GetBookmark(), pos->packet_id, state ));
			return true;
		}

		if ( packet.pMemoryBarriers ) {
			CHECK_ERR( _ProcessMemoryBarriers( packet.srcStageMask, packet.dstStageMask, packet.dependencyFlags,
											   packet.memoryBarrierCount, packet.pMemoryBarriers, pos.GetBookmark(), pos->packet_id, state ));
		}

		if ( packet.pImageMemoryBarriers ) {
			CHECK_ERR( _ProcessImageBarriers( packet.srcStageMask, packet.dstStageMask, packet.dependencyFlags,
											  packet.imageMemoryBarrierCount, packet.pImageMemoryBarriers, pos.GetBookmark(), pos->packet_id, state ));
		}

		if ( packet.pBufferMemoryBarriers ) {
			CHECK_ERR( _ProcessBufferBarriers( packet.srcStageMask, packet.dstStageMask, packet.dependencyFlags,
											   packet.bufferMemoryBarrierCount, packet.pBufferMemoryBarriers, pos.GetBookmark(), pos->packet_id, state ));
		}
		return true;
	}
	
/*
=================================================
	_ProcessExecutionBarrier
=================================================
*/
	bool SynchronizationsAnalyzer::_ProcessExecutionBarrier (VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags,
															 TraceRange::Bookmark pos, PacketID packetId, CommandBufferState &state) const
	{
		const uint	sp_index = state.subpassIndices.empty() ? VK_SUBPASS_EXTERNAL : state.subpassIndices.back().first;

		// add to global barriers
		{
			ExecutionSync	sync;
			sync.dependencyFlags	= dependencyFlags;
			sync.srcStageMask		= srcStageMask;
			sync.dstStageMask		= dstStageMask;

			SyncItem		item;
			item.uid				= ++_uidCounter;
			item.funcUID			= state.funcUID;
			item.packetId			= packetId;
			item.cmdBufferUID		= state.cmdBufferUID;
			item.renderPassUID		= state.renderPassUID;
			item.data				= sync;

			state.syncQueue.globalSync.push_back( std::move(item) );
		}

		// add execution barrier to all images
		for (auto& img : state.syncQueue.imageSync)
		{
			ImageSync		sync;
			sync.dependencyFlags	= dependencyFlags;
			sync.srcStageMask		= srcStageMask;
			sync.dstStageMask		= dstStageMask;
			sync.uid				= ++_uidCounter;
			sync.type				= ESyncType::ExecutionBarrier;
			sync.funcUID			= state.funcUID;
			sync.packetId			= packetId;
			sync.cmdBufferUID		= state.cmdBufferUID;
			sync.renderPassUID		= state.renderPassUID;
			sync.subpassIndex		= sp_index;

			img.second.push_back( std::move(sync) );
		}
		
		// add execution barrier to all buffers
		for (auto& buf : state.syncQueue.bufferSync)
		{
			BufferSync		sync;
			sync.dependencyFlags	= dependencyFlags;
			sync.srcStageMask		= srcStageMask;
			sync.dstStageMask		= dstStageMask;
			sync.uid				= ++_uidCounter;
			sync.type				= ESyncType::ExecutionBarrier;
			sync.funcUID			= state.funcUID;
			sync.packetId			= packetId;
			sync.cmdBufferUID		= state.cmdBufferUID;
			sync.renderPassUID		= state.renderPassUID;
			sync.subpassIndex		= sp_index;

			buf.second.push_back( std::move(sync) );
		}
		return true;
	}
	
/*
=================================================
	_ProcessMemoryBarriers
=================================================
*/
	bool SynchronizationsAnalyzer::_ProcessMemoryBarriers (VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags,
														   uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers,
														   TraceRange::Bookmark pos, PacketID packetId, CommandBufferState &state) const
	{
		const uint	sp_index = state.subpassIndices.empty() ? VK_SUBPASS_EXTERNAL : state.subpassIndices.back().first;

		for (uint i = 0; i < memoryBarrierCount; ++i)
		{
			// add to global barriers
			{
				MemorySync	sync;
				sync.dependencyFlags	= dependencyFlags;
				sync.srcStageMask		= srcStageMask;
				sync.dstStageMask		= dstStageMask;
				sync.srcAccessMask		= pMemoryBarriers[i].srcAccessMask;
				sync.dstAccessMask		= pMemoryBarriers[i].dstAccessMask;

				SyncItem	item;
				item.uid				= ++_uidCounter;
				item.funcUID			= state.funcUID;
				item.packetId			= packetId;
				item.cmdBufferUID		= state.cmdBufferUID;
				item.renderPassUID		= state.renderPassUID;
				item.data				= sync;

				state.syncQueue.globalSync.push_back( std::move(item) );
			}
			
			// add memory barrier to all images
			for (auto& img : state.syncQueue.imageSync)
			{
				ImageSync		sync;
				sync.dependencyFlags	= dependencyFlags;
				sync.srcStageMask		= srcStageMask;
				sync.dstStageMask		= dstStageMask;
				sync.srcAccessMask		= pMemoryBarriers[i].srcAccessMask;
				sync.dstAccessMask		= pMemoryBarriers[i].dstAccessMask;
				sync.uid				= ++_uidCounter;
				sync.type				= ESyncType::MemoryBarrier;
				sync.funcUID			= state.funcUID;
				sync.packetId			= packetId;
				sync.cmdBufferUID		= state.cmdBufferUID;
				sync.renderPassUID		= state.renderPassUID;
				sync.subpassIndex		= sp_index;

				img.second.push_back( std::move(sync) );
			}
		
			// add memory barrier to all buffers
			for (auto& buf : state.syncQueue.bufferSync)
			{
				BufferSync		sync;
				sync.dependencyFlags	= dependencyFlags;
				sync.srcStageMask		= srcStageMask;
				sync.dstStageMask		= dstStageMask;
				sync.srcAccessMask		= pMemoryBarriers[i].srcAccessMask;
				sync.dstAccessMask		= pMemoryBarriers[i].dstAccessMask;
				sync.uid				= ++_uidCounter;
				sync.type				= ESyncType::MemoryBarrier;
				sync.funcUID			= state.funcUID;
				sync.packetId			= packetId;
				sync.cmdBufferUID		= state.cmdBufferUID;
				sync.renderPassUID		= state.renderPassUID;
				sync.subpassIndex		= sp_index;

				buf.second.push_back( std::move(sync) );
			}
		}
		return true;
	}
	
/*
=================================================
	_ProcessImageBarriers
=================================================
*/
	bool SynchronizationsAnalyzer::_ProcessImageBarriers (VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags,
														  uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers,
														  TraceRange::Bookmark pos, PacketID packetId, CommandBufferState &state) const
	{
		for (uint i = 0; i < imageMemoryBarrierCount; ++i)
		{
			ImageSync				sync;
			sync.dependencyFlags	= dependencyFlags;
			sync.srcStageMask		= srcStageMask;
			sync.dstStageMask		= dstStageMask;
			sync.srcAccessMask		= pImageMemoryBarriers[i].srcAccessMask;
			sync.dstAccessMask		= pImageMemoryBarriers[i].dstAccessMask;
			sync.oldLayout			= pImageMemoryBarriers[i].oldLayout;
			sync.newLayout			= pImageMemoryBarriers[i].newLayout;
			sync.subresourceRange	= pImageMemoryBarriers[i].subresourceRange;

			sync.uid				= ++_uidCounter;
			sync.type				= ESyncType::ResourceBarrier;
			sync.funcUID			= state.funcUID;
			sync.packetId			= packetId;
			sync.cmdBufferUID		= state.cmdBufferUID;
			sync.renderPassUID		= state.renderPassUID;
			sync.subpassIndex		= state.subpassIndices.empty() ? VK_SUBPASS_EXTERNAL : state.subpassIndices.back().first;

			state.syncQueue.imageSync.insert({ ResourceID(pImageMemoryBarriers[i].image), {} }).first->second.push_back( std::move(sync) );
		}
		return true;
	}
	
/*
=================================================
	_ProcessBufferBarriers
=================================================
*/
	bool SynchronizationsAnalyzer::_ProcessBufferBarriers (VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags,
														   uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers,
														   TraceRange::Bookmark pos, PacketID packetId, CommandBufferState &state) const
	{
		for (uint i = 0; i < bufferMemoryBarrierCount; ++i)
		{
			BufferSync				sync;
			sync.dependencyFlags	= dependencyFlags;
			sync.srcStageMask		= srcStageMask;
			sync.dstStageMask		= dstStageMask;
			sync.srcAccessMask		= pBufferMemoryBarriers[i].srcAccessMask;
			sync.dstAccessMask		= pBufferMemoryBarriers[i].dstAccessMask;
			sync.offset				= pBufferMemoryBarriers[i].offset;
			sync.size				= pBufferMemoryBarriers[i].size;

			sync.uid				= ++_uidCounter;
			sync.type				= ESyncType::ResourceBarrier;
			sync.funcUID			= state.funcUID;
			sync.packetId			= packetId;
			sync.cmdBufferUID		= state.cmdBufferUID;
			sync.renderPassUID		= state.renderPassUID;
			sync.subpassIndex		= state.subpassIndices.empty() ? VK_SUBPASS_EXTERNAL : state.subpassIndices.back().first;
			
			state.syncQueue.bufferSync.insert({ ResourceID(pBufferMemoryBarriers[i].buffer), {} }).first->second.push_back( std::move(sync) );
		}
		return true;
	}

/*
=================================================
	_OnCmdBeginRenderPass
=================================================
*/
	bool SynchronizationsAnalyzer::_OnCmdBeginRenderPass (const TraceRange::Iterator &pos, CommandBufferState &state) const
	{
		auto&	packet = pos.Cast< packet_vkCmdBeginRenderPass >();
		CHECK_ERR( state.id == ResourceID(packet.commandBuffer) );
		CHECK_ERR( state.state == ECmdBufferState::Recording );
		
		state.funcUID		= ++_uidCounter;
		state.renderPassUID	= ++_uidCounter;
		state.renderpassId	= ResourceID(packet.pRenderPassBegin->renderPass);
		state.framebufferId	= ResourceID(packet.pRenderPassBegin->framebuffer);
		state.subpassIndices.clear();
		state.subpassIndices.push_back({ 0, pos.GetBookmark() });

		CHECK_ERR( _ProcessSubpass( pos.GetBookmark(), pos->packet_id, state ));
		return true;
	}
	
/*
=================================================
	_ProcessSubpass
=================================================
*/
	bool SynchronizationsAnalyzer::_ProcessSubpass (TraceRange::Bookmark pos, PacketID packetId, CommandBufferState &state) const
	{
		auto*	rp_info	= _renderPassAnalyzer->GetRenderPass( state.renderpassId, pos );
		auto*	fb_info	= _renderPassAnalyzer->GetFramebuffer( state.framebufferId, pos );
		CHECK_ERR( rp_info and fb_info );
		CHECK_ERR( state.subpassIndices.size() > 0 and state.subpassIndices.size() <= rp_info->subpasses.size() );

		const uint	subpass_index = state.subpassIndices.back().first;

		for (auto& dep : rp_info->dependencies)
		{
			if ( (dep.srcSubpass == subpass_index and dep.dstSubpass == VK_SUBPASS_EXTERNAL) or
				 //(dep.srcSubpass == VK_SUBPASS_EXTERNAL and dep.dstSubpass == subpass_index) or
				 (dep.dstSubpass == subpass_index) )
			{
				CHECK_ERR( _ProcessSubpassDeps( *rp_info, dep, fb_info->imageViews, pos, packetId, state ));
			}
		}

		return true;
	}
	
/*
=================================================
	_ProcessSubpassDeps
=================================================
*/
	bool SynchronizationsAnalyzer::_ProcessSubpassDeps (const RenderPassAnalyzer::RenderPassInfo &renderpassInfo, const VkSubpassDependency &dependency,
														ArrayView<ResourceID> imageViewIDs, TraceRange::Bookmark pos, PacketID packetId, CommandBufferState &state) const
	{
		auto&	subpass = renderpassInfo.subpasses[ state.subpassIndices.back().first ];
		ASSERT( subpass.pipelineBindPoint == VK_PIPELINE_BIND_POINT_GRAPHICS );

		for (auto& ref : subpass.colorAttachments)
		{
			CHECK_ERR( ref.attachment < imageViewIDs.size() );
			CHECK_ERR( _ProcessImageDeps( imageViewIDs[ref.attachment], ref.layout, VK_ACCESS_COLOR_ATTACHMENT_READ_BIT,
										  ref.attachment, renderpassInfo, dependency, pos, packetId, state ));
		}

		if ( subpass.depthStencilAttachment.has_value() )
		{
			auto&	ref = *subpass.depthStencilAttachment;
			
			CHECK_ERR( ref.attachment < imageViewIDs.size() );
			CHECK_ERR( _ProcessImageDeps( imageViewIDs[ref.attachment], ref.layout, VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT,
										  ref.attachment, renderpassInfo, dependency, pos, packetId, state ));
		}

		for (auto& ref : subpass.inputAttachments)
		{
			CHECK_ERR( ref.attachment < imageViewIDs.size() );
			CHECK_ERR( _ProcessImageDeps( imageViewIDs[ref.attachment], ref.layout, VK_ACCESS_INPUT_ATTACHMENT_READ_BIT,
										  ref.attachment, renderpassInfo, dependency, pos, packetId, state ));
		}

		/*for (auto& index : subpass.preserveAttachments)
		{
			CHECK_ERR( index < imageViewIDs.size() );
			CHECK_ERR( _ProcessImageDeps( imageViewIDs[index], VK_IMAGE_LAYOUT_UNDEFINED, VK_ACCESS_FLAG_BITS_MAX_ENUM,
										  index, renderpassInfo, dependency, pos, packetId, state ));
		}*/

		for (auto& ref : subpass.resolveAttachments)
		{
			CHECK_ERR( ref.attachment < imageViewIDs.size() );
			CHECK_ERR( _ProcessImageDeps( imageViewIDs[ref.attachment], ref.layout, VK_ACCESS_TRANSFER_READ_BIT,
										  ref.attachment, renderpassInfo, dependency, pos, packetId, state ));
		}
		return true;
	}
	
/*
=================================================
	_ProcessImageDeps
=================================================
*/
	bool SynchronizationsAnalyzer::_ProcessImageDeps (ResourceID imageViewId, const VkImageLayout layout, const VkAccessFlagBits, const uint attachmentIndex,
													  const RenderPassAnalyzer::RenderPassInfo &renderpassInfo, const VkSubpassDependency &dependency,
													  TraceRange::Bookmark pos, PacketID packetId, CommandBufferState &state) const
	{
		auto*	view_info = _imageAnalyzer->GetImageView( imageViewId, pos );
		CHECK_ERR( view_info );

		auto&	barriers = state.syncQueue.imageSync.insert({ view_info->image->id, {} }).first->second;

		ImageSync		sync;
		sync.subpassIndex		= state.subpassIndices.back().first;
		sync.dependencyFlags	= dependency.dependencyFlags;
		sync.srcStageMask		= dependency.srcStageMask;
		sync.dstStageMask		= dependency.dstStageMask;
		sync.srcAccessMask		= dependency.srcAccessMask;
		sync.dstAccessMask		= dependency.dstAccessMask;
		sync.newLayout			= layout;
		sync.subresourceRange	= view_info->createInfo.subresourceRange;

		sync.uid				= ++_uidCounter;
		sync.type				= ESyncType::SubpassDependency;
		sync.funcUID			= state.funcUID;
		sync.packetId			= packetId;
		sync.cmdBufferUID		= state.cmdBufferUID;
		sync.renderPassUID		= state.renderPassUID;


		// find oldLayout
		if ( sync.subpassIndex == 0 ) {
			sync.oldLayout = renderpassInfo.attachments[attachmentIndex].initialLayout;
		}
		else
		for (uint i = sync.subpassIndex-1; i < renderpassInfo.subpasses.size(); --i)
		{
			for (auto& ref : renderpassInfo.subpasses[i].colorAttachments) {
				if ( ref.attachment == attachmentIndex )
					sync.oldLayout = ref.layout;
			}
			if ( renderpassInfo.subpasses[i].depthStencilAttachment.has_value() ) {
				auto&	ref = *renderpassInfo.subpasses[i].depthStencilAttachment;
				if ( ref.attachment == attachmentIndex )
					sync.oldLayout = ref.layout;
			}
			for (auto& ref : renderpassInfo.subpasses[i].inputAttachments) {
				if ( ref.attachment == attachmentIndex )
					sync.oldLayout = ref.layout;
			}
			for (auto& ref : renderpassInfo.subpasses[i].resolveAttachments) {
				if ( ref.attachment == attachmentIndex )
					sync.oldLayout = ref.layout;
			}
		}

		// find previous subpass dependency
		if ( dependency.srcSubpass != VK_SUBPASS_EXTERNAL and sync.subpassIndex == dependency.dstSubpass )
		{
			bool	found = false;

			for (auto iter = barriers.rbegin(), end = barriers.rend(); iter != end; ++iter)
			{
				if ( iter->renderPassUID != sync.renderPassUID )
					break;
				
				CHECK( iter->type == ESyncType::SubpassDependency );
				CHECK( iter->subpassIndex == dependency.srcSubpass );
				CHECK( not iter->outputComplete );
				CHECK( not sync.inputComplete );

				iter->output.push_back( sync.uid );
				iter->outputComplete = true;

				sync.input.push_back( iter->uid );
				sync.inputComplete = true;

				found = true;
				break;
			}

			ASSERT( found );
		}

		barriers.push_back( std::move(sync) );
		return true;
	}

/*
=================================================
	_OnCmdNextSubpass
=================================================
*/
	bool SynchronizationsAnalyzer::_OnCmdNextSubpass (const TraceRange::Iterator &pos, CommandBufferState &state) const
	{
		auto&	packet = pos.Cast< packet_vkCmdNextSubpass >();
		CHECK_ERR( state.id == ResourceID(packet.commandBuffer) );
		CHECK_ERR( state.state == ECmdBufferState::Recording );
		
		state.funcUID = ++_uidCounter;
		state.subpassIndices.push_back({ uint(state.subpassIndices.size()), pos.GetBookmark() });

		CHECK_ERR( _ProcessSubpass( pos.GetBookmark(), pos->packet_id, state ));
		return true;
	}
	
/*
=================================================
	_OnCmdEndRenderPass
=================================================
*/
	bool SynchronizationsAnalyzer::_OnCmdEndRenderPass (const TraceRange::Iterator &pos, CommandBufferState &state) const
	{
		auto&	packet = pos.Cast< packet_vkCmdEndRenderPass >();
		CHECK_ERR( state.id == ResourceID(packet.commandBuffer) );
		CHECK_ERR( state.state == ECmdBufferState::Recording );
		
		// TODO ?
		//CHECK_ERR( _ProcessSubpass( pos.GetBookmark(), state ));
		
		state.funcUID		= ++_uidCounter;
		state.renderPassUID	= 0;
		state.framebufferId	= 0;
		state.renderpassId	= 0;
		state.subpassIndices.clear();
		return true;
	}
	
/*
=================================================
	_MergeSyncQueues
=================================================
*/
	void SynchronizationsAnalyzer::_MergeSyncQueues (INOUT SyncQueue &dst, const SyncQueue &src) const
	{
		HashMap<UID,UID>	uid_mapping;

		const auto	AddMapping = [&uid_mapping, this] (UID src)
		{
			auto	inserted = uid_mapping.insert({ src, 0 });
			if ( inserted.second )
				inserted.first->second = ++_uidCounter;
		};
		
		const auto	Remap = [&uid_mapping] (UID src)
		{
			auto	mapped = uid_mapping.find( src );
			return (mapped != uid_mapping.end() ? mapped->second : src);
		};

		
		// pass 1
		for (auto& img : src.imageSync) {
			for (auto& imgbar : img.second) {
				AddMapping( imgbar.uid );
				AddMapping( imgbar.funcUID );
				AddMapping( imgbar.renderPassUID );
				AddMapping( imgbar.cmdBufferUID );
			}
		}
		for (auto& buf : src.bufferSync) {
			for (auto& bufbar : buf.second) {
				AddMapping( bufbar.uid );
				AddMapping( bufbar.funcUID );
				AddMapping( bufbar.renderPassUID );
				AddMapping( bufbar.cmdBufferUID );
			}
		}
		for (auto& glob : src.globalSync) {
			AddMapping( glob.uid );
			AddMapping( glob.funcUID );
			AddMapping( glob.renderPassUID );
			AddMapping( glob.cmdBufferUID );
		}

		// pass 2
		for (auto& img : src.imageSync)
		{
			auto&	barriers = dst.imageSync.insert({ img.first, {} }).first->second;
			barriers.reserve( barriers.size() + img.second.size() );

			for (auto imgbar : img.second)
			{
				imgbar.uid				= Remap( imgbar.uid );
				imgbar.funcUID			= Remap( imgbar.funcUID );
				imgbar.renderPassUID	= Remap( imgbar.renderPassUID );
				imgbar.cmdBufferUID		= Remap( imgbar.cmdBufferUID );

				for (auto& uid : imgbar.input)	{ uid = Remap( uid ); }
				for (auto& uid : imgbar.output)	{ uid = Remap( uid ); }

				barriers.push_back( std::move(imgbar) );
			}
		}

		for (auto& buf : src.bufferSync)
		{
			auto&	barriers = dst.bufferSync.insert({ buf.first, {} }).first->second;
			barriers.reserve( barriers.size() + buf.second.size() );

			for (auto bufbar : buf.second)
			{
				bufbar.uid				= Remap( bufbar.uid );
				bufbar.funcUID			= Remap( bufbar.funcUID );
				bufbar.renderPassUID	= Remap( bufbar.renderPassUID );
				bufbar.cmdBufferUID		= Remap( bufbar.cmdBufferUID );
				
				for (auto& uid : bufbar.input)	{ uid = Remap( uid ); }
				for (auto& uid : bufbar.output)	{ uid = Remap( uid ); }

				barriers.push_back( std::move(bufbar) );
			}
		}

		dst.globalSync.reserve( dst.globalSync.size() + src.globalSync.size() );

		for (auto glob : src.globalSync)
		{
			glob.uid			= Remap( glob.uid );
			glob.funcUID		= Remap( glob.funcUID );
			glob.renderPassUID	= Remap( glob.renderPassUID );
			glob.cmdBufferUID	= Remap( glob.cmdBufferUID );

			for (auto& uid : glob.input)	{ uid = Remap( uid ); }
			for (auto& uid : glob.output)	{ uid = Remap( uid ); }

			dst.globalSync.push_back( std::move(glob) );
		}
	}

/*
=================================================
	_OnCmdExecuteCommands
=================================================
*/
	bool SynchronizationsAnalyzer::_OnCmdExecuteCommands (const TraceRange::Iterator &pos, CommandBufferState &state) const
	{
		auto&	packet = pos.Cast< packet_vkCmdExecuteCommands >();
		
		// skip secondary command buffers
		if ( state.id != ResourceID(packet.commandBuffer) )
			return true;

		for (uint i = 0; i < packet.commandBufferCount; ++i)
		{
			auto	cmdbuf = _cmdBuffers.find( ResourceID(packet.pCommandBuffers[i]) );
			CHECK_ERR( cmdbuf != _cmdBuffers.end() );

			_MergeSyncQueues( INOUT state.syncQueue, cmdbuf->second.syncQueue );
		}
		return true;
	}

/*
=================================================
	_ProcessSemaphore
=================================================
*/
	bool SynchronizationsAnalyzer::_ProcessSemaphore (const TraceRange::Iterator &, ResourceID id, EResOp op)
	{
		if ( op == EResOp::Destruct )
		{
			auto	sem = _semaphores.find( id );
			if ( sem != _semaphores.end() )
			{
				CHECK( sem->second.waiting.empty() );
			}

			_semaphores.erase( id );
			return true;
		}

		return true;
	}
	
/*
=================================================
	_SignalSemaphore
=================================================
*/
	bool SynchronizationsAnalyzer::_SignalSemaphore (TraceRange::Bookmark, ResourceID id, UID uid)
	{
		auto&	info = _semaphores.insert({ id, {} }).first->second;

		for (auto& cb : info.waiting) {
			cb( id, uid );
		}

		info.waiting.clear();
		info.signaledIn	= uid;
		info.isSignaled = true;

		return true;
	}
	
/*
=================================================
	_WaitSemaphore
=================================================
*/
	bool SynchronizationsAnalyzer::_WaitSemaphore (ResourceID id, SemaphoreState::OnSignaled_t &&cb)
	{
		CHECK_ERR( cb );

		auto&	info = _semaphores.insert({ id, {} }).first->second;

		if ( info.isSignaled )
			cb( id, info.signaledIn );
		else
			info.waiting.push_back( std::move(cb) );
	
		return true;
	}
	
/*
=================================================
	_ProcessEvent
=================================================
*/
	bool SynchronizationsAnalyzer::_ProcessEvent (const TraceRange::Iterator &pos, ResourceID, EResOp)
	{
		switch ( pos->packet_id )
		{
			//case VKTRACE_TPI_VK_vkCmdWaitEvents :			break;
			case VKTRACE_TPI_VK_vkSetEvent :				break;
			case VKTRACE_TPI_VK_vkResetEvent :				break;
		}
		return true;
	}
	
/*
=================================================
	_ProcessImage
=================================================
*/
	bool SynchronizationsAnalyzer::_ProcessImage (const TraceRange::Iterator &pos, ResourceID imageId, FrameID frameId, EResOp)
	{
		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkAcquireNextImageKHR :
			{
				auto&	packet		= pos.Cast< packet_vkAcquireNextImageKHR >();
				auto*	swapchain	= _swapchains.FindIn( ResourceID(packet.swapchain), pos );
				CHECK_ERR( swapchain );
				CHECK_ERR( swapchain->bookmarks.back().pos == pos.GetBookmark() );

				auto*	acquire = std::get_if<SwapchainAcquireImage>( &swapchain->bookmarks.back().data );
				CHECK_ERR( acquire and acquire->image == 0 );

				acquire->image = imageId;
				break;
			}

			case VKTRACE_TPI_VK_vkAcquireNextImage2KHR :
			{
				auto&	packet		= pos.Cast< packet_vkAcquireNextImage2KHR >();
				auto*	swapchain	= _swapchains.FindIn( ResourceID(packet.pAcquireInfo->swapchain), pos );
				CHECK_ERR( swapchain );
				CHECK_ERR( swapchain->bookmarks.back().pos == pos.GetBookmark() );

				auto*	acquire = std::get_if<SwapchainAcquireImage>( &swapchain->bookmarks.back().data );
				CHECK_ERR( acquire and acquire->image == 0 );

				acquire->image = imageId;
				break;
			}

			case VKTRACE_TPI_VK_vkQueuePresentKHR :
				break;		// TODO
		}
		return true;
	}

/*
=================================================
	_FindSignaledFence
=================================================
*/
	bool SynchronizationsAnalyzer::_FindSignaledFence (DeviceInfo_t &dev, ResourceID fenceId, UID currUID, OUT UID &uid) const
	{
		uid = 0;

		for (auto iter = dev.bookmarks.rbegin(), end = dev.bookmarks.rend(); iter != end; ++iter)
		{
			uint	status = 0;	// 1 - found, 2 - error, 3 - exit

			Visit( iter->data,
				[fenceId, &status] (const HostWaitForFences &cmd) {
					for (auto& id : cmd.fences) {
						if ( id == fenceId ) {
							status = 1;
							break;
						}
					}
				},
				[fenceId, &status] (const HostResetFences &cmd) {
					for (auto& id : cmd.fences) {
						if ( id == fenceId ) {
							ASSERT(false);	// fence was reseted
							status = 2;
							break;
						}
					}
				},
				[fenceId, &status] (const HostAcquireNextImage &cmd) {
					if ( fenceId == cmd.fence )
						status = 1;
				},
				[fenceId, &status] (const HostWaitForDeviceIdle &) {
					ASSERT(false);	// global sync found, all enqueed fences was signaled before
					status = 1;
				},
				[fenceId, &status, &uid] (const HostQueueSubmit &cmd) {
					if ( fenceId == cmd.fence ) {
						status	= 3;
						uid		= cmd.fenceUID;
					}
				},
				[] (const HostWaitForQueueIdle &)	{},
				[] (std::nullptr_t)					{},
				[] (const auto&)					{ ASSERT(false); }
			);

			switch ( status ) {
				case 0 :
					break;	// continue searching

				case 1 :
					iter->output.push_back( currUID );
					uid = iter->uid;
					return true;

				case 2 :
					RETURN_ERR( "something goes wrong" );

				case 3 :
					ASSERT( uid != 0 );
					return true;
			}
		}

		RETURN_ERR( "fence is not found!" );
	}
//-----------------------------------------------------------------------------


	using UID			= SynchronizationsAnalyzer::UID;
	using ESyncType		= SynchronizationsAnalyzer::ESyncType;
	using ImageSync		= SynchronizationsAnalyzer::ImageSync;
	using BufferSync	= SynchronizationsAnalyzer::BufferSync;
	
/*
=================================================
	IsExplicitResourceMemoryBarrier
=================================================
*/
	template <typename T>
	ND_ inline bool IsExplicitResourceMemoryBarrier (const T &barrier)
	{
		return	barrier.type == SynchronizationsAnalyzer::ESyncType::SubpassDependency or
				barrier.type == SynchronizationsAnalyzer::ESyncType::ResourceBarrier;
	}

/*
=================================================
	BuildImageDependencies
=================================================
*/
	struct ImageDependencies
	{
		HashMap< ResourceID, ImageSync* >	states;
	};

	static void BuildImageDependencies (SynchronizationsAnalyzer::ImageBarriers_t::value_type &img, UID finalUID, INOUT ImageDependencies &deps)
	{
		auto	curr = deps.states.find( img.first );

		for	(auto iter = img.second.rbegin(), end = img.second.rend(); iter != end; ++iter)
		{
			// skip execution and global memory barriers if image not used after that
			/*if ( curr == deps.states.end() and
				 not IsExplicitResourceMemoryBarrier( *iter ) )
				continue;*/
			
			if ( curr == deps.states.end() )
			{
				curr = deps.states.insert({ img.first, iter.operator->() }).first;
				curr->second->output.push_back( finalUID );
			}
			else
			if ( not IsExplicitResourceMemoryBarrier( *iter ) and
				 not IsExplicitResourceMemoryBarrier( *curr->second ) )
			{
				CHECK( deps.states.erase( img.first ) == 1 );
				curr = deps.states.end();
			}
			else
			{
				iter->output.push_back( curr->second->uid );
				curr->second->input.push_back( iter->uid );

				curr->second = iter.operator->();
			}
		}
	}
	
/*
=================================================
	BuildBufferDependencies
=================================================
*/
	struct BufferDependencies
	{
		HashMap< ResourceID, BufferSync* >	states;
	};

	static void BuildBufferDependencies (SynchronizationsAnalyzer::BufferBarriers_t::value_type &buf, UID finalUID, INOUT BufferDependencies &deps)
	{
		auto	curr = deps.states.find( buf.first );

		for	(auto iter = buf.second.rbegin(), end = buf.second.rend(); iter != end; ++iter)
		{
			// skip execution and global memory barriers if image not used after that
			/*if ( curr == deps.states.end() and
				 iter->type != ESyncType::SubpassDependency and
				 iter->type != ESyncType::ResourceBarrier )
				continue;*/
			
			if ( curr == deps.states.end() )
			{
				curr = deps.states.insert({ buf.first, iter.operator->() }).first;
				curr->second->output.push_back( finalUID );
			}
			else
			if ( not IsExplicitResourceMemoryBarrier( *iter ) and
				 not IsExplicitResourceMemoryBarrier( *curr->second ) )
			{
				CHECK( deps.states.erase( buf.first ) == 1 );
				curr = deps.states.end();
			}
			else
			{
				iter->output.push_back( curr->second->uid );
				curr->second->input.push_back( iter->uid );

				curr->second = iter.operator->();
			}
		}
	}
	
/*
=================================================
	BuildGlobalDependencies
=================================================
*/
	struct GlobalDependencies
	{
		SynchronizationsAnalyzer::SyncItem*	last = null;
	};

	static void BuildGlobalDependencies (Array<SynchronizationsAnalyzer::SyncItem> &syncs, UID finalUID, INOUT GlobalDependencies &deps)
	{
		for (auto iter = syncs.rbegin(), end = syncs.rend(); iter != end; ++iter)
		{
			if ( deps.last == null ) {
				iter->output.push_back( finalUID );
			}else{
				deps.last->input.push_back( iter->uid );
				iter->output.push_back( deps.last->uid );
			}
			
			deps.last = iter.operator->();
		}
	}

/*
=================================================
	_BuildCommandDependencies
=================================================
*/
	bool SynchronizationsAnalyzer::_BuildCommandDependencies (UID finalUID, QueueInfo_t &queue) const
	{
		struct Dependencies {
			ImageDependencies	images;
			BufferDependencies	buffers;
			GlobalDependencies	global;
		};
		Dependencies	deps;

		for (auto bm_iter = queue.bookmarks.rbegin(), bm_end = queue.bookmarks.rend(); bm_iter != bm_end; ++bm_iter)
		{
			bool	finished = false;

			Visit( bm_iter->data,
				[&bm_iter, &deps, finalUID] (QueueExecutionStart &cmd)
				{
					for (auto q_iter = cmd.syncQueues.rbegin(), q_end = cmd.syncQueues.rend(); q_iter != q_end; ++q_iter)
					{
						for (auto& img : q_iter->imageSync) {
							BuildImageDependencies( img, finalUID, INOUT deps.images );
						}
						for (auto& buf : q_iter->bufferSync) {
							BuildBufferDependencies( buf, finalUID, INOUT deps.buffers );
						}
						BuildGlobalDependencies( q_iter->globalSync, finalUID, INOUT deps.global );
					}
					
					// add dependency on semaphores
					if ( not cmd.waitSemaphores.empty() )
					{
						for (auto& img : deps.images.states) {
							img.second->input.push_back( bm_iter->uid );
						}
						for (auto& buf : deps.buffers.states) {
							buf.second->input.push_back( bm_iter->uid );
						}
						if ( deps.global.last ) {
							deps.global.last->input.push_back( bm_iter->uid );
						}
						deps = {};
					}
				},

				[&bm_iter, &finished] (const QueueExecutionFinish &cmd)
				{
					// signal semaphores are global barrier for all stages and memory accesses
					if ( not cmd.signalSemaphores.empty() )
						finished = true;
				},

				[&finished] (const QueueWaitIdle &)		{ finished = true; },
				[&finished] (const QueueFenceSignal &)	{ finished = true; },
				[]			(std::nullptr_t)			{},
				[]			(const auto &)				{ ASSERT(false); }
			);

			// add dependency on last command
			if ( finished )
			{
				for (auto& img : deps.images.states) {
					img.second->input.push_back( bm_iter->uid );
				}
				for (auto& buf : deps.buffers.states) {
					buf.second->input.push_back( bm_iter->uid );
				}
				if ( deps.global.last ) {
					deps.global.last->input.push_back( bm_iter->uid );
				}
				break;
			}
		}
		return true;
	}
	
/*
=================================================
	_BuildQueueWaitDependencies
=================================================
*/
	bool SynchronizationsAnalyzer::_BuildQueueWaitDependencies (UID finalUID, QueueInfo_t &queue) const
	{
		auto&	last = queue.bookmarks.back();
		ASSERT( last.uid == finalUID );

		for (auto bm_iter = queue.bookmarks.rbegin(), bm_end = queue.bookmarks.rend(); bm_iter != bm_end; ++bm_iter)
		{
			bool	finished = false;

			Visit( bm_iter->data,
				[&bm_iter, &finished, &last] (const QueueExecutionFinish &) {
					finished = true;
					bm_iter->output.push_back( last.uid );
					last.input.push_back( bm_iter->uid );
				},
				[&bm_iter, &finished, &last] (const QueueFenceSignal &) {
					finished = true;
					bm_iter->output.push_back( last.uid );
					last.input.push_back( bm_iter->uid );
				},
				[&finished] (const QueueWaitIdle &) {
					finished = true;
				},
				[] (const QueueExecutionStart &)	{},
				[] (std::nullptr_t)					{},
				[] (const auto &)					{ ASSERT(false); }
			);

			if ( finished )
				break;
		}
		return true;
	}


}	// VTC
