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
		auto const*  obj = iter.Cast< packet_vkCmdDrawIndirectCountAMD *>();
		result << indent << "app.vkCmdDrawIndirectCountAMD( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*buffer*/ " << "app.GetResource(BufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, obj->buffer ) << "))";
		result << ",\n";
		result << indent << "		/*offset*/ " << IntToString(obj->offset);
		result << ",\n";
		result << indent << "		/*countBuffer*/ " << "app.GetResource(BufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, obj->countBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*countBufferOffset*/ " << IntToString(obj->countBufferOffset);
		result << ",\n";
		result << indent << "		/*maxDrawCount*/ " << IntToString(obj->maxDrawCount);
		result << ",\n";
		result << indent << "		/*stride*/ " << IntToString(obj->stride);
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDrawIndexedIndirectCountAMD : {
		auto const*  obj = iter.Cast< packet_vkCmdDrawIndexedIndirectCountAMD *>();
		result << indent << "app.vkCmdDrawIndexedIndirectCountAMD( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*buffer*/ " << "app.GetResource(BufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, obj->buffer ) << "))";
		result << ",\n";
		result << indent << "		/*offset*/ " << IntToString(obj->offset);
		result << ",\n";
		result << indent << "		/*countBuffer*/ " << "app.GetResource(BufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, obj->countBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*countBufferOffset*/ " << IntToString(obj->countBufferOffset);
		result << ",\n";
		result << indent << "		/*maxDrawCount*/ " << IntToString(obj->maxDrawCount);
		result << ",\n";
		result << indent << "		/*stride*/ " << IntToString(obj->stride);
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateDebugReportCallbackEXT : break;
	case VKTRACE_TPI_VK_vkDestroyDebugReportCallbackEXT : break;
	case VKTRACE_TPI_VK_vkDebugReportMessageEXT : break;
	case VKTRACE_TPI_VK_vkDebugMarkerSetObjectTagEXT : {
		auto const*  obj = iter.Cast< packet_vkDebugMarkerSetObjectTagEXT *>();
		if ( obj->pTagInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pTagInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkDebugMarkerSetObjectTagEXT( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pTagInfo*/ " << nameSer.GetPtr( obj->pTagInfo );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDebugMarkerSetObjectNameEXT : {
		auto const*  obj = iter.Cast< packet_vkDebugMarkerSetObjectNameEXT *>();
		if ( obj->pNameInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pNameInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkDebugMarkerSetObjectNameEXT( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pNameInfo*/ " << nameSer.GetPtr( obj->pNameInfo );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDebugMarkerBeginEXT : {
		auto const*  obj = iter.Cast< packet_vkCmdDebugMarkerBeginEXT *>();
		if ( obj->pMarkerInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pMarkerInfo), nameSer, remapper, indent );
		}
		result << indent << "app.vkCmdDebugMarkerBeginEXT( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*pMarkerInfo*/ " << nameSer.GetPtr( obj->pMarkerInfo );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDebugMarkerEndEXT : {
		auto const*  obj = iter.Cast< packet_vkCmdDebugMarkerEndEXT *>();
		result << indent << "app.vkCmdDebugMarkerEndEXT( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDebugMarkerInsertEXT : {
		auto const*  obj = iter.Cast< packet_vkCmdDebugMarkerInsertEXT *>();
		if ( obj->pMarkerInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pMarkerInfo), nameSer, remapper, indent );
		}
		result << indent << "app.vkCmdDebugMarkerInsertEXT( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
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
		auto const*  obj = iter.Cast< packet_vkQueueSubmit *>();
		if ( obj->pSubmits ) {
			CHECK( obj->submitCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pSubmits, "submits"s, "submitInfo"s, "info"s );
			before << indent << "VkSubmitInfo  " << arr_name << "[" << IntToString(obj->submitCount) << "] = {};\n";
			for (uint i = 0; i < obj->submitCount; ++i) {
				Serialize2_VkSubmitInfo( obj->pSubmits + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkQueueSubmit( \n";
		result << indent << "		/*queue*/ " << "app.GetResource(QueueID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT, obj->queue ) << "))";
		result << ",\n";
		result << indent << "		/*submitCount*/ " << IntToString(obj->submitCount);
		result << ",\n";
		result << indent << "		/*pSubmits*/ " << nameSer.Get( &obj->pSubmits );
		result << ",\n";
		result << indent << "		/*fence*/ " << "app.GetResource(FenceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT, obj->fence ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkQueueWaitIdle : {
		auto const*  obj = iter.Cast< packet_vkQueueWaitIdle *>();
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkQueueWaitIdle( \n";
		result << indent << "		/*queue*/ " << "app.GetResource(QueueID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT, obj->queue ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDeviceWaitIdle : {
		auto const*  obj = iter.Cast< packet_vkDeviceWaitIdle *>();
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkDeviceWaitIdle( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkAllocateMemory : {
		auto const*  obj = iter.Cast< packet_vkAllocateMemory *>();
		if ( obj->pAllocateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pAllocateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkAllocateMemory( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pAllocateInfo*/ " << nameSer.GetPtr( obj->pAllocateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pMemory*/ " << "&app.EditResource(DeviceMemoryID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, *obj->pMemory ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkFreeMemory : {
		auto const*  obj = iter.Cast< packet_vkFreeMemory *>();
		result << indent << "app.vkFreeMemory( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*memory*/ " << "app.GetResource(DeviceMemoryID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, obj->memory ) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkMapMemory : break;
	case VKTRACE_TPI_VK_vkUnmapMemory : break;
	case VKTRACE_TPI_VK_vkFlushMappedMemoryRanges : {
		auto const*  obj = iter.Cast< packet_vkFlushMappedMemoryRanges *>();
		if ( obj->pMemoryRanges ) {
			CHECK( obj->memoryRangeCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pMemoryRanges, "memoryRanges"s, "mappedMemoryRange"s );
			before << indent << "VkMappedMemoryRange  " << arr_name << "[" << IntToString(obj->memoryRangeCount) << "] = {};\n";
			for (uint i = 0; i < obj->memoryRangeCount; ++i) {
				Serialize2_VkMappedMemoryRange( obj->pMemoryRanges + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkFlushMappedMemoryRanges( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*memoryRangeCount*/ " << IntToString(obj->memoryRangeCount);
		result << ",\n";
		result << indent << "		/*pMemoryRanges*/ " << nameSer.Get( &obj->pMemoryRanges );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkInvalidateMappedMemoryRanges : {
		auto const*  obj = iter.Cast< packet_vkInvalidateMappedMemoryRanges *>();
		if ( obj->pMemoryRanges ) {
			CHECK( obj->memoryRangeCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pMemoryRanges, "memoryRanges"s, "mappedMemoryRange"s );
			before << indent << "VkMappedMemoryRange  " << arr_name << "[" << IntToString(obj->memoryRangeCount) << "] = {};\n";
			for (uint i = 0; i < obj->memoryRangeCount; ++i) {
				Serialize2_VkMappedMemoryRange( obj->pMemoryRanges + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkInvalidateMappedMemoryRanges( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*memoryRangeCount*/ " << IntToString(obj->memoryRangeCount);
		result << ",\n";
		result << indent << "		/*pMemoryRanges*/ " << nameSer.Get( &obj->pMemoryRanges );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetDeviceMemoryCommitment : break;
	case VKTRACE_TPI_VK_vkBindBufferMemory : {
		auto const*  obj = iter.Cast< packet_vkBindBufferMemory *>();
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkBindBufferMemory( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*buffer*/ " << "app.GetResource(BufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, obj->buffer ) << "))";
		result << ",\n";
		result << indent << "		/*memory*/ " << "app.GetResource(DeviceMemoryID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, obj->memory ) << "))";
		result << ",\n";
		result << indent << "		/*memoryOffset*/ " << IntToString(obj->memoryOffset);
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkBindImageMemory : {
		auto const*  obj = iter.Cast< packet_vkBindImageMemory *>();
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkBindImageMemory( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*image*/ " << "app.GetResource(ImageID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, obj->image ) << "))";
		result << ",\n";
		result << indent << "		/*memory*/ " << "app.GetResource(DeviceMemoryID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, obj->memory ) << "))";
		result << ",\n";
		result << indent << "		/*memoryOffset*/ " << IntToString(obj->memoryOffset);
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetBufferMemoryRequirements : break;
	case VKTRACE_TPI_VK_vkGetImageMemoryRequirements : break;
	case VKTRACE_TPI_VK_vkGetImageSparseMemoryRequirements : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSparseImageFormatProperties : break;
	case VKTRACE_TPI_VK_vkQueueBindSparse : {
		auto const*  obj = iter.Cast< packet_vkQueueBindSparse *>();
		if ( obj->pBindInfo ) {
			CHECK( obj->bindInfoCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pBindInfo, "bindInfo"s, "bindSparseInfo"s, "info"s );
			before << indent << "VkBindSparseInfo  " << arr_name << "[" << IntToString(obj->bindInfoCount) << "] = {};\n";
			for (uint i = 0; i < obj->bindInfoCount; ++i) {
				Serialize2_VkBindSparseInfo( obj->pBindInfo + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkQueueBindSparse( \n";
		result << indent << "		/*queue*/ " << "app.GetResource(QueueID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT, obj->queue ) << "))";
		result << ",\n";
		result << indent << "		/*bindInfoCount*/ " << IntToString(obj->bindInfoCount);
		result << ",\n";
		result << indent << "		/*pBindInfo*/ " << nameSer.Get( &obj->pBindInfo );
		result << ",\n";
		result << indent << "		/*fence*/ " << "app.GetResource(FenceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT, obj->fence ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateFence : {
		auto const*  obj = iter.Cast< packet_vkCreateFence *>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateFence( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pFence*/ " << "&app.EditResource(FenceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT, *obj->pFence ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyFence : {
		auto const*  obj = iter.Cast< packet_vkDestroyFence *>();
		result << indent << "app.vkDestroyFence( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*fence*/ " << "app.GetResource(FenceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT, obj->fence ) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkResetFences : {
		auto const*  obj = iter.Cast< packet_vkResetFences *>();
		if ( obj->pFences ) {
			CHECK( obj->fenceCount > 0 );
			before << indent << "const VkFence  " << nameSer.MakeUnique( &obj->pFences, "fences"s, "fence"s ) << "[] = {";
			for (uint i = 0; i < obj->fenceCount; ++i) {
				before << (i ? "," : "") << (i%4 == 0 ? "\n\t"s << indent : " ") << "app.GetResource(FenceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT, obj->pFences[i] ) << "))";
			}
			before << "\n" << indent << "};\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pFences ) << ") == " << IntToString(obj->fenceCount) << " );\n\n";
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkResetFences( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*fenceCount*/ " << IntToString(obj->fenceCount);
		result << ",\n";
		result << indent << "		/*pFences*/ " << nameSer.Get( &obj->pFences );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetFenceStatus : break;
	case VKTRACE_TPI_VK_vkWaitForFences : {
		auto const*  obj = iter.Cast< packet_vkWaitForFences *>();
		if ( obj->pFences ) {
			CHECK( obj->fenceCount > 0 );
			before << indent << "const VkFence  " << nameSer.MakeUnique( &obj->pFences, "fences"s, "fence"s ) << "[] = {";
			for (uint i = 0; i < obj->fenceCount; ++i) {
				before << (i ? "," : "") << (i%4 == 0 ? "\n\t"s << indent : " ") << "app.GetResource(FenceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT, obj->pFences[i] ) << "))";
			}
			before << "\n" << indent << "};\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pFences ) << ") == " << IntToString(obj->fenceCount) << " );\n\n";
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkWaitForFences( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*fenceCount*/ " << IntToString(obj->fenceCount);
		result << ",\n";
		result << indent << "		/*pFences*/ " << nameSer.Get( &obj->pFences );
		result << ",\n";
		result << indent << "		/*waitAll*/ " << BoolToString(obj->waitAll);
		result << ",\n";
		result << indent << "		/*timeout*/ " << IntToString(obj->timeout);
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateSemaphore : {
		auto const*  obj = iter.Cast< packet_vkCreateSemaphore *>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateSemaphore( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pSemaphore*/ " << "&app.EditResource(SemaphoreID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT, *obj->pSemaphore ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroySemaphore : {
		auto const*  obj = iter.Cast< packet_vkDestroySemaphore *>();
		result << indent << "app.vkDestroySemaphore( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*semaphore*/ " << "app.GetResource(SemaphoreID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT, obj->semaphore ) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateEvent : {
		auto const*  obj = iter.Cast< packet_vkCreateEvent *>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateEvent( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pEvent*/ " << "&app.EditResource(EventID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_EVENT_EXT, *obj->pEvent ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyEvent : {
		auto const*  obj = iter.Cast< packet_vkDestroyEvent *>();
		result << indent << "app.vkDestroyEvent( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*event*/ " << "app.GetResource(EventID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_EVENT_EXT, obj->event ) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetEventStatus : break;
	case VKTRACE_TPI_VK_vkSetEvent : {
		auto const*  obj = iter.Cast< packet_vkSetEvent *>();
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkSetEvent( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*event*/ " << "app.GetResource(EventID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_EVENT_EXT, obj->event ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkResetEvent : {
		auto const*  obj = iter.Cast< packet_vkResetEvent *>();
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkResetEvent( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*event*/ " << "app.GetResource(EventID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_EVENT_EXT, obj->event ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateQueryPool : {
		auto const*  obj = iter.Cast< packet_vkCreateQueryPool *>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateQueryPool( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pQueryPool*/ " << "&app.EditResource(QueryPoolID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_QUERY_POOL_EXT, *obj->pQueryPool ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyQueryPool : {
		auto const*  obj = iter.Cast< packet_vkDestroyQueryPool *>();
		result << indent << "app.vkDestroyQueryPool( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*queryPool*/ " << "app.GetResource(QueryPoolID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_QUERY_POOL_EXT, obj->queryPool ) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetQueryPoolResults : break;
	case VKTRACE_TPI_VK_vkCreateBuffer : {
		auto const*  obj = iter.Cast< packet_vkCreateBuffer *>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateBuffer( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pBuffer*/ " << "&app.EditResource(BufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, *obj->pBuffer ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyBuffer : {
		auto const*  obj = iter.Cast< packet_vkDestroyBuffer *>();
		result << indent << "app.vkDestroyBuffer( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*buffer*/ " << "app.GetResource(BufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, obj->buffer ) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateBufferView : {
		auto const*  obj = iter.Cast< packet_vkCreateBufferView *>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateBufferView( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pView*/ " << "&app.EditResource(BufferViewID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_VIEW_EXT, *obj->pView ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyBufferView : {
		auto const*  obj = iter.Cast< packet_vkDestroyBufferView *>();
		result << indent << "app.vkDestroyBufferView( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*bufferView*/ " << "app.GetResource(BufferViewID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_VIEW_EXT, obj->bufferView ) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateImage : {
		auto const*  obj = iter.Cast< packet_vkCreateImage *>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateImage( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pImage*/ " << "&app.EditResource(ImageID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, *obj->pImage ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyImage : {
		auto const*  obj = iter.Cast< packet_vkDestroyImage *>();
		result << indent << "app.vkDestroyImage( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*image*/ " << "app.GetResource(ImageID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, obj->image ) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetImageSubresourceLayout : break;
	case VKTRACE_TPI_VK_vkCreateImageView : {
		auto const*  obj = iter.Cast< packet_vkCreateImageView *>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateImageView( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pView*/ " << "&app.EditResource(ImageViewID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_VIEW_EXT, *obj->pView ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyImageView : {
		auto const*  obj = iter.Cast< packet_vkDestroyImageView *>();
		result << indent << "app.vkDestroyImageView( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*imageView*/ " << "app.GetResource(ImageViewID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_VIEW_EXT, obj->imageView ) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateShaderModule : break;
	case VKTRACE_TPI_VK_vkDestroyShaderModule : {
		auto const*  obj = iter.Cast< packet_vkDestroyShaderModule *>();
		result << indent << "app.vkDestroyShaderModule( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*shaderModule*/ " << "app.GetResource(ShaderModuleID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_SHADER_MODULE_EXT, obj->shaderModule ) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreatePipelineCache : {
		auto const*  obj = iter.Cast< packet_vkCreatePipelineCache *>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreatePipelineCache( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pPipelineCache*/ " << "&app.EditResource(PipelineCacheID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_CACHE_EXT, *obj->pPipelineCache ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyPipelineCache : break;
	case VKTRACE_TPI_VK_vkGetPipelineCacheData : break;
	case VKTRACE_TPI_VK_vkMergePipelineCaches : {
		auto const*  obj = iter.Cast< packet_vkMergePipelineCaches *>();
		if ( obj->pSrcCaches ) {
			CHECK( obj->srcCacheCount > 0 );
			before << indent << "const VkPipelineCache  " << nameSer.MakeUnique( &obj->pSrcCaches, "srcCaches"s, "pipelineCache"s ) << "[] = {";
			for (uint i = 0; i < obj->srcCacheCount; ++i) {
				before << (i ? "," : "") << (i%4 == 0 ? "\n\t"s << indent : " ") << "app.GetResource(PipelineCacheID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_CACHE_EXT, obj->pSrcCaches[i] ) << "))";
			}
			before << "\n" << indent << "};\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pSrcCaches ) << ") == " << IntToString(obj->srcCacheCount) << " );\n\n";
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkMergePipelineCaches( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*dstCache*/ " << "app.GetResource(PipelineCacheID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_CACHE_EXT, obj->dstCache ) << "))";
		result << ",\n";
		result << indent << "		/*srcCacheCount*/ " << IntToString(obj->srcCacheCount);
		result << ",\n";
		result << indent << "		/*pSrcCaches*/ " << nameSer.Get( &obj->pSrcCaches );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateGraphicsPipelines : {
		auto const*  obj = iter.Cast< packet_vkCreateGraphicsPipelines *>();
		if ( obj->pCreateInfos ) {
			CHECK( obj->createInfoCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pCreateInfos, "createInfos"s, "graphicsPipelineCreateInfo"s, "createInfo"s );
			before << indent << "VkGraphicsPipelineCreateInfo  " << arr_name << "[" << IntToString(obj->createInfoCount) << "] = {};\n";
			for (uint i = 0; i < obj->createInfoCount; ++i) {
				Serialize2_VkGraphicsPipelineCreateInfo( obj->pCreateInfos + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		before << "		VkPipeline " << nameSer.MakeUnique( &obj->pPipelines, "pipelines"s, "pipeline"s ) << "[" << IntToString(obj->createInfoCount) << "] = {};\n";
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateGraphicsPipelines( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pipelineCache*/ " << "app.GetResource(PipelineCacheID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_CACHE_EXT, obj->pipelineCache ) << "))";
		result << ",\n";
		result << indent << "		/*createInfoCount*/ " << IntToString(obj->createInfoCount);
		result << ",\n";
		result << indent << "		/*pCreateInfos*/ " << nameSer.Get( &obj->pCreateInfos );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pPipelines*/ " << nameSer.Get( &obj->pPipelines );
		result << " ));\n";
		for (uint i = 0; i < obj->createInfoCount; ++i) {
			result << indent << "app.EditResource(PipelineID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_EXT, obj->pPipelines[i] ) << ")) = " << nameSer.Get( &obj->pPipelines ) << "[" << IntToString(i) << "];\n";
		}
		break;
	}

	case VKTRACE_TPI_VK_vkCreateComputePipelines : {
		auto const*  obj = iter.Cast< packet_vkCreateComputePipelines *>();
		if ( obj->pCreateInfos ) {
			CHECK( obj->createInfoCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pCreateInfos, "createInfos"s, "computePipelineCreateInfo"s, "createInfo"s );
			before << indent << "VkComputePipelineCreateInfo  " << arr_name << "[" << IntToString(obj->createInfoCount) << "] = {};\n";
			for (uint i = 0; i < obj->createInfoCount; ++i) {
				Serialize2_VkComputePipelineCreateInfo( obj->pCreateInfos + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		before << "		VkPipeline " << nameSer.MakeUnique( &obj->pPipelines, "pipelines"s, "pipeline"s ) << "[" << IntToString(obj->createInfoCount) << "] = {};\n";
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateComputePipelines( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pipelineCache*/ " << "app.GetResource(PipelineCacheID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_CACHE_EXT, obj->pipelineCache ) << "))";
		result << ",\n";
		result << indent << "		/*createInfoCount*/ " << IntToString(obj->createInfoCount);
		result << ",\n";
		result << indent << "		/*pCreateInfos*/ " << nameSer.Get( &obj->pCreateInfos );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pPipelines*/ " << nameSer.Get( &obj->pPipelines );
		result << " ));\n";
		for (uint i = 0; i < obj->createInfoCount; ++i) {
			result << indent << "app.EditResource(PipelineID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_EXT, obj->pPipelines[i] ) << ")) = " << nameSer.Get( &obj->pPipelines ) << "[" << IntToString(i) << "];\n";
		}
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyPipeline : {
		auto const*  obj = iter.Cast< packet_vkDestroyPipeline *>();
		result << indent << "app.vkDestroyPipeline( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pipeline*/ " << "app.GetResource(PipelineID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_EXT, obj->pipeline ) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreatePipelineLayout : {
		auto const*  obj = iter.Cast< packet_vkCreatePipelineLayout *>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreatePipelineLayout( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pPipelineLayout*/ " << "&app.EditResource(PipelineLayoutID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_LAYOUT_EXT, *obj->pPipelineLayout ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyPipelineLayout : {
		auto const*  obj = iter.Cast< packet_vkDestroyPipelineLayout *>();
		result << indent << "app.vkDestroyPipelineLayout( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pipelineLayout*/ " << "app.GetResource(PipelineLayoutID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_LAYOUT_EXT, obj->pipelineLayout ) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateSampler : {
		auto const*  obj = iter.Cast< packet_vkCreateSampler *>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateSampler( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pSampler*/ " << "&app.EditResource(SamplerID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_EXT, *obj->pSampler ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroySampler : {
		auto const*  obj = iter.Cast< packet_vkDestroySampler *>();
		result << indent << "app.vkDestroySampler( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*sampler*/ " << "app.GetResource(SamplerID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_EXT, obj->sampler ) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateDescriptorSetLayout : {
		auto const*  obj = iter.Cast< packet_vkCreateDescriptorSetLayout *>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateDescriptorSetLayout( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pSetLayout*/ " << "&app.EditResource(DescriptorSetLayoutID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT_EXT, *obj->pSetLayout ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyDescriptorSetLayout : {
		auto const*  obj = iter.Cast< packet_vkDestroyDescriptorSetLayout *>();
		result << indent << "app.vkDestroyDescriptorSetLayout( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*descriptorSetLayout*/ " << "app.GetResource(DescriptorSetLayoutID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT_EXT, obj->descriptorSetLayout ) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateDescriptorPool : {
		auto const*  obj = iter.Cast< packet_vkCreateDescriptorPool *>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateDescriptorPool( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pDescriptorPool*/ " << "&app.EditResource(DescriptorPoolID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_POOL_EXT, *obj->pDescriptorPool ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyDescriptorPool : {
		auto const*  obj = iter.Cast< packet_vkDestroyDescriptorPool *>();
		result << indent << "app.vkDestroyDescriptorPool( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*descriptorPool*/ " << "app.GetResource(DescriptorPoolID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_POOL_EXT, obj->descriptorPool ) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkResetDescriptorPool : {
		auto const*  obj = iter.Cast< packet_vkResetDescriptorPool *>();
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkResetDescriptorPool( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*descriptorPool*/ " << "app.GetResource(DescriptorPoolID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_POOL_EXT, obj->descriptorPool ) << "))";
		result << ",\n";
		result << indent << "		/*flags*/ " << Serialize_VkDescriptorPoolResetFlags( obj->flags );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkAllocateDescriptorSets : {
		auto const*  obj = iter.Cast< packet_vkAllocateDescriptorSets *>();
		if ( obj->pAllocateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pAllocateInfo), nameSer, remapper, indent );
		}
		before << "		VkDescriptorSet " << nameSer.MakeUnique( &obj->pDescriptorSets, "descriptorSets"s, "descriptorSet"s ) << "[" << IntToString(obj->pAllocateInfo->descriptorSetCount) << "] = {};\n";
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkAllocateDescriptorSets( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pAllocateInfo*/ " << nameSer.GetPtr( obj->pAllocateInfo );
		result << ",\n";
		result << indent << "		/*pDescriptorSets*/ " << nameSer.Get( &obj->pDescriptorSets );
		result << " ));\n";
		for (uint i = 0; i < obj->pAllocateInfo->descriptorSetCount; ++i) {
			result << indent << "app.EditResource(DescriptorSetID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_EXT, obj->pDescriptorSets[i] ) << ")) = " << nameSer.Get( &obj->pDescriptorSets ) << "[" << IntToString(i) << "];\n";
		}
		break;
	}

	case VKTRACE_TPI_VK_vkFreeDescriptorSets : {
		auto const*  obj = iter.Cast< packet_vkFreeDescriptorSets *>();
		if ( obj->pDescriptorSets ) {
			CHECK( obj->descriptorSetCount > 0 );
			before << indent << "const VkDescriptorSet  " << nameSer.MakeUnique( &obj->pDescriptorSets, "descriptorSets"s, "descriptorSet"s ) << "[] = {";
			for (uint i = 0; i < obj->descriptorSetCount; ++i) {
				before << (i ? "," : "") << (i%4 == 0 ? "\n\t"s << indent : " ") << "app.GetResource(DescriptorSetID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_EXT, obj->pDescriptorSets[i] ) << "))";
			}
			before << "\n" << indent << "};\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pDescriptorSets ) << ") == " << IntToString(obj->descriptorSetCount) << " );\n\n";
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkFreeDescriptorSets( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*descriptorPool*/ " << "app.GetResource(DescriptorPoolID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_POOL_EXT, obj->descriptorPool ) << "))";
		result << ",\n";
		result << indent << "		/*descriptorSetCount*/ " << IntToString(obj->descriptorSetCount);
		result << ",\n";
		result << indent << "		/*pDescriptorSets*/ " << nameSer.Get( &obj->pDescriptorSets );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkUpdateDescriptorSets : {
		auto const*  obj = iter.Cast< packet_vkUpdateDescriptorSets *>();
		if ( obj->pDescriptorWrites ) {
			CHECK( obj->descriptorWriteCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pDescriptorWrites, "descriptorWrites"s, "writeDescriptorSet"s );
			before << indent << "VkWriteDescriptorSet  " << arr_name << "[" << IntToString(obj->descriptorWriteCount) << "] = {};\n";
			for (uint i = 0; i < obj->descriptorWriteCount; ++i) {
				Serialize2_VkWriteDescriptorSet( obj->pDescriptorWrites + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		if ( obj->pDescriptorCopies ) {
			CHECK( obj->descriptorCopyCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pDescriptorCopies, "descriptorCopies"s, "copyDescriptorSet"s );
			before << indent << "VkCopyDescriptorSet  " << arr_name << "[" << IntToString(obj->descriptorCopyCount) << "] = {};\n";
			for (uint i = 0; i < obj->descriptorCopyCount; ++i) {
				Serialize2_VkCopyDescriptorSet( obj->pDescriptorCopies + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkUpdateDescriptorSets( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*descriptorWriteCount*/ " << IntToString(obj->descriptorWriteCount);
		result << ",\n";
		result << indent << "		/*pDescriptorWrites*/ " << nameSer.Get( &obj->pDescriptorWrites );
		result << ",\n";
		result << indent << "		/*descriptorCopyCount*/ " << IntToString(obj->descriptorCopyCount);
		result << ",\n";
		result << indent << "		/*pDescriptorCopies*/ " << nameSer.Get( &obj->pDescriptorCopies );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateFramebuffer : {
		auto const*  obj = iter.Cast< packet_vkCreateFramebuffer *>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateFramebuffer( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pFramebuffer*/ " << "&app.EditResource(FramebufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_FRAMEBUFFER_EXT, *obj->pFramebuffer ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyFramebuffer : {
		auto const*  obj = iter.Cast< packet_vkDestroyFramebuffer *>();
		result << indent << "app.vkDestroyFramebuffer( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*framebuffer*/ " << "app.GetResource(FramebufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_FRAMEBUFFER_EXT, obj->framebuffer ) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateRenderPass : {
		auto const*  obj = iter.Cast< packet_vkCreateRenderPass *>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateRenderPass( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pRenderPass*/ " << "&app.EditResource(RenderPassID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_RENDER_PASS_EXT, *obj->pRenderPass ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyRenderPass : {
		auto const*  obj = iter.Cast< packet_vkDestroyRenderPass *>();
		result << indent << "app.vkDestroyRenderPass( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*renderPass*/ " << "app.GetResource(RenderPassID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_RENDER_PASS_EXT, obj->renderPass ) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetRenderAreaGranularity : break;
	case VKTRACE_TPI_VK_vkCreateCommandPool : {
		auto const*  obj = iter.Cast< packet_vkCreateCommandPool *>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateCommandPool( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pCommandPool*/ " << "&app.EditResource(CommandPoolID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_POOL_EXT, *obj->pCommandPool ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyCommandPool : {
		auto const*  obj = iter.Cast< packet_vkDestroyCommandPool *>();
		result << indent << "app.vkDestroyCommandPool( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*commandPool*/ " << "app.GetResource(CommandPoolID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_POOL_EXT, obj->commandPool ) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkResetCommandPool : {
		auto const*  obj = iter.Cast< packet_vkResetCommandPool *>();
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkResetCommandPool( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*commandPool*/ " << "app.GetResource(CommandPoolID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_POOL_EXT, obj->commandPool ) << "))";
		result << ",\n";
		result << indent << "		/*flags*/ " << Serialize_VkCommandPoolResetFlags( obj->flags );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkAllocateCommandBuffers : {
		auto const*  obj = iter.Cast< packet_vkAllocateCommandBuffers *>();
		if ( obj->pAllocateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pAllocateInfo), nameSer, remapper, indent );
		}
		before << "		VkCommandBuffer " << nameSer.MakeUnique( &obj->pCommandBuffers, "commandBuffers"s, "commandBuffer"s ) << "[" << IntToString(obj->pAllocateInfo->commandBufferCount) << "] = {};\n";
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkAllocateCommandBuffers( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pAllocateInfo*/ " << nameSer.GetPtr( obj->pAllocateInfo );
		result << ",\n";
		result << indent << "		/*pCommandBuffers*/ " << nameSer.Get( &obj->pCommandBuffers );
		result << " ));\n";
		for (uint i = 0; i < obj->pAllocateInfo->commandBufferCount; ++i) {
			result << indent << "app.EditResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->pCommandBuffers[i] ) << ")) = " << nameSer.Get( &obj->pCommandBuffers ) << "[" << IntToString(i) << "];\n";
		}
		break;
	}

	case VKTRACE_TPI_VK_vkFreeCommandBuffers : {
		auto const*  obj = iter.Cast< packet_vkFreeCommandBuffers *>();
		if ( obj->pCommandBuffers ) {
			CHECK( obj->commandBufferCount > 0 );
			before << indent << "const VkCommandBuffer  " << nameSer.MakeUnique( &obj->pCommandBuffers, "commandBuffers"s, "commandBuffer"s ) << "[] = {";
			for (uint i = 0; i < obj->commandBufferCount; ++i) {
				before << (i ? "," : "") << (i%4 == 0 ? "\n\t"s << indent : " ") << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->pCommandBuffers[i] ) << "))";
			}
			before << "\n" << indent << "};\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pCommandBuffers ) << ") == " << IntToString(obj->commandBufferCount) << " );\n\n";
		}
		result << indent << "app.vkFreeCommandBuffers( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*commandPool*/ " << "app.GetResource(CommandPoolID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_POOL_EXT, obj->commandPool ) << "))";
		result << ",\n";
		result << indent << "		/*commandBufferCount*/ " << IntToString(obj->commandBufferCount);
		result << ",\n";
		result << indent << "		/*pCommandBuffers*/ " << nameSer.Get( &obj->pCommandBuffers );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkBeginCommandBuffer : {
		auto const*  obj = iter.Cast< packet_vkBeginCommandBuffer *>();
		if ( obj->pBeginInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pBeginInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkBeginCommandBuffer( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*pBeginInfo*/ " << nameSer.GetPtr( obj->pBeginInfo );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkEndCommandBuffer : {
		auto const*  obj = iter.Cast< packet_vkEndCommandBuffer *>();
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkEndCommandBuffer( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkResetCommandBuffer : {
		auto const*  obj = iter.Cast< packet_vkResetCommandBuffer *>();
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkResetCommandBuffer( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*flags*/ " << Serialize_VkCommandBufferResetFlags( obj->flags );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdBindPipeline : {
		auto const*  obj = iter.Cast< packet_vkCmdBindPipeline *>();
		result << indent << "app.vkCmdBindPipeline( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*pipelineBindPoint*/ " << Serialize_VkPipelineBindPoint( obj->pipelineBindPoint );
		result << ",\n";
		result << indent << "		/*pipeline*/ " << "app.GetResource(PipelineID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_EXT, obj->pipeline ) << "))";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetViewport : {
		auto const*  obj = iter.Cast< packet_vkCmdSetViewport *>();
		if ( obj->pViewports ) {
			CHECK( obj->viewportCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pViewports, "viewports"s, "viewport"s );
			before << indent << "VkViewport  " << arr_name << "[" << IntToString(obj->viewportCount) << "] = {};\n";
			for (uint i = 0; i < obj->viewportCount; ++i) {
				Serialize2_VkViewport( obj->pViewports + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdSetViewport( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*firstViewport*/ " << IntToString(obj->firstViewport);
		result << ",\n";
		result << indent << "		/*viewportCount*/ " << IntToString(obj->viewportCount);
		result << ",\n";
		result << indent << "		/*pViewports*/ " << nameSer.Get( &obj->pViewports );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetScissor : {
		auto const*  obj = iter.Cast< packet_vkCmdSetScissor *>();
		if ( obj->pScissors ) {
			CHECK( obj->scissorCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pScissors, "scissors"s, "rect2D"s );
			before << indent << "VkRect2D  " << arr_name << "[" << IntToString(obj->scissorCount) << "] = {};\n";
			for (uint i = 0; i < obj->scissorCount; ++i) {
				Serialize2_VkRect2D( obj->pScissors + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdSetScissor( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*firstScissor*/ " << IntToString(obj->firstScissor);
		result << ",\n";
		result << indent << "		/*scissorCount*/ " << IntToString(obj->scissorCount);
		result << ",\n";
		result << indent << "		/*pScissors*/ " << nameSer.Get( &obj->pScissors );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetLineWidth : {
		auto const*  obj = iter.Cast< packet_vkCmdSetLineWidth *>();
		result << indent << "app.vkCmdSetLineWidth( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*lineWidth*/ " << FloatToString(obj->lineWidth);
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetDepthBias : {
		auto const*  obj = iter.Cast< packet_vkCmdSetDepthBias *>();
		result << indent << "app.vkCmdSetDepthBias( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*depthBiasConstantFactor*/ " << FloatToString(obj->depthBiasConstantFactor);
		result << ",\n";
		result << indent << "		/*depthBiasClamp*/ " << FloatToString(obj->depthBiasClamp);
		result << ",\n";
		result << indent << "		/*depthBiasSlopeFactor*/ " << FloatToString(obj->depthBiasSlopeFactor);
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetBlendConstants : {
		auto const*  obj = iter.Cast< packet_vkCmdSetBlendConstants *>();
		result << indent << "app.vkCmdSetBlendConstants( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*blendConstants*/ " << "StaticArray<float, " << IntToString(std::size(obj->blendConstants)) << ">{ ";
		for (uint i = 0; i < std::size(obj->blendConstants); ++i) {
			result << (i ? ", " : "") << FloatToString(obj->blendConstants[i]);
		}
		result << " }";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetDepthBounds : {
		auto const*  obj = iter.Cast< packet_vkCmdSetDepthBounds *>();
		result << indent << "app.vkCmdSetDepthBounds( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*minDepthBounds*/ " << FloatToString(obj->minDepthBounds);
		result << ",\n";
		result << indent << "		/*maxDepthBounds*/ " << FloatToString(obj->maxDepthBounds);
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetStencilCompareMask : {
		auto const*  obj = iter.Cast< packet_vkCmdSetStencilCompareMask *>();
		result << indent << "app.vkCmdSetStencilCompareMask( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*faceMask*/ " << Serialize_VkStencilFaceFlags( obj->faceMask );
		result << ",\n";
		result << indent << "		/*compareMask*/ " << IntToString(obj->compareMask);
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetStencilWriteMask : {
		auto const*  obj = iter.Cast< packet_vkCmdSetStencilWriteMask *>();
		result << indent << "app.vkCmdSetStencilWriteMask( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*faceMask*/ " << Serialize_VkStencilFaceFlags( obj->faceMask );
		result << ",\n";
		result << indent << "		/*writeMask*/ " << IntToString(obj->writeMask);
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetStencilReference : {
		auto const*  obj = iter.Cast< packet_vkCmdSetStencilReference *>();
		result << indent << "app.vkCmdSetStencilReference( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*faceMask*/ " << Serialize_VkStencilFaceFlags( obj->faceMask );
		result << ",\n";
		result << indent << "		/*reference*/ " << IntToString(obj->reference);
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdBindDescriptorSets : {
		auto const*  obj = iter.Cast< packet_vkCmdBindDescriptorSets *>();
		if ( obj->pDescriptorSets ) {
			CHECK( obj->descriptorSetCount > 0 );
			before << indent << "const VkDescriptorSet  " << nameSer.MakeUnique( &obj->pDescriptorSets, "descriptorSets"s, "descriptorSet"s ) << "[] = {";
			for (uint i = 0; i < obj->descriptorSetCount; ++i) {
				before << (i ? "," : "") << (i%4 == 0 ? "\n\t"s << indent : " ") << "app.GetResource(DescriptorSetID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_EXT, obj->pDescriptorSets[i] ) << "))";
			}
			before << "\n" << indent << "};\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pDescriptorSets ) << ") == " << IntToString(obj->descriptorSetCount) << " );\n\n";
		}
		if ( obj->pDynamicOffsets ) {
			CHECK( obj->dynamicOffsetCount > 0 );
			before << indent << "const uint32_t  " << nameSer.MakeUnique( &obj->pDynamicOffsets, "dynamicOffsets"s ) << "[] = { ";
			for (uint i = 0; i < obj->dynamicOffsetCount; ++i) {
				before << (i ? ", " : "") << (i%16 == 0 ? "\n\t"s << indent : " ") << IntToString(obj->pDynamicOffsets[i]);
			}
			before << indent << " };\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pDynamicOffsets ) << ") == " << IntToString(obj->dynamicOffsetCount) << " );\n\n";
		}
		result << indent << "app.vkCmdBindDescriptorSets( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*pipelineBindPoint*/ " << Serialize_VkPipelineBindPoint( obj->pipelineBindPoint );
		result << ",\n";
		result << indent << "		/*layout*/ " << "app.GetResource(PipelineLayoutID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_LAYOUT_EXT, obj->layout ) << "))";
		result << ",\n";
		result << indent << "		/*firstSet*/ " << IntToString(obj->firstSet);
		result << ",\n";
		result << indent << "		/*descriptorSetCount*/ " << IntToString(obj->descriptorSetCount);
		result << ",\n";
		result << indent << "		/*pDescriptorSets*/ " << nameSer.Get( &obj->pDescriptorSets );
		result << ",\n";
		result << indent << "		/*dynamicOffsetCount*/ " << IntToString(obj->dynamicOffsetCount);
		result << ",\n";
		result << indent << "		/*pDynamicOffsets*/ " << nameSer.Get( &obj->pDynamicOffsets );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdBindIndexBuffer : {
		auto const*  obj = iter.Cast< packet_vkCmdBindIndexBuffer *>();
		result << indent << "app.vkCmdBindIndexBuffer( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*buffer*/ " << "app.GetResource(BufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, obj->buffer ) << "))";
		result << ",\n";
		result << indent << "		/*offset*/ " << IntToString(obj->offset);
		result << ",\n";
		result << indent << "		/*indexType*/ " << Serialize_VkIndexType( obj->indexType );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdBindVertexBuffers : {
		auto const*  obj = iter.Cast< packet_vkCmdBindVertexBuffers *>();
		if ( obj->pBuffers ) {
			CHECK( obj->bindingCount > 0 );
			before << indent << "const VkBuffer  " << nameSer.MakeUnique( &obj->pBuffers, "buffers"s, "buffer"s ) << "[] = {";
			for (uint i = 0; i < obj->bindingCount; ++i) {
				before << (i ? "," : "") << (i%4 == 0 ? "\n\t"s << indent : " ") << "app.GetResource(BufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, obj->pBuffers[i] ) << "))";
			}
			before << "\n" << indent << "};\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pBuffers ) << ") == " << IntToString(obj->bindingCount) << " );\n\n";
		}
		if ( obj->pOffsets ) {
			CHECK( obj->bindingCount > 0 );
			before << indent << "const VkDeviceSize  " << nameSer.MakeUnique( &obj->pOffsets, "offsets"s ) << "[] = { ";
			for (uint i = 0; i < obj->bindingCount; ++i) {
				before << (i ? ", " : "") << (i%16 == 0 ? "\n\t"s << indent : " ") << IntToString(obj->pOffsets[i]);
			}
			before << indent << " };\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pOffsets ) << ") == " << IntToString(obj->bindingCount) << " );\n\n";
		}
		result << indent << "app.vkCmdBindVertexBuffers( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*firstBinding*/ " << IntToString(obj->firstBinding);
		result << ",\n";
		result << indent << "		/*bindingCount*/ " << IntToString(obj->bindingCount);
		result << ",\n";
		result << indent << "		/*pBuffers*/ " << nameSer.Get( &obj->pBuffers );
		result << ",\n";
		result << indent << "		/*pOffsets*/ " << nameSer.Get( &obj->pOffsets );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDraw : {
		auto const*  obj = iter.Cast< packet_vkCmdDraw *>();
		result << indent << "app.vkCmdDraw( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*vertexCount*/ " << IntToString(obj->vertexCount);
		result << ",\n";
		result << indent << "		/*instanceCount*/ " << IntToString(obj->instanceCount);
		result << ",\n";
		result << indent << "		/*firstVertex*/ " << IntToString(obj->firstVertex);
		result << ",\n";
		result << indent << "		/*firstInstance*/ " << IntToString(obj->firstInstance);
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDrawIndexed : {
		auto const*  obj = iter.Cast< packet_vkCmdDrawIndexed *>();
		result << indent << "app.vkCmdDrawIndexed( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*indexCount*/ " << IntToString(obj->indexCount);
		result << ",\n";
		result << indent << "		/*instanceCount*/ " << IntToString(obj->instanceCount);
		result << ",\n";
		result << indent << "		/*firstIndex*/ " << IntToString(obj->firstIndex);
		result << ",\n";
		result << indent << "		/*vertexOffset*/ " << IntToString(obj->vertexOffset);
		result << ",\n";
		result << indent << "		/*firstInstance*/ " << IntToString(obj->firstInstance);
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDrawIndirect : {
		auto const*  obj = iter.Cast< packet_vkCmdDrawIndirect *>();
		result << indent << "app.vkCmdDrawIndirect( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*buffer*/ " << "app.GetResource(BufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, obj->buffer ) << "))";
		result << ",\n";
		result << indent << "		/*offset*/ " << IntToString(obj->offset);
		result << ",\n";
		result << indent << "		/*drawCount*/ " << IntToString(obj->drawCount);
		result << ",\n";
		result << indent << "		/*stride*/ " << IntToString(obj->stride);
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDrawIndexedIndirect : {
		auto const*  obj = iter.Cast< packet_vkCmdDrawIndexedIndirect *>();
		result << indent << "app.vkCmdDrawIndexedIndirect( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*buffer*/ " << "app.GetResource(BufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, obj->buffer ) << "))";
		result << ",\n";
		result << indent << "		/*offset*/ " << IntToString(obj->offset);
		result << ",\n";
		result << indent << "		/*drawCount*/ " << IntToString(obj->drawCount);
		result << ",\n";
		result << indent << "		/*stride*/ " << IntToString(obj->stride);
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDispatch : {
		auto const*  obj = iter.Cast< packet_vkCmdDispatch *>();
		result << indent << "app.vkCmdDispatch( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*groupCountX*/ " << IntToString(obj->groupCountX);
		result << ",\n";
		result << indent << "		/*groupCountY*/ " << IntToString(obj->groupCountY);
		result << ",\n";
		result << indent << "		/*groupCountZ*/ " << IntToString(obj->groupCountZ);
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDispatchIndirect : {
		auto const*  obj = iter.Cast< packet_vkCmdDispatchIndirect *>();
		result << indent << "app.vkCmdDispatchIndirect( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*buffer*/ " << "app.GetResource(BufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, obj->buffer ) << "))";
		result << ",\n";
		result << indent << "		/*offset*/ " << IntToString(obj->offset);
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdCopyBuffer : {
		auto const*  obj = iter.Cast< packet_vkCmdCopyBuffer *>();
		if ( obj->pRegions ) {
			CHECK( obj->regionCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pRegions, "regions"s, "bufferCopy"s );
			before << indent << "VkBufferCopy  " << arr_name << "[" << IntToString(obj->regionCount) << "] = {};\n";
			for (uint i = 0; i < obj->regionCount; ++i) {
				Serialize2_VkBufferCopy( obj->pRegions + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdCopyBuffer( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*srcBuffer*/ " << "app.GetResource(BufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, obj->srcBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*dstBuffer*/ " << "app.GetResource(BufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, obj->dstBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*regionCount*/ " << IntToString(obj->regionCount);
		result << ",\n";
		result << indent << "		/*pRegions*/ " << nameSer.Get( &obj->pRegions );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdCopyImage : {
		auto const*  obj = iter.Cast< packet_vkCmdCopyImage *>();
		if ( obj->pRegions ) {
			CHECK( obj->regionCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pRegions, "regions"s, "imageCopy"s );
			before << indent << "VkImageCopy  " << arr_name << "[" << IntToString(obj->regionCount) << "] = {};\n";
			for (uint i = 0; i < obj->regionCount; ++i) {
				Serialize2_VkImageCopy( obj->pRegions + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdCopyImage( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*srcImage*/ " << "app.GetResource(ImageID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, obj->srcImage ) << "))";
		result << ",\n";
		result << indent << "		/*srcImageLayout*/ " << Serialize_VkImageLayout( obj->srcImageLayout );
		result << ",\n";
		result << indent << "		/*dstImage*/ " << "app.GetResource(ImageID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, obj->dstImage ) << "))";
		result << ",\n";
		result << indent << "		/*dstImageLayout*/ " << Serialize_VkImageLayout( obj->dstImageLayout );
		result << ",\n";
		result << indent << "		/*regionCount*/ " << IntToString(obj->regionCount);
		result << ",\n";
		result << indent << "		/*pRegions*/ " << nameSer.Get( &obj->pRegions );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdBlitImage : {
		auto const*  obj = iter.Cast< packet_vkCmdBlitImage *>();
		if ( obj->pRegions ) {
			CHECK( obj->regionCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pRegions, "regions"s, "imageBlit"s );
			before << indent << "VkImageBlit  " << arr_name << "[" << IntToString(obj->regionCount) << "] = {};\n";
			for (uint i = 0; i < obj->regionCount; ++i) {
				Serialize2_VkImageBlit( obj->pRegions + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdBlitImage( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*srcImage*/ " << "app.GetResource(ImageID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, obj->srcImage ) << "))";
		result << ",\n";
		result << indent << "		/*srcImageLayout*/ " << Serialize_VkImageLayout( obj->srcImageLayout );
		result << ",\n";
		result << indent << "		/*dstImage*/ " << "app.GetResource(ImageID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, obj->dstImage ) << "))";
		result << ",\n";
		result << indent << "		/*dstImageLayout*/ " << Serialize_VkImageLayout( obj->dstImageLayout );
		result << ",\n";
		result << indent << "		/*regionCount*/ " << IntToString(obj->regionCount);
		result << ",\n";
		result << indent << "		/*pRegions*/ " << nameSer.Get( &obj->pRegions );
		result << ",\n";
		result << indent << "		/*filter*/ " << Serialize_VkFilter( obj->filter );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdCopyBufferToImage : {
		auto const*  obj = iter.Cast< packet_vkCmdCopyBufferToImage *>();
		if ( obj->pRegions ) {
			CHECK( obj->regionCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pRegions, "regions"s, "bufferImageCopy"s );
			before << indent << "VkBufferImageCopy  " << arr_name << "[" << IntToString(obj->regionCount) << "] = {};\n";
			for (uint i = 0; i < obj->regionCount; ++i) {
				Serialize2_VkBufferImageCopy( obj->pRegions + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdCopyBufferToImage( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*srcBuffer*/ " << "app.GetResource(BufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, obj->srcBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*dstImage*/ " << "app.GetResource(ImageID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, obj->dstImage ) << "))";
		result << ",\n";
		result << indent << "		/*dstImageLayout*/ " << Serialize_VkImageLayout( obj->dstImageLayout );
		result << ",\n";
		result << indent << "		/*regionCount*/ " << IntToString(obj->regionCount);
		result << ",\n";
		result << indent << "		/*pRegions*/ " << nameSer.Get( &obj->pRegions );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdCopyImageToBuffer : {
		auto const*  obj = iter.Cast< packet_vkCmdCopyImageToBuffer *>();
		if ( obj->pRegions ) {
			CHECK( obj->regionCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pRegions, "regions"s, "bufferImageCopy"s );
			before << indent << "VkBufferImageCopy  " << arr_name << "[" << IntToString(obj->regionCount) << "] = {};\n";
			for (uint i = 0; i < obj->regionCount; ++i) {
				Serialize2_VkBufferImageCopy( obj->pRegions + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdCopyImageToBuffer( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*srcImage*/ " << "app.GetResource(ImageID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, obj->srcImage ) << "))";
		result << ",\n";
		result << indent << "		/*srcImageLayout*/ " << Serialize_VkImageLayout( obj->srcImageLayout );
		result << ",\n";
		result << indent << "		/*dstBuffer*/ " << "app.GetResource(BufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, obj->dstBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*regionCount*/ " << IntToString(obj->regionCount);
		result << ",\n";
		result << indent << "		/*pRegions*/ " << nameSer.Get( &obj->pRegions );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdUpdateBuffer : {
		auto const*  obj = iter.Cast< packet_vkCmdUpdateBuffer *>();
		CHECK( (obj->dataSize > 0) and (obj->dataSize % 4 == 0) );
		before << indent << "const FIValue " << nameSer.MakeUnique( &obj->pData, "data"s ) << "[] = {";
		for (uint i = 0; i < obj->dataSize; ++i) {
			before << (i ? "," : "") << (i%8 == 0 ? "\n\t"s << indent : " ") << VoidToFIValueString( obj->pData, i*sizeof(FIValue) );
		}
		before << '\n' << indent << "};\n";
		before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pData ) << ") == " << IntToString(obj->dataSize) << " );\n\n";
		result << indent << "app.vkCmdUpdateBuffer( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*dstBuffer*/ " << "app.GetResource(BufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, obj->dstBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*dstOffset*/ " << IntToString(obj->dstOffset);
		result << ",\n";
		result << indent << "		/*dataSize*/ " << IntToString(obj->dataSize);
		result << ",\n";
		result << indent << "		/*pData*/ " << nameSer.Get( &obj->pData );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdFillBuffer : {
		auto const*  obj = iter.Cast< packet_vkCmdFillBuffer *>();
		result << indent << "app.vkCmdFillBuffer( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*dstBuffer*/ " << "app.GetResource(BufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, obj->dstBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*dstOffset*/ " << IntToString(obj->dstOffset);
		result << ",\n";
		result << indent << "		/*size*/ " << IntToString(obj->size);
		result << ",\n";
		result << indent << "		/*data*/ " << IntToString(obj->data);
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdClearColorImage : {
		auto const*  obj = iter.Cast< packet_vkCmdClearColorImage *>();
		if ( obj->pColor ) {
			before << Serialize_VkClearColorValue( obj->pColor, nameSer, remapper, indent );
		}
		if ( obj->pRanges ) {
			CHECK( obj->rangeCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pRanges, "ranges"s, "imageSubresourceRange"s );
			before << indent << "VkImageSubresourceRange  " << arr_name << "[" << IntToString(obj->rangeCount) << "] = {};\n";
			for (uint i = 0; i < obj->rangeCount; ++i) {
				Serialize2_VkImageSubresourceRange( obj->pRanges + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdClearColorImage( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*image*/ " << "app.GetResource(ImageID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, obj->image ) << "))";
		result << ",\n";
		result << indent << "		/*imageLayout*/ " << Serialize_VkImageLayout( obj->imageLayout );
		result << ",\n";
		result << indent << "		/*pColor*/ " << nameSer.GetPtr( obj->pColor );
		result << ",\n";
		result << indent << "		/*rangeCount*/ " << IntToString(obj->rangeCount);
		result << ",\n";
		result << indent << "		/*pRanges*/ " << nameSer.Get( &obj->pRanges );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdClearDepthStencilImage : {
		auto const*  obj = iter.Cast< packet_vkCmdClearDepthStencilImage *>();
		if ( obj->pDepthStencil ) {
			before << Serialize_VkClearDepthStencilValue( obj->pDepthStencil, nameSer, remapper, indent );
		}
		if ( obj->pRanges ) {
			CHECK( obj->rangeCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pRanges, "ranges"s, "imageSubresourceRange"s );
			before << indent << "VkImageSubresourceRange  " << arr_name << "[" << IntToString(obj->rangeCount) << "] = {};\n";
			for (uint i = 0; i < obj->rangeCount; ++i) {
				Serialize2_VkImageSubresourceRange( obj->pRanges + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdClearDepthStencilImage( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*image*/ " << "app.GetResource(ImageID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, obj->image ) << "))";
		result << ",\n";
		result << indent << "		/*imageLayout*/ " << Serialize_VkImageLayout( obj->imageLayout );
		result << ",\n";
		result << indent << "		/*pDepthStencil*/ " << nameSer.GetPtr( obj->pDepthStencil );
		result << ",\n";
		result << indent << "		/*rangeCount*/ " << IntToString(obj->rangeCount);
		result << ",\n";
		result << indent << "		/*pRanges*/ " << nameSer.Get( &obj->pRanges );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdClearAttachments : {
		auto const*  obj = iter.Cast< packet_vkCmdClearAttachments *>();
		if ( obj->pAttachments ) {
			CHECK( obj->attachmentCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pAttachments, "attachments"s, "clearAttachment"s );
			before << indent << "VkClearAttachment  " << arr_name << "[" << IntToString(obj->attachmentCount) << "] = {};\n";
			for (uint i = 0; i < obj->attachmentCount; ++i) {
				Serialize2_VkClearAttachment( obj->pAttachments + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		if ( obj->pRects ) {
			CHECK( obj->rectCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pRects, "rects"s, "clearRect"s );
			before << indent << "VkClearRect  " << arr_name << "[" << IntToString(obj->rectCount) << "] = {};\n";
			for (uint i = 0; i < obj->rectCount; ++i) {
				Serialize2_VkClearRect( obj->pRects + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdClearAttachments( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*attachmentCount*/ " << IntToString(obj->attachmentCount);
		result << ",\n";
		result << indent << "		/*pAttachments*/ " << nameSer.Get( &obj->pAttachments );
		result << ",\n";
		result << indent << "		/*rectCount*/ " << IntToString(obj->rectCount);
		result << ",\n";
		result << indent << "		/*pRects*/ " << nameSer.Get( &obj->pRects );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdResolveImage : {
		auto const*  obj = iter.Cast< packet_vkCmdResolveImage *>();
		if ( obj->pRegions ) {
			CHECK( obj->regionCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pRegions, "regions"s, "imageResolve"s );
			before << indent << "VkImageResolve  " << arr_name << "[" << IntToString(obj->regionCount) << "] = {};\n";
			for (uint i = 0; i < obj->regionCount; ++i) {
				Serialize2_VkImageResolve( obj->pRegions + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdResolveImage( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*srcImage*/ " << "app.GetResource(ImageID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, obj->srcImage ) << "))";
		result << ",\n";
		result << indent << "		/*srcImageLayout*/ " << Serialize_VkImageLayout( obj->srcImageLayout );
		result << ",\n";
		result << indent << "		/*dstImage*/ " << "app.GetResource(ImageID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, obj->dstImage ) << "))";
		result << ",\n";
		result << indent << "		/*dstImageLayout*/ " << Serialize_VkImageLayout( obj->dstImageLayout );
		result << ",\n";
		result << indent << "		/*regionCount*/ " << IntToString(obj->regionCount);
		result << ",\n";
		result << indent << "		/*pRegions*/ " << nameSer.Get( &obj->pRegions );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdSetEvent : {
		auto const*  obj = iter.Cast< packet_vkCmdSetEvent *>();
		result << indent << "app.vkCmdSetEvent( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*event*/ " << "app.GetResource(EventID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_EVENT_EXT, obj->event ) << "))";
		result << ",\n";
		result << indent << "		/*stageMask*/ " << Serialize_VkPipelineStageFlags( obj->stageMask );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdResetEvent : {
		auto const*  obj = iter.Cast< packet_vkCmdResetEvent *>();
		result << indent << "app.vkCmdResetEvent( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*event*/ " << "app.GetResource(EventID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_EVENT_EXT, obj->event ) << "))";
		result << ",\n";
		result << indent << "		/*stageMask*/ " << Serialize_VkPipelineStageFlags( obj->stageMask );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdWaitEvents : {
		auto const*  obj = iter.Cast< packet_vkCmdWaitEvents *>();
		if ( obj->pEvents ) {
			CHECK( obj->eventCount > 0 );
			before << indent << "const VkEvent  " << nameSer.MakeUnique( &obj->pEvents, "events"s, "event"s ) << "[] = {";
			for (uint i = 0; i < obj->eventCount; ++i) {
				before << (i ? "," : "") << (i%4 == 0 ? "\n\t"s << indent : " ") << "app.GetResource(EventID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_EVENT_EXT, obj->pEvents[i] ) << "))";
			}
			before << "\n" << indent << "};\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pEvents ) << ") == " << IntToString(obj->eventCount) << " );\n\n";
		}
		if ( obj->pMemoryBarriers ) {
			CHECK( obj->memoryBarrierCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pMemoryBarriers, "memoryBarriers"s, "memoryBarrier"s, "barrier"s );
			before << indent << "VkMemoryBarrier  " << arr_name << "[" << IntToString(obj->memoryBarrierCount) << "] = {};\n";
			for (uint i = 0; i < obj->memoryBarrierCount; ++i) {
				Serialize2_VkMemoryBarrier( obj->pMemoryBarriers + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		if ( obj->pBufferMemoryBarriers ) {
			CHECK( obj->bufferMemoryBarrierCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pBufferMemoryBarriers, "bufferMemoryBarriers"s, "bufferMemoryBarrier"s, "barrier"s );
			before << indent << "VkBufferMemoryBarrier  " << arr_name << "[" << IntToString(obj->bufferMemoryBarrierCount) << "] = {};\n";
			for (uint i = 0; i < obj->bufferMemoryBarrierCount; ++i) {
				Serialize2_VkBufferMemoryBarrier( obj->pBufferMemoryBarriers + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		if ( obj->pImageMemoryBarriers ) {
			CHECK( obj->imageMemoryBarrierCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pImageMemoryBarriers, "imageMemoryBarriers"s, "imageMemoryBarrier"s, "barrier"s );
			before << indent << "VkImageMemoryBarrier  " << arr_name << "[" << IntToString(obj->imageMemoryBarrierCount) << "] = {};\n";
			for (uint i = 0; i < obj->imageMemoryBarrierCount; ++i) {
				Serialize2_VkImageMemoryBarrier( obj->pImageMemoryBarriers + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdWaitEvents( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*eventCount*/ " << IntToString(obj->eventCount);
		result << ",\n";
		result << indent << "		/*pEvents*/ " << nameSer.Get( &obj->pEvents );
		result << ",\n";
		result << indent << "		/*srcStageMask*/ " << Serialize_VkPipelineStageFlags( obj->srcStageMask );
		result << ",\n";
		result << indent << "		/*dstStageMask*/ " << Serialize_VkPipelineStageFlags( obj->dstStageMask );
		result << ",\n";
		result << indent << "		/*memoryBarrierCount*/ " << IntToString(obj->memoryBarrierCount);
		result << ",\n";
		result << indent << "		/*pMemoryBarriers*/ " << nameSer.Get( &obj->pMemoryBarriers );
		result << ",\n";
		result << indent << "		/*bufferMemoryBarrierCount*/ " << IntToString(obj->bufferMemoryBarrierCount);
		result << ",\n";
		result << indent << "		/*pBufferMemoryBarriers*/ " << nameSer.Get( &obj->pBufferMemoryBarriers );
		result << ",\n";
		result << indent << "		/*imageMemoryBarrierCount*/ " << IntToString(obj->imageMemoryBarrierCount);
		result << ",\n";
		result << indent << "		/*pImageMemoryBarriers*/ " << nameSer.Get( &obj->pImageMemoryBarriers );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdPipelineBarrier : {
		auto const*  obj = iter.Cast< packet_vkCmdPipelineBarrier *>();
		if ( obj->pMemoryBarriers ) {
			CHECK( obj->memoryBarrierCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pMemoryBarriers, "memoryBarriers"s, "memoryBarrier"s, "barrier"s );
			before << indent << "VkMemoryBarrier  " << arr_name << "[" << IntToString(obj->memoryBarrierCount) << "] = {};\n";
			for (uint i = 0; i < obj->memoryBarrierCount; ++i) {
				Serialize2_VkMemoryBarrier( obj->pMemoryBarriers + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		if ( obj->pBufferMemoryBarriers ) {
			CHECK( obj->bufferMemoryBarrierCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pBufferMemoryBarriers, "bufferMemoryBarriers"s, "bufferMemoryBarrier"s, "barrier"s );
			before << indent << "VkBufferMemoryBarrier  " << arr_name << "[" << IntToString(obj->bufferMemoryBarrierCount) << "] = {};\n";
			for (uint i = 0; i < obj->bufferMemoryBarrierCount; ++i) {
				Serialize2_VkBufferMemoryBarrier( obj->pBufferMemoryBarriers + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		if ( obj->pImageMemoryBarriers ) {
			CHECK( obj->imageMemoryBarrierCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pImageMemoryBarriers, "imageMemoryBarriers"s, "imageMemoryBarrier"s, "barrier"s );
			before << indent << "VkImageMemoryBarrier  " << arr_name << "[" << IntToString(obj->imageMemoryBarrierCount) << "] = {};\n";
			for (uint i = 0; i < obj->imageMemoryBarrierCount; ++i) {
				Serialize2_VkImageMemoryBarrier( obj->pImageMemoryBarriers + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdPipelineBarrier( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*srcStageMask*/ " << Serialize_VkPipelineStageFlags( obj->srcStageMask );
		result << ",\n";
		result << indent << "		/*dstStageMask*/ " << Serialize_VkPipelineStageFlags( obj->dstStageMask );
		result << ",\n";
		result << indent << "		/*dependencyFlags*/ " << Serialize_VkDependencyFlags( obj->dependencyFlags );
		result << ",\n";
		result << indent << "		/*memoryBarrierCount*/ " << IntToString(obj->memoryBarrierCount);
		result << ",\n";
		result << indent << "		/*pMemoryBarriers*/ " << nameSer.Get( &obj->pMemoryBarriers );
		result << ",\n";
		result << indent << "		/*bufferMemoryBarrierCount*/ " << IntToString(obj->bufferMemoryBarrierCount);
		result << ",\n";
		result << indent << "		/*pBufferMemoryBarriers*/ " << nameSer.Get( &obj->pBufferMemoryBarriers );
		result << ",\n";
		result << indent << "		/*imageMemoryBarrierCount*/ " << IntToString(obj->imageMemoryBarrierCount);
		result << ",\n";
		result << indent << "		/*pImageMemoryBarriers*/ " << nameSer.Get( &obj->pImageMemoryBarriers );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdBeginQuery : {
		auto const*  obj = iter.Cast< packet_vkCmdBeginQuery *>();
		result << indent << "app.vkCmdBeginQuery( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*queryPool*/ " << "app.GetResource(QueryPoolID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_QUERY_POOL_EXT, obj->queryPool ) << "))";
		result << ",\n";
		result << indent << "		/*query*/ " << IntToString(obj->query);
		result << ",\n";
		result << indent << "		/*flags*/ " << Serialize_VkQueryControlFlags( obj->flags );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdEndQuery : {
		auto const*  obj = iter.Cast< packet_vkCmdEndQuery *>();
		result << indent << "app.vkCmdEndQuery( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*queryPool*/ " << "app.GetResource(QueryPoolID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_QUERY_POOL_EXT, obj->queryPool ) << "))";
		result << ",\n";
		result << indent << "		/*query*/ " << IntToString(obj->query);
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdResetQueryPool : {
		auto const*  obj = iter.Cast< packet_vkCmdResetQueryPool *>();
		result << indent << "app.vkCmdResetQueryPool( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*queryPool*/ " << "app.GetResource(QueryPoolID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_QUERY_POOL_EXT, obj->queryPool ) << "))";
		result << ",\n";
		result << indent << "		/*firstQuery*/ " << IntToString(obj->firstQuery);
		result << ",\n";
		result << indent << "		/*queryCount*/ " << IntToString(obj->queryCount);
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdWriteTimestamp : {
		auto const*  obj = iter.Cast< packet_vkCmdWriteTimestamp *>();
		result << indent << "app.vkCmdWriteTimestamp( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*pipelineStage*/ " << Serialize_VkPipelineStageFlagBits( obj->pipelineStage );
		result << ",\n";
		result << indent << "		/*queryPool*/ " << "app.GetResource(QueryPoolID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_QUERY_POOL_EXT, obj->queryPool ) << "))";
		result << ",\n";
		result << indent << "		/*query*/ " << IntToString(obj->query);
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdCopyQueryPoolResults : {
		auto const*  obj = iter.Cast< packet_vkCmdCopyQueryPoolResults *>();
		result << indent << "app.vkCmdCopyQueryPoolResults( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*queryPool*/ " << "app.GetResource(QueryPoolID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_QUERY_POOL_EXT, obj->queryPool ) << "))";
		result << ",\n";
		result << indent << "		/*firstQuery*/ " << IntToString(obj->firstQuery);
		result << ",\n";
		result << indent << "		/*queryCount*/ " << IntToString(obj->queryCount);
		result << ",\n";
		result << indent << "		/*dstBuffer*/ " << "app.GetResource(BufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, obj->dstBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*dstOffset*/ " << IntToString(obj->dstOffset);
		result << ",\n";
		result << indent << "		/*stride*/ " << IntToString(obj->stride);
		result << ",\n";
		result << indent << "		/*flags*/ " << Serialize_VkQueryResultFlags( obj->flags );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdPushConstants : {
		auto const*  obj = iter.Cast< packet_vkCmdPushConstants *>();
		CHECK( (obj->size > 0) and (obj->size % 4 == 0) );
		before << indent << "const FIValue " << nameSer.MakeUnique( &obj->pValues, "values"s ) << "[] = {";
		for (uint i = 0; i < obj->size; ++i) {
			before << (i ? "," : "") << (i%8 == 0 ? "\n\t"s << indent : " ") << VoidToFIValueString( obj->pValues, i*sizeof(FIValue) );
		}
		before << '\n' << indent << "};\n";
		before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pValues ) << ") == " << IntToString(obj->size) << " );\n\n";
		result << indent << "app.vkCmdPushConstants( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*layout*/ " << "app.GetResource(PipelineLayoutID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_LAYOUT_EXT, obj->layout ) << "))";
		result << ",\n";
		result << indent << "		/*stageFlags*/ " << Serialize_VkShaderStageFlags( obj->stageFlags );
		result << ",\n";
		result << indent << "		/*offset*/ " << IntToString(obj->offset);
		result << ",\n";
		result << indent << "		/*size*/ " << IntToString(obj->size);
		result << ",\n";
		result << indent << "		/*pValues*/ " << nameSer.Get( &obj->pValues );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdBeginRenderPass : {
		auto const*  obj = iter.Cast< packet_vkCmdBeginRenderPass *>();
		if ( obj->pRenderPassBegin ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pRenderPassBegin), nameSer, remapper, indent );
		}
		result << indent << "app.vkCmdBeginRenderPass( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*pRenderPassBegin*/ " << nameSer.GetPtr( obj->pRenderPassBegin );
		result << ",\n";
		result << indent << "		/*contents*/ " << Serialize_VkSubpassContents( obj->contents );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdNextSubpass : {
		auto const*  obj = iter.Cast< packet_vkCmdNextSubpass *>();
		result << indent << "app.vkCmdNextSubpass( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*contents*/ " << Serialize_VkSubpassContents( obj->contents );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdEndRenderPass : {
		auto const*  obj = iter.Cast< packet_vkCmdEndRenderPass *>();
		result << indent << "app.vkCmdEndRenderPass( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdExecuteCommands : {
		auto const*  obj = iter.Cast< packet_vkCmdExecuteCommands *>();
		if ( obj->pCommandBuffers ) {
			CHECK( obj->commandBufferCount > 0 );
			before << indent << "const VkCommandBuffer  " << nameSer.MakeUnique( &obj->pCommandBuffers, "commandBuffers"s, "commandBuffer"s ) << "[] = {";
			for (uint i = 0; i < obj->commandBufferCount; ++i) {
				before << (i ? "," : "") << (i%4 == 0 ? "\n\t"s << indent : " ") << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->pCommandBuffers[i] ) << "))";
			}
			before << "\n" << indent << "};\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pCommandBuffers ) << ") == " << IntToString(obj->commandBufferCount) << " );\n\n";
		}
		result << indent << "app.vkCmdExecuteCommands( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*commandBufferCount*/ " << IntToString(obj->commandBufferCount);
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
		auto const*  obj = iter.Cast< packet_vkCreateSwapchainKHR *>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateSwapchainKHR( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pSwapchain*/ " << "&app.EditResource(SwapchainKHRID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT, *obj->pSwapchain ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroySwapchainKHR : break;
	case VKTRACE_TPI_VK_vkGetSwapchainImagesKHR : break;
	case VKTRACE_TPI_VK_vkAcquireNextImageKHR : break;
	case VKTRACE_TPI_VK_vkQueuePresentKHR : break;
	case VKTRACE_TPI_VK_vkCreateSharedSwapchainsKHR : {
		auto const*  obj = iter.Cast< packet_vkCreateSharedSwapchainsKHR *>();
		if ( obj->pCreateInfos ) {
			CHECK( obj->swapchainCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pCreateInfos, "createInfos"s, "swapchainCreateInfo"s, "createInfo"s );
			before << indent << "VkSwapchainCreateInfoKHR  " << arr_name << "[" << IntToString(obj->swapchainCount) << "] = {};\n";
			for (uint i = 0; i < obj->swapchainCount; ++i) {
				Serialize2_VkSwapchainCreateInfoKHR( obj->pCreateInfos + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		before << "		VkSwapchainKHR " << nameSer.MakeUnique( &obj->pSwapchains, "swapchains"s, "swapchain"s ) << "[" << IntToString(obj->swapchainCount) << "] = {};\n";
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateSharedSwapchainsKHR( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*swapchainCount*/ " << IntToString(obj->swapchainCount);
		result << ",\n";
		result << indent << "		/*pCreateInfos*/ " << nameSer.Get( &obj->pCreateInfos );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pSwapchains*/ " << nameSer.Get( &obj->pSwapchains );
		result << " ));\n";
		for (uint i = 0; i < obj->swapchainCount; ++i) {
			result << indent << "app.EditResource(SwapchainKHRID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT, obj->pSwapchains[i] ) << ")) = " << nameSer.Get( &obj->pSwapchains ) << "[" << IntToString(i) << "];\n";
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
		auto const*  obj = iter.Cast< packet_vkCreateDescriptorUpdateTemplateKHR *>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateDescriptorUpdateTemplateKHR( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pDescriptorUpdateTemplate*/ " << "&app.EditResource(DescriptorUpdateTemplateID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_EXT, *obj->pDescriptorUpdateTemplate ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyDescriptorUpdateTemplateKHR : {
		auto const*  obj = iter.Cast< packet_vkDestroyDescriptorUpdateTemplateKHR *>();
		result << indent << "app.vkDestroyDescriptorUpdateTemplateKHR( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*descriptorUpdateTemplate*/ " << "app.GetResource(DescriptorUpdateTemplateID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_EXT, obj->descriptorUpdateTemplate ) << "))";
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
	case VKTRACE_TPI_VK_vkCreateDisplayModeKHR : break;
	case VKTRACE_TPI_VK_vkGetDisplayPlaneCapabilitiesKHR : break;
	case VKTRACE_TPI_VK_vkCreateDisplayPlaneSurfaceKHR : break;
	case VKTRACE_TPI_VK_vkTrimCommandPoolKHR : {
		auto const*  obj = iter.Cast< packet_vkTrimCommandPoolKHR *>();
		result << indent << "app.vkTrimCommandPoolKHR( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*commandPool*/ " << "app.GetResource(CommandPoolID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_POOL_EXT, obj->commandPool ) << "))";
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
		auto const*  obj = iter.Cast< packet_vkImportSemaphoreFdKHR *>();
		if ( obj->pImportSemaphoreFdInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pImportSemaphoreFdInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkImportSemaphoreFdKHR( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pImportSemaphoreFdInfo*/ " << nameSer.GetPtr( obj->pImportSemaphoreFdInfo );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetSemaphoreFdKHR : break;
	case VKTRACE_TPI_VK_vkCmdPushDescriptorSetKHR : {
		auto const*  obj = iter.Cast< packet_vkCmdPushDescriptorSetKHR *>();
		if ( obj->pDescriptorWrites ) {
			CHECK( obj->descriptorWriteCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pDescriptorWrites, "descriptorWrites"s, "writeDescriptorSet"s );
			before << indent << "VkWriteDescriptorSet  " << arr_name << "[" << IntToString(obj->descriptorWriteCount) << "] = {};\n";
			for (uint i = 0; i < obj->descriptorWriteCount; ++i) {
				Serialize2_VkWriteDescriptorSet( obj->pDescriptorWrites + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdPushDescriptorSetKHR( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*pipelineBindPoint*/ " << Serialize_VkPipelineBindPoint( obj->pipelineBindPoint );
		result << ",\n";
		result << indent << "		/*layout*/ " << "app.GetResource(PipelineLayoutID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_LAYOUT_EXT, obj->layout ) << "))";
		result << ",\n";
		result << indent << "		/*set*/ " << IntToString(obj->set);
		result << ",\n";
		result << indent << "		/*descriptorWriteCount*/ " << IntToString(obj->descriptorWriteCount);
		result << ",\n";
		result << indent << "		/*pDescriptorWrites*/ " << nameSer.Get( &obj->pDescriptorWrites );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetSwapchainStatusKHR : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceExternalFencePropertiesKHR : break;
	case VKTRACE_TPI_VK_vkGetDeviceGroupPeerMemoryFeaturesKHX : break;
	case VKTRACE_TPI_VK_vkBindBufferMemory2KHR : {
		auto const*  obj = iter.Cast< packet_vkBindBufferMemory2KHR *>();
		if ( obj->pBindInfos ) {
			CHECK( obj->bindInfoCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pBindInfos, "bindInfos"s, "bindBufferMemoryInfo"s, "info"s );
			before << indent << "VkBindBufferMemoryInfo  " << arr_name << "[" << IntToString(obj->bindInfoCount) << "] = {};\n";
			for (uint i = 0; i < obj->bindInfoCount; ++i) {
				Serialize2_VkBindBufferMemoryInfo( obj->pBindInfos + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkBindBufferMemory2KHR( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*bindInfoCount*/ " << IntToString(obj->bindInfoCount);
		result << ",\n";
		result << indent << "		/*pBindInfos*/ " << nameSer.Get( &obj->pBindInfos );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkBindImageMemory2KHR : {
		auto const*  obj = iter.Cast< packet_vkBindImageMemory2KHR *>();
		if ( obj->pBindInfos ) {
			CHECK( obj->bindInfoCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pBindInfos, "bindInfos"s, "bindImageMemoryInfo"s, "info"s );
			before << indent << "VkBindImageMemoryInfo  " << arr_name << "[" << IntToString(obj->bindInfoCount) << "] = {};\n";
			for (uint i = 0; i < obj->bindInfoCount; ++i) {
				Serialize2_VkBindImageMemoryInfo( obj->pBindInfos + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkBindImageMemory2KHR( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*bindInfoCount*/ " << IntToString(obj->bindInfoCount);
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
		auto const*  obj = iter.Cast< packet_vkCmdProcessCommandsNVX *>();
		if ( obj->pProcessCommandsInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pProcessCommandsInfo), nameSer, remapper, indent );
		}
		result << indent << "app.vkCmdProcessCommandsNVX( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*pProcessCommandsInfo*/ " << nameSer.GetPtr( obj->pProcessCommandsInfo );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdReserveSpaceForCommandsNVX : {
		auto const*  obj = iter.Cast< packet_vkCmdReserveSpaceForCommandsNVX *>();
		if ( obj->pReserveSpaceInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pReserveSpaceInfo), nameSer, remapper, indent );
		}
		result << indent << "app.vkCmdReserveSpaceForCommandsNVX( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*pReserveSpaceInfo*/ " << nameSer.GetPtr( obj->pReserveSpaceInfo );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateIndirectCommandsLayoutNVX : {
		auto const*  obj = iter.Cast< packet_vkCreateIndirectCommandsLayoutNVX *>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateIndirectCommandsLayoutNVX( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pIndirectCommandsLayout*/ " << "&app.EditResource(IndirectCommandsLayoutNVXID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_NVX_EXT, *obj->pIndirectCommandsLayout ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyIndirectCommandsLayoutNVX : {
		auto const*  obj = iter.Cast< packet_vkDestroyIndirectCommandsLayoutNVX *>();
		result << indent << "app.vkDestroyIndirectCommandsLayoutNVX( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*indirectCommandsLayout*/ " << "app.GetResource(IndirectCommandsLayoutNVXID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_NVX_EXT, obj->indirectCommandsLayout ) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateObjectTableNVX : {
		auto const*  obj = iter.Cast< packet_vkCreateObjectTableNVX *>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateObjectTableNVX( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pObjectTable*/ " << "&app.EditResource(ObjectTableNVXID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_OBJECT_TABLE_NVX_EXT, *obj->pObjectTable ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyObjectTableNVX : {
		auto const*  obj = iter.Cast< packet_vkDestroyObjectTableNVX *>();
		result << indent << "app.vkDestroyObjectTableNVX( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*objectTable*/ " << "app.GetResource(ObjectTableNVXID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_OBJECT_TABLE_NVX_EXT, obj->objectTable ) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkRegisterObjectsNVX : {
		auto const*  obj = iter.Cast< packet_vkRegisterObjectsNVX *>();
		if ( obj->ppObjectTableEntries ) {
			CHECK( obj->objectCount > 0 );
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
			CHECK( obj->objectCount > 0 );
			before << indent << "const uint32_t  " << nameSer.MakeUnique( &obj->pObjectIndices, "objectIndices"s ) << "[] = { ";
			for (uint i = 0; i < obj->objectCount; ++i) {
				before << (i ? ", " : "") << (i%16 == 0 ? "\n\t"s << indent : " ") << IntToString(obj->pObjectIndices[i]);
			}
			before << indent << " };\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pObjectIndices ) << ") == " << IntToString(obj->objectCount) << " );\n\n";
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkRegisterObjectsNVX( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*objectTable*/ " << "app.GetResource(ObjectTableNVXID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_OBJECT_TABLE_NVX_EXT, obj->objectTable ) << "))";
		result << ",\n";
		result << indent << "		/*objectCount*/ " << IntToString(obj->objectCount);
		result << ",\n";
		result << indent << "		/*ppObjectTableEntries*/ " << nameSer.Get( &obj->ppObjectTableEntries );
		result << ",\n";
		result << indent << "		/*pObjectIndices*/ " << nameSer.Get( &obj->pObjectIndices );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkUnregisterObjectsNVX : {
		auto const*  obj = iter.Cast< packet_vkUnregisterObjectsNVX *>();
		if ( obj->pObjectEntryTypes ) {
			CHECK( obj->objectCount > 0 );
			before << indent << "const VkObjectEntryTypeNVX  " << nameSer.MakeUnique( &obj->pObjectEntryTypes, "objectEntryTypes"s ) << "[] = {";
			for (uint i = 0; i < obj->objectCount; ++i) {
				before << (i ? "," : "") << (i%4 == 0 ? "\n\t"s << indent : " ") << Serialize_VkObjectEntryTypeNVX( obj->pObjectEntryTypes[i] );
			}
			before << "\n" << indent << " };\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pObjectEntryTypes ) << ") == " << IntToString(obj->objectCount) << " );\n\n";
		}
		if ( obj->pObjectIndices ) {
			CHECK( obj->objectCount > 0 );
			before << indent << "const uint32_t  " << nameSer.MakeUnique( &obj->pObjectIndices, "objectIndices"s ) << "[] = { ";
			for (uint i = 0; i < obj->objectCount; ++i) {
				before << (i ? ", " : "") << (i%16 == 0 ? "\n\t"s << indent : " ") << IntToString(obj->pObjectIndices[i]);
			}
			before << indent << " };\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pObjectIndices ) << ") == " << IntToString(obj->objectCount) << " );\n\n";
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkUnregisterObjectsNVX( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*objectTable*/ " << "app.GetResource(ObjectTableNVXID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_OBJECT_TABLE_NVX_EXT, obj->objectTable ) << "))";
		result << ",\n";
		result << indent << "		/*objectCount*/ " << IntToString(obj->objectCount);
		result << ",\n";
		result << indent << "		/*pObjectEntryTypes*/ " << nameSer.Get( &obj->pObjectEntryTypes );
		result << ",\n";
		result << indent << "		/*pObjectIndices*/ " << nameSer.Get( &obj->pObjectIndices );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX : break;
	case VKTRACE_TPI_VK_vkCmdSetViewportWScalingNV : {
		auto const*  obj = iter.Cast< packet_vkCmdSetViewportWScalingNV *>();
		if ( obj->pViewportWScalings ) {
			CHECK( obj->viewportCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pViewportWScalings, "viewportWScalings"s, "viewportWScalingNV"s );
			before << indent << "VkViewportWScalingNV  " << arr_name << "[" << IntToString(obj->viewportCount) << "] = {};\n";
			for (uint i = 0; i < obj->viewportCount; ++i) {
				Serialize2_VkViewportWScalingNV( obj->pViewportWScalings + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdSetViewportWScalingNV( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*firstViewport*/ " << IntToString(obj->firstViewport);
		result << ",\n";
		result << indent << "		/*viewportCount*/ " << IntToString(obj->viewportCount);
		result << ",\n";
		result << indent << "		/*pViewportWScalings*/ " << nameSer.Get( &obj->pViewportWScalings );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkReleaseDisplayEXT : break;
	case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceCapabilities2EXT : break;
	case VKTRACE_TPI_VK_vkGetRefreshCycleDurationGOOGLE : break;
	case VKTRACE_TPI_VK_vkGetPastPresentationTimingGOOGLE : break;
	case VKTRACE_TPI_VK_vkCmdSetDiscardRectangleEXT : {
		auto const*  obj = iter.Cast< packet_vkCmdSetDiscardRectangleEXT *>();
		if ( obj->pDiscardRectangles ) {
			CHECK( obj->discardRectangleCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pDiscardRectangles, "discardRectangles"s, "rect2D"s );
			before << indent << "VkRect2D  " << arr_name << "[" << IntToString(obj->discardRectangleCount) << "] = {};\n";
			for (uint i = 0; i < obj->discardRectangleCount; ++i) {
				Serialize2_VkRect2D( obj->pDiscardRectangles + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkCmdSetDiscardRectangleEXT( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*firstDiscardRectangle*/ " << IntToString(obj->firstDiscardRectangle);
		result << ",\n";
		result << indent << "		/*discardRectangleCount*/ " << IntToString(obj->discardRectangleCount);
		result << ",\n";
		result << indent << "		/*pDiscardRectangles*/ " << nameSer.Get( &obj->pDiscardRectangles );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkSetHdrMetadataEXT : {
		auto const*  obj = iter.Cast< packet_vkSetHdrMetadataEXT *>();
		if ( obj->pSwapchains ) {
			CHECK( obj->swapchainCount > 0 );
			before << indent << "const VkSwapchainKHR  " << nameSer.MakeUnique( &obj->pSwapchains, "swapchains"s, "swapchain"s ) << "[] = {";
			for (uint i = 0; i < obj->swapchainCount; ++i) {
				before << (i ? "," : "") << (i%4 == 0 ? "\n\t"s << indent : " ") << "app.GetResource(SwapchainKHRID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT, obj->pSwapchains[i] ) << "))";
			}
			before << "\n" << indent << "};\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pSwapchains ) << ") == " << IntToString(obj->swapchainCount) << " );\n\n";
		}
		if ( obj->pMetadata ) {
			CHECK( obj->swapchainCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pMetadata, "metadata"s, "hdrMetadata"s );
			before << indent << "VkHdrMetadataEXT  " << arr_name << "[" << IntToString(obj->swapchainCount) << "] = {};\n";
			for (uint i = 0; i < obj->swapchainCount; ++i) {
				Serialize2_VkHdrMetadataEXT( obj->pMetadata + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		result << indent << "app.vkSetHdrMetadataEXT( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*swapchainCount*/ " << IntToString(obj->swapchainCount);
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
		auto const*  obj = iter.Cast< packet_vkDisplayPowerControlEXT *>();
		if ( obj->pDisplayPowerInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pDisplayPowerInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkDisplayPowerControlEXT( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*display*/ " << "app.GetResource(DisplayKHRID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DISPLAY_KHR_EXT, obj->display ) << "))";
		result << ",\n";
		result << indent << "		/*pDisplayPowerInfo*/ " << nameSer.GetPtr( obj->pDisplayPowerInfo );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkRegisterDeviceEventEXT : {
		auto const*  obj = iter.Cast< packet_vkRegisterDeviceEventEXT *>();
		if ( obj->pDeviceEventInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pDeviceEventInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkRegisterDeviceEventEXT( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pDeviceEventInfo*/ " << nameSer.GetPtr( obj->pDeviceEventInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pFence*/ " << "&app.EditResource(FenceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT, *obj->pFence ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkRegisterDisplayEventEXT : {
		auto const*  obj = iter.Cast< packet_vkRegisterDisplayEventEXT *>();
		if ( obj->pDisplayEventInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pDisplayEventInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkRegisterDisplayEventEXT( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*display*/ " << "app.GetResource(DisplayKHRID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DISPLAY_KHR_EXT, obj->display ) << "))";
		result << ",\n";
		result << indent << "		/*pDisplayEventInfo*/ " << nameSer.GetPtr( obj->pDisplayEventInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pFence*/ " << "&app.EditResource(FenceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT, *obj->pFence ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetSwapchainCounterEXT : break;
	case VKTRACE_TPI_VK_vkCmdSetSampleLocationsEXT : {
		auto const*  obj = iter.Cast< packet_vkCmdSetSampleLocationsEXT *>();
		if ( obj->pSampleLocationsInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pSampleLocationsInfo), nameSer, remapper, indent );
		}
		result << indent << "app.vkCmdSetSampleLocationsEXT( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*pSampleLocationsInfo*/ " << nameSer.GetPtr( obj->pSampleLocationsInfo );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetPhysicalDeviceMultisamplePropertiesEXT : break;
	case VKTRACE_TPI_VK_vkCreateSamplerYcbcrConversionKHR : {
		auto const*  obj = iter.Cast< packet_vkCreateSamplerYcbcrConversionKHR *>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateSamplerYcbcrConversionKHR( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pYcbcrConversion*/ " << "&app.EditResource(SamplerYcbcrConversionID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION_EXT, *obj->pYcbcrConversion ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroySamplerYcbcrConversionKHR : {
		auto const*  obj = iter.Cast< packet_vkDestroySamplerYcbcrConversionKHR *>();
		result << indent << "app.vkDestroySamplerYcbcrConversionKHR( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*ycbcrConversion*/ " << "app.GetResource(SamplerYcbcrConversionID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION_EXT, obj->ycbcrConversion ) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetDisplayPlaneSupportedDisplaysKHR : break;
	case VKTRACE_TPI_VK_vkImportFenceFdKHR : {
		auto const*  obj = iter.Cast< packet_vkImportFenceFdKHR *>();
		if ( obj->pImportFenceFdInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pImportFenceFdInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkImportFenceFdKHR( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pImportFenceFdInfo*/ " << nameSer.GetPtr( obj->pImportFenceFdInfo );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetFenceFdKHR : break;
	case VKTRACE_TPI_VK_vkImportFenceWin32HandleKHR : {
		auto const*  obj = iter.Cast< packet_vkImportFenceWin32HandleKHR *>();
		if ( obj->pImportFenceWin32HandleInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pImportFenceWin32HandleInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkImportFenceWin32HandleKHR( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pImportFenceWin32HandleInfo*/ " << nameSer.GetPtr( obj->pImportFenceWin32HandleInfo );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetFenceWin32HandleKHR : break;
	case VKTRACE_TPI_VK_vkGetMemoryWin32HandleKHR : break;
	case VKTRACE_TPI_VK_vkGetMemoryWin32HandlePropertiesKHR : break;
	case VKTRACE_TPI_VK_vkImportSemaphoreWin32HandleKHR : {
		auto const*  obj = iter.Cast< packet_vkImportSemaphoreWin32HandleKHR *>();
		if ( obj->pImportSemaphoreWin32HandleInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pImportSemaphoreWin32HandleInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkImportSemaphoreWin32HandleKHR( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pImportSemaphoreWin32HandleInfo*/ " << nameSer.GetPtr( obj->pImportSemaphoreWin32HandleInfo );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetSemaphoreWin32HandleKHR : break;
	case VKTRACE_TPI_VK_vkGetMemoryHostPointerPropertiesEXT : break;
	case VKTRACE_TPI_VK_vkCreateValidationCacheEXT : break;
	case VKTRACE_TPI_VK_vkDestroyValidationCacheEXT : {
		auto const*  obj = iter.Cast< packet_vkDestroyValidationCacheEXT *>();
		result << indent << "app.vkDestroyValidationCacheEXT( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*validationCache*/ " << "app.GetResource(ValidationCacheEXTID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_VALIDATION_CACHE_EXT_EXT, obj->validationCache ) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkMergeValidationCachesEXT : {
		auto const*  obj = iter.Cast< packet_vkMergeValidationCachesEXT *>();
		if ( obj->pSrcCaches ) {
			CHECK( obj->srcCacheCount > 0 );
			before << indent << "const VkValidationCacheEXT  " << nameSer.MakeUnique( &obj->pSrcCaches, "srcCaches"s, "validationCache"s ) << "[] = {";
			for (uint i = 0; i < obj->srcCacheCount; ++i) {
				before << (i ? "," : "") << (i%4 == 0 ? "\n\t"s << indent : " ") << "app.GetResource(ValidationCacheEXTID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_VALIDATION_CACHE_EXT_EXT, obj->pSrcCaches[i] ) << "))";
			}
			before << "\n" << indent << "};\n";
			before << indent << "STATIC_ASSERT( std::size(" << nameSer.Get( &obj->pSrcCaches ) << ") == " << IntToString(obj->srcCacheCount) << " );\n\n";
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkMergeValidationCachesEXT( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*dstCache*/ " << "app.GetResource(ValidationCacheEXTID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_VALIDATION_CACHE_EXT_EXT, obj->dstCache ) << "))";
		result << ",\n";
		result << indent << "		/*srcCacheCount*/ " << IntToString(obj->srcCacheCount);
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
		auto const*  obj = iter.Cast< packet_vkBindBufferMemory2 *>();
		if ( obj->pBindInfos ) {
			CHECK( obj->bindInfoCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pBindInfos, "bindInfos"s, "bindBufferMemoryInfo"s, "info"s );
			before << indent << "VkBindBufferMemoryInfo  " << arr_name << "[" << IntToString(obj->bindInfoCount) << "] = {};\n";
			for (uint i = 0; i < obj->bindInfoCount; ++i) {
				Serialize2_VkBindBufferMemoryInfo( obj->pBindInfos + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkBindBufferMemory2( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*bindInfoCount*/ " << IntToString(obj->bindInfoCount);
		result << ",\n";
		result << indent << "		/*pBindInfos*/ " << nameSer.Get( &obj->pBindInfos );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkBindImageMemory2 : {
		auto const*  obj = iter.Cast< packet_vkBindImageMemory2 *>();
		if ( obj->pBindInfos ) {
			CHECK( obj->bindInfoCount > 0 );
			const String arr_name = nameSer.MakeUnique( &obj->pBindInfos, "bindInfos"s, "bindImageMemoryInfo"s, "info"s );
			before << indent << "VkBindImageMemoryInfo  " << arr_name << "[" << IntToString(obj->bindInfoCount) << "] = {};\n";
			for (uint i = 0; i < obj->bindInfoCount; ++i) {
				Serialize2_VkBindImageMemoryInfo( obj->pBindInfos + i, String(arr_name) << "[" << IntToString(i) << "]", nameSer, remapper, indent, INOUT result, INOUT before );
			}
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkBindImageMemory2( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*bindInfoCount*/ " << IntToString(obj->bindInfoCount);
		result << ",\n";
		result << indent << "		/*pBindInfos*/ " << nameSer.Get( &obj->pBindInfos );
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkGetDeviceGroupPeerMemoryFeatures : break;
	case VKTRACE_TPI_VK_vkCmdSetDeviceMask : {
		auto const*  obj = iter.Cast< packet_vkCmdSetDeviceMask *>();
		result << indent << "app.vkCmdSetDeviceMask( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*deviceMask*/ " << IntToString(obj->deviceMask);
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCmdDispatchBase : {
		auto const*  obj = iter.Cast< packet_vkCmdDispatchBase *>();
		result << indent << "app.vkCmdDispatchBase( \n";
		result << indent << "		/*commandBuffer*/ " << "app.GetResource(CommandBufferID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, obj->commandBuffer ) << "))";
		result << ",\n";
		result << indent << "		/*baseGroupX*/ " << IntToString(obj->baseGroupX);
		result << ",\n";
		result << indent << "		/*baseGroupY*/ " << IntToString(obj->baseGroupY);
		result << ",\n";
		result << indent << "		/*baseGroupZ*/ " << IntToString(obj->baseGroupZ);
		result << ",\n";
		result << indent << "		/*groupCountX*/ " << IntToString(obj->groupCountX);
		result << ",\n";
		result << indent << "		/*groupCountY*/ " << IntToString(obj->groupCountY);
		result << ",\n";
		result << indent << "		/*groupCountZ*/ " << IntToString(obj->groupCountZ);
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
		auto const*  obj = iter.Cast< packet_vkTrimCommandPool *>();
		result << indent << "app.vkTrimCommandPool( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*commandPool*/ " << "app.GetResource(CommandPoolID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_POOL_EXT, obj->commandPool ) << "))";
		result << ",\n";
		result << indent << "		/*flags*/ " << Serialize_VkCommandPoolTrimFlags( obj->flags );
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateSamplerYcbcrConversion : {
		auto const*  obj = iter.Cast< packet_vkCreateSamplerYcbcrConversion *>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateSamplerYcbcrConversion( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pYcbcrConversion*/ " << "&app.EditResource(SamplerYcbcrConversionID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION_EXT, *obj->pYcbcrConversion ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroySamplerYcbcrConversion : {
		auto const*  obj = iter.Cast< packet_vkDestroySamplerYcbcrConversion *>();
		result << indent << "app.vkDestroySamplerYcbcrConversion( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*ycbcrConversion*/ " << "app.GetResource(SamplerYcbcrConversionID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION_EXT, obj->ycbcrConversion ) << "))";
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << " );\n";
		break;
	}

	case VKTRACE_TPI_VK_vkCreateDescriptorUpdateTemplate : {
		auto const*  obj = iter.Cast< packet_vkCreateDescriptorUpdateTemplate *>();
		if ( obj->pCreateInfo ) {
			before << SerializeStruct( BitCast<VkBaseInStructure const*>(obj->pCreateInfo), nameSer, remapper, indent );
		}
		VK_CALL( obj->result );
		result << indent << "VK_CALL( app.vkCreateDescriptorUpdateTemplate( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*pCreateInfo*/ " << nameSer.GetPtr( obj->pCreateInfo );
		result << ",\n";
		result << indent << "		/*pAllocator*/ " << "null";
		result << ",\n";
		result << indent << "		/*pDescriptorUpdateTemplate*/ " << "&app.EditResource(DescriptorUpdateTemplateID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_EXT, *obj->pDescriptorUpdateTemplate ) << "))";
		result << " ));\n";
		break;
	}

	case VKTRACE_TPI_VK_vkDestroyDescriptorUpdateTemplate : {
		auto const*  obj = iter.Cast< packet_vkDestroyDescriptorUpdateTemplate *>();
		result << indent << "app.vkDestroyDescriptorUpdateTemplate( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, obj->device ) << "))";
		result << ",\n";
		result << indent << "		/*descriptorUpdateTemplate*/ " << "app.GetResource(DescriptorUpdateTemplateID(" << remapper( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_EXT, obj->descriptorUpdateTemplate ) << "))";
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
