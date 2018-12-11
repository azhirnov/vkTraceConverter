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

		if ( key == "-vulkan" )
			vulkan_headers = value;
		else
		if ( key == "-vktrace" )
			vktrace_ids = value;
		else
		if ( key == "-output" )
			output = value;
		else
			RETURN_ERR( "unsupported command arg: "s << key, 1 );
	}

	
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
	CHECK_ERR( generator.GenFuncErrorChecks( fs::path(output).append( "CheckPacketError.h" )), -13 );
	
	CHECK_ERR( generator.MarkRequiredTypesForSerializing(), -14 );
	CHECK_ERR( generator.GenRawVulkanCalls( fs::path(output).append( "BuildRawVulkanCalls.h" )), -15 );
	CHECK_ERR( generator.GenEnumToString( fs::path(output).append( "VkEnumToString.h" ), fs::path(output).append( "VkEnumToStringImpl.h" )), -16 );
	CHECK_ERR( generator.GenStructToString( fs::path(output).append( "VkStructToString.h" ), fs::path(output).append( "VkStructToStringImpl.h" )), -17 );
	CHECK_ERR( generator.GenStructTypeHelpers( fs::path(output).append( "VkStructTypes.h" )), -18 );
	CHECK_ERR( generator.GenFormatHelpers( fs::path(output).append( "VkFormatHelpers.h" )), -19 );

	CHECK_ERR( generator.GenVulkanTracePacker( fs::path(output).append( "VulkanTracePacketIDs.h" ),
											   fs::path(output).append( "VulkanTraceStructPacker.h" ),
											   fs::path(output).append( "VulkanTraceStructPackerImpl.h" ),
											   fs::path(output).append( "VulkanTraceFuncPacker.h" )), -20 );
	
	CHECK_ERR( generator.GenVulkanTracePlayer( fs::path(output).append( "VulkanTraceStructUnpacker.h" ),
											   fs::path(output).append( "VulkanTraceStructUnpackerImpl.h" ),
											   fs::path(output).append( "VulkanTraceFuncUnpacker.h" )), -21 );

	return 0;
}
