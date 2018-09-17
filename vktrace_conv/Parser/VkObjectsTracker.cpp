// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Parser/AppTrace.h"

namespace VTC
{
	
	//
	// Vulkan Objects Tracker
	//

	class AppTrace::VkObjectsTracker
	{
	// types
	private:
		struct SwapchainInfo
		{
			Array<ResourceID>		images;
		};

		struct CommandPoolInfo
		{
			HashSet<ResourceID>		commandBuffers;
		};

		struct DescriptorPoolInfo
		{
			HashSet<ResourceID>		descriptorSets;
		};

		struct PhysicalDeviceInfo
		{
			ResourceID				instance	= 0;
		};

		struct QueueInfo
		{
			ResourceID				device		= 0;
		};

		struct CommandBufferInfo
		{
			ResourceID				currFramebuffer		= 0;
		};

		struct FramebufferInfo
		{
			Array<ResourceID>		attachments;
		};

		using Swapchains_t		= HashMap< ResourceID, SwapchainInfo >;
		using CommandPools_t	= HashMap< ResourceID, CommandPoolInfo >;
		using DescriptorPools_t	= HashMap< ResourceID, DescriptorPoolInfo >;
		using PhysicalDevices_t	= HashMap< ResourceID, PhysicalDeviceInfo >;
		using Queues_t			= HashMap< ResourceID, QueueInfo >;
		using CommandBuffers_t	= HashMap< ResourceID, CommandBufferInfo >;
		using Framebuffers_t	= HashMap< ResourceID, FramebufferInfo >;


	// variables
	private:
		Swapchains_t		_swapchains;
		CommandPools_t		_commandPools;
		DescriptorPools_t	_descriptorPools;
		PhysicalDevices_t	_physicalDevices;
		Queues_t			_queues;
		CommandBuffers_t	_commandBuffers;
		Framebuffers_t		_framebuffers;


	// methods
	public:
		void AddResourceBookmark (EResourceType type, ResourceID id, const Iterator &pos, FrameID frameId, EResOp op, Analyzers_t &analyzers);

	private:
		void _SendResourceUsageEvent (EResourceType type, ResourceID id, const Iterator &pos, FrameID frameId, EResOp op, Analyzers_t &analyzers);

		bool _ProcessPhysicalDevice (ResourceID id, const Iterator &pos, FrameID frameId, EResOp op, Analyzers_t &analyzers);
		bool _ProcessCommandPool (ResourceID id, const Iterator &pos, FrameID frameId, EResOp op, Analyzers_t &analyzers);
		bool _ProcessDescriptorPool (ResourceID id, const Iterator &pos, FrameID frameId, EResOp op, Analyzers_t &analyzers);
		bool _ProcessSwpachain (ResourceID id, const Iterator &pos, FrameID frameId, EResOp op, Analyzers_t &analyzers);
		bool _ProcessQueue (ResourceID id, const Iterator &pos, FrameID frameId, Analyzers_t &analyzers);
		bool _ProcessCommandBuffers (ResourceID id, const Iterator &pos, FrameID frameId, Analyzers_t &analyzers);
		bool _ProcessFramebuffer (ResourceID id, const Iterator &pos, FrameID frameId, Analyzers_t &analyzers);
	};
//-----------------------------------------------------------------------------


/*
=================================================
	constructor
=================================================
*/
	AppTrace::AppTrace () :
		_objTracker{ new VkObjectsTracker() }
	{
	}
	
/*
=================================================
	destructor
=================================================
*/
	AppTrace::~AppTrace ()
	{
		Close();
	}

/*
=================================================
	_AddResourceBookmark
=================================================
*/
	void AppTrace::_AddResourceBookmark (EResourceType type, ResourceID id, const Iterator &pos, FrameID frameId, EResOp op)
	{
		if ( id == 0 )
			return;

		_objTracker->AddResourceBookmark( type, id, pos, frameId, op, _analyzers );
	}
//-----------------------------------------------------------------------------


	
/*
=================================================
	AddResourceBookmark
=================================================
*/
	void AppTrace::VkObjectsTracker::AddResourceBookmark (EResourceType type, ResourceID id, const Iterator &pos, FrameID frameId, EResOp op, Analyzers_t &analyzers)
	{
		if ( type != VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT and
			 type != VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT )
		{
			_SendResourceUsageEvent( type, id, pos, frameId, op, analyzers );
		}

		// add indirect resource usage
		switch ( type )
		{
			case VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT :
				if ( pos->packet_id != VKTRACE_TPI_VK_vkDestroyInstance )
					break;
				// else: enter to _ProcessPhysicalDevice

			case VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT :
				CHECK( _ProcessPhysicalDevice( id, pos, frameId, op, analyzers ));
				break;

			case VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_POOL_EXT :
				CHECK( _ProcessCommandPool( id, pos, frameId, op, analyzers ));
				break;

			case VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_POOL_EXT :
				CHECK( _ProcessDescriptorPool( id, pos, frameId, op, analyzers ));
				break;

			case VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT :
				CHECK( _ProcessSwpachain( id, pos, frameId, op, analyzers ));
				break;

			case VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT :
				if ( pos->packet_id != VKTRACE_TPI_VK_vkDestroyDevice )
					break;
				// else: enter _ProcessQueue

			case VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT :
				CHECK( _ProcessQueue( id, pos, frameId, analyzers ));
				break;

			case VK_DEBUG_REPORT_OBJECT_TYPE_FRAMEBUFFER_EXT :
				CHECK( _ProcessFramebuffer( id, pos, frameId, analyzers ));
				break;

			case VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT :
				CHECK( _ProcessCommandBuffers( id, pos, frameId, analyzers ));
				break;
		}
	}
	
/*
=================================================
	_SendResourceUsageEvent
=================================================
*/
	void AppTrace::VkObjectsTracker::_SendResourceUsageEvent (EResourceType type, ResourceID id, const Iterator &pos, FrameID frameId, EResOp op, Analyzers_t &analyzers)
	{
		if ( id == 0 )
			return;

		for (auto& analyzer : analyzers)
		{
			analyzer->AddResourceUsage( pos, type, id, frameId, op );
		}
	}
	
/*
=================================================
	_ProcessPhysicalDevice
=================================================
*/
	bool AppTrace::VkObjectsTracker::_ProcessPhysicalDevice (ResourceID id, const Iterator &pos, FrameID frameId, EResOp op, Analyzers_t &analyzers)
	{
		if ( op == EResOp::Construct )
		{
			CHECK_ERR( pos->packet_id == VKTRACE_TPI_VK_vkEnumeratePhysicalDevices );

			auto&	packet = pos.Cast< packet_vkEnumeratePhysicalDevices >();

			if ( _physicalDevices.insert({ id, PhysicalDeviceInfo{ResourceID(packet.instance)} }).second )
			{
				_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, id, pos, frameId, EResOp::Construct, analyzers );
			}
			return true;
		}

		if ( op == EResOp::Destruct )
		{
			CHECK_ERR( pos->packet_id == VKTRACE_TPI_VK_vkDestroyInstance );

			for (auto iter = _physicalDevices.begin(); iter != _physicalDevices.end();)
			{
				if ( iter->second.instance == id )
				{
					_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, iter->first, pos, frameId, EResOp::Destruct, analyzers );

					iter = _physicalDevices.erase( iter );
				}
				else
					++iter;
			}
			return true;
		}
		
		_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, id, pos, frameId, EResOp::Access, analyzers );
		return true;
	}

/*
=================================================
	_ProcessCommandPool
=================================================
*/
	bool AppTrace::VkObjectsTracker::_ProcessCommandPool (ResourceID id, const Iterator &pos, FrameID frameId, EResOp op, Analyzers_t &analyzers)
	{
		if ( op == EResOp::Construct )
		{
			CHECK( _commandPools.insert({ id, {} }).second );
			return true;
		}
		
		if ( op == EResOp::Destruct )
		{
			CHECK( _commandPools.erase( id ) == 1 );
			return true;
		}

		auto	cmd_pool = _commandPools.find( id );
		CHECK_ERR( cmd_pool != _commandPools.end() );

		switch ( pos->packet_id )
		{
			// AllocateCommandBuffers
			case VKTRACE_TPI_VK_vkAllocateCommandBuffers :
			{
				auto&	packet = pos.Cast< packet_vkAllocateCommandBuffers >();
				CHECK_ERR( packet.pAllocateInfo );
				CHECK_ERR( cmd_pool->first == ResourceID(packet.pAllocateInfo->commandPool) );
				ASSERT( packet.pAllocateInfo->pNext == null );		// add support if triggered

				for (uint i = 0; i < packet.pAllocateInfo->commandBufferCount; ++i)
				{
					CHECK( cmd_pool->second.commandBuffers.insert( ResourceID(packet.pCommandBuffers[i]) ).second );
				}
				break;
			}

			// FreeCommandBuffers
			case VKTRACE_TPI_VK_vkFreeCommandBuffers :
			{
				auto&	packet = pos.Cast< packet_vkFreeCommandBuffers >();
				CHECK_ERR( cmd_pool->first == ResourceID(packet.commandPool) );

				for (uint i = 0; i < packet.commandBufferCount; ++i)
				{
					CHECK( cmd_pool->second.commandBuffers.erase( ResourceID(packet.pCommandBuffers[i]) ) == 1 );
				}
				break;
			}

			// ResetCommandPool
			case VKTRACE_TPI_VK_vkResetCommandPool :
			{
				auto&	packet = pos.Cast< packet_vkResetCommandPool >();
				CHECK_ERR( cmd_pool->first == ResourceID(packet.commandPool) );

				// this function doesn't free command buffers, only put thier in the initial state
				for (auto& cmdbuf : cmd_pool->second.commandBuffers)
				{
					_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, cmdbuf, pos, frameId, EResOp::Access, analyzers );
				}
				break;
			}
		}
		return true;
	}
	
/*
=================================================
	_ProcessDescriptorPool
=================================================
*/
	bool AppTrace::VkObjectsTracker::_ProcessDescriptorPool (ResourceID id, const Iterator &pos, FrameID frameId, EResOp op, Analyzers_t &analyzers)
	{
		if ( op == EResOp::Construct )
		{
			CHECK( _descriptorPools.insert({ id, {} }).second );
			return true;
		}
		
		if ( op == EResOp::Destruct )
		{
			CHECK( _descriptorPools.erase( id ) == 1 );
			return true;
		}

		auto	desc_pool = _descriptorPools.find( id );
		CHECK_ERR( desc_pool != _descriptorPools.end() );

		switch ( pos->packet_id )
		{
			// AllocateDescriptorSets
			case VKTRACE_TPI_VK_vkAllocateDescriptorSets :
			{
				auto&	packet = pos.Cast< packet_vkAllocateDescriptorSets >();
				CHECK_ERR( packet.pAllocateInfo );
				CHECK_ERR( desc_pool->first == ResourceID(packet.pAllocateInfo->descriptorPool) );
				ASSERT( packet.pAllocateInfo->pNext == null );		// add support if triggered

				for (uint i = 0; i < packet.pAllocateInfo->descriptorSetCount; ++i)
				{
					CHECK( desc_pool->second.descriptorSets.insert( ResourceID(packet.pDescriptorSets[i]) ).second );
				}
				break;
			}

			// FreeDescriptorSets
			case VKTRACE_TPI_VK_vkFreeDescriptorSets :
			{
				auto&	packet = pos.Cast< packet_vkFreeDescriptorSets >();
				CHECK_ERR( desc_pool->first == ResourceID(packet.descriptorPool) );

				for (uint i = 0; i < packet.descriptorSetCount; ++i)
				{
					CHECK( desc_pool->second.descriptorSets.erase( ResourceID(packet.pDescriptorSets[i]) ) == 1 );
				}
				break;
			}

			// ResetDescriptorPool
			case VKTRACE_TPI_VK_vkResetDescriptorPool :
			{
				auto&	packet = pos.Cast< packet_vkResetDescriptorPool >();
				CHECK_ERR( desc_pool->first == ResourceID(packet.descriptorPool) );

				// implicitly free all descriptor sets
				for (auto& desc : desc_pool->second.descriptorSets)
				{
					_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_EXT, desc, pos, frameId, EResOp::Destruct, analyzers );
				}

				desc_pool->second.descriptorSets.clear();
				break;
			}
		}
		return true;
	}
	
/*
=================================================
	_ProcessSwpachain
=================================================
*/
	bool AppTrace::VkObjectsTracker::_ProcessSwpachain (ResourceID id, const Iterator &pos, FrameID frameId, EResOp op, Analyzers_t &analyzers)
	{
		if ( op == EResOp::Construct )
		{
			CHECK( _swapchains.insert({ id, {} }).second );
			return true;
		}
		
		if ( op == EResOp::Destruct )
		{
			CHECK( _swapchains.erase( id ) == 1 );
			return true;
		}

		auto	swapchain = _swapchains.find( id );
		CHECK_ERR( swapchain != _swapchains.end() );

		switch ( pos->packet_id )
		{
			// GetSwapchainImages
			case VKTRACE_TPI_VK_vkGetSwapchainImagesKHR :
			{
				auto&	packet = pos.Cast< packet_vkGetSwapchainImagesKHR >();
				CHECK_ERR( swapchain->first == ResourceID(packet.swapchain) );

				if ( packet.pSwapchainImageCount )
				{
					swapchain->second.images.resize( *packet.pSwapchainImageCount );
				}

				if ( packet.pSwapchainImages )
				{
					for (uint i = 0; i < swapchain->second.images.size(); ++i)
					{
						swapchain->second.images[i] = ResourceID(packet.pSwapchainImages[i]);
					}
				}
				break;
			}

			// AcquireNextImage
			case VKTRACE_TPI_VK_vkAcquireNextImageKHR :
			{
				auto&	packet = pos.Cast< packet_vkAcquireNextImageKHR >();
				CHECK_ERR( swapchain->first == ResourceID(packet.swapchain) );
				CHECK_ERR( *packet.pImageIndex < swapchain->second.images.size() );
				
				_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, swapchain->second.images[*packet.pImageIndex],
										 pos, frameId, EResOp::Access, analyzers );
				break;
			}

			// AcquireNextImage2
			case VKTRACE_TPI_VK_vkAcquireNextImage2KHX :
			{
				ASSERT(false);	// TODO
				break;
			}

			// AcquireNextImage2
			case VKTRACE_TPI_VK_vkAcquireNextImage2KHR :
			{
				ASSERT(false);	// TODO
				break;
			}
		}
		return true;
	}
		
/*
=================================================
	_ProcessQueue
=================================================
*/
	bool AppTrace::VkObjectsTracker::_ProcessQueue (ResourceID id, const Iterator &pos, FrameID frameId, Analyzers_t &analyzers)
	{
		switch ( pos->packet_id )
		{
			// GetDeviceQueue
			case VKTRACE_TPI_VK_vkGetDeviceQueue :
			{
				auto&	packet = pos.Cast< packet_vkGetDeviceQueue >();
				CHECK_ERR( id == ResourceID(*packet.pQueue) );

				if ( _queues.insert({ ResourceID(*packet.pQueue), QueueInfo{ResourceID(packet.device)} }).second )
				{
					_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT, id, pos, frameId, EResOp::Construct, analyzers );
				}
				break;
			}

			// GetDeviceQueue2
			case VKTRACE_TPI_VK_vkGetDeviceQueue2 :
			{
				auto&	packet = pos.Cast< packet_vkGetDeviceQueue2 >();
				CHECK_ERR( id == ResourceID(*packet.pQueue) );

				if ( _queues.insert({ ResourceID(*packet.pQueue), QueueInfo{ResourceID(packet.device)} }).second )
				{
					_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT, id, pos, frameId, EResOp::Construct, analyzers );
				}
				break;
			}

			// QueuePresent
			case VKTRACE_TPI_VK_vkQueuePresentKHR :
			{
				auto&	packet = pos.Cast< packet_vkQueuePresentKHR >();
				CHECK_ERR( packet.pPresentInfo );

				for (uint i = 0; i < packet.pPresentInfo->swapchainCount; ++i)
				{
					auto	swapchain = _swapchains.find( ResourceID(packet.pPresentInfo->pSwapchains[i]) );
					CHECK_ERR( swapchain != _swapchains.end() );

					CHECK_ERR( packet.pPresentInfo->pImageIndices[i] < swapchain->second.images.size() );

					_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT,
											 swapchain->second.images[ packet.pPresentInfo->pImageIndices[i] ],
											 pos, frameId, EResOp::Access, analyzers );
				}
				break;
			}

			// DestroyDevice
			case VKTRACE_TPI_VK_vkDestroyDevice :
			{
				auto&	packet = pos.Cast< packet_vkDestroyDevice >();

				for (auto iter = _queues.begin(); iter != _queues.end();)
				{
					if ( iter->second.device == ResourceID(packet.device) )
					{
						_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT, iter->first, pos, frameId, EResOp::Destruct, analyzers );

						iter = _queues.erase( iter );
					}
					else
						++iter;
				}
				break;
			}

			default :
				_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT, id, pos, frameId, EResOp::Access, analyzers );
				break;
		}
		return true;
	}
	
/*
=================================================
	_ProcessCommandBuffers
=================================================
*/
	bool AppTrace::VkObjectsTracker::_ProcessCommandBuffers (ResourceID id, const Iterator &pos, FrameID frameId, Analyzers_t &analyzers)
	{
		switch( pos->packet_id )
		{
			// Begin
			case VKTRACE_TPI_VK_vkCmdBeginRenderPass :
			{
				auto&	packet = pos.Cast< packet_vkCmdBeginRenderPass >();
				CHECK_ERR( packet.pRenderPassBegin );
				CHECK_ERR( ResourceID(packet.commandBuffer) == id );

				_commandBuffers.insert({ id, {} }).first->second.currFramebuffer = ResourceID(packet.pRenderPassBegin->framebuffer);

				auto	fb = _framebuffers.find( ResourceID(packet.pRenderPassBegin->framebuffer) );
				CHECK_ERR( fb != _framebuffers.end() );

				for (auto& view : fb->second.attachments)
				{
					_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_VIEW_EXT, view, pos, frameId, EResOp::Access, analyzers );
				}
				break;
			}

			//case VKTRACE_TPI_VK_vkCmdBeginRenderPass2KHR :
			//	break;

			// Next / End
			case VKTRACE_TPI_VK_vkCmdNextSubpass :
			case VKTRACE_TPI_VK_vkCmdEndRenderPass :
			{
				auto	cmdbuf = _commandBuffers.find( id );
				CHECK_ERR( cmdbuf != _commandBuffers.end() );
				
				auto	fb = _framebuffers.find( cmdbuf->second.currFramebuffer );
				CHECK_ERR( fb != _framebuffers.end() );

				for (auto& view : fb->second.attachments)
				{
					_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_VIEW_EXT, view, pos, frameId, EResOp::Access, analyzers );
				}
				break;
			}

			// End
			case VKTRACE_TPI_VK_vkEndCommandBuffer :
			{
				_commandBuffers.erase( id );
				break;
			}
		}
		return true;
	}

/*
=================================================
	_ProcessFramebuffer
=================================================
*/
	bool AppTrace::VkObjectsTracker::_ProcessFramebuffer (ResourceID id, const Iterator &pos, FrameID frameId, Analyzers_t &analyzers)
	{
		switch ( pos->packet_id )
		{
			// Create
			case VKTRACE_TPI_VK_vkCreateFramebuffer :
			{
				auto&	packet = pos.Cast< packet_vkCreateFramebuffer >();
				CHECK_ERR( packet.pCreateInfo );
				CHECK_ERR( ResourceID(*packet.pFramebuffer) == id );
				
				auto&	info = _framebuffers.insert({ id, {} }).first->second;

				info.attachments.resize( packet.pCreateInfo->attachmentCount );

				for (uint i = 0; i < packet.pCreateInfo->attachmentCount; ++i)
				{
					info.attachments[i] = ResourceID(packet.pCreateInfo->pAttachments[i]);
				}
				break;
			}

			// Destroy
			case VKTRACE_TPI_VK_vkDestroyFramebuffer :
			{
				auto	framebuffer = _framebuffers.find( id );
				CHECK_ERR( framebuffer != _framebuffers.end() );

				for (auto& view : framebuffer->second.attachments)
				{
					_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_VIEW_EXT, view, pos, frameId, EResOp::Access, analyzers );
				}

				CHECK( _framebuffers.erase( id ) == 1 );
				break;
			}
		}
		return true;
	}


}	// VTC
