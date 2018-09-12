// Copyright (c)  Zhirnov Andrey. For more information see 'LICENSE.txt'

#include "Analyzer/ImageUsageAnalyzer.h"

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
	Process
=================================================
*/	
	void ImageUsageAnalyzer::Process (const TraceRange::Iterator &pos)
	{
		switch ( pos->packet_id )
		{
			// CmdWaitEvents
			case VKTRACE_TPI_VK_vkCmdWaitEvents : {
				auto&	packet = pos.Cast<packet_vkCmdWaitEvents>();

				CHECK( _ProcessImageMemoryBarriers( pos.GetBookmark(), pos->packet_id, packet.srcStageMask, packet.dstStageMask,
												    { packet.pImageMemoryBarriers, packet.imageMemoryBarrierCount } ));
				break;
			}

			// CmdPipelineBarrier
			case VKTRACE_TPI_VK_vkCmdPipelineBarrier : {
				packet_vkCmdPipelineBarrier const&	packet = pos.Cast<packet_vkCmdPipelineBarrier>();
				
				CHECK( _ProcessImageMemoryBarriers( pos.GetBookmark(), pos->packet_id, packet.srcStageMask, packet.dstStageMask,
												    { packet.pImageMemoryBarriers, packet.imageMemoryBarrierCount } ));
				break;
			}

			case VKTRACE_TPI_VK_vkCreateFramebuffer :		CHECK( _OnCreateFramebuffer( pos ));	break;
			case VKTRACE_TPI_VK_vkCreateRenderPass :		CHECK( _OnCreateRenderPass( pos ));		break;
			case VKTRACE_TPI_VK_vkCmdBeginRenderPass :		CHECK( _OnBeginRenderPass( pos ));		break;
			case VKTRACE_TPI_VK_vkCmdNextSubpass :			CHECK( _OnNextSubpass( pos ));			break;
			case VKTRACE_TPI_VK_vkCmdEndRenderPass :		CHECK( _OnEndRenderPass( pos ));		break;
			case VKTRACE_TPI_VK_vkCreateImage :				CHECK( _OnCreateImage( pos ));			break;
			case VKTRACE_TPI_VK_vkGetSwapchainImagesKHR :	CHECK( _OnGetSwapchainImages( pos ));	break;
		}
	}
	
/*
=================================================
	_OnCreateFramebuffer
=================================================
*/
	bool ImageUsageAnalyzer::_OnCreateFramebuffer (const TraceRange::Iterator &pos)
	{
		auto&	packet = pos.Cast<packet_vkCreateFramebuffer>();
		CHECK_ERR( packet.pCreateInfo );
		ASSERT( packet.pCreateInfo->pNext == null );	// add support if assert triggered

		auto	framebuffer	= _framebuffers.insert({ ResourceID(*packet.pFramebuffer), FbAttachmentRef_t() }).first;
		auto	renderpass	= _renderPasses.find( ResourceID(packet.pCreateInfo->renderPass) );
		CHECK_ERR( renderpass != _renderPasses.end() );

		for (uint i = 0; i < packet.pCreateInfo->attachmentCount; ++i)
		{
			auto	imageview = _imageViews.find( ResourceID(packet.pCreateInfo->pAttachments[i]) );
			CHECK_ERR( imageview != _imageViews.end() );

			framebuffer->second.push_back( &imageview->second );
		}
		return true;
	}
	
/*
=================================================
	_OnCreateRenderPass
=================================================
*/
	bool ImageUsageAnalyzer::_OnCreateRenderPass (const TraceRange::Iterator &pos)
	{
		auto&	packet = pos.Cast<packet_vkCreateRenderPass>();
		CHECK_ERR( packet.pCreateInfo );
		ASSERT( packet.pCreateInfo->pNext == null );	// add support if assert triggered

		auto	renderpass = _renderPasses.insert({ ResourceID(*packet.pRenderPass), RenderPassInfo() }).first;

		for (uint i = 0; i < packet.pCreateInfo->attachmentCount; ++i) {
			renderpass->second.attachments.push_back( packet.pCreateInfo->pAttachments[i] );
		}

		for (uint i = 0; i < packet.pCreateInfo->subpassCount; ++i)
		{
			renderpass->second.subpasses.push_back( {} );

			const auto&	subpass = packet.pCreateInfo->pSubpasses[i];

			for (uint j = 0; j < subpass.colorAttachmentCount; ++j) {
				renderpass->second.subpasses.back().colorAttachmentsRef.push_back( subpass.pColorAttachments[j] );
			}
			for (uint j = 0; j < subpass.inputAttachmentCount; ++j) {
				renderpass->second.subpasses.back().inputAttachmetsRef.push_back( subpass.pInputAttachments[j] );
			}
			if ( subpass.pDepthStencilAttachment ) {
				renderpass->second.subpasses.back().depthStencilRef = *subpass.pDepthStencilAttachment;
			}
		}
		return true;
	}
	
/*
=================================================
	_ProcessSubpass
=================================================
*/
	bool ImageUsageAnalyzer::_ProcessSubpass (const TraceRange::Iterator &pos, const RenderPassInfo::Subpass &sp, FbAttachmentRef_t &fbAttachments)
	{
		for (auto& attachment : sp.colorAttachmentsRef)
		{
			auto*	image = fbAttachments[ attachment.attachment ]->image;

			_AddImageUsage( pos.GetBookmark(), pos->packet_id, image, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, attachment.layout );
		}
		
		for (auto& attachment : sp.inputAttachmetsRef)
		{
			auto*	image = fbAttachments[ attachment.attachment ]->image;

			_AddImageUsage( pos.GetBookmark(), pos->packet_id, image, VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT, attachment.layout );
		}

		if ( sp.depthStencilRef.layout != VK_IMAGE_LAYOUT_UNDEFINED )
		{
			auto*	image = fbAttachments[ sp.depthStencilRef.attachment ]->image;

			_AddImageUsage( pos.GetBookmark(), pos->packet_id, image, VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT, sp.depthStencilRef.layout );
		}

		// TODO: resolve attachments
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

		auto	renderpass	= _renderPasses.find( ResourceID(packet.pRenderPassBegin->renderPass) );
		auto	framebuffer	= _framebuffers.find( ResourceID(packet.pRenderPassBegin->framebuffer) );

		CHECK_ERR( renderpass != _renderPasses.end() );
		CHECK_ERR( framebuffer != _framebuffers.end() );
		CHECK_ERR( renderpass->second.attachments.size() == framebuffer->second.size() );


		for (size_t i = 0; i < renderpass->second.attachments.size(); ++i)
		{
			const auto&	rp_att = renderpass->second.attachments[i];
			auto&		fb_att = framebuffer->second[i];

			fb_att->bookmarks.push_back({ pos.GetBookmark(), pos->packet_id });
					
			_AddImageUsage( pos.GetBookmark(), pos->packet_id, fb_att->image, 0, rp_att.initialLayout );
		}

		CHECK_ERR( _ProcessSubpass( pos, renderpass->second.subpasses.front(), framebuffer->second ));
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

		auto	renderpass	= _renderPasses.find( cmd_buffer->second.renderPass );
		auto	framebuffer	= _framebuffers.find( cmd_buffer->second.framebuffer );
		CHECK_ERR( renderpass != _renderPasses.end() );
		CHECK_ERR( framebuffer != _framebuffers.end() );
		
		CHECK_ERR( _ProcessSubpass( pos, renderpass->second.subpasses.front(), framebuffer->second ));
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

		auto	renderpass	= _renderPasses.find( cmd_buffer->second.renderPass );
		auto	framebuffer	= _framebuffers.find( cmd_buffer->second.framebuffer );
		CHECK_ERR( renderpass != _renderPasses.end() );
		CHECK_ERR( framebuffer != _framebuffers.end() );
		
		for (size_t i = 0; i < renderpass->second.attachments.size(); ++i)
		{
			const auto&	rp_att = renderpass->second.attachments[i];
			auto&		fb_att = framebuffer->second[i];

			fb_att->bookmarks.push_back({ pos.GetBookmark(), pos->packet_id });
					
			_AddImageUsage( pos.GetBookmark(), pos->packet_id, fb_att->image, 0, rp_att.finalLayout );
		}
		return true;
	}
	
/*
=================================================
	_OnCreateImage
=================================================
*/
	bool ImageUsageAnalyzer::_OnCreateImage (const TraceRange::Iterator &pos)
	{
		auto&	packet = pos.Cast<packet_vkCreateImage>();
		CHECK_ERR( packet.pCreateInfo );
		ASSERT( packet.pCreateInfo->pNext == null );	// add support if assert triggered

		auto	image = _images.insert({ ResourceID(*packet.pImage), ImageInfo{*packet.pCreateInfo} }).first;

		image->second.bookmarks.push_back({ pos.GetBookmark(), pos->packet_id });
		return true;
	}
	
/*
=================================================
	_OnGetSwapchainImages
=================================================
*/
	bool ImageUsageAnalyzer::_OnGetSwapchainImages (const TraceRange::Iterator &pos)
	{
		auto&	packet = pos.Cast<packet_vkGetSwapchainImagesKHR>();
				
		if ( packet.pSwapchainImageCount and packet.pSwapchainImages )
		{
			for (uint i = 0; i < *packet.pSwapchainImageCount; ++i)
			{
				auto	image = _images.insert({ ResourceID(packet.pSwapchainImages[i]), ImageInfo() }).first;

				image->second.bookmarks.push_back({ pos.GetBookmark(), pos->packet_id });
			}
		}
		return true;
	}

/*
=================================================
	AddResourceUsage
=================================================
*/
	void ImageUsageAnalyzer::AddResourceUsage (const TraceRange::Iterator &pos, EResourceType type, ResourceID id, FrameID)
	{
		switch ( type )
		{
			case VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT :		CHECK( _ProcessImageUsage( pos, id ));			break;
			case VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_VIEW_EXT :	CHECK( _ProcessImageViewUsage( pos, id ));		break;
		}
	}
	
/*
=================================================
	_ProcessImageUsage
=================================================
*/
	bool ImageUsageAnalyzer::_ProcessImageUsage (const TraceRange::Iterator &pos, ResourceID id)
	{
		if ( pos->packet_id == VKTRACE_TPI_VK_vkCreateImage or
			 pos->packet_id == VKTRACE_TPI_VK_vkGetSwapchainImagesKHR )
			return true;

		auto	image = _images.find( id );
		CHECK_ERR( image != _images.end() );

		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkCmdClearColorImage :			CHECK( _OnClearColorImage( pos, image ));			break;
			case VKTRACE_TPI_VK_vkCmdClearDepthStencilImage :	CHECK( _OnClearDepthStencilImage( pos, image ));	break;
			case VKTRACE_TPI_VK_vkCmdCopyImageToBuffer :		CHECK( _OnCopyImageToBuffer( pos, image ));			break;
			case VKTRACE_TPI_VK_vkCmdCopyBufferToImage :		CHECK( _OnCopyBufferToImage( pos, image ));			break;
			case VKTRACE_TPI_VK_vkCmdCopyImage :				CHECK( _OnCopyImage( pos, image ));					break;
			case VKTRACE_TPI_VK_vkCmdResolveImage :				CHECK( _OnResolveImage( pos, image ));				break;
			case VKTRACE_TPI_VK_vkCmdBlitImage :				CHECK( _OnBlitImage( pos, image ));					break;
			case VKTRACE_TPI_VK_vkCreateImageView :				CHECK( _OnCreateImageView( pos, image ));			break;
				
			// ignore
			case VKTRACE_TPI_VK_vkCmdWaitEvents :				break;
			case VKTRACE_TPI_VK_vkCmdPipelineBarrier :			break;

			case VKTRACE_TPI_VK_vkDestroyImage :
			case VKTRACE_TPI_VK_vkGetImageMemoryRequirements :
			case VKTRACE_TPI_VK_vkBindImageMemory :
				image->second.bookmarks.push_back({ pos.GetBookmark(), pos->packet_id });
				break;

			default : {
				ASSERT(false);
				image->second.bookmarks.push_back({ pos.GetBookmark(), pos->packet_id });
				break;
			}
		}
		return true;
	}
	
/*
=================================================
	_OnClearColorImage
=================================================
*/
	bool ImageUsageAnalyzer::_OnClearColorImage (const TraceRange::Iterator &pos, ImagesMap_t::iterator image)
	{
		auto&	packet = pos.Cast<packet_vkCmdClearColorImage>();
		CHECK_ERR( image->first == ResourceID(packet.image) );
				
		_AddImageUsage( pos.GetBookmark(), pos->packet_id, &image->second, VK_IMAGE_USAGE_TRANSFER_DST_BIT, packet.imageLayout );
		return true;
	}
	
/*
=================================================
	_OnClearDepthStencilImage
=================================================
*/
	bool ImageUsageAnalyzer::_OnClearDepthStencilImage (const TraceRange::Iterator &pos, ImagesMap_t::iterator image)
	{
		auto&	packet = pos.Cast<packet_vkCmdClearDepthStencilImage>();
		CHECK_ERR( image->first == ResourceID(packet.image) );

		_AddImageUsage( pos.GetBookmark(), pos->packet_id, &image->second, VK_IMAGE_USAGE_TRANSFER_DST_BIT, packet.imageLayout );
		return true;
	}
	
/*
=================================================
	_OnCopyImageToBuffer
=================================================
*/
	bool ImageUsageAnalyzer::_OnCopyImageToBuffer (const TraceRange::Iterator &pos, ImagesMap_t::iterator image)
	{
		auto&	packet = pos.Cast<packet_vkCmdCopyImageToBuffer>();
		CHECK_ERR( image->first == ResourceID(packet.srcImage) );
				
		_AddImageUsage( pos.GetBookmark(), pos->packet_id, &image->second, VK_IMAGE_USAGE_TRANSFER_SRC_BIT, packet.srcImageLayout );
		return true;
	}
	
/*
=================================================
	_OnCopyBufferToImage
=================================================
*/
	bool ImageUsageAnalyzer::_OnCopyBufferToImage (const TraceRange::Iterator &pos, ImagesMap_t::iterator image)
	{
		auto&	packet = pos.Cast<packet_vkCmdCopyBufferToImage>();
		CHECK_ERR( image->first == ResourceID(packet.dstImage) );
				
		_AddImageUsage( pos.GetBookmark(), pos->packet_id, &image->second, VK_IMAGE_USAGE_TRANSFER_DST_BIT, packet.dstImageLayout );
		return true;
	}
	
/*
=================================================
	_OnCopyImage
=================================================
*/
	bool ImageUsageAnalyzer::_OnCopyImage (const TraceRange::Iterator &pos, ImagesMap_t::iterator image)
	{
		auto&	packet = pos.Cast<packet_vkCmdCopyImage>();

		CHECK_ERR(	image->first == ResourceID(packet.srcImage) or
					image->first == ResourceID(packet.dstImage) );

		if ( image->first == ResourceID(packet.srcImage) ) {
			_AddImageUsage( pos.GetBookmark(), pos->packet_id, &image->second, VK_IMAGE_USAGE_TRANSFER_SRC_BIT, packet.srcImageLayout );
		}
		if ( image->first == ResourceID(packet.dstImage) ) {
			_AddImageUsage( pos.GetBookmark(), pos->packet_id, &image->second, VK_IMAGE_USAGE_TRANSFER_DST_BIT, packet.dstImageLayout );
		}
		return true;
	}
	
/*
=================================================
	_OnResolveImage
=================================================
*/
	bool ImageUsageAnalyzer::_OnResolveImage (const TraceRange::Iterator &pos, ImagesMap_t::iterator image)
	{
		auto&	packet = pos.Cast<packet_vkCmdResolveImage>();

		CHECK_ERR(	image->first == ResourceID(packet.srcImage) or
					image->first == ResourceID(packet.dstImage) );

		if ( image->first == ResourceID(packet.srcImage) ) {
			_AddImageUsage( pos.GetBookmark(), pos->packet_id, &image->second, VK_IMAGE_USAGE_TRANSFER_SRC_BIT, packet.srcImageLayout );
		}
		if ( image->first == ResourceID(packet.dstImage) ) {
			_AddImageUsage( pos.GetBookmark(), pos->packet_id, &image->second, VK_IMAGE_USAGE_TRANSFER_DST_BIT, packet.dstImageLayout );
		}
		return true;
	}
	
/*
=================================================
	_OnBlitImage
=================================================
*/
	bool ImageUsageAnalyzer::_OnBlitImage (const TraceRange::Iterator &pos, ImagesMap_t::iterator image)
	{
		auto&	packet = pos.Cast<packet_vkCmdBlitImage >();

		CHECK_ERR(	image->first == ResourceID(packet.srcImage) or
					image->first == ResourceID(packet.dstImage) );

		if ( image->first == ResourceID(packet.srcImage) ) {
			_AddImageUsage( pos.GetBookmark(), pos->packet_id, &image->second, VK_IMAGE_USAGE_TRANSFER_SRC_BIT, packet.srcImageLayout );
		}
		if ( image->first == ResourceID(packet.dstImage) ) {
			_AddImageUsage( pos.GetBookmark(), pos->packet_id, &image->second, VK_IMAGE_USAGE_TRANSFER_DST_BIT, packet.dstImageLayout );
		}
		return true;
	}
	
/*
=================================================
	_OnCreateImageView
=================================================
*/
	bool ImageUsageAnalyzer::_OnCreateImageView (const TraceRange::Iterator &pos, ImagesMap_t::iterator image)
	{
		auto&	packet = pos.Cast<packet_vkCreateImageView>();
		CHECK_ERR( packet.pCreateInfo );
		ASSERT( packet.pCreateInfo->pNext == null );	// add support if assert triggered

		CHECK_ERR( image->first == ResourceID(packet.pCreateInfo->image) );

		_imageViews.insert({ ResourceID(*packet.pView), ImageViewInfo{ *packet.pCreateInfo, image->first, &image->second } });

		image->second.imageViews.insert( ResourceID(*packet.pView) );
		image->second.bookmarks.push_back({ pos.GetBookmark(), pos->packet_id });
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

		auto	image_view = _imageViews.find( id );
		CHECK_ERR( image_view != _imageViews.end() );

		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkDestroyImageView :
			case VKTRACE_TPI_VK_vkCreateFramebuffer :
			case VKTRACE_TPI_VK_vkUpdateDescriptorSets :	// TODO
				image_view->second.bookmarks.push_back({ pos.GetBookmark(), pos->packet_id });
				break;

			default : {
				ASSERT(false);
				image_view->second.bookmarks.push_back({ pos.GetBookmark(), pos->packet_id });
				break;
			}
		}
		return true;
	}

/*
=================================================
	_ProcessImageMemoryBarriers
=================================================
*/
	bool ImageUsageAnalyzer::_ProcessImageMemoryBarriers (TraceRange::Bookmark pos, PacketID packetId,
														  VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask,
														  ArrayView<VkImageMemoryBarrier> barriers)
	{
		for (auto& bar : barriers)
		{
			auto	image = _images.find( ResourceID(bar.image) );

			if ( image == _images.end() )
				continue;

			CHECK_ERR( _AddImageUsage( pos, packetId, &image->second, srcStageMask, bar.srcAccessMask, bar.oldLayout ));
			CHECK_ERR( _AddImageUsage( pos, packetId, &image->second, dstStageMask, bar.dstAccessMask, bar.newLayout ));
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
	bool ImageUsageAnalyzer::_AddImageUsage (TraceRange::Bookmark pos, PacketID packetId, ImageInfo *image,
											 VkPipelineStageFlags stage, VkAccessFlags access, VkImageLayout layout)
	{
		image->allAccessFlags	|= access;
		image->allStageFlags	|= stage;
		image->usage			|= ConvertToImageUsage( stage, access, layout );
		image->layouts.insert( layout );

		if ( image->bookmarks.back().pos	  != pos	or
			 image->bookmarks.back().packetId != packetId )
		{
			image->bookmarks.push_back({ pos, packetId });
		}
		return true;
	}
	
/*
=================================================
	_ProcessImageUsage
=================================================
*/
	bool ImageUsageAnalyzer::_AddImageUsage (TraceRange::Bookmark pos, PacketID packetId, ImageInfo *image,
											 VkImageUsageFlags usage, VkImageLayout layout)
	{
		image->usage		|= usage;
		image->layouts.insert( layout );

		if ( image->bookmarks.back().pos	  != pos	or
			 image->bookmarks.back().packetId != packetId )
		{
			image->bookmarks.push_back({ pos, packetId });
		}
		return true;
	}


}	// VTC
