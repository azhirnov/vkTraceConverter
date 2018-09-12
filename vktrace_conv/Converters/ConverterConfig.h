// Copyright (c)  Zhirnov Andrey. For more information see 'LICENSE.txt'

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
		struct CppRawVulkan
		{
			bool		isEnabled			= false;
			//bool		isMultithreaded		= false;
			//bool		isAsyncLoadEnabled	= false;
			FrameID		firstFrame			= 0;
			FrameID		lastFrame			= ~FrameID(0);
		};


		struct CppVulkanEZ
		{
			bool		isEnabled		= false;
		};


		struct CppRawOpenGL
		{
			bool		isEnabled		= false;
		};


		struct CppFrameGraph
		{
			bool		isEnabled		= false;
		};


		struct GraphViz
		{
			bool		isEnabled		= false;
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
			CppRawVulkan			cppRawVulkan;
			CppVulkanEZ				cppVulkanEZ;
			CppRawOpenGL			cppRawOpenGL;
			CppFrameGraph			cppFrameGraph;
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

		String					directory;
	};


}	// VTC
