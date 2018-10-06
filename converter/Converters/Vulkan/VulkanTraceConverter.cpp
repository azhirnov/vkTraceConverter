// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Converters/Vulkan/VulkanTraceConverter.h"
#include "extensions/vulkan_loader/VulkanCheckError.h"
#include "Converters/Utils/TracePacker.h"
#include "Converters/Utils/BasicTypesConverter.h"

namespace VTC
{
	using VPacker = TracePacker;
	
#	include "Generated/VulkanTraceStructPacker.h"
#	include "Generated/VulkanTraceStructPackerImpl.h"
#	include "Types/VulkanCreateInfo.h"
#	include "Types/TraceFileHeader.h"

/*
=================================================
	RunConverter_VulkanPlayer
=================================================
*/
	bool RunConverter_VulkanPlayer (const AppTrace &trace, const ConverterConfig &config)
	{
		FG_TIMEPROFILER();

		VulkanTraceConverter	conv{ config };

		return conv.Run( trace );
	}
	
/*
=================================================
	constructor
=================================================
*/
	VulkanTraceConverter::VulkanTraceConverter (const ConverterConfig &cfg) :
		_config{ cfg.conveters.vulkanTrace },
		_directory{ fs::path{cfg.outputDirectory}.append("vk-trace") },
		_dataDir{ fs::path{cfg.outputDirectory}.append("data") },			// TODO
		_inputFile{ cfg.inputTraceFile },
		_fileName{ fs::path{cfg.outputDirectory}.filename().string() << "-vk" }
	{
		if ( not fs::exists( _directory ) ) {
			CHECK( fs::create_directories( _directory ));
		}
	}
	
/*
=================================================
	Run
=================================================
*/
	bool VulkanTraceConverter::Run (const AppTrace &appTrace)
	{
		// initialization
		{
			_appTrace		= &appTrace;
			_dataCounter	= 0;

			// request analyzers
			_swapchainAnalyzer		= appTrace.GetAnalyzer< SwapchainAnalyzer >();
			_resourcesBookmarks		= appTrace.GetAnalyzer< AllResourcesBookmarks >();
			_deviceAnalyzer			= appTrace.GetAnalyzer< DeviceAnalyzer >();
			_memTransferAnalyzer	= appTrace.GetAnalyzer< MemoryTransferAnalyzer >();
			_memoryObjAnalyzer		= appTrace.GetAnalyzer< MemoryObjAnalyzer >();
			_imageAnalyzer			= appTrace.GetAnalyzer< ImageAnalyzer >();
			_bufferAnalyzer			= appTrace.GetAnalyzer< BufferAnalyzer >();
			_extensionAnalyzer		= appTrace.GetAnalyzer< ExtensionAnalyzer >();
			_queueAnalyzer			= appTrace.GetAnalyzer< QueueAnalyzer >();
			_fpsAnalyzer			= appTrace.GetAnalyzer< FPSAnalyzer >();

			CHECK_ERR( _swapchainAnalyzer and _resourcesBookmarks and _deviceAnalyzer and _queueAnalyzer );
			CHECK_ERR( _memTransferAnalyzer and _extensionAnalyzer and _fpsAnalyzer );
			CHECK_ERR( _memoryObjAnalyzer and _imageAnalyzer and _bufferAnalyzer );

			_tracePacker.reset( new TracePacker{ _resourcesBookmarks, _config.useUniqueResourceIndices });
		}


		// convert packets
		const FrameID	last_frame	= Min( _config.lastFrame, appTrace.GetFrameCount() );
		FrameID			curr_frame	= 0;
		const auto&		present_bm	= appTrace.PresentBookmark();
		
		for (auto iter = appTrace.FullTrace().begin(); iter < appTrace.FullTrace().LastBookmark(); ++iter)
		{
			for (; not (iter < present_bm[curr_frame]) and curr_frame < present_bm.size(); ++curr_frame) {}

			if ( curr_frame >= last_frame )
				break;

			if ( not appTrace.CheckPacketErrors( iter ) )
				continue;
			
			CHECK_ERR( _ConvertFunction( iter, curr_frame ));
		}

		CHECK_ERR( _AfterConverting() );

		_appTrace = null;
		_tracePacker.reset();
		return true;
	}
	
/*
=================================================
	_InitializeResources
=================================================
*/
	void VulkanTraceConverter::_InitializeResources (INOUT TracePacker &packer) const
	{
		for (size_t i = 0; i < VkResourceTypes::Count; ++i)
		{
			uint64_t	count = _resourcesBookmarks->GetResourceCountByType( GetVkResourceType(i) );

			if ( not count )
				continue;

			packer.Begin( EPacketID::VInitializeResource );
			packer << uint(i);
			packer << count;
			packer.End( EPacketID::VInitializeResource );
		}
	}

/*
=================================================
	_PackVulkanCreateInfo
=================================================
*/
	bool VulkanTraceConverter::_PackVulkanCreateInfo (INOUT TracePacker &packer) const
	{
		using ESwapchainType	= VulkanCreateInfo::ESwapchainType;
		using EImplFlags		= VulkanCreateInfo::EImplFlags;

		VulkanCreateInfo		ci	= {};
		TraceRange::Bookmark	pos;
		const uint64_t			sw_count = _resourcesBookmarks->GetUniqueResourceCountByType( VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT );

		CHECK_ERR( sw_count <= 1 );
		CHECK_ERR( sw_count == 0 or not _swapchainAnalyzer->GetSwapchains().empty() );
		CHECK_ERR( _resourcesBookmarks->GetResourceCountByType( VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT ) == 1 );
		
		auto		first_bm		= _appTrace->GetFrameTrace( FrameID(0) ).begin().GetBookmark();

		auto&		instance		= *_resourcesBookmarks->GetResourcesByType( VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT )->begin();
		auto*		instance_info	= _deviceAnalyzer->GetInstanceInfo( instance.first, first_bm );
		CHECK_ERR(	instance_info and
					instance_info->physicalDevices.size() and
					instance_info->logicalDevices.size() == 1 );
		
		ResourceID	device_id		= *instance_info->logicalDevices.begin();
		auto*		device_info		= _deviceAnalyzer->GetLogicalDeviceInfo( device_id, first_bm );
		CHECK_ERR( device_info );

		const auto	queues			= _queueAnalyzer->GetDeviceQueues( device_info->id, device_info->FirstBookmark().pos );
		auto*		swapchain		= sw_count ? &_swapchainAnalyzer->GetSwapchains().begin()->second.front() : null;


		Array<const char*>		inst_extensions;
		Array<const char*>		dev_extensions;
		Array<VkQueue>			queue_ids;
		Array<VkQueueFlags>		queue_flags;
		Array<float>			queue_priorities;
		Array<VkImage>			swapchain_images;

		pos = device_info->FirstBookmark().pos;

		for (auto& ext : _extensionAnalyzer->GetInstanceExtensions()) {
			inst_extensions.push_back( ext.data() );
		}
		for (auto& ext : _extensionAnalyzer->GetDeviceExtensions()) {
			dev_extensions.push_back( ext.data() );
		}
		for (auto& queue_info : queues)
		{
			if ( queue_info->usageFlags == 0 and not queue_info->usedForPresent )
				continue;

			pos = std::max( pos, queue_info->FirstBookmark().pos );
			queue_ids.push_back( VkQueue(queue_info->id) );
			queue_flags.push_back( queue_info->usageFlags );
			queue_priorities.push_back( queue_info->priority );
		}

		ci.instanceVersion			= _extensionAnalyzer->GetMinVersion();
		ci.instanceExtensionCount	= uint(inst_extensions.size());
		ci.instanceExtensions		= inst_extensions.data();
		ci.instanceID				= VkInstance(instance.first);

		ci.deviceExtensionCount		= uint(dev_extensions.size());
		ci.deviceExtensions			= dev_extensions.data();
		ci.physicalDeviceID			= VkPhysicalDevice(device_info->physicalDevice);
		ci.deviceID					= VkDevice(device_info->id);

		ci.queueCount				= uint(queue_ids.size());
		ci.queueIDs					= queue_ids.data();
		ci.queueFamilies			= queue_flags.data();
		ci.queuePriorities			= queue_priorities.data();

		ci.implementationFlags		= EImplFlags::None;
		if ( _config.remapMemory )				ci.implementationFlags |= EImplFlags::OverrideMemoryAllocation;
		if ( _config.remapQueueFamily )			ci.implementationFlags |= EImplFlags::RemapQueueFamilies;
		if ( _config.indirectSwapchain )		ci.implementationFlags |= EImplFlags::IndirectSwapchain;
		if ( _config.useUniqueResourceIndices )	ci.implementationFlags |= EImplFlags::UniqueResourceIndices;

		ci.swapchainType			= ESwapchainType::WithoutSwapchain;

		if ( swapchain )
		{
			pos = std::max( pos, swapchain->FirstBookmark().pos );

			ci.swapchainID				= VkSwapchainKHR(swapchain->id);
			ci.swapchainType			= ESwapchainType::DefaultSwapchain;
			ci.swapchainImageWidth		= swapchain->createInfo.imageExtent.width;
			ci.swapchainImageHeight		= swapchain->createInfo.imageExtent.height;
			ci.swapchainColorFormat		= swapchain->createInfo.imageFormat;
			ci.swapchainColorSpace		= swapchain->createInfo.imageColorSpace;
			ci.swapchainMinImageCount	= swapchain->createInfo.minImageCount;
			ci.swapchainImageArrayLayers= swapchain->createInfo.imageArrayLayers;
			ci.swapchainPreTransform	= swapchain->createInfo.preTransform;
			ci.swapchainPresentMode		= swapchain->createInfo.presentMode;
			ci.swapchainCompositeAlpha	= swapchain->createInfo.compositeAlpha;
			ci.swapchainColorImageUsage	= 0;
			ci.swapchainImageLayout		= VK_IMAGE_LAYOUT_UNDEFINED;

			for (auto& img : swapchain->images)
			{
				auto*	img_info = _imageAnalyzer->GetImage( img.id, img.pos );
				CHECK_ERR( img_info );

				if ( ci.swapchainImageLayout == VK_IMAGE_LAYOUT_UNDEFINED )
				{
					if ( img_info->layouts.find( VK_IMAGE_LAYOUT_PRESENT_SRC_KHR ) != img_info->layouts.end() )
						ci.swapchainImageLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
					
					// not supported, yet
					//if ( img_info->layouts.find( VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR ) != img_info->layouts.end() )
					//	ci.swapchainImageLayout = VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR;

					CHECK_ERR( ci.swapchainImageLayout != VK_IMAGE_LAYOUT_UNDEFINED );
				}
				else
					CHECK_ERR( img_info->layouts.find( ci.swapchainImageLayout ) != img_info->layouts.end() );

				ci.swapchainColorImageUsage |= img_info->usage;

				swapchain_images.push_back( VkImage(img.id) );
				pos = std::max( pos, img.pos );
			}

			ci.swapchainImageCount		= uint(swapchain_images.size());
			ci.swapchainImageIDs		= swapchain_images.data();
		}

		
		packer.SetCurrentPos( pos );
		packer.Begin( EPacketID::VCreateDevice );
		packer.BeginStruct();
		
		// instanceExtensions
		packer.Push( ci.instanceExtensions );
		 for (uint i = 0; i < ci.instanceExtensionCount; ++i) {
			packer.Push( ci.instanceExtensions[i] );
			 packer.AddString( ci.instanceExtensions[i] );
			packer.PopAndStore( ci.instanceExtensions[i] );
		 }
		packer.Pop( OUT ci.instanceExtensions );
		packer.RemapVkResource( INOUT &ci.instanceID );

		// deviceExtensions
		packer.Push( ci.deviceExtensions );
		 for (uint i = 0; i < ci.deviceExtensionCount; ++i) {
			packer.Push( ci.deviceExtensions[i] );
			 packer.AddString( ci.deviceExtensions[i] );
			packer.PopAndStore( ci.deviceExtensions[i] );
		 }
		packer.Pop( OUT ci.deviceExtensions );
		packer.RemapVkResource( INOUT &ci.physicalDeviceID );
		packer.RemapVkResource( INOUT &ci.deviceID );

		// queueIDs
		packer.Push( ci.queueIDs );
		 for (uint i = 0; i < ci.queueCount; ++i) {
			packer << ci.queueIDs[i];
		 }
		packer.Pop( OUT ci.queueIDs );

		// queueFamilies
		packer.Push( ci.queueFamilies );
		 for (uint i = 0; i < ci.queueCount; ++i) {
			packer << ci.queueFamilies[i];
		 }
		packer.Pop( OUT ci.queueFamilies );

		// queuePriorities
		packer.Push( ci.queuePriorities );
		 for (uint i = 0; i < ci.queueCount; ++i) {
			packer << ci.queuePriorities[i];
		 }
		packer.Pop( OUT ci.queuePriorities );
		
		// swapchainImageIDs
		packer.Push( ci.swapchainImageIDs );
		 for (uint i = 0; i < ci.swapchainImageCount; ++i) {
			packer << ci.swapchainImageIDs[i];
		 }
		packer.Pop( OUT ci.swapchainImageIDs );
		packer.RemapVkResource( INOUT &ci.swapchainID );

		packer.EndStruct( ci );
		packer.End( EPacketID::VCreateDevice );

		return true;
	}
	
/*
=================================================
	_SetSourceFPS
=================================================
*/
	void VulkanTraceConverter::_SetSourceFPS (INOUT TracePacker &packer) const
	{
		packer.Begin( EPacketID::SetSourceFPS );
		packer << uint(_fpsAnalyzer->GetAverageFPS() + 0.5);
		packer.End( EPacketID::SetSourceFPS );
	}

/*
=================================================
	_AfterConverting
=================================================
*/
	bool VulkanTraceConverter::_AfterConverting ()
	{
		const auto		fname	= fs::path{_directory}.append( _fileName + ".bin" );
		FileWStream		file	{ fname };
		CHECK_ERR( file.IsOpen() );

		// header
		{
			TraceFileHeader		header		= {};
			header.magic					= TraceFileHeader::MagicNumber;
			header.instructionSet			= uint(EPacketID::_VulkanApi | EPacketID::_V100);
			header.pointerSize				= sizeof(void*);
			header.archiveType				= TraceFileHeader::EArchiveType::None;	// TODO
			header.instructionBlockOffset	= sizeof(header);
			header.dataBlockOffset			= ~0ull;

			CHECK_ERR( file.Write( header ));
		}

		// pack part 1
		{
			TracePacker		packer{ _resourcesBookmarks, _config.useUniqueResourceIndices };

			CHECK_ERR( _PackData( INOUT packer ));
			
			_SetSourceFPS( INOUT packer );
			_InitializeResources( INOUT packer );
			_PackVulkanCreateInfo( INOUT packer );

			CHECK_ERR( file.Write( packer.GetData() ));
		}

		// pack part 2
		_EndOfTrace( INOUT *_tracePacker );
		CHECK_ERR( file.Write( _tracePacker->GetData() ));

		CHECK_ERR( _GenMain( fname.string() ));
		CHECK_ERR( _GenCMake() );

		return true;
	}
	
/*
=================================================
	_GenMain
=================================================
*/
	bool VulkanTraceConverter::_GenMain (StringView path) const
	{
		auto*		swapchain	= _swapchainAnalyzer->GetSwapchains().empty() ? null : &_swapchainAnalyzer->GetSwapchains().begin()->second.front();
		const uint	width		= swapchain ? swapchain->createInfo.imageExtent.width : 800;
		const uint	height		= swapchain ? swapchain->createInfo.imageExtent.height : 600;

		String	str;
		str << "#ifdef _WIN32\n"
			<< "#	include <Windows.h>\n"
			<< "#else\n"
			<< "#	include <dlfcn.h>\n"
			<< "#	include <linux/limits.h>\n"
			<< "#endif\n"
			<< "#include <VPPlayer.h>\n"
			<< "using namespace VTPlayer;\n\n"

			<< "int main ()\n{\n"
			<< "# ifdef _WIN32\n"
			<< "	HMODULE module = LoadLibraryA( \"VTPlayer.dll\" );\n"
			<< "	if ( module == nullptr )\n"
			<< "		return -1;\n\n"
			<< "	PFN_CreatePlayer	CreatePlayer	= reinterpret_cast<PFN_CreatePlayer>(GetProcAddress( module, \"CreatePlayer\" ));\n"
			<< "	PFN_DestroyPlayer	DestroyPlayer	= reinterpret_cast<PFN_DestroyPlayer>(GetProcAddress( module, \"DestroyPlayer\" ));\n"
			<< "	PFN_PlayerStart		PlayerStart		= reinterpret_cast<PFN_PlayerStart>(GetProcAddress( module, \"PlayerStart\" ));\n"
			<< "	PFN_PlayerPause		PlayerPause		= reinterpret_cast<PFN_PlayerPause>(GetProcAddress( module, \"PlayerPause\" ));\n"
			<< "	PFN_PlayerIsActive	PlayerIsActive	= reinterpret_cast<PFN_PlayerIsActive>(GetProcAddress( module, \"PlayerIsActive\" ));\n"
			<< "# else\n"
			<< "	void* module = dlopen( \"VTPlayer.so\", RTLD_NOW | RTLD_LOCAL );\n"
			<< "	if ( module == nullptr )\n"
			<< "		return -1;\n\n"
			<< "	PFN_CreatePlayer	CreatePlayer	= reinterpret_cast<PFN_CreatePlayer>(dlsym( module, \"CreatePlayer\" ));\n"
			<< "	PFN_DestroyPlayer	DestroyPlayer	= reinterpret_cast<PFN_DestroyPlayer>(dlsym( module, \"DestroyPlayer\" ));\n"
			<< "	PFN_PlayerStart		PlayerStart		= reinterpret_cast<PFN_PlayerStart>(dlsym( module, \"PlayerStart\" ));\n"
			<< "	PFN_PlayerPause		PlayerPause		= reinterpret_cast<PFN_PlayerPause>(dlsym( module, \"PlayerPause\" ));\n"
			<< "	PFN_PlayerIsActive	PlayerIsActive	= reinterpret_cast<PFN_PlayerIsActive>(dlsym( module, \"PlayerIsActive\" ));\n"
			<< "# endif\n\n"

			<< "	if ( !CreatePlayer || !DestroyPlayer || !PlayerStart || !PlayerPause || !PlayerIsActive )\n"
			<< "		return -2;\n\n"

			<< "	VTPlayerInstance	player1  = nullptr;\n"
			<< "	VTPlayerSettings	settings = {};\n"
			<< "	settings.structSize			= sizeof(settings);\n"
			<< "	settings.playerVersion		= VTPLAYER_VERSION_LATEST;\n"
			<< "	settings.playerTraceFile	= \"" << ConvertToCStyleString( path ) << "\";\n"
			<< "	settings.playerDataFile		= \"" << ConvertToCStyleString( _inputFile ) << "\";\n"
			<< "	settings.playerDebugMode	= 0;\n"
			<< "	settings.playerTestMode		= 0;\n"
			<< "	settings.playerBenchmarkMode= 0;\n"
			<< "	settings.windowWidth		= " << ToString(width) << ";\n"
			<< "	settings.windowHeight		= " << ToString(height) << ";\n"
			<< "	settings.windowTitle		= \"" << _fileName << "\";\n"
			<< "	settings.windowFPSinTitle	= 1;\n"
			<< "	settings.windowResizable	= 1;\n"
			<< "	settings.preferredGPUName	= nullptr;\n\n"

			<< "	if ( !CreatePlayer( &settings, OUT &player1 ) )\n"
			<< "		return -3;\n\n"
			<< "	if ( !PlayerStart( player1 ) )\n"
			<< "		return -4;\n\n"
			<< "	while ( PlayerIsActive( player1 ) )\n\t{\n"
			<< "		Sleep( 1 );\n\t};\n\n"

			<< "	DestroyPlayer( player1 );\n"
			<< "# ifdef _WIN32\n"
			<< "	FreeLibrary( module );\n"
			<< "# else\n"
			<< "	dlclose( module );\n"
			<< "# endif\n"
			<< "	return 0;\n"
			<< "}\n";

		FileWStream		file{ fs::path{_directory}.append( "main.cpp" ) };
		CHECK_ERR( file.IsOpen() );
		CHECK_ERR( file.Write( StringView(str) ));

		return true;
	}
	
/*
=================================================
	_GenCMake
=================================================
*/
	bool VulkanTraceConverter::_GenCMake () const
	{
		String	str;
		str << "cmake_minimum_required (VERSION 3.6.0)\n\n"
			<< "project( \"" << _fileName << "\" LANGUAGES C CXX )\n\n"
			<< "add_executable( \"" << _fileName << "\" \"main.cpp\" )\n\n";
		
		FileWStream		file{ fs::path{_directory}.append( "CMakeLists.txt" ) };
		CHECK_ERR( file.IsOpen() );
		CHECK_ERR( file.Write( StringView(str) ));

		return true;
	}

/*
=================================================
	_PackData
=================================================
*/
	bool VulkanTraceConverter::_PackData (INOUT TracePacker &packer) const
	{
		uint64_t	total_size = 0;

		for (auto& data : _dataAccess)
		{
			packer.Begin( EPacketID::SetData );
			packer << data.first.dataId;
			packer << data.first.offset;
			packer << data.first.size;
			packer << data.second.min;
			packer << data.second.max;
			packer.End( EPacketID::SetData );

			total_size += data.first.size;
		}

		FG_LOGI( "total data size: "s << ToString(BytesU(total_size)) );
		return true;
	}

/*
=================================================
	_EndOfTrace
=================================================
*/
	void VulkanTraceConverter::_EndOfTrace (INOUT TracePacker &packer) const
	{
		packer.Begin( EPacketID::End );
		packer.End( EPacketID::End );
	}

/*
=================================================
	_ConvertFunction
=================================================
*/
	bool VulkanTraceConverter::_ConvertFunction (const TraceRange::Iterator &iter, FrameID frameId)
	{
		_tracePacker->SetCurrentPos( iter.GetBookmark() );

		switch ( iter->packet_id )
		{
			// skip some packets
			case VKTRACE_TPI_VK_vkCreateSwapchainKHR :				break;
			case VKTRACE_TPI_VK_vkCreateSharedSwapchainsKHR :		break;

			// remap queue family index
			/*case VKTRACE_TPI_VK_vkCreateCommandPool :				CHECK_ERR( _OnCreateCommandPool( iter, INOUT *_tracePacker ));			break;
			case VKTRACE_TPI_VK_vkCreateBuffer :					CHECK_ERR( _OnCreateBuffer( iter, INOUT *_tracePacker ));				break;
			case VKTRACE_TPI_VK_vkCreateImage :						CHECK_ERR( _OnCreateImage( iter, INOUT *_tracePacker ));				break;
			*/
			// load data from file and call function
			case VKTRACE_TPI_VK_vkCreateShaderModule :				CHECK_ERR( _OnCreateShaderModule( iter, frameId, INOUT *_tracePacker ));					break;
			case VKTRACE_TPI_VK_vkCreatePipelineCache :				CHECK_ERR( _OnCreatePipelineCache( iter, frameId, INOUT *_tracePacker ));					break;
			case VKTRACE_TPI_VK_vkCmdUpdateBuffer :					CHECK_ERR( _OnCmdUpdateBuffer( iter, frameId, INOUT *_tracePacker ));						break;
			case VKTRACE_TPI_VK_vkCmdPushDescriptorSetWithTemplateKHR :	CHECK_ERR( _OnCmdPushDescriptorSetWithTemplate( iter, frameId, INOUT *_tracePacker ));	break;
			case VKTRACE_TPI_VK_vkUpdateDescriptorSetWithTemplate :	CHECK_ERR( _OnUpdateDescriptorSetWithTemplate( iter, frameId, INOUT *_tracePacker ));		break;

			// remap swapchain images
			case VKTRACE_TPI_VK_vkAcquireNextImageKHR :				CHECK_ERR( _OnAcquireNextImage( iter, INOUT *_tracePacker ));			break;
			case VKTRACE_TPI_VK_vkAcquireNextImage2KHR :			ASSERT(false);															break;	// TODO
			case VKTRACE_TPI_VK_vkQueuePresentKHR :					CHECK_ERR( _OnQueuePresent( iter, INOUT *_tracePacker ));				break;
			case VKTRACE_TPI_VK_vkCreateRenderPass :				CHECK_ERR( _OnCreateRenderPass( iter, INOUT *_tracePacker ));			break;
				
			// remap swapchain images adn queue family index
			case VKTRACE_TPI_VK_vkCmdWaitEvents :					CHECK_ERR( _OnCmdWaitEvents( iter, INOUT *_tracePacker ));				break;
			case VKTRACE_TPI_VK_vkCmdPipelineBarrier :				CHECK_ERR( _OnCmdPipelineBarrier( iter, INOUT *_tracePacker ));			break;

			/*
			//case VKTRACE_TPI_VK_vkGetDeviceMemoryCommitment :		CHECK_ERR( _OnGetDeviceMemoryCommitment( iter, INOUT *_tracePacker ));	break;
					
			case VKTRACE_TPI_VK_vkCreatePipelineCache :				CHECK_ERR( _OnCreatePipelineCache( iter, INOUT *_tracePacker ));		break;
			case VKTRACE_TPI_VK_vkDestroyPipelineCache :			CHECK_ERR( _OnDestroyPipelineCache( iter, INOUT *_tracePacker ));		break;
					
					
			case VKTRACE_TPI_VK_vkUpdateDescriptorSetWithTemplateKHR :	break;
			case VKTRACE_TPI_VK_vkCmdPushDescriptorSetWithTemplateKHR : break;
			case VKTRACE_TPI_VK_vkUpdateDescriptorSetWithTemplate : break;
			*/

			// remap memory
			case VKTRACE_TPI_VK_vkAllocateMemory :					CHECK_ERR( _OnAllocateMemory( iter, INOUT *_tracePacker ));				break;
			case VKTRACE_TPI_VK_vkFreeMemory :						CHECK_ERR( _OnFreeMemory( iter, INOUT *_tracePacker ));					break;
			case VKTRACE_TPI_VK_vkMapMemory :						CHECK_ERR( _OnMapMemory( iter, INOUT *_tracePacker ));					break;
			case VKTRACE_TPI_VK_vkUnmapMemory :						CHECK_ERR( _OnUnmapMemory( iter, INOUT *_tracePacker ));				break;
			case VKTRACE_TPI_VK_vkFlushMappedMemoryRanges :			CHECK_ERR( _OnFlushMappedMemoryRanges( iter, frameId, INOUT *_tracePacker ));	break;
			case VKTRACE_TPI_VK_vkInvalidateMappedMemoryRanges :	break;
			case VKTRACE_TPI_VK_vkBindBufferMemory :				CHECK_ERR( _OnBindBufferMemory( iter, INOUT *_tracePacker ));			break;
			case VKTRACE_TPI_VK_vkBindImageMemory :					CHECK_ERR( _OnBindImageMemory( iter, INOUT *_tracePacker ));			break;
			case VKTRACE_TPI_VK_vkBindBufferMemory2 :
			case VKTRACE_TPI_VK_vkBindBufferMemory2KHR :			CHECK_ERR( _OnBindBufferMemory2( iter, INOUT *_tracePacker ));			break;
			case VKTRACE_TPI_VK_vkBindImageMemory2 :
			case VKTRACE_TPI_VK_vkBindImageMemory2KHR :				CHECK_ERR( _OnBindImageMemory2( iter, INOUT *_tracePacker ));			break;
			case VKTRACE_TPI_VK_vkDestroyBuffer :					CHECK_ERR( _OnDestroyBuffer( iter, INOUT *_tracePacker ));				break;
			case VKTRACE_TPI_VK_vkDestroyImage :					CHECK_ERR( _OnDestroyImage( iter, INOUT *_tracePacker ));				break;

			// use default serializer
			default :												CHECK_ERR( _ConvertVkFunction( iter, INOUT *_tracePacker ));			break;
		}
		return true;
	}

/*
=================================================
	_ConvertVkFunction
=================================================
*/
	bool VulkanTraceConverter::_ConvertVkFunction (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const
	{
#		ifdef _MSC_VER
#			pragma warning (push)
#			pragma warning (disable: 4505)
#			pragma warning (disable: 4189)
#		endif

#		include "Generated/VulkanTraceFuncPacker.h"

#		ifdef _MSC_VER
#			pragma warning (pop)
#		endif

		return true;
	}

/*
=================================================
	_RequestData
=================================================
*/
	VulkanTraceConverter::DataID  VulkanTraceConverter::_RequestData (uint64_t offset, uint64_t size, FrameID frameId)
	{
		DataAccessInfo	info{ offset, size };
		auto			data_iter = _dataAccess.find( info );

		// create new data
		if ( data_iter == _dataAccess.end() )
		{
			info.dataId = _dataCounter++;
			data_iter	= _dataAccess.insert({ info, {} }).first;
		}

		data_iter->second.min = Min( data_iter->second.min, frameId );
		data_iter->second.max = Max( data_iter->second.max, frameId );

		return data_iter->first.dataId;
	}
	
	VulkanTraceConverter::DataID  VulkanTraceConverter::_RequestData (const TraceRange::Iterator &pos, const void* hdr, const void *member, uint64_t size, FrameID frameId)
	{
		return _RequestData( _appTrace->FullTrace().GetPositionInFile( pos, hdr, member ), size, frameId );
	}
	
/*
=================================================
	_OnAcquireNextImage
=================================================
*/
	bool VulkanTraceConverter::_OnAcquireNextImage (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		auto&	packet = pos.Cast< packet_vkAcquireNextImageKHR >();
		VK_CHECK( packet.result );
		
		auto*	swapchain = _swapchainAnalyzer->GetSwapchain( ResourceID(packet.swapchain), pos.GetBookmark() );
		CHECK_ERR( swapchain );
		CHECK_ERR( *packet.pImageIndex < swapchain->images.size() );

		packer.Begin( EPacketID::VAcquireNextImageKHR );
		{
			packer << packet.device;
			packer << packet.swapchain;
			packer << packet.timeout;
			packer << packet.semaphore;
			packer << packet.fence;
			packer << VkImage(swapchain->images[ *packet.pImageIndex ].id);
		}
		packer.End( EPacketID::VAcquireNextImageKHR );

		return true;
	}
	
/*
=================================================
	_OnQueuePresent
=================================================
*/
	bool VulkanTraceConverter::_OnQueuePresent (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		auto&	packet = pos.Cast< packet_vkQueuePresentKHR >();
		VK_CHECK( packet.result );
		CHECK_ERR( packet.pPresentInfo );
		CHECK_ERR( packet.pPresentInfo->pNext == null );
		CHECK_ERR( packet.pPresentInfo->swapchainCount == 1 );
		
		auto*	swapchain = _swapchainAnalyzer->GetSwapchain( ResourceID(packet.pPresentInfo->pSwapchains[0]), pos.GetBookmark() );
		CHECK_ERR( swapchain );

		packer.Begin( EPacketID::VQueuePresentKHR );
		{
			packer << packet.queue;
			packer << VkImage(swapchain->images[ *packet.pPresentInfo->pImageIndices ].id);
			packer << packet.pPresentInfo->waitSemaphoreCount;

			packer.Push( packet.pPresentInfo->pWaitSemaphores );
			 for (uint i = 0; i < packet.pPresentInfo->waitSemaphoreCount; ++i) {
				packer << packet.pPresentInfo->pWaitSemaphores[i];
			 }
			packer.PopAndStore( packet.pPresentInfo->pWaitSemaphores );
		}
		packer.End( EPacketID::VQueuePresentKHR );

		return true;
	}
	
/*
=================================================
	IsPresentLayout
=================================================
*/
	ND_ inline bool  IsPresentLayout (VkImageLayout layout)
	{
		if ( layout == VK_IMAGE_LAYOUT_PRESENT_SRC_KHR or
			 layout == VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR )
		{
			return true;
		}
		return false;
	}

/*
=================================================
	_OnCreateRenderPass
=================================================
*/
	bool VulkanTraceConverter::_OnCreateRenderPass (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		// replace image layouts with *present* by *transfer*
		if ( _config.indirectSwapchain )
		{
			auto&	packet = pos.Cast< packet_vkCreateRenderPass >();

			for (uint i = 0; i < packet.pCreateInfo->attachmentCount; ++i)
			{
				auto&	attachment = const_cast<VkAttachmentDescription *>( packet.pCreateInfo->pAttachments )[i];

				if ( IsPresentLayout( attachment.initialLayout ) )
					attachment.initialLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;	// from blit command

				if ( IsPresentLayout( attachment.finalLayout ) )
					attachment.finalLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;		// to blit command
			}
		}
			
		return _ConvertVkFunction( pos, packer );
	}
	
/*
=================================================
	_OnWaitEvents2
=================================================
*/
	bool VulkanTraceConverter::_OnWaitEvents2 (const TraceRange::Iterator &pos) const
	{
		// replace image layouts with *present* by *transfer*
		if ( _config.indirectSwapchain )
		{
			auto&	packet = pos.Cast< packet_vkCmdWaitEvents >();

			for (uint i = 0; i < packet.imageMemoryBarrierCount; ++i)
			{
				auto&	barrier = const_cast<VkImageMemoryBarrier *>( packet.pImageMemoryBarriers )[i];

				if ( IsPresentLayout( barrier.oldLayout ) )
					barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;	// from blit command

				if ( IsPresentLayout( barrier.newLayout ) )
					barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;	// to blit command
			}
		}
		return true;
	}
	
/*
=================================================
	_OnPipelineBarrier2
=================================================
*/
	bool VulkanTraceConverter::_OnPipelineBarrier2 (const TraceRange::Iterator &pos) const
	{
		// replace image layouts with *present* by *transfer*
		if ( _config.indirectSwapchain )
		{
			auto&	packet = pos.Cast< packet_vkCmdPipelineBarrier >();

			for (uint i = 0; i < packet.imageMemoryBarrierCount; ++i)
			{
				auto&	barrier = const_cast<VkImageMemoryBarrier *>( packet.pImageMemoryBarriers )[i];

				if ( IsPresentLayout( barrier.oldLayout ) )
					barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;	// from blit command

				if ( IsPresentLayout( barrier.newLayout ) )
					barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;	// to blit command
			}
		}
		return true;
	}

/*
=================================================
	_OnCmdWaitEvents
=================================================
*/
	bool VulkanTraceConverter::_OnCmdWaitEvents (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		CHECK_ERR( _OnWaitEvents2( pos ));
		//CHECK_ERR( _OnWaitEvents3( pos ));
		return _ConvertVkFunction( pos, packer );
	}
	
/*
=================================================
	_OnCmdPipelineBarrier
=================================================
*/
	bool VulkanTraceConverter::_OnCmdPipelineBarrier (const TraceRange::Iterator &pos, INOUT TracePacker &packer) const
	{
		CHECK_ERR( _OnPipelineBarrier2( pos ));
		//CHECK_ERR( _OnPipelineBarrier3( pos ));
		return _ConvertVkFunction( pos, packer );
	}

/*
=================================================
	_OnCreateShaderModule
=================================================
*/
	bool VulkanTraceConverter::_OnCreateShaderModule (const TraceRange::Iterator &pos, FrameID frameId, INOUT TracePacker &packer)
	{
		auto&	packet = pos.Cast< packet_vkCreateShaderModule >();
		CHECK_ERR( packet.pCreateInfo );
		VK_CHECK( packet.result );
		
		DataID		data_id = _RequestData( pos, packet.header, packet.pCreateInfo->pCode, packet.pCreateInfo->codeSize, frameId );
		CHECK_ERR( data_id != ~DataID(0) );
		
		const_cast<VkShaderModuleCreateInfo *>(packet.pCreateInfo)->pCode = null;
		const_cast<VkShaderModuleCreateInfo *>(packet.pCreateInfo)->codeSize = 0;

		packer.Begin( EPacketID::VCreateShaderModule );
		{
			packer.Push( packet.pCreateInfo );
			 VPack_VkShaderModuleCreateInfo( packet.pCreateInfo, packer );
			packer.PopAndStore( packet.pCreateInfo );

			packer << data_id;
			packer << packet.device;
			packer.Push( packet.pShaderModule );
			 packer << (*packet.pShaderModule);
			packer.PopAndStore( packet.pShaderModule );
		}
		packer.End( EPacketID::VCreateShaderModule );

		return true;
	}
	
/*
=================================================
	_OnCreatePipelineCache
=================================================
*/
	bool VulkanTraceConverter::_OnCreatePipelineCache (const TraceRange::Iterator &pos, FrameID, INOUT TracePacker &packer)
	{
		auto&	packet = pos.Cast< packet_vkCreatePipelineCache >();
		CHECK_ERR( packet.pCreateInfo );
		VK_CHECK( packet.result );

		const_cast<VkPipelineCacheCreateInfo *>(packet.pCreateInfo)->pInitialData	 = null;
		const_cast<VkPipelineCacheCreateInfo *>(packet.pCreateInfo)->initialDataSize = 0;

		packer.Begin( EPacketID::VCreatePipelineCache );
		{
			packer.Push( packet.pCreateInfo );
			 VPack_VkPipelineCacheCreateInfo( packet.pCreateInfo, packer );
			packer.PopAndStore( packet.pCreateInfo );
			
			packer << packet.device;
			packer.Push( packet.pPipelineCache );
			 packer << (*packet.pPipelineCache);
			packer.PopAndStore( packet.pPipelineCache );
		}
		packer.End( EPacketID::VCreatePipelineCache );

		return true;
	}
	
/*
=================================================
	_OnCmdUpdateBuffer
=================================================
*/
	bool VulkanTraceConverter::_OnCmdUpdateBuffer (const TraceRange::Iterator &pos, FrameID frameId, INOUT TracePacker &packer)
	{
		auto&	packet = pos.Cast< packet_vkCmdUpdateBuffer >();

		DataID		data_id = _RequestData( pos, packet.header, packet.pData, packet.dataSize, frameId );
		CHECK_ERR( data_id != ~DataID(0) );

		packer.Begin( EPacketID::VCmdUpdateBuffer );
		{
			packer << packet.commandBuffer;
			packer << packet.dstBuffer;
			packer << packet.dstOffset;
			packer << packet.dataSize;
			packer << data_id;
		}
		packer.End( EPacketID::VCmdUpdateBuffer );

		return true;
	}
	
/*
=================================================
	_OnCmdPushDescriptorSetWithTemplate
=================================================
*/
	bool VulkanTraceConverter::_OnCmdPushDescriptorSetWithTemplate (const TraceRange::Iterator &, FrameID, INOUT TracePacker &)
	{
		// TODO
		return false;
	}
	
/*
=================================================
	_OnUpdateDescriptorSetWithTemplate
=================================================
*/
	bool VulkanTraceConverter::_OnUpdateDescriptorSetWithTemplate (const TraceRange::Iterator &, FrameID, INOUT TracePacker &)
	{
		// TODO
		return false;
	}


}	// VTC
