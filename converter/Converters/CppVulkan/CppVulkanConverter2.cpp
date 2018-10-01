// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Converters/CppVulkan/CppVulkanConverter.h"
#include "extensions/vulkan_loader/VulkanCheckError.h"
#include "Converters/Utils/BasicTypesConverter.h"

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
#	include "Generated/VkEnumToStringImpl.h"
#	include "Generated/VkStructToStringImpl.h"

#ifdef _MSC_VER
#	pragma warning (pop)
#endif


/*
=================================================
	_ConvertFunction
=================================================
*/
	bool CppVulkanConverter::_ConvertFunction (const TraceRange::Iterator &pos, FrameID frameId, INOUT String &src)
	{
		_resRemapper->SetCurrentPos( pos.GetBookmark() );
			
		_tempStr1.clear();
		_tempStr2.clear();
		_nameSerializer.Clear();

		switch ( pos->packet_id )
		{
			// skip some packets
			case VKTRACE_TPI_VK_vkCreateSwapchainKHR :				break;
			case VKTRACE_TPI_VK_vkCreateSharedSwapchainsKHR :		ASSERT(!"not supported");										break;

			// remap queue family index
			/*case VKTRACE_TPI_VK_vkCreateCommandPool :				CHECK_ERR( _OnCreateCommandPool( pos, INOUT src ));				break;
			case VKTRACE_TPI_VK_vkCreateBuffer :					CHECK_ERR( _OnCreateBuffer( pos, INOUT src ));					break;
			case VKTRACE_TPI_VK_vkCreateImage :						CHECK_ERR( _OnCreateImage( pos, INOUT src ));					break;
			case VKTRACE_TPI_VK_vkCmdWaitEvents :					CHECK_ERR( _OnCmdWaitEvents( pos, INOUT src ));					break;
			case VKTRACE_TPI_VK_vkCmdPipelineBarrier :				CHECK_ERR( _OnCmdPipelineBarrier( pos, INOUT src ));			break;
			*/
			// load data from file and call function
			case VKTRACE_TPI_VK_vkCreateShaderModule :				CHECK_ERR( _OnCreateShaderModule( pos, frameId, INOUT src ));	break;
			case VKTRACE_TPI_VK_vkCreatePipelineCache :				CHECK_ERR( _OnCreatePipelineCache( pos, INOUT src ));			break;

			// remap swapchain images
			case VKTRACE_TPI_VK_vkAcquireNextImageKHR :				CHECK_ERR( _OnAcquireNextImage( pos, INOUT src ));				break;
			case VKTRACE_TPI_VK_vkAcquireNextImage2KHR :			ASSERT(!"not supported");										break;
			case VKTRACE_TPI_VK_vkQueuePresentKHR :					CHECK_ERR( _OnQueuePresent( pos, INOUT src ));					break;


			/*
			//case VKTRACE_TPI_VK_vkGetDeviceMemoryCommitment :		CHECK_ERR( _OnGetDeviceMemoryCommitment( pos, INOUT src ));		break;
					
			case VKTRACE_TPI_VK_vkDestroyPipelineCache :			CHECK_ERR( _OnDestroyPipelineCache( pos, INOUT src ));			break;
					
					
			case VKTRACE_TPI_VK_vkUpdateDescriptorSetWithTemplateKHR :	break;
			case VKTRACE_TPI_VK_vkCmdPushDescriptorSetWithTemplateKHR : break;
			case VKTRACE_TPI_VK_vkUpdateDescriptorSetWithTemplate : break;
			*/

			// remap memory
			case VKTRACE_TPI_VK_vkAllocateMemory :					CHECK_ERR( _OnAllocateMemory( pos, INOUT src ));				break;
			case VKTRACE_TPI_VK_vkFreeMemory :						CHECK_ERR( _OnFreeMemory( pos, INOUT src ));					break;
			case VKTRACE_TPI_VK_vkMapMemory :						CHECK_ERR( _OnMapMemory( pos, INOUT src ));						break;
			case VKTRACE_TPI_VK_vkUnmapMemory :						CHECK_ERR( _OnUnmapMemory( pos, INOUT src ));					break;
			case VKTRACE_TPI_VK_vkFlushMappedMemoryRanges :			CHECK_ERR( _OnFlushMappedMemoryRanges( pos, frameId, INOUT src ));	break;
			case VKTRACE_TPI_VK_vkInvalidateMappedMemoryRanges :	break;	// unused
			case VKTRACE_TPI_VK_vkBindBufferMemory :				CHECK_ERR( _OnBindBufferMemory( pos, INOUT src ));				break;
			case VKTRACE_TPI_VK_vkBindImageMemory :					CHECK_ERR( _OnBindImageMemory( pos, INOUT src ));				break;
			case VKTRACE_TPI_VK_vkBindBufferMemory2 :
			case VKTRACE_TPI_VK_vkBindBufferMemory2KHR :			CHECK_ERR( _OnBindBufferMemory2( pos, INOUT src ));				break;
			case VKTRACE_TPI_VK_vkBindImageMemory2 :
			case VKTRACE_TPI_VK_vkBindImageMemory2KHR :				CHECK_ERR( _OnBindImageMemory2( pos, INOUT src ));				break;
			case VKTRACE_TPI_VK_vkDestroyBuffer :					CHECK_ERR( _OnDestroyBuffer( pos, INOUT src ));					break;
			case VKTRACE_TPI_VK_vkDestroyImage :					CHECK_ERR( _OnDestroyImage( pos, INOUT src ));					break;

			// use default serializer
			default :												CHECK_ERR( _ConvertVkFunction( pos, INOUT src ));				break;
		}
		return true;
	}

/*
=================================================
	_ConvertVkFunction
=================================================
*/
	bool CppVulkanConverter::_ConvertVkFunction (const TraceRange::Iterator &iter, INOUT String &src) const
	{
		const StringView	indent		= "\t";
		String&				result		= _tempStr1;
		String&				before		= _tempStr2;
		NameSerializer&		nameSer		= _nameSerializer;
		ResRemapper&		remapper	= *_resRemapper;

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
	_OnCreateShaderModule
=================================================
*/
	bool CppVulkanConverter::_OnCreateShaderModule (const TraceRange::Iterator &pos, FrameID frameId, INOUT String &src)
	{
		auto&	packet = pos.Cast< packet_vkCreateShaderModule >();
		CHECK_ERR( packet.pCreateInfo );
		VK_CHECK( packet.result );

		DataID		data_id = _RequestData( _inputFile, pos, packet.header, packet.pCreateInfo->pCode, packet.pCreateInfo->codeSize, frameId );
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
	_OnCreatePipelineCache
=================================================
*/
	bool CppVulkanConverter::_OnCreatePipelineCache (const TraceRange::Iterator &pos, INOUT String &src)
	{
		auto&	packet = pos.Cast< packet_vkCreatePipelineCache >();
		VK_CHECK( packet.result );
		
		const_cast<VkPipelineCacheCreateInfo*>(packet.pCreateInfo)->initialDataSize	= 0;
		const_cast<VkPipelineCacheCreateInfo*>(packet.pCreateInfo)->pInitialData	= null;

		return _ConvertVkFunction( pos, INOUT src );
	}

/*
=================================================
	_OnAcquireNextImage
=================================================
*/
	bool CppVulkanConverter::_OnAcquireNextImage (const TraceRange::Iterator &pos, INOUT String &src) const
	{
		auto&	packet = pos.Cast< packet_vkAcquireNextImageKHR >();
		VK_CHECK( packet.result );

		auto*	swapchain = _swapchainAnalyzer->GetSwapchain( ResourceID(packet.swapchain), pos.GetBookmark() );
		CHECK_ERR( swapchain );
		CHECK_ERR( *packet.pImageIndex < swapchain->images.size() );

		src << "\tCHECK( app.AcquireImage( "
			<< "ImageID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, swapchain->images[ *packet.pImageIndex ].id ) << "), "
			<< "SemaphoreID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT, packet.semaphore ) << ") ));\n";

		return true;
	}
	
/*
=================================================
	_OnQueuePresent
=================================================
*/
	bool CppVulkanConverter::_OnQueuePresent (const TraceRange::Iterator &pos, INOUT String &src) const
	{
		auto&	packet = pos.Cast< packet_vkQueuePresentKHR >();
		VK_CHECK( packet.result );
		CHECK_ERR( packet.pPresentInfo );
		CHECK_ERR( packet.pPresentInfo->swapchainCount == 1 );
		CHECK_ERR( packet.pPresentInfo->waitSemaphoreCount == 1 );
		
		auto*	swapchain = _swapchainAnalyzer->GetSwapchain( ResourceID(packet.pPresentInfo->pSwapchains[0]), pos.GetBookmark() );
		CHECK_ERR( swapchain );

		src << "\tCHECK( app.Present( "
			<< "QueueID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT, packet.queue ) << "), "
			<< "ImageID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, swapchain->images[ *packet.pPresentInfo->pImageIndices ].id ) << "), "
			<< "SemaphoreID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT, *packet.pPresentInfo->pWaitSemaphores ) << ") ));\n";

		return true;
	}
	
}	// VTC
