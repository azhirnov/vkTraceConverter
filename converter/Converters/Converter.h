// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Converters/ConverterConfig.h"
#include "Parser/AppTrace.h"

namespace VTC
{

	//bool RunDataConverter (const AppTrace &trace, const ConverterConfig &config, const ResourceDataWriterPtr &writer);
	bool RunConverter_VulkanCppSource (const AppTrace &trace, const ConverterConfig &config);
	bool RunConverter_VulkanPlayer (const AppTrace &trace, const ConverterConfig &config);
	//bool RunConverter_VulkanEZPlayer (const AppTrace &trace, const ConverterConfig &config);
	//bool RunConverter_FrameGraphPlayer (const AppTrace &trace, const ConverterConfig &config);
	//bool RunConverter_OpenGLPlayer (const AppTrace &trace, const ConverterConfig &config);
	bool RunConverter_GraphViz (const AppTrace &trace, const ConverterConfig &config);

}	// VTC
