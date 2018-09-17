// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Analyzer/IAnalyzer.h"

namespace VTC
{

	//
	// Swapchain Analyzer
	//

	class SwapchainAnalyzer final : public IAnalyzer
	{
	// types
	public:
		struct Bookmark
		{
			TraceRange::Bookmark			pos;
			PacketID						packetId;
		};

		struct SwapchainInfo
		{
			VkSwapchainCreateInfoKHR		createInfo;
			Array<ResourceID>				images;
			HashSet<ResourceID>				semaphores;
			Array<Bookmark>					bookmarks;
		};

		struct ImageInfo
		{
			ResourceID						swapchain			= 0;
			uint							indexInSwapchain	= 0;
		};
		
		struct SemaphoreInfo
		{
			HashSet<ResourceID>				swapchains;
			Array<Bookmark>					bookmarks;
			bool							usedInAcquire	= false;
			bool							usedInPresent	= false;
		};

		using SwapchainsMap_t	= HashMap< ResourceID, SwapchainInfo >;
		using ImagesMap_t		= HashMap< ResourceID, ImageInfo >;
		using SemaphoresMap_t	= HashMap< ResourceID, SemaphoreInfo >;


	// variables
	private:
		SwapchainsMap_t		_swapchains;
		SemaphoresMap_t		_semaphores;
		ImagesMap_t			_images;


	// methods
	public:
		SwapchainAnalyzer ();
		
		ND_ SwapchainsMap_t const&		GetSwapchains ()	const	{ return _swapchains; }
		ND_ SemaphoresMap_t const&		GetSemaphores ()	const	{ return _semaphores; }
		ND_ ImagesMap_t const&			GetImages ()		const	{ return _images; }


	// IAnalyzer implementation
	public:
		void PreProcess (const class AppTrace &) override {}

		void Process (const TraceRange::Iterator &) override {}
		
		void PostProcess () override {}

		void AddResourceUsage (const TraceRange::Iterator &, EResourceType, ResourceID, FrameID, EResOp) override;
		
		std::type_index		GetType ()	const override		{ return typeid(*this); }
		
		String				Report ()	const override		{ return "TODO"; }


	private:
		bool _ProcessSwapchainUsage (const TraceRange::Iterator &, ResourceID);
		bool _ProcessSemaphoreUsage (const TraceRange::Iterator &, ResourceID);

		bool _OnCreateSwapchain (const TraceRange::Iterator &);
		bool _OnCreateSharedSwapchains (const TraceRange::Iterator &);
		bool _OnGetSwapchainImages (const TraceRange::Iterator &);
		bool _OnAcquireNextImage (const TraceRange::Iterator &);
		bool _OnQueuePresent (const TraceRange::Iterator &);

		bool _AddSwapchainSemaphore (SwapchainsMap_t::iterator swapchainIter, const TraceRange::Iterator &pos, ResourceID semaphoreId);
		bool _AddSwapchainImageUsage (ResourceID imageId, ResourceID swapchainId = 0, uint indexInSwapchain = ~0u);
	};


}	// VTC
