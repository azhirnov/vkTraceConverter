// auto-generated file

void VUnpackStruct (VkBaseOutStructure *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	switch ( ptr->sType )
	{
		case VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO : {
			VkSemaphoreCreateInfo*  obj = BitCast<VkSemaphoreCreateInfo*>( ptr );
			VUnpack_VkSemaphoreCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_COARSE_SAMPLE_ORDER_STATE_CREATE_INFO_NV : {
			VkPipelineViewportCoarseSampleOrderStateCreateInfoNV*  obj = BitCast<VkPipelineViewportCoarseSampleOrderStateCreateInfoNV*>( ptr );
			VUnpack_VkPipelineViewportCoarseSampleOrderStateCreateInfoNV( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_DOMAIN_ORIGIN_STATE_CREATE_INFO : {
			VkPipelineTessellationDomainOriginStateCreateInfo*  obj = BitCast<VkPipelineTessellationDomainOriginStateCreateInfo*>( ptr );
			VUnpack_VkPipelineTessellationDomainOriginStateCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO : {
			VkBufferViewCreateInfo*  obj = BitCast<VkBufferViewCreateInfo*>( ptr );
			VUnpack_VkBufferViewCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_MEMORY_BARRIER : {
			VkMemoryBarrier*  obj = BitCast<VkMemoryBarrier*>( ptr );
			VUnpack_VkMemoryBarrier( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO : {
			VkPipelineInputAssemblyStateCreateInfo*  obj = BitCast<VkPipelineInputAssemblyStateCreateInfo*>( ptr );
			VUnpack_VkPipelineInputAssemblyStateCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO_KHR : {
			VkImageFormatListCreateInfoKHR*  obj = BitCast<VkImageFormatListCreateInfoKHR*>( ptr );
			VUnpack_VkImageFormatListCreateInfoKHR( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE : {
			VkMappedMemoryRange*  obj = BitCast<VkMappedMemoryRange*>( ptr );
			VUnpack_VkMappedMemoryRange( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_SUBMIT_INFO : {
			VkSubmitInfo*  obj = BitCast<VkSubmitInfo*>( ptr );
			VUnpack_VkSubmitInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO : {
			VkPipelineDynamicStateCreateInfo*  obj = BitCast<VkPipelineDynamicStateCreateInfo*>( ptr );
			VUnpack_VkPipelineDynamicStateCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO : {
			VkImageViewCreateInfo*  obj = BitCast<VkImageViewCreateInfo*>( ptr );
			VUnpack_VkImageViewCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO : {
			VkPipelineTessellationStateCreateInfo*  obj = BitCast<VkPipelineTessellationStateCreateInfo*>( ptr );
			VUnpack_VkPipelineTessellationStateCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO : {
			VkMemoryAllocateInfo*  obj = BitCast<VkMemoryAllocateInfo*>( ptr );
			VUnpack_VkMemoryAllocateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_BIND_SPARSE_INFO : {
			VkBindSparseInfo*  obj = BitCast<VkBindSparseInfo*>( ptr );
			VUnpack_VkBindSparseInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO : {
			VkPipelineViewportStateCreateInfo*  obj = BitCast<VkPipelineViewportStateCreateInfo*>( ptr );
			VUnpack_VkPipelineViewportStateCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO : {
			VkPipelineVertexInputStateCreateInfo*  obj = BitCast<VkPipelineVertexInputStateCreateInfo*>( ptr );
			VUnpack_VkPipelineVertexInputStateCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_FENCE_CREATE_INFO : {
			VkFenceCreateInfo*  obj = BitCast<VkFenceCreateInfo*>( ptr );
			VUnpack_VkFenceCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_EVENT_CREATE_INFO : {
			VkEventCreateInfo*  obj = BitCast<VkEventCreateInfo*>( ptr );
			VUnpack_VkEventCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO : {
			VkRenderPassBeginInfo*  obj = BitCast<VkRenderPassBeginInfo*>( ptr );
			VUnpack_VkRenderPassBeginInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO : {
			VkQueryPoolCreateInfo*  obj = BitCast<VkQueryPoolCreateInfo*>( ptr );
			VUnpack_VkQueryPoolCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO : {
			VkBufferCreateInfo*  obj = BitCast<VkBufferCreateInfo*>( ptr );
			VUnpack_VkBufferCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO : {
			VkImageCreateInfo*  obj = BitCast<VkImageCreateInfo*>( ptr );
			VUnpack_VkImageCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO : {
			VkPipelineMultisampleStateCreateInfo*  obj = BitCast<VkPipelineMultisampleStateCreateInfo*>( ptr );
			VUnpack_VkPipelineMultisampleStateCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO : {
			VkShaderModuleCreateInfo*  obj = BitCast<VkShaderModuleCreateInfo*>( ptr );
			VUnpack_VkShaderModuleCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO_EXT : {
			VkDescriptorSetLayoutBindingFlagsCreateInfoEXT*  obj = BitCast<VkDescriptorSetLayoutBindingFlagsCreateInfoEXT*>( ptr );
			VUnpack_VkDescriptorSetLayoutBindingFlagsCreateInfoEXT( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO : {
			VkPipelineCacheCreateInfo*  obj = BitCast<VkPipelineCacheCreateInfo*>( ptr );
			VUnpack_VkPipelineCacheCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO : {
			VkPipelineShaderStageCreateInfo*  obj = BitCast<VkPipelineShaderStageCreateInfo*>( ptr );
			VUnpack_VkPipelineShaderStageCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO : {
			VkPipelineRasterizationStateCreateInfo*  obj = BitCast<VkPipelineRasterizationStateCreateInfo*>( ptr );
			VUnpack_VkPipelineRasterizationStateCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO : {
			VkPipelineDepthStencilStateCreateInfo*  obj = BitCast<VkPipelineDepthStencilStateCreateInfo*>( ptr );
			VUnpack_VkPipelineDepthStencilStateCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO : {
			VkCommandBufferInheritanceInfo*  obj = BitCast<VkCommandBufferInheritanceInfo*>( ptr );
			VUnpack_VkCommandBufferInheritanceInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO : {
			VkPipelineColorBlendStateCreateInfo*  obj = BitCast<VkPipelineColorBlendStateCreateInfo*>( ptr );
			VUnpack_VkPipelineColorBlendStateCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO : {
			VkGraphicsPipelineCreateInfo*  obj = BitCast<VkGraphicsPipelineCreateInfo*>( ptr );
			VUnpack_VkGraphicsPipelineCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_INFO : {
			VkSamplerYcbcrConversionInfo*  obj = BitCast<VkSamplerYcbcrConversionInfo*>( ptr );
			VUnpack_VkSamplerYcbcrConversionInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO : {
			VkComputePipelineCreateInfo*  obj = BitCast<VkComputePipelineCreateInfo*>( ptr );
			VUnpack_VkComputePipelineCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO : {
			VkPipelineLayoutCreateInfo*  obj = BitCast<VkPipelineLayoutCreateInfo*>( ptr );
			VUnpack_VkPipelineLayoutCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO : {
			VkSamplerCreateInfo*  obj = BitCast<VkSamplerCreateInfo*>( ptr );
			VUnpack_VkSamplerCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO : {
			VkDescriptorSetLayoutCreateInfo*  obj = BitCast<VkDescriptorSetLayoutCreateInfo*>( ptr );
			VUnpack_VkDescriptorSetLayoutCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO : {
			VkDescriptorPoolCreateInfo*  obj = BitCast<VkDescriptorPoolCreateInfo*>( ptr );
			VUnpack_VkDescriptorPoolCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO : {
			VkDescriptorSetAllocateInfo*  obj = BitCast<VkDescriptorSetAllocateInfo*>( ptr );
			VUnpack_VkDescriptorSetAllocateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET : {
			VkWriteDescriptorSet*  obj = BitCast<VkWriteDescriptorSet*>( ptr );
			VUnpack_VkWriteDescriptorSet( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET : {
			VkCopyDescriptorSet*  obj = BitCast<VkCopyDescriptorSet*>( ptr );
			VUnpack_VkCopyDescriptorSet( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO : {
			VkFramebufferCreateInfo*  obj = BitCast<VkFramebufferCreateInfo*>( ptr );
			VUnpack_VkFramebufferCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO : {
			VkRenderPassCreateInfo*  obj = BitCast<VkRenderPassCreateInfo*>( ptr );
			VUnpack_VkRenderPassCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO : {
			VkCommandPoolCreateInfo*  obj = BitCast<VkCommandPoolCreateInfo*>( ptr );
			VUnpack_VkCommandPoolCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO : {
			VkCommandBufferAllocateInfo*  obj = BitCast<VkCommandBufferAllocateInfo*>( ptr );
			VUnpack_VkCommandBufferAllocateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO : {
			VkCommandBufferBeginInfo*  obj = BitCast<VkCommandBufferBeginInfo*>( ptr );
			VUnpack_VkCommandBufferBeginInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER : {
			VkBufferMemoryBarrier*  obj = BitCast<VkBufferMemoryBarrier*>( ptr );
			VUnpack_VkBufferMemoryBarrier( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER : {
			VkImageMemoryBarrier*  obj = BitCast<VkImageMemoryBarrier*>( ptr );
			VUnpack_VkImageMemoryBarrier( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_TO_COLOR_STATE_CREATE_INFO_NV : {
			VkPipelineCoverageToColorStateCreateInfoNV*  obj = BitCast<VkPipelineCoverageToColorStateCreateInfoNV*>( ptr );
			VUnpack_VkPipelineCoverageToColorStateCreateInfoNV( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO : {
			VkBindBufferMemoryInfo*  obj = BitCast<VkBindBufferMemoryInfo*>( ptr );
			VUnpack_VkBindBufferMemoryInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO : {
			VkBindImageMemoryInfo*  obj = BitCast<VkBindImageMemoryInfo*>( ptr );
			VUnpack_VkBindImageMemoryInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_SUBPASS_END_INFO_KHR : {
			VkSubpassEndInfoKHR*  obj = BitCast<VkSubpassEndInfoKHR*>( ptr );
			VUnpack_VkSubpassEndInfoKHR( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO : {
			VkMemoryDedicatedAllocateInfo*  obj = BitCast<VkMemoryDedicatedAllocateInfo*>( ptr );
			VUnpack_VkMemoryDedicatedAllocateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO : {
			VkMemoryAllocateFlagsInfo*  obj = BitCast<VkMemoryAllocateFlagsInfo*>( ptr );
			VUnpack_VkMemoryAllocateFlagsInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_DEVICE_GROUP_RENDER_PASS_BEGIN_INFO : {
			VkDeviceGroupRenderPassBeginInfo*  obj = BitCast<VkDeviceGroupRenderPassBeginInfo*>( ptr );
			VUnpack_VkDeviceGroupRenderPassBeginInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_DEVICE_GROUP_COMMAND_BUFFER_BEGIN_INFO : {
			VkDeviceGroupCommandBufferBeginInfo*  obj = BitCast<VkDeviceGroupCommandBufferBeginInfo*>( ptr );
			VUnpack_VkDeviceGroupCommandBufferBeginInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_DEVICE_GROUP_SUBMIT_INFO : {
			VkDeviceGroupSubmitInfo*  obj = BitCast<VkDeviceGroupSubmitInfo*>( ptr );
			VUnpack_VkDeviceGroupSubmitInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_DEVICE_GROUP_BIND_SPARSE_INFO : {
			VkDeviceGroupBindSparseInfo*  obj = BitCast<VkDeviceGroupBindSparseInfo*>( ptr );
			VUnpack_VkDeviceGroupBindSparseInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_DEVICE_GROUP_INFO : {
			VkBindBufferMemoryDeviceGroupInfo*  obj = BitCast<VkBindBufferMemoryDeviceGroupInfo*>( ptr );
			VUnpack_VkBindBufferMemoryDeviceGroupInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_DEVICE_GROUP_INFO : {
			VkBindImageMemoryDeviceGroupInfo*  obj = BitCast<VkBindImageMemoryDeviceGroupInfo*>( ptr );
			VUnpack_VkBindImageMemoryDeviceGroupInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_SAMPLER_REDUCTION_MODE_CREATE_INFO_EXT : {
			VkSamplerReductionModeCreateInfoEXT*  obj = BitCast<VkSamplerReductionModeCreateInfoEXT*>( ptr );
			VUnpack_VkSamplerReductionModeCreateInfoEXT( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2_KHR : {
			VkAttachmentReference2KHR*  obj = BitCast<VkAttachmentReference2KHR*>( ptr );
			VUnpack_VkAttachmentReference2KHR( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_RENDER_PASS_INPUT_ATTACHMENT_ASPECT_CREATE_INFO : {
			VkRenderPassInputAttachmentAspectCreateInfo*  obj = BitCast<VkRenderPassInputAttachmentAspectCreateInfo*>( ptr );
			VUnpack_VkRenderPassInputAttachmentAspectCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO : {
			VkImageViewUsageCreateInfo*  obj = BitCast<VkImageViewUsageCreateInfo*>( ptr );
			VUnpack_VkImageViewUsageCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_RENDER_PASS_MULTIVIEW_CREATE_INFO : {
			VkRenderPassMultiviewCreateInfo*  obj = BitCast<VkRenderPassMultiviewCreateInfo*>( ptr );
			VUnpack_VkRenderPassMultiviewCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_RENDER_PASS_SAMPLE_LOCATIONS_BEGIN_INFO_EXT : {
			VkRenderPassSampleLocationsBeginInfoEXT*  obj = BitCast<VkRenderPassSampleLocationsBeginInfoEXT*>( ptr );
			VUnpack_VkRenderPassSampleLocationsBeginInfoEXT( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2 : {
			VkDeviceQueueInfo2*  obj = BitCast<VkDeviceQueueInfo2*>( ptr );
			VUnpack_VkDeviceQueueInfo2( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_PROTECTED_SUBMIT_INFO : {
			VkProtectedSubmitInfo*  obj = BitCast<VkProtectedSubmitInfo*>( ptr );
			VUnpack_VkProtectedSubmitInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_CREATE_INFO : {
			VkSamplerYcbcrConversionCreateInfo*  obj = BitCast<VkSamplerYcbcrConversionCreateInfo*>( ptr );
			VUnpack_VkSamplerYcbcrConversionCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_BIND_IMAGE_PLANE_MEMORY_INFO : {
			VkBindImagePlaneMemoryInfo*  obj = BitCast<VkBindImagePlaneMemoryInfo*>( ptr );
			VUnpack_VkBindImagePlaneMemoryInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_CREATE_INFO : {
			VkDescriptorUpdateTemplateCreateInfo*  obj = BitCast<VkDescriptorUpdateTemplateCreateInfo*>( ptr );
			VUnpack_VkDescriptorUpdateTemplateCreateInfo( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_IMAGE_SWAPCHAIN_CREATE_INFO_KHR : {
			VkImageSwapchainCreateInfoKHR*  obj = BitCast<VkImageSwapchainCreateInfoKHR*>( ptr );
			VUnpack_VkImageSwapchainCreateInfoKHR( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_SWAPCHAIN_INFO_KHR : {
			VkBindImageMemorySwapchainInfoKHR*  obj = BitCast<VkBindImageMemorySwapchainInfoKHR*>( ptr );
			VUnpack_VkBindImageMemorySwapchainInfoKHR( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_ADVANCED_STATE_CREATE_INFO_EXT : {
			VkPipelineColorBlendAdvancedStateCreateInfoEXT*  obj = BitCast<VkPipelineColorBlendAdvancedStateCreateInfoEXT*>( ptr );
			VUnpack_VkPipelineColorBlendAdvancedStateCreateInfoEXT( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_2_KHR : {
			VkAttachmentDescription2KHR*  obj = BitCast<VkAttachmentDescription2KHR*>( ptr );
			VUnpack_VkAttachmentDescription2KHR( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_2_KHR : {
			VkSubpassDescription2KHR*  obj = BitCast<VkSubpassDescription2KHR*>( ptr );
			VUnpack_VkSubpassDescription2KHR( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_SUBPASS_DEPENDENCY_2_KHR : {
			VkSubpassDependency2KHR*  obj = BitCast<VkSubpassDependency2KHR*>( ptr );
			VUnpack_VkSubpassDependency2KHR( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO_2_KHR : {
			VkRenderPassCreateInfo2KHR*  obj = BitCast<VkRenderPassCreateInfo2KHR*>( ptr );
			VUnpack_VkRenderPassCreateInfo2KHR( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_SUBPASS_BEGIN_INFO_KHR : {
			VkSubpassBeginInfoKHR*  obj = BitCast<VkSubpassBeginInfoKHR*>( ptr );
			VUnpack_VkSubpassBeginInfoKHR( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_ALLOCATE_INFO_EXT : {
			VkDescriptorSetVariableDescriptorCountAllocateInfoEXT*  obj = BitCast<VkDescriptorSetVariableDescriptorCountAllocateInfoEXT*>( ptr );
			VUnpack_VkDescriptorSetVariableDescriptorCountAllocateInfoEXT( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_RASTERIZATION_ORDER_AMD : {
			VkPipelineRasterizationStateRasterizationOrderAMD*  obj = BitCast<VkPipelineRasterizationStateRasterizationOrderAMD*>( ptr );
			VUnpack_VkPipelineRasterizationStateRasterizationOrderAMD( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_NAME_INFO_EXT : {
			VkDebugMarkerObjectNameInfoEXT*  obj = BitCast<VkDebugMarkerObjectNameInfoEXT*>( ptr );
			VUnpack_VkDebugMarkerObjectNameInfoEXT( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_DEBUG_MARKER_MARKER_INFO_EXT : {
			VkDebugMarkerMarkerInfoEXT*  obj = BitCast<VkDebugMarkerMarkerInfoEXT*>( ptr );
			VUnpack_VkDebugMarkerMarkerInfoEXT( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_IMAGE_CREATE_INFO_NV : {
			VkDedicatedAllocationImageCreateInfoNV*  obj = BitCast<VkDedicatedAllocationImageCreateInfoNV*>( ptr );
			VUnpack_VkDedicatedAllocationImageCreateInfoNV( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_BUFFER_CREATE_INFO_NV : {
			VkDedicatedAllocationBufferCreateInfoNV*  obj = BitCast<VkDedicatedAllocationBufferCreateInfoNV*>( ptr );
			VUnpack_VkDedicatedAllocationBufferCreateInfoNV( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_MEMORY_ALLOCATE_INFO_NV : {
			VkDedicatedAllocationMemoryAllocateInfoNV*  obj = BitCast<VkDedicatedAllocationMemoryAllocateInfoNV*>( ptr );
			VUnpack_VkDedicatedAllocationMemoryAllocateInfoNV( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_IMAGE_VIEW_ASTC_DECODE_MODE_EXT : {
			VkImageViewASTCDecodeModeEXT*  obj = BitCast<VkImageViewASTCDecodeModeEXT*>( ptr );
			VUnpack_VkImageViewASTCDecodeModeEXT( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_CONDITIONAL_RENDERING_INFO_EXT : {
			VkCommandBufferInheritanceConditionalRenderingInfoEXT*  obj = BitCast<VkCommandBufferInheritanceConditionalRenderingInfoEXT*>( ptr );
			VUnpack_VkCommandBufferInheritanceConditionalRenderingInfoEXT( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_EXCLUSIVE_SCISSOR_STATE_CREATE_INFO_NV : {
			VkPipelineViewportExclusiveScissorStateCreateInfoNV*  obj = BitCast<VkPipelineViewportExclusiveScissorStateCreateInfoNV*>( ptr );
			VUnpack_VkPipelineViewportExclusiveScissorStateCreateInfoNV( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_W_SCALING_STATE_CREATE_INFO_NV : {
			VkPipelineViewportWScalingStateCreateInfoNV*  obj = BitCast<VkPipelineViewportWScalingStateCreateInfoNV*>( ptr );
			VUnpack_VkPipelineViewportWScalingStateCreateInfoNV( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_SWIZZLE_STATE_CREATE_INFO_NV : {
			VkPipelineViewportSwizzleStateCreateInfoNV*  obj = BitCast<VkPipelineViewportSwizzleStateCreateInfoNV*>( ptr );
			VUnpack_VkPipelineViewportSwizzleStateCreateInfoNV( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_DISCARD_RECTANGLE_STATE_CREATE_INFO_EXT : {
			VkPipelineDiscardRectangleStateCreateInfoEXT*  obj = BitCast<VkPipelineDiscardRectangleStateCreateInfoEXT*>( ptr );
			VUnpack_VkPipelineDiscardRectangleStateCreateInfoEXT( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_CONSERVATIVE_STATE_CREATE_INFO_EXT : {
			VkPipelineRasterizationConservativeStateCreateInfoEXT*  obj = BitCast<VkPipelineRasterizationConservativeStateCreateInfoEXT*>( ptr );
			VUnpack_VkPipelineRasterizationConservativeStateCreateInfoEXT( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_INLINE_UNIFORM_BLOCK_EXT : {
			VkWriteDescriptorSetInlineUniformBlockEXT*  obj = BitCast<VkWriteDescriptorSetInlineUniformBlockEXT*>( ptr );
			VUnpack_VkWriteDescriptorSetInlineUniformBlockEXT( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_SHADING_RATE_IMAGE_STATE_CREATE_INFO_NV : {
			VkPipelineViewportShadingRateImageStateCreateInfoNV*  obj = BitCast<VkPipelineViewportShadingRateImageStateCreateInfoNV*>( ptr );
			VUnpack_VkPipelineViewportShadingRateImageStateCreateInfoNV( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_INLINE_UNIFORM_BLOCK_CREATE_INFO_EXT : {
			VkDescriptorPoolInlineUniformBlockCreateInfoEXT*  obj = BitCast<VkDescriptorPoolInlineUniformBlockCreateInfoEXT*>( ptr );
			VUnpack_VkDescriptorPoolInlineUniformBlockCreateInfoEXT( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_SAMPLE_LOCATIONS_INFO_EXT : {
			VkSampleLocationsInfoEXT*  obj = BitCast<VkSampleLocationsInfoEXT*>( ptr );
			VUnpack_VkSampleLocationsInfoEXT( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_SAMPLE_LOCATIONS_STATE_CREATE_INFO_EXT : {
			VkPipelineSampleLocationsStateCreateInfoEXT*  obj = BitCast<VkPipelineSampleLocationsStateCreateInfoEXT*>( ptr );
			VUnpack_VkPipelineSampleLocationsStateCreateInfoEXT( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_MODULATION_STATE_CREATE_INFO_NV : {
			VkPipelineCoverageModulationStateCreateInfoNV*  obj = BitCast<VkPipelineCoverageModulationStateCreateInfoNV*>( ptr );
			VUnpack_VkPipelineCoverageModulationStateCreateInfoNV( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_REPRESENTATIVE_FRAGMENT_TEST_STATE_CREATE_INFO_NV : {
			VkPipelineRepresentativeFragmentTestStateCreateInfoNV*  obj = BitCast<VkPipelineRepresentativeFragmentTestStateCreateInfoNV*>( ptr );
			VUnpack_VkPipelineRepresentativeFragmentTestStateCreateInfoNV( obj, unpacker );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_DIVISOR_STATE_CREATE_INFO_EXT : {
			VkPipelineVertexInputDivisorStateCreateInfoEXT*  obj = BitCast<VkPipelineVertexInputDivisorStateCreateInfoEXT*>( ptr );
			VUnpack_VkPipelineVertexInputDivisorStateCreateInfoEXT( obj, unpacker );
			break;
		}

	}
}

void VUnpack_VkSemaphoreCreateInfo (VkSemaphoreCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkPipelineViewportCoarseSampleOrderStateCreateInfoNV (VkPipelineViewportCoarseSampleOrderStateCreateInfoNV *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pCustomSampleOrders );
	for (uint i = 0; (ptr->pCustomSampleOrders != null) and (i < ptr->customSampleOrderCount); ++i) {
		VUnpack_VkCoarseSampleOrderCustomNV( const_cast<VkCoarseSampleOrderCustomNV*>(ptr->pCustomSampleOrders + i), unpacker );
	}
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkDescriptorUpdateTemplateEntry (VkDescriptorUpdateTemplateEntry *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
}


void VUnpack_VkPipelineTessellationDomainOriginStateCreateInfo (VkPipelineTessellationDomainOriginStateCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkBufferViewCreateInfo (VkBufferViewCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.RemapVkResources( INOUT &ptr->buffer, 1 );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkMemoryBarrier (VkMemoryBarrier *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkPipelineColorBlendAttachmentState (VkPipelineColorBlendAttachmentState *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
}


void VUnpack_VkAllocationCallbacks (VkAllocationCallbacks *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pUserData );
}


void VUnpack_VkPipelineInputAssemblyStateCreateInfo (VkPipelineInputAssemblyStateCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkExtent3D (VkExtent3D *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
}


void VUnpack_VkSparseBufferMemoryBindInfo (VkSparseBufferMemoryBindInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.RemapVkResources( INOUT &ptr->buffer, 1 );
	unpacker.UnpackPtr( INOUT ptr->pBinds );
	for (uint i = 0; (ptr->pBinds != null) and (i < ptr->bindCount); ++i) {
		VUnpack_VkSparseMemoryBind( const_cast<VkSparseMemoryBind*>(ptr->pBinds + i), unpacker );
	}
}


void VUnpack_VkImageFormatListCreateInfoKHR (VkImageFormatListCreateInfoKHR *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pViewFormats );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkOffset2D (VkOffset2D *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
}


void VUnpack_VkMappedMemoryRange (VkMappedMemoryRange *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.RemapVkResources( INOUT &ptr->memory, 1 );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkSubmitInfo (VkSubmitInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pWaitSemaphores );
	unpacker.RemapVkResources( INOUT ptr->pWaitSemaphores, ptr->waitSemaphoreCount );
	unpacker.UnpackPtr( INOUT ptr->pWaitDstStageMask );
	unpacker.UnpackPtr( INOUT ptr->pCommandBuffers );
	unpacker.RemapVkResources( INOUT ptr->pCommandBuffers, ptr->commandBufferCount );
	unpacker.UnpackPtr( INOUT ptr->pSignalSemaphores );
	unpacker.RemapVkResources( INOUT ptr->pSignalSemaphores, ptr->signalSemaphoreCount );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkPipelineDynamicStateCreateInfo (VkPipelineDynamicStateCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pDynamicStates );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkSparseMemoryBind (VkSparseMemoryBind *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.RemapVkResources( INOUT &ptr->memory, 1 );
}


void VUnpack_VkImageViewCreateInfo (VkImageViewCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.RemapVkResources( INOUT &ptr->image, 1 );
	VUnpack_VkComponentMapping( &ptr->components, unpacker );
	VUnpack_VkImageSubresourceRange( &ptr->subresourceRange, unpacker );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkPipelineTessellationStateCreateInfo (VkPipelineTessellationStateCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkMemoryAllocateInfo (VkMemoryAllocateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkSpecializationMapEntry (VkSpecializationMapEntry *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
}


void VUnpack_VkComponentMapping (VkComponentMapping *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
}


void VUnpack_VkImageResolve (VkImageResolve *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	VUnpack_VkImageSubresourceLayers( &ptr->srcSubresource, unpacker );
	VUnpack_VkOffset3D( &ptr->srcOffset, unpacker );
	VUnpack_VkImageSubresourceLayers( &ptr->dstSubresource, unpacker );
	VUnpack_VkOffset3D( &ptr->dstOffset, unpacker );
	VUnpack_VkExtent3D( &ptr->extent, unpacker );
}


void VUnpack_VkBindSparseInfo (VkBindSparseInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pWaitSemaphores );
	unpacker.RemapVkResources( INOUT ptr->pWaitSemaphores, ptr->waitSemaphoreCount );
	unpacker.UnpackPtr( INOUT ptr->pBufferBinds );
	for (uint i = 0; (ptr->pBufferBinds != null) and (i < ptr->bufferBindCount); ++i) {
		VUnpack_VkSparseBufferMemoryBindInfo( const_cast<VkSparseBufferMemoryBindInfo*>(ptr->pBufferBinds + i), unpacker );
	}
	unpacker.UnpackPtr( INOUT ptr->pImageOpaqueBinds );
	for (uint i = 0; (ptr->pImageOpaqueBinds != null) and (i < ptr->imageOpaqueBindCount); ++i) {
		VUnpack_VkSparseImageOpaqueMemoryBindInfo( const_cast<VkSparseImageOpaqueMemoryBindInfo*>(ptr->pImageOpaqueBinds + i), unpacker );
	}
	unpacker.UnpackPtr( INOUT ptr->pImageBinds );
	for (uint i = 0; (ptr->pImageBinds != null) and (i < ptr->imageBindCount); ++i) {
		VUnpack_VkSparseImageMemoryBindInfo( const_cast<VkSparseImageMemoryBindInfo*>(ptr->pImageBinds + i), unpacker );
	}
	unpacker.UnpackPtr( INOUT ptr->pSignalSemaphores );
	unpacker.RemapVkResources( INOUT ptr->pSignalSemaphores, ptr->signalSemaphoreCount );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkSparseImageOpaqueMemoryBindInfo (VkSparseImageOpaqueMemoryBindInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.RemapVkResources( INOUT &ptr->image, 1 );
	unpacker.UnpackPtr( INOUT ptr->pBinds );
	for (uint i = 0; (ptr->pBinds != null) and (i < ptr->bindCount); ++i) {
		VUnpack_VkSparseMemoryBind( const_cast<VkSparseMemoryBind*>(ptr->pBinds + i), unpacker );
	}
}


void VUnpack_VkPipelineViewportStateCreateInfo (VkPipelineViewportStateCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pViewports );
	for (uint i = 0; (ptr->pViewports != null) and (i < ptr->viewportCount); ++i) {
		VUnpack_VkViewport( const_cast<VkViewport*>(ptr->pViewports + i), unpacker );
	}
	unpacker.UnpackPtr( INOUT ptr->pScissors );
	for (uint i = 0; (ptr->pScissors != null) and (i < ptr->scissorCount); ++i) {
		VUnpack_VkRect2D( const_cast<VkRect2D*>(ptr->pScissors + i), unpacker );
	}
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkPipelineVertexInputStateCreateInfo (VkPipelineVertexInputStateCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pVertexBindingDescriptions );
	for (uint i = 0; (ptr->pVertexBindingDescriptions != null) and (i < ptr->vertexBindingDescriptionCount); ++i) {
		VUnpack_VkVertexInputBindingDescription( const_cast<VkVertexInputBindingDescription*>(ptr->pVertexBindingDescriptions + i), unpacker );
	}
	unpacker.UnpackPtr( INOUT ptr->pVertexAttributeDescriptions );
	for (uint i = 0; (ptr->pVertexAttributeDescriptions != null) and (i < ptr->vertexAttributeDescriptionCount); ++i) {
		VUnpack_VkVertexInputAttributeDescription( const_cast<VkVertexInputAttributeDescription*>(ptr->pVertexAttributeDescriptions + i), unpacker );
	}
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkImageSubresource (VkImageSubresource *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
}


void VUnpack_VkOffset3D (VkOffset3D *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
}


void VUnpack_VkSparseImageMemoryBind (VkSparseImageMemoryBind *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	VUnpack_VkImageSubresource( &ptr->subresource, unpacker );
	VUnpack_VkOffset3D( &ptr->offset, unpacker );
	VUnpack_VkExtent3D( &ptr->extent, unpacker );
	unpacker.RemapVkResources( INOUT &ptr->memory, 1 );
}


void VUnpack_VkSparseImageMemoryBindInfo (VkSparseImageMemoryBindInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.RemapVkResources( INOUT &ptr->image, 1 );
	unpacker.UnpackPtr( INOUT ptr->pBinds );
	for (uint i = 0; (ptr->pBinds != null) and (i < ptr->bindCount); ++i) {
		VUnpack_VkSparseImageMemoryBind( const_cast<VkSparseImageMemoryBind*>(ptr->pBinds + i), unpacker );
	}
}


void VUnpack_VkFenceCreateInfo (VkFenceCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkEventCreateInfo (VkEventCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkRenderPassBeginInfo (VkRenderPassBeginInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.RemapVkResources( INOUT &ptr->renderPass, 1 );
	unpacker.RemapVkResources( INOUT &ptr->framebuffer, 1 );
	VUnpack_VkRect2D( &ptr->renderArea, unpacker );
	unpacker.UnpackPtr( INOUT ptr->pClearValues );
	for (uint i = 0; (ptr->pClearValues != null) and (i < ptr->clearValueCount); ++i) {
		VUnpack_VkClearValue( const_cast<VkClearValue*>(ptr->pClearValues + i), unpacker );
	}
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkQueryPoolCreateInfo (VkQueryPoolCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkBufferCreateInfo (VkBufferCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pQueueFamilyIndices );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkImageCreateInfo (VkImageCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpack_VkExtent3D( &ptr->extent, unpacker );
	unpacker.UnpackPtr( INOUT ptr->pQueueFamilyIndices );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkPipelineMultisampleStateCreateInfo (VkPipelineMultisampleStateCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pSampleMask );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkViewport (VkViewport *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
}


void VUnpack_VkImageSubresourceRange (VkImageSubresourceRange *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
}


void VUnpack_VkShaderModuleCreateInfo (VkShaderModuleCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pCode );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkDescriptorSetLayoutBindingFlagsCreateInfoEXT (VkDescriptorSetLayoutBindingFlagsCreateInfoEXT *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pBindingFlags );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkPipelineCacheCreateInfo (VkPipelineCacheCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pInitialData );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkSpecializationInfo (VkSpecializationInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pMapEntries );
	for (uint i = 0; (ptr->pMapEntries != null) and (i < ptr->mapEntryCount); ++i) {
		VUnpack_VkSpecializationMapEntry( const_cast<VkSpecializationMapEntry*>(ptr->pMapEntries + i), unpacker );
	}
	unpacker.UnpackPtr( INOUT ptr->pData );
}


void VUnpack_VkPipelineShaderStageCreateInfo (VkPipelineShaderStageCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.RemapVkResources( INOUT &ptr->module, 1 );
	unpacker.UnpackPtr( INOUT ptr->pName );
	unpacker.UnpackPtr( INOUT ptr->pSpecializationInfo );
	VUnpack_VkSpecializationInfo( const_cast<VkSpecializationInfo*>(ptr->pSpecializationInfo), unpacker );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkVertexInputBindingDescription (VkVertexInputBindingDescription *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
}


void VUnpack_VkImageCopy (VkImageCopy *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	VUnpack_VkImageSubresourceLayers( &ptr->srcSubresource, unpacker );
	VUnpack_VkOffset3D( &ptr->srcOffset, unpacker );
	VUnpack_VkImageSubresourceLayers( &ptr->dstSubresource, unpacker );
	VUnpack_VkOffset3D( &ptr->dstOffset, unpacker );
	VUnpack_VkExtent3D( &ptr->extent, unpacker );
}


void VUnpack_VkVertexInputAttributeDescription (VkVertexInputAttributeDescription *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
}


void VUnpack_VkPipelineRasterizationStateCreateInfo (VkPipelineRasterizationStateCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkExtent2D (VkExtent2D *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
}


void VUnpack_VkRect2D (VkRect2D *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	VUnpack_VkOffset2D( &ptr->offset, unpacker );
	VUnpack_VkExtent2D( &ptr->extent, unpacker );
}


void VUnpack_VkStencilOpState (VkStencilOpState *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
}


void VUnpack_VkPipelineDepthStencilStateCreateInfo (VkPipelineDepthStencilStateCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpack_VkStencilOpState( &ptr->front, unpacker );
	VUnpack_VkStencilOpState( &ptr->back, unpacker );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkCommandBufferInheritanceInfo (VkCommandBufferInheritanceInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.RemapVkResources( INOUT &ptr->renderPass, 1 );
	unpacker.RemapVkResources( INOUT &ptr->framebuffer, 1 );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkPipelineColorBlendStateCreateInfo (VkPipelineColorBlendStateCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pAttachments );
	for (uint i = 0; (ptr->pAttachments != null) and (i < ptr->attachmentCount); ++i) {
		VUnpack_VkPipelineColorBlendAttachmentState( const_cast<VkPipelineColorBlendAttachmentState*>(ptr->pAttachments + i), unpacker );
	}
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkGraphicsPipelineCreateInfo (VkGraphicsPipelineCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pStages );
	for (uint i = 0; (ptr->pStages != null) and (i < ptr->stageCount); ++i) {
		VUnpackStruct( BitCast<VkBaseOutStructure*>(const_cast<VkPipelineShaderStageCreateInfo*>(ptr->pStages + i)), unpacker );
	}
	unpacker.UnpackPtr( INOUT ptr->pVertexInputState );
	VUnpackStruct( BitCast<VkBaseOutStructure*>(const_cast<VkPipelineVertexInputStateCreateInfo*>(ptr->pVertexInputState)), unpacker );
	unpacker.UnpackPtr( INOUT ptr->pInputAssemblyState );
	VUnpackStruct( BitCast<VkBaseOutStructure*>(const_cast<VkPipelineInputAssemblyStateCreateInfo*>(ptr->pInputAssemblyState)), unpacker );
	unpacker.UnpackPtr( INOUT ptr->pTessellationState );
	VUnpackStruct( BitCast<VkBaseOutStructure*>(const_cast<VkPipelineTessellationStateCreateInfo*>(ptr->pTessellationState)), unpacker );
	unpacker.UnpackPtr( INOUT ptr->pViewportState );
	VUnpackStruct( BitCast<VkBaseOutStructure*>(const_cast<VkPipelineViewportStateCreateInfo*>(ptr->pViewportState)), unpacker );
	unpacker.UnpackPtr( INOUT ptr->pRasterizationState );
	VUnpackStruct( BitCast<VkBaseOutStructure*>(const_cast<VkPipelineRasterizationStateCreateInfo*>(ptr->pRasterizationState)), unpacker );
	unpacker.UnpackPtr( INOUT ptr->pMultisampleState );
	VUnpackStruct( BitCast<VkBaseOutStructure*>(const_cast<VkPipelineMultisampleStateCreateInfo*>(ptr->pMultisampleState)), unpacker );
	unpacker.UnpackPtr( INOUT ptr->pDepthStencilState );
	VUnpackStruct( BitCast<VkBaseOutStructure*>(const_cast<VkPipelineDepthStencilStateCreateInfo*>(ptr->pDepthStencilState)), unpacker );
	unpacker.UnpackPtr( INOUT ptr->pColorBlendState );
	VUnpackStruct( BitCast<VkBaseOutStructure*>(const_cast<VkPipelineColorBlendStateCreateInfo*>(ptr->pColorBlendState)), unpacker );
	unpacker.UnpackPtr( INOUT ptr->pDynamicState );
	VUnpackStruct( BitCast<VkBaseOutStructure*>(const_cast<VkPipelineDynamicStateCreateInfo*>(ptr->pDynamicState)), unpacker );
	unpacker.RemapVkResources( INOUT &ptr->layout, 1 );
	unpacker.RemapVkResources( INOUT &ptr->renderPass, 1 );
	unpacker.RemapVkResources( INOUT &ptr->basePipelineHandle, 1 );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkSamplerYcbcrConversionInfo (VkSamplerYcbcrConversionInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.RemapVkResources( INOUT &ptr->conversion, 1 );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkComputePipelineCreateInfo (VkComputePipelineCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( BitCast<VkBaseOutStructure*>(&ptr->stage), unpacker );
	unpacker.RemapVkResources( INOUT &ptr->layout, 1 );
	unpacker.RemapVkResources( INOUT &ptr->basePipelineHandle, 1 );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkPushConstantRange (VkPushConstantRange *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
}


void VUnpack_VkPipelineLayoutCreateInfo (VkPipelineLayoutCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pSetLayouts );
	unpacker.RemapVkResources( INOUT ptr->pSetLayouts, ptr->setLayoutCount );
	unpacker.UnpackPtr( INOUT ptr->pPushConstantRanges );
	for (uint i = 0; (ptr->pPushConstantRanges != null) and (i < ptr->pushConstantRangeCount); ++i) {
		VUnpack_VkPushConstantRange( const_cast<VkPushConstantRange*>(ptr->pPushConstantRanges + i), unpacker );
	}
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkSamplerCreateInfo (VkSamplerCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkDescriptorSetLayoutBinding (VkDescriptorSetLayoutBinding *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pImmutableSamplers );
	unpacker.RemapVkResources( INOUT ptr->pImmutableSamplers, ptr->descriptorCount );
}


void VUnpack_VkDescriptorSetLayoutCreateInfo (VkDescriptorSetLayoutCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pBindings );
	for (uint i = 0; (ptr->pBindings != null) and (i < ptr->bindingCount); ++i) {
		VUnpack_VkDescriptorSetLayoutBinding( const_cast<VkDescriptorSetLayoutBinding*>(ptr->pBindings + i), unpacker );
	}
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkDescriptorPoolSize (VkDescriptorPoolSize *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
}


void VUnpack_VkDescriptorPoolCreateInfo (VkDescriptorPoolCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pPoolSizes );
	for (uint i = 0; (ptr->pPoolSizes != null) and (i < ptr->poolSizeCount); ++i) {
		VUnpack_VkDescriptorPoolSize( const_cast<VkDescriptorPoolSize*>(ptr->pPoolSizes + i), unpacker );
	}
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkDescriptorSetAllocateInfo (VkDescriptorSetAllocateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.RemapVkResources( INOUT &ptr->descriptorPool, 1 );
	unpacker.UnpackPtr( INOUT ptr->pSetLayouts );
	unpacker.RemapVkResources( INOUT ptr->pSetLayouts, ptr->descriptorSetCount );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkClearValue (VkClearValue *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	VUnpack_VkClearColorValue( &ptr->color, unpacker );
	VUnpack_VkClearDepthStencilValue( &ptr->depthStencil, unpacker );
}


void VUnpack_VkDescriptorImageInfo (VkDescriptorImageInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.RemapVkResources( INOUT &ptr->sampler, 1 );
	unpacker.RemapVkResources( INOUT &ptr->imageView, 1 );
}


void VUnpack_VkDescriptorBufferInfo (VkDescriptorBufferInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.RemapVkResources( INOUT &ptr->buffer, 1 );
}


void VUnpack_VkWriteDescriptorSet (VkWriteDescriptorSet *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.RemapVkResources( INOUT &ptr->dstSet, 1 );
	unpacker.UnpackPtr( INOUT ptr->pImageInfo );
	for (uint i = 0; (ptr->pImageInfo != null) and (i < ptr->descriptorCount); ++i) {
		VUnpack_VkDescriptorImageInfo( const_cast<VkDescriptorImageInfo*>(ptr->pImageInfo + i), unpacker );
	}
	unpacker.UnpackPtr( INOUT ptr->pBufferInfo );
	for (uint i = 0; (ptr->pBufferInfo != null) and (i < ptr->descriptorCount); ++i) {
		VUnpack_VkDescriptorBufferInfo( const_cast<VkDescriptorBufferInfo*>(ptr->pBufferInfo + i), unpacker );
	}
	unpacker.UnpackPtr( INOUT ptr->pTexelBufferView );
	unpacker.RemapVkResources( INOUT ptr->pTexelBufferView, ptr->descriptorCount );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkCopyDescriptorSet (VkCopyDescriptorSet *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.RemapVkResources( INOUT &ptr->srcSet, 1 );
	unpacker.RemapVkResources( INOUT &ptr->dstSet, 1 );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkFramebufferCreateInfo (VkFramebufferCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.RemapVkResources( INOUT &ptr->renderPass, 1 );
	unpacker.UnpackPtr( INOUT ptr->pAttachments );
	unpacker.RemapVkResources( INOUT ptr->pAttachments, ptr->attachmentCount );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkAttachmentDescription (VkAttachmentDescription *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
}


void VUnpack_VkAttachmentReference (VkAttachmentReference *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
}


void VUnpack_VkSubpassDescription (VkSubpassDescription *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pInputAttachments );
	for (uint i = 0; (ptr->pInputAttachments != null) and (i < ptr->inputAttachmentCount); ++i) {
		VUnpack_VkAttachmentReference( const_cast<VkAttachmentReference*>(ptr->pInputAttachments + i), unpacker );
	}
	unpacker.UnpackPtr( INOUT ptr->pColorAttachments );
	for (uint i = 0; (ptr->pColorAttachments != null) and (i < ptr->colorAttachmentCount); ++i) {
		VUnpack_VkAttachmentReference( const_cast<VkAttachmentReference*>(ptr->pColorAttachments + i), unpacker );
	}
	unpacker.UnpackPtr( INOUT ptr->pResolveAttachments );
	for (uint i = 0; (ptr->pResolveAttachments != null) and (i < ptr->colorAttachmentCount); ++i) {
		VUnpack_VkAttachmentReference( const_cast<VkAttachmentReference*>(ptr->pResolveAttachments + i), unpacker );
	}
	unpacker.UnpackPtr( INOUT ptr->pDepthStencilAttachment );
	VUnpack_VkAttachmentReference( const_cast<VkAttachmentReference*>(ptr->pDepthStencilAttachment), unpacker );
	unpacker.UnpackPtr( INOUT ptr->pPreserveAttachments );
}


void VUnpack_VkSubpassDependency (VkSubpassDependency *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
}


void VUnpack_VkRenderPassCreateInfo (VkRenderPassCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pAttachments );
	for (uint i = 0; (ptr->pAttachments != null) and (i < ptr->attachmentCount); ++i) {
		VUnpack_VkAttachmentDescription( const_cast<VkAttachmentDescription*>(ptr->pAttachments + i), unpacker );
	}
	unpacker.UnpackPtr( INOUT ptr->pSubpasses );
	for (uint i = 0; (ptr->pSubpasses != null) and (i < ptr->subpassCount); ++i) {
		VUnpack_VkSubpassDescription( const_cast<VkSubpassDescription*>(ptr->pSubpasses + i), unpacker );
	}
	unpacker.UnpackPtr( INOUT ptr->pDependencies );
	for (uint i = 0; (ptr->pDependencies != null) and (i < ptr->dependencyCount); ++i) {
		VUnpack_VkSubpassDependency( const_cast<VkSubpassDependency*>(ptr->pDependencies + i), unpacker );
	}
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkCommandPoolCreateInfo (VkCommandPoolCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkCommandBufferAllocateInfo (VkCommandBufferAllocateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.RemapVkResources( INOUT &ptr->commandPool, 1 );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkCommandBufferBeginInfo (VkCommandBufferBeginInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pInheritanceInfo );
	VUnpackStruct( BitCast<VkBaseOutStructure*>(const_cast<VkCommandBufferInheritanceInfo*>(ptr->pInheritanceInfo)), unpacker );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkBufferCopy (VkBufferCopy *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
}


void VUnpack_VkImageSubresourceLayers (VkImageSubresourceLayers *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
}


void VUnpack_VkImageBlit (VkImageBlit *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	VUnpack_VkImageSubresourceLayers( &ptr->srcSubresource, unpacker );
	VUnpack_VkImageSubresourceLayers( &ptr->dstSubresource, unpacker );
}


void VUnpack_VkBufferImageCopy (VkBufferImageCopy *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	VUnpack_VkImageSubresourceLayers( &ptr->imageSubresource, unpacker );
	VUnpack_VkOffset3D( &ptr->imageOffset, unpacker );
	VUnpack_VkExtent3D( &ptr->imageExtent, unpacker );
}


void VUnpack_VkClearColorValue (VkClearColorValue *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
}


void VUnpack_VkClearDepthStencilValue (VkClearDepthStencilValue *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
}


void VUnpack_VkClearAttachment (VkClearAttachment *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	VUnpack_VkClearValue( &ptr->clearValue, unpacker );
}


void VUnpack_VkClearRect (VkClearRect *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	VUnpack_VkRect2D( &ptr->rect, unpacker );
}


void VUnpack_VkViewportSwizzleNV (VkViewportSwizzleNV *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
}


void VUnpack_VkBufferMemoryBarrier (VkBufferMemoryBarrier *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.RemapVkResources( INOUT &ptr->buffer, 1 );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkImageMemoryBarrier (VkImageMemoryBarrier *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.RemapVkResources( INOUT &ptr->image, 1 );
	VUnpack_VkImageSubresourceRange( &ptr->subresourceRange, unpacker );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkPipelineCoverageToColorStateCreateInfoNV (VkPipelineCoverageToColorStateCreateInfoNV *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkShadingRatePaletteNV (VkShadingRatePaletteNV *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pShadingRatePaletteEntries );
}


void VUnpack_VkBindBufferMemoryInfo (VkBindBufferMemoryInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.RemapVkResources( INOUT &ptr->buffer, 1 );
	unpacker.RemapVkResources( INOUT &ptr->memory, 1 );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkBindImageMemoryInfo (VkBindImageMemoryInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.RemapVkResources( INOUT &ptr->image, 1 );
	unpacker.RemapVkResources( INOUT &ptr->memory, 1 );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkSubpassEndInfoKHR (VkSubpassEndInfoKHR *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkMemoryDedicatedAllocateInfo (VkMemoryDedicatedAllocateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.RemapVkResources( INOUT &ptr->image, 1 );
	unpacker.RemapVkResources( INOUT &ptr->buffer, 1 );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkMemoryAllocateFlagsInfo (VkMemoryAllocateFlagsInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkDeviceGroupRenderPassBeginInfo (VkDeviceGroupRenderPassBeginInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pDeviceRenderAreas );
	for (uint i = 0; (ptr->pDeviceRenderAreas != null) and (i < ptr->deviceRenderAreaCount); ++i) {
		VUnpack_VkRect2D( const_cast<VkRect2D*>(ptr->pDeviceRenderAreas + i), unpacker );
	}
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkDeviceGroupCommandBufferBeginInfo (VkDeviceGroupCommandBufferBeginInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkDeviceGroupSubmitInfo (VkDeviceGroupSubmitInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pWaitSemaphoreDeviceIndices );
	unpacker.UnpackPtr( INOUT ptr->pCommandBufferDeviceMasks );
	unpacker.UnpackPtr( INOUT ptr->pSignalSemaphoreDeviceIndices );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkDeviceGroupBindSparseInfo (VkDeviceGroupBindSparseInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkBindBufferMemoryDeviceGroupInfo (VkBindBufferMemoryDeviceGroupInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pDeviceIndices );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkBindImageMemoryDeviceGroupInfo (VkBindImageMemoryDeviceGroupInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pDeviceIndices );
	unpacker.UnpackPtr( INOUT ptr->pSplitInstanceBindRegions );
	for (uint i = 0; (ptr->pSplitInstanceBindRegions != null) and (i < ptr->splitInstanceBindRegionCount); ++i) {
		VUnpack_VkRect2D( const_cast<VkRect2D*>(ptr->pSplitInstanceBindRegions + i), unpacker );
	}
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkSamplerReductionModeCreateInfoEXT (VkSamplerReductionModeCreateInfoEXT *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkAttachmentReference2KHR (VkAttachmentReference2KHR *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkInputAttachmentAspectReference (VkInputAttachmentAspectReference *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
}


void VUnpack_VkRenderPassInputAttachmentAspectCreateInfo (VkRenderPassInputAttachmentAspectCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pAspectReferences );
	for (uint i = 0; (ptr->pAspectReferences != null) and (i < ptr->aspectReferenceCount); ++i) {
		VUnpack_VkInputAttachmentAspectReference( const_cast<VkInputAttachmentAspectReference*>(ptr->pAspectReferences + i), unpacker );
	}
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkImageViewUsageCreateInfo (VkImageViewUsageCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkRenderPassMultiviewCreateInfo (VkRenderPassMultiviewCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pViewMasks );
	unpacker.UnpackPtr( INOUT ptr->pViewOffsets );
	unpacker.UnpackPtr( INOUT ptr->pCorrelationMasks );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkRenderPassSampleLocationsBeginInfoEXT (VkRenderPassSampleLocationsBeginInfoEXT *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pAttachmentInitialSampleLocations );
	for (uint i = 0; (ptr->pAttachmentInitialSampleLocations != null) and (i < ptr->attachmentInitialSampleLocationsCount); ++i) {
		VUnpack_VkAttachmentSampleLocationsEXT( const_cast<VkAttachmentSampleLocationsEXT*>(ptr->pAttachmentInitialSampleLocations + i), unpacker );
	}
	unpacker.UnpackPtr( INOUT ptr->pPostSubpassSampleLocations );
	for (uint i = 0; (ptr->pPostSubpassSampleLocations != null) and (i < ptr->postSubpassSampleLocationsCount); ++i) {
		VUnpack_VkSubpassSampleLocationsEXT( const_cast<VkSubpassSampleLocationsEXT*>(ptr->pPostSubpassSampleLocations + i), unpacker );
	}
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkDeviceQueueInfo2 (VkDeviceQueueInfo2 *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkProtectedSubmitInfo (VkProtectedSubmitInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkSamplerYcbcrConversionCreateInfo (VkSamplerYcbcrConversionCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpack_VkComponentMapping( &ptr->components, unpacker );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkBindImagePlaneMemoryInfo (VkBindImagePlaneMemoryInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkDescriptorUpdateTemplateCreateInfo (VkDescriptorUpdateTemplateCreateInfo *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pDescriptorUpdateEntries );
	for (uint i = 0; (ptr->pDescriptorUpdateEntries != null) and (i < ptr->descriptorUpdateEntryCount); ++i) {
		VUnpack_VkDescriptorUpdateTemplateEntry( const_cast<VkDescriptorUpdateTemplateEntry*>(ptr->pDescriptorUpdateEntries + i), unpacker );
	}
	unpacker.RemapVkResources( INOUT &ptr->descriptorSetLayout, 1 );
	unpacker.RemapVkResources( INOUT &ptr->pipelineLayout, 1 );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkCoarseSampleLocationNV (VkCoarseSampleLocationNV *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
}


void VUnpack_VkImageSwapchainCreateInfoKHR (VkImageSwapchainCreateInfoKHR *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.RemapVkResources( INOUT &ptr->swapchain, 1 );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkBindImageMemorySwapchainInfoKHR (VkBindImageMemorySwapchainInfoKHR *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.RemapVkResources( INOUT &ptr->swapchain, 1 );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkVertexInputBindingDivisorDescriptionEXT (VkVertexInputBindingDivisorDescriptionEXT *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
}


void VUnpack_VkSubpassSampleLocationsEXT (VkSubpassSampleLocationsEXT *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	VUnpackStruct( BitCast<VkBaseOutStructure*>(&ptr->sampleLocationsInfo), unpacker );
}


void VUnpack_VkPipelineColorBlendAdvancedStateCreateInfoEXT (VkPipelineColorBlendAdvancedStateCreateInfoEXT *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkAttachmentDescription2KHR (VkAttachmentDescription2KHR *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkSubpassDescription2KHR (VkSubpassDescription2KHR *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pInputAttachments );
	for (uint i = 0; (ptr->pInputAttachments != null) and (i < ptr->inputAttachmentCount); ++i) {
		VUnpackStruct( BitCast<VkBaseOutStructure*>(const_cast<VkAttachmentReference2KHR*>(ptr->pInputAttachments + i)), unpacker );
	}
	unpacker.UnpackPtr( INOUT ptr->pColorAttachments );
	for (uint i = 0; (ptr->pColorAttachments != null) and (i < ptr->colorAttachmentCount); ++i) {
		VUnpackStruct( BitCast<VkBaseOutStructure*>(const_cast<VkAttachmentReference2KHR*>(ptr->pColorAttachments + i)), unpacker );
	}
	unpacker.UnpackPtr( INOUT ptr->pResolveAttachments );
	for (uint i = 0; (ptr->pResolveAttachments != null) and (i < ptr->colorAttachmentCount); ++i) {
		VUnpackStruct( BitCast<VkBaseOutStructure*>(const_cast<VkAttachmentReference2KHR*>(ptr->pResolveAttachments + i)), unpacker );
	}
	unpacker.UnpackPtr( INOUT ptr->pDepthStencilAttachment );
	VUnpackStruct( BitCast<VkBaseOutStructure*>(const_cast<VkAttachmentReference2KHR*>(ptr->pDepthStencilAttachment)), unpacker );
	unpacker.UnpackPtr( INOUT ptr->pPreserveAttachments );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkSubpassDependency2KHR (VkSubpassDependency2KHR *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkRenderPassCreateInfo2KHR (VkRenderPassCreateInfo2KHR *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pAttachments );
	for (uint i = 0; (ptr->pAttachments != null) and (i < ptr->attachmentCount); ++i) {
		VUnpackStruct( BitCast<VkBaseOutStructure*>(const_cast<VkAttachmentDescription2KHR*>(ptr->pAttachments + i)), unpacker );
	}
	unpacker.UnpackPtr( INOUT ptr->pSubpasses );
	for (uint i = 0; (ptr->pSubpasses != null) and (i < ptr->subpassCount); ++i) {
		VUnpackStruct( BitCast<VkBaseOutStructure*>(const_cast<VkSubpassDescription2KHR*>(ptr->pSubpasses + i)), unpacker );
	}
	unpacker.UnpackPtr( INOUT ptr->pDependencies );
	for (uint i = 0; (ptr->pDependencies != null) and (i < ptr->dependencyCount); ++i) {
		VUnpackStruct( BitCast<VkBaseOutStructure*>(const_cast<VkSubpassDependency2KHR*>(ptr->pDependencies + i)), unpacker );
	}
	unpacker.UnpackPtr( INOUT ptr->pCorrelatedViewMasks );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkSubpassBeginInfoKHR (VkSubpassBeginInfoKHR *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkDescriptorSetVariableDescriptorCountAllocateInfoEXT (VkDescriptorSetVariableDescriptorCountAllocateInfoEXT *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pDescriptorCounts );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkPipelineRasterizationStateRasterizationOrderAMD (VkPipelineRasterizationStateRasterizationOrderAMD *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkDebugMarkerObjectNameInfoEXT (VkDebugMarkerObjectNameInfoEXT *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pObjectName );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkDebugMarkerMarkerInfoEXT (VkDebugMarkerMarkerInfoEXT *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pMarkerName );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkDedicatedAllocationImageCreateInfoNV (VkDedicatedAllocationImageCreateInfoNV *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkDedicatedAllocationBufferCreateInfoNV (VkDedicatedAllocationBufferCreateInfoNV *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkDedicatedAllocationMemoryAllocateInfoNV (VkDedicatedAllocationMemoryAllocateInfoNV *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.RemapVkResources( INOUT &ptr->image, 1 );
	unpacker.RemapVkResources( INOUT &ptr->buffer, 1 );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkCoarseSampleOrderCustomNV (VkCoarseSampleOrderCustomNV *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pSampleLocations );
	for (uint i = 0; (ptr->pSampleLocations != null) and (i < ptr->sampleLocationCount); ++i) {
		VUnpack_VkCoarseSampleLocationNV( const_cast<VkCoarseSampleLocationNV*>(ptr->pSampleLocations + i), unpacker );
	}
}


void VUnpack_VkImageViewASTCDecodeModeEXT (VkImageViewASTCDecodeModeEXT *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkCommandBufferInheritanceConditionalRenderingInfoEXT (VkCommandBufferInheritanceConditionalRenderingInfoEXT *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkViewportWScalingNV (VkViewportWScalingNV *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
}


void VUnpack_VkPipelineViewportExclusiveScissorStateCreateInfoNV (VkPipelineViewportExclusiveScissorStateCreateInfoNV *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pExclusiveScissors );
	for (uint i = 0; (ptr->pExclusiveScissors != null) and (i < ptr->exclusiveScissorCount); ++i) {
		VUnpack_VkRect2D( const_cast<VkRect2D*>(ptr->pExclusiveScissors + i), unpacker );
	}
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkPipelineViewportWScalingStateCreateInfoNV (VkPipelineViewportWScalingStateCreateInfoNV *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pViewportWScalings );
	for (uint i = 0; (ptr->pViewportWScalings != null) and (i < ptr->viewportCount); ++i) {
		VUnpack_VkViewportWScalingNV( const_cast<VkViewportWScalingNV*>(ptr->pViewportWScalings + i), unpacker );
	}
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkPipelineViewportSwizzleStateCreateInfoNV (VkPipelineViewportSwizzleStateCreateInfoNV *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pViewportSwizzles );
	for (uint i = 0; (ptr->pViewportSwizzles != null) and (i < ptr->viewportCount); ++i) {
		VUnpack_VkViewportSwizzleNV( const_cast<VkViewportSwizzleNV*>(ptr->pViewportSwizzles + i), unpacker );
	}
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkPipelineDiscardRectangleStateCreateInfoEXT (VkPipelineDiscardRectangleStateCreateInfoEXT *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pDiscardRectangles );
	for (uint i = 0; (ptr->pDiscardRectangles != null) and (i < ptr->discardRectangleCount); ++i) {
		VUnpack_VkRect2D( const_cast<VkRect2D*>(ptr->pDiscardRectangles + i), unpacker );
	}
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkPipelineRasterizationConservativeStateCreateInfoEXT (VkPipelineRasterizationConservativeStateCreateInfoEXT *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkWriteDescriptorSetInlineUniformBlockEXT (VkWriteDescriptorSetInlineUniformBlockEXT *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pData );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkPipelineViewportShadingRateImageStateCreateInfoNV (VkPipelineViewportShadingRateImageStateCreateInfoNV *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pShadingRatePalettes );
	VUnpack_VkShadingRatePaletteNV( const_cast<VkShadingRatePaletteNV*>(ptr->pShadingRatePalettes), unpacker );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkDescriptorPoolInlineUniformBlockCreateInfoEXT (VkDescriptorPoolInlineUniformBlockCreateInfoEXT *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkSampleLocationEXT (VkSampleLocationEXT *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
}


void VUnpack_VkSampleLocationsInfoEXT (VkSampleLocationsInfoEXT *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpack_VkExtent2D( &ptr->sampleLocationGridSize, unpacker );
	unpacker.UnpackPtr( INOUT ptr->pSampleLocations );
	for (uint i = 0; (ptr->pSampleLocations != null) and (i < ptr->sampleLocationsCount); ++i) {
		VUnpack_VkSampleLocationEXT( const_cast<VkSampleLocationEXT*>(ptr->pSampleLocations + i), unpacker );
	}
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkAttachmentSampleLocationsEXT (VkAttachmentSampleLocationsEXT *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	VUnpackStruct( BitCast<VkBaseOutStructure*>(&ptr->sampleLocationsInfo), unpacker );
}


void VUnpack_VkPipelineSampleLocationsStateCreateInfoEXT (VkPipelineSampleLocationsStateCreateInfoEXT *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( BitCast<VkBaseOutStructure*>(&ptr->sampleLocationsInfo), unpacker );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkPipelineCoverageModulationStateCreateInfoNV (VkPipelineCoverageModulationStateCreateInfoNV *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pCoverageModulationTable );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkPipelineRepresentativeFragmentTestStateCreateInfoNV (VkPipelineRepresentativeFragmentTestStateCreateInfoNV *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


void VUnpack_VkPipelineVertexInputDivisorStateCreateInfoEXT (VkPipelineVertexInputDivisorStateCreateInfoEXT *ptr, const VUnpacker &unpacker)
{
	if ( ptr == null ) return;
	unpacker.UnpackPtr( INOUT ptr->pNext );
	unpacker.UnpackPtr( INOUT ptr->pVertexBindingDivisors );
	for (uint i = 0; (ptr->pVertexBindingDivisors != null) and (i < ptr->vertexBindingDivisorCount); ++i) {
		VUnpack_VkVertexInputBindingDivisorDescriptionEXT( const_cast<VkVertexInputBindingDivisorDescriptionEXT*>(ptr->pVertexBindingDivisors + i), unpacker );
	}
	VUnpackStruct( Cast<VkBaseOutStructure>(const_cast<void*>(ptr->pNext)), unpacker );
}


