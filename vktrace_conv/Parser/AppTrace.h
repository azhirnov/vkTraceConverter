// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Parser/TraceRange.h"
#include "Analyzer/IAnalyzer.h"

namespace VTC
{

	//
	// Application Trace
	//

	class AppTrace final
	{
	// types
	public:
		using Iterator		= TraceRange::Iterator;
		using Bookmark		= TraceRange::Bookmark;
		
	private:
		using GpuInfoArray_t	= Array< struct_gpuinfo >;
		using Bookmarks_t		= Array< Bookmark >;
		using UniqueThreads_t	= HashSet< ThreadID >;
		using Analyzers_t		= Array< AnalyzerPtr >;

		class VkObjectsTracker;


	// variables
	private:
		TraceRange					_fullTrace;		// full vktrace file
		FileLike *					_traceFile		= null;

		vktrace_trace_file_header	_fileHeader;
		GpuInfoArray_t				_gpuInfo;
		Array< uint64_t >			_portabilityTable;

		Bookmarks_t					_presentBookmarks;

		Analyzers_t					_analyzers;
		UniqueThreads_t				_uniqueThreads;

		UniquePtr<VkObjectsTracker>	_objTracker;


	// methods
	public:
		AppTrace ();
		~AppTrace ();

		void AddAnalyzer (AnalyzerPtr &&);

		bool Open (StringView filename);
		void Close ();

		ND_ TraceRange const&			FullTrace ()						const	{ return _fullTrace; }

		ND_ TraceRange					GetFrameTrace (FrameID id)			const;
		ND_ FrameID						GetFrameCount ()					const	{ return FrameID(_presentBookmarks.size()); }

		template <typename T>
		ND_ T const*					GetAnalyzer ()						const	{ return Cast<T>(GetAnalyzer( typeid(T) )); }

		ND_ IAnalyzer const*			GetAnalyzer (std::type_index id)	const;

		ND_ vktrace_trace_file_header const&	GetTraceFileHeader ()		const	{ return _fileHeader; }


	private:
		bool _ReadPortabilityTable ();
		bool _ParseFullTrace ();

		void _AddResourceBookmark (EResourceType type, ResourceID id, const Iterator &pos, FrameID frameId, EResOp op);
		void _AddStructBookmsrks (const VkBaseInStructure *header, const Iterator &pos, FrameID frameId);
	};


}	// VTC
