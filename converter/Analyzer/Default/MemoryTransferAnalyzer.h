// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Analyzer/IAnalyzer.h"
#include "Analyzer/ResourceTracker.h"

namespace VTC
{

	//
	// Memory Transfer Analyzer
	//

	class MemoryTransferAnalyzer final : public IAnalyzer
	{
	// types
	public:
		struct BlockInfo
		{
			VkDeviceSize	memOffset	= 0;	// offset in memory object
			uint64_t		fileOffset	= 0;	// position in file
			uint64_t		dataSize	= 0;
		};

		struct ResDataInfo : BlockInfo
		{
			ResourceID				id			= 0;
			EResourceType			type		= VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT;
			TraceRange::Bookmark	pos;				// bookmark when resource created/updated
			VkDeviceSize			resOffset	= 0;	// offset in image/buffer
		};

		struct MemTransferInfo
		{
			Array<BlockInfo>		blocks;
			Array<ResDataInfo>		resources;
			size_t					hostSyncIndex	= ~0u;	// bookmark index in '_hostSyncBookmarks'
		};

		using MemTransferMap_t		= HashMap< Pair<ResourceID, TraceRange::Bookmark>, MemTransferInfo >;


	// variables
	private:
		MemTransferMap_t					_memTransfer;

		TraceRange const*					_fullTrace			= null;
		uint16_t							_traceFileVersion	= 0;
		Array<TraceRange::Bookmark> 		_hostSyncBookmarks;

		class ImageAnalyzer const*			_imageAnalyzer		= null;
		class BufferAnalyzer const*			_bufferAnalyzer		= null;
		class MemoryObjAnalyzer const*		_memObjAnalyzer		= null;


	// methods
	public:
		MemoryTransferAnalyzer ();
		
		ND_ MemTransferInfo const*	GetTransfer (ResourceID memId, TraceRange::Bookmark pos) const;


	// IAnalyzer implementation
	public:
		void PreProcess (const class AppTrace &) override;

		void Process (const TraceRange::Iterator &) override;
		
		void PostProcess () override;

		void AddResourceUsage (const TraceRange::Iterator &, EResourceType, ResourceID, FrameID, EResOp) override {}

		std::type_index		GetType ()	const override		{ return typeid(*this); }

		String				Report ()	const override		{ return "TODO"; }


	private:
		bool _OnFlushMappedMemoryRanges (const TraceRange::Iterator &);
		bool _OnInvalidateMappedMemoryRanges (const TraceRange::Iterator &);
		// TODO:
		// update buffer
		// push constants

		bool _SearchResourceBlocks ();
	};


}	// VTC
