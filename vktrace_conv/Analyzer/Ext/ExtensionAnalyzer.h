// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Analyzer/IAnalyzer.h"

namespace VTC
{

	//
	// Extension Analyzer
	//

	class ExtensionAnalyzer final : public IAnalyzer
	{
	// variables
	private:
		HashSet<String>		_deviceExtensions;
		HashSet<String>		_instanceExtensions;
		int					_minVersion				= 0;


	// methods
	public:
		ExtensionAnalyzer ();


	// IAnalyzer implementation
	public:
		void PreProcess (const class AppTrace &) override {}
		void Process (const TraceRange::Iterator &) override;
		void PostProcess () override {}
		void AddResourceUsage (const TraceRange::Iterator &, EResourceType, ResourceID, FrameID, EResOp) override {}

		std::type_index		GetType ()	const override		{ return typeid(*this); }
		String				Report ()	const override		{ return "TODO"; }
	};


}	// VTC
