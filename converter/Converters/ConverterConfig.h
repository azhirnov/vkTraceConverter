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


		struct OpenGLTrace
		{
			bool		isEnabled		= false;
		};


		struct FrameGraphTrace
		{
			bool		isEnabled		= false;
		};


		struct GraphViz
		{
			bool		isEnabled		= false;
			bool		showSync		= false;	// build sync usage graph
			FrameID		firstFrame		= 0;
			FrameID		lastFrame		= ~FrameID(0);
		};


		struct Screenshot
		{
			uint		frequency		= 30;		// in frames
			bool		isEnabled		= false;
		};


	// extension passes:
		struct RemoveRedundantCalls
		{
			bool		isEnabled		= false;
		};


		struct OptRenderPasses
		{
			bool		isEnabled		= false;
		};


		struct OptDedicatedAllocation
		{
			enum class EMode : uint {
				Auto,
				DisableAll,
				EnableAll,
				EnableForRT,
			};

			uint64_t	minLimit		= 0;
			EMode		mode			= EMode::Auto;
			bool		isEnabled		= false;
		};


		struct OptMemoryAllocation
		{
			bool		isEnabled		= false;
		};


		struct OptPipelineBarriers
		{
			bool		isEnabled		= false;
		};


		struct GpuBenchmark
		{
			bool		isEnabled		= false;
		};


		struct CpuBenchmark
		{
			bool		isEnabled		= false;
		};


	// config:
		struct Converters {
			VulkanCppSource			vulkanCppSource;
			VulkanTrace				vulkanTrace;
			VulkanEZTrace			vulkanEZTrace;
			OpenGLTrace				openGLTrace;
			FrameGraphTrace			frameGraphTrace;
			GraphViz				graphviz;
			Screenshot				screenshot;
		}						conveters;

		struct ExtensionPasses {
			RemoveRedundantCalls	remRedundant;
			OptRenderPasses			optRenderpass;
			OptDedicatedAllocation	optDedicated;
			OptMemoryAllocation		optMemory;
			OptPipelineBarriers		optBarrier;
			GpuBenchmark			gpuBench;
			CpuBenchmark			cpuBench;
		}						passes;

		String					inputTraceFile;
		String					outputDirectory;
	};


}	// VTC
