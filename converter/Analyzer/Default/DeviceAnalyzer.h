// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Analyzer/IAnalyzer.h"
#include "Analyzer/ResourceTracker.h"

namespace VTC
{

	//
	// Device Analyzer
	//

	class DeviceAnalyzer final : public IAnalyzer
	{
	// types
	public:
		struct InstanceInfo
		{
			VkInstanceCreateFlags		instanceCreateFlags		= 0;
			HashSet<String>				enabledLayers;
			HashSet<String>				enabledExtensions;
			String						applicationName;
			uint32_t					applicationVersion		= 0;
			String						engineName;
			uint32_t					engineVersion			= 0;
			uint32_t					apiVersion				= 0;

			Array<ResourceID>			physicalDevices;
			HashSet<ResourceID>			logicalDevices;
		};


		struct QueueFamilyProperties
		{
			VkQueueFamilyProperties		props;
			bool						presentSupported	= false;
		};


		struct PhysicalDeviceInfo
		{
			ResourceID							instance;
			VkPhysicalDeviceProperties			deviceProperties;
			VkPhysicalDeviceFeatures			deviceFeatures;
			VkPhysicalDeviceMemoryProperties	deviceMemoryProperties;
			Array<QueueFamilyProperties>		queueFamilyProperties;

			HashSet<ResourceID>					logicalDevices;
		};


		struct QueueInstance
		{
			ResourceID					id			= 0;
			float						priority	= 0.0f;
		};

		struct QueueFamilyInfo
		{
			VkDeviceQueueCreateFlags	flags				= 0;
			uint32_t					queueFamilyIndex	= 0;
			Array<QueueInstance>		instances;
		};


		struct LogicalDeviceInfo
		{
			ResourceID					id					= 0;
			VkDeviceCreateFlags			deviceCreateFlags	= 0;
			Array<QueueFamilyInfo>		queues;
			HashSet<String>				enabledLayers;
			HashSet<String>				enabledExtensions;
			VkPhysicalDeviceFeatures	enabledFeatures;
			ResourceID					physicalDevice;
		};


		using InstancesMap_t		= ResourceTracker< InstanceInfo, DefaultBookmark, true >;
		using PhysicalDevicesMap_t	= ResourceTracker< PhysicalDeviceInfo, DefaultBookmark, true >;
		using LogicalDevicesMap_t	= ResourceTracker< LogicalDeviceInfo, DefaultBookmark, true >;

		using InstanceInfo_t		= InstancesMap_t::Item_t;
		using PhysicalDeviceInfo_t	= PhysicalDevicesMap_t::Item_t;
		using LogicalDeviceInfo_t	= LogicalDevicesMap_t::Item_t;


	// variables
	private:
		InstancesMap_t			_instances;
		PhysicalDevicesMap_t	_physicalDevices;
		LogicalDevicesMap_t		_logicalDevices;


	// methods
	public:
		DeviceAnalyzer ();

		ND_ InstanceInfo_t const*		GetInstanceInfo (ResourceID id, TraceRange::Bookmark pos)		const	{ return _instances.FindIn( id, pos, false ); }
		ND_ PhysicalDeviceInfo_t const*	GetPhysicalDeviceInfo (ResourceID id, TraceRange::Bookmark pos)	const	{ return _physicalDevices.FindIn( id, pos, false ); }
		ND_ LogicalDeviceInfo_t const*	GetLogicalDeviceInfo (ResourceID id, TraceRange::Bookmark pos)	const	{ return _logicalDevices.FindIn( id, pos, false ); }


	// IAnalyzer implementation
	public:
		void PreProcess (const class AppTrace &) override {}

		void Process (const TraceRange::Iterator &) override {}
		
		void PostProcess () override {}

		void AddResourceUsage (const TraceRange::Iterator &, EResourceType, ResourceID, FrameID, EResOp) override;
		
		std::type_index		GetType ()	const override		{ return typeid(*this); }

		String				Report ()	const override		{ return "TODO"; }


	private:
		bool _ProcessInstanceUsage (const TraceRange::Iterator &, ResourceID);
		bool _ProcessPhysicalDeviceUsage (const TraceRange::Iterator &, ResourceID);
		bool _ProcessLogicalDeviceUsage (const TraceRange::Iterator &, ResourceID);
		bool _ProcessQueueUsage (const TraceRange::Iterator &, ResourceID);
		bool _ProcessCommandBufferUsage (const TraceRange::Iterator &, ResourceID);

		bool _OnCreateInstance (const TraceRange::Iterator &);
		bool _OnEnumeratePhysicalDevices (const TraceRange::Iterator &);

		bool _OnGetPhysicalDeviceQueueFamilyProperties (const TraceRange::Iterator &, PhysicalDeviceInfo &);
		bool _OnGetPhysicalDeviceSurfaceSupportKHR (const TraceRange::Iterator &, PhysicalDeviceInfo &);

		bool _OnCreateDevice (const TraceRange::Iterator &, ResourceID);
		bool _OnGetDeviceQueue (const TraceRange::Iterator &, LogicalDeviceInfo &);
		bool _OnGetDeviceQueue2 (const TraceRange::Iterator &, LogicalDeviceInfo &);
	};


}	// VTC
