// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Analyzer/Default/ImageAnalyzer.h"
#include "Analyzer/Default/MemoryObjAnalyzer.h"
#include "Analyzer/Default/RenderPassAnalyzer.h"
#include "Parser/AppTrace.h"

namespace VTC
{

/*
=================================================
	constructor
=================================================
*/
	ImageAnalyzer::ImageAnalyzer ()
	{
	}

/*
=================================================
	PreProcess
=================================================
*/
	void ImageAnalyzer::PreProcess (const AppTrace &appTrace)
	{
		_memoryObjAnalyzer	= appTrace.GetAnalyzer< MemoryObjAnalyzer >();
		_renderPassAnalyzer	= appTrace.GetAnalyzer< RenderPassAnalyzer >();

		CHECK( _memoryObjAnalyzer and _renderPassAnalyzer );

		// TODO: add link to command buffer analyzer, render pass analyzer, ...
	}
	
/*
=================================================
	Process
=================================================
*/
	void ImageAnalyzer::Process (const TraceRange::Iterator &pos)
	{
		switch( pos->packet_id )
		{
			// CmdWaitEvents
			case VKTRACE_TPI_VK_vkCmdWaitEvents : {
				auto&	packet = pos.Cast<packet_vkCmdWaitEvents>();

				CHECK( _ProcessImageMemoryBarriers( pos.GetBookmark(), packet.srcStageMask, packet.dstStageMask,
												    { packet.pImageMemoryBarriers, packet.imageMemoryBarrierCount } ));
				break;
			}

			// CmdPipelineBarrier
			case VKTRACE_TPI_VK_vkCmdPipelineBarrier : {
				packet_vkCmdPipelineBarrier const&	packet = pos.Cast<packet_vkCmdPipelineBarrier>();
				
				CHECK( _ProcessImageMemoryBarriers( pos.GetBookmark(), packet.srcStageMask, packet.dstStageMask,
												    { packet.pImageMemoryBarriers, packet.imageMemoryBarrierCount } ));
				break;
			}
		}
	}

/*
=================================================
	AddResourceUsage
=================================================
*/
	void ImageAnalyzer::AddResourceUsage (const TraceRange::Iterator &pos, EResourceType type, ResourceID id, FrameID, EResOp op)
	{
		switch ( type )
		{
			case VK_OBJECT_TYPE_IMAGE :			CHECK( _ProcessImageUsage( pos, id, op ));		break;
			case VK_OBJECT_TYPE_IMAGE_VIEW :	CHECK( _ProcessImageViewUsage( pos, id, op ));	break;
			case VK_OBJECT_TYPE_RENDER_PASS :	CHECK( _ProcessRenderPass( pos, id ));			break;
		}
	}
	
/*
=================================================
	_ProcessImageUsage
=================================================
*/
	bool ImageAnalyzer::_ProcessImageUsage (const TraceRange::Iterator &pos, ResourceID id, EResOp op)
	{
		if ( pos->packet_id == VKTRACE_TPI_VK_vkCreateImage )
			return _OnCreateImage( pos, id );

		if ( pos->packet_id == VKTRACE_TPI_VK_vkGetSwapchainImagesKHR )
			return _OnGetSwapchainImages( pos, id );
	
		ImagesMap_t::iterator	image;
		CHECK( _images.AddResourceUsage( OUT image, pos, id, op ));

		auto&	info = image->second.back();

		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkCmdClearColorImage :						CHECK( _OnClearColorImage( pos, info ));				break;
			case VKTRACE_TPI_VK_vkCmdClearDepthStencilImage :				CHECK( _OnClearDepthStencilImage( pos, info ));			break;
			case VKTRACE_TPI_VK_vkCmdCopyImageToBuffer :					CHECK( _OnCopyImageToBuffer( pos, info ));				break;
			case VKTRACE_TPI_VK_vkCmdCopyBufferToImage :					CHECK( _OnCopyBufferToImage( pos, info ));				break;
			case VKTRACE_TPI_VK_vkCmdCopyImage :							CHECK( _OnCopyImage( pos, info ));						break;
			case VKTRACE_TPI_VK_vkCmdResolveImage :							CHECK( _OnResolveImage( pos, info ));					break;
			case VKTRACE_TPI_VK_vkCmdBlitImage :							CHECK( _OnBlitImage( pos, info ));						break;
			case VKTRACE_TPI_VK_vkGetImageSubresourceLayout :				CHECK( _OnGetImageSubresourceLayout( pos, info ));		break;
			case VKTRACE_TPI_VK_vkGetImageMemoryRequirements :				CHECK( _OnGetImageMemoryRequirements( pos, info ));		break;
			case VKTRACE_TPI_VK_vkGetImageMemoryRequirements2 :
			case VKTRACE_TPI_VK_vkGetImageMemoryRequirements2KHR :			CHECK( _OnGetImageMemoryRequirements2( pos, info ));	break;
			case VKTRACE_TPI_VK_vkGetImageSparseMemoryRequirements :		break;
			case VKTRACE_TPI_VK_vkGetImageSparseMemoryRequirements2 :		break;
			case VKTRACE_TPI_VK_vkGetImageSparseMemoryRequirements2KHR :	break;	// TODO
			case VKTRACE_TPI_VK_vkBindImageMemory :							CHECK( _OnBindImageMemory( pos, info ));				break;
			case VKTRACE_TPI_VK_vkBindImageMemory2 :
			case VKTRACE_TPI_VK_vkBindImageMemory2KHR :						CHECK( _OnBindImageMemory2( pos, info ));				break;

			case VKTRACE_TPI_VK_vkDestroyImage :
			case VKTRACE_TPI_VK_vkAllocateMemory :
			case VKTRACE_TPI_VK_vkAcquireNextImageKHR :
			case VKTRACE_TPI_VK_vkAcquireNextImage2KHX :
			case VKTRACE_TPI_VK_vkAcquireNextImage2KHR :
			case VKTRACE_TPI_VK_vkQueuePresentKHR :
			case VKTRACE_TPI_VK_vkCmdWaitEvents :
			case VKTRACE_TPI_VK_vkCmdPipelineBarrier :
			case VKTRACE_TPI_VK_vkCreateImageView :
			case VKTRACE_TPI_VK_vkDestroySwapchainKHR :
				break;

			default :
				ASSERT(false);	// unknown usage
				break;
		}
		return true;
	}
	
/*
=================================================
	_OnCreateImage
=================================================
*/
	bool ImageAnalyzer::_OnCreateImage (const TraceRange::Iterator &pos, ResourceID id)
	{
		auto&	packet = pos.Cast<packet_vkCreateImage>();
		CHECK_ERR( packet.pCreateInfo );
		CHECK_ERR( id == ResourceID(*packet.pImage) );
		//ASSERT( packet.pCreateInfo->pNext == null );	// add support if assert triggered

		ImagesMap_t::iterator	image;
		CHECK_ERR( _images.AddResourceUsage( OUT image, pos, ResourceID(*packet.pImage), EResOp::Construct ));

		auto&	info = image->second.back();
		
		info.id			= ResourceID(*packet.pImage);
		info.createInfo = *packet.pCreateInfo;
		info.deviceId	= ResourceID(packet.device);
		info.swapchain	= ResourceID(0);
		return true;
	}
	
/*
=================================================
	_OnGetSwapchainImages
=================================================
*/
	bool ImageAnalyzer::_OnGetSwapchainImages (const TraceRange::Iterator &pos, ResourceID id)
	{
		auto&	packet = pos.Cast< packet_vkGetSwapchainImagesKHR >();

		ImagesMap_t::iterator	image;
		CHECK_ERR( _images.AddResourceUsage( OUT image, pos, id, EResOp::Construct ));

		auto&	info = image->second.back();

		info.id			= id;
		info.createInfo	= {};
		info.deviceId	= ResourceID(packet.device);
		info.swapchain	= ResourceID(packet.swapchain);
		return true;
	}

/*
=================================================
	_OnClearColorImage
=================================================
*/
	bool ImageAnalyzer::_OnClearColorImage (const TraceRange::Iterator &pos, ImageInfo_t &image)
	{
		auto&	packet = pos.Cast<packet_vkCmdClearColorImage>();
		CHECK_ERR( image.id == ResourceID(packet.image) );
				
		_AddImageUsage( image, VK_IMAGE_USAGE_TRANSFER_DST_BIT, packet.imageLayout );
		return true;
	}
	
/*
=================================================
	_OnClearDepthStencilImage
=================================================
*/
	bool ImageAnalyzer::_OnClearDepthStencilImage (const TraceRange::Iterator &pos, ImageInfo_t &image)
	{
		auto&	packet = pos.Cast<packet_vkCmdClearDepthStencilImage>();
		CHECK_ERR( image.id == ResourceID(packet.image) );

		_AddImageUsage( image, VK_IMAGE_USAGE_TRANSFER_DST_BIT, packet.imageLayout );
		return true;
	}
	
/*
=================================================
	_OnCopyImageToBuffer
=================================================
*/
	bool ImageAnalyzer::_OnCopyImageToBuffer (const TraceRange::Iterator &pos, ImageInfo_t &image)
	{
		auto&	packet = pos.Cast<packet_vkCmdCopyImageToBuffer>();
		CHECK_ERR( image.id == ResourceID(packet.srcImage) );
				
		_AddImageUsage( image, VK_IMAGE_USAGE_TRANSFER_SRC_BIT, packet.srcImageLayout );
		return true;
	}
	
/*
=================================================
	_OnCopyBufferToImage
=================================================
*/
	bool ImageAnalyzer::_OnCopyBufferToImage (const TraceRange::Iterator &pos, ImageInfo_t &image)
	{
		auto&	packet = pos.Cast<packet_vkCmdCopyBufferToImage>();
		CHECK_ERR( image.id == ResourceID(packet.dstImage) );
				
		_AddImageUsage( image, VK_IMAGE_USAGE_TRANSFER_DST_BIT, packet.dstImageLayout );
		return true;
	}
	
/*
=================================================
	_OnCopyImage
=================================================
*/
	bool ImageAnalyzer::_OnCopyImage (const TraceRange::Iterator &pos, ImageInfo_t &image)
	{
		auto&	packet = pos.Cast<packet_vkCmdCopyImage>();

		CHECK_ERR(	image.id == ResourceID(packet.srcImage) or
					image.id == ResourceID(packet.dstImage) );

		if ( image.id == ResourceID(packet.srcImage) ) {
			_AddImageUsage( image, VK_IMAGE_USAGE_TRANSFER_SRC_BIT, packet.srcImageLayout );
		}
		if ( image.id == ResourceID(packet.dstImage) ) {
			_AddImageUsage( image, VK_IMAGE_USAGE_TRANSFER_DST_BIT, packet.dstImageLayout );
		}

		_AddImageAccess( image, pos.GetBookmark() );
		return true;
	}
	
/*
=================================================
	_OnResolveImage
=================================================
*/
	bool ImageAnalyzer::_OnResolveImage (const TraceRange::Iterator &pos, ImageInfo_t &image)
	{
		auto&	packet = pos.Cast<packet_vkCmdResolveImage>();

		CHECK_ERR(	image.id == ResourceID(packet.srcImage) or
					image.id == ResourceID(packet.dstImage) );

		if ( image.id == ResourceID(packet.srcImage) ) {
			_AddImageUsage( image, VK_IMAGE_USAGE_TRANSFER_SRC_BIT, packet.srcImageLayout );
		}
		if ( image.id == ResourceID(packet.dstImage) ) {
			_AddImageUsage( image, VK_IMAGE_USAGE_TRANSFER_DST_BIT, packet.dstImageLayout );
		}

		_AddImageAccess( image, pos.GetBookmark() );
		return true;
	}
	
/*
=================================================
	_OnBlitImage
=================================================
*/
	bool ImageAnalyzer::_OnBlitImage (const TraceRange::Iterator &pos, ImageInfo_t &image)
	{
		auto&	packet = pos.Cast<packet_vkCmdBlitImage >();

		CHECK_ERR(	image.id == ResourceID(packet.srcImage) or
					image.id == ResourceID(packet.dstImage) );

		if ( image.id == ResourceID(packet.srcImage) ) {
			_AddImageUsage( image, VK_IMAGE_USAGE_TRANSFER_SRC_BIT, packet.srcImageLayout );
		}
		if ( image.id == ResourceID(packet.dstImage) ) {
			_AddImageUsage( image, VK_IMAGE_USAGE_TRANSFER_DST_BIT, packet.dstImageLayout );
		}

		_AddImageAccess( image, pos.GetBookmark() );
		return true;
	}
	
/*
=================================================
	_OnGetImageSubresourceLayout
=================================================
*/
	bool ImageAnalyzer::_OnGetImageSubresourceLayout (const TraceRange::Iterator &pos, ImageInfo_t &image)
	{
		auto&	packet = pos.Cast< packet_vkGetImageSubresourceLayout >();
		CHECK_ERR( image.id == ResourceID(packet.image) );

		image.subresLayouts.insert({ ImageSubresource{*packet.pSubresource}, *packet.pLayout });
		return true;
	}
	
/*
=================================================
	_OnGetImageMemoryRequirements
=================================================
*/
	bool ImageAnalyzer::_OnGetImageMemoryRequirements (const TraceRange::Iterator &pos, ImageInfo_t &image)
	{
		auto&	packet = pos.Cast< packet_vkGetImageMemoryRequirements >();
		CHECK_ERR( image.id == ResourceID(packet.image) );

		image.memRequirements = *packet.pMemoryRequirements;
		return true;
	}
	
/*
=================================================
	_OnGetImageMemoryRequirements2
=================================================
*/
	bool ImageAnalyzer::_OnGetImageMemoryRequirements2 (const TraceRange::Iterator &pos, ImageInfo_t &image)
	{
		STATIC_ASSERT( sizeof(packet_vkGetImageMemoryRequirements2) == sizeof(packet_vkGetImageMemoryRequirements2KHR) );

		auto&	packet = pos.Cast< packet_vkGetImageMemoryRequirements2 >();
		CHECK_ERR( image.id == ResourceID(packet.pInfo->image) );
		ASSERT( packet.pInfo->pNext == null );					// add support if triggered
		//ASSERT( packet.pMemoryRequirements->pNext == null );	// add support if triggered

		image.memRequirements = packet.pMemoryRequirements->memoryRequirements;
		return true;
	}
	
/*
=================================================
	_OnBindImageMemory
=================================================
*/
	bool ImageAnalyzer::_OnBindImageMemory (const TraceRange::Iterator &pos, ImageInfo_t &image)
	{
		auto&	packet = pos.Cast< packet_vkBindImageMemory >();
		CHECK_ERR( image.id == ResourceID(packet.image) );

		image.memId		= ResourceID(packet.memory);
		image.memOffset	= packet.memoryOffset;
		return true;
	}
	
/*
=================================================
	_OnBindImageMemory2
=================================================
*/
	bool ImageAnalyzer::_OnBindImageMemory2 (const TraceRange::Iterator &pos, ImageInfo_t &image)
	{
		STATIC_ASSERT( sizeof(packet_vkBindImageMemory2) == sizeof(packet_vkBindImageMemory2KHR) );

		auto&	packet = pos.Cast< packet_vkBindImageMemory2 >();

		for (uint i = 0; i < packet.bindInfoCount; ++i)
		{
			if ( image.id == ResourceID(packet.pBindInfos[i].image) )
			{
				ASSERT( packet.pBindInfos[i].pNext == null );	// add support if triggered

				image.memId		= ResourceID(packet.pBindInfos[i].memory);
				image.memOffset	= packet.pBindInfos[i].memoryOffset;
				break;
			}
		}
		return true;
	}

/*
=================================================
	_ProcessImageViewUsage
=================================================
*/
	bool ImageAnalyzer::_ProcessImageViewUsage (const TraceRange::Iterator &pos, ResourceID id, EResOp op)
	{
		if ( pos->packet_id == VKTRACE_TPI_VK_vkCreateImageView )
			return _OnCreateImageView( pos, id );

		if ( pos->packet_id == VKTRACE_TPI_VK_vkDestroyFramebuffer )
			return true;	// TODO: image view may be already destroyed

		ImageViewsMap_t::iterator	view;
		CHECK_ERR( _imageViews.AddResourceUsage( OUT view, pos, id, op ));

		auto&	info = view->second.back();

		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkDestroyImageView :
			case VKTRACE_TPI_VK_vkCreateFramebuffer :
			case VKTRACE_TPI_VK_vkDestroyFramebuffer :
				break;

			case VKTRACE_TPI_VK_vkUpdateDescriptorSets :
			case VKTRACE_TPI_VK_vkCmdBeginRenderPass :
			case VKTRACE_TPI_VK_vkCmdNextSubpass :
			case VKTRACE_TPI_VK_vkCmdEndRenderPass :
				_AddImageAccess( *info.image, pos.GetBookmark() );
				break;

			// render target usage
			case VKTRACE_TPI_VK_vkCmdDraw :
			case VKTRACE_TPI_VK_vkCmdDrawIndirect :
			case VKTRACE_TPI_VK_vkCmdDrawIndirectCountAMD :
			case VKTRACE_TPI_VK_vkCmdDrawIndexed :
			case VKTRACE_TPI_VK_vkCmdDrawIndexedIndirect :
			case VKTRACE_TPI_VK_vkCmdDrawIndexedIndirectCountAMD :
				_AddImageAccess( *info.image, pos.GetBookmark() );
				break;

			default :
				ASSERT(false);	// unknown usage
				break;
		}
		return true;
	}
	
/*
=================================================
	_OnCreateImageView
=================================================
*/
	bool ImageAnalyzer::_OnCreateImageView (const TraceRange::Iterator &pos, ResourceID id)
	{
		auto&	packet = pos.Cast<packet_vkCreateImageView>();
		CHECK_ERR( packet.pCreateInfo );
		CHECK_ERR( id == ResourceID(*packet.pView) );
		ASSERT( packet.pCreateInfo->pNext == null );	// add support if assert triggered

		auto*	image = _images.FindIn( ResourceID(packet.pCreateInfo->image), pos );
		CHECK_ERR( image );

		ImageViewsMap_t::iterator	view;
		CHECK_ERR( _imageViews.AddResourceUsage( OUT view, pos, id, EResOp::Construct ));

		auto&	info = view->second.back();

		info.id			= id;
		info.createInfo	= *packet.pCreateInfo;
		info.image		= image;

		image->imageViews.insert({ id, pos.GetBookmark() });
		
		_AddImageAccess( *image, pos.GetBookmark() );
		return true;
	}
	
/*
=================================================
	_ProcessRenderPass
=================================================
*/
	bool ImageAnalyzer::_ProcessRenderPass (const TraceRange::Iterator &pos, ResourceID)
	{
		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkCmdBeginRenderPass :	CHECK( _OnBeginRenderPass( pos ));	break;
		}
		return true;
	}
	
/*
=================================================
	_OnBeginRenderPass
=================================================
*/
	bool ImageAnalyzer::_OnBeginRenderPass (const TraceRange::Iterator &pos)
	{
		auto&	packet = pos.Cast< packet_vkCmdBeginRenderPass >();

		auto*	fb_info	= _renderPassAnalyzer->GetFramebuffer( ResourceID(packet.pRenderPassBegin->framebuffer), pos.GetBookmark() );
		auto*	rp_info	= _renderPassAnalyzer->GetRenderPass( ResourceID(packet.pRenderPassBegin->renderPass), pos.GetBookmark() );
		CHECK_ERR( fb_info and rp_info );

		Array<ImageInfo_t *>	images;

		for (auto& view : fb_info->imageViews)
		{
			auto*	view_info = _imageViews.FindIn( view, pos.GetBookmark() );
			CHECK_ERR( view_info );

			images.push_back( view_info->image );
		}

		// add usage from initial and final state
		for (size_t i = 0; i < rp_info->attachments.size(); ++i)
		{
			_AddImageUsage( *images[i], 0, 0, rp_info->attachments[i].initialLayout );
			_AddImageUsage( *images[i], 0, 0, rp_info->attachments[i].finalLayout );
		}

		// add usage from subpasses
		for (auto& subpass : rp_info->subpasses)
		{
			for (auto& col : subpass.colorAttachments) {
				if ( col.attachment < images.size() )
					_AddImageUsage( *images[col.attachment], 0, VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT, col.layout );
			}

			if ( subpass.depthStencilAttachment.has_value() and subpass.depthStencilAttachment->attachment < images.size() )
				_AddImageUsage( *images[subpass.depthStencilAttachment->attachment], 0, VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT, subpass.depthStencilAttachment->layout );

			for (auto& res : subpass.resolveAttachments) {
				if ( res.attachment < images.size() )
					_AddImageUsage( *images[res.attachment], 0, VK_ACCESS_TRANSFER_READ_BIT, res.layout );
			}

			for (auto& in : subpass.inputAttachments) {
				if ( in.attachment < images.size() )
					_AddImageUsage( *images[in.attachment], 0, VK_ACCESS_INPUT_ATTACHMENT_READ_BIT, in.layout );
			}
		}

		return true;
	}

/*
=================================================
	_ProcessImageMemoryBarriers
=================================================
*/
	bool ImageAnalyzer::_ProcessImageMemoryBarriers (TraceRange::Bookmark pos, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask,
													 ArrayView<VkImageMemoryBarrier> barriers)
	{
		for (auto& bar : barriers)
		{
			auto*	image = _images.FindIn( ResourceID(bar.image), pos );
			CHECK_ERR( image );

			CHECK_ERR( _AddImageUsage( *image, srcStageMask, bar.srcAccessMask, bar.oldLayout ));
			CHECK_ERR( _AddImageUsage( *image, dstStageMask, bar.dstAccessMask, bar.newLayout ));
		}
		return true;
	}
	
/*
=================================================
	ConvertToImageUsage
=================================================
*/
	ND_ static VkImageUsageFlags  ConvertToImageUsage (VkPipelineStageFlags, VkAccessFlags access, VkImageLayout layout)
	{
		ENABLE_ENUM_CHECKS();
		switch ( layout )
		{
			case VK_IMAGE_LAYOUT_UNDEFINED :							break;
			case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL :				return VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
			case VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL :
			case VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL :
			case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL :
			case VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL :		return VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
			case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL :					return VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
			case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL :					return VK_IMAGE_USAGE_TRANSFER_DST_BIT;
			case VK_IMAGE_LAYOUT_PREINITIALIZED :						break;
			case VK_IMAGE_LAYOUT_PRESENT_SRC_KHR :						break;
			case VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR :					break;
			case VK_IMAGE_LAYOUT_SHADING_RATE_OPTIMAL_NV :				return VK_IMAGE_USAGE_SHADING_RATE_IMAGE_BIT_NV;
			case VK_IMAGE_LAYOUT_RANGE_SIZE :							break;
			case VK_IMAGE_LAYOUT_MAX_ENUM :								break;
			case VK_IMAGE_LAYOUT_FRAGMENT_DENSITY_MAP_OPTIMAL_EXT :		return VK_IMAGE_USAGE_FRAGMENT_DENSITY_MAP_BIT_EXT;

			case VK_IMAGE_LAYOUT_GENERAL :
			{
				for (VkAccessFlags j = 1; j < VK_ACCESS_FLAG_BITS_MAX_ENUM; j <<= 1)
				{
					if ( not EnumEq( access, j ) )
						continue;

					switch ( VkAccessFlagBits(j) )
					{
						case VK_ACCESS_INDIRECT_COMMAND_READ_BIT :				break;
						case VK_ACCESS_INDEX_READ_BIT :							break;
						case VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT :				break;
						case VK_ACCESS_UNIFORM_READ_BIT :						break;
						case VK_ACCESS_INPUT_ATTACHMENT_READ_BIT :				return VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT;
						case VK_ACCESS_SHADER_READ_BIT :
						case VK_ACCESS_SHADER_WRITE_BIT :						return VK_IMAGE_USAGE_STORAGE_BIT;
						case VK_ACCESS_COLOR_ATTACHMENT_READ_NONCOHERENT_BIT_EXT :
						case VK_ACCESS_COLOR_ATTACHMENT_READ_BIT :
						case VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT :				return VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
						case VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT :
						case VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT :		return VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
						case VK_ACCESS_TRANSFER_READ_BIT :						return VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
						case VK_ACCESS_TRANSFER_WRITE_BIT :						return VK_IMAGE_USAGE_TRANSFER_DST_BIT;
						case VK_ACCESS_HOST_READ_BIT :							break;
						case VK_ACCESS_HOST_WRITE_BIT :							break;
						case VK_ACCESS_MEMORY_READ_BIT :						break;
						case VK_ACCESS_MEMORY_WRITE_BIT :						break;
						case VK_ACCESS_CONDITIONAL_RENDERING_READ_BIT_EXT :		break;
						case VK_ACCESS_COMMAND_PROCESS_READ_BIT_NVX :			break;
						case VK_ACCESS_COMMAND_PROCESS_WRITE_BIT_NVX :			break;
						case VK_ACCESS_TRANSFORM_FEEDBACK_WRITE_BIT_EXT :		break;
						case VK_ACCESS_TRANSFORM_FEEDBACK_COUNTER_READ_BIT_EXT:	break;
						case VK_ACCESS_TRANSFORM_FEEDBACK_COUNTER_WRITE_BIT_EXT:break;
						case VK_ACCESS_SHADING_RATE_IMAGE_READ_BIT_NV :			return VK_IMAGE_USAGE_SHADING_RATE_IMAGE_BIT_NV;
						case VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_NV :		break;
						case VK_ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_NV :	break;
						case VK_ACCESS_FRAGMENT_DENSITY_MAP_READ_BIT_EXT :		return VK_IMAGE_USAGE_FRAGMENT_DENSITY_MAP_BIT_EXT;
						case VK_ACCESS_FLAG_BITS_MAX_ENUM :						break;
					}
				}
				break;
			}

			case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL :
			{
				if ( access == VK_ACCESS_INPUT_ATTACHMENT_READ_BIT )
					return VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT;
				else
					return VK_IMAGE_USAGE_SAMPLED_BIT;
			}
		}
		DISABLE_ENUM_CHECKS();
		return 0;
	}
	
/*
=================================================
	_AddImageUsage
=================================================
*/
	bool ImageAnalyzer::_AddImageUsage (ImageInfo_t &image, VkPipelineStageFlags stage, VkAccessFlags access, VkImageLayout layout)
	{
		image.allAccessFlags	|= access;
		image.allStageFlags		|= stage;
		image.usage				|= ConvertToImageUsage( stage, access, layout );
		image.layouts.insert( layout );
		return true;
	}
	
	bool ImageAnalyzer::_AddImageUsage (ImageInfo_t &image, VkImageUsageFlags usage, VkImageLayout layout)
	{
		image.usage		|= usage;
		image.layouts.insert( layout );
		return true;
	}
	
/*
=================================================
	_AddImageAccess
=================================================
*/
	void ImageAnalyzer::_AddImageAccess (ImageInfo_t &image, TraceRange::Bookmark pos)
	{
		if ( image.firstAccess == TraceRange::Bookmark() )
			image.firstAccess = image.lastAccess = pos;
		else
			image.lastAccess = std::max( image.lastAccess, pos );
	}


}	// VTC
