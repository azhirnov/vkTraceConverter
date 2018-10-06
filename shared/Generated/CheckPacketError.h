// auto-generated file

ENABLE_ENUM_CHECKS();
switch ( iter->packet_id )
{
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalImageFormatPropertiesNV : {
		auto&  packet = iter.Cast< packet_vkGetPhysicalDeviceExternalImageFormatPropertiesNV >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkCmdDrawIndirectCountAMD : break;
	case VKTRACE_TPI_VK_vkCmdDrawIndexedIndirectCountAMD : break;
	case VKTRACE_TPI_VK_vkCreateDebugReportCallbackEXT : {
		auto&  packet = iter.Cast< packet_vkCreateDebugReportCallbackEXT >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDestroyDebugReportCallbackEXT : break;
	case VKTRACE_TPI_VK_vkDebugReportMessageEXT : break;
	case VKTRACE_TPI_VK_vkDebugMarkerSetObjectTagEXT : {
		auto&  packet = iter.Cast< packet_vkDebugMarkerSetObjectTagEXT >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDebugMarkerSetObjectNameEXT : {
		auto&  packet = iter.Cast< packet_vkDebugMarkerSetObjectNameEXT >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkCmdDebugMarkerBeginEXT : break;
	case VKTRACE_TPI_VK_vkCmdDebugMarkerEndEXT : break;
	case VKTRACE_TPI_VK_vkCmdDebugMarkerInsertEXT : break;
	case VKTRACE_TPI_VK_vkCreateInstance : {
		auto&  packet = iter.Cast< packet_vkCreateInstance >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDestroyInstance : break;
	case VKTRACE_TPI_VK_vkEnumeratePhysicalDevices : {
		auto&  packet = iter.Cast< packet_vkEnumeratePhysicalDevices >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceFeatures : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceFormatProperties : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceImageFormatProperties : {
		auto&  packet = iter.Cast< packet_vkGetPhysicalDeviceImageFormatProperties >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceProperties : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceQueueFamilyProperties : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceMemoryProperties : break;
	case VKTRACE_TPI_VK_vkGetInstanceProcAddr : break;
	case VKTRACE_TPI_VK_vkGetDeviceProcAddr : break;
	case VKTRACE_TPI_VK_vkCreateDevice : {
		auto&  packet = iter.Cast< packet_vkCreateDevice >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDestroyDevice : break;
	case VKTRACE_TPI_VK_vkEnumerateInstanceExtensionProperties : {
		auto&  packet = iter.Cast< packet_vkEnumerateInstanceExtensionProperties >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkEnumerateDeviceExtensionProperties : {
		auto&  packet = iter.Cast< packet_vkEnumerateDeviceExtensionProperties >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkEnumerateInstanceLayerProperties : {
		auto&  packet = iter.Cast< packet_vkEnumerateInstanceLayerProperties >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkEnumerateDeviceLayerProperties : {
		auto&  packet = iter.Cast< packet_vkEnumerateDeviceLayerProperties >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetDeviceQueue : break;
	case VKTRACE_TPI_VK_vkQueueSubmit : {
		auto&  packet = iter.Cast< packet_vkQueueSubmit >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkQueueWaitIdle : {
		auto&  packet = iter.Cast< packet_vkQueueWaitIdle >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDeviceWaitIdle : {
		auto&  packet = iter.Cast< packet_vkDeviceWaitIdle >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkAllocateMemory : {
		auto&  packet = iter.Cast< packet_vkAllocateMemory >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkFreeMemory : break;
	case VKTRACE_TPI_VK_vkMapMemory : {
		auto&  packet = iter.Cast< packet_vkMapMemory >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkUnmapMemory : break;
	case VKTRACE_TPI_VK_vkFlushMappedMemoryRanges : {
		auto&  packet = iter.Cast< packet_vkFlushMappedMemoryRanges >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkInvalidateMappedMemoryRanges : {
		auto&  packet = iter.Cast< packet_vkInvalidateMappedMemoryRanges >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetDeviceMemoryCommitment : break;
	case VKTRACE_TPI_VK_vkBindBufferMemory : {
		auto&  packet = iter.Cast< packet_vkBindBufferMemory >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkBindImageMemory : {
		auto&  packet = iter.Cast< packet_vkBindImageMemory >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetBufferMemoryRequirements : break;
	case VKTRACE_TPI_VK_vkGetImageMemoryRequirements : break;
	case VKTRACE_TPI_VK_vkGetImageSparseMemoryRequirements : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSparseImageFormatProperties : break;
	case VKTRACE_TPI_VK_vkQueueBindSparse : {
		auto&  packet = iter.Cast< packet_vkQueueBindSparse >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkCreateFence : {
		auto&  packet = iter.Cast< packet_vkCreateFence >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDestroyFence : break;
	case VKTRACE_TPI_VK_vkResetFences : {
		auto&  packet = iter.Cast< packet_vkResetFences >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetFenceStatus : {
		auto&  packet = iter.Cast< packet_vkGetFenceStatus >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkWaitForFences : {
		auto&  packet = iter.Cast< packet_vkWaitForFences >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkCreateSemaphore : {
		auto&  packet = iter.Cast< packet_vkCreateSemaphore >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDestroySemaphore : break;
	case VKTRACE_TPI_VK_vkCreateEvent : {
		auto&  packet = iter.Cast< packet_vkCreateEvent >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDestroyEvent : break;
	case VKTRACE_TPI_VK_vkGetEventStatus : {
		auto&  packet = iter.Cast< packet_vkGetEventStatus >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkSetEvent : {
		auto&  packet = iter.Cast< packet_vkSetEvent >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkResetEvent : {
		auto&  packet = iter.Cast< packet_vkResetEvent >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkCreateQueryPool : {
		auto&  packet = iter.Cast< packet_vkCreateQueryPool >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDestroyQueryPool : break;
	case VKTRACE_TPI_VK_vkGetQueryPoolResults : {
		auto&  packet = iter.Cast< packet_vkGetQueryPoolResults >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkCreateBuffer : {
		auto&  packet = iter.Cast< packet_vkCreateBuffer >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDestroyBuffer : break;
	case VKTRACE_TPI_VK_vkCreateBufferView : {
		auto&  packet = iter.Cast< packet_vkCreateBufferView >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDestroyBufferView : break;
	case VKTRACE_TPI_VK_vkCreateImage : {
		auto&  packet = iter.Cast< packet_vkCreateImage >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDestroyImage : break;
	case VKTRACE_TPI_VK_vkGetImageSubresourceLayout : break;
	case VKTRACE_TPI_VK_vkCreateImageView : {
		auto&  packet = iter.Cast< packet_vkCreateImageView >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDestroyImageView : break;
	case VKTRACE_TPI_VK_vkCreateShaderModule : {
		auto&  packet = iter.Cast< packet_vkCreateShaderModule >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDestroyShaderModule : break;
	case VKTRACE_TPI_VK_vkCreatePipelineCache : {
		auto&  packet = iter.Cast< packet_vkCreatePipelineCache >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDestroyPipelineCache : break;
	case VKTRACE_TPI_VK_vkGetPipelineCacheData : {
		auto&  packet = iter.Cast< packet_vkGetPipelineCacheData >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkMergePipelineCaches : {
		auto&  packet = iter.Cast< packet_vkMergePipelineCaches >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkCreateGraphicsPipelines : {
		auto&  packet = iter.Cast< packet_vkCreateGraphicsPipelines >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkCreateComputePipelines : {
		auto&  packet = iter.Cast< packet_vkCreateComputePipelines >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDestroyPipeline : break;
	case VKTRACE_TPI_VK_vkCreatePipelineLayout : {
		auto&  packet = iter.Cast< packet_vkCreatePipelineLayout >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDestroyPipelineLayout : break;
	case VKTRACE_TPI_VK_vkCreateSampler : {
		auto&  packet = iter.Cast< packet_vkCreateSampler >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDestroySampler : break;
	case VKTRACE_TPI_VK_vkCreateDescriptorSetLayout : {
		auto&  packet = iter.Cast< packet_vkCreateDescriptorSetLayout >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDestroyDescriptorSetLayout : break;
	case VKTRACE_TPI_VK_vkCreateDescriptorPool : {
		auto&  packet = iter.Cast< packet_vkCreateDescriptorPool >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDestroyDescriptorPool : break;
	case VKTRACE_TPI_VK_vkResetDescriptorPool : {
		auto&  packet = iter.Cast< packet_vkResetDescriptorPool >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkAllocateDescriptorSets : {
		auto&  packet = iter.Cast< packet_vkAllocateDescriptorSets >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkFreeDescriptorSets : {
		auto&  packet = iter.Cast< packet_vkFreeDescriptorSets >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkUpdateDescriptorSets : break;
	case VKTRACE_TPI_VK_vkCreateFramebuffer : {
		auto&  packet = iter.Cast< packet_vkCreateFramebuffer >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDestroyFramebuffer : break;
	case VKTRACE_TPI_VK_vkCreateRenderPass : {
		auto&  packet = iter.Cast< packet_vkCreateRenderPass >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDestroyRenderPass : break;
	case VKTRACE_TPI_VK_vkGetRenderAreaGranularity : break;
	case VKTRACE_TPI_VK_vkCreateCommandPool : {
		auto&  packet = iter.Cast< packet_vkCreateCommandPool >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDestroyCommandPool : break;
	case VKTRACE_TPI_VK_vkResetCommandPool : {
		auto&  packet = iter.Cast< packet_vkResetCommandPool >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkAllocateCommandBuffers : {
		auto&  packet = iter.Cast< packet_vkAllocateCommandBuffers >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkFreeCommandBuffers : break;
	case VKTRACE_TPI_VK_vkBeginCommandBuffer : {
		auto&  packet = iter.Cast< packet_vkBeginCommandBuffer >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkEndCommandBuffer : {
		auto&  packet = iter.Cast< packet_vkEndCommandBuffer >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkResetCommandBuffer : {
		auto&  packet = iter.Cast< packet_vkResetCommandBuffer >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkCmdBindPipeline : break;
	case VKTRACE_TPI_VK_vkCmdSetViewport : break;
	case VKTRACE_TPI_VK_vkCmdSetScissor : break;
	case VKTRACE_TPI_VK_vkCmdSetLineWidth : break;
	case VKTRACE_TPI_VK_vkCmdSetDepthBias : break;
	case VKTRACE_TPI_VK_vkCmdSetBlendConstants : break;
	case VKTRACE_TPI_VK_vkCmdSetDepthBounds : break;
	case VKTRACE_TPI_VK_vkCmdSetStencilCompareMask : break;
	case VKTRACE_TPI_VK_vkCmdSetStencilWriteMask : break;
	case VKTRACE_TPI_VK_vkCmdSetStencilReference : break;
	case VKTRACE_TPI_VK_vkCmdBindDescriptorSets : break;
	case VKTRACE_TPI_VK_vkCmdBindIndexBuffer : break;
	case VKTRACE_TPI_VK_vkCmdBindVertexBuffers : break;
	case VKTRACE_TPI_VK_vkCmdDraw : break;
	case VKTRACE_TPI_VK_vkCmdDrawIndexed : break;
	case VKTRACE_TPI_VK_vkCmdDrawIndirect : break;
	case VKTRACE_TPI_VK_vkCmdDrawIndexedIndirect : break;
	case VKTRACE_TPI_VK_vkCmdDispatch : break;
	case VKTRACE_TPI_VK_vkCmdDispatchIndirect : break;
	case VKTRACE_TPI_VK_vkCmdCopyBuffer : break;
	case VKTRACE_TPI_VK_vkCmdCopyImage : break;
	case VKTRACE_TPI_VK_vkCmdBlitImage : break;
	case VKTRACE_TPI_VK_vkCmdCopyBufferToImage : break;
	case VKTRACE_TPI_VK_vkCmdCopyImageToBuffer : break;
	case VKTRACE_TPI_VK_vkCmdUpdateBuffer : break;
	case VKTRACE_TPI_VK_vkCmdFillBuffer : break;
	case VKTRACE_TPI_VK_vkCmdClearColorImage : break;
	case VKTRACE_TPI_VK_vkCmdClearDepthStencilImage : break;
	case VKTRACE_TPI_VK_vkCmdClearAttachments : break;
	case VKTRACE_TPI_VK_vkCmdResolveImage : break;
	case VKTRACE_TPI_VK_vkCmdSetEvent : break;
	case VKTRACE_TPI_VK_vkCmdResetEvent : break;
	case VKTRACE_TPI_VK_vkCmdWaitEvents : break;
	case VKTRACE_TPI_VK_vkCmdPipelineBarrier : break;
	case VKTRACE_TPI_VK_vkCmdBeginQuery : break;
	case VKTRACE_TPI_VK_vkCmdEndQuery : break;
	case VKTRACE_TPI_VK_vkCmdResetQueryPool : break;
	case VKTRACE_TPI_VK_vkCmdWriteTimestamp : break;
	case VKTRACE_TPI_VK_vkCmdCopyQueryPoolResults : break;
	case VKTRACE_TPI_VK_vkCmdPushConstants : break;
	case VKTRACE_TPI_VK_vkCmdBeginRenderPass : break;
	case VKTRACE_TPI_VK_vkCmdNextSubpass : break;
	case VKTRACE_TPI_VK_vkCmdEndRenderPass : break;
	case VKTRACE_TPI_VK_vkCmdExecuteCommands : break;
	case VKTRACE_TPI_VK_vkDestroySurfaceKHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceSupportKHR : {
		auto&  packet = iter.Cast< packet_vkGetPhysicalDeviceSurfaceSupportKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceCapabilitiesKHR : {
		auto&  packet = iter.Cast< packet_vkGetPhysicalDeviceSurfaceCapabilitiesKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceFormatsKHR : {
		auto&  packet = iter.Cast< packet_vkGetPhysicalDeviceSurfaceFormatsKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfacePresentModesKHR : {
		auto&  packet = iter.Cast< packet_vkGetPhysicalDeviceSurfacePresentModesKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkCreateSwapchainKHR : {
		auto&  packet = iter.Cast< packet_vkCreateSwapchainKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDestroySwapchainKHR : break;
	case VKTRACE_TPI_VK_vkGetSwapchainImagesKHR : {
		auto&  packet = iter.Cast< packet_vkGetSwapchainImagesKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkAcquireNextImageKHR : {
		auto&  packet = iter.Cast< packet_vkAcquireNextImageKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkQueuePresentKHR : {
		auto&  packet = iter.Cast< packet_vkQueuePresentKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkCreateSharedSwapchainsKHR : {
		auto&  packet = iter.Cast< packet_vkCreateSharedSwapchainsKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkCreateWin32SurfaceKHR : {
		auto&  packet = iter.Cast< packet_vkCreateWin32SurfaceKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceWin32PresentationSupportKHR : break;
	case VKTRACE_TPI_VK_vkCreateXlibSurfaceKHR : {
		auto&  packet = iter.Cast< packet_vkCreateXlibSurfaceKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceXlibPresentationSupportKHR : break;
	case VKTRACE_TPI_VK_vkCreateXcbSurfaceKHR : {
		auto&  packet = iter.Cast< packet_vkCreateXcbSurfaceKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceXcbPresentationSupportKHR : break;
	case VKTRACE_TPI_VK_vkCreateAndroidSurfaceKHR : {
		auto&  packet = iter.Cast< packet_vkCreateAndroidSurfaceKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetMemoryWin32HandleNV : {
		auto&  packet = iter.Cast< packet_vkGetMemoryWin32HandleNV >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkCreateDescriptorUpdateTemplateKHR : {
		auto&  packet = iter.Cast< packet_vkCreateDescriptorUpdateTemplateKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDestroyDescriptorUpdateTemplateKHR : break;
	case VKTRACE_TPI_VK_vkUpdateDescriptorSetWithTemplateKHR : break;
	case VKTRACE_TPI_VK_vkCmdPushDescriptorSetWithTemplateKHR : break;
	case VKTRACE_TPI_VK_vkCreateWaylandSurfaceKHR : {
		auto&  packet = iter.Cast< packet_vkCreateWaylandSurfaceKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceWaylandPresentationSupportKHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceFeatures2KHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceProperties2KHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceFormatProperties2KHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceImageFormatProperties2KHR : {
		auto&  packet = iter.Cast< packet_vkGetPhysicalDeviceImageFormatProperties2KHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceQueueFamilyProperties2KHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceMemoryProperties2KHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSparseImageFormatProperties2KHR : break;
	case VKTRACE_TPI_VK_vkGetImageMemoryRequirements2KHR : break;
	case VKTRACE_TPI_VK_vkGetBufferMemoryRequirements2KHR : break;
	case VKTRACE_TPI_VK_vkGetImageSparseMemoryRequirements2KHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceCapabilities2KHR : {
		auto&  packet = iter.Cast< packet_vkGetPhysicalDeviceSurfaceCapabilities2KHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceFormats2KHR : {
		auto&  packet = iter.Cast< packet_vkGetPhysicalDeviceSurfaceFormats2KHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceDisplayPropertiesKHR : {
		auto&  packet = iter.Cast< packet_vkGetPhysicalDeviceDisplayPropertiesKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceDisplayPlanePropertiesKHR : {
		auto&  packet = iter.Cast< packet_vkGetPhysicalDeviceDisplayPlanePropertiesKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetDisplayModePropertiesKHR : {
		auto&  packet = iter.Cast< packet_vkGetDisplayModePropertiesKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkCreateDisplayModeKHR : {
		auto&  packet = iter.Cast< packet_vkCreateDisplayModeKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetDisplayPlaneCapabilitiesKHR : {
		auto&  packet = iter.Cast< packet_vkGetDisplayPlaneCapabilitiesKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkCreateDisplayPlaneSurfaceKHR : {
		auto&  packet = iter.Cast< packet_vkCreateDisplayPlaneSurfaceKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkTrimCommandPoolKHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalBufferPropertiesKHR : break;
	case VKTRACE_TPI_VK_vkGetMemoryFdKHR : {
		auto&  packet = iter.Cast< packet_vkGetMemoryFdKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetMemoryFdPropertiesKHR : {
		auto&  packet = iter.Cast< packet_vkGetMemoryFdPropertiesKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR : break;
	case VKTRACE_TPI_VK_vkImportSemaphoreFdKHR : {
		auto&  packet = iter.Cast< packet_vkImportSemaphoreFdKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetSemaphoreFdKHR : {
		auto&  packet = iter.Cast< packet_vkGetSemaphoreFdKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkCmdPushDescriptorSetKHR : break;
	case VKTRACE_TPI_VK_vkGetSwapchainStatusKHR : {
		auto&  packet = iter.Cast< packet_vkGetSwapchainStatusKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalFencePropertiesKHR : break;
	case VKTRACE_TPI_VK_vkBindBufferMemory2KHR : {
		auto&  packet = iter.Cast< packet_vkBindBufferMemory2KHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkBindImageMemory2KHR : {
		auto&  packet = iter.Cast< packet_vkBindImageMemory2KHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkCmdProcessCommandsNVX : break;
	case VKTRACE_TPI_VK_vkCmdReserveSpaceForCommandsNVX : break;
	case VKTRACE_TPI_VK_vkCreateIndirectCommandsLayoutNVX : {
		auto&  packet = iter.Cast< packet_vkCreateIndirectCommandsLayoutNVX >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDestroyIndirectCommandsLayoutNVX : break;
	case VKTRACE_TPI_VK_vkCreateObjectTableNVX : {
		auto&  packet = iter.Cast< packet_vkCreateObjectTableNVX >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDestroyObjectTableNVX : break;
	case VKTRACE_TPI_VK_vkRegisterObjectsNVX : {
		auto&  packet = iter.Cast< packet_vkRegisterObjectsNVX >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkUnregisterObjectsNVX : {
		auto&  packet = iter.Cast< packet_vkUnregisterObjectsNVX >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX : break;
	case VKTRACE_TPI_VK_vkCmdSetViewportWScalingNV : break;
	case VKTRACE_TPI_VK_vkReleaseDisplayEXT : {
		auto&  packet = iter.Cast< packet_vkReleaseDisplayEXT >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceCapabilities2EXT : {
		auto&  packet = iter.Cast< packet_vkGetPhysicalDeviceSurfaceCapabilities2EXT >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetRefreshCycleDurationGOOGLE : {
		auto&  packet = iter.Cast< packet_vkGetRefreshCycleDurationGOOGLE >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetPastPresentationTimingGOOGLE : {
		auto&  packet = iter.Cast< packet_vkGetPastPresentationTimingGOOGLE >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkCmdSetDiscardRectangleEXT : break;
	case VKTRACE_TPI_VK_vkSetHdrMetadataEXT : break;
	case VKTRACE_TPI_VK_vkAcquireXlibDisplayEXT : {
		auto&  packet = iter.Cast< packet_vkAcquireXlibDisplayEXT >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetRandROutputDisplayEXT : {
		auto&  packet = iter.Cast< packet_vkGetRandROutputDisplayEXT >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDisplayPowerControlEXT : {
		auto&  packet = iter.Cast< packet_vkDisplayPowerControlEXT >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkRegisterDeviceEventEXT : {
		auto&  packet = iter.Cast< packet_vkRegisterDeviceEventEXT >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkRegisterDisplayEventEXT : {
		auto&  packet = iter.Cast< packet_vkRegisterDisplayEventEXT >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetSwapchainCounterEXT : {
		auto&  packet = iter.Cast< packet_vkGetSwapchainCounterEXT >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkCmdSetSampleLocationsEXT : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceMultisamplePropertiesEXT : break;
	case VKTRACE_TPI_VK_vkCreateSamplerYcbcrConversionKHR : {
		auto&  packet = iter.Cast< packet_vkCreateSamplerYcbcrConversionKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDestroySamplerYcbcrConversionKHR : break;
	case VKTRACE_TPI_VK_vkGetDisplayPlaneSupportedDisplaysKHR : {
		auto&  packet = iter.Cast< packet_vkGetDisplayPlaneSupportedDisplaysKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkImportFenceFdKHR : {
		auto&  packet = iter.Cast< packet_vkImportFenceFdKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetFenceFdKHR : {
		auto&  packet = iter.Cast< packet_vkGetFenceFdKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkImportFenceWin32HandleKHR : {
		auto&  packet = iter.Cast< packet_vkImportFenceWin32HandleKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetFenceWin32HandleKHR : {
		auto&  packet = iter.Cast< packet_vkGetFenceWin32HandleKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetMemoryWin32HandleKHR : {
		auto&  packet = iter.Cast< packet_vkGetMemoryWin32HandleKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetMemoryWin32HandlePropertiesKHR : {
		auto&  packet = iter.Cast< packet_vkGetMemoryWin32HandlePropertiesKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkImportSemaphoreWin32HandleKHR : {
		auto&  packet = iter.Cast< packet_vkImportSemaphoreWin32HandleKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetSemaphoreWin32HandleKHR : {
		auto&  packet = iter.Cast< packet_vkGetSemaphoreWin32HandleKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetMemoryHostPointerPropertiesEXT : {
		auto&  packet = iter.Cast< packet_vkGetMemoryHostPointerPropertiesEXT >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkCreateValidationCacheEXT : {
		auto&  packet = iter.Cast< packet_vkCreateValidationCacheEXT >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDestroyValidationCacheEXT : break;
	case VKTRACE_TPI_VK_vkMergeValidationCachesEXT : {
		auto&  packet = iter.Cast< packet_vkMergeValidationCachesEXT >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetValidationCacheDataEXT : {
		auto&  packet = iter.Cast< packet_vkGetValidationCacheDataEXT >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetShaderInfoAMD : {
		auto&  packet = iter.Cast< packet_vkGetShaderInfoAMD >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetDeviceQueue2 : break;
	case VKTRACE_TPI_VK_vkGetDescriptorSetLayoutSupport : break;
	case VKTRACE_TPI_VK_vkGetDeviceGroupPresentCapabilitiesKHR : {
		auto&  packet = iter.Cast< packet_vkGetDeviceGroupPresentCapabilitiesKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetDeviceGroupSurfacePresentModesKHR : {
		auto&  packet = iter.Cast< packet_vkGetDeviceGroupSurfacePresentModesKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetPhysicalDevicePresentRectanglesKHR : {
		auto&  packet = iter.Cast< packet_vkGetPhysicalDevicePresentRectanglesKHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkAcquireNextImage2KHR : {
		auto&  packet = iter.Cast< packet_vkAcquireNextImage2KHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkBindBufferMemory2 : {
		auto&  packet = iter.Cast< packet_vkBindBufferMemory2 >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkBindImageMemory2 : {
		auto&  packet = iter.Cast< packet_vkBindImageMemory2 >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetDeviceGroupPeerMemoryFeatures : break;
	case VKTRACE_TPI_VK_vkCmdSetDeviceMask : break;
	case VKTRACE_TPI_VK_vkCmdDispatchBase : break;
	case VKTRACE_TPI_VK_vkEnumeratePhysicalDeviceGroups : {
		auto&  packet = iter.Cast< packet_vkEnumeratePhysicalDeviceGroups >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetImageMemoryRequirements2 : break;
	case VKTRACE_TPI_VK_vkGetBufferMemoryRequirements2 : break;
	case VKTRACE_TPI_VK_vkGetImageSparseMemoryRequirements2 : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceFeatures2 : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceProperties2 : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceFormatProperties2 : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceImageFormatProperties2 : {
		auto&  packet = iter.Cast< packet_vkGetPhysicalDeviceImageFormatProperties2 >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceQueueFamilyProperties2 : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceMemoryProperties2 : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSparseImageFormatProperties2 : break;
	case VKTRACE_TPI_VK_vkTrimCommandPool : break;
	case VKTRACE_TPI_VK_vkCreateSamplerYcbcrConversion : {
		auto&  packet = iter.Cast< packet_vkCreateSamplerYcbcrConversion >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDestroySamplerYcbcrConversion : break;
	case VKTRACE_TPI_VK_vkCreateDescriptorUpdateTemplate : {
		auto&  packet = iter.Cast< packet_vkCreateDescriptorUpdateTemplate >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkDestroyDescriptorUpdateTemplate : break;
	case VKTRACE_TPI_VK_vkUpdateDescriptorSetWithTemplate : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalBufferProperties : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalFenceProperties : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalSemaphoreProperties : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceDisplayProperties2KHR : {
		auto&  packet = iter.Cast< packet_vkGetPhysicalDeviceDisplayProperties2KHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceDisplayPlaneProperties2KHR : {
		auto&  packet = iter.Cast< packet_vkGetPhysicalDeviceDisplayPlaneProperties2KHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetDisplayModeProperties2KHR : {
		auto&  packet = iter.Cast< packet_vkGetDisplayModeProperties2KHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
	case VKTRACE_TPI_VK_vkGetDisplayPlaneCapabilities2KHR : {
		auto&  packet = iter.Cast< packet_vkGetDisplayPlaneCapabilities2KHR >();
		result = (packet.result == VK_SUCCESS);
		break;
	}
}
DISABLE_ENUM_CHECKS();
