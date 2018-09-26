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
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalImageFormatPropertiesNV : break;
	case VKTRACE_TPI_VK_vkCmdDrawIndirectCountAMD : break;
	case VKTRACE_TPI_VK_vkCmdDrawIndexedIndirectCountAMD : break;
	case VKTRACE_TPI_VK_vkCreateDebugReportCallbackEXT : break;
	case VKTRACE_TPI_VK_vkDestroyDebugReportCallbackEXT : break;
	case VKTRACE_TPI_VK_vkDebugReportMessageEXT : break;
	case VKTRACE_TPI_VK_vkDebugMarkerSetObjectTagEXT : break;
	case VKTRACE_TPI_VK_vkDebugMarkerSetObjectNameEXT : {
		auto const*  obj = iter.Cast< packet_vkDebugMarkerSetObjectNameEXT *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VDebugMarkerSetObjectNameEXT );
		packer << (obj->device);
		packer.Push( obj->pNameInfo );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pNameInfo), packer );
		packer.Pop( obj->pNameInfo );
		packer.End( EPacketID::VDebugMarkerSetObjectNameEXT );
	}

	case VKTRACE_TPI_VK_vkCmdDebugMarkerBeginEXT : {
		auto const*  obj = iter.Cast< packet_vkCmdDebugMarkerBeginEXT *>();
		packer.Begin( EPacketID::VCmdDebugMarkerBeginEXT );
		packer << (obj->commandBuffer);
		packer.Push( obj->pMarkerInfo );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pMarkerInfo), packer );
		packer.Pop( obj->pMarkerInfo );
		packer.End( EPacketID::VCmdDebugMarkerBeginEXT );
	}

	case VKTRACE_TPI_VK_vkCmdDebugMarkerEndEXT : {
		auto const*  obj = iter.Cast< packet_vkCmdDebugMarkerEndEXT *>();
		packer.Begin( EPacketID::VCmdDebugMarkerEndEXT );
		packer << (obj->commandBuffer);
		packer.End( EPacketID::VCmdDebugMarkerEndEXT );
	}

	case VKTRACE_TPI_VK_vkCmdDebugMarkerInsertEXT : {
		auto const*  obj = iter.Cast< packet_vkCmdDebugMarkerInsertEXT *>();
		packer.Begin( EPacketID::VCmdDebugMarkerInsertEXT );
		packer << (obj->commandBuffer);
		packer.Push( obj->pMarkerInfo );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pMarkerInfo), packer );
		packer.Pop( obj->pMarkerInfo );
		packer.End( EPacketID::VCmdDebugMarkerInsertEXT );
	}

	case VKTRACE_TPI_VK_vkCreateInstance : break;
	case VKTRACE_TPI_VK_vkDestroyInstance : break;
	case VKTRACE_TPI_VK_vkEnumeratePhysicalDevices : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceFeatures : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceFormatProperties : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceImageFormatProperties : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceProperties : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceQueueFamilyProperties : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceMemoryProperties : break;
	case VKTRACE_TPI_VK_vkGetInstanceProcAddr : break;
	case VKTRACE_TPI_VK_vkGetDeviceProcAddr : break;
	case VKTRACE_TPI_VK_vkCreateDevice : break;
	case VKTRACE_TPI_VK_vkDestroyDevice : break;
	case VKTRACE_TPI_VK_vkEnumerateInstanceExtensionProperties : break;
	case VKTRACE_TPI_VK_vkEnumerateDeviceExtensionProperties : break;
	case VKTRACE_TPI_VK_vkEnumerateInstanceLayerProperties : break;
	case VKTRACE_TPI_VK_vkEnumerateDeviceLayerProperties : break;
	case VKTRACE_TPI_VK_vkGetDeviceQueue : {
		auto const*  obj = iter.Cast< packet_vkGetDeviceQueue *>();
		packer.Begin( EPacketID::VGetDeviceQueue );
		packer << (obj->device);
		packer << (obj->queueFamilyIndex);
		packer << (obj->queueIndex);
		packer << (obj->pQueue);
		packer.End( EPacketID::VGetDeviceQueue );
	}

	case VKTRACE_TPI_VK_vkQueueSubmit : {
		auto const*  obj = iter.Cast< packet_vkQueueSubmit *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VQueueSubmit );
		packer << (obj->queue);
		packer << (obj->submitCount);
		packer.Push( obj->pSubmits, obj->submitCount );
		for (uint i = 0; obj->pSubmits and i < obj->submitCount; ++i) {
			VPackStruct( BitCast<VkBaseInStructure const*>(obj->pSubmits + i), packer );
		}
		packer.Pop( obj->pSubmits );
		packer << (obj->fence);
		packer.End( EPacketID::VQueueSubmit );
	}

	case VKTRACE_TPI_VK_vkQueueWaitIdle : {
		auto const*  obj = iter.Cast< packet_vkQueueWaitIdle *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VQueueWaitIdle );
		packer << (obj->queue);
		packer.End( EPacketID::VQueueWaitIdle );
	}

	case VKTRACE_TPI_VK_vkDeviceWaitIdle : {
		auto const*  obj = iter.Cast< packet_vkDeviceWaitIdle *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VDeviceWaitIdle );
		packer << (obj->device);
		packer.End( EPacketID::VDeviceWaitIdle );
	}

	case VKTRACE_TPI_VK_vkAllocateMemory : {
		auto const*  obj = iter.Cast< packet_vkAllocateMemory *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VAllocateMemory );
		packer << (obj->device);
		packer.Push( obj->pAllocateInfo );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pAllocateInfo), packer );
		packer.Pop( obj->pAllocateInfo );
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer << (obj->pMemory);
		packer.End( EPacketID::VAllocateMemory );
	}

	case VKTRACE_TPI_VK_vkFreeMemory : {
		auto const*  obj = iter.Cast< packet_vkFreeMemory *>();
		packer.Begin( EPacketID::VFreeMemory );
		packer << (obj->device);
		packer << (obj->memory);
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer.End( EPacketID::VFreeMemory );
	}

	case VKTRACE_TPI_VK_vkMapMemory : break;
	case VKTRACE_TPI_VK_vkUnmapMemory : break;
	case VKTRACE_TPI_VK_vkFlushMappedMemoryRanges : {
		auto const*  obj = iter.Cast< packet_vkFlushMappedMemoryRanges *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VFlushMappedMemoryRanges );
		packer << (obj->device);
		packer << (obj->memoryRangeCount);
		packer.Push( obj->pMemoryRanges, obj->memoryRangeCount );
		for (uint i = 0; obj->pMemoryRanges and i < obj->memoryRangeCount; ++i) {
			VPackStruct( BitCast<VkBaseInStructure const*>(obj->pMemoryRanges + i), packer );
		}
		packer.Pop( obj->pMemoryRanges );
		packer.End( EPacketID::VFlushMappedMemoryRanges );
	}

	case VKTRACE_TPI_VK_vkInvalidateMappedMemoryRanges : break;
	case VKTRACE_TPI_VK_vkGetDeviceMemoryCommitment : break;
	case VKTRACE_TPI_VK_vkBindBufferMemory : {
		auto const*  obj = iter.Cast< packet_vkBindBufferMemory *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VBindBufferMemory );
		packer << (obj->device);
		packer << (obj->buffer);
		packer << (obj->memory);
		packer << (obj->memoryOffset);
		packer.End( EPacketID::VBindBufferMemory );
	}

	case VKTRACE_TPI_VK_vkBindImageMemory : {
		auto const*  obj = iter.Cast< packet_vkBindImageMemory *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VBindImageMemory );
		packer << (obj->device);
		packer << (obj->image);
		packer << (obj->memory);
		packer << (obj->memoryOffset);
		packer.End( EPacketID::VBindImageMemory );
	}

	case VKTRACE_TPI_VK_vkGetBufferMemoryRequirements : break;
	case VKTRACE_TPI_VK_vkGetImageMemoryRequirements : break;
	case VKTRACE_TPI_VK_vkGetImageSparseMemoryRequirements : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSparseImageFormatProperties : break;
	case VKTRACE_TPI_VK_vkQueueBindSparse : {
		auto const*  obj = iter.Cast< packet_vkQueueBindSparse *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VQueueBindSparse );
		packer << (obj->queue);
		packer << (obj->bindInfoCount);
		packer.Push( obj->pBindInfo, obj->bindInfoCount );
		for (uint i = 0; obj->pBindInfo and i < obj->bindInfoCount; ++i) {
			VPackStruct( BitCast<VkBaseInStructure const*>(obj->pBindInfo + i), packer );
		}
		packer.Pop( obj->pBindInfo );
		packer << (obj->fence);
		packer.End( EPacketID::VQueueBindSparse );
	}

	case VKTRACE_TPI_VK_vkCreateFence : {
		auto const*  obj = iter.Cast< packet_vkCreateFence *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VCreateFence );
		packer << (obj->device);
		packer.Push( obj->pCreateInfo );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), packer );
		packer.Pop( obj->pCreateInfo );
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer << (obj->pFence);
		packer.End( EPacketID::VCreateFence );
	}

	case VKTRACE_TPI_VK_vkDestroyFence : {
		auto const*  obj = iter.Cast< packet_vkDestroyFence *>();
		packer.Begin( EPacketID::VDestroyFence );
		packer << (obj->device);
		packer << (obj->fence);
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer.End( EPacketID::VDestroyFence );
	}

	case VKTRACE_TPI_VK_vkResetFences : {
		auto const*  obj = iter.Cast< packet_vkResetFences *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VResetFences );
		packer << (obj->device);
		packer << (obj->fenceCount);
		packer.Push( obj->pFences, obj->fenceCount );
		for (uint i = 0; obj->pFences and i < obj->fenceCount; ++i) {
			packer << (obj->pFences[i]);
		}
		packer.Pop( obj->pFences );
		packer.End( EPacketID::VResetFences );
	}

	case VKTRACE_TPI_VK_vkGetFenceStatus : break;
	case VKTRACE_TPI_VK_vkWaitForFences : {
		auto const*  obj = iter.Cast< packet_vkWaitForFences *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VWaitForFences );
		packer << (obj->device);
		packer << (obj->fenceCount);
		packer.Push( obj->pFences, obj->fenceCount );
		for (uint i = 0; obj->pFences and i < obj->fenceCount; ++i) {
			packer << (obj->pFences[i]);
		}
		packer.Pop( obj->pFences );
		packer << (obj->waitAll);
		packer << (obj->timeout);
		packer.End( EPacketID::VWaitForFences );
	}

	case VKTRACE_TPI_VK_vkCreateSemaphore : {
		auto const*  obj = iter.Cast< packet_vkCreateSemaphore *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VCreateSemaphore );
		packer << (obj->device);
		packer.Push( obj->pCreateInfo );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), packer );
		packer.Pop( obj->pCreateInfo );
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer << (obj->pSemaphore);
		packer.End( EPacketID::VCreateSemaphore );
	}

	case VKTRACE_TPI_VK_vkDestroySemaphore : {
		auto const*  obj = iter.Cast< packet_vkDestroySemaphore *>();
		packer.Begin( EPacketID::VDestroySemaphore );
		packer << (obj->device);
		packer << (obj->semaphore);
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer.End( EPacketID::VDestroySemaphore );
	}

	case VKTRACE_TPI_VK_vkCreateEvent : {
		auto const*  obj = iter.Cast< packet_vkCreateEvent *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VCreateEvent );
		packer << (obj->device);
		packer.Push( obj->pCreateInfo );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), packer );
		packer.Pop( obj->pCreateInfo );
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer << (obj->pEvent);
		packer.End( EPacketID::VCreateEvent );
	}

	case VKTRACE_TPI_VK_vkDestroyEvent : {
		auto const*  obj = iter.Cast< packet_vkDestroyEvent *>();
		packer.Begin( EPacketID::VDestroyEvent );
		packer << (obj->device);
		packer << (obj->event);
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer.End( EPacketID::VDestroyEvent );
	}

	case VKTRACE_TPI_VK_vkGetEventStatus : break;
	case VKTRACE_TPI_VK_vkSetEvent : {
		auto const*  obj = iter.Cast< packet_vkSetEvent *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VSetEvent );
		packer << (obj->device);
		packer << (obj->event);
		packer.End( EPacketID::VSetEvent );
	}

	case VKTRACE_TPI_VK_vkResetEvent : {
		auto const*  obj = iter.Cast< packet_vkResetEvent *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VResetEvent );
		packer << (obj->device);
		packer << (obj->event);
		packer.End( EPacketID::VResetEvent );
	}

	case VKTRACE_TPI_VK_vkCreateQueryPool : {
		auto const*  obj = iter.Cast< packet_vkCreateQueryPool *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VCreateQueryPool );
		packer << (obj->device);
		packer.Push( obj->pCreateInfo );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), packer );
		packer.Pop( obj->pCreateInfo );
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer << (obj->pQueryPool);
		packer.End( EPacketID::VCreateQueryPool );
	}

	case VKTRACE_TPI_VK_vkDestroyQueryPool : {
		auto const*  obj = iter.Cast< packet_vkDestroyQueryPool *>();
		packer.Begin( EPacketID::VDestroyQueryPool );
		packer << (obj->device);
		packer << (obj->queryPool);
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer.End( EPacketID::VDestroyQueryPool );
	}

	case VKTRACE_TPI_VK_vkGetQueryPoolResults : break;
	case VKTRACE_TPI_VK_vkCreateBuffer : {
		auto const*  obj = iter.Cast< packet_vkCreateBuffer *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VCreateBuffer );
		packer << (obj->device);
		packer.Push( obj->pCreateInfo );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), packer );
		packer.Pop( obj->pCreateInfo );
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer << (obj->pBuffer);
		packer.End( EPacketID::VCreateBuffer );
	}

	case VKTRACE_TPI_VK_vkDestroyBuffer : {
		auto const*  obj = iter.Cast< packet_vkDestroyBuffer *>();
		packer.Begin( EPacketID::VDestroyBuffer );
		packer << (obj->device);
		packer << (obj->buffer);
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer.End( EPacketID::VDestroyBuffer );
	}

	case VKTRACE_TPI_VK_vkCreateBufferView : {
		auto const*  obj = iter.Cast< packet_vkCreateBufferView *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VCreateBufferView );
		packer << (obj->device);
		packer.Push( obj->pCreateInfo );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), packer );
		packer.Pop( obj->pCreateInfo );
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer << (obj->pView);
		packer.End( EPacketID::VCreateBufferView );
	}

	case VKTRACE_TPI_VK_vkDestroyBufferView : {
		auto const*  obj = iter.Cast< packet_vkDestroyBufferView *>();
		packer.Begin( EPacketID::VDestroyBufferView );
		packer << (obj->device);
		packer << (obj->bufferView);
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer.End( EPacketID::VDestroyBufferView );
	}

	case VKTRACE_TPI_VK_vkCreateImage : {
		auto const*  obj = iter.Cast< packet_vkCreateImage *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VCreateImage );
		packer << (obj->device);
		packer.Push( obj->pCreateInfo );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), packer );
		packer.Pop( obj->pCreateInfo );
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer << (obj->pImage);
		packer.End( EPacketID::VCreateImage );
	}

	case VKTRACE_TPI_VK_vkDestroyImage : {
		auto const*  obj = iter.Cast< packet_vkDestroyImage *>();
		packer.Begin( EPacketID::VDestroyImage );
		packer << (obj->device);
		packer << (obj->image);
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer.End( EPacketID::VDestroyImage );
	}

	case VKTRACE_TPI_VK_vkGetImageSubresourceLayout : break;
	case VKTRACE_TPI_VK_vkCreateImageView : {
		auto const*  obj = iter.Cast< packet_vkCreateImageView *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VCreateImageView );
		packer << (obj->device);
		packer.Push( obj->pCreateInfo );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), packer );
		packer.Pop( obj->pCreateInfo );
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer << (obj->pView);
		packer.End( EPacketID::VCreateImageView );
	}

	case VKTRACE_TPI_VK_vkDestroyImageView : {
		auto const*  obj = iter.Cast< packet_vkDestroyImageView *>();
		packer.Begin( EPacketID::VDestroyImageView );
		packer << (obj->device);
		packer << (obj->imageView);
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer.End( EPacketID::VDestroyImageView );
	}

	case VKTRACE_TPI_VK_vkCreateShaderModule : break;
	case VKTRACE_TPI_VK_vkDestroyShaderModule : {
		auto const*  obj = iter.Cast< packet_vkDestroyShaderModule *>();
		packer.Begin( EPacketID::VDestroyShaderModule );
		packer << (obj->device);
		packer << (obj->shaderModule);
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer.End( EPacketID::VDestroyShaderModule );
	}

	case VKTRACE_TPI_VK_vkCreatePipelineCache : break;
	case VKTRACE_TPI_VK_vkDestroyPipelineCache : {
		auto const*  obj = iter.Cast< packet_vkDestroyPipelineCache *>();
		packer.Begin( EPacketID::VDestroyPipelineCache );
		packer << (obj->device);
		packer << (obj->pipelineCache);
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer.End( EPacketID::VDestroyPipelineCache );
	}

	case VKTRACE_TPI_VK_vkGetPipelineCacheData : break;
	case VKTRACE_TPI_VK_vkMergePipelineCaches : {
		auto const*  obj = iter.Cast< packet_vkMergePipelineCaches *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VMergePipelineCaches );
		packer << (obj->device);
		packer << (obj->dstCache);
		packer << (obj->srcCacheCount);
		packer.Push( obj->pSrcCaches, obj->srcCacheCount );
		for (uint i = 0; obj->pSrcCaches and i < obj->srcCacheCount; ++i) {
			packer << (obj->pSrcCaches[i]);
		}
		packer.Pop( obj->pSrcCaches );
		packer.End( EPacketID::VMergePipelineCaches );
	}

	case VKTRACE_TPI_VK_vkCreateGraphicsPipelines : {
		auto const*  obj = iter.Cast< packet_vkCreateGraphicsPipelines *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VCreateGraphicsPipelines );
		packer << (obj->device);
		packer << (obj->pipelineCache);
		packer << (obj->createInfoCount);
		packer.Push( obj->pCreateInfos, obj->createInfoCount );
		for (uint i = 0; obj->pCreateInfos and i < obj->createInfoCount; ++i) {
			VPackStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfos + i), packer );
		}
		packer.Pop( obj->pCreateInfos );
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer.Push( obj->pPipelines, obj->createInfoCount );
		for (uint i = 0; obj->pPipelines and i < obj->createInfoCount; ++i) {
			packer << (obj->pPipelines[i]);
		}
		packer.Pop( obj->pPipelines );
		packer.End( EPacketID::VCreateGraphicsPipelines );
	}

	case VKTRACE_TPI_VK_vkCreateComputePipelines : {
		auto const*  obj = iter.Cast< packet_vkCreateComputePipelines *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VCreateComputePipelines );
		packer << (obj->device);
		packer << (obj->pipelineCache);
		packer << (obj->createInfoCount);
		packer.Push( obj->pCreateInfos, obj->createInfoCount );
		for (uint i = 0; obj->pCreateInfos and i < obj->createInfoCount; ++i) {
			VPackStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfos + i), packer );
		}
		packer.Pop( obj->pCreateInfos );
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer.Push( obj->pPipelines, obj->createInfoCount );
		for (uint i = 0; obj->pPipelines and i < obj->createInfoCount; ++i) {
			packer << (obj->pPipelines[i]);
		}
		packer.Pop( obj->pPipelines );
		packer.End( EPacketID::VCreateComputePipelines );
	}

	case VKTRACE_TPI_VK_vkDestroyPipeline : {
		auto const*  obj = iter.Cast< packet_vkDestroyPipeline *>();
		packer.Begin( EPacketID::VDestroyPipeline );
		packer << (obj->device);
		packer << (obj->pipeline);
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer.End( EPacketID::VDestroyPipeline );
	}

	case VKTRACE_TPI_VK_vkCreatePipelineLayout : {
		auto const*  obj = iter.Cast< packet_vkCreatePipelineLayout *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VCreatePipelineLayout );
		packer << (obj->device);
		packer.Push( obj->pCreateInfo );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), packer );
		packer.Pop( obj->pCreateInfo );
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer << (obj->pPipelineLayout);
		packer.End( EPacketID::VCreatePipelineLayout );
	}

	case VKTRACE_TPI_VK_vkDestroyPipelineLayout : {
		auto const*  obj = iter.Cast< packet_vkDestroyPipelineLayout *>();
		packer.Begin( EPacketID::VDestroyPipelineLayout );
		packer << (obj->device);
		packer << (obj->pipelineLayout);
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer.End( EPacketID::VDestroyPipelineLayout );
	}

	case VKTRACE_TPI_VK_vkCreateSampler : {
		auto const*  obj = iter.Cast< packet_vkCreateSampler *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VCreateSampler );
		packer << (obj->device);
		packer.Push( obj->pCreateInfo );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), packer );
		packer.Pop( obj->pCreateInfo );
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer << (obj->pSampler);
		packer.End( EPacketID::VCreateSampler );
	}

	case VKTRACE_TPI_VK_vkDestroySampler : {
		auto const*  obj = iter.Cast< packet_vkDestroySampler *>();
		packer.Begin( EPacketID::VDestroySampler );
		packer << (obj->device);
		packer << (obj->sampler);
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer.End( EPacketID::VDestroySampler );
	}

	case VKTRACE_TPI_VK_vkCreateDescriptorSetLayout : {
		auto const*  obj = iter.Cast< packet_vkCreateDescriptorSetLayout *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VCreateDescriptorSetLayout );
		packer << (obj->device);
		packer.Push( obj->pCreateInfo );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), packer );
		packer.Pop( obj->pCreateInfo );
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer << (obj->pSetLayout);
		packer.End( EPacketID::VCreateDescriptorSetLayout );
	}

	case VKTRACE_TPI_VK_vkDestroyDescriptorSetLayout : {
		auto const*  obj = iter.Cast< packet_vkDestroyDescriptorSetLayout *>();
		packer.Begin( EPacketID::VDestroyDescriptorSetLayout );
		packer << (obj->device);
		packer << (obj->descriptorSetLayout);
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer.End( EPacketID::VDestroyDescriptorSetLayout );
	}

	case VKTRACE_TPI_VK_vkCreateDescriptorPool : {
		auto const*  obj = iter.Cast< packet_vkCreateDescriptorPool *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VCreateDescriptorPool );
		packer << (obj->device);
		packer.Push( obj->pCreateInfo );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), packer );
		packer.Pop( obj->pCreateInfo );
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer << (obj->pDescriptorPool);
		packer.End( EPacketID::VCreateDescriptorPool );
	}

	case VKTRACE_TPI_VK_vkDestroyDescriptorPool : {
		auto const*  obj = iter.Cast< packet_vkDestroyDescriptorPool *>();
		packer.Begin( EPacketID::VDestroyDescriptorPool );
		packer << (obj->device);
		packer << (obj->descriptorPool);
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer.End( EPacketID::VDestroyDescriptorPool );
	}

	case VKTRACE_TPI_VK_vkResetDescriptorPool : {
		auto const*  obj = iter.Cast< packet_vkResetDescriptorPool *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VResetDescriptorPool );
		packer << (obj->device);
		packer << (obj->descriptorPool);
		packer << (obj->flags);
		packer.End( EPacketID::VResetDescriptorPool );
	}

	case VKTRACE_TPI_VK_vkAllocateDescriptorSets : {
		auto const*  obj = iter.Cast< packet_vkAllocateDescriptorSets *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VAllocateDescriptorSets );
		packer << (obj->device);
		packer.Push( obj->pAllocateInfo );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pAllocateInfo), packer );
		packer.Pop( obj->pAllocateInfo );
		packer.Push( obj->pDescriptorSets, obj->pAllocateInfo->descriptorSetCount );
		for (uint i = 0; obj->pDescriptorSets and i < obj->pAllocateInfo->descriptorSetCount; ++i) {
			packer << (obj->pDescriptorSets[i]);
		}
		packer.Pop( obj->pDescriptorSets );
		packer.End( EPacketID::VAllocateDescriptorSets );
	}

	case VKTRACE_TPI_VK_vkFreeDescriptorSets : {
		auto const*  obj = iter.Cast< packet_vkFreeDescriptorSets *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VFreeDescriptorSets );
		packer << (obj->device);
		packer << (obj->descriptorPool);
		packer << (obj->descriptorSetCount);
		packer.Push( obj->pDescriptorSets, obj->descriptorSetCount );
		for (uint i = 0; obj->pDescriptorSets and i < obj->descriptorSetCount; ++i) {
			packer << (obj->pDescriptorSets[i]);
		}
		packer.Pop( obj->pDescriptorSets );
		packer.End( EPacketID::VFreeDescriptorSets );
	}

	case VKTRACE_TPI_VK_vkUpdateDescriptorSets : {
		auto const*  obj = iter.Cast< packet_vkUpdateDescriptorSets *>();
		packer.Begin( EPacketID::VUpdateDescriptorSets );
		packer << (obj->device);
		packer << (obj->descriptorWriteCount);
		packer.Push( obj->pDescriptorWrites, obj->descriptorWriteCount );
		for (uint i = 0; obj->pDescriptorWrites and i < obj->descriptorWriteCount; ++i) {
			VPackStruct( BitCast<VkBaseInStructure const*>(obj->pDescriptorWrites + i), packer );
		}
		packer.Pop( obj->pDescriptorWrites );
		packer << (obj->descriptorCopyCount);
		packer.Push( obj->pDescriptorCopies, obj->descriptorCopyCount );
		for (uint i = 0; obj->pDescriptorCopies and i < obj->descriptorCopyCount; ++i) {
			VPackStruct( BitCast<VkBaseInStructure const*>(obj->pDescriptorCopies + i), packer );
		}
		packer.Pop( obj->pDescriptorCopies );
		packer.End( EPacketID::VUpdateDescriptorSets );
	}

	case VKTRACE_TPI_VK_vkCreateFramebuffer : {
		auto const*  obj = iter.Cast< packet_vkCreateFramebuffer *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VCreateFramebuffer );
		packer << (obj->device);
		packer.Push( obj->pCreateInfo );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), packer );
		packer.Pop( obj->pCreateInfo );
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer << (obj->pFramebuffer);
		packer.End( EPacketID::VCreateFramebuffer );
	}

	case VKTRACE_TPI_VK_vkDestroyFramebuffer : {
		auto const*  obj = iter.Cast< packet_vkDestroyFramebuffer *>();
		packer.Begin( EPacketID::VDestroyFramebuffer );
		packer << (obj->device);
		packer << (obj->framebuffer);
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer.End( EPacketID::VDestroyFramebuffer );
	}

	case VKTRACE_TPI_VK_vkCreateRenderPass : {
		auto const*  obj = iter.Cast< packet_vkCreateRenderPass *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VCreateRenderPass );
		packer << (obj->device);
		packer.Push( obj->pCreateInfo );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), packer );
		packer.Pop( obj->pCreateInfo );
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer << (obj->pRenderPass);
		packer.End( EPacketID::VCreateRenderPass );
	}

	case VKTRACE_TPI_VK_vkDestroyRenderPass : {
		auto const*  obj = iter.Cast< packet_vkDestroyRenderPass *>();
		packer.Begin( EPacketID::VDestroyRenderPass );
		packer << (obj->device);
		packer << (obj->renderPass);
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer.End( EPacketID::VDestroyRenderPass );
	}

	case VKTRACE_TPI_VK_vkGetRenderAreaGranularity : break;
	case VKTRACE_TPI_VK_vkCreateCommandPool : {
		auto const*  obj = iter.Cast< packet_vkCreateCommandPool *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VCreateCommandPool );
		packer << (obj->device);
		packer.Push( obj->pCreateInfo );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), packer );
		packer.Pop( obj->pCreateInfo );
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer << (obj->pCommandPool);
		packer.End( EPacketID::VCreateCommandPool );
	}

	case VKTRACE_TPI_VK_vkDestroyCommandPool : {
		auto const*  obj = iter.Cast< packet_vkDestroyCommandPool *>();
		packer.Begin( EPacketID::VDestroyCommandPool );
		packer << (obj->device);
		packer << (obj->commandPool);
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer.End( EPacketID::VDestroyCommandPool );
	}

	case VKTRACE_TPI_VK_vkResetCommandPool : {
		auto const*  obj = iter.Cast< packet_vkResetCommandPool *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VResetCommandPool );
		packer << (obj->device);
		packer << (obj->commandPool);
		packer << (obj->flags);
		packer.End( EPacketID::VResetCommandPool );
	}

	case VKTRACE_TPI_VK_vkAllocateCommandBuffers : {
		auto const*  obj = iter.Cast< packet_vkAllocateCommandBuffers *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VAllocateCommandBuffers );
		packer << (obj->device);
		packer.Push( obj->pAllocateInfo );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pAllocateInfo), packer );
		packer.Pop( obj->pAllocateInfo );
		packer.Push( obj->pCommandBuffers, obj->pAllocateInfo->commandBufferCount );
		for (uint i = 0; obj->pCommandBuffers and i < obj->pAllocateInfo->commandBufferCount; ++i) {
			packer << (obj->pCommandBuffers[i]);
		}
		packer.Pop( obj->pCommandBuffers );
		packer.End( EPacketID::VAllocateCommandBuffers );
	}

	case VKTRACE_TPI_VK_vkFreeCommandBuffers : {
		auto const*  obj = iter.Cast< packet_vkFreeCommandBuffers *>();
		packer.Begin( EPacketID::VFreeCommandBuffers );
		packer << (obj->device);
		packer << (obj->commandPool);
		packer << (obj->commandBufferCount);
		packer.Push( obj->pCommandBuffers, obj->commandBufferCount );
		for (uint i = 0; obj->pCommandBuffers and i < obj->commandBufferCount; ++i) {
			packer << (obj->pCommandBuffers[i]);
		}
		packer.Pop( obj->pCommandBuffers );
		packer.End( EPacketID::VFreeCommandBuffers );
	}

	case VKTRACE_TPI_VK_vkBeginCommandBuffer : {
		auto const*  obj = iter.Cast< packet_vkBeginCommandBuffer *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VBeginCommandBuffer );
		packer << (obj->commandBuffer);
		packer.Push( obj->pBeginInfo );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pBeginInfo), packer );
		packer.Pop( obj->pBeginInfo );
		packer.End( EPacketID::VBeginCommandBuffer );
	}

	case VKTRACE_TPI_VK_vkEndCommandBuffer : {
		auto const*  obj = iter.Cast< packet_vkEndCommandBuffer *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VEndCommandBuffer );
		packer << (obj->commandBuffer);
		packer.End( EPacketID::VEndCommandBuffer );
	}

	case VKTRACE_TPI_VK_vkResetCommandBuffer : {
		auto const*  obj = iter.Cast< packet_vkResetCommandBuffer *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VResetCommandBuffer );
		packer << (obj->commandBuffer);
		packer << (obj->flags);
		packer.End( EPacketID::VResetCommandBuffer );
	}

	case VKTRACE_TPI_VK_vkCmdBindPipeline : {
		auto const*  obj = iter.Cast< packet_vkCmdBindPipeline *>();
		packer.Begin( EPacketID::VCmdBindPipeline );
		packer << (obj->commandBuffer);
		packer << (obj->pipelineBindPoint);
		packer << (obj->pipeline);
		packer.End( EPacketID::VCmdBindPipeline );
	}

	case VKTRACE_TPI_VK_vkCmdSetViewport : {
		auto const*  obj = iter.Cast< packet_vkCmdSetViewport *>();
		packer.Begin( EPacketID::VCmdSetViewport );
		packer << (obj->commandBuffer);
		packer << (obj->firstViewport);
		packer << (obj->viewportCount);
		packer.Push( obj->pViewports, obj->viewportCount );
		for (uint i = 0; obj->pViewports and i < obj->viewportCount; ++i) {
			VPack_VkViewport( obj->pViewports + i, packer );
		}
		packer.Pop( obj->pViewports );
		packer.End( EPacketID::VCmdSetViewport );
	}

	case VKTRACE_TPI_VK_vkCmdSetScissor : {
		auto const*  obj = iter.Cast< packet_vkCmdSetScissor *>();
		packer.Begin( EPacketID::VCmdSetScissor );
		packer << (obj->commandBuffer);
		packer << (obj->firstScissor);
		packer << (obj->scissorCount);
		packer.Push( obj->pScissors, obj->scissorCount );
		for (uint i = 0; obj->pScissors and i < obj->scissorCount; ++i) {
			VPack_VkRect2D( obj->pScissors + i, packer );
		}
		packer.Pop( obj->pScissors );
		packer.End( EPacketID::VCmdSetScissor );
	}

	case VKTRACE_TPI_VK_vkCmdSetLineWidth : {
		auto const*  obj = iter.Cast< packet_vkCmdSetLineWidth *>();
		packer.Begin( EPacketID::VCmdSetLineWidth );
		packer << (obj->commandBuffer);
		packer << (obj->lineWidth);
		packer.End( EPacketID::VCmdSetLineWidth );
	}

	case VKTRACE_TPI_VK_vkCmdSetDepthBias : {
		auto const*  obj = iter.Cast< packet_vkCmdSetDepthBias *>();
		packer.Begin( EPacketID::VCmdSetDepthBias );
		packer << (obj->commandBuffer);
		packer << (obj->depthBiasConstantFactor);
		packer << (obj->depthBiasClamp);
		packer << (obj->depthBiasSlopeFactor);
		packer.End( EPacketID::VCmdSetDepthBias );
	}

	case VKTRACE_TPI_VK_vkCmdSetBlendConstants : {
		auto const*  obj = iter.Cast< packet_vkCmdSetBlendConstants *>();
		packer.Begin( EPacketID::VCmdSetBlendConstants );
		packer << (obj->commandBuffer);
		packer.Push( obj->blendConstants, std::size(obj->blendConstants) );
		for (uint i = 0; obj->blendConstants and i < std::size(obj->blendConstants); ++i) {
			packer << (obj->blendConstants[i]);
		}
		packer.Pop( obj->blendConstants );
		packer.End( EPacketID::VCmdSetBlendConstants );
	}

	case VKTRACE_TPI_VK_vkCmdSetDepthBounds : {
		auto const*  obj = iter.Cast< packet_vkCmdSetDepthBounds *>();
		packer.Begin( EPacketID::VCmdSetDepthBounds );
		packer << (obj->commandBuffer);
		packer << (obj->minDepthBounds);
		packer << (obj->maxDepthBounds);
		packer.End( EPacketID::VCmdSetDepthBounds );
	}

	case VKTRACE_TPI_VK_vkCmdSetStencilCompareMask : {
		auto const*  obj = iter.Cast< packet_vkCmdSetStencilCompareMask *>();
		packer.Begin( EPacketID::VCmdSetStencilCompareMask );
		packer << (obj->commandBuffer);
		packer << (obj->faceMask);
		packer << (obj->compareMask);
		packer.End( EPacketID::VCmdSetStencilCompareMask );
	}

	case VKTRACE_TPI_VK_vkCmdSetStencilWriteMask : {
		auto const*  obj = iter.Cast< packet_vkCmdSetStencilWriteMask *>();
		packer.Begin( EPacketID::VCmdSetStencilWriteMask );
		packer << (obj->commandBuffer);
		packer << (obj->faceMask);
		packer << (obj->writeMask);
		packer.End( EPacketID::VCmdSetStencilWriteMask );
	}

	case VKTRACE_TPI_VK_vkCmdSetStencilReference : {
		auto const*  obj = iter.Cast< packet_vkCmdSetStencilReference *>();
		packer.Begin( EPacketID::VCmdSetStencilReference );
		packer << (obj->commandBuffer);
		packer << (obj->faceMask);
		packer << (obj->reference);
		packer.End( EPacketID::VCmdSetStencilReference );
	}

	case VKTRACE_TPI_VK_vkCmdBindDescriptorSets : {
		auto const*  obj = iter.Cast< packet_vkCmdBindDescriptorSets *>();
		packer.Begin( EPacketID::VCmdBindDescriptorSets );
		packer << (obj->commandBuffer);
		packer << (obj->pipelineBindPoint);
		packer << (obj->layout);
		packer << (obj->firstSet);
		packer << (obj->descriptorSetCount);
		packer.Push( obj->pDescriptorSets, obj->descriptorSetCount );
		for (uint i = 0; obj->pDescriptorSets and i < obj->descriptorSetCount; ++i) {
			packer << (obj->pDescriptorSets[i]);
		}
		packer.Pop( obj->pDescriptorSets );
		packer << (obj->dynamicOffsetCount);
		packer.Push( obj->pDynamicOffsets, obj->dynamicOffsetCount );
		for (uint i = 0; obj->pDynamicOffsets and i < obj->dynamicOffsetCount; ++i) {
			packer << (obj->pDynamicOffsets[i]);
		}
		packer.Pop( obj->pDynamicOffsets );
		packer.End( EPacketID::VCmdBindDescriptorSets );
	}

	case VKTRACE_TPI_VK_vkCmdBindIndexBuffer : {
		auto const*  obj = iter.Cast< packet_vkCmdBindIndexBuffer *>();
		packer.Begin( EPacketID::VCmdBindIndexBuffer );
		packer << (obj->commandBuffer);
		packer << (obj->buffer);
		packer << (obj->offset);
		packer << (obj->indexType);
		packer.End( EPacketID::VCmdBindIndexBuffer );
	}

	case VKTRACE_TPI_VK_vkCmdBindVertexBuffers : {
		auto const*  obj = iter.Cast< packet_vkCmdBindVertexBuffers *>();
		packer.Begin( EPacketID::VCmdBindVertexBuffers );
		packer << (obj->commandBuffer);
		packer << (obj->firstBinding);
		packer << (obj->bindingCount);
		packer.Push( obj->pBuffers, obj->bindingCount );
		for (uint i = 0; obj->pBuffers and i < obj->bindingCount; ++i) {
			packer << (obj->pBuffers[i]);
		}
		packer.Pop( obj->pBuffers );
		packer.Push( obj->pOffsets, obj->bindingCount );
		for (uint i = 0; obj->pOffsets and i < obj->bindingCount; ++i) {
			packer << (obj->pOffsets[i]);
		}
		packer.Pop( obj->pOffsets );
		packer.End( EPacketID::VCmdBindVertexBuffers );
	}

	case VKTRACE_TPI_VK_vkCmdDraw : {
		auto const*  obj = iter.Cast< packet_vkCmdDraw *>();
		packer.Begin( EPacketID::VCmdDraw );
		packer << (obj->commandBuffer);
		packer << (obj->vertexCount);
		packer << (obj->instanceCount);
		packer << (obj->firstVertex);
		packer << (obj->firstInstance);
		packer.End( EPacketID::VCmdDraw );
	}

	case VKTRACE_TPI_VK_vkCmdDrawIndexed : {
		auto const*  obj = iter.Cast< packet_vkCmdDrawIndexed *>();
		packer.Begin( EPacketID::VCmdDrawIndexed );
		packer << (obj->commandBuffer);
		packer << (obj->indexCount);
		packer << (obj->instanceCount);
		packer << (obj->firstIndex);
		packer << (obj->vertexOffset);
		packer << (obj->firstInstance);
		packer.End( EPacketID::VCmdDrawIndexed );
	}

	case VKTRACE_TPI_VK_vkCmdDrawIndirect : {
		auto const*  obj = iter.Cast< packet_vkCmdDrawIndirect *>();
		packer.Begin( EPacketID::VCmdDrawIndirect );
		packer << (obj->commandBuffer);
		packer << (obj->buffer);
		packer << (obj->offset);
		packer << (obj->drawCount);
		packer << (obj->stride);
		packer.End( EPacketID::VCmdDrawIndirect );
	}

	case VKTRACE_TPI_VK_vkCmdDrawIndexedIndirect : {
		auto const*  obj = iter.Cast< packet_vkCmdDrawIndexedIndirect *>();
		packer.Begin( EPacketID::VCmdDrawIndexedIndirect );
		packer << (obj->commandBuffer);
		packer << (obj->buffer);
		packer << (obj->offset);
		packer << (obj->drawCount);
		packer << (obj->stride);
		packer.End( EPacketID::VCmdDrawIndexedIndirect );
	}

	case VKTRACE_TPI_VK_vkCmdDispatch : {
		auto const*  obj = iter.Cast< packet_vkCmdDispatch *>();
		packer.Begin( EPacketID::VCmdDispatch );
		packer << (obj->commandBuffer);
		packer << (obj->groupCountX);
		packer << (obj->groupCountY);
		packer << (obj->groupCountZ);
		packer.End( EPacketID::VCmdDispatch );
	}

	case VKTRACE_TPI_VK_vkCmdDispatchIndirect : {
		auto const*  obj = iter.Cast< packet_vkCmdDispatchIndirect *>();
		packer.Begin( EPacketID::VCmdDispatchIndirect );
		packer << (obj->commandBuffer);
		packer << (obj->buffer);
		packer << (obj->offset);
		packer.End( EPacketID::VCmdDispatchIndirect );
	}

	case VKTRACE_TPI_VK_vkCmdCopyBuffer : {
		auto const*  obj = iter.Cast< packet_vkCmdCopyBuffer *>();
		packer.Begin( EPacketID::VCmdCopyBuffer );
		packer << (obj->commandBuffer);
		packer << (obj->srcBuffer);
		packer << (obj->dstBuffer);
		packer << (obj->regionCount);
		packer.Push( obj->pRegions, obj->regionCount );
		for (uint i = 0; obj->pRegions and i < obj->regionCount; ++i) {
			VPack_VkBufferCopy( obj->pRegions + i, packer );
		}
		packer.Pop( obj->pRegions );
		packer.End( EPacketID::VCmdCopyBuffer );
	}

	case VKTRACE_TPI_VK_vkCmdCopyImage : {
		auto const*  obj = iter.Cast< packet_vkCmdCopyImage *>();
		packer.Begin( EPacketID::VCmdCopyImage );
		packer << (obj->commandBuffer);
		packer << (obj->srcImage);
		packer << (obj->srcImageLayout);
		packer << (obj->dstImage);
		packer << (obj->dstImageLayout);
		packer << (obj->regionCount);
		packer.Push( obj->pRegions, obj->regionCount );
		for (uint i = 0; obj->pRegions and i < obj->regionCount; ++i) {
			VPack_VkImageCopy( obj->pRegions + i, packer );
		}
		packer.Pop( obj->pRegions );
		packer.End( EPacketID::VCmdCopyImage );
	}

	case VKTRACE_TPI_VK_vkCmdBlitImage : {
		auto const*  obj = iter.Cast< packet_vkCmdBlitImage *>();
		packer.Begin( EPacketID::VCmdBlitImage );
		packer << (obj->commandBuffer);
		packer << (obj->srcImage);
		packer << (obj->srcImageLayout);
		packer << (obj->dstImage);
		packer << (obj->dstImageLayout);
		packer << (obj->regionCount);
		packer.Push( obj->pRegions, obj->regionCount );
		for (uint i = 0; obj->pRegions and i < obj->regionCount; ++i) {
			VPack_VkImageBlit( obj->pRegions + i, packer );
		}
		packer.Pop( obj->pRegions );
		packer << (obj->filter);
		packer.End( EPacketID::VCmdBlitImage );
	}

	case VKTRACE_TPI_VK_vkCmdCopyBufferToImage : {
		auto const*  obj = iter.Cast< packet_vkCmdCopyBufferToImage *>();
		packer.Begin( EPacketID::VCmdCopyBufferToImage );
		packer << (obj->commandBuffer);
		packer << (obj->srcBuffer);
		packer << (obj->dstImage);
		packer << (obj->dstImageLayout);
		packer << (obj->regionCount);
		packer.Push( obj->pRegions, obj->regionCount );
		for (uint i = 0; obj->pRegions and i < obj->regionCount; ++i) {
			VPack_VkBufferImageCopy( obj->pRegions + i, packer );
		}
		packer.Pop( obj->pRegions );
		packer.End( EPacketID::VCmdCopyBufferToImage );
	}

	case VKTRACE_TPI_VK_vkCmdCopyImageToBuffer : {
		auto const*  obj = iter.Cast< packet_vkCmdCopyImageToBuffer *>();
		packer.Begin( EPacketID::VCmdCopyImageToBuffer );
		packer << (obj->commandBuffer);
		packer << (obj->srcImage);
		packer << (obj->srcImageLayout);
		packer << (obj->dstBuffer);
		packer << (obj->regionCount);
		packer.Push( obj->pRegions, obj->regionCount );
		for (uint i = 0; obj->pRegions and i < obj->regionCount; ++i) {
			VPack_VkBufferImageCopy( obj->pRegions + i, packer );
		}
		packer.Pop( obj->pRegions );
		packer.End( EPacketID::VCmdCopyImageToBuffer );
	}

	case VKTRACE_TPI_VK_vkCmdUpdateBuffer : break;
	case VKTRACE_TPI_VK_vkCmdFillBuffer : {
		auto const*  obj = iter.Cast< packet_vkCmdFillBuffer *>();
		packer.Begin( EPacketID::VCmdFillBuffer );
		packer << (obj->commandBuffer);
		packer << (obj->dstBuffer);
		packer << (obj->dstOffset);
		packer << (obj->size);
		packer << (obj->data);
		packer.End( EPacketID::VCmdFillBuffer );
	}

	case VKTRACE_TPI_VK_vkCmdClearColorImage : {
		auto const*  obj = iter.Cast< packet_vkCmdClearColorImage *>();
		packer.Begin( EPacketID::VCmdClearColorImage );
		packer << (obj->commandBuffer);
		packer << (obj->image);
		packer << (obj->imageLayout);
		packer.Push( obj->pColor );
		VPack_VkClearColorValue( obj->pColor, packer );
		packer.Pop( obj->pColor );
		packer << (obj->rangeCount);
		packer.Push( obj->pRanges, obj->rangeCount );
		for (uint i = 0; obj->pRanges and i < obj->rangeCount; ++i) {
			VPack_VkImageSubresourceRange( obj->pRanges + i, packer );
		}
		packer.Pop( obj->pRanges );
		packer.End( EPacketID::VCmdClearColorImage );
	}

	case VKTRACE_TPI_VK_vkCmdClearDepthStencilImage : {
		auto const*  obj = iter.Cast< packet_vkCmdClearDepthStencilImage *>();
		packer.Begin( EPacketID::VCmdClearDepthStencilImage );
		packer << (obj->commandBuffer);
		packer << (obj->image);
		packer << (obj->imageLayout);
		packer.Push( obj->pDepthStencil );
		VPack_VkClearDepthStencilValue( obj->pDepthStencil, packer );
		packer.Pop( obj->pDepthStencil );
		packer << (obj->rangeCount);
		packer.Push( obj->pRanges, obj->rangeCount );
		for (uint i = 0; obj->pRanges and i < obj->rangeCount; ++i) {
			VPack_VkImageSubresourceRange( obj->pRanges + i, packer );
		}
		packer.Pop( obj->pRanges );
		packer.End( EPacketID::VCmdClearDepthStencilImage );
	}

	case VKTRACE_TPI_VK_vkCmdClearAttachments : {
		auto const*  obj = iter.Cast< packet_vkCmdClearAttachments *>();
		packer.Begin( EPacketID::VCmdClearAttachments );
		packer << (obj->commandBuffer);
		packer << (obj->attachmentCount);
		packer.Push( obj->pAttachments, obj->attachmentCount );
		for (uint i = 0; obj->pAttachments and i < obj->attachmentCount; ++i) {
			VPack_VkClearAttachment( obj->pAttachments + i, packer );
		}
		packer.Pop( obj->pAttachments );
		packer << (obj->rectCount);
		packer.Push( obj->pRects, obj->rectCount );
		for (uint i = 0; obj->pRects and i < obj->rectCount; ++i) {
			VPack_VkClearRect( obj->pRects + i, packer );
		}
		packer.Pop( obj->pRects );
		packer.End( EPacketID::VCmdClearAttachments );
	}

	case VKTRACE_TPI_VK_vkCmdResolveImage : {
		auto const*  obj = iter.Cast< packet_vkCmdResolveImage *>();
		packer.Begin( EPacketID::VCmdResolveImage );
		packer << (obj->commandBuffer);
		packer << (obj->srcImage);
		packer << (obj->srcImageLayout);
		packer << (obj->dstImage);
		packer << (obj->dstImageLayout);
		packer << (obj->regionCount);
		packer.Push( obj->pRegions, obj->regionCount );
		for (uint i = 0; obj->pRegions and i < obj->regionCount; ++i) {
			VPack_VkImageResolve( obj->pRegions + i, packer );
		}
		packer.Pop( obj->pRegions );
		packer.End( EPacketID::VCmdResolveImage );
	}

	case VKTRACE_TPI_VK_vkCmdSetEvent : {
		auto const*  obj = iter.Cast< packet_vkCmdSetEvent *>();
		packer.Begin( EPacketID::VCmdSetEvent );
		packer << (obj->commandBuffer);
		packer << (obj->event);
		packer << (obj->stageMask);
		packer.End( EPacketID::VCmdSetEvent );
	}

	case VKTRACE_TPI_VK_vkCmdResetEvent : {
		auto const*  obj = iter.Cast< packet_vkCmdResetEvent *>();
		packer.Begin( EPacketID::VCmdResetEvent );
		packer << (obj->commandBuffer);
		packer << (obj->event);
		packer << (obj->stageMask);
		packer.End( EPacketID::VCmdResetEvent );
	}

	case VKTRACE_TPI_VK_vkCmdWaitEvents : {
		auto const*  obj = iter.Cast< packet_vkCmdWaitEvents *>();
		packer.Begin( EPacketID::VCmdWaitEvents );
		packer << (obj->commandBuffer);
		packer << (obj->eventCount);
		packer.Push( obj->pEvents, obj->eventCount );
		for (uint i = 0; obj->pEvents and i < obj->eventCount; ++i) {
			packer << (obj->pEvents[i]);
		}
		packer.Pop( obj->pEvents );
		packer << (obj->srcStageMask);
		packer << (obj->dstStageMask);
		packer << (obj->memoryBarrierCount);
		packer.Push( obj->pMemoryBarriers, obj->memoryBarrierCount );
		for (uint i = 0; obj->pMemoryBarriers and i < obj->memoryBarrierCount; ++i) {
			VPackStruct( BitCast<VkBaseInStructure const*>(obj->pMemoryBarriers + i), packer );
		}
		packer.Pop( obj->pMemoryBarriers );
		packer << (obj->bufferMemoryBarrierCount);
		packer.Push( obj->pBufferMemoryBarriers, obj->bufferMemoryBarrierCount );
		for (uint i = 0; obj->pBufferMemoryBarriers and i < obj->bufferMemoryBarrierCount; ++i) {
			VPackStruct( BitCast<VkBaseInStructure const*>(obj->pBufferMemoryBarriers + i), packer );
		}
		packer.Pop( obj->pBufferMemoryBarriers );
		packer << (obj->imageMemoryBarrierCount);
		packer.Push( obj->pImageMemoryBarriers, obj->imageMemoryBarrierCount );
		for (uint i = 0; obj->pImageMemoryBarriers and i < obj->imageMemoryBarrierCount; ++i) {
			VPackStruct( BitCast<VkBaseInStructure const*>(obj->pImageMemoryBarriers + i), packer );
		}
		packer.Pop( obj->pImageMemoryBarriers );
		packer.End( EPacketID::VCmdWaitEvents );
	}

	case VKTRACE_TPI_VK_vkCmdPipelineBarrier : {
		auto const*  obj = iter.Cast< packet_vkCmdPipelineBarrier *>();
		packer.Begin( EPacketID::VCmdPipelineBarrier );
		packer << (obj->commandBuffer);
		packer << (obj->srcStageMask);
		packer << (obj->dstStageMask);
		packer << (obj->dependencyFlags);
		packer << (obj->memoryBarrierCount);
		packer.Push( obj->pMemoryBarriers, obj->memoryBarrierCount );
		for (uint i = 0; obj->pMemoryBarriers and i < obj->memoryBarrierCount; ++i) {
			VPackStruct( BitCast<VkBaseInStructure const*>(obj->pMemoryBarriers + i), packer );
		}
		packer.Pop( obj->pMemoryBarriers );
		packer << (obj->bufferMemoryBarrierCount);
		packer.Push( obj->pBufferMemoryBarriers, obj->bufferMemoryBarrierCount );
		for (uint i = 0; obj->pBufferMemoryBarriers and i < obj->bufferMemoryBarrierCount; ++i) {
			VPackStruct( BitCast<VkBaseInStructure const*>(obj->pBufferMemoryBarriers + i), packer );
		}
		packer.Pop( obj->pBufferMemoryBarriers );
		packer << (obj->imageMemoryBarrierCount);
		packer.Push( obj->pImageMemoryBarriers, obj->imageMemoryBarrierCount );
		for (uint i = 0; obj->pImageMemoryBarriers and i < obj->imageMemoryBarrierCount; ++i) {
			VPackStruct( BitCast<VkBaseInStructure const*>(obj->pImageMemoryBarriers + i), packer );
		}
		packer.Pop( obj->pImageMemoryBarriers );
		packer.End( EPacketID::VCmdPipelineBarrier );
	}

	case VKTRACE_TPI_VK_vkCmdBeginQuery : {
		auto const*  obj = iter.Cast< packet_vkCmdBeginQuery *>();
		packer.Begin( EPacketID::VCmdBeginQuery );
		packer << (obj->commandBuffer);
		packer << (obj->queryPool);
		packer << (obj->query);
		packer << (obj->flags);
		packer.End( EPacketID::VCmdBeginQuery );
	}

	case VKTRACE_TPI_VK_vkCmdEndQuery : {
		auto const*  obj = iter.Cast< packet_vkCmdEndQuery *>();
		packer.Begin( EPacketID::VCmdEndQuery );
		packer << (obj->commandBuffer);
		packer << (obj->queryPool);
		packer << (obj->query);
		packer.End( EPacketID::VCmdEndQuery );
	}

	case VKTRACE_TPI_VK_vkCmdResetQueryPool : {
		auto const*  obj = iter.Cast< packet_vkCmdResetQueryPool *>();
		packer.Begin( EPacketID::VCmdResetQueryPool );
		packer << (obj->commandBuffer);
		packer << (obj->queryPool);
		packer << (obj->firstQuery);
		packer << (obj->queryCount);
		packer.End( EPacketID::VCmdResetQueryPool );
	}

	case VKTRACE_TPI_VK_vkCmdWriteTimestamp : break;
	case VKTRACE_TPI_VK_vkCmdCopyQueryPoolResults : {
		auto const*  obj = iter.Cast< packet_vkCmdCopyQueryPoolResults *>();
		packer.Begin( EPacketID::VCmdCopyQueryPoolResults );
		packer << (obj->commandBuffer);
		packer << (obj->queryPool);
		packer << (obj->firstQuery);
		packer << (obj->queryCount);
		packer << (obj->dstBuffer);
		packer << (obj->dstOffset);
		packer << (obj->stride);
		packer << (obj->flags);
		packer.End( EPacketID::VCmdCopyQueryPoolResults );
	}

	case VKTRACE_TPI_VK_vkCmdPushConstants : {
		auto const*  obj = iter.Cast< packet_vkCmdPushConstants *>();
		packer.Begin( EPacketID::VCmdPushConstants );
		packer << (obj->commandBuffer);
		packer << (obj->layout);
		packer << (obj->stageFlags);
		packer << (obj->offset);
		packer << (obj->size);
		packer.SetArray( obj->pValues, obj->size );
		packer.End( EPacketID::VCmdPushConstants );
	}

	case VKTRACE_TPI_VK_vkCmdBeginRenderPass : {
		auto const*  obj = iter.Cast< packet_vkCmdBeginRenderPass *>();
		packer.Begin( EPacketID::VCmdBeginRenderPass );
		packer << (obj->commandBuffer);
		packer.Push( obj->pRenderPassBegin );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pRenderPassBegin), packer );
		packer.Pop( obj->pRenderPassBegin );
		packer << (obj->contents);
		packer.End( EPacketID::VCmdBeginRenderPass );
	}

	case VKTRACE_TPI_VK_vkCmdNextSubpass : {
		auto const*  obj = iter.Cast< packet_vkCmdNextSubpass *>();
		packer.Begin( EPacketID::VCmdNextSubpass );
		packer << (obj->commandBuffer);
		packer << (obj->contents);
		packer.End( EPacketID::VCmdNextSubpass );
	}

	case VKTRACE_TPI_VK_vkCmdEndRenderPass : {
		auto const*  obj = iter.Cast< packet_vkCmdEndRenderPass *>();
		packer.Begin( EPacketID::VCmdEndRenderPass );
		packer << (obj->commandBuffer);
		packer.End( EPacketID::VCmdEndRenderPass );
	}

	case VKTRACE_TPI_VK_vkCmdExecuteCommands : {
		auto const*  obj = iter.Cast< packet_vkCmdExecuteCommands *>();
		packer.Begin( EPacketID::VCmdExecuteCommands );
		packer << (obj->commandBuffer);
		packer << (obj->commandBufferCount);
		packer.Push( obj->pCommandBuffers, obj->commandBufferCount );
		for (uint i = 0; obj->pCommandBuffers and i < obj->commandBufferCount; ++i) {
			packer << (obj->pCommandBuffers[i]);
		}
		packer.Pop( obj->pCommandBuffers );
		packer.End( EPacketID::VCmdExecuteCommands );
	}

	case VKTRACE_TPI_VK_vkDestroySurfaceKHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceSupportKHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceCapabilitiesKHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceFormatsKHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfacePresentModesKHR : break;
	case VKTRACE_TPI_VK_vkCreateSwapchainKHR : break;
	case VKTRACE_TPI_VK_vkDestroySwapchainKHR : break;
	case VKTRACE_TPI_VK_vkGetSwapchainImagesKHR : break;
	case VKTRACE_TPI_VK_vkAcquireNextImageKHR : break;
	case VKTRACE_TPI_VK_vkQueuePresentKHR : break;
	case VKTRACE_TPI_VK_vkCreateSharedSwapchainsKHR : break;
	case VKTRACE_TPI_VK_vkCreateWin32SurfaceKHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceWin32PresentationSupportKHR : break;
	case VKTRACE_TPI_VK_vkCreateXlibSurfaceKHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceXlibPresentationSupportKHR : break;
	case VKTRACE_TPI_VK_vkCreateXcbSurfaceKHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceXcbPresentationSupportKHR : break;
	case VKTRACE_TPI_VK_vkCreateAndroidSurfaceKHR : break;
	case VKTRACE_TPI_VK_vkGetMemoryWin32HandleNV : break;
	case VKTRACE_TPI_VK_vkCreateDescriptorUpdateTemplateKHR : break;
	case VKTRACE_TPI_VK_vkDestroyDescriptorUpdateTemplateKHR : break;
	case VKTRACE_TPI_VK_vkUpdateDescriptorSetWithTemplateKHR : break;
	case VKTRACE_TPI_VK_vkCmdPushDescriptorSetWithTemplateKHR : break;
	case VKTRACE_TPI_VK_vkCreateWaylandSurfaceKHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceWaylandPresentationSupportKHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceFeatures2KHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceProperties2KHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceFormatProperties2KHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceImageFormatProperties2KHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceQueueFamilyProperties2KHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceMemoryProperties2KHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSparseImageFormatProperties2KHR : break;
	case VKTRACE_TPI_VK_vkGetImageMemoryRequirements2KHR : break;
	case VKTRACE_TPI_VK_vkGetBufferMemoryRequirements2KHR : break;
	case VKTRACE_TPI_VK_vkGetImageSparseMemoryRequirements2KHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceCapabilities2KHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceFormats2KHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceDisplayPropertiesKHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceDisplayPlanePropertiesKHR : break;
	case VKTRACE_TPI_VK_vkGetDisplayModePropertiesKHR : break;
	case VKTRACE_TPI_VK_vkCreateDisplayModeKHR : break;
	case VKTRACE_TPI_VK_vkGetDisplayPlaneCapabilitiesKHR : break;
	case VKTRACE_TPI_VK_vkCreateDisplayPlaneSurfaceKHR : break;
	case VKTRACE_TPI_VK_vkTrimCommandPoolKHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalBufferPropertiesKHR : break;
	case VKTRACE_TPI_VK_vkGetMemoryFdKHR : break;
	case VKTRACE_TPI_VK_vkGetMemoryFdPropertiesKHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR : break;
	case VKTRACE_TPI_VK_vkImportSemaphoreFdKHR : break;
	case VKTRACE_TPI_VK_vkGetSemaphoreFdKHR : break;
	case VKTRACE_TPI_VK_vkCmdPushDescriptorSetKHR : {
		auto const*  obj = iter.Cast< packet_vkCmdPushDescriptorSetKHR *>();
		packer.Begin( EPacketID::VCmdPushDescriptorSetKHR );
		packer << (obj->commandBuffer);
		packer << (obj->pipelineBindPoint);
		packer << (obj->layout);
		packer << (obj->set);
		packer << (obj->descriptorWriteCount);
		packer.Push( obj->pDescriptorWrites, obj->descriptorWriteCount );
		for (uint i = 0; obj->pDescriptorWrites and i < obj->descriptorWriteCount; ++i) {
			VPackStruct( BitCast<VkBaseInStructure const*>(obj->pDescriptorWrites + i), packer );
		}
		packer.Pop( obj->pDescriptorWrites );
		packer.End( EPacketID::VCmdPushDescriptorSetKHR );
	}

	case VKTRACE_TPI_VK_vkGetSwapchainStatusKHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalFencePropertiesKHR : break;
	case VKTRACE_TPI_VK_vkGetDeviceGroupPeerMemoryFeaturesKHX : break;
	case VKTRACE_TPI_VK_vkBindBufferMemory2KHR : break;
	case VKTRACE_TPI_VK_vkBindImageMemory2KHR : break;
	case VKTRACE_TPI_VK_vkCmdSetDeviceMaskKHX : break;
	case VKTRACE_TPI_VK_vkGetDeviceGroupPresentCapabilitiesKHX : break;
	case VKTRACE_TPI_VK_vkGetDeviceGroupSurfacePresentModesKHX : break;
	case VKTRACE_TPI_VK_vkAcquireNextImage2KHX : break;
	case VKTRACE_TPI_VK_vkCmdDispatchBaseKHX : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDevicePresentRectanglesKHX : break;
	case VKTRACE_TPI_VK_vkEnumeratePhysicalDeviceGroupsKHX : break;
	case VKTRACE_TPI_VK_vkCmdProcessCommandsNVX : {
		auto const*  obj = iter.Cast< packet_vkCmdProcessCommandsNVX *>();
		packer.Begin( EPacketID::VCmdProcessCommandsNVX );
		packer << (obj->commandBuffer);
		packer.Push( obj->pProcessCommandsInfo );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pProcessCommandsInfo), packer );
		packer.Pop( obj->pProcessCommandsInfo );
		packer.End( EPacketID::VCmdProcessCommandsNVX );
	}

	case VKTRACE_TPI_VK_vkCmdReserveSpaceForCommandsNVX : {
		auto const*  obj = iter.Cast< packet_vkCmdReserveSpaceForCommandsNVX *>();
		packer.Begin( EPacketID::VCmdReserveSpaceForCommandsNVX );
		packer << (obj->commandBuffer);
		packer.Push( obj->pReserveSpaceInfo );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pReserveSpaceInfo), packer );
		packer.Pop( obj->pReserveSpaceInfo );
		packer.End( EPacketID::VCmdReserveSpaceForCommandsNVX );
	}

	case VKTRACE_TPI_VK_vkCreateIndirectCommandsLayoutNVX : {
		auto const*  obj = iter.Cast< packet_vkCreateIndirectCommandsLayoutNVX *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VCreateIndirectCommandsLayoutNVX );
		packer << (obj->device);
		packer.Push( obj->pCreateInfo );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), packer );
		packer.Pop( obj->pCreateInfo );
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer << (obj->pIndirectCommandsLayout);
		packer.End( EPacketID::VCreateIndirectCommandsLayoutNVX );
	}

	case VKTRACE_TPI_VK_vkDestroyIndirectCommandsLayoutNVX : {
		auto const*  obj = iter.Cast< packet_vkDestroyIndirectCommandsLayoutNVX *>();
		packer.Begin( EPacketID::VDestroyIndirectCommandsLayoutNVX );
		packer << (obj->device);
		packer << (obj->indirectCommandsLayout);
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer.End( EPacketID::VDestroyIndirectCommandsLayoutNVX );
	}

	case VKTRACE_TPI_VK_vkCreateObjectTableNVX : {
		auto const*  obj = iter.Cast< packet_vkCreateObjectTableNVX *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VCreateObjectTableNVX );
		packer << (obj->device);
		packer.Push( obj->pCreateInfo );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), packer );
		packer.Pop( obj->pCreateInfo );
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer << (obj->pObjectTable);
		packer.End( EPacketID::VCreateObjectTableNVX );
	}

	case VKTRACE_TPI_VK_vkDestroyObjectTableNVX : {
		auto const*  obj = iter.Cast< packet_vkDestroyObjectTableNVX *>();
		packer.Begin( EPacketID::VDestroyObjectTableNVX );
		packer << (obj->device);
		packer << (obj->objectTable);
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer.End( EPacketID::VDestroyObjectTableNVX );
	}

	case VKTRACE_TPI_VK_vkRegisterObjectsNVX : {
		auto const*  obj = iter.Cast< packet_vkRegisterObjectsNVX *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VRegisterObjectsNVX );
		packer << (obj->device);
		packer << (obj->objectTable);
		packer << (obj->objectCount);
		packer.Push( obj->ppObjectTableEntries );
		for (uint i = 0; obj->ppObjectTableEntries and i < obj->objectCount; ++i) {
			VPack_VkObjectTableEntryNVX( obj->ppObjectTableEntries[i], packer );
		}
		packer.Pop( obj->ppObjectTableEntries );
		packer.Push( obj->pObjectIndices, obj->objectCount );
		for (uint i = 0; obj->pObjectIndices and i < obj->objectCount; ++i) {
			packer << (obj->pObjectIndices[i]);
		}
		packer.Pop( obj->pObjectIndices );
		packer.End( EPacketID::VRegisterObjectsNVX );
	}

	case VKTRACE_TPI_VK_vkUnregisterObjectsNVX : {
		auto const*  obj = iter.Cast< packet_vkUnregisterObjectsNVX *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VUnregisterObjectsNVX );
		packer << (obj->device);
		packer << (obj->objectTable);
		packer << (obj->objectCount);
		packer.Push( obj->pObjectEntryTypes, obj->objectCount );
		for (uint i = 0; obj->pObjectEntryTypes and i < obj->objectCount; ++i) {
			packer << (obj->pObjectEntryTypes[i]);
		}
		packer.Pop( obj->pObjectEntryTypes );
		packer.Push( obj->pObjectIndices, obj->objectCount );
		for (uint i = 0; obj->pObjectIndices and i < obj->objectCount; ++i) {
			packer << (obj->pObjectIndices[i]);
		}
		packer.Pop( obj->pObjectIndices );
		packer.End( EPacketID::VUnregisterObjectsNVX );
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX : break;
	case VKTRACE_TPI_VK_vkCmdSetViewportWScalingNV : {
		auto const*  obj = iter.Cast< packet_vkCmdSetViewportWScalingNV *>();
		packer.Begin( EPacketID::VCmdSetViewportWScalingNV );
		packer << (obj->commandBuffer);
		packer << (obj->firstViewport);
		packer << (obj->viewportCount);
		packer.Push( obj->pViewportWScalings, obj->viewportCount );
		for (uint i = 0; obj->pViewportWScalings and i < obj->viewportCount; ++i) {
			VPack_VkViewportWScalingNV( obj->pViewportWScalings + i, packer );
		}
		packer.Pop( obj->pViewportWScalings );
		packer.End( EPacketID::VCmdSetViewportWScalingNV );
	}

	case VKTRACE_TPI_VK_vkReleaseDisplayEXT : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceCapabilities2EXT : break;
	case VKTRACE_TPI_VK_vkGetRefreshCycleDurationGOOGLE : break;
	case VKTRACE_TPI_VK_vkGetPastPresentationTimingGOOGLE : break;
	case VKTRACE_TPI_VK_vkCmdSetDiscardRectangleEXT : {
		auto const*  obj = iter.Cast< packet_vkCmdSetDiscardRectangleEXT *>();
		packer.Begin( EPacketID::VCmdSetDiscardRectangleEXT );
		packer << (obj->commandBuffer);
		packer << (obj->firstDiscardRectangle);
		packer << (obj->discardRectangleCount);
		packer.Push( obj->pDiscardRectangles, obj->discardRectangleCount );
		for (uint i = 0; obj->pDiscardRectangles and i < obj->discardRectangleCount; ++i) {
			VPack_VkRect2D( obj->pDiscardRectangles + i, packer );
		}
		packer.Pop( obj->pDiscardRectangles );
		packer.End( EPacketID::VCmdSetDiscardRectangleEXT );
	}

	case VKTRACE_TPI_VK_vkSetHdrMetadataEXT : break;
	case VKTRACE_TPI_VK_vkAcquireXlibDisplayEXT : break;
	case VKTRACE_TPI_VK_vkGetRandROutputDisplayEXT : break;
	case VKTRACE_TPI_VK_vkDisplayPowerControlEXT : break;
	case VKTRACE_TPI_VK_vkRegisterDeviceEventEXT : break;
	case VKTRACE_TPI_VK_vkRegisterDisplayEventEXT : break;
	case VKTRACE_TPI_VK_vkGetSwapchainCounterEXT : break;
	case VKTRACE_TPI_VK_vkCmdSetSampleLocationsEXT : {
		auto const*  obj = iter.Cast< packet_vkCmdSetSampleLocationsEXT *>();
		packer.Begin( EPacketID::VCmdSetSampleLocationsEXT );
		packer << (obj->commandBuffer);
		packer.Push( obj->pSampleLocationsInfo );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pSampleLocationsInfo), packer );
		packer.Pop( obj->pSampleLocationsInfo );
		packer.End( EPacketID::VCmdSetSampleLocationsEXT );
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceMultisamplePropertiesEXT : break;
	case VKTRACE_TPI_VK_vkCreateSamplerYcbcrConversionKHR : break;
	case VKTRACE_TPI_VK_vkDestroySamplerYcbcrConversionKHR : break;
	case VKTRACE_TPI_VK_vkGetDisplayPlaneSupportedDisplaysKHR : break;
	case VKTRACE_TPI_VK_vkImportFenceFdKHR : break;
	case VKTRACE_TPI_VK_vkGetFenceFdKHR : break;
	case VKTRACE_TPI_VK_vkImportFenceWin32HandleKHR : break;
	case VKTRACE_TPI_VK_vkGetFenceWin32HandleKHR : break;
	case VKTRACE_TPI_VK_vkGetMemoryWin32HandleKHR : break;
	case VKTRACE_TPI_VK_vkGetMemoryWin32HandlePropertiesKHR : break;
	case VKTRACE_TPI_VK_vkImportSemaphoreWin32HandleKHR : break;
	case VKTRACE_TPI_VK_vkGetSemaphoreWin32HandleKHR : break;
	case VKTRACE_TPI_VK_vkGetMemoryHostPointerPropertiesEXT : break;
	case VKTRACE_TPI_VK_vkCreateValidationCacheEXT : break;
	case VKTRACE_TPI_VK_vkDestroyValidationCacheEXT : break;
	case VKTRACE_TPI_VK_vkMergeValidationCachesEXT : break;
	case VKTRACE_TPI_VK_vkGetValidationCacheDataEXT : break;
	case VKTRACE_TPI_VK_vkGetShaderInfoAMD : break;
	case VKTRACE_TPI_VK_vkGetDeviceQueue2 : {
		auto const*  obj = iter.Cast< packet_vkGetDeviceQueue2 *>();
		packer.Begin( EPacketID::VGetDeviceQueue2 );
		packer << (obj->device);
		packer.Push( obj->pQueueInfo );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pQueueInfo), packer );
		packer.Pop( obj->pQueueInfo );
		packer << (obj->pQueue);
		packer.End( EPacketID::VGetDeviceQueue2 );
	}

	case VKTRACE_TPI_VK_vkEnumerateInstanceVersion : break;
	case VKTRACE_TPI_VK_vkGetDescriptorSetLayoutSupport : break;
	case VKTRACE_TPI_VK_vkGetDeviceGroupPresentCapabilitiesKHR : break;
	case VKTRACE_TPI_VK_vkGetDeviceGroupSurfacePresentModesKHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDevicePresentRectanglesKHR : break;
	case VKTRACE_TPI_VK_vkAcquireNextImage2KHR : break;
	case VKTRACE_TPI_VK_vkBindBufferMemory2 : {
		auto const*  obj = iter.Cast< packet_vkBindBufferMemory2 *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VBindBufferMemory2 );
		packer << (obj->device);
		packer << (obj->bindInfoCount);
		packer.Push( obj->pBindInfos, obj->bindInfoCount );
		for (uint i = 0; obj->pBindInfos and i < obj->bindInfoCount; ++i) {
			VPackStruct( BitCast<VkBaseInStructure const*>(obj->pBindInfos + i), packer );
		}
		packer.Pop( obj->pBindInfos );
		packer.End( EPacketID::VBindBufferMemory2 );
	}

	case VKTRACE_TPI_VK_vkBindImageMemory2 : {
		auto const*  obj = iter.Cast< packet_vkBindImageMemory2 *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VBindImageMemory2 );
		packer << (obj->device);
		packer << (obj->bindInfoCount);
		packer.Push( obj->pBindInfos, obj->bindInfoCount );
		for (uint i = 0; obj->pBindInfos and i < obj->bindInfoCount; ++i) {
			VPackStruct( BitCast<VkBaseInStructure const*>(obj->pBindInfos + i), packer );
		}
		packer.Pop( obj->pBindInfos );
		packer.End( EPacketID::VBindImageMemory2 );
	}

	case VKTRACE_TPI_VK_vkGetDeviceGroupPeerMemoryFeatures : break;
	case VKTRACE_TPI_VK_vkCmdSetDeviceMask : {
		auto const*  obj = iter.Cast< packet_vkCmdSetDeviceMask *>();
		packer.Begin( EPacketID::VCmdSetDeviceMask );
		packer << (obj->commandBuffer);
		packer << (obj->deviceMask);
		packer.End( EPacketID::VCmdSetDeviceMask );
	}

	case VKTRACE_TPI_VK_vkCmdDispatchBase : {
		auto const*  obj = iter.Cast< packet_vkCmdDispatchBase *>();
		packer.Begin( EPacketID::VCmdDispatchBase );
		packer << (obj->commandBuffer);
		packer << (obj->baseGroupX);
		packer << (obj->baseGroupY);
		packer << (obj->baseGroupZ);
		packer << (obj->groupCountX);
		packer << (obj->groupCountY);
		packer << (obj->groupCountZ);
		packer.End( EPacketID::VCmdDispatchBase );
	}

	case VKTRACE_TPI_VK_vkEnumeratePhysicalDeviceGroups : break;
	case VKTRACE_TPI_VK_vkGetImageMemoryRequirements2 : break;
	case VKTRACE_TPI_VK_vkGetBufferMemoryRequirements2 : break;
	case VKTRACE_TPI_VK_vkGetImageSparseMemoryRequirements2 : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceFeatures2 : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceProperties2 : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceFormatProperties2 : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceImageFormatProperties2 : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceQueueFamilyProperties2 : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceMemoryProperties2 : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSparseImageFormatProperties2 : break;
	case VKTRACE_TPI_VK_vkTrimCommandPool : {
		auto const*  obj = iter.Cast< packet_vkTrimCommandPool *>();
		packer.Begin( EPacketID::VTrimCommandPool );
		packer << (obj->device);
		packer << (obj->commandPool);
		packer << (obj->flags);
		packer.End( EPacketID::VTrimCommandPool );
	}

	case VKTRACE_TPI_VK_vkCreateSamplerYcbcrConversion : {
		auto const*  obj = iter.Cast< packet_vkCreateSamplerYcbcrConversion *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VCreateSamplerYcbcrConversion );
		packer << (obj->device);
		packer.Push( obj->pCreateInfo );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), packer );
		packer.Pop( obj->pCreateInfo );
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer << (obj->pYcbcrConversion);
		packer.End( EPacketID::VCreateSamplerYcbcrConversion );
	}

	case VKTRACE_TPI_VK_vkDestroySamplerYcbcrConversion : {
		auto const*  obj = iter.Cast< packet_vkDestroySamplerYcbcrConversion *>();
		packer.Begin( EPacketID::VDestroySamplerYcbcrConversion );
		packer << (obj->device);
		packer << (obj->ycbcrConversion);
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer.End( EPacketID::VDestroySamplerYcbcrConversion );
	}

	case VKTRACE_TPI_VK_vkCreateDescriptorUpdateTemplate : {
		auto const*  obj = iter.Cast< packet_vkCreateDescriptorUpdateTemplate *>();
		VK_CALL( obj->result );
		packer.Begin( EPacketID::VCreateDescriptorUpdateTemplate );
		packer << (obj->device);
		packer.Push( obj->pCreateInfo );
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), packer );
		packer.Pop( obj->pCreateInfo );
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer << (obj->pDescriptorUpdateTemplate);
		packer.End( EPacketID::VCreateDescriptorUpdateTemplate );
	}

	case VKTRACE_TPI_VK_vkDestroyDescriptorUpdateTemplate : {
		auto const*  obj = iter.Cast< packet_vkDestroyDescriptorUpdateTemplate *>();
		packer.Begin( EPacketID::VDestroyDescriptorUpdateTemplate );
		packer << (obj->device);
		packer << (obj->descriptorUpdateTemplate);
		packer << static_cast<VkAllocationCallbacks const*>(null);
		packer.End( EPacketID::VDestroyDescriptorUpdateTemplate );
	}

	case VKTRACE_TPI_VK_vkUpdateDescriptorSetWithTemplate : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalBufferProperties : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalFenceProperties : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalSemaphoreProperties : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceDisplayProperties2KHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceDisplayPlaneProperties2KHR : break;
	case VKTRACE_TPI_VK_vkGetDisplayModeProperties2KHR : break;
	case VKTRACE_TPI_VK_vkGetDisplayPlaneCapabilities2KHR : break;
}
DISABLE_ENUM_CHECKS();
