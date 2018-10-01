// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Analyzer/IAnalyzer.h"
#include "Analyzer/ResourceTracker.h"
#include "Analyzer/Default/RenderPassAnalyzer.h"
#include "stl/Containers/Union.h"

namespace VTC
{

	//
	// Synchronizations Analyzer
	//

	class SynchronizationsAnalyzer final : public IAnalyzer
	{
	// types
	public:
		using UID	= uint64_t;

		enum class EConnectionFlags {
			None		= 0,
			Signal		= 1 << 0,
			Wait		= 1 << 1,
			HostWait	= 1 << 2,
			Execution	= 1 << 3,	// indicates execution order dependency
			Barrier		= 1 << 4,
			Strong		= 1 << 5,
		};

		struct Dependency {
			UID					uid		= 0;
			EConnectionFlags	flags	= EConnectionFlags::None;
		};

		using Dependencies_t	= Array< Dependency >;
		
		enum class ESyncType {
			Unknown,
			SubpassDependency,
			ResourceBarrier,
			MemoryBarrier,
			ExecutionBarrier,
			Semaphore,
		};

		struct ResourceSync
		{
			UID						uid					= 0;
			ESyncType				type				= ESyncType::Unknown;
			bool					inputComplete		= false;	// 'true' means that 'input' contains all needed dependencies
			bool					outputComplete		= false;	// 'true' means that 'output' contains all needed dependencies
			PacketID				packetId			= 0;
			UID						funcUID				= 0;
			UID						cmdBufferUID		= 0;
			UID						renderPassUID		= 0;
			uint					subpassIndex		= VK_SUBPASS_EXTERNAL;
			Dependencies_t			input;
			Dependencies_t			output;
			Array<ResourceID>		events;
			VkDependencyFlags		dependencyFlags		= 0;
			VkPipelineStageFlags	srcStageMask		= 0;
			VkPipelineStageFlags	dstStageMask		= 0;
			VkAccessFlags			srcAccessMask		= 0;
			VkAccessFlags			dstAccessMask		= 0;
		};

		struct BufferSync : ResourceSync
		{
			VkDeviceSize			offset				= 0;
			VkDeviceSize			size				= 0;

			BufferSync () {}
		};

		struct ImageSync : ResourceSync
		{
			VkImageLayout			oldLayout			= VK_IMAGE_LAYOUT_UNDEFINED;
			VkImageLayout			newLayout			= VK_IMAGE_LAYOUT_UNDEFINED;
			VkImageSubresourceRange	subresourceRange	= {};

			ImageSync () {}
		};

		using ImageBarriers_t		= HashMap< ResourceID, Array<ImageSync> >;
		using BufferBarriers_t		= HashMap< ResourceID, Array<BufferSync> >;
		//-------------------------------------------------------------------------------------


		struct MemorySync
		{
			Array<ResourceID>		events;
			VkDependencyFlags		dependencyFlags		= 0;
			VkPipelineStageFlags	srcStageMask		= 0;
			VkPipelineStageFlags	dstStageMask		= 0;
			VkAccessFlags			srcAccessMask		= 0;
			VkAccessFlags			dstAccessMask		= 0;

			MemorySync () {}
		};

		struct ExecutionSync
		{
			Array<ResourceID>		events;
			VkDependencyFlags		dependencyFlags		= 0;
			VkPipelineStageFlags	srcStageMask		= 0;
			VkPipelineStageFlags	dstStageMask		= 0;

			ExecutionSync () {}
		};

		using SyncUnion_t	= Union< std::nullptr_t, MemorySync, ExecutionSync >;
		//-------------------------------------------------------------------------------------


		struct SyncItem
		{
			UID						uid					= 0;
			bool					inputComplete		= false;	// 'true' means that 'input' contains all needed dependencies
			bool					outputComplete		= false;	// 'true' means that 'output' contains all needed dependencies
			PacketID				packetId			= 0;
			UID						funcUID				= 0;
			UID						cmdBufferUID		= 0;
			UID						renderPassUID		= 0;
			Dependencies_t			input;
			Dependencies_t			output;
			SyncUnion_t				data;
		};

		struct SyncQueue
		{
			Array< SyncItem >		globalSync;
			ImageBarriers_t			imageSync;
			BufferBarriers_t		bufferSync;
		};

		using SubpassIndices_t	= Array<Pair< uint, TraceRange::Bookmark >>;

		enum class ECmdBufferState
		{
			Initial,
			Recording,
			Recorded,
		};

		struct CommandBufferState
		{
			ResourceID					id				= 0;
			ECmdBufferState				state			= ECmdBufferState::Initial;

			VkCommandBufferUsageFlags	flags			= 0;
			ResourceID					renderpassId	= 0;
			ResourceID					framebufferId	= 0;
			SubpassIndices_t			subpassIndices;
			UID							funcUID			= 0;
			UID							cmdBufferUID	= 0;
			UID							renderPassUID	= 0;

			SyncQueue					syncQueue;
		};

		using CmdBufferStates_t	= HashMap< ResourceID, CommandBufferState >;
		using WaitSemaphores_t	= Array<Pair< ResourceID, VkPipelineStageFlags >>;
		using CmdProcessor_t	= std::function< void (SyncQueue &) >;
		using SyncQueesRIter_t	= Array<SyncQueue>::reverse_iterator;
		//-------------------------------------------------------------------------------------


		struct QueueExecutionStart {
			Array<SyncQueue>			syncQueues;
			WaitSemaphores_t			waitSemaphores;
		};

		struct QueueExecutionFinish {
			Array<ResourceID>			signalSemaphores;
		};

		struct QueueFenceSignal {
			ResourceID					fence		= 0;
		};

		struct QueueWaitIdle
		{};

		using QueueUnion_t	= Union< std::nullptr_t, QueueExecutionStart, QueueExecutionFinish, QueueFenceSignal, QueueWaitIdle >;

		struct QueueInfo
		{
			ResourceID					id			= 0;
			ResourceID					deviceId	= 0;
		};

		struct QueueBookmark
		{
			UID							uid			= 0;
			FrameID						frameId		= ~FrameID(0);
			Dependencies_t				input;
			Dependencies_t				output;
			QueueUnion_t				data;

			bool operator == (const QueueBookmark &) const { return false; }	// never unite bookmarks
		};

		using Queues_t			= ResourceTracker< QueueInfo, QueueBookmark, true >;
		using QueueInfo_t		= Queues_t::Item_t;
		using QueueBookmark_t	= Queues_t::Bookmark_t;
		using QueueBM_RIter_t	= decltype(QueueInfo_t::bookmarks)::reverse_iterator;
		//-------------------------------------------------------------------------------------
		

		struct SwapchainAcquireImage {
			bool						hasSemaphore = false;
			ResourceID					image		= 0;
		};

		struct SwapchainPresent {
			Array<ResourceID>			waitSemaphores;
			ResourceID					image		= 0;
		};

		using SwapchainUnion_t	= Union< std::nullptr_t, SwapchainAcquireImage, SwapchainPresent >;

		struct SwapchainInfo
		{
			ResourceID					id			= 0;
			ResourceID					deviceId	= 0;
		};

		struct SwapchainBookmark
		{
			UID							uid			= 0;
			FrameID						frameId		= ~FrameID(0);
			Dependencies_t				input;
			Dependencies_t				output;
			SwapchainUnion_t			data;

			bool operator == (const SwapchainBookmark &) const { return false; }	// never unite bookmarks
		};

		using Swapchains_t			= ResourceTracker< SwapchainInfo, SwapchainBookmark, true >;
		using SwapchainInfo_t		= Swapchains_t::Item_t;
		//-------------------------------------------------------------------------------------


		struct HostWaitForFences {
			Array<ResourceID>			fences;
			bool						waitAll		= false;
		};

		struct HostResetFences {
			Array<ResourceID>			fences;
		};

		struct HostQueueSubmit {
			ResourceID					queueId		= 0;
			ResourceID					fence		= 0;
			UID							fenceUID	= 0;
		};

		struct HostAcquireNextImage {
			ResourceID					fence		= 0;
		};

		struct HostWaitForQueueIdle {
			ResourceID					queue		= 0;
		};

		struct HostWaitForDeviceIdle
		{};

		using HasSyncUnion_t	= Union< std::nullptr_t, HostWaitForFences, HostResetFences, HostQueueSubmit, HostAcquireNextImage,
										 HostWaitForQueueIdle, HostWaitForDeviceIdle >;

		struct DeviceInfo
		{
			ResourceID					id			= 0;
		};

		struct HostSyncBookmark
		{
			UID							uid			= 0;
			FrameID						frameId		= ~FrameID(0);
			ThreadID					threadId	= 0;
			Dependencies_t				input;
			Dependencies_t				output;
			HasSyncUnion_t				data;

			bool operator == (const HostSyncBookmark &) const { return false; }	// never unite bookmarks
		};

		using Devices_t		= ResourceTracker< DeviceInfo, HostSyncBookmark, true >;
		using DeviceInfo_t	= Devices_t::Item_t;
		//-------------------------------------------------------------------------------------
		

		struct SemaphoreState
		{
			using OnSignaled_t = std::function< void (ResourceID, UID) >;

			Array<OnSignaled_t>		waiting;
			UID						signaledIn	= 0;
			bool					isSignaled	= false;
		};
		
		using SemaphoreStates_t		= HashMap< ResourceID, SemaphoreState >;
		//-------------------------------------------------------------------------------------


	// variables
	private:
		CmdBufferStates_t				_cmdBuffers;
		Queues_t						_queues;
		Swapchains_t					_swapchains;
		Devices_t						_devices;
		SemaphoreStates_t				_semaphores;
		mutable UID						_uidCounter				= 0;

		FrameID							_firstFrame				= 0;
		FrameID							_lastFrame				= ~FrameID(0);

		class RenderPassAnalyzer const*	_renderPassAnalyzer		= null;
		class ImageAnalyzer const*		_imageAnalyzer			= null;

		static constexpr uint			_frameCmpBias			= 2;


	// methods
	public:
		SynchronizationsAnalyzer ();
		SynchronizationsAnalyzer (FrameID first, FrameID last);

		void SetRange (FrameID first, FrameID last);

		ND_ Queues_t const&		GetQueues ()		const		{ return _queues; }
		ND_ Swapchains_t const&	GetSwapchains ()	const		{ return _swapchains; }
		ND_ Devices_t const&	GetDevices ()		const		{ return _devices; }


	// IAnalyzer implementation
	public:
		void PreProcess (const class AppTrace &) override;
		void Process (const TraceRange::Iterator &) override {}
		void PostProcess () override {}
		void AddResourceUsage (const TraceRange::Iterator &, EResourceType, ResourceID, FrameID, EResOp) override;

		std::type_index		GetType ()	const override		{ return typeid(*this); }
		String				Report ()	const override		{ return "TODO"; }


	private:
		bool _ProcessDevice (const TraceRange::Iterator &, ResourceID, FrameID, EResOp);
		bool _ProcessQueue (const TraceRange::Iterator &, ResourceID, FrameID, EResOp);
		bool _ProcessSwapchain (const TraceRange::Iterator &, ResourceID, FrameID, EResOp);
		bool _ProcessCommandBuffer (const TraceRange::Iterator &, ResourceID, EResOp);
		bool _ProcessSemaphore (const TraceRange::Iterator &, ResourceID, EResOp);
		bool _ProcessEvent (const TraceRange::Iterator &, ResourceID, EResOp);
		bool _ProcessImage (const TraceRange::Iterator &, ResourceID, FrameID, EResOp);
		
		bool _OnDeviceWaitIdle (const TraceRange::Iterator &, ResourceID, FrameID);
		bool _OnWaitForFences (const TraceRange::Iterator &, ResourceID, FrameID);
		bool _OnResetFences (const TraceRange::Iterator &, ResourceID, FrameID);

		bool _OnAcquireNextImage (const TraceRange::Iterator &, ResourceID, FrameID);
		bool _OnAcquireNextImage2 (const TraceRange::Iterator &, ResourceID, FrameID);
		bool _OnQueuePresent (const TraceRange::Iterator &, ResourceID, FrameID);

		bool _OnQueueSubmit (const TraceRange::Iterator &, ResourceID, FrameID);
		bool _OnQueueWaitIdle (const TraceRange::Iterator &, ResourceID, FrameID);
		bool _OnQueueBindSparse (const TraceRange::Iterator &, ResourceID, FrameID);
		bool _SubmitCommands (const VkSubmitInfo &, const TraceRange::Iterator &, ResourceID, FrameID, UID, UID, UID);
		bool _BuildCommandDependencies (UID, QueueInfo_t &) const;
		bool _BuildQueueWaitDependencies (UID, QueueInfo_t &) const;

		bool _OnCmdWaitEvents (const TraceRange::Iterator &, CommandBufferState &) const;
		bool _OnCmdSetEvent (const TraceRange::Iterator &, CommandBufferState &)  const;
		bool _OnCmdResetEvent (const TraceRange::Iterator &, CommandBufferState &) const;
		bool _OnCmdPipelineBarrier (const TraceRange::Iterator &, CommandBufferState &) const;
		bool _OnCmdBeginRenderPass (const TraceRange::Iterator &, CommandBufferState &) const;
		bool _OnCmdNextSubpass (const TraceRange::Iterator &, CommandBufferState &) const;
		bool _OnCmdEndRenderPass (const TraceRange::Iterator &, CommandBufferState &) const;
		bool _OnCmdExecuteCommands (const TraceRange::Iterator &, CommandBufferState &) const;
		void _MergeSyncQueues (INOUT SyncQueue &dst, const SyncQueue &src) const;

		bool _ProcessExecutionBarrier (VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags,
									   PacketID packetId, CommandBufferState &state) const;

		bool _ProcessMemoryBarriers (VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags,
									 uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers,
									 PacketID packetId, CommandBufferState &state) const;

		bool _ProcessImageBarriers (VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags,
									uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers,
									PacketID packetId, CommandBufferState &state) const;

		bool _ProcessBufferBarriers (VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags,
									 uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers,
									 PacketID packetId, CommandBufferState &state) const;

		bool _ProcessSubpass (TraceRange::Bookmark pos, PacketID packetId, CommandBufferState &state) const;

		bool _ProcessSubpassDeps (const RenderPassAnalyzer::RenderPassInfo &renderpassInfo, const VkSubpassDependency &dependency,
								  ArrayView<ResourceID> imageViewIDs, TraceRange::Bookmark pos, PacketID packetId, CommandBufferState &state) const;

		bool _ProcessImageDeps (ResourceID imageViewId, VkImageLayout layout, VkAccessFlagBits access, uint attachmentIndex,
								const RenderPassAnalyzer::RenderPassInfo &renderpassInfo, const VkSubpassDependency &dependency,
								TraceRange::Bookmark pos, PacketID packetId, CommandBufferState &state) const;

		bool _SignalSemaphore (TraceRange::Bookmark, ResourceID, UID);
		bool _WaitSemaphore (ResourceID, SemaphoreState::OnSignaled_t &&);

		bool _FindSignaledFence (DeviceInfo_t &, ResourceID, FrameID, UID, OUT UID &);

		bool _ReleaseUnusedQueueData (ResourceID queueId, FrameID frameId);
	};


	FG_BIT_OPERATORS( SynchronizationsAnalyzer::EConnectionFlags );

}	// VTC
