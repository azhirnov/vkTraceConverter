// auto-generated file

case EPacketID::VGetDeviceQueue : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  queueFamilyIndex = unpacker.Get<uint32_t>();
	auto const&  queueIndex = unpacker.Get<uint32_t>();
	auto const&  pQueue = unpacker.Get<VkQueue *>();
	vkGetDeviceQueue( device, queueFamilyIndex, queueIndex, pQueue );
	break;
}

case EPacketID::VQueueSubmit : {
	auto const&  queue = unpacker.Get<VkQueue>();
	auto const&  submitCount = unpacker.Get<uint32_t>();
	auto const&  pSubmits = unpacker.Get<const VkSubmitInfo *>(submitCount);
	auto const&  fence = unpacker.Get<VkFence>();
	VK_CALL( vkQueueSubmit( queue, submitCount, pSubmits, fence ));
	break;
}

case EPacketID::VCreateSampler : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  pCreateInfo = unpacker.Get<const VkSamplerCreateInfo *>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	auto const&  pSampler = unpacker.Get<VkSampler *>();
	VK_CALL( vkCreateSampler( device, pCreateInfo, pAllocator, pSampler ));
	break;
}

case EPacketID::VCreateEvent : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  pCreateInfo = unpacker.Get<const VkEventCreateInfo *>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	auto const&  pEvent = unpacker.Get<VkEvent *>();
	VK_CALL( vkCreateEvent( device, pCreateInfo, pAllocator, pEvent ));
	break;
}

case EPacketID::VFlushMappedMemoryRanges : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  memoryRangeCount = unpacker.Get<uint32_t>();
	auto const&  pMemoryRanges = unpacker.Get<const VkMappedMemoryRange *>(memoryRangeCount);
	VK_CALL( vkFlushMappedMemoryRanges( device, memoryRangeCount, pMemoryRanges ));
	break;
}

case EPacketID::VCmdSetDepthBias : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  depthBiasConstantFactor = unpacker.Get<float>();
	auto const&  depthBiasClamp = unpacker.Get<float>();
	auto const&  depthBiasSlopeFactor = unpacker.Get<float>();
	vkCmdSetDepthBias( commandBuffer, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor );
	break;
}

case EPacketID::VAllocateMemory : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  pAllocateInfo = unpacker.Get<const VkMemoryAllocateInfo *>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	auto const&  pMemory = unpacker.Get<VkDeviceMemory *>();
	VK_CALL( vkAllocateMemory( device, pAllocateInfo, pAllocator, pMemory ));
	break;
}

case EPacketID::VDestroyPipeline : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  pipeline = unpacker.Get<VkPipeline>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	vkDestroyPipeline( device, pipeline, pAllocator );
	break;
}

case EPacketID::VCmdDispatchIndirect : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  buffer = unpacker.Get<VkBuffer>();
	auto const&  offset = unpacker.Get<VkDeviceSize>();
	vkCmdDispatchIndirect( commandBuffer, buffer, offset );
	break;
}

case EPacketID::VQueueWaitIdle : {
	auto const&  queue = unpacker.Get<VkQueue>();
	VK_CALL( vkQueueWaitIdle( queue ));
	break;
}

case EPacketID::VCreateImage : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  pCreateInfo = unpacker.Get<const VkImageCreateInfo *>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	auto const&  pImage = unpacker.Get<VkImage *>();
	VK_CALL( vkCreateImage( device, pCreateInfo, pAllocator, pImage ));
	break;
}

case EPacketID::VCreateDescriptorSetLayout : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  pCreateInfo = unpacker.Get<const VkDescriptorSetLayoutCreateInfo *>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	auto const&  pSetLayout = unpacker.Get<VkDescriptorSetLayout *>();
	VK_CALL( vkCreateDescriptorSetLayout( device, pCreateInfo, pAllocator, pSetLayout ));
	break;
}

case EPacketID::VFreeMemory : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  memory = unpacker.Get<VkDeviceMemory>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	vkFreeMemory( device, memory, pAllocator );
	break;
}

case EPacketID::VDeviceWaitIdle : {
	auto const&  device = unpacker.Get<VkDevice>();
	VK_CALL( vkDeviceWaitIdle( device ));
	break;
}

case EPacketID::VCmdSetScissor : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  firstScissor = unpacker.Get<uint32_t>();
	auto const&  scissorCount = unpacker.Get<uint32_t>();
	auto const&  pScissors = unpacker.Get<const VkRect2D *>(scissorCount);
	vkCmdSetScissor( commandBuffer, firstScissor, scissorCount, pScissors );
	break;
}

case EPacketID::VBindBufferMemory : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  buffer = unpacker.Get<VkBuffer>();
	auto const&  memory = unpacker.Get<VkDeviceMemory>();
	auto const&  memoryOffset = unpacker.Get<VkDeviceSize>();
	VK_CALL( vkBindBufferMemory( device, buffer, memory, memoryOffset ));
	break;
}

case EPacketID::VBindImageMemory : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  image = unpacker.Get<VkImage>();
	auto const&  memory = unpacker.Get<VkDeviceMemory>();
	auto const&  memoryOffset = unpacker.Get<VkDeviceSize>();
	VK_CALL( vkBindImageMemory( device, image, memory, memoryOffset ));
	break;
}

case EPacketID::VQueueBindSparse : {
	auto const&  queue = unpacker.Get<VkQueue>();
	auto const&  bindInfoCount = unpacker.Get<uint32_t>();
	auto const&  pBindInfo = unpacker.Get<const VkBindSparseInfo *>(bindInfoCount);
	auto const&  fence = unpacker.Get<VkFence>();
	VK_CALL( vkQueueBindSparse( queue, bindInfoCount, pBindInfo, fence ));
	break;
}

case EPacketID::VCreateFence : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  pCreateInfo = unpacker.Get<const VkFenceCreateInfo *>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	auto const&  pFence = unpacker.Get<VkFence *>();
	VK_CALL( vkCreateFence( device, pCreateInfo, pAllocator, pFence ));
	break;
}

case EPacketID::VDestroyFence : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  fence = unpacker.Get<VkFence>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	vkDestroyFence( device, fence, pAllocator );
	break;
}

case EPacketID::VCreateCommandPool : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  pCreateInfo = unpacker.Get<const VkCommandPoolCreateInfo *>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	auto const&  pCommandPool = unpacker.Get<VkCommandPool *>();
	VK_CALL( vkCreateCommandPool( device, pCreateInfo, pAllocator, pCommandPool ));
	break;
}

case EPacketID::VCmdPipelineBarrier : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  srcStageMask = unpacker.Get<VkPipelineStageFlags>();
	auto const&  dstStageMask = unpacker.Get<VkPipelineStageFlags>();
	auto const&  dependencyFlags = unpacker.Get<VkDependencyFlags>();
	auto const&  memoryBarrierCount = unpacker.Get<uint32_t>();
	auto const&  pMemoryBarriers = unpacker.Get<const VkMemoryBarrier *>(memoryBarrierCount);
	auto const&  bufferMemoryBarrierCount = unpacker.Get<uint32_t>();
	auto const&  pBufferMemoryBarriers = unpacker.Get<const VkBufferMemoryBarrier *>(bufferMemoryBarrierCount);
	auto const&  imageMemoryBarrierCount = unpacker.Get<uint32_t>();
	auto const&  pImageMemoryBarriers = unpacker.Get<const VkImageMemoryBarrier *>(imageMemoryBarrierCount);
	vkCmdPipelineBarrier( commandBuffer, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers );
	break;
}

case EPacketID::VCmdBindPipeline : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  pipelineBindPoint = unpacker.Get<VkPipelineBindPoint>();
	auto const&  pipeline = unpacker.Get<VkPipeline>();
	vkCmdBindPipeline( commandBuffer, pipelineBindPoint, pipeline );
	break;
}

case EPacketID::VResetFences : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  fenceCount = unpacker.Get<uint32_t>();
	auto const&  pFences = unpacker.Get<const VkFence *>(fenceCount);
	VK_CALL( vkResetFences( device, fenceCount, pFences ));
	break;
}

case EPacketID::VWaitForFences : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  fenceCount = unpacker.Get<uint32_t>();
	auto const&  pFences = unpacker.Get<const VkFence *>(fenceCount);
	auto const&  waitAll = unpacker.Get<VkBool32>();
	auto const&  timeout = unpacker.Get<uint64_t>();
	VK_CALL( vkWaitForFences( device, fenceCount, pFences, waitAll, timeout ));
	break;
}

case EPacketID::VResetCommandPool : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  commandPool = unpacker.Get<VkCommandPool>();
	auto const&  flags = unpacker.Get<VkCommandPoolResetFlags>();
	VK_CALL( vkResetCommandPool( device, commandPool, flags ));
	break;
}

case EPacketID::VCreateSemaphore : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  pCreateInfo = unpacker.Get<const VkSemaphoreCreateInfo *>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	auto const&  pSemaphore = unpacker.Get<VkSemaphore *>();
	VK_CALL( vkCreateSemaphore( device, pCreateInfo, pAllocator, pSemaphore ));
	break;
}

case EPacketID::VDestroyBuffer : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  buffer = unpacker.Get<VkBuffer>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	vkDestroyBuffer( device, buffer, pAllocator );
	break;
}

case EPacketID::VDestroySemaphore : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  semaphore = unpacker.Get<VkSemaphore>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	vkDestroySemaphore( device, semaphore, pAllocator );
	break;
}

case EPacketID::VDestroyEvent : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  event = unpacker.Get<VkEvent>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	vkDestroyEvent( device, event, pAllocator );
	break;
}

case EPacketID::VResetDescriptorPool : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  descriptorPool = unpacker.Get<VkDescriptorPool>();
	auto const&  flags = unpacker.Get<VkDescriptorPoolResetFlags>();
	VK_CALL( vkResetDescriptorPool( device, descriptorPool, flags ));
	break;
}

case EPacketID::VSetEvent : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  event = unpacker.Get<VkEvent>();
	VK_CALL( vkSetEvent( device, event ));
	break;
}

case EPacketID::VResetEvent : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  event = unpacker.Get<VkEvent>();
	VK_CALL( vkResetEvent( device, event ));
	break;
}

case EPacketID::VCreateQueryPool : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  pCreateInfo = unpacker.Get<const VkQueryPoolCreateInfo *>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	auto const&  pQueryPool = unpacker.Get<VkQueryPool *>();
	VK_CALL( vkCreateQueryPool( device, pCreateInfo, pAllocator, pQueryPool ));
	break;
}

case EPacketID::VDestroyQueryPool : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  queryPool = unpacker.Get<VkQueryPool>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	vkDestroyQueryPool( device, queryPool, pAllocator );
	break;
}

case EPacketID::VCreateBuffer : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  pCreateInfo = unpacker.Get<const VkBufferCreateInfo *>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	auto const&  pBuffer = unpacker.Get<VkBuffer *>();
	VK_CALL( vkCreateBuffer( device, pCreateInfo, pAllocator, pBuffer ));
	break;
}

case EPacketID::VCreateBufferView : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  pCreateInfo = unpacker.Get<const VkBufferViewCreateInfo *>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	auto const&  pView = unpacker.Get<VkBufferView *>();
	VK_CALL( vkCreateBufferView( device, pCreateInfo, pAllocator, pView ));
	break;
}

case EPacketID::VDestroyBufferView : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  bufferView = unpacker.Get<VkBufferView>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	vkDestroyBufferView( device, bufferView, pAllocator );
	break;
}

case EPacketID::VDestroyImage : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  image = unpacker.Get<VkImage>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	vkDestroyImage( device, image, pAllocator );
	break;
}

case EPacketID::VCmdNextSubpass : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  contents = unpacker.Get<VkSubpassContents>();
	vkCmdNextSubpass( commandBuffer, contents );
	break;
}

case EPacketID::VCreatePipelineLayout : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  pCreateInfo = unpacker.Get<const VkPipelineLayoutCreateInfo *>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	auto const&  pPipelineLayout = unpacker.Get<VkPipelineLayout *>();
	VK_CALL( vkCreatePipelineLayout( device, pCreateInfo, pAllocator, pPipelineLayout ));
	break;
}

case EPacketID::VCreateImageView : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  pCreateInfo = unpacker.Get<const VkImageViewCreateInfo *>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	auto const&  pView = unpacker.Get<VkImageView *>();
	VK_CALL( vkCreateImageView( device, pCreateInfo, pAllocator, pView ));
	break;
}

case EPacketID::VCmdSetViewport : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  firstViewport = unpacker.Get<uint32_t>();
	auto const&  viewportCount = unpacker.Get<uint32_t>();
	auto const&  pViewports = unpacker.Get<const VkViewport *>(viewportCount);
	vkCmdSetViewport( commandBuffer, firstViewport, viewportCount, pViewports );
	break;
}

case EPacketID::VDestroySampler : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  sampler = unpacker.Get<VkSampler>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	vkDestroySampler( device, sampler, pAllocator );
	break;
}

case EPacketID::VDestroyImageView : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  imageView = unpacker.Get<VkImageView>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	vkDestroyImageView( device, imageView, pAllocator );
	break;
}

case EPacketID::VDestroyRenderPass : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  renderPass = unpacker.Get<VkRenderPass>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	vkDestroyRenderPass( device, renderPass, pAllocator );
	break;
}

case EPacketID::VCmdFillBuffer : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  dstBuffer = unpacker.Get<VkBuffer>();
	auto const&  dstOffset = unpacker.Get<VkDeviceSize>();
	auto const&  size = unpacker.Get<VkDeviceSize>();
	auto const&  data = unpacker.Get<uint32_t>();
	vkCmdFillBuffer( commandBuffer, dstBuffer, dstOffset, size, data );
	break;
}

case EPacketID::VCmdBindIndexBuffer : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  buffer = unpacker.Get<VkBuffer>();
	auto const&  offset = unpacker.Get<VkDeviceSize>();
	auto const&  indexType = unpacker.Get<VkIndexType>();
	vkCmdBindIndexBuffer( commandBuffer, buffer, offset, indexType );
	break;
}

case EPacketID::VDestroyShaderModule : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  shaderModule = unpacker.Get<VkShaderModule>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	vkDestroyShaderModule( device, shaderModule, pAllocator );
	break;
}

case EPacketID::VDestroyPipelineCache : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  pipelineCache = unpacker.Get<VkPipelineCache>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	vkDestroyPipelineCache( device, pipelineCache, pAllocator );
	break;
}

case EPacketID::VMergePipelineCaches : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  dstCache = unpacker.Get<VkPipelineCache>();
	auto const&  srcCacheCount = unpacker.Get<uint32_t>();
	auto const&  pSrcCaches = unpacker.Get<const VkPipelineCache *>(srcCacheCount);
	VK_CALL( vkMergePipelineCaches( device, dstCache, srcCacheCount, pSrcCaches ));
	break;
}

case EPacketID::VCreateComputePipelines : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  pipelineCache = unpacker.Get<VkPipelineCache>();
	auto const&  createInfoCount = unpacker.Get<uint32_t>();
	auto const&  pCreateInfos = unpacker.Get<const VkComputePipelineCreateInfo *>(createInfoCount);
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	auto const&  pPipelines = unpacker.Get<VkPipeline *>(createInfoCount);
	VK_CALL( vkCreateComputePipelines( device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines ));
	break;
}

case EPacketID::VCreateGraphicsPipelines : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  pipelineCache = unpacker.Get<VkPipelineCache>();
	auto const&  createInfoCount = unpacker.Get<uint32_t>();
	auto const&  pCreateInfos = unpacker.Get<const VkGraphicsPipelineCreateInfo *>(createInfoCount);
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	auto const&  pPipelines = unpacker.Get<VkPipeline *>(createInfoCount);
	VK_CALL( vkCreateGraphicsPipelines( device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines ));
	break;
}

case EPacketID::VResetCommandBuffer : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  flags = unpacker.Get<VkCommandBufferResetFlags>();
	VK_CALL( vkResetCommandBuffer( commandBuffer, flags ));
	break;
}

case EPacketID::VCmdCopyImage : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  srcImage = unpacker.Get<VkImage>();
	auto const&  srcImageLayout = unpacker.Get<VkImageLayout>();
	auto const&  dstImage = unpacker.Get<VkImage>();
	auto const&  dstImageLayout = unpacker.Get<VkImageLayout>();
	auto const&  regionCount = unpacker.Get<uint32_t>();
	auto const&  pRegions = unpacker.Get<const VkImageCopy *>(regionCount);
	vkCmdCopyImage( commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions );
	break;
}

case EPacketID::VDestroyPipelineLayout : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  pipelineLayout = unpacker.Get<VkPipelineLayout>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	vkDestroyPipelineLayout( device, pipelineLayout, pAllocator );
	break;
}

case EPacketID::VDestroyDescriptorSetLayout : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  descriptorSetLayout = unpacker.Get<VkDescriptorSetLayout>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	vkDestroyDescriptorSetLayout( device, descriptorSetLayout, pAllocator );
	break;
}

case EPacketID::VAllocateCommandBuffers : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  pAllocateInfo = unpacker.Get<const VkCommandBufferAllocateInfo *>();
	auto const&  pCommandBuffers = unpacker.Get<VkCommandBuffer *>(pAllocateInfo->commandBufferCount);
	VK_CALL( vkAllocateCommandBuffers( device, pAllocateInfo, pCommandBuffers ));
	break;
}

case EPacketID::VCreateDescriptorPool : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  pCreateInfo = unpacker.Get<const VkDescriptorPoolCreateInfo *>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	auto const&  pDescriptorPool = unpacker.Get<VkDescriptorPool *>();
	VK_CALL( vkCreateDescriptorPool( device, pCreateInfo, pAllocator, pDescriptorPool ));
	break;
}

case EPacketID::VDestroyDescriptorPool : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  descriptorPool = unpacker.Get<VkDescriptorPool>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	vkDestroyDescriptorPool( device, descriptorPool, pAllocator );
	break;
}

case EPacketID::VCreateFramebuffer : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  pCreateInfo = unpacker.Get<const VkFramebufferCreateInfo *>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	auto const&  pFramebuffer = unpacker.Get<VkFramebuffer *>();
	VK_CALL( vkCreateFramebuffer( device, pCreateInfo, pAllocator, pFramebuffer ));
	break;
}

case EPacketID::VAllocateDescriptorSets : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  pAllocateInfo = unpacker.Get<const VkDescriptorSetAllocateInfo *>();
	auto const&  pDescriptorSets = unpacker.Get<VkDescriptorSet *>(pAllocateInfo->descriptorSetCount);
	VK_CALL( vkAllocateDescriptorSets( device, pAllocateInfo, pDescriptorSets ));
	break;
}

case EPacketID::VFreeDescriptorSets : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  descriptorPool = unpacker.Get<VkDescriptorPool>();
	auto const&  descriptorSetCount = unpacker.Get<uint32_t>();
	auto const&  pDescriptorSets = unpacker.Get<const VkDescriptorSet *>(descriptorSetCount);
	VK_CALL( vkFreeDescriptorSets( device, descriptorPool, descriptorSetCount, pDescriptorSets ));
	break;
}

case EPacketID::VCmdSetLineWidth : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  lineWidth = unpacker.Get<float>();
	vkCmdSetLineWidth( commandBuffer, lineWidth );
	break;
}

case EPacketID::VUpdateDescriptorSets : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  descriptorWriteCount = unpacker.Get<uint32_t>();
	auto const&  pDescriptorWrites = unpacker.Get<const VkWriteDescriptorSet *>(descriptorWriteCount);
	auto const&  descriptorCopyCount = unpacker.Get<uint32_t>();
	auto const&  pDescriptorCopies = unpacker.Get<const VkCopyDescriptorSet *>(descriptorCopyCount);
	vkUpdateDescriptorSets( device, descriptorWriteCount, pDescriptorWrites, descriptorCopyCount, pDescriptorCopies );
	break;
}

case EPacketID::VDestroyFramebuffer : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  framebuffer = unpacker.Get<VkFramebuffer>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	vkDestroyFramebuffer( device, framebuffer, pAllocator );
	break;
}

case EPacketID::VDestroyCommandPool : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  commandPool = unpacker.Get<VkCommandPool>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	vkDestroyCommandPool( device, commandPool, pAllocator );
	break;
}

case EPacketID::VCreateRenderPass : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  pCreateInfo = unpacker.Get<const VkRenderPassCreateInfo *>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	auto const&  pRenderPass = unpacker.Get<VkRenderPass *>();
	VK_CALL( vkCreateRenderPass( device, pCreateInfo, pAllocator, pRenderPass ));
	break;
}

case EPacketID::VFreeCommandBuffers : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  commandPool = unpacker.Get<VkCommandPool>();
	auto const&  commandBufferCount = unpacker.Get<uint32_t>();
	auto const&  pCommandBuffers = unpacker.Get<const VkCommandBuffer *>(commandBufferCount);
	vkFreeCommandBuffers( device, commandPool, commandBufferCount, pCommandBuffers );
	break;
}

case EPacketID::VBeginCommandBuffer : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  pBeginInfo = unpacker.Get<const VkCommandBufferBeginInfo *>();
	VK_CALL( vkBeginCommandBuffer( commandBuffer, pBeginInfo ));
	break;
}

case EPacketID::VEndCommandBuffer : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	VK_CALL( vkEndCommandBuffer( commandBuffer ));
	break;
}

case EPacketID::VCmdBindVertexBuffers : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  firstBinding = unpacker.Get<uint32_t>();
	auto const&  bindingCount = unpacker.Get<uint32_t>();
	auto const&  pBuffers = unpacker.Get<const VkBuffer *>(bindingCount);
	auto const&  pOffsets = unpacker.Get<const VkDeviceSize *>(bindingCount);
	vkCmdBindVertexBuffers( commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets );
	break;
}

case EPacketID::VCmdSetBlendConstants : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  blendConstants = unpacker.Get<const float [ 4 ]>();
	vkCmdSetBlendConstants( commandBuffer, blendConstants );
	break;
}

case EPacketID::VCmdSetDepthBounds : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  minDepthBounds = unpacker.Get<float>();
	auto const&  maxDepthBounds = unpacker.Get<float>();
	vkCmdSetDepthBounds( commandBuffer, minDepthBounds, maxDepthBounds );
	break;
}

case EPacketID::VCmdSetStencilCompareMask : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  faceMask = unpacker.Get<VkStencilFaceFlags>();
	auto const&  compareMask = unpacker.Get<uint32_t>();
	vkCmdSetStencilCompareMask( commandBuffer, faceMask, compareMask );
	break;
}

case EPacketID::VCmdSetStencilWriteMask : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  faceMask = unpacker.Get<VkStencilFaceFlags>();
	auto const&  writeMask = unpacker.Get<uint32_t>();
	vkCmdSetStencilWriteMask( commandBuffer, faceMask, writeMask );
	break;
}

case EPacketID::VCmdSetStencilReference : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  faceMask = unpacker.Get<VkStencilFaceFlags>();
	auto const&  reference = unpacker.Get<uint32_t>();
	vkCmdSetStencilReference( commandBuffer, faceMask, reference );
	break;
}

case EPacketID::VCmdBindDescriptorSets : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  pipelineBindPoint = unpacker.Get<VkPipelineBindPoint>();
	auto const&  layout = unpacker.Get<VkPipelineLayout>();
	auto const&  firstSet = unpacker.Get<uint32_t>();
	auto const&  descriptorSetCount = unpacker.Get<uint32_t>();
	auto const&  pDescriptorSets = unpacker.Get<const VkDescriptorSet *>(descriptorSetCount);
	auto const&  dynamicOffsetCount = unpacker.Get<uint32_t>();
	auto const&  pDynamicOffsets = unpacker.Get<const uint32_t *>(dynamicOffsetCount);
	vkCmdBindDescriptorSets( commandBuffer, pipelineBindPoint, layout, firstSet, descriptorSetCount, pDescriptorSets, dynamicOffsetCount, pDynamicOffsets );
	break;
}

case EPacketID::VCmdDraw : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  vertexCount = unpacker.Get<uint32_t>();
	auto const&  instanceCount = unpacker.Get<uint32_t>();
	auto const&  firstVertex = unpacker.Get<uint32_t>();
	auto const&  firstInstance = unpacker.Get<uint32_t>();
	vkCmdDraw( commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance );
	break;
}

case EPacketID::VCmdDrawIndexed : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  indexCount = unpacker.Get<uint32_t>();
	auto const&  instanceCount = unpacker.Get<uint32_t>();
	auto const&  firstIndex = unpacker.Get<uint32_t>();
	auto const&  vertexOffset = unpacker.Get<int32_t>();
	auto const&  firstInstance = unpacker.Get<uint32_t>();
	vkCmdDrawIndexed( commandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance );
	break;
}

case EPacketID::VCmdDrawIndirect : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  buffer = unpacker.Get<VkBuffer>();
	auto const&  offset = unpacker.Get<VkDeviceSize>();
	auto const&  drawCount = unpacker.Get<uint32_t>();
	auto const&  stride = unpacker.Get<uint32_t>();
	vkCmdDrawIndirect( commandBuffer, buffer, offset, drawCount, stride );
	break;
}

case EPacketID::VCmdDrawIndexedIndirect : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  buffer = unpacker.Get<VkBuffer>();
	auto const&  offset = unpacker.Get<VkDeviceSize>();
	auto const&  drawCount = unpacker.Get<uint32_t>();
	auto const&  stride = unpacker.Get<uint32_t>();
	vkCmdDrawIndexedIndirect( commandBuffer, buffer, offset, drawCount, stride );
	break;
}

case EPacketID::VCmdDispatch : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  groupCountX = unpacker.Get<uint32_t>();
	auto const&  groupCountY = unpacker.Get<uint32_t>();
	auto const&  groupCountZ = unpacker.Get<uint32_t>();
	vkCmdDispatch( commandBuffer, groupCountX, groupCountY, groupCountZ );
	break;
}

case EPacketID::VCmdCopyBuffer : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  srcBuffer = unpacker.Get<VkBuffer>();
	auto const&  dstBuffer = unpacker.Get<VkBuffer>();
	auto const&  regionCount = unpacker.Get<uint32_t>();
	auto const&  pRegions = unpacker.Get<const VkBufferCopy *>(regionCount);
	vkCmdCopyBuffer( commandBuffer, srcBuffer, dstBuffer, regionCount, pRegions );
	break;
}

case EPacketID::VCmdBlitImage : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  srcImage = unpacker.Get<VkImage>();
	auto const&  srcImageLayout = unpacker.Get<VkImageLayout>();
	auto const&  dstImage = unpacker.Get<VkImage>();
	auto const&  dstImageLayout = unpacker.Get<VkImageLayout>();
	auto const&  regionCount = unpacker.Get<uint32_t>();
	auto const&  pRegions = unpacker.Get<const VkImageBlit *>(regionCount);
	auto const&  filter = unpacker.Get<VkFilter>();
	vkCmdBlitImage( commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions, filter );
	break;
}

case EPacketID::VCmdCopyBufferToImage : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  srcBuffer = unpacker.Get<VkBuffer>();
	auto const&  dstImage = unpacker.Get<VkImage>();
	auto const&  dstImageLayout = unpacker.Get<VkImageLayout>();
	auto const&  regionCount = unpacker.Get<uint32_t>();
	auto const&  pRegions = unpacker.Get<const VkBufferImageCopy *>(regionCount);
	vkCmdCopyBufferToImage( commandBuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions );
	break;
}

case EPacketID::VCmdCopyImageToBuffer : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  srcImage = unpacker.Get<VkImage>();
	auto const&  srcImageLayout = unpacker.Get<VkImageLayout>();
	auto const&  dstBuffer = unpacker.Get<VkBuffer>();
	auto const&  regionCount = unpacker.Get<uint32_t>();
	auto const&  pRegions = unpacker.Get<const VkBufferImageCopy *>(regionCount);
	vkCmdCopyImageToBuffer( commandBuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions );
	break;
}

case EPacketID::VCmdBeginRenderPass2KHR : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  pRenderPassBegin = unpacker.Get<const VkRenderPassBeginInfo *>();
	auto const&  pSubpassBeginInfo = unpacker.Get<const VkSubpassBeginInfoKHR *>();
	vkCmdBeginRenderPass2KHR( commandBuffer, pRenderPassBegin, pSubpassBeginInfo );
	break;
}

case EPacketID::VCmdClearColorImage : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  image = unpacker.Get<VkImage>();
	auto const&  imageLayout = unpacker.Get<VkImageLayout>();
	auto const&  pColor = unpacker.Get<const VkClearColorValue *>();
	auto const&  rangeCount = unpacker.Get<uint32_t>();
	auto const&  pRanges = unpacker.Get<const VkImageSubresourceRange *>(rangeCount);
	vkCmdClearColorImage( commandBuffer, image, imageLayout, pColor, rangeCount, pRanges );
	break;
}

case EPacketID::VCmdClearDepthStencilImage : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  image = unpacker.Get<VkImage>();
	auto const&  imageLayout = unpacker.Get<VkImageLayout>();
	auto const&  pDepthStencil = unpacker.Get<const VkClearDepthStencilValue *>();
	auto const&  rangeCount = unpacker.Get<uint32_t>();
	auto const&  pRanges = unpacker.Get<const VkImageSubresourceRange *>(rangeCount);
	vkCmdClearDepthStencilImage( commandBuffer, image, imageLayout, pDepthStencil, rangeCount, pRanges );
	break;
}

case EPacketID::VCmdClearAttachments : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  attachmentCount = unpacker.Get<uint32_t>();
	auto const&  pAttachments = unpacker.Get<const VkClearAttachment *>(attachmentCount);
	auto const&  rectCount = unpacker.Get<uint32_t>();
	auto const&  pRects = unpacker.Get<const VkClearRect *>(rectCount);
	vkCmdClearAttachments( commandBuffer, attachmentCount, pAttachments, rectCount, pRects );
	break;
}

case EPacketID::VCmdResolveImage : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  srcImage = unpacker.Get<VkImage>();
	auto const&  srcImageLayout = unpacker.Get<VkImageLayout>();
	auto const&  dstImage = unpacker.Get<VkImage>();
	auto const&  dstImageLayout = unpacker.Get<VkImageLayout>();
	auto const&  regionCount = unpacker.Get<uint32_t>();
	auto const&  pRegions = unpacker.Get<const VkImageResolve *>(regionCount);
	vkCmdResolveImage( commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions );
	break;
}

case EPacketID::VCmdSetEvent : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  event = unpacker.Get<VkEvent>();
	auto const&  stageMask = unpacker.Get<VkPipelineStageFlags>();
	vkCmdSetEvent( commandBuffer, event, stageMask );
	break;
}

case EPacketID::VCmdResetEvent : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  event = unpacker.Get<VkEvent>();
	auto const&  stageMask = unpacker.Get<VkPipelineStageFlags>();
	vkCmdResetEvent( commandBuffer, event, stageMask );
	break;
}

case EPacketID::VCmdWaitEvents : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  eventCount = unpacker.Get<uint32_t>();
	auto const&  pEvents = unpacker.Get<const VkEvent *>(eventCount);
	auto const&  srcStageMask = unpacker.Get<VkPipelineStageFlags>();
	auto const&  dstStageMask = unpacker.Get<VkPipelineStageFlags>();
	auto const&  memoryBarrierCount = unpacker.Get<uint32_t>();
	auto const&  pMemoryBarriers = unpacker.Get<const VkMemoryBarrier *>(memoryBarrierCount);
	auto const&  bufferMemoryBarrierCount = unpacker.Get<uint32_t>();
	auto const&  pBufferMemoryBarriers = unpacker.Get<const VkBufferMemoryBarrier *>(bufferMemoryBarrierCount);
	auto const&  imageMemoryBarrierCount = unpacker.Get<uint32_t>();
	auto const&  pImageMemoryBarriers = unpacker.Get<const VkImageMemoryBarrier *>(imageMemoryBarrierCount);
	vkCmdWaitEvents( commandBuffer, eventCount, pEvents, srcStageMask, dstStageMask, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers );
	break;
}

case EPacketID::VCmdBeginQuery : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  queryPool = unpacker.Get<VkQueryPool>();
	auto const&  query = unpacker.Get<uint32_t>();
	auto const&  flags = unpacker.Get<VkQueryControlFlags>();
	vkCmdBeginQuery( commandBuffer, queryPool, query, flags );
	break;
}

case EPacketID::VCmdEndQuery : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  queryPool = unpacker.Get<VkQueryPool>();
	auto const&  query = unpacker.Get<uint32_t>();
	vkCmdEndQuery( commandBuffer, queryPool, query );
	break;
}

case EPacketID::VCmdResetQueryPool : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  queryPool = unpacker.Get<VkQueryPool>();
	auto const&  firstQuery = unpacker.Get<uint32_t>();
	auto const&  queryCount = unpacker.Get<uint32_t>();
	vkCmdResetQueryPool( commandBuffer, queryPool, firstQuery, queryCount );
	break;
}

case EPacketID::VCmdCopyQueryPoolResults : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  queryPool = unpacker.Get<VkQueryPool>();
	auto const&  firstQuery = unpacker.Get<uint32_t>();
	auto const&  queryCount = unpacker.Get<uint32_t>();
	auto const&  dstBuffer = unpacker.Get<VkBuffer>();
	auto const&  dstOffset = unpacker.Get<VkDeviceSize>();
	auto const&  stride = unpacker.Get<VkDeviceSize>();
	auto const&  flags = unpacker.Get<VkQueryResultFlags>();
	vkCmdCopyQueryPoolResults( commandBuffer, queryPool, firstQuery, queryCount, dstBuffer, dstOffset, stride, flags );
	break;
}

case EPacketID::VCmdBeginRenderPass : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  pRenderPassBegin = unpacker.Get<const VkRenderPassBeginInfo *>();
	auto const&  contents = unpacker.Get<VkSubpassContents>();
	vkCmdBeginRenderPass( commandBuffer, pRenderPassBegin, contents );
	break;
}

case EPacketID::VCmdEndRenderPass : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	vkCmdEndRenderPass( commandBuffer );
	break;
}

case EPacketID::VCmdExecuteCommands : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  commandBufferCount = unpacker.Get<uint32_t>();
	auto const&  pCommandBuffers = unpacker.Get<const VkCommandBuffer *>(commandBufferCount);
	vkCmdExecuteCommands( commandBuffer, commandBufferCount, pCommandBuffers );
	break;
}

case EPacketID::VBindBufferMemory2 : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  bindInfoCount = unpacker.Get<uint32_t>();
	auto const&  pBindInfos = unpacker.Get<const VkBindBufferMemoryInfo *>(bindInfoCount);
	VK_CALL( vkBindBufferMemory2( device, bindInfoCount, pBindInfos ));
	break;
}

case EPacketID::VBindImageMemory2 : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  bindInfoCount = unpacker.Get<uint32_t>();
	auto const&  pBindInfos = unpacker.Get<const VkBindImageMemoryInfo *>(bindInfoCount);
	VK_CALL( vkBindImageMemory2( device, bindInfoCount, pBindInfos ));
	break;
}

case EPacketID::VCmdSetDeviceMask : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  deviceMask = unpacker.Get<uint32_t>();
	vkCmdSetDeviceMask( commandBuffer, deviceMask );
	break;
}

case EPacketID::VCmdDispatchBase : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  baseGroupX = unpacker.Get<uint32_t>();
	auto const&  baseGroupY = unpacker.Get<uint32_t>();
	auto const&  baseGroupZ = unpacker.Get<uint32_t>();
	auto const&  groupCountX = unpacker.Get<uint32_t>();
	auto const&  groupCountY = unpacker.Get<uint32_t>();
	auto const&  groupCountZ = unpacker.Get<uint32_t>();
	vkCmdDispatchBase( commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ );
	break;
}

case EPacketID::VTrimCommandPool : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  commandPool = unpacker.Get<VkCommandPool>();
	auto const&  flags = unpacker.Get<VkCommandPoolTrimFlags>();
	vkTrimCommandPool( device, commandPool, flags );
	break;
}

case EPacketID::VGetDeviceQueue2 : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  pQueueInfo = unpacker.Get<const VkDeviceQueueInfo2 *>();
	auto const&  pQueue = unpacker.Get<VkQueue *>();
	vkGetDeviceQueue2( device, pQueueInfo, pQueue );
	break;
}

case EPacketID::VCreateSamplerYcbcrConversion : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  pCreateInfo = unpacker.Get<const VkSamplerYcbcrConversionCreateInfo *>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	auto const&  pYcbcrConversion = unpacker.Get<VkSamplerYcbcrConversion *>();
	VK_CALL( vkCreateSamplerYcbcrConversion( device, pCreateInfo, pAllocator, pYcbcrConversion ));
	break;
}

case EPacketID::VDestroySamplerYcbcrConversion : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  ycbcrConversion = unpacker.Get<VkSamplerYcbcrConversion>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	vkDestroySamplerYcbcrConversion( device, ycbcrConversion, pAllocator );
	break;
}

case EPacketID::VCreateDescriptorUpdateTemplate : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  pCreateInfo = unpacker.Get<const VkDescriptorUpdateTemplateCreateInfo *>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	auto const&  pDescriptorUpdateTemplate = unpacker.Get<VkDescriptorUpdateTemplate *>();
	VK_CALL( vkCreateDescriptorUpdateTemplate( device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate ));
	break;
}

case EPacketID::VDestroyDescriptorUpdateTemplate : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  descriptorUpdateTemplate = unpacker.Get<VkDescriptorUpdateTemplate>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	vkDestroyDescriptorUpdateTemplate( device, descriptorUpdateTemplate, pAllocator );
	break;
}

case EPacketID::VCmdPushDescriptorSetKHR : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  pipelineBindPoint = unpacker.Get<VkPipelineBindPoint>();
	auto const&  layout = unpacker.Get<VkPipelineLayout>();
	auto const&  set = unpacker.Get<uint32_t>();
	auto const&  descriptorWriteCount = unpacker.Get<uint32_t>();
	auto const&  pDescriptorWrites = unpacker.Get<const VkWriteDescriptorSet *>(descriptorWriteCount);
	vkCmdPushDescriptorSetKHR( commandBuffer, pipelineBindPoint, layout, set, descriptorWriteCount, pDescriptorWrites );
	break;
}

case EPacketID::VCreateRenderPass2KHR : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  pCreateInfo = unpacker.Get<const VkRenderPassCreateInfo2KHR *>();
	auto const&  pAllocator = unpacker.Get<const VkAllocationCallbacks *>();
	auto const&  pRenderPass = unpacker.Get<VkRenderPass *>();
	VK_CALL( vkCreateRenderPass2KHR( device, pCreateInfo, pAllocator, pRenderPass ));
	break;
}

case EPacketID::VCmdNextSubpass2KHR : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  pSubpassBeginInfo = unpacker.Get<const VkSubpassBeginInfoKHR *>();
	auto const&  pSubpassEndInfo = unpacker.Get<const VkSubpassEndInfoKHR *>();
	vkCmdNextSubpass2KHR( commandBuffer, pSubpassBeginInfo, pSubpassEndInfo );
	break;
}

case EPacketID::VCmdEndRenderPass2KHR : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  pSubpassEndInfo = unpacker.Get<const VkSubpassEndInfoKHR *>();
	vkCmdEndRenderPass2KHR( commandBuffer, pSubpassEndInfo );
	break;
}

case EPacketID::VCmdDrawIndirectCountKHR : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  buffer = unpacker.Get<VkBuffer>();
	auto const&  offset = unpacker.Get<VkDeviceSize>();
	auto const&  countBuffer = unpacker.Get<VkBuffer>();
	auto const&  countBufferOffset = unpacker.Get<VkDeviceSize>();
	auto const&  maxDrawCount = unpacker.Get<uint32_t>();
	auto const&  stride = unpacker.Get<uint32_t>();
	vkCmdDrawIndirectCountKHR( commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride );
	break;
}

case EPacketID::VCmdDrawIndexedIndirectCountKHR : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  buffer = unpacker.Get<VkBuffer>();
	auto const&  offset = unpacker.Get<VkDeviceSize>();
	auto const&  countBuffer = unpacker.Get<VkBuffer>();
	auto const&  countBufferOffset = unpacker.Get<VkDeviceSize>();
	auto const&  maxDrawCount = unpacker.Get<uint32_t>();
	auto const&  stride = unpacker.Get<uint32_t>();
	vkCmdDrawIndexedIndirectCountKHR( commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride );
	break;
}

case EPacketID::VDebugMarkerSetObjectNameEXT : {
	auto const&  device = unpacker.Get<VkDevice>();
	auto const&  pNameInfo = unpacker.Get<const VkDebugMarkerObjectNameInfoEXT *>();
	VK_CALL( vkDebugMarkerSetObjectNameEXT( device, pNameInfo ));
	break;
}

case EPacketID::VCmdDebugMarkerBeginEXT : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  pMarkerInfo = unpacker.Get<const VkDebugMarkerMarkerInfoEXT *>();
	vkCmdDebugMarkerBeginEXT( commandBuffer, pMarkerInfo );
	break;
}

case EPacketID::VCmdDebugMarkerEndEXT : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	vkCmdDebugMarkerEndEXT( commandBuffer );
	break;
}

case EPacketID::VCmdDebugMarkerInsertEXT : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  pMarkerInfo = unpacker.Get<const VkDebugMarkerMarkerInfoEXT *>();
	vkCmdDebugMarkerInsertEXT( commandBuffer, pMarkerInfo );
	break;
}

case EPacketID::VCmdPushConstants : {
	auto const&  commandBuffer = unpacker.Get<VkCommandBuffer>();
	auto const&  layout = unpacker.Get<VkPipelineLayout>();
	auto const&  stageFlags = unpacker.Get<VkShaderStageFlags>();
	auto const&  offset = unpacker.Get<uint32_t>();
	auto const&  size = unpacker.Get<uint32_t>();
	auto const&  pValues = unpacker.Get<const void *>(size);
	vkCmdPushConstants( commandBuffer, layout, stageFlags, offset, size, pValues );
	break;
}

