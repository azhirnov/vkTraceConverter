// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Converters/FrameGraph/FrameGraphConverter.h"
#include "framegraph/Public/MemoryDesc.h"
#include "framegraph/Public/BufferDesc.h"

namespace VTC
{

	//
	// Buffer Converter
	//

	class FrameGraphConverter::BufferConverter
	{
	// types
	private:
		struct PendingBuffer
		{
			uint64_t				uid			= UMax;
			uint					id			= UMax;
			FG::BufferDesc			desc;
			FG::MemoryDesc			mem;
			bool					memBinded	= false;
		};

		struct HostAccessibleBuffer
		{
			BufferAnalyzer::BufferInfo_t const*			buffer		= null;
			MemoryObjAnalyzer::MemoryObjInfo_t const*	memory		= null;
			TraceRange::Bookmark						lastPos;
		};

		using PendingBuffers_t	= Array< PendingBuffer >;
		using IndexArray_t		= Array< uint >;
		using HosteBuffers_t	= Array< HostAccessibleBuffer >;
		using EMemoryUsage		= MemoryObjAnalyzer::EMemoryUsage;


	// variables
	private:
		FrameGraphConverter &	_fgConv;

		PendingBuffers_t		_pendingBuffers;
		IndexArray_t			_readyToDelete;
		IndexArray_t			_freeIndices;

		Array<RawBufferID>		_remapping;

		HosteBuffers_t			_hostBuffers;

		uint					_bufferCounter	= 0;


	// methods
	public:
		explicit BufferConverter (FrameGraphConverter &fgConv) : _fgConv{fgConv} {}
		
		bool OnBeginFrame (TraceRange::Bookmark, FrameID, TracePacker &packer);
		bool OnEndFrame (TracePacker &packer);

		bool CreateBuffer (const TraceRange::Iterator &);
		bool DestroyBuffer (const TraceRange::Iterator &);
		bool BindMemory (const TraceRange::Iterator &);
		bool BindMemory2 (const TraceRange::Iterator &);

		ND_ uint			GetBufferCount ()		const	{ return _bufferCounter; }

		ND_ RawBufferID		Remap (ResourceID id, TraceRange::Bookmark)		const;
		ND_ RawBufferID		Remap (VkBuffer id, TraceRange::Bookmark pos)	const	{ return Remap( ResourceID(id), pos ); }


	private:
		bool _AddHostBuffer (VkBuffer buf, MemoryObjAnalyzer::MemoryObjInfo_t const* mem, TraceRange::Bookmark pos);
		bool _UpdateBuffer (const HostAccessibleBuffer &, TraceRange::Bookmark, FrameID, INOUT TracePacker &);
	};


}	// VTC
