// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Analyzer/Ext/ExtensionAnalyzer.h"

#ifndef VK_KHR_WIN32_SURFACE_EXTENSION_NAME
#define VK_KHR_WIN32_SURFACE_EXTENSION_NAME "VK_KHR_win32_surface"
#endif

#ifndef VK_KHR_XLIB_SURFACE_EXTENSION_NAME
#define VK_KHR_XLIB_SURFACE_EXTENSION_NAME "VK_KHR_xlib_surface"
#endif

#ifndef VK_KHR_XCB_SURFACE_EXTENSION_NAME
#define VK_KHR_XCB_SURFACE_EXTENSION_NAME "VK_KHR_xcb_surface"
#endif

#ifndef VK_KHR_ANDROID_SURFACE_EXTENSION_NAME
#define VK_KHR_ANDROID_SURFACE_EXTENSION_NAME "VK_KHR_android_surface"
#endif

#ifndef VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME
#define VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME "VK_KHR_wayland_surface"
#endif

#ifndef VK_EXT_ACQUIRE_XLIB_DISPLAY_EXTENSION_NAME
#define VK_EXT_ACQUIRE_XLIB_DISPLAY_EXTENSION_NAME "VK_EXT_acquire_xlib_display"
#endif


namespace VTC
{

/*
=================================================
	constructor
=================================================
*/
	ExtensionAnalyzer::ExtensionAnalyzer ()
	{
		_minVersion = VK_API_VERSION_1_0;
	}
	
/*
=================================================
	Process
=================================================
*/
	void ExtensionAnalyzer::Process (const TraceRange::Iterator &iter)
	{
		switch ( iter->packet_id )
		{
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalImageFormatPropertiesNV :
				_instanceExtensions.insert( VK_NV_EXTERNAL_MEMORY_CAPABILITIES_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkCmdDrawIndirectCountAMD :
			case VKTRACE_TPI_VK_vkCmdDrawIndexedIndirectCountAMD :
				_deviceExtensions.insert( VK_AMD_DRAW_INDIRECT_COUNT_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkCreateDebugReportCallbackEXT :
			case VKTRACE_TPI_VK_vkDestroyDebugReportCallbackEXT :
			case VKTRACE_TPI_VK_vkDebugReportMessageEXT :
				_instanceExtensions.insert( VK_EXT_DEBUG_REPORT_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkDebugMarkerSetObjectTagEXT :
			case VKTRACE_TPI_VK_vkDebugMarkerSetObjectNameEXT :
			case VKTRACE_TPI_VK_vkCmdDebugMarkerBeginEXT :
			case VKTRACE_TPI_VK_vkCmdDebugMarkerEndEXT :
			case VKTRACE_TPI_VK_vkCmdDebugMarkerInsertEXT :
				_deviceExtensions.insert( VK_EXT_DEBUG_MARKER_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkDestroySurfaceKHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceSupportKHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceCapabilitiesKHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceFormatsKHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfacePresentModesKHR :
				_instanceExtensions.insert( VK_KHR_SURFACE_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkCreateSwapchainKHR :
			case VKTRACE_TPI_VK_vkDestroySwapchainKHR :
			case VKTRACE_TPI_VK_vkGetSwapchainImagesKHR :
			case VKTRACE_TPI_VK_vkAcquireNextImageKHR :
			case VKTRACE_TPI_VK_vkQueuePresentKHR :
			case VKTRACE_TPI_VK_vkCreateSharedSwapchainsKHR :
				_deviceExtensions.insert( VK_KHR_SWAPCHAIN_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkCreateWin32SurfaceKHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceWin32PresentationSupportKHR :
				_instanceExtensions.insert( VK_KHR_WIN32_SURFACE_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkCreateXlibSurfaceKHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceXlibPresentationSupportKHR :
				_instanceExtensions.insert( VK_KHR_XLIB_SURFACE_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkCreateXcbSurfaceKHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceXcbPresentationSupportKHR :
				_instanceExtensions.insert( VK_KHR_XCB_SURFACE_EXTENSION_NAME );
				break;
				
			case VKTRACE_TPI_VK_vkCreateAndroidSurfaceKHR :
				_instanceExtensions.insert( VK_KHR_ANDROID_SURFACE_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkGetMemoryWin32HandleNV :
				_deviceExtensions.insert( VK_NV_EXTERNAL_MEMORY_WIN32_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkCreateDescriptorUpdateTemplateKHR :
			case VKTRACE_TPI_VK_vkDestroyDescriptorUpdateTemplateKHR :
			case VKTRACE_TPI_VK_vkUpdateDescriptorSetWithTemplateKHR :
				_deviceExtensions.insert( VK_KHR_DESCRIPTOR_UPDATE_TEMPLATE_EXTENSION_NAME );
				break;
				
			case VKTRACE_TPI_VK_vkCmdPushDescriptorSetKHR :
			case VKTRACE_TPI_VK_vkCmdPushDescriptorSetWithTemplateKHR :
				_deviceExtensions.insert( VK_KHR_PUSH_DESCRIPTOR_EXTENSION_NAME );
				break;
				
			case VKTRACE_TPI_VK_vkCreateWaylandSurfaceKHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceWaylandPresentationSupportKHR :
				_instanceExtensions.insert( VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME );
				break;
				
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceFeatures2KHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceProperties2KHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceFormatProperties2KHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceImageFormatProperties2KHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceQueueFamilyProperties2KHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceMemoryProperties2KHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceSparseImageFormatProperties2KHR :
				_instanceExtensions.insert( VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkGetImageMemoryRequirements2KHR :
			case VKTRACE_TPI_VK_vkGetBufferMemoryRequirements2KHR :
			case VKTRACE_TPI_VK_vkGetImageSparseMemoryRequirements2KHR :
				_deviceExtensions.insert( VK_KHR_GET_MEMORY_REQUIREMENTS_2_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceCapabilities2KHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceFormats2KHR :
				_instanceExtensions.insert( VK_KHR_GET_SURFACE_CAPABILITIES_2_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkGetPhysicalDeviceDisplayPropertiesKHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceDisplayPlanePropertiesKHR :
			case VKTRACE_TPI_VK_vkGetDisplayPlaneSupportedDisplaysKHR :
			case VKTRACE_TPI_VK_vkGetDisplayModePropertiesKHR :
			case VKTRACE_TPI_VK_vkCreateDisplayModeKHR :
			case VKTRACE_TPI_VK_vkGetDisplayPlaneCapabilitiesKHR :
			case VKTRACE_TPI_VK_vkCreateDisplayPlaneSurfaceKHR :
				_instanceExtensions.insert( VK_KHR_DISPLAY_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkTrimCommandPoolKHR :
				_deviceExtensions.insert( VK_KHR_MAINTENANCE1_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalBufferPropertiesKHR :
				_instanceExtensions.insert( VK_KHR_EXTERNAL_MEMORY_CAPABILITIES_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkGetMemoryFdKHR :
			case VKTRACE_TPI_VK_vkGetMemoryFdPropertiesKHR :
				_deviceExtensions.insert( VK_KHR_EXTERNAL_MEMORY_FD_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR :
				_instanceExtensions.insert( VK_KHR_EXTERNAL_SEMAPHORE_CAPABILITIES_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkImportSemaphoreFdKHR :
			case VKTRACE_TPI_VK_vkGetSemaphoreFdKHR :
				_deviceExtensions.insert( VK_KHR_EXTERNAL_SEMAPHORE_FD_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkGetSwapchainStatusKHR :
				_deviceExtensions.insert( VK_KHR_SHARED_PRESENTABLE_IMAGE_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalFencePropertiesKHR :
				_instanceExtensions.insert( VK_KHR_EXTERNAL_FENCE_CAPABILITIES_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkBindBufferMemory2KHR :
			case VKTRACE_TPI_VK_vkBindImageMemory2KHR :
				_deviceExtensions.insert( VK_KHR_BIND_MEMORY_2_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkCmdProcessCommandsNVX :
			case VKTRACE_TPI_VK_vkCmdReserveSpaceForCommandsNVX :
			case VKTRACE_TPI_VK_vkCreateIndirectCommandsLayoutNVX :
			case VKTRACE_TPI_VK_vkDestroyIndirectCommandsLayoutNVX :
			case VKTRACE_TPI_VK_vkCreateObjectTableNVX :
			case VKTRACE_TPI_VK_vkDestroyObjectTableNVX :
			case VKTRACE_TPI_VK_vkRegisterObjectsNVX :
			case VKTRACE_TPI_VK_vkUnregisterObjectsNVX :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX :
			case VKTRACE_TPI_VK_vkCmdSetViewportWScalingNV :
				_deviceExtensions.insert( VK_NVX_DEVICE_GENERATED_COMMANDS_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkReleaseDisplayEXT :
				_instanceExtensions.insert( VK_EXT_DIRECT_MODE_DISPLAY_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceCapabilities2EXT :
				_instanceExtensions.insert( VK_EXT_DISPLAY_SURFACE_COUNTER_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkGetRefreshCycleDurationGOOGLE :
			case VKTRACE_TPI_VK_vkGetPastPresentationTimingGOOGLE :
				_deviceExtensions.insert( VK_GOOGLE_DISPLAY_TIMING_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkCmdSetDiscardRectangleEXT :
				_deviceExtensions.insert( VK_EXT_DISCARD_RECTANGLES_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkSetHdrMetadataEXT :
				_deviceExtensions.insert( VK_EXT_HDR_METADATA_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkAcquireXlibDisplayEXT :
			case VKTRACE_TPI_VK_vkGetRandROutputDisplayEXT :
				_instanceExtensions.insert( VK_EXT_ACQUIRE_XLIB_DISPLAY_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkDisplayPowerControlEXT :
			case VKTRACE_TPI_VK_vkRegisterDeviceEventEXT :
			case VKTRACE_TPI_VK_vkRegisterDisplayEventEXT :
			case VKTRACE_TPI_VK_vkGetSwapchainCounterEXT :
				_deviceExtensions.insert( VK_EXT_DISPLAY_CONTROL_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkCmdSetSampleLocationsEXT :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceMultisamplePropertiesEXT :
				_deviceExtensions.insert( VK_EXT_SAMPLE_LOCATIONS_EXTENSION_NAME );
				break;
				
			case VKTRACE_TPI_VK_vkCreateSamplerYcbcrConversionKHR :
			case VKTRACE_TPI_VK_vkDestroySamplerYcbcrConversionKHR :
				_deviceExtensions.insert( VK_KHR_SAMPLER_YCBCR_CONVERSION_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkImportFenceFdKHR :
			case VKTRACE_TPI_VK_vkGetFenceFdKHR :
				_deviceExtensions.insert( VK_KHR_EXTERNAL_FENCE_FD_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkImportFenceWin32HandleKHR :
			case VKTRACE_TPI_VK_vkGetFenceWin32HandleKHR :
				_deviceExtensions.insert( VK_KHR_EXTERNAL_FENCE_WIN32_EXTENSION_NAME );
				break;
				
			case VKTRACE_TPI_VK_vkGetMemoryWin32HandleKHR :
			case VKTRACE_TPI_VK_vkGetMemoryWin32HandlePropertiesKHR :
				_deviceExtensions.insert( VK_KHR_EXTERNAL_MEMORY_WIN32_EXTENSION_NAME );
				break;
				
			case VKTRACE_TPI_VK_vkImportSemaphoreWin32HandleKHR :
			case VKTRACE_TPI_VK_vkGetSemaphoreWin32HandleKHR :
				_deviceExtensions.insert( VK_KHR_EXTERNAL_SEMAPHORE_WIN32_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkGetMemoryHostPointerPropertiesEXT :
				_deviceExtensions.insert( VK_EXT_EXTERNAL_MEMORY_HOST_EXTENSION_NAME );
				break;
				
			case VKTRACE_TPI_VK_vkCreateValidationCacheEXT :
			case VKTRACE_TPI_VK_vkDestroyValidationCacheEXT :
			case VKTRACE_TPI_VK_vkMergeValidationCachesEXT :
			case VKTRACE_TPI_VK_vkGetValidationCacheDataEXT :
				_deviceExtensions.insert( VK_EXT_VALIDATION_CACHE_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkGetShaderInfoAMD :
				_deviceExtensions.insert( VK_AMD_SHADER_INFO_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkGetDeviceQueue2 :
			case VKTRACE_TPI_VK_vkEnumerateInstanceVersion :
			case VKTRACE_TPI_VK_vkBindBufferMemory2 :
			case VKTRACE_TPI_VK_vkBindImageMemory2 :
			case VKTRACE_TPI_VK_vkGetDeviceGroupPeerMemoryFeatures :
			case VKTRACE_TPI_VK_vkCmdSetDeviceMask :
			case VKTRACE_TPI_VK_vkCmdDispatchBase :
			case VKTRACE_TPI_VK_vkEnumeratePhysicalDeviceGroups :
			case VKTRACE_TPI_VK_vkGetImageMemoryRequirements2 :
			case VKTRACE_TPI_VK_vkGetBufferMemoryRequirements2 :
			case VKTRACE_TPI_VK_vkGetImageSparseMemoryRequirements2 :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceFeatures2 :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceProperties2 :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceFormatProperties2 :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceImageFormatProperties2 :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceQueueFamilyProperties2 :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceMemoryProperties2 :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceSparseImageFormatProperties2 :
			case VKTRACE_TPI_VK_vkTrimCommandPool :
			case VKTRACE_TPI_VK_vkCreateSamplerYcbcrConversion :
			case VKTRACE_TPI_VK_vkDestroySamplerYcbcrConversion :
			case VKTRACE_TPI_VK_vkCreateDescriptorUpdateTemplate :
			case VKTRACE_TPI_VK_vkDestroyDescriptorUpdateTemplate :
			case VKTRACE_TPI_VK_vkUpdateDescriptorSetWithTemplate :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalBufferProperties :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalFenceProperties :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalSemaphoreProperties :
			case VKTRACE_TPI_VK_vkGetDescriptorSetLayoutSupport :
				_minVersion = Max( _minVersion, VK_API_VERSION_1_1 );
				break;

			case VKTRACE_TPI_VK_vkGetDeviceGroupPresentCapabilitiesKHR :
			case VKTRACE_TPI_VK_vkGetDeviceGroupSurfacePresentModesKHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDevicePresentRectanglesKHR :
			case VKTRACE_TPI_VK_vkAcquireNextImage2KHR :
				_minVersion = Max( _minVersion, VK_API_VERSION_1_1 );
				_deviceExtensions.insert( VK_KHR_SWAPCHAIN_EXTENSION_NAME );
				break;

			case VKTRACE_TPI_VK_vkGetPhysicalDeviceDisplayProperties2KHR :
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceDisplayPlaneProperties2KHR :
			case VKTRACE_TPI_VK_vkGetDisplayModeProperties2KHR :
			case VKTRACE_TPI_VK_vkGetDisplayPlaneCapabilities2KHR :
				_minVersion = Max( _minVersion, VK_API_VERSION_1_1 );
				_instanceExtensions.insert( VK_KHR_GET_DISPLAY_PROPERTIES_2_EXTENSION_NAME );
				break;
		}
	}


}	// VTC
