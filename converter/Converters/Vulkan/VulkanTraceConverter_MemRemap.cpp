// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Converters/Vulkan/VulkanTraceConverter.h"
#include "extensions/vulkan_loader/VulkanCheckError.h"
#include "Converters/Utils/TracePacker.h"

#undef  NOMINMAX
#define VMA_RECORDING_ENABLED		0
#define VMA_DEDICATED_ALLOCATION	1
#include "external/VulkanMemoryAllocator/src/vk_mem_alloc.h"


namespace VTC
{
	using VPacker = TracePacker;
#	include "Generated/VulkanTraceStructPacker.h"

/*
=================================================
	_OnBindBufferMemory
=================================================
*/
	bool VulkanTraceConverter::_OnBindBufferMemory (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		if ( _config.remapMemory )
			return _RemapBufferMemory( pos, INOUT packer );
		else
			return _ConvertVkFunction( pos, INOUT packer );
	}
	
/*
=================================================
	_OnBindImageMemory
=================================================
*/
	bool VulkanTraceConverter::_OnBindImageMemory (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		if ( _config.remapMemory )
			return _RemapImageMemory( pos, INOUT packer );
		else
			return _ConvertVkFunction( pos, INOUT packer );
	}
	
/*
=================================================
	_OnBindBufferMemory2
=================================================
*/
	bool VulkanTraceConverter::_OnBindBufferMemory2 (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		if ( _config.remapMemory )
			return _RemapBufferMemory2( pos, INOUT packer );
		else
			return _ConvertVkFunction( pos, INOUT packer );
	}
	
/*
=================================================
	_OnBindImageMemory2
=================================================
*/
	bool VulkanTraceConverter::_OnBindImageMemory2 (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		if ( _config.remapMemory )
			return _RemapImageMemory2( pos, INOUT packer );
		else
			return _ConvertVkFunction( pos, INOUT packer );
	}
	
/*
=================================================
	_OnAllocateMemory
=================================================
*/
	bool VulkanTraceConverter::_OnAllocateMemory (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		if ( _config.remapMemory )
			return true;
		else
			return _ConvertVkFunction( pos, INOUT packer );
	}
	
/*
=================================================
	_OnFreeMemory
=================================================
*/
	bool VulkanTraceConverter::_OnFreeMemory (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		if ( _config.remapMemory )
			return true;
		else
			return _ConvertVkFunction( pos, INOUT packer );
	}
	
/*
=================================================
	_OnMapMemory
=================================================
*/
	bool VulkanTraceConverter::_OnMapMemory (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		if ( _config.remapMemory )
			return true;
		else
			return _OverrideMapMemory( pos, INOUT packer );
	}
	
/*
=================================================
	_OnUnmapMemory
=================================================
*/
	bool VulkanTraceConverter::_OnUnmapMemory (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		if ( _config.remapMemory )
			return true;
		else
			return _OverrideUnmapMemory( pos, INOUT packer );
	}
	
/*
=================================================
	_OnFlushMappedMemoryRanges
=================================================
*/
	bool VulkanTraceConverter::_OnFlushMappedMemoryRanges (const TraceRange::Iterator &pos, FrameID frameId, INOUT TracePacker &packer)
	{
		if ( _config.remapMemory )
			return _RemapFlushMemoryRanges( pos, frameId, INOUT packer );
		else
			return _OverrideFlushMappedMemoryRanges( pos, frameId, INOUT packer );
	}
	
/*
=================================================
	_OnDestroyImage
=================================================
*/
	bool VulkanTraceConverter::_OnDestroyImage (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		if ( _config.remapMemory )
			return _FreeImageMemory( pos, INOUT packer );
		else
			return _ConvertVkFunction( pos, INOUT packer );
	}
	
/*
=================================================
	_OnDestroyBuffer
=================================================
*/
	bool VulkanTraceConverter::_OnDestroyBuffer (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		if ( _config.remapMemory )
			return _FreeBufferMemory( pos, INOUT packer );
		else
			return _ConvertVkFunction( pos, INOUT packer );
	}
//-----------------------------------------------------------------------------

	
/*
=================================================
	_OverrideMapMemory
=================================================
*/
	bool VulkanTraceConverter::_OverrideMapMemory (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		auto&	packet = pos.Cast< packet_vkMapMemory >();
		VK_CHECK( packet.result );
		
		packer.Begin( EPacketID::VMapMemory );
		packer << packet.device;
		packer << packet.memory;
		packer << packet.offset;
		packer << packet.size;
		packer << packet.flags;
		packer.End( EPacketID::VMapMemory );
		return true;
	}
	
/*
=================================================
	_OverrideUnmapMemory
=================================================
*/
	bool VulkanTraceConverter::_OverrideUnmapMemory (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		auto&	packet = pos.Cast< packet_vkUnmapMemory >();
		
		packer.Begin( EPacketID::VUnmapMemory );
		packer << packet.device;
		packer << packet.memory;
		packer.End( EPacketID::VUnmapMemory );
		return true;
	}
	
/*
=================================================
	_OverrideFlushMappedMemoryRanges
=================================================
*/
	bool VulkanTraceConverter::_OverrideFlushMappedMemoryRanges (const TraceRange::Iterator &pos, FrameID frameId, INOUT TracePacker &packer)
	{
		auto&	packet = pos.Cast< packet_vkFlushMappedMemoryRanges >();
		VK_CHECK( packet.result );
		CHECK_ERR( packet.memoryRangeCount > 0 and packet.pMemoryRanges );
		
		for (uint i = 0; i < packet.memoryRangeCount; ++i)
		{
			auto	mem_id		= packet.pMemoryRanges[i].memory;
			auto*	transfer	= _memTransferAnalyzer->GetTransfer( ResourceID(mem_id), pos.GetBookmark() );
			CHECK_ERR( transfer );
			
			for (auto& block : transfer->blocks)
			{
				DataID	data_id = _RequestData( block.fileOffset, block.dataSize, frameId );
				CHECK_ERR( data_id != ~DataID(0) );

				packer.Begin( EPacketID::VLoadDataToMappedMemory );
				packer << mem_id;
				packer << data_id;
				packer << block.memOffset;
				packer << block.dataSize;
				packer.End( EPacketID::VLoadDataToMappedMemory );
			}
		}

		packer.Begin( EPacketID::VFlushMappedMemoryRanges );
		{
			packer << packet.device;
			packer << packet.memoryRangeCount;
			packer.Push( packet.pMemoryRanges );
			 for (uint i = 0; i < packet.memoryRangeCount; ++i) {
				VPack_VkMappedMemoryRange( packet.pMemoryRanges + i, packer );
			 }
			packer.PopAndStore( packet.pMemoryRanges );
		}
		packer.End( EPacketID::VFlushMappedMemoryRanges );

		return true;
	}
//-----------------------------------------------------------------------------

	
	using EMemoryUsage = MemoryObjAnalyzer::EMemoryUsage;
/*
=================================================
	ConvertVmaAllocationCreateFlagsAndMemoryUsage
=================================================
*/
	static void ConvertVmaAllocationCreateFlagsAndMemoryUsage (VkMemoryPropertyFlags propertyFlags, EMemoryUsage usage, INOUT TracePacker &packer)
	{
		VmaAllocationCreateFlags	create_flags	= 0;
		VmaMemoryUsage				usage_flags		= VMA_MEMORY_USAGE_UNKNOWN;
		
		for (EMemoryUsage t = EMemoryUsage(1); t < EMemoryUsage::_Last; t = EMemoryUsage(uint(t) << 1))
		{
			if ( not EnumEq( usage, t ) )
				continue;

			switch ( t )
			{
				case EMemoryUsage::HostRead :
					usage_flags = VmaMemoryUsage(usage_flags | VMA_MEMORY_USAGE_CPU_TO_GPU);
					break;

				case EMemoryUsage::HostWrite :
					usage_flags = VmaMemoryUsage(usage_flags | VMA_MEMORY_USAGE_GPU_TO_CPU);
					break;

				case EMemoryUsage::Dedicated :
					create_flags = (create_flags | VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT);
					break;

				case EMemoryUsage::Exported :
				case EMemoryUsage::Imported :
				default :
					ASSERT( !"not supported" );
					break;
			}
		}
		
		if ( EnumEq( propertyFlags, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT ) )
			usage_flags = VmaMemoryUsage(usage_flags | VMA_MEMORY_USAGE_GPU_ONLY);

		if ( EnumEq( propertyFlags, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT ) )
			create_flags = (create_flags | VMA_ALLOCATION_CREATE_MAPPED_BIT);

		if ( usage_flags == VMA_MEMORY_USAGE_UNKNOWN )
			usage_flags = VmaMemoryUsage(usage_flags | VMA_MEMORY_USAGE_UNKNOWN);

		packer << create_flags;
		packer << usage_flags;
		packer << propertyFlags;
	}

/*
=================================================
	_RemapBufferMemory
=================================================
*/
	bool VulkanTraceConverter::_RemapBufferMemory (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		auto&	packet = pos.Cast< packet_vkBindBufferMemory >();
		VK_CHECK( packet.result );
		
		if ( not _initializedResources.insert( ResourceID(packet.buffer) ).second )
			return true;

		auto*	mem = _memoryObjAnalyzer->GetMemoryObj( ResourceID(packet.memory), pos.GetBookmark() );
		CHECK_ERR( mem );
		
		auto*	res_info = _resourcesBookmarks->GetResource( mem->id, pos.GetBookmark() );
		CHECK_ERR( res_info );

		CHECK( mem->dedicatedResource == ResourceID(0) or mem->dedicatedResource == ResourceID(packet.buffer) );
		
		packer.Begin( EPacketID::VAllocateBufferMemory );
		packer << packet.device;
		packer << packet.buffer;
		packer << res_info->uniqueIndex;
		ConvertVmaAllocationCreateFlagsAndMemoryUsage( mem->propertyFlags, mem->usage, INOUT packer );
		packer.End( EPacketID::VAllocateBufferMemory );
		return true;
	}
	
/*
=================================================
	_RemapImageMemory
=================================================
*/
	bool VulkanTraceConverter::_RemapImageMemory (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		auto&	packet = pos.Cast< packet_vkBindImageMemory >();
		VK_CHECK( packet.result );
		
		if ( not _initializedResources.insert( ResourceID(packet.image) ).second )
			return true;

		auto*	mem = _memoryObjAnalyzer->GetMemoryObj( ResourceID(packet.memory), pos.GetBookmark() );
		CHECK_ERR( mem );
		
		auto*	res_info = _resourcesBookmarks->GetResource( mem->id, pos.GetBookmark() );
		CHECK_ERR( res_info );

		CHECK( mem->dedicatedResource == ResourceID(0) or mem->dedicatedResource == ResourceID(packet.image) );

		packer.Begin( EPacketID::VAllocateImageMemory );
		packer << packet.device;
		packer << packet.image;
		packer << res_info->uniqueIndex;
		ConvertVmaAllocationCreateFlagsAndMemoryUsage( mem->propertyFlags, mem->usage, INOUT packer );
		packer.End( EPacketID::VAllocateImageMemory );
		return true;
	}
	
/*
=================================================
	_RemapBufferMemory2
=================================================
*/
	bool VulkanTraceConverter::_RemapBufferMemory2 (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		auto&	packet = pos.Cast< packet_vkBindBufferMemory2 >();
		VK_CHECK( packet.result );

		for (uint i = 0; i < packet.bindInfoCount; ++i)
		{
			auto&	binding = packet.pBindInfos[i];
			
			if ( not _initializedResources.insert( ResourceID(binding.buffer) ).second )
				continue;

			auto*	mem = _memoryObjAnalyzer->GetMemoryObj( ResourceID(binding.memory), pos.GetBookmark() );
			CHECK_ERR( mem );
			
			auto*	res_info = _resourcesBookmarks->GetResource( mem->id, pos.GetBookmark() );
			CHECK_ERR( res_info );

			CHECK( mem->dedicatedResource == ResourceID(0) or mem->dedicatedResource == ResourceID(binding.buffer) );
			
			packer.Begin( EPacketID::VAllocateBufferMemory );
			packer << packet.device;
			packer << binding.buffer;
			packer << res_info->uniqueIndex;
			ConvertVmaAllocationCreateFlagsAndMemoryUsage( mem->propertyFlags, mem->usage, INOUT packer );
			packer.End( EPacketID::VAllocateBufferMemory );
		}
		return true;
	}
	
/*
=================================================
	_RemapImageMemory2
=================================================
*/
	bool VulkanTraceConverter::_RemapImageMemory2 (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		auto&	packet = pos.Cast< packet_vkBindImageMemory2 >();
		VK_CHECK( packet.result );

		for (uint i = 0; i < packet.bindInfoCount; ++i)
		{
			auto&	binding = packet.pBindInfos[i];
			
			if ( not _initializedResources.insert( ResourceID(binding.image) ).second )
				continue;

			auto*	mem = _memoryObjAnalyzer->GetMemoryObj( ResourceID(binding.memory), pos.GetBookmark() );
			CHECK_ERR( mem );
			
			auto*	res_info = _resourcesBookmarks->GetResource( mem->id, pos.GetBookmark() );
			CHECK_ERR( res_info );

			CHECK( mem->dedicatedResource == ResourceID(0) or mem->dedicatedResource == ResourceID(binding.image) );
			
			packer.Begin( EPacketID::VAllocateImageMemory );
			packer << packet.device;
			packer << binding.image;
			packer << res_info->uniqueIndex;
			ConvertVmaAllocationCreateFlagsAndMemoryUsage( mem->propertyFlags, mem->usage, INOUT packer );
			packer.End( EPacketID::VAllocateImageMemory );
		}
		return true;
	}
	
/*
=================================================
	_RemapFlushMemoryRanges
=================================================
*/
	bool VulkanTraceConverter::_RemapFlushMemoryRanges (const TraceRange::Iterator &pos, FrameID frameId, INOUT TracePacker &packer)
	{
		auto&	packet = pos.Cast< packet_vkFlushMappedMemoryRanges >();

		for (uint i = 0; i < packet.memoryRangeCount; ++i)
		{
			auto&	flush_range	= packet.pMemoryRanges[i];
			auto*	transfer	= _memTransferAnalyzer->GetTransfer( ResourceID(flush_range.memory), pos.GetBookmark() );
			CHECK_ERR( transfer );
			
			auto*	mem			= _memoryObjAnalyzer->GetMemoryObj( ResourceID(flush_range.memory), pos.GetBookmark() );
			CHECK_ERR( mem );

			auto*	res_info	= _resourcesBookmarks->GetResource( mem->id, pos.GetBookmark() );
			CHECK_ERR( res_info );


			for (auto& res : transfer->resources)
			{
				if ( res.type == VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT )
				{
					// initialize buffer memory
					if ( _initializedResources.insert( res.id ).second )
					{
						ASSERT( pos.GetBookmark() < res.pos );
						
						packer.Begin( EPacketID::VAllocateBufferMemory );
						packer << packet.device;
						packer << VkBuffer(res.id);
						packer << res_info->uniqueIndex;
						ConvertVmaAllocationCreateFlagsAndMemoryUsage( mem->propertyFlags, mem->usage, INOUT packer );
						packer.End( EPacketID::VAllocateBufferMemory );
					}

					DataID	data_id = _RequestData( res.fileOffset, res.dataSize, frameId );
					CHECK_ERR( data_id != ~DataID(0) );

					packer.Begin( EPacketID::VLoadDataToBuffer );
					packer << packet.device;
					packer << VkBuffer(res.id);
					packer << data_id;
					packer << res.resOffset;
					packer << res.dataSize;
					packer.End( EPacketID::VLoadDataToBuffer );
				}
				else
				{
					ASSERT( res.type == VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT );

					// initialize buffer memory
					if ( _initializedResources.insert( res.id ).second )
					{
						ASSERT( pos.GetBookmark() < res.pos );
						
						packer.Begin( EPacketID::VAllocateImageMemory );
						packer << packet.device;
						packer << VkImage(res.id);
						packer << res_info->uniqueIndex;
						ConvertVmaAllocationCreateFlagsAndMemoryUsage( mem->propertyFlags, mem->usage, INOUT packer );
						packer.End( EPacketID::VAllocateImageMemory );
					}

					DataID	data_id = _RequestData( res.fileOffset, res.dataSize, frameId );
					CHECK_ERR( data_id != ~DataID(0) );

					packer.Begin( EPacketID::VLoadDataToImage );
					packer << packet.device;
					packer << VkImage(res.id);
					packer << data_id;
					packer << res.resOffset;
					packer << res.dataSize;
					packer.End( EPacketID::VLoadDataToImage );
				}
			}
		}
		return true;
	}

/*
=================================================
	_FreeImageMemory
=================================================
*/
	bool VulkanTraceConverter::_FreeImageMemory (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		auto&	packet = pos.Cast< packet_vkDestroyImage >();
		
		CHECK( _initializedResources.erase( ResourceID(packet.image) ) == 1 );

		packer.Begin( EPacketID::VFreeImageMemory );
		packer << packet.device;
		packer << packet.image;
		packer.End( EPacketID::VFreeImageMemory );
		return true;
	}
	
/*
=================================================
	_FreeBufferMemory
=================================================
*/
	bool VulkanTraceConverter::_FreeBufferMemory (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		auto&	packet = pos.Cast< packet_vkDestroyBuffer >();
		
		CHECK( _initializedResources.erase( ResourceID(packet.buffer) ) == 1 );
		
		packer.Begin( EPacketID::VFreeBufferMemory );
		packer << packet.device;
		packer << packet.buffer;
		packer.End( EPacketID::VFreeBufferMemory );
		return true;
	}


}	// VTC
