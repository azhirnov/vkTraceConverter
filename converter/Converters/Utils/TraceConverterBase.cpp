// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Converters/Utils/TraceConverterBase.h"
#include "Converters/Utils/TracePacker.h"
#include "Converters/Utils/BasicTypesConverter.h"

namespace VTC
{

/*
=================================================
	FindBestInstance
=================================================
*/
	static AllResourcesBookmarks::ResourceInfo_t const*  FindBestInstance (Ptr<const AllResourcesBookmarks> analyzer)
	{
		auto*	map = analyzer->GetResourcesByType( VK_OBJECT_TYPE_INSTANCE );
		CHECK_ERR( map );

		AllResourcesBookmarks::ResourceInfo_t const*	result = null;

		for (auto& item : *map)
		for (auto& inst : item.second)
		{
			if ( result )
			{
				BytesU	curr_range	= (result->LastBookmark().pos.Value() - result->FirstBookmark().pos.Value());
				BytesU	new_range	= (inst.LastBookmark().pos.Value() - inst.FirstBookmark().pos.Value());

				if ( new_range > curr_range )
					result = &inst;
			}
			else
				result = &inst;
		}

		CHECK_ERR( result );
		return result;
	}

/*
=================================================
	_PackVulkanCreateInfo
=================================================
*/
	bool TraceConverterBase::_PackVulkanCreateInfo (VulkanCreateInfo::EImplFlags implFlags, INOUT TracePacker &packer) const
	{
		using ESwapchainType	= VulkanCreateInfo::ESwapchainType;
		using EImplFlags		= VulkanCreateInfo::EImplFlags;

		VulkanCreateInfo		ci	= {};
		TraceRange::Bookmark	pos;
		const uint64_t			sw_count = _resourcesBookmarks->GetUniqueResourceCountByType( VK_OBJECT_TYPE_SWAPCHAIN_KHR );

		CHECK_ERR( sw_count <= 1 );
		CHECK_ERR( sw_count == 0 or not _swapchainAnalyzer->GetSwapchains().empty() );
		CHECK_ERR( _resourcesBookmarks->GetResourceCountByType( VK_OBJECT_TYPE_INSTANCE ) > 0 );
		
		auto		first_bm		= _appTrace->GetFrameTrace( FrameID(0) ).begin().GetBookmark();

		auto&		instance		= *FindBestInstance( _resourcesBookmarks );
		auto*		instance_info	= _deviceAnalyzer->GetInstanceInfo( instance.id, first_bm );
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
		ci.instanceID				= VkInstance(instance.id);

		ci.deviceExtensionCount		= uint(dev_extensions.size());
		ci.deviceExtensions			= dev_extensions.data();
		ci.physicalDeviceID			= VkPhysicalDevice(device_info->physicalDevice);
		ci.deviceID					= VkDevice(device_info->id);

		ci.queueCount				= uint(queue_ids.size());
		ci.queueIDs					= queue_ids.data();
		ci.queueFamilies			= queue_flags.data();
		ci.queuePriorities			= queue_priorities.data();

		ci.implementationFlags		= implFlags;
		ci.swapchainType			= ESwapchainType::WithoutSwapchain;

		if ( swapchain )
		{
			pos = std::max( pos, swapchain->FirstBookmark().pos );

			ci.swapchainID				= VkSwapchainKHR( swapchain->id );
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
		packer.Begin( EPacketID::CreateVkDevice );
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
		packer.End( EPacketID::CreateVkDevice );

		return true;
	}
	
/*
=================================================
	_GenMain
=================================================
*/
	bool TraceConverterBase::_GenMain (StringView windowTitle, StringView inputTraceFile, const fs::path &convertedTraceFile, const fs::path &outputFile) const
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
			<< "	HMODULE module = ::LoadLibraryA( \"VTPlayer.dll\" );\n"
			<< "	if ( module == nullptr )\n"
			<< "		return -1;\n\n"
			<< "	PFN_CreatePlayer	CreatePlayer	= reinterpret_cast<PFN_CreatePlayer>(GetProcAddress( module, \"CreatePlayer\" ));\n"
			<< "	PFN_DestroyPlayer	DestroyPlayer	= reinterpret_cast<PFN_DestroyPlayer>(GetProcAddress( module, \"DestroyPlayer\" ));\n"
			<< "	PFN_PlayerStart		PlayerStart		= reinterpret_cast<PFN_PlayerStart>(GetProcAddress( module, \"PlayerStart\" ));\n"
			<< "	PFN_PlayerPause		PlayerPause		= reinterpret_cast<PFN_PlayerPause>(GetProcAddress( module, \"PlayerPause\" ));\n"
			<< "	PFN_PlayerIsActive	PlayerIsActive	= reinterpret_cast<PFN_PlayerIsActive>(GetProcAddress( module, \"PlayerIsActive\" ));\n"
			<< "	const auto			FreeModule		= [] (HMODULE mod) { ::FreeLibrary( mod ); };\n"
			<< "	const auto			Yeld			= [] () { ::Sleep( 1 ); };\n"
			<< "# else\n"
			<< "	void* module = ::dlopen( \"VTPlayer.so\", RTLD_NOW | RTLD_LOCAL );\n"
			<< "	if ( module == nullptr )\n"
			<< "		return -1;\n\n"
			<< "	PFN_CreatePlayer	CreatePlayer	= reinterpret_cast<PFN_CreatePlayer>(dlsym( module, \"CreatePlayer\" ));\n"
			<< "	PFN_DestroyPlayer	DestroyPlayer	= reinterpret_cast<PFN_DestroyPlayer>(dlsym( module, \"DestroyPlayer\" ));\n"
			<< "	PFN_PlayerStart		PlayerStart		= reinterpret_cast<PFN_PlayerStart>(dlsym( module, \"PlayerStart\" ));\n"
			<< "	PFN_PlayerPause		PlayerPause		= reinterpret_cast<PFN_PlayerPause>(dlsym( module, \"PlayerPause\" ));\n"
			<< "	PFN_PlayerIsActive	PlayerIsActive	= reinterpret_cast<PFN_PlayerIsActive>(dlsym( module, \"PlayerIsActive\" ));\n"
			<< "	const auto			FreeModule		= [] (HMODULE mod) { ::dlclose( mod ); };\n"
			<< "	const auto			Yeld			= [] () { ::Sleep( 1 ); };\n"
			<< "# endif\n\n"

			<< "	if ( !CreatePlayer || !DestroyPlayer || !PlayerStart || !PlayerPause || !PlayerIsActive )\n"
			<< "		return -2;\n\n"

			<< "	VTPlayerInstance	player1  = nullptr;\n"
			<< "	VTPlayerSettings	settings = {};\n"
			<< "	settings.structSize			= sizeof(settings);\n"
			<< "	settings.playerVersion		= VTPLAYER_VERSION_LATEST;\n"
			<< "	settings.playerTraceFile	= \"" << ConvertToCStyleString( convertedTraceFile.string() ) << "\";\n"
			<< "	settings.playerDataFile		= \"" << ConvertToCStyleString( inputTraceFile ) << "\";\n"
			<< "	settings.playerDebugMode	= 0;\n"
			<< "	settings.playerTestMode		= 0;\n"
			<< "	settings.playerBenchmarkMode= 0;\n"
			<< "	settings.windowWidth		= " << ToString( width ) << ";\n"
			<< "	settings.windowHeight		= " << ToString( height ) << ";\n"
			<< "	settings.windowTitle		= \"" << windowTitle << "\";\n"
			<< "	settings.windowFPSinTitle	= 1;\n"
			<< "	settings.windowResizable	= 1;\n"
			<< "	settings.preferredGPUName	= nullptr;\n"
			<< "	settings.swapchainVkPresentMode = ~0u;\n"
			<< "	settings.swapchainVkPreTransform = ~0u;\n"
			<< "	settings.swapchainVkCompositeAlpha = ~0u;\n\n"

			<< "	if ( !CreatePlayer( &settings, OUT &player1 ) )\n"
			<< "		return -3;\n\n"
			<< "	if ( !PlayerStart( player1 ) )\n"
			<< "		return -4;\n\n"
			<< "	while ( PlayerIsActive( player1 ) )\n\t{\n"
			<< "		Yeld();\n\t};\n\n"

			<< "	DestroyPlayer( player1 );\n"
			<< "	FreeModule( module );\n"
			<< "	return 0;\n"
			<< "}\n";

		FileWStream		file{ outputFile };
		CHECK_ERR( file.IsOpen() );
		CHECK_ERR( file.Write( StringView(str) ));

		return true;
	}
	
/*
=================================================
	_GenCMake
=================================================
*/
	bool TraceConverterBase::_GenCMake (StringView projectName, const fs::path &outputFile) const
	{
		String	str;
		str << "cmake_minimum_required (VERSION 3.6.0)\n\n"
			<< "project( \"" << projectName << "\" LANGUAGES C CXX )\n\n"
			<< "add_executable( \"" << projectName << "\" \"main.cpp\" )\n\n";
		
		FileWStream		file{ outputFile };
		CHECK_ERR( file.IsOpen() );
		CHECK_ERR( file.Write( StringView(str) ));

		return true;
	}
	
/*
=================================================
	_PackData
=================================================
*/
	bool TraceConverterBase::_PackData (INOUT TracePacker &packer) const
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
	_RequestData
=================================================
*/
	TraceConverterBase::DataID  TraceConverterBase::_RequestData (uint64_t offset, uint64_t size, FrameID frameId)
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
	
	TraceConverterBase::DataID  TraceConverterBase::_RequestData (const TraceRange::Iterator &pos, const void* hdr, const void *member, uint64_t size, FrameID frameId)
	{
		return _RequestData( _appTrace->FullTrace().GetPositionInFile( pos, hdr, member ), size, frameId );
	}

/*
=================================================
	_EndOfTrace
=================================================
*/
	void TraceConverterBase::_EndOfTrace (INOUT TracePacker &packer) const
	{
		packer.Begin( EPacketID::End );
		packer.End( EPacketID::End );
	}


}	// VTC
