// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'
/*
	Converts vktrace to c++ code with raw vulkan api calls.
*/

#pragma once

#include "Analyzer/Default/ImageAnalyzer.h"
#include "Analyzer/Default/BufferAnalyzer.h"
#include "Analyzer/Default/MemoryObjAnalyzer.h"
#include "Analyzer/Default/MemoryTransferAnalyzer.h"
#include "Analyzer/Default/SwapchainAnalyzer.h"
#include "Analyzer/Default/DeviceAnalyzer.h"
#include "Analyzer/Default/QueueAnalyzer.h"
#include "Analyzer/Default/AllResourcesBookmarks.h"

#include "Converters/Converter.h"
#include "Converters/Utils/ResRemapper.h"
#include "Converters/Utils/NameSerializer.h"


namespace VTC
{

	//
	// C++ Vulkan Source Converter
	//

	class CppVulkanConverter
	{
	// types
	private:
		using DataID = uint;	// same as DataID in engine

		struct DataAccessInfo
		{
			DataID			dataId		= UMax;
			uint64_t		offset		= 0;
			uint64_t		size		= 0;

			DataAccessInfo () {}
			DataAccessInfo (uint64_t offset, uint64_t size) : offset{offset}, size{size} {}

			ND_ bool  operator == (const DataAccessInfo &rhs) const		{ return offset == rhs.offset and size == rhs.size; }
		};

		struct DataAccessInfoHash {
			ND_ size_t  operator () (const DataAccessInfo &x) const	{ return size_t(HashOf(x.offset) + HashOf(x.size)); }
		};

		using DatAccessInFile_t			= HashMap< DataAccessInfo, HashSet<FrameID>, DataAccessInfoHash >;
		using DataAccess_t				= HashMap< String, DatAccessInFile_t >;
		using InitializedResources_t	= HashSet< ResourceID >;
		using Config_t					= ConverterConfig::VulkanCppSource;


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
		QueueAnalyzer const*			_queueAnalyzer			= null;
		
		AllResourcesBookmarks const*	_resourcesBookmarks		= null;

		mutable NameSerializer			_nameSerializer;
		UniquePtr<ResRemapper>			_resRemapper;

		mutable String					_tempStr1;
		mutable String					_tempStr2;
		mutable InitializedResources_t	_initializedResources;	// used in _Remap***

		DataAccess_t					_dataAccess;
		DataID							_dataCounter	= 0;
		uint64_t						_dataSize		= 0;


	// methods
	public:
		CppVulkanConverter (const ConverterConfig &cfg);

		bool Run (const AppTrace &trace);


	private:
		bool _ConvertFrame1 (FrameID index, const TraceRange &trace);
		bool _ConvertFrame2 (FrameID index, const TraceRange &trace);

		bool _ConvertFunction (const TraceRange::Iterator &iter, FrameID frameId, INOUT String &src);
		bool _ConvertVkFunction (const TraceRange::Iterator &iter, INOUT String &src) const;

		bool _GenCommonFile (FrameID first, FrameID last) const;
		bool _GenCMakeFile (FrameID first, FrameID last) const;
		bool _GenMain (FrameID first, FrameID last) const;

		bool _StoreFile (const fs::path &filename, StringView data) const;

		ND_ DataID  _RequestData (const String &filename, uint64_t offset, uint64_t size, FrameID frameId);

		ND_ DataID  _RequestData (const String &filename, const TraceRange::Iterator &iter,
								  const void* hdr, const void *member, uint64_t size, FrameID frameId);

		bool _InitializeResources (INOUT String &str) const;
		bool _SetupDevice (TraceRange::Bookmark pos, INOUT String &str) const;
		bool _SetupQueues (const DeviceAnalyzer::LogicalDeviceInfo_t &deviceInfo, INOUT String &str) const;
		bool _SetupSwapchain (const SwapchainAnalyzer::SwapchainInfo_t &swapchain, INOUT String &str) const;
		bool _SetupResourceFiles (INOUT String &str) const;
		bool _SetupDrawFrames (FrameID first, FrameID last, INOUT String &str) const;

		// remap queue family
		bool _OnCreateCommandPool (const TraceRange::Iterator &, INOUT String &src) const;
		bool _OnCreateBuffer (const TraceRange::Iterator &, INOUT String &src) const;
		bool _OnCreateImage (const TraceRange::Iterator &, INOUT String &src) const;
		bool _OnCmdWaitEvents (const TraceRange::Iterator &, INOUT String &src) const;
		bool _OnCmdPipelineBarrier (const TraceRange::Iterator &, INOUT String &src);
		
		// remap memory
		bool _OnBindBufferMemory (const TraceRange::Iterator &, INOUT String &src) const;
		bool _OnBindImageMemory (const TraceRange::Iterator &, INOUT String &src) const;
		bool _OnBindBufferMemory2 (const TraceRange::Iterator &, INOUT String &src) const;
		bool _OnBindImageMemory2 (const TraceRange::Iterator &, INOUT String &src) const;
		bool _OnAllocateMemory (const TraceRange::Iterator &, INOUT String &src) const;
		bool _OnFreeMemory (const TraceRange::Iterator &, INOUT String &src) const;
		bool _OnMapMemory (const TraceRange::Iterator &, INOUT String &src) const;
		bool _OnUnmapMemory (const TraceRange::Iterator &, INOUT String &src) const;
		bool _OnFlushMappedMemoryRanges (const TraceRange::Iterator &, FrameID frameId, INOUT String &src);
		bool _OnDestroyImage (const TraceRange::Iterator &, INOUT String &src) const;
		bool _OnDestroyBuffer (const TraceRange::Iterator &, INOUT String &src) const;
		
		bool _OverrideMapMemory (const TraceRange::Iterator &, INOUT String &src) const;
		bool _OverrideUnmapMemory (const TraceRange::Iterator &, INOUT String &src) const;
		bool _OverrideFlushMappedMemoryRanges (const TraceRange::Iterator &, FrameID frameId, INOUT String &src);

		bool _RemapBufferMemory (const TraceRange::Iterator &, INOUT String &src) const;
		bool _RemapImageMemory (const TraceRange::Iterator &, INOUT String &src) const;
		bool _RemapBufferMemory2 (const TraceRange::Iterator &, INOUT String &src) const;
		bool _RemapImageMemory2 (const TraceRange::Iterator &, INOUT String &src) const;
		bool _RemapFlushMemoryRanges (const TraceRange::Iterator &, FrameID frameId, INOUT String &src);
		bool _FreeImageMemory (const TraceRange::Iterator &, INOUT String &src) const;
		bool _FreeBufferMemory (const TraceRange::Iterator &, INOUT String &src) const;

		// remap swapchain images
		bool _OnAcquireNextImage (const TraceRange::Iterator &, INOUT String &src) const;
		bool _OnQueuePresent (const TraceRange::Iterator &, INOUT String &src) const;

		// use loadable data
		bool _OnCreateShaderModule (const TraceRange::Iterator &, FrameID frameId, INOUT String &src);
		bool _OnCreatePipelineCache (const TraceRange::Iterator &, INOUT String &src);
	};


}	// VTC
