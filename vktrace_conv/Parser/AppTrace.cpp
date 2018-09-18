// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Parser/AppTrace.h"

namespace VTC
{
	
/*
=================================================
	AddAnalyzer
=================================================
*/
	void AppTrace::AddAnalyzer (AnalyzerPtr &&value)
	{
		ASSERT( _fullTrace.empty() );	// trace already processed, new analyzer never be used

		_analyzers.push_back( std::move(value) );
	}
	
/*
=================================================
	GetAnalyzer
=================================================
*/
	IAnalyzer const*  AppTrace::GetAnalyzer (std::type_index id) const
	{
		for (auto& analyzer : _analyzers)
		{
			if ( analyzer->GetType() == id )
				return analyzer.get();
		}
		return null;
	}

/*
=================================================
	GetFrameTrace
=================================================
*/
	TraceRange  AppTrace::GetFrameTrace (FrameID id) const
	{
		CHECK_ERR( id < _presentBookmarks.size() );

		if ( id == 0 )
			return _fullTrace.SubRange( _fullTrace.FirstBookmark(), _presentBookmarks.front() );

		return _fullTrace.SubRange( _presentBookmarks[id-1], _presentBookmarks[id] );
	}

/*
=================================================
	Open
=================================================
*/
	bool AppTrace::Open (StringView filename)
	{
		Close();
		FG_TIMEPROFILER();

		_traceFile.reset( new HddRFile{ filename });
		CHECK_ERR( _traceFile->IsOpen() );

		return _ProcessTrace();
	}

	bool AppTrace::Open (const fs::path &path)
	{
		Close();
		FG_TIMEPROFILER();
		
		_traceFile.reset( new HddRFile{ path });
		CHECK_ERR( _traceFile->IsOpen() );

		return _ProcessTrace();
	}
	
/*
=================================================
	_ProcessTrace
=================================================
*/
	bool AppTrace::_ProcessTrace ()
	{
		CHECK_ERR( _traceFile->Read( OUT _fileHeader ));
		CHECK_ERR( _traceFile->Read( _fileHeader.n_gpuinfo, _gpuInfo ));
		
		//if ( _fileHeader.portability_table_valid )
		//	_fileHeader.portability_table_valid = _ReadPortabilityTable();

		_fullTrace = TraceRange{ _traceFile };

		CHECK_ERR( _ParseFullTrace() );
		return true;
	}
	
/*
=================================================
	Close
=================================================
*/
	void AppTrace::Close ()
	{
		_fullTrace	= Default;
		_traceFile	= null;

		_fileHeader	= Default;
		_gpuInfo.clear();
		_portabilityTable.clear();

		_presentBookmarks.clear();
	}
	
/*
=================================================
	_ReadPortabilityTable
----
	copied from readPortabilityTable() in vkreplay_main.cpp
=================================================
*
	bool AppTrace::_ReadPortabilityTable ()
	{
		uint64_t table_size			= 0;
		uint64_t original_file_pos	= vktrace_FileLike_GetCurrentPosition( _traceFile );

		if ( not vktrace_FileLike_SetCurrentPosition( _traceFile, _traceFile->mFileLen - sizeof(uint64_t) ) )
			return false;

		if ( not vktrace_FileLike_ReadRaw( _traceFile, OUT &table_size, sizeof(table_size) ) )
			return false;

		if ( table_size != 0 )
		{
			if ( not vktrace_FileLike_SetCurrentPosition( _traceFile, _traceFile->mFileLen - ((table_size + 1) * sizeof(uint64_t)) ) )
		        return false;

			_portabilityTable.resize( size_t(table_size) );

			CHECK_ERR( vktrace_FileLike_ReadRaw( _traceFile, _portabilityTable.data(), size_t(ArraySizeOf(_portabilityTable)) ));
		}

		if ( not vktrace_FileLike_SetCurrentPosition( _traceFile, original_file_pos ) )
			return false;

		return true;
	}
	
/*
=================================================
	_ParseFullTrace
----
	this is first trace processing pass,
	run analyzers for each packet,
	bookmark all resource usage
=================================================
*/
	bool AppTrace::_ParseFullTrace ()
	{
		FrameID		frame_id	= 0;
		bool		new_frame	= false;
		
		// pre processing
		for (auto& analyzer : _analyzers) {
			analyzer->PreProcess( *this );
		}

		for (auto iter = _fullTrace.begin(); iter < _fullTrace.LastBookmark(); ++iter)
		{
			ASSERT( iter->tracer_id == VKTRACE_TID_VULKAN );

			_uniqueThreads.insert( iter->thread_id );

			// add bookmark to next frame
			if ( new_frame )
			{
				ASSERT( frame_id != ~FrameID(0) );
				++frame_id;

				_presentBookmarks.push_back( iter.GetBookmark() );
				new_frame = false;
			}

			// analyze before bookmarking
			for (auto& analyzer : _analyzers)
			{
				analyzer->Process( iter );
			}

			// search in function arguments and struct data to find vulkan resource usage and add bookmarks
#			include "Generated/BuildFunctionResourceBookmarks.h"


			// divide by frames
			switch ( iter->packet_id )
			{
				case VKTRACE_TPI_VK_vkQueuePresentKHR :
					new_frame = true;
					break;
			}
		}
		
		// post processing
		for (auto& analyzer : _analyzers) {
			analyzer->PostProcess();
		}

		FG_LOGI( "total frames: "s << ToString(_presentBookmarks.size()) );
		FG_LOGI( "unique threads: "s << ToString(_uniqueThreads.size()) );
		return true;
	}
	
/*
=================================================
	_AddStructBookmsrks
=================================================
*/
	void AppTrace::_AddStructBookmsrks (const VkBaseInStructure *header, const Iterator &iter, FrameID frame_id)
	{
#		include "Generated/BuildStructResourceBookmarks.h"
	}


}	// VTC
