// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Analyzer/Default/RenderPassAnalyzer.h"
#include "Parser/AppTrace.h"

namespace VTC
{

/*
=================================================
	constructor
=================================================
*/
	RenderPassAnalyzer::RenderPassAnalyzer ()
	{
	}
	
/*
=================================================
	PreProcess
=================================================
*/
	void RenderPassAnalyzer::PreProcess (const AppTrace &)
	{
		_renderPasses.clear();
		_framebuffers.clear();
	}

/*
=================================================
	AddResourceUsage
=================================================
*/
	void RenderPassAnalyzer::AddResourceUsage (const TraceRange::Iterator &pos, EResourceType type, ResourceID id, FrameID, EResOp op)
	{
		switch ( type )
		{
			case VK_DEBUG_REPORT_OBJECT_TYPE_FRAMEBUFFER_EXT :	CHECK( _ProcessFramebufferUsage( pos, id, op ));	break;
			case VK_DEBUG_REPORT_OBJECT_TYPE_RENDER_PASS_EXT :	CHECK( _ProcessRenderPassUsage( pos, id, op ));		break;
		}
	}
	
/*
=================================================
	_ProcessFramebufferUsage
=================================================
*/
	bool RenderPassAnalyzer::_ProcessFramebufferUsage (const TraceRange::Iterator &pos, ResourceID id, EResOp op)
	{
		if ( pos->packet_id == VKTRACE_TPI_VK_vkCreateFramebuffer )
			return _OnCreateFramebuffer( pos, id );
		
		FramebufferMap_t::iterator	framebuffer;
		CHECK_ERR( _framebuffers.AddResourceUsage( OUT framebuffer, pos, id, op ));

		//auto&	info = framebuffer->second.back();

		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkCmdBeginRenderPass :
			case VKTRACE_TPI_VK_vkCmdNextSubpass :
			case VKTRACE_TPI_VK_vkCmdEndRenderPass :
			case VKTRACE_TPI_VK_vkBeginCommandBuffer :	// in VkCommandBufferInheritanceInfo
			case VKTRACE_TPI_VK_vkDestroyFramebuffer :
			case VKTRACE_TPI_VK_vkCmdDrawIndexed :
			case VKTRACE_TPI_VK_vkCmdDrawIndexedIndirect :
			case VKTRACE_TPI_VK_vkCmdDrawIndexedIndirectCountAMD :
			case VKTRACE_TPI_VK_vkCmdDraw :
			case VKTRACE_TPI_VK_vkCmdDrawIndirect :
			case VKTRACE_TPI_VK_vkCmdDrawIndirectCountAMD :
				break;

			default :
				ASSERT(false);		// unknown usage
				break;
		}
		return true;
	}
	
/*
=================================================
	_OnCreateFramebuffer
=================================================
*/
	bool RenderPassAnalyzer::_OnCreateFramebuffer (const TraceRange::Iterator &pos, ResourceID id)
	{
		auto&	packet = pos.Cast< packet_vkCreateFramebuffer >();
		CHECK_ERR( ResourceID(*packet.pFramebuffer) == id );
		
		FramebufferMap_t::iterator	framebuffer;
		CHECK_ERR( _framebuffers.AddResourceUsage( OUT framebuffer, pos, id, EResOp::Construct ));
		
		auto&	info = framebuffer->second.back();

		info.id			= id;
		info.flags		= packet.pCreateInfo->flags;
		info.renderPass	= ResourceID(packet.pCreateInfo->renderPass);
		info.width		= packet.pCreateInfo->width;
		info.height		= packet.pCreateInfo->height;
		info.layers		= packet.pCreateInfo->layers;

		info.imageViews.reserve( packet.pCreateInfo->attachmentCount );

		for (uint i = 0; i < packet.pCreateInfo->attachmentCount; ++i)
		{
			info.imageViews.push_back( ResourceID(packet.pCreateInfo->pAttachments[i]) );
		}

		return true;
	}
	
/*
=================================================
	_ProcessRenderPassUsage
=================================================
*/
	bool RenderPassAnalyzer::_ProcessRenderPassUsage (const TraceRange::Iterator &pos, ResourceID id, EResOp op)
	{
		if ( pos->packet_id == VKTRACE_TPI_VK_vkCreateRenderPass )
			return _OnCreateRenderPass( pos, id );
		
		RenderPassesMap_t::iterator		renderpass;
		CHECK_ERR( _renderPasses.AddResourceUsage( OUT renderpass, pos, id, op ));

		//auto&	info = renderpass->second.back();

		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkCreateFramebuffer :
			case VKTRACE_TPI_VK_vkCreateGraphicsPipelines :
			case VKTRACE_TPI_VK_vkBeginCommandBuffer :	// in VkCommandBufferInheritanceInfo
			case VKTRACE_TPI_VK_vkCmdBeginRenderPass :
			case VKTRACE_TPI_VK_vkCmdNextSubpass :
			case VKTRACE_TPI_VK_vkCmdEndRenderPass :
			case VKTRACE_TPI_VK_vkDestroyRenderPass :
			case VKTRACE_TPI_VK_vkGetRenderAreaGranularity :
				break;

			default :
				ASSERT(false);		// unknown usage
				break;
		}
		return true;
	}
	
/*
=================================================
	_OnCreateRenderPass
=================================================
*/
	bool RenderPassAnalyzer::_OnCreateRenderPass (const TraceRange::Iterator &pos, ResourceID id)
	{
		auto&	packet = pos.Cast< packet_vkCreateRenderPass >();
		CHECK_ERR( ResourceID(*packet.pRenderPass) == id );
		
		RenderPassesMap_t::iterator		renderpass;
		CHECK_ERR( _renderPasses.AddResourceUsage( OUT renderpass, pos, id, EResOp::Construct ));

		auto&	info = renderpass->second.back();

		info.id		= id;
		info.flags	= packet.pCreateInfo->flags;

		info.attachments.assign( packet.pCreateInfo->pAttachments, packet.pCreateInfo->pAttachments + packet.pCreateInfo->attachmentCount );
		info.dependencies.assign( packet.pCreateInfo->pDependencies, packet.pCreateInfo->pDependencies + packet.pCreateInfo->dependencyCount );
		
		info.subpasses.reserve( packet.pCreateInfo->subpassCount );

		for (uint i = 0; i < packet.pCreateInfo->subpassCount; ++i)
		{
			auto&	src = packet.pCreateInfo->pSubpasses[i];
			Subpass	dst;

			dst.flags				= src.flags;
			dst.pipelineBindPoint	= src.pipelineBindPoint;

			if ( src.pColorAttachments )
				dst.colorAttachments.assign( src.pColorAttachments, src.pColorAttachments + src.colorAttachmentCount );

			if ( src.pDepthStencilAttachment )
				dst.depthStencilAttachment = *src.pDepthStencilAttachment;

			if ( src.pResolveAttachments )
				dst.resolveAttachments.assign( src.pResolveAttachments, src.pResolveAttachments + src.colorAttachmentCount );
			
			if ( src.pInputAttachments )
				dst.inputAttachments.assign( src.pInputAttachments, src.pInputAttachments + src.inputAttachmentCount );

			if ( src.pPreserveAttachments )
				dst.preserveAttachments.assign( src.pPreserveAttachments, src.pPreserveAttachments + src.preserveAttachmentCount );

			info.subpasses.push_back( std::move(dst) );
		}
		return true;
	}


}	// VTC
