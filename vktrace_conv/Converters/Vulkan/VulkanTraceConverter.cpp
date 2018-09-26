// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Converters/Vulkan/VulkanTraceConverter.h"
#include "extensions/vulkan_loader/VulkanCheckError.h"

namespace VTC
{
	using VPacker = TracePacker;
	
#	include "Generated/VulkanTraceStructPacker.h"
#	include "Generated/VulkanTraceStructPackerImpl.h"

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
		_projName{ fs::path{cfg.outputDirectory}.filename().string() << "-vk" }
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

			_tracePacker.reset( new TracePacker{ _resourcesBookmarks });
		}

		const FrameID	last_frame	= Min( _config.lastFrame, appTrace.GetFrameCount() );

		// convert packets
		for (FrameID i = FrameID(0); i < last_frame; ++i)
		{
			auto	frame_trace = appTrace.GetFrameTrace( i );

			for (auto iter = frame_trace.begin(); iter < frame_trace.LastBookmark(); ++iter)
			{
				CHECK_ERR( _ConvertFunction( iter, i ));
			}
		}

		_appTrace = null;
		_tracePacker.reset();
		return true;
	}
	
/*
=================================================
	_ConvertFunction
=================================================
*/
	bool VulkanTraceConverter::_ConvertFunction (const TraceRange::Iterator &iter, FrameID frameId)
	{
		_tracePacker->Flush();
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
			case VKTRACE_TPI_VK_vkCmdWaitEvents :					CHECK_ERR( _OnCmdWaitEvents( iter, INOUT *_tracePacker ));				break;
			case VKTRACE_TPI_VK_vkCmdPipelineBarrier :				CHECK_ERR( _OnCmdPipelineBarrier( iter, INOUT *_tracePacker ));			break;
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
	_OnAcquireNextImage
=================================================
*/
	bool VulkanTraceConverter::_OnAcquireNextImage (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const
	{
		return false;
	}
	
/*
=================================================
	_OnQueuePresent
=================================================
*/
	bool VulkanTraceConverter::_OnQueuePresent (const TraceRange::Iterator &iter, INOUT TracePacker &packer) const
	{
		return false;
	}
	
/*
=================================================
	_OnCreateShaderModule
=================================================
*/
	bool VulkanTraceConverter::_OnCreateShaderModule (const TraceRange::Iterator &iter, FrameID frameId, INOUT TracePacker &packer)
	{
		return false;
	}
	
/*
=================================================
	_OnCreatePipelineCache
=================================================
*/
	bool VulkanTraceConverter::_OnCreatePipelineCache (const TraceRange::Iterator &iter, FrameID frameId, INOUT TracePacker &packer)
	{
		return false;
	}
	
/*
=================================================
	_OnCmdUpdateBuffer
=================================================
*/
	bool VulkanTraceConverter::_OnCmdUpdateBuffer (const TraceRange::Iterator &iter, FrameID frameId, INOUT TracePacker &packer)
	{
		return false;
	}
	
/*
=================================================
	_OnCmdPushDescriptorSetWithTemplate
=================================================
*/
	bool VulkanTraceConverter::_OnCmdPushDescriptorSetWithTemplate (const TraceRange::Iterator &iter, FrameID frameId, INOUT TracePacker &packer)
	{
		return false;
	}
	
/*
=================================================
	_OnUpdateDescriptorSetWithTemplate
=================================================
*/
	bool VulkanTraceConverter::_OnUpdateDescriptorSetWithTemplate (const TraceRange::Iterator &iter, FrameID frameId, INOUT TracePacker &packer)
	{
		return false;
	}


}	// VTC
