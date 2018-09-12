// Copyright (c)  Zhirnov Andrey. For more information see 'LICENSE.txt'

#pragma once

#include "engine/DrawCommand.h"
#include "engine/CommandBufferBuilder.h"
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
		using ResourceMap_t		= StaticArray< Array<VkResourceID_t>, 32 >;
		using ObjectMap_t		= Array< DrawCommand >;
		using DataMap_t			= HashMap< DataID, Array<uint8_t> >;

		struct QueueInfo
		{
			QueueID				id;
			VkQueueFlags		flags;
			float				priority;
		};


	// variables
	private:
		VulkanDevice			_vulkan;
		VulkanSwapchainPtr		_swapchain;
		WindowPtr				_window;
		uint2					_surfaceSize;
		
		mutable ResourceMap_t 	_resources;
		ObjectMap_t				_objects;
		DataMap_t				_loadableData;
		

	// methods
	public:
		VApp ();
		~VApp ();

		bool CreateWindow (uint width, uint height, StringView caption);

		bool CreateDevice (InstanceID				instance,
						   PhysicalDeviceID			physicalDevice,
						   DeviceID					logicalDevice,
						   //SurfaceKHRID			surface,
						   StringView				gpuDeviceName,
						   uint						apiVersion,
						   ArrayView<QueueInfo>		queues,
						   ArrayView<StringView>	instanceLayers		= Default,
						   ArrayView<StringView>	instanceExtensions	= Default,
						   ArrayView<StringView>	deviceExtensions	= Default);

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

		bool Run (ArrayView<VDrawFrame_t> frames);


		bool AcquireImage (ImageID image, SemaphoreID imageAvailableSemaphore) const;
		bool Present (QueueID queue, ImageID image, SemaphoreID renderFinishedSemaphore) const;


		ND_ DrawCommand const&			GetObject (ObjectID id)				const	{ return _objects[size_t(id)]; }

		ND_ ArrayView<uint8_t>			LoadData (DataID id);

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

		ASSERT( index < _resources.size() );
		ASSERT( size_t(id) < _resources[index].size() );

		return BitCast< typename _ObjInfo<ResIdType>::vktype >( _resources[index] [size_t(id)] );
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

		ASSERT( index < _resources.size() );
		ASSERT( size_t(id) < _resources[index].size() );

		return BitCast< typename _ObjInfo<ResIdType>::vktype >( _resources[index] [size_t(id)] );
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

		ASSERT( index < _resources.size() );
		ASSERT( count < ResIdType(~0u) );

		_resources[ index ].resize( size_t(count) );
	}


}	// VTC
