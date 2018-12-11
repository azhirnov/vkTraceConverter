// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Common.h"
#include "stl/CompileTime/TypeList.h"
#include "stl/Math/Bytes.h"
#include "stl/Math/Math.h"
#include "stl/Algorithms/EnumUtils.h"
#include "stl/Memory/LinearAllocator.h"

#include "extensions/vulkan_loader/VulkanLoader.h"
#include "Types/VkResourceTypes.h"
#include "Types/TracePacketHeader.h"
#include "Vulkan/VUnpacker.h"

#include "Converters/Utils/TracePacker.h"
#include "Parser/AppTrace.h"

using namespace VTC;
using namespace VTPlayer;
using VPacker = TracePacker;
#include "Generated/VulkanTraceStructPacker.h"



static void VPackerTest1 (const AppTrace &appTrace)
{
	auto*	res_bookmarks = appTrace.GetAnalyzer< AllResourcesBookmarks >();
	TEST( res_bookmarks );

	auto&	device_info	= res_bookmarks->GetResourcesByType( EResourceType::VK_OBJECT_TYPE_DEVICE )->begin()->second.front();
	auto&	mem_info	= res_bookmarks->GetResourcesByType( EResourceType::VK_OBJECT_TYPE_DEVICE_MEMORY )->begin()->second.front();
	auto&	image_info	= res_bookmarks->GetResourcesByType( EResourceType::VK_OBJECT_TYPE_IMAGE )->begin()->second.front();
	auto	pos			= std::max( device_info.FirstBookmark().pos, std::max( mem_info.FirstBookmark().pos, image_info.FirstBookmark().pos ));


	// pack
	VkDevice		src_device	= VkDevice(device_info.id);
	VkImage			src_image	= VkImage(image_info.id);
	VkDeviceMemory	src_mem		= VkDeviceMemory(mem_info.id);

	VkMemoryDedicatedAllocateInfoKHR	src_dedicated = {};
	src_dedicated.sType		= VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO_KHR;
	src_dedicated.buffer	= VK_NULL_HANDLE;
	src_dedicated.image		= src_image;

	VkMemoryAllocateInfo	src_alloc = {};
	src_alloc.sType				= VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	src_alloc.pNext				= &src_dedicated;
	src_alloc.allocationSize	= 1024;
	src_alloc.memoryTypeIndex	= 2;

	VPacker		packer{ res_bookmarks, false };
	packer.SetCurrentPos( pos );
	packer.Begin( EPacketID::VAllocateMemory );
	packer << src_device;
	packer.Push( &src_alloc );
	 VPackStruct( BitCast<VkBaseInStructure const*>(&src_alloc), packer );
	packer.PopAndStore( &src_alloc );
	packer << static_cast<VkAllocationCallbacks const*>(null);
	packer.Push( &src_mem );
	 packer << src_mem;
	packer.PopAndStore( &src_mem );
	packer.End( EPacketID::VAllocateMemory );


	// unpack
	VUnpacker::ResourceMap_t	resources;
	
	for (size_t i = 0; i < VkResourceTypes::Count; ++i) {
		size_t	count = res_bookmarks->GetResourceCountByType( GetVkResourceType(i) );
		resources[i].resize( count );
	}

	resources[ VkResourceIndex<VkDevice> ][ device_info.localIndex ]	= ResourceID(src_device);
	resources[ VkResourceIndex<VkImage> ][ image_info.localIndex ]		= ResourceID(src_image);
	resources[ VkResourceIndex<VkDeviceMemory> ][ mem_info.localIndex ]	= ResourceID(src_mem);


	TracePacketHeader const*	header		= BitCast<TracePacketHeader const*>( packer.GetData().data() );
	void *						data_ptr	= const_cast<uint8_t *>(packer.GetData().data()) + SizeOf<TracePacketHeader>;
	LinearAllocator<>			allocator;
	VUnpacker					unpacker	{ data_ptr, BytesU(header->size), BytesU(header->offset), resources, allocator };

	TEST( packer.GetData().size() == header->size + sizeof(*header) );

	auto	dst_device		= unpacker.Get<VkDevice>();
	auto*	dst_alloc		= unpacker.Get<VkMemoryAllocateInfo const*>();
	auto*	dst_callbacks	= unpacker.Get<VkAllocationCallbacks const*>();
	auto*	dst_mem			= unpacker.Get<VkDeviceMemory*>();
	auto*	dst_dedicated	= Cast<VkMemoryDedicatedAllocateInfoKHR>(dst_alloc->pNext);

	TEST( dst_device == src_device );
	//TEST( *dst_mem == VkDeviceMemory(mem_info.localIndex) );
	TEST( dst_callbacks == null );
	TEST( src_alloc.sType == dst_alloc->sType );
	TEST( src_alloc.allocationSize == dst_alloc->allocationSize );
	TEST( src_alloc.memoryTypeIndex == dst_alloc->memoryTypeIndex );
	TEST( src_dedicated.sType == dst_dedicated->sType );
	TEST( null == dst_dedicated->buffer );
	TEST( src_image == dst_dedicated->image );
	TEST( null == dst_dedicated->pNext );
}


static void VPackerTest2 (const AppTrace &appTrace)
{
	auto*	res_bookmarks = appTrace.GetAnalyzer< AllResourcesBookmarks >();
	TEST( res_bookmarks );
	
	auto&	cmd_info	= res_bookmarks->GetResourcesByType( EResourceType::VK_OBJECT_TYPE_COMMAND_BUFFER )->begin()->second.front();
	auto&	layout_info	= res_bookmarks->GetResourcesByType( EResourceType::VK_OBJECT_TYPE_PIPELINE_LAYOUT )->begin()->second.front();
	auto	pos			= std::max( cmd_info.FirstBookmark().pos, layout_info.FirstBookmark().pos );


	// pack
	auto				src_cmdbuf		= VkCommandBuffer(cmd_info.id);
	auto				src_layout		= VkPipelineLayout(layout_info.id);
	const uint			src_data[]		= { 0x11111, 0x22222, 0x333333, 0x4444 };
	VkShaderStageFlags	src_stageFlags	= 0;
	uint				src_offset		= 16;

	VPacker		packer{ res_bookmarks, false };
	packer.SetCurrentPos( pos );
	packer.Begin( EPacketID::VCmdPushConstants );
	packer << src_cmdbuf;
	packer << src_layout;
	packer << src_stageFlags;
	packer << src_offset;
	packer << uint(sizeof(src_data));
	packer.Push( src_data );
	 packer.AddArray( src_data, sizeof(src_data) );
	packer.PopAndStore( src_data );
	packer.End( EPacketID::VCmdPushConstants );
	

	// unpack
	VUnpacker::ResourceMap_t	resources;
	
	for (size_t i = 0; i < VkResourceTypes::Count; ++i) {
		size_t	count = res_bookmarks->GetResourceCountByType( GetVkResourceType(i) );
		resources[i].resize( count );
	}
	resources[ VkResourceIndex<VkCommandBuffer> ][ cmd_info.localIndex ]	 = ResourceID(src_cmdbuf);
	resources[ VkResourceIndex<VkPipelineLayout> ][ layout_info.localIndex ] = ResourceID(src_layout);

	TracePacketHeader const*	header		= BitCast<TracePacketHeader const*>( packer.GetData().data() );
	void *						data_ptr	= const_cast<uint8_t *>(packer.GetData().data()) + SizeOf<TracePacketHeader>;
	LinearAllocator<>			allocator;
	VUnpacker					unpacker	{ data_ptr, BytesU(header->size), BytesU(header->offset), resources, allocator };
	
	TEST( packer.GetData().size() == header->size + sizeof(*header) );

	auto const&  dst_cmdbuf		= unpacker.Get<VkCommandBuffer>();
	auto const&  dst_layout		= unpacker.Get<VkPipelineLayout>();
	auto const&  dst_stageFlags	= unpacker.Get<VkShaderStageFlags>();
	auto const&  dst_offset		= unpacker.Get<uint32_t>();
	auto const&  dst_size		= unpacker.Get<uint32_t>();
	auto const&  dst_pValues	= unpacker.Get<const void *>( dst_size );
	//vkCmdPushConstants( commandBuffer, layout, stageFlags, offset, size, pValues );

	TEST( src_cmdbuf == dst_cmdbuf );
	TEST( src_layout == dst_layout );
	TEST( src_stageFlags == dst_stageFlags );
	TEST( src_offset == dst_offset );
	TEST( sizeof(src_data) == dst_size );
	TEST( memcmp( src_data, dst_pValues, dst_size ) == 0 );
}


static void VPackerTest3 (const AppTrace &appTrace)
{
	auto*	res_bookmarks = appTrace.GetAnalyzer< AllResourcesBookmarks >();
	TEST( res_bookmarks );
	
	auto&	cmd_info	= res_bookmarks->GetResourcesByType( EResourceType::VK_OBJECT_TYPE_COMMAND_BUFFER )->begin()->second.front();
	auto	pos			= cmd_info.FirstBookmark().pos;


	// pack
	auto		src_cmdbuf		= VkCommandBuffer(cmd_info.id);
	const float	src_blend[4]	= { 0.1f, 0.2f, 0.3f, 0.4f };

	VPacker		packer{ res_bookmarks, false };
	packer.SetCurrentPos( pos );
	packer.Begin( EPacketID::VCmdSetBlendConstants );
	packer << src_cmdbuf;
	packer << src_blend[0];
	packer << src_blend[1];
	packer << src_blend[2];
	packer << src_blend[3];
	packer.End( EPacketID::VCmdSetBlendConstants );
	

	// unpack
	VUnpacker::ResourceMap_t	resources;
	
	for (size_t i = 0; i < VkResourceTypes::Count; ++i) {
		size_t	count = res_bookmarks->GetResourceCountByType( GetVkResourceType(i) );
		resources[i].resize( count );
	}
	resources[ VkResourceIndex<VkCommandBuffer> ][ cmd_info.localIndex ] = ResourceID(src_cmdbuf);

	TracePacketHeader const*	header		= BitCast<TracePacketHeader const*>( packer.GetData().data() );
	void *						data_ptr	= const_cast<uint8_t *>(packer.GetData().data()) + SizeOf<TracePacketHeader>;
	LinearAllocator<>			allocator;
	VUnpacker					unpacker	{ data_ptr, BytesU(header->size), BytesU(header->offset), resources, allocator };
	
	TEST( packer.GetData().size() == header->size + sizeof(*header) );
	
	auto const&  dst_cmdbuf	= unpacker.Get<VkCommandBuffer>();
	auto const&  dst_blend = unpacker.Get<const float [4]>();
	//vkCmdSetBlendConstants( commandBuffer, blendConstants );

	TEST( src_cmdbuf == dst_cmdbuf );
	TEST( memcmp( src_blend, dst_blend, sizeof(src_blend) ) == 0 );
}


static void VPackerTest4 (const AppTrace &)
{
	const char*	src_data[] = {
		"11111111",
		"222222",
		"33333333333333333333333333333",
		"444444444444444"
	};

	VPacker		packer{ null, false };

	packer.Begin( EPacketID::VCreateDevice );
	packer << CountOf(src_data);
	packer.Push( src_data );
	 for (auto& str : src_data) {
		packer.Push( str );
		 packer.AddString( str );
		packer.PopAndStore( str );
	 }
	packer.PopAndStore( src_data );
	packer.End( EPacketID::VCreateDevice );

	
	VUnpacker::ResourceMap_t	resources;
	TracePacketHeader const*	header		= BitCast<TracePacketHeader const*>( packer.GetData().data() );
	void *						data_ptr	= const_cast<uint8_t *>(packer.GetData().data()) + SizeOf<TracePacketHeader>;
	LinearAllocator<>			allocator;
	VUnpacker					unpacker	{ data_ptr, BytesU(header->size), BytesU(header->offset), resources, allocator };

	auto const&  dst_size = unpacker.Get<size_t>();
	auto const&  dst_data = unpacker.Get<char const* const*>( uint(dst_size) );

	TEST( CountOf(src_data) == dst_size );
	TEST( StringView(src_data[0]) == StringView(dst_data[0]) );
	TEST( StringView(src_data[1]) == StringView(dst_data[1]) );
	TEST( StringView(src_data[2]) == StringView(dst_data[2]) );
	TEST( StringView(src_data[3]) == StringView(dst_data[3]) );
}


extern void Test_VPacker ()
{
	AppTrace	app_trace;
	app_trace.AddAnalyzer(AnalyzerPtr{ new AllResourcesBookmarks() });

	TEST( app_trace.Open( "C:\\Projects\\VkTraceConvertor\\tests\\player\\mgf_events.vktrace"sv ));

	VPackerTest1( app_trace );
	VPackerTest2( app_trace );
	VPackerTest3( app_trace );
	VPackerTest4( app_trace );

    FG_LOGI( "Test_VPacker finished" );
}


#include "Generated/VulkanTraceStructPackerImpl.h"
#include "Converters/Utils/TracePacker.cpp"
#include "Analyzer/Default/AllResourcesBookmarks.cpp"
#include "Parser/AppTrace.cpp"
#include "Parser/TraceRange.cpp"
#include "Parser/VkObjectsTracker.cpp"
