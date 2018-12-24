// auto-generated file

void VPackStruct (const VkBaseInStructure *ptr, VPacker &packer)
{
	if ( ptr == null ) return;
	ENABLE_ENUM_CHECKS();
	switch ( ptr->sType )
	{
		case VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO : {
			VkSemaphoreCreateInfo const *  obj = BitCast<VkSemaphoreCreateInfo const *>( ptr );
			VPack_VkSemaphoreCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_COARSE_SAMPLE_ORDER_STATE_CREATE_INFO_NV : {
			VkPipelineViewportCoarseSampleOrderStateCreateInfoNV const *  obj = BitCast<VkPipelineViewportCoarseSampleOrderStateCreateInfoNV const *>( ptr );
			VPack_VkPipelineViewportCoarseSampleOrderStateCreateInfoNV( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_DOMAIN_ORIGIN_STATE_CREATE_INFO : {
			VkPipelineTessellationDomainOriginStateCreateInfo const *  obj = BitCast<VkPipelineTessellationDomainOriginStateCreateInfo const *>( ptr );
			VPack_VkPipelineTessellationDomainOriginStateCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO : {
			VkBufferViewCreateInfo const *  obj = BitCast<VkBufferViewCreateInfo const *>( ptr );
			VPack_VkBufferViewCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_MEMORY_BARRIER : {
			VkMemoryBarrier const *  obj = BitCast<VkMemoryBarrier const *>( ptr );
			VPack_VkMemoryBarrier( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO : {
			VkPipelineInputAssemblyStateCreateInfo const *  obj = BitCast<VkPipelineInputAssemblyStateCreateInfo const *>( ptr );
			VPack_VkPipelineInputAssemblyStateCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO_KHR : {
			VkImageFormatListCreateInfoKHR const *  obj = BitCast<VkImageFormatListCreateInfoKHR const *>( ptr );
			VPack_VkImageFormatListCreateInfoKHR( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE : {
			VkMappedMemoryRange const *  obj = BitCast<VkMappedMemoryRange const *>( ptr );
			VPack_VkMappedMemoryRange( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_SUBMIT_INFO : {
			VkSubmitInfo const *  obj = BitCast<VkSubmitInfo const *>( ptr );
			VPack_VkSubmitInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO : {
			VkPipelineDynamicStateCreateInfo const *  obj = BitCast<VkPipelineDynamicStateCreateInfo const *>( ptr );
			VPack_VkPipelineDynamicStateCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO : {
			VkImageViewCreateInfo const *  obj = BitCast<VkImageViewCreateInfo const *>( ptr );
			VPack_VkImageViewCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO : {
			VkPipelineTessellationStateCreateInfo const *  obj = BitCast<VkPipelineTessellationStateCreateInfo const *>( ptr );
			VPack_VkPipelineTessellationStateCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO : {
			VkMemoryAllocateInfo const *  obj = BitCast<VkMemoryAllocateInfo const *>( ptr );
			VPack_VkMemoryAllocateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_BIND_SPARSE_INFO : {
			VkBindSparseInfo const *  obj = BitCast<VkBindSparseInfo const *>( ptr );
			VPack_VkBindSparseInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO : {
			VkPipelineViewportStateCreateInfo const *  obj = BitCast<VkPipelineViewportStateCreateInfo const *>( ptr );
			VPack_VkPipelineViewportStateCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO : {
			VkPipelineVertexInputStateCreateInfo const *  obj = BitCast<VkPipelineVertexInputStateCreateInfo const *>( ptr );
			VPack_VkPipelineVertexInputStateCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_FENCE_CREATE_INFO : {
			VkFenceCreateInfo const *  obj = BitCast<VkFenceCreateInfo const *>( ptr );
			VPack_VkFenceCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_EVENT_CREATE_INFO : {
			VkEventCreateInfo const *  obj = BitCast<VkEventCreateInfo const *>( ptr );
			VPack_VkEventCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO : {
			VkRenderPassBeginInfo const *  obj = BitCast<VkRenderPassBeginInfo const *>( ptr );
			VPack_VkRenderPassBeginInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO : {
			VkQueryPoolCreateInfo const *  obj = BitCast<VkQueryPoolCreateInfo const *>( ptr );
			VPack_VkQueryPoolCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO : {
			VkBufferCreateInfo const *  obj = BitCast<VkBufferCreateInfo const *>( ptr );
			VPack_VkBufferCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO : {
			VkImageCreateInfo const *  obj = BitCast<VkImageCreateInfo const *>( ptr );
			VPack_VkImageCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO : {
			VkPipelineMultisampleStateCreateInfo const *  obj = BitCast<VkPipelineMultisampleStateCreateInfo const *>( ptr );
			VPack_VkPipelineMultisampleStateCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO : {
			VkShaderModuleCreateInfo const *  obj = BitCast<VkShaderModuleCreateInfo const *>( ptr );
			VPack_VkShaderModuleCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO_EXT : {
			VkDescriptorSetLayoutBindingFlagsCreateInfoEXT const *  obj = BitCast<VkDescriptorSetLayoutBindingFlagsCreateInfoEXT const *>( ptr );
			VPack_VkDescriptorSetLayoutBindingFlagsCreateInfoEXT( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO : {
			VkPipelineCacheCreateInfo const *  obj = BitCast<VkPipelineCacheCreateInfo const *>( ptr );
			VPack_VkPipelineCacheCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO : {
			VkPipelineShaderStageCreateInfo const *  obj = BitCast<VkPipelineShaderStageCreateInfo const *>( ptr );
			VPack_VkPipelineShaderStageCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO : {
			VkPipelineRasterizationStateCreateInfo const *  obj = BitCast<VkPipelineRasterizationStateCreateInfo const *>( ptr );
			VPack_VkPipelineRasterizationStateCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO : {
			VkPipelineDepthStencilStateCreateInfo const *  obj = BitCast<VkPipelineDepthStencilStateCreateInfo const *>( ptr );
			VPack_VkPipelineDepthStencilStateCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO : {
			VkCommandBufferInheritanceInfo const *  obj = BitCast<VkCommandBufferInheritanceInfo const *>( ptr );
			VPack_VkCommandBufferInheritanceInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO : {
			VkPipelineColorBlendStateCreateInfo const *  obj = BitCast<VkPipelineColorBlendStateCreateInfo const *>( ptr );
			VPack_VkPipelineColorBlendStateCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO : {
			VkGraphicsPipelineCreateInfo const *  obj = BitCast<VkGraphicsPipelineCreateInfo const *>( ptr );
			VPack_VkGraphicsPipelineCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_INFO : {
			VkSamplerYcbcrConversionInfo const *  obj = BitCast<VkSamplerYcbcrConversionInfo const *>( ptr );
			VPack_VkSamplerYcbcrConversionInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO : {
			VkComputePipelineCreateInfo const *  obj = BitCast<VkComputePipelineCreateInfo const *>( ptr );
			VPack_VkComputePipelineCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO : {
			VkPipelineLayoutCreateInfo const *  obj = BitCast<VkPipelineLayoutCreateInfo const *>( ptr );
			VPack_VkPipelineLayoutCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO : {
			VkSamplerCreateInfo const *  obj = BitCast<VkSamplerCreateInfo const *>( ptr );
			VPack_VkSamplerCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO : {
			VkDescriptorSetLayoutCreateInfo const *  obj = BitCast<VkDescriptorSetLayoutCreateInfo const *>( ptr );
			VPack_VkDescriptorSetLayoutCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO : {
			VkDescriptorPoolCreateInfo const *  obj = BitCast<VkDescriptorPoolCreateInfo const *>( ptr );
			VPack_VkDescriptorPoolCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO : {
			VkDescriptorSetAllocateInfo const *  obj = BitCast<VkDescriptorSetAllocateInfo const *>( ptr );
			VPack_VkDescriptorSetAllocateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET : {
			VkWriteDescriptorSet const *  obj = BitCast<VkWriteDescriptorSet const *>( ptr );
			VPack_VkWriteDescriptorSet( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET : {
			VkCopyDescriptorSet const *  obj = BitCast<VkCopyDescriptorSet const *>( ptr );
			VPack_VkCopyDescriptorSet( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO : {
			VkFramebufferCreateInfo const *  obj = BitCast<VkFramebufferCreateInfo const *>( ptr );
			VPack_VkFramebufferCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO : {
			VkRenderPassCreateInfo const *  obj = BitCast<VkRenderPassCreateInfo const *>( ptr );
			VPack_VkRenderPassCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO : {
			VkCommandPoolCreateInfo const *  obj = BitCast<VkCommandPoolCreateInfo const *>( ptr );
			VPack_VkCommandPoolCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO : {
			VkCommandBufferAllocateInfo const *  obj = BitCast<VkCommandBufferAllocateInfo const *>( ptr );
			VPack_VkCommandBufferAllocateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO : {
			VkCommandBufferBeginInfo const *  obj = BitCast<VkCommandBufferBeginInfo const *>( ptr );
			VPack_VkCommandBufferBeginInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER : {
			VkBufferMemoryBarrier const *  obj = BitCast<VkBufferMemoryBarrier const *>( ptr );
			VPack_VkBufferMemoryBarrier( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER : {
			VkImageMemoryBarrier const *  obj = BitCast<VkImageMemoryBarrier const *>( ptr );
			VPack_VkImageMemoryBarrier( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_TO_COLOR_STATE_CREATE_INFO_NV : {
			VkPipelineCoverageToColorStateCreateInfoNV const *  obj = BitCast<VkPipelineCoverageToColorStateCreateInfoNV const *>( ptr );
			VPack_VkPipelineCoverageToColorStateCreateInfoNV( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO : {
			VkBindBufferMemoryInfo const *  obj = BitCast<VkBindBufferMemoryInfo const *>( ptr );
			VPack_VkBindBufferMemoryInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO : {
			VkBindImageMemoryInfo const *  obj = BitCast<VkBindImageMemoryInfo const *>( ptr );
			VPack_VkBindImageMemoryInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_SUBPASS_END_INFO_KHR : {
			VkSubpassEndInfoKHR const *  obj = BitCast<VkSubpassEndInfoKHR const *>( ptr );
			VPack_VkSubpassEndInfoKHR( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO : {
			VkMemoryDedicatedAllocateInfo const *  obj = BitCast<VkMemoryDedicatedAllocateInfo const *>( ptr );
			VPack_VkMemoryDedicatedAllocateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO : {
			VkMemoryAllocateFlagsInfo const *  obj = BitCast<VkMemoryAllocateFlagsInfo const *>( ptr );
			VPack_VkMemoryAllocateFlagsInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_DEVICE_GROUP_RENDER_PASS_BEGIN_INFO : {
			VkDeviceGroupRenderPassBeginInfo const *  obj = BitCast<VkDeviceGroupRenderPassBeginInfo const *>( ptr );
			VPack_VkDeviceGroupRenderPassBeginInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_DEVICE_GROUP_COMMAND_BUFFER_BEGIN_INFO : {
			VkDeviceGroupCommandBufferBeginInfo const *  obj = BitCast<VkDeviceGroupCommandBufferBeginInfo const *>( ptr );
			VPack_VkDeviceGroupCommandBufferBeginInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_DEVICE_GROUP_SUBMIT_INFO : {
			VkDeviceGroupSubmitInfo const *  obj = BitCast<VkDeviceGroupSubmitInfo const *>( ptr );
			VPack_VkDeviceGroupSubmitInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_DEVICE_GROUP_BIND_SPARSE_INFO : {
			VkDeviceGroupBindSparseInfo const *  obj = BitCast<VkDeviceGroupBindSparseInfo const *>( ptr );
			VPack_VkDeviceGroupBindSparseInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_DEVICE_GROUP_INFO : {
			VkBindBufferMemoryDeviceGroupInfo const *  obj = BitCast<VkBindBufferMemoryDeviceGroupInfo const *>( ptr );
			VPack_VkBindBufferMemoryDeviceGroupInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_DEVICE_GROUP_INFO : {
			VkBindImageMemoryDeviceGroupInfo const *  obj = BitCast<VkBindImageMemoryDeviceGroupInfo const *>( ptr );
			VPack_VkBindImageMemoryDeviceGroupInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_SAMPLER_REDUCTION_MODE_CREATE_INFO_EXT : {
			VkSamplerReductionModeCreateInfoEXT const *  obj = BitCast<VkSamplerReductionModeCreateInfoEXT const *>( ptr );
			VPack_VkSamplerReductionModeCreateInfoEXT( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2_KHR : {
			VkAttachmentReference2KHR const *  obj = BitCast<VkAttachmentReference2KHR const *>( ptr );
			VPack_VkAttachmentReference2KHR( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_RENDER_PASS_INPUT_ATTACHMENT_ASPECT_CREATE_INFO : {
			VkRenderPassInputAttachmentAspectCreateInfo const *  obj = BitCast<VkRenderPassInputAttachmentAspectCreateInfo const *>( ptr );
			VPack_VkRenderPassInputAttachmentAspectCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO : {
			VkImageViewUsageCreateInfo const *  obj = BitCast<VkImageViewUsageCreateInfo const *>( ptr );
			VPack_VkImageViewUsageCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_RENDER_PASS_MULTIVIEW_CREATE_INFO : {
			VkRenderPassMultiviewCreateInfo const *  obj = BitCast<VkRenderPassMultiviewCreateInfo const *>( ptr );
			VPack_VkRenderPassMultiviewCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_RENDER_PASS_SAMPLE_LOCATIONS_BEGIN_INFO_EXT : {
			VkRenderPassSampleLocationsBeginInfoEXT const *  obj = BitCast<VkRenderPassSampleLocationsBeginInfoEXT const *>( ptr );
			VPack_VkRenderPassSampleLocationsBeginInfoEXT( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2 : {
			VkDeviceQueueInfo2 const *  obj = BitCast<VkDeviceQueueInfo2 const *>( ptr );
			VPack_VkDeviceQueueInfo2( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_PROTECTED_SUBMIT_INFO : {
			VkProtectedSubmitInfo const *  obj = BitCast<VkProtectedSubmitInfo const *>( ptr );
			VPack_VkProtectedSubmitInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_CREATE_INFO : {
			VkSamplerYcbcrConversionCreateInfo const *  obj = BitCast<VkSamplerYcbcrConversionCreateInfo const *>( ptr );
			VPack_VkSamplerYcbcrConversionCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_BIND_IMAGE_PLANE_MEMORY_INFO : {
			VkBindImagePlaneMemoryInfo const *  obj = BitCast<VkBindImagePlaneMemoryInfo const *>( ptr );
			VPack_VkBindImagePlaneMemoryInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_CREATE_INFO : {
			VkDescriptorUpdateTemplateCreateInfo const *  obj = BitCast<VkDescriptorUpdateTemplateCreateInfo const *>( ptr );
			VPack_VkDescriptorUpdateTemplateCreateInfo( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_IMAGE_SWAPCHAIN_CREATE_INFO_KHR : {
			VkImageSwapchainCreateInfoKHR const *  obj = BitCast<VkImageSwapchainCreateInfoKHR const *>( ptr );
			VPack_VkImageSwapchainCreateInfoKHR( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_SWAPCHAIN_INFO_KHR : {
			VkBindImageMemorySwapchainInfoKHR const *  obj = BitCast<VkBindImageMemorySwapchainInfoKHR const *>( ptr );
			VPack_VkBindImageMemorySwapchainInfoKHR( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_ADVANCED_STATE_CREATE_INFO_EXT : {
			VkPipelineColorBlendAdvancedStateCreateInfoEXT const *  obj = BitCast<VkPipelineColorBlendAdvancedStateCreateInfoEXT const *>( ptr );
			VPack_VkPipelineColorBlendAdvancedStateCreateInfoEXT( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_2_KHR : {
			VkAttachmentDescription2KHR const *  obj = BitCast<VkAttachmentDescription2KHR const *>( ptr );
			VPack_VkAttachmentDescription2KHR( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_2_KHR : {
			VkSubpassDescription2KHR const *  obj = BitCast<VkSubpassDescription2KHR const *>( ptr );
			VPack_VkSubpassDescription2KHR( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_SUBPASS_DEPENDENCY_2_KHR : {
			VkSubpassDependency2KHR const *  obj = BitCast<VkSubpassDependency2KHR const *>( ptr );
			VPack_VkSubpassDependency2KHR( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO_2_KHR : {
			VkRenderPassCreateInfo2KHR const *  obj = BitCast<VkRenderPassCreateInfo2KHR const *>( ptr );
			VPack_VkRenderPassCreateInfo2KHR( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_SUBPASS_BEGIN_INFO_KHR : {
			VkSubpassBeginInfoKHR const *  obj = BitCast<VkSubpassBeginInfoKHR const *>( ptr );
			VPack_VkSubpassBeginInfoKHR( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_ALLOCATE_INFO_EXT : {
			VkDescriptorSetVariableDescriptorCountAllocateInfoEXT const *  obj = BitCast<VkDescriptorSetVariableDescriptorCountAllocateInfoEXT const *>( ptr );
			VPack_VkDescriptorSetVariableDescriptorCountAllocateInfoEXT( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_MEMORY_ALLOCATE_INFO_NV : {
			VkDedicatedAllocationMemoryAllocateInfoNV const *  obj = BitCast<VkDedicatedAllocationMemoryAllocateInfoNV const *>( ptr );
			VPack_VkDedicatedAllocationMemoryAllocateInfoNV( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_RASTERIZATION_ORDER_AMD : {
			VkPipelineRasterizationStateRasterizationOrderAMD const *  obj = BitCast<VkPipelineRasterizationStateRasterizationOrderAMD const *>( ptr );
			VPack_VkPipelineRasterizationStateRasterizationOrderAMD( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_NAME_INFO_EXT : {
			VkDebugMarkerObjectNameInfoEXT const *  obj = BitCast<VkDebugMarkerObjectNameInfoEXT const *>( ptr );
			VPack_VkDebugMarkerObjectNameInfoEXT( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_DEBUG_MARKER_MARKER_INFO_EXT : {
			VkDebugMarkerMarkerInfoEXT const *  obj = BitCast<VkDebugMarkerMarkerInfoEXT const *>( ptr );
			VPack_VkDebugMarkerMarkerInfoEXT( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_IMAGE_CREATE_INFO_NV : {
			VkDedicatedAllocationImageCreateInfoNV const *  obj = BitCast<VkDedicatedAllocationImageCreateInfoNV const *>( ptr );
			VPack_VkDedicatedAllocationImageCreateInfoNV( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_BUFFER_CREATE_INFO_NV : {
			VkDedicatedAllocationBufferCreateInfoNV const *  obj = BitCast<VkDedicatedAllocationBufferCreateInfoNV const *>( ptr );
			VPack_VkDedicatedAllocationBufferCreateInfoNV( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_IMAGE_VIEW_ASTC_DECODE_MODE_EXT : {
			VkImageViewASTCDecodeModeEXT const *  obj = BitCast<VkImageViewASTCDecodeModeEXT const *>( ptr );
			VPack_VkImageViewASTCDecodeModeEXT( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_CONDITIONAL_RENDERING_INFO_EXT : {
			VkCommandBufferInheritanceConditionalRenderingInfoEXT const *  obj = BitCast<VkCommandBufferInheritanceConditionalRenderingInfoEXT const *>( ptr );
			VPack_VkCommandBufferInheritanceConditionalRenderingInfoEXT( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_EXCLUSIVE_SCISSOR_STATE_CREATE_INFO_NV : {
			VkPipelineViewportExclusiveScissorStateCreateInfoNV const *  obj = BitCast<VkPipelineViewportExclusiveScissorStateCreateInfoNV const *>( ptr );
			VPack_VkPipelineViewportExclusiveScissorStateCreateInfoNV( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_W_SCALING_STATE_CREATE_INFO_NV : {
			VkPipelineViewportWScalingStateCreateInfoNV const *  obj = BitCast<VkPipelineViewportWScalingStateCreateInfoNV const *>( ptr );
			VPack_VkPipelineViewportWScalingStateCreateInfoNV( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_SWIZZLE_STATE_CREATE_INFO_NV : {
			VkPipelineViewportSwizzleStateCreateInfoNV const *  obj = BitCast<VkPipelineViewportSwizzleStateCreateInfoNV const *>( ptr );
			VPack_VkPipelineViewportSwizzleStateCreateInfoNV( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_DISCARD_RECTANGLE_STATE_CREATE_INFO_EXT : {
			VkPipelineDiscardRectangleStateCreateInfoEXT const *  obj = BitCast<VkPipelineDiscardRectangleStateCreateInfoEXT const *>( ptr );
			VPack_VkPipelineDiscardRectangleStateCreateInfoEXT( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_CONSERVATIVE_STATE_CREATE_INFO_EXT : {
			VkPipelineRasterizationConservativeStateCreateInfoEXT const *  obj = BitCast<VkPipelineRasterizationConservativeStateCreateInfoEXT const *>( ptr );
			VPack_VkPipelineRasterizationConservativeStateCreateInfoEXT( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_INLINE_UNIFORM_BLOCK_EXT : {
			VkWriteDescriptorSetInlineUniformBlockEXT const *  obj = BitCast<VkWriteDescriptorSetInlineUniformBlockEXT const *>( ptr );
			VPack_VkWriteDescriptorSetInlineUniformBlockEXT( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_SHADING_RATE_IMAGE_STATE_CREATE_INFO_NV : {
			VkPipelineViewportShadingRateImageStateCreateInfoNV const *  obj = BitCast<VkPipelineViewportShadingRateImageStateCreateInfoNV const *>( ptr );
			VPack_VkPipelineViewportShadingRateImageStateCreateInfoNV( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_INLINE_UNIFORM_BLOCK_CREATE_INFO_EXT : {
			VkDescriptorPoolInlineUniformBlockCreateInfoEXT const *  obj = BitCast<VkDescriptorPoolInlineUniformBlockCreateInfoEXT const *>( ptr );
			VPack_VkDescriptorPoolInlineUniformBlockCreateInfoEXT( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_SAMPLE_LOCATIONS_INFO_EXT : {
			VkSampleLocationsInfoEXT const *  obj = BitCast<VkSampleLocationsInfoEXT const *>( ptr );
			VPack_VkSampleLocationsInfoEXT( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_SAMPLE_LOCATIONS_STATE_CREATE_INFO_EXT : {
			VkPipelineSampleLocationsStateCreateInfoEXT const *  obj = BitCast<VkPipelineSampleLocationsStateCreateInfoEXT const *>( ptr );
			VPack_VkPipelineSampleLocationsStateCreateInfoEXT( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_MODULATION_STATE_CREATE_INFO_NV : {
			VkPipelineCoverageModulationStateCreateInfoNV const *  obj = BitCast<VkPipelineCoverageModulationStateCreateInfoNV const *>( ptr );
			VPack_VkPipelineCoverageModulationStateCreateInfoNV( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_REPRESENTATIVE_FRAGMENT_TEST_STATE_CREATE_INFO_NV : {
			VkPipelineRepresentativeFragmentTestStateCreateInfoNV const *  obj = BitCast<VkPipelineRepresentativeFragmentTestStateCreateInfoNV const *>( ptr );
			VPack_VkPipelineRepresentativeFragmentTestStateCreateInfoNV( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_DIVISOR_STATE_CREATE_INFO_EXT : {
			VkPipelineVertexInputDivisorStateCreateInfoEXT const *  obj = BitCast<VkPipelineVertexInputDivisorStateCreateInfoEXT const *>( ptr );
			VPack_VkPipelineVertexInputDivisorStateCreateInfoEXT( obj, packer );
			break;
		}

		case VK_STRUCTURE_TYPE_APPLICATION_INFO : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_PROPERTIES : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_16BIT_STORAGE_FEATURES : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_MEMORY_DEDICATED_REQUIREMENTS : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GROUP_PROPERTIES : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DEVICE_GROUP_DEVICE_CREATE_INFO : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_BUFFER_MEMORY_REQUIREMENTS_INFO_2 : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_IMAGE_MEMORY_REQUIREMENTS_INFO_2 : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_IMAGE_SPARSE_MEMORY_REQUIREMENTS_INFO_2 : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2 : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_SPARSE_IMAGE_MEMORY_REQUIREMENTS_2 : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2 : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2 : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2 : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2 : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2 : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2 : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2 : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_SPARSE_IMAGE_FORMAT_PROPERTIES_2 : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SPARSE_IMAGE_FORMAT_INFO_2 : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_POINT_CLIPPING_PROPERTIES : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_FEATURES : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PROPERTIES : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VARIABLE_POINTER_FEATURES : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_FEATURES : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_PROPERTIES : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_IMAGE_PLANE_MEMORY_REQUIREMENTS_INFO : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLER_YCBCR_CONVERSION_FEATURES : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_IMAGE_FORMAT_PROPERTIES : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_EXTERNAL_IMAGE_FORMAT_PROPERTIES : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_BUFFER_INFO : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_EXTERNAL_BUFFER_PROPERTIES : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_BUFFER_CREATE_INFO : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_FENCE_INFO : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_EXTERNAL_FENCE_PROPERTIES : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_EXPORT_FENCE_CREATE_INFO : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_SEMAPHORE_INFO : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_EXTERNAL_SEMAPHORE_PROPERTIES : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_3_PROPERTIES : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_SUPPORT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DRAW_PARAMETER_FEATURES : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PRESENT_INFO_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DEVICE_GROUP_PRESENT_CAPABILITIES_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_ACQUIRE_NEXT_IMAGE_INFO_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DEVICE_GROUP_PRESENT_INFO_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DEVICE_GROUP_SWAPCHAIN_CREATE_INFO_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DISPLAY_MODE_CREATE_INFO_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DISPLAY_PRESENT_INFO_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_TAG_INFO_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TRANSFORM_FEEDBACK_FEATURES_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TRANSFORM_FEEDBACK_PROPERTIES_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_STREAM_CREATE_INFO_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_TEXTURE_LOD_GATHER_FORMAT_PROPERTIES_AMD : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CORNER_SAMPLED_IMAGE_FEATURES_NV : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO_NV : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO_NV : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_NV : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_EXPORT_MEMORY_WIN32_HANDLE_INFO_NV : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_WIN32_KEYED_MUTEX_ACQUIRE_RELEASE_INFO_NV : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_VALIDATION_FLAGS_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_VI_SURFACE_CREATE_INFO_NN : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ASTC_DECODE_FEATURES_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_EXPORT_MEMORY_WIN32_HANDLE_INFO_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_MEMORY_WIN32_HANDLE_PROPERTIES_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_MEMORY_GET_WIN32_HANDLE_INFO_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_IMPORT_MEMORY_FD_INFO_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_MEMORY_FD_PROPERTIES_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_MEMORY_GET_FD_INFO_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_WIN32_KEYED_MUTEX_ACQUIRE_RELEASE_INFO_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_WIN32_HANDLE_INFO_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_WIN32_HANDLE_INFO_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_D3D12_FENCE_SUBMIT_INFO_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_SEMAPHORE_GET_WIN32_HANDLE_INFO_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_FD_INFO_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_SEMAPHORE_GET_FD_INFO_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PUSH_DESCRIPTOR_PROPERTIES_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CONDITIONAL_RENDERING_FEATURES_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_CONDITIONAL_RENDERING_BEGIN_INFO_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FLOAT16_INT8_FEATURES_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PRESENT_REGIONS_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_OBJECT_TABLE_CREATE_INFO_NVX : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_INDIRECT_COMMANDS_LAYOUT_CREATE_INFO_NVX : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_CMD_PROCESS_COMMANDS_INFO_NVX : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_CMD_RESERVE_SPACE_FOR_COMMANDS_INFO_NVX : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DEVICE_GENERATED_COMMANDS_LIMITS_NVX : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DEVICE_GENERATED_COMMANDS_FEATURES_NVX : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DISPLAY_POWER_INFO_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DEVICE_EVENT_INFO_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DISPLAY_EVENT_INFO_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_SWAPCHAIN_COUNTER_CREATE_INFO_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PRESENT_TIMES_INFO_GOOGLE : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PER_VIEW_ATTRIBUTES_PROPERTIES_NVX : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DISCARD_RECTANGLE_PROPERTIES_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CONSERVATIVE_RASTERIZATION_PROPERTIES_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_HDR_METADATA_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_SHARED_PRESENT_SURFACE_CAPABILITIES_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_IMPORT_FENCE_WIN32_HANDLE_INFO_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_EXPORT_FENCE_WIN32_HANDLE_INFO_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_FENCE_GET_WIN32_HANDLE_INFO_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_IMPORT_FENCE_FD_INFO_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_FENCE_GET_FD_INFO_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_SURFACE_FORMAT_2_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DISPLAY_PROPERTIES_2_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DISPLAY_PLANE_PROPERTIES_2_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DISPLAY_MODE_PROPERTIES_2_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DISPLAY_PLANE_INFO_2_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DISPLAY_PLANE_CAPABILITIES_2_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_IOS_SURFACE_CREATE_INFO_MVK : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_TAG_INFO_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CALLBACK_DATA_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_USAGE_ANDROID : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_PROPERTIES_ANDROID : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_FORMAT_PROPERTIES_ANDROID : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_IMPORT_ANDROID_HARDWARE_BUFFER_INFO_ANDROID : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_MEMORY_GET_ANDROID_HARDWARE_BUFFER_INFO_ANDROID : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_EXTERNAL_FORMAT_ANDROID : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLER_FILTER_MINMAX_PROPERTIES_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INLINE_UNIFORM_BLOCK_FEATURES_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INLINE_UNIFORM_BLOCK_PROPERTIES_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLE_LOCATIONS_PROPERTIES_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_MULTISAMPLE_PROPERTIES_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BLEND_OPERATION_ADVANCED_FEATURES_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BLEND_OPERATION_ADVANCED_PROPERTIES_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DRM_FORMAT_MODIFIER_PROPERTIES_LIST_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DRM_FORMAT_MODIFIER_PROPERTIES_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_EXPLICIT_CREATE_INFO_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_PROPERTIES_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_VALIDATION_CACHE_CREATE_INFO_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_SHADER_MODULE_VALIDATION_CACHE_CREATE_INFO_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_PROPERTIES_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_LAYOUT_SUPPORT_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADING_RATE_IMAGE_FEATURES_NV : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADING_RATE_IMAGE_PROPERTIES_NV : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_NV : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_NV : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_GEOMETRY_NV : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_GEOMETRY_TRIANGLES_NV : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_GEOMETRY_AABB_NV : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_BIND_ACCELERATION_STRUCTURE_MEMORY_INFO_NV : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_NV : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_INFO_NV : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PROPERTIES_NV : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_NV : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_INFO_NV : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_REPRESENTATIVE_FRAGMENT_TEST_FEATURES_NV : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DEVICE_QUEUE_GLOBAL_PRIORITY_CREATE_INFO_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_8BIT_STORAGE_FEATURES_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_IMPORT_MEMORY_HOST_POINTER_INFO_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_MEMORY_HOST_POINTER_PROPERTIES_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_MEMORY_HOST_PROPERTIES_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_INT64_FEATURES_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_CALIBRATED_TIMESTAMP_INFO_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_AMD : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_DEVICE_MEMORY_OVERALLOCATION_CREATE_INFO_AMD : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_ATTRIBUTE_DIVISOR_PROPERTIES_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_ATTRIBUTE_DIVISOR_FEATURES_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRIVER_PROPERTIES_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FLOAT_CONTROLS_PROPERTIES_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COMPUTE_SHADER_DERIVATIVES_FEATURES_NV : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_NV : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_PROPERTIES_NV : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_BARYCENTRIC_FEATURES_NV : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_IMAGE_FOOTPRINT_FEATURES_NV : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXCLUSIVE_SCISSOR_FEATURES_NV : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_CHECKPOINT_DATA_NV : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_QUEUE_FAMILY_CHECKPOINT_PROPERTIES_NV : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_MEMORY_MODEL_FEATURES_KHR : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PCI_BUS_INFO_PROPERTIES_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_IMAGEPIPE_SURFACE_CREATE_INFO_FUCHSIA : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_FEATURES_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_PROPERTIES_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_RENDER_PASS_FRAGMENT_DENSITY_MAP_CREATE_INFO_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SCALAR_BLOCK_LAYOUT_FEATURES_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_IMAGE_STENCIL_USAGE_CREATE_INFO_EXT : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_RANGE_SIZE : ASSERT(false); break;
		case VK_STRUCTURE_TYPE_MAX_ENUM : ASSERT(false); break;
	}
	DISABLE_ENUM_CHECKS();
}

void VPack_VkSemaphoreCreateInfo (const VkSemaphoreCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkPipelineViewportCoarseSampleOrderStateCreateInfoNV (const VkPipelineViewportCoarseSampleOrderStateCreateInfoNV *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_COARSE_SAMPLE_ORDER_STATE_CREATE_INFO_NV );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pCustomSampleOrders );
	 for (uint i = 0; obj->pCustomSampleOrders and i < obj->customSampleOrderCount; ++i) {
		VPack_VkCoarseSampleOrderCustomNV( obj->pCustomSampleOrders + i, packer );
	 }
	packer.Pop( OUT obj->pCustomSampleOrders );
	packer.EndStruct( *obj );
}


void VPack_VkDescriptorUpdateTemplateEntry (const VkDescriptorUpdateTemplateEntry *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.EndStruct( *obj );
}


void VPack_VkPipelineTessellationDomainOriginStateCreateInfo (const VkPipelineTessellationDomainOriginStateCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_DOMAIN_ORIGIN_STATE_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkBufferViewCreateInfo (const VkBufferViewCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.RemapVkResource( INOUT &obj->buffer );
	packer.EndStruct( *obj );
}


void VPack_VkMemoryBarrier (const VkMemoryBarrier *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_MEMORY_BARRIER );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkPipelineColorBlendAttachmentState (const VkPipelineColorBlendAttachmentState *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.EndStruct( *obj );
}


void VPack_VkPipelineInputAssemblyStateCreateInfo (const VkPipelineInputAssemblyStateCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkExtent3D (const VkExtent3D *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.EndStruct( *obj );
}


void VPack_VkSparseBufferMemoryBindInfo (const VkSparseBufferMemoryBindInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.RemapVkResource( INOUT &obj->buffer );
	packer.Push( obj->pBinds );
	 for (uint i = 0; obj->pBinds and i < obj->bindCount; ++i) {
		VPack_VkSparseMemoryBind( obj->pBinds + i, packer );
	 }
	packer.Pop( OUT obj->pBinds );
	packer.EndStruct( *obj );
}


void VPack_VkImageFormatListCreateInfoKHR (const VkImageFormatListCreateInfoKHR *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO_KHR );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pViewFormats );
	 for (uint i = 0; obj->pViewFormats and i < obj->viewFormatCount; ++i) {
		packer << (obj->pViewFormats[i]);
	 }
	packer.Pop( OUT obj->pViewFormats );
	packer.EndStruct( *obj );
}


void VPack_VkOffset2D (const VkOffset2D *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.EndStruct( *obj );
}


void VPack_VkMappedMemoryRange (const VkMappedMemoryRange *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.RemapVkResource( INOUT &obj->memory );
	packer.EndStruct( *obj );
}


void VPack_VkSubmitInfo (const VkSubmitInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_SUBMIT_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pWaitSemaphores );
	 for (uint i = 0; obj->pWaitSemaphores and i < obj->waitSemaphoreCount; ++i) {
		packer << (obj->pWaitSemaphores[i]);
	 }
	packer.Pop( OUT obj->pWaitSemaphores );
	packer.Push( obj->pWaitDstStageMask );
	 for (uint i = 0; obj->pWaitDstStageMask and i < obj->waitSemaphoreCount; ++i) {
		packer << (obj->pWaitDstStageMask[i]);
	 }
	packer.Pop( OUT obj->pWaitDstStageMask );
	packer.Push( obj->pCommandBuffers );
	 for (uint i = 0; obj->pCommandBuffers and i < obj->commandBufferCount; ++i) {
		packer << (obj->pCommandBuffers[i]);
	 }
	packer.Pop( OUT obj->pCommandBuffers );
	packer.Push( obj->pSignalSemaphores );
	 for (uint i = 0; obj->pSignalSemaphores and i < obj->signalSemaphoreCount; ++i) {
		packer << (obj->pSignalSemaphores[i]);
	 }
	packer.Pop( OUT obj->pSignalSemaphores );
	packer.EndStruct( *obj );
}


void VPack_VkPipelineDynamicStateCreateInfo (const VkPipelineDynamicStateCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pDynamicStates );
	 for (uint i = 0; obj->pDynamicStates and i < obj->dynamicStateCount; ++i) {
		packer << (obj->pDynamicStates[i]);
	 }
	packer.Pop( OUT obj->pDynamicStates );
	packer.EndStruct( *obj );
}


void VPack_VkSparseMemoryBind (const VkSparseMemoryBind *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.RemapVkResource( INOUT &obj->memory );
	packer.EndStruct( *obj );
}


void VPack_VkImageViewCreateInfo (const VkImageViewCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.RemapVkResource( INOUT &obj->image );
	VPack_VkComponentMapping( &obj->components, packer );
	VPack_VkImageSubresourceRange( &obj->subresourceRange, packer );
	packer.EndStruct( *obj );
}


void VPack_VkPipelineTessellationStateCreateInfo (const VkPipelineTessellationStateCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkMemoryAllocateInfo (const VkMemoryAllocateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkSpecializationMapEntry (const VkSpecializationMapEntry *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.EndStruct( *obj );
}


void VPack_VkComponentMapping (const VkComponentMapping *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.EndStruct( *obj );
}


void VPack_VkImageResolve (const VkImageResolve *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	VPack_VkImageSubresourceLayers( &obj->srcSubresource, packer );
	VPack_VkOffset3D( &obj->srcOffset, packer );
	VPack_VkImageSubresourceLayers( &obj->dstSubresource, packer );
	VPack_VkOffset3D( &obj->dstOffset, packer );
	VPack_VkExtent3D( &obj->extent, packer );
	packer.EndStruct( *obj );
}


void VPack_VkBindSparseInfo (const VkBindSparseInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_BIND_SPARSE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pWaitSemaphores );
	 for (uint i = 0; obj->pWaitSemaphores and i < obj->waitSemaphoreCount; ++i) {
		packer << (obj->pWaitSemaphores[i]);
	 }
	packer.Pop( OUT obj->pWaitSemaphores );
	packer.Push( obj->pBufferBinds );
	 for (uint i = 0; obj->pBufferBinds and i < obj->bufferBindCount; ++i) {
		VPack_VkSparseBufferMemoryBindInfo( obj->pBufferBinds + i, packer );
	 }
	packer.Pop( OUT obj->pBufferBinds );
	packer.Push( obj->pImageOpaqueBinds );
	 for (uint i = 0; obj->pImageOpaqueBinds and i < obj->imageOpaqueBindCount; ++i) {
		VPack_VkSparseImageOpaqueMemoryBindInfo( obj->pImageOpaqueBinds + i, packer );
	 }
	packer.Pop( OUT obj->pImageOpaqueBinds );
	packer.Push( obj->pImageBinds );
	 for (uint i = 0; obj->pImageBinds and i < obj->imageBindCount; ++i) {
		VPack_VkSparseImageMemoryBindInfo( obj->pImageBinds + i, packer );
	 }
	packer.Pop( OUT obj->pImageBinds );
	packer.Push( obj->pSignalSemaphores );
	 for (uint i = 0; obj->pSignalSemaphores and i < obj->signalSemaphoreCount; ++i) {
		packer << (obj->pSignalSemaphores[i]);
	 }
	packer.Pop( OUT obj->pSignalSemaphores );
	packer.EndStruct( *obj );
}


void VPack_VkSparseImageOpaqueMemoryBindInfo (const VkSparseImageOpaqueMemoryBindInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.RemapVkResource( INOUT &obj->image );
	packer.Push( obj->pBinds );
	 for (uint i = 0; obj->pBinds and i < obj->bindCount; ++i) {
		VPack_VkSparseMemoryBind( obj->pBinds + i, packer );
	 }
	packer.Pop( OUT obj->pBinds );
	packer.EndStruct( *obj );
}


void VPack_VkPipelineViewportStateCreateInfo (const VkPipelineViewportStateCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pViewports );
	 for (uint i = 0; obj->pViewports and i < obj->viewportCount; ++i) {
		VPack_VkViewport( obj->pViewports + i, packer );
	 }
	packer.Pop( OUT obj->pViewports );
	packer.Push( obj->pScissors );
	 for (uint i = 0; obj->pScissors and i < obj->scissorCount; ++i) {
		VPack_VkRect2D( obj->pScissors + i, packer );
	 }
	packer.Pop( OUT obj->pScissors );
	packer.EndStruct( *obj );
}


void VPack_VkPipelineVertexInputStateCreateInfo (const VkPipelineVertexInputStateCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pVertexBindingDescriptions );
	 for (uint i = 0; obj->pVertexBindingDescriptions and i < obj->vertexBindingDescriptionCount; ++i) {
		VPack_VkVertexInputBindingDescription( obj->pVertexBindingDescriptions + i, packer );
	 }
	packer.Pop( OUT obj->pVertexBindingDescriptions );
	packer.Push( obj->pVertexAttributeDescriptions );
	 for (uint i = 0; obj->pVertexAttributeDescriptions and i < obj->vertexAttributeDescriptionCount; ++i) {
		VPack_VkVertexInputAttributeDescription( obj->pVertexAttributeDescriptions + i, packer );
	 }
	packer.Pop( OUT obj->pVertexAttributeDescriptions );
	packer.EndStruct( *obj );
}


void VPack_VkImageSubresource (const VkImageSubresource *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.EndStruct( *obj );
}


void VPack_VkOffset3D (const VkOffset3D *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.EndStruct( *obj );
}


void VPack_VkSparseImageMemoryBind (const VkSparseImageMemoryBind *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	VPack_VkImageSubresource( &obj->subresource, packer );
	VPack_VkOffset3D( &obj->offset, packer );
	VPack_VkExtent3D( &obj->extent, packer );
	packer.RemapVkResource( INOUT &obj->memory );
	packer.EndStruct( *obj );
}


void VPack_VkSparseImageMemoryBindInfo (const VkSparseImageMemoryBindInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.RemapVkResource( INOUT &obj->image );
	packer.Push( obj->pBinds );
	 for (uint i = 0; obj->pBinds and i < obj->bindCount; ++i) {
		VPack_VkSparseImageMemoryBind( obj->pBinds + i, packer );
	 }
	packer.Pop( OUT obj->pBinds );
	packer.EndStruct( *obj );
}


void VPack_VkFenceCreateInfo (const VkFenceCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_FENCE_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkEventCreateInfo (const VkEventCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_EVENT_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkRenderPassBeginInfo (const VkRenderPassBeginInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.RemapVkResource( INOUT &obj->renderPass );
	packer.RemapVkResource( INOUT &obj->framebuffer );
	VPack_VkRect2D( &obj->renderArea, packer );
	packer.Push( obj->pClearValues );
	 for (uint i = 0; obj->pClearValues and i < obj->clearValueCount; ++i) {
		VPack_VkClearValue( obj->pClearValues + i, packer );
	 }
	packer.Pop( OUT obj->pClearValues );
	packer.EndStruct( *obj );
}


void VPack_VkQueryPoolCreateInfo (const VkQueryPoolCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkBufferCreateInfo (const VkBufferCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pQueueFamilyIndices );
	 for (uint i = 0; obj->pQueueFamilyIndices and i < obj->queueFamilyIndexCount; ++i) {
		packer << (obj->pQueueFamilyIndices[i]);
	 }
	packer.Pop( OUT obj->pQueueFamilyIndices );
	packer.EndStruct( *obj );
}


void VPack_VkImageCreateInfo (const VkImageCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	VPack_VkExtent3D( &obj->extent, packer );
	packer.Push( obj->pQueueFamilyIndices );
	 for (uint i = 0; obj->pQueueFamilyIndices and i < obj->queueFamilyIndexCount; ++i) {
		packer << (obj->pQueueFamilyIndices[i]);
	 }
	packer.Pop( OUT obj->pQueueFamilyIndices );
	packer.EndStruct( *obj );
}


void VPack_VkPipelineMultisampleStateCreateInfo (const VkPipelineMultisampleStateCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pSampleMask );
	 for (uint i = 0; obj->pSampleMask and i < ((uint(obj->rasterizationSamples) + 31) / 32); ++i) {
		packer << (obj->pSampleMask[i]);
	 }
	packer.Pop( OUT obj->pSampleMask );
	packer.EndStruct( *obj );
}


void VPack_VkViewport (const VkViewport *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.EndStruct( *obj );
}


void VPack_VkImageSubresourceRange (const VkImageSubresourceRange *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.EndStruct( *obj );
}


void VPack_VkShaderModuleCreateInfo (const VkShaderModuleCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pCode );
	 for (uint i = 0; obj->pCode and i < obj->codeSize; ++i) {
		packer << (obj->pCode[i]);
	 }
	packer.Pop( OUT obj->pCode );
	packer.EndStruct( *obj );
}


void VPack_VkDescriptorSetLayoutBindingFlagsCreateInfoEXT (const VkDescriptorSetLayoutBindingFlagsCreateInfoEXT *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO_EXT );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pBindingFlags );
	 for (uint i = 0; obj->pBindingFlags and i < obj->bindingCount; ++i) {
		packer << (obj->pBindingFlags[i]);
	 }
	packer.Pop( OUT obj->pBindingFlags );
	packer.EndStruct( *obj );
}


void VPack_VkPipelineCacheCreateInfo (const VkPipelineCacheCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pInitialData );
	 packer.AddArray( obj->pInitialData, obj->initialDataSize );
	packer.Pop( OUT obj->pInitialData );
	packer.EndStruct( *obj );
}


void VPack_VkSpecializationInfo (const VkSpecializationInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.Push( obj->pMapEntries );
	 for (uint i = 0; obj->pMapEntries and i < obj->mapEntryCount; ++i) {
		VPack_VkSpecializationMapEntry( obj->pMapEntries + i, packer );
	 }
	packer.Pop( OUT obj->pMapEntries );
	packer.Push( obj->pData );
	 packer.AddArray( obj->pData, obj->dataSize );
	packer.Pop( OUT obj->pData );
	packer.EndStruct( *obj );
}


void VPack_VkPipelineShaderStageCreateInfo (const VkPipelineShaderStageCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.RemapVkResource( INOUT &obj->module );
	packer.Push( obj->pName );
	 packer.AddString( obj->pName );
	packer.Pop( OUT obj->pName );
	packer.Push( obj->pSpecializationInfo );
	 VPack_VkSpecializationInfo( obj->pSpecializationInfo, packer );
	packer.Pop( OUT obj->pSpecializationInfo );
	packer.EndStruct( *obj );
}


void VPack_VkVertexInputBindingDescription (const VkVertexInputBindingDescription *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.EndStruct( *obj );
}


void VPack_VkImageCopy (const VkImageCopy *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	VPack_VkImageSubresourceLayers( &obj->srcSubresource, packer );
	VPack_VkOffset3D( &obj->srcOffset, packer );
	VPack_VkImageSubresourceLayers( &obj->dstSubresource, packer );
	VPack_VkOffset3D( &obj->dstOffset, packer );
	VPack_VkExtent3D( &obj->extent, packer );
	packer.EndStruct( *obj );
}


void VPack_VkVertexInputAttributeDescription (const VkVertexInputAttributeDescription *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.EndStruct( *obj );
}


void VPack_VkPipelineRasterizationStateCreateInfo (const VkPipelineRasterizationStateCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkExtent2D (const VkExtent2D *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.EndStruct( *obj );
}


void VPack_VkRect2D (const VkRect2D *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	VPack_VkOffset2D( &obj->offset, packer );
	VPack_VkExtent2D( &obj->extent, packer );
	packer.EndStruct( *obj );
}


void VPack_VkStencilOpState (const VkStencilOpState *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.EndStruct( *obj );
}


void VPack_VkPipelineDepthStencilStateCreateInfo (const VkPipelineDepthStencilStateCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	VPack_VkStencilOpState( &obj->front, packer );
	VPack_VkStencilOpState( &obj->back, packer );
	packer.EndStruct( *obj );
}


void VPack_VkCommandBufferInheritanceInfo (const VkCommandBufferInheritanceInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.RemapVkResource( INOUT &obj->renderPass );
	packer.RemapVkResource( INOUT &obj->framebuffer );
	packer.EndStruct( *obj );
}


void VPack_VkPipelineColorBlendStateCreateInfo (const VkPipelineColorBlendStateCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pAttachments );
	 for (uint i = 0; obj->pAttachments and i < obj->attachmentCount; ++i) {
		VPack_VkPipelineColorBlendAttachmentState( obj->pAttachments + i, packer );
	 }
	packer.Pop( OUT obj->pAttachments );
	packer.EndStruct( *obj );
}


void VPack_VkGraphicsPipelineCreateInfo (const VkGraphicsPipelineCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pStages );
	 for (uint i = 0; obj->pStages and i < obj->stageCount; ++i) {
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pStages + i), packer );
	 }
	packer.Pop( OUT obj->pStages );
	packer.Push( obj->pVertexInputState );
	 VPackStruct( BitCast<VkBaseInStructure const*>(obj->pVertexInputState), packer );
	packer.Pop( OUT obj->pVertexInputState );
	packer.Push( obj->pInputAssemblyState );
	 VPackStruct( BitCast<VkBaseInStructure const*>(obj->pInputAssemblyState), packer );
	packer.Pop( OUT obj->pInputAssemblyState );
	packer.Push( obj->pTessellationState );
	 VPackStruct( BitCast<VkBaseInStructure const*>(obj->pTessellationState), packer );
	packer.Pop( OUT obj->pTessellationState );
	packer.Push( obj->pViewportState );
	 VPackStruct( BitCast<VkBaseInStructure const*>(obj->pViewportState), packer );
	packer.Pop( OUT obj->pViewportState );
	packer.Push( obj->pRasterizationState );
	 VPackStruct( BitCast<VkBaseInStructure const*>(obj->pRasterizationState), packer );
	packer.Pop( OUT obj->pRasterizationState );
	packer.Push( obj->pMultisampleState );
	 VPackStruct( BitCast<VkBaseInStructure const*>(obj->pMultisampleState), packer );
	packer.Pop( OUT obj->pMultisampleState );
	packer.Push( obj->pDepthStencilState );
	 VPackStruct( BitCast<VkBaseInStructure const*>(obj->pDepthStencilState), packer );
	packer.Pop( OUT obj->pDepthStencilState );
	packer.Push( obj->pColorBlendState );
	 VPackStruct( BitCast<VkBaseInStructure const*>(obj->pColorBlendState), packer );
	packer.Pop( OUT obj->pColorBlendState );
	packer.Push( obj->pDynamicState );
	 VPackStruct( BitCast<VkBaseInStructure const*>(obj->pDynamicState), packer );
	packer.Pop( OUT obj->pDynamicState );
	packer.RemapVkResource( INOUT &obj->layout );
	packer.RemapVkResource( INOUT &obj->renderPass );
	packer.RemapVkResource( INOUT &obj->basePipelineHandle );
	packer.EndStruct( *obj );
}


void VPack_VkSamplerYcbcrConversionInfo (const VkSamplerYcbcrConversionInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.RemapVkResource( INOUT &obj->conversion );
	packer.EndStruct( *obj );
}


void VPack_VkComputePipelineCreateInfo (const VkComputePipelineCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	VPackStruct( BitCast<VkBaseInStructure const*>(&obj->stage), packer );
	packer.RemapVkResource( INOUT &obj->layout );
	packer.RemapVkResource( INOUT &obj->basePipelineHandle );
	packer.EndStruct( *obj );
}


void VPack_VkPushConstantRange (const VkPushConstantRange *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.EndStruct( *obj );
}


void VPack_VkPipelineLayoutCreateInfo (const VkPipelineLayoutCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pSetLayouts );
	 for (uint i = 0; obj->pSetLayouts and i < obj->setLayoutCount; ++i) {
		packer << (obj->pSetLayouts[i]);
	 }
	packer.Pop( OUT obj->pSetLayouts );
	packer.Push( obj->pPushConstantRanges );
	 for (uint i = 0; obj->pPushConstantRanges and i < obj->pushConstantRangeCount; ++i) {
		VPack_VkPushConstantRange( obj->pPushConstantRanges + i, packer );
	 }
	packer.Pop( OUT obj->pPushConstantRanges );
	packer.EndStruct( *obj );
}


void VPack_VkSamplerCreateInfo (const VkSamplerCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkDescriptorSetLayoutBinding (const VkDescriptorSetLayoutBinding *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.Push( obj->pImmutableSamplers );
	 for (uint i = 0; obj->pImmutableSamplers and i < obj->descriptorCount; ++i) {
		packer << (obj->pImmutableSamplers[i]);
	 }
	packer.Pop( OUT obj->pImmutableSamplers );
	packer.EndStruct( *obj );
}


void VPack_VkDescriptorSetLayoutCreateInfo (const VkDescriptorSetLayoutCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pBindings );
	 for (uint i = 0; obj->pBindings and i < obj->bindingCount; ++i) {
		VPack_VkDescriptorSetLayoutBinding( obj->pBindings + i, packer );
	 }
	packer.Pop( OUT obj->pBindings );
	packer.EndStruct( *obj );
}


void VPack_VkDescriptorPoolSize (const VkDescriptorPoolSize *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.EndStruct( *obj );
}


void VPack_VkDescriptorPoolCreateInfo (const VkDescriptorPoolCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pPoolSizes );
	 for (uint i = 0; obj->pPoolSizes and i < obj->poolSizeCount; ++i) {
		VPack_VkDescriptorPoolSize( obj->pPoolSizes + i, packer );
	 }
	packer.Pop( OUT obj->pPoolSizes );
	packer.EndStruct( *obj );
}


void VPack_VkDescriptorSetAllocateInfo (const VkDescriptorSetAllocateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.RemapVkResource( INOUT &obj->descriptorPool );
	packer.Push( obj->pSetLayouts );
	 for (uint i = 0; obj->pSetLayouts and i < obj->descriptorSetCount; ++i) {
		packer << (obj->pSetLayouts[i]);
	 }
	packer.Pop( OUT obj->pSetLayouts );
	packer.EndStruct( *obj );
}


void VPack_VkClearValue (const VkClearValue *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	VPack_VkClearColorValue( &obj->color, packer );
	VPack_VkClearDepthStencilValue( &obj->depthStencil, packer );
	packer.EndStruct( *obj );
}


void VPack_VkDescriptorImageInfo (const VkDescriptorImageInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.RemapVkResource( INOUT &obj->sampler );
	packer.RemapVkResource( INOUT &obj->imageView );
	packer.EndStruct( *obj );
}


void VPack_VkDescriptorBufferInfo (const VkDescriptorBufferInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.RemapVkResource( INOUT &obj->buffer );
	packer.EndStruct( *obj );
}


void VPack_VkWriteDescriptorSet (const VkWriteDescriptorSet *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.RemapVkResource( INOUT &obj->dstSet );
	packer.Push( obj->pImageInfo );
	 for (uint i = 0; obj->pImageInfo and i < obj->descriptorCount; ++i) {
		VPack_VkDescriptorImageInfo( obj->pImageInfo + i, packer );
	 }
	packer.Pop( OUT obj->pImageInfo );
	packer.Push( obj->pBufferInfo );
	 for (uint i = 0; obj->pBufferInfo and i < obj->descriptorCount; ++i) {
		VPack_VkDescriptorBufferInfo( obj->pBufferInfo + i, packer );
	 }
	packer.Pop( OUT obj->pBufferInfo );
	packer.Push( obj->pTexelBufferView );
	 for (uint i = 0; obj->pTexelBufferView and i < obj->descriptorCount; ++i) {
		packer << (obj->pTexelBufferView[i]);
	 }
	packer.Pop( OUT obj->pTexelBufferView );
	packer.EndStruct( *obj );
}


void VPack_VkCopyDescriptorSet (const VkCopyDescriptorSet *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.RemapVkResource( INOUT &obj->srcSet );
	packer.RemapVkResource( INOUT &obj->dstSet );
	packer.EndStruct( *obj );
}


void VPack_VkFramebufferCreateInfo (const VkFramebufferCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.RemapVkResource( INOUT &obj->renderPass );
	packer.Push( obj->pAttachments );
	 for (uint i = 0; obj->pAttachments and i < obj->attachmentCount; ++i) {
		packer << (obj->pAttachments[i]);
	 }
	packer.Pop( OUT obj->pAttachments );
	packer.EndStruct( *obj );
}


void VPack_VkAttachmentDescription (const VkAttachmentDescription *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.EndStruct( *obj );
}


void VPack_VkAttachmentReference (const VkAttachmentReference *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.EndStruct( *obj );
}


void VPack_VkSubpassDescription (const VkSubpassDescription *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.Push( obj->pInputAttachments );
	 for (uint i = 0; obj->pInputAttachments and i < obj->inputAttachmentCount; ++i) {
		VPack_VkAttachmentReference( obj->pInputAttachments + i, packer );
	 }
	packer.Pop( OUT obj->pInputAttachments );
	packer.Push( obj->pColorAttachments );
	 for (uint i = 0; obj->pColorAttachments and i < obj->colorAttachmentCount; ++i) {
		VPack_VkAttachmentReference( obj->pColorAttachments + i, packer );
	 }
	packer.Pop( OUT obj->pColorAttachments );
	packer.Push( obj->pResolveAttachments );
	 for (uint i = 0; obj->pResolveAttachments and i < obj->colorAttachmentCount; ++i) {
		VPack_VkAttachmentReference( obj->pResolveAttachments + i, packer );
	 }
	packer.Pop( OUT obj->pResolveAttachments );
	packer.Push( obj->pDepthStencilAttachment );
	 VPack_VkAttachmentReference( obj->pDepthStencilAttachment, packer );
	packer.Pop( OUT obj->pDepthStencilAttachment );
	packer.Push( obj->pPreserveAttachments );
	 for (uint i = 0; obj->pPreserveAttachments and i < obj->preserveAttachmentCount; ++i) {
		packer << (obj->pPreserveAttachments[i]);
	 }
	packer.Pop( OUT obj->pPreserveAttachments );
	packer.EndStruct( *obj );
}


void VPack_VkSubpassDependency (const VkSubpassDependency *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.EndStruct( *obj );
}


void VPack_VkRenderPassCreateInfo (const VkRenderPassCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pAttachments );
	 for (uint i = 0; obj->pAttachments and i < obj->attachmentCount; ++i) {
		VPack_VkAttachmentDescription( obj->pAttachments + i, packer );
	 }
	packer.Pop( OUT obj->pAttachments );
	packer.Push( obj->pSubpasses );
	 for (uint i = 0; obj->pSubpasses and i < obj->subpassCount; ++i) {
		VPack_VkSubpassDescription( obj->pSubpasses + i, packer );
	 }
	packer.Pop( OUT obj->pSubpasses );
	packer.Push( obj->pDependencies );
	 for (uint i = 0; obj->pDependencies and i < obj->dependencyCount; ++i) {
		VPack_VkSubpassDependency( obj->pDependencies + i, packer );
	 }
	packer.Pop( OUT obj->pDependencies );
	packer.EndStruct( *obj );
}


void VPack_VkCommandPoolCreateInfo (const VkCommandPoolCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkCommandBufferAllocateInfo (const VkCommandBufferAllocateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.RemapVkResource( INOUT &obj->commandPool );
	packer.EndStruct( *obj );
}


void VPack_VkCommandBufferBeginInfo (const VkCommandBufferBeginInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pInheritanceInfo );
	 VPackStruct( BitCast<VkBaseInStructure const*>(obj->pInheritanceInfo), packer );
	packer.Pop( OUT obj->pInheritanceInfo );
	packer.EndStruct( *obj );
}


void VPack_VkBufferCopy (const VkBufferCopy *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.EndStruct( *obj );
}


void VPack_VkImageSubresourceLayers (const VkImageSubresourceLayers *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.EndStruct( *obj );
}


void VPack_VkImageBlit (const VkImageBlit *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	VPack_VkImageSubresourceLayers( &obj->srcSubresource, packer );
	for (uint i = 0; obj->srcOffsets and i < CountOf(obj->srcOffsets); ++i) {
		VPack_VkOffset3D( &obj->srcOffsets[i], packer );
	}
	VPack_VkImageSubresourceLayers( &obj->dstSubresource, packer );
	for (uint i = 0; obj->dstOffsets and i < CountOf(obj->dstOffsets); ++i) {
		VPack_VkOffset3D( &obj->dstOffsets[i], packer );
	}
	packer.EndStruct( *obj );
}


void VPack_VkBufferImageCopy (const VkBufferImageCopy *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	VPack_VkImageSubresourceLayers( &obj->imageSubresource, packer );
	VPack_VkOffset3D( &obj->imageOffset, packer );
	VPack_VkExtent3D( &obj->imageExtent, packer );
	packer.EndStruct( *obj );
}


void VPack_VkClearColorValue (const VkClearColorValue *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.EndStruct( *obj );
}


void VPack_VkClearDepthStencilValue (const VkClearDepthStencilValue *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.EndStruct( *obj );
}


void VPack_VkClearAttachment (const VkClearAttachment *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	VPack_VkClearValue( &obj->clearValue, packer );
	packer.EndStruct( *obj );
}


void VPack_VkClearRect (const VkClearRect *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	VPack_VkRect2D( &obj->rect, packer );
	packer.EndStruct( *obj );
}


void VPack_VkViewportSwizzleNV (const VkViewportSwizzleNV *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.EndStruct( *obj );
}


void VPack_VkBufferMemoryBarrier (const VkBufferMemoryBarrier *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.RemapVkResource( INOUT &obj->buffer );
	packer.EndStruct( *obj );
}


void VPack_VkImageMemoryBarrier (const VkImageMemoryBarrier *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.RemapVkResource( INOUT &obj->image );
	VPack_VkImageSubresourceRange( &obj->subresourceRange, packer );
	packer.EndStruct( *obj );
}


void VPack_VkPipelineCoverageToColorStateCreateInfoNV (const VkPipelineCoverageToColorStateCreateInfoNV *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_TO_COLOR_STATE_CREATE_INFO_NV );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkShadingRatePaletteNV (const VkShadingRatePaletteNV *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.Push( obj->pShadingRatePaletteEntries );
	 for (uint i = 0; obj->pShadingRatePaletteEntries and i < obj->shadingRatePaletteEntryCount; ++i) {
		packer << (obj->pShadingRatePaletteEntries[i]);
	 }
	packer.Pop( OUT obj->pShadingRatePaletteEntries );
	packer.EndStruct( *obj );
}


void VPack_VkBindBufferMemoryInfo (const VkBindBufferMemoryInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.RemapVkResource( INOUT &obj->buffer );
	packer.RemapVkResource( INOUT &obj->memory );
	packer.EndStruct( *obj );
}


void VPack_VkBindImageMemoryInfo (const VkBindImageMemoryInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.RemapVkResource( INOUT &obj->image );
	packer.RemapVkResource( INOUT &obj->memory );
	packer.EndStruct( *obj );
}


void VPack_VkSubpassEndInfoKHR (const VkSubpassEndInfoKHR *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_SUBPASS_END_INFO_KHR );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkMemoryDedicatedAllocateInfo (const VkMemoryDedicatedAllocateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.RemapVkResource( INOUT &obj->image );
	packer.RemapVkResource( INOUT &obj->buffer );
	packer.EndStruct( *obj );
}


void VPack_VkMemoryAllocateFlagsInfo (const VkMemoryAllocateFlagsInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkDeviceGroupRenderPassBeginInfo (const VkDeviceGroupRenderPassBeginInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_DEVICE_GROUP_RENDER_PASS_BEGIN_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pDeviceRenderAreas );
	 for (uint i = 0; obj->pDeviceRenderAreas and i < obj->deviceRenderAreaCount; ++i) {
		VPack_VkRect2D( obj->pDeviceRenderAreas + i, packer );
	 }
	packer.Pop( OUT obj->pDeviceRenderAreas );
	packer.EndStruct( *obj );
}


void VPack_VkDeviceGroupCommandBufferBeginInfo (const VkDeviceGroupCommandBufferBeginInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_DEVICE_GROUP_COMMAND_BUFFER_BEGIN_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkDeviceGroupSubmitInfo (const VkDeviceGroupSubmitInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_DEVICE_GROUP_SUBMIT_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pWaitSemaphoreDeviceIndices );
	 for (uint i = 0; obj->pWaitSemaphoreDeviceIndices and i < obj->waitSemaphoreCount; ++i) {
		packer << (obj->pWaitSemaphoreDeviceIndices[i]);
	 }
	packer.Pop( OUT obj->pWaitSemaphoreDeviceIndices );
	packer.Push( obj->pCommandBufferDeviceMasks );
	 for (uint i = 0; obj->pCommandBufferDeviceMasks and i < obj->commandBufferCount; ++i) {
		packer << (obj->pCommandBufferDeviceMasks[i]);
	 }
	packer.Pop( OUT obj->pCommandBufferDeviceMasks );
	packer.Push( obj->pSignalSemaphoreDeviceIndices );
	 for (uint i = 0; obj->pSignalSemaphoreDeviceIndices and i < obj->signalSemaphoreCount; ++i) {
		packer << (obj->pSignalSemaphoreDeviceIndices[i]);
	 }
	packer.Pop( OUT obj->pSignalSemaphoreDeviceIndices );
	packer.EndStruct( *obj );
}


void VPack_VkDeviceGroupBindSparseInfo (const VkDeviceGroupBindSparseInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_DEVICE_GROUP_BIND_SPARSE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkBindBufferMemoryDeviceGroupInfo (const VkBindBufferMemoryDeviceGroupInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_DEVICE_GROUP_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pDeviceIndices );
	 for (uint i = 0; obj->pDeviceIndices and i < obj->deviceIndexCount; ++i) {
		packer << (obj->pDeviceIndices[i]);
	 }
	packer.Pop( OUT obj->pDeviceIndices );
	packer.EndStruct( *obj );
}


void VPack_VkBindImageMemoryDeviceGroupInfo (const VkBindImageMemoryDeviceGroupInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_DEVICE_GROUP_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pDeviceIndices );
	 for (uint i = 0; obj->pDeviceIndices and i < obj->deviceIndexCount; ++i) {
		packer << (obj->pDeviceIndices[i]);
	 }
	packer.Pop( OUT obj->pDeviceIndices );
	packer.Push( obj->pSplitInstanceBindRegions );
	 for (uint i = 0; obj->pSplitInstanceBindRegions and i < obj->splitInstanceBindRegionCount; ++i) {
		VPack_VkRect2D( obj->pSplitInstanceBindRegions + i, packer );
	 }
	packer.Pop( OUT obj->pSplitInstanceBindRegions );
	packer.EndStruct( *obj );
}


void VPack_VkSamplerReductionModeCreateInfoEXT (const VkSamplerReductionModeCreateInfoEXT *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_SAMPLER_REDUCTION_MODE_CREATE_INFO_EXT );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkAttachmentReference2KHR (const VkAttachmentReference2KHR *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2_KHR );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkInputAttachmentAspectReference (const VkInputAttachmentAspectReference *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.EndStruct( *obj );
}


void VPack_VkRenderPassInputAttachmentAspectCreateInfo (const VkRenderPassInputAttachmentAspectCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_RENDER_PASS_INPUT_ATTACHMENT_ASPECT_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pAspectReferences );
	 for (uint i = 0; obj->pAspectReferences and i < obj->aspectReferenceCount; ++i) {
		VPack_VkInputAttachmentAspectReference( obj->pAspectReferences + i, packer );
	 }
	packer.Pop( OUT obj->pAspectReferences );
	packer.EndStruct( *obj );
}


void VPack_VkImageViewUsageCreateInfo (const VkImageViewUsageCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkRenderPassMultiviewCreateInfo (const VkRenderPassMultiviewCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_RENDER_PASS_MULTIVIEW_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pViewMasks );
	 for (uint i = 0; obj->pViewMasks and i < obj->subpassCount; ++i) {
		packer << (obj->pViewMasks[i]);
	 }
	packer.Pop( OUT obj->pViewMasks );
	packer.Push( obj->pViewOffsets );
	 for (uint i = 0; obj->pViewOffsets and i < obj->dependencyCount; ++i) {
		packer << (obj->pViewOffsets[i]);
	 }
	packer.Pop( OUT obj->pViewOffsets );
	packer.Push( obj->pCorrelationMasks );
	 for (uint i = 0; obj->pCorrelationMasks and i < obj->correlationMaskCount; ++i) {
		packer << (obj->pCorrelationMasks[i]);
	 }
	packer.Pop( OUT obj->pCorrelationMasks );
	packer.EndStruct( *obj );
}


void VPack_VkRenderPassSampleLocationsBeginInfoEXT (const VkRenderPassSampleLocationsBeginInfoEXT *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_RENDER_PASS_SAMPLE_LOCATIONS_BEGIN_INFO_EXT );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pAttachmentInitialSampleLocations );
	 for (uint i = 0; obj->pAttachmentInitialSampleLocations and i < obj->attachmentInitialSampleLocationsCount; ++i) {
		VPack_VkAttachmentSampleLocationsEXT( obj->pAttachmentInitialSampleLocations + i, packer );
	 }
	packer.Pop( OUT obj->pAttachmentInitialSampleLocations );
	packer.Push( obj->pPostSubpassSampleLocations );
	 for (uint i = 0; obj->pPostSubpassSampleLocations and i < obj->postSubpassSampleLocationsCount; ++i) {
		VPack_VkSubpassSampleLocationsEXT( obj->pPostSubpassSampleLocations + i, packer );
	 }
	packer.Pop( OUT obj->pPostSubpassSampleLocations );
	packer.EndStruct( *obj );
}


void VPack_VkDeviceQueueInfo2 (const VkDeviceQueueInfo2 *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2 );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkProtectedSubmitInfo (const VkProtectedSubmitInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_PROTECTED_SUBMIT_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkSamplerYcbcrConversionCreateInfo (const VkSamplerYcbcrConversionCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	VPack_VkComponentMapping( &obj->components, packer );
	packer.EndStruct( *obj );
}


void VPack_VkBindImagePlaneMemoryInfo (const VkBindImagePlaneMemoryInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_BIND_IMAGE_PLANE_MEMORY_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkDescriptorUpdateTemplateCreateInfo (const VkDescriptorUpdateTemplateCreateInfo *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_CREATE_INFO );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pDescriptorUpdateEntries );
	 for (uint i = 0; obj->pDescriptorUpdateEntries and i < obj->descriptorUpdateEntryCount; ++i) {
		VPack_VkDescriptorUpdateTemplateEntry( obj->pDescriptorUpdateEntries + i, packer );
	 }
	packer.Pop( OUT obj->pDescriptorUpdateEntries );
	packer.RemapVkResource( INOUT &obj->descriptorSetLayout );
	packer.RemapVkResource( INOUT &obj->pipelineLayout );
	packer.EndStruct( *obj );
}


void VPack_VkCoarseSampleLocationNV (const VkCoarseSampleLocationNV *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.EndStruct( *obj );
}


void VPack_VkImageSwapchainCreateInfoKHR (const VkImageSwapchainCreateInfoKHR *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_IMAGE_SWAPCHAIN_CREATE_INFO_KHR );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.RemapVkResource( INOUT &obj->swapchain );
	packer.EndStruct( *obj );
}


void VPack_VkBindImageMemorySwapchainInfoKHR (const VkBindImageMemorySwapchainInfoKHR *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_SWAPCHAIN_INFO_KHR );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.RemapVkResource( INOUT &obj->swapchain );
	packer.EndStruct( *obj );
}


void VPack_VkVertexInputBindingDivisorDescriptionEXT (const VkVertexInputBindingDivisorDescriptionEXT *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.EndStruct( *obj );
}


void VPack_VkSubpassSampleLocationsEXT (const VkSubpassSampleLocationsEXT *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	VPackStruct( BitCast<VkBaseInStructure const*>(&obj->sampleLocationsInfo), packer );
	packer.EndStruct( *obj );
}


void VPack_VkPipelineColorBlendAdvancedStateCreateInfoEXT (const VkPipelineColorBlendAdvancedStateCreateInfoEXT *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_ADVANCED_STATE_CREATE_INFO_EXT );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkAttachmentDescription2KHR (const VkAttachmentDescription2KHR *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_2_KHR );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkSubpassDescription2KHR (const VkSubpassDescription2KHR *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_2_KHR );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pInputAttachments );
	 for (uint i = 0; obj->pInputAttachments and i < obj->inputAttachmentCount; ++i) {
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pInputAttachments + i), packer );
	 }
	packer.Pop( OUT obj->pInputAttachments );
	packer.Push( obj->pColorAttachments );
	 for (uint i = 0; obj->pColorAttachments and i < obj->colorAttachmentCount; ++i) {
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pColorAttachments + i), packer );
	 }
	packer.Pop( OUT obj->pColorAttachments );
	packer.Push( obj->pResolveAttachments );
	 for (uint i = 0; obj->pResolveAttachments and i < obj->colorAttachmentCount; ++i) {
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pResolveAttachments + i), packer );
	 }
	packer.Pop( OUT obj->pResolveAttachments );
	packer.Push( obj->pDepthStencilAttachment );
	 VPackStruct( BitCast<VkBaseInStructure const*>(obj->pDepthStencilAttachment), packer );
	packer.Pop( OUT obj->pDepthStencilAttachment );
	packer.Push( obj->pPreserveAttachments );
	 for (uint i = 0; obj->pPreserveAttachments and i < obj->preserveAttachmentCount; ++i) {
		packer << (obj->pPreserveAttachments[i]);
	 }
	packer.Pop( OUT obj->pPreserveAttachments );
	packer.EndStruct( *obj );
}


void VPack_VkSubpassDependency2KHR (const VkSubpassDependency2KHR *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_SUBPASS_DEPENDENCY_2_KHR );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkRenderPassCreateInfo2KHR (const VkRenderPassCreateInfo2KHR *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO_2_KHR );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pAttachments );
	 for (uint i = 0; obj->pAttachments and i < obj->attachmentCount; ++i) {
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pAttachments + i), packer );
	 }
	packer.Pop( OUT obj->pAttachments );
	packer.Push( obj->pSubpasses );
	 for (uint i = 0; obj->pSubpasses and i < obj->subpassCount; ++i) {
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pSubpasses + i), packer );
	 }
	packer.Pop( OUT obj->pSubpasses );
	packer.Push( obj->pDependencies );
	 for (uint i = 0; obj->pDependencies and i < obj->dependencyCount; ++i) {
		VPackStruct( BitCast<VkBaseInStructure const*>(obj->pDependencies + i), packer );
	 }
	packer.Pop( OUT obj->pDependencies );
	packer.Push( obj->pCorrelatedViewMasks );
	 for (uint i = 0; obj->pCorrelatedViewMasks and i < obj->correlatedViewMaskCount; ++i) {
		packer << (obj->pCorrelatedViewMasks[i]);
	 }
	packer.Pop( OUT obj->pCorrelatedViewMasks );
	packer.EndStruct( *obj );
}


void VPack_VkSubpassBeginInfoKHR (const VkSubpassBeginInfoKHR *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_SUBPASS_BEGIN_INFO_KHR );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkDescriptorSetVariableDescriptorCountAllocateInfoEXT (const VkDescriptorSetVariableDescriptorCountAllocateInfoEXT *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_ALLOCATE_INFO_EXT );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pDescriptorCounts );
	 for (uint i = 0; obj->pDescriptorCounts and i < obj->descriptorSetCount; ++i) {
		packer << (obj->pDescriptorCounts[i]);
	 }
	packer.Pop( OUT obj->pDescriptorCounts );
	packer.EndStruct( *obj );
}


void VPack_VkDedicatedAllocationMemoryAllocateInfoNV (const VkDedicatedAllocationMemoryAllocateInfoNV *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_MEMORY_ALLOCATE_INFO_NV );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.RemapVkResource( INOUT &obj->image );
	packer.RemapVkResource( INOUT &obj->buffer );
	packer.EndStruct( *obj );
}


void VPack_VkPipelineRasterizationStateRasterizationOrderAMD (const VkPipelineRasterizationStateRasterizationOrderAMD *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_RASTERIZATION_ORDER_AMD );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkDebugMarkerObjectNameInfoEXT (const VkDebugMarkerObjectNameInfoEXT *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_NAME_INFO_EXT );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pObjectName );
	 packer.AddString( obj->pObjectName );
	packer.Pop( OUT obj->pObjectName );
	packer.EndStruct( *obj );
}


void VPack_VkDebugMarkerMarkerInfoEXT (const VkDebugMarkerMarkerInfoEXT *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_DEBUG_MARKER_MARKER_INFO_EXT );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pMarkerName );
	 packer.AddString( obj->pMarkerName );
	packer.Pop( OUT obj->pMarkerName );
	packer.EndStruct( *obj );
}


void VPack_VkDedicatedAllocationImageCreateInfoNV (const VkDedicatedAllocationImageCreateInfoNV *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_IMAGE_CREATE_INFO_NV );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkDedicatedAllocationBufferCreateInfoNV (const VkDedicatedAllocationBufferCreateInfoNV *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_BUFFER_CREATE_INFO_NV );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkCoarseSampleOrderCustomNV (const VkCoarseSampleOrderCustomNV *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.Push( obj->pSampleLocations );
	 for (uint i = 0; obj->pSampleLocations and i < obj->sampleLocationCount; ++i) {
		VPack_VkCoarseSampleLocationNV( obj->pSampleLocations + i, packer );
	 }
	packer.Pop( OUT obj->pSampleLocations );
	packer.EndStruct( *obj );
}


void VPack_VkImageViewASTCDecodeModeEXT (const VkImageViewASTCDecodeModeEXT *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_IMAGE_VIEW_ASTC_DECODE_MODE_EXT );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkCommandBufferInheritanceConditionalRenderingInfoEXT (const VkCommandBufferInheritanceConditionalRenderingInfoEXT *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_CONDITIONAL_RENDERING_INFO_EXT );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkViewportWScalingNV (const VkViewportWScalingNV *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.EndStruct( *obj );
}


void VPack_VkPipelineViewportExclusiveScissorStateCreateInfoNV (const VkPipelineViewportExclusiveScissorStateCreateInfoNV *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_EXCLUSIVE_SCISSOR_STATE_CREATE_INFO_NV );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pExclusiveScissors );
	 for (uint i = 0; obj->pExclusiveScissors and i < obj->exclusiveScissorCount; ++i) {
		VPack_VkRect2D( obj->pExclusiveScissors + i, packer );
	 }
	packer.Pop( OUT obj->pExclusiveScissors );
	packer.EndStruct( *obj );
}


void VPack_VkPipelineViewportWScalingStateCreateInfoNV (const VkPipelineViewportWScalingStateCreateInfoNV *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_W_SCALING_STATE_CREATE_INFO_NV );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pViewportWScalings );
	 for (uint i = 0; obj->pViewportWScalings and i < obj->viewportCount; ++i) {
		VPack_VkViewportWScalingNV( obj->pViewportWScalings + i, packer );
	 }
	packer.Pop( OUT obj->pViewportWScalings );
	packer.EndStruct( *obj );
}


void VPack_VkPipelineViewportSwizzleStateCreateInfoNV (const VkPipelineViewportSwizzleStateCreateInfoNV *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_SWIZZLE_STATE_CREATE_INFO_NV );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pViewportSwizzles );
	 for (uint i = 0; obj->pViewportSwizzles and i < obj->viewportCount; ++i) {
		VPack_VkViewportSwizzleNV( obj->pViewportSwizzles + i, packer );
	 }
	packer.Pop( OUT obj->pViewportSwizzles );
	packer.EndStruct( *obj );
}


void VPack_VkPipelineDiscardRectangleStateCreateInfoEXT (const VkPipelineDiscardRectangleStateCreateInfoEXT *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_PIPELINE_DISCARD_RECTANGLE_STATE_CREATE_INFO_EXT );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pDiscardRectangles );
	 for (uint i = 0; obj->pDiscardRectangles and i < obj->discardRectangleCount; ++i) {
		VPack_VkRect2D( obj->pDiscardRectangles + i, packer );
	 }
	packer.Pop( OUT obj->pDiscardRectangles );
	packer.EndStruct( *obj );
}


void VPack_VkPipelineRasterizationConservativeStateCreateInfoEXT (const VkPipelineRasterizationConservativeStateCreateInfoEXT *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_CONSERVATIVE_STATE_CREATE_INFO_EXT );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkWriteDescriptorSetInlineUniformBlockEXT (const VkWriteDescriptorSetInlineUniformBlockEXT *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_INLINE_UNIFORM_BLOCK_EXT );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pData );
	 packer.AddArray( obj->pData, obj->dataSize );
	packer.Pop( OUT obj->pData );
	packer.EndStruct( *obj );
}


void VPack_VkPipelineViewportShadingRateImageStateCreateInfoNV (const VkPipelineViewportShadingRateImageStateCreateInfoNV *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_SHADING_RATE_IMAGE_STATE_CREATE_INFO_NV );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pShadingRatePalettes );
	 VPack_VkShadingRatePaletteNV( obj->pShadingRatePalettes, packer );
	packer.Pop( OUT obj->pShadingRatePalettes );
	packer.EndStruct( *obj );
}


void VPack_VkDescriptorPoolInlineUniformBlockCreateInfoEXT (const VkDescriptorPoolInlineUniformBlockCreateInfoEXT *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_INLINE_UNIFORM_BLOCK_CREATE_INFO_EXT );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkSampleLocationEXT (const VkSampleLocationEXT *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	packer.EndStruct( *obj );
}


void VPack_VkSampleLocationsInfoEXT (const VkSampleLocationsInfoEXT *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_SAMPLE_LOCATIONS_INFO_EXT );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	VPack_VkExtent2D( &obj->sampleLocationGridSize, packer );
	packer.Push( obj->pSampleLocations );
	 for (uint i = 0; obj->pSampleLocations and i < obj->sampleLocationsCount; ++i) {
		VPack_VkSampleLocationEXT( obj->pSampleLocations + i, packer );
	 }
	packer.Pop( OUT obj->pSampleLocations );
	packer.EndStruct( *obj );
}


void VPack_VkAttachmentSampleLocationsEXT (const VkAttachmentSampleLocationsEXT *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	VPackStruct( BitCast<VkBaseInStructure const*>(&obj->sampleLocationsInfo), packer );
	packer.EndStruct( *obj );
}


void VPack_VkPipelineSampleLocationsStateCreateInfoEXT (const VkPipelineSampleLocationsStateCreateInfoEXT *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_PIPELINE_SAMPLE_LOCATIONS_STATE_CREATE_INFO_EXT );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	VPackStruct( BitCast<VkBaseInStructure const*>(&obj->sampleLocationsInfo), packer );
	packer.EndStruct( *obj );
}


void VPack_VkPipelineCoverageModulationStateCreateInfoNV (const VkPipelineCoverageModulationStateCreateInfoNV *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_MODULATION_STATE_CREATE_INFO_NV );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pCoverageModulationTable );
	 for (uint i = 0; obj->pCoverageModulationTable and i < obj->coverageModulationTableCount; ++i) {
		packer << (obj->pCoverageModulationTable[i]);
	 }
	packer.Pop( OUT obj->pCoverageModulationTable );
	packer.EndStruct( *obj );
}


void VPack_VkPipelineRepresentativeFragmentTestStateCreateInfoNV (const VkPipelineRepresentativeFragmentTestStateCreateInfoNV *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_PIPELINE_REPRESENTATIVE_FRAGMENT_TEST_STATE_CREATE_INFO_NV );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.EndStruct( *obj );
}


void VPack_VkPipelineVertexInputDivisorStateCreateInfoEXT (const VkPipelineVertexInputDivisorStateCreateInfoEXT *obj, VPacker &packer)
{
	if ( obj == null ) return;
	packer.BeginStruct();
	ASSERT( obj->sType == VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_DIVISOR_STATE_CREATE_INFO_EXT );
	packer.Push( obj->pNext );
	 VPackStruct( BitCast<VkBaseInStructure const *>(obj->pNext), packer );
	packer.Pop( OUT obj->pNext );
	packer.Push( obj->pVertexBindingDivisors );
	 for (uint i = 0; obj->pVertexBindingDivisors and i < obj->vertexBindingDivisorCount; ++i) {
		VPack_VkVertexInputBindingDivisorDescriptionEXT( obj->pVertexBindingDivisors + i, packer );
	 }
	packer.Pop( OUT obj->pVertexBindingDivisors );
	packer.EndStruct( *obj );
}


