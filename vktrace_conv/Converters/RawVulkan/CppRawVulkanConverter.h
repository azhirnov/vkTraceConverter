// Copyright (c)  Zhirnov Andrey. For more information see 'LICENSE.txt'

#pragma once

#include "Converters/Converter.h"
#include "Analyzer/ImageUsageAnalyzer.h"
#include "Analyzer/SwapchainAnalyzer.h"
#include "Analyzer/DrawCallAnalyzer.h"
#include "Analyzer/AllResourcesBookmarks.h"
#include "Analyzer/DeviceAnalyzer.h"
#include "Converters/Utils/ResRemapper.h"

#include <filesystem>

namespace VTC
{
	namespace fs = std::filesystem;



	//
	// CPP Raw Vulkan API Converter
	//

	class CppRawVulkanConverter
	{
	// variables
	private:
		ConverterConfig::CppRawVulkan	_config;

		const fs::path					_directory;
		const fs::path					_dataDir;
		const String					_projName;

		AppTrace const *				_appTrace				= null;

		ImageUsageAnalyzer const*		_imageUsageAnalyzer		= null;
		SwapchainAnalyzer const*		_swapchainAnalyzer		= null;
		//DrawCallAnalyzer const*		_drawCallAnalyzer		= null;
		AllResourcesBookmarks const*	_resourcesBookmarks		= null;
		DeviceAnalyzer const*			_deviceAnalyzer			= null;

		UniquePtr<ResRemapper>			_resRemapper;


	// methods
	public:
		CppRawVulkanConverter (const ConverterConfig &cfg);

		bool Run (const AppTrace &trace);

	private:
		bool _ConvertFrame (FrameID index, const TraceRange &trace);
		bool _GenCommonFile (FrameID first, FrameID last) const;
		bool _GenCMakeFile (FrameID first, FrameID last) const;
		bool _GenMain (FrameID first, FrameID last) const;

		bool _StoreFile (const fs::path &filename, StringView data) const;

		bool _InitializeResources (INOUT String &str) const;
		bool _SetupDevice (INOUT String &str) const;
		bool _SetupQueues (const DeviceAnalyzer::LogicalDeviceInfo &deviceInfo, INOUT String &str) const;
		bool _SetupSwapchain (ResourceID swapchainID, const VkSwapchainCreateInfoKHR &createInfo, INOUT String &str) const;
	};


}	// VTC
