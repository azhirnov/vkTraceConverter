// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "stl/Algorithms/EnumUtils.h"
#include "stl/Algorithms/Cast.h"
#include "stl/Stream/FileStream.h"
#include "stl/Stream/MemStream.h"

#include "framework/Vulkan/VulkanDeviceExt.h"
#include "framework/Vulkan/VulkanSwapchain.h"
#include "framework/Window/IWindow.h"

namespace VTPlayer
{
	using namespace FG;

	enum class EWindowFlags
	{
		None		= 0,
		ShowFPS		= 1 << 0,
		Fullscreen	= 1 << 1,
		Resizable	= 1 << 2,
	};
	FG_BIT_OPERATORS( EWindowFlags );


	enum class EPlayerFlags
	{
		None				= 0,
		EnableCpuBenchmark	= 1 << 0,
		EnableGpuBenchmark	= 1 << 1,
		DebugMode			= 1 << 2,
		TestMode			= 1 << 3,
	};
	FG_BIT_OPERATORS( EPlayerFlags );



	//
	// Player Settings
	//

	struct PlayerSettings
	{
		uint			version			= 0;
		String			traceFilename;
		String			dataFilename;							// may be empty if data packed into trace file
		EPlayerFlags	flags			= EPlayerFlags::None;
	};

	

	//
	// Window Settings
	//

	struct WindowSettings
	{
		uint2			size;
		int2			position;
		String			title;
		EWindowFlags	flags		= EWindowFlags::None;
	};



	//
	// Vulkan Settings
	//

	struct VulkanSettings
	{
		using QueueCreateInfo	= VulkanDevice::QueueCreateInfo;
		
		struct InstanceCreateInfo
		{
			uint			version		= 0;
			Array<String>	layers;
			Array<String>	extensions;
		};

		struct DeviceCreateInfo
		{
			String			preferredGPUName;
			Array<String>	extensions;
		};

		struct SwapchainCreateInfo
		{
			VkFormat						colorFormat			= VK_FORMAT_B8G8R8A8_UNORM;
			VkColorSpaceKHR					colorSpace			= VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
			uint							minImageCount		= 2;
			uint							imageArrayLayers	= 1;
			VkSurfaceTransformFlagBitsKHR	transform			= VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
			VkPresentModeKHR				presentMode			= VK_PRESENT_MODE_FIFO_KHR;
			VkCompositeAlphaFlagBitsKHR		compositeAlpha		= VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
			VkImageUsageFlags				colorImageUsage		= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_STORAGE_BIT;
		};

		InstanceCreateInfo		instance;
		DeviceCreateInfo		device;
		SwapchainCreateInfo		swapchain;
	};


}	// VTPlayer
