// Copyright (c)  Zhirnov Andrey. For more information see 'LICENSE.txt'

#include "Parser/AppTrace.h"

namespace VTC
{

/*
=================================================
	constructor
=================================================
*/
	AppTrace::AppTrace ()
	{
	}
	
/*
=================================================
	destructor
=================================================
*/
	AppTrace::~AppTrace ()
	{
		Close();
	}
	
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
			return _fullTrace.SubRange( _fullTrace.begin(), _fullTrace.Get(_presentBookmarks.front()) );

		return _fullTrace.SubRange( _fullTrace.Get(_presentBookmarks[id-1]), _fullTrace.Get(_presentBookmarks[id]) );
	}

/*
=================================================
	Open
=================================================
*/
	bool AppTrace::Open (StringView filename)
	{
		Close();
		
		FILE*	file = null;
		CHECK( fopen_s( OUT &file, filename.data(), "rb" ) == 0 );

		_traceFile	= vktrace_FileLike_create_file( file );
		
		CHECK_ERR( vktrace_FileLike_ReadRaw( _traceFile, &_fileHeader, sizeof(_fileHeader) ));
		_gpuInfo.resize( _fileHeader.n_gpuinfo );

		CHECK_ERR( vktrace_FileLike_ReadRaw( _traceFile, _gpuInfo.data(), size_t(ArraySizeOf(_gpuInfo)) ));
		
		if ( _fileHeader.portability_table_valid )
			_fileHeader.portability_table_valid = _ReadPortabilityTable();

		_fullTrace = TraceRange{ _traceFile };

		CHECK_ERR( _ParseFullTrace() );
		
		// post processing
		for (auto& analyzer : _analyzers) {
			analyzer->PostProcess();
		}
		return true;
	}
	
/*
=================================================
	Close
=================================================
*/
	void AppTrace::Close ()
	{
		if ( _traceFile )
		{
			if ( _traceFile->mFile )
				fclose( _traceFile->mFile );
			
			vktrace_free( _traceFile );
		}

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
*/
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
	create bookmarks for all resources
=================================================
*/
	bool AppTrace::_ParseFullTrace ()
	{
		FrameID		frame_id = 0;

		for (auto iter = _fullTrace.begin(), end = _fullTrace.end();
			 iter < end;
			 ++iter)
		{
			ASSERT( iter->tracer_id == VKTRACE_TID_VULKAN );

			_uniqueThreads.insert( iter->thread_id );

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
				case VKTRACE_TPI_VK_vkQueuePresentKHR : {
					_presentBookmarks.push_back( iter.GetBookmark() );
					
					ASSERT( frame_id != ~FrameID(0) );
					++frame_id;
					break;
				}
			}
		}

		FG_LOGI( "total frames: " + ToString(frame_id) );
		return true;
	}
	
/*
=================================================
	_AddStructBookmsrks
=================================================
*/
	bool AppTrace::_AddStructBookmsrks (const VkBaseInStructure *header, const Iterator &iter, FrameID frame_id)
	{
#		include "Generated/BuildStructResourceBookmarks.h"
		return true;
	}

/*
=================================================
	_AddResourceBookmark
=================================================
*/
	bool AppTrace::_AddResourceBookmark (EResourceType type, ResourceID id, const Iterator &pos, FrameID frameId)
	{
		if ( id == 0 )
			return true;

		for (auto& analyzer : _analyzers)
		{
			analyzer->AddResourceUsage( pos, type, id, frameId );
		}
		return true;
	}


}	// VTC
