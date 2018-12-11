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


ND_ inline VkObjectType  GetVkResourceType (size_t index)
{
	switch ( index )
	{
		case VkResourceIndex<VkInstance> :					return VK_OBJECT_TYPE_INSTANCE;
		case VkResourceIndex<VkPhysicalDevice> :			return VK_OBJECT_TYPE_PHYSICAL_DEVICE;
		case VkResourceIndex<VkDevice> :					return VK_OBJECT_TYPE_DEVICE;
		case VkResourceIndex<VkQueue> :						return VK_OBJECT_TYPE_QUEUE;
		case VkResourceIndex<VkSemaphore> :					return VK_OBJECT_TYPE_SEMAPHORE;
		case VkResourceIndex<VkCommandBuffer> :				return VK_OBJECT_TYPE_COMMAND_BUFFER;
		case VkResourceIndex<VkFence> :						return VK_OBJECT_TYPE_FENCE;
		case VkResourceIndex<VkDeviceMemory> :				return VK_OBJECT_TYPE_DEVICE_MEMORY;
		case VkResourceIndex<VkBuffer> :					return VK_OBJECT_TYPE_BUFFER;
		case VkResourceIndex<VkImage> :						return VK_OBJECT_TYPE_IMAGE;
		case VkResourceIndex<VkEvent> :						return VK_OBJECT_TYPE_EVENT;
		case VkResourceIndex<VkQueryPool> :					return VK_OBJECT_TYPE_QUERY_POOL;
		case VkResourceIndex<VkBufferView> :				return VK_OBJECT_TYPE_BUFFER_VIEW;
		case VkResourceIndex<VkImageView> :					return VK_OBJECT_TYPE_IMAGE_VIEW;
		case VkResourceIndex<VkShaderModule> :				return VK_OBJECT_TYPE_SHADER_MODULE;
		case VkResourceIndex<VkPipelineCache> :				return VK_OBJECT_TYPE_PIPELINE_CACHE;
		case VkResourceIndex<VkPipelineLayout> :			return VK_OBJECT_TYPE_PIPELINE_LAYOUT;
		case VkResourceIndex<VkRenderPass> :				return VK_OBJECT_TYPE_RENDER_PASS;
		case VkResourceIndex<VkPipeline> :					return VK_OBJECT_TYPE_PIPELINE;
		case VkResourceIndex<VkDescriptorSetLayout> :		return VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT;
		case VkResourceIndex<VkSampler> :					return VK_OBJECT_TYPE_SAMPLER;
		case VkResourceIndex<VkDescriptorPool> :			return VK_OBJECT_TYPE_DESCRIPTOR_POOL;
		case VkResourceIndex<VkDescriptorSet> :				return VK_OBJECT_TYPE_DESCRIPTOR_SET;
		case VkResourceIndex<VkFramebuffer> :				return VK_OBJECT_TYPE_FRAMEBUFFER;
		case VkResourceIndex<VkCommandPool> :				return VK_OBJECT_TYPE_COMMAND_POOL;
		case VkResourceIndex<VkSwapchainKHR> :				return VK_OBJECT_TYPE_SWAPCHAIN_KHR;
		case VkResourceIndex<VkSamplerYcbcrConversion> :	return VK_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION;
		case VkResourceIndex<VkObjectTableNVX> :			return VK_OBJECT_TYPE_OBJECT_TABLE_NVX;
		case VkResourceIndex<VkIndirectCommandsLayoutNVX> :	return VK_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_NVX;
		case VkResourceIndex<VkDescriptorUpdateTemplate> :	return VK_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE;
	}
	RETURN_ERR( "not supported!", VK_OBJECT_TYPE_MAX_ENUM );
}


template <typename T>
ND_ inline VkObjectType  GetVkResourceType ()
{
	return GetVkResourceType( VkResourceIndex<T> );
}


/*
ND_ static StringView  GetVkResourceTypeName (size_t index)
{
	switch ( index )
	{
		case VkResourceIndex<VkInstance> :					return "VK_OBJECT_TYPE_INSTANCE";
		case VkResourceIndex<VkPhysicalDevice> :			return "VK_OBJECT_TYPE_PHYSICAL_DEVICE";
		case VkResourceIndex<VkDevice> :					return "VK_OBJECT_TYPE_DEVICE";
		case VkResourceIndex<VkQueue> :						return "VK_OBJECT_TYPE_QUEUE";
		case VkResourceIndex<VkSemaphore> :					return "VK_OBJECT_TYPE_SEMAPHORE";
		case VkResourceIndex<VkCommandBuffer> :				return "VK_OBJECT_TYPE_COMMAND_BUFFER";
		case VkResourceIndex<VkFence> :						return "VK_OBJECT_TYPE_FENCE";
		case VkResourceIndex<VkDeviceMemory> :				return "VK_OBJECT_TYPE_DEVICE_MEMORY";
		case VkResourceIndex<VkBuffer> :					return "VK_OBJECT_TYPE_BUFFER";
		case VkResourceIndex<VkImage> :						return "VK_OBJECT_TYPE_IMAGE";
		case VkResourceIndex<VkEvent> :						return "VK_OBJECT_TYPE_EVENT";
		case VkResourceIndex<VkQueryPool> :					return "VK_OBJECT_TYPE_QUERY_POOL";
		case VkResourceIndex<VkBufferView> :				return "VK_OBJECT_TYPE_BUFFER_VIEW";
		case VkResourceIndex<VkImageView> :					return "VK_OBJECT_TYPE_IMAGE_VIEW";
		case VkResourceIndex<VkShaderModule> :				return "VK_OBJECT_TYPE_SHADER_MODULE";
		case VkResourceIndex<VkPipelineCache> :				return "VK_OBJECT_TYPE_PIPELINE_CACHE";
		case VkResourceIndex<VkPipelineLayout> :			return "VK_OBJECT_TYPE_PIPELINE_LAYOUT";
		case VkResourceIndex<VkRenderPass> :				return "VK_OBJECT_TYPE_RENDER_PASS";
		case VkResourceIndex<VkPipeline> :					return "VK_OBJECT_TYPE_PIPELINE";
		case VkResourceIndex<VkDescriptorSetLayout> :		return "VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT";
		case VkResourceIndex<VkSampler> :					return "VK_OBJECT_TYPE_SAMPLER";
		case VkResourceIndex<VkDescriptorPool> :			return "VK_OBJECT_TYPE_DESCRIPTOR_POOL";
		case VkResourceIndex<VkDescriptorSet> :				return "VK_OBJECT_TYPE_DESCRIPTOR_SET";
		case VkResourceIndex<VkFramebuffer> :				return "VK_OBJECT_TYPE_FRAMEBUFFER";
		case VkResourceIndex<VkCommandPool> :				return "VK_OBJECT_TYPE_COMMAND_POOL";
		case VkResourceIndex<VkSwapchainKHR> :				return "VK_OBJECT_TYPE_SWAPCHAIN_KHR";
		case VkResourceIndex<VkSamplerYcbcrConversion> :	return "VK_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION";
		case VkResourceIndex<VkObjectTableNVX> :			return "VK_OBJECT_TYPE_OBJECT_TABLE_NVX";
		case VkResourceIndex<VkIndirectCommandsLayoutNVX> :	return "VK_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_NVX";
		case VkResourceIndex<VkDescriptorUpdateTemplate> :	return "VK_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE";
	}
	RETURN_ERR( "not supported!" );
}*/
