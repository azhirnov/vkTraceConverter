// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Converters/ConverterConfig.h"
#include "Parser/AppTrace.h"

namespace VTC
{

	bool RunConverter_VulkanCppSource (const AppTrace &trace, const ConverterConfig &config);
	//bool RunConverter_VulkanPlayer (const AppTrace &trace, const ConverterConfig &config);
	//bool RunConverter_VulkanEZPlayer (const AppTrace &trace, EOptimizationPass passes, EBenchmarkType benchmark);
	//bool RunConverter_FrameGraphPlayer (const AppTrace &trace, EOptimizationPass passes, EBenchmarkType benchmark);
	//bool RunConverter_OpenGLPlayer (const AppTrace &trace, EOptimizationPass passes, EBenchmarkType benchmark);
	//bool RunConverter_GraphViz (const AppTrace &trace, EOptimizationPass passes, EBenchmarkType benchmark);

}	// VTC
