
	// resource creation
	FgCreateGraphicsPipeline		=  1 | _FrameGraphApi | _V100,
	FgDestroyGraphicsPipeline		=  2 | _FrameGraphApi | _V100,
	FgCreateComputePipeline			=  3 | _FrameGraphApi | _V100,
	FgDestroyComputePipeline		=  4 | _FrameGraphApi | _V100,
	FgCreateMeshPipeline			=  5 | _FrameGraphApi | _V100,
	FgDestroyMeshPipeline			=  6 | _FrameGraphApi | _V100,
	FgCreateRayTracingPipeline		=  7 | _FrameGraphApi | _V100,
	FgDestroyRayTracingPipeline		=  8 | _FrameGraphApi | _V100,
	FgCreateSampler					=  9 | _FrameGraphApi | _V100,
	FgDestroySampler				= 10 | _FrameGraphApi | _V100,
	FgCreateImage					= 11 | _FrameGraphApi | _V100,
	FgDestroyImage					= 12 | _FrameGraphApi | _V100,
	FgCreateBuffer					= 13 | _FrameGraphApi | _V100,
	FgDestroyBuffer					= 14 | _FrameGraphApi | _V100,
	FgCreateShaderModule			= 15 | _FrameGraphApi | _V100,
	FgCreateRenderPass				= 16 | _FrameGraphApi | _V100,
	FgCreateThread					= 17 | _FrameGraphApi | _V100,

	FgSubmitRenderPass				= 20 | _FrameGraphApi | _V100,
	FgDispatchCompute				= 21 | _FrameGraphApi | _V100,
	FgDispatchComputeIndirect		= 22 | _FrameGraphApi | _V100,
	FgCopyBuffer					= 23 | _FrameGraphApi | _V100,
	FgCopyImage						= 24 | _FrameGraphApi | _V100,
	FgCopyBufferToImage				= 25 | _FrameGraphApi | _V100,
	FgCopyImageToBuffer				= 26 | _FrameGraphApi | _V100,
	FgBlitImage						= 27 | _FrameGraphApi | _V100,
	FgResolveImage					= 28 | _FrameGraphApi | _V100,
	FgFillBuffer					= 29 | _FrameGraphApi | _V100,
	FgClearColorImage				= 30 | _FrameGraphApi | _V100,
	FgClearDepthStencilImage		= 31 | _FrameGraphApi | _V100,
	FgUpdateBuffer					= 32 | _FrameGraphApi | _V100,
	FgReadBuffer					= 33 | _FrameGraphApi | _V100,
	FgUpdateImage					= 34 | _FrameGraphApi | _V100,
	FgReadImage						= 35 | _FrameGraphApi | _V100,
	FgPresent						= 36 | _FrameGraphApi | _V100,
	FgPresentVR						= 37 | _FrameGraphApi | _V100,
	FgBuildRayTracingGeometry		= 38 | _FrameGraphApi | _V100,
	FgBuildRayTracingScene			= 39 | _FrameGraphApi | _V100,
	FgTraceRays						= 40 | _FrameGraphApi | _V100,
	FgBeginFrame					= 41 | _FrameGraphApi | _V100,
	FgEndFrame						= 42 | _FrameGraphApi | _V100,
	FgBeginThread					= 43 | _FrameGraphApi | _V100,
	FgEndThread						= 44 | _FrameGraphApi | _V100,
	FgUpdateHostBuffer				= 46 | _FrameGraphApi | _V100,

	FgDrawVertices					= 70 | _FrameGraphApi | _V100,
	FgDrawIndexed					= 71 | _FrameGraphApi | _V100,
	FgDrawMeshes					= 72 | _FrameGraphApi | _V100,
	FgDrawVerticesIndirect			= 73 | _FrameGraphApi | _V100,
	FgDrawIndexedIndirect			= 74 | _FrameGraphApi | _V100,
	FgDrawMeshesIndirect			= 75 | _FrameGraphApi | _V100,
	FgClearAttachments				= 76 | _FrameGraphApi | _V100,
		
	FgSetGraphicsPipelineCount		= 101 | _FrameGraphApi | _V100,
	FgSetComputePipelineCount		= 102 | _FrameGraphApi | _V100,
	FgSetMeshPipelineCount			= 103 | _FrameGraphApi | _V100,
	FgSetRayTracingPipelineCount	= 104 | _FrameGraphApi | _V100,
	FgSetSamplerCount				= 105 | _FrameGraphApi | _V100,
	FgSetImageCount					= 106 | _FrameGraphApi | _V100,
	FgSetBufferCount				= 107 | _FrameGraphApi | _V100,
	FgSetShaderModuleCount			= 108 | _FrameGraphApi | _V100,
	FgSetLogicalPassCount			= 109 | _FrameGraphApi | _V100,
	FgSetThreadCount				= 110 | _FrameGraphApi | _V100,

