// Copyright (c)  Zhirnov Andrey. For more information see 'LICENSE.txt'

#pragma once

#include "Analyzer/IAnalyzer.h"

namespace VTC
{

	//
	// Device Initialization Analyzer
	//

	class DeviceAnalyzer final : public IAnalyzer
	{
	// types
	public:
		struct Bookmark
		{
			TraceRange::Bookmark		pos;
			PacketID					packetId;
		};


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
			Array<Bookmark>				bookmarks;
		};


		struct QueueFamilyProperties
		{
			VkQueueFamilyProperties		props;
			bool						presentSupported	= false;
		};


		struct PhysicalDeviceInfo
		{
			VkPhysicalDeviceProperties			deviceProperties;
			VkPhysicalDeviceFeatures			deviceFeatures;
			VkPhysicalDeviceMemoryProperties	deviceMemoryProperties;
			Array<QueueFamilyProperties>		queueFamilyProperties;

			HashSet<ResourceID>					logicalDevices;
			Array<Bookmark>						bookmarks;
		};


		struct QueueCreateInfo
		{
			VkDeviceQueueCreateFlags		flags				= 0;
			uint32_t						queueFamilyIndex	= 0;
			Array<float>					queuesPriorities;
		};


		struct LogicalDeviceInfo
		{
			VkDeviceCreateFlags				deviceCreateFlags	= 0;
			Array<QueueCreateInfo>			queueCreateInfos;
			HashSet<String>					enabledLayers;
			HashSet<String>					enabledExtensions;
			VkPhysicalDeviceFeatures		enabledFeatures;
			
			ResourceID						physicalDevice;
			HashSet<ResourceID>				queues;
			Array<Bookmark>					bookmarks;
		};


		struct QueueInfo
		{
			VkQueueFamilyProperties			props;
			VkDeviceQueueCreateFlags		createFlags		= 0;
			float							priority		= 0.0f;
			uint							familyIndex		= ~0u;
			uint							queueIndex		= ~0u;
			
			ResourceID						physicalDevice	= 0;
			ResourceID						logicalDevice	= 0;

			VkQueueFlags					usageFlags		= 0;
			bool							usedForPresent	= false;

			Array<Bookmark>					bookmarks;
		};


		using InstancesMap_t		= HashMap< ResourceID, InstanceInfo >;
		using PhysicalDevicesMap_t	= HashMap< ResourceID, PhysicalDeviceInfo >;
		using LogicalDevicesMap_t	= HashMap< ResourceID, LogicalDeviceInfo >;
		using QueuesMap_t			= HashMap< ResourceID, QueueInfo >;


	// variables
	private:
		InstancesMap_t			_instances;
		PhysicalDevicesMap_t	_physicalDevices;
		LogicalDevicesMap_t		_logicalDevices;
		QueuesMap_t				_queues;


	// methods
	public:
		DeviceAnalyzer ();

		ND_ InstanceInfo const*			GetInstanceInfo (ResourceID id) const;
		ND_ PhysicalDeviceInfo const*	GetPhysicalDeviceInfo (ResourceID id) const;
		ND_ LogicalDeviceInfo const*	GetLogicalDeviceInfo (ResourceID id) const;
		ND_ QueueInfo const*			GetQueueInfo (ResourceID id) const;


	// IAnalyzer implementation
	public:
		void Process (const TraceRange::Iterator &) override;
		
		void PostProcess () override {}

		void AddResourceUsage (const TraceRange::Iterator &, EResourceType, ResourceID, FrameID) override;
		
		std::type_index		GetType ()	const override		{ return typeid(*this); }

		String				Report ()	const override		{ return "TODO"; }


	private:
		bool _ProcessInstanceUsage (const TraceRange::Iterator &, ResourceID);
		bool _ProcessPhysicalDeviceUsage (const TraceRange::Iterator &, ResourceID);
		bool _ProcessLogicalDeviceUsage (const TraceRange::Iterator &, ResourceID);
		bool _ProcessQueueUsage (const TraceRange::Iterator &, ResourceID);

		bool _OnCreateInstance (const TraceRange::Iterator &);
		bool _OnEnumeratePhysicalDevices (const TraceRange::Iterator &);

		bool _OnCreateDevice (const TraceRange::Iterator &, ResourceID);
		bool _OnGetPhysicalDeviceQueueFamilyProperties (const TraceRange::Iterator &, PhysicalDeviceInfo &);
		bool _OnGetPhysicalDeviceSurfaceSupportKHR (const TraceRange::Iterator &, PhysicalDeviceInfo &);

		bool _OnGetDeviceQueue (const TraceRange::Iterator &, ResourceID);
	};


}	// VTC
