// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Analyzer/Default/MemoryObjAnalyzer.h"
#include "Analyzer/Default/BufferAnalyzer.h"
#include "Analyzer/Default/ImageAnalyzer.h"
#include "Analyzer/AnalyzerUtils.h"
#include "Parser/AppTrace.h"

namespace VTC
{

/*
=================================================
	constructor
=================================================
*/
	MemoryObjAnalyzer::MemoryObjAnalyzer ()
	{
	}
		
/*
=================================================
	PreProcess
=================================================
*/
	void MemoryObjAnalyzer::PreProcess (const AppTrace &appTrace)
	{
		_bufferAnalyzer = appTrace.GetAnalyzer< BufferAnalyzer >();
		_imageAnalyzer	= appTrace.GetAnalyzer< ImageAnalyzer >();

		CHECK( _bufferAnalyzer and _imageAnalyzer );
	}

/*
=================================================
	AddResourceUsage
=================================================
*/
	void MemoryObjAnalyzer::AddResourceUsage (const TraceRange::Iterator &pos, EResourceType type, ResourceID id, FrameID, EResOp op)
	{
		switch ( type )
		{
			case VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT :	CHECK( _ProcessMemoryUsage( pos, id, op ));		break;
		}
	}
	
/*
=================================================
	_ProcessMemoryUsage
=================================================
*/
	bool MemoryObjAnalyzer::_ProcessMemoryUsage (const TraceRange::Iterator &pos, ResourceID id, EResOp op)
	{
		if ( op == EResOp::Construct )
		{
			CHECK_ERR( pos->packet_id == VKTRACE_TPI_VK_vkAllocateMemory );
			return _OnAllocateMemory( pos, id );
		}

		MemoryObjectsMap_t::iterator	mem;
		CHECK_ERR( _memObjects.AddResourceUsage( OUT mem, pos, id, op ));

		auto&	info = mem->second.back();

		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkFlushMappedMemoryRanges :			CHECK_ERR( _OnFlushMappedMemoryRanges( pos, info ));		break;
			case VKTRACE_TPI_VK_vkInvalidateMappedMemoryRanges :	CHECK_ERR( _OnInvalidateMappedMemoryRanges( pos, info ));	break;
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
	_OnFlushMappedMemoryRanges
=================================================
*/
	bool MemoryObjAnalyzer::_OnFlushMappedMemoryRanges (const TraceRange::Iterator &, MemoryObjInfo_t &mem)
	{
		mem.usage |= EMemoryUsage::HostWrite;
		return true;
	}
	
/*
=================================================
	_OnInvalidateMappedMemoryRanges
=================================================
*/
	bool MemoryObjAnalyzer::_OnInvalidateMappedMemoryRanges (const TraceRange::Iterator &, MemoryObjInfo_t &mem)
	{
		mem.usage |= EMemoryUsage::HostRead;
		return true;
	}

/*
=================================================
	_OnMapMemory
=================================================
*/
	bool MemoryObjAnalyzer::_OnMapMemory (const TraceRange::Iterator &, MemoryObjInfo_t &mem)
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
	bool MemoryObjAnalyzer::_OnQueueBindSparse (const TraceRange::Iterator &, MemoryObjInfo_t &)
	{
		// TODO
		return true;
	}
	
/*
=================================================
	_OnAllocateMemory
=================================================
*/
	bool MemoryObjAnalyzer::_OnAllocateMemory (const TraceRange::Iterator &pos, ResourceID id)
	{
		auto&	packet = pos.Cast< packet_vkAllocateMemory >();
		CHECK_ERR( packet.pAllocateInfo );
		CHECK_ERR( ResourceID(*packet.pMemory) == id );

		MemoryObjectsMap_t::iterator	mem;
		CHECK_ERR( _memObjects.AddResourceUsage( OUT mem, pos, id, EResOp::Construct ));

		auto&	info = mem->second.back();

		info.id					= id;
		info.deviceId			= ResourceID(packet.device);
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

						info.usage |= EMemoryUsage::Dedicated;

						if ( packet.image )		info.dedicatedResource = ResourceID(packet.image);	else
						if ( packet.buffer )	info.dedicatedResource = ResourceID(packet.buffer);
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
					case VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_NV :
						// VkImportMemoryWin32HandleInfoNV
						info.usage |= EMemoryUsage::Imported;
						ASSERT( !"TODO" );
						break;

					case VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO :
						// VkExportMemoryAllocateInfo
					case VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO_NV :
						// VkExportMemoryAllocateInfoNV
					case VK_STRUCTURE_TYPE_EXPORT_MEMORY_WIN32_HANDLE_INFO_NV :
						// VkExportMemoryWin32HandleInfoNV
					case VK_STRUCTURE_TYPE_EXPORT_MEMORY_WIN32_HANDLE_INFO_KHR :
						// VkExportMemoryWin32HandleInfoKHR
						info.usage |= EMemoryUsage::Exported;
						ASSERT( !"TODO" );
						break;

					case VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO :
						// VkMemoryAllocateFlagsInfo
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
	bool MemoryObjAnalyzer::_OnBindBufferMemory (const TraceRange::Iterator &pos, MemoryObjInfo_t &mem)
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
	bool MemoryObjAnalyzer::_OnBindImageMemory (const TraceRange::Iterator &pos, MemoryObjInfo_t &mem)
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
	bool MemoryObjAnalyzer::_OnBindBufferMemory2 (const TraceRange::Iterator &pos, MemoryObjInfo_t &mem)
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
	bool MemoryObjAnalyzer::_OnBindImageMemory2 (const TraceRange::Iterator &pos, MemoryObjInfo_t &mem)
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
	bool MemoryObjAnalyzer::_BindBufferMemory (MemoryObjInfo_t &mem, VkBuffer buffer, VkDeviceSize memoryOffset, const TraceRange::Iterator &pos)
	{
		VkDeviceSize	buf_size = VK_WHOLE_SIZE;

		if ( _bufferAnalyzer )
		{
			auto*	info = _bufferAnalyzer->GetBuffer( ResourceID(buffer), pos.GetBookmark() );
			CHECK_ERR( info );

			if ( info->memRequirements.size > 0 )
				buf_size = info->memRequirements.size;

			// TODO: detect buffer parameters that require device local memory
		}

		mem.bufferBindings.push_back({ ResourceID(buffer), memoryOffset, buf_size, pos.GetBookmark() });

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
	bool MemoryObjAnalyzer::_BindImageMemory (MemoryObjInfo_t &mem, VkImage image, VkDeviceSize memoryOffset, const TraceRange::Iterator &pos)
	{
		VkDeviceSize	img_size = VK_WHOLE_SIZE;

		if ( _imageAnalyzer )
		{
			auto*	info = _imageAnalyzer->GetImage( ResourceID(image), pos.GetBookmark() );
			CHECK_ERR( info );

			if ( info->memRequirements.size > 0 )
				img_size = info->memRequirements.size;

			if ( info->createInfo.mipLevels > 1		or
					info->createInfo.arrayLayers > 1	or
					info->createInfo.samples > 1		or
					info->createInfo.tiling != VK_IMAGE_TILING_LINEAR )
			{
				mem.propertyFlags |= VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
			}

			if ( EnumEq( info->createInfo.usage, VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT ) )
				mem.propertyFlags |= VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT;
		}

		mem.imageBindings.push_back({ ResourceID(image), memoryOffset, img_size, pos.GetBookmark() });

		if ( mem.dedicatedResource ) {
			CHECK_ERR( mem.dedicatedResource == ResourceID(image) );
		}
		return true;
	}


}	// VTC
