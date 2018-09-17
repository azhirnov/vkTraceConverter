// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Analyzer/IAnalyzer.h"
#include "Analyzer/ResourceTracker.h"

namespace VTC
{

	//
	// Image Usage Analyzer
	//

	class ImageUsageAnalyzer final : public IAnalyzer
	{
	// types
	public:
		struct ImageInfo
		{
			ResourceID					id				= 0;
			VkImageCreateInfo			createInfo		= {};
			ResourceID					swapchain		= 0;
			VkImageUsageFlags			usage			= 0;
			VkAccessFlags				allAccessFlags	= 0;
			VkPipelineStageFlags		allStageFlags	= 0;
			HashSet<VkImageLayout>		layouts;
			HashSet<ResourceID>			imageViews;
		};

		using ImagesMap_t		= ResourceTracker< ImageInfo >;
		using ImageInfo_t		= ImagesMap_t::Item_t;


		struct ImageViewInfo
		{
			ResourceID					id			= 0;
			ImageInfo_t *				image		= null;
			VkImageViewCreateInfo		createInfo	= {};
		};
		
		using ImageViewsMap_t	= ResourceTracker< ImageViewInfo >;
		using ImageViewInfo_t	= ImageViewsMap_t::Item_t;


		struct FramebufferInfo
		{
			FixedArray< ImageViewInfo_t*, FG_MaxColorBuffers+1 >	attachment;
		};


		struct RenderPassInfo
		{
		// types
			static constexpr uint	maxAttachments	= FG_MaxColorBuffers+1;
			static constexpr uint	maxSubpasses	= FG_MaxRenderPassSubpasses;

			using Attachments_t		= FixedArray< VkAttachmentDescription, maxAttachments >;
			using AttachmentsRef_t	= FixedArray< VkAttachmentReference, maxAttachments >;
			
			struct Subpass {
				AttachmentsRef_t		colorAttachmentsRef;
				AttachmentsRef_t		inputAttachmetsRef;
				VkAttachmentReference	depthStencilRef		= {};
			};
			using Subpasses_t		= FixedArray< Subpass, maxSubpasses >;

		// variables
			Attachments_t		attachments;
			Subpasses_t			subpasses;
		};


		struct CommandBufferState
		{
			ResourceID		renderPass		= 0;
			ResourceID		framebuffer		= 0;
			uint			subpassIndex	= 0;
		};


		using FramebufferMap_t	= ResourceTracker< FramebufferInfo >;
		using FramebufferInfo_t	= FramebufferMap_t::Item_t;

		using RenderPassMap_t	= ResourceTracker< RenderPassInfo >;
		using RenderPassInfo_t	= RenderPassMap_t::Item_t;

		using CmdBufferMap_t	= HashMap< ResourceID, CommandBufferState >;


	// variables
	private:
		ImagesMap_t			_images;
		ImageViewsMap_t		_imageViews;
		FramebufferMap_t	_framebuffers;
		RenderPassMap_t		_renderPasses;
		CmdBufferMap_t		_cmdBuffers;


	// methods
	public:
		ImageUsageAnalyzer ();
		
		ND_ ImagesMap_t const&		GetImages ()		const	{ return _images; }
		ND_ ImageViewsMap_t const&	GetImageViews ()	const	{ return _imageViews; }


	// IAnalyzer implementation
	public:
		void PreProcess (const class AppTrace &) override {}

		void Process (const TraceRange::Iterator &) override {}
		
		void PostProcess () override {}

		void AddResourceUsage (const TraceRange::Iterator &, EResourceType, ResourceID, FrameID, EResOp) override;
		
		std::type_index		GetType ()	const override		{ return typeid(*this); }
		
		String				Report ()	const override		{ return "TODO"; }


	private:
		bool _ProcessImageUsage (const TraceRange::Iterator &, ResourceID);
		bool _ProcessImageViewUsage (const TraceRange::Iterator &, ResourceID);
		bool _ProcessFramebufferUsage (const TraceRange::Iterator &, ResourceID);
		bool _ProcessRenderPassUsage (const TraceRange::Iterator &, ResourceID);
		bool _ProcessCommandBufferUsage (const TraceRange::Iterator &, ResourceID);

		bool _OnCreateFramebuffer (const TraceRange::Iterator &, ResourceID);

		bool _OnCreateRenderPass (const TraceRange::Iterator &, ResourceID);
		bool _OnBeginRenderPass (const TraceRange::Iterator &);
		bool _OnNextSubpass (const TraceRange::Iterator &);
		bool _OnEndRenderPass (const TraceRange::Iterator &);

		bool _OnCreateImage (const TraceRange::Iterator &, ResourceID);
		bool _OnGetSwapchainImages (const TraceRange::Iterator &, ResourceID);
		bool _OnClearColorImage (const TraceRange::Iterator &pos, ImageInfo_t &image);
		bool _OnClearDepthStencilImage (const TraceRange::Iterator &pos, ImageInfo_t &image);
		bool _OnCopyImageToBuffer (const TraceRange::Iterator &pos, ImageInfo_t &image);
		bool _OnCopyBufferToImage (const TraceRange::Iterator &pos, ImageInfo_t &image);
		bool _OnCopyImage (const TraceRange::Iterator &pos, ImageInfo_t &image);
		bool _OnResolveImage (const TraceRange::Iterator &pos, ImageInfo_t &image);
		bool _OnBlitImage (const TraceRange::Iterator &pos, ImageInfo_t &image);
		bool _OnCreateImageView (const TraceRange::Iterator &pos, ImageInfo_t &image);

		bool _ProcessSubpass (const RenderPassInfo::Subpass &sp, const FramebufferInfo_t &fbAttachment);

		bool _ProcessImageMemoryBarriers (TraceRange::Bookmark pos,
										  VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask,
										  ArrayView<VkImageMemoryBarrier> barriers);

		bool _AddImageUsage (ImageInfo_t &image, VkImageUsageFlags usage, VkImageLayout layout);
		bool _AddImageUsage (ImageInfo_t &image, VkPipelineStageFlags stage, VkAccessFlags access, VkImageLayout layout);
	};


}	// VTC
