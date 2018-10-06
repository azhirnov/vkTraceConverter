// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once


//
// Vulkan Create Info
//

struct VulkanCreateInfo
{
	uint32_t						instanceVersion;
	uint32_t						instanceExtensionCount;
	const char* const*				instanceExtensions;		// [instanceExtensionCount]
	VkInstance						instanceID;

	uint32_t						deviceExtensionCount;
	const char* const*				deviceExtensions;		// [deviceExtensionCount]
	VkPhysicalDevice				physicalDeviceID;
	VkDevice						deviceID;

	uint32_t						queueCount;
	VkQueue const*					queueIDs;				// [queueCount]
	VkQueueFlags const*				queueFamilies;			// [queueCount]
	float const*					queuePriorities;		// [queueCount]

	enum class ESwapchainType : uint32_t {
		WithoutSwapchain		= 0,
		DefaultSwapchain		= 1,
	};
	ESwapchainType					swapchainType;			// 0 - none, 1 - default, ...
	VkSwapchainKHR					swapchainID;
	uint32_t						swapchainImageWidth;	// trace requires fixed image size
	uint32_t						swapchainImageHeight;
	VkFormat						swapchainColorFormat;
	VkColorSpaceKHR					swapchainColorSpace;
	uint32_t						swapchainMinImageCount;
	uint32_t						swapchainImageArrayLayers;
	VkSurfaceTransformFlagBitsKHR	swapchainPreTransform;
	VkPresentModeKHR				swapchainPresentMode;
	VkCompositeAlphaFlagBitsKHR		swapchainCompositeAlpha;
	VkImageUsageFlags				swapchainColorImageUsage;
	VkImageLayout					swapchainImageLayout;
	uint32_t						swapchainImageCount;
	VkImage const*					swapchainImageIDs;

	enum class EImplFlags : uint32_t {
		None						= 0,
		OverrideMemoryAllocation	= 1 << 0,
		RemapQueueFamilies			= 1 << 1,
		IndirectSwapchain			= 1 << 2,
		UniqueResourceIndices		= 1 << 3,
	};
	EImplFlags						implementationFlags;
};

FG_BIT_OPERATORS( VulkanCreateInfo::ESwapchainType );
FG_BIT_OPERATORS( VulkanCreateInfo::EImplFlags );
