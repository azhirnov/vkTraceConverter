// Copyright (c)  Zhirnov Andrey. For more information see 'LICENSE.txt'

#pragma once

#include "Analyzer/IAnalyzer.h"

namespace VTC
{

	//
	// Image Usage Analyzer
	//

	class ImageUsageAnalyzer final : public IAnalyzer
	{
	// types
	public:
		struct Bookmark
		{
			TraceRange::Bookmark		pos;
			PacketID					packetId;
		};


		struct ImageInfo
		{
			VkImageCreateInfo			createInfo		= {};
			VkImageUsageFlags			usage			= 0;
			VkAccessFlags				allAccessFlags	= 0;
			VkPipelineStageFlags		allStageFlags	= 0;
			HashSet<VkImageLayout>		layouts;
			HashSet<ResourceID>			imageViews;
			Array<Bookmark>				bookmarks;

			ImageInfo () {}
			explicit ImageInfo (const VkImageCreateInfo &ci) : createInfo{ci} {}
		};


		struct ImageViewInfo
		{
			ImageInfo *					image;
			ResourceID					imageId;
			VkImageViewCreateInfo		createInfo;
			Array<Bookmark>				bookmarks;

			ImageViewInfo (const VkImageViewCreateInfo &ci, ResourceID imageId, ImageInfo *imgRef) :
				image{imgRef}, imageId{imageId}, createInfo{ci} {}
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


		using ImagesMap_t		= HashMap< ResourceID, ImageInfo >;
		using ImageViewsMap_t	= HashMap< ResourceID, ImageViewInfo >;

		using FbAttachmentRef_t	= FixedArray< ImageViewInfo*, FG_MaxColorBuffers+1 >;
		using FramebufferMap_t	= HashMap< ResourceID, FbAttachmentRef_t >;			// link framebuffer to image views
		using RenderPassMap_t	= HashMap< ResourceID, RenderPassInfo >;
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
		void Process (const TraceRange::Iterator &) override;
		
		void PostProcess () override {}

		void AddResourceUsage (const TraceRange::Iterator &, EResourceType, ResourceID, FrameID) override;
		
		std::type_index		GetType ()	const override		{ return typeid(*this); }
		
		String				Report ()	const override		{ return "TODO"; }


	private:
		bool _ProcessImageUsage (const TraceRange::Iterator &, ResourceID);
		bool _ProcessImageViewUsage (const TraceRange::Iterator &, ResourceID);

		bool _OnCreateFramebuffer (const TraceRange::Iterator &);
		bool _OnCreateRenderPass (const TraceRange::Iterator &);
		bool _OnBeginRenderPass (const TraceRange::Iterator &);
		bool _OnNextSubpass (const TraceRange::Iterator &);
		bool _OnEndRenderPass (const TraceRange::Iterator &);
		bool _OnCreateImage (const TraceRange::Iterator &);
		bool _OnGetSwapchainImages (const TraceRange::Iterator &);

		bool _OnClearColorImage (const TraceRange::Iterator &pos, ImagesMap_t::iterator image);
		bool _OnClearDepthStencilImage (const TraceRange::Iterator &pos, ImagesMap_t::iterator image);
		bool _OnCopyImageToBuffer (const TraceRange::Iterator &pos, ImagesMap_t::iterator image);
		bool _OnCopyBufferToImage (const TraceRange::Iterator &pos, ImagesMap_t::iterator image);
		bool _OnCopyImage (const TraceRange::Iterator &pos, ImagesMap_t::iterator image);
		bool _OnResolveImage (const TraceRange::Iterator &pos, ImagesMap_t::iterator image);
		bool _OnBlitImage (const TraceRange::Iterator &pos, ImagesMap_t::iterator image);
		bool _OnCreateImageView (const TraceRange::Iterator &pos, ImagesMap_t::iterator image);

		bool _ProcessSubpass (const TraceRange::Iterator &pos, const RenderPassInfo::Subpass &sp, FbAttachmentRef_t &fbAttachment);

		bool _ProcessImageMemoryBarriers (TraceRange::Bookmark pos, PacketID packetId,
										  VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask,
										  ArrayView<VkImageMemoryBarrier> barriers);

		bool _AddImageUsage (TraceRange::Bookmark pos, PacketID packetId, ImageInfo* image, VkImageUsageFlags usage, VkImageLayout layout);
		bool _AddImageUsage (TraceRange::Bookmark pos, PacketID packetId, ImageInfo* image, VkPipelineStageFlags stage, VkAccessFlags access, VkImageLayout layout);
	};


}	// VTC
