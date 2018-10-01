// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Parser/TraceRange.h"
#include <typeindex>

namespace VTC
{

	//
	// Analyzer interface
	//

	class IAnalyzer
	{
	public:
		virtual ~IAnalyzer () {}

		// called once before reading packets
		virtual void PreProcess (const class AppTrace &) = 0;

		// called on each packet
		virtual void Process (const TraceRange::Iterator &) = 0;

		// called once after processing all file
		virtual void PostProcess () = 0;

		// called on each direct/indirect access to resource
		virtual void AddResourceUsage (const TraceRange::Iterator &, EResourceType, ResourceID, FrameID, EResOp) = 0;

		ND_ virtual std::type_index  GetType () const = 0;

		ND_ virtual String  Report () const = 0;
	};


	using AnalyzerPtr	= UniquePtr< IAnalyzer >;


}	// VTC
