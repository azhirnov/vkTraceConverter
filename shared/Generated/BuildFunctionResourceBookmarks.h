// auto-generated file

ENABLE_ENUM_CHECKS();
switch ( iter->packet_id )
{
	case VKTRACE_TPI_MESSAGE : break;
	case VKTRACE_TPI_MARKER_CHECKPOINT : break;
	case VKTRACE_TPI_MARKER_API_BOUNDARY : break;
	case VKTRACE_TPI_MARKER_API_GROUP_BEGIN : break;
	case VKTRACE_TPI_MARKER_API_GROUP_END : break;
	case VKTRACE_TPI_MARKER_TERMINATE_PROCESS : break;
	case VKTRACE_TPI_PORTABILITY_TABLE : break;
	case VKTRACE_TPI_VK_vkApiVersion : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalImageFormatPropertiesNV : {
		packet_vkGetPhysicalDeviceExternalImageFormatPropertiesNV const&  packet = iter.Cast<packet_vkGetPhysicalDeviceExternalImageFormatPropertiesNV>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDrawIndirectCountAMD : {
		packet_vkCmdDrawIndirectCountAMD const&  packet = iter.Cast<packet_vkCmdDrawIndirectCountAMD>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID(packet.buffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID(packet.countBuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDrawIndexedIndirectCountAMD : {
		packet_vkCmdDrawIndexedIndirectCountAMD const&  packet = iter.Cast<packet_vkCmdDrawIndexedIndirectCountAMD>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID(packet.buffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID(packet.countBuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCreateDebugReportCallbackEXT : {
		packet_vkCreateDebugReportCallbackEXT const&  packet = iter.Cast<packet_vkCreateDebugReportCallbackEXT>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT, ResourceID(packet.instance), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyDebugReportCallbackEXT : {
		packet_vkDestroyDebugReportCallbackEXT const&  packet = iter.Cast<packet_vkDestroyDebugReportCallbackEXT>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT, ResourceID(packet.instance), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkDebugReportMessageEXT : {
		packet_vkDebugReportMessageEXT const&  packet = iter.Cast<packet_vkDebugReportMessageEXT>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT, ResourceID(packet.instance), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkDebugMarkerSetObjectTagEXT : {
		packet_vkDebugMarkerSetObjectTagEXT const&  packet = iter.Cast<packet_vkDebugMarkerSetObjectTagEXT>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pTagInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pTagInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDebugMarkerSetObjectNameEXT : {
		packet_vkDebugMarkerSetObjectNameEXT const&  packet = iter.Cast<packet_vkDebugMarkerSetObjectNameEXT>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pNameInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pNameInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDebugMarkerBeginEXT : {
		packet_vkCmdDebugMarkerBeginEXT const&  packet = iter.Cast<packet_vkCmdDebugMarkerBeginEXT>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		if ( packet.pMarkerInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pMarkerInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDebugMarkerEndEXT : {
		packet_vkCmdDebugMarkerEndEXT const&  packet = iter.Cast<packet_vkCmdDebugMarkerEndEXT>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDebugMarkerInsertEXT : {
		packet_vkCmdDebugMarkerInsertEXT const&  packet = iter.Cast<packet_vkCmdDebugMarkerInsertEXT>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		if ( packet.pMarkerInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pMarkerInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkCreateInstance : {
		packet_vkCreateInstance const&  packet = iter.Cast<packet_vkCreateInstance>();
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pInstance ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT, ResourceID(*packet.pInstance), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyInstance : {
		packet_vkDestroyInstance const&  packet = iter.Cast<packet_vkDestroyInstance>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT, ResourceID(packet.instance), iter, frame_id, EResOp::Destruct );
		break;
	}

	case VKTRACE_TPI_VK_vkEnumeratePhysicalDevices : {
		packet_vkEnumeratePhysicalDevices const&  packet = iter.Cast<packet_vkEnumeratePhysicalDevices>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT, ResourceID(packet.instance), iter, frame_id, EResOp::Access );
		for (uint a = 0; packet.pPhysicalDevices and &packet.pPhysicalDeviceCount[0] and a < packet.pPhysicalDeviceCount[0]; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.pPhysicalDevices[a]), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceFeatures : {
		packet_vkGetPhysicalDeviceFeatures const&  packet = iter.Cast<packet_vkGetPhysicalDeviceFeatures>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceFormatProperties : {
		packet_vkGetPhysicalDeviceFormatProperties const&  packet = iter.Cast<packet_vkGetPhysicalDeviceFormatProperties>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceImageFormatProperties : {
		packet_vkGetPhysicalDeviceImageFormatProperties const&  packet = iter.Cast<packet_vkGetPhysicalDeviceImageFormatProperties>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceProperties : {
		packet_vkGetPhysicalDeviceProperties const&  packet = iter.Cast<packet_vkGetPhysicalDeviceProperties>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceQueueFamilyProperties : {
		packet_vkGetPhysicalDeviceQueueFamilyProperties const&  packet = iter.Cast<packet_vkGetPhysicalDeviceQueueFamilyProperties>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceMemoryProperties : {
		packet_vkGetPhysicalDeviceMemoryProperties const&  packet = iter.Cast<packet_vkGetPhysicalDeviceMemoryProperties>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetInstanceProcAddr : {
		packet_vkGetInstanceProcAddr const&  packet = iter.Cast<packet_vkGetInstanceProcAddr>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT, ResourceID(packet.instance), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetDeviceProcAddr : {
		packet_vkGetDeviceProcAddr const&  packet = iter.Cast<packet_vkGetDeviceProcAddr>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCreateDevice : {
		packet_vkCreateDevice const&  packet = iter.Cast<packet_vkCreateDevice>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pDevice ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(*packet.pDevice), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyDevice : {
		packet_vkDestroyDevice const&  packet = iter.Cast<packet_vkDestroyDevice>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Destruct );
		break;
	}

	case VKTRACE_TPI_VK_vkEnumerateInstanceExtensionProperties : {
		break;
	}

	case VKTRACE_TPI_VK_vkEnumerateDeviceExtensionProperties : {
		packet_vkEnumerateDeviceExtensionProperties const&  packet = iter.Cast<packet_vkEnumerateDeviceExtensionProperties>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkEnumerateInstanceLayerProperties : {
		break;
	}

	case VKTRACE_TPI_VK_vkEnumerateDeviceLayerProperties : {
		packet_vkEnumerateDeviceLayerProperties const&  packet = iter.Cast<packet_vkEnumerateDeviceLayerProperties>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetDeviceQueue : {
		packet_vkGetDeviceQueue const&  packet = iter.Cast<packet_vkGetDeviceQueue>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pQueue ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT, ResourceID(*packet.pQueue), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkQueueSubmit : {
		packet_vkQueueSubmit const&  packet = iter.Cast<packet_vkQueueSubmit>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT, ResourceID(packet.queue), iter, frame_id, EResOp::Access );
		for (uint a = 0; packet.pSubmits and a < packet.submitCount; ++a) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(packet.pSubmits[a])), iter, frame_id );
		}
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT, ResourceID(packet.fence), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkQueueWaitIdle : {
		packet_vkQueueWaitIdle const&  packet = iter.Cast<packet_vkQueueWaitIdle>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT, ResourceID(packet.queue), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkDeviceWaitIdle : {
		packet_vkDeviceWaitIdle const&  packet = iter.Cast<packet_vkDeviceWaitIdle>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkAllocateMemory : {
		packet_vkAllocateMemory const&  packet = iter.Cast<packet_vkAllocateMemory>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pAllocateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pAllocateInfo)), iter, frame_id );
		}
		if ( packet.pMemory ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, ResourceID(*packet.pMemory), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkFreeMemory : {
		packet_vkFreeMemory const&  packet = iter.Cast<packet_vkFreeMemory>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, ResourceID(packet.memory), iter, frame_id, EResOp::Destruct );
		break;
	}

	case VKTRACE_TPI_VK_vkMapMemory : {
		packet_vkMapMemory const&  packet = iter.Cast<packet_vkMapMemory>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, ResourceID(packet.memory), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkUnmapMemory : {
		packet_vkUnmapMemory const&  packet = iter.Cast<packet_vkUnmapMemory>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, ResourceID(packet.memory), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkFlushMappedMemoryRanges : {
		packet_vkFlushMappedMemoryRanges const&  packet = iter.Cast<packet_vkFlushMappedMemoryRanges>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		for (uint a = 0; packet.pMemoryRanges and a < packet.memoryRangeCount; ++a) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(packet.pMemoryRanges[a])), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkInvalidateMappedMemoryRanges : {
		packet_vkInvalidateMappedMemoryRanges const&  packet = iter.Cast<packet_vkInvalidateMappedMemoryRanges>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		for (uint a = 0; packet.pMemoryRanges and a < packet.memoryRangeCount; ++a) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(packet.pMemoryRanges[a])), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetDeviceMemoryCommitment : {
		packet_vkGetDeviceMemoryCommitment const&  packet = iter.Cast<packet_vkGetDeviceMemoryCommitment>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, ResourceID(packet.memory), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkBindBufferMemory : {
		packet_vkBindBufferMemory const&  packet = iter.Cast<packet_vkBindBufferMemory>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID(packet.buffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, ResourceID(packet.memory), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkBindImageMemory : {
		packet_vkBindImageMemory const&  packet = iter.Cast<packet_vkBindImageMemory>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, ResourceID(packet.image), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, ResourceID(packet.memory), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetBufferMemoryRequirements : {
		packet_vkGetBufferMemoryRequirements const&  packet = iter.Cast<packet_vkGetBufferMemoryRequirements>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID(packet.buffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetImageMemoryRequirements : {
		packet_vkGetImageMemoryRequirements const&  packet = iter.Cast<packet_vkGetImageMemoryRequirements>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, ResourceID(packet.image), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetImageSparseMemoryRequirements : {
		packet_vkGetImageSparseMemoryRequirements const&  packet = iter.Cast<packet_vkGetImageSparseMemoryRequirements>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, ResourceID(packet.image), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSparseImageFormatProperties : {
		packet_vkGetPhysicalDeviceSparseImageFormatProperties const&  packet = iter.Cast<packet_vkGetPhysicalDeviceSparseImageFormatProperties>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkQueueBindSparse : {
		packet_vkQueueBindSparse const&  packet = iter.Cast<packet_vkQueueBindSparse>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT, ResourceID(packet.queue), iter, frame_id, EResOp::Access );
		for (uint a = 0; packet.pBindInfo and a < packet.bindInfoCount; ++a) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(packet.pBindInfo[a])), iter, frame_id );
		}
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT, ResourceID(packet.fence), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCreateFence : {
		packet_vkCreateFence const&  packet = iter.Cast<packet_vkCreateFence>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pFence ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT, ResourceID(*packet.pFence), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyFence : {
		packet_vkDestroyFence const&  packet = iter.Cast<packet_vkDestroyFence>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT, ResourceID(packet.fence), iter, frame_id, EResOp::Destruct );
		break;
	}

	case VKTRACE_TPI_VK_vkResetFences : {
		packet_vkResetFences const&  packet = iter.Cast<packet_vkResetFences>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		for (uint a = 0; packet.pFences and &packet.fenceCount and a < packet.fenceCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT, ResourceID(packet.pFences[a]), iter, frame_id, EResOp::Access );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetFenceStatus : {
		packet_vkGetFenceStatus const&  packet = iter.Cast<packet_vkGetFenceStatus>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT, ResourceID(packet.fence), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkWaitForFences : {
		packet_vkWaitForFences const&  packet = iter.Cast<packet_vkWaitForFences>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		for (uint a = 0; packet.pFences and &packet.fenceCount and a < packet.fenceCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT, ResourceID(packet.pFences[a]), iter, frame_id, EResOp::Access );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkCreateSemaphore : {
		packet_vkCreateSemaphore const&  packet = iter.Cast<packet_vkCreateSemaphore>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pSemaphore ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT, ResourceID(*packet.pSemaphore), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroySemaphore : {
		packet_vkDestroySemaphore const&  packet = iter.Cast<packet_vkDestroySemaphore>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT, ResourceID(packet.semaphore), iter, frame_id, EResOp::Destruct );
		break;
	}

	case VKTRACE_TPI_VK_vkCreateEvent : {
		packet_vkCreateEvent const&  packet = iter.Cast<packet_vkCreateEvent>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pEvent ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_EVENT_EXT, ResourceID(*packet.pEvent), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyEvent : {
		packet_vkDestroyEvent const&  packet = iter.Cast<packet_vkDestroyEvent>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_EVENT_EXT, ResourceID(packet.event), iter, frame_id, EResOp::Destruct );
		break;
	}

	case VKTRACE_TPI_VK_vkGetEventStatus : {
		packet_vkGetEventStatus const&  packet = iter.Cast<packet_vkGetEventStatus>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_EVENT_EXT, ResourceID(packet.event), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkSetEvent : {
		packet_vkSetEvent const&  packet = iter.Cast<packet_vkSetEvent>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_EVENT_EXT, ResourceID(packet.event), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkResetEvent : {
		packet_vkResetEvent const&  packet = iter.Cast<packet_vkResetEvent>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_EVENT_EXT, ResourceID(packet.event), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCreateQueryPool : {
		packet_vkCreateQueryPool const&  packet = iter.Cast<packet_vkCreateQueryPool>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pQueryPool ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_QUERY_POOL_EXT, ResourceID(*packet.pQueryPool), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyQueryPool : {
		packet_vkDestroyQueryPool const&  packet = iter.Cast<packet_vkDestroyQueryPool>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_QUERY_POOL_EXT, ResourceID(packet.queryPool), iter, frame_id, EResOp::Destruct );
		break;
	}

	case VKTRACE_TPI_VK_vkGetQueryPoolResults : {
		packet_vkGetQueryPoolResults const&  packet = iter.Cast<packet_vkGetQueryPoolResults>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_QUERY_POOL_EXT, ResourceID(packet.queryPool), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCreateBuffer : {
		packet_vkCreateBuffer const&  packet = iter.Cast<packet_vkCreateBuffer>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pBuffer ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID(*packet.pBuffer), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyBuffer : {
		packet_vkDestroyBuffer const&  packet = iter.Cast<packet_vkDestroyBuffer>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID(packet.buffer), iter, frame_id, EResOp::Destruct );
		break;
	}

	case VKTRACE_TPI_VK_vkCreateBufferView : {
		packet_vkCreateBufferView const&  packet = iter.Cast<packet_vkCreateBufferView>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pView ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_VIEW_EXT, ResourceID(*packet.pView), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyBufferView : {
		packet_vkDestroyBufferView const&  packet = iter.Cast<packet_vkDestroyBufferView>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_VIEW_EXT, ResourceID(packet.bufferView), iter, frame_id, EResOp::Destruct );
		break;
	}

	case VKTRACE_TPI_VK_vkCreateImage : {
		packet_vkCreateImage const&  packet = iter.Cast<packet_vkCreateImage>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pImage ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, ResourceID(*packet.pImage), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyImage : {
		packet_vkDestroyImage const&  packet = iter.Cast<packet_vkDestroyImage>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, ResourceID(packet.image), iter, frame_id, EResOp::Destruct );
		break;
	}

	case VKTRACE_TPI_VK_vkGetImageSubresourceLayout : {
		packet_vkGetImageSubresourceLayout const&  packet = iter.Cast<packet_vkGetImageSubresourceLayout>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, ResourceID(packet.image), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCreateImageView : {
		packet_vkCreateImageView const&  packet = iter.Cast<packet_vkCreateImageView>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pView ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_VIEW_EXT, ResourceID(*packet.pView), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyImageView : {
		packet_vkDestroyImageView const&  packet = iter.Cast<packet_vkDestroyImageView>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_VIEW_EXT, ResourceID(packet.imageView), iter, frame_id, EResOp::Destruct );
		break;
	}

	case VKTRACE_TPI_VK_vkCreateShaderModule : {
		packet_vkCreateShaderModule const&  packet = iter.Cast<packet_vkCreateShaderModule>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pShaderModule ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SHADER_MODULE_EXT, ResourceID(*packet.pShaderModule), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyShaderModule : {
		packet_vkDestroyShaderModule const&  packet = iter.Cast<packet_vkDestroyShaderModule>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SHADER_MODULE_EXT, ResourceID(packet.shaderModule), iter, frame_id, EResOp::Destruct );
		break;
	}

	case VKTRACE_TPI_VK_vkCreatePipelineCache : {
		packet_vkCreatePipelineCache const&  packet = iter.Cast<packet_vkCreatePipelineCache>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pPipelineCache ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_CACHE_EXT, ResourceID(*packet.pPipelineCache), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyPipelineCache : {
		packet_vkDestroyPipelineCache const&  packet = iter.Cast<packet_vkDestroyPipelineCache>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_CACHE_EXT, ResourceID(packet.pipelineCache), iter, frame_id, EResOp::Destruct );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPipelineCacheData : {
		packet_vkGetPipelineCacheData const&  packet = iter.Cast<packet_vkGetPipelineCacheData>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_CACHE_EXT, ResourceID(packet.pipelineCache), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkMergePipelineCaches : {
		packet_vkMergePipelineCaches const&  packet = iter.Cast<packet_vkMergePipelineCaches>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_CACHE_EXT, ResourceID(packet.dstCache), iter, frame_id, EResOp::Access );
		for (uint a = 0; packet.pSrcCaches and &packet.srcCacheCount and a < packet.srcCacheCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_CACHE_EXT, ResourceID(packet.pSrcCaches[a]), iter, frame_id, EResOp::Access );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkCreateGraphicsPipelines : {
		packet_vkCreateGraphicsPipelines const&  packet = iter.Cast<packet_vkCreateGraphicsPipelines>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_CACHE_EXT, ResourceID(packet.pipelineCache), iter, frame_id, EResOp::Access );
		for (uint a = 0; packet.pCreateInfos and a < packet.createInfoCount; ++a) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(packet.pCreateInfos[a])), iter, frame_id );
		}
		for (uint a = 0; packet.pPipelines and &packet.createInfoCount and a < packet.createInfoCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_EXT, ResourceID(packet.pPipelines[a]), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkCreateComputePipelines : {
		packet_vkCreateComputePipelines const&  packet = iter.Cast<packet_vkCreateComputePipelines>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_CACHE_EXT, ResourceID(packet.pipelineCache), iter, frame_id, EResOp::Access );
		for (uint a = 0; packet.pCreateInfos and a < packet.createInfoCount; ++a) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(packet.pCreateInfos[a])), iter, frame_id );
		}
		for (uint a = 0; packet.pPipelines and &packet.createInfoCount and a < packet.createInfoCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_EXT, ResourceID(packet.pPipelines[a]), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyPipeline : {
		packet_vkDestroyPipeline const&  packet = iter.Cast<packet_vkDestroyPipeline>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_EXT, ResourceID(packet.pipeline), iter, frame_id, EResOp::Destruct );
		break;
	}

	case VKTRACE_TPI_VK_vkCreatePipelineLayout : {
		packet_vkCreatePipelineLayout const&  packet = iter.Cast<packet_vkCreatePipelineLayout>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pPipelineLayout ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_LAYOUT_EXT, ResourceID(*packet.pPipelineLayout), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyPipelineLayout : {
		packet_vkDestroyPipelineLayout const&  packet = iter.Cast<packet_vkDestroyPipelineLayout>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_LAYOUT_EXT, ResourceID(packet.pipelineLayout), iter, frame_id, EResOp::Destruct );
		break;
	}

	case VKTRACE_TPI_VK_vkCreateSampler : {
		packet_vkCreateSampler const&  packet = iter.Cast<packet_vkCreateSampler>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pSampler ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_EXT, ResourceID(*packet.pSampler), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroySampler : {
		packet_vkDestroySampler const&  packet = iter.Cast<packet_vkDestroySampler>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_EXT, ResourceID(packet.sampler), iter, frame_id, EResOp::Destruct );
		break;
	}

	case VKTRACE_TPI_VK_vkCreateDescriptorSetLayout : {
		packet_vkCreateDescriptorSetLayout const&  packet = iter.Cast<packet_vkCreateDescriptorSetLayout>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pSetLayout ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT_EXT, ResourceID(*packet.pSetLayout), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyDescriptorSetLayout : {
		packet_vkDestroyDescriptorSetLayout const&  packet = iter.Cast<packet_vkDestroyDescriptorSetLayout>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT_EXT, ResourceID(packet.descriptorSetLayout), iter, frame_id, EResOp::Destruct );
		break;
	}

	case VKTRACE_TPI_VK_vkCreateDescriptorPool : {
		packet_vkCreateDescriptorPool const&  packet = iter.Cast<packet_vkCreateDescriptorPool>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pDescriptorPool ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_POOL_EXT, ResourceID(*packet.pDescriptorPool), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyDescriptorPool : {
		packet_vkDestroyDescriptorPool const&  packet = iter.Cast<packet_vkDestroyDescriptorPool>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_POOL_EXT, ResourceID(packet.descriptorPool), iter, frame_id, EResOp::Destruct );
		break;
	}

	case VKTRACE_TPI_VK_vkResetDescriptorPool : {
		packet_vkResetDescriptorPool const&  packet = iter.Cast<packet_vkResetDescriptorPool>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_POOL_EXT, ResourceID(packet.descriptorPool), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkAllocateDescriptorSets : {
		packet_vkAllocateDescriptorSets const&  packet = iter.Cast<packet_vkAllocateDescriptorSets>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pAllocateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pAllocateInfo)), iter, frame_id );
		}
		for (uint a = 0; packet.pDescriptorSets and &packet.pAllocateInfo->descriptorSetCount and a < packet.pAllocateInfo->descriptorSetCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_EXT, ResourceID(packet.pDescriptorSets[a]), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkFreeDescriptorSets : {
		packet_vkFreeDescriptorSets const&  packet = iter.Cast<packet_vkFreeDescriptorSets>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_POOL_EXT, ResourceID(packet.descriptorPool), iter, frame_id, EResOp::Access );
		for (uint a = 0; packet.pDescriptorSets and &packet.descriptorSetCount and a < packet.descriptorSetCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_EXT, ResourceID(packet.pDescriptorSets[a]), iter, frame_id, EResOp::Destruct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkUpdateDescriptorSets : {
		packet_vkUpdateDescriptorSets const&  packet = iter.Cast<packet_vkUpdateDescriptorSets>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		for (uint a = 0; packet.pDescriptorWrites and a < packet.descriptorWriteCount; ++a) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(packet.pDescriptorWrites[a])), iter, frame_id );
		}
		for (uint a = 0; packet.pDescriptorCopies and a < packet.descriptorCopyCount; ++a) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(packet.pDescriptorCopies[a])), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkCreateFramebuffer : {
		packet_vkCreateFramebuffer const&  packet = iter.Cast<packet_vkCreateFramebuffer>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pFramebuffer ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_FRAMEBUFFER_EXT, ResourceID(*packet.pFramebuffer), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyFramebuffer : {
		packet_vkDestroyFramebuffer const&  packet = iter.Cast<packet_vkDestroyFramebuffer>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_FRAMEBUFFER_EXT, ResourceID(packet.framebuffer), iter, frame_id, EResOp::Destruct );
		break;
	}

	case VKTRACE_TPI_VK_vkCreateRenderPass : {
		packet_vkCreateRenderPass const&  packet = iter.Cast<packet_vkCreateRenderPass>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pRenderPass ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_RENDER_PASS_EXT, ResourceID(*packet.pRenderPass), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyRenderPass : {
		packet_vkDestroyRenderPass const&  packet = iter.Cast<packet_vkDestroyRenderPass>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_RENDER_PASS_EXT, ResourceID(packet.renderPass), iter, frame_id, EResOp::Destruct );
		break;
	}

	case VKTRACE_TPI_VK_vkGetRenderAreaGranularity : {
		packet_vkGetRenderAreaGranularity const&  packet = iter.Cast<packet_vkGetRenderAreaGranularity>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_RENDER_PASS_EXT, ResourceID(packet.renderPass), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCreateCommandPool : {
		packet_vkCreateCommandPool const&  packet = iter.Cast<packet_vkCreateCommandPool>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pCommandPool ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_POOL_EXT, ResourceID(*packet.pCommandPool), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyCommandPool : {
		packet_vkDestroyCommandPool const&  packet = iter.Cast<packet_vkDestroyCommandPool>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_POOL_EXT, ResourceID(packet.commandPool), iter, frame_id, EResOp::Destruct );
		break;
	}

	case VKTRACE_TPI_VK_vkResetCommandPool : {
		packet_vkResetCommandPool const&  packet = iter.Cast<packet_vkResetCommandPool>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_POOL_EXT, ResourceID(packet.commandPool), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkAllocateCommandBuffers : {
		packet_vkAllocateCommandBuffers const&  packet = iter.Cast<packet_vkAllocateCommandBuffers>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pAllocateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pAllocateInfo)), iter, frame_id );
		}
		for (uint a = 0; packet.pCommandBuffers and &packet.pAllocateInfo->commandBufferCount and a < packet.pAllocateInfo->commandBufferCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.pCommandBuffers[a]), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkFreeCommandBuffers : {
		packet_vkFreeCommandBuffers const&  packet = iter.Cast<packet_vkFreeCommandBuffers>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_POOL_EXT, ResourceID(packet.commandPool), iter, frame_id, EResOp::Access );
		for (uint a = 0; packet.pCommandBuffers and &packet.commandBufferCount and a < packet.commandBufferCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.pCommandBuffers[a]), iter, frame_id, EResOp::Destruct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkBeginCommandBuffer : {
		packet_vkBeginCommandBuffer const&  packet = iter.Cast<packet_vkBeginCommandBuffer>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		if ( packet.pBeginInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pBeginInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkEndCommandBuffer : {
		packet_vkEndCommandBuffer const&  packet = iter.Cast<packet_vkEndCommandBuffer>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkResetCommandBuffer : {
		packet_vkResetCommandBuffer const&  packet = iter.Cast<packet_vkResetCommandBuffer>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdBindPipeline : {
		packet_vkCmdBindPipeline const&  packet = iter.Cast<packet_vkCmdBindPipeline>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_EXT, ResourceID(packet.pipeline), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetViewport : {
		packet_vkCmdSetViewport const&  packet = iter.Cast<packet_vkCmdSetViewport>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetScissor : {
		packet_vkCmdSetScissor const&  packet = iter.Cast<packet_vkCmdSetScissor>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetLineWidth : {
		packet_vkCmdSetLineWidth const&  packet = iter.Cast<packet_vkCmdSetLineWidth>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetDepthBias : {
		packet_vkCmdSetDepthBias const&  packet = iter.Cast<packet_vkCmdSetDepthBias>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetBlendConstants : {
		packet_vkCmdSetBlendConstants const&  packet = iter.Cast<packet_vkCmdSetBlendConstants>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetDepthBounds : {
		packet_vkCmdSetDepthBounds const&  packet = iter.Cast<packet_vkCmdSetDepthBounds>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetStencilCompareMask : {
		packet_vkCmdSetStencilCompareMask const&  packet = iter.Cast<packet_vkCmdSetStencilCompareMask>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetStencilWriteMask : {
		packet_vkCmdSetStencilWriteMask const&  packet = iter.Cast<packet_vkCmdSetStencilWriteMask>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetStencilReference : {
		packet_vkCmdSetStencilReference const&  packet = iter.Cast<packet_vkCmdSetStencilReference>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdBindDescriptorSets : {
		packet_vkCmdBindDescriptorSets const&  packet = iter.Cast<packet_vkCmdBindDescriptorSets>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_LAYOUT_EXT, ResourceID(packet.layout), iter, frame_id, EResOp::Access );
		for (uint a = 0; packet.pDescriptorSets and &packet.descriptorSetCount and a < packet.descriptorSetCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_EXT, ResourceID(packet.pDescriptorSets[a]), iter, frame_id, EResOp::Access );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkCmdBindIndexBuffer : {
		packet_vkCmdBindIndexBuffer const&  packet = iter.Cast<packet_vkCmdBindIndexBuffer>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID(packet.buffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdBindVertexBuffers : {
		packet_vkCmdBindVertexBuffers const&  packet = iter.Cast<packet_vkCmdBindVertexBuffers>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		for (uint a = 0; packet.pBuffers and &packet.bindingCount and a < packet.bindingCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID(packet.pBuffers[a]), iter, frame_id, EResOp::Access );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDraw : {
		packet_vkCmdDraw const&  packet = iter.Cast<packet_vkCmdDraw>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDrawIndexed : {
		packet_vkCmdDrawIndexed const&  packet = iter.Cast<packet_vkCmdDrawIndexed>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDrawIndirect : {
		packet_vkCmdDrawIndirect const&  packet = iter.Cast<packet_vkCmdDrawIndirect>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID(packet.buffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDrawIndexedIndirect : {
		packet_vkCmdDrawIndexedIndirect const&  packet = iter.Cast<packet_vkCmdDrawIndexedIndirect>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID(packet.buffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDispatch : {
		packet_vkCmdDispatch const&  packet = iter.Cast<packet_vkCmdDispatch>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDispatchIndirect : {
		packet_vkCmdDispatchIndirect const&  packet = iter.Cast<packet_vkCmdDispatchIndirect>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID(packet.buffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdCopyBuffer : {
		packet_vkCmdCopyBuffer const&  packet = iter.Cast<packet_vkCmdCopyBuffer>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID(packet.srcBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID(packet.dstBuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdCopyImage : {
		packet_vkCmdCopyImage const&  packet = iter.Cast<packet_vkCmdCopyImage>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, ResourceID(packet.srcImage), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, ResourceID(packet.dstImage), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdBlitImage : {
		packet_vkCmdBlitImage const&  packet = iter.Cast<packet_vkCmdBlitImage>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, ResourceID(packet.srcImage), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, ResourceID(packet.dstImage), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdCopyBufferToImage : {
		packet_vkCmdCopyBufferToImage const&  packet = iter.Cast<packet_vkCmdCopyBufferToImage>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID(packet.srcBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, ResourceID(packet.dstImage), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdCopyImageToBuffer : {
		packet_vkCmdCopyImageToBuffer const&  packet = iter.Cast<packet_vkCmdCopyImageToBuffer>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, ResourceID(packet.srcImage), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID(packet.dstBuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdUpdateBuffer : {
		packet_vkCmdUpdateBuffer const&  packet = iter.Cast<packet_vkCmdUpdateBuffer>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID(packet.dstBuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdFillBuffer : {
		packet_vkCmdFillBuffer const&  packet = iter.Cast<packet_vkCmdFillBuffer>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID(packet.dstBuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdClearColorImage : {
		packet_vkCmdClearColorImage const&  packet = iter.Cast<packet_vkCmdClearColorImage>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, ResourceID(packet.image), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdClearDepthStencilImage : {
		packet_vkCmdClearDepthStencilImage const&  packet = iter.Cast<packet_vkCmdClearDepthStencilImage>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, ResourceID(packet.image), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdClearAttachments : {
		packet_vkCmdClearAttachments const&  packet = iter.Cast<packet_vkCmdClearAttachments>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdResolveImage : {
		packet_vkCmdResolveImage const&  packet = iter.Cast<packet_vkCmdResolveImage>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, ResourceID(packet.srcImage), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, ResourceID(packet.dstImage), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetEvent : {
		packet_vkCmdSetEvent const&  packet = iter.Cast<packet_vkCmdSetEvent>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_EVENT_EXT, ResourceID(packet.event), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdResetEvent : {
		packet_vkCmdResetEvent const&  packet = iter.Cast<packet_vkCmdResetEvent>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_EVENT_EXT, ResourceID(packet.event), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdWaitEvents : {
		packet_vkCmdWaitEvents const&  packet = iter.Cast<packet_vkCmdWaitEvents>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		for (uint a = 0; packet.pEvents and &packet.eventCount and a < packet.eventCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_EVENT_EXT, ResourceID(packet.pEvents[a]), iter, frame_id, EResOp::Access );
		}
		for (uint a = 0; packet.pMemoryBarriers and a < packet.memoryBarrierCount; ++a) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(packet.pMemoryBarriers[a])), iter, frame_id );
		}
		for (uint a = 0; packet.pBufferMemoryBarriers and a < packet.bufferMemoryBarrierCount; ++a) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(packet.pBufferMemoryBarriers[a])), iter, frame_id );
		}
		for (uint a = 0; packet.pImageMemoryBarriers and a < packet.imageMemoryBarrierCount; ++a) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(packet.pImageMemoryBarriers[a])), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkCmdPipelineBarrier : {
		packet_vkCmdPipelineBarrier const&  packet = iter.Cast<packet_vkCmdPipelineBarrier>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		for (uint a = 0; packet.pMemoryBarriers and a < packet.memoryBarrierCount; ++a) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(packet.pMemoryBarriers[a])), iter, frame_id );
		}
		for (uint a = 0; packet.pBufferMemoryBarriers and a < packet.bufferMemoryBarrierCount; ++a) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(packet.pBufferMemoryBarriers[a])), iter, frame_id );
		}
		for (uint a = 0; packet.pImageMemoryBarriers and a < packet.imageMemoryBarrierCount; ++a) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(packet.pImageMemoryBarriers[a])), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkCmdBeginQuery : {
		packet_vkCmdBeginQuery const&  packet = iter.Cast<packet_vkCmdBeginQuery>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_QUERY_POOL_EXT, ResourceID(packet.queryPool), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdEndQuery : {
		packet_vkCmdEndQuery const&  packet = iter.Cast<packet_vkCmdEndQuery>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_QUERY_POOL_EXT, ResourceID(packet.queryPool), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdResetQueryPool : {
		packet_vkCmdResetQueryPool const&  packet = iter.Cast<packet_vkCmdResetQueryPool>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_QUERY_POOL_EXT, ResourceID(packet.queryPool), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdWriteTimestamp : {
		packet_vkCmdWriteTimestamp const&  packet = iter.Cast<packet_vkCmdWriteTimestamp>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_QUERY_POOL_EXT, ResourceID(packet.queryPool), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdCopyQueryPoolResults : {
		packet_vkCmdCopyQueryPoolResults const&  packet = iter.Cast<packet_vkCmdCopyQueryPoolResults>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_QUERY_POOL_EXT, ResourceID(packet.queryPool), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, ResourceID(packet.dstBuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdPushConstants : {
		packet_vkCmdPushConstants const&  packet = iter.Cast<packet_vkCmdPushConstants>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_LAYOUT_EXT, ResourceID(packet.layout), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdBeginRenderPass : {
		packet_vkCmdBeginRenderPass const&  packet = iter.Cast<packet_vkCmdBeginRenderPass>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		if ( packet.pRenderPassBegin ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pRenderPassBegin)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkCmdNextSubpass : {
		packet_vkCmdNextSubpass const&  packet = iter.Cast<packet_vkCmdNextSubpass>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdEndRenderPass : {
		packet_vkCmdEndRenderPass const&  packet = iter.Cast<packet_vkCmdEndRenderPass>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdExecuteCommands : {
		packet_vkCmdExecuteCommands const&  packet = iter.Cast<packet_vkCmdExecuteCommands>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		for (uint a = 0; packet.pCommandBuffers and &packet.commandBufferCount and a < packet.commandBufferCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.pCommandBuffers[a]), iter, frame_id, EResOp::Access );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroySurfaceKHR : {
		packet_vkDestroySurfaceKHR const&  packet = iter.Cast<packet_vkDestroySurfaceKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT, ResourceID(packet.instance), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SURFACE_KHR_EXT, ResourceID(packet.surface), iter, frame_id, EResOp::Destruct );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceSupportKHR : {
		packet_vkGetPhysicalDeviceSurfaceSupportKHR const&  packet = iter.Cast<packet_vkGetPhysicalDeviceSurfaceSupportKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SURFACE_KHR_EXT, ResourceID(packet.surface), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceCapabilitiesKHR : {
		packet_vkGetPhysicalDeviceSurfaceCapabilitiesKHR const&  packet = iter.Cast<packet_vkGetPhysicalDeviceSurfaceCapabilitiesKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SURFACE_KHR_EXT, ResourceID(packet.surface), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceFormatsKHR : {
		packet_vkGetPhysicalDeviceSurfaceFormatsKHR const&  packet = iter.Cast<packet_vkGetPhysicalDeviceSurfaceFormatsKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SURFACE_KHR_EXT, ResourceID(packet.surface), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfacePresentModesKHR : {
		packet_vkGetPhysicalDeviceSurfacePresentModesKHR const&  packet = iter.Cast<packet_vkGetPhysicalDeviceSurfacePresentModesKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SURFACE_KHR_EXT, ResourceID(packet.surface), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCreateSwapchainKHR : {
		packet_vkCreateSwapchainKHR const&  packet = iter.Cast<packet_vkCreateSwapchainKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pSwapchain ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT, ResourceID(*packet.pSwapchain), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroySwapchainKHR : {
		packet_vkDestroySwapchainKHR const&  packet = iter.Cast<packet_vkDestroySwapchainKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT, ResourceID(packet.swapchain), iter, frame_id, EResOp::Destruct );
		break;
	}

	case VKTRACE_TPI_VK_vkGetSwapchainImagesKHR : {
		packet_vkGetSwapchainImagesKHR const&  packet = iter.Cast<packet_vkGetSwapchainImagesKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT, ResourceID(packet.swapchain), iter, frame_id, EResOp::Access );
		for (uint a = 0; packet.pSwapchainImages and &packet.pSwapchainImageCount[0] and a < packet.pSwapchainImageCount[0]; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, ResourceID(packet.pSwapchainImages[a]), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkAcquireNextImageKHR : {
		packet_vkAcquireNextImageKHR const&  packet = iter.Cast<packet_vkAcquireNextImageKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT, ResourceID(packet.swapchain), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT, ResourceID(packet.semaphore), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT, ResourceID(packet.fence), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkQueuePresentKHR : {
		packet_vkQueuePresentKHR const&  packet = iter.Cast<packet_vkQueuePresentKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT, ResourceID(packet.queue), iter, frame_id, EResOp::Access );
		if ( packet.pPresentInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pPresentInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkCreateSharedSwapchainsKHR : {
		packet_vkCreateSharedSwapchainsKHR const&  packet = iter.Cast<packet_vkCreateSharedSwapchainsKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		for (uint a = 0; packet.pCreateInfos and a < packet.swapchainCount; ++a) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(packet.pCreateInfos[a])), iter, frame_id );
		}
		for (uint a = 0; packet.pSwapchains and &packet.swapchainCount and a < packet.swapchainCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT, ResourceID(packet.pSwapchains[a]), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkCreateWin32SurfaceKHR : {
		packet_vkCreateWin32SurfaceKHR const&  packet = iter.Cast<packet_vkCreateWin32SurfaceKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT, ResourceID(packet.instance), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pSurface ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SURFACE_KHR_EXT, ResourceID(*packet.pSurface), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceWin32PresentationSupportKHR : {
		packet_vkGetPhysicalDeviceWin32PresentationSupportKHR const&  packet = iter.Cast<packet_vkGetPhysicalDeviceWin32PresentationSupportKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCreateXlibSurfaceKHR : {
		packet_vkCreateXlibSurfaceKHR const&  packet = iter.Cast<packet_vkCreateXlibSurfaceKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT, ResourceID(packet.instance), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pSurface ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SURFACE_KHR_EXT, ResourceID(*packet.pSurface), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceXlibPresentationSupportKHR : {
		packet_vkGetPhysicalDeviceXlibPresentationSupportKHR const&  packet = iter.Cast<packet_vkGetPhysicalDeviceXlibPresentationSupportKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCreateXcbSurfaceKHR : {
		packet_vkCreateXcbSurfaceKHR const&  packet = iter.Cast<packet_vkCreateXcbSurfaceKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT, ResourceID(packet.instance), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pSurface ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SURFACE_KHR_EXT, ResourceID(*packet.pSurface), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceXcbPresentationSupportKHR : {
		packet_vkGetPhysicalDeviceXcbPresentationSupportKHR const&  packet = iter.Cast<packet_vkGetPhysicalDeviceXcbPresentationSupportKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCreateAndroidSurfaceKHR : {
		packet_vkCreateAndroidSurfaceKHR const&  packet = iter.Cast<packet_vkCreateAndroidSurfaceKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT, ResourceID(packet.instance), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pSurface ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SURFACE_KHR_EXT, ResourceID(*packet.pSurface), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetMemoryWin32HandleNV : {
		packet_vkGetMemoryWin32HandleNV const&  packet = iter.Cast<packet_vkGetMemoryWin32HandleNV>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, ResourceID(packet.memory), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCreateDescriptorUpdateTemplateKHR : {
		packet_vkCreateDescriptorUpdateTemplateKHR const&  packet = iter.Cast<packet_vkCreateDescriptorUpdateTemplateKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pDescriptorUpdateTemplate ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_EXT, ResourceID(*packet.pDescriptorUpdateTemplate), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyDescriptorUpdateTemplateKHR : {
		packet_vkDestroyDescriptorUpdateTemplateKHR const&  packet = iter.Cast<packet_vkDestroyDescriptorUpdateTemplateKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_EXT, ResourceID(packet.descriptorUpdateTemplate), iter, frame_id, EResOp::Destruct );
		break;
	}

	case VKTRACE_TPI_VK_vkUpdateDescriptorSetWithTemplateKHR : {
		packet_vkUpdateDescriptorSetWithTemplateKHR const&  packet = iter.Cast<packet_vkUpdateDescriptorSetWithTemplateKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_EXT, ResourceID(packet.descriptorSet), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_EXT, ResourceID(packet.descriptorUpdateTemplate), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdPushDescriptorSetWithTemplateKHR : {
		packet_vkCmdPushDescriptorSetWithTemplateKHR const&  packet = iter.Cast<packet_vkCmdPushDescriptorSetWithTemplateKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_EXT, ResourceID(packet.descriptorUpdateTemplate), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_LAYOUT_EXT, ResourceID(packet.layout), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCreateWaylandSurfaceKHR : {
		packet_vkCreateWaylandSurfaceKHR const&  packet = iter.Cast<packet_vkCreateWaylandSurfaceKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT, ResourceID(packet.instance), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pSurface ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SURFACE_KHR_EXT, ResourceID(*packet.pSurface), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceWaylandPresentationSupportKHR : {
		packet_vkGetPhysicalDeviceWaylandPresentationSupportKHR const&  packet = iter.Cast<packet_vkGetPhysicalDeviceWaylandPresentationSupportKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceFeatures2KHR : {
		packet_vkGetPhysicalDeviceFeatures2KHR const&  packet = iter.Cast<packet_vkGetPhysicalDeviceFeatures2KHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceProperties2KHR : {
		packet_vkGetPhysicalDeviceProperties2KHR const&  packet = iter.Cast<packet_vkGetPhysicalDeviceProperties2KHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceFormatProperties2KHR : {
		packet_vkGetPhysicalDeviceFormatProperties2KHR const&  packet = iter.Cast<packet_vkGetPhysicalDeviceFormatProperties2KHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceImageFormatProperties2KHR : {
		packet_vkGetPhysicalDeviceImageFormatProperties2KHR const&  packet = iter.Cast<packet_vkGetPhysicalDeviceImageFormatProperties2KHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		if ( packet.pImageFormatInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pImageFormatInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceQueueFamilyProperties2KHR : {
		packet_vkGetPhysicalDeviceQueueFamilyProperties2KHR const&  packet = iter.Cast<packet_vkGetPhysicalDeviceQueueFamilyProperties2KHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceMemoryProperties2KHR : {
		packet_vkGetPhysicalDeviceMemoryProperties2KHR const&  packet = iter.Cast<packet_vkGetPhysicalDeviceMemoryProperties2KHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSparseImageFormatProperties2KHR : {
		packet_vkGetPhysicalDeviceSparseImageFormatProperties2KHR const&  packet = iter.Cast<packet_vkGetPhysicalDeviceSparseImageFormatProperties2KHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		if ( packet.pFormatInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pFormatInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetImageMemoryRequirements2KHR : {
		packet_vkGetImageMemoryRequirements2KHR const&  packet = iter.Cast<packet_vkGetImageMemoryRequirements2KHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetBufferMemoryRequirements2KHR : {
		packet_vkGetBufferMemoryRequirements2KHR const&  packet = iter.Cast<packet_vkGetBufferMemoryRequirements2KHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetImageSparseMemoryRequirements2KHR : {
		packet_vkGetImageSparseMemoryRequirements2KHR const&  packet = iter.Cast<packet_vkGetImageSparseMemoryRequirements2KHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceCapabilities2KHR : {
		packet_vkGetPhysicalDeviceSurfaceCapabilities2KHR const&  packet = iter.Cast<packet_vkGetPhysicalDeviceSurfaceCapabilities2KHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		if ( packet.pSurfaceInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pSurfaceInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceFormats2KHR : {
		packet_vkGetPhysicalDeviceSurfaceFormats2KHR const&  packet = iter.Cast<packet_vkGetPhysicalDeviceSurfaceFormats2KHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		if ( packet.pSurfaceInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pSurfaceInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceDisplayPropertiesKHR : {
		packet_vkGetPhysicalDeviceDisplayPropertiesKHR const&  packet = iter.Cast<packet_vkGetPhysicalDeviceDisplayPropertiesKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceDisplayPlanePropertiesKHR : {
		packet_vkGetPhysicalDeviceDisplayPlanePropertiesKHR const&  packet = iter.Cast<packet_vkGetPhysicalDeviceDisplayPlanePropertiesKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetDisplayModePropertiesKHR : {
		packet_vkGetDisplayModePropertiesKHR const&  packet = iter.Cast<packet_vkGetDisplayModePropertiesKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DISPLAY_KHR_EXT, ResourceID(packet.display), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCreateDisplayModeKHR : {
		packet_vkCreateDisplayModeKHR const&  packet = iter.Cast<packet_vkCreateDisplayModeKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DISPLAY_KHR_EXT, ResourceID(packet.display), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pMode ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DISPLAY_MODE_KHR_EXT, ResourceID(*packet.pMode), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetDisplayPlaneCapabilitiesKHR : {
		packet_vkGetDisplayPlaneCapabilitiesKHR const&  packet = iter.Cast<packet_vkGetDisplayPlaneCapabilitiesKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DISPLAY_MODE_KHR_EXT, ResourceID(packet.mode), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCreateDisplayPlaneSurfaceKHR : {
		packet_vkCreateDisplayPlaneSurfaceKHR const&  packet = iter.Cast<packet_vkCreateDisplayPlaneSurfaceKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT, ResourceID(packet.instance), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pSurface ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SURFACE_KHR_EXT, ResourceID(*packet.pSurface), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkTrimCommandPoolKHR : {
		packet_vkTrimCommandPoolKHR const&  packet = iter.Cast<packet_vkTrimCommandPoolKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_POOL_EXT, ResourceID(packet.commandPool), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalBufferPropertiesKHR : {
		packet_vkGetPhysicalDeviceExternalBufferPropertiesKHR const&  packet = iter.Cast<packet_vkGetPhysicalDeviceExternalBufferPropertiesKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		if ( packet.pExternalBufferInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pExternalBufferInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetMemoryFdKHR : {
		packet_vkGetMemoryFdKHR const&  packet = iter.Cast<packet_vkGetMemoryFdKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pGetFdInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pGetFdInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetMemoryFdPropertiesKHR : {
		packet_vkGetMemoryFdPropertiesKHR const&  packet = iter.Cast<packet_vkGetMemoryFdPropertiesKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR : {
		packet_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR const&  packet = iter.Cast<packet_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		if ( packet.pExternalSemaphoreInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pExternalSemaphoreInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkImportSemaphoreFdKHR : {
		packet_vkImportSemaphoreFdKHR const&  packet = iter.Cast<packet_vkImportSemaphoreFdKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pImportSemaphoreFdInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pImportSemaphoreFdInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetSemaphoreFdKHR : {
		packet_vkGetSemaphoreFdKHR const&  packet = iter.Cast<packet_vkGetSemaphoreFdKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pGetFdInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pGetFdInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkCmdPushDescriptorSetKHR : {
		packet_vkCmdPushDescriptorSetKHR const&  packet = iter.Cast<packet_vkCmdPushDescriptorSetKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_LAYOUT_EXT, ResourceID(packet.layout), iter, frame_id, EResOp::Access );
		for (uint a = 0; packet.pDescriptorWrites and a < packet.descriptorWriteCount; ++a) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(packet.pDescriptorWrites[a])), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetSwapchainStatusKHR : {
		packet_vkGetSwapchainStatusKHR const&  packet = iter.Cast<packet_vkGetSwapchainStatusKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT, ResourceID(packet.swapchain), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalFencePropertiesKHR : {
		packet_vkGetPhysicalDeviceExternalFencePropertiesKHR const&  packet = iter.Cast<packet_vkGetPhysicalDeviceExternalFencePropertiesKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		if ( packet.pExternalFenceInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pExternalFenceInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetDeviceGroupPeerMemoryFeaturesKHX : break;
	case VKTRACE_TPI_VK_vkBindBufferMemory2KHR : {
		packet_vkBindBufferMemory2KHR const&  packet = iter.Cast<packet_vkBindBufferMemory2KHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		for (uint a = 0; packet.pBindInfos and a < packet.bindInfoCount; ++a) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(packet.pBindInfos[a])), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkBindImageMemory2KHR : {
		packet_vkBindImageMemory2KHR const&  packet = iter.Cast<packet_vkBindImageMemory2KHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		for (uint a = 0; packet.pBindInfos and a < packet.bindInfoCount; ++a) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(packet.pBindInfos[a])), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetDeviceMaskKHX : break;
	case VKTRACE_TPI_VK_vkGetDeviceGroupPresentCapabilitiesKHX : break;
	case VKTRACE_TPI_VK_vkGetDeviceGroupSurfacePresentModesKHX : break;
	case VKTRACE_TPI_VK_vkAcquireNextImage2KHX : break;
	case VKTRACE_TPI_VK_vkCmdDispatchBaseKHX : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDevicePresentRectanglesKHX : break;
	case VKTRACE_TPI_VK_vkEnumeratePhysicalDeviceGroupsKHX : break;
	case VKTRACE_TPI_VK_vkCmdProcessCommandsNVX : {
		packet_vkCmdProcessCommandsNVX const&  packet = iter.Cast<packet_vkCmdProcessCommandsNVX>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		if ( packet.pProcessCommandsInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pProcessCommandsInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkCmdReserveSpaceForCommandsNVX : {
		packet_vkCmdReserveSpaceForCommandsNVX const&  packet = iter.Cast<packet_vkCmdReserveSpaceForCommandsNVX>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		if ( packet.pReserveSpaceInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pReserveSpaceInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkCreateIndirectCommandsLayoutNVX : {
		packet_vkCreateIndirectCommandsLayoutNVX const&  packet = iter.Cast<packet_vkCreateIndirectCommandsLayoutNVX>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pIndirectCommandsLayout ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_NVX_EXT, ResourceID(*packet.pIndirectCommandsLayout), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyIndirectCommandsLayoutNVX : {
		packet_vkDestroyIndirectCommandsLayoutNVX const&  packet = iter.Cast<packet_vkDestroyIndirectCommandsLayoutNVX>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_NVX_EXT, ResourceID(packet.indirectCommandsLayout), iter, frame_id, EResOp::Destruct );
		break;
	}

	case VKTRACE_TPI_VK_vkCreateObjectTableNVX : {
		packet_vkCreateObjectTableNVX const&  packet = iter.Cast<packet_vkCreateObjectTableNVX>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pObjectTable ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_OBJECT_TABLE_NVX_EXT, ResourceID(*packet.pObjectTable), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyObjectTableNVX : {
		packet_vkDestroyObjectTableNVX const&  packet = iter.Cast<packet_vkDestroyObjectTableNVX>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_OBJECT_TABLE_NVX_EXT, ResourceID(packet.objectTable), iter, frame_id, EResOp::Destruct );
		break;
	}

	case VKTRACE_TPI_VK_vkRegisterObjectsNVX : {
		packet_vkRegisterObjectsNVX const&  packet = iter.Cast<packet_vkRegisterObjectsNVX>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_OBJECT_TABLE_NVX_EXT, ResourceID(packet.objectTable), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkUnregisterObjectsNVX : {
		packet_vkUnregisterObjectsNVX const&  packet = iter.Cast<packet_vkUnregisterObjectsNVX>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_OBJECT_TABLE_NVX_EXT, ResourceID(packet.objectTable), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX : {
		packet_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX const&  packet = iter.Cast<packet_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetViewportWScalingNV : {
		packet_vkCmdSetViewportWScalingNV const&  packet = iter.Cast<packet_vkCmdSetViewportWScalingNV>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkReleaseDisplayEXT : {
		packet_vkReleaseDisplayEXT const&  packet = iter.Cast<packet_vkReleaseDisplayEXT>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DISPLAY_KHR_EXT, ResourceID(packet.display), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceCapabilities2EXT : {
		packet_vkGetPhysicalDeviceSurfaceCapabilities2EXT const&  packet = iter.Cast<packet_vkGetPhysicalDeviceSurfaceCapabilities2EXT>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SURFACE_KHR_EXT, ResourceID(packet.surface), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetRefreshCycleDurationGOOGLE : {
		packet_vkGetRefreshCycleDurationGOOGLE const&  packet = iter.Cast<packet_vkGetRefreshCycleDurationGOOGLE>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT, ResourceID(packet.swapchain), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPastPresentationTimingGOOGLE : {
		packet_vkGetPastPresentationTimingGOOGLE const&  packet = iter.Cast<packet_vkGetPastPresentationTimingGOOGLE>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT, ResourceID(packet.swapchain), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetDiscardRectangleEXT : {
		packet_vkCmdSetDiscardRectangleEXT const&  packet = iter.Cast<packet_vkCmdSetDiscardRectangleEXT>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkSetHdrMetadataEXT : {
		packet_vkSetHdrMetadataEXT const&  packet = iter.Cast<packet_vkSetHdrMetadataEXT>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		for (uint a = 0; packet.pSwapchains and &packet.swapchainCount and a < packet.swapchainCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT, ResourceID(packet.pSwapchains[a]), iter, frame_id, EResOp::Access );
		}
		for (uint a = 0; packet.pMetadata and a < packet.swapchainCount; ++a) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(packet.pMetadata[a])), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkAcquireXlibDisplayEXT : {
		packet_vkAcquireXlibDisplayEXT const&  packet = iter.Cast<packet_vkAcquireXlibDisplayEXT>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DISPLAY_KHR_EXT, ResourceID(packet.display), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetRandROutputDisplayEXT : {
		packet_vkGetRandROutputDisplayEXT const&  packet = iter.Cast<packet_vkGetRandROutputDisplayEXT>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		if ( packet.pDisplay ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DISPLAY_KHR_EXT, ResourceID(*packet.pDisplay), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDisplayPowerControlEXT : {
		packet_vkDisplayPowerControlEXT const&  packet = iter.Cast<packet_vkDisplayPowerControlEXT>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DISPLAY_KHR_EXT, ResourceID(packet.display), iter, frame_id, EResOp::Access );
		if ( packet.pDisplayPowerInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pDisplayPowerInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkRegisterDeviceEventEXT : {
		packet_vkRegisterDeviceEventEXT const&  packet = iter.Cast<packet_vkRegisterDeviceEventEXT>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pDeviceEventInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pDeviceEventInfo)), iter, frame_id );
		}
		if ( packet.pFence ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT, ResourceID(*packet.pFence), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkRegisterDisplayEventEXT : {
		packet_vkRegisterDisplayEventEXT const&  packet = iter.Cast<packet_vkRegisterDisplayEventEXT>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DISPLAY_KHR_EXT, ResourceID(packet.display), iter, frame_id, EResOp::Access );
		if ( packet.pDisplayEventInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pDisplayEventInfo)), iter, frame_id );
		}
		if ( packet.pFence ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT, ResourceID(*packet.pFence), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetSwapchainCounterEXT : {
		packet_vkGetSwapchainCounterEXT const&  packet = iter.Cast<packet_vkGetSwapchainCounterEXT>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT, ResourceID(packet.swapchain), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetSampleLocationsEXT : {
		packet_vkCmdSetSampleLocationsEXT const&  packet = iter.Cast<packet_vkCmdSetSampleLocationsEXT>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		if ( packet.pSampleLocationsInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pSampleLocationsInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceMultisamplePropertiesEXT : {
		packet_vkGetPhysicalDeviceMultisamplePropertiesEXT const&  packet = iter.Cast<packet_vkGetPhysicalDeviceMultisamplePropertiesEXT>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCreateSamplerYcbcrConversionKHR : {
		packet_vkCreateSamplerYcbcrConversionKHR const&  packet = iter.Cast<packet_vkCreateSamplerYcbcrConversionKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pYcbcrConversion ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION_EXT, ResourceID(*packet.pYcbcrConversion), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroySamplerYcbcrConversionKHR : {
		packet_vkDestroySamplerYcbcrConversionKHR const&  packet = iter.Cast<packet_vkDestroySamplerYcbcrConversionKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION_EXT, ResourceID(packet.ycbcrConversion), iter, frame_id, EResOp::Destruct );
		break;
	}

	case VKTRACE_TPI_VK_vkGetDisplayPlaneSupportedDisplaysKHR : {
		packet_vkGetDisplayPlaneSupportedDisplaysKHR const&  packet = iter.Cast<packet_vkGetDisplayPlaneSupportedDisplaysKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		if ( packet.pDisplays ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DISPLAY_KHR_EXT, ResourceID(*packet.pDisplays), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkImportFenceFdKHR : {
		packet_vkImportFenceFdKHR const&  packet = iter.Cast<packet_vkImportFenceFdKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pImportFenceFdInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pImportFenceFdInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetFenceFdKHR : {
		packet_vkGetFenceFdKHR const&  packet = iter.Cast<packet_vkGetFenceFdKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pGetFdInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pGetFdInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkImportFenceWin32HandleKHR : {
		packet_vkImportFenceWin32HandleKHR const&  packet = iter.Cast<packet_vkImportFenceWin32HandleKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pImportFenceWin32HandleInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pImportFenceWin32HandleInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetFenceWin32HandleKHR : {
		packet_vkGetFenceWin32HandleKHR const&  packet = iter.Cast<packet_vkGetFenceWin32HandleKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pGetWin32HandleInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pGetWin32HandleInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetMemoryWin32HandleKHR : {
		packet_vkGetMemoryWin32HandleKHR const&  packet = iter.Cast<packet_vkGetMemoryWin32HandleKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pGetWin32HandleInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pGetWin32HandleInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetMemoryWin32HandlePropertiesKHR : {
		packet_vkGetMemoryWin32HandlePropertiesKHR const&  packet = iter.Cast<packet_vkGetMemoryWin32HandlePropertiesKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkImportSemaphoreWin32HandleKHR : {
		packet_vkImportSemaphoreWin32HandleKHR const&  packet = iter.Cast<packet_vkImportSemaphoreWin32HandleKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pImportSemaphoreWin32HandleInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pImportSemaphoreWin32HandleInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetSemaphoreWin32HandleKHR : {
		packet_vkGetSemaphoreWin32HandleKHR const&  packet = iter.Cast<packet_vkGetSemaphoreWin32HandleKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pGetWin32HandleInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pGetWin32HandleInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetMemoryHostPointerPropertiesEXT : {
		packet_vkGetMemoryHostPointerPropertiesEXT const&  packet = iter.Cast<packet_vkGetMemoryHostPointerPropertiesEXT>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCreateValidationCacheEXT : {
		packet_vkCreateValidationCacheEXT const&  packet = iter.Cast<packet_vkCreateValidationCacheEXT>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pValidationCache ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_VALIDATION_CACHE_EXT_EXT, ResourceID(*packet.pValidationCache), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyValidationCacheEXT : {
		packet_vkDestroyValidationCacheEXT const&  packet = iter.Cast<packet_vkDestroyValidationCacheEXT>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_VALIDATION_CACHE_EXT_EXT, ResourceID(packet.validationCache), iter, frame_id, EResOp::Destruct );
		break;
	}

	case VKTRACE_TPI_VK_vkMergeValidationCachesEXT : {
		packet_vkMergeValidationCachesEXT const&  packet = iter.Cast<packet_vkMergeValidationCachesEXT>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_VALIDATION_CACHE_EXT_EXT, ResourceID(packet.dstCache), iter, frame_id, EResOp::Access );
		for (uint a = 0; packet.pSrcCaches and &packet.srcCacheCount and a < packet.srcCacheCount; ++a) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_VALIDATION_CACHE_EXT_EXT, ResourceID(packet.pSrcCaches[a]), iter, frame_id, EResOp::Access );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetValidationCacheDataEXT : {
		packet_vkGetValidationCacheDataEXT const&  packet = iter.Cast<packet_vkGetValidationCacheDataEXT>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_VALIDATION_CACHE_EXT_EXT, ResourceID(packet.validationCache), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetShaderInfoAMD : {
		packet_vkGetShaderInfoAMD const&  packet = iter.Cast<packet_vkGetShaderInfoAMD>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_EXT, ResourceID(packet.pipeline), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetDeviceQueue2 : {
		packet_vkGetDeviceQueue2 const&  packet = iter.Cast<packet_vkGetDeviceQueue2>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pQueueInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pQueueInfo)), iter, frame_id );
		}
		if ( packet.pQueue ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT, ResourceID(*packet.pQueue), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkEnumerateInstanceVersion : break;
	case VKTRACE_TPI_VK_vkGetDescriptorSetLayoutSupport : {
		packet_vkGetDescriptorSetLayoutSupport const&  packet = iter.Cast<packet_vkGetDescriptorSetLayoutSupport>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetDeviceGroupPresentCapabilitiesKHR : {
		packet_vkGetDeviceGroupPresentCapabilitiesKHR const&  packet = iter.Cast<packet_vkGetDeviceGroupPresentCapabilitiesKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetDeviceGroupSurfacePresentModesKHR : {
		packet_vkGetDeviceGroupSurfacePresentModesKHR const&  packet = iter.Cast<packet_vkGetDeviceGroupSurfacePresentModesKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SURFACE_KHR_EXT, ResourceID(packet.surface), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDevicePresentRectanglesKHR : {
		packet_vkGetPhysicalDevicePresentRectanglesKHR const&  packet = iter.Cast<packet_vkGetPhysicalDevicePresentRectanglesKHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SURFACE_KHR_EXT, ResourceID(packet.surface), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkAcquireNextImage2KHR : {
		packet_vkAcquireNextImage2KHR const&  packet = iter.Cast<packet_vkAcquireNextImage2KHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pAcquireInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pAcquireInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkBindBufferMemory2 : {
		packet_vkBindBufferMemory2 const&  packet = iter.Cast<packet_vkBindBufferMemory2>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		for (uint a = 0; packet.pBindInfos and a < packet.bindInfoCount; ++a) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(packet.pBindInfos[a])), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkBindImageMemory2 : {
		packet_vkBindImageMemory2 const&  packet = iter.Cast<packet_vkBindImageMemory2>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		for (uint a = 0; packet.pBindInfos and a < packet.bindInfoCount; ++a) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(packet.pBindInfos[a])), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetDeviceGroupPeerMemoryFeatures : {
		packet_vkGetDeviceGroupPeerMemoryFeatures const&  packet = iter.Cast<packet_vkGetDeviceGroupPeerMemoryFeatures>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetDeviceMask : {
		packet_vkCmdSetDeviceMask const&  packet = iter.Cast<packet_vkCmdSetDeviceMask>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDispatchBase : {
		packet_vkCmdDispatchBase const&  packet = iter.Cast<packet_vkCmdDispatchBase>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, ResourceID(packet.commandBuffer), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkEnumeratePhysicalDeviceGroups : {
		packet_vkEnumeratePhysicalDeviceGroups const&  packet = iter.Cast<packet_vkEnumeratePhysicalDeviceGroups>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT, ResourceID(packet.instance), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetImageMemoryRequirements2 : {
		packet_vkGetImageMemoryRequirements2 const&  packet = iter.Cast<packet_vkGetImageMemoryRequirements2>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetBufferMemoryRequirements2 : {
		packet_vkGetBufferMemoryRequirements2 const&  packet = iter.Cast<packet_vkGetBufferMemoryRequirements2>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetImageSparseMemoryRequirements2 : {
		packet_vkGetImageSparseMemoryRequirements2 const&  packet = iter.Cast<packet_vkGetImageSparseMemoryRequirements2>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceFeatures2 : {
		packet_vkGetPhysicalDeviceFeatures2 const&  packet = iter.Cast<packet_vkGetPhysicalDeviceFeatures2>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceProperties2 : {
		packet_vkGetPhysicalDeviceProperties2 const&  packet = iter.Cast<packet_vkGetPhysicalDeviceProperties2>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceFormatProperties2 : {
		packet_vkGetPhysicalDeviceFormatProperties2 const&  packet = iter.Cast<packet_vkGetPhysicalDeviceFormatProperties2>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceImageFormatProperties2 : {
		packet_vkGetPhysicalDeviceImageFormatProperties2 const&  packet = iter.Cast<packet_vkGetPhysicalDeviceImageFormatProperties2>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		if ( packet.pImageFormatInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pImageFormatInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceQueueFamilyProperties2 : {
		packet_vkGetPhysicalDeviceQueueFamilyProperties2 const&  packet = iter.Cast<packet_vkGetPhysicalDeviceQueueFamilyProperties2>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceMemoryProperties2 : {
		packet_vkGetPhysicalDeviceMemoryProperties2 const&  packet = iter.Cast<packet_vkGetPhysicalDeviceMemoryProperties2>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSparseImageFormatProperties2 : {
		packet_vkGetPhysicalDeviceSparseImageFormatProperties2 const&  packet = iter.Cast<packet_vkGetPhysicalDeviceSparseImageFormatProperties2>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		if ( packet.pFormatInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pFormatInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkTrimCommandPool : {
		packet_vkTrimCommandPool const&  packet = iter.Cast<packet_vkTrimCommandPool>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_POOL_EXT, ResourceID(packet.commandPool), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkCreateSamplerYcbcrConversion : {
		packet_vkCreateSamplerYcbcrConversion const&  packet = iter.Cast<packet_vkCreateSamplerYcbcrConversion>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pYcbcrConversion ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION_EXT, ResourceID(*packet.pYcbcrConversion), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroySamplerYcbcrConversion : {
		packet_vkDestroySamplerYcbcrConversion const&  packet = iter.Cast<packet_vkDestroySamplerYcbcrConversion>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION_EXT, ResourceID(packet.ycbcrConversion), iter, frame_id, EResOp::Destruct );
		break;
	}

	case VKTRACE_TPI_VK_vkCreateDescriptorUpdateTemplate : {
		packet_vkCreateDescriptorUpdateTemplate const&  packet = iter.Cast<packet_vkCreateDescriptorUpdateTemplate>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		if ( packet.pCreateInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pCreateInfo)), iter, frame_id );
		}
		if ( packet.pDescriptorUpdateTemplate ) {
			_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_EXT, ResourceID(*packet.pDescriptorUpdateTemplate), iter, frame_id, EResOp::Construct );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyDescriptorUpdateTemplate : {
		packet_vkDestroyDescriptorUpdateTemplate const&  packet = iter.Cast<packet_vkDestroyDescriptorUpdateTemplate>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_EXT, ResourceID(packet.descriptorUpdateTemplate), iter, frame_id, EResOp::Destruct );
		break;
	}

	case VKTRACE_TPI_VK_vkUpdateDescriptorSetWithTemplate : {
		packet_vkUpdateDescriptorSetWithTemplate const&  packet = iter.Cast<packet_vkUpdateDescriptorSetWithTemplate>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, ResourceID(packet.device), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_EXT, ResourceID(packet.descriptorSet), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_EXT, ResourceID(packet.descriptorUpdateTemplate), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalBufferProperties : {
		packet_vkGetPhysicalDeviceExternalBufferProperties const&  packet = iter.Cast<packet_vkGetPhysicalDeviceExternalBufferProperties>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		if ( packet.pExternalBufferInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pExternalBufferInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalFenceProperties : {
		packet_vkGetPhysicalDeviceExternalFenceProperties const&  packet = iter.Cast<packet_vkGetPhysicalDeviceExternalFenceProperties>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		if ( packet.pExternalFenceInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pExternalFenceInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalSemaphoreProperties : {
		packet_vkGetPhysicalDeviceExternalSemaphoreProperties const&  packet = iter.Cast<packet_vkGetPhysicalDeviceExternalSemaphoreProperties>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		if ( packet.pExternalSemaphoreInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pExternalSemaphoreInfo)), iter, frame_id );
		}
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceDisplayProperties2KHR : {
		packet_vkGetPhysicalDeviceDisplayProperties2KHR const&  packet = iter.Cast<packet_vkGetPhysicalDeviceDisplayProperties2KHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceDisplayPlaneProperties2KHR : {
		packet_vkGetPhysicalDeviceDisplayPlaneProperties2KHR const&  packet = iter.Cast<packet_vkGetPhysicalDeviceDisplayPlaneProperties2KHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetDisplayModeProperties2KHR : {
		packet_vkGetDisplayModeProperties2KHR const&  packet = iter.Cast<packet_vkGetDisplayModeProperties2KHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_DISPLAY_KHR_EXT, ResourceID(packet.display), iter, frame_id, EResOp::Access );
		break;
	}

	case VKTRACE_TPI_VK_vkGetDisplayPlaneCapabilities2KHR : {
		packet_vkGetDisplayPlaneCapabilities2KHR const&  packet = iter.Cast<packet_vkGetDisplayPlaneCapabilities2KHR>();
		_AddResourceBookmark( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, ResourceID(packet.physicalDevice), iter, frame_id, EResOp::Access );
		if ( packet.pDisplayPlaneInfo ) {
			_AddStructBookmsrks( BitCast<VkBaseInStructure const*>(&(*packet.pDisplayPlaneInfo)), iter, frame_id );
		}
		break;
	}

}
DISABLE_ENUM_CHECKS();
