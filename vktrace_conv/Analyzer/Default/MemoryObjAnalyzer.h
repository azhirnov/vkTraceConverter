// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Analyzer/IAnalyzer.h"
#include "Analyzer/ResourceTracker.h"

namespace VTC
{

	//
	// Memory Objects Analyzer
	//

	class MemoryObjAnalyzer final : public IAnalyzer
	{
	// types
	public:
		struct MemBinding
		{
			ResourceID				id		= 0;
			VkDeviceSize			offset	= 0;
			VkDeviceSize			size	= 0;
			TraceRange::Bookmark	pos;
		};

		enum class EMemoryUsage
		{
			None			= 0,
			HostRead		= 1 << 0,
			HostWrite		= 1 << 1,
			Dedicated		= 1 << 2,
			Exported		= 1 << 3,
			Imported		= 1 << 4,
			_Last,
		};

		struct MemInfo
		{
			ResourceID				id					= 0;
			ResourceID				deviceId			= 0;
			uint					memoryTypeIndex		= ~0u;
			VkMemoryPropertyFlags	propertyFlags		= 0;
			VkDeviceSize			size				= 0;
			ResourceID				dedicatedResource	= 0;	// image or buffer
			EMemoryUsage			usage				= EMemoryUsage::None;
			Array<MemBinding>		imageBindings;
			Array<MemBinding>		bufferBindings;
		};

		using MemoryObjectsMap_t	= ResourceTracker< MemInfo, DefaultBookmark, true >;
		using MemoryObjInfo_t		= MemoryObjectsMap_t::Item_t;


	// variables
	private:
		MemoryObjectsMap_t				_memObjects;

		class BufferAnalyzer const*		_bufferAnalyzer		= null;
		class ImageAnalyzer const*		_imageAnalyzer		= null;


	// methods
	public:
		MemoryObjAnalyzer ();
		
		ND_ MemoryObjInfo_t const*	GetMemoryObj (ResourceID id, TraceRange::Bookmark pos) const	{ return _memObjects.FindIn( id, pos ); }


	// IAnalyzer implementation
	public:
		void PreProcess (const class AppTrace &) override;

		void Process (const TraceRange::Iterator &) override {}
		
		void PostProcess () override {}

		void AddResourceUsage (const TraceRange::Iterator &, EResourceType, ResourceID, FrameID, EResOp) override;

		std::type_index		GetType ()	const override		{ return typeid(*this); }

		String				Report ()	const override		{ return "TODO"; }


	private:
		bool _ProcessMemoryUsage (const TraceRange::Iterator &, ResourceID, EResOp);
		
		bool _OnQueueBindSparse (const TraceRange::Iterator &, MemoryObjInfo_t &);
		bool _OnAllocateMemory (const TraceRange::Iterator &, ResourceID);
		bool _OnMapMemory (const TraceRange::Iterator &, MemoryObjInfo_t &);
		bool _OnBindBufferMemory (const TraceRange::Iterator &, MemoryObjInfo_t &);
		bool _OnBindImageMemory (const TraceRange::Iterator &, MemoryObjInfo_t &);
		bool _OnBindBufferMemory2 (const TraceRange::Iterator &, MemoryObjInfo_t &);
		bool _OnBindImageMemory2 (const TraceRange::Iterator &, MemoryObjInfo_t &);
		bool _BindBufferMemory (MemoryObjInfo_t &mem, VkBuffer buffer, VkDeviceSize memoryOffset, const TraceRange::Iterator &pos);
		bool _BindImageMemory (MemoryObjInfo_t &mem, VkImage image, VkDeviceSize memoryOffset, const TraceRange::Iterator &pos);
		bool _OnFlushMappedMemoryRanges (const TraceRange::Iterator &, MemoryObjInfo_t &);
		bool _OnInvalidateMappedMemoryRanges (const TraceRange::Iterator &, MemoryObjInfo_t &);
	};


	FG_BIT_OPERATORS( MemoryObjAnalyzer::EMemoryUsage );


}	// VTC
