// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "VkTraceCommon.h"

namespace VTC
{

	//
	// Converter Config
	//

	struct ConverterConfig
	{
	// converters:
		struct VulkanCppSource
		{
			bool		isEnabled				= false;
			//bool		isMultithreaded			= false;
			//bool		isAsyncLoadEnabled		= false;
			bool		remapMemory				= false;
			bool		remapQueueFamily		= false;
			bool		useUniqueResourceIndices= false;

			bool		divideByThreads			= false;
			bool		divideByPasses			= false;

			FrameID		firstFrame				= 0;
			FrameID		lastFrame				= ~FrameID(0);
		};
		

		struct VulkanTrace
		{
			bool		isEnabled				= false;
			bool		remapMemory				= false;
			bool		remapQueueFamily		= false;
			bool		indirectSwapchain		= false;
			bool		useUniqueResourceIndices= false;
			FrameID		lastFrame				= ~FrameID(0);
		};


		struct VulkanEZTrace
		{
			bool		isEnabled		= false;
		};


		struct FrameGraphTrace
		{
			bool		isEnabled				= false;
			FrameID		lastFrame				= ~FrameID(0);
		};


		struct GraphViz
		{
			bool		isEnabled		= false;
			bool		showSync		= false;	// build sync usage graph
			FrameID		firstFrame		= 0;
			FrameID		lastFrame		= ~FrameID(0);
		};


	// config:
		struct Converters {
			VulkanCppSource			vulkanCppSource;
			VulkanTrace				vulkanTrace;
			VulkanEZTrace			vulkanEZTrace;
			FrameGraphTrace			frameGraphTrace;
			GraphViz				graphviz;
		}						conveters;

		String					inputTraceFile;
		String					outputDirectory;
	};


}	// VTC
