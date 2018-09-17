// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Converters/ConverterConfig.h"
#include "Parser/AppTrace.h"

namespace VTC
{

	bool RunConverter_CppRawVulkan (const AppTrace &trace, const ConverterConfig &config);
	//bool RunConverter_CppVulkanEZ (const AppTrace &trace, EOptimizationPass passes, EBenchmarkType benchmark);
	//bool RunConverter_CppFrameGraph (const AppTrace &trace, EOptimizationPass passes, EBenchmarkType benchmark);
	//bool RunConverter_CppOpenGL (const AppTrace &trace, EOptimizationPass passes, EBenchmarkType benchmark);
	//bool RunConverter_GraphViz (const AppTrace &trace, EOptimizationPass passes, EBenchmarkType benchmark);

}	// VTC
