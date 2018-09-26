// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "VkTraceCommon.h"

namespace VTC
{

	template <typename T> struct IsVkResource					{ static constexpr bool	 value = false; };

	template <>  struct IsVkResource< VkInstance >				{ static constexpr bool	 value = true; };
	template <>  struct IsVkResource< VkPhysicalDevice >		{ static constexpr bool	 value = true; };
	template <>  struct IsVkResource< VkDevice >				{ static constexpr bool	 value = true; };
	template <>  struct IsVkResource< VkQueue >					{ static constexpr bool	 value = true; };
	template <>  struct IsVkResource< VkSemaphore >				{ static constexpr bool	 value = true; };
	template <>  struct IsVkResource< VkCommandBuffer >			{ static constexpr bool	 value = true; };
	template <>  struct IsVkResource< VkFence >					{ static constexpr bool	 value = true; };
	template <>  struct IsVkResource< VkDeviceMemory >			{ static constexpr bool	 value = true; };
	template <>  struct IsVkResource< VkBuffer >				{ static constexpr bool	 value = true; };
	template <>  struct IsVkResource< VkImage >					{ static constexpr bool	 value = true; };
	template <>  struct IsVkResource< VkEvent >					{ static constexpr bool	 value = true; };
	template <>  struct IsVkResource< VkQueryPool >				{ static constexpr bool	 value = true; };
	template <>  struct IsVkResource< VkBufferView >			{ static constexpr bool	 value = true; };
	template <>  struct IsVkResource< VkImageView >				{ static constexpr bool	 value = true; };
	template <>  struct IsVkResource< VkShaderModule >			{ static constexpr bool	 value = true; };
	template <>  struct IsVkResource< VkPipelineCache >			{ static constexpr bool	 value = true; };
	template <>  struct IsVkResource< VkPipelineLayout >		{ static constexpr bool	 value = true; };
	template <>  struct IsVkResource< VkRenderPass >			{ static constexpr bool	 value = true; };
	template <>  struct IsVkResource< VkPipeline >				{ static constexpr bool	 value = true; };
	template <>  struct IsVkResource< VkDescriptorSetLayout >	{ static constexpr bool	 value = true; };
	template <>  struct IsVkResource< VkSampler >				{ static constexpr bool	 value = true; };
	template <>  struct IsVkResource< VkDescriptorPool >		{ static constexpr bool	 value = true; };
	template <>  struct IsVkResource< VkDescriptorSet >			{ static constexpr bool	 value = true; };
	template <>  struct IsVkResource< VkFramebuffer >			{ static constexpr bool	 value = true; };
	template <>  struct IsVkResource< VkCommandPool >			{ static constexpr bool	 value = true; };
	template <>  struct IsVkResource< VkSwapchainKHR >			{ static constexpr bool	 value = true; };

}	// VTC
