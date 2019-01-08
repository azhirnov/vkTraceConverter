// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'
/*
	Converts vktrace to vtcTrace file with Vulkan API calls.
*/

#pragma once

#include "Analyzer/Default/BufferAnalyzer.h"
#include "Analyzer/Default/MemoryObjAnalyzer.h"
#include "Analyzer/Default/MemoryTransferAnalyzer.h"

#include "Converters/Utils/TraceConverterBase.h"
#include "Converters/Converter.h"


namespace VTC
{

	//
	// Vulkan Trace Converter
	//

	class VulkanTraceConverter final : public TraceConverterBase
	{
	// types
	private:
		using InitializedResources_t	= HashSet< ResourceID >;
		using Config_t					= ConverterConfig::VulkanTrace;


	// variables
	private:
		const Config_t						_config;

		const fs::path						_directory;
		const fs::path						_dataDir;
		const String						_inputFile;

		const String						_fileName;

		Ptr< BufferAnalyzer const>			_bufferAnalyzer;
		Ptr< MemoryObjAnalyzer const>		_memoryObjAnalyzer;
		Ptr< MemoryTransferAnalyzer const>	_memTransferAnalyzer;

		mutable InitializedResources_t		_initializedResources;	// used in _Remap***

		UniquePtr<TracePacker>				_tracePacker;
		
		uint64_t							_lastUpdateTime		= 0;	// nanoseconds


	// methods
	public:
		VulkanTraceConverter (const ConverterConfig &cfg);

		bool Run (const AppTrace &trace);


	private:
		bool _ConvertFunction (const TraceRange::Iterator &iter, FrameID frameId);
		bool _ConvertVkFunction (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const;

		bool _AfterConverting ();

		void _InitializeResources (INOUT TracePacker &packer) const;

		// remap queue family
		bool _OnCreateCommandPool (const TraceRange::Iterator &, INOUT TracePacker &) const;
		bool _OnCreateBuffer (const TraceRange::Iterator &, INOUT TracePacker &) const;
		bool _OnCreateImage (const TraceRange::Iterator &, INOUT TracePacker &) const;
		bool _OnWaitEvents3 (const TraceRange::Iterator &) const;
		bool _OnPipelineBarrier3 (const TraceRange::Iterator &) const;
		
		// remap swapchain images adn queue family index
		bool _OnCmdWaitEvents (const TraceRange::Iterator &, INOUT TracePacker &) const;
		bool _OnCmdPipelineBarrier (const TraceRange::Iterator &, INOUT TracePacker &) const;
		
		// remap memory
		bool _OnBindBufferMemory (const TraceRange::Iterator &, INOUT TracePacker &) const;
		bool _OnBindImageMemory (const TraceRange::Iterator &, INOUT TracePacker &) const;
		bool _OnBindBufferMemory2 (const TraceRange::Iterator &, INOUT TracePacker &) const;
		bool _OnBindImageMemory2 (const TraceRange::Iterator &, INOUT TracePacker &) const;
		bool _OnAllocateMemory (const TraceRange::Iterator &, INOUT TracePacker &) const;
		bool _OnFreeMemory (const TraceRange::Iterator &, INOUT TracePacker &) const;
		bool _OnMapMemory (const TraceRange::Iterator &, INOUT TracePacker &) const;
		bool _OnUnmapMemory (const TraceRange::Iterator &, INOUT TracePacker &) const;
		bool _OnFlushMappedMemoryRanges (const TraceRange::Iterator &, FrameID, INOUT TracePacker &);
		bool _OnDestroyImage (const TraceRange::Iterator &, INOUT TracePacker &) const;
		bool _OnDestroyBuffer (const TraceRange::Iterator &, INOUT TracePacker &) const;
		
		bool _OverrideMapMemory (const TraceRange::Iterator &, INOUT TracePacker &) const;
		bool _OverrideUnmapMemory (const TraceRange::Iterator &, INOUT TracePacker &) const;
		bool _OverrideFlushMappedMemoryRanges (const TraceRange::Iterator &, FrameID, INOUT TracePacker &);

		bool _RemapBufferMemory (const TraceRange::Iterator &, INOUT TracePacker &) const;
		bool _RemapImageMemory (const TraceRange::Iterator &, INOUT TracePacker &) const;
		bool _RemapBufferMemory2 (const TraceRange::Iterator &, INOUT TracePacker &) const;
		bool _RemapImageMemory2 (const TraceRange::Iterator &, INOUT TracePacker &) const;
		bool _RemapFlushMemoryRanges (const TraceRange::Iterator &, FrameID, INOUT TracePacker &);
		bool _FreeImageMemory (const TraceRange::Iterator &, INOUT TracePacker &) const;
		bool _FreeBufferMemory (const TraceRange::Iterator &, INOUT TracePacker &) const;

		// remap swapchain images
		bool _OnAcquireNextImage (const TraceRange::Iterator &, INOUT TracePacker &) const;
		bool _OnQueuePresent (const TraceRange::Iterator &, INOUT TracePacker &);
		bool _OnCreateRenderPass (const TraceRange::Iterator &, INOUT TracePacker &) const;
		bool _OnWaitEvents2 (const TraceRange::Iterator &) const;
		bool _OnPipelineBarrier2 (const TraceRange::Iterator &) const;

		// use loadable data
		bool _OnCreateShaderModule (const TraceRange::Iterator &, FrameID, INOUT TracePacker &);
		bool _OnCreatePipelineCache (const TraceRange::Iterator &, FrameID, INOUT TracePacker &);
		bool _OnCmdUpdateBuffer (const TraceRange::Iterator &, FrameID, INOUT TracePacker &);

		bool _OnUpdateDescriptorSets (const TraceRange::Iterator &, INOUT TracePacker &);
		bool _OnCmdPushDescriptorSetWithTemplate (const TraceRange::Iterator &, FrameID, INOUT TracePacker &);
		bool _OnUpdateDescriptorSetWithTemplate (const TraceRange::Iterator &, FrameID, INOUT TracePacker &);
	};


}	// VTC
