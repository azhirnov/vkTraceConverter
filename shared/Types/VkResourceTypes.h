// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

using VkResourceTypes	= FG::TypeList< VkInstance, VkPhysicalDevice, VkDevice, VkQueue, VkSemaphore, VkCommandBuffer, VkFence,
										VkDeviceMemory, VkBuffer, VkImage, VkEvent, VkQueryPool, VkBufferView, VkImageView, VkShaderModule,
										VkPipelineCache, VkPipelineLayout, VkRenderPass, VkPipeline, VkDescriptorSetLayout, VkSampler,
										VkDescriptorPool, VkDescriptorSet, VkFramebuffer, VkCommandPool, VkSwapchainKHR, VkSamplerYcbcrConversion,
										VkObjectTableNVX, VkIndirectCommandsLayoutNVX, VkDescriptorUpdateTemplate >;


template <typename T>
inline static constexpr size_t		VkResourceIndex	= VkResourceTypes::Index<T>;

template <typename T>
inline static constexpr bool		IsVkResource	= VkResourceTypes::HasType<T>;


ND_ inline VkDebugReportObjectTypeEXT  GetVkResourceType (size_t index)
{
	switch ( index )
	{
		case VkResourceIndex<VkInstance> :					return VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT;
		case VkResourceIndex<VkPhysicalDevice> :			return VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT;
		case VkResourceIndex<VkDevice> :					return VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT;
		case VkResourceIndex<VkQueue> :						return VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT;
		case VkResourceIndex<VkSemaphore> :					return VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT;
		case VkResourceIndex<VkCommandBuffer> :				return VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT;
		case VkResourceIndex<VkFence> :						return VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT;
		case VkResourceIndex<VkDeviceMemory> :				return VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT;
		case VkResourceIndex<VkBuffer> :					return VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT;
		case VkResourceIndex<VkImage> :						return VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT;
		case VkResourceIndex<VkEvent> :						return VK_DEBUG_REPORT_OBJECT_TYPE_EVENT_EXT;
		case VkResourceIndex<VkQueryPool> :					return VK_DEBUG_REPORT_OBJECT_TYPE_QUERY_POOL_EXT;
		case VkResourceIndex<VkBufferView> :				return VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_VIEW_EXT;
		case VkResourceIndex<VkImageView> :					return VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_VIEW_EXT;
		case VkResourceIndex<VkShaderModule> :				return VK_DEBUG_REPORT_OBJECT_TYPE_SHADER_MODULE_EXT;
		case VkResourceIndex<VkPipelineCache> :				return VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_CACHE_EXT;
		case VkResourceIndex<VkPipelineLayout> :			return VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_LAYOUT_EXT;
		case VkResourceIndex<VkRenderPass> :				return VK_DEBUG_REPORT_OBJECT_TYPE_RENDER_PASS_EXT;
		case VkResourceIndex<VkPipeline> :					return VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_EXT;
		case VkResourceIndex<VkDescriptorSetLayout> :		return VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT_EXT;
		case VkResourceIndex<VkSampler> :					return VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_EXT;
		case VkResourceIndex<VkDescriptorPool> :			return VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_POOL_EXT;
		case VkResourceIndex<VkDescriptorSet> :				return VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_EXT;
		case VkResourceIndex<VkFramebuffer> :				return VK_DEBUG_REPORT_OBJECT_TYPE_FRAMEBUFFER_EXT;
		case VkResourceIndex<VkCommandPool> :				return VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_POOL_EXT;
		case VkResourceIndex<VkSwapchainKHR> :				return VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT;
		case VkResourceIndex<VkSamplerYcbcrConversion> :	return VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION_EXT;
		case VkResourceIndex<VkObjectTableNVX> :			return VK_DEBUG_REPORT_OBJECT_TYPE_OBJECT_TABLE_NVX_EXT;
		case VkResourceIndex<VkIndirectCommandsLayoutNVX> :	return VK_DEBUG_REPORT_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_NVX_EXT;
		case VkResourceIndex<VkDescriptorUpdateTemplate> :	return VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_EXT;
	}
	RETURN_ERR( "not supported!", VK_DEBUG_REPORT_OBJECT_TYPE_MAX_ENUM_EXT );
}


template <typename T>
ND_ inline VkDebugReportObjectTypeEXT  GetVkResourceType ()
{
	return GetVkResourceType( VkResourceIndex<T> );
}


/*
ND_ static StringView  GetVkResourceTypeName (size_t index)
{
	switch ( index )
	{
		case VkResourceIndex<VkInstance> :					return "VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT";
		case VkResourceIndex<VkPhysicalDevice> :			return "VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT";
		case VkResourceIndex<VkDevice> :					return "VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT";
		case VkResourceIndex<VkQueue> :						return "VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT";
		case VkResourceIndex<VkSemaphore> :					return "VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT";
		case VkResourceIndex<VkCommandBuffer> :				return "VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT";
		case VkResourceIndex<VkFence> :						return "VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT";
		case VkResourceIndex<VkDeviceMemory> :				return "VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT";
		case VkResourceIndex<VkBuffer> :					return "VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT";
		case VkResourceIndex<VkImage> :						return "VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT";
		case VkResourceIndex<VkEvent> :						return "VK_DEBUG_REPORT_OBJECT_TYPE_EVENT_EXT";
		case VkResourceIndex<VkQueryPool> :					return "VK_DEBUG_REPORT_OBJECT_TYPE_QUERY_POOL_EXT";
		case VkResourceIndex<VkBufferView> :				return "VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_VIEW_EXT";
		case VkResourceIndex<VkImageView> :					return "VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_VIEW_EXT";
		case VkResourceIndex<VkShaderModule> :				return "VK_DEBUG_REPORT_OBJECT_TYPE_SHADER_MODULE_EXT";
		case VkResourceIndex<VkPipelineCache> :				return "VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_CACHE_EXT";
		case VkResourceIndex<VkPipelineLayout> :			return "VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_LAYOUT_EXT";
		case VkResourceIndex<VkRenderPass> :				return "VK_DEBUG_REPORT_OBJECT_TYPE_RENDER_PASS_EXT";
		case VkResourceIndex<VkPipeline> :					return "VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_EXT";
		case VkResourceIndex<VkDescriptorSetLayout> :		return "VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT_EXT";
		case VkResourceIndex<VkSampler> :					return "VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_EXT";
		case VkResourceIndex<VkDescriptorPool> :			return "VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_POOL_EXT";
		case VkResourceIndex<VkDescriptorSet> :				return "VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_EXT";
		case VkResourceIndex<VkFramebuffer> :				return "VK_DEBUG_REPORT_OBJECT_TYPE_FRAMEBUFFER_EXT";
		case VkResourceIndex<VkCommandPool> :				return "VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_POOL_EXT";
		case VkResourceIndex<VkSwapchainKHR> :				return "VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT";
		case VkResourceIndex<VkSamplerYcbcrConversion> :	return "VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION_EXT";
		case VkResourceIndex<VkObjectTableNVX> :			return "VK_DEBUG_REPORT_OBJECT_TYPE_OBJECT_TABLE_NVX_EXT";
		case VkResourceIndex<VkIndirectCommandsLayoutNVX> :	return "VK_DEBUG_REPORT_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_NVX_EXT";
		case VkResourceIndex<VkDescriptorUpdateTemplate> :	return "VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_EXT";
	}
	RETURN_ERR( "not supported!" );
}*/
