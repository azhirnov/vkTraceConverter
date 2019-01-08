// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Analyzer/IAnalyzer.h"
#include "Analyzer/ResourceTracker.h"

namespace VTC
{

	//
	// Queue Analyzer
	//

	class QueueAnalyzer final : public IAnalyzer
	{
	// types
	public:
		struct ResourceUsage
		{
			ResourceID						id		= 0;
			TraceRange::Bookmark			first;
			TraceRange::Bookmark			last;
		};

		using ResourceUsageMap_t	= HashMap< ResourceID, ResourceUsage >;
		using ResourceUsageMap2_t	= HashMap< ResourceID, Array<ResourceUsage> >;
		using ResourceBookmarks_t	= HashSet<Pair< ResourceID, TraceRange::Bookmark >>;


		struct QueueInfo
		{
			ResourceID						id				= 0;
			ResourceID						physicalDevice	= 0;
			ResourceID						logicalDevice	= 0;

			VkDeviceQueueCreateFlags		createFlags		= 0;
			float							priority		= 0.0f;
			uint							familyIndex		= UMax;
			uint							queueIndex		= UMax;

			VkQueueFlags					usageFlags		= 0;
			bool							usedForPresent	= false;

			ResourceUsageMap2_t				commandPools;
			ResourceUsageMap2_t				bufferUsage;
			ResourceUsageMap2_t				imageUsage;
		};


		struct CommandBufferState
		{
			ResourceID						commandPool		= 0;
			ResourceUsageMap_t				bufferUsage;
			ResourceUsageMap_t				imageUsage;
			ResourceBookmarks_t				secondaryBuffers;
			VkQueueFlags					queueUsageFlags	= 0;
			bool							oneTimeSubmit	= false;
			bool							isSecondary		= false;
			bool							recording		= false;
		};


		struct CommandBufferInfo
		{
			ResourceID						id				= 0;
			ResourceID						commandPool		= 0;
		};


		using QueuesMap_t			= ResourceTracker< QueueInfo, DefaultBookmark, true >;
		using QueueInfo_t			= QueuesMap_t::Item_t;

		using CmdBufferStates_t		= HashMap< ResourceID, CommandBufferState >;
		using CmdBufferMap_t		= ResourceTracker< CommandBufferInfo, DefaultBookmark, true >;
		using CmdBufferInfo_t		= CmdBufferMap_t::Item_t;


	// variables
	private:
		QueuesMap_t					_queues;
		CmdBufferStates_t			_cmdBufferStates;
		CmdBufferMap_t				_cmdBuffers;
		
		class DeviceAnalyzer const*	_deviceAnalyzer	= null;


	// methods
	public:
		QueueAnalyzer ();

		ND_ QueueInfo_t const*		GetQueueInfo (ResourceID id, TraceRange::Bookmark pos, bool strict = true)			const	{ return _queues.FindIn( id, pos, strict ); }
		ND_ CmdBufferInfo_t const*	GetCommandBufferInfo (ResourceID id, TraceRange::Bookmark pos, bool strict = true)	const	{ return _cmdBuffers.FindIn( id, pos, strict ); }

		ND_ Array<QueueInfo_t const*>  GetDeviceQueues (ResourceID deviceId, TraceRange::Bookmark pos) const;

		void GetCommandPoolQueues (ResourceID id, TraceRange::Bookmark begin, TraceRange::Bookmark end, OUT Array<ResourceID> &queueIDs) const;
		void GetImageQueues (ResourceID id, TraceRange::Bookmark begin, TraceRange::Bookmark end, OUT Array<ResourceID> &queueIDs) const;
		void GetBufferQueues (ResourceID id, TraceRange::Bookmark begin, TraceRange::Bookmark end, OUT Array<ResourceID> &queueIDs) const;


	// IAnalyzer implementation
	public:
		void PreProcess (const class AppTrace &) override;

		void Process (const TraceRange::Iterator &) override {}
		
		void PostProcess () override {}

		void AddResourceUsage (const TraceRange::Iterator &, EResourceType, ResourceID, FrameID, EResOp) override;
		
		std::type_index		GetType ()	const override		{ return typeid(*this); }

		String				Report ()	const override		{ return "TODO"; }


	private:
		bool _ProcessQueueUsage (const TraceRange::Iterator &, ResourceID, EResOp);
		bool _ProcessCommandPoolUsage (const TraceRange::Iterator &, ResourceID, EResOp);
		bool _ProcessCommandBufferUsage (const TraceRange::Iterator &, ResourceID, EResOp);

		bool _OnGetDeviceQueue (const TraceRange::Iterator &, ResourceID);
		
		bool _OnQueueSubmit (const TraceRange::Iterator &, ResourceID, QueueInfo &);
		bool _QueueSubmitCommand (TraceRange::Bookmark, QueueInfo &, ResourceID cmdBufferId);

		bool _OnCmdPipelineBarrier (ArrayView<VkBufferMemoryBarrier>, ArrayView<VkImageMemoryBarrier>,
									ResourceID, TraceRange::Bookmark);
	};


}	// VTC
