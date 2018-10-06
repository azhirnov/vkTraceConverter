// auto-generated file

ENABLE_ENUM_CHECKS();
switch ( header->sType )
{
	case VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_BUFFER_CREATE_INFO : {
		VkExternalMemoryBufferCreateInfo const&  value = *BitCast<VkExternalMemoryBufferCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO : {
		VkSemaphoreCreateInfo const&  value = *BitCast<VkSemaphoreCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO : {
		VkDeviceCreateInfo const&  value = *BitCast<VkDeviceCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		for (uint a = 0; (value).pQueueCreateInfos and a < (value).queueCreateInfoCount; ++a) {
			if ( ((value).pQueueCreateInfos[a]).pNext )
				_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(((value).pQueueCreateInfos[a]).pNext), iter, frame_id );
		}
		break;
	}

	case VK_STRUCTURE_TYPE_EXTERNAL_IMAGE_FORMAT_PROPERTIES : {
		VkExternalImageFormatProperties const&  value = *BitCast<VkExternalImageFormatProperties const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_COARSE_SAMPLE_ORDER_STATE_CREATE_INFO_NV : {
		VkPipelineViewportCoarseSampleOrderStateCreateInfoNV const&  value = *BitCast<VkPipelineViewportCoarseSampleOrderStateCreateInfoNV const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_DOMAIN_ORIGIN_STATE_CREATE_INFO : {
		VkPipelineTessellationDomainOriginStateCreateInfo const&  value = *BitCast<VkPipelineTessellationDomainOriginStateCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_APPLICATION_INFO : {
		VkApplicationInfo const&  value = *BitCast<VkApplicationInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT : {
		VkDebugUtilsObjectNameInfoEXT const&  value = *BitCast<VkDebugUtilsObjectNameInfoEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO : {
		VkBufferViewCreateInfo const&  value = *BitCast<VkBufferViewCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID((value).buffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO : {
		VkInstanceCreateInfo const&  value = *BitCast<VkInstanceCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		if ( (value).pApplicationInfo ) {
			if ( (*(value).pApplicationInfo).pNext )
				_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((*(value).pApplicationInfo).pNext), iter, frame_id );
		}
		break;
	}

	case VK_STRUCTURE_TYPE_VALIDATION_CACHE_CREATE_INFO_EXT : {
		VkValidationCacheCreateInfoEXT const&  value = *BitCast<VkValidationCacheCreateInfoEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_MEMORY_BARRIER : {
		VkMemoryBarrier const&  value = *BitCast<VkMemoryBarrier const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_MEMORY_WIN32_HANDLE_PROPERTIES_KHR : {
		#ifdef VULKAN_WIN32_H_
		VkMemoryWin32HandlePropertiesKHR const&  value = *BitCast<VkMemoryWin32HandlePropertiesKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		#endif
		break;
	}

	case VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_USAGE_ANDROID : {
		#ifdef VULKAN_ANDROID_H_
		VkAndroidHardwareBufferUsageANDROID const&  value = *BitCast<VkAndroidHardwareBufferUsageANDROID const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		#endif
		break;
	}

	case VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO : {
		VkPipelineInputAssemblyStateCreateInfo const&  value = *BitCast<VkPipelineInputAssemblyStateCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO_KHR : {
		VkImageFormatListCreateInfoKHR const&  value = *BitCast<VkImageFormatListCreateInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DEVICE_EVENT_INFO_EXT : {
		VkDeviceEventInfoEXT const&  value = *BitCast<VkDeviceEventInfoEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE : {
		VkMappedMemoryRange const&  value = *BitCast<VkMappedMemoryRange const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, ResourceID((value).memory), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO : {
		VkDeviceQueueCreateInfo const&  value = *BitCast<VkDeviceQueueCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_SUBMIT_INFO : {
		VkSubmitInfo const&  value = *BitCast<VkSubmitInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		for (uint a = 0; (value).pWaitSemaphores and a < (value).waitSemaphoreCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT, ResourceID((value).pWaitSemaphores[a]), iter, frame_id, EResOp::Access );
		}
		for (uint a = 0; (value).pCommandBuffers and a < (value).commandBufferCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID((value).pCommandBuffers[a]), iter, frame_id, EResOp::Access );
		}
		for (uint a = 0; (value).pSignalSemaphores and a < (value).signalSemaphoreCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT, ResourceID((value).pSignalSemaphores[a]), iter, frame_id, EResOp::Access );
		}
		break;
	}

	case VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO : {
		VkPipelineDynamicStateCreateInfo const&  value = *BitCast<VkPipelineDynamicStateCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO : {
		VkImageViewCreateInfo const&  value = *BitCast<VkImageViewCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, ResourceID((value).image), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO : {
		VkPipelineTessellationStateCreateInfo const&  value = *BitCast<VkPipelineTessellationStateCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_IMPORT_MEMORY_HOST_POINTER_INFO_EXT : {
		VkImportMemoryHostPointerInfoEXT const&  value = *BitCast<VkImportMemoryHostPointerInfoEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO : {
		VkMemoryAllocateInfo const&  value = *BitCast<VkMemoryAllocateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_BIND_SPARSE_INFO : {
		VkBindSparseInfo const&  value = *BitCast<VkBindSparseInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		for (uint a = 0; (value).pWaitSemaphores and a < (value).waitSemaphoreCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT, ResourceID((value).pWaitSemaphores[a]), iter, frame_id, EResOp::Access );
		}
		for (uint a = 0; (value).pBufferBinds and a < (value).bufferBindCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID(((value).pBufferBinds[a]).buffer), iter, frame_id, EResOp::Access );
			for (uint b = 0; ((value).pBufferBinds[a]).pBinds and b < ((value).pBufferBinds[a]).bindCount; ++b) {
				_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, ResourceID((((value).pBufferBinds[a]).pBinds[b]).memory), iter, frame_id, EResOp::Access );
			}
		}
		for (uint a = 0; (value).pImageOpaqueBinds and a < (value).imageOpaqueBindCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, ResourceID(((value).pImageOpaqueBinds[a]).image), iter, frame_id, EResOp::Access );
			for (uint b = 0; ((value).pImageOpaqueBinds[a]).pBinds and b < ((value).pImageOpaqueBinds[a]).bindCount; ++b) {
				_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, ResourceID((((value).pImageOpaqueBinds[a]).pBinds[b]).memory), iter, frame_id, EResOp::Access );
			}
		}
		for (uint a = 0; (value).pImageBinds and a < (value).imageBindCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, ResourceID(((value).pImageBinds[a]).image), iter, frame_id, EResOp::Access );
			for (uint b = 0; ((value).pImageBinds[a]).pBinds and b < ((value).pImageBinds[a]).bindCount; ++b) {
				_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, ResourceID((((value).pImageBinds[a]).pBinds[b]).memory), iter, frame_id, EResOp::Access );
			}
		}
		for (uint a = 0; (value).pSignalSemaphores and a < (value).signalSemaphoreCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT, ResourceID((value).pSignalSemaphores[a]), iter, frame_id, EResOp::Access );
		}
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2 : {
		VkPhysicalDeviceImageFormatInfo2 const&  value = *BitCast<VkPhysicalDeviceImageFormatInfo2 const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_SEMAPHORE_GET_WIN32_HANDLE_INFO_KHR : {
		#ifdef VULKAN_WIN32_H_
		VkSemaphoreGetWin32HandleInfoKHR const&  value = *BitCast<VkSemaphoreGetWin32HandleInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT, ResourceID((value).semaphore), iter, frame_id, EResOp::Access );
		#endif
		break;
	}

	case VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO : {
		VkPipelineViewportStateCreateInfo const&  value = *BitCast<VkPipelineViewportStateCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO : {
		VkPipelineVertexInputStateCreateInfo const&  value = *BitCast<VkPipelineVertexInputStateCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_WIN32_HANDLE_INFO_KHR : {
		#ifdef VULKAN_WIN32_H_
		VkExportSemaphoreWin32HandleInfoKHR const&  value = *BitCast<VkExportSemaphoreWin32HandleInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		#endif
		break;
	}

	case VK_STRUCTURE_TYPE_ACQUIRE_NEXT_IMAGE_INFO_KHR : {
		VkAcquireNextImageInfoKHR const&  value = *BitCast<VkAcquireNextImageInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT, ResourceID((value).swapchain), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT, ResourceID((value).semaphore), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT, ResourceID((value).fence), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_PROPERTIES : {
		VkPhysicalDeviceProtectedMemoryProperties const&  value = *BitCast<VkPhysicalDeviceProtectedMemoryProperties const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_FENCE_CREATE_INFO : {
		VkFenceCreateInfo const&  value = *BitCast<VkFenceCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_EVENT_CREATE_INFO : {
		VkEventCreateInfo const&  value = *BitCast<VkEventCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO : {
		VkRenderPassBeginInfo const&  value = *BitCast<VkRenderPassBeginInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_RENDER_PASS_EXT, ResourceID((value).renderPass), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_FRAMEBUFFER_EXT, ResourceID((value).framebuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO : {
		VkQueryPoolCreateInfo const&  value = *BitCast<VkQueryPoolCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO : {
		VkBufferCreateInfo const&  value = *BitCast<VkBufferCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO : {
		VkImageCreateInfo const&  value = *BitCast<VkImageCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO : {
		VkPipelineMultisampleStateCreateInfo const&  value = *BitCast<VkPipelineMultisampleStateCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO : {
		VkShaderModuleCreateInfo const&  value = *BitCast<VkShaderModuleCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO_EXT : {
		VkDescriptorSetLayoutBindingFlagsCreateInfoEXT const&  value = *BitCast<VkDescriptorSetLayoutBindingFlagsCreateInfoEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO : {
		VkPipelineCacheCreateInfo const&  value = *BitCast<VkPipelineCacheCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DISPLAY_PLANE_INFO_2_KHR : {
		VkDisplayPlaneInfo2KHR const&  value = *BitCast<VkDisplayPlaneInfo2KHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DISPLAY_MODE_KHR_EXT, ResourceID((value).mode), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO : {
		VkPipelineShaderStageCreateInfo const&  value = *BitCast<VkPipelineShaderStageCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SHADER_MODULE_EXT, ResourceID((value).module), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_NV : {
		#ifdef VULKAN_WIN32_H_
		VkImportMemoryWin32HandleInfoNV const&  value = *BitCast<VkImportMemoryWin32HandleInfoNV const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		#endif
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_BUFFER_INFO : {
		VkPhysicalDeviceExternalBufferInfo const&  value = *BitCast<VkPhysicalDeviceExternalBufferInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO : {
		VkPipelineRasterizationStateCreateInfo const&  value = *BitCast<VkPipelineRasterizationStateCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_MEMORY_HOST_POINTER_PROPERTIES_EXT : {
		VkMemoryHostPointerPropertiesEXT const&  value = *BitCast<VkMemoryHostPointerPropertiesEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DEVICE_GENERATED_COMMANDS_FEATURES_NVX : {
		VkDeviceGeneratedCommandsFeaturesNVX const&  value = *BitCast<VkDeviceGeneratedCommandsFeaturesNVX const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PRESENT_TIMES_INFO_GOOGLE : {
		VkPresentTimesInfoGOOGLE const&  value = *BitCast<VkPresentTimesInfoGOOGLE const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO : {
		VkPipelineDepthStencilStateCreateInfo const&  value = *BitCast<VkPipelineDepthStencilStateCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR : {
		#ifdef VULKAN_ANDROID_H_
		VkAndroidSurfaceCreateInfoKHR const&  value = *BitCast<VkAndroidSurfaceCreateInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		#endif
		break;
	}

	case VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO : {
		VkCommandBufferInheritanceInfo const&  value = *BitCast<VkCommandBufferInheritanceInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_RENDER_PASS_EXT, ResourceID((value).renderPass), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_FRAMEBUFFER_EXT, ResourceID((value).framebuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO : {
		VkPipelineColorBlendStateCreateInfo const&  value = *BitCast<VkPipelineColorBlendStateCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_IMPORT_FENCE_FD_INFO_KHR : {
		VkImportFenceFdInfoKHR const&  value = *BitCast<VkImportFenceFdInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT, ResourceID((value).fence), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO : {
		VkGraphicsPipelineCreateInfo const&  value = *BitCast<VkGraphicsPipelineCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		for (uint a = 0; (value).pStages and a < (value).stageCount; ++a) {
			if ( ((value).pStages[a]).pNext )
				_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(((value).pStages[a]).pNext), iter, frame_id );
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SHADER_MODULE_EXT, ResourceID(((value).pStages[a]).module), iter, frame_id, EResOp::Access );
		}
		if ( (value).pVertexInputState ) {
			if ( (*(value).pVertexInputState).pNext )
				_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((*(value).pVertexInputState).pNext), iter, frame_id );
		}
		if ( (value).pInputAssemblyState ) {
			if ( (*(value).pInputAssemblyState).pNext )
				_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((*(value).pInputAssemblyState).pNext), iter, frame_id );
		}
		if ( (value).pTessellationState ) {
			if ( (*(value).pTessellationState).pNext )
				_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((*(value).pTessellationState).pNext), iter, frame_id );
		}
		if ( (value).pViewportState ) {
			if ( (*(value).pViewportState).pNext )
				_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((*(value).pViewportState).pNext), iter, frame_id );
		}
		if ( (value).pRasterizationState ) {
			if ( (*(value).pRasterizationState).pNext )
				_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((*(value).pRasterizationState).pNext), iter, frame_id );
		}
		if ( (value).pMultisampleState ) {
			if ( (*(value).pMultisampleState).pNext )
				_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((*(value).pMultisampleState).pNext), iter, frame_id );
		}
		if ( (value).pDepthStencilState ) {
			if ( (*(value).pDepthStencilState).pNext )
				_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((*(value).pDepthStencilState).pNext), iter, frame_id );
		}
		if ( (value).pColorBlendState ) {
			if ( (*(value).pColorBlendState).pNext )
				_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((*(value).pColorBlendState).pNext), iter, frame_id );
		}
		if ( (value).pDynamicState ) {
			if ( (*(value).pDynamicState).pNext )
				_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((*(value).pDynamicState).pNext), iter, frame_id );
		}
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_LAYOUT_EXT, ResourceID((value).layout), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_RENDER_PASS_EXT, ResourceID((value).renderPass), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_EXT, ResourceID((value).basePipelineHandle), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_INFO : {
		VkSamplerYcbcrConversionInfo const&  value = *BitCast<VkSamplerYcbcrConversionInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION_EXT, ResourceID((value).conversion), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO : {
		VkComputePipelineCreateInfo const&  value = *BitCast<VkComputePipelineCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_LAYOUT_EXT, ResourceID((value).layout), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_EXT, ResourceID((value).basePipelineHandle), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO : {
		VkPipelineLayoutCreateInfo const&  value = *BitCast<VkPipelineLayoutCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		for (uint a = 0; (value).pSetLayouts and a < (value).setLayoutCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT_EXT, ResourceID((value).pSetLayouts[a]), iter, frame_id, EResOp::Access );
		}
		break;
	}

	case VK_STRUCTURE_TYPE_DISPLAY_PLANE_PROPERTIES_2_KHR : {
		VkDisplayPlaneProperties2KHR const&  value = *BitCast<VkDisplayPlaneProperties2KHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DISPLAY_PRESENT_INFO_KHR : {
		VkDisplayPresentInfoKHR const&  value = *BitCast<VkDisplayPresentInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO : {
		VkSamplerCreateInfo const&  value = *BitCast<VkSamplerCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO : {
		VkDescriptorSetLayoutCreateInfo const&  value = *BitCast<VkDescriptorSetLayoutCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		for (uint a = 0; (value).pBindings and a < (value).bindingCount; ++a) {
			for (uint b = 0; ((value).pBindings[a]).pImmutableSamplers and b < ((value).pBindings[a]).descriptorCount; ++b) {
				_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_EXT, ResourceID(((value).pBindings[a]).pImmutableSamplers[b]), iter, frame_id, EResOp::Access );
			}
		}
		break;
	}

	case VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_NVX : {
		VkAccelerationStructureCreateInfoNVX const&  value = *BitCast<VkAccelerationStructureCreateInfoNVX const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		for (uint a = 0; (value).pGeometries and a < (value).geometryCount; ++a) {
			if ( ((value).pGeometries[a]).pNext )
				_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(((value).pGeometries[a]).pNext), iter, frame_id );
		}
		break;
	}

	case VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO : {
		VkDescriptorPoolCreateInfo const&  value = *BitCast<VkDescriptorPoolCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_IMAGE_MEMORY_REQUIREMENTS_INFO_2 : {
		VkImageMemoryRequirementsInfo2 const&  value = *BitCast<VkImageMemoryRequirementsInfo2 const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, ResourceID((value).image), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO : {
		VkDescriptorSetAllocateInfo const&  value = *BitCast<VkDescriptorSetAllocateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_POOL_EXT, ResourceID((value).descriptorPool), iter, frame_id, EResOp::Access );
		for (uint a = 0; (value).pSetLayouts and a < (value).descriptorSetCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT_EXT, ResourceID((value).pSetLayouts[a]), iter, frame_id, EResOp::Access );
		}
		break;
	}

	case VK_STRUCTURE_TYPE_EXPORT_MEMORY_WIN32_HANDLE_INFO_NV : {
		#ifdef VULKAN_WIN32_H_
		VkExportMemoryWin32HandleInfoNV const&  value = *BitCast<VkExportMemoryWin32HandleInfoNV const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		#endif
		break;
	}

	case VK_STRUCTURE_TYPE_HDR_METADATA_EXT : {
		VkHdrMetadataEXT const&  value = *BitCast<VkHdrMetadataEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_SEMAPHORE_INFO : {
		VkPhysicalDeviceExternalSemaphoreInfo const&  value = *BitCast<VkPhysicalDeviceExternalSemaphoreInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET : {
		VkWriteDescriptorSet const&  value = *BitCast<VkWriteDescriptorSet const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_EXT, ResourceID((value).dstSet), iter, frame_id, EResOp::Access );
		for (uint a = 0; (value).pImageInfo and a < (value).descriptorCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_EXT, ResourceID(((value).pImageInfo[a]).sampler), iter, frame_id, EResOp::Access );
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_VIEW_EXT, ResourceID(((value).pImageInfo[a]).imageView), iter, frame_id, EResOp::Access );
		}
		for (uint a = 0; (value).pBufferInfo and a < (value).descriptorCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID(((value).pBufferInfo[a]).buffer), iter, frame_id, EResOp::Access );
		}
		for (uint a = 0; (value).pTexelBufferView and a < (value).descriptorCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_VIEW_EXT, ResourceID((value).pTexelBufferView[a]), iter, frame_id, EResOp::Access );
		}
		break;
	}

	case VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET : {
		VkCopyDescriptorSet const&  value = *BitCast<VkCopyDescriptorSet const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_EXT, ResourceID((value).srcSet), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_EXT, ResourceID((value).dstSet), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLER_FILTER_MINMAX_PROPERTIES_EXT : {
		VkPhysicalDeviceSamplerFilterMinmaxPropertiesEXT const&  value = *BitCast<VkPhysicalDeviceSamplerFilterMinmaxPropertiesEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO : {
		VkFramebufferCreateInfo const&  value = *BitCast<VkFramebufferCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_RENDER_PASS_EXT, ResourceID((value).renderPass), iter, frame_id, EResOp::Access );
		for (uint a = 0; (value).pAttachments and a < (value).attachmentCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_VIEW_EXT, ResourceID((value).pAttachments[a]), iter, frame_id, EResOp::Access );
		}
		break;
	}

	case VK_STRUCTURE_TYPE_GEOMETRY_TRIANGLES_NVX : {
		VkGeometryTrianglesNVX const&  value = *BitCast<VkGeometryTrianglesNVX const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID((value).vertexData), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID((value).indexData), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID((value).transformData), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO : {
		VkRenderPassCreateInfo const&  value = *BitCast<VkRenderPassCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO : {
		VkCommandPoolCreateInfo const&  value = *BitCast<VkCommandPoolCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO : {
		VkCommandBufferAllocateInfo const&  value = *BitCast<VkCommandBufferAllocateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_POOL_EXT, ResourceID((value).commandPool), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO : {
		VkCommandBufferBeginInfo const&  value = *BitCast<VkCommandBufferBeginInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		if ( (value).pInheritanceInfo ) {
			if ( (*(value).pInheritanceInfo).pNext )
				_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((*(value).pInheritanceInfo).pNext), iter, frame_id );
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_RENDER_PASS_EXT, ResourceID((*(value).pInheritanceInfo).renderPass), iter, frame_id, EResOp::Access );
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_FRAMEBUFFER_EXT, ResourceID((*(value).pInheritanceInfo).framebuffer), iter, frame_id, EResOp::Access );
		}
		break;
	}

	case VK_STRUCTURE_TYPE_MIR_SURFACE_CREATE_INFO_KHR : {
		#ifdef VULKAN_MIR_H_
		VkMirSurfaceCreateInfoKHR const&  value = *BitCast<VkMirSurfaceCreateInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		#endif
		break;
	}

	case VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_LAYOUT_SUPPORT_EXT : {
		VkDescriptorSetVariableDescriptorCountLayoutSupportEXT const&  value = *BitCast<VkDescriptorSetVariableDescriptorCountLayoutSupportEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DEVICE_GENERATED_COMMANDS_LIMITS_NVX : {
		VkDeviceGeneratedCommandsLimitsNVX const&  value = *BitCast<VkDeviceGeneratedCommandsLimitsNVX const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER : {
		VkBufferMemoryBarrier const&  value = *BitCast<VkBufferMemoryBarrier const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID((value).buffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER : {
		VkImageMemoryBarrier const&  value = *BitCast<VkImageMemoryBarrier const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, ResourceID((value).image), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_TO_COLOR_STATE_CREATE_INFO_NV : {
		VkPipelineCoverageToColorStateCreateInfoNV const&  value = *BitCast<VkPipelineCoverageToColorStateCreateInfoNV const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_IMPORT_FENCE_WIN32_HANDLE_INFO_KHR : {
		#ifdef VULKAN_WIN32_H_
		VkImportFenceWin32HandleInfoKHR const&  value = *BitCast<VkImportFenceWin32HandleInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT, ResourceID((value).fence), iter, frame_id, EResOp::Access );
		#endif
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_POINT_CLIPPING_PROPERTIES : {
		VkPhysicalDevicePointClippingProperties const&  value = *BitCast<VkPhysicalDevicePointClippingProperties const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_PROPERTIES : {
		VkPhysicalDeviceSubgroupProperties const&  value = *BitCast<VkPhysicalDeviceSubgroupProperties const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO : {
		VkBindBufferMemoryInfo const&  value = *BitCast<VkBindBufferMemoryInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID((value).buffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, ResourceID((value).memory), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO : {
		VkBindImageMemoryInfo const&  value = *BitCast<VkBindImageMemoryInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, ResourceID((value).image), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, ResourceID((value).memory), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_SUBPASS_END_INFO_KHR : {
		VkSubpassEndInfoKHR const&  value = *BitCast<VkSubpassEndInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_16BIT_STORAGE_FEATURES : {
		VkPhysicalDevice16BitStorageFeatures const&  value = *BitCast<VkPhysicalDevice16BitStorageFeatures const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_MEMORY_DEDICATED_REQUIREMENTS : {
		VkMemoryDedicatedRequirements const&  value = *BitCast<VkMemoryDedicatedRequirements const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADING_RATE_IMAGE_PROPERTIES_NV : {
		VkPhysicalDeviceShadingRateImagePropertiesNV const&  value = *BitCast<VkPhysicalDeviceShadingRateImagePropertiesNV const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO : {
		VkMemoryDedicatedAllocateInfo const&  value = *BitCast<VkMemoryDedicatedAllocateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, ResourceID((value).image), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID((value).buffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO : {
		VkMemoryAllocateFlagsInfo const&  value = *BitCast<VkMemoryAllocateFlagsInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DEVICE_GROUP_RENDER_PASS_BEGIN_INFO : {
		VkDeviceGroupRenderPassBeginInfo const&  value = *BitCast<VkDeviceGroupRenderPassBeginInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DEVICE_GROUP_COMMAND_BUFFER_BEGIN_INFO : {
		VkDeviceGroupCommandBufferBeginInfo const&  value = *BitCast<VkDeviceGroupCommandBufferBeginInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DEVICE_GROUP_SUBMIT_INFO : {
		VkDeviceGroupSubmitInfo const&  value = *BitCast<VkDeviceGroupSubmitInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DEVICE_GROUP_BIND_SPARSE_INFO : {
		VkDeviceGroupBindSparseInfo const&  value = *BitCast<VkDeviceGroupBindSparseInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_DEVICE_GROUP_INFO : {
		VkBindBufferMemoryDeviceGroupInfo const&  value = *BitCast<VkBindBufferMemoryDeviceGroupInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_DEVICE_GROUP_INFO : {
		VkBindImageMemoryDeviceGroupInfo const&  value = *BitCast<VkBindImageMemoryDeviceGroupInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GROUP_PROPERTIES : {
		VkPhysicalDeviceGroupProperties const&  value = *BitCast<VkPhysicalDeviceGroupProperties const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		for (uint a = 0; (value).physicalDevices and a < VK_MAX_DEVICE_GROUP_SIZE; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID((value).physicalDevices[a]), iter, frame_id, EResOp::Access );
		}
		break;
	}

	case VK_STRUCTURE_TYPE_DEVICE_GROUP_DEVICE_CREATE_INFO : {
		VkDeviceGroupDeviceCreateInfo const&  value = *BitCast<VkDeviceGroupDeviceCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		for (uint a = 0; (value).pPhysicalDevices and a < (value).physicalDeviceCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID((value).pPhysicalDevices[a]), iter, frame_id, EResOp::Access );
		}
		break;
	}

	case VK_STRUCTURE_TYPE_SAMPLER_REDUCTION_MODE_CREATE_INFO_EXT : {
		VkSamplerReductionModeCreateInfoEXT const&  value = *BitCast<VkSamplerReductionModeCreateInfoEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_BUFFER_MEMORY_REQUIREMENTS_INFO_2 : {
		VkBufferMemoryRequirementsInfo2 const&  value = *BitCast<VkBufferMemoryRequirementsInfo2 const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID((value).buffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_IMAGE_SPARSE_MEMORY_REQUIREMENTS_INFO_2 : {
		VkImageSparseMemoryRequirementsInfo2 const&  value = *BitCast<VkImageSparseMemoryRequirementsInfo2 const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, ResourceID((value).image), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2_KHR : {
		VkAttachmentReference2KHR const&  value = *BitCast<VkAttachmentReference2KHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2 : {
		VkMemoryRequirements2 const&  value = *BitCast<VkMemoryRequirements2 const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_SUPPORT : {
		VkDescriptorSetLayoutSupport const&  value = *BitCast<VkDescriptorSetLayoutSupport const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_SPARSE_IMAGE_MEMORY_REQUIREMENTS_2 : {
		VkSparseImageMemoryRequirements2 const&  value = *BitCast<VkSparseImageMemoryRequirements2 const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2 : {
		VkPhysicalDeviceFeatures2 const&  value = *BitCast<VkPhysicalDeviceFeatures2 const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2 : {
		VkPhysicalDeviceProperties2 const&  value = *BitCast<VkPhysicalDeviceProperties2 const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2 : {
		VkFormatProperties2 const&  value = *BitCast<VkFormatProperties2 const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VARIABLE_POINTER_FEATURES : {
		VkPhysicalDeviceVariablePointerFeatures const&  value = *BitCast<VkPhysicalDeviceVariablePointerFeatures const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2 : {
		VkImageFormatProperties2 const&  value = *BitCast<VkImageFormatProperties2 const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2 : {
		VkQueueFamilyProperties2 const&  value = *BitCast<VkQueueFamilyProperties2 const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2 : {
		VkPhysicalDeviceMemoryProperties2 const&  value = *BitCast<VkPhysicalDeviceMemoryProperties2 const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_SPARSE_IMAGE_FORMAT_PROPERTIES_2 : {
		VkSparseImageFormatProperties2 const&  value = *BitCast<VkSparseImageFormatProperties2 const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SPARSE_IMAGE_FORMAT_INFO_2 : {
		VkPhysicalDeviceSparseImageFormatInfo2 const&  value = *BitCast<VkPhysicalDeviceSparseImageFormatInfo2 const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ASTC_DECODE_FEATURES_EXT : {
		VkPhysicalDeviceASTCDecodeFeaturesEXT const&  value = *BitCast<VkPhysicalDeviceASTCDecodeFeaturesEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_RENDER_PASS_INPUT_ATTACHMENT_ASPECT_CREATE_INFO : {
		VkRenderPassInputAttachmentAspectCreateInfo const&  value = *BitCast<VkRenderPassInputAttachmentAspectCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO : {
		VkImageViewUsageCreateInfo const&  value = *BitCast<VkImageViewUsageCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_RENDER_PASS_MULTIVIEW_CREATE_INFO : {
		VkRenderPassMultiviewCreateInfo const&  value = *BitCast<VkRenderPassMultiviewCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_FEATURES : {
		VkPhysicalDeviceMultiviewFeatures const&  value = *BitCast<VkPhysicalDeviceMultiviewFeatures const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DISPLAY_MODE_CREATE_INFO_KHR : {
		VkDisplayModeCreateInfoKHR const&  value = *BitCast<VkDisplayModeCreateInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PROPERTIES : {
		VkPhysicalDeviceMultiviewProperties const&  value = *BitCast<VkPhysicalDeviceMultiviewProperties const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_FEATURES : {
		VkPhysicalDeviceProtectedMemoryFeatures const&  value = *BitCast<VkPhysicalDeviceProtectedMemoryFeatures const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_RENDER_PASS_SAMPLE_LOCATIONS_BEGIN_INFO_EXT : {
		VkRenderPassSampleLocationsBeginInfoEXT const&  value = *BitCast<VkRenderPassSampleLocationsBeginInfoEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2 : {
		VkDeviceQueueInfo2 const&  value = *BitCast<VkDeviceQueueInfo2 const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PROTECTED_SUBMIT_INFO : {
		VkProtectedSubmitInfo const&  value = *BitCast<VkProtectedSubmitInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_CREATE_INFO : {
		VkSamplerYcbcrConversionCreateInfo const&  value = *BitCast<VkSamplerYcbcrConversionCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_BIND_IMAGE_PLANE_MEMORY_INFO : {
		VkBindImagePlaneMemoryInfo const&  value = *BitCast<VkBindImagePlaneMemoryInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_IMAGE_PLANE_MEMORY_REQUIREMENTS_INFO : {
		VkImagePlaneMemoryRequirementsInfo const&  value = *BitCast<VkImagePlaneMemoryRequirementsInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLER_YCBCR_CONVERSION_FEATURES : {
		VkPhysicalDeviceSamplerYcbcrConversionFeatures const&  value = *BitCast<VkPhysicalDeviceSamplerYcbcrConversionFeatures const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_IMAGE_FORMAT_PROPERTIES : {
		VkSamplerYcbcrConversionImageFormatProperties const&  value = *BitCast<VkSamplerYcbcrConversionImageFormatProperties const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_CREATE_INFO : {
		VkDescriptorUpdateTemplateCreateInfo const&  value = *BitCast<VkDescriptorUpdateTemplateCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT_EXT, ResourceID((value).descriptorSetLayout), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_LAYOUT_EXT, ResourceID((value).pipelineLayout), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO : {
		VkPhysicalDeviceExternalImageFormatInfo const&  value = *BitCast<VkPhysicalDeviceExternalImageFormatInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_EXTERNAL_BUFFER_PROPERTIES : {
		VkExternalBufferProperties const&  value = *BitCast<VkExternalBufferProperties const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BLEND_OPERATION_ADVANCED_PROPERTIES_EXT : {
		VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT const&  value = *BitCast<VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES : {
		VkPhysicalDeviceIDProperties const&  value = *BitCast<VkPhysicalDeviceIDProperties const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO : {
		VkExternalMemoryImageCreateInfo const&  value = *BitCast<VkExternalMemoryImageCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CORNER_SAMPLED_IMAGE_FEATURES_NV : {
		VkPhysicalDeviceCornerSampledImageFeaturesNV const&  value = *BitCast<VkPhysicalDeviceCornerSampledImageFeaturesNV const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO : {
		VkExportMemoryAllocateInfo const&  value = *BitCast<VkExportMemoryAllocateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_REPRESENTATIVE_FRAGMENT_TEST_FEATURES_NV : {
		VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV const&  value = *BitCast<VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_FENCE_INFO : {
		VkPhysicalDeviceExternalFenceInfo const&  value = *BitCast<VkPhysicalDeviceExternalFenceInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_EXPORT_MEMORY_WIN32_HANDLE_INFO_KHR : {
		#ifdef VULKAN_WIN32_H_
		VkExportMemoryWin32HandleInfoKHR const&  value = *BitCast<VkExportMemoryWin32HandleInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		#endif
		break;
	}

	case VK_STRUCTURE_TYPE_EXTERNAL_FENCE_PROPERTIES : {
		VkExternalFenceProperties const&  value = *BitCast<VkExternalFenceProperties const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_EXPORT_FENCE_CREATE_INFO : {
		VkExportFenceCreateInfo const&  value = *BitCast<VkExportFenceCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO : {
		VkExportSemaphoreCreateInfo const&  value = *BitCast<VkExportSemaphoreCreateInfo const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO_NV : {
		VkExportMemoryAllocateInfoNV const&  value = *BitCast<VkExportMemoryAllocateInfoNV const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_EXTERNAL_SEMAPHORE_PROPERTIES : {
		VkExternalSemaphoreProperties const&  value = *BitCast<VkExternalSemaphoreProperties const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_3_PROPERTIES : {
		VkPhysicalDeviceMaintenance3Properties const&  value = *BitCast<VkPhysicalDeviceMaintenance3Properties const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DRAW_PARAMETER_FEATURES : {
		VkPhysicalDeviceShaderDrawParameterFeatures const&  value = *BitCast<VkPhysicalDeviceShaderDrawParameterFeatures const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CONDITIONAL_RENDERING_FEATURES_EXT : {
		VkPhysicalDeviceConditionalRenderingFeaturesEXT const&  value = *BitCast<VkPhysicalDeviceConditionalRenderingFeaturesEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_IMPORT_MEMORY_FD_INFO_KHR : {
		VkImportMemoryFdInfoKHR const&  value = *BitCast<VkImportMemoryFdInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR : {
		VkSwapchainCreateInfoKHR const&  value = *BitCast<VkSwapchainCreateInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SURFACE_KHR_EXT, ResourceID((value).surface), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT, ResourceID((value).oldSwapchain), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_PRESENT_INFO_KHR : {
		VkPresentInfoKHR const&  value = *BitCast<VkPresentInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		for (uint a = 0; (value).pWaitSemaphores and a < (value).waitSemaphoreCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT, ResourceID((value).pWaitSemaphores[a]), iter, frame_id, EResOp::Access );
		}
		for (uint a = 0; (value).pSwapchains and a < (value).swapchainCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT, ResourceID((value).pSwapchains[a]), iter, frame_id, EResOp::Access );
		}
		break;
	}

	case VK_STRUCTURE_TYPE_IMAGE_SWAPCHAIN_CREATE_INFO_KHR : {
		VkImageSwapchainCreateInfoKHR const&  value = *BitCast<VkImageSwapchainCreateInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT, ResourceID((value).swapchain), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_SWAPCHAIN_INFO_KHR : {
		VkBindImageMemorySwapchainInfoKHR const&  value = *BitCast<VkBindImageMemorySwapchainInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT, ResourceID((value).swapchain), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_DEVICE_GROUP_PRESENT_CAPABILITIES_KHR : {
		VkDeviceGroupPresentCapabilitiesKHR const&  value = *BitCast<VkDeviceGroupPresentCapabilitiesKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_WIN32_KEYED_MUTEX_ACQUIRE_RELEASE_INFO_NV : {
		#ifdef VULKAN_WIN32_H_
		VkWin32KeyedMutexAcquireReleaseInfoNV const&  value = *BitCast<VkWin32KeyedMutexAcquireReleaseInfoNV const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		for (uint a = 0; (value).pAcquireSyncs and a < (value).acquireCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, ResourceID((value).pAcquireSyncs[a]), iter, frame_id, EResOp::Access );
		}
		for (uint a = 0; (value).pReleaseSyncs and a < (value).releaseCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, ResourceID((value).pReleaseSyncs[a]), iter, frame_id, EResOp::Access );
		}
		#endif
		break;
	}

	case VK_STRUCTURE_TYPE_DEVICE_GROUP_PRESENT_INFO_KHR : {
		VkDeviceGroupPresentInfoKHR const&  value = *BitCast<VkDeviceGroupPresentInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DEVICE_GROUP_SWAPCHAIN_CREATE_INFO_KHR : {
		VkDeviceGroupSwapchainCreateInfoKHR const&  value = *BitCast<VkDeviceGroupSwapchainCreateInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR : {
		VkDisplaySurfaceCreateInfoKHR const&  value = *BitCast<VkDisplaySurfaceCreateInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DISPLAY_MODE_KHR_EXT, ResourceID((value).displayMode), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR : {
		#ifdef VULKAN_XCB_H_
		VkXcbSurfaceCreateInfoKHR const&  value = *BitCast<VkXcbSurfaceCreateInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		#endif
		break;
	}

	case VK_STRUCTURE_TYPE_MEMORY_FD_PROPERTIES_KHR : {
		VkMemoryFdPropertiesKHR const&  value = *BitCast<VkMemoryFdPropertiesKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_MEMORY_GET_FD_INFO_KHR : {
		VkMemoryGetFdInfoKHR const&  value = *BitCast<VkMemoryGetFdInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, ResourceID((value).memory), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_FD_INFO_KHR : {
		VkImportSemaphoreFdInfoKHR const&  value = *BitCast<VkImportSemaphoreFdInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT, ResourceID((value).semaphore), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_SEMAPHORE_GET_FD_INFO_KHR : {
		VkSemaphoreGetFdInfoKHR const&  value = *BitCast<VkSemaphoreGetFdInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT, ResourceID((value).semaphore), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PUSH_DESCRIPTOR_PROPERTIES_KHR : {
		VkPhysicalDevicePushDescriptorPropertiesKHR const&  value = *BitCast<VkPhysicalDevicePushDescriptorPropertiesKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_ADVANCED_STATE_CREATE_INFO_EXT : {
		VkPipelineColorBlendAdvancedStateCreateInfoEXT const&  value = *BitCast<VkPipelineColorBlendAdvancedStateCreateInfoEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PRESENT_REGIONS_KHR : {
		VkPresentRegionsKHR const&  value = *BitCast<VkPresentRegionsKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_2_KHR : {
		VkAttachmentDescription2KHR const&  value = *BitCast<VkAttachmentDescription2KHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_2_KHR : {
		VkSubpassDescription2KHR const&  value = *BitCast<VkSubpassDescription2KHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		for (uint a = 0; (value).pInputAttachments and a < (value).inputAttachmentCount; ++a) {
			if ( ((value).pInputAttachments[a]).pNext )
				_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(((value).pInputAttachments[a]).pNext), iter, frame_id );
		}
		for (uint a = 0; (value).pColorAttachments and a < (value).colorAttachmentCount; ++a) {
			if ( ((value).pColorAttachments[a]).pNext )
				_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(((value).pColorAttachments[a]).pNext), iter, frame_id );
		}
		for (uint a = 0; (value).pResolveAttachments and a < (value).colorAttachmentCount; ++a) {
			if ( ((value).pResolveAttachments[a]).pNext )
				_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(((value).pResolveAttachments[a]).pNext), iter, frame_id );
		}
		if ( (value).pDepthStencilAttachment ) {
			if ( (*(value).pDepthStencilAttachment).pNext )
				_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((*(value).pDepthStencilAttachment).pNext), iter, frame_id );
		}
		break;
	}

	case VK_STRUCTURE_TYPE_SUBPASS_DEPENDENCY_2_KHR : {
		VkSubpassDependency2KHR const&  value = *BitCast<VkSubpassDependency2KHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_QUEUE_FAMILY_CHECKPOINT_PROPERTIES_NV : {
		VkQueueFamilyCheckpointPropertiesNV const&  value = *BitCast<VkQueueFamilyCheckpointPropertiesNV const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO_2_KHR : {
		VkRenderPassCreateInfo2KHR const&  value = *BitCast<VkRenderPassCreateInfo2KHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		for (uint a = 0; (value).pAttachments and a < (value).attachmentCount; ++a) {
			if ( ((value).pAttachments[a]).pNext )
				_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(((value).pAttachments[a]).pNext), iter, frame_id );
		}
		for (uint a = 0; (value).pSubpasses and a < (value).subpassCount; ++a) {
			if ( ((value).pSubpasses[a]).pNext )
				_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(((value).pSubpasses[a]).pNext), iter, frame_id );
			for (uint b = 0; ((value).pSubpasses[a]).pInputAttachments and b < ((value).pSubpasses[a]).inputAttachmentCount; ++b) {
				if ( (((value).pSubpasses[a]).pInputAttachments[b]).pNext )
					_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((((value).pSubpasses[a]).pInputAttachments[b]).pNext), iter, frame_id );
			}
			for (uint b = 0; ((value).pSubpasses[a]).pColorAttachments and b < ((value).pSubpasses[a]).colorAttachmentCount; ++b) {
				if ( (((value).pSubpasses[a]).pColorAttachments[b]).pNext )
					_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((((value).pSubpasses[a]).pColorAttachments[b]).pNext), iter, frame_id );
			}
			for (uint b = 0; ((value).pSubpasses[a]).pResolveAttachments and b < ((value).pSubpasses[a]).colorAttachmentCount; ++b) {
				if ( (((value).pSubpasses[a]).pResolveAttachments[b]).pNext )
					_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((((value).pSubpasses[a]).pResolveAttachments[b]).pNext), iter, frame_id );
			}
			if ( ((value).pSubpasses[a]).pDepthStencilAttachment ) {
				if ( (*((value).pSubpasses[a]).pDepthStencilAttachment).pNext )
					_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((*((value).pSubpasses[a]).pDepthStencilAttachment).pNext), iter, frame_id );
			}
		}
		for (uint a = 0; (value).pDependencies and a < (value).dependencyCount; ++a) {
			if ( ((value).pDependencies[a]).pNext )
				_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(((value).pDependencies[a]).pNext), iter, frame_id );
		}
		break;
	}

	case VK_STRUCTURE_TYPE_SUBPASS_BEGIN_INFO_KHR : {
		VkSubpassBeginInfoKHR const&  value = *BitCast<VkSubpassBeginInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_SHARED_PRESENT_SURFACE_CAPABILITIES_KHR : {
		VkSharedPresentSurfaceCapabilitiesKHR const&  value = *BitCast<VkSharedPresentSurfaceCapabilitiesKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_EXT : {
		VkSurfaceCapabilities2EXT const&  value = *BitCast<VkSurfaceCapabilities2EXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_FENCE_GET_FD_INFO_KHR : {
		VkFenceGetFdInfoKHR const&  value = *BitCast<VkFenceGetFdInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT, ResourceID((value).fence), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR : {
		VkPhysicalDeviceSurfaceInfo2KHR const&  value = *BitCast<VkPhysicalDeviceSurfaceInfo2KHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SURFACE_KHR_EXT, ResourceID((value).surface), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_KHR : {
		VkSurfaceCapabilities2KHR const&  value = *BitCast<VkSurfaceCapabilities2KHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_SURFACE_FORMAT_2_KHR : {
		VkSurfaceFormat2KHR const&  value = *BitCast<VkSurfaceFormat2KHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DISPLAY_PROPERTIES_2_KHR : {
		VkDisplayProperties2KHR const&  value = *BitCast<VkDisplayProperties2KHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_WIN32_HANDLE_INFO_KHR : {
		#ifdef VULKAN_WIN32_H_
		VkImportSemaphoreWin32HandleInfoKHR const&  value = *BitCast<VkImportSemaphoreWin32HandleInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT, ResourceID((value).semaphore), iter, frame_id, EResOp::Access );
		#endif
		break;
	}

	case VK_STRUCTURE_TYPE_DISPLAY_MODE_PROPERTIES_2_KHR : {
		VkDisplayModeProperties2KHR const&  value = *BitCast<VkDisplayModeProperties2KHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DISPLAY_PLANE_CAPABILITIES_2_KHR : {
		VkDisplayPlaneCapabilities2KHR const&  value = *BitCast<VkDisplayPlaneCapabilities2KHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_ALLOCATE_INFO_EXT : {
		VkDescriptorSetVariableDescriptorCountAllocateInfoEXT const&  value = *BitCast<VkDescriptorSetVariableDescriptorCountAllocateInfoEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_8BIT_STORAGE_FEATURES_KHR : {
		VkPhysicalDevice8BitStorageFeaturesKHR const&  value = *BitCast<VkPhysicalDevice8BitStorageFeaturesKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_INFO_NVX : {
		VkAccelerationStructureMemoryRequirementsInfoNVX const&  value = *BitCast<VkAccelerationStructureMemoryRequirementsInfoNVX const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_ACCELERATION_STRUCTURE_NVX_EXT, ResourceID((value).accelerationStructure), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_MEMORY_MODEL_FEATURES_KHR : {
		VkPhysicalDeviceVulkanMemoryModelFeaturesKHR const&  value = *BitCast<VkPhysicalDeviceVulkanMemoryModelFeaturesKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT : {
		VkDebugReportCallbackCreateInfoEXT const&  value = *BitCast<VkDebugReportCallbackCreateInfoEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_RASTERIZATION_ORDER_AMD : {
		VkPipelineRasterizationStateRasterizationOrderAMD const&  value = *BitCast<VkPipelineRasterizationStateRasterizationOrderAMD const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_GEOMETRY_NVX : {
		VkGeometryNVX const&  value = *BitCast<VkGeometryNVX const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_NAME_INFO_EXT : {
		VkDebugMarkerObjectNameInfoEXT const&  value = *BitCast<VkDebugMarkerObjectNameInfoEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_TAG_INFO_EXT : {
		VkDebugMarkerObjectTagInfoEXT const&  value = *BitCast<VkDebugMarkerObjectTagInfoEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DEBUG_MARKER_MARKER_INFO_EXT : {
		VkDebugMarkerMarkerInfoEXT const&  value = *BitCast<VkDebugMarkerMarkerInfoEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_IMAGE_CREATE_INFO_NV : {
		VkDedicatedAllocationImageCreateInfoNV const&  value = *BitCast<VkDedicatedAllocationImageCreateInfoNV const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_BUFFER_CREATE_INFO_NV : {
		VkDedicatedAllocationBufferCreateInfoNV const&  value = *BitCast<VkDedicatedAllocationBufferCreateInfoNV const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_EXTERNAL_FORMAT_ANDROID : {
		#ifdef VULKAN_ANDROID_H_
		VkExternalFormatANDROID const&  value = *BitCast<VkExternalFormatANDROID const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		#endif
		break;
	}

	case VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_MEMORY_ALLOCATE_INFO_NV : {
		VkDedicatedAllocationMemoryAllocateInfoNV const&  value = *BitCast<VkDedicatedAllocationMemoryAllocateInfoNV const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, ResourceID((value).image), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID((value).buffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_SHADER_MODULE_VALIDATION_CACHE_CREATE_INFO_EXT : {
		VkShaderModuleValidationCacheCreateInfoEXT const&  value = *BitCast<VkShaderModuleValidationCacheCreateInfoEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_VALIDATION_CACHE_EXT_EXT, ResourceID((value).validationCache), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CONSERVATIVE_RASTERIZATION_PROPERTIES_EXT : {
		VkPhysicalDeviceConservativeRasterizationPropertiesEXT const&  value = *BitCast<VkPhysicalDeviceConservativeRasterizationPropertiesEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_TEXTURE_LOD_GATHER_FORMAT_PROPERTIES_AMD : {
		VkTextureLODGatherFormatPropertiesAMD const&  value = *BitCast<VkTextureLODGatherFormatPropertiesAMD const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO_NV : {
		VkExternalMemoryImageCreateInfoNV const&  value = *BitCast<VkExternalMemoryImageCreateInfoNV const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_VALIDATION_FLAGS_EXT : {
		VkValidationFlagsEXT const&  value = *BitCast<VkValidationFlagsEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_IMAGE_VIEW_ASTC_DECODE_MODE_EXT : {
		VkImageViewASTCDecodeModeEXT const&  value = *BitCast<VkImageViewASTCDecodeModeEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_CONDITIONAL_RENDERING_BEGIN_INFO_EXT : {
		VkConditionalRenderingBeginInfoEXT const&  value = *BitCast<VkConditionalRenderingBeginInfoEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID((value).buffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_D3D12_FENCE_SUBMIT_INFO_KHR : {
		#ifdef VULKAN_WIN32_H_
		VkD3D12FenceSubmitInfoKHR const&  value = *BitCast<VkD3D12FenceSubmitInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		#endif
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DISCARD_RECTANGLE_PROPERTIES_EXT : {
		VkPhysicalDeviceDiscardRectanglePropertiesEXT const&  value = *BitCast<VkPhysicalDeviceDiscardRectanglePropertiesEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_CONDITIONAL_RENDERING_INFO_EXT : {
		VkCommandBufferInheritanceConditionalRenderingInfoEXT const&  value = *BitCast<VkCommandBufferInheritanceConditionalRenderingInfoEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_INDIRECT_COMMANDS_LAYOUT_CREATE_INFO_NVX : {
		VkIndirectCommandsLayoutCreateInfoNVX const&  value = *BitCast<VkIndirectCommandsLayoutCreateInfoNVX const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DISPLAY_EVENT_INFO_EXT : {
		VkDisplayEventInfoEXT const&  value = *BitCast<VkDisplayEventInfoEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_CMD_PROCESS_COMMANDS_INFO_NVX : {
		VkCmdProcessCommandsInfoNVX const&  value = *BitCast<VkCmdProcessCommandsInfoNVX const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_OBJECT_TABLE_NVX_EXT, ResourceID((value).objectTable), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_NVX_EXT, ResourceID((value).indirectCommandsLayout), iter, frame_id, EResOp::Access );
		for (uint a = 0; (value).pIndirectCommandsTokens and a < (value).indirectCommandsTokenCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID(((value).pIndirectCommandsTokens[a]).buffer), iter, frame_id, EResOp::Access );
		}
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID((value).targetCommandBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID((value).sequencesCountBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID((value).sequencesIndexBuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_CMD_RESERVE_SPACE_FOR_COMMANDS_INFO_NVX : {
		VkCmdReserveSpaceForCommandsInfoNVX const&  value = *BitCast<VkCmdReserveSpaceForCommandsInfoNVX const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_OBJECT_TABLE_NVX_EXT, ResourceID((value).objectTable), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_NVX_EXT, ResourceID((value).indirectCommandsLayout), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_OBJECT_TABLE_CREATE_INFO_NVX : {
		VkObjectTableCreateInfoNVX const&  value = *BitCast<VkObjectTableCreateInfoNVX const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_EXCLUSIVE_SCISSOR_STATE_CREATE_INFO_NV : {
		VkPipelineViewportExclusiveScissorStateCreateInfoNV const&  value = *BitCast<VkPipelineViewportExclusiveScissorStateCreateInfoNV const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_W_SCALING_STATE_CREATE_INFO_NV : {
		VkPipelineViewportWScalingStateCreateInfoNV const&  value = *BitCast<VkPipelineViewportWScalingStateCreateInfoNV const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXCLUSIVE_SCISSOR_FEATURES_NV : {
		VkPhysicalDeviceExclusiveScissorFeaturesNV const&  value = *BitCast<VkPhysicalDeviceExclusiveScissorFeaturesNV const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DISPLAY_POWER_INFO_EXT : {
		VkDisplayPowerInfoEXT const&  value = *BitCast<VkDisplayPowerInfoEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_SWAPCHAIN_COUNTER_CREATE_INFO_EXT : {
		VkSwapchainCounterCreateInfoEXT const&  value = *BitCast<VkSwapchainCounterCreateInfoEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PER_VIEW_ATTRIBUTES_PROPERTIES_NVX : {
		VkPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX const&  value = *BitCast<VkPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_SWIZZLE_STATE_CREATE_INFO_NV : {
		VkPipelineViewportSwizzleStateCreateInfoNV const&  value = *BitCast<VkPipelineViewportSwizzleStateCreateInfoNV const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PIPELINE_DISCARD_RECTANGLE_STATE_CREATE_INFO_EXT : {
		VkPipelineDiscardRectangleStateCreateInfoEXT const&  value = *BitCast<VkPipelineDiscardRectangleStateCreateInfoEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_RAYTRACING_PIPELINE_CREATE_INFO_NVX : {
		VkRaytracingPipelineCreateInfoNVX const&  value = *BitCast<VkRaytracingPipelineCreateInfoNVX const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		for (uint a = 0; (value).pStages and a < (value).stageCount; ++a) {
			if ( ((value).pStages[a]).pNext )
				_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(((value).pStages[a]).pNext), iter, frame_id );
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SHADER_MODULE_EXT, ResourceID(((value).pStages[a]).module), iter, frame_id, EResOp::Access );
		}
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_LAYOUT_EXT, ResourceID((value).layout), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_EXT, ResourceID((value).basePipelineHandle), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_CONSERVATIVE_STATE_CREATE_INFO_EXT : {
		VkPipelineRasterizationConservativeStateCreateInfoEXT const&  value = *BitCast<VkPipelineRasterizationConservativeStateCreateInfoEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_TAG_INFO_EXT : {
		VkDebugUtilsObjectTagInfoEXT const&  value = *BitCast<VkDebugUtilsObjectTagInfoEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT : {
		VkDebugUtilsLabelEXT const&  value = *BitCast<VkDebugUtilsLabelEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_MEMORY_HOST_PROPERTIES_EXT : {
		VkPhysicalDeviceExternalMemoryHostPropertiesEXT const&  value = *BitCast<VkPhysicalDeviceExternalMemoryHostPropertiesEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CALLBACK_DATA_EXT : {
		VkDebugUtilsMessengerCallbackDataEXT const&  value = *BitCast<VkDebugUtilsMessengerCallbackDataEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT : {
		VkDebugUtilsMessengerCreateInfoEXT const&  value = *BitCast<VkDebugUtilsMessengerCreateInfoEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INLINE_UNIFORM_BLOCK_FEATURES_EXT : {
		VkPhysicalDeviceInlineUniformBlockFeaturesEXT const&  value = *BitCast<VkPhysicalDeviceInlineUniformBlockFeaturesEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INLINE_UNIFORM_BLOCK_PROPERTIES_EXT : {
		VkPhysicalDeviceInlineUniformBlockPropertiesEXT const&  value = *BitCast<VkPhysicalDeviceInlineUniformBlockPropertiesEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_INLINE_UNIFORM_BLOCK_EXT : {
		VkWriteDescriptorSetInlineUniformBlockEXT const&  value = *BitCast<VkWriteDescriptorSetInlineUniformBlockEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_SHADING_RATE_IMAGE_STATE_CREATE_INFO_NV : {
		VkPipelineViewportShadingRateImageStateCreateInfoNV const&  value = *BitCast<VkPipelineViewportShadingRateImageStateCreateInfoNV const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_INLINE_UNIFORM_BLOCK_CREATE_INFO_EXT : {
		VkDescriptorPoolInlineUniformBlockCreateInfoEXT const&  value = *BitCast<VkDescriptorPoolInlineUniformBlockCreateInfoEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADING_RATE_IMAGE_FEATURES_NV : {
		VkPhysicalDeviceShadingRateImageFeaturesNV const&  value = *BitCast<VkPhysicalDeviceShadingRateImageFeaturesNV const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_SAMPLE_LOCATIONS_INFO_EXT : {
		VkSampleLocationsInfoEXT const&  value = *BitCast<VkSampleLocationsInfoEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PIPELINE_SAMPLE_LOCATIONS_STATE_CREATE_INFO_EXT : {
		VkPipelineSampleLocationsStateCreateInfoEXT const&  value = *BitCast<VkPipelineSampleLocationsStateCreateInfoEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLE_LOCATIONS_PROPERTIES_EXT : {
		VkPhysicalDeviceSampleLocationsPropertiesEXT const&  value = *BitCast<VkPhysicalDeviceSampleLocationsPropertiesEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_MULTISAMPLE_PROPERTIES_EXT : {
		VkMultisamplePropertiesEXT const&  value = *BitCast<VkMultisamplePropertiesEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BLEND_OPERATION_ADVANCED_FEATURES_EXT : {
		VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT const&  value = *BitCast<VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_MODULATION_STATE_CREATE_INFO_NV : {
		VkPipelineCoverageModulationStateCreateInfoNV const&  value = *BitCast<VkPipelineCoverageModulationStateCreateInfoNV const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES_EXT : {
		VkPhysicalDeviceDescriptorIndexingFeaturesEXT const&  value = *BitCast<VkPhysicalDeviceDescriptorIndexingFeaturesEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_FORMAT_PROPERTIES_ANDROID : {
		#ifdef VULKAN_ANDROID_H_
		VkAndroidHardwareBufferFormatPropertiesANDROID const&  value = *BitCast<VkAndroidHardwareBufferFormatPropertiesANDROID const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		#endif
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_PROPERTIES_EXT : {
		VkPhysicalDeviceDescriptorIndexingPropertiesEXT const&  value = *BitCast<VkPhysicalDeviceDescriptorIndexingPropertiesEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_GEOMETRY_AABB_NVX : {
		VkGeometryAABBNVX const&  value = *BitCast<VkGeometryAABBNVX const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID((value).aabbData), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_BIND_ACCELERATION_STRUCTURE_MEMORY_INFO_NVX : {
		VkBindAccelerationStructureMemoryInfoNVX const&  value = *BitCast<VkBindAccelerationStructureMemoryInfoNVX const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_ACCELERATION_STRUCTURE_NVX_EXT, ResourceID((value).accelerationStructure), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, ResourceID((value).memory), iter, frame_id, EResOp::Access );
		break;
	}

	case VK_STRUCTURE_TYPE_DESCRIPTOR_ACCELERATION_STRUCTURE_INFO_NVX : {
		VkDescriptorAccelerationStructureInfoNVX const&  value = *BitCast<VkDescriptorAccelerationStructureInfoNVX const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		for (uint a = 0; (value).pAccelerationStructures and a < (value).accelerationStructureCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_ACCELERATION_STRUCTURE_NVX_EXT, ResourceID((value).pAccelerationStructures[a]), iter, frame_id, EResOp::Access );
		}
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAYTRACING_PROPERTIES_NVX : {
		VkPhysicalDeviceRaytracingPropertiesNVX const&  value = *BitCast<VkPhysicalDeviceRaytracingPropertiesNVX const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PIPELINE_REPRESENTATIVE_FRAGMENT_TEST_STATE_CREATE_INFO_NV : {
		VkPipelineRepresentativeFragmentTestStateCreateInfoNV const&  value = *BitCast<VkPipelineRepresentativeFragmentTestStateCreateInfoNV const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_DEVICE_QUEUE_GLOBAL_PRIORITY_CREATE_INFO_EXT : {
		VkDeviceQueueGlobalPriorityCreateInfoEXT const&  value = *BitCast<VkDeviceQueueGlobalPriorityCreateInfoEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_AMD : {
		VkPhysicalDeviceShaderCorePropertiesAMD const&  value = *BitCast<VkPhysicalDeviceShaderCorePropertiesAMD const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_ATTRIBUTE_DIVISOR_PROPERTIES_EXT : {
		VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT const&  value = *BitCast<VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_DIVISOR_STATE_CREATE_INFO_EXT : {
		VkPipelineVertexInputDivisorStateCreateInfoEXT const&  value = *BitCast<VkPipelineVertexInputDivisorStateCreateInfoEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_FENCE_GET_WIN32_HANDLE_INFO_KHR : {
		#ifdef VULKAN_WIN32_H_
		VkFenceGetWin32HandleInfoKHR const&  value = *BitCast<VkFenceGetWin32HandleInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT, ResourceID((value).fence), iter, frame_id, EResOp::Access );
		#endif
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_ATTRIBUTE_DIVISOR_FEATURES_EXT : {
		VkPhysicalDeviceVertexAttributeDivisorFeaturesEXT const&  value = *BitCast<VkPhysicalDeviceVertexAttributeDivisorFeaturesEXT const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COMPUTE_SHADER_DERIVATIVES_FEATURES_NV : {
		VkPhysicalDeviceComputeShaderDerivativesFeaturesNV const&  value = *BitCast<VkPhysicalDeviceComputeShaderDerivativesFeaturesNV const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_NV : {
		VkPhysicalDeviceMeshShaderFeaturesNV const&  value = *BitCast<VkPhysicalDeviceMeshShaderFeaturesNV const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_PROPERTIES_NV : {
		VkPhysicalDeviceMeshShaderPropertiesNV const&  value = *BitCast<VkPhysicalDeviceMeshShaderPropertiesNV const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_BARYCENTRIC_FEATURES_NV : {
		VkPhysicalDeviceFragmentShaderBarycentricFeaturesNV const&  value = *BitCast<VkPhysicalDeviceFragmentShaderBarycentricFeaturesNV const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_IMAGE_FOOTPRINT_FEATURES_NV : {
		VkPhysicalDeviceShaderImageFootprintFeaturesNV const&  value = *BitCast<VkPhysicalDeviceShaderImageFootprintFeaturesNV const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_CHECKPOINT_DATA_NV : {
		VkCheckpointDataNV const&  value = *BitCast<VkCheckpointDataNV const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		break;
	}

	case VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR : {
		#ifdef VULKAN_WIN32_H_
		VkWin32SurfaceCreateInfoKHR const&  value = *BitCast<VkWin32SurfaceCreateInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		#endif
		break;
	}

	case VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_KHR : {
		#ifdef VULKAN_WIN32_H_
		VkImportMemoryWin32HandleInfoKHR const&  value = *BitCast<VkImportMemoryWin32HandleInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		#endif
		break;
	}

	case VK_STRUCTURE_TYPE_MEMORY_GET_WIN32_HANDLE_INFO_KHR : {
		#ifdef VULKAN_WIN32_H_
		VkMemoryGetWin32HandleInfoKHR const&  value = *BitCast<VkMemoryGetWin32HandleInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, ResourceID((value).memory), iter, frame_id, EResOp::Access );
		#endif
		break;
	}

	case VK_STRUCTURE_TYPE_WIN32_KEYED_MUTEX_ACQUIRE_RELEASE_INFO_KHR : {
		#ifdef VULKAN_WIN32_H_
		VkWin32KeyedMutexAcquireReleaseInfoKHR const&  value = *BitCast<VkWin32KeyedMutexAcquireReleaseInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		for (uint a = 0; (value).pAcquireSyncs and a < (value).acquireCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, ResourceID((value).pAcquireSyncs[a]), iter, frame_id, EResOp::Access );
		}
		for (uint a = 0; (value).pReleaseSyncs and a < (value).releaseCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, ResourceID((value).pReleaseSyncs[a]), iter, frame_id, EResOp::Access );
		}
		#endif
		break;
	}

	case VK_STRUCTURE_TYPE_EXPORT_FENCE_WIN32_HANDLE_INFO_KHR : {
		#ifdef VULKAN_WIN32_H_
		VkExportFenceWin32HandleInfoKHR const&  value = *BitCast<VkExportFenceWin32HandleInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		#endif
		break;
	}

	case VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_PROPERTIES_ANDROID : {
		#ifdef VULKAN_ANDROID_H_
		VkAndroidHardwareBufferPropertiesANDROID const&  value = *BitCast<VkAndroidHardwareBufferPropertiesANDROID const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		#endif
		break;
	}

	case VK_STRUCTURE_TYPE_IMPORT_ANDROID_HARDWARE_BUFFER_INFO_ANDROID : {
		#ifdef VULKAN_ANDROID_H_
		VkImportAndroidHardwareBufferInfoANDROID const&  value = *BitCast<VkImportAndroidHardwareBufferInfoANDROID const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		#endif
		break;
	}

	case VK_STRUCTURE_TYPE_MEMORY_GET_ANDROID_HARDWARE_BUFFER_INFO_ANDROID : {
		#ifdef VULKAN_ANDROID_H_
		VkMemoryGetAndroidHardwareBufferInfoANDROID const&  value = *BitCast<VkMemoryGetAndroidHardwareBufferInfoANDROID const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, ResourceID((value).memory), iter, frame_id, EResOp::Access );
		#endif
		break;
	}

	case VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR : {
		#ifdef VULKAN_XLIB_H_
		VkXlibSurfaceCreateInfoKHR const&  value = *BitCast<VkXlibSurfaceCreateInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		#endif
		break;
	}

	case VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR : {
		#ifdef VULKAN_WAYLAND_H_
		VkWaylandSurfaceCreateInfoKHR const&  value = *BitCast<VkWaylandSurfaceCreateInfoKHR const *>( header );
		if ( (value).pNext )
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>((value).pNext), iter, frame_id );
		#endif
		break;
	}

	case VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO : break;
	case VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO : break;
	case VK_STRUCTURE_TYPE_VI_SURFACE_CREATE_INFO_NN : break;
	case VK_STRUCTURE_TYPE_IOS_SURFACE_CREATE_INFO_MVK : break;
	case VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK : break;
	case VK_STRUCTURE_TYPE_GEOMETRY_INSTANCE_NVX : break;
	case VK_STRUCTURE_TYPE_HIT_SHADER_MODULE_CREATE_INFO_NVX : break;
	case VK_STRUCTURE_TYPE_RANGE_SIZE : break;
	case VK_STRUCTURE_TYPE_MAX_ENUM : break;
}
DISABLE_ENUM_CHECKS();
