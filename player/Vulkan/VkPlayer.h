// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Core/IPlayer.h"
#include "Reader/TraceReader.h"
#include "stl/Memory/LinearAllocator.h"
#include <chrono>

#undef NOMINMAX
#define VMA_RECORDING_ENABLED		0
#define VMA_DEDICATED_ALLOCATION	1
#include "external/VulkanMemoryAllocator/src/vk_mem_alloc.h"

namespace VTPlayer
{
#	include "IDs/EVulkanPacketIDs.h"

	struct VUnpacker;


	//
	// Vulkan Trace Player
	//

	class VkPlayer_v100 final : public IPlayer, public IWindowEventListener, public VulkanDeviceFn
	{
	// types
	public:
		using DataID			= uint;
		using FrameID			= uint;
		using ResourceID		= uint64_t;
		using ResourceMap_t		= StaticArray< Array<ResourceID>, VkResourceTypes::Count >;


	private:
		using Nonoseconds		= std::chrono::nanoseconds;
		using TimePoint_t		= std::chrono::time_point< std::chrono::high_resolution_clock >;

		struct MemAllocationInfo
		{
			VmaAllocation		alloc		= null;
			bool				isCoherent	= false;
		};
		
		using ImageAllocations_t	= Array< MemAllocationInfo >;
		using BufferAllocations_t	= Array< MemAllocationInfo >;
		

		struct MemRange
		{
			void *				mappedPtr	= null;
			VkDeviceSize		offset		= 0;
			VkDeviceSize		size		= 0;
		};
		using MappedMemory_t	= HashMap< ResourceID, MemRange >;
		

		struct FilePart
		{
			DataID				id				= UMax;
			uint64_t			offset			= 0;
			uint64_t			size			= 0;
			FrameID				firstFrame		= FrameID(0);	// frame when data will be requested at first time
			FrameID				lastFrame		= FrameID(0);	// frame when data can be unloaded
		};

		using DataBuffer_t		= Array<uint8_t>;
		using DataMap_t			= HashMap< DataID, DataBuffer_t >;
		using LoadEvents_t		= HashMap< FrameID, Array<FilePart> >;
		using UnloadEvents_t	= HashMap< FrameID, Array<DataID> >;


		struct SwapchainImage
		{
			size_t				id				= 0;
			VkImage				image			= VK_NULL_HANDLE;
			VkCommandBuffer		cmdbuf			= VK_NULL_HANDLE;
			VkCommandPool		cmdpool			= VK_NULL_HANDLE;	// temporary
		};
		using SwapchainImages_t	= FixedArray< SwapchainImage, 8 >;


		struct FrameQueries
		{
			Array<VkSemaphore>		waitSemaphores;					// this semaphores will signal when each submited command buffer complete execution
			Array<VkSemaphore>		signalSemaphores;
			VkCommandBuffer			beforeFrame			= VK_NULL_HANDLE;
			VkCommandBuffer			afterFrame			= VK_NULL_HANDLE;
			uint					counter				= 0;
			bool					isStarted			= false;	// set 'true' when 'afterFrame' command submited
			static constexpr uint	InitialCounter		= 2;		// 0,1 indices used in 'beforeFrame' and 'afterFrame'
		};
		using FrameQueries_t	= FixedArray< FrameQueries, 4 >;

		struct QueryPool
		{
			VkQueryPool			queryPool		= VK_NULL_HANDLE;
			VkQueue				queue			= VK_NULL_HANDLE;	// queue where query commands will be submited
			VkCommandPool		cmdPool			= VK_NULL_HANDLE;	// ...
			FrameQueries_t		perFrame;
			uint				frameIndex		= 0;
			uint				queryCount		= 0;				// the total count is queryCount * frames
			bool				supportsPresent	= false;
		};
		using QueryPools_t		= Array< QueryPool >;


		struct PendingQueueSubmit
		{
			VkQueue									target;
			FixedArray< VkCommandBuffer, 8 >		commandBuffers;
			FixedArray< VkSemaphore, 8 >			waitSemaphores;
			FixedArray< VkPipelineStageFlags, 8 >	waitDstStageMask;
			FixedArray< VkSemaphore, 8 >			signalSemaphores;
		};
		using PengingQueueSubmits_t	= Array< PendingQueueSubmit >;



	// variables
	private:
		TraceReader				_trace;
		SharedPtr<RStream>		_dataFile;

		VulkanDeviceExt			_vulkan;
		VulkanSwapchainPtr		_swapchain;
		size_t					_swapchainId		= 0;
		IWindow *				_window				= null;

		FrameID					_currFrameId		= 0;
		bool					_isPaused			= false;
		bool					_playOneFrame		= false;
		bool					_isFinished			= false;
		bool					_playWithSourceFPS	= true;
		TimePoint_t				_lastPresentTime;
		
		ResourceMap_t			_vkResources;
		VmaAllocator			_memAllocator		= null;

		// for memory remapping
		ImageAllocations_t		_imageAlloc;
		BufferAllocations_t		_bufferAlloc;
		
		// origin memory model
		MappedMemory_t			_mappedMemory;
		
		// for indirect swapchain
		struct {
			SwapchainImages_t		images;
			VkDeviceMemory			memory			= VK_NULL_HANDLE;
			VkSemaphore				renderFinished	= VK_NULL_HANDLE;
			uint					imageIndex		= 0;
			uint2					dimension;
		}						_indirectSwapchain;

		// profiling
		struct {
			QueryPools_t			queries;
			FrameID					frameId				= 0;
			uint					frameCounter		= 0;
			uint					averageFPS			= 0;	// measure in cpu-side
			Nonoseconds				averageFTime;				// measure in gpu-side
			Nonoseconds				accumFTime;
			TimePoint_t				lastUpdateTime;
		}						_profiling;

		// ...
		Array<VkCommandPool>	_commandPools;
		PengingQueueSubmits_t	_pendingSubmits;		// will be inserted in nearest vkQueueSubmit call
		Array<VkSemaphore>		_semaphorePool;			// currently unused semaphores

		LinearAllocator<>		_perPacketAllocator;	// allocate memory when process packet and recycle before processing next packet

		DataMap_t				_loadableData;
		LoadEvents_t			_loadEvents;
		UnloadEvents_t			_unloadEvents;
		
		VulkanSettings const&	_vulkanSettings;
		WindowSettings const&	_windowSettings;
		PlayerSettings const&	_playerSettings;

		uint					_implementationFlags	= 0;


	// methods
	public:
		VkPlayer_v100 (const VulkanSettings &, const WindowSettings &, const PlayerSettings &,
					   const SharedPtr<RStream> &, const SharedPtr<RStream> &);
		~VkPlayer_v100 () override;


	// IPlayer implementation
	public:
		bool Play () override;
		bool Pause () override;
		bool Init (IWindow *) override;
		bool Draw () override;

	// IWindowEventListener implementation
	public:
		void OnResize (const uint2 &size) override;
		void OnRefresh () override {}
		void OnDestroy () override;
		void OnUpdate () override {}
		void OnKey (StringView, EKeyAction) override;
		void OnMouseMove (const float2 &) override {}


	private:
		void _Destroy ();

		bool _RunCommand ();
		bool _RunCommand2 (EVulkanPacketID, VUnpacker &);
		bool _CreateAllocator (VkDeviceSize pageSize);
		bool _CreateDevice (const struct VulkanCreateInfo &);
		bool _CreateCommandPools ();

		bool _CreateQueryPools ();
		void _DestroyQueryPools ();
		bool _BuildQueryCommandBuffers ();
		bool _UpdateFrameStatistic (size_t queueId);
		bool _InsertQueryOnAcquireImage (INOUT VkSemaphore &);
		bool _InsertQueryOnPresent (OUT VkSubmitInfo &submit, size_t queueId);
		
		bool _CreateSwapchain (struct VulkanCreateInfo &);
		bool _InitDirectSwapchain (const struct VulkanCreateInfo &);
		bool _InitIndirectSwapchain (const struct VulkanCreateInfo &);
		void _DestroyIndirectSwapchain ();
		bool _AcquireIndirectSwapchainImage (size_t imageId);
		bool _QueuePresentToIndirectSwapchain (size_t queueId, VkQueue queue, VkImage image, ArrayView<VkSemaphore> waitSemaphores);
		bool _QueuePresentToDirectSwapchain (size_t queueId, VkQueue queue, VkImage image, ArrayView<VkSemaphore> waitSemaphores);

		bool _CreateSemaphores ();
		void _DestroySemaphores ();

		bool _PrepareData (FrameID frameId);
		bool _LoadDataPart (FilePart &part);

		bool _LoadDataToVMAMemory (VkDevice dev, MemAllocationInfo &mem, DataID dataId, VkDeviceSize offset, VkDeviceSize size) const;

		ND_ ArrayView<uint8_t>  _LoadData (DataID id) const;

		ND_ bool  _IsOriginMemoryModel () const;
		ND_ bool  _IsQueueFamilyRemappingEnabled () const;
		ND_ bool  _IsIndirectSwapchainEnabled () const;
		ND_ bool  _IsProfilingEnabled () const;

		ND_ bool  _OverridePacketProcessor (EVulkanPacketID, VUnpacker &);

		bool _SetData (VUnpacker &);
		bool _CreateDevice (VUnpacker &);
		bool _Initializeresource (VUnpacker &);

		bool _MapMemory (VUnpacker &);
		bool _UnmapMemory (VUnpacker &);
		bool _LoadDataToMappedMemory (VUnpacker &);

		bool _AllocateBufferMemory (VUnpacker &);
		bool _AllocateImageMemory (VUnpacker &);
		bool _FreeBufferMemory (VUnpacker &);
		bool _FreeImageMemory (VUnpacker &);
		bool _LoadDataToBuffer (VUnpacker &);
		bool _LoadDataToImage (VUnpacker &);

		bool _AcquireNextImage (VUnpacker &);
		bool _QueuePresent (VUnpacker &);

		bool _CreateShaderModule (VUnpacker &);
		bool _CreatePipelineCache (VUnpacker &);
		bool _CmdUpdateBuffer (VUnpacker &);
		bool _CmdPushDescriptorSetWithTemplate (VUnpacker &);
		bool _UpdateDescriptorSetWithTemplate (VUnpacker &);

		bool _ImageCapture (VUnpacker &);
		bool _BufferCapture (VUnpacker &);

		bool _QueueSubmit (VUnpacker &);
	};


}	// VTPlayer
