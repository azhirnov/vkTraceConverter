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
	bool VulkanTraceConverter::_OnBindBufferMemory (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const
	{
		if ( _config.remapMemory )
			return _RemapBufferMemory( iter, INOUT packer );
		else
			return _ConvertVkFunction( iter, INOUT packer );
	}
	
/*
=================================================
	_OnBindImageMemory
=================================================
*/
	bool VulkanTraceConverter::_OnBindImageMemory (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const
	{
		if ( _config.remapMemory )
			return _RemapImageMemory( iter, INOUT packer );
		else
			return _ConvertVkFunction( iter, INOUT packer );
	}
	
/*
=================================================
	_OnBindBufferMemory2
=================================================
*/
	bool VulkanTraceConverter::_OnBindBufferMemory2 (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const
	{
		if ( _config.remapMemory )
			return _RemapBufferMemory2( iter, INOUT packer );
		else
			return _ConvertVkFunction( iter, INOUT packer );
	}
	
/*
=================================================
	_OnBindImageMemory2
=================================================
*/
	bool VulkanTraceConverter::_OnBindImageMemory2 (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const
	{
		if ( _config.remapMemory )
			return _RemapImageMemory2( iter, INOUT packer );
		else
			return _ConvertVkFunction( iter, INOUT packer );
	}
	
/*
=================================================
	_OnAllocateMemory
=================================================
*/
	bool VulkanTraceConverter::_OnAllocateMemory (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const
	{
		if ( _config.remapMemory )
			return true;
		else
			return _ConvertVkFunction( iter, INOUT packer );
	}
	
/*
=================================================
	_OnFreeMemory
=================================================
*/
	bool VulkanTraceConverter::_OnFreeMemory (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const
	{
		if ( _config.remapMemory )
			return true;
		else
			return _ConvertVkFunction( iter, INOUT packer );
	}
	
/*
=================================================
	_OnMapMemory
=================================================
*/
	bool VulkanTraceConverter::_OnMapMemory (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const
	{
		if ( _config.remapMemory )
			return true;
		else
			return _OverrideMapMemory( iter, INOUT packer );
	}
	
/*
=================================================
	_OnUnmapMemory
=================================================
*/
	bool VulkanTraceConverter::_OnUnmapMemory (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const
	{
		if ( _config.remapMemory )
			return true;
		else
			return _OverrideUnmapMemory( iter, INOUT packer );
	}
	
/*
=================================================
	_OnFlushMappedMemoryRanges
=================================================
*/
	bool VulkanTraceConverter::_OnFlushMappedMemoryRanges (const TraceRange::Iterator &iter, FrameID frameId, INOUT TracePacker &packer)
	{
		if ( _config.remapMemory )
			return _RemapFlushMemoryRanges( iter, frameId, INOUT packer );
		else
			return _OverrideFlushMappedMemoryRanges( iter, frameId, INOUT packer );
	}
	
/*
=================================================
	_OnDestroyImage
=================================================
*/
	bool VulkanTraceConverter::_OnDestroyImage (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const
	{
		if ( _config.remapMemory )
			return _FreeImageMemory( iter, INOUT packer );
		else
			return _ConvertVkFunction( iter, INOUT packer );
	}
	
/*
=================================================
	_OnDestroyBuffer
=================================================
*/
	bool VulkanTraceConverter::_OnDestroyBuffer (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const
	{
		if ( _config.remapMemory )
			return _FreeBufferMemory( iter, INOUT packer );
		else
			return _ConvertVkFunction( iter, INOUT packer );
	}
//-----------------------------------------------------------------------------

	
/*
=================================================
	_OverrideMapMemory
=================================================
*/
	bool VulkanTraceConverter::_OverrideMapMemory (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const
	{
		auto&	packet = iter.Cast< packet_vkMapMemory >();
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
	bool VulkanTraceConverter::_OverrideUnmapMemory (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const
	{
		auto&	packet = iter.Cast< packet_vkUnmapMemory >();
		
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
	bool VulkanTraceConverter::_OverrideFlushMappedMemoryRanges (const TraceRange::Iterator &iter, FrameID frameId, INOUT TracePacker &packer)
	{
		auto&	packet = iter.Cast< packet_vkFlushMappedMemoryRanges >();
		VK_CHECK( packet.result );
		CHECK_ERR( packet.memoryRangeCount > 0 and packet.pMemoryRanges );
		
		for (uint i = 0; i < packet.memoryRangeCount; ++i)
		{
			auto	mem_id		= packet.pMemoryRanges[i].memory;
			auto*	transfer	= _memTransferAnalyzer->GetTransfer( ResourceID(mem_id), iter.GetBookmark() );
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
	bool VulkanTraceConverter::_RemapBufferMemory (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const
	{
		auto&	packet = iter.Cast< packet_vkBindBufferMemory >();
		VK_CHECK( packet.result );
		
		if ( not _initializedResources.insert( ResourceID(packet.buffer) ).second )
			return true;

		auto*	mem = _memoryObjAnalyzer->GetMemoryObj( ResourceID(packet.memory), iter.GetBookmark() );
		CHECK_ERR( mem );
		CHECK( mem->dedicatedResource == ResourceID(0) or mem->dedicatedResource == ResourceID(packet.buffer) );
		
		packer.Begin( EPacketID::VAllocateBufferMemory );
		packer << packet.device;
		packer << packet.buffer;
		ConvertVmaAllocationCreateFlagsAndMemoryUsage( mem->propertyFlags, mem->usage, INOUT packer );
		packer.End( EPacketID::VAllocateBufferMemory );
		return true;
	}
	
/*
=================================================
	_RemapImageMemory
=================================================
*/
	bool VulkanTraceConverter::_RemapImageMemory (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const
	{
		auto&	packet = iter.Cast< packet_vkBindImageMemory >();
		VK_CHECK( packet.result );
		
		if ( not _initializedResources.insert( ResourceID(packet.image) ).second )
			return true;

		auto*	mem = _memoryObjAnalyzer->GetMemoryObj( ResourceID(packet.memory), iter.GetBookmark() );
		CHECK_ERR( mem );
		CHECK( mem->dedicatedResource == ResourceID(0) or mem->dedicatedResource == ResourceID(packet.image) );

		packer.Begin( EPacketID::VAllocateImageMemory );
		packer << packet.device;
		packer << packet.image;
		ConvertVmaAllocationCreateFlagsAndMemoryUsage( mem->propertyFlags, mem->usage, INOUT packer );
		packer.End( EPacketID::VAllocateImageMemory );
		return true;
	}
	
/*
=================================================
	_RemapBufferMemory2
=================================================
*/
	bool VulkanTraceConverter::_RemapBufferMemory2 (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const
	{
		auto&	packet = iter.Cast< packet_vkBindBufferMemory2 >();
		VK_CHECK( packet.result );

		for (uint i = 0; i < packet.bindInfoCount; ++i)
		{
			auto&	binding = packet.pBindInfos[i];
			auto*	mem		= _memoryObjAnalyzer->GetMemoryObj( ResourceID(binding.memory), iter.GetBookmark() );
			
			if ( not _initializedResources.insert( ResourceID(binding.buffer) ).second )
				continue;

			CHECK_ERR( mem );
			CHECK( mem->dedicatedResource == ResourceID(0) or mem->dedicatedResource == ResourceID(binding.buffer) );
			
			packer.Begin( EPacketID::VAllocateBufferMemory );
			packer << packet.device;
			packer << binding.buffer;
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
	bool VulkanTraceConverter::_RemapImageMemory2 (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const
	{
		auto&	packet = iter.Cast< packet_vkBindImageMemory2 >();
		VK_CHECK( packet.result );

		for (uint i = 0; i < packet.bindInfoCount; ++i)
		{
			auto&	binding = packet.pBindInfos[i];
			auto*	mem		= _memoryObjAnalyzer->GetMemoryObj( ResourceID(binding.memory), iter.GetBookmark() );
			
			if ( not _initializedResources.insert( ResourceID(binding.image) ).second )
				continue;

			CHECK_ERR( mem );
			CHECK( mem->dedicatedResource == ResourceID(0) or mem->dedicatedResource == ResourceID(binding.image) );
			
			packer.Begin( EPacketID::VAllocateImageMemory );
			packer << packet.device;
			packer << binding.image;
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
	bool VulkanTraceConverter::_RemapFlushMemoryRanges (const TraceRange::Iterator &iter, FrameID frameId, INOUT TracePacker &packer)
	{
		auto&	packet = iter.Cast< packet_vkFlushMappedMemoryRanges >();

		for (uint i = 0; i < packet.memoryRangeCount; ++i)
		{
			auto&	flush_range	= packet.pMemoryRanges[i];
			auto*	transfer	= _memTransferAnalyzer->GetTransfer( ResourceID(flush_range.memory), iter.GetBookmark() );
			CHECK_ERR( transfer );

			auto*	mem			= _memoryObjAnalyzer->GetMemoryObj( ResourceID(flush_range.memory), iter.GetBookmark() );
			CHECK_ERR( mem );

			for (auto& block : transfer->blocks)
			{
				// search in buffer bindings
				for (auto& buffer : mem->bufferBindings)
				{
					auto*	info = _bufferAnalyzer->GetBuffer( buffer.id, buffer.pos );
					CHECK_ERR( info );

					// buffer was destroyed or not yet created
					if ( iter.GetBookmark() > info->LastBookmark().pos or
						 iter.GetBookmark() < info->FirstBookmark().pos )
						continue;

					// check intersection
					if ( buffer.offset >= (block.memOffset + block.dataSize) or
						 block.memOffset >= (buffer.offset + buffer.size) )
						continue;

					// initialize buffer memory
					if ( _initializedResources.insert( buffer.id ).second )
					{
						ASSERT( iter.GetBookmark() < buffer.pos );
						
						packer.Begin( EPacketID::VAllocateBufferMemory );
						packer << packet.device;
						packer << VkBuffer(buffer.id);
						ConvertVmaAllocationCreateFlagsAndMemoryUsage( mem->propertyFlags, mem->usage, INOUT packer );
						packer.End( EPacketID::VAllocateBufferMemory );
					}

					// intersect
					VkDeviceSize	offset		= Max( buffer.offset, block.memOffset );
					VkDeviceSize	size		= Min( buffer.offset + buffer.size, block.memOffset + block.dataSize ) - offset;
					uint64_t		file_pos	= block.fileOffset + (block.memOffset - offset);

					DataID	data_id = _RequestData( file_pos, size, frameId );
					CHECK_ERR( data_id != ~DataID(0) );

					packer.Begin( EPacketID::VLoadDataToBuffer );
					packer << packet.device;
					packer << VkBuffer(buffer.id);
					packer << data_id;
					packer << offset;
					packer << size;
					packer.End( EPacketID::VLoadDataToBuffer );
				}

				// search in image bindings
				for (auto& image : mem->imageBindings)
				{
					auto*	info = _imageAnalyzer->GetImage( image.id, image.pos );
					CHECK_ERR( info );

					// image was destroyed or not yet created
					if ( iter.GetBookmark() > info->LastBookmark().pos or
						 iter.GetBookmark() < info->FirstBookmark().pos )
						continue;

					// check intersection
					if ( image.offset >= (block.memOffset + block.dataSize) or
						 block.memOffset >= (image.offset + image.size) )
						continue;
					
					// initialize buffer memory
					if ( _initializedResources.insert( image.id ).second )
					{
						ASSERT( iter.GetBookmark() < image.pos );
						
						packer.Begin( EPacketID::VAllocateImageMemory );
						packer << packet.device;
						packer << VkImage(image.id);
						ConvertVmaAllocationCreateFlagsAndMemoryUsage( mem->propertyFlags, mem->usage, INOUT packer );
						packer.End( EPacketID::VAllocateImageMemory );
					}

					// intersect
					VkDeviceSize	offset		= Max( image.offset, block.memOffset );
					VkDeviceSize	size		= Min( image.offset + image.size, block.memOffset + block.dataSize ) - offset;
					uint64_t		file_pos	= block.fileOffset + (block.memOffset - offset);

					DataID	data_id = _RequestData( file_pos, size, frameId );
					CHECK_ERR( data_id != ~DataID(0) );

					packer.Begin( EPacketID::VLoadDataToImage );
					packer << packet.device;
					packer << VkImage(image.id);
					packer << data_id;
					packer << offset;
					packer << size;
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
	bool VulkanTraceConverter::_FreeImageMemory (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const
	{
		auto&	packet = iter.Cast< packet_vkDestroyImage >();
		
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
	bool VulkanTraceConverter::_FreeBufferMemory (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const
	{
		auto&	packet = iter.Cast< packet_vkDestroyBuffer >();
		
		CHECK( _initializedResources.erase( ResourceID(packet.buffer) ) == 1 );
		
		packer.Begin( EPacketID::VFreeBufferMemory );
		packer << packet.device;
		packer << packet.buffer;
		packer.End( EPacketID::VFreeBufferMemory );
		return true;
	}


}	// VTC
