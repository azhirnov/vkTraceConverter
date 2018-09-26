// auto-generated file

case EPacketID::VGetDeviceQueue : {
	app.vkGetDeviceQueue( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*queueFamilyIndex*/ unpacker.Get<uint32_t >(),
				/*queueIndex*/ unpacker.Get<uint32_t >(),
				/*pQueue*/ unpacker.Get<VkQueue * >() );
	break;
}

case EPacketID::VQueueSubmit : {
	VK_CALL( app.vkQueueSubmit( 
				/*queue*/ unpacker.Get<VkQueue >(),
				/*submitCount*/ unpacker.Get<uint32_t >(),
				/*pSubmits*/ unpacker.Get<const VkSubmitInfo * >(),
				/*fence*/ unpacker.Get<VkFence >() ));
	break;
}

case EPacketID::VCreateSampler : {
	VK_CALL( app.vkCreateSampler( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*pCreateInfo*/ unpacker.Get<const VkSamplerCreateInfo * >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >(),
				/*pSampler*/ unpacker.Get<VkSampler * >() ));
	break;
}

case EPacketID::VCreateEvent : {
	VK_CALL( app.vkCreateEvent( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*pCreateInfo*/ unpacker.Get<const VkEventCreateInfo * >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >(),
				/*pEvent*/ unpacker.Get<VkEvent * >() ));
	break;
}

case EPacketID::VFlushMappedMemoryRanges : {
	VK_CALL( app.vkFlushMappedMemoryRanges( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*memoryRangeCount*/ unpacker.Get<uint32_t >(),
				/*pMemoryRanges*/ unpacker.Get<const VkMappedMemoryRange * >() ));
	break;
}

case EPacketID::VCmdSetDepthBias : {
	app.vkCmdSetDepthBias( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*depthBiasConstantFactor*/ unpacker.Get<float >(),
				/*depthBiasClamp*/ unpacker.Get<float >(),
				/*depthBiasSlopeFactor*/ unpacker.Get<float >() );
	break;
}

case EPacketID::VAllocateMemory : {
	VK_CALL( app.vkAllocateMemory( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*pAllocateInfo*/ unpacker.Get<const VkMemoryAllocateInfo * >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >(),
				/*pMemory*/ unpacker.Get<VkDeviceMemory * >() ));
	break;
}

case EPacketID::VDestroyPipeline : {
	app.vkDestroyPipeline( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*pipeline*/ unpacker.Get<VkPipeline >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >() );
	break;
}

case EPacketID::VCmdDispatchIndirect : {
	app.vkCmdDispatchIndirect( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*buffer*/ unpacker.Get<VkBuffer >(),
				/*offset*/ unpacker.Get<VkDeviceSize >() );
	break;
}

case EPacketID::VQueueWaitIdle : {
	VK_CALL( app.vkQueueWaitIdle( 
				/*queue*/ unpacker.Get<VkQueue >() ));
	break;
}

case EPacketID::VCreateImage : {
	VK_CALL( app.vkCreateImage( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*pCreateInfo*/ unpacker.Get<const VkImageCreateInfo * >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >(),
				/*pImage*/ unpacker.Get<VkImage * >() ));
	break;
}

case EPacketID::VCreateDescriptorSetLayout : {
	VK_CALL( app.vkCreateDescriptorSetLayout( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*pCreateInfo*/ unpacker.Get<const VkDescriptorSetLayoutCreateInfo * >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >(),
				/*pSetLayout*/ unpacker.Get<VkDescriptorSetLayout * >() ));
	break;
}

case EPacketID::VFreeMemory : {
	app.vkFreeMemory( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*memory*/ unpacker.Get<VkDeviceMemory >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >() );
	break;
}

case EPacketID::VDeviceWaitIdle : {
	VK_CALL( app.vkDeviceWaitIdle( 
				/*device*/ unpacker.Get<VkDevice >() ));
	break;
}

case EPacketID::VCmdSetScissor : {
	app.vkCmdSetScissor( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*firstScissor*/ unpacker.Get<uint32_t >(),
				/*scissorCount*/ unpacker.Get<uint32_t >(),
				/*pScissors*/ unpacker.Get<const VkRect2D * >() );
	break;
}

case EPacketID::VBindBufferMemory : {
	VK_CALL( app.vkBindBufferMemory( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*buffer*/ unpacker.Get<VkBuffer >(),
				/*memory*/ unpacker.Get<VkDeviceMemory >(),
				/*memoryOffset*/ unpacker.Get<VkDeviceSize >() ));
	break;
}

case EPacketID::VBindImageMemory : {
	VK_CALL( app.vkBindImageMemory( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*image*/ unpacker.Get<VkImage >(),
				/*memory*/ unpacker.Get<VkDeviceMemory >(),
				/*memoryOffset*/ unpacker.Get<VkDeviceSize >() ));
	break;
}

case EPacketID::VQueueBindSparse : {
	VK_CALL( app.vkQueueBindSparse( 
				/*queue*/ unpacker.Get<VkQueue >(),
				/*bindInfoCount*/ unpacker.Get<uint32_t >(),
				/*pBindInfo*/ unpacker.Get<const VkBindSparseInfo * >(),
				/*fence*/ unpacker.Get<VkFence >() ));
	break;
}

case EPacketID::VCreateFence : {
	VK_CALL( app.vkCreateFence( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*pCreateInfo*/ unpacker.Get<const VkFenceCreateInfo * >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >(),
				/*pFence*/ unpacker.Get<VkFence * >() ));
	break;
}

case EPacketID::VDestroyFence : {
	app.vkDestroyFence( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*fence*/ unpacker.Get<VkFence >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >() );
	break;
}

case EPacketID::VCreateCommandPool : {
	VK_CALL( app.vkCreateCommandPool( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*pCreateInfo*/ unpacker.Get<const VkCommandPoolCreateInfo * >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >(),
				/*pCommandPool*/ unpacker.Get<VkCommandPool * >() ));
	break;
}

case EPacketID::VCmdPipelineBarrier : {
	app.vkCmdPipelineBarrier( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*srcStageMask*/ unpacker.Get<VkPipelineStageFlags >(),
				/*dstStageMask*/ unpacker.Get<VkPipelineStageFlags >(),
				/*dependencyFlags*/ unpacker.Get<VkDependencyFlags >(),
				/*memoryBarrierCount*/ unpacker.Get<uint32_t >(),
				/*pMemoryBarriers*/ unpacker.Get<const VkMemoryBarrier * >(),
				/*bufferMemoryBarrierCount*/ unpacker.Get<uint32_t >(),
				/*pBufferMemoryBarriers*/ unpacker.Get<const VkBufferMemoryBarrier * >(),
				/*imageMemoryBarrierCount*/ unpacker.Get<uint32_t >(),
				/*pImageMemoryBarriers*/ unpacker.Get<const VkImageMemoryBarrier * >() );
	break;
}

case EPacketID::VCmdBindPipeline : {
	app.vkCmdBindPipeline( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*pipelineBindPoint*/ unpacker.Get<VkPipelineBindPoint >(),
				/*pipeline*/ unpacker.Get<VkPipeline >() );
	break;
}

case EPacketID::VResetFences : {
	VK_CALL( app.vkResetFences( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*fenceCount*/ unpacker.Get<uint32_t >(),
				/*pFences*/ unpacker.Get<const VkFence * >() ));
	break;
}

case EPacketID::VWaitForFences : {
	VK_CALL( app.vkWaitForFences( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*fenceCount*/ unpacker.Get<uint32_t >(),
				/*pFences*/ unpacker.Get<const VkFence * >(),
				/*waitAll*/ unpacker.Get<VkBool32 >(),
				/*timeout*/ unpacker.Get<uint64_t >() ));
	break;
}

case EPacketID::VResetCommandPool : {
	VK_CALL( app.vkResetCommandPool( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*commandPool*/ unpacker.Get<VkCommandPool >(),
				/*flags*/ unpacker.Get<VkCommandPoolResetFlags >() ));
	break;
}

case EPacketID::VCreateSemaphore : {
	VK_CALL( app.vkCreateSemaphore( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*pCreateInfo*/ unpacker.Get<const VkSemaphoreCreateInfo * >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >(),
				/*pSemaphore*/ unpacker.Get<VkSemaphore * >() ));
	break;
}

case EPacketID::VDestroyBuffer : {
	app.vkDestroyBuffer( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*buffer*/ unpacker.Get<VkBuffer >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >() );
	break;
}

case EPacketID::VDestroySemaphore : {
	app.vkDestroySemaphore( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*semaphore*/ unpacker.Get<VkSemaphore >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >() );
	break;
}

case EPacketID::VDestroyEvent : {
	app.vkDestroyEvent( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*event*/ unpacker.Get<VkEvent >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >() );
	break;
}

case EPacketID::VResetDescriptorPool : {
	VK_CALL( app.vkResetDescriptorPool( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*descriptorPool*/ unpacker.Get<VkDescriptorPool >(),
				/*flags*/ unpacker.Get<VkDescriptorPoolResetFlags >() ));
	break;
}

case EPacketID::VSetEvent : {
	VK_CALL( app.vkSetEvent( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*event*/ unpacker.Get<VkEvent >() ));
	break;
}

case EPacketID::VResetEvent : {
	VK_CALL( app.vkResetEvent( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*event*/ unpacker.Get<VkEvent >() ));
	break;
}

case EPacketID::VCreateQueryPool : {
	VK_CALL( app.vkCreateQueryPool( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*pCreateInfo*/ unpacker.Get<const VkQueryPoolCreateInfo * >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >(),
				/*pQueryPool*/ unpacker.Get<VkQueryPool * >() ));
	break;
}

case EPacketID::VDestroyQueryPool : {
	app.vkDestroyQueryPool( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*queryPool*/ unpacker.Get<VkQueryPool >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >() );
	break;
}

case EPacketID::VCreateBuffer : {
	VK_CALL( app.vkCreateBuffer( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*pCreateInfo*/ unpacker.Get<const VkBufferCreateInfo * >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >(),
				/*pBuffer*/ unpacker.Get<VkBuffer * >() ));
	break;
}

case EPacketID::VCreateBufferView : {
	VK_CALL( app.vkCreateBufferView( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*pCreateInfo*/ unpacker.Get<const VkBufferViewCreateInfo * >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >(),
				/*pView*/ unpacker.Get<VkBufferView * >() ));
	break;
}

case EPacketID::VDestroyBufferView : {
	app.vkDestroyBufferView( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*bufferView*/ unpacker.Get<VkBufferView >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >() );
	break;
}

case EPacketID::VDestroyImage : {
	app.vkDestroyImage( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*image*/ unpacker.Get<VkImage >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >() );
	break;
}

case EPacketID::VCmdNextSubpass : {
	app.vkCmdNextSubpass( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*contents*/ unpacker.Get<VkSubpassContents >() );
	break;
}

case EPacketID::VCreatePipelineLayout : {
	VK_CALL( app.vkCreatePipelineLayout( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*pCreateInfo*/ unpacker.Get<const VkPipelineLayoutCreateInfo * >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >(),
				/*pPipelineLayout*/ unpacker.Get<VkPipelineLayout * >() ));
	break;
}

case EPacketID::VCreateImageView : {
	VK_CALL( app.vkCreateImageView( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*pCreateInfo*/ unpacker.Get<const VkImageViewCreateInfo * >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >(),
				/*pView*/ unpacker.Get<VkImageView * >() ));
	break;
}

case EPacketID::VCmdSetViewport : {
	app.vkCmdSetViewport( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*firstViewport*/ unpacker.Get<uint32_t >(),
				/*viewportCount*/ unpacker.Get<uint32_t >(),
				/*pViewports*/ unpacker.Get<const VkViewport * >() );
	break;
}

case EPacketID::VDestroySampler : {
	app.vkDestroySampler( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*sampler*/ unpacker.Get<VkSampler >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >() );
	break;
}

case EPacketID::VDestroyImageView : {
	app.vkDestroyImageView( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*imageView*/ unpacker.Get<VkImageView >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >() );
	break;
}

case EPacketID::VDestroyRenderPass : {
	app.vkDestroyRenderPass( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*renderPass*/ unpacker.Get<VkRenderPass >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >() );
	break;
}

case EPacketID::VCmdFillBuffer : {
	app.vkCmdFillBuffer( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*dstBuffer*/ unpacker.Get<VkBuffer >(),
				/*dstOffset*/ unpacker.Get<VkDeviceSize >(),
				/*size*/ unpacker.Get<VkDeviceSize >(),
				/*data*/ unpacker.Get<uint32_t >() );
	break;
}

case EPacketID::VCmdBindIndexBuffer : {
	app.vkCmdBindIndexBuffer( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*buffer*/ unpacker.Get<VkBuffer >(),
				/*offset*/ unpacker.Get<VkDeviceSize >(),
				/*indexType*/ unpacker.Get<VkIndexType >() );
	break;
}

case EPacketID::VDestroyShaderModule : {
	app.vkDestroyShaderModule( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*shaderModule*/ unpacker.Get<VkShaderModule >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >() );
	break;
}

case EPacketID::VDestroyPipelineCache : {
	app.vkDestroyPipelineCache( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*pipelineCache*/ unpacker.Get<VkPipelineCache >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >() );
	break;
}

case EPacketID::VMergePipelineCaches : {
	VK_CALL( app.vkMergePipelineCaches( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*dstCache*/ unpacker.Get<VkPipelineCache >(),
				/*srcCacheCount*/ unpacker.Get<uint32_t >(),
				/*pSrcCaches*/ unpacker.Get<const VkPipelineCache * >() ));
	break;
}

case EPacketID::VCreateComputePipelines : {
	VK_CALL( app.vkCreateComputePipelines( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*pipelineCache*/ unpacker.Get<VkPipelineCache >(),
				/*createInfoCount*/ unpacker.Get<uint32_t >(),
				/*pCreateInfos*/ unpacker.Get<const VkComputePipelineCreateInfo * >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >(),
				/*pPipelines*/ unpacker.Get<VkPipeline * >() ));
	break;
}

case EPacketID::VCreateGraphicsPipelines : {
	VK_CALL( app.vkCreateGraphicsPipelines( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*pipelineCache*/ unpacker.Get<VkPipelineCache >(),
				/*createInfoCount*/ unpacker.Get<uint32_t >(),
				/*pCreateInfos*/ unpacker.Get<const VkGraphicsPipelineCreateInfo * >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >(),
				/*pPipelines*/ unpacker.Get<VkPipeline * >() ));
	break;
}

case EPacketID::VResetCommandBuffer : {
	VK_CALL( app.vkResetCommandBuffer( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*flags*/ unpacker.Get<VkCommandBufferResetFlags >() ));
	break;
}

case EPacketID::VCmdCopyImage : {
	app.vkCmdCopyImage( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*srcImage*/ unpacker.Get<VkImage >(),
				/*srcImageLayout*/ unpacker.Get<VkImageLayout >(),
				/*dstImage*/ unpacker.Get<VkImage >(),
				/*dstImageLayout*/ unpacker.Get<VkImageLayout >(),
				/*regionCount*/ unpacker.Get<uint32_t >(),
				/*pRegions*/ unpacker.Get<const VkImageCopy * >() );
	break;
}

case EPacketID::VDestroyPipelineLayout : {
	app.vkDestroyPipelineLayout( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*pipelineLayout*/ unpacker.Get<VkPipelineLayout >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >() );
	break;
}

case EPacketID::VDestroyDescriptorSetLayout : {
	app.vkDestroyDescriptorSetLayout( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*descriptorSetLayout*/ unpacker.Get<VkDescriptorSetLayout >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >() );
	break;
}

case EPacketID::VAllocateCommandBuffers : {
	VK_CALL( app.vkAllocateCommandBuffers( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*pAllocateInfo*/ unpacker.Get<const VkCommandBufferAllocateInfo * >(),
				/*pCommandBuffers*/ unpacker.Get<VkCommandBuffer * >() ));
	break;
}

case EPacketID::VCreateDescriptorPool : {
	VK_CALL( app.vkCreateDescriptorPool( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*pCreateInfo*/ unpacker.Get<const VkDescriptorPoolCreateInfo * >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >(),
				/*pDescriptorPool*/ unpacker.Get<VkDescriptorPool * >() ));
	break;
}

case EPacketID::VDestroyDescriptorPool : {
	app.vkDestroyDescriptorPool( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*descriptorPool*/ unpacker.Get<VkDescriptorPool >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >() );
	break;
}

case EPacketID::VCreateFramebuffer : {
	VK_CALL( app.vkCreateFramebuffer( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*pCreateInfo*/ unpacker.Get<const VkFramebufferCreateInfo * >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >(),
				/*pFramebuffer*/ unpacker.Get<VkFramebuffer * >() ));
	break;
}

case EPacketID::VAllocateDescriptorSets : {
	VK_CALL( app.vkAllocateDescriptorSets( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*pAllocateInfo*/ unpacker.Get<const VkDescriptorSetAllocateInfo * >(),
				/*pDescriptorSets*/ unpacker.Get<VkDescriptorSet * >() ));
	break;
}

case EPacketID::VFreeDescriptorSets : {
	VK_CALL( app.vkFreeDescriptorSets( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*descriptorPool*/ unpacker.Get<VkDescriptorPool >(),
				/*descriptorSetCount*/ unpacker.Get<uint32_t >(),
				/*pDescriptorSets*/ unpacker.Get<const VkDescriptorSet * >() ));
	break;
}

case EPacketID::VCmdSetLineWidth : {
	app.vkCmdSetLineWidth( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*lineWidth*/ unpacker.Get<float >() );
	break;
}

case EPacketID::VUpdateDescriptorSets : {
	app.vkUpdateDescriptorSets( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*descriptorWriteCount*/ unpacker.Get<uint32_t >(),
				/*pDescriptorWrites*/ unpacker.Get<const VkWriteDescriptorSet * >(),
				/*descriptorCopyCount*/ unpacker.Get<uint32_t >(),
				/*pDescriptorCopies*/ unpacker.Get<const VkCopyDescriptorSet * >() );
	break;
}

case EPacketID::VDestroyFramebuffer : {
	app.vkDestroyFramebuffer( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*framebuffer*/ unpacker.Get<VkFramebuffer >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >() );
	break;
}

case EPacketID::VDestroyCommandPool : {
	app.vkDestroyCommandPool( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*commandPool*/ unpacker.Get<VkCommandPool >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >() );
	break;
}

case EPacketID::VCreateRenderPass : {
	VK_CALL( app.vkCreateRenderPass( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*pCreateInfo*/ unpacker.Get<const VkRenderPassCreateInfo * >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >(),
				/*pRenderPass*/ unpacker.Get<VkRenderPass * >() ));
	break;
}

case EPacketID::VFreeCommandBuffers : {
	app.vkFreeCommandBuffers( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*commandPool*/ unpacker.Get<VkCommandPool >(),
				/*commandBufferCount*/ unpacker.Get<uint32_t >(),
				/*pCommandBuffers*/ unpacker.Get<const VkCommandBuffer * >() );
	break;
}

case EPacketID::VBeginCommandBuffer : {
	VK_CALL( app.vkBeginCommandBuffer( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*pBeginInfo*/ unpacker.Get<const VkCommandBufferBeginInfo * >() ));
	break;
}

case EPacketID::VEndCommandBuffer : {
	VK_CALL( app.vkEndCommandBuffer( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >() ));
	break;
}

case EPacketID::VCmdBindVertexBuffers : {
	app.vkCmdBindVertexBuffers( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*firstBinding*/ unpacker.Get<uint32_t >(),
				/*bindingCount*/ unpacker.Get<uint32_t >(),
				/*pBuffers*/ unpacker.Get<const VkBuffer * >(),
				/*pOffsets*/ unpacker.Get<const VkDeviceSize * >() );
	break;
}

case EPacketID::VCmdSetBlendConstants : {
	app.vkCmdSetBlendConstants( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*blendConstants*/ unpacker.Get<const float [ 4 ] >() );
	break;
}

case EPacketID::VCmdSetDepthBounds : {
	app.vkCmdSetDepthBounds( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*minDepthBounds*/ unpacker.Get<float >(),
				/*maxDepthBounds*/ unpacker.Get<float >() );
	break;
}

case EPacketID::VCmdSetStencilCompareMask : {
	app.vkCmdSetStencilCompareMask( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*faceMask*/ unpacker.Get<VkStencilFaceFlags >(),
				/*compareMask*/ unpacker.Get<uint32_t >() );
	break;
}

case EPacketID::VCmdSetStencilWriteMask : {
	app.vkCmdSetStencilWriteMask( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*faceMask*/ unpacker.Get<VkStencilFaceFlags >(),
				/*writeMask*/ unpacker.Get<uint32_t >() );
	break;
}

case EPacketID::VCmdSetStencilReference : {
	app.vkCmdSetStencilReference( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*faceMask*/ unpacker.Get<VkStencilFaceFlags >(),
				/*reference*/ unpacker.Get<uint32_t >() );
	break;
}

case EPacketID::VCmdBindDescriptorSets : {
	app.vkCmdBindDescriptorSets( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*pipelineBindPoint*/ unpacker.Get<VkPipelineBindPoint >(),
				/*layout*/ unpacker.Get<VkPipelineLayout >(),
				/*firstSet*/ unpacker.Get<uint32_t >(),
				/*descriptorSetCount*/ unpacker.Get<uint32_t >(),
				/*pDescriptorSets*/ unpacker.Get<const VkDescriptorSet * >(),
				/*dynamicOffsetCount*/ unpacker.Get<uint32_t >(),
				/*pDynamicOffsets*/ unpacker.Get<const uint32_t * >() );
	break;
}

case EPacketID::VCmdDraw : {
	app.vkCmdDraw( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*vertexCount*/ unpacker.Get<uint32_t >(),
				/*instanceCount*/ unpacker.Get<uint32_t >(),
				/*firstVertex*/ unpacker.Get<uint32_t >(),
				/*firstInstance*/ unpacker.Get<uint32_t >() );
	break;
}

case EPacketID::VCmdDrawIndexed : {
	app.vkCmdDrawIndexed( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*indexCount*/ unpacker.Get<uint32_t >(),
				/*instanceCount*/ unpacker.Get<uint32_t >(),
				/*firstIndex*/ unpacker.Get<uint32_t >(),
				/*vertexOffset*/ unpacker.Get<int32_t >(),
				/*firstInstance*/ unpacker.Get<uint32_t >() );
	break;
}

case EPacketID::VCmdDrawIndirect : {
	app.vkCmdDrawIndirect( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*buffer*/ unpacker.Get<VkBuffer >(),
				/*offset*/ unpacker.Get<VkDeviceSize >(),
				/*drawCount*/ unpacker.Get<uint32_t >(),
				/*stride*/ unpacker.Get<uint32_t >() );
	break;
}

case EPacketID::VCmdDrawIndexedIndirect : {
	app.vkCmdDrawIndexedIndirect( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*buffer*/ unpacker.Get<VkBuffer >(),
				/*offset*/ unpacker.Get<VkDeviceSize >(),
				/*drawCount*/ unpacker.Get<uint32_t >(),
				/*stride*/ unpacker.Get<uint32_t >() );
	break;
}

case EPacketID::VCmdDispatch : {
	app.vkCmdDispatch( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*groupCountX*/ unpacker.Get<uint32_t >(),
				/*groupCountY*/ unpacker.Get<uint32_t >(),
				/*groupCountZ*/ unpacker.Get<uint32_t >() );
	break;
}

case EPacketID::VCmdCopyBuffer : {
	app.vkCmdCopyBuffer( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*srcBuffer*/ unpacker.Get<VkBuffer >(),
				/*dstBuffer*/ unpacker.Get<VkBuffer >(),
				/*regionCount*/ unpacker.Get<uint32_t >(),
				/*pRegions*/ unpacker.Get<const VkBufferCopy * >() );
	break;
}

case EPacketID::VCmdBlitImage : {
	app.vkCmdBlitImage( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*srcImage*/ unpacker.Get<VkImage >(),
				/*srcImageLayout*/ unpacker.Get<VkImageLayout >(),
				/*dstImage*/ unpacker.Get<VkImage >(),
				/*dstImageLayout*/ unpacker.Get<VkImageLayout >(),
				/*regionCount*/ unpacker.Get<uint32_t >(),
				/*pRegions*/ unpacker.Get<const VkImageBlit * >(),
				/*filter*/ unpacker.Get<VkFilter >() );
	break;
}

case EPacketID::VCmdCopyBufferToImage : {
	app.vkCmdCopyBufferToImage( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*srcBuffer*/ unpacker.Get<VkBuffer >(),
				/*dstImage*/ unpacker.Get<VkImage >(),
				/*dstImageLayout*/ unpacker.Get<VkImageLayout >(),
				/*regionCount*/ unpacker.Get<uint32_t >(),
				/*pRegions*/ unpacker.Get<const VkBufferImageCopy * >() );
	break;
}

case EPacketID::VCmdCopyImageToBuffer : {
	app.vkCmdCopyImageToBuffer( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*srcImage*/ unpacker.Get<VkImage >(),
				/*srcImageLayout*/ unpacker.Get<VkImageLayout >(),
				/*dstBuffer*/ unpacker.Get<VkBuffer >(),
				/*regionCount*/ unpacker.Get<uint32_t >(),
				/*pRegions*/ unpacker.Get<const VkBufferImageCopy * >() );
	break;
}

case EPacketID::VCmdBeginRenderPass2KHR : {
	app.vkCmdBeginRenderPass2KHR( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*pRenderPassBegin*/ unpacker.Get<const VkRenderPassBeginInfo * >(),
				/*pSubpassBeginInfo*/ unpacker.Get<const VkSubpassBeginInfoKHR * >() );
	break;
}

case EPacketID::VCmdClearColorImage : {
	app.vkCmdClearColorImage( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*image*/ unpacker.Get<VkImage >(),
				/*imageLayout*/ unpacker.Get<VkImageLayout >(),
				/*pColor*/ unpacker.Get<const VkClearColorValue * >(),
				/*rangeCount*/ unpacker.Get<uint32_t >(),
				/*pRanges*/ unpacker.Get<const VkImageSubresourceRange * >() );
	break;
}

case EPacketID::VCmdClearDepthStencilImage : {
	app.vkCmdClearDepthStencilImage( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*image*/ unpacker.Get<VkImage >(),
				/*imageLayout*/ unpacker.Get<VkImageLayout >(),
				/*pDepthStencil*/ unpacker.Get<const VkClearDepthStencilValue * >(),
				/*rangeCount*/ unpacker.Get<uint32_t >(),
				/*pRanges*/ unpacker.Get<const VkImageSubresourceRange * >() );
	break;
}

case EPacketID::VCmdClearAttachments : {
	app.vkCmdClearAttachments( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*attachmentCount*/ unpacker.Get<uint32_t >(),
				/*pAttachments*/ unpacker.Get<const VkClearAttachment * >(),
				/*rectCount*/ unpacker.Get<uint32_t >(),
				/*pRects*/ unpacker.Get<const VkClearRect * >() );
	break;
}

case EPacketID::VCmdResolveImage : {
	app.vkCmdResolveImage( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*srcImage*/ unpacker.Get<VkImage >(),
				/*srcImageLayout*/ unpacker.Get<VkImageLayout >(),
				/*dstImage*/ unpacker.Get<VkImage >(),
				/*dstImageLayout*/ unpacker.Get<VkImageLayout >(),
				/*regionCount*/ unpacker.Get<uint32_t >(),
				/*pRegions*/ unpacker.Get<const VkImageResolve * >() );
	break;
}

case EPacketID::VCmdSetEvent : {
	app.vkCmdSetEvent( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*event*/ unpacker.Get<VkEvent >(),
				/*stageMask*/ unpacker.Get<VkPipelineStageFlags >() );
	break;
}

case EPacketID::VCmdResetEvent : {
	app.vkCmdResetEvent( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*event*/ unpacker.Get<VkEvent >(),
				/*stageMask*/ unpacker.Get<VkPipelineStageFlags >() );
	break;
}

case EPacketID::VCmdWaitEvents : {
	app.vkCmdWaitEvents( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*eventCount*/ unpacker.Get<uint32_t >(),
				/*pEvents*/ unpacker.Get<const VkEvent * >(),
				/*srcStageMask*/ unpacker.Get<VkPipelineStageFlags >(),
				/*dstStageMask*/ unpacker.Get<VkPipelineStageFlags >(),
				/*memoryBarrierCount*/ unpacker.Get<uint32_t >(),
				/*pMemoryBarriers*/ unpacker.Get<const VkMemoryBarrier * >(),
				/*bufferMemoryBarrierCount*/ unpacker.Get<uint32_t >(),
				/*pBufferMemoryBarriers*/ unpacker.Get<const VkBufferMemoryBarrier * >(),
				/*imageMemoryBarrierCount*/ unpacker.Get<uint32_t >(),
				/*pImageMemoryBarriers*/ unpacker.Get<const VkImageMemoryBarrier * >() );
	break;
}

case EPacketID::VCmdBeginQuery : {
	app.vkCmdBeginQuery( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*queryPool*/ unpacker.Get<VkQueryPool >(),
				/*query*/ unpacker.Get<uint32_t >(),
				/*flags*/ unpacker.Get<VkQueryControlFlags >() );
	break;
}

case EPacketID::VCmdEndQuery : {
	app.vkCmdEndQuery( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*queryPool*/ unpacker.Get<VkQueryPool >(),
				/*query*/ unpacker.Get<uint32_t >() );
	break;
}

case EPacketID::VCmdResetQueryPool : {
	app.vkCmdResetQueryPool( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*queryPool*/ unpacker.Get<VkQueryPool >(),
				/*firstQuery*/ unpacker.Get<uint32_t >(),
				/*queryCount*/ unpacker.Get<uint32_t >() );
	break;
}

case EPacketID::VCmdCopyQueryPoolResults : {
	app.vkCmdCopyQueryPoolResults( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*queryPool*/ unpacker.Get<VkQueryPool >(),
				/*firstQuery*/ unpacker.Get<uint32_t >(),
				/*queryCount*/ unpacker.Get<uint32_t >(),
				/*dstBuffer*/ unpacker.Get<VkBuffer >(),
				/*dstOffset*/ unpacker.Get<VkDeviceSize >(),
				/*stride*/ unpacker.Get<VkDeviceSize >(),
				/*flags*/ unpacker.Get<VkQueryResultFlags >() );
	break;
}

case EPacketID::VCmdBeginRenderPass : {
	app.vkCmdBeginRenderPass( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*pRenderPassBegin*/ unpacker.Get<const VkRenderPassBeginInfo * >(),
				/*contents*/ unpacker.Get<VkSubpassContents >() );
	break;
}

case EPacketID::VCmdEndRenderPass : {
	app.vkCmdEndRenderPass( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >() );
	break;
}

case EPacketID::VCmdExecuteCommands : {
	app.vkCmdExecuteCommands( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*commandBufferCount*/ unpacker.Get<uint32_t >(),
				/*pCommandBuffers*/ unpacker.Get<const VkCommandBuffer * >() );
	break;
}

case EPacketID::VDestroyIndirectCommandsLayoutNVX : {
	app.vkDestroyIndirectCommandsLayoutNVX( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*indirectCommandsLayout*/ unpacker.Get<VkIndirectCommandsLayoutNVX >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >() );
	break;
}

case EPacketID::VBindBufferMemory2 : {
	VK_CALL( app.vkBindBufferMemory2( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*bindInfoCount*/ unpacker.Get<uint32_t >(),
				/*pBindInfos*/ unpacker.Get<const VkBindBufferMemoryInfo * >() ));
	break;
}

case EPacketID::VBindImageMemory2 : {
	VK_CALL( app.vkBindImageMemory2( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*bindInfoCount*/ unpacker.Get<uint32_t >(),
				/*pBindInfos*/ unpacker.Get<const VkBindImageMemoryInfo * >() ));
	break;
}

case EPacketID::VCmdSetDeviceMask : {
	app.vkCmdSetDeviceMask( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*deviceMask*/ unpacker.Get<uint32_t >() );
	break;
}

case EPacketID::VCmdDispatchBase : {
	app.vkCmdDispatchBase( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*baseGroupX*/ unpacker.Get<uint32_t >(),
				/*baseGroupY*/ unpacker.Get<uint32_t >(),
				/*baseGroupZ*/ unpacker.Get<uint32_t >(),
				/*groupCountX*/ unpacker.Get<uint32_t >(),
				/*groupCountY*/ unpacker.Get<uint32_t >(),
				/*groupCountZ*/ unpacker.Get<uint32_t >() );
	break;
}

case EPacketID::VTrimCommandPool : {
	app.vkTrimCommandPool( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*commandPool*/ unpacker.Get<VkCommandPool >(),
				/*flags*/ unpacker.Get<VkCommandPoolTrimFlags >() );
	break;
}

case EPacketID::VGetDeviceQueue2 : {
	app.vkGetDeviceQueue2( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*pQueueInfo*/ unpacker.Get<const VkDeviceQueueInfo2 * >(),
				/*pQueue*/ unpacker.Get<VkQueue * >() );
	break;
}

case EPacketID::VCreateSamplerYcbcrConversion : {
	VK_CALL( app.vkCreateSamplerYcbcrConversion( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*pCreateInfo*/ unpacker.Get<const VkSamplerYcbcrConversionCreateInfo * >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >(),
				/*pYcbcrConversion*/ unpacker.Get<VkSamplerYcbcrConversion * >() ));
	break;
}

case EPacketID::VDestroySamplerYcbcrConversion : {
	app.vkDestroySamplerYcbcrConversion( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*ycbcrConversion*/ unpacker.Get<VkSamplerYcbcrConversion >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >() );
	break;
}

case EPacketID::VCreateDescriptorUpdateTemplate : {
	VK_CALL( app.vkCreateDescriptorUpdateTemplate( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*pCreateInfo*/ unpacker.Get<const VkDescriptorUpdateTemplateCreateInfo * >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >(),
				/*pDescriptorUpdateTemplate*/ unpacker.Get<VkDescriptorUpdateTemplate * >() ));
	break;
}

case EPacketID::VDestroyDescriptorUpdateTemplate : {
	app.vkDestroyDescriptorUpdateTemplate( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*descriptorUpdateTemplate*/ unpacker.Get<VkDescriptorUpdateTemplate >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >() );
	break;
}

case EPacketID::VCmdPushDescriptorSetKHR : {
	app.vkCmdPushDescriptorSetKHR( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*pipelineBindPoint*/ unpacker.Get<VkPipelineBindPoint >(),
				/*layout*/ unpacker.Get<VkPipelineLayout >(),
				/*set*/ unpacker.Get<uint32_t >(),
				/*descriptorWriteCount*/ unpacker.Get<uint32_t >(),
				/*pDescriptorWrites*/ unpacker.Get<const VkWriteDescriptorSet * >() );
	break;
}

case EPacketID::VCreateRenderPass2KHR : {
	VK_CALL( app.vkCreateRenderPass2KHR( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*pCreateInfo*/ unpacker.Get<const VkRenderPassCreateInfo2KHR * >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >(),
				/*pRenderPass*/ unpacker.Get<VkRenderPass * >() ));
	break;
}

case EPacketID::VCmdNextSubpass2KHR : {
	app.vkCmdNextSubpass2KHR( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*pSubpassBeginInfo*/ unpacker.Get<const VkSubpassBeginInfoKHR * >(),
				/*pSubpassEndInfo*/ unpacker.Get<const VkSubpassEndInfoKHR * >() );
	break;
}

case EPacketID::VCmdEndRenderPass2KHR : {
	app.vkCmdEndRenderPass2KHR( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*pSubpassEndInfo*/ unpacker.Get<const VkSubpassEndInfoKHR * >() );
	break;
}

case EPacketID::VCmdDrawIndirectCountKHR : {
	app.vkCmdDrawIndirectCountKHR( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*buffer*/ unpacker.Get<VkBuffer >(),
				/*offset*/ unpacker.Get<VkDeviceSize >(),
				/*countBuffer*/ unpacker.Get<VkBuffer >(),
				/*countBufferOffset*/ unpacker.Get<VkDeviceSize >(),
				/*maxDrawCount*/ unpacker.Get<uint32_t >(),
				/*stride*/ unpacker.Get<uint32_t >() );
	break;
}

case EPacketID::VCmdDrawIndexedIndirectCountKHR : {
	app.vkCmdDrawIndexedIndirectCountKHR( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*buffer*/ unpacker.Get<VkBuffer >(),
				/*offset*/ unpacker.Get<VkDeviceSize >(),
				/*countBuffer*/ unpacker.Get<VkBuffer >(),
				/*countBufferOffset*/ unpacker.Get<VkDeviceSize >(),
				/*maxDrawCount*/ unpacker.Get<uint32_t >(),
				/*stride*/ unpacker.Get<uint32_t >() );
	break;
}

case EPacketID::VCmdBeginConditionalRenderingEXT : {
	app.vkCmdBeginConditionalRenderingEXT( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*pConditionalRenderingBegin*/ unpacker.Get<const VkConditionalRenderingBeginInfoEXT * >() );
	break;
}

case EPacketID::VCmdEndConditionalRenderingEXT : {
	app.vkCmdEndConditionalRenderingEXT( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >() );
	break;
}

case EPacketID::VCmdProcessCommandsNVX : {
	app.vkCmdProcessCommandsNVX( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*pProcessCommandsInfo*/ unpacker.Get<const VkCmdProcessCommandsInfoNVX * >() );
	break;
}

case EPacketID::VCmdReserveSpaceForCommandsNVX : {
	app.vkCmdReserveSpaceForCommandsNVX( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*pReserveSpaceInfo*/ unpacker.Get<const VkCmdReserveSpaceForCommandsInfoNVX * >() );
	break;
}

case EPacketID::VCreateIndirectCommandsLayoutNVX : {
	VK_CALL( app.vkCreateIndirectCommandsLayoutNVX( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*pCreateInfo*/ unpacker.Get<const VkIndirectCommandsLayoutCreateInfoNVX * >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >(),
				/*pIndirectCommandsLayout*/ unpacker.Get<VkIndirectCommandsLayoutNVX * >() ));
	break;
}

case EPacketID::VCreateObjectTableNVX : {
	VK_CALL( app.vkCreateObjectTableNVX( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*pCreateInfo*/ unpacker.Get<const VkObjectTableCreateInfoNVX * >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >(),
				/*pObjectTable*/ unpacker.Get<VkObjectTableNVX * >() ));
	break;
}

case EPacketID::VDestroyObjectTableNVX : {
	app.vkDestroyObjectTableNVX( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*objectTable*/ unpacker.Get<VkObjectTableNVX >(),
				/*pAllocator*/ unpacker.Get<const VkAllocationCallbacks * >() );
	break;
}

case EPacketID::VRegisterObjectsNVX : {
	VK_CALL( app.vkRegisterObjectsNVX( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*objectTable*/ unpacker.Get<VkObjectTableNVX >(),
				/*objectCount*/ unpacker.Get<uint32_t >(),
				/*ppObjectTableEntries*/ unpacker.Get<const VkObjectTableEntryNVX * const * >(),
				/*pObjectIndices*/ unpacker.Get<const uint32_t * >() ));
	break;
}

case EPacketID::VUnregisterObjectsNVX : {
	VK_CALL( app.vkUnregisterObjectsNVX( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*objectTable*/ unpacker.Get<VkObjectTableNVX >(),
				/*objectCount*/ unpacker.Get<uint32_t >(),
				/*pObjectEntryTypes*/ unpacker.Get<const VkObjectEntryTypeNVX * >(),
				/*pObjectIndices*/ unpacker.Get<const uint32_t * >() ));
	break;
}

case EPacketID::VCmdSetViewportWScalingNV : {
	app.vkCmdSetViewportWScalingNV( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*firstViewport*/ unpacker.Get<uint32_t >(),
				/*viewportCount*/ unpacker.Get<uint32_t >(),
				/*pViewportWScalings*/ unpacker.Get<const VkViewportWScalingNV * >() );
	break;
}

case EPacketID::VCmdSetDiscardRectangleEXT : {
	app.vkCmdSetDiscardRectangleEXT( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*firstDiscardRectangle*/ unpacker.Get<uint32_t >(),
				/*discardRectangleCount*/ unpacker.Get<uint32_t >(),
				/*pDiscardRectangles*/ unpacker.Get<const VkRect2D * >() );
	break;
}

case EPacketID::VCmdSetSampleLocationsEXT : {
	app.vkCmdSetSampleLocationsEXT( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*pSampleLocationsInfo*/ unpacker.Get<const VkSampleLocationsInfoEXT * >() );
	break;
}

case EPacketID::VDebugMarkerSetObjectNameEXT : {
	VK_CALL( app.vkDebugMarkerSetObjectNameEXT( 
				/*device*/ unpacker.Get<VkDevice >(),
				/*pNameInfo*/ unpacker.Get<const VkDebugMarkerObjectNameInfoEXT * >() ));
	break;
}

case EPacketID::VCmdDebugMarkerBeginEXT : {
	app.vkCmdDebugMarkerBeginEXT( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*pMarkerInfo*/ unpacker.Get<const VkDebugMarkerMarkerInfoEXT * >() );
	break;
}

case EPacketID::VCmdDebugMarkerEndEXT : {
	app.vkCmdDebugMarkerEndEXT( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >() );
	break;
}

case EPacketID::VCmdDebugMarkerInsertEXT : {
	app.vkCmdDebugMarkerInsertEXT( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*pMarkerInfo*/ unpacker.Get<const VkDebugMarkerMarkerInfoEXT * >() );
	break;
}

case EPacketID::VCmdPushConstants : {
	app.vkCmdPushConstants( 
				/*commandBuffer*/ unpacker.Get<VkCommandBuffer >(),
				/*layout*/ unpacker.Get<VkPipelineLayout >(),
				/*stageFlags*/ unpacker.Get<VkShaderStageFlags >(),
				/*offset*/ unpacker.Get<uint32_t >(),
				/*size*/ unpacker.Get<uint32_t >(),
				/*pValues*/ unpacker.Get<const void * >() );
	break;
}

