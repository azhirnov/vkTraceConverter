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

			case VKTRACE_TPI_VK_vkCreateDevice :
			case VKTRACE_TPI_VK_vkQueueSubmit :
			case VKTRACE_TPI_VK_vkQueueWaitIdle :
			case VKTRACE_TPI_VK_vkDeviceWaitIdle :
			case VKTRACE_TPI_VK_vkWaitForFences :
				_hostSyncBookmarks.push_back( pos.GetBookmark() );
				break;
		}
	}
	
/*
=================================================
	PostProcess
=================================================
*/
	void MemoryTransferAnalyzer::PostProcess ()
	{
		CHECK( _SearchResourceBlocks() );
	}
	
/*
=================================================
	_SearchResourceBlocks
=================================================
*/
	bool MemoryTransferAnalyzer::_SearchResourceBlocks ()
	{
		for (auto& item : _memTransfer)
		{
			auto	pos	= item.first.second;
			auto*	mem	= _memObjAnalyzer->GetMemoryObj( item.first.first, pos );
			CHECK_ERR( mem );

			for (auto& block : item.second.blocks)
			{
				// search in buffer bindings
				for (auto& buffer : mem->bufferBindings)
				{
					auto*	info = _bufferAnalyzer->GetBuffer( buffer.id, buffer.pos );
					CHECK_ERR( info );

					// buffer was destroyed or not yet created
					if ( pos > info->LastBookmark().pos or
						 pos < info->FirstBookmark().pos )
						continue;

					if ( not IsIntersects( buffer.offset, (buffer.offset + info->createInfo.size), block.memOffset, (block.memOffset + block.dataSize) ))
						continue;

					ASSERT( not buffer.aliased );

					ResDataInfo		res_data;
					res_data.memOffset	= Max( buffer.offset, block.memOffset );
					res_data.resOffset	= res_data.memOffset - buffer.offset;
					res_data.dataSize	= Min( buffer.offset + info->createInfo.size, block.memOffset + block.dataSize ) - res_data.memOffset;
					res_data.fileOffset	= block.fileOffset + (block.memOffset - res_data.memOffset);
					res_data.id			= buffer.id;
					res_data.pos		= buffer.pos;
					res_data.type		= VK_OBJECT_TYPE_BUFFER;

					item.second.resources.push_back( std::move(res_data) );
				}
				
				// search in image bindings
				for (auto& image : mem->imageBindings)
				{
					auto*	info = _imageAnalyzer->GetImage( image.id, image.pos );
					CHECK_ERR( info );

					// image was destroyed or not yet created
					if ( pos > info->LastBookmark().pos or
						 pos < info->FirstBookmark().pos )
						continue;

					if ( not IsIntersects( image.offset, (image.offset + image.size), block.memOffset, (block.memOffset + block.dataSize) ))
						continue;
					
					ASSERT( not image.aliased );

					ResDataInfo		res_data;
					res_data.memOffset	= Max( image.offset, block.memOffset );
					res_data.resOffset	= res_data.memOffset - image.offset;
					res_data.dataSize	= Min( image.offset + image.size, block.memOffset + block.dataSize ) - res_data.memOffset;
					res_data.fileOffset	= block.fileOffset + (block.memOffset - res_data.memOffset);
					res_data.id			= image.id;
					res_data.pos		= image.pos;
					res_data.type		= VK_OBJECT_TYPE_IMAGE;

					item.second.resources.push_back( std::move(res_data) );
				}
			}
		}
		return true;
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

			info.hostSyncIndex = _hostSyncBookmarks.size()-1;

			// add memory blocks
			if ( pageguard_speedup and _traceFileVersion >= VKTRACE_TRACE_FILE_VERSION_5 )
			{
				PageGuardChangedBlockInfo const*	changed_info = Cast<PageGuardChangedBlockInfo>( packet.ppData[i] );

				if ( changed_info[0].length == 0 )
					continue;
				
				const void*	src_data	= packet.ppData[i] + (SizeOf<PageGuardChangedBlockInfo> * (changed_info[0].offset+1));
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
