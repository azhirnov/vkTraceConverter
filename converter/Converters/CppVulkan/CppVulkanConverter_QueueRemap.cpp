// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Converters/CppVulkan/CppVulkanConverter.h"
#include "extensions/vulkan_loader/VulkanCheckError.h"

namespace VTC
{

#	include "Generated/VkEnumToString.h"
#	include "Generated/VkStructToString.h"


/*
=================================================
	_OnCreateCommandPool
=================================================
*
	bool CppVulkanConverter::_OnCreateCommandPool (const TraceRange::Iterator &iter, INOUT String &src) const
	{
		auto&	packet	= iter.Cast< packet_vkCreateCommandPool >();
		CHECK_ERR( packet.pCreateInfo );

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
	*/

}	// VTC
