// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Analyzer/IAnalyzer.h"
#include "Analyzer/ResourceTracker.h"

namespace VTC
{

	//
	// Swapchain Analyzer
	//

	class SwapchainAnalyzer final : public IAnalyzer
	{
	// types
	public:
		struct ImageInfo
		{
			ResourceID					id			= 0;
			uint						index		= 0;
			bool						acquired	= false;
			Array<FrameID>				usedInFrames;
		};

		struct SemaphoreInfo
		{
			bool						usedInAcquire	= false;
			bool						usedInPresent	= false;
		};

		using SemaphoreMap_t	= HashMap< ResourceID, SemaphoreInfo >;


		struct SwapchainInfo
		{
			ResourceID					id			= 0;
			ResourceID					deviceId	= 0;
			VkSwapchainCreateInfoKHR	createInfo	= {};
			Array<ImageInfo>			images;
			SemaphoreMap_t				semaphores;
		};

		using SwapchainsMap_t	= ResourceTracker< SwapchainInfo, DefaultBookmark, true >;
		using SwapchainInfo_t	= SwapchainsMap_t::Item_t;


	// variables
	private:
		SwapchainsMap_t		_swapchains;


	// methods
	public:
		SwapchainAnalyzer ();
		
		ND_ SwapchainInfo_t const*	GetSwapchain (ResourceID id, TraceRange::Bookmark pos)	const	{ return _swapchains.FindIn( id, pos ); }
		ND_ SwapchainsMap_t const&	GetSwapchains ()										const	{ return _swapchains; }


	// IAnalyzer implementation
	public:
		void PreProcess (const class AppTrace &) override {}

		void Process (const TraceRange::Iterator &) override {}
		
		void PostProcess () override {}

		void AddResourceUsage (const TraceRange::Iterator &, EResourceType, ResourceID, FrameID, EResOp) override;
		
		std::type_index		GetType ()	const override		{ return typeid(*this); }
		
		String				Report ()	const override		{ return "TODO"; }


	private:
		bool _OnCreateSwapchain (const TraceRange::Iterator &, ResourceID);
		bool _OnCreateSharedSwapchains (const TraceRange::Iterator &, ResourceID);
		bool _OnGetSwapchainImages (const TraceRange::Iterator &, SwapchainInfo_t &);
		bool _OnAcquireNextImage (const TraceRange::Iterator &, SwapchainInfo_t &, FrameID);
		bool _OnQueuePresent (const TraceRange::Iterator &, SwapchainInfo_t &);
	};


}	// VTC
