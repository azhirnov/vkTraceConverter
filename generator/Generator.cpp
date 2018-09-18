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
	StringView	output;

	for (int i = 1; i < argc; ++i)
	{
		StringView	key = argv[i];
		StringView	value;

		if ( ++i < argc )
			value = argv[i];

		if ( key == "-vulkan" ){
			vulkan_headers = value;
		}else
		if ( key == "-vktrace" ) {
			vktrace_ids = value;
		}else
		if ( key == "-output" ) {
			output = value;
		}else {
			RETURN_ERR( "unsupported command arg: "s << key, 1 );
		}
	}

	// temp
#if 0
	vulkan_headers = "C:/Projects/VkTraceConvertor/build/install/Vulkan-Headers/include/vulkan";
	vktrace_ids = "C:/Projects/VkTraceConvertor/external/LunarG-VulkanTools/vktrace/vktrace_common/vktrace_trace_packet_identifiers.h";
	output = "C:/Projects/VkTraceConvertor/vktrace_conv/Generated";
	FG_LOGI( "vulkan_headers: "s << vulkan_headers );
	FG_LOGI( "vktrace_ids: "s << vktrace_ids );
	FG_LOGI( "output: "s << output );
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
	
	CHECK_ERR( generator.GenBookmarksForFunc( fs::path(output).append( "BuildFunctionResourceBookmarks.h" )), -9 );
	CHECK_ERR( generator.GenBookmarksForStruct( fs::path(output).append( "BuildStructResourceBookmarks.h" )), -10 );

	CHECK_ERR( generator.MarkRequiredTypesForUnpack(), -11 );
	CHECK_ERR( generator.GenUnpacker( fs::path(output).append( "UnpackPacket.h" )), -12 );
	
	CHECK_ERR( generator.MarkRequiredTypesForSerializing(), -14 );
	CHECK_ERR( generator.GenRawVulkanCalls( fs::path(output).append( "BuildRawVulkanCalls.h" )), -15 );
	CHECK_ERR( generator.GenEnumToString( fs::path(output).append( "VkEnumToString.h" ), fs::path(output).append( "VkEnumToStringImpl.h" )), -16 );
	CHECK_ERR( generator.GenStructToString( fs::path(output).append( "VkStructToString.h" ), fs::path(output).append( "VkStructToStringImpl.h" )), -17 );
	CHECK_ERR( generator.GenStructTypeHelpers( fs::path(output).append( "VkStructTypes.h" )), -18 );

	return 0;
}
