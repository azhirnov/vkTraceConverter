// Copyright (c)  Zhirnov Andrey. For more information see 'LICENSE.txt'

#include "engine/Application.h"
#include "framework/Window/WindowGLFW.h"
#include "framework/Window/WindowSDL2.h"

namespace VTC
{

/*
=================================================
	constructor
=================================================
*/
	VApp::VApp ()
	{
#	if defined(FG_ENABLE_GLFW)
		_window.reset( new WindowGLFW() );

#	elif defined(FG_ENABLE_SDL2)
		_window.reset( new WindowSDL2() );

#	else
#		error unknown window library!
#	endif

		VulkanDeviceFn_Init( _vulkan );
	}
	
/*
=================================================
	destructor
=================================================
*/
	VApp::~VApp ()
	{
		if ( _swapchain ) {
			_swapchain->Destroy();
			_swapchain.reset();
		}

		_vulkan.Destroy();

		if ( _window ) {
			_window->Destroy();
			_window.reset();
		}
	}
	
/*
=================================================
	OnResize
=================================================
*/
	void VApp::OnResize (const uint2 &size)
	{
		ASSERT(false);

		_swapchain->Recreate( size );
	}
	
/*
=================================================
	OnRefrash
=================================================
*/
	void VApp::OnRefrash ()
	{
	}
	
/*
=================================================
	OnDestroy
=================================================
*/
	void VApp::OnDestroy ()
	{
	}
	
/*
=================================================
	OnUpdate
=================================================
*/
	void VApp::OnUpdate ()
	{
	}

/*
=================================================
	CreateWindow
=================================================
*/
	bool VApp::CreateWindow (uint width, uint height, StringView caption)
	{
		CHECK_ERR( _window );

		CHECK_ERR( _window->Create( uint2{width, height}, caption, this ));

		_surfaceSize = uint2{width, height};
		return true;
	}
	
/*
=================================================
	CreateDevice
=================================================
*/
	bool VApp::CreateDevice (InstanceID				instance,
							 PhysicalDeviceID		physicalDevice,
							 DeviceID				logicalDevice,
							 StringView				gpuDeviceName,
							 uint					apiVersion,
							 ArrayView<QueueInfo>	queues,
							 ArrayView<StringView>	instanceLayers,
							 ArrayView<StringView>	instanceExtensions,
							 ArrayView<StringView>	deviceExtensions)
	{
		// not supported yet:
		ASSERT( instanceLayers.empty() );
		ASSERT( instanceExtensions.empty() );
		ASSERT( deviceExtensions.empty() );


		FixedArray< VulkanDevice::QueueCreateInfo, 16 >		queue_ci;
		for (auto& q : queues) {
			queue_ci.push_back({ q.flags, q.priority });
		}

		CHECK_ERR( _vulkan.Create( _window->GetVulkanSurface(), "", apiVersion, gpuDeviceName, queue_ci ));
		CHECK_ERR( queues.size() == _vulkan.GetVkQuues().size() );

		CHECK_ERR( _vulkan.CreateDebugCallback( VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT | VK_DEBUG_REPORT_ERROR_BIT_EXT ));


		// map resource IDs
		EditResource( instance )		= _vulkan.GetVkInstance();
		EditResource( physicalDevice )	= _vulkan.GetVkPhysicalDevice();
		EditResource( logicalDevice )	= _vulkan.GetVkDevice();

		for (size_t i = 0; i < queues.size(); ++i) {
			EditResource(queues[i].id) = _vulkan.GetVkQuues()[i].id;
		}
		return true;
	}

/*
=================================================
	CreateSwapchain
=================================================
*/
	bool VApp::CreateSwapchain (SwapchainKHRID						swapchain,
								ArrayView<ImageID>					swapchainImages,
								SemaphoreID							imageAvailableSemaphore,
								SemaphoreID							renderFinishedSemaphore,
								VkFormat							colorFormat,
								VkColorSpaceKHR						colorSpace,
								const uint							minImageCount,
								const uint							imageArrayLayers,
								const VkSurfaceTransformFlagBitsKHR	transform,
								const VkPresentModeKHR				presentMode,
								const VkCompositeAlphaFlagBitsKHR	compositeAlpha,
								const VkImageUsageFlags				colorImageUsage)
	{
		CHECK_ERR( not _swapchain );
		
		_swapchain.reset( new VulkanSwapchain{ _vulkan });

		CHECK_ERR( _swapchain->ChooseColorFormat( INOUT colorFormat, INOUT colorSpace ));

		CHECK_ERR( _swapchain->Create( _surfaceSize, colorFormat, colorSpace, minImageCount, imageArrayLayers,
									   transform, presentMode, compositeAlpha, colorImageUsage ));
		
		
		uint	count = 0;
		VK_CHECK( vkGetSwapchainImagesKHR( _vulkan.GetVkDevice(), _swapchain->GetVkSwapchain(), OUT &count, null ));
		CHECK_ERR( count > 0 );
		
		FixedArray< VkImage, FG_MaxSwapchainLength >	images;
		images.resize( count );
		VK_CHECK( vkGetSwapchainImagesKHR( _vulkan.GetVkDevice(), _swapchain->GetVkSwapchain(), OUT &count, OUT images.data() ));

		CHECK_ERR( count == swapchainImages.size() );

		for (size_t i = 0; i < images.size(); ++i)
		{
			EditResource( swapchainImages[i] ) = images[i];
		}

		EditResource( swapchain ) = _swapchain->GetVkSwapchain();

		CHECK_ERR( imageAvailableSemaphore != renderFinishedSemaphore );

		EditResource( imageAvailableSemaphore )	= _swapchain->GetImageAvailableSemaphore();
		EditResource( renderFinishedSemaphore ) = _swapchain->GetRenderFinishedSemaphore();

		return true;
	}
	
/*
=================================================
	Run
=================================================
*/
	bool VApp::Run (ArrayView<VDrawFrame_t> frames)
	{
		for (size_t i = 0; i < frames.size(); ++i)
		{
			if ( not _window->Update() )
				return true;

			frames[i]( *this );
		}

		return true;
	}
	
/*
=================================================
	LoadData
=================================================
*/
	ArrayView<uint8_t>  VApp::LoadData (DataID id)
	{
		ASSERT(false);
		return {};
	}
	
/*
=================================================
	AcquireImage
=================================================
*/
	bool VApp::AcquireImage (ImageID image, SemaphoreID imageAvailableSemaphore) const
	{
		CHECK_ERR( _swapchain );
		CHECK_ERR( GetResource(imageAvailableSemaphore) == _swapchain->GetImageAvailableSemaphore() );
		
		VK_CHECK( _swapchain->AcquireNextImage() );		// TODO: handle errors

		ASSERT( GetResource(image) == _swapchain->GetCurrentImage() );
		return true;
	}
	
/*
=================================================
	Present
=================================================
*/
	bool VApp::Present (QueueID queue, ImageID image, SemaphoreID renderFinishedSemaphore) const
	{
		CHECK_ERR( _swapchain );
		CHECK_ERR( GetResource(renderFinishedSemaphore) == _swapchain->GetRenderFinishedSemaphore() );
		ASSERT( GetResource(image) == _swapchain->GetCurrentImage() );
		
		CHECK_ERR( _swapchain->Present( GetResource(queue) ));
		return true;
	}


}	// VTC

