// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Parser/AppTrace.h"
#include "Analyzer/Default/AllResourcesBookmarks.h"
#include "Analyzer/Default/DeviceAnalyzer.h"
#include "Analyzer/Default/QueueAnalyzer.h"
#include "Analyzer/Default/SwapchainAnalyzer.h"
#include "Analyzer/Default/ImageAnalyzer.h"
#include "Analyzer/Ext/ExtensionAnalyzer.h"
#include "Analyzer/Ext/FPSAnalyzer.h"

namespace VTC
{
#	include "Types/VulkanCreateInfo.h"

	class TracePacker;


	//
	// Trace Converter Base
	//

	class TraceConverterBase
	{
	// types
	protected:
		using DataID	= uint;
		
		struct DataAccessInfo
		{
			DataID			dataId		= UMax;
			uint64_t		offset		= 0;
			uint64_t		size		= 0;

			DataAccessInfo () {}
			DataAccessInfo (uint64_t offset, uint64_t size) : offset{offset}, size{size} {}

			ND_ bool  operator == (const DataAccessInfo &rhs) const		{ return offset == rhs.offset and size == rhs.size; }
		};

		struct DataAccessFrameMinMax {
			FrameID			min		= UMax;
			FrameID			max		= FrameID(0);
		};

		struct DataAccessInfoHash {
			ND_ size_t  operator () (const DataAccessInfo &x) const	{ return size_t(HashOf(x.offset) + HashOf(x.size)); }
		};
		
		using DataAccess_t				= HashMap< DataAccessInfo, DataAccessFrameMinMax, DataAccessInfoHash >;


	// variables
	protected:
		Ptr< AppTrace const>				_appTrace;

		Ptr< AllResourcesBookmarks const>	_resourcesBookmarks;
		Ptr< DeviceAnalyzer const>			_deviceAnalyzer;
		Ptr< QueueAnalyzer const>			_queueAnalyzer;
		Ptr< SwapchainAnalyzer const>		_swapchainAnalyzer;
		Ptr< ImageAnalyzer const>			_imageAnalyzer;
		Ptr< ExtensionAnalyzer const>		_extensionAnalyzer;
		Ptr< FPSAnalyzer const>				_fpsAnalyzer;
		
		DataAccess_t						_dataAccess;
		DataID								_dataCounter		= 0;


	// methods
	protected:
		bool _PackVulkanCreateInfo (VulkanCreateInfo::EImplFlags implFlags, INOUT TracePacker &packer) const;
		bool _PackData (INOUT TracePacker &packer) const;
		void _EndOfTrace (INOUT TracePacker &packer) const;

		bool _GenMain (StringView windowTitle, StringView inputTraceFile, const fs::path &convertedTraceFile, const fs::path &outputFile) const;
		bool _GenCMake (StringView projectName, const fs::path &outputFile) const;
		
		ND_ DataID  _RequestData (uint64_t offset, uint64_t size, FrameID frameId);
		ND_ DataID  _RequestData (const TraceRange::Iterator &iter, const void* hdr, const void *member, uint64_t size, FrameID frameId);
	};


}	// VTC
