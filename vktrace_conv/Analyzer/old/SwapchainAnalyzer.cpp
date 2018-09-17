// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Analyzer/old/SwapchainAnalyzer.h"

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
	void SwapchainAnalyzer::AddResourceUsage (const TraceRange::Iterator &pos, EResourceType type, ResourceID id, FrameID, EResOp)
	{
		switch ( type )
		{
			case VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT :	CHECK( _ProcessSwapchainUsage( pos, id ));	break;
			case VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT :		CHECK( _ProcessSemaphoreUsage( pos, id ));	break;
		}
	}
	
/*
=================================================
	_ProcessSwapchainUsage
=================================================
*/
	bool SwapchainAnalyzer::_ProcessSwapchainUsage (const TraceRange::Iterator &pos, ResourceID id)
	{
		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkCreateSwapchainKHR :			CHECK( _OnCreateSwapchain( pos ));			break;
			case VKTRACE_TPI_VK_vkCreateSharedSwapchainsKHR :	CHECK( _OnCreateSharedSwapchains( pos ));	break;
			case VKTRACE_TPI_VK_vkGetSwapchainImagesKHR :		CHECK( _OnGetSwapchainImages( pos ));		break;
			case VKTRACE_TPI_VK_vkAcquireNextImageKHR :			CHECK( _OnAcquireNextImage( pos ));			break;
			case VKTRACE_TPI_VK_vkQueuePresentKHR :				CHECK( _OnQueuePresent( pos ));				break;
		}


		// add bookmark
		{
			auto	iter = _swapchains.find( id );
			CHECK_ERR( iter != _swapchains.end() );		// used unknown swapchain
			
			iter->second.bookmarks.push_back({ pos.GetBookmark(), pos->packet_id });
		}
		return true;
	}
	
/*
=================================================
	_OnCreateSwapchain
=================================================
*/
	bool SwapchainAnalyzer::_OnCreateSwapchain (const TraceRange::Iterator &pos)
	{
		auto&	packet = pos.Cast<packet_vkCreateSwapchainKHR>();
		CHECK_ERR( packet.pCreateInfo );
		ASSERT( packet.pCreateInfo->pNext == null );	// add support if assert triggered

		auto	iter = _swapchains.find( ResourceID(*packet.pSwapchain) );
		CHECK_ERR( iter == _swapchains.end() );

		iter = _swapchains.insert({ ResourceID(*packet.pSwapchain), SwapchainInfo{} }).first;

		iter->second.createInfo = *packet.pCreateInfo;
		return true;
	}
	
/*
=================================================
	_OnCreateSharedSwapchains
=================================================
*/
	bool SwapchainAnalyzer::_OnCreateSharedSwapchains (const TraceRange::Iterator &)
	{
		ASSERT(false);	// TODO
		return true;
	}
	
/*
=================================================
	_OnGetSwapchainImages
=================================================
*/
	bool SwapchainAnalyzer::_OnGetSwapchainImages (const TraceRange::Iterator &pos)
	{
		auto&	packet = pos.Cast<packet_vkGetSwapchainImagesKHR>();
				
		// setup swapchain images
		{
			auto	iter = _swapchains.find( ResourceID(packet.swapchain) );
			CHECK_ERR( iter != _swapchains.end() );	// used unknown swapchain

			if ( iter->second.images.empty() )
			{
				CHECK_ERR( packet.pSwapchainImageCount );
				iter->second.images.resize( *packet.pSwapchainImageCount );
			}
			else
			if ( packet.pSwapchainImageCount )
			{
				CHECK_ERR( iter->second.images.size() == *packet.pSwapchainImageCount );
			}
		}

		// add images
		if ( packet.pSwapchainImageCount and packet.pSwapchainImages )
		{
			for (uint i = 0; i < *packet.pSwapchainImageCount; ++i)
			{
				CHECK_ERR( _AddSwapchainImageUsage( ResourceID(packet.pSwapchainImages[i]), ResourceID(packet.swapchain), i ));
			}
		}
		return true;
	}
	
/*
=================================================
	_OnAcquireNextImage
=================================================
*/
	bool SwapchainAnalyzer::_OnAcquireNextImage (const TraceRange::Iterator &pos)
	{
		auto&	packet = pos.Cast<packet_vkAcquireNextImageKHR>();
				
		auto	iter = _swapchains.find( ResourceID(packet.swapchain) );
		CHECK_ERR( iter != _swapchains.end() );	// used unknown swapchain

		CHECK_ERR( _AddSwapchainSemaphore( iter, pos, ResourceID(packet.semaphore) ));

		CHECK_ERR( *packet.pImageIndex < iter->second.images.size() );
		CHECK_ERR( _AddSwapchainImageUsage( iter->second.images[*packet.pImageIndex], ResourceID(packet.swapchain), *packet.pImageIndex ));

		return true;
	}
	
/*
=================================================
	_OnQueuePresent
=================================================
*/
	bool SwapchainAnalyzer::_OnQueuePresent (const TraceRange::Iterator &pos)
	{
		auto&	packet = pos.Cast<packet_vkQueuePresentKHR>();
		CHECK_ERR( packet.pPresentInfo );
		ASSERT( packet.pPresentInfo->pNext == null );	// add support if assert triggered

		for (uint i = 0; i < packet.pPresentInfo->swapchainCount; ++i)
		{
			auto	iter = _swapchains.find( ResourceID(packet.pPresentInfo->pSwapchains[i]) );
			CHECK_ERR( iter != _swapchains.end() );	// used unknown swapchain

			for (uint j = 0; j < packet.pPresentInfo->waitSemaphoreCount; ++j)
			{
				CHECK_ERR( _AddSwapchainSemaphore( iter, pos, ResourceID(packet.pPresentInfo->pWaitSemaphores[i]) ));
			}

			uint	image_idx = packet.pPresentInfo->pImageIndices[i];

			CHECK_ERR( image_idx < iter->second.images.size() );
			CHECK_ERR( _AddSwapchainImageUsage( iter->second.images[image_idx], iter->first, image_idx ));
		}
		return true;
	}

/*
=================================================
	_ProcessSemaphoreUsage
=================================================
*/
	bool SwapchainAnalyzer::_ProcessSemaphoreUsage (const TraceRange::Iterator &pos, ResourceID id)
	{
		auto	iter = _semaphores.find( id );

		if ( iter == _semaphores.end() )
			return true;

		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkAcquireNextImageKHR :
				iter->second.usedInAcquire = true;
				break;

			case VKTRACE_TPI_VK_vkQueuePresentKHR :
				iter->second.usedInPresent = true;
				break;
		}

		iter->second.bookmarks.push_back({ pos.GetBookmark(), pos->packet_id });
		return true;
	}
	
/*
=================================================
	_AddSwapchainSemaphore
=================================================
*/
	bool SwapchainAnalyzer::_AddSwapchainSemaphore (SwapchainsMap_t::iterator swapchainIter, const TraceRange::Iterator &pos, ResourceID semaphoreId)
	{
		if ( semaphoreId == 0 )
			return true;

		swapchainIter->second.semaphores.insert( semaphoreId );

		auto	iter = _semaphores.insert({ semaphoreId, SemaphoreInfo{} }).first;

		iter->second.bookmarks.push_back({ pos.GetBookmark(), pos->packet_id });
		iter->second.swapchains.insert( swapchainIter->first );

		return true;
	}

/*
=================================================
	_AddSwapchainImageUsage
=================================================
*/
	bool SwapchainAnalyzer::_AddSwapchainImageUsage (ResourceID imageId, ResourceID swapchainId, uint indexInSwapchain)
	{
		auto	iter = _images.find( imageId );

		// create new
		if ( iter == _images.end() )
		{
			iter = _images.insert({ imageId, ImageInfo{} }).first;

			CHECK_ERR( swapchainId != 0 );	// in first usage swapchain must be defined

			auto	swc_iter = _swapchains.find( swapchainId );
			CHECK_ERR( swc_iter != _swapchains.end() );		// swapchain must be added at first

			CHECK( indexInSwapchain < swc_iter->second.images.size() );

			swc_iter->second.images.resize( Max( swc_iter->second.images.size(), indexInSwapchain+1 ) );
			swc_iter->second.images[indexInSwapchain] = imageId;

			iter->second.swapchain			= swapchainId;
			iter->second.indexInSwapchain	= indexInSwapchain;
		}


		CHECK( swapchainId == 0 or iter->second.swapchain == swapchainId );
		CHECK( indexInSwapchain == ~0u or iter->second.indexInSwapchain == indexInSwapchain );

		return true;
	}


}	// VTC
