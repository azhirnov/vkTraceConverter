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
	case VKTRACE_TPI_VK_vkCmdDrawIndirectCountAMD : {
		packet_vkCmdDrawIndirectCountAMD const*  obj = iter.Cast<packet_vkCmdDrawIndirectCountAMD*>();
		result << indent << "app.vkCmdDrawIndirectCountAMD( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*buffer*/ " << "app.GetResource(BufferID(" << remapper(obj->buffer) << "))";
		result << ",\n";
		result << indent << "		/*offset*/ " << IntToString( obj->offset );
		result << ",\n";
		result << indent << "		/*countBuffer*/ " << "app.GetResource(BufferID(" << remapper(obj->countBuffer) << "))";
		result << ",\n";
		result << indent << "		/*countBufferOffset*/ " << IntToString( obj->countBufferOffset );
		result << ",\n";
		result << indent << "		/*maxDrawCount*/ " << IntToString( obj->maxDrawCount );
		result << ",\n";
		result << indent << "		/*stride*/ " << IntToString( obj->stride );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDrawIndexedIndirectCountAMD : {
		packet_vkCmdDrawIndexedIndirectCountAMD const*  obj = iter.Cast<packet_vkCmdDrawIndexedIndirectCountAMD*>();
		result << indent << "app.vkCmdDrawIndexedIndirectCountAMD( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*buffer*/ " << "app.GetResource(BufferID(" << remapper(obj->buffer) << "))";
		result << ",\n";
		result << indent << "		/*offset*/ " << IntToString( obj->offset );
		result << ",\n";
		result << indent << "		/*countBuffer*/ " << "app.GetResource(BufferID(" << remapper(obj->countBuffer) << "))";
		result << ",\n";
		result << indent << "		/*countBufferOffset*/ " << IntToString( obj->countBufferOffset );
		result << ",\n";
		result << indent << "		/*maxDrawCount*/ " << IntToString( obj->maxDrawCount );
		result << ",\n";
		result << indent << "		/*stride*/ " << IntToString( obj->stride );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateDebugReportCallbackEXT : break;
	case VKTRACE_TPI_VK_vkDestroyDebugReportCallbackEXT : break;
	case VKTRACE_TPI_VK_vkDebugReportMessageEXT : break;
	case VKTRACE_TPI_VK_vkDebugMarkerSetObjectTagEXT : {
		packet_vkDebugMarkerSetObjectTagEXT const*  obj = iter.Cast<packet_vkDebugMarkerSetObjectTagEXT*>();
		if ( obj->pTagInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pTagInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkDebugMarkerSetObjectTagEXT( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pTagInfo*/ " << nameSer.GetPtr( obj->pTagInfo );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDebugMarkerSetObjectNameEXT : {
		packet_vkDebugMarkerSetObjectNameEXT const*  obj = iter.Cast<packet_vkDebugMarkerSetObjectNameEXT*>();
		if ( obj->pNameInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pNameInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkDebugMarkerSetObjectNameEXT( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pNameInfo*/ " << nameSer.GetPtr( obj->pNameInfo );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDebugMarkerBeginEXT : {
		packet_vkCmdDebugMarkerBeginEXT const*  obj = iter.Cast<packet_vkCmdDebugMarkerBeginEXT*>();
		if ( obj->pMarkerInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pMarkerInfo), nameSer, remapper, indent );
		}
		result << indent << "app.vkCmdDebugMarkerBeginEXT( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*pMarkerInfo*/ " << nameSer.GetPtr( obj->pMarkerInfo );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDebugMarkerEndEXT : {
		packet_vkCmdDebugMarkerEndEXT const*  obj = iter.Cast<packet_vkCmdDebugMarkerEndEXT*>();
		result << indent << "app.vkCmdDebugMarkerEndEXT( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDebugMarkerInsertEXT : {
		packet_vkCmdDebugMarkerInsertEXT const*  obj = iter.Cast<packet_vkCmdDebugMarkerInsertEXT*>();
		if ( obj->pMarkerInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pMarkerInfo), nameSer, remapper, indent );
		}
		result << indent << "app.vkCmdDebugMarkerInsertEXT( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*pMarkerInfo*/ " << nameSer.GetPtr( obj->pMarkerInfo );
		result << " );\n";
		break;
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
	case VKTRACE_TPI_VK_vkGetDeviceQueue : break;
	case VKTRACE_TPI_VK_vkQueueSubmit : {
		packet_vkQueueSubmit const*  obj = iter.Cast<packet_vkQueueSubmit*>();
		if ( obj->pSubmits ) {
			ASSERT( obj->submitCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pSubmits, "submits"s, "submitInfo"s, "info"s );
			before << indent << "VkSubmitInfo  " << arr_name << "[" << IntToString(obj->submitCount) << "] = {};\n";
			for (uint i = 0; i < obj->submitCount; ++i) {
				Serialize2_VkSubmitInfo( obj->pSubmits + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkQueueSubmit( \n";
		result << indent << "		/*queue*/ " << "app.GetResource(QueueID(" << remapper(obj->queue) << "))";
		result << ",\n";
		result << indent << "		/*submitCount*/ " << IntToString( obj->submitCount );
		result << ",\n";
		result << indent << "		/*pSubmits*/ " << nameSer.Get( &obj->pSubmits );
		result << ",\n";
		result << indent << "		/*fence*/ " << "app.GetResource(FenceID(" << remapper(obj->fence) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkQueueWaitIdle : {
		packet_vkQueueWaitIdle const*  obj = iter.Cast<packet_vkQueueWaitIdle*>();
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkQueueWaitIdle( \n";
		result << indent << "		/*queue*/ " << "app.GetResource(QueueID(" << remapper(obj->queue) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDeviceWaitIdle : {
		packet_vkDeviceWaitIdle const*  obj = iter.Cast<packet_vkDeviceWaitIdle*>();
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkDeviceWaitIdle( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkAllocateMemory : {
		packet_vkAllocateMemory const*  obj = iter.Cast<packet_vkAllocateMemory*>();
		if ( obj->pAllocateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pAllocateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkAllocateMemory( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pAllocateInfo*/ " << nameSer.GetPtr( obj->pAllocateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pMemory*/ " << "&app.EditResource(DeviceMemoryID(" << remapper(*obj->pMemory) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkFreeMemory : {
		packet_vkFreeMemory const*  obj = iter.Cast<packet_vkFreeMemory*>();
		result << indent << "app.vkFreeMemory( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*memory*/ " << "app.GetResource(DeviceMemoryID(" << remapper(obj->memory) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkMapMemory : break;
	case VKTRACE_TPI_VK_vkUnmapMemory : break;
	case VKTRACE_TPI_VK_vkFlushMappedMemoryRanges : break;
	case VKTRACE_TPI_VK_vkInvalidateMappedMemoryRanges : break;
	case VKTRACE_TPI_VK_vkGetDeviceMemoryCommitment : break;
	case VKTRACE_TPI_VK_vkBindBufferMemory : {
		packet_vkBindBufferMemory const*  obj = iter.Cast<packet_vkBindBufferMemory*>();
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkBindBufferMemory( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*buffer*/ " << "app.GetResource(BufferID(" << remapper(obj->buffer) << "))";
		result << ",\n";
		result << indent << "		/*memory*/ " << "app.GetResource(DeviceMemoryID(" << remapper(obj->memory) << "))";
		result << ",\n";
		result << indent << "		/*memoryOffset*/ " << IntToString( obj->memoryOffset );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkBindImageMemory : {
		packet_vkBindImageMemory const*  obj = iter.Cast<packet_vkBindImageMemory*>();
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkBindImageMemory( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*image*/ " << "app.GetResource(ImageID(" << remapper(obj->image) << "))";
		result << ",\n";
		result << indent << "		/*memory*/ " << "app.GetResource(DeviceMemoryID(" << remapper(obj->memory) << "))";
		result << ",\n";
		result << indent << "		/*memoryOffset*/ " << IntToString( obj->memoryOffset );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetBufferMemoryRequirements : break;
	case VKTRACE_TPI_VK_vkGetImageMemoryRequirements : break;
	case VKTRACE_TPI_VK_vkGetImageSparseMemoryRequirements : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSparseImageFormatProperties : break;
	case VKTRACE_TPI_VK_vkQueueBindSparse : {
		packet_vkQueueBindSparse const*  obj = iter.Cast<packet_vkQueueBindSparse*>();
		if ( obj->pBindInfo ) {
			ASSERT( obj->bindInfoCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pBindInfo, "bindInfo"s, "bindSparseInfo"s, "info"s );
			before << indent << "VkBindSparseInfo  " << arr_name << "[" << IntToString(obj->bindInfoCount) << "] = {};\n";
			for (uint i = 0; i < obj->bindInfoCount; ++i) {
				Serialize2_VkBindSparseInfo( obj->pBindInfo + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkQueueBindSparse( \n";
		result << indent << "		/*queue*/ " << "app.GetResource(QueueID(" << remapper(obj->queue) << "))";
		result << ",\n";
		result << indent << "		/*bindInfoCount*/ " << IntToString( obj->bindInfoCount );
		result << ",\n";
		result << indent << "		/*pBindInfo*/ " << nameSer.Get( &obj->pBindInfo );
		result << ",\n";
		result << indent << "		/*fence*/ " << "app.GetResource(FenceID(" << remapper(obj->fence) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateFence : {
		packet_vkCreateFence const*  obj = iter.Cast<packet_vkCreateFence*>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateFence( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pFence*/ " << "&app.EditResource(FenceID(" << remapper(*obj->pFence) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyFence : {
		packet_vkDestroyFence const*  obj = iter.Cast<packet_vkDestroyFence*>();
		result << indent << "app.vkDestroyFence( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*fence*/ " << "app.GetResource(FenceID(" << remapper(obj->fence) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkResetFences : {
		packet_vkResetFences const*  obj = iter.Cast<packet_vkResetFences*>();
		if ( obj->pFences ) {
			ASSERT( obj->fenceCount > 0 );
			before << indent << "const VkFence  " << nameSer.MakeUnique( &obj->pFences, "fences"s, "fence"s ) << "[] = {";
			for (uint i = 0; i < obj->fenceCount; ++i) {
				before << (i ? "," : "") << (i%4 == 0 ? "\n\t"s << indent : " ") << "app.GetResource(FenceID(" << remapper(obj->pFences[i]) << "))";
			}
			before << "\n" << indent << "};\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pFences ) << ") == " << IntToString(obj->fenceCount) << " );\n\n";
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkResetFences( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*fenceCount*/ " << IntToString( obj->fenceCount );
		result << ",\n";
		result << indent << "		/*pFences*/ " << nameSer.Get( &obj->pFences );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetFenceStatus : break;
	case VKTRACE_TPI_VK_vkWaitForFences : {
		packet_vkWaitForFences const*  obj = iter.Cast<packet_vkWaitForFences*>();
		if ( obj->pFences ) {
			ASSERT( obj->fenceCount > 0 );
			before << indent << "const VkFence  " << nameSer.MakeUnique( &obj->pFences, "fences"s, "fence"s ) << "[] = {";
			for (uint i = 0; i < obj->fenceCount; ++i) {
				before << (i ? "," : "") << (i%4 == 0 ? "\n\t"s << indent : " ") << "app.GetResource(FenceID(" << remapper(obj->pFences[i]) << "))";
			}
			before << "\n" << indent << "};\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pFences ) << ") == " << IntToString(obj->fenceCount) << " );\n\n";
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkWaitForFences( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*fenceCount*/ " << IntToString( obj->fenceCount );
		result << ",\n";
		result << indent << "		/*pFences*/ " << nameSer.Get( &obj->pFences );
		result << ",\n";
		result << indent << "		/*waitAll*/ " << BoolToString( obj->waitAll );
		result << ",\n";
		result << indent << "		/*timeout*/ " << IntToString( obj->timeout );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateSemaphore : {
		packet_vkCreateSemaphore const*  obj = iter.Cast<packet_vkCreateSemaphore*>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateSemaphore( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pSemaphore*/ " << "&app.EditResource(SemaphoreID(" << remapper(*obj->pSemaphore) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroySemaphore : {
		packet_vkDestroySemaphore const*  obj = iter.Cast<packet_vkDestroySemaphore*>();
		result << indent << "app.vkDestroySemaphore( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*semaphore*/ " << "app.GetResource(SemaphoreID(" << remapper(obj->semaphore) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateEvent : {
		packet_vkCreateEvent const*  obj = iter.Cast<packet_vkCreateEvent*>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateEvent( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pEvent*/ " << "&app.EditResource(EventID(" << remapper(*obj->pEvent) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyEvent : {
		packet_vkDestroyEvent const*  obj = iter.Cast<packet_vkDestroyEvent*>();
		result << indent << "app.vkDestroyEvent( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*event*/ " << "app.GetResource(EventID(" << remapper(obj->event) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetEventStatus : break;
	case VKTRACE_TPI_VK_vkSetEvent : {
		packet_vkSetEvent const*  obj = iter.Cast<packet_vkSetEvent*>();
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkSetEvent( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*event*/ " << "app.GetResource(EventID(" << remapper(obj->event) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkResetEvent : {
		packet_vkResetEvent const*  obj = iter.Cast<packet_vkResetEvent*>();
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkResetEvent( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*event*/ " << "app.GetResource(EventID(" << remapper(obj->event) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateQueryPool : {
		packet_vkCreateQueryPool const*  obj = iter.Cast<packet_vkCreateQueryPool*>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateQueryPool( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pQueryPool*/ " << "&app.EditResource(QueryPoolID(" << remapper(*obj->pQueryPool) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyQueryPool : {
		packet_vkDestroyQueryPool const*  obj = iter.Cast<packet_vkDestroyQueryPool*>();
		result << indent << "app.vkDestroyQueryPool( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*queryPool*/ " << "app.GetResource(QueryPoolID(" << remapper(obj->queryPool) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetQueryPoolResults : break;
	case VKTRACE_TPI_VK_vkCreateBuffer : {
		packet_vkCreateBuffer const*  obj = iter.Cast<packet_vkCreateBuffer*>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateBuffer( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pBuffer*/ " << "&app.EditResource(BufferID(" << remapper(*obj->pBuffer) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyBuffer : {
		packet_vkDestroyBuffer const*  obj = iter.Cast<packet_vkDestroyBuffer*>();
		result << indent << "app.vkDestroyBuffer( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*buffer*/ " << "app.GetResource(BufferID(" << remapper(obj->buffer) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateBufferView : {
		packet_vkCreateBufferView const*  obj = iter.Cast<packet_vkCreateBufferView*>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateBufferView( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pView*/ " << "&app.EditResource(BufferViewID(" << remapper(*obj->pView) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyBufferView : {
		packet_vkDestroyBufferView const*  obj = iter.Cast<packet_vkDestroyBufferView*>();
		result << indent << "app.vkDestroyBufferView( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*bufferView*/ " << "app.GetResource(BufferViewID(" << remapper(obj->bufferView) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateImage : {
		packet_vkCreateImage const*  obj = iter.Cast<packet_vkCreateImage*>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateImage( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pImage*/ " << "&app.EditResource(ImageID(" << remapper(*obj->pImage) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyImage : {
		packet_vkDestroyImage const*  obj = iter.Cast<packet_vkDestroyImage*>();
		result << indent << "app.vkDestroyImage( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*image*/ " << "app.GetResource(ImageID(" << remapper(obj->image) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetImageSubresourceLayout : break;
	case VKTRACE_TPI_VK_vkCreateImageView : {
		packet_vkCreateImageView const*  obj = iter.Cast<packet_vkCreateImageView*>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateImageView( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pView*/ " << "&app.EditResource(ImageViewID(" << remapper(*obj->pView) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyImageView : {
		packet_vkDestroyImageView const*  obj = iter.Cast<packet_vkDestroyImageView*>();
		result << indent << "app.vkDestroyImageView( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*imageView*/ " << "app.GetResource(ImageViewID(" << remapper(obj->imageView) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateShaderModule : break;
	case VKTRACE_TPI_VK_vkDestroyShaderModule : {
		packet_vkDestroyShaderModule const*  obj = iter.Cast<packet_vkDestroyShaderModule*>();
		result << indent << "app.vkDestroyShaderModule( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*shaderModule*/ " << "app.GetResource(ShaderModuleID(" << remapper(obj->shaderModule) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreatePipelineCache : break;
	case VKTRACE_TPI_VK_vkDestroyPipelineCache : {
		packet_vkDestroyPipelineCache const*  obj = iter.Cast<packet_vkDestroyPipelineCache*>();
		result << indent << "app.vkDestroyPipelineCache( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pipelineCache*/ " << "app.GetResource(PipelineCacheID(" << remapper(obj->pipelineCache) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetPipelineCacheData : break;
	case VKTRACE_TPI_VK_vkMergePipelineCaches : {
		packet_vkMergePipelineCaches const*  obj = iter.Cast<packet_vkMergePipelineCaches*>();
		if ( obj->pSrcCaches ) {
			ASSERT( obj->srcCacheCount > 0 );
			before << indent << "const VkPipelineCache  " << nameSer.MakeUnique( &obj->pSrcCaches, "srcCaches"s, "pipelineCache"s ) << "[] = {";
			for (uint i = 0; i < obj->srcCacheCount; ++i) {
				before << (i ? "," : "") << (i%4 == 0 ? "\n\t"s << indent : " ") << "app.GetResource(PipelineCacheID(" << remapper(obj->pSrcCaches[i]) << "))";
			}
			before << "\n" << indent << "};\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pSrcCaches ) << ") == " << IntToString(obj->srcCacheCount) << " );\n\n";
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkMergePipelineCaches( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*dstCache*/ " << "app.GetResource(PipelineCacheID(" << remapper(obj->dstCache) << "))";
		result << ",\n";
		result << indent << "		/*srcCacheCount*/ " << IntToString( obj->srcCacheCount );
		result << ",\n";
		result << indent << "		/*pSrcCaches*/ " << nameSer.Get( &obj->pSrcCaches );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateGraphicsPipelines : {
		packet_vkCreateGraphicsPipelines const*  obj = iter.Cast<packet_vkCreateGraphicsPipelines*>();
		if ( obj->pCreateInfos ) {
			ASSERT( obj->createInfoCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pCreateInfos, "createInfos"s, "graphicsPipelineCreateInfo"s, "createInfo"s );
			before << indent << "VkGraphicsPipelineCreateInfo  " << arr_name << "[" << IntToString(obj->createInfoCount) << "] = {};\n";
			for (uint i = 0; i < obj->createInfoCount; ++i) {
				Serialize2_VkGraphicsPipelineCreateInfo( obj->pCreateInfos + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateGraphicsPipelines( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pipelineCache*/ " << "app.GetResource(PipelineCacheID(" << remapper(obj->pipelineCache) << "))";
		result << ",\n";
		result << indent << "		/*createInfoCount*/ " << IntToString( obj->createInfoCount );
		result << ",\n";
		result << indent << "		/*pCreateInfos*/ " << nameSer.Get( &obj->pCreateInfos );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pPipelines*/ " << "&app.EditResource(PipelineID(" << remapper(*obj->pPipelines) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateComputePipelines : {
		packet_vkCreateComputePipelines const*  obj = iter.Cast<packet_vkCreateComputePipelines*>();
		if ( obj->pCreateInfos ) {
			ASSERT( obj->createInfoCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pCreateInfos, "createInfos"s, "computePipelineCreateInfo"s, "createInfo"s );
			before << indent << "VkComputePipelineCreateInfo  " << arr_name << "[" << IntToString(obj->createInfoCount) << "] = {};\n";
			for (uint i = 0; i < obj->createInfoCount; ++i) {
				Serialize2_VkComputePipelineCreateInfo( obj->pCreateInfos + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateComputePipelines( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pipelineCache*/ " << "app.GetResource(PipelineCacheID(" << remapper(obj->pipelineCache) << "))";
		result << ",\n";
		result << indent << "		/*createInfoCount*/ " << IntToString( obj->createInfoCount );
		result << ",\n";
		result << indent << "		/*pCreateInfos*/ " << nameSer.Get( &obj->pCreateInfos );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pPipelines*/ " << "&app.EditResource(PipelineID(" << remapper(*obj->pPipelines) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyPipeline : {
		packet_vkDestroyPipeline const*  obj = iter.Cast<packet_vkDestroyPipeline*>();
		result << indent << "app.vkDestroyPipeline( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pipeline*/ " << "app.GetResource(PipelineID(" << remapper(obj->pipeline) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreatePipelineLayout : {
		packet_vkCreatePipelineLayout const*  obj = iter.Cast<packet_vkCreatePipelineLayout*>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreatePipelineLayout( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pPipelineLayout*/ " << "&app.EditResource(PipelineLayoutID(" << remapper(*obj->pPipelineLayout) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyPipelineLayout : {
		packet_vkDestroyPipelineLayout const*  obj = iter.Cast<packet_vkDestroyPipelineLayout*>();
		result << indent << "app.vkDestroyPipelineLayout( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pipelineLayout*/ " << "app.GetResource(PipelineLayoutID(" << remapper(obj->pipelineLayout) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateSampler : {
		packet_vkCreateSampler const*  obj = iter.Cast<packet_vkCreateSampler*>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateSampler( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pSampler*/ " << "&app.EditResource(SamplerID(" << remapper(*obj->pSampler) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroySampler : {
		packet_vkDestroySampler const*  obj = iter.Cast<packet_vkDestroySampler*>();
		result << indent << "app.vkDestroySampler( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*sampler*/ " << "app.GetResource(SamplerID(" << remapper(obj->sampler) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateDescriptorSetLayout : {
		packet_vkCreateDescriptorSetLayout const*  obj = iter.Cast<packet_vkCreateDescriptorSetLayout*>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateDescriptorSetLayout( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pSetLayout*/ " << "&app.EditResource(DescriptorSetLayoutID(" << remapper(*obj->pSetLayout) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyDescriptorSetLayout : {
		packet_vkDestroyDescriptorSetLayout const*  obj = iter.Cast<packet_vkDestroyDescriptorSetLayout*>();
		result << indent << "app.vkDestroyDescriptorSetLayout( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*descriptorSetLayout*/ " << "app.GetResource(DescriptorSetLayoutID(" << remapper(obj->descriptorSetLayout) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateDescriptorPool : {
		packet_vkCreateDescriptorPool const*  obj = iter.Cast<packet_vkCreateDescriptorPool*>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateDescriptorPool( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pDescriptorPool*/ " << "&app.EditResource(DescriptorPoolID(" << remapper(*obj->pDescriptorPool) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyDescriptorPool : {
		packet_vkDestroyDescriptorPool const*  obj = iter.Cast<packet_vkDestroyDescriptorPool*>();
		result << indent << "app.vkDestroyDescriptorPool( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*descriptorPool*/ " << "app.GetResource(DescriptorPoolID(" << remapper(obj->descriptorPool) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkResetDescriptorPool : {
		packet_vkResetDescriptorPool const*  obj = iter.Cast<packet_vkResetDescriptorPool*>();
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkResetDescriptorPool( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*descriptorPool*/ " << "app.GetResource(DescriptorPoolID(" << remapper(obj->descriptorPool) << "))";
		result << ",\n";
		result << indent << "		/*flags*/ " << Serialize_VkDescriptorPoolResetFlags( obj->flags );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkAllocateDescriptorSets : {
		packet_vkAllocateDescriptorSets const*  obj = iter.Cast<packet_vkAllocateDescriptorSets*>();
		if ( obj->pAllocateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pAllocateInfo), nameSer, remapper, indent );
		}
		before << "VkDescriptorSet " << nameSer.MakeUnique( &obj->pDescriptorSets, "descriptorSets"s, "descriptorSet"s ) << "[" << IntToString(obj->pAllocateInfo->descriptorSetCount) << "] = {};\n";
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkAllocateDescriptorSets( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pAllocateInfo*/ " << nameSer.GetPtr( obj->pAllocateInfo );
		result << ",\n";
		result << indent << "		/*pDescriptorSets*/ " << nameSer.Get( &obj->pDescriptorSets );
		result << " ));\n";
		for (uint i = 0; i < obj->pAllocateInfo->descriptorSetCount; ++i) {
			result << "app.EditResource(DescriptorSetID(" << remapper(*obj->pDescriptorSets) << ")) = " << nameSer.Get( &obj->pDescriptorSets ) << "[" << IntToString(i) << "];\n";
		}
		break;
	}

	case VKTRACE_TPI_VK_vkFreeDescriptorSets : {
		packet_vkFreeDescriptorSets const*  obj = iter.Cast<packet_vkFreeDescriptorSets*>();
		if ( obj->pDescriptorSets ) {
			ASSERT( obj->descriptorSetCount > 0 );
			before << indent << "const VkDescriptorSet  " << nameSer.MakeUnique( &obj->pDescriptorSets, "descriptorSets"s, "descriptorSet"s ) << "[] = {";
			for (uint i = 0; i < obj->descriptorSetCount; ++i) {
				before << (i ? "," : "") << (i%4 == 0 ? "\n\t"s << indent : " ") << "app.GetResource(DescriptorSetID(" << remapper(obj->pDescriptorSets[i]) << "))";
			}
			before << "\n" << indent << "};\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pDescriptorSets ) << ") == " << IntToString(obj->descriptorSetCount) << " );\n\n";
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkFreeDescriptorSets( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*descriptorPool*/ " << "app.GetResource(DescriptorPoolID(" << remapper(obj->descriptorPool) << "))";
		result << ",\n";
		result << indent << "		/*descriptorSetCount*/ " << IntToString( obj->descriptorSetCount );
		result << ",\n";
		result << indent << "		/*pDescriptorSets*/ " << nameSer.Get( &obj->pDescriptorSets );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkUpdateDescriptorSets : {
		packet_vkUpdateDescriptorSets const*  obj = iter.Cast<packet_vkUpdateDescriptorSets*>();
		if ( obj->pDescriptorWrites ) {
			ASSERT( obj->descriptorWriteCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pDescriptorWrites, "descriptorWrites"s, "writeDescriptorSet"s );
			before << indent << "VkWriteDescriptorSet  " << arr_name << "[" << IntToString(obj->descriptorWriteCount) << "] = {};\n";
			for (uint i = 0; i < obj->descriptorWriteCount; ++i) {
				Serialize2_VkWriteDescriptorSet( obj->pDescriptorWrites + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		if ( obj->pDescriptorCopies ) {
			ASSERT( obj->descriptorCopyCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pDescriptorCopies, "descriptorCopies"s, "copyDescriptorSet"s );
			before << indent << "VkCopyDescriptorSet  " << arr_name << "[" << IntToString(obj->descriptorCopyCount) << "] = {};\n";
			for (uint i = 0; i < obj->descriptorCopyCount; ++i) {
				Serialize2_VkCopyDescriptorSet( obj->pDescriptorCopies + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkUpdateDescriptorSets( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*descriptorWriteCount*/ " << IntToString( obj->descriptorWriteCount );
		result << ",\n";
		result << indent << "		/*pDescriptorWrites*/ " << nameSer.Get( &obj->pDescriptorWrites );
		result << ",\n";
		result << indent << "		/*descriptorCopyCount*/ " << IntToString( obj->descriptorCopyCount );
		result << ",\n";
		result << indent << "		/*pDescriptorCopies*/ " << nameSer.Get( &obj->pDescriptorCopies );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateFramebuffer : {
		packet_vkCreateFramebuffer const*  obj = iter.Cast<packet_vkCreateFramebuffer*>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateFramebuffer( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pFramebuffer*/ " << "&app.EditResource(FramebufferID(" << remapper(*obj->pFramebuffer) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyFramebuffer : {
		packet_vkDestroyFramebuffer const*  obj = iter.Cast<packet_vkDestroyFramebuffer*>();
		result << indent << "app.vkDestroyFramebuffer( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*framebuffer*/ " << "app.GetResource(FramebufferID(" << remapper(obj->framebuffer) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateRenderPass : {
		packet_vkCreateRenderPass const*  obj = iter.Cast<packet_vkCreateRenderPass*>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateRenderPass( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pRenderPass*/ " << "&app.EditResource(RenderPassID(" << remapper(*obj->pRenderPass) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyRenderPass : {
		packet_vkDestroyRenderPass const*  obj = iter.Cast<packet_vkDestroyRenderPass*>();
		result << indent << "app.vkDestroyRenderPass( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*renderPass*/ " << "app.GetResource(RenderPassID(" << remapper(obj->renderPass) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetRenderAreaGranularity : break;
	case VKTRACE_TPI_VK_vkCreateCommandPool : {
		packet_vkCreateCommandPool const*  obj = iter.Cast<packet_vkCreateCommandPool*>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateCommandPool( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pCommandPool*/ " << "&app.EditResource(CommandPoolID(" << remapper(*obj->pCommandPool) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyCommandPool : {
		packet_vkDestroyCommandPool const*  obj = iter.Cast<packet_vkDestroyCommandPool*>();
		result << indent << "app.vkDestroyCommandPool( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*commandPool*/ " << "app.GetResource(CommandPoolID(" << remapper(obj->commandPool) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkResetCommandPool : {
		packet_vkResetCommandPool const*  obj = iter.Cast<packet_vkResetCommandPool*>();
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkResetCommandPool( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*commandPool*/ " << "app.GetResource(CommandPoolID(" << remapper(obj->commandPool) << "))";
		result << ",\n";
		result << indent << "		/*flags*/ " << Serialize_VkCommandPoolResetFlags( obj->flags );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkAllocateCommandBuffers : {
		packet_vkAllocateCommandBuffers const*  obj = iter.Cast<packet_vkAllocateCommandBuffers*>();
		if ( obj->pAllocateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pAllocateInfo), nameSer, remapper, indent );
		}
		before << "VkCommandBuffer " << nameSer.MakeUnique( &obj->pCommandBuffers, "commandBuffers"s, "commandBuffer"s ) << "[" << IntToString(obj->pAllocateInfo->commandBufferCount) << "] = {};\n";
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkAllocateCommandBuffers( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pAllocateInfo*/ " << nameSer.GetPtr( obj->pAllocateInfo );
		result << ",\n";
		result << indent << "		/*pCommandBuffers*/ " << nameSer.Get( &obj->pCommandBuffers );
		result << " ));\n";
		for (uint i = 0; i < obj->pAllocateInfo->commandBufferCount; ++i) {
			result << "app.EditResource(CommandBufferID(" << remapper(*obj->pCommandBuffers) << ")) = " << nameSer.Get( &obj->pCommandBuffers ) << "[" << IntToString(i) << "];\n";
		}
		break;
	}

	case VKTRACE_TPI_VK_vkFreeCommandBuffers : {
		packet_vkFreeCommandBuffers const*  obj = iter.Cast<packet_vkFreeCommandBuffers*>();
		if ( obj->pCommandBuffers ) {
			ASSERT( obj->commandBufferCount > 0 );
			before << indent << "const VkCommandBuffer  " << nameSer.MakeUnique( &obj->pCommandBuffers, "commandBuffers"s, "commandBuffer"s ) << "[] = {";
			for (uint i = 0; i < obj->commandBufferCount; ++i) {
				before << (i ? "," : "") << (i%4 == 0 ? "\n\t"s << indent : " ") << "app.GetResource(CommandBufferID(" << remapper(obj->pCommandBuffers[i]) << "))";
			}
			before << "\n" << indent << "};\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pCommandBuffers ) << ") == " << IntToString(obj->commandBufferCount) << " );\n\n";
		}
		result << indent << "app.vkFreeCommandBuffers( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*commandPool*/ " << "app.GetResource(CommandPoolID(" << remapper(obj->commandPool) << "))";
		result << ",\n";
		result << indent << "		/*commandBufferCount*/ " << IntToString( obj->commandBufferCount );
		result << ",\n";
		result << indent << "		/*pCommandBuffers*/ " << nameSer.Get( &obj->pCommandBuffers );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkBeginCommandBuffer : {
		packet_vkBeginCommandBuffer const*  obj = iter.Cast<packet_vkBeginCommandBuffer*>();
		if ( obj->pBeginInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pBeginInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkBeginCommandBuffer( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*pBeginInfo*/ " << nameSer.GetPtr( obj->pBeginInfo );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkEndCommandBuffer : {
		packet_vkEndCommandBuffer const*  obj = iter.Cast<packet_vkEndCommandBuffer*>();
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkEndCommandBuffer( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkResetCommandBuffer : {
		packet_vkResetCommandBuffer const*  obj = iter.Cast<packet_vkResetCommandBuffer*>();
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkResetCommandBuffer( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*flags*/ " << Serialize_VkCommandBufferResetFlags( obj->flags );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdBindPipeline : {
		packet_vkCmdBindPipeline const*  obj = iter.Cast<packet_vkCmdBindPipeline*>();
		result << indent << "app.vkCmdBindPipeline( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*pipelineBindPoint*/ " << Serialize_VkPipelineBindPoint( obj->pipelineBindPoint );
		result << ",\n";
		result << indent << "		/*pipeline*/ " << "app.GetResource(PipelineID(" << remapper(obj->pipeline) << "))";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetViewport : {
		packet_vkCmdSetViewport const*  obj = iter.Cast<packet_vkCmdSetViewport*>();
		if ( obj->pViewports ) {
			ASSERT( obj->viewportCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pViewports, "viewports"s, "viewport"s );
			before << indent << "VkViewport  " << arr_name << "[" << IntToString(obj->viewportCount) << "] = {};\n";
			for (uint i = 0; i < obj->viewportCount; ++i) {
				Serialize2_VkViewport( obj->pViewports + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdSetViewport( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*firstViewport*/ " << IntToString( obj->firstViewport );
		result << ",\n";
		result << indent << "		/*viewportCount*/ " << IntToString( obj->viewportCount );
		result << ",\n";
		result << indent << "		/*pViewports*/ " << nameSer.Get( &obj->pViewports );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetScissor : {
		packet_vkCmdSetScissor const*  obj = iter.Cast<packet_vkCmdSetScissor*>();
		if ( obj->pScissors ) {
			ASSERT( obj->scissorCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pScissors, "scissors"s, "rect2D"s );
			before << indent << "VkRect2D  " << arr_name << "[" << IntToString(obj->scissorCount) << "] = {};\n";
			for (uint i = 0; i < obj->scissorCount; ++i) {
				Serialize2_VkRect2D( obj->pScissors + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdSetScissor( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*firstScissor*/ " << IntToString( obj->firstScissor );
		result << ",\n";
		result << indent << "		/*scissorCount*/ " << IntToString( obj->scissorCount );
		result << ",\n";
		result << indent << "		/*pScissors*/ " << nameSer.Get( &obj->pScissors );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetLineWidth : {
		packet_vkCmdSetLineWidth const*  obj = iter.Cast<packet_vkCmdSetLineWidth*>();
		result << indent << "app.vkCmdSetLineWidth( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*lineWidth*/ " << FloatToString( obj->lineWidth );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetDepthBias : {
		packet_vkCmdSetDepthBias const*  obj = iter.Cast<packet_vkCmdSetDepthBias*>();
		result << indent << "app.vkCmdSetDepthBias( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*depthBiasConstantFactor*/ " << FloatToString( obj->depthBiasConstantFactor );
		result << ",\n";
		result << indent << "		/*depthBiasClamp*/ " << FloatToString( obj->depthBiasClamp );
		result << ",\n";
		result << indent << "		/*depthBiasSlopeFactor*/ " << FloatToString( obj->depthBiasSlopeFactor );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetBlendConstants : {
		packet_vkCmdSetBlendConstants const*  obj = iter.Cast<packet_vkCmdSetBlendConstants*>();
		result << indent << "app.vkCmdSetBlendConstants( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*blendConstants*/ " << "StaticArray<float, " << IntToString(std::size(obj->blendConstants)) << ">{ ";
		for (uint i = 0; i < std::size(obj->blendConstants); ++i) {
			result << (i ? ", " : "") << FloatToString( obj->blendConstants[i] );
		}
		result << " }";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetDepthBounds : {
		packet_vkCmdSetDepthBounds const*  obj = iter.Cast<packet_vkCmdSetDepthBounds*>();
		result << indent << "app.vkCmdSetDepthBounds( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*minDepthBounds*/ " << FloatToString( obj->minDepthBounds );
		result << ",\n";
		result << indent << "		/*maxDepthBounds*/ " << FloatToString( obj->maxDepthBounds );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetStencilCompareMask : {
		packet_vkCmdSetStencilCompareMask const*  obj = iter.Cast<packet_vkCmdSetStencilCompareMask*>();
		result << indent << "app.vkCmdSetStencilCompareMask( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*faceMask*/ " << Serialize_VkStencilFaceFlags( obj->faceMask );
		result << ",\n";
		result << indent << "		/*compareMask*/ " << IntToString( obj->compareMask );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetStencilWriteMask : {
		packet_vkCmdSetStencilWriteMask const*  obj = iter.Cast<packet_vkCmdSetStencilWriteMask*>();
		result << indent << "app.vkCmdSetStencilWriteMask( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*faceMask*/ " << Serialize_VkStencilFaceFlags( obj->faceMask );
		result << ",\n";
		result << indent << "		/*writeMask*/ " << IntToString( obj->writeMask );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetStencilReference : {
		packet_vkCmdSetStencilReference const*  obj = iter.Cast<packet_vkCmdSetStencilReference*>();
		result << indent << "app.vkCmdSetStencilReference( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*faceMask*/ " << Serialize_VkStencilFaceFlags( obj->faceMask );
		result << ",\n";
		result << indent << "		/*reference*/ " << IntToString( obj->reference );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdBindDescriptorSets : {
		packet_vkCmdBindDescriptorSets const*  obj = iter.Cast<packet_vkCmdBindDescriptorSets*>();
		if ( obj->pDescriptorSets ) {
			ASSERT( obj->descriptorSetCount > 0 );
			before << indent << "const VkDescriptorSet  " << nameSer.MakeUnique( &obj->pDescriptorSets, "descriptorSets"s, "descriptorSet"s ) << "[] = {";
			for (uint i = 0; i < obj->descriptorSetCount; ++i) {
				before << (i ? "," : "") << (i%4 == 0 ? "\n\t"s << indent : " ") << "app.GetResource(DescriptorSetID(" << remapper(obj->pDescriptorSets[i]) << "))";
			}
			before << "\n" << indent << "};\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pDescriptorSets ) << ") == " << IntToString(obj->descriptorSetCount) << " );\n\n";
		}
		if ( obj->pDynamicOffsets ) {
			ASSERT( obj->dynamicOffsetCount > 0 );
			before << indent << "const uint32_t  " << nameSer.MakeUnique( &obj->pDynamicOffsets, "dynamicOffsets"s ) << "[] = { ";
			for (uint i = 0; i < obj->dynamicOffsetCount; ++i) {
				before << (i ? ", " : "") << (i%16 == 0 ? "\n\t"s << indent : " ") << IntToString( obj->pDynamicOffsets[i] );
			}
			before << indent << " };\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pDynamicOffsets ) << ") == " << IntToString(obj->dynamicOffsetCount) << " );\n\n";
		}
		result << indent << "app.vkCmdBindDescriptorSets( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*pipelineBindPoint*/ " << Serialize_VkPipelineBindPoint( obj->pipelineBindPoint );
		result << ",\n";
		result << indent << "		/*layout*/ " << "app.GetResource(PipelineLayoutID(" << remapper(obj->layout) << "))";
		result << ",\n";
		result << indent << "		/*firstSet*/ " << IntToString( obj->firstSet );
		result << ",\n";
		result << indent << "		/*descriptorSetCount*/ " << IntToString( obj->descriptorSetCount );
		result << ",\n";
		result << indent << "		/*pDescriptorSets*/ " << nameSer.Get( &obj->pDescriptorSets );
		result << ",\n";
		result << indent << "		/*dynamicOffsetCount*/ " << IntToString( obj->dynamicOffsetCount );
		result << ",\n";
		result << indent << "		/*pDynamicOffsets*/ " << nameSer.Get( &obj->pDynamicOffsets );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdBindIndexBuffer : {
		packet_vkCmdBindIndexBuffer const*  obj = iter.Cast<packet_vkCmdBindIndexBuffer*>();
		result << indent << "app.vkCmdBindIndexBuffer( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*buffer*/ " << "app.GetResource(BufferID(" << remapper(obj->buffer) << "))";
		result << ",\n";
		result << indent << "		/*offset*/ " << IntToString( obj->offset );
		result << ",\n";
		result << indent << "		/*indexType*/ " << Serialize_VkIndexType( obj->indexType );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdBindVertexBuffers : {
		packet_vkCmdBindVertexBuffers const*  obj = iter.Cast<packet_vkCmdBindVertexBuffers*>();
		if ( obj->pBuffers ) {
			ASSERT( obj->bindingCount > 0 );
			before << indent << "const VkBuffer  " << nameSer.MakeUnique( &obj->pBuffers, "buffers"s, "buffer"s ) << "[] = {";
			for (uint i = 0; i < obj->bindingCount; ++i) {
				before << (i ? "," : "") << (i%4 == 0 ? "\n\t"s << indent : " ") << "app.GetResource(BufferID(" << remapper(obj->pBuffers[i]) << "))";
			}
			before << "\n" << indent << "};\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pBuffers ) << ") == " << IntToString(obj->bindingCount) << " );\n\n";
		}
		if ( obj->pOffsets ) {
			ASSERT( obj->bindingCount > 0 );
			before << indent << "const VkDeviceSize  " << nameSer.MakeUnique( &obj->pOffsets, "offsets"s ) << "[] = { ";
			for (uint i = 0; i < obj->bindingCount; ++i) {
				before << (i ? ", " : "") << (i%16 == 0 ? "\n\t"s << indent : " ") << IntToString( obj->pOffsets[i] );
			}
			before << indent << " };\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pOffsets ) << ") == " << IntToString(obj->bindingCount) << " );\n\n";
		}
		result << indent << "app.vkCmdBindVertexBuffers( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*firstBinding*/ " << IntToString( obj->firstBinding );
		result << ",\n";
		result << indent << "		/*bindingCount*/ " << IntToString( obj->bindingCount );
		result << ",\n";
		result << indent << "		/*pBuffers*/ " << nameSer.Get( &obj->pBuffers );
		result << ",\n";
		result << indent << "		/*pOffsets*/ " << nameSer.Get( &obj->pOffsets );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDraw : {
		packet_vkCmdDraw const*  obj = iter.Cast<packet_vkCmdDraw*>();
		result << indent << "app.vkCmdDraw( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*vertexCount*/ " << IntToString( obj->vertexCount );
		result << ",\n";
		result << indent << "		/*instanceCount*/ " << IntToString( obj->instanceCount );
		result << ",\n";
		result << indent << "		/*firstVertex*/ " << IntToString( obj->firstVertex );
		result << ",\n";
		result << indent << "		/*firstInstance*/ " << IntToString( obj->firstInstance );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDrawIndexed : {
		packet_vkCmdDrawIndexed const*  obj = iter.Cast<packet_vkCmdDrawIndexed*>();
		result << indent << "app.vkCmdDrawIndexed( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*indexCount*/ " << IntToString( obj->indexCount );
		result << ",\n";
		result << indent << "		/*instanceCount*/ " << IntToString( obj->instanceCount );
		result << ",\n";
		result << indent << "		/*firstIndex*/ " << IntToString( obj->firstIndex );
		result << ",\n";
		result << indent << "		/*vertexOffset*/ " << IntToString( obj->vertexOffset );
		result << ",\n";
		result << indent << "		/*firstInstance*/ " << IntToString( obj->firstInstance );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDrawIndirect : {
		packet_vkCmdDrawIndirect const*  obj = iter.Cast<packet_vkCmdDrawIndirect*>();
		result << indent << "app.vkCmdDrawIndirect( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*buffer*/ " << "app.GetResource(BufferID(" << remapper(obj->buffer) << "))";
		result << ",\n";
		result << indent << "		/*offset*/ " << IntToString( obj->offset );
		result << ",\n";
		result << indent << "		/*drawCount*/ " << IntToString( obj->drawCount );
		result << ",\n";
		result << indent << "		/*stride*/ " << IntToString( obj->stride );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDrawIndexedIndirect : {
		packet_vkCmdDrawIndexedIndirect const*  obj = iter.Cast<packet_vkCmdDrawIndexedIndirect*>();
		result << indent << "app.vkCmdDrawIndexedIndirect( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*buffer*/ " << "app.GetResource(BufferID(" << remapper(obj->buffer) << "))";
		result << ",\n";
		result << indent << "		/*offset*/ " << IntToString( obj->offset );
		result << ",\n";
		result << indent << "		/*drawCount*/ " << IntToString( obj->drawCount );
		result << ",\n";
		result << indent << "		/*stride*/ " << IntToString( obj->stride );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDispatch : {
		packet_vkCmdDispatch const*  obj = iter.Cast<packet_vkCmdDispatch*>();
		result << indent << "app.vkCmdDispatch( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*groupCountX*/ " << IntToString( obj->groupCountX );
		result << ",\n";
		result << indent << "		/*groupCountY*/ " << IntToString( obj->groupCountY );
		result << ",\n";
		result << indent << "		/*groupCountZ*/ " << IntToString( obj->groupCountZ );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDispatchIndirect : {
		packet_vkCmdDispatchIndirect const*  obj = iter.Cast<packet_vkCmdDispatchIndirect*>();
		result << indent << "app.vkCmdDispatchIndirect( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*buffer*/ " << "app.GetResource(BufferID(" << remapper(obj->buffer) << "))";
		result << ",\n";
		result << indent << "		/*offset*/ " << IntToString( obj->offset );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdCopyBuffer : {
		packet_vkCmdCopyBuffer const*  obj = iter.Cast<packet_vkCmdCopyBuffer*>();
		if ( obj->pRegions ) {
			ASSERT( obj->regionCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pRegions, "regions"s, "bufferCopy"s );
			before << indent << "VkBufferCopy  " << arr_name << "[" << IntToString(obj->regionCount) << "] = {};\n";
			for (uint i = 0; i < obj->regionCount; ++i) {
				Serialize2_VkBufferCopy( obj->pRegions + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdCopyBuffer( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*srcBuffer*/ " << "app.GetResource(BufferID(" << remapper(obj->srcBuffer) << "))";
		result << ",\n";
		result << indent << "		/*dstBuffer*/ " << "app.GetResource(BufferID(" << remapper(obj->dstBuffer) << "))";
		result << ",\n";
		result << indent << "		/*regionCount*/ " << IntToString( obj->regionCount );
		result << ",\n";
		result << indent << "		/*pRegions*/ " << nameSer.Get( &obj->pRegions );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdCopyImage : {
		packet_vkCmdCopyImage const*  obj = iter.Cast<packet_vkCmdCopyImage*>();
		if ( obj->pRegions ) {
			ASSERT( obj->regionCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pRegions, "regions"s, "imageCopy"s );
			before << indent << "VkImageCopy  " << arr_name << "[" << IntToString(obj->regionCount) << "] = {};\n";
			for (uint i = 0; i < obj->regionCount; ++i) {
				Serialize2_VkImageCopy( obj->pRegions + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdCopyImage( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*srcImage*/ " << "app.GetResource(ImageID(" << remapper(obj->srcImage) << "))";
		result << ",\n";
		result << indent << "		/*srcImageLayout*/ " << Serialize_VkImageLayout( obj->srcImageLayout );
		result << ",\n";
		result << indent << "		/*dstImage*/ " << "app.GetResource(ImageID(" << remapper(obj->dstImage) << "))";
		result << ",\n";
		result << indent << "		/*dstImageLayout*/ " << Serialize_VkImageLayout( obj->dstImageLayout );
		result << ",\n";
		result << indent << "		/*regionCount*/ " << IntToString( obj->regionCount );
		result << ",\n";
		result << indent << "		/*pRegions*/ " << nameSer.Get( &obj->pRegions );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdBlitImage : {
		packet_vkCmdBlitImage const*  obj = iter.Cast<packet_vkCmdBlitImage*>();
		if ( obj->pRegions ) {
			ASSERT( obj->regionCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pRegions, "regions"s, "imageBlit"s );
			before << indent << "VkImageBlit  " << arr_name << "[" << IntToString(obj->regionCount) << "] = {};\n";
			for (uint i = 0; i < obj->regionCount; ++i) {
				Serialize2_VkImageBlit( obj->pRegions + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdBlitImage( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*srcImage*/ " << "app.GetResource(ImageID(" << remapper(obj->srcImage) << "))";
		result << ",\n";
		result << indent << "		/*srcImageLayout*/ " << Serialize_VkImageLayout( obj->srcImageLayout );
		result << ",\n";
		result << indent << "		/*dstImage*/ " << "app.GetResource(ImageID(" << remapper(obj->dstImage) << "))";
		result << ",\n";
		result << indent << "		/*dstImageLayout*/ " << Serialize_VkImageLayout( obj->dstImageLayout );
		result << ",\n";
		result << indent << "		/*regionCount*/ " << IntToString( obj->regionCount );
		result << ",\n";
		result << indent << "		/*pRegions*/ " << nameSer.Get( &obj->pRegions );
		result << ",\n";
		result << indent << "		/*filter*/ " << Serialize_VkFilter( obj->filter );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdCopyBufferToImage : {
		packet_vkCmdCopyBufferToImage const*  obj = iter.Cast<packet_vkCmdCopyBufferToImage*>();
		if ( obj->pRegions ) {
			ASSERT( obj->regionCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pRegions, "regions"s, "bufferImageCopy"s );
			before << indent << "VkBufferImageCopy  " << arr_name << "[" << IntToString(obj->regionCount) << "] = {};\n";
			for (uint i = 0; i < obj->regionCount; ++i) {
				Serialize2_VkBufferImageCopy( obj->pRegions + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdCopyBufferToImage( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*srcBuffer*/ " << "app.GetResource(BufferID(" << remapper(obj->srcBuffer) << "))";
		result << ",\n";
		result << indent << "		/*dstImage*/ " << "app.GetResource(ImageID(" << remapper(obj->dstImage) << "))";
		result << ",\n";
		result << indent << "		/*dstImageLayout*/ " << Serialize_VkImageLayout( obj->dstImageLayout );
		result << ",\n";
		result << indent << "		/*regionCount*/ " << IntToString( obj->regionCount );
		result << ",\n";
		result << indent << "		/*pRegions*/ " << nameSer.Get( &obj->pRegions );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdCopyImageToBuffer : {
		packet_vkCmdCopyImageToBuffer const*  obj = iter.Cast<packet_vkCmdCopyImageToBuffer*>();
		if ( obj->pRegions ) {
			ASSERT( obj->regionCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pRegions, "regions"s, "bufferImageCopy"s );
			before << indent << "VkBufferImageCopy  " << arr_name << "[" << IntToString(obj->regionCount) << "] = {};\n";
			for (uint i = 0; i < obj->regionCount; ++i) {
				Serialize2_VkBufferImageCopy( obj->pRegions + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdCopyImageToBuffer( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*srcImage*/ " << "app.GetResource(ImageID(" << remapper(obj->srcImage) << "))";
		result << ",\n";
		result << indent << "		/*srcImageLayout*/ " << Serialize_VkImageLayout( obj->srcImageLayout );
		result << ",\n";
		result << indent << "		/*dstBuffer*/ " << "app.GetResource(BufferID(" << remapper(obj->dstBuffer) << "))";
		result << ",\n";
		result << indent << "		/*regionCount*/ " << IntToString( obj->regionCount );
		result << ",\n";
		result << indent << "		/*pRegions*/ " << nameSer.Get( &obj->pRegions );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdUpdateBuffer : {
		packet_vkCmdUpdateBuffer const*  obj = iter.Cast<packet_vkCmdUpdateBuffer*>();
		ASSERT( (obj->dataSize > 0) and (obj->dataSize % 4 == 0) );
		before << indent << "const FIValue " << nameSer.MakeUnique( &obj->pData, "data"s ) << "[] = {";
		for (uint i = 0; i < obj->dataSize; ++i) {
			before << (i ? "," : "") << (i%8 == 0 ? "\n\t"s << indent : " ") << VoidToFIValueString( obj->pData, i*sizeof(FIValue) );
		}
		before << '\n' << indent << "};\n";
		before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pData ) << ") == " << IntToString(obj->dataSize) << " );\n\n";
		result << indent << "app.vkCmdUpdateBuffer( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*dstBuffer*/ " << "app.GetResource(BufferID(" << remapper(obj->dstBuffer) << "))";
		result << ",\n";
		result << indent << "		/*dstOffset*/ " << IntToString( obj->dstOffset );
		result << ",\n";
		result << indent << "		/*dataSize*/ " << IntToString( obj->dataSize );
		result << ",\n";
		result << indent << "		/*pData*/ " << nameSer.Get( &obj->pData );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdFillBuffer : {
		packet_vkCmdFillBuffer const*  obj = iter.Cast<packet_vkCmdFillBuffer*>();
		result << indent << "app.vkCmdFillBuffer( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*dstBuffer*/ " << "app.GetResource(BufferID(" << remapper(obj->dstBuffer) << "))";
		result << ",\n";
		result << indent << "		/*dstOffset*/ " << IntToString( obj->dstOffset );
		result << ",\n";
		result << indent << "		/*size*/ " << IntToString( obj->size );
		result << ",\n";
		result << indent << "		/*data*/ " << IntToString( obj->data );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdClearColorImage : {
		packet_vkCmdClearColorImage const*  obj = iter.Cast<packet_vkCmdClearColorImage*>();
		if ( obj->pColor ) {
			before << Serialize_VkClearColorValue( obj->pColor, nameSer, remapper, indent );
		}
		if ( obj->pRanges ) {
			ASSERT( obj->rangeCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pRanges, "ranges"s, "imageSubresourceRange"s );
			before << indent << "VkImageSubresourceRange  " << arr_name << "[" << IntToString(obj->rangeCount) << "] = {};\n";
			for (uint i = 0; i < obj->rangeCount; ++i) {
				Serialize2_VkImageSubresourceRange( obj->pRanges + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdClearColorImage( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*image*/ " << "app.GetResource(ImageID(" << remapper(obj->image) << "))";
		result << ",\n";
		result << indent << "		/*imageLayout*/ " << Serialize_VkImageLayout( obj->imageLayout );
		result << ",\n";
		result << indent << "		/*pColor*/ " << nameSer.GetPtr( obj->pColor );
		result << ",\n";
		result << indent << "		/*rangeCount*/ " << IntToString( obj->rangeCount );
		result << ",\n";
		result << indent << "		/*pRanges*/ " << nameSer.Get( &obj->pRanges );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdClearDepthStencilImage : {
		packet_vkCmdClearDepthStencilImage const*  obj = iter.Cast<packet_vkCmdClearDepthStencilImage*>();
		if ( obj->pDepthStencil ) {
			before << Serialize_VkClearDepthStencilValue( obj->pDepthStencil, nameSer, remapper, indent );
		}
		if ( obj->pRanges ) {
			ASSERT( obj->rangeCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pRanges, "ranges"s, "imageSubresourceRange"s );
			before << indent << "VkImageSubresourceRange  " << arr_name << "[" << IntToString(obj->rangeCount) << "] = {};\n";
			for (uint i = 0; i < obj->rangeCount; ++i) {
				Serialize2_VkImageSubresourceRange( obj->pRanges + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdClearDepthStencilImage( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*image*/ " << "app.GetResource(ImageID(" << remapper(obj->image) << "))";
		result << ",\n";
		result << indent << "		/*imageLayout*/ " << Serialize_VkImageLayout( obj->imageLayout );
		result << ",\n";
		result << indent << "		/*pDepthStencil*/ " << nameSer.GetPtr( obj->pDepthStencil );
		result << ",\n";
		result << indent << "		/*rangeCount*/ " << IntToString( obj->rangeCount );
		result << ",\n";
		result << indent << "		/*pRanges*/ " << nameSer.Get( &obj->pRanges );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdClearAttachments : {
		packet_vkCmdClearAttachments const*  obj = iter.Cast<packet_vkCmdClearAttachments*>();
		if ( obj->pAttachments ) {
			ASSERT( obj->attachmentCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pAttachments, "attachments"s, "clearAttachment"s );
			before << indent << "VkClearAttachment  " << arr_name << "[" << IntToString(obj->attachmentCount) << "] = {};\n";
			for (uint i = 0; i < obj->attachmentCount; ++i) {
				Serialize2_VkClearAttachment( obj->pAttachments + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		if ( obj->pRects ) {
			ASSERT( obj->rectCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pRects, "rects"s, "clearRect"s );
			before << indent << "VkClearRect  " << arr_name << "[" << IntToString(obj->rectCount) << "] = {};\n";
			for (uint i = 0; i < obj->rectCount; ++i) {
				Serialize2_VkClearRect( obj->pRects + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdClearAttachments( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*attachmentCount*/ " << IntToString( obj->attachmentCount );
		result << ",\n";
		result << indent << "		/*pAttachments*/ " << nameSer.Get( &obj->pAttachments );
		result << ",\n";
		result << indent << "		/*rectCount*/ " << IntToString( obj->rectCount );
		result << ",\n";
		result << indent << "		/*pRects*/ " << nameSer.Get( &obj->pRects );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdResolveImage : {
		packet_vkCmdResolveImage const*  obj = iter.Cast<packet_vkCmdResolveImage*>();
		if ( obj->pRegions ) {
			ASSERT( obj->regionCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pRegions, "regions"s, "imageResolve"s );
			before << indent << "VkImageResolve  " << arr_name << "[" << IntToString(obj->regionCount) << "] = {};\n";
			for (uint i = 0; i < obj->regionCount; ++i) {
				Serialize2_VkImageResolve( obj->pRegions + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdResolveImage( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*srcImage*/ " << "app.GetResource(ImageID(" << remapper(obj->srcImage) << "))";
		result << ",\n";
		result << indent << "		/*srcImageLayout*/ " << Serialize_VkImageLayout( obj->srcImageLayout );
		result << ",\n";
		result << indent << "		/*dstImage*/ " << "app.GetResource(ImageID(" << remapper(obj->dstImage) << "))";
		result << ",\n";
		result << indent << "		/*dstImageLayout*/ " << Serialize_VkImageLayout( obj->dstImageLayout );
		result << ",\n";
		result << indent << "		/*regionCount*/ " << IntToString( obj->regionCount );
		result << ",\n";
		result << indent << "		/*pRegions*/ " << nameSer.Get( &obj->pRegions );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetEvent : {
		packet_vkCmdSetEvent const*  obj = iter.Cast<packet_vkCmdSetEvent*>();
		result << indent << "app.vkCmdSetEvent( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*event*/ " << "app.GetResource(EventID(" << remapper(obj->event) << "))";
		result << ",\n";
		result << indent << "		/*stageMask*/ " << Serialize_VkPipelineStageFlags( obj->stageMask );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdResetEvent : {
		packet_vkCmdResetEvent const*  obj = iter.Cast<packet_vkCmdResetEvent*>();
		result << indent << "app.vkCmdResetEvent( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*event*/ " << "app.GetResource(EventID(" << remapper(obj->event) << "))";
		result << ",\n";
		result << indent << "		/*stageMask*/ " << Serialize_VkPipelineStageFlags( obj->stageMask );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdWaitEvents : {
		packet_vkCmdWaitEvents const*  obj = iter.Cast<packet_vkCmdWaitEvents*>();
		if ( obj->pEvents ) {
			ASSERT( obj->eventCount > 0 );
			before << indent << "const VkEvent  " << nameSer.MakeUnique( &obj->pEvents, "events"s, "event"s ) << "[] = {";
			for (uint i = 0; i < obj->eventCount; ++i) {
				before << (i ? "," : "") << (i%4 == 0 ? "\n\t"s << indent : " ") << "app.GetResource(EventID(" << remapper(obj->pEvents[i]) << "))";
			}
			before << "\n" << indent << "};\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pEvents ) << ") == " << IntToString(obj->eventCount) << " );\n\n";
		}
		if ( obj->pMemoryBarriers ) {
			ASSERT( obj->memoryBarrierCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pMemoryBarriers, "memoryBarriers"s, "memoryBarrier"s, "barrier"s );
			before << indent << "VkMemoryBarrier  " << arr_name << "[" << IntToString(obj->memoryBarrierCount) << "] = {};\n";
			for (uint i = 0; i < obj->memoryBarrierCount; ++i) {
				Serialize2_VkMemoryBarrier( obj->pMemoryBarriers + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		if ( obj->pBufferMemoryBarriers ) {
			ASSERT( obj->bufferMemoryBarrierCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pBufferMemoryBarriers, "bufferMemoryBarriers"s, "bufferMemoryBarrier"s, "barrier"s );
			before << indent << "VkBufferMemoryBarrier  " << arr_name << "[" << IntToString(obj->bufferMemoryBarrierCount) << "] = {};\n";
			for (uint i = 0; i < obj->bufferMemoryBarrierCount; ++i) {
				Serialize2_VkBufferMemoryBarrier( obj->pBufferMemoryBarriers + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		if ( obj->pImageMemoryBarriers ) {
			ASSERT( obj->imageMemoryBarrierCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pImageMemoryBarriers, "imageMemoryBarriers"s, "imageMemoryBarrier"s, "barrier"s );
			before << indent << "VkImageMemoryBarrier  " << arr_name << "[" << IntToString(obj->imageMemoryBarrierCount) << "] = {};\n";
			for (uint i = 0; i < obj->imageMemoryBarrierCount; ++i) {
				Serialize2_VkImageMemoryBarrier( obj->pImageMemoryBarriers + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdWaitEvents( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*eventCount*/ " << IntToString( obj->eventCount );
		result << ",\n";
		result << indent << "		/*pEvents*/ " << nameSer.Get( &obj->pEvents );
		result << ",\n";
		result << indent << "		/*srcStageMask*/ " << Serialize_VkPipelineStageFlags( obj->srcStageMask );
		result << ",\n";
		result << indent << "		/*dstStageMask*/ " << Serialize_VkPipelineStageFlags( obj->dstStageMask );
		result << ",\n";
		result << indent << "		/*memoryBarrierCount*/ " << IntToString( obj->memoryBarrierCount );
		result << ",\n";
		result << indent << "		/*pMemoryBarriers*/ " << nameSer.Get( &obj->pMemoryBarriers );
		result << ",\n";
		result << indent << "		/*bufferMemoryBarrierCount*/ " << IntToString( obj->bufferMemoryBarrierCount );
		result << ",\n";
		result << indent << "		/*pBufferMemoryBarriers*/ " << nameSer.Get( &obj->pBufferMemoryBarriers );
		result << ",\n";
		result << indent << "		/*imageMemoryBarrierCount*/ " << IntToString( obj->imageMemoryBarrierCount );
		result << ",\n";
		result << indent << "		/*pImageMemoryBarriers*/ " << nameSer.Get( &obj->pImageMemoryBarriers );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdPipelineBarrier : {
		packet_vkCmdPipelineBarrier const*  obj = iter.Cast<packet_vkCmdPipelineBarrier*>();
		if ( obj->pMemoryBarriers ) {
			ASSERT( obj->memoryBarrierCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pMemoryBarriers, "memoryBarriers"s, "memoryBarrier"s, "barrier"s );
			before << indent << "VkMemoryBarrier  " << arr_name << "[" << IntToString(obj->memoryBarrierCount) << "] = {};\n";
			for (uint i = 0; i < obj->memoryBarrierCount; ++i) {
				Serialize2_VkMemoryBarrier( obj->pMemoryBarriers + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		if ( obj->pBufferMemoryBarriers ) {
			ASSERT( obj->bufferMemoryBarrierCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pBufferMemoryBarriers, "bufferMemoryBarriers"s, "bufferMemoryBarrier"s, "barrier"s );
			before << indent << "VkBufferMemoryBarrier  " << arr_name << "[" << IntToString(obj->bufferMemoryBarrierCount) << "] = {};\n";
			for (uint i = 0; i < obj->bufferMemoryBarrierCount; ++i) {
				Serialize2_VkBufferMemoryBarrier( obj->pBufferMemoryBarriers + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		if ( obj->pImageMemoryBarriers ) {
			ASSERT( obj->imageMemoryBarrierCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pImageMemoryBarriers, "imageMemoryBarriers"s, "imageMemoryBarrier"s, "barrier"s );
			before << indent << "VkImageMemoryBarrier  " << arr_name << "[" << IntToString(obj->imageMemoryBarrierCount) << "] = {};\n";
			for (uint i = 0; i < obj->imageMemoryBarrierCount; ++i) {
				Serialize2_VkImageMemoryBarrier( obj->pImageMemoryBarriers + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdPipelineBarrier( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*srcStageMask*/ " << Serialize_VkPipelineStageFlags( obj->srcStageMask );
		result << ",\n";
		result << indent << "		/*dstStageMask*/ " << Serialize_VkPipelineStageFlags( obj->dstStageMask );
		result << ",\n";
		result << indent << "		/*dependencyFlags*/ " << Serialize_VkDependencyFlags( obj->dependencyFlags );
		result << ",\n";
		result << indent << "		/*memoryBarrierCount*/ " << IntToString( obj->memoryBarrierCount );
		result << ",\n";
		result << indent << "		/*pMemoryBarriers*/ " << nameSer.Get( &obj->pMemoryBarriers );
		result << ",\n";
		result << indent << "		/*bufferMemoryBarrierCount*/ " << IntToString( obj->bufferMemoryBarrierCount );
		result << ",\n";
		result << indent << "		/*pBufferMemoryBarriers*/ " << nameSer.Get( &obj->pBufferMemoryBarriers );
		result << ",\n";
		result << indent << "		/*imageMemoryBarrierCount*/ " << IntToString( obj->imageMemoryBarrierCount );
		result << ",\n";
		result << indent << "		/*pImageMemoryBarriers*/ " << nameSer.Get( &obj->pImageMemoryBarriers );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdBeginQuery : {
		packet_vkCmdBeginQuery const*  obj = iter.Cast<packet_vkCmdBeginQuery*>();
		result << indent << "app.vkCmdBeginQuery( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*queryPool*/ " << "app.GetResource(QueryPoolID(" << remapper(obj->queryPool) << "))";
		result << ",\n";
		result << indent << "		/*query*/ " << IntToString( obj->query );
		result << ",\n";
		result << indent << "		/*flags*/ " << Serialize_VkQueryControlFlags( obj->flags );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdEndQuery : {
		packet_vkCmdEndQuery const*  obj = iter.Cast<packet_vkCmdEndQuery*>();
		result << indent << "app.vkCmdEndQuery( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*queryPool*/ " << "app.GetResource(QueryPoolID(" << remapper(obj->queryPool) << "))";
		result << ",\n";
		result << indent << "		/*query*/ " << IntToString( obj->query );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdResetQueryPool : {
		packet_vkCmdResetQueryPool const*  obj = iter.Cast<packet_vkCmdResetQueryPool*>();
		result << indent << "app.vkCmdResetQueryPool( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*queryPool*/ " << "app.GetResource(QueryPoolID(" << remapper(obj->queryPool) << "))";
		result << ",\n";
		result << indent << "		/*firstQuery*/ " << IntToString( obj->firstQuery );
		result << ",\n";
		result << indent << "		/*queryCount*/ " << IntToString( obj->queryCount );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdWriteTimestamp : {
		packet_vkCmdWriteTimestamp const*  obj = iter.Cast<packet_vkCmdWriteTimestamp*>();
		result << indent << "app.vkCmdWriteTimestamp( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*pipelineStage*/ " << Serialize_VkPipelineStageFlagBits( obj->pipelineStage );
		result << ",\n";
		result << indent << "		/*queryPool*/ " << "app.GetResource(QueryPoolID(" << remapper(obj->queryPool) << "))";
		result << ",\n";
		result << indent << "		/*query*/ " << IntToString( obj->query );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdCopyQueryPoolResults : {
		packet_vkCmdCopyQueryPoolResults const*  obj = iter.Cast<packet_vkCmdCopyQueryPoolResults*>();
		result << indent << "app.vkCmdCopyQueryPoolResults( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*queryPool*/ " << "app.GetResource(QueryPoolID(" << remapper(obj->queryPool) << "))";
		result << ",\n";
		result << indent << "		/*firstQuery*/ " << IntToString( obj->firstQuery );
		result << ",\n";
		result << indent << "		/*queryCount*/ " << IntToString( obj->queryCount );
		result << ",\n";
		result << indent << "		/*dstBuffer*/ " << "app.GetResource(BufferID(" << remapper(obj->dstBuffer) << "))";
		result << ",\n";
		result << indent << "		/*dstOffset*/ " << IntToString( obj->dstOffset );
		result << ",\n";
		result << indent << "		/*stride*/ " << IntToString( obj->stride );
		result << ",\n";
		result << indent << "		/*flags*/ " << Serialize_VkQueryResultFlags( obj->flags );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdPushConstants : {
		packet_vkCmdPushConstants const*  obj = iter.Cast<packet_vkCmdPushConstants*>();
		ASSERT( (obj->size > 0) and (obj->size % 4 == 0) );
		before << indent << "const FIValue " << nameSer.MakeUnique( &obj->pValues, "values"s ) << "[] = {";
		for (uint i = 0; i < obj->size; ++i) {
			before << (i ? "," : "") << (i%8 == 0 ? "\n\t"s << indent : " ") << VoidToFIValueString( obj->pValues, i*sizeof(FIValue) );
		}
		before << '\n' << indent << "};\n";
		before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pValues ) << ") == " << IntToString(obj->size) << " );\n\n";
		result << indent << "app.vkCmdPushConstants( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*layout*/ " << "app.GetResource(PipelineLayoutID(" << remapper(obj->layout) << "))";
		result << ",\n";
		result << indent << "		/*stageFlags*/ " << Serialize_VkShaderStageFlags( obj->stageFlags );
		result << ",\n";
		result << indent << "		/*offset*/ " << IntToString( obj->offset );
		result << ",\n";
		result << indent << "		/*size*/ " << IntToString( obj->size );
		result << ",\n";
		result << indent << "		/*pValues*/ " << nameSer.Get( &obj->pValues );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdBeginRenderPass : {
		packet_vkCmdBeginRenderPass const*  obj = iter.Cast<packet_vkCmdBeginRenderPass*>();
		if ( obj->pRenderPassBegin ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pRenderPassBegin), nameSer, remapper, indent );
		}
		result << indent << "app.vkCmdBeginRenderPass( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*pRenderPassBegin*/ " << nameSer.GetPtr( obj->pRenderPassBegin );
		result << ",\n";
		result << indent << "		/*contents*/ " << Serialize_VkSubpassContents( obj->contents );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdNextSubpass : {
		packet_vkCmdNextSubpass const*  obj = iter.Cast<packet_vkCmdNextSubpass*>();
		result << indent << "app.vkCmdNextSubpass( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*contents*/ " << Serialize_VkSubpassContents( obj->contents );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdEndRenderPass : {
		packet_vkCmdEndRenderPass const*  obj = iter.Cast<packet_vkCmdEndRenderPass*>();
		result << indent << "app.vkCmdEndRenderPass( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdExecuteCommands : {
		packet_vkCmdExecuteCommands const*  obj = iter.Cast<packet_vkCmdExecuteCommands*>();
		if ( obj->pCommandBuffers ) {
			ASSERT( obj->commandBufferCount > 0 );
			before << indent << "const VkCommandBuffer  " << nameSer.MakeUnique( &obj->pCommandBuffers, "commandBuffers"s, "commandBuffer"s ) << "[] = {";
			for (uint i = 0; i < obj->commandBufferCount; ++i) {
				before << (i ? "," : "") << (i%4 == 0 ? "\n\t"s << indent : " ") << "app.GetResource(CommandBufferID(" << remapper(obj->pCommandBuffers[i]) << "))";
			}
			before << "\n" << indent << "};\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pCommandBuffers ) << ") == " << IntToString(obj->commandBufferCount) << " );\n\n";
		}
		result << indent << "app.vkCmdExecuteCommands( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*commandBufferCount*/ " << IntToString( obj->commandBufferCount );
		result << ",\n";
		result << indent << "		/*pCommandBuffers*/ " << nameSer.Get( &obj->pCommandBuffers );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroySurfaceKHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceSupportKHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceCapabilitiesKHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceFormatsKHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfacePresentModesKHR : break;
	case VKTRACE_TPI_VK_vkCreateSwapchainKHR : {
		packet_vkCreateSwapchainKHR const*  obj = iter.Cast<packet_vkCreateSwapchainKHR*>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateSwapchainKHR( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pSwapchain*/ " << "&app.EditResource(SwapchainKHRID(" << remapper(*obj->pSwapchain) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroySwapchainKHR : break;
	case VKTRACE_TPI_VK_vkGetSwapchainImagesKHR : break;
	case VKTRACE_TPI_VK_vkAcquireNextImageKHR : break;
	case VKTRACE_TPI_VK_vkQueuePresentKHR : break;
	case VKTRACE_TPI_VK_vkCreateSharedSwapchainsKHR : {
		packet_vkCreateSharedSwapchainsKHR const*  obj = iter.Cast<packet_vkCreateSharedSwapchainsKHR*>();
		if ( obj->pCreateInfos ) {
			ASSERT( obj->swapchainCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pCreateInfos, "createInfos"s, "swapchainCreateInfo"s, "createInfo"s );
			before << indent << "VkSwapchainCreateInfoKHR  " << arr_name << "[" << IntToString(obj->swapchainCount) << "] = {};\n";
			for (uint i = 0; i < obj->swapchainCount; ++i) {
				Serialize2_VkSwapchainCreateInfoKHR( obj->pCreateInfos + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		before << "VkSwapchainKHR " << nameSer.MakeUnique( &obj->pSwapchains, "swapchains"s, "swapchain"s ) << "[" << IntToString(obj->swapchainCount) << "] = {};\n";
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateSharedSwapchainsKHR( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*swapchainCount*/ " << IntToString( obj->swapchainCount );
		result << ",\n";
		result << indent << "		/*pCreateInfos*/ " << nameSer.Get( &obj->pCreateInfos );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pSwapchains*/ " << nameSer.Get( &obj->pSwapchains );
		result << " ));\n";
		for (uint i = 0; i < obj->swapchainCount; ++i) {
			result << "app.EditResource(SwapchainKHRID(" << remapper(*obj->pSwapchains) << ")) = " << nameSer.Get( &obj->pSwapchains ) << "[" << IntToString(i) << "];\n";
		}
		break;
	}

	case VKTRACE_TPI_VK_vkCreateWin32SurfaceKHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceWin32PresentationSupportKHR : break;
	case VKTRACE_TPI_VK_vkCreateXlibSurfaceKHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceXlibPresentationSupportKHR : break;
	case VKTRACE_TPI_VK_vkCreateXcbSurfaceKHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceXcbPresentationSupportKHR : break;
	case VKTRACE_TPI_VK_vkCreateAndroidSurfaceKHR : break;
	case VKTRACE_TPI_VK_vkGetMemoryWin32HandleNV : break;
	case VKTRACE_TPI_VK_vkCreateDescriptorUpdateTemplateKHR : {
		packet_vkCreateDescriptorUpdateTemplateKHR const*  obj = iter.Cast<packet_vkCreateDescriptorUpdateTemplateKHR*>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateDescriptorUpdateTemplateKHR( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pDescriptorUpdateTemplate*/ " << "&app.EditResource(DescriptorUpdateTemplateID(" << remapper(*obj->pDescriptorUpdateTemplate) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyDescriptorUpdateTemplateKHR : {
		packet_vkDestroyDescriptorUpdateTemplateKHR const*  obj = iter.Cast<packet_vkDestroyDescriptorUpdateTemplateKHR*>();
		result << indent << "app.vkDestroyDescriptorUpdateTemplateKHR( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*descriptorUpdateTemplate*/ " << "app.GetResource(DescriptorUpdateTemplateID(" << remapper(obj->descriptorUpdateTemplate) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

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
	case VKTRACE_TPI_VK_vkCreateDisplayModeKHR : {
		packet_vkCreateDisplayModeKHR const*  obj = iter.Cast<packet_vkCreateDisplayModeKHR*>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( vkCreateDisplayModeKHR( \n";
		result << indent << "		/*physicalDevice*/ " << "app.GetResource(PhysicalDeviceID(" << remapper(obj->physicalDevice) << "))";
		result << ",\n";
		result << indent << "		/*display*/ " << "app.GetResource(DisplayKHRID(" << remapper(obj->display) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pMode*/ " << "&app.EditResource(DisplayModeKHRID(" << remapper(*obj->pMode) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetDisplayPlaneCapabilitiesKHR : break;
	case VKTRACE_TPI_VK_vkCreateDisplayPlaneSurfaceKHR : break;
	case VKTRACE_TPI_VK_vkTrimCommandPoolKHR : {
		packet_vkTrimCommandPoolKHR const*  obj = iter.Cast<packet_vkTrimCommandPoolKHR*>();
		result << indent << "app.vkTrimCommandPoolKHR( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*commandPool*/ " << "app.GetResource(CommandPoolID(" << remapper(obj->commandPool) << "))";
		result << ",\n";
		result << indent << "		/*flags*/ " << Serialize_VkCommandPoolTrimFlags( obj->flags );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalBufferPropertiesKHR : break;
	case VKTRACE_TPI_VK_vkGetMemoryFdKHR : break;
	case VKTRACE_TPI_VK_vkGetMemoryFdPropertiesKHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR : break;
	case VKTRACE_TPI_VK_vkImportSemaphoreFdKHR : {
		packet_vkImportSemaphoreFdKHR const*  obj = iter.Cast<packet_vkImportSemaphoreFdKHR*>();
		if ( obj->pImportSemaphoreFdInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pImportSemaphoreFdInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkImportSemaphoreFdKHR( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pImportSemaphoreFdInfo*/ " << nameSer.GetPtr( obj->pImportSemaphoreFdInfo );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetSemaphoreFdKHR : break;
	case VKTRACE_TPI_VK_vkCmdPushDescriptorSetKHR : {
		packet_vkCmdPushDescriptorSetKHR const*  obj = iter.Cast<packet_vkCmdPushDescriptorSetKHR*>();
		if ( obj->pDescriptorWrites ) {
			ASSERT( obj->descriptorWriteCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pDescriptorWrites, "descriptorWrites"s, "writeDescriptorSet"s );
			before << indent << "VkWriteDescriptorSet  " << arr_name << "[" << IntToString(obj->descriptorWriteCount) << "] = {};\n";
			for (uint i = 0; i < obj->descriptorWriteCount; ++i) {
				Serialize2_VkWriteDescriptorSet( obj->pDescriptorWrites + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdPushDescriptorSetKHR( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*pipelineBindPoint*/ " << Serialize_VkPipelineBindPoint( obj->pipelineBindPoint );
		result << ",\n";
		result << indent << "		/*layout*/ " << "app.GetResource(PipelineLayoutID(" << remapper(obj->layout) << "))";
		result << ",\n";
		result << indent << "		/*set*/ " << IntToString( obj->set );
		result << ",\n";
		result << indent << "		/*descriptorWriteCount*/ " << IntToString( obj->descriptorWriteCount );
		result << ",\n";
		result << indent << "		/*pDescriptorWrites*/ " << nameSer.Get( &obj->pDescriptorWrites );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetSwapchainStatusKHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalFencePropertiesKHR : break;
	case VKTRACE_TPI_VK_vkGetDeviceGroupPeerMemoryFeaturesKHX : break;
	case VKTRACE_TPI_VK_vkBindBufferMemory2KHR : {
		packet_vkBindBufferMemory2KHR const*  obj = iter.Cast<packet_vkBindBufferMemory2KHR*>();
		if ( obj->pBindInfos ) {
			ASSERT( obj->bindInfoCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pBindInfos, "bindInfos"s, "bindBufferMemoryInfo"s, "info"s );
			before << indent << "VkBindBufferMemoryInfo  " << arr_name << "[" << IntToString(obj->bindInfoCount) << "] = {};\n";
			for (uint i = 0; i < obj->bindInfoCount; ++i) {
				Serialize2_VkBindBufferMemoryInfo( obj->pBindInfos + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkBindBufferMemory2KHR( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*bindInfoCount*/ " << IntToString( obj->bindInfoCount );
		result << ",\n";
		result << indent << "		/*pBindInfos*/ " << nameSer.Get( &obj->pBindInfos );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkBindImageMemory2KHR : {
		packet_vkBindImageMemory2KHR const*  obj = iter.Cast<packet_vkBindImageMemory2KHR*>();
		if ( obj->pBindInfos ) {
			ASSERT( obj->bindInfoCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pBindInfos, "bindInfos"s, "bindImageMemoryInfo"s, "info"s );
			before << indent << "VkBindImageMemoryInfo  " << arr_name << "[" << IntToString(obj->bindInfoCount) << "] = {};\n";
			for (uint i = 0; i < obj->bindInfoCount; ++i) {
				Serialize2_VkBindImageMemoryInfo( obj->pBindInfos + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkBindImageMemory2KHR( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*bindInfoCount*/ " << IntToString( obj->bindInfoCount );
		result << ",\n";
		result << indent << "		/*pBindInfos*/ " << nameSer.Get( &obj->pBindInfos );
		result << " ));\n";
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
		packet_vkCmdProcessCommandsNVX const*  obj = iter.Cast<packet_vkCmdProcessCommandsNVX*>();
		if ( obj->pProcessCommandsInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pProcessCommandsInfo), nameSer, remapper, indent );
		}
		result << indent << "app.vkCmdProcessCommandsNVX( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*pProcessCommandsInfo*/ " << nameSer.GetPtr( obj->pProcessCommandsInfo );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdReserveSpaceForCommandsNVX : {
		packet_vkCmdReserveSpaceForCommandsNVX const*  obj = iter.Cast<packet_vkCmdReserveSpaceForCommandsNVX*>();
		if ( obj->pReserveSpaceInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pReserveSpaceInfo), nameSer, remapper, indent );
		}
		result << indent << "app.vkCmdReserveSpaceForCommandsNVX( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*pReserveSpaceInfo*/ " << nameSer.GetPtr( obj->pReserveSpaceInfo );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateIndirectCommandsLayoutNVX : {
		packet_vkCreateIndirectCommandsLayoutNVX const*  obj = iter.Cast<packet_vkCreateIndirectCommandsLayoutNVX*>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateIndirectCommandsLayoutNVX( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pIndirectCommandsLayout*/ " << "&app.EditResource(IndirectCommandsLayoutNVXID(" << remapper(*obj->pIndirectCommandsLayout) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyIndirectCommandsLayoutNVX : {
		packet_vkDestroyIndirectCommandsLayoutNVX const*  obj = iter.Cast<packet_vkDestroyIndirectCommandsLayoutNVX*>();
		result << indent << "app.vkDestroyIndirectCommandsLayoutNVX( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*indirectCommandsLayout*/ " << "app.GetResource(IndirectCommandsLayoutNVXID(" << remapper(obj->indirectCommandsLayout) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateObjectTableNVX : {
		packet_vkCreateObjectTableNVX const*  obj = iter.Cast<packet_vkCreateObjectTableNVX*>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateObjectTableNVX( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pObjectTable*/ " << "&app.EditResource(ObjectTableNVXID(" << remapper(*obj->pObjectTable) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyObjectTableNVX : {
		packet_vkDestroyObjectTableNVX const*  obj = iter.Cast<packet_vkDestroyObjectTableNVX*>();
		result << indent << "app.vkDestroyObjectTableNVX( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*objectTable*/ " << "app.GetResource(ObjectTableNVXID(" << remapper(obj->objectTable) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkRegisterObjectsNVX : {
		packet_vkRegisterObjectsNVX const*  obj = iter.Cast<packet_vkRegisterObjectsNVX*>();
		if ( obj->ppObjectTableEntries ) {
			ASSERT( obj->objectCount > 0 );
			for (uint i = 0; i < obj->objectCount; ++i) {
				before << Serialize_VkObjectTableEntryNVX( obj->ppObjectTableEntries[i], nameSer, remapper, indent );
			}
			before << indent << "const VkObjectTableEntryNVX*  " << nameSer.MakeUnique( &obj->ppObjectTableEntries, "ppObjectTableEntries"s, "objectTableEntryNVX"s ) << " = { ";
			for (uint i = 0; i < obj->objectCount; ++i) {
				before << (i ? "," : "") << "\n\t\t" << indent << nameSer.GetPtr( obj->ppObjectTableEntries[i] );
			}
			before << indent << " };\n";
		}
		if ( obj->pObjectIndices ) {
			ASSERT( obj->objectCount > 0 );
			before << indent << "const uint32_t  " << nameSer.MakeUnique( &obj->pObjectIndices, "objectIndices"s ) << "[] = { ";
			for (uint i = 0; i < obj->objectCount; ++i) {
				before << (i ? ", " : "") << (i%16 == 0 ? "\n\t"s << indent : " ") << IntToString( obj->pObjectIndices[i] );
			}
			before << indent << " };\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pObjectIndices ) << ") == " << IntToString(obj->objectCount) << " );\n\n";
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkRegisterObjectsNVX( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*objectTable*/ " << "app.GetResource(ObjectTableNVXID(" << remapper(obj->objectTable) << "))";
		result << ",\n";
		result << indent << "		/*objectCount*/ " << IntToString( obj->objectCount );
		result << ",\n";
		result << indent << "		/*ppObjectTableEntries*/ " << nameSer.Get( &obj->ppObjectTableEntries );
		result << ",\n";
		result << indent << "		/*pObjectIndices*/ " << nameSer.Get( &obj->pObjectIndices );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkUnregisterObjectsNVX : {
		packet_vkUnregisterObjectsNVX const*  obj = iter.Cast<packet_vkUnregisterObjectsNVX*>();
		if ( obj->pObjectEntryTypes ) {
			ASSERT( obj->objectCount > 0 );
			before << indent << "const VkObjectEntryTypeNVX  " << nameSer.MakeUnique( &obj->pObjectEntryTypes, "objectEntryTypes"s ) << "[] = {";
			for (uint i = 0; i < obj->objectCount; ++i) {
				before << (i ? "," : "") << (i%4 == 0 ? "\n\t"s << indent : " ") << Serialize_VkObjectEntryTypeNVX( obj->pObjectEntryTypes[i] );
			}
			before << "\n" << indent << " };\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pObjectEntryTypes ) << ") == " << IntToString(obj->objectCount) << " );\n\n";
		}
		if ( obj->pObjectIndices ) {
			ASSERT( obj->objectCount > 0 );
			before << indent << "const uint32_t  " << nameSer.MakeUnique( &obj->pObjectIndices, "objectIndices"s ) << "[] = { ";
			for (uint i = 0; i < obj->objectCount; ++i) {
				before << (i ? ", " : "") << (i%16 == 0 ? "\n\t"s << indent : " ") << IntToString( obj->pObjectIndices[i] );
			}
			before << indent << " };\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pObjectIndices ) << ") == " << IntToString(obj->objectCount) << " );\n\n";
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkUnregisterObjectsNVX( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*objectTable*/ " << "app.GetResource(ObjectTableNVXID(" << remapper(obj->objectTable) << "))";
		result << ",\n";
		result << indent << "		/*objectCount*/ " << IntToString( obj->objectCount );
		result << ",\n";
		result << indent << "		/*pObjectEntryTypes*/ " << nameSer.Get( &obj->pObjectEntryTypes );
		result << ",\n";
		result << indent << "		/*pObjectIndices*/ " << nameSer.Get( &obj->pObjectIndices );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX : break;
	case VKTRACE_TPI_VK_vkCmdSetViewportWScalingNV : {
		packet_vkCmdSetViewportWScalingNV const*  obj = iter.Cast<packet_vkCmdSetViewportWScalingNV*>();
		if ( obj->pViewportWScalings ) {
			ASSERT( obj->viewportCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pViewportWScalings, "viewportWScalings"s, "viewportWScalingNV"s );
			before << indent << "VkViewportWScalingNV  " << arr_name << "[" << IntToString(obj->viewportCount) << "] = {};\n";
			for (uint i = 0; i < obj->viewportCount; ++i) {
				Serialize2_VkViewportWScalingNV( obj->pViewportWScalings + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdSetViewportWScalingNV( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*firstViewport*/ " << IntToString( obj->firstViewport );
		result << ",\n";
		result << indent << "		/*viewportCount*/ " << IntToString( obj->viewportCount );
		result << ",\n";
		result << indent << "		/*pViewportWScalings*/ " << nameSer.Get( &obj->pViewportWScalings );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkReleaseDisplayEXT : {
		packet_vkReleaseDisplayEXT const*  obj = iter.Cast<packet_vkReleaseDisplayEXT*>();
		VK_CALL( obj->result );
		result << indent << "VK_CALL( vkReleaseDisplayEXT( \n";
		result << indent << "		/*physicalDevice*/ " << "app.GetResource(PhysicalDeviceID(" << remapper(obj->physicalDevice) << "))";
		result << ",\n";
		result << indent << "		/*display*/ " << "app.GetResource(DisplayKHRID(" << remapper(obj->display) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceCapabilities2EXT : break;
	case VKTRACE_TPI_VK_vkGetRefreshCycleDurationGOOGLE : break;
	case VKTRACE_TPI_VK_vkGetPastPresentationTimingGOOGLE : break;
	case VKTRACE_TPI_VK_vkCmdSetDiscardRectangleEXT : {
		packet_vkCmdSetDiscardRectangleEXT const*  obj = iter.Cast<packet_vkCmdSetDiscardRectangleEXT*>();
		if ( obj->pDiscardRectangles ) {
			ASSERT( obj->discardRectangleCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pDiscardRectangles, "discardRectangles"s, "rect2D"s );
			before << indent << "VkRect2D  " << arr_name << "[" << IntToString(obj->discardRectangleCount) << "] = {};\n";
			for (uint i = 0; i < obj->discardRectangleCount; ++i) {
				Serialize2_VkRect2D( obj->pDiscardRectangles + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdSetDiscardRectangleEXT( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*firstDiscardRectangle*/ " << IntToString( obj->firstDiscardRectangle );
		result << ",\n";
		result << indent << "		/*discardRectangleCount*/ " << IntToString( obj->discardRectangleCount );
		result << ",\n";
		result << indent << "		/*pDiscardRectangles*/ " << nameSer.Get( &obj->pDiscardRectangles );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkSetHdrMetadataEXT : {
		packet_vkSetHdrMetadataEXT const*  obj = iter.Cast<packet_vkSetHdrMetadataEXT*>();
		if ( obj->pSwapchains ) {
			ASSERT( obj->swapchainCount > 0 );
			before << indent << "const VkSwapchainKHR  " << nameSer.MakeUnique( &obj->pSwapchains, "swapchains"s, "swapchain"s ) << "[] = {";
			for (uint i = 0; i < obj->swapchainCount; ++i) {
				before << (i ? "," : "") << (i%4 == 0 ? "\n\t"s << indent : " ") << "app.GetResource(SwapchainKHRID(" << remapper(obj->pSwapchains[i]) << "))";
			}
			before << "\n" << indent << "};\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pSwapchains ) << ") == " << IntToString(obj->swapchainCount) << " );\n\n";
		}
		if ( obj->pMetadata ) {
			ASSERT( obj->swapchainCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pMetadata, "metadata"s, "hdrMetadata"s );
			before << indent << "VkHdrMetadataEXT  " << arr_name << "[" << IntToString(obj->swapchainCount) << "] = {};\n";
			for (uint i = 0; i < obj->swapchainCount; ++i) {
				Serialize2_VkHdrMetadataEXT( obj->pMetadata + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkSetHdrMetadataEXT( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*swapchainCount*/ " << IntToString( obj->swapchainCount );
		result << ",\n";
		result << indent << "		/*pSwapchains*/ " << nameSer.Get( &obj->pSwapchains );
		result << ",\n";
		result << indent << "		/*pMetadata*/ " << nameSer.Get( &obj->pMetadata );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkAcquireXlibDisplayEXT : break;
	case VKTRACE_TPI_VK_vkGetRandROutputDisplayEXT : break;
	case VKTRACE_TPI_VK_vkDisplayPowerControlEXT : {
		packet_vkDisplayPowerControlEXT const*  obj = iter.Cast<packet_vkDisplayPowerControlEXT*>();
		if ( obj->pDisplayPowerInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pDisplayPowerInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkDisplayPowerControlEXT( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*display*/ " << "app.GetResource(DisplayKHRID(" << remapper(obj->display) << "))";
		result << ",\n";
		result << indent << "		/*pDisplayPowerInfo*/ " << nameSer.GetPtr( obj->pDisplayPowerInfo );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkRegisterDeviceEventEXT : {
		packet_vkRegisterDeviceEventEXT const*  obj = iter.Cast<packet_vkRegisterDeviceEventEXT*>();
		if ( obj->pDeviceEventInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pDeviceEventInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkRegisterDeviceEventEXT( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pDeviceEventInfo*/ " << nameSer.GetPtr( obj->pDeviceEventInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pFence*/ " << "&app.EditResource(FenceID(" << remapper(*obj->pFence) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkRegisterDisplayEventEXT : {
		packet_vkRegisterDisplayEventEXT const*  obj = iter.Cast<packet_vkRegisterDisplayEventEXT*>();
		if ( obj->pDisplayEventInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pDisplayEventInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkRegisterDisplayEventEXT( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*display*/ " << "app.GetResource(DisplayKHRID(" << remapper(obj->display) << "))";
		result << ",\n";
		result << indent << "		/*pDisplayEventInfo*/ " << nameSer.GetPtr( obj->pDisplayEventInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pFence*/ " << "&app.EditResource(FenceID(" << remapper(*obj->pFence) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetSwapchainCounterEXT : break;
	case VKTRACE_TPI_VK_vkCmdSetSampleLocationsEXT : {
		packet_vkCmdSetSampleLocationsEXT const*  obj = iter.Cast<packet_vkCmdSetSampleLocationsEXT*>();
		if ( obj->pSampleLocationsInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pSampleLocationsInfo), nameSer, remapper, indent );
		}
		result << indent << "app.vkCmdSetSampleLocationsEXT( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*pSampleLocationsInfo*/ " << nameSer.GetPtr( obj->pSampleLocationsInfo );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceMultisamplePropertiesEXT : break;
	case VKTRACE_TPI_VK_vkCreateSamplerYcbcrConversionKHR : {
		packet_vkCreateSamplerYcbcrConversionKHR const*  obj = iter.Cast<packet_vkCreateSamplerYcbcrConversionKHR*>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateSamplerYcbcrConversionKHR( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pYcbcrConversion*/ " << "&app.EditResource(SamplerYcbcrConversionID(" << remapper(*obj->pYcbcrConversion) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroySamplerYcbcrConversionKHR : {
		packet_vkDestroySamplerYcbcrConversionKHR const*  obj = iter.Cast<packet_vkDestroySamplerYcbcrConversionKHR*>();
		result << indent << "app.vkDestroySamplerYcbcrConversionKHR( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*ycbcrConversion*/ " << "app.GetResource(SamplerYcbcrConversionID(" << remapper(obj->ycbcrConversion) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetDisplayPlaneSupportedDisplaysKHR : break;
	case VKTRACE_TPI_VK_vkImportFenceFdKHR : {
		packet_vkImportFenceFdKHR const*  obj = iter.Cast<packet_vkImportFenceFdKHR*>();
		if ( obj->pImportFenceFdInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pImportFenceFdInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkImportFenceFdKHR( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pImportFenceFdInfo*/ " << nameSer.GetPtr( obj->pImportFenceFdInfo );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetFenceFdKHR : break;
	case VKTRACE_TPI_VK_vkImportFenceWin32HandleKHR : {
		packet_vkImportFenceWin32HandleKHR const*  obj = iter.Cast<packet_vkImportFenceWin32HandleKHR*>();
		if ( obj->pImportFenceWin32HandleInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pImportFenceWin32HandleInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkImportFenceWin32HandleKHR( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pImportFenceWin32HandleInfo*/ " << nameSer.GetPtr( obj->pImportFenceWin32HandleInfo );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetFenceWin32HandleKHR : break;
	case VKTRACE_TPI_VK_vkGetMemoryWin32HandleKHR : break;
	case VKTRACE_TPI_VK_vkGetMemoryWin32HandlePropertiesKHR : break;
	case VKTRACE_TPI_VK_vkImportSemaphoreWin32HandleKHR : {
		packet_vkImportSemaphoreWin32HandleKHR const*  obj = iter.Cast<packet_vkImportSemaphoreWin32HandleKHR*>();
		if ( obj->pImportSemaphoreWin32HandleInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pImportSemaphoreWin32HandleInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkImportSemaphoreWin32HandleKHR( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pImportSemaphoreWin32HandleInfo*/ " << nameSer.GetPtr( obj->pImportSemaphoreWin32HandleInfo );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetSemaphoreWin32HandleKHR : break;
	case VKTRACE_TPI_VK_vkGetMemoryHostPointerPropertiesEXT : break;
	case VKTRACE_TPI_VK_vkCreateValidationCacheEXT : break;
	case VKTRACE_TPI_VK_vkDestroyValidationCacheEXT : {
		packet_vkDestroyValidationCacheEXT const*  obj = iter.Cast<packet_vkDestroyValidationCacheEXT*>();
		result << indent << "app.vkDestroyValidationCacheEXT( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*validationCache*/ " << "app.GetResource(ValidationCacheEXTID(" << remapper(obj->validationCache) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkMergeValidationCachesEXT : {
		packet_vkMergeValidationCachesEXT const*  obj = iter.Cast<packet_vkMergeValidationCachesEXT*>();
		if ( obj->pSrcCaches ) {
			ASSERT( obj->srcCacheCount > 0 );
			before << indent << "const VkValidationCacheEXT  " << nameSer.MakeUnique( &obj->pSrcCaches, "srcCaches"s, "validationCache"s ) << "[] = {";
			for (uint i = 0; i < obj->srcCacheCount; ++i) {
				before << (i ? "," : "") << (i%4 == 0 ? "\n\t"s << indent : " ") << "app.GetResource(ValidationCacheEXTID(" << remapper(obj->pSrcCaches[i]) << "))";
			}
			before << "\n" << indent << "};\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pSrcCaches ) << ") == " << IntToString(obj->srcCacheCount) << " );\n\n";
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkMergeValidationCachesEXT( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*dstCache*/ " << "app.GetResource(ValidationCacheEXTID(" << remapper(obj->dstCache) << "))";
		result << ",\n";
		result << indent << "		/*srcCacheCount*/ " << IntToString( obj->srcCacheCount );
		result << ",\n";
		result << indent << "		/*pSrcCaches*/ " << nameSer.Get( &obj->pSrcCaches );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetValidationCacheDataEXT : break;
	case VKTRACE_TPI_VK_vkGetShaderInfoAMD : break;
	case VKTRACE_TPI_VK_vkGetDeviceQueue2 : break;
	case VKTRACE_TPI_VK_vkEnumerateInstanceVersion : break;
	case VKTRACE_TPI_VK_vkGetDescriptorSetLayoutSupport : break;
	case VKTRACE_TPI_VK_vkGetDeviceGroupPresentCapabilitiesKHR : break;
	case VKTRACE_TPI_VK_vkGetDeviceGroupSurfacePresentModesKHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDevicePresentRectanglesKHR : break;
	case VKTRACE_TPI_VK_vkAcquireNextImage2KHR : break;
	case VKTRACE_TPI_VK_vkBindBufferMemory2 : {
		packet_vkBindBufferMemory2 const*  obj = iter.Cast<packet_vkBindBufferMemory2*>();
		if ( obj->pBindInfos ) {
			ASSERT( obj->bindInfoCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pBindInfos, "bindInfos"s, "bindBufferMemoryInfo"s, "info"s );
			before << indent << "VkBindBufferMemoryInfo  " << arr_name << "[" << IntToString(obj->bindInfoCount) << "] = {};\n";
			for (uint i = 0; i < obj->bindInfoCount; ++i) {
				Serialize2_VkBindBufferMemoryInfo( obj->pBindInfos + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkBindBufferMemory2( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*bindInfoCount*/ " << IntToString( obj->bindInfoCount );
		result << ",\n";
		result << indent << "		/*pBindInfos*/ " << nameSer.Get( &obj->pBindInfos );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkBindImageMemory2 : {
		packet_vkBindImageMemory2 const*  obj = iter.Cast<packet_vkBindImageMemory2*>();
		if ( obj->pBindInfos ) {
			ASSERT( obj->bindInfoCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pBindInfos, "bindInfos"s, "bindImageMemoryInfo"s, "info"s );
			before << indent << "VkBindImageMemoryInfo  " << arr_name << "[" << IntToString(obj->bindInfoCount) << "] = {};\n";
			for (uint i = 0; i < obj->bindInfoCount; ++i) {
				Serialize2_VkBindImageMemoryInfo( obj->pBindInfos + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkBindImageMemory2( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*bindInfoCount*/ " << IntToString( obj->bindInfoCount );
		result << ",\n";
		result << indent << "		/*pBindInfos*/ " << nameSer.Get( &obj->pBindInfos );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetDeviceGroupPeerMemoryFeatures : break;
	case VKTRACE_TPI_VK_vkCmdSetDeviceMask : {
		packet_vkCmdSetDeviceMask const*  obj = iter.Cast<packet_vkCmdSetDeviceMask*>();
		result << indent << "app.vkCmdSetDeviceMask( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*deviceMask*/ " << IntToString( obj->deviceMask );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDispatchBase : {
		packet_vkCmdDispatchBase const*  obj = iter.Cast<packet_vkCmdDispatchBase*>();
		result << indent << "app.vkCmdDispatchBase( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper(obj->commandBuffer) << "))";
		result << ",\n";
		result << indent << "		/*baseGroupX*/ " << IntToString( obj->baseGroupX );
		result << ",\n";
		result << indent << "		/*baseGroupY*/ " << IntToString( obj->baseGroupY );
		result << ",\n";
		result << indent << "		/*baseGroupZ*/ " << IntToString( obj->baseGroupZ );
		result << ",\n";
		result << indent << "		/*groupCountX*/ " << IntToString( obj->groupCountX );
		result << ",\n";
		result << indent << "		/*groupCountY*/ " << IntToString( obj->groupCountY );
		result << ",\n";
		result << indent << "		/*groupCountZ*/ " << IntToString( obj->groupCountZ );
		result << " );\n";
		break;
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
		packet_vkTrimCommandPool const*  obj = iter.Cast<packet_vkTrimCommandPool*>();
		result << indent << "app.vkTrimCommandPool( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*commandPool*/ " << "app.GetResource(CommandPoolID(" << remapper(obj->commandPool) << "))";
		result << ",\n";
		result << indent << "		/*flags*/ " << Serialize_VkCommandPoolTrimFlags( obj->flags );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateSamplerYcbcrConversion : {
		packet_vkCreateSamplerYcbcrConversion const*  obj = iter.Cast<packet_vkCreateSamplerYcbcrConversion*>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateSamplerYcbcrConversion( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pYcbcrConversion*/ " << "&app.EditResource(SamplerYcbcrConversionID(" << remapper(*obj->pYcbcrConversion) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroySamplerYcbcrConversion : {
		packet_vkDestroySamplerYcbcrConversion const*  obj = iter.Cast<packet_vkDestroySamplerYcbcrConversion*>();
		result << indent << "app.vkDestroySamplerYcbcrConversion( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*ycbcrConversion*/ " << "app.GetResource(SamplerYcbcrConversionID(" << remapper(obj->ycbcrConversion) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateDescriptorUpdateTemplate : {
		packet_vkCreateDescriptorUpdateTemplate const*  obj = iter.Cast<packet_vkCreateDescriptorUpdateTemplate*>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateDescriptorUpdateTemplate( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pDescriptorUpdateTemplate*/ " << "&app.EditResource(DescriptorUpdateTemplateID(" << remapper(*obj->pDescriptorUpdateTemplate) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyDescriptorUpdateTemplate : {
		packet_vkDestroyDescriptorUpdateTemplate const*  obj = iter.Cast<packet_vkDestroyDescriptorUpdateTemplate*>();
		result << indent << "app.vkDestroyDescriptorUpdateTemplate( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper(obj->device) << "))";
		result << ",\n";
		result << indent << "		/*descriptorUpdateTemplate*/ " << "app.GetResource(DescriptorUpdateTemplateID(" << remapper(obj->descriptorUpdateTemplate) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
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
