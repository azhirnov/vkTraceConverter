// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Converters/CppVulkan/CppVulkanConverter.h"
#include "extensions/vulkan_loader/VulkanCheckError.h"

namespace VTC
{

#	include "Generated/VkEnumToString.h"
#	include "Generated/VkStructToString.h"

/*
=================================================
	_OnBindBufferMemory
=================================================
*/
	bool CppVulkanConverter::_OnBindBufferMemory (const TraceRange::Iterator &iter, INOUT String &src) const
	{
		if ( _config.remapMemory )
			return _RemapBufferMemory( iter, INOUT src );
		else
			return _ConvertVkFunction( iter, INOUT src );
	}
	
/*
=================================================
	_OnBindImageMemory
=================================================
*/
	bool CppVulkanConverter::_OnBindImageMemory (const TraceRange::Iterator &iter, INOUT String &src) const
	{
		if ( _config.remapMemory )
			return _RemapImageMemory( iter, INOUT src );
		else
			return _ConvertVkFunction( iter, INOUT src );
	}
	
/*
=================================================
	_OnBindBufferMemory2
=================================================
*/
	bool CppVulkanConverter::_OnBindBufferMemory2 (const TraceRange::Iterator &iter, INOUT String &src) const
	{
		if ( _config.remapMemory )
			return _RemapBufferMemory2( iter, INOUT src );
		else
			return _ConvertVkFunction( iter, INOUT src );
	}
	
/*
=================================================
	_OnBindImageMemory2
=================================================
*/
	bool CppVulkanConverter::_OnBindImageMemory2 (const TraceRange::Iterator &iter, INOUT String &src) const
	{
		if ( _config.remapMemory )
			return _RemapImageMemory2( iter, INOUT src );
		else
			return _ConvertVkFunction( iter, INOUT src );
	}
	
/*
=================================================
	_OnAllocateMemory
=================================================
*/
	bool CppVulkanConverter::_OnAllocateMemory (const TraceRange::Iterator &iter, INOUT String &src) const
	{
		if ( _config.remapMemory )
			return true;
		else
			return _ConvertVkFunction( iter, INOUT src );
	}
	
/*
=================================================
	_OnFreeMemory
=================================================
*/
	bool CppVulkanConverter::_OnFreeMemory (const TraceRange::Iterator &iter, INOUT String &src) const
	{
		if ( _config.remapMemory )
			return true;
		else
			return _ConvertVkFunction( iter, INOUT src );
	}
	
/*
=================================================
	_OnMapMemory
=================================================
*/
	bool CppVulkanConverter::_OnMapMemory (const TraceRange::Iterator &iter, INOUT String &src) const
	{
		if ( _config.remapMemory )
			return true;
		else
			return _OverrideMapMemory( iter, INOUT src );
	}
	
/*
=================================================
	_OnUnmapMemory
=================================================
*/
	bool CppVulkanConverter::_OnUnmapMemory (const TraceRange::Iterator &iter, INOUT String &src) const
	{
		if ( _config.remapMemory )
			return true;
		else
			return _OverrideUnmapMemory( iter, INOUT src );
	}
	
/*
=================================================
	_OnFlushMappedMemoryRanges
=================================================
*/
	bool CppVulkanConverter::_OnFlushMappedMemoryRanges (const TraceRange::Iterator &iter, FrameID frameId, INOUT String &src)
	{
		if ( _config.remapMemory )
			return _RemapFlushMemoryRanges( iter, frameId, INOUT src );
		else
			return _OverrideFlushMappedMemoryRanges( iter, frameId, INOUT src );
	}
	
/*
=================================================
	_OnDestroyImage
=================================================
*/
	bool CppVulkanConverter::_OnDestroyImage (const TraceRange::Iterator &iter, INOUT String &src) const
	{
		if ( _config.remapMemory )
			return _FreeImageMemory( iter, INOUT src );
		else
			return _ConvertVkFunction( iter, INOUT src );
	}
	
/*
=================================================
	_OnDestroyBuffer
=================================================
*/
	bool CppVulkanConverter::_OnDestroyBuffer (const TraceRange::Iterator &iter, INOUT String &src) const
	{
		if ( _config.remapMemory )
			return _FreeBufferMemory( iter, INOUT src );
		else
			return _ConvertVkFunction( iter, INOUT src );
	}
//-----------------------------------------------------------------------------
	

/*
=================================================
	_OverrideMapMemory
=================================================
*/
	bool CppVulkanConverter::_OverrideMapMemory (const TraceRange::Iterator &iter, INOUT String &src) const
	{
		auto&	packet = iter.Cast< packet_vkMapMemory >();
		VK_CHECK( packet.result );

		src << "\t{\n"
			<< "\t	void*  mappedMem = null;\n"
			<< "\t	VK_CALL( app.vkMapMemory(\n"
			<< "\t				/*device*/ app.GetResource(DeviceID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, packet.device ) << ")),\n"
			<< "\t				/*memory*/ app.GetResource(DeviceMemoryID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, packet.memory ) << ")),\n"
			<< "\t				/*offset*/ " << IntToString( packet.offset ) << ",\n"
			<< "\t				/*size*/ " << IntToString( packet.size ) << ",\n"
			<< "\t				/*flags*/ " << Serialize_VkMemoryMapFlags( packet.flags ) << ",\n"
			<< "\t				/*ppData*/ &mappedMem ));\n"
			<< "\t	app.OnMapMemory( DeviceMemoryID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, packet.memory ) << "), mappedMem, "
						<< IntToString( packet.offset ) << ", " << IntToString( packet.size ) << " );\n"
			<< "\t}\n";

		return true;
	}
	
/*
=================================================
	_OverrideUnmapMemory
=================================================
*/
	bool CppVulkanConverter::_OverrideUnmapMemory (const TraceRange::Iterator &iter, INOUT String &src) const
	{
		auto&	packet = iter.Cast< packet_vkUnmapMemory >();

		src << "\tapp.vkUnmapMemory(\n"
			<< "\t		/*device*/ app.GetResource(DeviceID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, packet.device ) << ")),\n"
			<< "\t		/*memory*/ app.GetResource(DeviceMemoryID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, packet.memory ) << ")) );\n"
			<< "\tapp.OnUnmapMemory( DeviceMemoryID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, packet.memory ) << ") );\n";

		return true;
	}
	
/*
=================================================
	_OverrideFlushMappedMemoryRanges
=================================================
*/
	bool CppVulkanConverter::_OverrideFlushMappedMemoryRanges (const TraceRange::Iterator &iter, FrameID frameId, INOUT String &src)
	{
		const StringView	indent = "\t\t";

		auto&	before = _tempStr1;
		auto&	result = _tempStr2;
		auto&	packet = iter.Cast< packet_vkFlushMappedMemoryRanges >();

		VK_CHECK( packet.result );
		CHECK_ERR( packet.memoryRangeCount > 0 and packet.pMemoryRanges );

		src << "\t{\n";

		const String arr_name = _nameSerializer.MakeUnique( &packet.pMemoryRanges, "memoryRanges"s, "mappedMemoryRange"s );

		before << indent << "VkMappedMemoryRange  " << arr_name << "[" << IntToString( packet.memoryRangeCount ) << "] = {};\n";
		
		for (uint i = 0; i < packet.memoryRangeCount; ++i)
		{
			Serialize2_VkMappedMemoryRange( packet.pMemoryRanges + i, String(arr_name) << "[" << IntToString(i) << "]",
										    _nameSerializer, *_resRemapper, indent, INOUT result, INOUT before );

			auto	mem_id		= ResourceID(packet.pMemoryRanges[i].memory);
			auto*	transfer	= _memTransferAnalyzer->GetTransfer( mem_id, iter.GetBookmark() );
			CHECK_ERR( transfer );
			
			for (auto& block : transfer->blocks)
			{
				DataID	data_id = _RequestData( _inputFile, block.fileOffset, block.dataSize, frameId );
				CHECK_ERR( data_id != ~DataID(0) );

				src << indent << "app.LoadDataToMappedMemory( DeviceMemoryID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, mem_id ) << "), "
					<< "DataID(" << IntToString( data_id ) << "), "
					<< IntToString( block.memOffset ) << ", "
					<< IntToString( block.dataSize ) << " );\n";
			}
		}

		result << indent << "VK_CALL( app.vkFlushMappedMemoryRanges( \n";
		result << indent << "		/*device*/ " << "app.GetResource(DeviceID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, packet.device ) << ")),\n";
		result << indent << "		/*memoryRangeCount*/ " << IntToString( packet.memoryRangeCount ) << ",\n";
		result << indent << "		/*pMemoryRanges*/ " << _nameSerializer.Get( &packet.pMemoryRanges ) << " ));\n";

		src << before << result << "\t}\n";
		return true;
	}
//-----------------------------------------------------------------------------

	
	using EMemoryUsage = MemoryObjAnalyzer::EMemoryUsage;

/*
=================================================
	ConvertVmaAllocationCreateFlagsAndMemoryUsage
=================================================
*/
	ND_ static String  ConvertVmaAllocationCreateFlagsAndMemoryUsage (VkMemoryPropertyFlags flags, EMemoryUsage usage)
	{
		String	create_flags;
		String	usage_flags;

		for (EMemoryUsage t = EMemoryUsage(1); t < EMemoryUsage::_Last; t = EMemoryUsage(uint(t) << 1))
		{
			if ( not EnumEq( usage, t ) )
				continue;

			switch ( t )
			{
				case EMemoryUsage::HostRead :
					usage_flags << (usage_flags.empty() ? "" : "|") << "VMA_MEMORY_USAGE_CPU_TO_GPU";
					break;

				case EMemoryUsage::HostWrite :
					usage_flags << (usage_flags.empty() ? "" : "|") << "VMA_MEMORY_USAGE_GPU_TO_CPU";
					break;

				case EMemoryUsage::Dedicated :
					create_flags << (create_flags.empty() ? "" : "|") << "VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT";
					break;

				case EMemoryUsage::Exported :
				case EMemoryUsage::Imported :
				default :
					ASSERT( !"not supported" );
					break;
			}
		}
		
		if ( EnumEq( flags, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT ) )
			usage_flags << (usage_flags.empty() ? "" : "|") << "VMA_MEMORY_USAGE_GPU_ONLY";

		if ( EnumEq( flags, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT ) )
			create_flags << (create_flags.empty() ? "" : "|") << "VMA_ALLOCATION_CREATE_MAPPED_BIT";


		if ( usage_flags.empty() )
			usage_flags << "VMA_MEMORY_USAGE_UNKNOWN";

		if ( create_flags.empty() )
			create_flags << "0";

		return create_flags << ", " << usage_flags << ", " << Serialize_VkMemoryPropertyFlags( flags );
	}
	
/*
=================================================
	_RemapBufferMemory
=================================================
*/
	bool CppVulkanConverter::_RemapBufferMemory (const TraceRange::Iterator &iter, INOUT String &src) const
	{
		auto&	packet = iter.Cast< packet_vkBindBufferMemory >();
		VK_CHECK( packet.result );
		
		if ( not _initializedResources.insert( ResourceID(packet.buffer) ).second )
			return true;

		auto*	mem = _memoryObjAnalyzer->GetMemoryObj( ResourceID(packet.memory), iter.GetBookmark() );
		CHECK_ERR( mem );
		CHECK( mem->dedicatedResource == ResourceID(0) or mem->dedicatedResource == ResourceID(packet.buffer) );

		src << "\tapp.AllocateBufferMemory( "
			<< "BufferID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, packet.buffer ) << "), "
			<< ConvertVmaAllocationCreateFlagsAndMemoryUsage( mem->propertyFlags, mem->usage ) << " );\n";

		return true;
	}
	
/*
=================================================
	_RemapImageMemory
=================================================
*/
	bool CppVulkanConverter::_RemapImageMemory (const TraceRange::Iterator &iter, INOUT String &src) const
	{
		auto&	packet = iter.Cast< packet_vkBindImageMemory >();
		VK_CHECK( packet.result );
		
		if ( not _initializedResources.insert( ResourceID(packet.image) ).second )
			return true;

		auto*	mem = _memoryObjAnalyzer->GetMemoryObj( ResourceID(packet.memory), iter.GetBookmark() );
		CHECK_ERR( mem );
		CHECK( mem->dedicatedResource == ResourceID(0) or mem->dedicatedResource == ResourceID(packet.image) );

		src << "\tapp.AllocateImageMemory( "
			<< "ImageID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, packet.image ) << "), "
			<< ConvertVmaAllocationCreateFlagsAndMemoryUsage( mem->propertyFlags, mem->usage ) << " );\n";

		return true;
	}
	
/*
=================================================
	_RemapBufferMemory2
=================================================
*/
	bool CppVulkanConverter::_RemapBufferMemory2 (const TraceRange::Iterator &iter, INOUT String &src) const
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

			src << "\tapp.AllocateBufferMemory( "
				<< "BufferID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, binding.buffer ) << "), "
				<< ConvertVmaAllocationCreateFlagsAndMemoryUsage( mem->propertyFlags, mem->usage ) << " );\n";
		}
		return true;
	}
	
/*
=================================================
	_RemapImageMemory2
=================================================
*/
	bool CppVulkanConverter::_RemapImageMemory2 (const TraceRange::Iterator &iter, INOUT String &src) const
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
			
			src << "\tapp.AllocateImageMemory( "
				<< "ImageID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, binding.image ) << "), "
				<< ConvertVmaAllocationCreateFlagsAndMemoryUsage( mem->propertyFlags, mem->usage ) << " );\n";
		}
		return true;
	}
	
/*
=================================================
	_RemapFlushMemoryRanges
=================================================
*/
	bool CppVulkanConverter::_RemapFlushMemoryRanges (const TraceRange::Iterator &iter, FrameID frameId, INOUT String &src)
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
						
						src << "\tapp.AllocateBufferMemory( "
							<< "BufferID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, buffer.id ) << "), "
							<< ConvertVmaAllocationCreateFlagsAndMemoryUsage( mem->propertyFlags, mem->usage ) << " );\n";
					}

					// intersect
					VkDeviceSize	offset		= Max( buffer.offset, block.memOffset );
					VkDeviceSize	size		= Min( buffer.offset + buffer.size, block.memOffset + block.dataSize ) - offset;
					uint64_t		file_pos	= block.fileOffset + (block.memOffset - offset);

					DataID	data_id = _RequestData( _inputFile, file_pos, size, frameId );
					CHECK_ERR( data_id != ~DataID(0) );

					src << "\tapp.LoadDataToBuffer( BufferID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, buffer.id ) << "), "
						<< "DataID(" << IntToString( data_id ) << "), "
						<< IntToString( offset ) << ", "
						<< IntToString( size ) << " );\n";
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

						src << "\tapp.AllocateImageMemory( "
							<< "ImageID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, image.id ) << "), "
							<< ConvertVmaAllocationCreateFlagsAndMemoryUsage( mem->propertyFlags, mem->usage ) << " );\n";
					}

					// intersect
					VkDeviceSize	offset		= Max( image.offset, block.memOffset );
					VkDeviceSize	size		= Min( image.offset + image.size, block.memOffset + block.dataSize ) - offset;
					uint64_t		file_pos	= block.fileOffset + (block.memOffset - offset);

					DataID	data_id = _RequestData( _inputFile, file_pos, size, frameId );
					CHECK_ERR( data_id != ~DataID(0) );

					src << "\tapp.LoadDataToImage( ImageID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, image.id ) << "), "
						<< "DataID(" << IntToString( data_id ) << "), "
						<< IntToString( offset ) << ", "
						<< IntToString( size ) << " );\n";
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
	bool CppVulkanConverter::_FreeImageMemory (const TraceRange::Iterator &iter, INOUT String &src) const
	{
		auto&	packet = iter.Cast< packet_vkDestroyImage >();
		
		CHECK( _initializedResources.erase( ResourceID(packet.image) ) == 1 );

		src << "\tapp.vkDestroyImage( \n"
			<< "\t		/*device*/ " << "app.GetResource(DeviceID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, packet.device ) << ")),\n"
			<< "\t		/*image*/ " << "app.GetResource(ImageID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, packet.image ) << ")),\n"
			<< "\t		/*pAllocator*/ null );\n"
			<< "\tapp.FreeImageMemory( ImageID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, packet.image ) << ") );\n";

		return true;
	}
	
/*
=================================================
	_FreeBufferMemory
=================================================
*/
	bool CppVulkanConverter::_FreeBufferMemory (const TraceRange::Iterator &iter, INOUT String &src) const
	{
		auto&	packet = iter.Cast< packet_vkDestroyBuffer >();
		
		CHECK( _initializedResources.erase( ResourceID(packet.buffer) ) == 1 );

		src << "\tapp.vkDestroyBuffer( \n"
			<< "\t		/*device*/ " << "app.GetResource(DeviceID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, packet.device ) << ")),\n"
			<< "\t		/*buffer*/ " << "app.GetResource(BufferID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, packet.buffer ) << ")),\n"
			<< "\t		/*pAllocator*/ null );\n"
			<< "\tapp.FreeBufferMemory( BufferID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, packet.buffer ) << ") );\n";

		return true;
	}

}	// VTC
