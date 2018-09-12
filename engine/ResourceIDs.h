// Copyright (c)  Zhirnov Andrey. For more information see 'LICENSE.txt'

#pragma once

#include "engine/Common.h"

namespace VTC
{

	using VkResourceID_t = uint64_t;
	using ResourceID_t = uint32_t; // not a real vulkan handle, just a index in array

	enum class InstanceID : ResourceID_t {};
	enum class PhysicalDeviceID : ResourceID_t {};
	enum class DeviceID : ResourceID_t {};
	enum class QueueID : ResourceID_t {};
	enum class SemaphoreID : ResourceID_t {};
	enum class CommandBufferID : ResourceID_t {};
	enum class FenceID : ResourceID_t {};
	enum class DeviceMemoryID : ResourceID_t {};
	enum class BufferID : ResourceID_t {};
	enum class ImageID : ResourceID_t {};
	enum class EventID : ResourceID_t {};
	enum class QueryPoolID : ResourceID_t {};
	enum class BufferViewID : ResourceID_t {};
	enum class ImageViewID : ResourceID_t {};
	enum class ShaderModuleID : ResourceID_t {};
	enum class PipelineCacheID : ResourceID_t {};
	enum class PipelineLayoutID : ResourceID_t {};
	enum class RenderPassID : ResourceID_t {};
	enum class PipelineID : ResourceID_t {};
	enum class DescriptorSetLayoutID : ResourceID_t {};
	enum class SamplerID : ResourceID_t {};
	enum class DescriptorPoolID : ResourceID_t {};
	enum class DescriptorSetID : ResourceID_t {};
	enum class FramebufferID : ResourceID_t {};
	enum class CommandPoolID : ResourceID_t {};
	enum class SwapchainKHRID : ResourceID_t {};
	//enum class SurfaceKHRID : ResourceID_t {};
	
	enum class ObjectID : size_t {};
	enum class DataID : uint64_t {};


	template <typename ID>  struct _ObjInfo;
	
	template <>  struct _ObjInfo< InstanceID >				{ static constexpr uint	 index = 0;		using vktype = VkInstance; };
	template <>  struct _ObjInfo< PhysicalDeviceID >		{ static constexpr uint	 index = 1;		using vktype = VkPhysicalDevice; };
	template <>  struct _ObjInfo< DeviceID >				{ static constexpr uint	 index = 2;		using vktype = VkDevice; };
	template <>  struct _ObjInfo< QueueID >					{ static constexpr uint	 index = 3;		using vktype = VkQueue; };
	template <>  struct _ObjInfo< SemaphoreID >				{ static constexpr uint	 index = 4;		using vktype = VkSemaphore; };
	template <>  struct _ObjInfo< CommandBufferID >			{ static constexpr uint	 index = 5;		using vktype = VkCommandBuffer; };
	template <>  struct _ObjInfo< FenceID >					{ static constexpr uint	 index = 6;		using vktype = VkFence; };
	template <>  struct _ObjInfo< DeviceMemoryID >			{ static constexpr uint	 index = 7;		using vktype = VkDeviceMemory; };
	template <>  struct _ObjInfo< BufferID >				{ static constexpr uint	 index = 8;		using vktype = VkBuffer; };
	template <>  struct _ObjInfo< ImageID >					{ static constexpr uint	 index = 9;		using vktype = VkImage; };
	template <>  struct _ObjInfo< EventID >					{ static constexpr uint	 index = 10;	using vktype = VkEvent; };
	template <>  struct _ObjInfo< QueryPoolID >				{ static constexpr uint	 index = 11;	using vktype = VkQueryPool; };
	template <>  struct _ObjInfo< BufferViewID >			{ static constexpr uint	 index = 12;	using vktype = VkBufferView; };
	template <>  struct _ObjInfo< ImageViewID >				{ static constexpr uint	 index = 13;	using vktype = VkImageView; };
	template <>  struct _ObjInfo< ShaderModuleID >			{ static constexpr uint	 index = 14;	using vktype = VkShaderModule; };
	template <>  struct _ObjInfo< PipelineCacheID >			{ static constexpr uint	 index = 15;	using vktype = VkPipelineCache; };
	template <>  struct _ObjInfo< PipelineLayoutID >		{ static constexpr uint	 index = 16;	using vktype = VkPipelineLayout; };
	template <>  struct _ObjInfo< RenderPassID >			{ static constexpr uint	 index = 17;	using vktype = VkRenderPass; };
	template <>  struct _ObjInfo< PipelineID >				{ static constexpr uint	 index = 18;	using vktype = VkPipeline; };
	template <>  struct _ObjInfo< DescriptorSetLayoutID >	{ static constexpr uint	 index = 19;	using vktype = VkDescriptorSetLayout; };
	template <>  struct _ObjInfo< SamplerID >				{ static constexpr uint	 index = 20;	using vktype = VkSampler; };
	template <>  struct _ObjInfo< DescriptorPoolID >		{ static constexpr uint	 index = 21;	using vktype = VkDescriptorPool; };
	template <>  struct _ObjInfo< DescriptorSetID >			{ static constexpr uint	 index = 22;	using vktype = VkDescriptorSet; };
	template <>  struct _ObjInfo< FramebufferID >			{ static constexpr uint	 index = 23;	using vktype = VkFramebuffer; };
	template <>  struct _ObjInfo< CommandPoolID >			{ static constexpr uint	 index = 24;	using vktype = VkCommandPool; };
	template <>  struct _ObjInfo< SwapchainKHRID >			{ static constexpr uint	 index = 25;	using vktype = VkSwapchainKHR; };
	//template <>  struct _ObjInfo< SurfaceKHRID >			{ static constexpr uint	 index = 26;	using vktype = VkSurfaceKHR; };
	
}	// VTC
