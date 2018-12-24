// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'
/*
	Converts vktrace to vtcTrace with FrameGraph API calls.
*/

#pragma once

#include "Analyzer/Default/BufferAnalyzer.h"
#include "Analyzer/Default/MemoryObjAnalyzer.h"
#include "Analyzer/Default/MemoryTransferAnalyzer.h"
#include "Analyzer/Default/RenderPassAnalyzer.h"

#include "Converters/Utils/TraceConverterBase.h"
#include "Converters/Converter.h"

#include "framegraph/Public/FrameGraphDrawTask.h"
#include "framegraph/Public/FrameGraphTask.h"

namespace VTC
{

	//
	// Frame Graph Converter
	//

	class FrameGraphConverter final : public TraceConverterBase
	{
	// types
	public:
		class DrawCallConverter;
		class PipelineConverter;
		class SamplerConverter;
		class ImageConverter;
		class BufferConverter;

		using Config_t	= ConverterConfig::FrameGraphTrace;


	// variables
	private:
		const Config_t						_config;

		const fs::path						_directory;
		const fs::path						_dataDir;
		const String						_inputFile;

		const String						_fileName;
		
		Ptr< BufferAnalyzer const>			_bufferAnalyzer;
		Ptr< MemoryObjAnalyzer const>		_memoryObjAnalyzer;
		Ptr< MemoryTransferAnalyzer const>	_memTransferAnalyzer;
		Ptr< RenderPassAnalyzer const>		_renderPassAnalyzer;

		UniquePtr< DrawCallConverter >		_drawCallConv;
		UniquePtr< PipelineConverter >		_pipelineConv;
		UniquePtr< SamplerConverter >		_samplerConv;
		UniquePtr< ImageConverter >			_imageConv;
		UniquePtr< BufferConverter >		_bufferConv;
		
		uint64_t							_lastUpdateTime		= 0;	// nanoseconds

		UniquePtr<TracePacker>				_tracePacker;
		UniquePtr<TracePacker>				_tempPacker;


	// methods
	public:
		FrameGraphConverter (const ConverterConfig &cfg);

		bool Run (const AppTrace &trace);


	private:
		bool _ConvertFunction (const TraceRange::Iterator &iter, FrameID frameId);
		
		bool _AfterConverting ();
		
		void _InitializeResources (INOUT TracePacker &packer) const;
		void _PackCreateThreads (INOUT TracePacker &packer) const;

		bool _OnBeginFrame (TraceRange::Bookmark, FrameID, INOUT TracePacker &packer) const;
		bool _OnEndFrame (uint64_t dt, INOUT TracePacker &packer) const;
	};


}	// VTC
