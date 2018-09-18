// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Converters/CppVulkan/CppVulkanConverter.h"
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
#	include "Generated/VkEnumToStringImpl.h"
#	include "Generated/VkStructToStringImpl.h"

#ifdef _MSC_VER
#	pragma warning (pop)
#endif

	
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
	_OnCreateCommandPool
=================================================
*/
	bool CppVulkanConverter::_OnCreateCommandPool (const TraceRange::Iterator &iter, INOUT String &src) const
	{
		auto&	packet	= iter.Cast< packet_vkCreateCommandPool >();
		CHECK_ERR( packet.pCreateInfo );

		// remap queue family index
		//const_cast<VkCommandPoolCreateInfo *>(packet.pCreateInfo)->queueFamilyIndex =
		//	uint(_deviceAnalyzer->GetCommandPoolQueueFamily( ResourceID(*packet.pCommandPool), iter.GetBookmark() ));

		return _ConvertVkFunction( iter, INOUT src );
	}
	
/*
=================================================
	_OnCreateBuffer
=================================================
*
	bool CppVulkanConverter::_OnCreateBuffer (const TraceRange::Iterator &iter, INOUT String &src) const
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
	bool CppVulkanConverter::_OnCreateImage (const TraceRange::Iterator &iter, INOUT String &src) const
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
	bool CppVulkanConverter::_OnCmdWaitEvents (const TraceRange::Iterator &iter, INOUT String &src) const
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
	bool CppVulkanConverter::_OnCmdPipelineBarrier (const TraceRange::Iterator &iter, INOUT String &src) const
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
	bool CppVulkanConverter::_OnCreateShaderModule (const TraceRange::Iterator &iter, FrameID frameId, INOUT String &src)
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
	_OnAcquireNextImage
=================================================
*/
	bool CppVulkanConverter::_OnAcquireNextImage (const TraceRange::Iterator &iter, INOUT String &src) const
	{
		auto&	packet = iter.Cast< packet_vkAcquireNextImageKHR >();

		auto*	swapchain = _swapchainAnalyzer->GetSwapchain( ResourceID(packet.swapchain), iter.GetBookmark() );
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
	bool CppVulkanConverter::_OnQueuePresent (const TraceRange::Iterator &iter, INOUT String &src) const
	{
		auto&	packet = iter.Cast< packet_vkQueuePresentKHR >();
		CHECK_ERR( packet.pPresentInfo );
		CHECK_ERR( packet.pPresentInfo->swapchainCount == 1 );
		CHECK_ERR( packet.pPresentInfo->waitSemaphoreCount == 1 );
		
		auto*	swapchain = _swapchainAnalyzer->GetSwapchain( ResourceID(packet.pPresentInfo->pSwapchains[0]), iter.GetBookmark() );
		CHECK_ERR( swapchain );

		src << "\tCHECK( app.Present( "
			<< "QueueID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT, packet.queue ) << "), "
			<< "ImageID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, swapchain->images[ *packet.pPresentInfo->pImageIndices ].id ) << "), "
			<< "SemaphoreID(" << (*_resRemapper)( VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT, *packet.pPresentInfo->pWaitSemaphores ) << ") ));\n";

		return true;
	}
	
}	// VTC
