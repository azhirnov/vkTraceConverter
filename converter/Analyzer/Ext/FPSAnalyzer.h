// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Analyzer/IAnalyzer.h"

namespace VTC
{

	//
	// FPS Analyzer
	//

	class FPSAnalyzer final : public IAnalyzer
	{
	// variables
	private:
		Array<double>		_fpsHistory;
		uint64_t			_lastUpdateTime	= 0;	// nanoseconds
		uint				_updateCounter	= 0;

		double				_averageFPS		= 0.0;

		const uint64_t		_historyRate	= 10 * 1000'000'000ull;	// nanoseconds


	// methods
	public:
		FPSAnalyzer ();

		ND_ ArrayView<double>	GetFPSHistory ()	const	{ return _fpsHistory; }
		ND_ double				GetAverageFPS ()	const	{ return _averageFPS; }


	// IAnalyzer implementation
	public:
		void PreProcess (const class AppTrace &) override;
		void Process (const TraceRange::Iterator &) override;
		void PostProcess () override;
		void AddResourceUsage (const TraceRange::Iterator &, EResourceType, ResourceID, FrameID, EResOp) override {}

		std::type_index		GetType ()	const override		{ return typeid(*this); }
		String				Report ()	const override		{ return "TODO"; }
	};

}	// VTC
