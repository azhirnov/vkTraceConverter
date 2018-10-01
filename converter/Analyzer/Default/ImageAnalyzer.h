// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Analyzer/IAnalyzer.h"
#include "Analyzer/ResourceTracker.h"

namespace VTC
{

	//
	// Image Analyzer
	//

	class ImageAnalyzer final : public IAnalyzer
	{
	// types
	public:
		struct ImageSubresource : VkImageSubresource
		{
			ImageSubresource (const VkImageSubresource &subres) : VkImageSubresource{subres}
			{}

			ND_ bool operator == (const ImageSubresource &rhs) const {
				return	aspectMask	== rhs.aspectMask	and
						mipLevel	== rhs.mipLevel		and
						arrayLayer	== rhs.arrayLayer;
			}

			ND_ size_t  GetHash () const {
				return size_t(HashOf( aspectMask ) + HashOf( mipLevel ) + HashOf( arrayLayer ));
			}
		};

		struct ImageSubresourceHash {
			ND_ size_t  operator () (const ImageSubresource &value) const { return value.GetHash(); }
		};

		using SubresLayouts_t	= HashMap< ImageSubresource, VkSubresourceLayout, ImageSubresourceHash >;
		using ImageViewIDs_t	= HashMap< ResourceID, TraceRange::Bookmark >;


		struct ImageInfo
		{
			ResourceID					id				= 0;
			ResourceID					memId			= 0;
			ResourceID					deviceId		= 0;
			VkImageCreateInfo			createInfo		= {};
			ResourceID					swapchain		= 0;
			VkImageUsageFlags			usage			= 0;
			VkAccessFlags				allAccessFlags	= 0;
			VkPipelineStageFlags		allStageFlags	= 0;
			HashSet<VkImageLayout>		layouts;
			ImageViewIDs_t				imageViews;
			SubresLayouts_t				subresLayouts;
			VkMemoryRequirements		memRequirements	= {};
		};

		using ImagesMap_t		= ResourceTracker< ImageInfo, DefaultBookmark, true >;
		using ImageInfo_t		= ImagesMap_t::Item_t;


		struct ImageViewInfo
		{
			ResourceID					id			= 0;
			ImageInfo_t *				image		= null;
			VkImageViewCreateInfo		createInfo	= {};
		};
		
		using ImageViewsMap_t	= ResourceTracker< ImageViewInfo, DefaultBookmark, true >;
		using ImageViewInfo_t	= ImageViewsMap_t::Item_t;


	// variables
	private:
		ImagesMap_t						_images;
		ImageViewsMap_t					_imageViews;
		
		class MemoryObjAnalyzer const*	_memoryObjAnalyzer		= null;
		class RenderPassAnalyzer const*	_renderPassAnalyzer		= null;


	// methods
	public:
		ImageAnalyzer ();
		
		ND_ ImageInfo_t const*		GetImage (ResourceID id, TraceRange::Bookmark pos) const		{ return _images.FindIn( id, pos ); }
		ND_ ImageViewInfo_t const*	GetImageView (ResourceID id, TraceRange::Bookmark pos) const	{ return _imageViews.FindIn( id, pos ); }


	// IAnalyzer implementation
	public:
		void PreProcess (const class AppTrace &) override;

		void Process (const TraceRange::Iterator &) override;
		
		void PostProcess () override {}

		void AddResourceUsage (const TraceRange::Iterator &, EResourceType, ResourceID, FrameID, EResOp) override;
		
		std::type_index		GetType ()	const override		{ return typeid(*this); }
		
		String				Report ()	const override		{ return "TODO"; }


	private:
		bool _ProcessImageUsage (const TraceRange::Iterator &, ResourceID, EResOp);
		bool _ProcessImageViewUsage (const TraceRange::Iterator &, ResourceID, EResOp);
		bool _ProcessRenderPass (const TraceRange::Iterator &, ResourceID);

		bool _OnCreateImage (const TraceRange::Iterator &, ResourceID);
		bool _OnGetSwapchainImages (const TraceRange::Iterator &, ResourceID);
		bool _OnClearColorImage (const TraceRange::Iterator &, ImageInfo_t &);
		bool _OnClearDepthStencilImage (const TraceRange::Iterator &, ImageInfo_t &);
		bool _OnCopyImageToBuffer (const TraceRange::Iterator &, ImageInfo_t &);
		bool _OnCopyBufferToImage (const TraceRange::Iterator &, ImageInfo_t &);
		bool _OnCopyImage (const TraceRange::Iterator &, ImageInfo_t &);
		bool _OnResolveImage (const TraceRange::Iterator &, ImageInfo_t &);
		bool _OnBlitImage (const TraceRange::Iterator &, ImageInfo_t &);
		bool _OnGetImageSubresourceLayout (const TraceRange::Iterator &, ImageInfo_t &);
		bool _OnGetImageMemoryRequirements (const TraceRange::Iterator &, ImageInfo_t &);
		bool _OnGetImageMemoryRequirements2 (const TraceRange::Iterator &, ImageInfo_t &);
		bool _OnBindImageMemory (const TraceRange::Iterator &, ImageInfo_t &);
		bool _OnBindImageMemory2 (const TraceRange::Iterator &, ImageInfo_t &);
		
		bool _OnCreateImageView (const TraceRange::Iterator &, ResourceID);

		bool _OnBeginRenderPass (const TraceRange::Iterator &);

		bool _ProcessImageMemoryBarriers (TraceRange::Bookmark pos, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask,
										  ArrayView<VkImageMemoryBarrier> barriers);

		bool _AddImageUsage (ImageInfo_t &image, VkImageUsageFlags usage, VkImageLayout layout);
		bool _AddImageUsage (ImageInfo_t &image, VkPipelineStageFlags stage, VkAccessFlags access, VkImageLayout layout);
	};


}	// VTC
