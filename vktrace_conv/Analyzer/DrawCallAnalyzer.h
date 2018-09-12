// Copyright (c)  Zhirnov Andrey. For more information see 'LICENSE.txt'

#pragma once

#include "Analyzer/IAnalyzer.h"

namespace VTC
{

	//
	// Draw Call Analyzer
	//

	class DrawCallAnalyzer final : public IAnalyzer
	{
	// types
	private:
		using ColorBlendAttachments_t	= FixedArray< VkPipelineColorBlendAttachmentState, FG_MaxColorBuffers >;
		using SampleMask_t				= FixedArray< VkSampleMask, 64 / 32 >;
		using DynamicStates_t			= FixedArray< VkDynamicState, 32 >;
		using VertexBindings_t			= FixedArray< VkVertexInputBindingDescription, FG_MaxVertexBuffers >;
		using VertexAttributes_t		= FixedArray< VkVertexInputAttributeDescription, FG_MaxAttribs >;
		using Viewports_t				= FixedArray< VkViewport, FG_MaxViewports >;
		using Scissors_t				= FixedArray< VkRect2D, FG_MaxViewports >;
		using VertexBuffers_t			= FixedArray< Pair<ResourceID, VkDeviceSize>, FG_MaxVertexBuffers >;
		using PushConstantState_t		= FixedArray< uint32_t, FG_MaxPushConstantsSize/4 >;


		struct GraphicsPipelineState
		{
			VkPipelineInputAssemblyStateCreateInfo	inputAssembly;
			VkPipelineColorBlendStateCreateInfo		blendState;
			ColorBlendAttachments_t					blendAttachments;
			VkPipelineDepthStencilStateCreateInfo	depthStencilState;
			VkPipelineMultisampleStateCreateInfo	multisampleState;
			SampleMask_t							sampleMask;
			VkPipelineRasterizationStateCreateInfo	rasterizationState;
			VkPipelineTessellationStateCreateInfo	tessellationState;
			//VkPipelineDynamicStateCreateInfo		dynamicStates;
			DynamicStates_t							dynamicStates;
			VkPipelineVertexInputStateCreateInfo	vertexInput;
			VertexBindings_t						vertexBindings;
			VertexAttributes_t						vertexAttribs;
			//VkPipelineViewportStateCreateInfo		viewports;
			Viewports_t								viewports;
			Scissors_t								scissors;
		};


		struct IndexBuffer
		{
			ResourceID			buffer;
			VkDeviceSize		offset;
			VkIndexType			indexType;
		};


		struct CmdBufferState
		{
			GraphicsPipelineState		pipelineState;
			VertexBuffers_t				vertexBuffers;
			IndexBuffer					indexBuffer;
			ResourceID					graphicsPipeline;
			ResourceID					computePipeline;
		};

		using CmdBufferPipelineStateMap_t		= HashMap< ResourceID, GraphicsPipelineState >;


	// variables
	private:


	// methods
	public:
	};


}	// VTC
