// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Analyzer/Default/DeviceAnalyzer.h"
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
				CHECK_ERR( _instances.AddResourceUsage( pos, id, EResOp::Access ));
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
		CHECK_ERR( _instances.AddResourceUsage( OUT instance, pos, ResourceID(*packet.pInstance), EResOp::Construct ));

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
		CHECK_ERR( _instances.AddResourceUsage( OUT instance, pos, ResourceID(packet.instance), EResOp::Access ));

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
				CHECK( _physicalDevices.AddResourceUsage( OUT dev, pos, info.physicalDevices[i], EResOp::Construct ));

				dev->second.back().instance = ResourceID(packet.instance);
			}
			else
			{
				CHECK( _physicalDevices.AddResourceUsage( pos, info.physicalDevices[i], EResOp::Access ));
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
		CHECK_ERR( _physicalDevices.AddResourceUsage( OUT dev, pos, id, EResOp::Access ));

		auto&	info = dev->second.back();

		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceFeatures :
				info.deviceFeatures = *pos.Cast< packet_vkGetPhysicalDeviceFeatures >().pFeatures;
				break;
			
			case VKTRACE_TPI_VK_vkGetPhysicalDeviceProperties :
				info.deviceProperties = *pos.Cast< packet_vkGetPhysicalDeviceProperties >().pProperties;
				break;

			case VKTRACE_TPI_VK_vkGetPhysicalDeviceMemoryProperties :
				info.deviceMemoryProperties = *pos.Cast< packet_vkGetPhysicalDeviceMemoryProperties >().pMemoryProperties;
				break;

			case VKTRACE_TPI_VK_vkGetPhysicalDeviceQueueFamilyProperties :
				CHECK_ERR( _OnGetPhysicalDeviceQueueFamilyProperties( pos, info ));
				break;

			case VKTRACE_TPI_VK_vkGetPhysicalDeviceSurfaceSupportKHR :
				CHECK_ERR( _OnGetPhysicalDeviceSurfaceSupportKHR( pos, info ));
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
		CHECK_ERR( _logicalDevices.AddResourceUsage( OUT dev, pos, id, EResOp::Access ));

		auto&	info = dev->second.back();

		switch ( pos->packet_id )
		{
			case VKTRACE_TPI_VK_vkGetDeviceQueue :		CHECK( _OnGetDeviceQueue( pos, info ));		break;
			case VKTRACE_TPI_VK_vkGetDeviceQueue2 :		CHECK( _OnGetDeviceQueue2( pos, info ));	break;
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
		CHECK_ERR( _logicalDevices.AddResourceUsage( OUT dev, pos, id, EResOp::Construct ));

		auto&	info = dev->second.back();

		info.id					= id;
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
			QueueFamilyInfo		ci;
			ci.flags			= packet.pCreateInfo->pQueueCreateInfos[i].flags;
			ci.queueFamilyIndex	= packet.pCreateInfo->pQueueCreateInfos[i].queueFamilyIndex;

			for (uint j = 0; j < packet.pCreateInfo->pQueueCreateInfos[i].queueCount; ++j) {
				ci.instances.push_back({ ResourceID(0), packet.pCreateInfo->pQueueCreateInfos[i].pQueuePriorities[j] });
			}

			info.queues.push_back( std::move(ci) );
		}
		return true;
	}
	
/*
=================================================
	_OnGetDeviceQueue
=================================================
*/
	bool DeviceAnalyzer::_OnGetDeviceQueue (const TraceRange::Iterator &pos, LogicalDeviceInfo &dev)
	{
		auto&	packet = pos.Cast< packet_vkGetDeviceQueue >();
		CHECK_ERR( dev.id == ResourceID(packet.device) );
		CHECK_ERR( packet.queueFamilyIndex < dev.queues.size() );

		auto&	queue_family = dev.queues[ packet.queueFamilyIndex ];
		CHECK_ERR( queue_family.queueFamilyIndex == packet.queueFamilyIndex );
		CHECK_ERR( packet.queueIndex < queue_family.instances.size() );

		queue_family.instances[ packet.queueIndex ].id = ResourceID(*packet.pQueue);
		return true;
	}
	
/*
=================================================
	_OnGetDeviceQueue2
=================================================
*/
	bool DeviceAnalyzer::_OnGetDeviceQueue2 (const TraceRange::Iterator &pos, LogicalDeviceInfo &dev)
	{
		auto&	packet = pos.Cast< packet_vkGetDeviceQueue2 >();
		CHECK_ERR( dev.id == ResourceID(packet.device) );

		auto&	queue_family = dev.queues[ packet.pQueueInfo->queueFamilyIndex ];
		CHECK_ERR( queue_family.queueFamilyIndex == packet.pQueueInfo->queueFamilyIndex );
		CHECK_ERR( packet.pQueueInfo->queueIndex < queue_family.instances.size() );

		queue_family.instances[ packet.pQueueInfo->queueIndex ].id = ResourceID(*packet.pQueue);
		return true;
	}

}	// VTC
