// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Converters/GraphViz/GraphVizConverter.h"
#include <thread>

namespace VTC
{

/*
=================================================
	RunConverter_GraphViz
=================================================
*/
	bool RunConverter_GraphViz (const AppTrace &trace, const ConverterConfig &config)
	{
		FG_TIMEPROFILER();
		FG_LOGI( "run GraphViz converter" );

		GraphVizConverter	conv{ config };

		return conv.Run( trace );
	}
	
/*
=================================================
	constructor
=================================================
*/
	GraphVizConverter::GraphVizConverter (const ConverterConfig &cfg) :
		_config{ cfg.conveters.graphviz },
		_directory{ fs::path{cfg.outputDirectory}.append("graphviz") }
	{
		if ( not fs::exists( _directory ) ) {
			CHECK( fs::create_directories( _directory ));
		}
	}
	
/*
=================================================
	Run
=================================================
*/
	bool GraphVizConverter::Run (const AppTrace &appTrace)
	{
		// initialization
		{
			_syncAnalyzer	= appTrace.GetAnalyzer< SynchronizationsAnalyzer >();

			//CHECK_ERR( _syncAnalyzer );
		}

		const FrameID	last_frame	= Min( _config.lastFrame, appTrace.GetFrameCount() );
		
		if ( _config.showSync )
			CHECK_ERR( _ConvertSyncGraph( _config.firstFrame, last_frame, appTrace ));

		return true;
	}
	
/*
=================================================
	_StoreFile
=================================================
*/
	bool GraphVizConverter::_StoreFile (const fs::path &filename, StringView data) const
	{
		FileWStream		file{ filename };
		CHECK_ERR( file.IsOpen() );
		CHECK_ERR( file.Write( data ));
		return true;
	}
	

#ifdef PLATFORM_WINDOWS
/*
=================================================
	RunExe
=================================================
*/
	static bool RunExe (StringView commands, uint timeoutMS)
	{
		char	buf[MAX_PATH] = {};
		::GetSystemDirectoryA( buf, UINT(CountOf(buf)) );
		
		String		command_line;
		command_line << '"' << buf << "\\cmd.exe\" /C " << commands;

		STARTUPINFOA			startup_info = {};
		PROCESS_INFORMATION		proc_info	 = {};
		
		bool process_created = ::CreateProcessA(
			NULL,
			command_line.data(),
			NULL,
			NULL,
			FALSE,
			CREATE_NO_WINDOW,
			NULL,
			NULL,
			OUT &startup_info,
			OUT &proc_info
		);

		if ( not process_created )
			return false;

		if ( ::WaitForSingleObject( proc_info.hThread, timeoutMS ) != WAIT_OBJECT_0 )
			return false;
		
		DWORD process_exit;
		::GetExitCodeProcess( proc_info.hProcess, OUT &process_exit );

		return true;
	}
#endif	// PLATFORM_WINDOWS

/*
=================================================
	_Visualize
=================================================
*/
	bool GraphVizConverter::_Visualize (const fs::path &filename, StringView format) const
	{
#	ifdef VTC_GRAPHVIZ_DOT_EXECUTABLE
		fs::path	output_file {filename};

		output_file.replace_extension( output_file.extension().string() << '.' << format );
	
		// delete previous version
		if ( fs::exists( output_file ) ) {
			fs::remove( output_file );
			std::this_thread::sleep_for( std::chrono::milliseconds(1) );
		}

		CHECK_ERR( RunExe( "\""s << VTC_GRAPHVIZ_DOT_EXECUTABLE << "\" -T" << format << " -O " << filename.string(), 30 * 1000 ));

		// if graph generated successfully then file must exists
		CHECK_ERR( fs::exists( output_file ));

		return true;
#	else
		return true;
#	endif
	}


}	// VTC
