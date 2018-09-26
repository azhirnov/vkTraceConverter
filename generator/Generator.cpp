// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Generator.h"

/*
=================================================
	main
=================================================
*/
int main (int argc, const char** argv)
{
	using namespace VTC;

	CHECK_ERR( argv > 0 );
	
	StringView	vulkan_headers;
	StringView	vktrace_ids;
	StringView	output1;
	StringView	output2;

	for (int i = 1; i < argc; ++i)
	{
		StringView	key = argv[i];
		StringView	value;

		if ( ++i < argc )
			value = argv[i];

		if ( key == "-vulkan" )
			vulkan_headers = value;
		else
		if ( key == "-vktrace" )
			vktrace_ids = value;
		else
		if ( key == "-output" )
			output1 = value;
		else
		if ( key == "-player-output" )
			output2 = value;
		else
			RETURN_ERR( "unsupported command arg: "s << key, 1 );
	}

	// temp
#if 1
	vulkan_headers = "C:/Projects/VkTraceConvertor/build/install/Vulkan-Headers/include/vulkan";
	vktrace_ids = "C:/Projects/VkTraceConvertor/external/LunarG-VulkanTools/vktrace/vktrace_common/vktrace_trace_packet_identifiers.h";
	output1 = "C:/Projects/VkTraceConvertor/vktrace_conv/Generated";
	output2 = "C:/Projects/VkTraceConvertor/player/Generated";
	FG_LOGI( "vulkan_headers: "s << vulkan_headers );
	FG_LOGI( "vktrace_ids: "s << vktrace_ids );
	FG_LOGI( "output1: "s << output1 );
	FG_LOGI( "output2: "s << output2 );
#endif

	
	Generator	generator;

	CHECK_ERR( generator.ParseVkHeaders( vulkan_headers ), -1 );
	CHECK_ERR( generator.ParsePacketIDs( vktrace_ids ), -2 );
	CHECK_ERR( generator.BuildBasicTypeMap(), -3 );
	CHECK_ERR( generator.BuildResourceTypeMap(), -4 );
	CHECK_ERR( generator.BuildFuncArgCountOfMap(), -5 );
	CHECK_ERR( generator.BuildStructFieldCountOfMap(), -6 );
	CHECK_ERR( generator.BuildFuncArgDestructorMap(), -7 );
	CHECK_ERR( generator.BuildSkipPacketsMap(), -8 );
	CHECK_ERR( generator.SetFunctionsScope(), -9 );
	
	CHECK_ERR( generator.GenBookmarksForFunc( fs::path(output1).append( "BuildFunctionResourceBookmarks.h" )), -9 );
	CHECK_ERR( generator.GenBookmarksForStruct( fs::path(output1).append( "BuildStructResourceBookmarks.h" )), -10 );

	CHECK_ERR( generator.MarkRequiredTypesForUnpack(), -11 );
	CHECK_ERR( generator.GenUnpacker( fs::path(output1).append( "UnpackPacket.h" )), -12 );
	
	CHECK_ERR( generator.MarkRequiredTypesForSerializing(), -14 );
	CHECK_ERR( generator.GenRawVulkanCalls( fs::path(output1).append( "BuildRawVulkanCalls.h" )), -15 );
	CHECK_ERR( generator.GenEnumToString( fs::path(output1).append( "VkEnumToString.h" ), fs::path(output1).append( "VkEnumToStringImpl.h" )), -16 );
	CHECK_ERR( generator.GenStructToString( fs::path(output1).append( "VkStructToString.h" ), fs::path(output1).append( "VkStructToStringImpl.h" )), -17 );
	CHECK_ERR( generator.GenStructTypeHelpers( fs::path(output1).append( "VkStructTypes.h" )), -18 );

	CHECK_ERR( generator.GenVulkanTracePacker( fs::path(output1).append( "VulkanTracePacketIDs.h" ),
											   fs::path(output1).append( "VulkanTraceStructPacker.h" ),
											   fs::path(output1).append( "VulkanTraceStructPackerImpl.h" ),
											   fs::path(output1).append( "VulkanTraceFuncPacker.h" )), -19 );
	
	CHECK_ERR( generator.GenVulkanTracePlayer( fs::path(output2).append( "VulkanTraceStructUnpacker.h" ),
											   fs::path(output2).append( "VulkanTraceStructUnpackerImpl.h" ),
											   fs::path(output2).append( "VulkanTraceFuncUnpacker.h" )), -20 );

	return 0;
}
