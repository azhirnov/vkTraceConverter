// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Analyzer/IAnalyzer.h"
#include "Analyzer/ResourceTracker.h"

namespace VTC
{

	//
	// Render Pass Analyzer
	//

	class RenderPassAnalyzer final : public IAnalyzer
	{
	// types
	public:
		using AttachmentsRef_t		= Array< VkAttachmentReference >;
		using DepthStencilRef_t		= std::optional< VkAttachmentReference >;
		using Dependencies_t		= Array< VkSubpassDependency >;
		using Preserves_t			= Array< uint >;

		struct Subpass
		{
			VkSubpassDescriptionFlags	flags				= 0;
			VkPipelineBindPoint			pipelineBindPoint	= VK_PIPELINE_BIND_POINT_MAX_ENUM;
			AttachmentsRef_t			colorAttachments;
			DepthStencilRef_t			depthStencilAttachment;
			AttachmentsRef_t			resolveAttachments;
			AttachmentsRef_t			inputAttachments;
			Preserves_t					preserveAttachments;
		};

		using Subpasses_t			= Array< Subpass >;
		using Attachments_t			= Array< VkAttachmentDescription >;


		struct RenderPassInfo
		{
			ResourceID				id			= 0;
			VkRenderPassCreateFlags	flags		= 0;
			Attachments_t			attachments;
			Subpasses_t				subpasses;
			Dependencies_t			dependencies;
		};

		using RenderPassesMap_t	= ResourceTracker< RenderPassInfo, DefaultBookmark, true  >;
		using RenderPassInfo_t	= RenderPassesMap_t::Item_t;


		struct FramebufferInfo
		{
			ResourceID					id			= 0;
			VkFramebufferCreateFlags	flags		= 0;
			ResourceID					renderPass	= 0;
			uint32_t					width		= 0;
			uint32_t					height		= 0;
			uint32_t					layers		= 0;
			Array<ResourceID>			imageViews;
		};

		using FramebufferMap_t	= ResourceTracker< FramebufferInfo, DefaultBookmark, true  >;
		using FramebufferInfo_t	= FramebufferMap_t::Item_t;


	// variables
	private:
		RenderPassesMap_t			_renderPasses;
		FramebufferMap_t			_framebuffers;


	// methods
	public:
		RenderPassAnalyzer ();
		
		ND_ FramebufferInfo_t const *	GetFramebuffer (ResourceID id, TraceRange::Bookmark pos) const		{ return _framebuffers.FindIn( id, pos ); }
		ND_ RenderPassInfo_t const *	GetRenderPass (ResourceID id, TraceRange::Bookmark pos) const		{ return _renderPasses.FindIn( id, pos ); }


	// IAnalyzer implementation
	public:
		void PreProcess (const class AppTrace &) override;
		void Process (const TraceRange::Iterator &) override {}
		void PostProcess () override {}
		void AddResourceUsage (const TraceRange::Iterator &, EResourceType, ResourceID, FrameID, EResOp) override;

		std::type_index		GetType ()	const override		{ return typeid(*this); }
		String				Report ()	const override		{ return "TODO"; }


	private:
		bool _ProcessFramebufferUsage (const TraceRange::Iterator &, ResourceID, EResOp);
		bool _ProcessRenderPassUsage (const TraceRange::Iterator &, ResourceID, EResOp);
		
		bool _OnCreateFramebuffer (const TraceRange::Iterator &, ResourceID);

		bool _OnCreateRenderPass (const TraceRange::Iterator &, ResourceID);
	};


}	// VTC
