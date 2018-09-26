// auto-generated file

void VUnpackStruct (VkBaseOutStructure *ptr, void *start)
{
	if ( ptr == null ) return;
	switch ( ptr->sType )
	{
		case VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO : {
			VkSemaphoreCreateInfo*  obj = BitCast<VkSemaphoreCreateInfo*>( ptr );
			VUnpack_VkSemaphoreCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_DOMAIN_ORIGIN_STATE_CREATE_INFO : {
			VkPipelineTessellationDomainOriginStateCreateInfo*  obj = BitCast<VkPipelineTessellationDomainOriginStateCreateInfo*>( ptr );
			VUnpack_VkPipelineTessellationDomainOriginStateCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO : {
			VkBufferViewCreateInfo*  obj = BitCast<VkBufferViewCreateInfo*>( ptr );
			VUnpack_VkBufferViewCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_MEMORY_BARRIER : {
			VkMemoryBarrier*  obj = BitCast<VkMemoryBarrier*>( ptr );
			VUnpack_VkMemoryBarrier( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO : {
			VkPipelineInputAssemblyStateCreateInfo*  obj = BitCast<VkPipelineInputAssemblyStateCreateInfo*>( ptr );
			VUnpack_VkPipelineInputAssemblyStateCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO_KHR : {
			VkImageFormatListCreateInfoKHR*  obj = BitCast<VkImageFormatListCreateInfoKHR*>( ptr );
			VUnpack_VkImageFormatListCreateInfoKHR( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE : {
			VkMappedMemoryRange*  obj = BitCast<VkMappedMemoryRange*>( ptr );
			VUnpack_VkMappedMemoryRange( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_SUBMIT_INFO : {
			VkSubmitInfo*  obj = BitCast<VkSubmitInfo*>( ptr );
			VUnpack_VkSubmitInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO : {
			VkPipelineDynamicStateCreateInfo*  obj = BitCast<VkPipelineDynamicStateCreateInfo*>( ptr );
			VUnpack_VkPipelineDynamicStateCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO : {
			VkImageViewCreateInfo*  obj = BitCast<VkImageViewCreateInfo*>( ptr );
			VUnpack_VkImageViewCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO : {
			VkPipelineTessellationStateCreateInfo*  obj = BitCast<VkPipelineTessellationStateCreateInfo*>( ptr );
			VUnpack_VkPipelineTessellationStateCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO : {
			VkMemoryAllocateInfo*  obj = BitCast<VkMemoryAllocateInfo*>( ptr );
			VUnpack_VkMemoryAllocateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_BIND_SPARSE_INFO : {
			VkBindSparseInfo*  obj = BitCast<VkBindSparseInfo*>( ptr );
			VUnpack_VkBindSparseInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO : {
			VkPipelineViewportStateCreateInfo*  obj = BitCast<VkPipelineViewportStateCreateInfo*>( ptr );
			VUnpack_VkPipelineViewportStateCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO : {
			VkPipelineVertexInputStateCreateInfo*  obj = BitCast<VkPipelineVertexInputStateCreateInfo*>( ptr );
			VUnpack_VkPipelineVertexInputStateCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_FENCE_CREATE_INFO : {
			VkFenceCreateInfo*  obj = BitCast<VkFenceCreateInfo*>( ptr );
			VUnpack_VkFenceCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_EVENT_CREATE_INFO : {
			VkEventCreateInfo*  obj = BitCast<VkEventCreateInfo*>( ptr );
			VUnpack_VkEventCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO : {
			VkRenderPassBeginInfo*  obj = BitCast<VkRenderPassBeginInfo*>( ptr );
			VUnpack_VkRenderPassBeginInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO : {
			VkQueryPoolCreateInfo*  obj = BitCast<VkQueryPoolCreateInfo*>( ptr );
			VUnpack_VkQueryPoolCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO : {
			VkBufferCreateInfo*  obj = BitCast<VkBufferCreateInfo*>( ptr );
			VUnpack_VkBufferCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO : {
			VkImageCreateInfo*  obj = BitCast<VkImageCreateInfo*>( ptr );
			VUnpack_VkImageCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO : {
			VkPipelineMultisampleStateCreateInfo*  obj = BitCast<VkPipelineMultisampleStateCreateInfo*>( ptr );
			VUnpack_VkPipelineMultisampleStateCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO_EXT : {
			VkDescriptorSetLayoutBindingFlagsCreateInfoEXT*  obj = BitCast<VkDescriptorSetLayoutBindingFlagsCreateInfoEXT*>( ptr );
			VUnpack_VkDescriptorSetLayoutBindingFlagsCreateInfoEXT( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO : {
			VkPipelineShaderStageCreateInfo*  obj = BitCast<VkPipelineShaderStageCreateInfo*>( ptr );
			VUnpack_VkPipelineShaderStageCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO : {
			VkPipelineRasterizationStateCreateInfo*  obj = BitCast<VkPipelineRasterizationStateCreateInfo*>( ptr );
			VUnpack_VkPipelineRasterizationStateCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO : {
			VkPipelineDepthStencilStateCreateInfo*  obj = BitCast<VkPipelineDepthStencilStateCreateInfo*>( ptr );
			VUnpack_VkPipelineDepthStencilStateCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO : {
			VkCommandBufferInheritanceInfo*  obj = BitCast<VkCommandBufferInheritanceInfo*>( ptr );
			VUnpack_VkCommandBufferInheritanceInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO : {
			VkPipelineColorBlendStateCreateInfo*  obj = BitCast<VkPipelineColorBlendStateCreateInfo*>( ptr );
			VUnpack_VkPipelineColorBlendStateCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO : {
			VkGraphicsPipelineCreateInfo*  obj = BitCast<VkGraphicsPipelineCreateInfo*>( ptr );
			VUnpack_VkGraphicsPipelineCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_INFO : {
			VkSamplerYcbcrConversionInfo*  obj = BitCast<VkSamplerYcbcrConversionInfo*>( ptr );
			VUnpack_VkSamplerYcbcrConversionInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO : {
			VkComputePipelineCreateInfo*  obj = BitCast<VkComputePipelineCreateInfo*>( ptr );
			VUnpack_VkComputePipelineCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO : {
			VkPipelineLayoutCreateInfo*  obj = BitCast<VkPipelineLayoutCreateInfo*>( ptr );
			VUnpack_VkPipelineLayoutCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO : {
			VkSamplerCreateInfo*  obj = BitCast<VkSamplerCreateInfo*>( ptr );
			VUnpack_VkSamplerCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO : {
			VkDescriptorSetLayoutCreateInfo*  obj = BitCast<VkDescriptorSetLayoutCreateInfo*>( ptr );
			VUnpack_VkDescriptorSetLayoutCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO : {
			VkDescriptorPoolCreateInfo*  obj = BitCast<VkDescriptorPoolCreateInfo*>( ptr );
			VUnpack_VkDescriptorPoolCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO : {
			VkDescriptorSetAllocateInfo*  obj = BitCast<VkDescriptorSetAllocateInfo*>( ptr );
			VUnpack_VkDescriptorSetAllocateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET : {
			VkWriteDescriptorSet*  obj = BitCast<VkWriteDescriptorSet*>( ptr );
			VUnpack_VkWriteDescriptorSet( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET : {
			VkCopyDescriptorSet*  obj = BitCast<VkCopyDescriptorSet*>( ptr );
			VUnpack_VkCopyDescriptorSet( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO : {
			VkFramebufferCreateInfo*  obj = BitCast<VkFramebufferCreateInfo*>( ptr );
			VUnpack_VkFramebufferCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO : {
			VkRenderPassCreateInfo*  obj = BitCast<VkRenderPassCreateInfo*>( ptr );
			VUnpack_VkRenderPassCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO : {
			VkCommandPoolCreateInfo*  obj = BitCast<VkCommandPoolCreateInfo*>( ptr );
			VUnpack_VkCommandPoolCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO : {
			VkCommandBufferAllocateInfo*  obj = BitCast<VkCommandBufferAllocateInfo*>( ptr );
			VUnpack_VkCommandBufferAllocateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO : {
			VkCommandBufferBeginInfo*  obj = BitCast<VkCommandBufferBeginInfo*>( ptr );
			VUnpack_VkCommandBufferBeginInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER : {
			VkBufferMemoryBarrier*  obj = BitCast<VkBufferMemoryBarrier*>( ptr );
			VUnpack_VkBufferMemoryBarrier( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER : {
			VkImageMemoryBarrier*  obj = BitCast<VkImageMemoryBarrier*>( ptr );
			VUnpack_VkImageMemoryBarrier( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_TO_COLOR_STATE_CREATE_INFO_NV : {
			VkPipelineCoverageToColorStateCreateInfoNV*  obj = BitCast<VkPipelineCoverageToColorStateCreateInfoNV*>( ptr );
			VUnpack_VkPipelineCoverageToColorStateCreateInfoNV( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO : {
			VkBindBufferMemoryInfo*  obj = BitCast<VkBindBufferMemoryInfo*>( ptr );
			VUnpack_VkBindBufferMemoryInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO : {
			VkBindImageMemoryInfo*  obj = BitCast<VkBindImageMemoryInfo*>( ptr );
			VUnpack_VkBindImageMemoryInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_SUBPASS_END_INFO_KHR : {
			VkSubpassEndInfoKHR*  obj = BitCast<VkSubpassEndInfoKHR*>( ptr );
			VUnpack_VkSubpassEndInfoKHR( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO : {
			VkMemoryDedicatedAllocateInfo*  obj = BitCast<VkMemoryDedicatedAllocateInfo*>( ptr );
			VUnpack_VkMemoryDedicatedAllocateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO : {
			VkMemoryAllocateFlagsInfo*  obj = BitCast<VkMemoryAllocateFlagsInfo*>( ptr );
			VUnpack_VkMemoryAllocateFlagsInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_DEVICE_GROUP_RENDER_PASS_BEGIN_INFO : {
			VkDeviceGroupRenderPassBeginInfo*  obj = BitCast<VkDeviceGroupRenderPassBeginInfo*>( ptr );
			VUnpack_VkDeviceGroupRenderPassBeginInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_DEVICE_GROUP_COMMAND_BUFFER_BEGIN_INFO : {
			VkDeviceGroupCommandBufferBeginInfo*  obj = BitCast<VkDeviceGroupCommandBufferBeginInfo*>( ptr );
			VUnpack_VkDeviceGroupCommandBufferBeginInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_DEVICE_GROUP_SUBMIT_INFO : {
			VkDeviceGroupSubmitInfo*  obj = BitCast<VkDeviceGroupSubmitInfo*>( ptr );
			VUnpack_VkDeviceGroupSubmitInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_DEVICE_GROUP_BIND_SPARSE_INFO : {
			VkDeviceGroupBindSparseInfo*  obj = BitCast<VkDeviceGroupBindSparseInfo*>( ptr );
			VUnpack_VkDeviceGroupBindSparseInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_DEVICE_GROUP_INFO : {
			VkBindBufferMemoryDeviceGroupInfo*  obj = BitCast<VkBindBufferMemoryDeviceGroupInfo*>( ptr );
			VUnpack_VkBindBufferMemoryDeviceGroupInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_DEVICE_GROUP_INFO : {
			VkBindImageMemoryDeviceGroupInfo*  obj = BitCast<VkBindImageMemoryDeviceGroupInfo*>( ptr );
			VUnpack_VkBindImageMemoryDeviceGroupInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_SAMPLER_REDUCTION_MODE_CREATE_INFO_EXT : {
			VkSamplerReductionModeCreateInfoEXT*  obj = BitCast<VkSamplerReductionModeCreateInfoEXT*>( ptr );
			VUnpack_VkSamplerReductionModeCreateInfoEXT( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2_KHR : {
			VkAttachmentReference2KHR*  obj = BitCast<VkAttachmentReference2KHR*>( ptr );
			VUnpack_VkAttachmentReference2KHR( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_RENDER_PASS_INPUT_ATTACHMENT_ASPECT_CREATE_INFO : {
			VkRenderPassInputAttachmentAspectCreateInfo*  obj = BitCast<VkRenderPassInputAttachmentAspectCreateInfo*>( ptr );
			VUnpack_VkRenderPassInputAttachmentAspectCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO : {
			VkImageViewUsageCreateInfo*  obj = BitCast<VkImageViewUsageCreateInfo*>( ptr );
			VUnpack_VkImageViewUsageCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_RENDER_PASS_MULTIVIEW_CREATE_INFO : {
			VkRenderPassMultiviewCreateInfo*  obj = BitCast<VkRenderPassMultiviewCreateInfo*>( ptr );
			VUnpack_VkRenderPassMultiviewCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_RENDER_PASS_SAMPLE_LOCATIONS_BEGIN_INFO_EXT : {
			VkRenderPassSampleLocationsBeginInfoEXT*  obj = BitCast<VkRenderPassSampleLocationsBeginInfoEXT*>( ptr );
			VUnpack_VkRenderPassSampleLocationsBeginInfoEXT( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2 : {
			VkDeviceQueueInfo2*  obj = BitCast<VkDeviceQueueInfo2*>( ptr );
			VUnpack_VkDeviceQueueInfo2( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_PROTECTED_SUBMIT_INFO : {
			VkProtectedSubmitInfo*  obj = BitCast<VkProtectedSubmitInfo*>( ptr );
			VUnpack_VkProtectedSubmitInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_CREATE_INFO : {
			VkSamplerYcbcrConversionCreateInfo*  obj = BitCast<VkSamplerYcbcrConversionCreateInfo*>( ptr );
			VUnpack_VkSamplerYcbcrConversionCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_BIND_IMAGE_PLANE_MEMORY_INFO : {
			VkBindImagePlaneMemoryInfo*  obj = BitCast<VkBindImagePlaneMemoryInfo*>( ptr );
			VUnpack_VkBindImagePlaneMemoryInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_CREATE_INFO : {
			VkDescriptorUpdateTemplateCreateInfo*  obj = BitCast<VkDescriptorUpdateTemplateCreateInfo*>( ptr );
			VUnpack_VkDescriptorUpdateTemplateCreateInfo( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_IMAGE_SWAPCHAIN_CREATE_INFO_KHR : {
			VkImageSwapchainCreateInfoKHR*  obj = BitCast<VkImageSwapchainCreateInfoKHR*>( ptr );
			VUnpack_VkImageSwapchainCreateInfoKHR( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_SWAPCHAIN_INFO_KHR : {
			VkBindImageMemorySwapchainInfoKHR*  obj = BitCast<VkBindImageMemorySwapchainInfoKHR*>( ptr );
			VUnpack_VkBindImageMemorySwapchainInfoKHR( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_ADVANCED_STATE_CREATE_INFO_EXT : {
			VkPipelineColorBlendAdvancedStateCreateInfoEXT*  obj = BitCast<VkPipelineColorBlendAdvancedStateCreateInfoEXT*>( ptr );
			VUnpack_VkPipelineColorBlendAdvancedStateCreateInfoEXT( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_2_KHR : {
			VkAttachmentDescription2KHR*  obj = BitCast<VkAttachmentDescription2KHR*>( ptr );
			VUnpack_VkAttachmentDescription2KHR( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_2_KHR : {
			VkSubpassDescription2KHR*  obj = BitCast<VkSubpassDescription2KHR*>( ptr );
			VUnpack_VkSubpassDescription2KHR( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_SUBPASS_DEPENDENCY_2_KHR : {
			VkSubpassDependency2KHR*  obj = BitCast<VkSubpassDependency2KHR*>( ptr );
			VUnpack_VkSubpassDependency2KHR( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO_2_KHR : {
			VkRenderPassCreateInfo2KHR*  obj = BitCast<VkRenderPassCreateInfo2KHR*>( ptr );
			VUnpack_VkRenderPassCreateInfo2KHR( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_SUBPASS_BEGIN_INFO_KHR : {
			VkSubpassBeginInfoKHR*  obj = BitCast<VkSubpassBeginInfoKHR*>( ptr );
			VUnpack_VkSubpassBeginInfoKHR( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_ALLOCATE_INFO_EXT : {
			VkDescriptorSetVariableDescriptorCountAllocateInfoEXT*  obj = BitCast<VkDescriptorSetVariableDescriptorCountAllocateInfoEXT*>( ptr );
			VUnpack_VkDescriptorSetVariableDescriptorCountAllocateInfoEXT( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_RASTERIZATION_ORDER_AMD : {
			VkPipelineRasterizationStateRasterizationOrderAMD*  obj = BitCast<VkPipelineRasterizationStateRasterizationOrderAMD*>( ptr );
			VUnpack_VkPipelineRasterizationStateRasterizationOrderAMD( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_NAME_INFO_EXT : {
			VkDebugMarkerObjectNameInfoEXT*  obj = BitCast<VkDebugMarkerObjectNameInfoEXT*>( ptr );
			VUnpack_VkDebugMarkerObjectNameInfoEXT( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_DEBUG_MARKER_MARKER_INFO_EXT : {
			VkDebugMarkerMarkerInfoEXT*  obj = BitCast<VkDebugMarkerMarkerInfoEXT*>( ptr );
			VUnpack_VkDebugMarkerMarkerInfoEXT( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_IMAGE_CREATE_INFO_NV : {
			VkDedicatedAllocationImageCreateInfoNV*  obj = BitCast<VkDedicatedAllocationImageCreateInfoNV*>( ptr );
			VUnpack_VkDedicatedAllocationImageCreateInfoNV( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_BUFFER_CREATE_INFO_NV : {
			VkDedicatedAllocationBufferCreateInfoNV*  obj = BitCast<VkDedicatedAllocationBufferCreateInfoNV*>( ptr );
			VUnpack_VkDedicatedAllocationBufferCreateInfoNV( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_MEMORY_ALLOCATE_INFO_NV : {
			VkDedicatedAllocationMemoryAllocateInfoNV*  obj = BitCast<VkDedicatedAllocationMemoryAllocateInfoNV*>( ptr );
			VUnpack_VkDedicatedAllocationMemoryAllocateInfoNV( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_IMAGE_VIEW_ASTC_DECODE_MODE_EXT : {
			VkImageViewASTCDecodeModeEXT*  obj = BitCast<VkImageViewASTCDecodeModeEXT*>( ptr );
			VUnpack_VkImageViewASTCDecodeModeEXT( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_CONDITIONAL_RENDERING_BEGIN_INFO_EXT : {
			VkConditionalRenderingBeginInfoEXT*  obj = BitCast<VkConditionalRenderingBeginInfoEXT*>( ptr );
			VUnpack_VkConditionalRenderingBeginInfoEXT( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_CONDITIONAL_RENDERING_INFO_EXT : {
			VkCommandBufferInheritanceConditionalRenderingInfoEXT*  obj = BitCast<VkCommandBufferInheritanceConditionalRenderingInfoEXT*>( ptr );
			VUnpack_VkCommandBufferInheritanceConditionalRenderingInfoEXT( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_INDIRECT_COMMANDS_LAYOUT_CREATE_INFO_NVX : {
			VkIndirectCommandsLayoutCreateInfoNVX*  obj = BitCast<VkIndirectCommandsLayoutCreateInfoNVX*>( ptr );
			VUnpack_VkIndirectCommandsLayoutCreateInfoNVX( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_CMD_PROCESS_COMMANDS_INFO_NVX : {
			VkCmdProcessCommandsInfoNVX*  obj = BitCast<VkCmdProcessCommandsInfoNVX*>( ptr );
			VUnpack_VkCmdProcessCommandsInfoNVX( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_CMD_RESERVE_SPACE_FOR_COMMANDS_INFO_NVX : {
			VkCmdReserveSpaceForCommandsInfoNVX*  obj = BitCast<VkCmdReserveSpaceForCommandsInfoNVX*>( ptr );
			VUnpack_VkCmdReserveSpaceForCommandsInfoNVX( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_OBJECT_TABLE_CREATE_INFO_NVX : {
			VkObjectTableCreateInfoNVX*  obj = BitCast<VkObjectTableCreateInfoNVX*>( ptr );
			VUnpack_VkObjectTableCreateInfoNVX( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_W_SCALING_STATE_CREATE_INFO_NV : {
			VkPipelineViewportWScalingStateCreateInfoNV*  obj = BitCast<VkPipelineViewportWScalingStateCreateInfoNV*>( ptr );
			VUnpack_VkPipelineViewportWScalingStateCreateInfoNV( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_SWIZZLE_STATE_CREATE_INFO_NV : {
			VkPipelineViewportSwizzleStateCreateInfoNV*  obj = BitCast<VkPipelineViewportSwizzleStateCreateInfoNV*>( ptr );
			VUnpack_VkPipelineViewportSwizzleStateCreateInfoNV( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_DISCARD_RECTANGLE_STATE_CREATE_INFO_EXT : {
			VkPipelineDiscardRectangleStateCreateInfoEXT*  obj = BitCast<VkPipelineDiscardRectangleStateCreateInfoEXT*>( ptr );
			VUnpack_VkPipelineDiscardRectangleStateCreateInfoEXT( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_CONSERVATIVE_STATE_CREATE_INFO_EXT : {
			VkPipelineRasterizationConservativeStateCreateInfoEXT*  obj = BitCast<VkPipelineRasterizationConservativeStateCreateInfoEXT*>( ptr );
			VUnpack_VkPipelineRasterizationConservativeStateCreateInfoEXT( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_INLINE_UNIFORM_BLOCK_EXT : {
			VkWriteDescriptorSetInlineUniformBlockEXT*  obj = BitCast<VkWriteDescriptorSetInlineUniformBlockEXT*>( ptr );
			VUnpack_VkWriteDescriptorSetInlineUniformBlockEXT( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_INLINE_UNIFORM_BLOCK_CREATE_INFO_EXT : {
			VkDescriptorPoolInlineUniformBlockCreateInfoEXT*  obj = BitCast<VkDescriptorPoolInlineUniformBlockCreateInfoEXT*>( ptr );
			VUnpack_VkDescriptorPoolInlineUniformBlockCreateInfoEXT( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_SAMPLE_LOCATIONS_INFO_EXT : {
			VkSampleLocationsInfoEXT*  obj = BitCast<VkSampleLocationsInfoEXT*>( ptr );
			VUnpack_VkSampleLocationsInfoEXT( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_SAMPLE_LOCATIONS_STATE_CREATE_INFO_EXT : {
			VkPipelineSampleLocationsStateCreateInfoEXT*  obj = BitCast<VkPipelineSampleLocationsStateCreateInfoEXT*>( ptr );
			VUnpack_VkPipelineSampleLocationsStateCreateInfoEXT( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_MODULATION_STATE_CREATE_INFO_NV : {
			VkPipelineCoverageModulationStateCreateInfoNV*  obj = BitCast<VkPipelineCoverageModulationStateCreateInfoNV*>( ptr );
			VUnpack_VkPipelineCoverageModulationStateCreateInfoNV( obj, start );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_DIVISOR_STATE_CREATE_INFO_EXT : {
			VkPipelineVertexInputDivisorStateCreateInfoEXT*  obj = BitCast<VkPipelineVertexInputDivisorStateCreateInfoEXT*>( ptr );
			VUnpack_VkPipelineVertexInputDivisorStateCreateInfoEXT( obj, start );
			break;
		}

	}
}

void VUnpack_VkSemaphoreCreateInfo (VkSemaphoreCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkDescriptorUpdateTemplateEntry (VkDescriptorUpdateTemplateEntry *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkPipelineTessellationDomainOriginStateCreateInfo (VkPipelineTessellationDomainOriginStateCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkBufferViewCreateInfo (VkBufferViewCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkMemoryBarrier (VkMemoryBarrier *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkPipelineColorBlendAttachmentState (VkPipelineColorBlendAttachmentState *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkAllocationCallbacks (VkAllocationCallbacks *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pUserData, start );
}


void VUnpack_VkPipelineInputAssemblyStateCreateInfo (VkPipelineInputAssemblyStateCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkExtent3D (VkExtent3D *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkSparseBufferMemoryBindInfo (VkSparseBufferMemoryBindInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pBinds, start );
	for (uint i = 0; (ptr->pBinds != null) and (i < ptr->bindCount); ++i) {
		VUnpack_VkSparseMemoryBind( PtrCast<VkSparseMemoryBind>(ptr->pBinds + i), start );
	}
}


void VUnpack_VkImageFormatListCreateInfoKHR (VkImageFormatListCreateInfoKHR *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pViewFormats, start );
}


void VUnpack_VkOffset2D (VkOffset2D *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkMappedMemoryRange (VkMappedMemoryRange *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkSubmitInfo (VkSubmitInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pWaitSemaphores, start );
	VUnpackPointer( INOUT ptr->pWaitDstStageMask, start );
	VUnpackPointer( INOUT ptr->pCommandBuffers, start );
	VUnpackPointer( INOUT ptr->pSignalSemaphores, start );
}


void VUnpack_VkPipelineDynamicStateCreateInfo (VkPipelineDynamicStateCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pDynamicStates, start );
}


void VUnpack_VkSparseMemoryBind (VkSparseMemoryBind *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkImageViewCreateInfo (VkImageViewCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkPipelineTessellationStateCreateInfo (VkPipelineTessellationStateCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkMemoryAllocateInfo (VkMemoryAllocateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkSpecializationMapEntry (VkSpecializationMapEntry *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkComponentMapping (VkComponentMapping *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkImageResolve (VkImageResolve *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkBindSparseInfo (VkBindSparseInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pWaitSemaphores, start );
	VUnpackPointer( INOUT ptr->pBufferBinds, start );
	for (uint i = 0; (ptr->pBufferBinds != null) and (i < ptr->bufferBindCount); ++i) {
		VUnpack_VkSparseBufferMemoryBindInfo( PtrCast<VkSparseBufferMemoryBindInfo>(ptr->pBufferBinds + i), start );
	}
	VUnpackPointer( INOUT ptr->pImageOpaqueBinds, start );
	for (uint i = 0; (ptr->pImageOpaqueBinds != null) and (i < ptr->imageOpaqueBindCount); ++i) {
		VUnpack_VkSparseImageOpaqueMemoryBindInfo( PtrCast<VkSparseImageOpaqueMemoryBindInfo>(ptr->pImageOpaqueBinds + i), start );
	}
	VUnpackPointer( INOUT ptr->pImageBinds, start );
	for (uint i = 0; (ptr->pImageBinds != null) and (i < ptr->imageBindCount); ++i) {
		VUnpack_VkSparseImageMemoryBindInfo( PtrCast<VkSparseImageMemoryBindInfo>(ptr->pImageBinds + i), start );
	}
	VUnpackPointer( INOUT ptr->pSignalSemaphores, start );
}


void VUnpack_VkSparseImageOpaqueMemoryBindInfo (VkSparseImageOpaqueMemoryBindInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pBinds, start );
	for (uint i = 0; (ptr->pBinds != null) and (i < ptr->bindCount); ++i) {
		VUnpack_VkSparseMemoryBind( PtrCast<VkSparseMemoryBind>(ptr->pBinds + i), start );
	}
}


void VUnpack_VkPipelineViewportStateCreateInfo (VkPipelineViewportStateCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pViewports, start );
	for (uint i = 0; (ptr->pViewports != null) and (i < ptr->viewportCount); ++i) {
		VUnpack_VkViewport( PtrCast<VkViewport>(ptr->pViewports + i), start );
	}
	VUnpackPointer( INOUT ptr->pScissors, start );
	for (uint i = 0; (ptr->pScissors != null) and (i < ptr->scissorCount); ++i) {
		VUnpack_VkRect2D( PtrCast<VkRect2D>(ptr->pScissors + i), start );
	}
}


void VUnpack_VkPipelineVertexInputStateCreateInfo (VkPipelineVertexInputStateCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pVertexBindingDescriptions, start );
	for (uint i = 0; (ptr->pVertexBindingDescriptions != null) and (i < ptr->vertexBindingDescriptionCount); ++i) {
		VUnpack_VkVertexInputBindingDescription( PtrCast<VkVertexInputBindingDescription>(ptr->pVertexBindingDescriptions + i), start );
	}
	VUnpackPointer( INOUT ptr->pVertexAttributeDescriptions, start );
	for (uint i = 0; (ptr->pVertexAttributeDescriptions != null) and (i < ptr->vertexAttributeDescriptionCount); ++i) {
		VUnpack_VkVertexInputAttributeDescription( PtrCast<VkVertexInputAttributeDescription>(ptr->pVertexAttributeDescriptions + i), start );
	}
}


void VUnpack_VkImageSubresource (VkImageSubresource *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkOffset3D (VkOffset3D *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkSparseImageMemoryBind (VkSparseImageMemoryBind *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkSparseImageMemoryBindInfo (VkSparseImageMemoryBindInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pBinds, start );
	for (uint i = 0; (ptr->pBinds != null) and (i < ptr->bindCount); ++i) {
		VUnpack_VkSparseImageMemoryBind( PtrCast<VkSparseImageMemoryBind>(ptr->pBinds + i), start );
	}
}


void VUnpack_VkFenceCreateInfo (VkFenceCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkEventCreateInfo (VkEventCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkRenderPassBeginInfo (VkRenderPassBeginInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pClearValues, start );
	for (uint i = 0; (ptr->pClearValues != null) and (i < ptr->clearValueCount); ++i) {
		VUnpack_VkClearValue( PtrCast<VkClearValue>(ptr->pClearValues + i), start );
	}
}


void VUnpack_VkQueryPoolCreateInfo (VkQueryPoolCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkBufferCreateInfo (VkBufferCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pQueueFamilyIndices, start );
}


void VUnpack_VkImageCreateInfo (VkImageCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pQueueFamilyIndices, start );
}


void VUnpack_VkPipelineMultisampleStateCreateInfo (VkPipelineMultisampleStateCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pSampleMask, start );
}


void VUnpack_VkViewport (VkViewport *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkImageSubresourceRange (VkImageSubresourceRange *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkDescriptorSetLayoutBindingFlagsCreateInfoEXT (VkDescriptorSetLayoutBindingFlagsCreateInfoEXT *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pBindingFlags, start );
}


void VUnpack_VkSpecializationInfo (VkSpecializationInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pMapEntries, start );
	for (uint i = 0; (ptr->pMapEntries != null) and (i < ptr->mapEntryCount); ++i) {
		VUnpack_VkSpecializationMapEntry( PtrCast<VkSpecializationMapEntry>(ptr->pMapEntries + i), start );
	}
	VUnpackPointer( INOUT ptr->pData, start );
}


void VUnpack_VkPipelineShaderStageCreateInfo (VkPipelineShaderStageCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pName, start );
	VUnpackPointer( INOUT ptr->pSpecializationInfo, start );
	VUnpack_VkSpecializationInfo( PtrCast<VkSpecializationInfo>(ptr->pSpecializationInfo), start );
}


void VUnpack_VkVertexInputBindingDescription (VkVertexInputBindingDescription *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkImageCopy (VkImageCopy *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkVertexInputAttributeDescription (VkVertexInputAttributeDescription *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkPipelineRasterizationStateCreateInfo (VkPipelineRasterizationStateCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkExtent2D (VkExtent2D *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkRect2D (VkRect2D *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkStencilOpState (VkStencilOpState *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkPipelineDepthStencilStateCreateInfo (VkPipelineDepthStencilStateCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkCommandBufferInheritanceInfo (VkCommandBufferInheritanceInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkPipelineColorBlendStateCreateInfo (VkPipelineColorBlendStateCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pAttachments, start );
	for (uint i = 0; (ptr->pAttachments != null) and (i < ptr->attachmentCount); ++i) {
		VUnpack_VkPipelineColorBlendAttachmentState( PtrCast<VkPipelineColorBlendAttachmentState>(ptr->pAttachments + i), start );
	}
}


void VUnpack_VkGraphicsPipelineCreateInfo (VkGraphicsPipelineCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pStages, start );
	for (uint i = 0; (ptr->pStages != null) and (i < ptr->stageCount); ++i) {
		VUnpackStruct( PtrCast<VkBaseOutStructure>(ptr->pStages + i), start );
	}
	VUnpackPointer( INOUT ptr->pVertexInputState, start );
	VUnpackStruct( PtrCast<VkBaseOutStructure>(ptr->pVertexInputState), start );
	VUnpackPointer( INOUT ptr->pInputAssemblyState, start );
	VUnpackStruct( PtrCast<VkBaseOutStructure>(ptr->pInputAssemblyState), start );
	VUnpackPointer( INOUT ptr->pTessellationState, start );
	VUnpackStruct( PtrCast<VkBaseOutStructure>(ptr->pTessellationState), start );
	VUnpackPointer( INOUT ptr->pViewportState, start );
	VUnpackStruct( PtrCast<VkBaseOutStructure>(ptr->pViewportState), start );
	VUnpackPointer( INOUT ptr->pRasterizationState, start );
	VUnpackStruct( PtrCast<VkBaseOutStructure>(ptr->pRasterizationState), start );
	VUnpackPointer( INOUT ptr->pMultisampleState, start );
	VUnpackStruct( PtrCast<VkBaseOutStructure>(ptr->pMultisampleState), start );
	VUnpackPointer( INOUT ptr->pDepthStencilState, start );
	VUnpackStruct( PtrCast<VkBaseOutStructure>(ptr->pDepthStencilState), start );
	VUnpackPointer( INOUT ptr->pColorBlendState, start );
	VUnpackStruct( PtrCast<VkBaseOutStructure>(ptr->pColorBlendState), start );
	VUnpackPointer( INOUT ptr->pDynamicState, start );
	VUnpackStruct( PtrCast<VkBaseOutStructure>(ptr->pDynamicState), start );
}


void VUnpack_VkSamplerYcbcrConversionInfo (VkSamplerYcbcrConversionInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkComputePipelineCreateInfo (VkComputePipelineCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkPushConstantRange (VkPushConstantRange *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkPipelineLayoutCreateInfo (VkPipelineLayoutCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pSetLayouts, start );
	VUnpackPointer( INOUT ptr->pPushConstantRanges, start );
	for (uint i = 0; (ptr->pPushConstantRanges != null) and (i < ptr->pushConstantRangeCount); ++i) {
		VUnpack_VkPushConstantRange( PtrCast<VkPushConstantRange>(ptr->pPushConstantRanges + i), start );
	}
}


void VUnpack_VkSamplerCreateInfo (VkSamplerCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkDescriptorSetLayoutBinding (VkDescriptorSetLayoutBinding *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pImmutableSamplers, start );
}


void VUnpack_VkDescriptorSetLayoutCreateInfo (VkDescriptorSetLayoutCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pBindings, start );
	for (uint i = 0; (ptr->pBindings != null) and (i < ptr->bindingCount); ++i) {
		VUnpack_VkDescriptorSetLayoutBinding( PtrCast<VkDescriptorSetLayoutBinding>(ptr->pBindings + i), start );
	}
}


void VUnpack_VkDescriptorPoolSize (VkDescriptorPoolSize *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkDescriptorPoolCreateInfo (VkDescriptorPoolCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pPoolSizes, start );
	for (uint i = 0; (ptr->pPoolSizes != null) and (i < ptr->poolSizeCount); ++i) {
		VUnpack_VkDescriptorPoolSize( PtrCast<VkDescriptorPoolSize>(ptr->pPoolSizes + i), start );
	}
}


void VUnpack_VkDescriptorSetAllocateInfo (VkDescriptorSetAllocateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pSetLayouts, start );
}


void VUnpack_VkClearValue (VkClearValue *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkDescriptorImageInfo (VkDescriptorImageInfo *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkDescriptorBufferInfo (VkDescriptorBufferInfo *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkWriteDescriptorSet (VkWriteDescriptorSet *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pImageInfo, start );
	for (uint i = 0; (ptr->pImageInfo != null) and (i < ptr->descriptorCount); ++i) {
		VUnpack_VkDescriptorImageInfo( PtrCast<VkDescriptorImageInfo>(ptr->pImageInfo + i), start );
	}
	VUnpackPointer( INOUT ptr->pBufferInfo, start );
	for (uint i = 0; (ptr->pBufferInfo != null) and (i < ptr->descriptorCount); ++i) {
		VUnpack_VkDescriptorBufferInfo( PtrCast<VkDescriptorBufferInfo>(ptr->pBufferInfo + i), start );
	}
	VUnpackPointer( INOUT ptr->pTexelBufferView, start );
}


void VUnpack_VkCopyDescriptorSet (VkCopyDescriptorSet *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkFramebufferCreateInfo (VkFramebufferCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pAttachments, start );
}


void VUnpack_VkAttachmentDescription (VkAttachmentDescription *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkAttachmentReference (VkAttachmentReference *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkSubpassDescription (VkSubpassDescription *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pInputAttachments, start );
	for (uint i = 0; (ptr->pInputAttachments != null) and (i < ptr->inputAttachmentCount); ++i) {
		VUnpack_VkAttachmentReference( PtrCast<VkAttachmentReference>(ptr->pInputAttachments + i), start );
	}
	VUnpackPointer( INOUT ptr->pColorAttachments, start );
	for (uint i = 0; (ptr->pColorAttachments != null) and (i < ptr->colorAttachmentCount); ++i) {
		VUnpack_VkAttachmentReference( PtrCast<VkAttachmentReference>(ptr->pColorAttachments + i), start );
	}
	VUnpackPointer( INOUT ptr->pResolveAttachments, start );
	for (uint i = 0; (ptr->pResolveAttachments != null) and (i < ptr->colorAttachmentCount); ++i) {
		VUnpack_VkAttachmentReference( PtrCast<VkAttachmentReference>(ptr->pResolveAttachments + i), start );
	}
	VUnpackPointer( INOUT ptr->pDepthStencilAttachment, start );
	VUnpack_VkAttachmentReference( PtrCast<VkAttachmentReference>(ptr->pDepthStencilAttachment), start );
	VUnpackPointer( INOUT ptr->pPreserveAttachments, start );
}


void VUnpack_VkSubpassDependency (VkSubpassDependency *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkRenderPassCreateInfo (VkRenderPassCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pAttachments, start );
	for (uint i = 0; (ptr->pAttachments != null) and (i < ptr->attachmentCount); ++i) {
		VUnpack_VkAttachmentDescription( PtrCast<VkAttachmentDescription>(ptr->pAttachments + i), start );
	}
	VUnpackPointer( INOUT ptr->pSubpasses, start );
	for (uint i = 0; (ptr->pSubpasses != null) and (i < ptr->subpassCount); ++i) {
		VUnpack_VkSubpassDescription( PtrCast<VkSubpassDescription>(ptr->pSubpasses + i), start );
	}
	VUnpackPointer( INOUT ptr->pDependencies, start );
	for (uint i = 0; (ptr->pDependencies != null) and (i < ptr->dependencyCount); ++i) {
		VUnpack_VkSubpassDependency( PtrCast<VkSubpassDependency>(ptr->pDependencies + i), start );
	}
}


void VUnpack_VkCommandPoolCreateInfo (VkCommandPoolCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkCommandBufferAllocateInfo (VkCommandBufferAllocateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkCommandBufferBeginInfo (VkCommandBufferBeginInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pInheritanceInfo, start );
	VUnpackStruct( PtrCast<VkBaseOutStructure>(ptr->pInheritanceInfo), start );
}


void VUnpack_VkBufferCopy (VkBufferCopy *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkImageSubresourceLayers (VkImageSubresourceLayers *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkImageBlit (VkImageBlit *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkBufferImageCopy (VkBufferImageCopy *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkClearColorValue (VkClearColorValue *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkClearDepthStencilValue (VkClearDepthStencilValue *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkClearAttachment (VkClearAttachment *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkClearRect (VkClearRect *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkViewportSwizzleNV (VkViewportSwizzleNV *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkBufferMemoryBarrier (VkBufferMemoryBarrier *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkImageMemoryBarrier (VkImageMemoryBarrier *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkPipelineCoverageToColorStateCreateInfoNV (VkPipelineCoverageToColorStateCreateInfoNV *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkBindBufferMemoryInfo (VkBindBufferMemoryInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkBindImageMemoryInfo (VkBindImageMemoryInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkSubpassEndInfoKHR (VkSubpassEndInfoKHR *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkMemoryDedicatedAllocateInfo (VkMemoryDedicatedAllocateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkMemoryAllocateFlagsInfo (VkMemoryAllocateFlagsInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkDeviceGroupRenderPassBeginInfo (VkDeviceGroupRenderPassBeginInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pDeviceRenderAreas, start );
	for (uint i = 0; (ptr->pDeviceRenderAreas != null) and (i < ptr->deviceRenderAreaCount); ++i) {
		VUnpack_VkRect2D( PtrCast<VkRect2D>(ptr->pDeviceRenderAreas + i), start );
	}
}


void VUnpack_VkDeviceGroupCommandBufferBeginInfo (VkDeviceGroupCommandBufferBeginInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkDeviceGroupSubmitInfo (VkDeviceGroupSubmitInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pWaitSemaphoreDeviceIndices, start );
	VUnpackPointer( INOUT ptr->pCommandBufferDeviceMasks, start );
	VUnpackPointer( INOUT ptr->pSignalSemaphoreDeviceIndices, start );
}


void VUnpack_VkDeviceGroupBindSparseInfo (VkDeviceGroupBindSparseInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkBindBufferMemoryDeviceGroupInfo (VkBindBufferMemoryDeviceGroupInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pDeviceIndices, start );
}


void VUnpack_VkBindImageMemoryDeviceGroupInfo (VkBindImageMemoryDeviceGroupInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pDeviceIndices, start );
	VUnpackPointer( INOUT ptr->pSplitInstanceBindRegions, start );
	for (uint i = 0; (ptr->pSplitInstanceBindRegions != null) and (i < ptr->splitInstanceBindRegionCount); ++i) {
		VUnpack_VkRect2D( PtrCast<VkRect2D>(ptr->pSplitInstanceBindRegions + i), start );
	}
}


void VUnpack_VkSamplerReductionModeCreateInfoEXT (VkSamplerReductionModeCreateInfoEXT *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkAttachmentReference2KHR (VkAttachmentReference2KHR *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkInputAttachmentAspectReference (VkInputAttachmentAspectReference *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkRenderPassInputAttachmentAspectCreateInfo (VkRenderPassInputAttachmentAspectCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pAspectReferences, start );
	for (uint i = 0; (ptr->pAspectReferences != null) and (i < ptr->aspectReferenceCount); ++i) {
		VUnpack_VkInputAttachmentAspectReference( PtrCast<VkInputAttachmentAspectReference>(ptr->pAspectReferences + i), start );
	}
}


void VUnpack_VkImageViewUsageCreateInfo (VkImageViewUsageCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkRenderPassMultiviewCreateInfo (VkRenderPassMultiviewCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pViewMasks, start );
	VUnpackPointer( INOUT ptr->pViewOffsets, start );
	VUnpackPointer( INOUT ptr->pCorrelationMasks, start );
}


void VUnpack_VkRenderPassSampleLocationsBeginInfoEXT (VkRenderPassSampleLocationsBeginInfoEXT *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pAttachmentInitialSampleLocations, start );
	for (uint i = 0; (ptr->pAttachmentInitialSampleLocations != null) and (i < ptr->attachmentInitialSampleLocationsCount); ++i) {
		VUnpack_VkAttachmentSampleLocationsEXT( PtrCast<VkAttachmentSampleLocationsEXT>(ptr->pAttachmentInitialSampleLocations + i), start );
	}
	VUnpackPointer( INOUT ptr->pPostSubpassSampleLocations, start );
	for (uint i = 0; (ptr->pPostSubpassSampleLocations != null) and (i < ptr->postSubpassSampleLocationsCount); ++i) {
		VUnpack_VkSubpassSampleLocationsEXT( PtrCast<VkSubpassSampleLocationsEXT>(ptr->pPostSubpassSampleLocations + i), start );
	}
}


void VUnpack_VkDeviceQueueInfo2 (VkDeviceQueueInfo2 *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkProtectedSubmitInfo (VkProtectedSubmitInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkSamplerYcbcrConversionCreateInfo (VkSamplerYcbcrConversionCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkBindImagePlaneMemoryInfo (VkBindImagePlaneMemoryInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkDescriptorUpdateTemplateCreateInfo (VkDescriptorUpdateTemplateCreateInfo *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pDescriptorUpdateEntries, start );
	for (uint i = 0; (ptr->pDescriptorUpdateEntries != null) and (i < ptr->descriptorUpdateEntryCount); ++i) {
		VUnpack_VkDescriptorUpdateTemplateEntry( PtrCast<VkDescriptorUpdateTemplateEntry>(ptr->pDescriptorUpdateEntries + i), start );
	}
}


void VUnpack_VkImageSwapchainCreateInfoKHR (VkImageSwapchainCreateInfoKHR *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkBindImageMemorySwapchainInfoKHR (VkBindImageMemorySwapchainInfoKHR *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkIndirectCommandsLayoutTokenNVX (VkIndirectCommandsLayoutTokenNVX *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkVertexInputBindingDivisorDescriptionEXT (VkVertexInputBindingDivisorDescriptionEXT *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkSubpassSampleLocationsEXT (VkSubpassSampleLocationsEXT *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkPipelineColorBlendAdvancedStateCreateInfoEXT (VkPipelineColorBlendAdvancedStateCreateInfoEXT *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkAttachmentDescription2KHR (VkAttachmentDescription2KHR *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkSubpassDescription2KHR (VkSubpassDescription2KHR *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pInputAttachments, start );
	for (uint i = 0; (ptr->pInputAttachments != null) and (i < ptr->inputAttachmentCount); ++i) {
		VUnpackStruct( PtrCast<VkBaseOutStructure>(ptr->pInputAttachments + i), start );
	}
	VUnpackPointer( INOUT ptr->pColorAttachments, start );
	for (uint i = 0; (ptr->pColorAttachments != null) and (i < ptr->colorAttachmentCount); ++i) {
		VUnpackStruct( PtrCast<VkBaseOutStructure>(ptr->pColorAttachments + i), start );
	}
	VUnpackPointer( INOUT ptr->pResolveAttachments, start );
	for (uint i = 0; (ptr->pResolveAttachments != null) and (i < ptr->colorAttachmentCount); ++i) {
		VUnpackStruct( PtrCast<VkBaseOutStructure>(ptr->pResolveAttachments + i), start );
	}
	VUnpackPointer( INOUT ptr->pDepthStencilAttachment, start );
	VUnpackStruct( PtrCast<VkBaseOutStructure>(ptr->pDepthStencilAttachment), start );
	VUnpackPointer( INOUT ptr->pPreserveAttachments, start );
}


void VUnpack_VkSubpassDependency2KHR (VkSubpassDependency2KHR *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkRenderPassCreateInfo2KHR (VkRenderPassCreateInfo2KHR *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pAttachments, start );
	for (uint i = 0; (ptr->pAttachments != null) and (i < ptr->attachmentCount); ++i) {
		VUnpackStruct( PtrCast<VkBaseOutStructure>(ptr->pAttachments + i), start );
	}
	VUnpackPointer( INOUT ptr->pSubpasses, start );
	for (uint i = 0; (ptr->pSubpasses != null) and (i < ptr->subpassCount); ++i) {
		VUnpackStruct( PtrCast<VkBaseOutStructure>(ptr->pSubpasses + i), start );
	}
	VUnpackPointer( INOUT ptr->pDependencies, start );
	for (uint i = 0; (ptr->pDependencies != null) and (i < ptr->dependencyCount); ++i) {
		VUnpackStruct( PtrCast<VkBaseOutStructure>(ptr->pDependencies + i), start );
	}
	VUnpackPointer( INOUT ptr->pCorrelatedViewMasks, start );
}


void VUnpack_VkSubpassBeginInfoKHR (VkSubpassBeginInfoKHR *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkDescriptorSetVariableDescriptorCountAllocateInfoEXT (VkDescriptorSetVariableDescriptorCountAllocateInfoEXT *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pDescriptorCounts, start );
}


void VUnpack_VkPipelineRasterizationStateRasterizationOrderAMD (VkPipelineRasterizationStateRasterizationOrderAMD *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkDebugMarkerObjectNameInfoEXT (VkDebugMarkerObjectNameInfoEXT *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pObjectName, start );
}


void VUnpack_VkDebugMarkerMarkerInfoEXT (VkDebugMarkerMarkerInfoEXT *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pMarkerName, start );
}


void VUnpack_VkDedicatedAllocationImageCreateInfoNV (VkDedicatedAllocationImageCreateInfoNV *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkDedicatedAllocationBufferCreateInfoNV (VkDedicatedAllocationBufferCreateInfoNV *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkDedicatedAllocationMemoryAllocateInfoNV (VkDedicatedAllocationMemoryAllocateInfoNV *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkImageViewASTCDecodeModeEXT (VkImageViewASTCDecodeModeEXT *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkConditionalRenderingBeginInfoEXT (VkConditionalRenderingBeginInfoEXT *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkCommandBufferInheritanceConditionalRenderingInfoEXT (VkCommandBufferInheritanceConditionalRenderingInfoEXT *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkIndirectCommandsTokenNVX (VkIndirectCommandsTokenNVX *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkIndirectCommandsLayoutCreateInfoNVX (VkIndirectCommandsLayoutCreateInfoNVX *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pTokens, start );
	for (uint i = 0; (ptr->pTokens != null) and (i < ptr->tokenCount); ++i) {
		VUnpack_VkIndirectCommandsLayoutTokenNVX( PtrCast<VkIndirectCommandsLayoutTokenNVX>(ptr->pTokens + i), start );
	}
}


void VUnpack_VkCmdProcessCommandsInfoNVX (VkCmdProcessCommandsInfoNVX *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pIndirectCommandsTokens, start );
	for (uint i = 0; (ptr->pIndirectCommandsTokens != null) and (i < ptr->indirectCommandsTokenCount); ++i) {
		VUnpack_VkIndirectCommandsTokenNVX( PtrCast<VkIndirectCommandsTokenNVX>(ptr->pIndirectCommandsTokens + i), start );
	}
}


void VUnpack_VkCmdReserveSpaceForCommandsInfoNVX (VkCmdReserveSpaceForCommandsInfoNVX *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkObjectTableCreateInfoNVX (VkObjectTableCreateInfoNVX *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pObjectEntryTypes, start );
	VUnpackPointer( INOUT ptr->pObjectEntryCounts, start );
	VUnpackPointer( INOUT ptr->pObjectEntryUsageFlags, start );
}


void VUnpack_VkObjectTableEntryNVX (VkObjectTableEntryNVX *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkViewportWScalingNV (VkViewportWScalingNV *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkPipelineViewportWScalingStateCreateInfoNV (VkPipelineViewportWScalingStateCreateInfoNV *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pViewportWScalings, start );
	for (uint i = 0; (ptr->pViewportWScalings != null) and (i < ptr->viewportCount); ++i) {
		VUnpack_VkViewportWScalingNV( PtrCast<VkViewportWScalingNV>(ptr->pViewportWScalings + i), start );
	}
}


void VUnpack_VkPipelineViewportSwizzleStateCreateInfoNV (VkPipelineViewportSwizzleStateCreateInfoNV *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pViewportSwizzles, start );
	for (uint i = 0; (ptr->pViewportSwizzles != null) and (i < ptr->viewportCount); ++i) {
		VUnpack_VkViewportSwizzleNV( PtrCast<VkViewportSwizzleNV>(ptr->pViewportSwizzles + i), start );
	}
}


void VUnpack_VkPipelineDiscardRectangleStateCreateInfoEXT (VkPipelineDiscardRectangleStateCreateInfoEXT *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pDiscardRectangles, start );
	for (uint i = 0; (ptr->pDiscardRectangles != null) and (i < ptr->discardRectangleCount); ++i) {
		VUnpack_VkRect2D( PtrCast<VkRect2D>(ptr->pDiscardRectangles + i), start );
	}
}


void VUnpack_VkPipelineRasterizationConservativeStateCreateInfoEXT (VkPipelineRasterizationConservativeStateCreateInfoEXT *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkWriteDescriptorSetInlineUniformBlockEXT (VkWriteDescriptorSetInlineUniformBlockEXT *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pData, start );
}


void VUnpack_VkDescriptorPoolInlineUniformBlockCreateInfoEXT (VkDescriptorPoolInlineUniformBlockCreateInfoEXT *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkSampleLocationEXT (VkSampleLocationEXT *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkSampleLocationsInfoEXT (VkSampleLocationsInfoEXT *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pSampleLocations, start );
	for (uint i = 0; (ptr->pSampleLocations != null) and (i < ptr->sampleLocationsCount); ++i) {
		VUnpack_VkSampleLocationEXT( PtrCast<VkSampleLocationEXT>(ptr->pSampleLocations + i), start );
	}
}


void VUnpack_VkAttachmentSampleLocationsEXT (VkAttachmentSampleLocationsEXT *ptr, void *start)
{
	if ( ptr == null ) return;
}


void VUnpack_VkPipelineSampleLocationsStateCreateInfoEXT (VkPipelineSampleLocationsStateCreateInfoEXT *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
}


void VUnpack_VkPipelineCoverageModulationStateCreateInfoNV (VkPipelineCoverageModulationStateCreateInfoNV *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pCoverageModulationTable, start );
}


void VUnpack_VkPipelineVertexInputDivisorStateCreateInfoEXT (VkPipelineVertexInputDivisorStateCreateInfoEXT *ptr, void *start)
{
	if ( ptr == null ) return;
	VUnpackPointer( INOUT ptr->pNext, start );
	VUnpackPointer( INOUT ptr->pVertexBindingDivisors, start );
	for (uint i = 0; (ptr->pVertexBindingDivisors != null) and (i < ptr->vertexBindingDivisorCount); ++i) {
		VUnpack_VkVertexInputBindingDivisorDescriptionEXT( PtrCast<VkVertexInputBindingDivisorDescriptionEXT>(ptr->pVertexBindingDivisors + i), start );
	}
}


