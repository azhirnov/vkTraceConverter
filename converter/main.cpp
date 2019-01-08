// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Parser/AppTrace.h"
#include "Converters/Converter.h"
#include "Converters/Data/ResourceDataManager.h"

#include "Analyzer/Default/ImageAnalyzer.h"
#include "Analyzer/Default/BufferAnalyzer.h"
#include "Analyzer/Default/MemoryObjAnalyzer.h"
#include "Analyzer/Default/RenderPassAnalyzer.h"
#include "Analyzer/Default/SwapchainAnalyzer.h"
#include "Analyzer/Default/DeviceAnalyzer.h"
#include "Analyzer/Default/QueueAnalyzer.h"
#include "Analyzer/Default/MemoryTransferAnalyzer.h"
#include "Analyzer/Default/AllResourcesBookmarks.h"
#include "Analyzer/Ext/ExtensionAnalyzer.h"
#include "Analyzer/Ext/SynchronizationsAnalyzer.h"
#include "Analyzer/Ext/FPSAnalyzer.h"

#include <iostream>

using namespace VTC;

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
					vk-cpp		-- converts to c++ source with raw vulkan api calls (very large source files!).
					vk-trace	-- converts to vulkan trace file.
					vez-trace	-- converts to vulkan-ez trace file (WIP).
					fg-trace	-- converts to framegraph trace file (WIP).
					graphviz	-- converts to dot file.
					all			-- enable all converters.

--cfg-vk-cpp		configure 'vk-cpp' converter:
						multithreaded=[true/false] -- enable/disable multithread submiting to queue.
						async-load=[true/false] -- enable/disable async data loading.
						begin=[N] -- start converting on N frame, default is 0.
						end=[N] -- stop converting on N frame, default is -1.
						remap-mem=[true/false] -- enable this for portability.
						remap-queue=[true/false] -- enable this for portability.

--cfg-vk-trace		configure 'vk-trace' converter:
						end=[N] -- stop converting on N frame, default is -1.
						remap-mem=[true/false] -- enable this for portability.
						remap-queue=[true/false] -- enable this for portability.
						indirect-swapchain=[true/false] -- enable this for portability.

--cfg-vez-trace		configure 'vez-trace' converter:

--cfg-fg-trace		configure 'fg-trace' converter:
						end=[N] -- stop converting on N frame, default is -1.
						force-dbo=[true/false] -- always use dynamic offset for UBO and SSBO.

--cfg-graphviz		configure 'graphviz' converter:
						begin=[N] -- start converting on N frame, default is 0.
						end=[N] -- stop converting on N frame, default is -1.
						show-sync=[true/false] -- show/hide barriers, events, semaphores, fences, subpass dependencies.
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

		if ( name == "vk-cpp" or name == "all" )		{ config.vulkanCppSource.isEnabled = true;	match = true; }
		if ( name == "vk-trace" or name == "all" )		{ config.vulkanTrace.isEnabled = true;  	match = true; }
		if ( name == "vez-trace" or name == "all" )		{ config.vulkanEZTrace.isEnabled = true;	match = true; }
		if ( name == "fg-trace" or name == "all" )		{ config.frameGraphTrace.isEnabled = true;	match = true; }
		if ( name == "graphviz" or name == "all" )		{ config.graphviz.isEnabled = true;			match = true; }

		if ( not match ) {
			FG_LOGE( "unknown converter type: \""s << name << '"' );
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
	auto&	cfg = mainConfig.conveters.vulkanCppSource;

	if ( param == "begin" )				{ cfg.firstFrame = FrameID(std::stoll( String(value) ));			return true; }
	if ( param == "end" )				{ cfg.lastFrame = FrameID(std::stoll( String(value) ));				return true; }
	if ( param == "remap-mem" )			{ cfg.remapMemory = (value.empty() or value == "true");				return true; }
	if ( param == "remap-queue" )		{ cfg.remapQueueFamily = (value.empty() or value == "true");		return true; }
	if ( param == "multithreaded" )		{ /*cfg.isMultithreaded = (value.empty() or value == "true");*/		return true; }
	if ( param == "async-load" )		{ /*cfg.isAsyncLoadEnabled = (value.empty() or value == "true");*/	return true; }
	if ( param == "divide-by-threads" )	{ cfg.divideByThreads = (value.empty() or value == "true");			return true; }
	if ( param == "divide-by-passes" )	{ cfg.divideByPasses = (value.empty() or value == "true");			return true; }

	RETURN_ERR( "unknown parameter for --cfg-vk-cpp: \""s << param << '"' );
}

/*
=================================================
	ParseVkTraceConfig
=================================================
*/
static bool ParseVkTraceConfig (StringView param, StringView value, INOUT ConverterConfig &mainConfig)
{
	auto&	cfg = mainConfig.conveters.vulkanTrace;

	if ( param == "end" )				{ cfg.lastFrame = FrameID(std::stoll( String(value) ));				return true; }
	if ( param == "remap-mem" )			{ cfg.remapMemory = (value.empty() or value == "true");				return true; }
	if ( param == "remap-queue" )		{ cfg.remapQueueFamily = (value.empty() or value == "true");		return true; }
	if ( param == "indirect-swapchain" ){ cfg.indirectSwapchain = (value.empty() or value == "true");		return true; }
	if ( param == "multithreaded" )		{ /*cfg.isMultithreaded = (value.empty() or value == "true");*/		return true; }
	if ( param == "async-load" )		{ /*cfg.isAsyncLoadEnabled = (value.empty() or value == "true");*/	return true; }

	RETURN_ERR( "unknown parameter for --cfg-vk-trace: \""s << param << '"' );
}

/*
=================================================
	ParseFgTraceConfig
=================================================
*/
static bool ParseFgTraceConfig (StringView param, StringView value, INOUT ConverterConfig &mainConfig)
{
	auto&	cfg = mainConfig.conveters.frameGraphTrace;

	if ( param == "end" )				{ cfg.lastFrame = FrameID(std::stoll( String(value) ));				return true; }
	if ( param == "force-dbo" )			{ cfg.forceDBO = (value.empty() or value == "true");				return true; }

	RETURN_ERR( "unknown parameter for --cfg-fg-trace: \""s << param << '"' );
}

/*
=================================================
	ParseGraphVizConfig
=================================================
*/
static bool ParseGraphVizConfig (StringView param, StringView value, INOUT ConverterConfig &mainConfig)
{
	auto&	cfg = mainConfig.conveters.graphviz;
	
	if ( param == "begin" )				{ cfg.firstFrame = FrameID(std::stoll( String(value) ));	return true; }
	if ( param == "end" )				{ cfg.lastFrame = FrameID(std::stoll( String(value) ));		return true; }
	if ( param == "show-sync" )			{ cfg.showSync = (value.empty() or value == "true");		return true; }

	RETURN_ERR( "unknown parameter for --cfg-graphviz: \""s << param << '"' );
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
		{ "--cfg-vk-trace",			&ParseVkTraceConfig },
		{ "--cfg-vez-trace",		[] (StringView, StringView, ConverterConfig &) { return false; } },
		{ "--cfg-fg-trace",			&ParseFgTraceConfig },
		{ "--cfg-graphviz",			&ParseGraphVizConfig },
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



	// parse arguments
	for (int i = 1; i < argc; ++i)
	{
		StringView	curr = argv[i];

		// 'open vktrace' command
		if ( curr == "-o" or curr == "--open" )
		{
			CHECK_ERR( i+1 < argc, -100 );

			config.inputTraceFile = argv[++i];
			continue;
		}

		// 'set output directory' command
		if ( curr == "-d" or curr == "--output-dir" )
		{
			CHECK_ERR( i+1 < argc, -101 );

			config.outputDirectory = argv[++i];
			continue;
		}

		// 'add converter' command
		if ( curr == "-c" or curr == "--convert" )
		{
			CHECK( ParseConverters( argc, argv, INOUT ++i, INOUT config.conveters ));
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


	// initialize tracer
	AppTrace	app_trace;
	app_trace.AddAnalyzer(AnalyzerPtr{ new AllResourcesBookmarks() });
	app_trace.AddAnalyzer(AnalyzerPtr{ new DeviceAnalyzer() });
	app_trace.AddAnalyzer(AnalyzerPtr{ new QueueAnalyzer() });
	app_trace.AddAnalyzer(AnalyzerPtr{ new SwapchainAnalyzer() });
	app_trace.AddAnalyzer(AnalyzerPtr{ new ImageAnalyzer() });
	app_trace.AddAnalyzer(AnalyzerPtr{ new BufferAnalyzer() });
	app_trace.AddAnalyzer(AnalyzerPtr{ new MemoryObjAnalyzer() });
	app_trace.AddAnalyzer(AnalyzerPtr{ new RenderPassAnalyzer() });
	app_trace.AddAnalyzer(AnalyzerPtr{ new MemoryTransferAnalyzer() });
	//app_trace.AddAnalyzer(AnalyzerPtr{ new SynchronizationsAnalyzer( 3101, 3104 ) });
	app_trace.AddAnalyzer(AnalyzerPtr{ new FPSAnalyzer() });
	app_trace.AddAnalyzer(AnalyzerPtr{ new ExtensionAnalyzer() });

	// load vktrace
	CHECK_ERR( app_trace.Open( StringView(config.inputTraceFile) ), -120 );


	// run converters
	if ( config.conveters.vulkanCppSource.isEnabled )	CHECK_ERR( RunConverter_VulkanCppSource( app_trace, config ), -130 );
	if ( config.conveters.vulkanTrace.isEnabled )		CHECK_ERR( RunConverter_VulkanPlayer( app_trace, config ), -131 );
	if ( config.conveters.graphviz.isEnabled )			CHECK_ERR( RunConverter_GraphViz( app_trace, config ), -132 );
	if ( config.conveters.frameGraphTrace.isEnabled )	CHECK_ERR( RunConverter_FrameGraph( app_trace, config ), -133 );

	return 0;
}
