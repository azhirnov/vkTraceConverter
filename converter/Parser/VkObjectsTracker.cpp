// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'
/*
	Helper object to send bookmarks on direct / indirect resource usage.
*/

#include "Parser/AppTrace.h"
#include <bitset>

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


		static constexpr uint	MaxVertexBuffers	= 16;
		static constexpr uint	MaxDescriptorSets	= 8;

		using VertexBuffers_t			= StaticArray< ResourceID, MaxVertexBuffers >;
		using EnabledVertexBuffers_t	= BitSet< MaxVertexBuffers >;

		using DescriptorSets_t			= StaticArray< ResourceID, MaxDescriptorSets >;


		struct CommandBufferState
		{
			ResourceID				framebuffer				= 0;
			ResourceID				renderPass				= 0;

			ResourceID				graphicsPipeline		= 0;
			DescriptorSets_t		graphicsDescriptorSets;

			ResourceID				computePipeline			= 0;
			DescriptorSets_t		computeDescriptorSets;

			ResourceID				indexBuffer				= 0;
			VertexBuffers_t			vertexBuffers;
		};

		struct FramebufferInfo
		{
			Array<ResourceID>		attachments;
		};

		struct PipelineLayoutInfo
		{
			uint					descriptorSetCount = 0;
		};

		struct GraphicsPipelineInfo
		{
			uint					descriptorSetCount = 0;
			EnabledVertexBuffers_t	vertexBuffers;
		};

		struct ComputePipelineInfo
		{
			uint					descriptorSetCount = 0;
		};

		using Swapchains_t			= HashMap< ResourceID, SwapchainInfo >;
		using CommandPools_t		= HashMap< ResourceID, CommandPoolInfo >;
		using DescriptorPools_t		= HashMap< ResourceID, DescriptorPoolInfo >;
		using PhysicalDevices_t		= HashMap< ResourceID, PhysicalDeviceInfo >;
		using Queues_t				= HashMap< ResourceID, QueueInfo >;
		using CommandBuffers_t		= HashMap< ResourceID, CommandBufferState >;
		using Framebuffers_t		= HashMap< ResourceID, FramebufferInfo >;
		using PipelineLayouts_t		= HashMap< ResourceID, PipelineLayoutInfo >;
		using GraphicsPipelines_t	= HashMap< ResourceID, GraphicsPipelineInfo >;
		using ComputePipelines_t	= HashMap< ResourceID, ComputePipelineInfo >;


	// variables
	private:
		Swapchains_t			_swapchains;
		CommandPools_t			_commandPools;
		DescriptorPools_t		_descriptorPools;
		PhysicalDevices_t		_physicalDevices;
		Queues_t				_queues;
		CommandBuffers_t		_commandBuffers;
		Framebuffers_t			_framebuffers;
		PipelineLayouts_t		_pipelineLayouts;
		GraphicsPipelines_t		_graphicsPipelines;
		ComputePipelines_t		_computePipelines;


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
		bool _ProcessFramebuffer (ResourceID id, const Iterator &pos);
		bool _ProcessPipelineLayout (ResourceID id, const Iterator &pos);
		bool _ProcessPipeline (ResourceID id, const Iterator &pos);
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
				[[fallthrough]]; // else: enter to _ProcessPhysicalDevice

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
				[[fallthrough]]; // else: enter _ProcessQueue

			case VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT :
				CHECK( _ProcessQueue( id, pos, frameId, analyzers ));
				break;

			case VK_DEBUG_REPORT_OBJECT_TYPE_FRAMEBUFFER_EXT :
				CHECK( _ProcessFramebuffer( id, pos ));
				break;

			case VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT :
				CHECK( _ProcessCommandBuffers( id, pos, frameId, analyzers ));
				break;

			case VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_LAYOUT_EXT :
				CHECK( _ProcessPipelineLayout( id, pos ));
				break;

			case VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_EXT :
				CHECK( _ProcessPipeline( id, pos ));
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
		
		_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT, id, pos, frameId, op, analyzers );
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
					ASSERT( packet.pCommandBuffers[i] );
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
					_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, cmdbuf, pos, frameId, EResOp::IndirectAccess, analyzers );
				}
				break;
			}

			// Destroy
			case VKTRACE_TPI_VK_vkDestroyCommandPool :
			{
				for (auto& cmdbuf : cmd_pool->second.commandBuffers)
				{
					_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, cmdbuf, pos, frameId, EResOp::Destruct, analyzers );
				}
				CHECK( _commandPools.erase( id ) == 1 );
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
					ASSERT( packet.pDescriptorSets[i] );
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

			// Reset
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

			// Destroy
			case VKTRACE_TPI_VK_vkDestroyDescriptorPool :
			{
				for (auto& desc : desc_pool->second.descriptorSets)
				{
					_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_EXT, desc, pos, frameId, EResOp::Destruct, analyzers );
				}

				CHECK( _descriptorPools.erase( id ) == 1 );
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
										 pos, frameId, EResOp::IndirectAccess, analyzers );
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

			// Destroy
			case VKTRACE_TPI_VK_vkDestroySwapchainKHR :
			{
				for (auto& image : swapchain->second.images)
				{
					_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, image, pos, frameId, EResOp::Destruct, analyzers );
				}

				CHECK( _swapchains.erase( id ) == 1 );
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
				
				_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT, id, pos, frameId, EResOp::Access, analyzers );

				for (uint i = 0; i < packet.pPresentInfo->swapchainCount; ++i)
				{
					auto	swapchain = _swapchains.find( ResourceID(packet.pPresentInfo->pSwapchains[i]) );
					CHECK_ERR( swapchain != _swapchains.end() );

					CHECK_ERR( packet.pPresentInfo->pImageIndices[i] < swapchain->second.images.size() );

					_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT,
											 swapchain->second.images[ packet.pPresentInfo->pImageIndices[i] ],
											 pos, frameId, EResOp::IndirectAccess, analyzers );
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
		if ( pos->packet_id == VKTRACE_TPI_VK_vkBeginCommandBuffer )
		{
			_commandBuffers.insert({ id, {} });
			return true;
		}
		
		auto	cmdbuf = _commandBuffers.find( id );
		if ( cmdbuf == _commandBuffers.end() )
			return true;


		auto&	state = cmdbuf->second;

		switch( pos->packet_id )
		{
			// BeginRenderPass
			case VKTRACE_TPI_VK_vkCmdBeginRenderPass :
			{
				auto&	packet = pos.Cast< packet_vkCmdBeginRenderPass >();
				CHECK_ERR( ResourceID(packet.commandBuffer) == id );

				state.framebuffer	= ResourceID(packet.pRenderPassBegin->framebuffer);
				state.renderPass	= ResourceID(packet.pRenderPassBegin->renderPass);

				auto	fb = _framebuffers.find( ResourceID(packet.pRenderPassBegin->framebuffer) );
				CHECK_ERR( fb != _framebuffers.end() );

				for (auto& view : fb->second.attachments)
				{
					_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_VIEW_EXT, view, pos, frameId, EResOp::IndirectAccess, analyzers );
				}
				break;
			}

			//case VKTRACE_TPI_VK_vkCmdBeginRenderPass2KHR :
			//	break;

			// Next / End RenderPass
			case VKTRACE_TPI_VK_vkCmdNextSubpass :
			case VKTRACE_TPI_VK_vkCmdEndRenderPass :
			{
				// add bookmark to render pass
				_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_RENDER_PASS_EXT, state.renderPass, pos, frameId, EResOp::IndirectAccess, analyzers );

				// add bookmarks to image view
				auto	fb = _framebuffers.find( state.framebuffer );
				CHECK_ERR( fb != _framebuffers.end() );

				for (auto& view : fb->second.attachments)
				{
					_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_VIEW_EXT, view, pos, frameId, EResOp::IndirectAccess, analyzers );
				}
				break;
			}

			// BindPipeline
			case VKTRACE_TPI_VK_vkCmdBindPipeline :
			{
				auto&	packet = pos.Cast< packet_vkCmdBindPipeline >();
				CHECK_ERR( ResourceID(packet.commandBuffer) == id );

				switch( packet.pipelineBindPoint )
				{
					case VK_PIPELINE_BIND_POINT_GRAPHICS :		state.graphicsPipeline	= ResourceID(packet.pipeline);	break;
					case VK_PIPELINE_BIND_POINT_COMPUTE :		state.computePipeline	= ResourceID(packet.pipeline);	break;
					default :									ASSERT(!"unknown bind point");	break;
				}
				break;
			}
			
			// BindDescriptorSets
			case VKTRACE_TPI_VK_vkCmdBindDescriptorSets :
			{
				auto&	packet = pos.Cast< packet_vkCmdBindDescriptorSets >();
				CHECK_ERR( ResourceID(packet.commandBuffer) == id );

				auto&	descriptor_sets = (packet.pipelineBindPoint == VK_PIPELINE_BIND_POINT_GRAPHICS ?
										   state.graphicsDescriptorSets : state.computeDescriptorSets);

				for (uint i = 0; i < packet.descriptorSetCount; ++i)
				{
					descriptor_sets[ packet.firstSet + i ] = ResourceID(packet.pDescriptorSets[i]);
				}
				break;
			}

			// BindIndexBuffer
			case VKTRACE_TPI_VK_vkCmdBindIndexBuffer :
			{
				auto&	packet = pos.Cast< packet_vkCmdBindIndexBuffer >();
				CHECK_ERR( ResourceID(packet.commandBuffer) == id );

				state.indexBuffer = ResourceID(packet.buffer);
				break;
			}

			// BindVertexBuffers
			case VKTRACE_TPI_VK_vkCmdBindVertexBuffers :
			{
				auto&	packet = pos.Cast< packet_vkCmdBindVertexBuffers >();
				CHECK_ERR( ResourceID(packet.commandBuffer) == id );

				for (uint i = 0; i < packet.bindingCount; ++i)
				{
					state.vertexBuffers[ packet.firstBinding + i ] = ResourceID(packet.pBuffers[i]);
				}
				break;
			}

			// DrawIndexed
			case VKTRACE_TPI_VK_vkCmdDrawIndexed :
			case VKTRACE_TPI_VK_vkCmdDrawIndexedIndirect :
			case VKTRACE_TPI_VK_vkCmdDrawIndexedIndirectCountAMD :
			{
				_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, state.indexBuffer, pos, frameId, EResOp::IndirectAccess, analyzers );
				[[fallthrough]];
			}

			// Draw
			case VKTRACE_TPI_VK_vkCmdDraw :
			case VKTRACE_TPI_VK_vkCmdDrawIndirect :
			case VKTRACE_TPI_VK_vkCmdDrawIndirectCountAMD :
			{
				auto	ppln = _graphicsPipelines.find( state.graphicsPipeline );
				CHECK_ERR( ppln != _graphicsPipelines.end() );

				// add bookmarks to vertex buffers
				for (size_t i = 0; i < ppln->second.vertexBuffers.size(); ++i) {
					if ( ppln->second.vertexBuffers[i] )
						_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, state.vertexBuffers[i], pos, frameId, EResOp::IndirectAccess, analyzers );
				}

				// add bookmarks to descriptor sets
				for (uint i = 0; i < ppln->second.descriptorSetCount; ++i) {
					_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_EXT, state.graphicsDescriptorSets[i], pos, frameId, EResOp::IndirectAccess, analyzers );
				}

				_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_EXT, state.graphicsPipeline, pos, frameId, EResOp::IndirectAccess, analyzers );
				_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_FRAMEBUFFER_EXT, state.framebuffer, pos, frameId, EResOp::IndirectAccess, analyzers );
				
				// add bookmarks to image view
				auto	fb = _framebuffers.find( state.framebuffer );
				if ( fb != _framebuffers.end() ) {
					for (auto& view : fb->second.attachments) {
						_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_VIEW_EXT, view, pos, frameId, EResOp::IndirectAccess, analyzers );
					}
				}
				break;
			}

			// Dispatch
			case VKTRACE_TPI_VK_vkCmdDispatch :
			case VKTRACE_TPI_VK_vkCmdDispatchIndirect :
			case VKTRACE_TPI_VK_vkCmdDispatchBaseKHX :
			case VKTRACE_TPI_VK_vkCmdDispatchBase :
			{
				auto	ppln = _computePipelines.find( state.computePipeline );
				CHECK_ERR( ppln != _computePipelines.end() );
				
				// add bookmarks to descriptor sets
				for (uint i = 0; i < ppln->second.descriptorSetCount; ++i) {
					_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_EXT, state.graphicsDescriptorSets[i], pos, frameId, EResOp::IndirectAccess, analyzers );
				}

				_SendResourceUsageEvent( VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_EXT, state.computePipeline, pos, frameId, EResOp::IndirectAccess, analyzers );
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
	bool AppTrace::VkObjectsTracker::_ProcessFramebuffer (ResourceID id, const Iterator &pos)
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
				CHECK( _framebuffers.erase( id ) == 1 );
				break;
			}
		}
		return true;
	}
	
/*
=================================================
	_ProcessPipelineLayout
=================================================
*/
	bool AppTrace::VkObjectsTracker::_ProcessPipelineLayout (ResourceID id, const Iterator &pos)
	{
		switch ( pos->packet_id )
		{
			// Create
			case VKTRACE_TPI_VK_vkCreatePipelineLayout :
			{
				auto&	packet = pos.Cast< packet_vkCreatePipelineLayout >();
				CHECK_ERR( id == ResourceID(*packet.pPipelineLayout) );

				CHECK( _pipelineLayouts.insert({ id, PipelineLayoutInfo{packet.pCreateInfo->setLayoutCount} }).second );
				break;
			}

			// Destroy
			case VKTRACE_TPI_VK_vkDestroyPipelineLayout :
				CHECK( _pipelineLayouts.erase( id ) == 1 );
				break;
		}
		return true;
	}
	
/*
=================================================
	_ProcessPipeline
=================================================
*/
	bool AppTrace::VkObjectsTracker::_ProcessPipeline (ResourceID id, const Iterator &pos)
	{
		switch ( pos->packet_id )
		{
			// CreateGraphicsPipelines
			case VKTRACE_TPI_VK_vkCreateGraphicsPipelines :
			{
				auto&	packet = pos.Cast< packet_vkCreateGraphicsPipelines >();

				for (uint i = 0; i < packet.createInfoCount; ++i)
				{
					if ( id == ResourceID(packet.pPipelines[i]) )
					{
						auto&	info	= packet.pCreateInfos[i];
						auto&	ppln	= _graphicsPipelines.insert({ id, {} }).first->second;
						auto	layout	= _pipelineLayouts.find( ResourceID(info.layout) );
						CHECK_ERR( layout != _pipelineLayouts.end() );

						for (uint j = 0; info.pVertexInputState and j < info.pVertexInputState->vertexBindingDescriptionCount; ++j)
						{
							auto&	bind = info.pVertexInputState->pVertexBindingDescriptions[j];
							ASSERT( bind.binding < ppln.vertexBuffers.size() );

							ppln.vertexBuffers.set( bind.binding );
						}

						ppln.descriptorSetCount = layout->second.descriptorSetCount;
						break;
					}
				}
				break;
			}

			// CreateComputePipelines
			case VKTRACE_TPI_VK_vkCreateComputePipelines :
			{
				auto&	packet = pos.Cast< packet_vkCreateComputePipelines >();

				for (uint i = 0; i < packet.createInfoCount; ++i)
				{
					if ( id == ResourceID(packet.pPipelines[i]) )
					{
						auto&	info	= packet.pCreateInfos[i];
						auto&	ppln	= _computePipelines.insert({ id, {} }).first->second;
						auto	layout	= _pipelineLayouts.find( ResourceID(info.layout) );
						CHECK_ERR( layout != _pipelineLayouts.end() );

						ppln.descriptorSetCount = layout->second.descriptorSetCount;
					}
				}
				break;
			}

			// Destroy
			case VKTRACE_TPI_VK_vkDestroyPipeline :
			{
				CHECK( _graphicsPipelines.erase( id ) != _computePipelines.erase( id ) );
				break;
			}
		}
		return true;
	}


}	// VTC
