
	// initialization
	VInitializeResource			= 0x01 | _CustomBit | _VulkanApi | _V100,

	// original memory model
	VMapMemory					= 0x11 | _CustomBit | _VulkanApi | _V100,
	VUnmapMemory				= 0x12 | _CustomBit | _VulkanApi | _V100,
	VLoadDataToMappedMemory		= 0x13 | _CustomBit | _VulkanApi | _V100,

	// use custom memory allocator for portability
	VAllocateBufferMemory		= 0x21 | _CustomBit | _VulkanApi | _V100,
	VAllocateImageMemory		= 0x22 | _CustomBit | _VulkanApi | _V100,
	VFreeBufferMemory			= 0x23 | _CustomBit | _VulkanApi | _V100,
	VFreeImageMemory			= 0x24 | _CustomBit | _VulkanApi | _V100,
	VLoadDataToBuffer			= 0x25 | _CustomBit | _VulkanApi | _V100,
	VLoadDataToImage			= 0x26 | _CustomBit | _VulkanApi | _V100,

	// with data loading
	VCreateShaderModule			= 0x31 | _CustomBit | _VulkanApi | _V100,
	VCreatePipelineCache		= 0x32 | _CustomBit | _VulkanApi | _V100,
	VCmdUpdateBuffer			= 0x33 | _CustomBit | _VulkanApi | _V100,

	// swapchain
	VAcquireNextImageKHR		= 0x41 | _CustomBit | _VulkanApi | _V100,
	VQueuePresentKHR			= 0x42 | _CustomBit | _VulkanApi | _V100,

	// ...
	VCmdPushDescriptorSetWithTemplate	= 0x51 | _CustomBit | _VulkanApi | _V100,
	VUpdateDescriptorSetWithTemplate	= 0x52 | _CustomBit | _VulkanApi | _V100,

	// resource capture
	VImageCapture				= 0x61 | _CustomBit | _VulkanApi | _V100,
	VBufferCapture				= 0x62 | _CustomBit | _VulkanApi | _V100,
	VImageCaptureReady			= 0x63 | _CustomBit | _VulkanApi | _V100,
	VBufferCaptureReady			= 0x64 | _CustomBit | _VulkanApi | _V100,

	// profiling
	VTimerStart					= 0x71 | _CustomBit | _VulkanApi | _V100,
	VTimerStop					= 0x72 | _CustomBit | _VulkanApi | _V100,
	VTimerReady					= 0x73 | _CustomBit | _VulkanApi | _V100,
	VCpuTimerStart				= 0x74 | _CustomBit | _VulkanApi | _V100,
	VCpuTimerStop				= 0x75 | _CustomBit | _VulkanApi | _V100,
