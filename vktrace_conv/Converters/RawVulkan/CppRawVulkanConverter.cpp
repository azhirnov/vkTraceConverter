// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Converters/RawVulkan/CppRawVulkanConverter.h"
#include "extensions/vulkan_loader/VulkanCheckError.h"

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
		FG_TIMEPROFILER();

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
		_directory{ fs::path{cfg.outputDirectory}.append("vk-cpp") },
		_dataDir{ fs::path{cfg.outputDirectory}.append("data") },			// TODO
		_inputFile{ cfg.inputTraceFile },
		_projName{ fs::path{cfg.outputDirectory}.filename().string() << "-vk" }
	{
		if ( not fs::exists( _directory ) ) {
			CHECK( fs::create_directories( _directory ));
		}

		_tempStr1.reserve( 1024 );
		_tempStr2.reserve( 1024 );
	}
	
/*
=================================================
	Run
=================================================
*/
	bool CppRawVulkanConverter::Run (const AppTrace &trace)
	{
		// initialization
		{
			_appTrace		= &trace;
			_dataCounter	= 0;
			_dataSize		= 0;

			// request analyzers
			_swapchainAnalyzer	= trace.GetAnalyzer< SwapchainAnalyzer >();
			_resourcesBookmarks	= trace.GetAnalyzer< AllResourcesBookmarks >();
			_deviceAnalyzer		= trace.GetAnalyzer< DeviceAnalyzer >();

			CHECK_ERR( _swapchainAnalyzer and _resourcesBookmarks and _deviceAnalyzer );

			_resRemapper.reset( new ResRemapper{ _resourcesBookmarks });
		}

		const FrameID	last_frame	= Min( _config.lastFrame, trace.GetFrameCount() );

		// convert packets
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
	_ConvertVkFunction
=================================================
*/
	bool CppRawVulkanConverter::_ConvertVkFunction (const TraceRange::Iterator &iter, INOUT String &src)
	{
		const StringView	indent		= "\t";
		String&				result		= _tempStr1;
		String&				before		= _tempStr2;
		NameSerializer&		nameSer		= _nameSerializer;
		ResRemapper&		remapper	= *_resRemapper;

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

		for (auto iter = trace.begin(); iter < trace.LastBookmark(); ++iter)
		{
			PerThread &		thread	= per_thread_source[ iter->thread_id ];

			_resRemapper->SetCurrentPos( iter.GetBookmark() );


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
			
			switch ( iter->packet_id )
			{
				// skip some packets
				case VKTRACE_TPI_VK_vkCreateSwapchainKHR :				break;
				case VKTRACE_TPI_VK_vkCreateSharedSwapchainsKHR :		break;

				// remap queue family index
				case VKTRACE_TPI_VK_vkCreateCommandPool :				CHECK( _OnCreateCommandPool( iter, INOUT src ));						break;
				//case VKTRACE_TPI_VK_vkCreateBuffer :					CHECK( _OnCreateBuffer( iter, INOUT src ));								break;
				//case VKTRACE_TPI_VK_vkCreateImage :						CHECK( _OnCreateImage( iter, INOUT src ));								break;
				//case VKTRACE_TPI_VK_vkCmdWaitEvents :					CHECK( _OnCmdWaitEvents( iter, INOUT src ));							break;
				//case VKTRACE_TPI_VK_vkCmdPipelineBarrier :				CHECK( _OnCmdPipelineBarrier( iter, INOUT src ));						break;

				// load data from file and call function
				case VKTRACE_TPI_VK_vkCreateShaderModule :				CHECK( _OnCreateShaderModule( iter, frameIndex, INOUT src ));			break;
				case VKTRACE_TPI_VK_vkMapMemory :						CHECK( _OnMapMemory( iter, INOUT src ));								break;
				case VKTRACE_TPI_VK_vkUnmapMemory :						CHECK( _OnUnmapMemory( iter, INOUT src ));								break;
				case VKTRACE_TPI_VK_vkFlushMappedMemoryRanges :			/*CHECK( _OnFlushMappedMemoryRanges( iter, frameIndex, INOUT src ));*/	break;
				case VKTRACE_TPI_VK_vkInvalidateMappedMemoryRanges :	/*CHECK( _OnInvalidateMappedMemoryRanges( iter, frameIndex, INOUT src ));*/	break;

				case VKTRACE_TPI_VK_vkAcquireNextImageKHR :				CHECK( _OnAcquireNextImage( iter, INOUT src ));				break;
				case VKTRACE_TPI_VK_vkAcquireNextImage2KHR :			ASSERT(false);												break;		// TODO
				case VKTRACE_TPI_VK_vkQueuePresentKHR :					CHECK( _OnQueuePresent( iter, INOUT src ));					break;

				/*
				//case VKTRACE_TPI_VK_vkGetDeviceMemoryCommitment :		CHECK( _OnGetDeviceMemoryCommitment( iter, INOUT src ));	break;
					
				case VKTRACE_TPI_VK_vkCreatePipelineCache :				CHECK( _OnCreatePipelineCache( iter, INOUT src ));			break;
				case VKTRACE_TPI_VK_vkDestroyPipelineCache :			CHECK( _OnDestroyPipelineCache( iter, INOUT src ));			break;
					
					
				case VKTRACE_TPI_VK_vkUpdateDescriptorSetWithTemplateKHR :	break;
				case VKTRACE_TPI_VK_vkCmdPushDescriptorSetWithTemplateKHR : break;
				case VKTRACE_TPI_VK_vkUpdateDescriptorSetWithTemplate : break;
				*/
				default :		_ConvertVkFunction( iter, INOUT src );
			}

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
		
		str << "target_compile_definitions( \"" << _projName << "\" PRIVATE $<$<CONFIG:Debug>: ${PROJECTS_SHARED_DEFINES_DEBUG}> )\n"
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

		//str << "add_definitions( \"-DDATA_PATH=\\\"" << ConvertToCStyleString( _dataDir.string() ) << "\\\"\" )\n";
		
#	if defined(FG_ENABLE_GLFW)
		str << "add_definitions( -DFG_ENABLE_GLFW )\n";
#	endif
#	if defined(FG_ENABLE_SDL2)
		str << "add_definitions( -DFG_ENABLE_SDL2 )\n";
#	endif
		str << "add_definitions(-D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -D_LARGE_FILES -DNOMINMAX)\n"
			<< "add_definitions(-D__STDC_LIMIT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_CONSTANT_MACROS)\n";

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

		auto&	swapchain	= *_swapchainAnalyzer->GetSwapchains().begin();
		auto	first_bm	= _appTrace->GetFrameTrace( first ).begin().GetBookmark();

		String	str;
		str << "#include \"Common.h\"\n\n";
		str << "int main ()\n{\n";
		str << "	VApp  app;\n\n";

		CHECK_ERR( _InitializeResources( INOUT str ));

		str << "\n	CHECK_ERR( app.CreateWindow( " << ToString( swapchain.second.createInfo.imageExtent.width )
					+ ", " << ToString( swapchain.second.createInfo.imageExtent.height ) << ", \"" << _projName << "\" ));\n\n";

		CHECK_ERR( _SetupDevice( first_bm, INOUT str ));
		CHECK_ERR( _SetupSwapchain( swapchain.first, swapchain.second.createInfo, INOUT str ));
		CHECK_ERR( _SetupResourceFiles( INOUT str ));

		CHECK_ERR( _SetupDrawFrames( first, last, INOUT str ));

		str << "}\n\n";


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
			uint	count = _resourcesBookmarks->GetResourceCountByType( res_type.first );

			if ( not count )
				continue;

			str << "	app.AllocateResources( " << res_type.second << '(' << IntToString(count) << ") );\n";
		}
		return true;
	}

/*
=================================================
	_SetupSwapchain
=================================================
*/
	bool CppRawVulkanConverter::_SetupDevice (TraceRange::Bookmark pos, INOUT String &str) const
	{
		CHECK_ERR( _resourcesBookmarks->GetResourceCountByType( VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT ) == 1 );

		auto&	instance		= *_resourcesBookmarks->GetResourcesByType( VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT )->begin();
		auto*	instance_info	= _deviceAnalyzer->GetInstanceInfo( instance.first, pos );
		CHECK_ERR(	instance_info and
					instance_info->physicalDevices.size() and
					instance_info->logicalDevices.size() == 1 );

		ResourceID	device_id	= *instance_info->logicalDevices.begin();
		auto*		device_info	= _deviceAnalyzer->GetLogicalDeviceInfo( device_id, pos );
		CHECK_ERR( device_info );

		str << "	CHECK_ERR( app.CreateDevice(\n"
			<< "			/*instance*/ InstanceID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT, instance.first ) << "),\n"
			<< "			/*physicalDevice*/ PhysicalDeviceID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, device_info->physicalDevice ) << "),\n"
			<< "			/*logicalDevice*/ DeviceID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, device_id ) << "),\n"
			<< "			/*gpuDeviceName*/ \"\",\n"
			<< "			/*apiVersion*/ VK_API_VERSION_1_1,\n"
			<< "			/*queues*/ {";

		CHECK_ERR( _SetupQueues( pos, *device_info, INOUT str ));

		str << "},\n"
			<< "			/*instanceLayers*/ VulkanDevice::GetRecomendedInstanceLayers(),\n"
			<< "			/*instanceExtensions*/ VulkanDevice::GetRecomendedInstanceExtensions(),\n"
			<< "			/*deviceExtensions*/ VulkanDevice::GetRecomendedDeviceExtensions() ));\n\n";

		return true;
	}
	
/*
=================================================
	_SetupQueues
=================================================
*/
	bool CppRawVulkanConverter::_SetupQueues (TraceRange::Bookmark pos, const DeviceAnalyzer::LogicalDeviceInfo &deviceInfo, INOUT String &str) const
	{
		CHECK_ERR( deviceInfo.queues.size() > 0 );

		for (auto& q : deviceInfo.queues)
		{
			auto*	queue_info	= _deviceAnalyzer->GetQueueInfo( q, pos );
			CHECK_ERR( queue_info );

			if ( q != *deviceInfo.queues.begin() )
				str << ",\t\t\t\t\n";

			str << "{ QueueID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT, q ) << "), VkQueueFlags("
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
		str << "			/*swapchain*/ SwapchainKHRID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT, swapchainID ) << "),\n";
		str << "			/*swapchainImages*/ { ";
	
		for (size_t i = 0; i < images.size(); ++i) {
			for (auto& img : images) {
				if ( img.second.indexInSwapchain == i ) {
					str << (i ? ", " : "") << "ImageID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, img.first ) << ")";
					break;
				}
			}
		}
		str << " },\n";

		str << "\t\t\t/*imageAvailableSemaphore*/ SemaphoreID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT, semaphore1.second.usedInAcquire ? semaphore1.first : semaphore2.first ) << "),\n"
			<< "\t\t\t/*renderFinishedSemaphore*/ SemaphoreID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT, semaphore1.second.usedInPresent ? semaphore1.first : semaphore2.first ) << "),\n"
			<< "\t\t\t/*colorFormat*/ " << Serialize_VkFormat( createInfo.imageFormat ) << ",\n"
			<< "\t\t\t/*colorSpace*/ " << Serialize_VkColorSpaceKHR( createInfo.imageColorSpace ) << ",\n"
			<< "\t\t\t/*minImageCount*/ " << ToString( createInfo.minImageCount ) << ",\n"
			<< "\t\t\t/*imageArrayLayers*/ " << ToString( createInfo.imageArrayLayers ) << ",\n"
			<< "\t\t\t/*preTransform*/ " << Serialize_VkSurfaceTransformFlagBitsKHR( createInfo.preTransform ) << ",\n"
			<< "\t\t\t/*presentMode*/ " << Serialize_VkPresentModeKHR( createInfo.presentMode ) << ",\n"
			<< "\t\t\t/*compositeAlpha*/ " << Serialize_VkCompositeAlphaFlagBitsKHR( createInfo.compositeAlpha ) << ",\n"
			<< "\t\t\t/*colorImageUsage*/ " << Serialize_VkImageUsageFlags( createInfo.imageUsage ) << " ));\n\n";

		return true;
	}
	
/*
=================================================
	_SetupResourceFiles
=================================================
*/
	bool CppRawVulkanConverter::_SetupResourceFiles (INOUT String &str) const
	{
		// validate ranges (may be too slow)
#		if 0 //def FG_DEBUG
		for (auto& file : _dataAccess)
		{
			for (auto& data1 : file.second)
			{
				// check intersection
				for (auto& data2 : file.second)
				{
					if ( &data1 == &data2 )
						break;

					CHECK(	(data1.first.offset + data1.first.size) <= data2.first.offset or
							data1.first.offset >= (data2.first.offset + data2.first.size) );
				}
			}
		}
#		endif

		constexpr uint	maxPartSize = 16;


		// serialize
		for (auto& file : _dataAccess)
		{
			str << "	CHECK_ERR( app.AddExternalData( \"" << ConvertToCStyleString( file.first ) << "\", {\n";

			size_t	counter = 0;

			for (auto& data : file.second)
			{
				FrameID		first_frame	= ~FrameID(0);
				FrameID		last_frame	= 0;

				for (auto frame_id : data.second)
				{
					first_frame	= Min( frame_id, first_frame );
					last_frame	= Max( frame_id, last_frame );
				}

				str << (counter == 0 ? "" : ",\n")
					<< "\t\t\t\t\t\t\t\t{ DataID(" << IntToString(data.first.dataId) << "), "
					<< IntToString(data.first.offset) << ", "
					<< IntToString(data.first.size) << ", "
					<< "FrameID(" << IntToString(first_frame) << "), "
					<< "FrameID(" << IntToString(last_frame + 1) << ")"
					<< " }";

				++counter;
				
				// restart
				if ( counter > maxPartSize  and
					 &data != (--file.second.end()).operator->() )
				{
					counter = 0;
					str << "} ));\n\n"
						<< "	CHECK_ERR( app.AddExternalData( \"" << ConvertToCStyleString( file.first ) << "\", {\n";
				}
			}

			str << "} ));\n\n";
		}

		constexpr uint64_t	maxDataSizeForPreloading = 500ull << 20;	// Mb

		if ( _dataSize < maxDataSizeForPreloading )
		{
			str << "	CHECK_ERR( app.PreloadAllData() );\n\n";
		}

		FG_LOGI( "total data size: "s << ToString(BytesU(_dataSize)) );
		return true;
	}
	
/*
=================================================
	_SetupDrawFrames
=================================================
*/
	bool CppRawVulkanConverter::_SetupDrawFrames (FrameID first, FrameID last, INOUT String &str) const
	{
		str << "	const VDrawFrame_t  frames[] = {";

		for (FrameID i = first; i < last; ++i) {
			str << (i == first ? "" : ",") << ((i - first) % 8 ?  " " : "\n\t\t\t") << GetFrameFuncName( i );
		}

		str << "\n	};\n\n";
		str << "	CHECK_ERR( app.Run( frames ));\n";
			
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
	
/*
=================================================
	_RequestData
=================================================
*/
	CppRawVulkanConverter::DataID  CppRawVulkanConverter::_RequestData (const String &filename, uint64_t offset, uint64_t size, FrameID frameId)
	{
		DataAccessInfo	info{ offset, size };

		auto&	file	  = _dataAccess.insert({ filename, DatAccessInFile_t{} }).first->second;
		auto	data_iter = file.find( info );

		// create new data
		if ( data_iter == file.end() )
		{
			info.dataId = _dataCounter++;
			data_iter	= file.insert({ info, {} }).first;

			_dataSize += size;
		}

		data_iter->second.insert( frameId );

		return data_iter->first.dataId;
	}
	
	CppRawVulkanConverter::DataID  CppRawVulkanConverter::_RequestData (const String &filename, const TraceRange::Iterator &iter,
																		const void* hdr, const void *member, uint64_t size, FrameID frameId)
	{
		return _RequestData( filename, _appTrace->FullTrace().GetPositionInFile( iter, hdr, member ), size, frameId );
	}
	
/*
=================================================
	_OnCreateCommandPool
=================================================
*/
	bool CppRawVulkanConverter::_OnCreateCommandPool (const TraceRange::Iterator &iter, INOUT String &src)
	{
		auto&	packet	= iter.Cast< packet_vkCreateCommandPool >();
		CHECK_ERR( packet.pCreateInfo );

		// remap queue family index
		const_cast<VkCommandPoolCreateInfo *>(packet.pCreateInfo)->queueFamilyIndex =
			uint(_deviceAnalyzer->GetCommandPoolQueueFamily( ResourceID(*packet.pCommandPool), iter.GetBookmark() ));

		return _ConvertVkFunction( iter, INOUT src );
	}
	
/*
=================================================
	_OnCreateBuffer
=================================================
*
	bool CppRawVulkanConverter::_OnCreateBuffer (const TraceRange::Iterator &iter, INOUT String &src)
	{
		auto&	packet = iter.Cast< packet_vkCreateBuffer >();
		CHECK_ERR( packet.pCreateInfo );
		
		Array<uint>	family_indices;

		if ( packet.pCreateInfo->pQueueFamilyIndices )
		{
			auto*	family_indices = const_cast<uint *>(packet.pCreateInfo->pQueueFamilyIndices);

			for (uint i = 0; i < packet.pCreateInfo->queueFamilyIndexCount; ++i)
			{
				family_indices[i] = _deviceAnalyzer->GetBufferQueueFamily( ResourceID(packet.pBuffer), iter.GetBookmark() );
			}
		}
		
		return _ConvertVkFunction( iter, INOUT src );
	}
	
/*
=================================================
	_OnCreateImage
=================================================
*
	bool CppRawVulkanConverter::_OnCreateImage (const TraceRange::Iterator &iter, INOUT String &src)
	{
		auto&	packet = iter.Cast< packet_vkCreateImage >();
		CHECK_ERR( packet.pCreateInfo );

		Array<uint>	family_indices;

		if ( packet.pCreateInfo->pQueueFamilyIndices )
		{
			auto*	family_indices = const_cast<uint *>(packet.pCreateInfo->pQueueFamilyIndices);

			for (uint i = 0; i < packet.pCreateInfo->queueFamilyIndexCount; ++i)
			{
				family_indices[i] = _deviceAnalyzer->GetImageQueueFamily( ResourceID(packet.pImage), iter.GetBookmark() );
			}
		}

		return _ConvertVkFunction( iter, INOUT src );
	}
	
/*
=================================================
	_OnCmdWaitEvents
=================================================
*
	bool CppRawVulkanConverter::_OnCmdWaitEvents (const TraceRange::Iterator &iter, INOUT String &src)
	{
		auto&	packet = iter.Cast< packet_vkCmdWaitEvents >();

		if ( packet.pBufferMemoryBarriers )
		{
			for (uint i = 0; i < packet.bufferMemoryBarrierCount; ++i)
			{
				auto&	src_family = const_cast<uint &>(packet.pBufferMemoryBarriers[i].srcQueueFamilyIndex);
				auto&	dst_family = const_cast<uint &>(packet.pBufferMemoryBarriers[i].dstQueueFamilyIndex);

				src_family = _GetBufferQueueFamily( ResourceID(packet.pBufferMemoryBarriers[i].buffer), src_family );
				dst_family = _GetBufferQueueFamily( ResourceID(packet.pBufferMemoryBarriers[i].buffer), dst_family );
			}
		}

		if ( packet.pImageMemoryBarriers )
		{
			for (uint i = 0; i < packet.imageMemoryBarrierCount; ++i)
			{
				auto&	src_family = const_cast<uint &>(packet.pImageMemoryBarriers[i].srcQueueFamilyIndex);
				auto&	dst_family = const_cast<uint &>(packet.pImageMemoryBarriers[i].dstQueueFamilyIndex);

				src_family = _GetImageQueueFamily( ResourceID(packet.pImageMemoryBarriers[i].image), src_family );
				dst_family = _GetImageQueueFamily( ResourceID(packet.pImageMemoryBarriers[i].image), dst_family );
			}
		}

		return _ConvertVkFunction( iter, INOUT src );
	}
	
/*
=================================================
	_OnCmdPipelineBarrier
=================================================
*
	bool CppRawVulkanConverter::_OnCmdPipelineBarrier (const TraceRange::Iterator &iter, INOUT String &src)
	{
		auto&	packet = iter.Cast< packet_vkCmdPipelineBarrier >();

		if ( packet.pBufferMemoryBarriers )
		{
			for (uint i = 0; i < packet.bufferMemoryBarrierCount; ++i)
			{
				auto&	src_family = const_cast<uint &>(packet.pBufferMemoryBarriers[i].srcQueueFamilyIndex);
				auto&	dst_family = const_cast<uint &>(packet.pBufferMemoryBarriers[i].dstQueueFamilyIndex);

				src_family = _GetBufferQueueFamily( ResourceID(packet.pBufferMemoryBarriers[i].buffer), src_family );
				dst_family = _GetBufferQueueFamily( ResourceID(packet.pBufferMemoryBarriers[i].buffer), dst_family );
			}
		}

		if ( packet.pImageMemoryBarriers )
		{
			for (uint i = 0; i < packet.imageMemoryBarrierCount; ++i)
			{
				auto&	src_family = const_cast<uint &>(packet.pImageMemoryBarriers[i].srcQueueFamilyIndex);
				auto&	dst_family = const_cast<uint &>(packet.pImageMemoryBarriers[i].dstQueueFamilyIndex);

				src_family = _GetImageQueueFamily( ResourceID(packet.pImageMemoryBarriers[i].image), src_family );
				dst_family = _GetImageQueueFamily( ResourceID(packet.pImageMemoryBarriers[i].image), dst_family );
			}
		}

		return _ConvertVkFunction( iter, INOUT src );
	}

/*
=================================================
	_OnCreateShaderModule
=================================================
*/
	bool CppRawVulkanConverter::_OnCreateShaderModule (const TraceRange::Iterator &iter, FrameID frameId, INOUT String &src)
	{
		auto&	packet = iter.Cast< packet_vkCreateShaderModule >();
		CHECK_ERR( packet.pCreateInfo );

		DataID		data_id = _RequestData( _inputFile, iter, packet.header, packet.pCreateInfo->pCode, packet.pCreateInfo->codeSize, frameId );
		CHECK_ERR( data_id != ~DataID(0) );

		_nameSerializer.Clear();

		const String	ci_name = _nameSerializer.MakeUnique( &packet.pCreateInfo, "shaderModuleCreateInfo"s, "createInfo"s );

		src << "\t{\n"
			<< "\t	auto  spirv_data = app.LoadData( DataID(" << IntToString(data_id) << ") );\n"
			<< "\t	CHECK( uint64_t(spirv_data.size()) == " << IntToString(packet.pCreateInfo->codeSize) << " );\n"
			<<		SerializeStruct( BitCast<VkBaseInStructure const*>(packet.pCreateInfo->pNext), _nameSerializer, *_resRemapper, "\t\t" )
			<< "\t	VkShaderModuleCreateInfo " << ci_name << " = {};\n"
			<< "\t	" << ci_name << ".sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;\n"
			<< "\t	" << ci_name << ".pNext = " << _nameSerializer.GetPtr( packet.pCreateInfo->pNext ) << ";\n"
			<< "\t	" << ci_name << ".flags = " << Serialize_VkShaderModuleCreateFlags( packet.pCreateInfo->flags ) << ";\n"
			<< "\t	" << ci_name << ".codeSize = spirv_data.size();\n"
			<< "\t	" << ci_name << ".pCode = BitCast<uint const*>(spirv_data.data());\n"
			<< "\t	VK_CALL( app.vkCreateShaderModule(\n"
			<< "\t				/*device*/ app.GetResource(DeviceID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, packet.device ) << ")),\n"
			<< "\t				/*pCreateInfo*/ &" << ci_name << ",\n"
			<< "\t				/*pAllocator*/ null,\n"
			<< "\t				/*pShaderModule*/ &app.EditResource(ShaderModuleID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_SHADER_MODULE_EXT, *packet.pShaderModule ) << ")) ));\n"
			<< "\t}\n";

		return true;
	}
	
/*
=================================================
	_OnMapMemory
=================================================
*/
	bool CppRawVulkanConverter::_OnMapMemory (const TraceRange::Iterator &iter, INOUT String &src)
	{
		auto&	packet = iter.Cast< packet_vkMapMemory >();
		VK_CHECK( packet.result );

		src << "\t{\n"
			<< "\t	void*  mappedMem = null;\n"
			<< "\t	VK_CALL( app.vkMapMemory(\n"
			<< "\t				/*device*/ app.GetResource(DeviceID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, packet.device ) << ")),\n"
			<< "\t				/*memory*/ app.GetResource(DeviceMemoryID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, packet.memory ) << ")),\n"
			<< "\t				/*offset*/ " << IntToString( packet.offset ) << ",\n"
			<< "\t				/*size*/ " << IntToString( packet.size ) << ",\n"
			<< "\t				/*flags*/ " << Serialize_VkMemoryMapFlags( packet.flags ) << ",\n"
			<< "\t				/*ppData*/ &mappedMem ));\n"
			<< "\t	app.OnMapMemory( DeviceMemoryID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, packet.memory ) << "), mappedMem, "
						<< IntToString( packet.offset ) << ", " << IntToString( packet.size ) << " );\n"
			<< "\t}\n";

		return true;
	}
	
/*
=================================================
	_OnUnmapMemory
=================================================
*/
	bool CppRawVulkanConverter::_OnUnmapMemory (const TraceRange::Iterator &iter, INOUT String &src)
	{
		auto&	packet = iter.Cast< packet_vkUnmapMemory >();
		
		//DataID		data_id = _RequestData( _inputFile, iter, packet.header, packet.pData, , frameId );
		//CHECK_ERR( data_id != ~DataID(0) );

		src << "\tapp.vkUnmapMemory(\n"
			<< "\t		/*device*/ app.GetResource(DeviceID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, packet.device ) << ")),\n"
			<< "\t		/*memory*/ app.GetResource(DeviceMemoryID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, packet.memory ) << ")) );\n"
			<< "\tapp.OnUnmapMemory( DeviceMemoryID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, packet.memory ) << ") );\n";

		return true;
	}
	
/*
=================================================
	_OnFlushMappedMemoryRanges
=================================================
*
	bool CppRawVulkanConverter::_OnFlushMappedMemoryRanges (const TraceRange::Iterator &iter, FrameID frameId, INOUT String &src)
	{
		const StringView	indent = "\t\t";

		auto&	before = _tempStr1;
		auto&	result = _tempStr2;
		auto&	packet = iter.Cast< packet_vkFlushMappedMemoryRanges >();

		VK_CHECK( packet.result );
		CHECK_ERR( packet.memoryRangeCount > 0 and packet.pMemoryRanges );
		
		_nameSerializer.Clear();
		before.clear();
		result.clear();

		src << "\t{\n";

		const String arr_name = _nameSerializer.MakeUnique( &packet.pMemoryRanges, "memoryRanges"s, "mappedMemoryRange"s );

		before << indent << "VkMappedMemoryRange  " << arr_name << "[" << IntToString( packet.memoryRangeCount ) << "] = {};\n";
		
		for (uint i = 0; i < packet.memoryRangeCount; ++i)
		{
			Serialize2_VkMappedMemoryRange( packet.pMemoryRanges + i, String(arr_name) << "[" << IntToString(i) << "]",
										    _nameSerializer, *_resRemapper, indent, INOUT result, INOUT before );
			
			// copied from method 'gpuMemory::copyMappingDataPageGuard(const void *)' in 'vkreplay_objmapper_class_defs.h'
#		ifdef USE_PAGEGUARD_SPEEDUP
			const bool	pageguard_speedup = true;
#		else
			const bool	pageguard_speedup = false;
#		endif

			if ( pageguard_speedup  and
				 _appTrace->GetTraceFileHeader().trace_file_version >= VKTRACE_TRACE_FILE_VERSION_5 )
			{
				PageGuardChangedBlockInfo const*	changed_info = Cast<PageGuardChangedBlockInfo>( packet.ppData[i] );

				if ( changed_info[0].length == 0 )
					continue;
				
				const void*	src_data	= packet.ppData[i] + (BytesU::SizeOf<PageGuardChangedBlockInfo>() * (changed_info[0].offset+1));
				BytesU		curr_offset;

				for (size_t j = 0; j < changed_info[0].offset; ++j)
				{
					if ( changed_info[j+1].length == 0 )
						continue;
							
					DataID	data_id = _RequestData( _inputFile, iter, packet.header, src_data + curr_offset, changed_info[j+1].length, frameId );
					CHECK_ERR( data_id != ~DataID(0) );

					CHECK_ERR( changed_info[j+1].offset >= packet.pMemoryRanges[i].offset );
					CHECK_ERR( (changed_info[j+1].offset + changed_info[j+1].length) <= (packet.pMemoryRanges[i].offset + packet.pMemoryRanges[i].size) );
						
					src << indent << "app.LoadDataToMappedMemory( DeviceMemoryID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, packet.pMemoryRanges[i].memory ) << "), "
						<< "DataID(" << IntToString( data_id ) << "), "
						<< IntToString( changed_info[j+1].offset ) << ", "
						<< IntToString( changed_info[j+1].length ) << " );\n";

					curr_offset += changed_info[j+1].length;
				}
			}
			else
			{
				DataID	data_id = _RequestData( _inputFile, iter, packet.header, packet.ppData + i, packet.pMemoryRanges[i].size, frameId );
				CHECK_ERR( data_id != ~DataID(0) );

				src << indent << "app.LoadDataToMappedMemory( DeviceMemoryID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, packet.pMemoryRanges[i].memory ) << "), "
					<< "DataID(" << IntToString( data_id ) << "), "
					<< IntToString( packet.pMemoryRanges[i].offset ) << ", "
					<< IntToString( packet.pMemoryRanges[i].size ) << " );\n";
			}
		}

		result << indent << "VK_CALL( app.vkFlushMappedMemoryRanges( \n";
		result << indent << "		/*device* / " << "app.GetResource(DeviceID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT, packet.device ) << "))";
		result << ",\n";
		result << indent << "		/*memoryRangeCount* / " << IntToString( packet.memoryRangeCount );
		result << ",\n";
		result << indent << "		/*pMemoryRanges* / " << _nameSerializer.Get( &packet.pMemoryRanges );
		result << " ));\n";

		src << before << result << "\t}\n";
		return true;
	}
	
/*
=================================================
	_OnInvalidateMappedMemoryRanges
=================================================
*
	bool CppRawVulkanConverter::_OnInvalidateMappedMemoryRanges (const TraceRange::Iterator &iter, FrameID frameId, INOUT String &src)
	{
#	if 1
		(void)(frameId);
		return _ConvertVkFunction( iter, INOUT src );

#	else
		// TODO: test loaded data with current memory
#	endif
	}
	
/*
=================================================
	_OnAcquireNextImage
=================================================
*/
	bool CppRawVulkanConverter::_OnAcquireNextImage (const TraceRange::Iterator &iter, INOUT String &src)
	{
		auto&	packet = iter.Cast< packet_vkAcquireNextImageKHR >();

		auto	swapchain = _swapchainAnalyzer->GetSwapchains().find( ResourceID(packet.swapchain) );
		CHECK_ERR( swapchain != _swapchainAnalyzer->GetSwapchains().end() );
		CHECK_ERR( *packet.pImageIndex < swapchain->second.images.size() );

		src << "\tCHECK( app.AcquireImage( "
			<< "ImageID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, swapchain->second.images[ *packet.pImageIndex ] ) << "), "
			<< "SemaphoreID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT, packet.semaphore ) << ") ));\n";

		return true;
	}
	
/*
=================================================
	_OnQueuePresent
=================================================
*/
	bool CppRawVulkanConverter::_OnQueuePresent (const TraceRange::Iterator &iter, INOUT String &src)
	{
		auto&	packet = iter.Cast< packet_vkQueuePresentKHR >();
		CHECK_ERR( packet.pPresentInfo );
		CHECK_ERR( packet.pPresentInfo->swapchainCount == 1 );
		CHECK_ERR( packet.pPresentInfo->waitSemaphoreCount == 1 );
		
		auto	swapchain = _swapchainAnalyzer->GetSwapchains().find( ResourceID(*packet.pPresentInfo->pSwapchains) );
		CHECK_ERR( swapchain != _swapchainAnalyzer->GetSwapchains().end() );

		src << "\tCHECK( app.Present( "
			<< "QueueID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT, packet.queue ) << "), "
			<< "ImageID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, swapchain->second.images[ *packet.pPresentInfo->pImageIndices ] ) << "), "
			<< "SemaphoreID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT, *packet.pPresentInfo->pWaitSemaphores ) << ") ));\n";

		return true;
	}


}	// VTC
