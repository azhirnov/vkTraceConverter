// Copyright (c)  Zhirnov Andrey. For more information see 'LICENSE.txt'

#include "extensions/vulkan_loader/VulkanCommon.h"
#include "Converters/RawVulkan/CppRawVulkanConverter.h"
#include "Converters/Utils/NameSerializer.h"

namespace VTC
{

#ifdef _MSC_VER
#	pragma warning (push)
#	pragma warning (disable: 4505)
#	pragma warning (disable: 4127)
#	pragma warning (disable: 4100)
#endif

#	include "Generated/VkEnumToString.h"
#	include "Generated/VkStructToString.h"

#ifdef _MSC_VER
#	pragma warning (pop)
#endif

/*
=================================================
	RunConverter_CppRawVulkan
=================================================
*/
	bool RunConverter_CppRawVulkan (const AppTrace &trace, const ConverterConfig &config)
	{
		CppRawVulkanConverter	conv{ config };

		return conv.Run( trace );
	}
	
/*
=================================================
	constructor
=================================================
*/
	CppRawVulkanConverter::CppRawVulkanConverter (const ConverterConfig &cfg) :
		_config{ cfg.conveters.cppRawVulkan },
		_directory{ fs::path{cfg.directory}.append("vk-cpp") },
		_dataDir{ fs::path{cfg.directory}.append("data") },			// TODO
		_projName{ "Test" }											// TODO
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
	bool CppRawVulkanConverter::Run (const AppTrace &trace)
	{
		_appTrace = &trace;

		// request analyzers
		_imageUsageAnalyzer	= trace.GetAnalyzer< ImageUsageAnalyzer >();
		_swapchainAnalyzer	= trace.GetAnalyzer< SwapchainAnalyzer >();
		_resourcesBookmarks	= trace.GetAnalyzer< AllResourcesBookmarks >();
		_deviceAnalyzer		= trace.GetAnalyzer< DeviceAnalyzer >();

		CHECK_ERR( _imageUsageAnalyzer and _swapchainAnalyzer and _resourcesBookmarks and _deviceAnalyzer );

		_resRemapper.reset( new ResRemapper{ _resourcesBookmarks });


		const FrameID	last_frame	= Min( _config.lastFrame, trace.GetFrameCount() );

		for (FrameID i = _config.firstFrame; i < last_frame; ++i)
		{
			CHECK_ERR( _ConvertFrame( i, trace.GetFrameTrace( i ) ));
		}

		CHECK_ERR( _GenCommonFile( _config.firstFrame, last_frame ));
		CHECK_ERR( _GenCMakeFile( _config.firstFrame, last_frame ));
		CHECK_ERR( _GenMain( _config.firstFrame, last_frame ));

		_appTrace = null;
		return true;
	}
	
/*
=================================================
	ConvertFrameFunc
=================================================
*/
	static bool ConvertFrameFunc (const TraceRange::Iterator &iter, NameSerializer &nameSer, ResRemapper &remapper, String &before, String &result, INOUT String &src)
	{
		// skip some packets
		switch ( iter->packet_id )
		{
			case VKTRACE_TPI_VK_vkCreateSwapchainKHR :
			case VKTRACE_TPI_VK_vkCreateSharedSwapchainsKHR :
				return true;
		}

		const StringView	indent	= "\t";

		nameSer.Clear();
		before.clear();
		result.clear();

#		ifdef _MSC_VER
#			pragma warning (push)
#			pragma warning (disable: 4505)
#			pragma warning (disable: 4189)
#		endif

#		include "Generated/BuildRawVulkanCalls.h"

#		ifdef _MSC_VER
#			pragma warning (pop)
#		endif

		if ( before.empty() )
		{
			src << result;
		}
		else
		{
			src << indent	<< "{\n"
				<< before
				<< result
				<< indent	<< "}\n";
		}

		return true;
	}

/*
=================================================
	GetFrame***FuncName
=================================================
*/
	ND_ static String  GetFrameFuncName (FrameID frameIndex)
	{
		return "Frame"s << ToString( frameIndex );
	}

	ND_ static String  GetFrameThreadFuncName (FrameID frameIndex, ThreadID threadId)
	{
		return GetFrameFuncName( frameIndex ) << "_Thread" << ToString( threadId );
	}

	ND_ static String  GetFrameThreadPassFuncName (FrameID frameIndex, ThreadID threadId, size_t passId)
	{
		return GetFrameThreadFuncName( frameIndex, threadId ) << "_Pass" << ToString( passId );
	}

/*
=================================================
	_ConvertFrame
=================================================
*/
	bool CppRawVulkanConverter::_ConvertFrame (const FrameID frameIndex, const TraceRange &trace)
	{
		struct PerThread
		{
			String			source;
			Array<String>	passes;		// move render passes to separate functions

			ResourceID		lastComputePpln		= 0;
			ResourceID		lastDispatchPpln	= 0;

			bool			isCompute			= false;
			bool			isRPActive			= false;
		};
		using PerThreadSource_t = HashMap< ThreadID, PerThread >;


		const fs::path		fname		= fs::path{_directory}.append( GetFrameFuncName( frameIndex ) << ".cpp" );
		PerThreadSource_t	per_thread_source;
		String				preload_src;	// contains code that can be used for async loading from HDD
		
		const auto			AddPass		= [frameIndex, &per_thread_source] (ThreadID threadId)
										{
											PerThread&		thread = per_thread_source[ threadId ];

											if ( thread.passes.empty() or not thread.passes.back().empty() )
											{
												const String	func = GetFrameThreadPassFuncName( frameIndex, threadId, thread.passes.size() );

												thread.passes.push_back( "static void "s << func << " (const VApp &app)\n{\n" );

												thread.source << '\t' << func << "( app );\n";
											}
										};

		
		NameSerializer	name_ser;
		String			temp1, temp2;

		for (auto iter = trace.begin(), end = trace.end(); iter < end; ++iter)
		{
			PerThread &		thread	= per_thread_source[ iter->thread_id ];


			// check if it is begiging of new pass
			switch ( iter->packet_id )
			{
				case VKTRACE_TPI_VK_vkCmdBeginRenderPass :
				{
					AddPass( iter->thread_id );

					thread.isCompute	= false;
					thread.isRPActive	= true;
					break;
				}

				case VKTRACE_TPI_VK_vkCmdBindPipeline :
				{
					auto&	pack = iter.Cast< packet_vkCmdBindPipeline >();

					if ( pack.pipelineBindPoint == VK_PIPELINE_BIND_POINT_COMPUTE )
					{
						thread.lastComputePpln = ResourceID(pack.pipeline);
					}
					break;
				}

				case VKTRACE_TPI_VK_vkCmdDispatch :
				case VKTRACE_TPI_VK_vkCmdDispatchIndirect :
				case VKTRACE_TPI_VK_vkCmdDispatchBaseKHX :
				case VKTRACE_TPI_VK_vkCmdDispatchBase :
				{
					ASSERT( not thread.isRPActive );
					
					if ( thread.lastComputePpln != thread.lastDispatchPpln and
						 thread.lastDispatchPpln != 0 )
					{
						AddPass( iter->thread_id );
					}

					thread.lastDispatchPpln	= thread.lastComputePpln;
					thread.isCompute		= true;
					break;
				}
			}

			String &	src = thread.isRPActive ? thread.passes.back() : thread.source;

			ConvertFrameFunc( iter, name_ser, *_resRemapper, temp1, temp2, INOUT src );
			

			// check if it is ending of current pass
			switch ( iter->packet_id )
			{
				case VKTRACE_TPI_VK_vkCmdEndRenderPass :
				{
					thread.isRPActive	= false;
					break;
				}
			}
		}


		// build single source file
		{
			String	str			= "#include \"Common.h\"\n\n";
			String	main_src	= "void "s << GetFrameFuncName( frameIndex ) << " (const VApp &app)\n{\n";

			for (auto& thread : per_thread_source)
			{
				for (auto& pass : thread.second.passes)
				{
					str << pass << "}\n\n";
				}

				const String	func = GetFrameThreadFuncName( frameIndex, thread.first );

				str << "static void " << func << " (const VApp &app)\n{\n"
					<< thread.second.source
					<< "}\n"
					<< "//==============================================================================\n\n\n";

				main_src << '\t' << func << "( app );\n";
			}
			str << main_src << "}\n\n";

			CHECK_ERR( _StoreFile( fname, str ));
		}
		return true;
	}
	
/*
=================================================
	_GenCommonFile
=================================================
*/
	bool CppRawVulkanConverter::_GenCommonFile (const FrameID first, const FrameID last) const
	{
		CHECK_ERR( first < last );

		String	str;
		str << "#pragma once\n\n"
			<< "#include \"engine/Application.h\"\n\n"
			<< "using namespace VTC;\n\n";

		for (FrameID i = first; i < last; ++i) {
			str << "void " << GetFrameFuncName( i ) << " (const VApp &app);\n";
		}
		

		const fs::path	fname = fs::path{_directory}.append( "Common.h" );

		CHECK_ERR( _StoreFile( fname, str ));
		return true;
	}
	
/*
=================================================
	_GenCMakeFile
=================================================
*/
	bool CppRawVulkanConverter::_GenCMakeFile (const FrameID first, const FrameID last) const
	{
		CHECK_ERR( first < last );

		String	str;
		str << "cmake_minimum_required (VERSION 3.6.0)\n\n"
			<< "project( \"" << _projName << "\" LANGUAGES C CXX )\n"
			<< "set_property( GLOBAL PROPERTY USE_FOLDERS ON )\n\n";

		str << "include( \"" VT_FRAMEGRAPH_SOURCE_PATH "/cmake/compilers.cmake\" )\n\n"
			<< "set( FG_EXTERNALS_PATH \"" VT_FRAMEGRAPH_EXTERNAL_PATH "\" )\n"
			<< "include( \"" VT_FRAMEGRAPH_SOURCE_PATH "/cmake/download_vk.cmake\" )\n\n";

#		if 0 //def FG_ENABLE_SDL2
		str << "set( VT_ENABLE_SDL2 ON CACHE BOOL \"\" )\n";
#		endif

#		ifdef FG_ENABLE_GLFW
		str << "set( VT_ENABLE_GLFW ON CACHE BOOL \"\" )\n";
#		endif

		str << "link_directories( \"" VT_FRAMEGRAPH_LIBRARY_PATH "\" )\n\n";

		str << "set( SOURCES ";

		for (FrameID i = first; i < last; ++i) {
			str << "\n\t\t\"" << GetFrameFuncName( i ) << "\"";
		}
		str << "\n\t\t\"" VT_APPLICATION_SOURCE_PATH "/engine/Application.h\""
			<< "\n\t\t\"" VT_APPLICATION_SOURCE_PATH "/engine/Application.cpp\""
			<< "\n\t\t\"Common.h\""
			<< "\n\t\t\"main.cpp\" )\n"
			<< "add_executable( \"" << _projName << "\" ${SOURCES} )\n\n";

		//str << "target_include_directories( \"" << _projName << "\" PRIVATE \"\" )\n";
		str << "target_include_directories( \"" << _projName << "\" PRIVATE \"" VT_FRAMEGRAPH_SOURCE_PATH "\" )\n"
			<< "target_include_directories( \"" << _projName << "\" PRIVATE \"" VT_FRAMEGRAPH_SOURCE_PATH "/extensions\" )\n"
			<< "target_include_directories( \"" << _projName << "\" PRIVATE \"" VT_FRAMEGRAPH_EXTERNAL_PATH "\" )\n"
			<< "target_include_directories( \"" << _projName << "\" PRIVATE \"${Vulkan_INCLUDE_DIRS}\" )\n"
			<< "target_include_directories( \"" << _projName << "\" PRIVATE \"" VT_APPLICATION_SOURCE_PATH "\" )\n\n";
		
		str << "target_compile_options( \"" << _projName << "\" PRIVATE $<$<CONFIG:DebugAnalyze>: ${PROJECTS_SHARED_CXX_FLAGS_DEBUGANALYZE}> )\n"
			<< "target_compile_definitions( \"" << _projName << "\" PRIVATE $<$<CONFIG:DebugAnalyze>: ${PROJECTS_SHARED_DEFINES_DEBUGANALYZE}> )\n"
			<< "set_target_properties( \"" << _projName << "\" PROPERTIES LINK_FLAGS_DEBUGANALYZE ${PROJECTS_SHARED_LINKER_FLAGS_DEBUGANALYZE} )\n\n"
			<< "target_compile_definitions( \"" << _projName << "\" PRIVATE $<$<CONFIG:Debug>: ${PROJECTS_SHARED_DEFINES_DEBUG}> )\n"
			<< "set_target_properties( \"" << _projName << "\" PROPERTIES LINK_FLAGS_DEBUG ${PROJECTS_SHARED_LINKER_FLAGS_DEBUG} )\n"
			<< "target_compile_options( \"" << _projName << "\" PRIVATE $<$<CONFIG:Debug>: ${PROJECTS_SHARED_CXX_FLAGS_DEBUG}> )\n\n"
			<< "set_target_properties( \"" << _projName << "\" PROPERTIES LINK_FLAGS_RELEASE ${PROJECTS_SHARED_LINKER_FLAGS_RELEASE} )\n"
			<< "target_compile_options( \"" << _projName << "\" PRIVATE $<$<CONFIG:Release>: ${PROJECTS_SHARED_CXX_FLAGS_RELEASE}> )\n"
			<< "target_compile_definitions( \"" << _projName << "\" PRIVATE $<$<CONFIG:Release>: ${PROJECTS_SHARED_DEFINES_RELEASE}> )\n\n"
			<< "target_compile_definitions( \"" << _projName << "\" PRIVATE $<$<CONFIG:Profile>: ${PROJECTS_SHARED_DEFINES_PROFILE}> )\n"
			<< "target_compile_options( \"" << _projName << "\" PRIVATE $<$<CONFIG:Profile>: ${PROJECTS_SHARED_CXX_FLAGS_PROFILE}> )\n"
			<< "set_target_properties( \"" << _projName << "\" PROPERTIES LINK_FLAGS_PROFILE ${PROJECTS_SHARED_LINKER_FLAGS_PROFILE} )\n\n";

		str << "target_link_libraries( \"" << _projName << "\" \"STL\" \"VulkanLoader\" \"Framework\" )\n"
			<< "if (${VT_ENABLE_SDL2})\n"
			<< "	target_link_libraries( \"" << _projName << "\" \"SDL2\" )\n"
			<< "endif ()\n"
			<< "if (${VT_ENABLE_GLFW})\n"
			<< "	target_link_libraries( \"" << _projName << "\" \"glfw3\" )\n"
			<< "endif ()\n\n";

		str << R"#(add_definitions( "-DDATA_PATH=\")#";
		for (char c : _dataDir.string()) {
			switch ( c ) {
				case '\\' :		str << '\\' << '\\';	break;
				case '"' :		str << '\\' << '\"';	break;
				default :		str << c;				break;
			}
		}
		str << "\\\"\" )\n";

#	if defined(FG_ENABLE_GLFW)
		str << "add_definitions( -DFG_ENABLE_GLFW )\n";
#	endif
#	if defined(FG_ENABLE_SDL2)
		str << "add_definitions( -DFG_ENABLE_SDL2 )\n";
#	endif
		

		const fs::path	fname = fs::path{_directory}.append( "CMakeLists.txt" );

		CHECK_ERR( _StoreFile( fname, str ));
		return true;
	}
	
/*
=================================================
	_GenMain
=================================================
*/
	bool CppRawVulkanConverter::_GenMain (const FrameID first, const FrameID last) const
	{
		CHECK_ERR( _swapchainAnalyzer->GetSwapchains().size() == 1 );

		auto&	swapchain = *_swapchainAnalyzer->GetSwapchains().begin();

		String	str;
		str << "#include \"Common.h\"\n\n";
		str << "int main ()\n{\n";
		str << "	const VDrawFrame_t  frames[] = {";

		for (FrameID i = first; i < last; ++i) {
			str << (i == first ? "" : ",") << ((i - first) % 8 ?  " " : "\n\t\t\t") << GetFrameFuncName( i );
		}

		str << "\n	};\n\n";
		str << "	VApp  app;\n\n";

		CHECK_ERR( _InitializeResources( INOUT str ));

		str << "	CHECK_ERR( app.CreateWindow( " << ToString( swapchain.second.createInfo.imageExtent.width )
					+ ", " << ToString( swapchain.second.createInfo.imageExtent.height ) << ", \"" << _projName << "\" ));\n\n";

		CHECK_ERR( _SetupDevice( INOUT str ));
		CHECK_ERR( _SetupSwapchain( swapchain.first, swapchain.second.createInfo, INOUT str ));

		str << "	CHECK_ERR( app.Run( frames ));\n"
			<< "}\n\n";


		const fs::path	fname = fs::path{_directory}.append( "main.cpp" );

		CHECK_ERR( _StoreFile( fname, str ));
		return true;
	}

/*
=================================================
	_InitializeResources
=================================================
*/
	bool CppRawVulkanConverter::_InitializeResources (INOUT String &str) const
	{
		const Pair<EResourceType, StringView> resources[] = {
			{ VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT,				"InstanceID" },
			{ VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT,		"PhysicalDeviceID" },
			{ VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT,				"DeviceID" },
			{ VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT,				"QueueID" },
			{ VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT,			"SemaphoreID" },
			{ VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT,		"CommandBufferID" },
			{ VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT,				"FenceID" },
			{ VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT,		"DeviceMemoryID" },
			{ VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT,				"BufferID" },
			{ VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT,				"ImageID" },
			{ VK_DEBUG_REPORT_OBJECT_TYPE_EVENT_EXT,				"EventID" },
			{ VK_DEBUG_REPORT_OBJECT_TYPE_QUERY_POOL_EXT,			"QueryPoolID" },
			{ VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_VIEW_EXT,			"BufferViewID" },
			{ VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_VIEW_EXT,			"ImageViewID" },
			{ VK_DEBUG_REPORT_OBJECT_TYPE_SHADER_MODULE_EXT,		"ShaderModuleID" },
			{ VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_CACHE_EXT,		"PipelineCacheID" },
			{ VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_LAYOUT_EXT,		"PipelineLayoutID" },
			{ VK_DEBUG_REPORT_OBJECT_TYPE_RENDER_PASS_EXT,			"RenderPassID" },
			{ VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_EXT,				"PipelineID" },
			{ VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT_EXT,"DescriptorSetLayoutID" },
			{ VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_EXT,				"SamplerID" },
			{ VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_POOL_EXT,		"DescriptorPoolID" },
			{ VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_EXT,		"DescriptorSetID" },
			{ VK_DEBUG_REPORT_OBJECT_TYPE_FRAMEBUFFER_EXT,			"FramebufferID" },
			{ VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_POOL_EXT,			"CommandPoolID" },
			//{ VK_DEBUG_REPORT_OBJECT_TYPE_SURFACE_KHR_EXT,		"SurfaceKHRID" }
			{ VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT,		"SwapchainKHRID" }
			//{ VK_DEBUG_REPORT_OBJECT_TYPE_DISPLAY_KHR_EXT,		"DisplayKHRID" }
		};

		for (auto& res_type : resources)
		{
			auto*	objects	= _resourcesBookmarks->GetResourcesByType( res_type.first );

			if ( not objects )
				continue;

			CHECK( objects->size() < ~0u );

			str << "	app.AllocateResources( " << res_type.second << '(' << IntToString( uint(objects->size()) ) << ") );\n";
		}
		return true;
	}

/*
=================================================
	_SetupSwapchain
=================================================
*/
	bool CppRawVulkanConverter::_SetupDevice (INOUT String &str) const
	{
		auto*	instances			= _resourcesBookmarks->GetResourcesByType( VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT );
		auto*	physical_devices	= _resourcesBookmarks->GetResourcesByType( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT );
		auto*	logical_devices		= _resourcesBookmarks->GetResourcesByType( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT );

		CHECK_ERR( instances and instances->size() == 1 );
		CHECK_ERR( physical_devices );
		CHECK_ERR( logical_devices and logical_devices->size() == 1 );

		ResourceID	device_id	= logical_devices->begin()->first;
		auto*		device_info	= _deviceAnalyzer->GetLogicalDeviceInfo( device_id );
		CHECK_ERR( device_info );

		str << "	CHECK_ERR( app.CreateDevice(\n"
			<< "			/*instance*/ InstanceID(" << (*_resRemapper)(instances->begin()->first) << "),\n"
			<< "			/*physicalDevice*/ PhysicalDeviceID(" << (*_resRemapper)(device_info->physicalDevice) << "),\n"
			<< "			/*logicalDevice*/ DeviceID(" << (*_resRemapper)(device_id) << "),\n"
			<< "			/*gpuDeviceName*/ \"\",\n"
			<< "			/*apiVersion*/ VK_API_VERSION_1_1,\n"
			<< "			/*queues*/ {";

		CHECK_ERR( _SetupQueues( *device_info, INOUT str ));

		str << "},\n"
			<< "			/*instanceLayers*/ {},\n"
			<< "			/*instanceExtensions*/ {},\n"
			<< "			/*deviceExtensions*/ {} ));\n\n";

		return true;
	}
	
/*
=================================================
	_SetupQueues
=================================================
*/
	bool CppRawVulkanConverter::_SetupQueues (const DeviceAnalyzer::LogicalDeviceInfo &deviceInfo, INOUT String &str) const
	{
		CHECK_ERR( deviceInfo.queues.size() > 0 );

		for (auto& q : deviceInfo.queues)
		{
			auto*	queue_info	= _deviceAnalyzer->GetQueueInfo( q );
			CHECK_ERR( queue_info );

			if ( q != *deviceInfo.queues.begin() )
				str << ",\t\t\t\t\n";

			str << "{ QueueID(" << (*_resRemapper)(q) << "), VkQueueFlags("
				<< (queue_info->usedForPresent ? "VK_QUEUE_PRESENT_BIT | " : "")
				<< Serialize_VkQueueFlags( queue_info->props.queueFlags & queue_info->usageFlags )
				<< "), " << FloatToString(queue_info->priority) << " }";
		}
		return true;
	}

/*
=================================================
	_SetupSwapchain
=================================================
*/
	bool CppRawVulkanConverter::_SetupSwapchain (ResourceID swapchainID, const VkSwapchainCreateInfoKHR &createInfo, INOUT String &str) const
	{
		CHECK_ERR( _swapchainAnalyzer->GetSemaphores().size() == 2 );

		auto&	semaphore1	= *_swapchainAnalyzer->GetSemaphores().begin();
		auto&	semaphore2	= *(++_swapchainAnalyzer->GetSemaphores().begin());
		auto&	images		= _swapchainAnalyzer->GetImages();

		CHECK_ERR(  semaphore1.second.usedInAcquire != semaphore2.second.usedInAcquire and
					semaphore1.second.usedInPresent != semaphore2.second.usedInPresent );

		str << "	CHECK_ERR( app.CreateSwapchain(\n";
		str << "			/*swapchain*/ SwapchainKHRID(" << (*_resRemapper)(swapchainID) << "),\n";
		str << "			/*swapchainImages*/ { ";
	
		for (size_t i = 0; i < images.size(); ++i) {
			for (auto& img : images) {
				if ( img.second.indexInSwapchain == i ) {
					str << (i ? ", " : "") << "ImageID(" << (*_resRemapper)(img.first) << ")";
					break;
				}
			}
		}
		str << " },\n";

		str << "			/*imageAvailableSemaphore*/ SemaphoreID(" << (*_resRemapper)( semaphore1.second.usedInAcquire ? semaphore1.first : semaphore2.first ) << "),\n"
			<< "			/*renderFinishedSemaphore*/ SemaphoreID(" << (*_resRemapper)( semaphore1.second.usedInPresent ? semaphore1.first : semaphore2.first ) << "),\n"
			<< "			/*colorFormat*/ " << Serialize_VkFormat( createInfo.imageFormat ) << ",\n"
			<< "			/*colorSpace*/ " << Serialize_VkColorSpaceKHR( createInfo.imageColorSpace ) << ",\n"
			<< "			/*minImageCount*/ " << ToString( createInfo.minImageCount ) << ",\n"
			<< "			/*imageArrayLayers*/ " << ToString( createInfo.imageArrayLayers ) << ",\n"
			<< "			/*preTransform*/ " << Serialize_VkSurfaceTransformFlagBitsKHR( createInfo.preTransform ) << ",\n"
			<< "			/*presentMode*/ " << Serialize_VkPresentModeKHR( createInfo.presentMode ) << ",\n"
			<< "			/*compositeAlpha*/ " << Serialize_VkCompositeAlphaFlagBitsKHR( createInfo.compositeAlpha ) << ",\n"
			<< "			/*colorImageUsage*/ " << Serialize_VkImageUsageFlags( createInfo.imageUsage ) << " ));\n\n";
		return true;
	}

/*
=================================================
	_StoreFile
=================================================
*/
	bool CppRawVulkanConverter::_StoreFile (const fs::path &filename, StringView data) const
	{
		FILE*	file = null;
		CHECK_ERR( fopen_s( OUT &file, filename.string().c_str(), "wb" ) == 0 );

		CHECK( fwrite( data.data(), sizeof(data[0]), data.size(), file ) == data.size() );

		fclose( file );

		return true;
	}


}	// VTC
