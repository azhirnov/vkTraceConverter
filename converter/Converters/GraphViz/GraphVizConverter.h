// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'
/*
	Converts vktrace to graphs.

	docs: https://graphviz.gitlab.io/_pages/pdf/dotguide.pdf
*/

#pragma once

#include "Converters/Converter.h"
#include "Analyzer/Ext/SynchronizationsAnalyzer.h"

namespace VTC
{

	//
	// GraphViz Converter
	//

	class GraphVizConverter
	{
	// types
	private:
		using Config_t	= ConverterConfig::GraphViz;


	// variables
	private:
		const Config_t						_config;
		const fs::path						_directory;

		SynchronizationsAnalyzer const*		_syncAnalyzer	= null;


	// methods
	public:
		GraphVizConverter (const ConverterConfig &cfg);

		bool Run (const AppTrace &trace);


	private:
		bool _ConvertSyncGraph (FrameID first, FrameID last, const AppTrace &trace) const;

		bool _StoreFile (const fs::path &filename, StringView data) const;
		bool _Visualize (const fs::path &filename, StringView format = "png") const;
	};


}	// VTC
