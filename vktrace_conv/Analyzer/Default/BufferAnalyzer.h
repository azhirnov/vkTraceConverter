// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Analyzer/IAnalyzer.h"
#include "Analyzer/ResourceTracker.h"

namespace VTC
{

	//
	// Buffer Analyzer
	//

	class BufferAnalyzer final : public IAnalyzer
	{
	// types
	public:
		using BufferViewIDs_t	= HashMap< ResourceID, TraceRange::Bookmark >;

		struct BufferInfo
		{
			ResourceID					id				= 0;
			ResourceID					memId			= 0;
			ResourceID					deviceId		= 0;
			VkBufferCreateInfo			createInfo		= {};
			VkBufferUsageFlags			usage			= 0;
			VkAccessFlags				allAccessFlags	= 0;
			VkPipelineStageFlags		allStageFlags	= 0;
			BufferViewIDs_t				bufferViews;
			VkMemoryRequirements		memRequirements	= {};
		};

		using BuffersMap_t		= ResourceTracker< BufferInfo >;
		using BufferInfo_t		= BuffersMap_t::Item_t;


		struct BufferViewInfo
		{
			ResourceID					id			= 0;
			BufferInfo_t *				buffer		= null;
			VkBufferViewCreateInfo		createInfo	= {};
		};

		using BufferViewsMap_t	= ResourceTracker< BufferViewInfo >;
		using BufferViewInfo_t	= BufferViewsMap_t::Item_t;


	// variables
	private:
		BuffersMap_t					_buffers;
		BufferViewsMap_t				_bufferViews;

		class MemoryObjAnalyzer const*	_memoryObjAnalyzer		= null;


	// methods
	public:
		BufferAnalyzer ();


	// IAnalyzer implementation
	public:
		void PreProcess (const class AppTrace &) override;

		void Process (const TraceRange::Iterator &) override;
		
		void PostProcess () override {}

		void AddResourceUsage (const TraceRange::Iterator &, EResourceType, ResourceID, FrameID, EResOp) override;
		
		std::type_index		GetType ()	const override		{ return typeid(*this); }
		
		String				Report ()	const override		{ return "TODO"; }


	private:
		bool _ProcessBufferUsage (const TraceRange::Iterator &, ResourceID, FrameID, EResOp);
		bool _ProcessBufferViewUsage (const TraceRange::Iterator &, ResourceID, FrameID, EResOp);

		bool _OnCreateBuffer (const TraceRange::Iterator &, ResourceID, FrameID);
		bool _OnBindBufferMemory (const TraceRange::Iterator &, BufferInfo_t &);
		bool _OnBindBufferMemory2 (const TraceRange::Iterator &, BufferInfo_t &);
		bool _OnGetBufferMemoryRequirements (const TraceRange::Iterator &, BufferInfo_t &);
		bool _OnGetBufferMemoryRequirements2 (const TraceRange::Iterator &, BufferInfo_t &);

		bool _OnCreateBufferView (const TraceRange::Iterator &, ResourceID, FrameID);

		bool _ProcessBufferMemoryBarriers (TraceRange::Bookmark pos, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask,
										   ArrayView<VkBufferMemoryBarrier> barriers);

		bool _AddBufferUsage (BufferInfo_t &, VkPipelineStageFlags, VkAccessFlags);
	};


}	// VTC
