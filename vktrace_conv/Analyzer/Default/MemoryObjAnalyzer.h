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

		struct MemInfo
		{
			ResourceID				id					= 0;
			ResourceID				deviceId			= 0;
			uint					memoryTypeIndex		= ~0u;
			VkMemoryPropertyFlags	propertyFlags		= 0;
			VkDeviceSize			size				= 0;
			ResourceID				dedicatedResource	= 0;	// image or buffer
			bool					isExported			= false;
			bool					isImported			= false;
			Array<MemBinding>		imageBindings;
			Array<MemBinding>		bufferBindings;
		};

		using MemoryObjectsMap_t	= ResourceTracker< MemInfo >;
		using MemoryInfo_t			= MemoryObjectsMap_t::Item_t;


	// variables
	private:
		MemoryObjectsMap_t				_memObjects;

		class BufferAnalyzer const*		_bufferAnalyzer		= null;
		class ImageAnalyzer const*		_imageAnalyzer		= null;


	// methods
	public:
		MemoryObjAnalyzer ();
		


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
		
		bool _OnQueueBindSparse (const TraceRange::Iterator &, MemoryInfo_t &);
		bool _OnAllocateMemory (const TraceRange::Iterator &, ResourceID);
		bool _OnMapMemory (const TraceRange::Iterator &, MemoryInfo_t &);
		bool _OnBindBufferMemory (const TraceRange::Iterator &, MemoryInfo_t &);
		bool _OnBindImageMemory (const TraceRange::Iterator &, MemoryInfo_t &);
		bool _OnBindBufferMemory2 (const TraceRange::Iterator &, MemoryInfo_t &);
		bool _OnBindImageMemory2 (const TraceRange::Iterator &, MemoryInfo_t &);
		bool _BindBufferMemory (MemoryInfo_t &mem, VkBuffer buffer, VkDeviceSize memoryOffset, const TraceRange::Iterator &pos);
		bool _BindImageMemory (MemoryInfo_t &mem, VkImage image, VkDeviceSize memoryOffset, const TraceRange::Iterator &pos);
	};


}	// VTC
