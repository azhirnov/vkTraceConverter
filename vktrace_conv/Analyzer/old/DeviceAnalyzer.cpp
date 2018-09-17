// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Analyzer/old/DeviceAnalyzer.h"
#include "Analyzer/AnalyzerUtils.h"

namespace VTC
{

/*
=================================================
	constructor
=================================================
*/
	DeviceAnalyzer::DeviceAnalyzer ()
	{
	}
	
/*
=================================================
	AddResourceUsage
=================================================
*/
	void DeviceAnalyzer::AddResourceUsage (const TraceRange::Iterator &pos, EResourceType type, ResourceID id, FrameID, EResOp)
	{
		switch ( type )
		{
			case VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT :			CHECK( _ProcessInstanceUsage( pos, id ));		break;
			case VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT :	CHECK( _ProcessPhysicalDeviceUsage( pos, id ));	break;
			case VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT :			CHECK( _ProcessLogicalDeviceUsage( pos, id ));	break;
			case VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT :			CHECK( _ProcessQueueUsage( pos, id ));			break;
			case VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT :	CHECK( _ProcessCommandBufferUsage( pos, id ));	break;
		}
	}
	
/*
=================================================
	_ProcessInstanceUsage
=================================================
*/
	bool DeviceAnalyzer::_ProcessInstanceUsage (const TraceRange::Iterator &pos, ResourceID id)
	{
		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkCreateInstance :				CHECK_ERR( _OnCreateInstance( pos ));			break;
			case VKTRACE_TPI_VK_vkEnumeratePhysicalDevices :	CHECK_ERR( _OnEnumeratePhysicalDevices( pos ));	break;

			default :
				CHECK_ERR( _instances.AddResourceUsage( pos, id, 0, EResOp::Access ));
				break;
		}
		return true;
	}

/*
=================================================
	_OnCreateInstance
=================================================
*/
	bool DeviceAnalyzer::_OnCreateInstance (const TraceRange::Iterator &pos)
	{
		auto&	packet		= pos.Cast< packet_vkCreateInstance >();
		CHECK_ERR( packet.pCreateInfo );
		ASSERT( packet.pCreateInfo->pNext == null );	// add support if assert triggered

		InstancesMap_t::iterator	instance;
		CHECK_ERR( _instances.AddResourceUsage( OUT instance, pos, ResourceID(*packet.pInstance), FrameID(0), EResOp::Construct ));

		auto&	info = instance->second.back();

		for (uint i = 0; i < packet.pCreateInfo->enabledExtensionCount; ++i) {
			info.enabledExtensions.insert( packet.pCreateInfo->ppEnabledExtensionNames[i] );
		}
		for (uint i = 0; i < packet.pCreateInfo->enabledLayerCount; ++i) {
			info.enabledLayers.insert( packet.pCreateInfo->ppEnabledLayerNames[i] );
		}

		info.instanceCreateFlags	= packet.pCreateInfo->flags;
		info.applicationName		= packet.pCreateInfo->pApplicationInfo->pApplicationName;
		info.applicationVersion		= packet.pCreateInfo->pApplicationInfo->applicationVersion;
		info.engineName				= packet.pCreateInfo->pApplicationInfo->pEngineName;
		info.engineVersion			= packet.pCreateInfo->pApplicationInfo->engineVersion;
		info.apiVersion				= packet.pCreateInfo->pApplicationInfo->apiVersion;
		return true;
	}
	
/*
=================================================
	_OnEnumeratePhysicalDevices
=================================================
*/
	bool DeviceAnalyzer::_OnEnumeratePhysicalDevices (const TraceRange::Iterator &pos)
	{
		auto&	packet	= pos.Cast< packet_vkEnumeratePhysicalDevices >();
		
		InstancesMap_t::iterator	instance;
		CHECK_ERR( _instances.AddResourceUsage( OUT instance, pos, ResourceID(packet.instance), 0, EResOp::Access ));

		auto&	info = instance->second.back();

		if ( packet.pPhysicalDeviceCount )
			info.physicalDevices.resize( *packet.pPhysicalDeviceCount );

		if ( not packet.pPhysicalDevices )
			return true;
		
		for (size_t i = 0; i < info.physicalDevices.size(); ++i)
		{
			info.physicalDevices[i] = ResourceID(packet.pPhysicalDevices[i]);

			if ( not _physicalDevices.FindIn( info.physicalDevices[i], pos, false ) )
			{
				PhysicalDevicesMap_t::iterator	dev;
				CHECK( _physicalDevices.AddResourceUsage( OUT dev, pos, info.physicalDevices[i], FrameID(0), EResOp::Construct ));

				dev->second.back().instance = ResourceID(packet.instance);
			}
			else
			{
				CHECK( _physicalDevices.AddResourceUsage( pos, info.physicalDevices[i], FrameID(0), EResOp::Access ));
			}
		}
		return true;
	}

/*
=================================================
	_ProcessPhysicalDeviceUsage
=================================================
*/
	bool DeviceAnalyzer::_ProcessPhysicalDeviceUsage (const TraceRange::Iterator &pos, ResourceID id)
	{
		if ( pos->packet_id == VKTRACE_TPI_VK_vkEnumeratePhysicalDevices )
			return true;
		
		PhysicalDevicesMap_t::iterator	dev;
		CHECK_ERR( _physicalDevices.AddResourceUsage( OUT dev, pos, id, FrameID(0), EResOp::Access ));
		auto&	dev_info = dev->second.back();

		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceFeatures :
				dev_info.deviceFeatures = *pos.Cast< packet_vkGetPhysicalDeviceFeatures >().pFeatures;
				break;
			
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceProperties :
				dev_info.deviceProperties = *pos.Cast< packet_vkGetPhysicalDeviceProperties >().pProperties;
				break;

			case VKTRACE_TPI_VK_vkGetPhysicalDeviceMemoryProperties :
				dev_info.deviceMemoryProperties = *pos.Cast< packet_vkGetPhysicalDeviceMemoryProperties >().pMemoryProperties;
				break;

			case VKTRACE_TPI_VK_vkGetPhysicalDeviceQueueFamilyProperties :
				CHECK_ERR( _OnGetPhysicalDeviceQueueFamilyProperties( pos, dev_info ));
				break;

			case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceSupportKHR :
				CHECK_ERR( _OnGetPhysicalDeviceSurfaceSupportKHR( pos, dev_info ));
				break;
		}
		return true;
	}
	
/*
=================================================
	_OnGetPhysicalDeviceQueueFamilyProperties
=================================================
*/
	bool DeviceAnalyzer::_OnGetPhysicalDeviceQueueFamilyProperties (const TraceRange::Iterator &pos, PhysicalDeviceInfo &info)
	{
		auto&	packet = pos.Cast< packet_vkGetPhysicalDeviceQueueFamilyProperties >();
		
		if ( packet.pQueueFamilyPropertyCount )
			info.queueFamilyProperties.resize( *packet.pQueueFamilyPropertyCount );

		if ( packet.pQueueFamilyProperties )
		{
			for (size_t i = 0; i < info.queueFamilyProperties.size(); ++i)
			{
				info.queueFamilyProperties[i].props = packet.pQueueFamilyProperties[i];
			}
		}
		return true;
	}
	
/*
=================================================
	_OnGetPhysicalDeviceSurfaceSupportKHR
=================================================
*/
	bool DeviceAnalyzer::_OnGetPhysicalDeviceSurfaceSupportKHR (const TraceRange::Iterator &pos, PhysicalDeviceInfo &info)
	{
		auto&	packet = pos.Cast< packet_vkGetPhysicalDeviceSurfaceSupportKHR >();

		CHECK_ERR( packet.queueFamilyIndex < info.queueFamilyProperties.size() );
		
		info.queueFamilyProperties[ packet.queueFamilyIndex ].presentSupported = *packet.pSupported;
		return true;
	}

/*
=================================================
	_ProcessLogicalDeviceUsage
=================================================
*/
	bool DeviceAnalyzer::_ProcessLogicalDeviceUsage (const TraceRange::Iterator &pos, ResourceID id)
	{
		if ( pos->packet_id == VKTRACE_TPI_VK_vkCreateDevice )
			return _OnCreateDevice( pos, id );
		
		LogicalDevicesMap_t::iterator	dev;
		CHECK_ERR( _logicalDevices.AddResourceUsage( OUT dev, pos, id, FrameID(0), EResOp::Access ));

		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkGetDeviceQueue :		CHECK( _OnGetDeviceQueue( pos, id, dev->second.back() ));	break;
			case VKTRACE_TPI_VK_vkGetDeviceQueue2 :		ASSERT(false);		break;
		}
		return true;
	}
	
/*
=================================================
	_OnCreateDevice
=================================================
*/
	bool DeviceAnalyzer::_OnCreateDevice (const TraceRange::Iterator &pos, ResourceID id)
	{
		auto&	packet = pos.Cast< packet_vkCreateDevice >();

		CHECK_ERR( packet.pCreateInfo );
		CHECK_ERR( ResourceID(*packet.pDevice) == id );
		ASSERT( packet.pCreateInfo->pNext == null );	// add support if assert triggered
		
		PhysicalDeviceInfo_t*	gpu	= _physicalDevices.FindIn( ResourceID(packet.physicalDevice), pos );
		CHECK_ERR( gpu );

		InstanceInfo_t*			instance = _instances.FindIn( gpu->instance, pos );
		CHECK_ERR( instance );

		gpu->logicalDevices.insert( id );
		instance->logicalDevices.insert( id );

		LogicalDevicesMap_t::iterator	dev;
		CHECK_ERR( _logicalDevices.AddResourceUsage( OUT dev, pos, id, FrameID(0), EResOp::Construct ));

		auto&	info	= dev->second.back();

		info.deviceCreateFlags	= packet.pCreateInfo->flags;
		info.enabledFeatures	= *packet.pCreateInfo->pEnabledFeatures;
		info.physicalDevice		= ResourceID(packet.physicalDevice);

		for (uint i = 0; i < packet.pCreateInfo->enabledExtensionCount; ++i) {
			info.enabledExtensions.insert( packet.pCreateInfo->ppEnabledExtensionNames[i] );
		}
		
		for (uint i = 0; i < packet.pCreateInfo->enabledLayerCount; ++i) {
			info.enabledLayers.insert( packet.pCreateInfo->ppEnabledLayerNames[i] );
		}

		for (uint i = 0; i < packet.pCreateInfo->queueCreateInfoCount; ++i)
		{
			QueueCreateInfo	ci;
			ci.flags			= packet.pCreateInfo->pQueueCreateInfos[i].flags;
			ci.queueFamilyIndex	= packet.pCreateInfo->pQueueCreateInfos[i].queueFamilyIndex;

			for (uint j = 0; j < packet.pCreateInfo->pQueueCreateInfos[i].queueCount; ++j) {
				ci.queuesPriorities.push_back( packet.pCreateInfo->pQueueCreateInfos[i].pQueuePriorities[j] );
			}

			info.queueCreateInfos.push_back( std::move(ci) );
		}
		return true;
	}
	
/*
=================================================
	_OnGetDeviceQueue
=================================================
*/
	bool DeviceAnalyzer::_OnGetDeviceQueue (const TraceRange::Iterator &pos, ResourceID id, LogicalDeviceInfo_t &dev)
	{
		auto&	packet = pos.Cast< packet_vkGetDeviceQueue >();
		CHECK_ERR( ResourceID(packet.device) == id );

		dev.queues.insert( ResourceID(*packet.pQueue) );

		PhysicalDeviceInfo_t const*	gpu	= _physicalDevices.FindIn( dev.physicalDevice, pos );
		CHECK_ERR( gpu );
		
		QueuesMap_t::iterator	queue;
		CHECK_ERR( _queues.AddResourceUsage( OUT queue, pos, ResourceID(*packet.pQueue), FrameID(0), EResOp::Construct ));

		auto&	info = queue->second.back();

		info.familyIndex	= packet.queueFamilyIndex;
		info.queueIndex		= packet.queueIndex;
		info.logicalDevice	= ResourceID(packet.device);
		info.physicalDevice	= dev.physicalDevice;

		CHECK_ERR( info.familyIndex < gpu->queueFamilyProperties.size() );
		info.props		= gpu->queueFamilyProperties[ info.familyIndex ].props;
		info.usageFlags	= info.props.queueFlags & (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT | VK_QUEUE_TRANSFER_BIT);	// TODO: track command buffers and set correct queue usage


		// find queue create info
		bool	found	= false;
		for (auto& ci : dev.queueCreateInfos)
		{
			if ( ci.queueFamilyIndex == packet.queueFamilyIndex )
			{
				CHECK_ERR( packet.queueIndex < ci.queuesPriorities.size() );

				found				= true;
				info.createFlags	= ci.flags;
				info.priority		= ci.queuesPriorities[ info.queueIndex ];
				break;
			}
		}

		CHECK_ERR( found );
		return true;
	}
	
/*
=================================================
	_ProcessQueueUsage
=================================================
*/
	bool DeviceAnalyzer::_ProcessQueueUsage (const TraceRange::Iterator &pos, ResourceID id)
	{
		if ( pos->packet_id == VKTRACE_TPI_VK_vkGetDeviceQueue )
			return true;
		
		QueuesMap_t::iterator	queue;
		CHECK_ERR( _queues.AddResourceUsage( OUT queue, pos, id, FrameID(0), EResOp::Access ));
		
		auto&	info = queue->second.back();

		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkQueuePresentKHR :
				info.usedForPresent = true;
				break;

			case VKTRACE_TPI_VK_vkQueueBindSparse :
				info.usageFlags |= VK_QUEUE_SPARSE_BINDING_BIT;
				break;

			case VKTRACE_TPI_VK_vkQueueSubmit :
				CHECK( _OnQueueSubmit( pos, id, info ));
				break;
		}
		return true;
	}
	
/*
=================================================
	_OnQueueSubmit
=================================================
*/
	bool DeviceAnalyzer::_OnQueueSubmit (const TraceRange::Iterator &pos, ResourceID id, QueueInfo &queue)
	{
		auto&	packet = pos.Cast< packet_vkQueueSubmit >();
		CHECK( ResourceID(packet.queue) == id );

		for (uint i = 0; i < packet.submitCount; ++i)
		{
			// check for 'VK_QUEUE_PROTECTED_BIT' flag
			auto*	protect = FindVkStruct<VkProtectedSubmitInfo>( packet.pSubmits[i].pNext );
			if ( protect and protect->protectedSubmit )
				queue.usageFlags |= VK_QUEUE_PROTECTED_BIT;


			// add dependent command buffers & pools
			for (uint j = 0; j < packet.pSubmits[i].commandBufferCount; ++i)
			{
				CHECK_ERR( _QueueSubmitCommand( queue, ResourceID(packet.pSubmits[i].pCommandBuffers[j]) ));
			}
		}
		return true;
	}
	
/*
=================================================
	_QueueSubmitCommand
=================================================
*/
	bool DeviceAnalyzer::_QueueSubmitCommand (QueueInfo &queue, ResourceID cmdBufferId)
	{
		queue.commandBuffers.insert( cmdBufferId );

		auto	cmdbuf = _cmdBuffers.find( cmdBufferId );
		CHECK_ERR( cmdbuf != _cmdBuffers.end() );
		CHECK_ERR( not cmdbuf->second.recording );

		queue.commandPools.insert( cmdbuf->second.commandPool );

		// merge image usage
		for (auto& image : cmdbuf->second.imageUsage)
		{
			queue.imageUsage.insert({ image.first, {} }).first->second.push_back( image.second );
		}

		// merge buffer usage
		for (auto& buffer : cmdbuf->second.bufferUsage)
		{
			queue.bufferUsage.insert({ buffer.first, {} }).first->second.push_back( buffer.second );
		}

		// submit secondary command buffers
		for (auto& secondary : cmdbuf->second.secondaryBuffers)
		{
			CHECK_ERR( _QueueSubmitCommand( queue, secondary ));
		}

		if ( cmdbuf->second.oneTimeSubmit )
		{
			cmdbuf->second.bufferUsage.clear();
			cmdbuf->second.imageUsage.clear();
			cmdbuf->second.secondaryBuffers.clear();
		}
		return true;
	}

/*
=================================================
	_ProcessCommandBufferUsage
=================================================
*/
	bool DeviceAnalyzer::_ProcessCommandBufferUsage (const TraceRange::Iterator &pos, ResourceID id)
	{
		switch ( pos->packet_id )
		{
			// Allocate
			case VKTRACE_TPI_VK_vkAllocateCommandBuffers :
			{
				auto&	packet	= pos.Cast< packet_vkAllocateCommandBuffers >();
				CHECK_ERR( packet.pAllocateInfo );

				auto	cmdbuf = _cmdBuffers.insert({ id, CommandBufferInfo() }).first;

				cmdbuf->second.commandPool	= ResourceID(packet.pAllocateInfo->commandPool);
				cmdbuf->second.isSecondary	= (packet.pAllocateInfo->level != VK_COMMAND_BUFFER_LEVEL_PRIMARY);
				break;
			}

			// Free
			case VKTRACE_TPI_VK_vkFreeCommandBuffers :
			{
				CHECK( _cmdBuffers.erase( id ) == 1 );
				break;
			}

			// Begin
			case VKTRACE_TPI_VK_vkBeginCommandBuffer :
			{
				auto&	packet = pos.Cast< packet_vkBeginCommandBuffer >();
				CHECK_ERR( packet.pBeginInfo );
				CHECK_ERR( ResourceID(packet.commandBuffer) == id );
				
				auto	cmdbuf = _cmdBuffers.find( id );
				CHECK_ERR( cmdbuf != _cmdBuffers.end() );

				cmdbuf->second.oneTimeSubmit	= EnumEq( packet.pBeginInfo->flags, VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT );
				cmdbuf->second.recording		= true;
				cmdbuf->second.bufferUsage.clear();
				cmdbuf->second.imageUsage.clear();
				cmdbuf->second.secondaryBuffers.clear();
				break;
			}

			// End
			case VKTRACE_TPI_VK_vkEndCommandBuffer :
			{
				auto&	packet = pos.Cast< packet_vkEndCommandBuffer >();
				CHECK_ERR( ResourceID(packet.commandBuffer) == id );
				
				auto	cmdbuf = _cmdBuffers.find( id );
				CHECK_ERR( cmdbuf != _cmdBuffers.end() );

				CHECK_ERR( cmdbuf->second.recording );
				cmdbuf->second.recording = false;
				break;
			}

			// Reset
			case VKTRACE_TPI_VK_vkResetCommandBuffer :
			case VKTRACE_TPI_VK_vkResetCommandPool :
			{
				auto	cmdbuf = _cmdBuffers.find( id );
				CHECK_ERR( cmdbuf != _cmdBuffers.end() );
				CHECK_ERR( not cmdbuf->second.recording );
				
				cmdbuf->second.bufferUsage.clear();
				cmdbuf->second.imageUsage.clear();
				cmdbuf->second.secondaryBuffers.clear();
				break;
			}

			// ExecuteCommands
			case VKTRACE_TPI_VK_vkCmdExecuteCommands :
			{
				auto&	packet = pos.Cast< packet_vkCmdExecuteCommands >();
				if ( ResourceID(packet.commandBuffer) != id )
					return true; // skip secondary buffers
				
				auto	cmdbuf = _cmdBuffers.find( id );
				CHECK_ERR( cmdbuf != _cmdBuffers.end() );
				CHECK_ERR( cmdbuf->second.recording );

				for (uint i = 0; i < packet.commandBufferCount; ++i) {
					cmdbuf->second.secondaryBuffers.insert( ResourceID(packet.pCommandBuffers[i]) );
				}
				break;
			}
			
			// WaitEvents
			case VKTRACE_TPI_VK_vkCmdWaitEvents :
			{
				auto& packet = pos.Cast< packet_vkCmdWaitEvents >();

				CHECK_ERR( _OnCmdPipelineBarrier( { packet.pBufferMemoryBarriers, packet.bufferMemoryBarrierCount },
												  { packet.pImageMemoryBarriers, packet.imageMemoryBarrierCount },
												  id, pos.GetBookmark() ));
				break;
			}

			// PipelineBarrier
			case VKTRACE_TPI_VK_vkCmdPipelineBarrier :
			{
				auto&	packet = pos.Cast< packet_vkCmdPipelineBarrier >();

				CHECK_ERR( _OnCmdPipelineBarrier( { packet.pBufferMemoryBarriers, packet.bufferMemoryBarrierCount },
												  { packet.pImageMemoryBarriers, packet.imageMemoryBarrierCount },
												  id, pos.GetBookmark() ));
				break;
			}
		}
		return true;
	}
	
/*
=================================================
	_OnCmdPipelineBarrier
=================================================
*/
	bool DeviceAnalyzer::_OnCmdPipelineBarrier (ArrayView<VkBufferMemoryBarrier> bufferBarriers, ArrayView<VkImageMemoryBarrier> imageBarriers,
												ResourceID id, TraceRange::Bookmark pos)
	{
		auto	cmdbuf = _cmdBuffers.find( id );
		CHECK_ERR( cmdbuf != _cmdBuffers.end() );
		CHECK_ERR( cmdbuf->second.recording );

		// TODO: check for acquire/release

		for (auto& bufbar : bufferBarriers)
		{
			auto	result = cmdbuf->second.bufferUsage.insert({ ResourceID(bufbar.buffer), {} });

			if ( result.second ) {
				result.first->second.first	= pos;
				result.first->second.id		= ResourceID(bufbar.buffer);
			}

			result.first->second.last = pos;
		}

		for (auto& imgbar : imageBarriers)
		{
			auto	result = cmdbuf->second.imageUsage.insert({ ResourceID(imgbar.image), {} });

			if ( result.second ) {
				result.first->second.first	= pos;
				result.first->second.id		= ResourceID(imgbar.image);
			}

			result.first->second.last = pos;
		}

		return true;
	}

/*
=================================================
	GetInstanceInfo
=================================================
*/
	DeviceAnalyzer::InstanceInfo_t const*  DeviceAnalyzer::GetInstanceInfo (ResourceID id, TraceRange::Bookmark pos) const
	{
		return _instances.FindIn( id, pos, false );
	}
	
/*
=================================================
	GetPhysicalDeviceInfo
=================================================
*/
	DeviceAnalyzer::PhysicalDeviceInfo_t const*  DeviceAnalyzer::GetPhysicalDeviceInfo (ResourceID id, TraceRange::Bookmark pos) const
	{
		return _physicalDevices.FindIn( id, pos, false );
	}
	
/*
=================================================
	GetLogicalDeviceInfo
=================================================
*/
	DeviceAnalyzer::LogicalDeviceInfo_t const*  DeviceAnalyzer::GetLogicalDeviceInfo (ResourceID id, TraceRange::Bookmark pos) const
	{
		return _logicalDevices.FindIn( id, pos, false );
	}
	
/*
=================================================
	GetQueueInfo
=================================================
*/
	DeviceAnalyzer::QueueInfo_t const*  DeviceAnalyzer::GetQueueInfo (ResourceID id, TraceRange::Bookmark pos) const
	{
		return _queues.FindIn( id, pos, false );
	}
	
/*
=================================================
	GetQueueFamily
=================================================
*
	VkQueueFlags  DeviceAnalyzer::GetQueueFamily (ResourceID queueId, TraceRange::Bookmark pos) const
	{
		auto*	info = _queues.FindIn( queueId, pos, false );
		CHECK_ERR( info, VK_QUEUE_FLAG_BITS_MAX_ENUM );
		
		return info->props.queueFlags;
	}
	
/*
=================================================
	GetQueuesFamily
=================================================
*
	VkQueueFlags  DeviceAnalyzer::GetQueuesFamily (ArrayView<ResourceID> queueIds, TraceRange::Bookmark pos) const
	{
		VkQueueFlags	result = 0;

		for (auto& q : queueIds)
		{
			auto*	info = _queues.FindIn( q, pos, false );
			CHECK_ERR( info, VK_QUEUE_FLAG_BITS_MAX_ENUM );

			result |= info->props.queueFlags;
		}
		return result;
	}

/*
=================================================
	GetCommandPoolQueueFamily
=================================================
*/
	VkQueueFlags  DeviceAnalyzer::GetCommandPoolQueueFamily (ResourceID commandPoolId, TraceRange::Bookmark pos) const
	{
		CHECK_ERR( not _queues.empty() );

		HashSet<VkQueueFlags>	supported_families;

		for (auto iter = _queues.begin(); iter != _queues.end(); ++iter)
		{
			auto	q = _queues.FindIn( iter, pos );

			if ( q == null )
				continue;

			if ( q->commandPools.find( commandPoolId ) == q->commandPools.end() )
				continue;

			supported_families.insert( q->props.queueFlags );
		}

		if ( supported_families.empty() )
		{
			ASSERT( not _queues.begin()->second.empty() );

			// may be unused command pool, return any valid index
			return _queues.begin()->second.back().props.queueFlags;
		}
		
		// TODO: merge flags
		ASSERT( supported_families.size() == 1 );
		
		return *supported_families.begin();
	}
	
/*
=================================================
	GetBufferQueueFamily
=================================================
*
	Array<VkQueueFlags>  DeviceAnalyzer::GetBufferQueueFamily (ResourceID bufferId, TraceRange::Bookmark pos) const
	{
		Array<VkQueueFlags>	supported_families;

		for (auto& queue : _queues)
		{
			for (auto& qobj : queue.second)
			{
				if ( pos >= qobj.bookmarks.front().pos and
					 pos <= qobj.bookmarks.back().pos )
				{
					if ( qobj.bufferUsage.find( bufferId ) == qobj.bufferUsage.end() )
						continue;

					bool	found = false;

					for (auto& flags : supported_families)
					{
						if ( flags == qobj.props.queueFlags ) {
							found = true;
							break;
						}
					}

					if ( not found )
						supported_families.push_back( qobj.props.queueFlags );
				}
			}
		}


		
		return *supported_families.begin();
	}
	
/*
=================================================
	GetImageQueueFamily
=================================================
*
	Array<VkQueueFlags>  DeviceAnalyzer::GetImageQueueFamily (ResourceID imageId, TraceRange::Bookmark pos) const
	{
		HashSet<VkQueueFlags>	supported_families;

		for (auto& queue : _queues)
		{
			for (auto& qobj : queue.second)
			{
				if ( pos >= qobj.bookmarks.front().pos and
					 pos <= qobj.bookmarks.back().pos )
				{
					if ( qobj.imageUsage.find( imageId ) == qobj.imageUsage.end() )
						continue;

					supported_families.insert( qobj.props.queueFlags );
				}
			}
		}

		// TODO: merge flags
		ASSERT( supported_families.size() == 1 );
		
		return *supported_families.begin();
	}*/


}	// VTC
