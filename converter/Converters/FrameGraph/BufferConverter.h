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
			VkBuffer				handle		= VK_NULL_HANDLE;
			uint					id			= ~0u;
			FG::BufferDesc			desc;
			FG::MemoryDesc			mem;
			TraceRange::Bookmark	startPos;
			bool					memBinded	= false;
		};

		using PendingBuffers_t	= Array< PendingBuffer >;
		using IndexArray_t		= Array< uint >;


	// variables
	private:
		FrameGraphConverter &	_fgConv;

		PendingBuffers_t		_pendingBuffers;
		IndexArray_t			_readyToDelete;
		IndexArray_t			_freeIndices;

		Array<RawBufferID>		_remapping;

		uint					_bufferCounter	= 0;


	// methods
	public:
		explicit BufferConverter (FrameGraphConverter &fgConv) : _fgConv{fgConv} {}
		
		bool OnBeginFrame (TraceRange::Bookmark, FrameID, TracePacker &packer);
		bool OnEndFrame (TracePacker &packer);

		bool CreateBuffer (const TraceRange::Iterator &);
		bool DestroyBuffer (const TraceRange::Iterator &);
		bool BindMemory (const TraceRange::Iterator &, INOUT TracePacker &);
		bool BindMemory2 (const TraceRange::Iterator &, INOUT TracePacker &);

		ND_ uint			GetBufferCount ()		const	{ return _bufferCounter; }

		ND_ RawBufferID		Remap (ResourceID id, TraceRange::Bookmark)		const;
		ND_ RawBufferID		Remap (VkBuffer id, TraceRange::Bookmark pos)	const	{ return Remap( ResourceID(id), pos ); }

	private:
		bool _UpdateBuffer (ResourceID, TraceRange::Bookmark, TraceRange::Bookmark, FrameID, INOUT TracePacker &);
	};


}	// VTC
