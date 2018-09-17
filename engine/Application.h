// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "engine/FIValue.h"
#include "engine/ResourceIDs.h"

namespace VTC
{
	
	//
	// Vulkan Application
	//

	class VApp final : public IWindowEventListener, public VulkanDeviceFn
	{
	// types
	public:
		struct QueueInfo
		{
			QueueID				id;
			VkQueueFlags		flags;
			float				priority;
		};

		struct FilePart
		{
			DataID			id			= DataID(~0u);
			uint64_t		offset		= 0;
			uint64_t		size		= 0;
			FrameID			firstFrame	= FrameID(0);	// frame when data will be requested at first time
			FrameID			lastFrame	= FrameID(0);	// frame when data can be unloaded
		};


	private:
		using ResourceMap_t		= StaticArray< Array<VkResourceID_t>, 32 >;

		struct MemRange
		{
			void *			mappedPtr	= null;
			VkDeviceSize	offset		= 0;
			VkDeviceSize	size		= 0;
		};
		using MappedMemory_t	= Array< MemRange >;

		
		struct FilePartExt : FilePart
		{
			FILE*		file = null;

			FilePartExt () {}
			FilePartExt (const FilePart &part, FILE* file) : FilePart{part}, file{file} {}
		};

		using DataMap_t			= HashMap< DataID, Array<uint8_t> >;
		using LoadEvents_t		= HashMap< FrameID, Array<FilePartExt> >;
		using UnloadEvents_t	= HashMap< FrameID, Array<DataID> >;
		using FileMap_t			= HashMap< String, FILE* >;


	// variables
	private:
		VulkanDeviceExt			_vulkan;
		VulkanSwapchainPtr		_swapchain;
		WindowPtr				_window;
		String					_windowTitle;
		uint2					_surfaceSize;
		
		mutable ResourceMap_t 	_resources;
		mutable MappedMemory_t	_mappedMemory;

		DataMap_t				_loadableData;
		LoadEvents_t			_loadEvents;
		UnloadEvents_t			_unloadEvents;
		FileMap_t				_files;


	// methods
	public:
		VApp ();
		~VApp ();


		bool CreateWindow (uint width, uint height, StringView title);

		bool CreateDevice (InstanceID				instance,
						   PhysicalDeviceID			physicalDevice,
						   DeviceID					logicalDevice,
						   //SurfaceKHRID			surface,
						   StringView				gpuDeviceName,
						   uint						apiVersion,
						   ArrayView<QueueInfo>		queues,
						   ArrayView<const char*>	instanceLayers		= VulkanDevice::GetRecomendedInstanceLayers(),
						   ArrayView<const char*>	instanceExtensions	= VulkanDevice::GetRecomendedInstanceExtensions(),
						   ArrayView<const char*>	deviceExtensions	= VulkanDevice::GetRecomendedDeviceExtensions());

		bool CreateSwapchain (SwapchainKHRID						swapchain,
							  ArrayView<ImageID>					swapchainImages,
							  SemaphoreID							imageAvailableSemaphore,
							  SemaphoreID							renderFinishedSemaphore,
							  const VkFormat						colorFormat			= VK_FORMAT_B8G8R8A8_UNORM,
							  const VkColorSpaceKHR					colorSpace			= VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,
							  const uint							minImageCount		= 2,
							  const uint							imageArrayLayers	= 1,
							  const VkSurfaceTransformFlagBitsKHR	preTransform		= VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
							  const VkPresentModeKHR				presentMode			= VK_PRESENT_MODE_FIFO_KHR,
							  const VkCompositeAlphaFlagBitsKHR		compositeAlpha		= VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
							  const VkImageUsageFlags				colorImageUsage		= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_STORAGE_BIT);
		
		template <typename ResIdType>
		void AllocateResources (const ResIdType count);

		bool AddExternalData (const String &filename, ArrayView<FilePart> parts);
		bool PreloadAllData ();

		bool Run (ArrayView<VDrawFrame_t> frames);


		bool AcquireImage (ImageID image, SemaphoreID imageAvailableSemaphore) const;
		bool Present (QueueID queue, ImageID image, SemaphoreID renderFinishedSemaphore) const;


		ND_ uint  GetMemoryTypeIndex (uint memoryTypeBits, VkMemoryPropertyFlags flags) const;


		ND_ ArrayView<uint8_t>  LoadData (DataID id) const;


		bool OnMapMemory (DeviceMemoryID memId, void *ptr, VkDeviceSize offset, VkDeviceSize size) const;
		bool OnUnmapMemory (DeviceMemoryID memId) const;
		//bool GetMappedMemory (DeviceMemoryID memId, OUT void* &ptr, OUT VkDeviceSize &size) const;
		bool LoadDataToMappedMemory (DeviceMemoryID memId, DataID dataId, VkDeviceSize offset, VkDeviceSize size) const;


		template <typename ResIdType>
		ND_ typename _ObjInfo<ResIdType>::vktype const	GetResource (ResIdType id)	const;

		template <typename ResIdType>
		ND_ typename _ObjInfo<ResIdType>::vktype & 		EditResource (ResIdType id)	const	{ return _EditResource( id ); }


	private:
		template <typename ResIdType>
		typename _ObjInfo<ResIdType>::vktype &  _EditResource (ResIdType id) const;

		ND_ VkInstance & 				EditResource (InstanceID id)				{ return _EditResource( id ); }
		ND_ VkPhysicalDevice & 			EditResource (PhysicalDeviceID id)			{ return _EditResource( id ); }
		ND_ VkDevice & 					EditResource (DeviceID id)					{ return _EditResource( id ); }
		ND_ VkQueue & 					EditResource (QueueID id)					{ return _EditResource( id ); }
		ND_ VkSwapchainKHR &			EditResource (SwapchainKHRID id)			{ return _EditResource( id ); }
		//ND_ VkSurfaceKHR &			EditResource (SurfaceKHRID id)				{ return _EditResource( id ); }
		
		bool _PrepareData (FrameID frameId);
		bool _LoadDataPart (FilePartExt &part);


	// implement IWindowEventListener
	private:
		void OnResize (const uint2 &size) override;
		void OnRefrash () override;
		void OnDestroy () override;
		void OnUpdate () override;
	};


	
/*
=================================================
	GetResource
=================================================
*/
	template <typename ResIdType>
	inline typename _ObjInfo<ResIdType>::vktype const  VApp::GetResource (ResIdType id) const
	{
		if ( id == ResIdType(~0u) )
			return 0;

		constexpr uint	index = _ObjInfo<ResIdType>::index;
		
		STATIC_ASSERT( index < std::tuple_size<decltype(_resources)>::value );
		ASSERT( size_t(id) < _resources[index].size() );

		auto	result = BitCast< typename _ObjInfo<ResIdType>::vktype >( _resources[index] [size_t(id)] );
		ASSERT( result != 0 );

		return result;
	}
	
/*
=================================================
	EditResource
=================================================
*/
	template <typename ResIdType>
	inline typename _ObjInfo<ResIdType>::vktype &  VApp::_EditResource (ResIdType id) const
	{
		constexpr uint	index = _ObjInfo<ResIdType>::index;
		
		STATIC_ASSERT( index < std::tuple_size<decltype(_resources)>::value );
		ASSERT( size_t(id) < _resources[index].size() );

		auto&	result = BitCast< typename _ObjInfo<ResIdType>::vktype >( _resources[index] [size_t(id)] );
		//ASSERT( result == 0 );

		return result;
	}
	
/*
=================================================
	AllocateResources
=================================================
*/
	template <typename ResIdType>
	inline void  VApp::AllocateResources (const ResIdType count)
	{
		constexpr uint	index = _ObjInfo<ResIdType>::index;
		
		STATIC_ASSERT( index < std::tuple_size<decltype(_resources)>::value );
		ASSERT( count < ResIdType(~0u) );

		_resources[ index ].resize( size_t(count) );

		if constexpr ( std::is_same_v< ResIdType, DeviceMemoryID > )
		{
			_mappedMemory.resize( size_t(count) );
		}
	}


}	// VTC