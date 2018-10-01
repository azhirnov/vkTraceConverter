// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Core/IPlayer.h"
#include "Reader/TraceReader.h"

#undef NOMINMAX
#define VMA_RECORDING_ENABLED		0
#define VMA_DEDICATED_ALLOCATION	1
#include "external/VulkanMemoryAllocator/src/vk_mem_alloc.h"

namespace VTPlayer
{
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
		struct MemAllocationInfo
		{
			VmaAllocation		alloc		= null;
			void *				mappedPtr	= null;
			VkDeviceSize		size		= 0;
			VkDeviceMemory		memId		= VK_NULL_HANDLE;
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
			DataID			id			= DataID(~0u);
			uint64_t		offset		= 0;
			uint64_t		size		= 0;
			FrameID			firstFrame	= FrameID(0);	// frame when data will be requested at first time
			FrameID			lastFrame	= FrameID(0);	// frame when data can be unloaded
		};

		using DataBuffer_t		= Array<uint8_t>;
		using DataMap_t			= HashMap< DataID, DataBuffer_t >;
		using LoadEvents_t		= HashMap< FrameID, Array<FilePart> >;
		using UnloadEvents_t	= HashMap< FrameID, Array<DataID> >;


	// variables
	private:
		TraceReader				_trace;
		SharedPtr<RFile>		_dataFile;

		VulkanDeviceExt			_vulkan;
		VulkanSwapchainPtr		_swapchain;
		IWindow *				_window;

		FrameID					_currFrameId;
		uint					_sourceFPS;
		bool					_isPaused;
		bool					_isFinished;
		
		ResourceMap_t			_vkResources;
		Array<uint64_t>			_resRemappingBuf;

		// for memory remapping
		ImageAllocations_t		_imageAlloc;
		BufferAllocations_t		_bufferAlloc;
		VmaAllocator			_memAllocator	= null;
		
		// origin memory model
		MappedMemory_t			_mappedMemory;
		
		DataMap_t				_loadableData;
		LoadEvents_t			_loadEvents;
		UnloadEvents_t			_unloadEvents;

		VulkanSettings const&	_vulkanSettings;
		WindowSettings const&	_windowSettings;


	// methods
	public:
		VkPlayer_v100 (const VulkanSettings &, const WindowSettings &,
					   const SharedPtr<RFile> &, const SharedPtr<RFile> &);
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
		void OnRefrash () override {}
		void OnDestroy () override;
		void OnUpdate () override {}


	private:
		void _Destroy ();

		bool _ProcessFrame ();
		bool _CreateAllocator (VkDeviceSize pageSize);
		bool _CreateDevice (const struct VulkanCreateInfo &);
		bool _CreateSwapchain (const struct VulkanCreateInfo &);
		
		bool _PrepareData (FrameID frameId);
		bool _LoadDataPart (FilePart &part);

		bool _LoadDataToVMAMemory (VkDevice dev, MemAllocationInfo &mem, DataID dataId, VkDeviceSize offset, VkDeviceSize size) const;

		ND_ DataBuffer_t  _LoadData (DataID id) const;

		bool _SetSourceFPS (VUnpacker &);
		bool _SetData (VUnpacker &);
		bool _MapMemory (VUnpacker &);
		bool _UnmapMemory (VUnpacker &);
		bool _LoadDataToMappedMemory (VUnpacker &);
		bool _CreateShaderModule (VUnpacker &);
		bool _CreatePipelineCache (VUnpacker &);
		bool _CmdUpdateBuffer (VUnpacker &);
		bool _AcquireNextImage (VUnpacker &);
		bool _QueuePresent (VUnpacker &);
		bool _AllocateBufferMemory (VUnpacker &);
		bool _AllocateImageMemory (VUnpacker &);
		bool _FreeBufferMemory (VUnpacker &);
		bool _FreeImageMemory (VUnpacker &);
		bool _LoadDataToBuffer (VUnpacker &);
		bool _LoadDataToImage (VUnpacker &);
		bool _CmdPushDescriptorSetWithTemplate (VUnpacker &);
		bool _UpdateDescriptorSetWithTemplate (VUnpacker &);
		bool _CreateDevice (VUnpacker &);
		bool _ImageCapture (VUnpacker &);
		bool _BufferCapture (VUnpacker &);
		bool _Initializeresource (VUnpacker &);
	};


}	// VTPlayer
