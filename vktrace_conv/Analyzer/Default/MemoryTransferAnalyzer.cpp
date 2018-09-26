// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Analyzer/Default/MemoryTransferAnalyzer.h"
#include "Analyzer/Default/BufferAnalyzer.h"
#include "Analyzer/Default/ImageAnalyzer.h"
#include "Analyzer/Default/MemoryObjAnalyzer.h"
#include "Analyzer/AnalyzerUtils.h"
#include "Parser/AppTrace.h"

#include "vktrace_pageguard_memorycopy.h"

namespace VTC
{

/*
=================================================
	constructor
=================================================
*/
	MemoryTransferAnalyzer::MemoryTransferAnalyzer ()
	{
	}
		
/*
=================================================
	GetTransfer
=================================================
*/
	MemoryTransferAnalyzer::MemTransferInfo const*  MemoryTransferAnalyzer::GetTransfer (ResourceID memId, TraceRange::Bookmark pos) const
	{
		auto	iter = _memTransfer.find({ memId, pos });

		if ( iter != _memTransfer.end() )
			return &iter->second;

		return null;
	}

/*
=================================================
	PreProcess
=================================================
*/
	void MemoryTransferAnalyzer::PreProcess (const AppTrace &appTrace)
	{
		_traceFileVersion	= appTrace.GetTraceFileHeader().trace_file_version;
		_fullTrace			= &appTrace.FullTrace();

		_imageAnalyzer		= appTrace.GetAnalyzer< ImageAnalyzer >();
		_bufferAnalyzer		= appTrace.GetAnalyzer< BufferAnalyzer >();
		_memObjAnalyzer		= appTrace.GetAnalyzer< MemoryObjAnalyzer >();

		CHECK( _imageAnalyzer and _bufferAnalyzer and _memObjAnalyzer );
	}

/*
=================================================
	Process
=================================================
*/
	void MemoryTransferAnalyzer::Process (const TraceRange::Iterator &pos)
	{
		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkFlushMappedMemoryRanges :			CHECK( _OnFlushMappedMemoryRanges( pos ));		break;
			case VKTRACE_TPI_VK_vkInvalidateMappedMemoryRanges :	CHECK( _OnInvalidateMappedMemoryRanges( pos ));	break;
		}
	}

/*
=================================================
	MergeBlocks
=================================================
*/
	static void MergeBlocks (INOUT MemoryTransferAnalyzer::MemTransferInfo &info,
							 const MemoryTransferAnalyzer::BlockInfo &block)
	{
		if ( not info.blocks.empty() and
			 info.blocks.back().fileOffset + info.blocks.back().dataSize == block.fileOffset and
			 info.blocks.back().memOffset + info.blocks.back().dataSize == block.memOffset )
		{
			ASSERT( info.blocks.back().memOffset + info.blocks.back().dataSize == block.memOffset );

			// merge
			info.blocks.back().dataSize += block.dataSize;
		}
		else
		{
			// append new block
			info.blocks.push_back( block );
		}
	}

/*
=================================================
	_OnFlushMappedMemoryRanges
=================================================
*/
	bool MemoryTransferAnalyzer::_OnFlushMappedMemoryRanges (const TraceRange::Iterator &pos)
	{
		auto&	packet = pos.Cast< packet_vkFlushMappedMemoryRanges >();
		
		// copied from method 'gpuMemory::copyMappingDataPageGuard(const void *)' in 'vkreplay_objmapper_class_defs.h'
#	ifdef USE_PAGEGUARD_SPEEDUP
		const bool	pageguard_speedup = true;
#	else
		const bool	pageguard_speedup = false;
#	endif
		
		for (uint i = 0; i < packet.memoryRangeCount; ++i)
		{
			ASSERT( packet.pMemoryRanges[i].pNext == null );	// add support if triggered

			auto	result	= _memTransfer.insert({ {ResourceID(packet.pMemoryRanges[i].memory), pos.GetBookmark()}, {} });
			auto&	info	= result.first->second;
			auto*	mem_obj	= _memObjAnalyzer->GetMemoryObj( ResourceID(packet.pMemoryRanges[i].memory), pos.GetBookmark() );
			CHECK_ERR( mem_obj );


			// add memory blocks
			if ( pageguard_speedup and _traceFileVersion >= VKTRACE_TRACE_FILE_VERSION_5 )
			{
				PageGuardChangedBlockInfo const*	changed_info = Cast<PageGuardChangedBlockInfo>( packet.ppData[i] );

				if ( changed_info[0].length == 0 )
					continue;
				
				const void*	src_data	= packet.ppData[i] + (BytesU::SizeOf<PageGuardChangedBlockInfo>() * (changed_info[0].offset+1));
				BytesU		curr_offset;

				for (size_t j = 1; j <= changed_info[0].offset; ++j)
				{
					if ( changed_info[j].length == 0 )
						continue;
					
					BlockInfo		block;
					block.memOffset		= changed_info[j].offset;
					block.fileOffset	= _fullTrace->GetPositionInFile( pos, packet.header, src_data + curr_offset );
					block.dataSize		= changed_info[j].length;

					MergeBlocks( INOUT info, block );

					ASSERT( changed_info[j].offset >= packet.pMemoryRanges[i].offset );
					//ASSERT( (changed_info[j].offset + changed_info[j].length) <= (packet.pMemoryRanges[i].offset + packet.pMemoryRanges[i].size) );
					ASSERT( (changed_info[j].offset + changed_info[j].length) <= mem_obj->size );	// TODO: use mapped size

					curr_offset += changed_info[j].length;
				}
			}
			else
			{
				BlockInfo		block;
				block.memOffset		= packet.pMemoryRanges[i].offset;
				block.fileOffset	= _fullTrace->GetPositionInFile( pos, packet.header, packet.ppData + i );
				block.dataSize		= packet.pMemoryRanges[i].size;
				
				MergeBlocks( INOUT info, block );
			}
		}
		return true;
	}
	
/*
=================================================
	_OnInvalidateMappedMemoryRanges
=================================================
*/
	bool MemoryTransferAnalyzer::_OnInvalidateMappedMemoryRanges (const TraceRange::Iterator &)
	{
		// TODO
		return true;
	}
	

}	// VTC
