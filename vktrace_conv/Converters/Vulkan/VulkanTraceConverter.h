// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'
/*
	Converts vktrace to vtcTrace file with vulkan api calls.
*/

#pragma once

#include "Analyzer/Default/ImageAnalyzer.h"
#include "Analyzer/Default/BufferAnalyzer.h"
#include "Analyzer/Default/MemoryObjAnalyzer.h"
#include "Analyzer/Default/MemoryTransferAnalyzer.h"
#include "Analyzer/Default/SwapchainAnalyzer.h"
#include "Analyzer/Default/DeviceAnalyzer.h"
#include "Analyzer/Default/AllResourcesBookmarks.h"

#include "Converters/Converter.h"
#include "Converters/Utils/TracePacker.h"


namespace VTC
{

	//
	// Vulkan Trace Converter
	//

	class VulkanTraceConverter
	{
	// types
	private:
		using DataID = uint;	// same as DataID in engine

		using InitializedResources_t	= HashSet< ResourceID >;
		using Config_t					= ConverterConfig::VulkanTrace;


	// variables
	private:
		const Config_t					_config;

		const fs::path					_directory;
		const fs::path					_dataDir;
		const String					_inputFile;

		const String					_projName;

		AppTrace const *				_appTrace				= null;

		ImageAnalyzer const*			_imageAnalyzer			= null;
		BufferAnalyzer const*			_bufferAnalyzer			= null;
		MemoryObjAnalyzer const*		_memoryObjAnalyzer		= null;
		MemoryTransferAnalyzer const*	_memTransferAnalyzer	= null;
		SwapchainAnalyzer const*		_swapchainAnalyzer		= null;
		DeviceAnalyzer const*			_deviceAnalyzer			= null;
		
		AllResourcesBookmarks const*	_resourcesBookmarks		= null;

		mutable InitializedResources_t	_initializedResources;	// used in _Remap***

		UniquePtr<TracePacker>			_tracePacker;


	// methods
	public:
		VulkanTraceConverter (const ConverterConfig &cfg);

		bool Run (const AppTrace &trace);


	private:
		bool _ConvertFunction (const TraceRange::Iterator &iter, FrameID frameId);
		bool _ConvertVkFunction (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const;

		bool _StoreFile (const fs::path &filename, StringView data) const;
		
		ND_ DataID  _RequestData (const String &filename, uint64_t offset, uint64_t size, FrameID frameId);

		ND_ DataID  _RequestData (const String &filename, const TraceRange::Iterator &iter,
								  const void* hdr, const void *member, uint64_t size, FrameID frameId);

		// remap queue family
		bool _OnCreateCommandPool (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const;
		bool _OnCreateBuffer (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const;
		bool _OnCreateImage (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const;
		bool _OnCmdWaitEvents (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const;
		bool _OnCmdPipelineBarrier (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const;
		
		// remap memory
		bool _OnBindBufferMemory (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const;
		bool _OnBindImageMemory (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const;
		bool _OnBindBufferMemory2 (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const;
		bool _OnBindImageMemory2 (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const;
		bool _OnAllocateMemory (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const;
		bool _OnFreeMemory (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const;
		bool _OnMapMemory (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const;
		bool _OnUnmapMemory (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const;
		bool _OnFlushMappedMemoryRanges (const TraceRange::Iterator &iter, FrameID frameId, INOUT TracePacker &packer);
		bool _OnDestroyImage (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const;
		bool _OnDestroyBuffer (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const;
		
		bool _OverrideMapMemory (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const;
		bool _OverrideUnmapMemory (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const;
		bool _OverrideFlushMappedMemoryRanges (const TraceRange::Iterator &iter, FrameID frameId, INOUT TracePacker &packer);

		bool _RemapBufferMemory (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const;
		bool _RemapImageMemory (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const;
		bool _RemapBufferMemory2 (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const;
		bool _RemapImageMemory2 (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const;
		bool _RemapFlushMemoryRanges (const TraceRange::Iterator &iter, FrameID frameId, INOUT TracePacker &packer);
		bool _FreeImageMemory (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const;
		bool _FreeBufferMemory (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const;


		// remap swapchain images
		bool _OnAcquireNextImage (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const;
		bool _OnQueuePresent (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const;


		// use loadable data
		bool _OnCreateShaderModule (const TraceRange::Iterator &iter, FrameID frameId, INOUT TracePacker &packer);
		bool _OnCreatePipelineCache (const TraceRange::Iterator &iter, FrameID frameId, INOUT TracePacker &packer);
		bool _OnCmdUpdateBuffer (const TraceRange::Iterator &iter, FrameID frameId, INOUT TracePacker &packer);
		bool _OnCmdPushDescriptorSetWithTemplate (const TraceRange::Iterator &iter, FrameID frameId, INOUT TracePacker &packer);
		bool _OnUpdateDescriptorSetWithTemplate (const TraceRange::Iterator &iter, FrameID frameId, INOUT TracePacker &packer);
	};


}	// VTC
