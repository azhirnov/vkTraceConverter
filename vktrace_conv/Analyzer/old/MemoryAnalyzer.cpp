// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Analyzer/old/MemoryAnalyzer.h"
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
	MemoryAnalyzer::MemoryAnalyzer () :
		_fullTrace{ null },
		_traceFileVersion{ 0 }
	{
	}
		
/*
=================================================
	PreProcess
=================================================
*/
	void MemoryAnalyzer::PreProcess (const class AppTrace &trace)
	{
		_traceFileVersion	= trace.GetTraceFileHeader().trace_file_version;
		_fullTrace			= &trace.FullTrace();
	}

/*
=================================================
	Process
=================================================
*/
	void MemoryAnalyzer::Process (const TraceRange::Iterator &pos)
	{
		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkCmdCopyImageToBuffer :	break;	// may be usefull if copied compressed data
			case VKTRACE_TPI_VK_vkCmdCopyBufferToImage :	break;
			//case VKTRACE_TPI_VK_vkFlushMappedMemoryRanges :			CHECK( _OnFlushMappedMemoryRanges( pos ));		break;
			//case VKTRACE_TPI_VK_vkInvalidateMappedMemoryRanges :	CHECK( _OnInvalidateMappedMemoryRanges( pos ));	break;
		}
	}
	
/*
=================================================
	MergeBlocks
=================================================
*
	static void MergeBlocks (INOUT MemoryAnalyzer::MemTransferInfo &info, const MemoryAnalyzer::BlockInfo &block)
	{
		if ( not info.blocks.empty() and
			 info.blocks.back().offset + info.blocks.back().size == block.offset )
		{
			// merge
			info.blocks.back().size += block.size;
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
*
	bool MemoryAnalyzer::_OnFlushMappedMemoryRanges (const TraceRange::Iterator &pos)
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


			// add memory blocks
			if ( pageguard_speedup and _traceFileVersion >= VKTRACE_TRACE_FILE_VERSION_5 )
			{
				PageGuardChangedBlockInfo const*	changed_info = Cast<PageGuardChangedBlockInfo>( packet.ppData[i] );

				if ( changed_info[0].length == 0 )
					continue;
				
				const void*	src_data	= packet.ppData[i] + (BytesU::SizeOf<PageGuardChangedBlockInfo>() * (changed_info[0].offset+1));
				BytesU		curr_offset;

				for (size_t j = 0; j < changed_info[0].offset; ++j)
				{
					if ( changed_info[j+1].length == 0 )
						continue;
							
					BlockInfo	block{ _fullTrace->GetPositionInFile( pos, packet.header, src_data + curr_offset ), changed_info[j+1].length };

					MergeBlocks( INOUT info, block );

					CHECK_ERR( changed_info[j+1].offset >= packet.pMemoryRanges[i].offset );
					CHECK_ERR( (changed_info[j+1].offset + changed_info[j+1].length) <= (packet.pMemoryRanges[i].offset + packet.pMemoryRanges[i].size) );

					curr_offset += changed_info[j+1].length;
				}
			}
			else
			{
				BlockInfo	block{ _fullTrace->GetPositionInFile( pos, packet.header, packet.ppData + i ), packet.pMemoryRanges[i].size };
				
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
	bool MemoryAnalyzer::_OnInvalidateMappedMemoryRanges (const TraceRange::Iterator &)
	{
#	if 1

#	else
		// TODO: test loaded data with current memory
#	endif
		return true;
	}
	
/*
=================================================
	AddResourceUsage
=================================================
*/
	void MemoryAnalyzer::AddResourceUsage (const TraceRange::Iterator &pos, EResourceType type, ResourceID id, FrameID, EResOp op)
	{
		switch ( type )
		{
			case VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT :	CHECK( _ProcessMemoryUsage( pos, id, op ));		break;
			//case VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT :			CHECK( _ProcessImageUsage( pos, id ));		break;
			//case VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT :			CHECK( _ProcessBufferUsage( pos, id ));		break;
		}
	}
	
/*
=================================================
	_ProcessMemoryUsage
=================================================
*/
	bool MemoryAnalyzer::_ProcessMemoryUsage (const TraceRange::Iterator &pos, ResourceID id, EResOp op)
	{
		if ( op == EResOp::Construct )
		{
			CHECK_ERR( pos->packet_id == VKTRACE_TPI_VK_vkAllocateMemory );
			return _OnAllocateMemory( pos, id );
		}

		MemoryObjectsMap_t::iterator	mem;
		CHECK_ERR( _memObjects.AddResourceUsage( OUT mem, pos, id, FrameID(0), op ));

		auto&	info = mem->second.back();

		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkFlushMappedMemoryRanges :			break;
			case VKTRACE_TPI_VK_vkInvalidateMappedMemoryRanges :	break;
			case VKTRACE_TPI_VK_vkQueueBindSparse :					CHECK_ERR( _OnQueueBindSparse( pos, info ));				break;
			case VKTRACE_TPI_VK_vkFreeMemory :						break;
			case VKTRACE_TPI_VK_vkMapMemory :						CHECK_ERR( _OnMapMemory( pos, info ));						break;
			case VKTRACE_TPI_VK_vkUnmapMemory :						break;
			case VKTRACE_TPI_VK_vkGetDeviceMemoryCommitment :		break;
			case VKTRACE_TPI_VK_vkBindBufferMemory :				CHECK_ERR( _OnBindBufferMemory( pos, info ));				break;
			case VKTRACE_TPI_VK_vkBindImageMemory :					CHECK_ERR( _OnBindImageMemory( pos, info ));				break;
			case VKTRACE_TPI_VK_vkBindBufferMemory2 :
			case VKTRACE_TPI_VK_vkBindBufferMemory2KHR :			CHECK_ERR( _OnBindBufferMemory2( pos, info ));				break;
			case VKTRACE_TPI_VK_vkBindImageMemory2 :
			case VKTRACE_TPI_VK_vkBindImageMemory2KHR :				CHECK_ERR( _OnBindImageMemory2( pos, info ));				break;
			default :												ASSERT(!"unknown packet"); break;
		}
		return true;
	}
	
/*
=================================================
	_OnMapMemory
=================================================
*/
	bool MemoryAnalyzer::_OnMapMemory (const TraceRange::Iterator &, MemoryInfo_t &mem)
	{
		if ( not EnumEq( mem.propertyFlags, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT ) )
		{
			// coherent is not needed becouse vktrace generate flush commands
			//mem.propertyFlags |= VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

			mem.propertyFlags |= VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
		}
		return true;
	}

/*
=================================================
	_OnQueueBindSparse
=================================================
*/
	bool MemoryAnalyzer::_OnQueueBindSparse (const TraceRange::Iterator &, MemoryInfo_t &)
	{
		// TODO
		return true;
	}
	
/*
=================================================
	_OnAllocateMemory
=================================================
*/
	bool MemoryAnalyzer::_OnAllocateMemory (const TraceRange::Iterator &pos, ResourceID id)
	{
		auto&	packet = pos.Cast< packet_vkAllocateMemory >();
		CHECK_ERR( packet.pAllocateInfo );
		CHECK_ERR( ResourceID(*packet.pMemory) == id );

		MemoryObjectsMap_t::iterator	mem;
		CHECK_ERR( _memObjects.AddResourceUsage( OUT mem, pos, id, FrameID(0), EResOp::Construct ));

		auto&	info = mem->second.back();

		info.id					= id;
		info.size				= packet.pAllocateInfo->allocationSize;
		info.memoryTypeIndex	= packet.pAllocateInfo->memoryTypeIndex;

		ForEachNextStruct( packet.pAllocateInfo->pNext,
			[&info] (const VkBaseInStructure *st) -> bool
			{
				switch ( st->sType )
				{
					case VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO :
					case VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_MEMORY_ALLOCATE_INFO_NV :
					{
						STATIC_ASSERT( sizeof(VkDedicatedAllocationMemoryAllocateInfoNV) == sizeof(VkMemoryDedicatedAllocateInfo) );

						auto&	packet = *BitCast<VkMemoryDedicatedAllocateInfo const*>( st );
						CHECK_ERR( (not packet.image) != (not packet.buffer) );

						if ( packet.image )
							info.dedicatedResource = ResourceID(packet.image);
						else if ( packet.buffer )
							info.dedicatedResource = ResourceID(packet.buffer);
						break;
					}

					case VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_KHR :
						// VkImportMemoryWin32HandleInfoKHR
					case VK_STRUCTURE_TYPE_IMPORT_MEMORY_FD_INFO_KHR :
						// VkImportMemoryFdInfoKHR
					case VK_STRUCTURE_TYPE_IMPORT_MEMORY_HOST_POINTER_INFO_EXT :
						// VkImportMemoryHostPointerInfoEXT
					case VK_STRUCTURE_TYPE_IMPORT_ANDROID_HARDWARE_BUFFER_INFO_ANDROID :
						// VkImportAndroidHardwareBufferInfoANDROID
					case VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO :
						// VkExportMemoryAllocateInfo
					case VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO_NV :
						// VkExportMemoryAllocateInfoNV
					case VK_STRUCTURE_TYPE_EXPORT_MEMORY_WIN32_HANDLE_INFO_NV :
						// VkExportMemoryWin32HandleInfoNV
					case VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_NV :
						// VkImportMemoryWin32HandleInfoNV
					case VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO :
						// VkMemoryAllocateFlagsInfo
					case VK_STRUCTURE_TYPE_EXPORT_MEMORY_WIN32_HANDLE_INFO_KHR :
						// VkExportMemoryWin32HandleInfoKHR
					default :
						ASSERT( !"TODO" );
						break;
				}
				return true;
			});

		return true;
	}
	
/*
=================================================
	_OnBindBufferMemory
=================================================
*/
	bool MemoryAnalyzer::_OnBindBufferMemory (const TraceRange::Iterator &pos, MemoryInfo_t &mem)
	{
		auto&	packet = pos.Cast< packet_vkBindBufferMemory >();
		CHECK_ERR( ResourceID(packet.memory) == mem.id );

		CHECK_ERR( _BindBufferMemory( mem, packet.buffer, packet.memoryOffset, pos ));
		return true;
	}
	
/*
=================================================
	_OnBindImageMemory
=================================================
*/
	bool MemoryAnalyzer::_OnBindImageMemory (const TraceRange::Iterator &pos, MemoryInfo_t &mem)
	{
		auto&	packet = pos.Cast< packet_vkBindImageMemory >();
		CHECK_ERR( ResourceID(packet.memory) == mem.id );
		
		CHECK_ERR( _BindImageMemory( mem, packet.image, packet.memoryOffset, pos ));
		return true;
	}
	
/*
=================================================
	_OnBindBufferMemory2
=================================================
*/
	bool MemoryAnalyzer::_OnBindBufferMemory2 (const TraceRange::Iterator &pos, MemoryInfo_t &mem)
	{
		STATIC_ASSERT( sizeof(packet_vkBindBufferMemory2) == sizeof(packet_vkBindBufferMemory2KHR) );

		auto&	packet = pos.Cast< packet_vkBindBufferMemory2 >();
		CHECK_ERR( packet.pBindInfos );

		for (uint i = 0; i < packet.bindInfoCount; ++i)
		{
			auto&	bind = packet.pBindInfos[i];

			if ( ResourceID(bind.memory) != mem.id )
				continue;

			ASSERT( bind.pNext == null );	// add support if triggered
			
			CHECK_ERR( _BindBufferMemory( mem, bind.buffer, bind.memoryOffset, pos ));
		}

		RETURN_ERR( "mem object is not processed!" );
	}
	
/*
=================================================
	_OnBindImageMemory2
=================================================
*/
	bool MemoryAnalyzer::_OnBindImageMemory2 (const TraceRange::Iterator &pos, MemoryInfo_t &mem)
	{
		STATIC_ASSERT( sizeof(packet_vkBindImageMemory2) == sizeof(packet_vkBindImageMemory2KHR) );

		auto&	packet = pos.Cast< packet_vkBindImageMemory2 >();
		CHECK_ERR( packet.pBindInfos );

		for (uint i = 0; i < packet.bindInfoCount; ++i)
		{
			auto&	bind = packet.pBindInfos[i];

			if ( ResourceID(bind.memory) != mem.id )
				continue;

			ASSERT( bind.pNext == null );	// add support if triggered
			
			CHECK_ERR( _BindImageMemory( mem, bind.image, bind.memoryOffset, pos ));
			return true;
		}

		RETURN_ERR( "mem object is not processed!" );
	}
	
/*
=================================================
	_BindBufferMemory
=================================================
*/
	bool MemoryAnalyzer::_BindBufferMemory (MemoryInfo_t &mem, VkBuffer buffer, VkDeviceSize memoryOffset, const TraceRange::Iterator &pos)
	{
		mem.bufferBindings.push_back({ ResourceID(buffer), memoryOffset, 0, pos.GetBookmark() });	// TODO

		if ( mem.dedicatedResource ) {
			CHECK_ERR( mem.dedicatedResource == ResourceID(buffer) );
		}
		return true;
	}
	
/*
=================================================
	_BindImageMemory
=================================================
*/
	bool MemoryAnalyzer::_BindImageMemory (MemoryInfo_t &mem, VkImage image, VkDeviceSize memoryOffset, const TraceRange::Iterator &pos)
	{
		mem.imageBindings.push_back({ ResourceID(image), memoryOffset, 0, pos.GetBookmark() });	// TODO

		if ( mem.dedicatedResource ) {
			CHECK_ERR( mem.dedicatedResource == ResourceID(image) );
		}
		return true;
	}

/*
=================================================
	_ProcessImageUsage
=================================================
*/
	bool MemoryAnalyzer::_ProcessImageUsage (const TraceRange::Iterator &pos, ResourceID id)
	{
		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkCreateImage :								break;
			case VKTRACE_TPI_VK_vkCreateImageView :							break;
			case VKTRACE_TPI_VK_vkDestroyImage :							break;
			case VKTRACE_TPI_VK_vkGetImageSubresourceLayout :				break;

			case VKTRACE_TPI_VK_vkGetImageMemoryRequirements :				break;
			case VKTRACE_TPI_VK_vkGetImageMemoryRequirements2 :				break;
			case VKTRACE_TPI_VK_vkGetImageMemoryRequirements2KHR :			break;

			case VKTRACE_TPI_VK_vkGetImageSparseMemoryRequirements :		break;
			case VKTRACE_TPI_VK_vkGetImageSparseMemoryRequirements2 :		break;
			case VKTRACE_TPI_VK_vkGetImageSparseMemoryRequirements2KHR :	break;
		}
		return true;
	}
	
/*
=================================================
	_ProcessBufferUsage
=================================================
*/
	bool MemoryAnalyzer::_ProcessBufferUsage (const TraceRange::Iterator &pos, ResourceID id)
	{
		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkCreateBuffer :					break;
			case VKTRACE_TPI_VK_vkDestroyBuffer :					break;
			case VKTRACE_TPI_VK_vkCreateBufferView :				break;

			case VKTRACE_TPI_VK_vkGetBufferMemoryRequirements :		break;
			case VKTRACE_TPI_VK_vkGetBufferMemoryRequirements2 :	break;
			case VKTRACE_TPI_VK_vkGetBufferMemoryRequirements2KHR :	break;
		}
		return true;
	}


}	// VTC
