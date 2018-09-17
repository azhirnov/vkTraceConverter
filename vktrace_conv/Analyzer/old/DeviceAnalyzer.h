// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "Analyzer/IAnalyzer.h"
#include "Analyzer/ResourceTracker.h"

namespace VTC
{

	//
	// Device Initialization Analyzer
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
		};


		struct ResourceUsage
		{
			ResourceID						id		= 0;
			TraceRange::Bookmark			first;
			TraceRange::Bookmark			last;
		};
		using ResourceUsageMap_t	= HashMap< ResourceID, ResourceUsage >;
		using ResourceUsageMap2_t	= HashMap< ResourceID, Array<ResourceUsage> >;


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

			HashSet<ResourceID>				commandBuffers;
			HashSet<ResourceID>				commandPools;

			ResourceUsageMap2_t				bufferUsage;
			ResourceUsageMap2_t				imageUsage;
		};


		struct CommandBufferInfo
		{
			ResourceID						commandPool		= 0;
			ResourceUsageMap_t				bufferUsage;
			ResourceUsageMap_t				imageUsage;
			HashSet<ResourceID>				secondaryBuffers;
			bool							oneTimeSubmit	= false;
			bool							isSecondary		= false;
			bool							recording		= false;
		};


		using InstancesMap_t		= ResourceTracker< InstanceInfo >;
		using PhysicalDevicesMap_t	= ResourceTracker< PhysicalDeviceInfo >;
		using LogicalDevicesMap_t	= ResourceTracker< LogicalDeviceInfo >;
		using QueuesMap_t			= ResourceTracker< QueueInfo >;
		using CmdBuffersMap_t		= HashMap< ResourceID, CommandBufferInfo >;

		using InstanceInfo_t		= InstancesMap_t::Item_t;
		using PhysicalDeviceInfo_t	= PhysicalDevicesMap_t::Item_t;
		using LogicalDeviceInfo_t	= LogicalDevicesMap_t::Item_t;
		using QueueInfo_t			= QueuesMap_t::Item_t;


	// variables
	private:
		InstancesMap_t			_instances;
		PhysicalDevicesMap_t	_physicalDevices;
		LogicalDevicesMap_t		_logicalDevices;
		QueuesMap_t				_queues;
		CmdBuffersMap_t			_cmdBuffers;


	// methods
	public:
		DeviceAnalyzer ();

		ND_ InstanceInfo_t const*		GetInstanceInfo (ResourceID id, TraceRange::Bookmark pos) const;
		ND_ PhysicalDeviceInfo_t const*	GetPhysicalDeviceInfo (ResourceID id, TraceRange::Bookmark pos) const;
		ND_ LogicalDeviceInfo_t const*	GetLogicalDeviceInfo (ResourceID id, TraceRange::Bookmark pos) const;
		ND_ QueueInfo_t const*			GetQueueInfo (ResourceID id, TraceRange::Bookmark pos) const;

		//ND_ VkQueueFlags				GetQueueFamily (ResourceID queueId, TraceRange::Bookmark pos) const;
		//ND_ VkQueueFlags				GetQueuesFamily (ArrayView<ResourceID> queueIds, TraceRange::Bookmark pos) const;
		ND_ VkQueueFlags				GetCommandPoolQueueFamily (ResourceID commandPoolId, TraceRange::Bookmark pos) const;
		//ND_ Array<VkQueueFlags>		GetBufferQueueFamily (ResourceID bufferId, TraceRange::Bookmark pos) const;
		//ND_ Array<VkQueueFlags>		GetImageQueueFamily (ResourceID imageId, TraceRange::Bookmark pos) const;


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

		bool _OnCreateDevice (const TraceRange::Iterator &, ResourceID);
		bool _OnGetPhysicalDeviceQueueFamilyProperties (const TraceRange::Iterator &, PhysicalDeviceInfo &);
		bool _OnGetPhysicalDeviceSurfaceSupportKHR (const TraceRange::Iterator &, PhysicalDeviceInfo &);

		bool _OnGetDeviceQueue (const TraceRange::Iterator &, ResourceID, LogicalDeviceInfo_t &);
		
		bool _OnQueueSubmit (const TraceRange::Iterator &, ResourceID, QueueInfo &);
		bool _QueueSubmitCommand (QueueInfo &, ResourceID cmdBufferId);

		bool _OnCmdPipelineBarrier (ArrayView<VkBufferMemoryBarrier>, ArrayView<VkImageMemoryBarrier>,
									ResourceID, TraceRange::Bookmark);
	};


}	// VTC
