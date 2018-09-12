// Copyright (c)  Zhirnov Andrey. For more information see 'LICENSE.txt'

#include "Parser/AppTrace.h"
#include "Converters/Converter.h"
#include "Converters/Data/ResourceDataManager.h"

#include "Analyzer/SwapchainAnalyzer.h"
#include "Analyzer/ImageUsageAnalyzer.h"
#include "Analyzer/AllResourcesBookmarks.h"
#include "Analyzer/DeviceAnalyzer.h"

#include <iostream>
#include <filesystem>

using namespace VTC;
using namespace std::string_literals;

/*
=================================================
	Help
=================================================
*/
static const char	s_Help[] = R"#(
-o
--open			open vktrace file

-d
--output-dir    output directory

-c      
--convert		run converters, available values:
					vk-cpp
					vez-cpp
					fg-cpp
					gl-cpp
					graphviz
					screenshot
					all
-e
--extension		extension passes, available values:
					rem-redundant
					opt-renderpass
					opt-dedicated	-- dedicated allocation.
					opt-mem			-- optimize memory.
					opt-barrier		-- optimize pipeline barriers.
					gpu-bench
					cpu-bench
					all

--cfg-vk-cpp			configure 'vk-cpp' converter:
							multithreaded=[true/false] -- enable/disable multithread submiting to queue.
							async-load=[true/false] -- enable/disable async data loading.
							begin=[N] -- start converting on N frame, default is 0.
							end=[N] -- stop converting on N frame, default is -1.

--cfg-vez-cpp			configure 'vez-cpp' converter:

--cfg-fg-cpp			configure 'fg-cpp' converter:

--cfg-gl-cpp			configure 'gl-cpp' converter:

--cfg-graphviz			configure 'graphviz' converter:

--cfg-screenshot		configure 'screenshot' converter:
							freq=[1..N] -- make screenshot every N frames, default is 30.
							begin=[N] -- start recording on N frame, default is 0.
							end=[N] -- stop recording on N frame, default is -1.
							marker-trigger="name" -- make screenshot on vkCmdDebugMarkerInsertEXT if pMarkerName == "name".
							begin-renderpass-trigger=[ID / "name"] -- make screenshot on vkCmdBeginRenderPass if renderPass == ID or 
													is renderPass was named by vkDebugMarkerSetObjectNameEXT and pObjectName == "name".
							end-renderpass-trigger=[ID / "name"] -- same as above.

--cfg-rem-redundant		configure 'rem-redundant' extension pass:

--cfg-opt-renderpass	configure 'opt-renderpass' extension pass:

--cfg-opt-dedicated		configure 'dedicated-on' extension pass:
							disable-all -- remove all usage of dedicated allocation.
							enable-auto -- use dedicated allocation if it is required for resource by implementation.
							enable-all -- always use dedicated allocation.
							enable-rt-only -- use dedicated allocation only for render targets.
							min-limit-kb=[1..N] -- set minimal resource size in Kb.
							min-limit-mb=[1..N] -- set minimal resource size in Mb.

--cfg-opt-mem			configure 'opt-mem' extension pass:

--cfg-opt-barrier		configure 'opt-barrier' extension pass:

--cfg-gpu-bench			configure 'gpu-bench' extension pass:

--cfg-cpu-bench			configure 'cpu-bench' extension pass:

)#";

/*
=================================================
	ParseConverters
=================================================
*/
static bool ParseConverters (const int argc, const char** argv, INOUT int &i, INOUT ConverterConfig::Converters &config)
{
	for (; i < argc; ++i)
	{
		StringView	name	= argv[i];
		bool		match	= false;

		if ( name.length() > 0 and name[0] == '-' )
			return true;

		if ( name == "vk-cpp" or name == "all" )
		{
			config.cppRawVulkan.isEnabled = true;
			match = true;
		}

		if ( name == "vez-cpp" or name == "all" )
		{
			config.cppVulkanEZ.isEnabled = true;
			match = true;
		}

		if ( name == "fg-cpp" or name == "all" )
		{
			config.cppFrameGraph.isEnabled = true;
			match = true;
		}

		if ( name == "gl-cpp" or name == "all" )
		{
			config.cppRawOpenGL.isEnabled = true;
			match = true;
		}

		if ( name == "graphviz" or name == "all" )
		{
			config.graphviz.isEnabled = true;
			match = true;
		}

		if ( name == "screenshot" or name == "all" )
		{
			config.screenshot.isEnabled = true;
			match = true;
		}

		if ( not match ) {
			FG_LOGE( "unknown converter type: \""s << name << '"' );
			continue;
		}
	}
	return true;
}

/*
=================================================
	ParseExtensionPasses
=================================================
*/
static bool ParseExtensionPasses (const int argc, const char** argv, INOUT int &i, INOUT ConverterConfig::ExtensionPasses &config)
{
	for (; i < argc; ++i)
	{
		StringView	name	= argv[i];
		bool		match	= false;
		
		if ( name.length() > 0 and name[0] == '-' )
			return true;

		if ( name == "rem-redundant" or name == "all" )
		{
			config.remRedundant.isEnabled = true;
			match = true;
		}

		if ( name == "opt-renderpass" or name == "all" )
		{
			config.optRenderpass.isEnabled = true;
			match = true;
		}

		if ( name == "opt-dedicated" or name == "all" )
		{
			config.optDedicated.isEnabled = true;
			match = true;
		}

		if ( name == "opt-mem" or name == "all" )
		{
			config.optMemory.isEnabled = true;
			match = true;
		}

		if ( name == "opt-barrier" or name == "all" )
		{
			config.optBarrier.isEnabled = true;
			match = true;
		}

		if ( name == "gpu-bench" or name == "all" )
		{
			config.gpuBench.isEnabled = true;
			match = true;
		}

		if ( name == "cpu-bench" or name == "all" )
		{
			config.cpuBench.isEnabled = true;
			match = true;
		}
		
		if ( not match ) {
			FG_LOGE( "unknown extension pass: \""s << name << '"' );
			continue;
		}
	}
	return true;
}

/*
=================================================
	ParseVkCppConfig
=================================================
*/
static bool ParseVkCppConfig (StringView param, StringView value, INOUT ConverterConfig &mainConfig)
{
	auto&	cfg = mainConfig.conveters.cppRawVulkan;

	if ( param == "begin" ) {
		cfg.firstFrame = FrameID(std::stoll( String(value) ));
		return true;
	}
	
	if ( param == "end" ) {
		cfg.lastFrame = FrameID(std::stoll( String(value) ));
		return true;
	}

	RETURN_ERR( "unknown parameter for --cfg-vk-cpp: \""s << param << '"' );
}

/*
=================================================
	ParseAdditionalConfig
=================================================
*/
static bool ParseAdditionalConfig (const int argc, const char** argv, StringView cfgName, INOUT int &i, INOUT ConverterConfig &config)
{
	using ParserFn_t = std::function< bool (StringView, StringView, ConverterConfig &) >;

	const Pair< String, ParserFn_t>	 cfg_parsers[] = {
		{ "--cfg-vk-cpp",			&ParseVkCppConfig },
		{ "--cfg-vez-cpp",			[] (StringView, StringView, ConverterConfig &) { return false; } },
		{ "--cfg-fg-cpp",			[] (StringView, StringView, ConverterConfig &) { return false; } },
		{ "--cfg-gl-cpp",			[] (StringView, StringView, ConverterConfig &) { return false; } },
		{ "--cfg-graphviz",			[] (StringView, StringView, ConverterConfig &) { return false; } },
		{ " --cfg-screenshot",		[] (StringView, StringView, ConverterConfig &) { return false; } },
		{ "--cfg-rem-redundant",	[] (StringView, StringView, ConverterConfig &) { return false; } },
		{ "--cfg-opt-renderpass",	[] (StringView, StringView, ConverterConfig &) { return false; } },
		{ "--cfg-opt-dedicated",	[] (StringView, StringView, ConverterConfig &) { return false; } },
		{ "--cfg-opt-mem",			[] (StringView, StringView, ConverterConfig &) { return false; } },
		{ "--cfg-opt-barrier",		[] (StringView, StringView, ConverterConfig &) { return false; } },
		{ "--cfg-gpu-bench",		[] (StringView, StringView, ConverterConfig &) { return false; } },
		{ "--cfg-cpu-bench",		[] (StringView, StringView, ConverterConfig &) { return false; } }
	};

	ParserFn_t	func;

	for (auto& parser : cfg_parsers) {
		if ( parser.first == cfgName ) {
			func = parser.second;
			break;
		}
	}

	if ( not func )
		RETURN_ERR( "unknown config name: \""s << cfgName << '"' );


	for (; i < argc; ++i)
	{
		StringView	name	= argv[i];
		StringView	value;
		size_t		pos		= name.find( '=' );

		if ( name.length() > 0 and name[0] == '-' )
			return true;
		
		if ( pos != size_t(-1) )
		{
			value = name.substr( pos+1 );
			name = name.substr( 0, pos );
		}

		if ( func( name, value, config ) )
			continue;

		FG_LOGE( "unknown config name: \""s << name << '"' );
	}
	return true;
}

/*
=================================================
	main
=================================================
*/
int main (int argc, const char** argv)
{
	ConverterConfig		config;
	AppTrace			app_trace;
	String				filename;

	// test
	#if 1
		const char*	test_commands[] = {
			"TODO: path to exe",
			"--convert",	"vk-cpp",
			"--cfg-vk-cpp",	"end=4",
			#if 0
				"--open",		R"(D:\VkTraceOutput\doom1.vktrace)",
				"--output-dir",	R"(D:\VkTraceOutput\converted\doom1)",
			#elif 1
				"--open",		R"(D:\VkTraceOutput\multithreading_1.vktrace)",
				"--output-dir",	R"(D:\VkTraceOutput\converted\multithreading)",
			#elif 0
				"--open",		R"(D:\VkTraceOutput\dota2_1.vktrace)",
				"--output-dir",	R"(D:\VkTraceOutput\converted\dota2)",
			#endif
		};
		argv = test_commands;
		argc = int(std::size( test_commands ));
	#endif


	// parse arguments
	for (int i = 1; i < argc; ++i)
	{
		StringView	curr = argv[i];

		// 'open vktrace' command
		if ( curr == "-o" or curr == "--open" )
		{
			CHECK_ERR( i+1 < argc, -100 );

			filename = argv[++i];
			continue;
		}

		// 'set output directory' command
		if ( curr == "-d" or curr == "--output-dir" )
		{
			CHECK_ERR( i+1 < argc, -101 );

			config.directory = argv[++i];
			continue;
		}

		// 'add converter' command
		if ( curr == "-c" or curr == "--convert" )
		{
			CHECK( ParseConverters( argc, argv, INOUT ++i, INOUT config.conveters ));
			--i;
			continue;
		}

		// 'add extension pass' command
		if ( curr == "-e" or curr == "--extension" )
		{
			CHECK( ParseExtensionPasses( argc, argv, INOUT ++i, INOUT config.passes ));
			--i;
			continue;
		}

		// additional configs
		if ( curr.length() > 5 and
			 curr[0] == '-' and curr[1] == '-' and curr[2] == 'c' and curr[3] == 'f' and curr[4] == 'g' )
		{
			CHECK( ParseAdditionalConfig( argc, argv, curr, INOUT ++i, INOUT config ));
			--i;
			continue;
		}

		// show help
		if ( curr == "-h" or curr == "--help" )
		{
            std::cout << s_Help << std::endl;
			return 0;
		}

		RETURN_ERR( "unknown command \""s << curr << "\", see help with command -h or --help", -102 );
	}

	// TODO: validate
	//if ( exists_converters == EConverterType::Unknown )
	//	RETURN_ERR( "converters is not defined!", -110 );


	// create resource data writer
	IResourceDataWriterPtr	data_writer;
	{
		namespace fs = std::filesystem;

		fs::path	path = fs::absolute(fs::path{ config.directory });

		if ( not fs::exists( path ) ) {
			CHECK_ERR( fs::create_directories( path ), -111 );
		}

		path.append( "data" );
		if ( not fs::exists( path ) ) {
			CHECK_ERR( fs::create_directories( path ), -112 );
		}

		data_writer.reset( new ResourceDataWriter() );
		
		path.append( "resources.bin" );
		CHECK_ERR( data_writer->Create( path.string() ), -113 );
	}


	// initialize tracer
	app_trace.AddAnalyzer(AnalyzerPtr{ new SwapchainAnalyzer() });
	app_trace.AddAnalyzer(AnalyzerPtr{ new ImageUsageAnalyzer() });
	app_trace.AddAnalyzer(AnalyzerPtr{ new AllResourcesBookmarks() });
	app_trace.AddAnalyzer(AnalyzerPtr{ new DeviceAnalyzer() });


	// load vktrace
	CHECK_ERR( app_trace.Open( filename ), -120 );


	// run converters
	if ( config.conveters.cppRawVulkan.isEnabled )
	{
		CHECK_ERR( RunConverter_CppRawVulkan( app_trace, config ));
	}

	return 0;
}
