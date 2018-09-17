// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Analyzer/Default/ImageAnalyzer.h"
#include "Analyzer/Default/BufferAnalyzer.h"
#include "Analyzer/Default/MemoryObjAnalyzer.h"

#include "Analyzer/old/SwapchainAnalyzer.h"
#include "Analyzer/old/DrawCallAnalyzer.h"
#include "Analyzer/old/AllResourcesBookmarks.h"
#include "Analyzer/old/DeviceAnalyzer.h"

#include "Converters/Converter.h"
#include "Converters/Utils/ResRemapper.h"
#include "Converters/Utils/NameSerializer.h"

#include <filesystem>

namespace VTC
{
	namespace fs = std::filesystem;



	//
	// CPP Raw Vulkan API Converter
	//

	class CppRawVulkanConverter
	{
	// types
	private:
		using DataID = uint;	// same as DataID in engine

		struct DataAccessInfo
		{
			DataID			dataId		= ~0u;
			uint64_t		offset		= 0;
			uint64_t		size		= 0;

			DataAccessInfo () {}
			DataAccessInfo (uint64_t offset, uint64_t size) : offset{offset}, size{size} {}

			ND_ bool  operator == (const DataAccessInfo &rhs) const		{ return offset == rhs.offset and size == rhs.size; }
		};

		struct DataAccessInfoHash {
			ND_ size_t  operator () (const DataAccessInfo &x) const	{ return size_t(HashOf(x.offset) + HashOf(x.size)); }
		};

		using DatAccessInFile_t		= HashMap< DataAccessInfo, HashSet<FrameID>, DataAccessInfoHash >;
		using DataAccess_t			= HashMap< String, DatAccessInFile_t >;


	// variables
	private:
		ConverterConfig::CppRawVulkan	_config;

		const fs::path					_directory;
		const fs::path					_dataDir;
		const String					_inputFile;

		const String					_projName;

		AppTrace const *				_appTrace				= null;

		ImageAnalyzer const*			_imageAnalyzer			= null;
		BufferAnalyzer const*			_bufferAnalyzer			= null;
		MemoryObjAnalyzer const*		_memoryObjAnalyzer		= null;

		SwapchainAnalyzer const*		_swapchainAnalyzer		= null;
		//DrawCallAnalyzer const*		_drawCallAnalyzer		= null;
		AllResourcesBookmarks const*	_resourcesBookmarks		= null;
		DeviceAnalyzer const*			_deviceAnalyzer			= null;
		
		NameSerializer					_nameSerializer;
		UniquePtr<ResRemapper>			_resRemapper;

		String							_tempStr1;
		String							_tempStr2;

		DataAccess_t					_dataAccess;
		DataID							_dataCounter	= 0;
		uint64_t						_dataSize		= 0;


	// methods
	public:
		CppRawVulkanConverter (const ConverterConfig &cfg);

		bool Run (const AppTrace &trace);


	private:
		bool _ConvertFrame (FrameID index, const TraceRange &trace);
		bool _ConvertVkFunction (const TraceRange::Iterator &iter, INOUT String &src);

		bool _GenCommonFile (FrameID first, FrameID last) const;
		bool _GenCMakeFile (FrameID first, FrameID last) const;
		bool _GenMain (FrameID first, FrameID last) const;

		bool _StoreFile (const fs::path &filename, StringView data) const;

		ND_ DataID  _RequestData (const String &filename, uint64_t offset, uint64_t size, FrameID frameId);

		ND_ DataID  _RequestData (const String &filename, const TraceRange::Iterator &iter,
								  const void* hdr, const void *member, uint64_t size, FrameID frameId);

		bool _InitializeResources (INOUT String &str) const;
		bool _SetupDevice (TraceRange::Bookmark pos, INOUT String &str) const;
		bool _SetupQueues (TraceRange::Bookmark pos, const DeviceAnalyzer::LogicalDeviceInfo &deviceInfo, INOUT String &str) const;
		bool _SetupSwapchain (ResourceID swapchainID, const VkSwapchainCreateInfoKHR &createInfo, INOUT String &str) const;
		bool _SetupResourceFiles (INOUT String &str) const;
		bool _SetupDrawFrames (FrameID first, FrameID last, INOUT String &str) const;

		bool _OnCreateCommandPool (const TraceRange::Iterator &iter, INOUT String &src);
		//bool _OnCreateBuffer (const TraceRange::Iterator &iter, INOUT String &src);
		//bool _OnCreateImage (const TraceRange::Iterator &iter, INOUT String &src);
		//bool _OnCmdWaitEvents (const TraceRange::Iterator &iter, INOUT String &src);
		//bool _OnCmdPipelineBarrier (const TraceRange::Iterator &iter, INOUT String &src);

		bool _OnCreateShaderModule (const TraceRange::Iterator &iter, FrameID frameId, INOUT String &src);
		bool _OnMapMemory (const TraceRange::Iterator &iter, INOUT String &src);
		bool _OnUnmapMemory (const TraceRange::Iterator &iter, INOUT String &src);
		//bool _OnFlushMappedMemoryRanges (const TraceRange::Iterator &iter, FrameID frameId, INOUT String &src);
		//bool _OnInvalidateMappedMemoryRanges (const TraceRange::Iterator &iter, FrameID frameId, INOUT String &src);
		bool _OnAcquireNextImage (const TraceRange::Iterator &iter, INOUT String &src);
		bool _OnQueuePresent (const TraceRange::Iterator &iter, INOUT String &src);
	};


}	// VTC
