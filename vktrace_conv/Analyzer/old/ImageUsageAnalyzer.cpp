// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Analyzer/old/ImageUsageAnalyzer.h"

namespace VTC
{

/*
=================================================
	constructor
=================================================
*/
	ImageUsageAnalyzer::ImageUsageAnalyzer ()
	{
	}

/*
=================================================
	AddResourceUsage
=================================================
*/
	void ImageUsageAnalyzer::AddResourceUsage (const TraceRange::Iterator &pos, EResourceType type, ResourceID id, FrameID, EResOp)
	{
		switch ( type )
		{
			case VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT :			CHECK( _ProcessImageUsage( pos, id ));			break;
			case VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_VIEW_EXT :		CHECK( _ProcessImageViewUsage( pos, id ));		break;
			case VK_DEBUG_REPORT_OBJECT_TYPE_FRAMEBUFFER_EXT :		CHECK( _ProcessFramebufferUsage( pos, id ));	break;
			case VK_DEBUG_REPORT_OBJECT_TYPE_RENDER_PASS_EXT :		CHECK( _ProcessRenderPassUsage( pos, id ));		break;
			case VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT :	CHECK( _ProcessCommandBufferUsage( pos, id ));	break;
		}
	}
	
/*
=================================================
	_ProcessImageUsage
=================================================
*/
	bool ImageUsageAnalyzer::_ProcessImageUsage (const TraceRange::Iterator &pos, ResourceID id)
	{
		if ( pos->packet_id == VKTRACE_TPI_VK_vkCreateImage )
			return _OnCreateImage( pos, id );

		if ( pos->packet_id == VKTRACE_TPI_VK_vkGetSwapchainImagesKHR )
			return _OnGetSwapchainImages( pos, id );
	
		ImagesMap_t::iterator	image;
		CHECK( _images.AddResourceUsage( OUT image, pos, id, FrameID(0), EResOp::Access ));

		auto&	info = image->second.back();

		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkCmdClearColorImage :			CHECK( _OnClearColorImage( pos, info ));		break;
			case VKTRACE_TPI_VK_vkCmdClearDepthStencilImage :	CHECK( _OnClearDepthStencilImage( pos, info ));	break;
			case VKTRACE_TPI_VK_vkCmdCopyImageToBuffer :		CHECK( _OnCopyImageToBuffer( pos, info ));		break;
			case VKTRACE_TPI_VK_vkCmdCopyBufferToImage :		CHECK( _OnCopyBufferToImage( pos, info ));		break;
			case VKTRACE_TPI_VK_vkCmdCopyImage :				CHECK( _OnCopyImage( pos, info ));				break;
			case VKTRACE_TPI_VK_vkCmdResolveImage :				CHECK( _OnResolveImage( pos, info ));			break;
			case VKTRACE_TPI_VK_vkCmdBlitImage :				CHECK( _OnBlitImage( pos, info ));				break;
			case VKTRACE_TPI_VK_vkCreateImageView :				CHECK( _OnCreateImageView( pos, info ));		break;
			
			case VKTRACE_TPI_VK_vkDestroyImage :
			case VKTRACE_TPI_VK_vkGetImageMemoryRequirements :
			case VKTRACE_TPI_VK_vkBindImageMemory :
			case VKTRACE_TPI_VK_vkAcquireNextImageKHR :
			case VKTRACE_TPI_VK_vkAcquireNextImage2KHX :
			case VKTRACE_TPI_VK_vkAcquireNextImage2KHR :
			case VKTRACE_TPI_VK_vkQueuePresentKHR :
			case VKTRACE_TPI_VK_vkCmdWaitEvents :
			case VKTRACE_TPI_VK_vkCmdPipelineBarrier :
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
	bool ImageUsageAnalyzer::_OnCreateImage (const TraceRange::Iterator &pos, ResourceID id)
	{
		auto&	packet = pos.Cast<packet_vkCreateImage>();
		CHECK_ERR( packet.pCreateInfo );
		CHECK_ERR( id == ResourceID(*packet.pImage) );
		ASSERT( packet.pCreateInfo->pNext == null );	// add support if assert triggered

		ImagesMap_t::iterator	image;
		CHECK_ERR( _images.AddResourceUsage( OUT image, pos, ResourceID(*packet.pImage), FrameID(0), EResOp::Construct ));

		auto&	info = image->second.back();
		
		info.id			= ResourceID(*packet.pImage);
		info.createInfo = *packet.pCreateInfo;
		info.swapchain	= ResourceID(0);
		return true;
	}
	
/*
=================================================
	_OnGetSwapchainImages
=================================================
*/
	bool ImageUsageAnalyzer::_OnGetSwapchainImages (const TraceRange::Iterator &pos, ResourceID id)
	{
		auto&	packet = pos.Cast< packet_vkGetSwapchainImagesKHR >();

		ImagesMap_t::iterator	image;
		CHECK_ERR( _images.AddResourceUsage( OUT image, pos, id, FrameID(0), EResOp::Construct ));

		auto&	info = image->second.back();

		info.id			= id;
		info.createInfo	= {};
		info.swapchain	= ResourceID(packet.swapchain);
		return true;
	}

/*
=================================================
	_OnClearColorImage
=================================================
*/
	bool ImageUsageAnalyzer::_OnClearColorImage (const TraceRange::Iterator &pos, ImageInfo_t &image)
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
	bool ImageUsageAnalyzer::_OnClearDepthStencilImage (const TraceRange::Iterator &pos, ImageInfo_t &image)
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
	bool ImageUsageAnalyzer::_OnCopyImageToBuffer (const TraceRange::Iterator &pos, ImageInfo_t &image)
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
	bool ImageUsageAnalyzer::_OnCopyBufferToImage (const TraceRange::Iterator &pos, ImageInfo_t &image)
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
	bool ImageUsageAnalyzer::_OnCopyImage (const TraceRange::Iterator &pos, ImageInfo_t &image)
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
		return true;
	}
	
/*
=================================================
	_OnResolveImage
=================================================
*/
	bool ImageUsageAnalyzer::_OnResolveImage (const TraceRange::Iterator &pos, ImageInfo_t &image)
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
		return true;
	}
	
/*
=================================================
	_OnBlitImage
=================================================
*/
	bool ImageUsageAnalyzer::_OnBlitImage (const TraceRange::Iterator &pos, ImageInfo_t &image)
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
		return true;
	}
	
/*
=================================================
	_OnCreateImageView
=================================================
*/
	bool ImageUsageAnalyzer::_OnCreateImageView (const TraceRange::Iterator &pos, ImageInfo_t &image)
	{
		auto&	packet = pos.Cast<packet_vkCreateImageView>();
		CHECK_ERR( packet.pCreateInfo );
		ASSERT( packet.pCreateInfo->pNext == null );	// add support if assert triggered
		CHECK_ERR( image.id == ResourceID(packet.pCreateInfo->image) );

		ImageViewsMap_t::iterator	view;
		CHECK_ERR( _imageViews.AddResourceUsage( OUT view, pos, ResourceID(*packet.pView), FrameID(0), EResOp::Construct ));

		auto&	info = view->second.back();

		info.id			= ResourceID(*packet.pView);
		info.createInfo	= *packet.pCreateInfo;
		info.image		= &image;

		image.imageViews.insert( ResourceID(*packet.pView) );
		return true;
	}

/*
=================================================
	_ProcessImageViewUsage
=================================================
*/
	bool ImageUsageAnalyzer::_ProcessImageViewUsage (const TraceRange::Iterator &pos, ResourceID id)
	{
		if ( pos->packet_id == VKTRACE_TPI_VK_vkCreateImageView )
			return true;

		ImageViewsMap_t::iterator	view;
		CHECK_ERR( _imageViews.AddResourceUsage( OUT view, pos, id, FrameID(0), EResOp::Access ));

		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkDestroyImageView :
			case VKTRACE_TPI_VK_vkCreateFramebuffer :
			case VKTRACE_TPI_VK_vkUpdateDescriptorSets :
				break;

			default :
				ASSERT(false);	// unknown usage
				break;
		}
		return true;
	}
	
/*
=================================================
	_ProcessImageMemoryBarriers
=================================================
*/
	bool ImageUsageAnalyzer::_ProcessFramebufferUsage (const TraceRange::Iterator &pos, ResourceID id)
	{
		switch( pos->packet_id )
		{
			// CreateFramebuffer
			case VKTRACE_TPI_VK_vkCreateFramebuffer :
				CHECK_ERR( _OnCreateFramebuffer( pos, id ));
				break;

			// DestroyFramebuffer
			case VKTRACE_TPI_VK_vkDestroyFramebuffer : {
				auto&	packet = pos.Cast< packet_vkDestroyFramebuffer >();

				CHECK( _framebuffers.AddResourceUsage( pos, ResourceID(packet.framebuffer), FrameID(0), EResOp::Destruct ));
				break;
			}
		}
		return true;
	}
	
/*
=================================================
	_OnCreateFramebuffer
=================================================
*/
	bool ImageUsageAnalyzer::_OnCreateFramebuffer (const TraceRange::Iterator &pos, ResourceID id)
	{
		auto&	packet = pos.Cast<packet_vkCreateFramebuffer>();
		CHECK_ERR( packet.pCreateInfo );
		CHECK_ERR( id == ResourceID(*packet.pFramebuffer) );
		ASSERT( packet.pCreateInfo->pNext == null );	// add support if assert triggered

		FramebufferMap_t::iterator	framebuffer;
		CHECK_ERR( _framebuffers.AddResourceUsage( OUT framebuffer, pos, ResourceID(*packet.pFramebuffer), FrameID(0), EResOp::Construct ));

		auto	renderpass = _renderPasses.FindIn( ResourceID(packet.pCreateInfo->renderPass), pos, false );
		CHECK_ERR( renderpass );

		for (uint i = 0; i < packet.pCreateInfo->attachmentCount; ++i)
		{
			auto	imageview = _imageViews.FindIn( ResourceID(packet.pCreateInfo->pAttachments[i]), pos, false );
			CHECK_ERR( imageview );

			framebuffer->second.back().attachment.push_back( imageview );
		}
		return true;
	}
	
/*
=================================================
	_ProcessRenderPassUsage
=================================================
*/
	bool ImageUsageAnalyzer::_ProcessRenderPassUsage (const TraceRange::Iterator &pos, ResourceID id)
	{
		switch( pos->packet_id )
		{
			// CreateRenderPass
			case VKTRACE_TPI_VK_vkCreateRenderPass :
				CHECK_ERR( _OnCreateRenderPass( pos, id ));
				break;

			// DestroyRenderPass
			case VKTRACE_TPI_VK_vkDestroyRenderPass : {
				auto&	packet = pos.Cast< packet_vkDestroyRenderPass >();

				CHECK( _renderPasses.AddResourceUsage( pos, ResourceID(packet.renderPass), FrameID(0), EResOp::Destruct ));
				break;
			}
		}
		return true;
	}
	
/*
=================================================
	_OnCreateRenderPass
=================================================
*/
	bool ImageUsageAnalyzer::_OnCreateRenderPass (const TraceRange::Iterator &pos, ResourceID id)
	{
		auto&	packet = pos.Cast<packet_vkCreateRenderPass>();
		CHECK_ERR( packet.pCreateInfo );
		CHECK_ERR( id == ResourceID(*packet.pRenderPass) );
		ASSERT( packet.pCreateInfo->pNext == null );	// add support if assert triggered

		RenderPassMap_t::iterator	renderpass;
		CHECK_ERR( _renderPasses.AddResourceUsage( OUT renderpass, pos, ResourceID(*packet.pRenderPass), FrameID(0), EResOp::Construct ));

		auto&	info = renderpass->second.back();

		for (uint i = 0; i < packet.pCreateInfo->attachmentCount; ++i) {
			info.attachments.push_back( packet.pCreateInfo->pAttachments[i] );
		}

		for (uint i = 0; i < packet.pCreateInfo->subpassCount; ++i)
		{
			info.subpasses.push_back( {} );

			const auto&	subpass = packet.pCreateInfo->pSubpasses[i];

			for (uint j = 0; j < subpass.colorAttachmentCount; ++j) {
				info.subpasses.back().colorAttachmentsRef.push_back( subpass.pColorAttachments[j] );
			}
			for (uint j = 0; j < subpass.inputAttachmentCount; ++j) {
				info.subpasses.back().inputAttachmetsRef.push_back( subpass.pInputAttachments[j] );
			}
			if ( subpass.pDepthStencilAttachment ) {
				info.subpasses.back().depthStencilRef = *subpass.pDepthStencilAttachment;
			}
		}
		return true;
	}
	
/*
=================================================
	_OnBeginRenderPass
=================================================
*/
	bool ImageUsageAnalyzer::_ProcessCommandBufferUsage (const TraceRange::Iterator &pos, ResourceID id)
	{
		switch( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkCmdBeginRenderPass :		CHECK_ERR( _OnBeginRenderPass( pos ));	break;
			case VKTRACE_TPI_VK_vkCmdNextSubpass :			CHECK_ERR( _OnNextSubpass( pos ));		break;
			case VKTRACE_TPI_VK_vkCmdEndRenderPass :		CHECK_ERR( _OnEndRenderPass( pos ));	break;
				
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

			case VKTRACE_TPI_VK_vkBeginCommandBuffer :
			case VKTRACE_TPI_VK_vkEndCommandBuffer :
			case VKTRACE_TPI_VK_vkResetCommandBuffer :
			case VKTRACE_TPI_VK_vkResetCommandPool :
			case VKTRACE_TPI_VK_vkFreeCommandBuffers :
				_cmdBuffers.erase( id );
				break;
		}
		return true;
	}

/*
=================================================
	_OnBeginRenderPass
=================================================
*/
	bool ImageUsageAnalyzer::_OnBeginRenderPass (const TraceRange::Iterator &pos)
	{
		auto&	packet = pos.Cast<packet_vkCmdBeginRenderPass>();
		CHECK_ERR( packet.pRenderPassBegin );
		ASSERT( packet.pRenderPassBegin->pNext == null );	// add support if assert triggered

		// update command buffer state
		{
			auto	cmd_buffer	= _cmdBuffers.insert({ ResourceID(packet.commandBuffer), {} }).first;

			cmd_buffer->second.renderPass	= ResourceID(packet.pRenderPassBegin->renderPass);
			cmd_buffer->second.framebuffer	= ResourceID(packet.pRenderPassBegin->framebuffer);
			cmd_buffer->second.subpassIndex	= 0;
		}

		auto	renderpass	= _renderPasses.FindIn( ResourceID(packet.pRenderPassBegin->renderPass), pos, false );
		auto	framebuffer	= _framebuffers.FindIn( ResourceID(packet.pRenderPassBegin->framebuffer), pos, false );

		CHECK_ERR( renderpass and framebuffer );
		CHECK_ERR( renderpass->attachments.size() == framebuffer->attachment.size() );


		for (size_t i = 0; i < renderpass->attachments.size(); ++i)
		{
			const auto&	rp_att = renderpass->attachments[i];
			auto&		fb_att = framebuffer->attachment[i];

			CHECK( _imageViews.AddResourceUsage( pos, fb_att->id, FrameID(0), EResOp::Access ));
			
			_AddImageUsage( *fb_att->image, 0, rp_att.initialLayout );
		}

		CHECK_ERR( _ProcessSubpass( renderpass->subpasses.front(), *framebuffer ));
		return true;
	}
	
/*
=================================================
	_OnNextSubpass
=================================================
*/
	bool ImageUsageAnalyzer::_OnNextSubpass (const TraceRange::Iterator &pos)
	{
		auto&	packet = pos.Cast<packet_vkCmdNextSubpass>();

		auto	cmd_buffer	= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd_buffer != _cmdBuffers.end() );

		auto	renderpass	= _renderPasses.FindIn( cmd_buffer->second.renderPass, pos, false );
		auto	framebuffer	= _framebuffers.FindIn( cmd_buffer->second.framebuffer, pos, false );
		CHECK_ERR( renderpass and framebuffer );
		
		CHECK_ERR( _ProcessSubpass( renderpass->subpasses.front(), *framebuffer ));
		return true;
	}
	
/*
=================================================
	_ProcessSubpass
=================================================
*/
	bool ImageUsageAnalyzer::_ProcessSubpass (const RenderPassInfo::Subpass &sp, const FramebufferInfo_t &info)
	{
		for (auto& attachment : sp.colorAttachmentsRef)
		{
			auto*	image = info.attachment[ attachment.attachment ]->image;

			_AddImageUsage( *image, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, attachment.layout );
		}
		
		for (auto& attachment : sp.inputAttachmetsRef)
		{
			auto*	image = info.attachment[ attachment.attachment ]->image;

			_AddImageUsage( *image, VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT, attachment.layout );
		}

		if ( sp.depthStencilRef.layout != VK_IMAGE_LAYOUT_UNDEFINED )
		{
			auto*	image = info.attachment[ sp.depthStencilRef.attachment ]->image;

			_AddImageUsage( *image, VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT, sp.depthStencilRef.layout );
		}

		// TODO: resolve attachments
		return true;
	}
	
/*
=================================================
	_OnEndRenderPass
=================================================
*/
	bool ImageUsageAnalyzer::_OnEndRenderPass (const TraceRange::Iterator &pos)
	{
		auto&	packet = pos.Cast<packet_vkCmdEndRenderPass>();

		auto	cmd_buffer	= _cmdBuffers.find( ResourceID(packet.commandBuffer) );
		CHECK_ERR( cmd_buffer != _cmdBuffers.end() );

		auto	renderpass	= _renderPasses.FindIn( cmd_buffer->second.renderPass, pos, false );
		auto	framebuffer	= _framebuffers.FindIn( cmd_buffer->second.framebuffer, pos, false );
		CHECK_ERR( renderpass and framebuffer );
		
		for (size_t i = 0; i < renderpass->attachments.size(); ++i)
		{
			const auto&	rp_att = renderpass->attachments[i];
			auto&		fb_att = framebuffer->attachment[i];

			CHECK( _imageViews.AddResourceUsage( pos, fb_att->id, FrameID(0), EResOp::Access ));
			
			_AddImageUsage( *fb_att->image, 0, rp_att.finalLayout );
		}
		return true;
	}

/*
=================================================
	_ProcessImageMemoryBarriers
=================================================
*/
	bool ImageUsageAnalyzer::_ProcessImageMemoryBarriers (TraceRange::Bookmark pos,
														  VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask,
														  ArrayView<VkImageMemoryBarrier> barriers)
	{
		for (auto& bar : barriers)
		{
			auto	image = _images.FindIn( ResourceID(bar.image), pos );

			if ( not image )
				continue;

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
			case VK_IMAGE_LAYOUT_RANGE_SIZE :							break;
			case VK_IMAGE_LAYOUT_MAX_ENUM :								break;

			case VK_IMAGE_LAYOUT_GENERAL :
			{
				for (VkAccessFlags j = 1; j < VK_ACCESS_FLAG_BITS_MAX_ENUM; j <<= 1)
				{
					if ( not EnumEq( access, j ) )
						continue;

					switch ( j )
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
	bool ImageUsageAnalyzer::_AddImageUsage (ImageInfo_t &image, VkPipelineStageFlags stage, VkAccessFlags access, VkImageLayout layout)
	{
		image.allAccessFlags	|= access;
		image.allStageFlags		|= stage;
		image.usage				|= ConvertToImageUsage( stage, access, layout );
		image.layouts.insert( layout );
		return true;
	}
	
	bool ImageUsageAnalyzer::_AddImageUsage (ImageInfo_t &image, VkImageUsageFlags usage, VkImageLayout layout)
	{
		image.usage		|= usage;
		image.layouts.insert( layout );
		return true;
	}


}	// VTC
