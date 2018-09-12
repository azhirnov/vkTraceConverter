// Copyright (c)  Zhirnov Andrey. For more information see 'LICENSE.txt'

#include "Analyzer/DeviceAnalyzer.h"
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
	Process
=================================================
*/
	void DeviceAnalyzer::Process (const TraceRange::Iterator &)
	{
	}
	
/*
=================================================
	AddResourceUsage
=================================================
*/
	void DeviceAnalyzer::AddResourceUsage (const TraceRange::Iterator &pos, EResourceType type, ResourceID id, FrameID)
	{
		switch ( type )
		{
			case VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT :			CHECK( _ProcessInstanceUsage( pos, id ));		break;
			case VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT :	CHECK( _ProcessPhysicalDeviceUsage( pos, id ));	break;
			case VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT :			CHECK( _ProcessLogicalDeviceUsage( pos, id ));	break;
			case VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT :			CHECK( _ProcessQueueUsage( pos, id ));			break;
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

			default : {
				auto	instance = _instances.find( id );
				CHECK_ERR( instance != _instances.end() );

				instance->second.bookmarks.push_back({ pos.GetBookmark(), pos->packet_id });
				break;
			}
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

		auto	instance	= _instances.insert({ ResourceID(*packet.pInstance), InstanceInfo() }).first;
		auto&	info		= instance->second;

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

		info.bookmarks.push_back({ pos.GetBookmark(), pos->packet_id });
		return true;
	}
	
/*
=================================================
	_OnEnumeratePhysicalDevices
=================================================
*/
	bool DeviceAnalyzer::_OnEnumeratePhysicalDevices (const TraceRange::Iterator &pos)
	{
		auto&	packet		= pos.Cast< packet_vkEnumeratePhysicalDevices >();
		auto	instance	= _instances.find( ResourceID(packet.instance) );

		CHECK_ERR( instance != _instances.end() );

		if ( packet.pPhysicalDeviceCount )
			instance->second.physicalDevices.resize( *packet.pPhysicalDeviceCount );

		if ( packet.pPhysicalDevices )
		{
			for (size_t i = 0; i < instance->second.physicalDevices.size(); ++i)
			{
				instance->second.physicalDevices[i] = ResourceID(packet.pPhysicalDevices[i]);

				_physicalDevices.insert({ ResourceID(packet.pPhysicalDevices[i]), PhysicalDeviceInfo() })
					.first->second.bookmarks.push_back({ pos.GetBookmark(), pos->packet_id });
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
		
		auto	dev = _physicalDevices.find( id );
		CHECK_ERR( dev != _physicalDevices.end() );

		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceFeatures :
				dev->second.deviceFeatures = *pos.Cast< packet_vkGetPhysicalDeviceFeatures >().pFeatures;
				break;
			
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceProperties :
				dev->second.deviceProperties = *pos.Cast< packet_vkGetPhysicalDeviceProperties >().pProperties;
				break;

			case VKTRACE_TPI_VK_vkGetPhysicalDeviceMemoryProperties :
				dev->second.deviceMemoryProperties = *pos.Cast< packet_vkGetPhysicalDeviceMemoryProperties >().pMemoryProperties;
				break;

			case VKTRACE_TPI_VK_vkGetPhysicalDeviceQueueFamilyProperties :
				CHECK_ERR( _OnGetPhysicalDeviceQueueFamilyProperties( pos, dev->second ));
				break;

			case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceSupportKHR :
				CHECK_ERR( _OnGetPhysicalDeviceSurfaceSupportKHR( pos, dev->second ));
				break;
			
			case VKTRACE_TPI_VK_vkCreateDevice :
				CHECK_ERR( _OnCreateDevice( pos, id ));
				break;
		}

		dev->second.bookmarks.push_back({ pos.GetBookmark(), pos->packet_id });
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
		ASSERT( packet.pCreateInfo->pNext == null );	// add support if assert triggered
		ASSERT( ResourceID(packet.physicalDevice) == id );

		auto	dev		= _logicalDevices.insert({ ResourceID(*packet.pDevice), LogicalDeviceInfo() }).first;
		auto&	info	= dev->second;

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

		info.bookmarks.push_back({ pos.GetBookmark(), pos->packet_id });
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
			return true;
		
		auto	dev = _logicalDevices.find( id );
		CHECK_ERR( dev != _logicalDevices.end() );

		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkGetDeviceQueue :		CHECK( _OnGetDeviceQueue( pos, id ));	break;
			case VKTRACE_TPI_VK_vkGetDeviceQueue2 :		ASSERT(false);		break;
		}

		dev->second.bookmarks.push_back({ pos.GetBookmark(), pos->packet_id });
		return true;
	}
	
/*
=================================================
	_OnGetDeviceQueue
=================================================
*/
	bool DeviceAnalyzer::_OnGetDeviceQueue (const TraceRange::Iterator &pos, ResourceID id)
	{
		auto&	packet = pos.Cast< packet_vkGetDeviceQueue >();
		ASSERT( ResourceID(packet.device) == id );

		auto	dev		= _logicalDevices.find( ResourceID(packet.device) );
		CHECK_ERR( dev != _logicalDevices.end() );

		dev->second.queues.insert( ResourceID(*packet.pQueue) );

		auto	gpu		= _physicalDevices.find( dev->second.physicalDevice );
		CHECK_ERR( gpu != _physicalDevices.end() );

		auto	queue	= _queues.insert({ ResourceID(*packet.pQueue), QueueInfo() }).first;
		auto&	info	= queue->second;

		info.familyIndex	= packet.queueFamilyIndex;
		info.queueIndex		= packet.queueIndex;
		info.logicalDevice	= ResourceID(packet.device);
		info.physicalDevice	= dev->second.physicalDevice;

		CHECK_ERR( info.familyIndex < gpu->second.queueFamilyProperties.size() );
		info.props		= gpu->second.queueFamilyProperties[ info.familyIndex ].props;
		info.usageFlags	= info.props.queueFlags & (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT | VK_QUEUE_TRANSFER_BIT);	// TODO: track command buffers and set correct queue usage


		// find queue create info
		bool	found	= false;
		for (auto& ci : dev->second.queueCreateInfos)
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

		auto	queue = _queues.find( id );
		CHECK_ERR( queue != _queues.end() );

		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkQueuePresentKHR :
				queue->second.usedForPresent = true;
				break;

			case VKTRACE_TPI_VK_vkQueueBindSparse :
				queue->second.usageFlags |= VK_QUEUE_SPARSE_BINDING_BIT;
				break;

			case VKTRACE_TPI_VK_vkQueueSubmit :
			{
				auto&	packet = pos.Cast< packet_vkQueueSubmit >();

				for (uint i = 0; i < packet.submitCount; ++i)
				{
					auto*	protect = FindVkStruct<VkProtectedSubmitInfo>( packet.pSubmits[i].pNext );
					if ( protect and protect->protectedSubmit )
						queue->second.usageFlags |= VK_QUEUE_PROTECTED_BIT;
				}
				break;
			}
		}

		queue->second.bookmarks.push_back({ pos.GetBookmark(), pos->packet_id });
		return true;
	}
	
/*
=================================================
	GetInstanceInfo
=================================================
*/
	DeviceAnalyzer::InstanceInfo const*  DeviceAnalyzer::GetInstanceInfo (ResourceID id) const
	{
		auto	instance = _instances.find( id );

		if ( instance != _instances.end() )
			return &instance->second;

		return null;
	}
	
/*
=================================================
	GetPhysicalDeviceInfo
=================================================
*/
	DeviceAnalyzer::PhysicalDeviceInfo const*  DeviceAnalyzer::GetPhysicalDeviceInfo (ResourceID id) const
	{
		auto	dev = _physicalDevices.find( id );

		if ( dev != _physicalDevices.end() )
			return &dev->second;

		return null;
	}
	
/*
=================================================
	GetLogicalDeviceInfo
=================================================
*/
	DeviceAnalyzer::LogicalDeviceInfo const*  DeviceAnalyzer::GetLogicalDeviceInfo (ResourceID id) const
	{
		auto	dev = _logicalDevices.find( id );

		if ( dev != _logicalDevices.end() )
			return &dev->second;

		return null;
	}
	
/*
=================================================
	GetQueueInfo
=================================================
*/
	DeviceAnalyzer::QueueInfo const*  DeviceAnalyzer::GetQueueInfo (ResourceID id) const
	{
		auto	queue = _queues.find( id );

		if ( queue != _queues.end() )
			return &queue->second;

		return null;
	}


}	// VTC
