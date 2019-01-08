// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Analyzer/Default/SwapchainAnalyzer.h"

namespace VTC
{

/*
=================================================
	constructor
=================================================
*/
	SwapchainAnalyzer::SwapchainAnalyzer ()
	{
	}

/*
=================================================
	AddResourceUsage
=================================================
*/
	void SwapchainAnalyzer::AddResourceUsage (const TraceRange::Iterator &pos, EResourceType type, ResourceID id, FrameID frameId, EResOp op)
	{
		if ( type != VK_OBJECT_TYPE_SWAPCHAIN_KHR )
			return;
		
		if ( pos->packet_id == VKTRACE_TPI_VK_vkCreateSwapchainKHR )
		{
			CHECK( _OnCreateSwapchain( pos, id ));
			return;
		}

		if ( pos->packet_id == VKTRACE_TPI_VK_vkCreateSharedSwapchainsKHR )
		{
			CHECK( _OnCreateSharedSwapchains( pos, id ));
			return;
		}

		SwapchainsMap_t::iterator	swapchain;
		CHECK_ERR( _swapchains.AddResourceUsage( OUT swapchain, pos, id, op ), void());

		auto&	info = swapchain->second.back();

		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkGetSwapchainImagesKHR :	CHECK( _OnGetSwapchainImages( pos, info ));			break;
			case VKTRACE_TPI_VK_vkAcquireNextImageKHR :		CHECK( _OnAcquireNextImage( pos, info, frameId ));	break;
			case VKTRACE_TPI_VK_vkQueuePresentKHR :			CHECK( _OnQueuePresent( pos, info ));				break;
			case VKTRACE_TPI_VK_vkDestroySwapchainKHR :		break;
			default :										ASSERT(false);	break;
		}
	}
	
/*
=================================================
	_OnCreateSwapchain
=================================================
*/
	bool SwapchainAnalyzer::_OnCreateSwapchain (const TraceRange::Iterator &pos, ResourceID id)
	{
		auto&	packet = pos.Cast<packet_vkCreateSwapchainKHR>();
		CHECK_ERR( packet.pCreateInfo );

		if ( id == ResourceID(packet.pCreateInfo->oldSwapchain) )
			return true;

		CHECK_ERR( id == ResourceID(*packet.pSwapchain) );
		ASSERT( packet.pCreateInfo->pNext == null );	// add support if assert triggered

		SwapchainsMap_t::iterator	swapchain;
		CHECK_ERR( _swapchains.AddResourceUsage( OUT swapchain, pos, ResourceID(*packet.pSwapchain), EResOp::Construct ));

		auto&	info = swapchain->second.back();

		info.id			= id;
		info.deviceId	= ResourceID(packet.device);
		info.createInfo = *packet.pCreateInfo;
		return true;
	}
	
/*
=================================================
	_OnCreateSharedSwapchains
=================================================
*/
	bool SwapchainAnalyzer::_OnCreateSharedSwapchains (const TraceRange::Iterator &, ResourceID)
	{
		ASSERT(false);	// TODO
		return true;
	}
	
/*
=================================================
	_OnGetSwapchainImages
=================================================
*/
	bool SwapchainAnalyzer::_OnGetSwapchainImages (const TraceRange::Iterator &pos, SwapchainInfo_t &swapchain)
	{
		auto&	packet = pos.Cast<packet_vkGetSwapchainImagesKHR>();
		CHECK_ERR( swapchain.id == ResourceID(packet.swapchain) );
				
		// setup swapchain images
		{
			if ( swapchain.images.empty() )
			{
				CHECK_ERR( packet.pSwapchainImageCount );
				swapchain.images.resize( *packet.pSwapchainImageCount );
			}
			else
			if ( packet.pSwapchainImageCount )
			{
				CHECK_ERR( swapchain.images.size() == *packet.pSwapchainImageCount );
			}
		}

		// add images
		if ( packet.pSwapchainImageCount and packet.pSwapchainImages )
		{
			for (uint i = 0; i < *packet.pSwapchainImageCount; ++i)
			{
				auto&	dst = swapchain.images[i];

				dst.id		= ResourceID(packet.pSwapchainImages[i]);
				dst.index	= i;
				dst.pos		= pos.GetBookmark();
			}
		}
		return true;
	}
	
/*
=================================================
	_OnAcquireNextImage
=================================================
*/
	bool SwapchainAnalyzer::_OnAcquireNextImage (const TraceRange::Iterator &pos, SwapchainInfo_t &swapchain, FrameID frameId)
	{
		auto&	packet = pos.Cast<packet_vkAcquireNextImageKHR>();
		CHECK_ERR( swapchain.id == ResourceID(packet.swapchain) );
		
		// update semaphore usage
		if ( packet.semaphore )
		{
			auto&	semaphore = swapchain.semaphores.insert({ ResourceID(packet.semaphore), {} }).first->second;
			semaphore.usedInAcquire = true;
		}

		// update image usage
		CHECK_ERR( *packet.pImageIndex < swapchain.images.size() );

		auto&	image = swapchain.images[ *packet.pImageIndex ];

		image.acquired = true;
		image.usedInFrames.push_back( frameId );
		return true;
	}
	
/*
=================================================
	_OnQueuePresent
=================================================
*/
	bool SwapchainAnalyzer::_OnQueuePresent (const TraceRange::Iterator &pos, SwapchainInfo_t &swapchain)
	{
		auto&	packet = pos.Cast<packet_vkQueuePresentKHR>();
		CHECK_ERR( packet.pPresentInfo );
		ASSERT( packet.pPresentInfo->pNext == null );	// add support if assert triggered

		for (uint i = 0; i < packet.pPresentInfo->swapchainCount; ++i)
		{
			auto	iter = _swapchains.find( ResourceID(packet.pPresentInfo->pSwapchains[i]) );
			CHECK_ERR( iter != _swapchains.end() );	// used unknown swapchain
			
			// update semaphore usage
			for (uint j = 0; j < packet.pPresentInfo->waitSemaphoreCount; ++j)
			{
				auto&	semaphore = swapchain.semaphores.insert({ ResourceID(packet.pPresentInfo->pWaitSemaphores[i]), {} }).first->second;
				semaphore.usedInPresent = true;
			}

			// update image usage
			CHECK_ERR( packet.pPresentInfo->pImageIndices[i] < swapchain.images.size() );

			auto&	image = swapchain.images[ packet.pPresentInfo->pImageIndices[i] ];

			CHECK_ERR( image.acquired );
			image.acquired = false;
		}
		return true;
	}

}	// VTC
