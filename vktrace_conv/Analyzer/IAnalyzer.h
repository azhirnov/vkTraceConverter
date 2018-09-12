// Copyright (c)  Zhirnov Andrey. For more information see 'LICENSE.txt'

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

		virtual void Process (const TraceRange::Iterator &) = 0;

		virtual void PostProcess () = 0;

		virtual void AddResourceUsage (const TraceRange::Iterator &, EResourceType, ResourceID, FrameID) = 0;

		ND_ virtual std::type_index  GetType () const = 0;

		ND_ virtual String  Report () const = 0;
	};


	using AnalyzerPtr	= UniquePtr< IAnalyzer >;


}	// VTC
