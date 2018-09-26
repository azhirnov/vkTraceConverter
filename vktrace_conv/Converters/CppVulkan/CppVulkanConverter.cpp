// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Converters/CppVulkan/CppVulkanConverter.h"
#include "extensions/vulkan_loader/VulkanCheckError.h"

namespace VTC
{
#	include "Generated/VkEnumToString.h"

/*
=================================================
	RunConverter_VulkanCppSource
=================================================
*/
	bool RunConverter_VulkanCppSource (const AppTrace &trace, const ConverterConfig &config)
	{
		FG_TIMEPROFILER();

		CppVulkanConverter	conv{ config };

		return conv.Run( trace );
	}
	
/*
=================================================
	constructor
=================================================
*/
	CppVulkanConverter::CppVulkanConverter (const ConverterConfig &cfg) :
		_config{ cfg.conveters.vulkanCppSource },
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
	bool CppVulkanConverter::Run (const AppTrace &appTrace)
	{
		// initialization
		{
			_appTrace		= &appTrace;
			_dataCounter	= 0;
			_dataSize		= 0;

			// request analyzers
			_swapchainAnalyzer		= appTrace.GetAnalyzer< SwapchainAnalyzer >();
			_resourcesBookmarks		= appTrace.GetAnalyzer< AllResourcesBookmarks >();
			_deviceAnalyzer			= appTrace.GetAnalyzer< DeviceAnalyzer >();
			_memTransferAnalyzer	= appTrace.GetAnalyzer< MemoryTransferAnalyzer >();
			_memoryObjAnalyzer		= appTrace.GetAnalyzer< MemoryObjAnalyzer >();
			_imageAnalyzer			= appTrace.GetAnalyzer< ImageAnalyzer >();
			_bufferAnalyzer			= appTrace.GetAnalyzer< BufferAnalyzer >();

			CHECK_ERR( _swapchainAnalyzer and _resourcesBookmarks and _deviceAnalyzer );
			CHECK_ERR( _memTransferAnalyzer );
			CHECK_ERR( _memoryObjAnalyzer and _imageAnalyzer and _bufferAnalyzer );

			_resRemapper.reset( new ResRemapper{ _resourcesBookmarks });
		}

		const FrameID	last_frame	= Min( _config.lastFrame, appTrace.GetFrameCount() );

		// convert packets
		for (FrameID i = _config.firstFrame; i < last_frame; ++i)
		{
			CHECK_ERR( _ConvertFrame( i, appTrace.GetFrameTrace( i ) ));
		}


		CHECK_ERR( _GenCommonFile( _config.firstFrame, last_frame ));
		CHECK_ERR( _GenCMakeFile( _config.firstFrame, last_frame ));
		CHECK_ERR( _GenMain( _config.firstFrame, last_frame ));

		_appTrace = null;
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
	bool CppVulkanConverter::_ConvertFrame (const FrameID frameIndex, const TraceRange &trace)
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
			
			_tempStr1.clear();
			_tempStr2.clear();
			_nameSerializer.Clear();


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
				//case VKTRACE_TPI_VK_vkCreateCommandPool :				CHECK( _OnCreateCommandPool( iter, INOUT src ));						break;
				//case VKTRACE_TPI_VK_vkCreateBuffer :					CHECK( _OnCreateBuffer( iter, INOUT src ));								break;
				//case VKTRACE_TPI_VK_vkCreateImage :						CHECK( _OnCreateImage( iter, INOUT src ));								break;
				//case VKTRACE_TPI_VK_vkCmdWaitEvents :					CHECK( _OnCmdWaitEvents( iter, INOUT src ));							break;
				//case VKTRACE_TPI_VK_vkCmdPipelineBarrier :				CHECK( _OnCmdPipelineBarrier( iter, INOUT src ));						break;

				// load data from file and call function
				case VKTRACE_TPI_VK_vkCreateShaderModule :				CHECK( _OnCreateShaderModule( iter, frameIndex, INOUT src ));			break;

				// remap swapchain images
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

				// remap memory
				case VKTRACE_TPI_VK_vkAllocateMemory :					CHECK( _OnAllocateMemory( iter, INOUT src ));				break;
				case VKTRACE_TPI_VK_vkFreeMemory :						CHECK( _OnFreeMemory( iter, INOUT src ));					break;
				case VKTRACE_TPI_VK_vkMapMemory :						CHECK( _OnMapMemory( iter, INOUT src ));					break;
				case VKTRACE_TPI_VK_vkUnmapMemory :						CHECK( _OnUnmapMemory( iter, INOUT src ));					break;
				case VKTRACE_TPI_VK_vkFlushMappedMemoryRanges :			CHECK( _OnFlushMappedMemoryRanges( iter, frameIndex, INOUT src ));	break;
				case VKTRACE_TPI_VK_vkInvalidateMappedMemoryRanges :	break;
				case VKTRACE_TPI_VK_vkBindBufferMemory :				CHECK( _OnBindBufferMemory( iter, INOUT src ));				break;
				case VKTRACE_TPI_VK_vkBindImageMemory :					CHECK( _OnBindImageMemory( iter, INOUT src ));				break;
				case VKTRACE_TPI_VK_vkBindBufferMemory2 :
				case VKTRACE_TPI_VK_vkBindBufferMemory2KHR :			CHECK( _OnBindBufferMemory2( iter, INOUT src ));			break;
				case VKTRACE_TPI_VK_vkBindImageMemory2 :
				case VKTRACE_TPI_VK_vkBindImageMemory2KHR :				CHECK( _OnBindImageMemory2( iter, INOUT src ));				break;
				case VKTRACE_TPI_VK_vkDestroyBuffer :					CHECK( _OnDestroyBuffer( iter, INOUT src ));				break;
				case VKTRACE_TPI_VK_vkDestroyImage :					CHECK( _OnDestroyImage( iter, INOUT src ));					break;

				// use default serializer
				default :												_ConvertVkFunction( iter, INOUT src );						break;
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
	bool CppVulkanConverter::_GenCommonFile (const FrameID first, const FrameID last) const
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
	bool CppVulkanConverter::_GenCMakeFile (const FrameID first, const FrameID last) const
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
		str << "add_definitions( -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -D_LARGE_FILES -DNOMINMAX )\n"
			<< "add_definitions( -D__STDC_LIMIT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_CONSTANT_MACROS )\n";

		str << "add_definitions( -DVTC_MEMORY_REMAPPING=" << IntToString( int(_config.remapMemory) ) << " )\n";


		const fs::path	fname = fs::path{_directory}.append( "CMakeLists.txt" );

		CHECK_ERR( _StoreFile( fname, str ));
		return true;
	}
	
/*
=================================================
	_GenMain
=================================================
*/
	bool CppVulkanConverter::_GenMain (const FrameID first, const FrameID last) const
	{
		CHECK_ERR( _resourcesBookmarks->GetUniqueResourceCountByType( VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT ) == 1 );
		CHECK_ERR( not _swapchainAnalyzer->GetSwapchains().empty() );

		auto&	swapchain	= _swapchainAnalyzer->GetSwapchains().begin()->second.front();
		auto	first_bm	= _appTrace->GetFrameTrace( first ).begin().GetBookmark();

		String	str;
		str << "#include \"Common.h\"\n\n";
		str << "int main ()\n{\n";
		str << "	VApp  app;\n\n";

		CHECK_ERR( _InitializeResources( INOUT str ));

		str << "\n	CHECK_ERR( app.CreateWindow( " << ToString( swapchain.createInfo.imageExtent.width )
					+ ", " << ToString( swapchain.createInfo.imageExtent.height ) << ", \"" << _projName << "\" ));\n\n";

		CHECK_ERR( _SetupDevice( first_bm, INOUT str ));
		CHECK_ERR( _SetupSwapchain( swapchain, INOUT str ));
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
	bool CppVulkanConverter::_InitializeResources (INOUT String &str) const
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
			uint64_t	count = _resourcesBookmarks->GetResourceCountByType( res_type.first );

			if ( not count )
				continue;

			str << "	app.AllocateResources( " << res_type.second << '(' << IntToString(count) << ") );\n";
		}
		return true;
	}

/*
=================================================
	_SetupDevice
=================================================
*/
	bool CppVulkanConverter::_SetupDevice (TraceRange::Bookmark pos, INOUT String &str) const
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
	bool CppVulkanConverter::_SetupQueues (TraceRange::Bookmark pos, const DeviceAnalyzer::LogicalDeviceInfo &deviceInfo, INOUT String &str) const
	{
		auto*	phys_dev = _deviceAnalyzer->GetPhysicalDeviceInfo( deviceInfo.physicalDevice, pos );
		CHECK_ERR( phys_dev );

		bool	is_first = true;

		for (auto& q : deviceInfo.queues)
		{
			CHECK_ERR( q.queueFamilyIndex < phys_dev->queueFamilyProperties.size() );

			auto&	props = phys_dev->queueFamilyProperties[ q.queueFamilyIndex ];

			for (size_t i = 0; i < q.instances.size(); ++i)
			{
				auto&	inst = q.instances[i];

				if ( inst.id == ResourceID(0) )
					continue;

				if ( not is_first )
					str << ",\t\t\t\t\n";

				str << "{ QueueID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT, inst.id ) << "), VkQueueFlags("
					<< (props.presentSupported ? "VK_QUEUE_PRESENT_BIT | " : "")
					<< Serialize_VkQueueFlags( props.props.queueFlags )
					<< "), " << FloatToString( inst.priority ) << " }";

				is_first = false;
			}
		}
		return true;
	}

/*
=================================================
	_SetupSwapchain
=================================================
*/
	bool CppVulkanConverter::_SetupSwapchain (const SwapchainAnalyzer::SwapchainInfo_t &swapchain, INOUT String &str) const
	{
		CHECK_ERR( swapchain.semaphores.size() == 2 );

		auto&	semaphore1	= *swapchain.semaphores.begin();
		auto&	semaphore2	= *(++swapchain.semaphores.begin());
		auto&	images		= swapchain.images;

		CHECK_ERR(  semaphore1.second.usedInAcquire != semaphore2.second.usedInAcquire and
					semaphore1.second.usedInPresent != semaphore2.second.usedInPresent );

		str << "	CHECK_ERR( app.CreateSwapchain(\n";
		str << "			/*swapchain*/ SwapchainKHRID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT, swapchain.id ) << "),\n";
		str << "			/*swapchainImages*/ { ";
	
		for (size_t i = 0; i < images.size(); ++i)
		{
			CHECK_ERR( images[i].index == i );

			str << (i ? ", " : "") << "ImageID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, images[i].id ) << ")";
		}
		str << " },\n";

		str << "\t\t\t/*imageAvailableSemaphore*/ SemaphoreID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT, semaphore1.second.usedInAcquire ? semaphore1.first : semaphore2.first ) << "),\n"
			<< "\t\t\t/*renderFinishedSemaphore*/ SemaphoreID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT, semaphore1.second.usedInPresent ? semaphore1.first : semaphore2.first ) << "),\n"
			<< "\t\t\t/*colorFormat*/ " << Serialize_VkFormat( swapchain.createInfo.imageFormat ) << ",\n"
			<< "\t\t\t/*colorSpace*/ " << Serialize_VkColorSpaceKHR( swapchain.createInfo.imageColorSpace ) << ",\n"
			<< "\t\t\t/*minImageCount*/ " << ToString( swapchain.createInfo.minImageCount ) << ",\n"
			<< "\t\t\t/*imageArrayLayers*/ " << ToString( swapchain.createInfo.imageArrayLayers ) << ",\n"
			<< "\t\t\t/*preTransform*/ " << Serialize_VkSurfaceTransformFlagBitsKHR( swapchain.createInfo.preTransform ) << ",\n"
			<< "\t\t\t/*presentMode*/ " << Serialize_VkPresentModeKHR( swapchain.createInfo.presentMode ) << ",\n"
			<< "\t\t\t/*compositeAlpha*/ " << Serialize_VkCompositeAlphaFlagBitsKHR( swapchain.createInfo.compositeAlpha ) << ",\n"
			<< "\t\t\t/*colorImageUsage*/ " << Serialize_VkImageUsageFlags( swapchain.createInfo.imageUsage ) << " ));\n\n";

		return true;
	}
	
/*
=================================================
	_SetupResourceFiles
=================================================
*/
	bool CppVulkanConverter::_SetupResourceFiles (INOUT String &str) const
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
	bool CppVulkanConverter::_SetupDrawFrames (FrameID first, FrameID last, INOUT String &str) const
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
	bool CppVulkanConverter::_StoreFile (const fs::path &filename, StringView data) const
	{
		HddWFile	file{ filename };
		CHECK_ERR( file.IsOpen() );
		CHECK_ERR( file.Write( data ));
		return true;
	}
	
/*
=================================================
	_RequestData
=================================================
*/
	CppVulkanConverter::DataID  CppVulkanConverter::_RequestData (const String &filename, uint64_t offset, uint64_t size, FrameID frameId)
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
	
	CppVulkanConverter::DataID  CppVulkanConverter::_RequestData (const String &filename, const TraceRange::Iterator &iter,
																  const void* hdr, const void *member, uint64_t size, FrameID frameId)
	{
		return _RequestData( filename, _appTrace->FullTrace().GetPositionInFile( iter, hdr, member ), size, frameId );
	}
	

}	// VTC