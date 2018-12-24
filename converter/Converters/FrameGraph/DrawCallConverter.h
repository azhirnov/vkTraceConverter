// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'
/*
	docs:
	https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#pipelines-dynamic-state
	https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#descriptorsets-compatibility
*/

#pragma once

#include "Converters/FrameGraph/FrameGraphConverter.h"
#include "Converters/FrameGraph/PipelineConverter.h"
#include "framegraph/Public/RenderPassDesc.h"
#include "framegraph/Public/FrameGraphDrawTask.h"

namespace VTC
{

	//
	// Draw Call Converter
	//

	class FrameGraphConverter::DrawCallConverter
	{
	// types
	private:
		struct DescriptorSetInfo
		{
			struct Descriptor
			{
			    VkDescriptorType		descriptorType	= VK_DESCRIPTOR_TYPE_MAX_ENUM;
			    VkShaderStageFlags		stageFlags		= 0;
				
				struct {
					VkSampler				sampler		= VK_NULL_HANDLE;
					VkImageView				view		= VK_NULL_HANDLE;
					VkImageLayout			layout		= VK_IMAGE_LAYOUT_UNDEFINED;
				}						image;

				struct {
					VkBuffer				handle			= VK_NULL_HANDLE;
					VkDeviceSize			offset			= 0;
					VkDeviceSize			range			= 0;
					uint					dynamicOffset	= 0;
				}						buffer;

				VkBufferView			bufferView		= VK_NULL_HANDLE;
			};

			ResourceID				layout		= 0;
			Array< Descriptor >		descriptors;

			DescriptorSetInfo () {}
			explicit DescriptorSetInfo (ResourceID layout) : layout{layout} {}
		};
		using DestriptorSetMap_t	= HashMap< ResourceID, DescriptorSetInfo >;
		
		using DestriptorStates_t	= StaticArray< DescriptorSetInfo, FG_MaxDescriptorSets >;
		using PushConstants_t		= FixedMap< PushConstantID, _fg_hidden_::PushConstantData, FG_MaxPushConstants >;
		using ColorBuffers_t		= _fg_hidden_::ColorBuffers_t;


		struct PipelineState
		{
			ResourceID				pipelineId		= 0;
			DestriptorStates_t		descriptors;
			PushConstants_t			pushConstants;
		};

		struct IndexBufferState
		{
			ResourceID			buffer		= 0;
			VkDeviceSize		offset		= 0;
			EIndex				indexType	= Default;
		};

		struct VertexBufferState
		{
			ResourceID			buffer		= 0;
			VkDeviceSize		offset		= 0;
		};
		using VertexBuffers_t	= StaticArray< VertexBufferState, FG_MaxVertexBuffers >;
		

		struct DynamicStates
		{
			using Viewports_t	= StaticArray< Optional<VkViewport>, FG_MaxViewports >;
			using Scissors_t	= StaticArray< Optional<VkRect2D>, FG_MaxViewports >;
			
			struct DepthBias {
				float		constantFactor;
				float		clamp;
				float		slopeFactor;
			};
			struct DepthBounds {
				float		min;
				float		max;
			};
			using StencilFace = StaticArray< Optional<uint>, 2 >;	// VK_STENCIL_FACE_FRONT_BIT, VK_STENCIL_FACE_BACK_BIT

			Viewports_t				viewports;				// VK_DYNAMIC_STATE_VIEWPORT
			Optional<uint>			viewportCount;
			Scissors_t				scissors;				// VK_DYNAMIC_STATE_SCISSOR
			Optional<uint>			scissorCount;
			Optional<float>			lineWidth;				// VK_DYNAMIC_STATE_LINE_WIDTH
			Optional<DepthBias>		depthBias;				// VK_DYNAMIC_STATE_DEPTH_BIAS
			Optional<float4>		blendConstants;			// VK_DYNAMIC_STATE_BLEND_CONSTANTS
			Optional<DepthBounds>	depthBounds;			// VK_DYNAMIC_STATE_DEPTH_BOUNDS
			StencilFace				stencilCompareMask;		// VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK
			StencilFace				stencilWriteMask;		// VK_DYNAMIC_STATE_STENCIL_WRITE_MASK
			StencilFace				stencilReference;		// VK_DYNAMIC_STATE_STENCIL_REFERENCE
				// VK_DYNAMIC_STATE_VIEWPORT_W_SCALING_NV
				// VK_DYNAMIC_STATE_DISCARD_RECTANGLE_EXT
				// VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_EXT
				// VK_DYNAMIC_STATE_VIEWPORT_SHADING_RATE_PALETTE_NV
				// VK_DYNAMIC_STATE_VIEWPORT_COARSE_SAMPLE_ORDER_NV
				// VK_DYNAMIC_STATE_EXCLUSIVE_SCISSOR_NV

			HashSet<VkDynamicState>	current;
		};


		struct RenderPass
		{
			FG::RenderPassDesc		desc;
			uint					index			= UMax;
			uint					drawCallCount	= 0;
			bool					isInitialized	= false;
		};
		using RenderPasses_t		= Deque< RenderPass >;

		using RenderTargets_t		= HashMap< RawImageID, FG::RenderPassDesc::ClearValue_t >;


		struct CommandBufferState
		{
			// for recording
			PipelineState				computePpln;
			PipelineState				graphicsPpln;
			DynamicStates				dynamicStates;
			IndexBufferState			indexBuffer;
			VertexBuffers_t				vertexBuffers;
			Ptr< RenderPass >			renderPass;
			RenderTargets_t				renderTargetClear;
			ResourceID					currRenderPass		= 0;
			ResourceID					currFramebuffer		= 0;
			uint						subpassIndex		= UMax;
			bool						isRecording			= false;

			// statistic
			uint						drawCallCount		= 0;
			uint						dispatchCount		= 0;
			uint						renderPassCount		= 0;
			FrameID						lastSubmission		= UMax;
			uint						submissionCount		= 0;

			// after recording
			UniquePtr<TracePacker>		threadPacker;
			UniquePtr<TracePacker>		renderpassPacker;
			VkCommandBufferUsageFlags	usageFlags			= 0;
		};
		using CmdBufferStates_t		= HashMap< ResourceID, CommandBufferState >;


		struct CommandPoolInfo
		{
			HashSet< ResourceID >	cmdBuffers;
		};
		using CommandPools_t		= HashMap< ResourceID, CommandPoolInfo >;

		struct DescriptorPoolInfo
		{
			HashSet< ResourceID >	descriptorSets;
		};
		using DescriptorPools_t		= HashMap< ResourceID, DescriptorPoolInfo >;

		using EMemoryUsage			= MemoryObjAnalyzer::EMemoryUsage;


	// variables
	private:
		FrameGraphConverter &	_fgConv;

		CmdBufferStates_t		_cmdBuffers;
		CommandPools_t			_cmdPools;

		RenderPasses_t			_renderPasses;
		uint					_maxRenderPasses	= 0;

		DestriptorSetMap_t		_descriptorSets;
		DescriptorPools_t		_descriptorPools;


	// methods
	public:
		explicit DrawCallConverter (FrameGraphConverter &fgConv);

		bool CreateCommandPool (const TraceRange::Iterator &);
		bool DestroyCommandPool (const TraceRange::Iterator &);
		bool ResetCommandPool (const TraceRange::Iterator &);
		bool AllocateCommandBuffers (const TraceRange::Iterator &);
		bool FreeCommandBuffers (const TraceRange::Iterator &);
		bool BeginCommandBuffer (const TraceRange::Iterator &);
		bool EndCommandBuffer (const TraceRange::Iterator &);
		bool ResetCommandBuffer (const TraceRange::Iterator &);
		
		bool CreateDescriptorPool (const TraceRange::Iterator &);
		bool DestroyDescriptorPool (const TraceRange::Iterator &);
		bool ResetDescriptorPool (const TraceRange::Iterator &);
		bool AllocateDescriptorSets (const TraceRange::Iterator &);
		bool FreeDescriptorSets (const TraceRange::Iterator &);
		bool UpdateDescriptorSets (const TraceRange::Iterator &);

		bool CmdBindPipeline (const TraceRange::Iterator &);
		bool CmdSetViewport (const TraceRange::Iterator &);
		bool CmdSetScissor (const TraceRange::Iterator &);
		bool CmdSetLineWidth (const TraceRange::Iterator &);
		bool CmdSetDepthBias (const TraceRange::Iterator &);
		bool CmdSetBlendConstants (const TraceRange::Iterator &);
		bool CmdSetDepthBounds (const TraceRange::Iterator &);
		bool CmdSetStencilCompareMask (const TraceRange::Iterator &);
		bool CmdSetStencilWriteMask (const TraceRange::Iterator &);
		bool CmdSetStencilReference (const TraceRange::Iterator &);
		bool CmdBindDescriptorSets (const TraceRange::Iterator &);
		bool CmdBindIndexBuffer (const TraceRange::Iterator &);
		bool CmdBindVertexBuffers (const TraceRange::Iterator &);
		bool CmdDraw (const TraceRange::Iterator &);
		bool CmdDrawIndexed (const TraceRange::Iterator &);
		bool CmdDrawIndirect (const TraceRange::Iterator &);
		bool CmdDrawIndexedIndirect (const TraceRange::Iterator &);
		bool CmdDispatch (const TraceRange::Iterator &);
		bool CmdDispatchIndirect (const TraceRange::Iterator &);
		bool CmdCopyBuffer (const TraceRange::Iterator &, FrameID);
		bool CmdCopyImage (const TraceRange::Iterator &, FrameID);
		bool CmdBlitImage (const TraceRange::Iterator &);
		bool CmdCopyBufferToImage (const TraceRange::Iterator &, FrameID);
		bool CmdCopyImageToBuffer (const TraceRange::Iterator &, FrameID);
		bool CmdUpdateBuffer (const TraceRange::Iterator &, FrameID);
		bool CmdFillBuffer (const TraceRange::Iterator &);
		bool CmdClearColorImage (const TraceRange::Iterator &);
		bool CmdClearDepthStencilImage (const TraceRange::Iterator &);
		bool CmdClearAttachments (const TraceRange::Iterator &);
		bool CmdResolveImage (const TraceRange::Iterator &);
		bool CmdPushConstants (const TraceRange::Iterator &);
		bool CmdBeginRenderPass (const TraceRange::Iterator &);
		bool CmdNextSubpass (const TraceRange::Iterator &);
		bool CmdEndRenderPass (const TraceRange::Iterator &);
		bool CmdExecuteCommands (const TraceRange::Iterator &);
		bool CmdDispatchBase (const TraceRange::Iterator &);
		bool CmdPushDescriptorSet (const TraceRange::Iterator &);
		bool CmdPushDescriptorSetWithTemplate (const TraceRange::Iterator &);

		bool QueueSubmit (const TraceRange::Iterator &, FrameID, INOUT TracePacker &);
		bool QueuePresent (const TraceRange::Iterator &, FrameID, INOUT TracePacker &);

		ND_ uint  GetMaxLogicalPasses () const		{ return _maxRenderPasses; }


	private:
		void _UpdateGraphicsPipelineDynamicStates (INOUT DynamicStates &, const HashSet<VkDynamicState> &, uint viewportCount, uint scissorCount) const;
		bool _UpdateDescriptorSet (INOUT PipelineState &, ResourceID layout) const;
		bool _UpdatePushConstants (INOUT PipelineState &, ResourceID layout) const;
		bool _BindDescriptorSet (INOUT DestriptorStates_t &, const packet_vkCmdBindDescriptorSets &) const;
		bool _CheckPipeline (const PipelineState &) const;

		ND_ bool _BufferHasHostAccess (ResourceID id, TraceRange::Bookmark pos) const;
		ND_ bool _ImageHasHostAccess (ResourceID id, TraceRange::Bookmark pos) const;

		bool _UpdateImage (CommandBufferState &, const packet_vkCmdCopyBufferToImage &, TraceRange::Bookmark, FrameID);
		bool _UpdateImage (CommandBufferState &, const packet_vkCmdCopyImage &, TraceRange::Bookmark, FrameID);

		bool _ReadImage (CommandBufferState &, const packet_vkCmdCopyBufferToImage &, TraceRange::Bookmark);
		bool _ReadImage (CommandBufferState &, const packet_vkCmdCopyImage &, TraceRange::Bookmark);

		bool _UpdateBuffer (CommandBufferState &, const packet_vkCmdCopyBuffer &, TraceRange::Bookmark, FrameID);
		bool _UpdateBuffer (CommandBufferState &, const packet_vkCmdCopyImageToBuffer &, TraceRange::Bookmark, FrameID);

		bool _ReadBuffer (CommandBufferState &, const packet_vkCmdCopyBuffer &, TraceRange::Bookmark);
		bool _ReadBuffer (CommandBufferState &, const packet_vkCmdCopyImageToBuffer &, TraceRange::Bookmark);

		bool _AddRenderPass (const RenderPassAnalyzer::RenderPassInfo_t &, const RenderPassAnalyzer::FramebufferInfo_t &, uint,
							 const VkRenderPassBeginInfo *, TraceRange::Bookmark, OUT RenderPass &) const;

		bool _MergeRenderPassStates (CommandBufferState &) const;

		bool _ConvertImageView (const ImageAnalyzer::ImageViewInfo_t &, OUT FG::ImageViewDesc &) const;

		bool _CompareDescriptorLayouts (ResourceID, ResourceID) const;
		
		bool _PackBaseDrawVertices (const CommandBufferState &, TraceRange::Bookmark, TracePacker &) const;
		bool _PackBaseDrawCall (const CommandBufferState &, TraceRange::Bookmark, TracePacker &) const;
		bool _PackDynamicStates (const CommandBufferState &, TracePacker &) const;
		bool _PackDescriptors (const PipelineDescription::DescriptorSets_t &, const FrameGraphConverter::PipelineConverter::PipelineLayoutInfo &,
								const DestriptorStates_t &, Ptr<RenderPass>, TraceRange::Bookmark, TracePacker &) const;
		bool _PackScissors (const CommandBufferState &, TracePacker &) const;
		bool _PackColorBuffers (const CommandBufferState &, TracePacker &) const;

		bool _PackRenderPass (CommandBufferState &) const;
	};


}	// VTC
