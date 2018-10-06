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
#include "Analyzer/Default/QueueAnalyzer.h"
#include "Analyzer/Default/AllResourcesBookmarks.h"
#include "Analyzer/Ext/ExtensionAnalyzer.h"
#include "Analyzer/Ext/FPSAnalyzer.h"

#include "Converters/Converter.h"
#include "Converters/Data/IResourceDataManager.h"


namespace VTC
{

	//
	// Vulkan Trace Converter
	//

	class VulkanTraceConverter
	{
	// types
	private:
		using DataID	= IResourceDataWriter::DataID;
		
		struct DataAccessInfo
		{
			DataID			dataId		= ~0u;
			uint64_t		offset		= 0;
			uint64_t		size		= 0;

			DataAccessInfo () {}
			DataAccessInfo (uint64_t offset, uint64_t size) : offset{offset}, size{size} {}

			ND_ bool  operator == (const DataAccessInfo &rhs) const		{ return offset == rhs.offset and size == rhs.size; }
		};

		struct DataAccessFrameMinMax {
			FrameID			min		= ~FrameID(0);
			FrameID			max		= FrameID(0);
		};

		struct DataAccessInfoHash {
			ND_ size_t  operator () (const DataAccessInfo &x) const	{ return size_t(HashOf(x.offset) + HashOf(x.size)); }
		};
		
		using DataAccess_t				= HashMap< DataAccessInfo, DataAccessFrameMinMax, DataAccessInfoHash >;
		using InitializedResources_t	= HashSet< ResourceID >;
		using Config_t					= ConverterConfig::VulkanTrace;


	// variables
	private:
		const Config_t					_config;

		const fs::path					_directory;
		const fs::path					_dataDir;
		const String					_inputFile;

		const String					_fileName;

		AppTrace const *				_appTrace				= null;

		ImageAnalyzer const*			_imageAnalyzer			= null;
		BufferAnalyzer const*			_bufferAnalyzer			= null;
		MemoryObjAnalyzer const*		_memoryObjAnalyzer		= null;
		MemoryTransferAnalyzer const*	_memTransferAnalyzer	= null;
		SwapchainAnalyzer const*		_swapchainAnalyzer		= null;
		DeviceAnalyzer const*			_deviceAnalyzer			= null;
		QueueAnalyzer const*			_queueAnalyzer			= null;
		
		AllResourcesBookmarks const*	_resourcesBookmarks		= null;
		ExtensionAnalyzer const*		_extensionAnalyzer		= null;
		FPSAnalyzer const*				_fpsAnalyzer			= null;

		mutable InitializedResources_t	_initializedResources;	// used in _Remap***

		UniquePtr<class TracePacker>	_tracePacker;

		DataAccess_t					_dataAccess;
		DataID							_dataCounter	= 0;


	// methods
	public:
		VulkanTraceConverter (const ConverterConfig &cfg);

		bool Run (const AppTrace &trace);


	private:
		bool _ConvertFunction (const TraceRange::Iterator &iter, FrameID frameId);
		bool _ConvertVkFunction (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const;

		bool _AfterConverting ();
		bool _CheckPacketErrors (const TraceRange::Iterator &iter) const;

		void _InitializeResources (INOUT TracePacker &packer) const;
		bool _PackVulkanCreateInfo (INOUT TracePacker &packer) const;
		void _SetSourceFPS (INOUT TracePacker &packer) const;
		void _EndOfTrace (INOUT TracePacker &packer) const;
		bool _PackData (INOUT TracePacker &packer) const;
		bool _GenMain (StringView path) const;
		bool _GenCMake () const;
		
		ND_ DataID  _RequestData (uint64_t offset, uint64_t size, FrameID frameId);
		ND_ DataID  _RequestData (const TraceRange::Iterator &iter, const void* hdr, const void *member, uint64_t size, FrameID frameId);

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
		bool _OnQueuePresent (const TraceRange::Iterator &, INOUT TracePacker &) const;
		bool _OnCreateRenderPass (const TraceRange::Iterator &, INOUT TracePacker &) const;
		bool _OnWaitEvents2 (const TraceRange::Iterator &) const;
		bool _OnPipelineBarrier2 (const TraceRange::Iterator &) const;

		// use loadable data
		bool _OnCreateShaderModule (const TraceRange::Iterator &, FrameID, INOUT TracePacker &);
		bool _OnCreatePipelineCache (const TraceRange::Iterator &, FrameID, INOUT TracePacker &);
		bool _OnCmdUpdateBuffer (const TraceRange::Iterator &, FrameID, INOUT TracePacker &);
		bool _OnCmdPushDescriptorSetWithTemplate (const TraceRange::Iterator &, FrameID, INOUT TracePacker &);
		bool _OnUpdateDescriptorSetWithTemplate (const TraceRange::Iterator &, FrameID, INOUT TracePacker &);
	};


}	// VTC
