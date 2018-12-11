// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "VkPlayer.h"
#include "stl/Algorithms/StringUtils.h"
#include "stl/Algorithms/EnumUtils.h"
#include <thread>
#include <variant>
#include "VUnpacker.h"

namespace VTPlayer
{
#	include "Types/VulkanCreateInfo.h"

/*
=================================================
	constructor
=================================================
*/
	VkPlayer_v100::VkPlayer_v100 (const VulkanSettings &vulkanSettings, const WindowSettings &windowSettings, const PlayerSettings &playerSettings,
								  const SharedPtr<RStream> &traceFile, const SharedPtr<RStream> &dataFile) :
		_trace{ traceFile },				_dataFile{ dataFile },
		_vulkanSettings{ vulkanSettings },	_windowSettings{ windowSettings },
		_playerSettings{ playerSettings }
	{
		VulkanDeviceFn_Init( _vulkan );

		_pendingSubmits.reserve( 16 );
		_perPacketAllocator.SetBlockSize( 4_Mb );
	}
	
/*
=================================================
	destructor
=================================================
*/
	VkPlayer_v100::~VkPlayer_v100 ()
	{
		_Destroy();
	}
	
/*
=================================================
	Play
=================================================
*/
	bool VkPlayer_v100::Play ()
	{
		if ( _isFinished )
			return false;

		_isPaused = false;
		return true;
	}
	
/*
=================================================
	Pause
=================================================
*/
	bool VkPlayer_v100::Pause ()
	{
		// TODO: wait idle?

		_isPaused = true;
		return true;
	}
	
/*
=================================================
	Init
=================================================
*/
	bool VkPlayer_v100::Init (IWindow *wnd)
	{
		CHECK_ERR( wnd );

		_window = wnd;
		_window->AddListener( this );

		_currFrameId = FrameID(0);
		return true;
	}
	
/*
=================================================
	OnResize
=================================================
*/
	void VkPlayer_v100::OnResize (const uint2 &size)
	{
		if ( not _swapchain )
			return;

		CHECK_FATAL( _IsIndirectSwapchainEnabled() );

		VK_CALL( vkDeviceWaitIdle( _vulkan.GetVkDevice() ));

		for (auto pool : _commandPools) {
			if ( pool )
				VK_CALL( vkResetCommandPool( _vulkan.GetVkDevice(), pool, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT ));
		}

		CHECK( _swapchain->Recreate( size ));

		_vkResources[VkResourceIndex<VkSwapchainKHR>][_swapchainId] = ResourceID(_swapchain->GetVkSwapchain());

		CHECK( _BuildQueryCommandBuffers() );
	}
	
/*
=================================================
	OnDestroy
=================================================
*/
	void VkPlayer_v100::OnDestroy ()
	{
		_Destroy();
	}
	
/*
=================================================
	OnKey
=================================================
*/
	void VkPlayer_v100::OnKey (StringView key, EKeyAction action)
	{
		// single press only
		if ( action != EKeyAction::Down )
			return;

		if ( key == "space" )
			_isPaused = not _isPaused;

		if ( key == "arrow right" )
			_playOneFrame = true;

		if ( key == "S" )
			_playWithSourceFPS = not _playWithSourceFPS;

		if ( key == "escape" )
			_isFinished = true;
	}

/*
=================================================
	_Destroy
=================================================
*/
	void VkPlayer_v100::_Destroy ()
	{
		_isFinished = true;

		if ( _vulkan.GetVkDevice() )
			VK_CALL( vkDeviceWaitIdle( _vulkan.GetVkDevice() ));

		_DestroyIndirectSwapchain();
		_DestroyQueryPools();
		_DestroySemaphores();

		for (auto& pool : _commandPools) {
			if ( pool )
				vkDestroyCommandPool( _vulkan.GetVkDevice(), pool, null );
		}
		_commandPools.clear();

		if ( _memAllocator ) {
			vmaDestroyAllocator( _memAllocator );
			_memAllocator = null;
		}

		if ( _swapchain ) {
			_swapchain->Destroy();
			_swapchain.reset();
		}

		_vulkan.Destroy();

		if ( _window ) {
			_window->RemoveListener( this );
			_window = null;
		}
	}

/*
=================================================
	Draw
=================================================
*/
	bool VkPlayer_v100::Draw ()
	{
		if ( _isFinished or not _window )
			return false;

		if ( not _window->Update() or (_isPaused and not _playOneFrame) )
		{
			std::this_thread::sleep_for( std::chrono::milliseconds(10) );
			return true;
		}

		_playOneFrame = false;

		const FrameID	last_frame_id = _currFrameId;

		CHECK_ERR( _PrepareData( last_frame_id ));

		while ( (last_frame_id == _currFrameId) and _RunCommand() )
		{}

		return true;
	}

/*
=================================================
	_RunCommand
=================================================
*/
	bool VkPlayer_v100::_RunCommand ()
	{
		_perPacketAllocator.Discard();

		if ( not _trace.ReadNext() ) {
			_isFinished = true;
			return false;
		}

		VUnpacker	unpacker{ _trace.GetPacketData(), _trace.GetPacketSize(), _trace.GetPacketOffset(), _vkResources, _perPacketAllocator };

		if ( _OverridePacketProcessor( EVulkanPacketID(_trace.GetPacketID()), unpacker ) )
			return true;

		return _RunCommand2( EVulkanPacketID(_trace.GetPacketID()), unpacker );
	}
	
/*
=================================================
	_RunCommand2
=================================================
*/
	bool VkPlayer_v100::_RunCommand2 (EVulkanPacketID packetId, VUnpacker &unpacker)
	{
		ENABLE_ENUM_CHECKS();
		switch ( packetId )
		{
			case EVulkanPacketID::End :									_isFinished = true;										break;
			case EVulkanPacketID::SetData :								CHECK( _SetData( unpacker ));							break;

			case EVulkanPacketID::VInitializeResource :					CHECK( _Initializeresource( unpacker ));				break;
			case EVulkanPacketID::CreateVkDevice :						CHECK( _CreateDevice( unpacker ));						break;

			case EVulkanPacketID::VMapMemory :							CHECK( _MapMemory( unpacker ));							break;
			case EVulkanPacketID::VUnmapMemory :						CHECK( _UnmapMemory( unpacker ));						break;
			case EVulkanPacketID::VLoadDataToMappedMemory :				CHECK( _LoadDataToMappedMemory( unpacker ));			break;

			case EVulkanPacketID::VAllocateBufferMemory :				CHECK( _AllocateBufferMemory( unpacker ));				break;
			case EVulkanPacketID::VAllocateImageMemory :				CHECK( _AllocateImageMemory( unpacker ));				break;
			case EVulkanPacketID::VFreeBufferMemory :					CHECK( _FreeBufferMemory( unpacker ));					break;
			case EVulkanPacketID::VFreeImageMemory :					CHECK( _FreeImageMemory( unpacker ));					break;
			case EVulkanPacketID::VLoadDataToBuffer :					CHECK( _LoadDataToBuffer( unpacker ));					break;
			case EVulkanPacketID::VLoadDataToImage :					CHECK( _LoadDataToImage( unpacker ));					break;

			case EVulkanPacketID::VCreateShaderModule :					CHECK( _CreateShaderModule( unpacker ));				break;
			case EVulkanPacketID::VCreatePipelineCache :				CHECK( _CreatePipelineCache( unpacker ));				break;
			case EVulkanPacketID::VCmdUpdateBuffer :					CHECK( _CmdUpdateBuffer( unpacker ));					break;

			case EVulkanPacketID::VAcquireNextImageKHR :				CHECK( _AcquireNextImage( unpacker ));					break;
			case EVulkanPacketID::VQueuePresentKHR :					CHECK( _QueuePresent( unpacker ));						break;

			case EVulkanPacketID::VCmdPushDescriptorSetWithTemplate :	CHECK( _CmdPushDescriptorSetWithTemplate( unpacker ));	break;
			case EVulkanPacketID::VUpdateDescriptorSetWithTemplate :	CHECK( _UpdateDescriptorSetWithTemplate( unpacker ));	break;

			case EVulkanPacketID::VImageCapture :						CHECK( _ImageCapture( unpacker ));						break;
			case EVulkanPacketID::VBufferCapture :						CHECK( _BufferCapture( unpacker ));						break;
			case EVulkanPacketID::VImageCaptureReady :					break;
			case EVulkanPacketID::VBufferCaptureReady :					break;

			case EVulkanPacketID::VTimerStart :							break;
			case EVulkanPacketID::VTimerStop :							break;
			case EVulkanPacketID::VTimerReady :							break;
			case EVulkanPacketID::VCpuTimerStart :						break;
			case EVulkanPacketID::VCpuTimerStop :						break;

			#include "Generated/VulkanTraceFuncUnpacker.h"
			
			case EVulkanPacketID::_VulkanApi :
			case EVulkanPacketID::_V100 :
			case EVulkanPacketID::_CustomBit :
			default :
				RETURN_ERR( "unsupported instruction" );
		}
		DISABLE_ENUM_CHECKS();

		return true;
	}

/*
=================================================
	_LoadData
=================================================
*/
	ArrayView<uint8_t>  VkPlayer_v100::_LoadData (DataID id) const
	{
		auto	data = _loadableData.find( id );
		CHECK_ERR( data != _loadableData.end() );

		return data->second;
	}

/*
=================================================
	_LoadDataPart
=================================================
*/
	bool  VkPlayer_v100::_LoadDataPart (FilePart &part)
	{
		CHECK_ERR( part.size < ~size_t(0) );

		auto	iter = _loadableData.insert({ part.id, {} });
		ASSERT( iter.second );	// all IDs must be unique

		auto&	buffer = iter.first->second;

		buffer.resize( size_t(part.size) );		// TODO: check for bad alloc exception

		CHECK_ERR( _dataFile->SeekSet( BytesU(part.offset) ));
		CHECK_ERR( _dataFile->Read( buffer.data(), BytesU(buffer.size()) ));

		return true;
	}

/*
=================================================
	_PrepareData
=================================================
*/
	bool  VkPlayer_v100::_PrepareData (FrameID frameId)
	{
		// load required data
		auto	load_ev = _loadEvents.find( frameId );

		if ( load_ev != _loadEvents.end() )
		{
			for (auto& part : load_ev->second) {
				CHECK_ERR( _LoadDataPart( part ));
			}

			_loadEvents.erase( frameId );
		}

		// unload data
		auto	unload_ev = _unloadEvents.find( frameId );

		if ( unload_ev != _unloadEvents.end() )
		{
			for (auto& id : unload_ev->second) {
				_loadableData.erase( id );
			}

			_unloadEvents.erase( frameId );
		}

		return true;
	}
	
/*
=================================================
	features
=================================================
*/
	inline bool  VkPlayer_v100::_IsOriginMemoryModel () const
	{
		return not EnumEq( VulkanCreateInfo::EImplFlags(_implementationFlags), VulkanCreateInfo::EImplFlags::OverrideMemoryAllocation );
	}
	
	inline bool  VkPlayer_v100::_IsQueueFamilyRemappingEnabled () const
	{
		return EnumEq( VulkanCreateInfo::EImplFlags(_implementationFlags), VulkanCreateInfo::EImplFlags::RemapQueueFamilies );
	}
	
	inline bool  VkPlayer_v100::_IsIndirectSwapchainEnabled () const
	{
		return EnumEq( VulkanCreateInfo::EImplFlags(_implementationFlags), VulkanCreateInfo::EImplFlags::IndirectSwapchain );
	}
	
	inline bool  VkPlayer_v100::_IsProfilingEnabled () const
	{
		return EnumEq( _playerSettings.flags, EPlayerFlags::EnableGpuBenchmark );
	}

/*
=================================================
	CalcFirstFrame
=================================================
*/
	ND_ static uint  CalcFirstFrame (uint frameIdOffset, uint frameId, uint64_t dataSize)
	{
		return frameIdOffset + frameId;
		//return frameIdOffset + uint( uint64_t(frameId) - Max( uint64_t(frameId), (dataSize >> 24) ));
	}
	
/*
=================================================
	_SetSourceFPS
=================================================
*/
	bool VkPlayer_v100::_SetData (VUnpacker &unpacker)
	{
		FilePart	part;
		part.id			<< unpacker;
		part.offset		<< unpacker;
		part.size		<< unpacker;
		part.firstFrame	<< unpacker;
		part.lastFrame	<< unpacker;
		
		const FrameID	next_frame	= _currFrameId + 1;
		const FrameID	first_frame = CalcFirstFrame( next_frame, part.firstFrame, part.size );
		const FrameID	last_frame	= next_frame + part.lastFrame + 1;

		ASSERT( first_frame > _currFrameId );
		ASSERT( last_frame > first_frame );

		_unloadEvents.insert({ last_frame, {} }).first->second.push_back( part.id );
		_loadEvents.insert({ first_frame, {} }).first->second.push_back( std::move(part) );

		return true;
	}

/*
=================================================
	_MapMemory
=================================================
*/
	bool VkPlayer_v100::_MapMemory (VUnpacker &unpacker)
	{
		CHECK_ERR( _IsOriginMemoryModel() );

		auto	device	= unpacker.Get<VkDevice>();
		auto	memory	= unpacker.Get<VkDeviceMemory>();
		auto	offset	= unpacker.Get<VkDeviceSize>();
		auto	size	= unpacker.Get<VkDeviceSize>();
		auto	flags	= unpacker.Get<VkMemoryMapFlags>();
		void*	ptr		= null;

		VK_CHECK( vkMapMemory( device, memory, offset, size, flags, OUT &ptr ));
		
		auto&	mem = _mappedMemory.insert({ ResourceID(memory), {} }).first->second;
		CHECK( mem.mappedPtr == null );

		mem = { ptr, offset, size };
		return true;
	}
	
/*
=================================================
	_UnmapMemory
=================================================
*/
	bool VkPlayer_v100::_UnmapMemory (VUnpacker &unpacker)
	{
		CHECK_ERR( _IsOriginMemoryModel() );

		auto	device	= unpacker.Get<VkDevice>();
		auto	memory	= unpacker.Get<VkDeviceMemory>();

		vkUnmapMemory( device, memory );

		auto	mem		= _mappedMemory.find( ResourceID(memory) );
		CHECK_ERR( mem != _mappedMemory.end() );
		CHECK( mem->second.mappedPtr != null );

		mem->second = {};
		return true;
	}
	
/*
=================================================
	_LoadDataToMappedMemory
=================================================
*/
	bool VkPlayer_v100::_LoadDataToMappedMemory (VUnpacker &unpacker)
	{
		CHECK_ERR( _IsOriginMemoryModel() );

		auto	memory		= unpacker.Get<VkDeviceMemory>();
		auto	data_id		= unpacker.Get<DataID>();
		auto	mem_offset	= unpacker.Get<VkDeviceSize>();
		auto	data_size	= unpacker.Get<uint64_t>();
		
		auto	mem = _mappedMemory.find( ResourceID(memory) );
		CHECK_ERR( mem != _mappedMemory.end() );
		CHECK_ERR( mem->second.mappedPtr != null );
		
		auto	data = _loadableData.find( data_id );
		CHECK_ERR( data != _loadableData.end() );
		CHECK_ERR( data->second.size() == data_size );

		CHECK_ERR( (mem_offset + data_size) <= mem->second.size );

		memcpy( mem->second.mappedPtr + BytesU(mem_offset), data->second.data(), data_size );
		return true;
	}
	
/*
=================================================
	_CreateShaderModule
=================================================
*/
	bool VkPlayer_v100::_CreateShaderModule (VUnpacker &unpacker)
	{
		auto*	create_info	= unpacker.Get<VkShaderModuleCreateInfo *>();
		auto	data_id		= unpacker.Get<DataID>();
		auto	device		= unpacker.Get<VkDevice>();
		auto	shader_id	= size_t(*unpacker.Get< NearUInt<VkShaderModule> *>());

		auto	shader_data	= _LoadData( data_id );
		CHECK_ERR( not shader_data.empty() );

		create_info->codeSize	= shader_data.size();
		create_info->pCode		= Cast<uint>( shader_data.data() );

		VkShaderModule	shader_module;
		VK_CHECK( vkCreateShaderModule( device, create_info, null, OUT &shader_module ));

		_vkResources[VkResourceIndex<VkShaderModule>][shader_id] = ResourceID(shader_module);
		return true;
	}
	
/*
=================================================
	_CreatePipelineCache
=================================================
*/
	bool VkPlayer_v100::_CreatePipelineCache (VUnpacker &unpacker)
	{
		auto*	create_info	= unpacker.Get<VkPipelineCacheCreateInfo *>();
		auto	device		= unpacker.Get<VkDevice>();
		auto	cache_id	= size_t(*unpacker.Get< NearUInt<VkPipelineCache> *>());

		create_info->pInitialData = null;
		create_info->initialDataSize = 0;	// may be not supported

		VkPipelineCache		ppln_cache;
		VK_CHECK( vkCreatePipelineCache( device, create_info, null, OUT &ppln_cache ));
		
		_vkResources[VkResourceIndex<VkPipelineCache>][cache_id] = ResourceID(ppln_cache);
		return true;
	}
	
/*
=================================================
	_CmdUpdateBuffer
=================================================
*/
	bool VkPlayer_v100::_CmdUpdateBuffer (VUnpacker &unpacker)
	{
		auto	cmd_buffer	= unpacker.Get<VkCommandBuffer>();
		auto	dst_buffer	= unpacker.Get<VkBuffer>();
		auto	dst_offset	= unpacker.Get<VkDeviceSize>();
		auto	data_size	= unpacker.Get<VkDeviceSize>();
		auto	data_id		= unpacker.Get<DataID>();
		
		auto	buffer_data	= _LoadData( data_id );
		CHECK_ERR( buffer_data.size() == data_size );

		vkCmdUpdateBuffer( cmd_buffer, dst_buffer, dst_offset, buffer_data.size(), buffer_data.data() );
		return true;
	}
	
/*
=================================================
	_AcquireIndirectSwapchainImage
=================================================
*/
	bool VkPlayer_v100::_AcquireIndirectSwapchainImage (size_t imageId)
	{
		for (size_t i = 0; i < _indirectSwapchain.images.size(); ++i)
		{
			if ( _indirectSwapchain.images[i].id == imageId )
			{
				_indirectSwapchain.imageIndex = uint(i);
				return true;
			}
		}

		RETURN_ERR( "can't find swapchain image!" );
	}

/*
=================================================
	_AcquireNextImage
=================================================
*/
	bool VkPlayer_v100::_AcquireNextImage (VUnpacker &unpacker)
	{
		auto	device		= unpacker.Get<VkDevice>();
		auto	swapchain	= unpacker.Get<VkSwapchainKHR>();
		auto	timeout		= unpacker.Get<uint64_t>();
		auto	semaphore	= unpacker.Get<VkSemaphore>();
		auto	fence		= unpacker.Get<VkFence>();
		auto	image_id	= unpacker.Get<NearUInt<VkImage>>();

		ASSERT( fence == VK_NULL_HANDLE );
		ASSERT( device == _vulkan.GetVkDevice() );
		ASSERT( swapchain == _swapchain->GetVkSwapchain() );

		if ( _IsProfilingEnabled() ) {
			CHECK( _InsertQueryOnAcquireImage( INOUT semaphore ));
		}

		VK_CALL( _swapchain->AcquireNextImage( semaphore ));

		if ( _IsIndirectSwapchainEnabled() )
			return _AcquireIndirectSwapchainImage( size_t(image_id) );


		CHECK_ERR( _vkResources[VkResourceIndex<VkImage>][image_id] == ResourceID(_swapchain->GetCurrentImage()) );
		
		FG_UNUSED( timeout );
		return true;
	}
	
/*
=================================================
	_QueuePresentToIndirectSwapchain
=================================================
*/
	bool VkPlayer_v100::_QueuePresentToIndirectSwapchain (size_t queueId, VkQueue queue, VkImage image, ArrayView<VkSemaphore> waitSemaphores)
	{
		auto&	current = _indirectSwapchain.images[_indirectSwapchain.imageIndex];
		CHECK_ERR( current.image == image );

		// find queue family index
		uint	family_index = ~0u;
		{
			for (auto& info : _vulkan.GetVkQuues()) {
				if ( info.id == queue )
					family_index = info.queueIndex;
			}
			CHECK_ERR( family_index < _commandPools.size() );
			CHECK_ERR( _commandPools[family_index] );
		}

		// reset/create command buffer
		auto	pool = _commandPools[family_index];

		if ( current.cmdbuf and current.cmdpool != pool )
		{
			vkFreeCommandBuffers( _vulkan.GetVkDevice(), current.cmdpool, 1, &current.cmdbuf );
			current.cmdbuf = VK_NULL_HANDLE;
		}

		if ( not current.cmdbuf )
		{
			VkCommandBufferAllocateInfo		info = {};
			info.sType				= VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			info.commandPool		= pool;
			info.level				= VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			info.commandBufferCount	= 1;

			VK_CALL( vkAllocateCommandBuffers( _vulkan.GetVkDevice(), &info, OUT &current.cmdbuf ));
			current.cmdpool = pool;
		}

		// bake command buffer
		{
			VkCommandBufferBeginInfo	begin = {};
			begin.sType	= VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			begin.flags	= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

			VK_CALL( vkBeginCommandBuffer( current.cmdbuf, &begin ));
			
			// image layout undefined to transfer optimal
			VkImageMemoryBarrier	barrier;
			barrier.sType					= VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			barrier.pNext					= null;
			barrier.image					= _swapchain->GetCurrentImage();
			barrier.oldLayout				= VK_IMAGE_LAYOUT_UNDEFINED;
			barrier.newLayout				= VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
			barrier.srcAccessMask			= VK_ACCESS_MEMORY_READ_BIT;
			barrier.dstAccessMask			= VK_ACCESS_TRANSFER_WRITE_BIT;
			barrier.srcQueueFamilyIndex		= VK_QUEUE_FAMILY_IGNORED;
			barrier.dstQueueFamilyIndex		= VK_QUEUE_FAMILY_IGNORED;
			barrier.subresourceRange.aspectMask		= VK_IMAGE_ASPECT_COLOR_BIT;
			barrier.subresourceRange.baseMipLevel	= 0;
			barrier.subresourceRange.levelCount		= 1;
			barrier.subresourceRange.baseArrayLayer	= 0;
			barrier.subresourceRange.layerCount		= 1;

			vkCmdPipelineBarrier( current.cmdbuf, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0,
								  0, null, 0, null, 1, &barrier );

			// blit image into swapchain image
			VkImageBlit		region = {};
			region.srcOffsets[0]				= { 0, 0, 0 };
			region.srcOffsets[1]				= { int(_indirectSwapchain.dimension.x), int(_indirectSwapchain.dimension.y), 1 };
			region.srcSubresource.aspectMask	= VK_IMAGE_ASPECT_COLOR_BIT;
			region.srcSubresource.baseArrayLayer= 0;
			region.srcSubresource.layerCount	= 1;
			region.srcSubresource.mipLevel		= 0;

			region.dstOffsets[0]				= { 0, 0, 0 };
			region.dstOffsets[1]				= { int(_swapchain->GetSurfaceSize().x), int(_swapchain->GetSurfaceSize().y), 1 };
			region.dstSubresource.aspectMask	= VK_IMAGE_ASPECT_COLOR_BIT;
			region.dstSubresource.baseArrayLayer= 0;
			region.dstSubresource.layerCount	= 1;
			region.dstSubresource.mipLevel		= 0;

			vkCmdBlitImage( current.cmdbuf,
							image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
							_swapchain->GetCurrentImage(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
						    1, &region, VK_FILTER_LINEAR );
			
			// image layout transfer optimal to present source
			barrier.oldLayout				= VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
			barrier.newLayout				= VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
			barrier.srcAccessMask			= VK_ACCESS_TRANSFER_WRITE_BIT;
			barrier.dstAccessMask			= VK_ACCESS_MEMORY_READ_BIT;

			vkCmdPipelineBarrier( current.cmdbuf, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, 0,
								  0, null, 0, null, 1, &barrier );

			VK_CALL( vkEndCommandBuffer( current.cmdbuf ));
		}

		// submit command buffer
		{
			FixedArray< VkPipelineStageFlags, 16 >	wait_dst_stage_mask;

			for (uint i = 0; i < waitSemaphores.size(); ++i) {
				wait_dst_stage_mask.push_back( VK_PIPELINE_STAGE_ALL_COMMANDS_BIT );	// TODO
			}

			VkSubmitInfo	submits[2]		= {};
			uint			submits_count	= 1;

			submits[0].sType				= VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submits[0].commandBufferCount	= 1;
			submits[0].pCommandBuffers		= &current.cmdbuf;
			submits[0].signalSemaphoreCount	= 1;
			submits[0].pSignalSemaphores	= &_indirectSwapchain.renderFinished;
			submits[0].waitSemaphoreCount	= uint(waitSemaphores.size());
			submits[0].pWaitDstStageMask	= waitSemaphores.empty() ? null : wait_dst_stage_mask.data();
			submits[0].pWaitSemaphores		= waitSemaphores.data();

			if ( _IsProfilingEnabled() )
			{
				CHECK_ERR( _InsertQueryOnPresent( OUT submits[submits_count], queueId ));
				++submits_count;
			}

			VK_CALL( vkQueueSubmit( queue, submits_count, submits, VK_NULL_HANDLE ));
		}

		// present
		VK_CHECK( _swapchain->Present( queue, {_indirectSwapchain.renderFinished} ));
		return true;
	}
	
/*
=================================================
	_QueuePresentToDirectSwapchain
=================================================
*/
	bool VkPlayer_v100::_QueuePresentToDirectSwapchain (size_t queueId, VkQueue queue, VkImage image, ArrayView<VkSemaphore> waitSemaphores)
	{
		ASSERT( image == _swapchain->GetCurrentImage() );

		if ( _IsProfilingEnabled() )
		{
			VkSubmitInfo	submit;
			CHECK_ERR( _InsertQueryOnPresent( OUT submit, queueId ));
			
			VK_CALL( vkQueueSubmit( queue, 1, &submit, VK_NULL_HANDLE ));
		}

		VK_CHECK( _swapchain->Present( queue, waitSemaphores ));
		return true;
	}

/*
=================================================
	_QueuePresent
=================================================
*/
	bool VkPlayer_v100::_QueuePresent (VUnpacker &unpacker)
	{
		auto	frame_time			= Nonoseconds{unpacker.Get<uint64_t>()};
		auto	queue_id			= unpacker.Get< NearUInt<VkQueue> >();
		auto	queue				= VkQueue(_vkResources[VkResourceIndex<VkQueue>][queue_id]);
		auto	image				= unpacker.Get<VkImage>();
		auto	semaphores_count	= unpacker.Get<uint>();
		auto*	wait_semaphores		= unpacker.Get<VkSemaphore const*>();

		++_currFrameId;
		_UpdateFrameStatistic( queue_id );
		
		if ( _IsIndirectSwapchainEnabled() )
			CHECK_ERR( _QueuePresentToIndirectSwapchain( queue_id, queue, image, {wait_semaphores, semaphores_count} ))
		else
			CHECK_ERR( _QueuePresentToDirectSwapchain( queue_id, queue, image, {wait_semaphores, semaphores_count} ));


		// add delay to limit FPS
		if ( _playWithSourceFPS )
		{
			TimePoint_t		time		= TimePoint_t::clock::now();
			Nonoseconds		dt			= time - _lastPresentTime;
			Nonoseconds		delay		= frame_time - dt;
			Nonoseconds		max_delay	= Nonoseconds{100'000'000};
			_lastPresentTime = time;

			if ( delay > Nonoseconds(0) )
				std::this_thread::sleep_for( Min(delay, max_delay) );
		}
		return true;
	}
	
/*
=================================================
	_AllocateBufferMemory
=================================================
*/
	bool VkPlayer_v100::_AllocateBufferMemory (VUnpacker &unpacker)
	{
		CHECK_ERR( not _IsOriginMemoryModel() );

		auto	device			= unpacker.Get<VkDevice>();
		auto	buffer_id		= unpacker.Get< NearUInt<VkBuffer> >();
		auto	pool_id			= unpacker.Get<uint64_t>();
		auto	create_flags	= unpacker.Get<VmaAllocationCreateFlags>();
		auto	usage_flags		= unpacker.Get<VmaMemoryUsage>();
		auto	property_flags	= unpacker.Get<VkMemoryPropertyFlags>();

		VkBuffer	buffer = VkBuffer(buffer_id);
		unpacker.RemapVkResources( INOUT &buffer, 1 );
		
		CHECK_ERR( buffer_id < _bufferAlloc.size() );

		auto&	mem = _bufferAlloc[buffer_id];
		CHECK_ERR( mem.alloc == null );

		VmaAllocationCreateInfo		info = {};
		info.flags			= create_flags;
		info.usage			= usage_flags;
		info.requiredFlags	= 0;
		info.preferredFlags	= property_flags;
		info.memoryTypeBits	= 0;
		info.pool			= VK_NULL_HANDLE;
		info.pUserData		= null;

		VK_CHECK( vmaAllocateMemoryForBuffer( _memAllocator, buffer, &info, OUT &mem.alloc, null ));
		VK_CHECK( vmaBindBufferMemory( _memAllocator, mem.alloc, buffer ));
		
		VmaAllocationInfo	alloc_info = {};
		vmaGetAllocationInfo( _memAllocator, mem.alloc, OUT &alloc_info );
		
		mem.isCoherent	= !!(_vulkan.GetDeviceMemoryProperties().memoryTypes[alloc_info.memoryType].propertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		
		FG_UNUSED( device );
		FG_UNUSED( pool_id );
		return true;
	}
	
/*
=================================================
	_AllocateImageMemory
=================================================
*/
	bool VkPlayer_v100::_AllocateImageMemory (VUnpacker &unpacker)
	{
		CHECK_ERR( not _IsOriginMemoryModel() );

		auto	device			= unpacker.Get<VkDevice>();
		auto	image_id		= unpacker.Get< NearUInt<VkImage> >();
		auto	pool_id			= unpacker.Get<uint64_t>();
		auto	create_flags	= unpacker.Get<VmaAllocationCreateFlags>();
		auto	usage_flags		= unpacker.Get<VmaMemoryUsage>();
		auto	property_flags	= unpacker.Get<VkMemoryPropertyFlags>();

		VkImage	image = VkImage(image_id);
		unpacker.RemapVkResources( INOUT &image, 1 );
		
		CHECK_ERR( image_id < _imageAlloc.size() );

		auto&	mem = _imageAlloc[image_id];
		CHECK_ERR( mem.alloc == null );

		VmaAllocationCreateInfo		info = {};
		info.flags			= create_flags;
		info.usage			= usage_flags;
		info.requiredFlags	= 0;
		info.preferredFlags	= property_flags;
		info.memoryTypeBits	= 0;
		info.pool			= VK_NULL_HANDLE;
		info.pUserData		= null;

		VK_CHECK( vmaAllocateMemoryForImage( _memAllocator, image, &info, OUT &mem.alloc, null ));
		VK_CHECK( vmaBindImageMemory( _memAllocator, mem.alloc, image ));
		
		VmaAllocationInfo	alloc_info = {};
		vmaGetAllocationInfo( _memAllocator, mem.alloc, OUT &alloc_info );

		mem.isCoherent	= !!(_vulkan.GetDeviceMemoryProperties().memoryTypes[alloc_info.memoryType].propertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		
		FG_UNUSED( device );
		FG_UNUSED( pool_id );
		return true;
	}
	
/*
=================================================
	_FreeBufferMemory
=================================================
*/
	bool VkPlayer_v100::_FreeBufferMemory (VUnpacker &unpacker)
	{
		CHECK_ERR( not _IsOriginMemoryModel() );

		auto	device		= unpacker.Get<VkDevice>();
		auto	buffer_id	= unpacker.Get< NearUInt<VkBuffer> >();
		
		CHECK_ERR( buffer_id < _bufferAlloc.size() );

		auto&	mem = _bufferAlloc[buffer_id];
		CHECK_ERR( mem.alloc );

		vmaFreeMemory( _memAllocator, mem.alloc );
		mem = {};
		
		FG_UNUSED( device );
		return true;
	}
	
/*
=================================================
	_FreeImageMemory
=================================================
*/
	bool VkPlayer_v100::_FreeImageMemory (VUnpacker &unpacker)
	{
		CHECK_ERR( not _IsOriginMemoryModel() );

		auto	device		= unpacker.Get<VkDevice>();
		auto	image_id	= unpacker.Get< NearUInt<VkImage> >();
		
		CHECK_ERR( image_id < _imageAlloc.size() );

		auto&	mem = _imageAlloc[image_id];
		CHECK_ERR( mem.alloc );

		vmaFreeMemory( _memAllocator, mem.alloc );
		mem = {};
		
		FG_UNUSED( device );
		return true;
	}
	
/*
=================================================
	_LoadDataToVMAMemory
=================================================
*/
	bool VkPlayer_v100::_LoadDataToVMAMemory (VkDevice device, MemAllocationInfo &mem, DataID dataId, VkDeviceSize offset, VkDeviceSize size) const
	{
		auto	data = _loadableData.find( dataId );
		CHECK_ERR( data != _loadableData.end() );
		CHECK_ERR( data->second.size() == size );
		
		VmaAllocationInfo	alloc_info = {};
		vmaGetAllocationInfo( _memAllocator, mem.alloc, OUT &alloc_info );
		
		CHECK_ERR( alloc_info.pMappedData );
		CHECK_ERR( (offset + size) <= alloc_info.size );

		memcpy( alloc_info.pMappedData + BytesU(offset), data->second.data(), size );

		if ( not mem.isCoherent )
		{
			VkMappedMemoryRange	range = {};
			range.sType		= VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
			range.memory	= alloc_info.deviceMemory;
			range.offset	= alloc_info.offset + offset;
			range.size		= size;
			VK_CALL( vkFlushMappedMemoryRanges( device, 1, &range ));
		}
		return true;
	}

/*
=================================================
	_LoadDataToBuffer
=================================================
*/
	bool VkPlayer_v100::_LoadDataToBuffer (VUnpacker &unpacker)
	{
		CHECK_ERR( not _IsOriginMemoryModel() );

		auto	device		= unpacker.Get<VkDevice>();
		auto	buffer_id	= unpacker.Get< NearUInt<VkBuffer> >();
		auto	data_id		= unpacker.Get<DataID>();
		auto	offset		= unpacker.Get<VkDeviceSize>();
		auto	size		= unpacker.Get<VkDeviceSize>();
		
		CHECK_ERR( buffer_id < _bufferAlloc.size() );

		return _LoadDataToVMAMemory( device, _bufferAlloc[buffer_id], data_id, offset, size );
	}
	
/*
=================================================
	_LoadDataToImage
=================================================
*/
	bool VkPlayer_v100::_LoadDataToImage (VUnpacker &unpacker)
	{
		CHECK_ERR( not _IsOriginMemoryModel() );

		auto	device		= unpacker.Get<VkDevice>();
		auto	image_id	= unpacker.Get< NearUInt<VkImage> >();
		auto	data_id		= unpacker.Get<DataID>();
		auto	offset		= unpacker.Get<VkDeviceSize>();
		auto	size		= unpacker.Get<VkDeviceSize>();
		
		CHECK_ERR( image_id < _imageAlloc.size() );

		return _LoadDataToVMAMemory( device, _imageAlloc[image_id], data_id, offset, size );
	}
	
/*
=================================================
	_CmdPushDescriptorSetWithTemplate
=================================================
*/
	bool VkPlayer_v100::_CmdPushDescriptorSetWithTemplate (VUnpacker &)
	{
		ASSERT(false);	// TODO
		return false;
	}
	
/*
=================================================
	_UpdateDescriptorSetWithTemplate
=================================================
*/
	bool VkPlayer_v100::_UpdateDescriptorSetWithTemplate (VUnpacker &)
	{
		ASSERT(false);	// TODO
		return false;
	}
	
/*
=================================================
	_CreateDevice
=================================================
*/
	bool VkPlayer_v100::_CreateDevice (VUnpacker &unpacker)
	{
		CHECK_ERR( _vulkan.GetVkInstance() == VK_NULL_HANDLE );
		CHECK_ERR( _vulkan.GetVkDevice() == VK_NULL_HANDLE );

		VulkanCreateInfo	ci = {};
		
		// instance
		ci.instanceVersion		<< unpacker;
		ci.instanceExtensionCount << unpacker;
		ci.instanceExtensions	= unpacker.Get<char const* const*>( ci.instanceExtensionCount );
		ci.instanceID			= VkInstance( unpacker.Get< NearUInt<VkInstance> >());

		// device
		ci.deviceExtensionCount	<< unpacker;
		ci.deviceExtensions		= unpacker.Get<char const* const*>( ci.deviceExtensionCount );
		ci.physicalDeviceID		= VkPhysicalDevice( unpacker.Get< NearUInt<VkPhysicalDevice> >());
		ci.deviceID				= VkDevice( unpacker.Get< NearUInt<VkDevice> >());

		// queue
		ci.queueCount			<< unpacker;
		ci.queueIDs				= BitCast<VkQueue *>( unpacker.Get< NearUInt<VkQueue> *>( ci.queueCount ));
		ci.queueFamilies		= unpacker.Get<VkQueueFlags const*>( ci.queueCount );
		ci.queuePriorities		= unpacker.Get<float const*>( ci.queueCount );

		// swapchain
		ci.swapchainType			<< unpacker;
		ci.swapchainID				= VkSwapchainKHR( unpacker.Get< NearUInt<VkSwapchainKHR> >());
		ci.swapchainImageWidth		<< unpacker;
		ci.swapchainImageHeight		<< unpacker;
		ci.swapchainColorFormat		<< unpacker;
		ci.swapchainColorSpace		<< unpacker;
		ci.swapchainMinImageCount	<< unpacker;
		ci.swapchainImageArrayLayers<< unpacker;
		ci.swapchainPreTransform	<< unpacker;
		ci.swapchainPresentMode		<< unpacker;
		ci.swapchainCompositeAlpha	<< unpacker;
		ci.swapchainColorImageUsage	<< unpacker;
		ci.swapchainImageLayout		<< unpacker;
		ci.swapchainImageCount		<< unpacker;
		ci.swapchainImageIDs		= BitCast<VkImage *>( unpacker.Get< NearUInt<VkImage> *>( ci.swapchainImageCount ));

		ci.implementationFlags		<< unpacker;
		FG_UNUSED( unpacker.Get<uint>() );

		_implementationFlags		= uint(ci.implementationFlags);

		CHECK_ERR( _CreateDevice( ci ));
		CHECK_ERR( _CreateCommandPools() );
		CHECK_ERR( _CreateSwapchain( ci ));
		CHECK_ERR( _CreateQueryPools() );
		CHECK_ERR( _CreateSemaphores() );

		++_currFrameId;
		return true;
	}
	
/*
=================================================
	_CreateDevice
=================================================
*/
	bool VkPlayer_v100::_CreateDevice (const VulkanCreateInfo &ci)
	{
		// initialize
		Array<const char*>						instance_layers;
		Array<const char*>						instance_extensions;
		Array<const char*>						device_extensions;
		Array<VulkanDevice::QueueCreateInfo>	queue_ci;

		if ( EnumEq( _playerSettings.flags, EPlayerFlags::DebugMode ) )
		{
			instance_layers.assign( VulkanDevice::GetRecomendedInstanceLayers().begin(), VulkanDevice::GetRecomendedInstanceLayers().end() );
			instance_extensions.assign( VulkanDevice::GetRecomendedInstanceExtensions().begin(), VulkanDevice::GetRecomendedInstanceExtensions().end() );
			device_extensions.assign( VulkanDevice::GetRecomendedDeviceExtensions().begin(), VulkanDevice::GetRecomendedDeviceExtensions().end() );
		}

		if ( ci.instanceExtensionCount and ci.instanceExtensions )
			instance_extensions.insert( instance_extensions.end(), ci.instanceExtensions, ci.instanceExtensions + ci.instanceExtensionCount );

		if ( ci.deviceExtensions and ci.deviceExtensionCount )
			device_extensions.insert( device_extensions.end(), ci.deviceExtensions, ci.deviceExtensions + ci.deviceExtensionCount );

		for (auto& layer : _vulkanSettings.instance.layers) {
			instance_layers.push_back( layer.data() );
		}
		for (auto& ext : _vulkanSettings.instance.extensions) {
			instance_extensions.push_back( ext.data() );
		}
		for (auto& ext : _vulkanSettings.device.extensions) {
			device_extensions.push_back( ext.data() );
		}
		for (uint i = 0; i < ci.queueCount; ++i) {
			queue_ci.push_back({ ci.queueFamilies[i], ci.queuePriorities[i] });
		}


		// create device
		CHECK_ERR( _vulkan.Create( _window->GetVulkanSurface(), "", "VTPlayer", ci.instanceVersion,
								   _vulkanSettings.device.preferredGPUName, queue_ci,
								   instance_layers, instance_extensions, device_extensions ));

		CHECK_ERR( queue_ci.size() == _vulkan.GetVkQuues().size() );
		

		// create debug callback
		if ( EnumEq( _playerSettings.flags, EPlayerFlags::DebugMode ) )
		{
			//_vulkan.CreateDebugReportCallback( DebugReportFlags_All );
			//_vulkan.CreateDebugUtilsCallback( DebugUtilsMessageSeverity_All );
			_vulkan.SetBreakOnValidationError( false );
		}


		// map resource IDs
		_vkResources[VkResourceIndex<VkInstance>][size_t(ci.instanceID)]			= ResourceID(_vulkan.GetVkInstance());
		_vkResources[VkResourceIndex<VkPhysicalDevice>][size_t(ci.physicalDeviceID)]= ResourceID(_vulkan.GetVkPhysicalDevice());
		_vkResources[VkResourceIndex<VkDevice>][size_t(ci.deviceID)]				= ResourceID(_vulkan.GetVkDevice());

		for (size_t i = 0; i < queue_ci.size(); ++i) {
			_vkResources[VkResourceIndex<VkQueue>][size_t(ci.queueIDs[i])] = ResourceID(_vulkan.GetVkQuues()[i].id);
		}

		CHECK_ERR( _CreateAllocator( 64ull << 20 ));

		_lastPresentTime = TimePoint_t::clock::now();
		return true;
	}
	
/*
=================================================
	_CreateCommandPools
----
	creates command pool for each queue family
=================================================
*/
	bool VkPlayer_v100::_CreateCommandPools ()
	{
		CHECK_ERR( _commandPools.empty() );

		uint	count = 0;
		vkGetPhysicalDeviceQueueFamilyProperties( _vulkan.GetVkPhysicalDevice(), OUT &count, null );
		CHECK_ERR( count > 0 );
		
		Array< VkQueueFamilyProperties >	queue_family_props;
		queue_family_props.resize( count );
		vkGetPhysicalDeviceQueueFamilyProperties( _vulkan.GetVkPhysicalDevice(), OUT &count, OUT queue_family_props.data() );

		_commandPools.resize( count );

		for (auto& queue : _vulkan.GetVkQuues())
		{
			if ( _commandPools[queue.familyIndex] )
				continue;

			VkCommandPoolCreateInfo	info = {};
			info.sType				= VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
			info.queueFamilyIndex	= queue.familyIndex;
			info.flags				= VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

			VkCommandPool	pool;
			VK_CHECK( vkCreateCommandPool( _vulkan.GetVkDevice(), &info, null, OUT &pool ));

			_commandPools[queue.familyIndex] = pool;
		}
		return true;
	}
	
/*
=================================================
	_CreateSemaphores
=================================================
*/
	bool VkPlayer_v100::_CreateSemaphores ()
	{
		CHECK_ERR( _semaphorePool.empty() );

		_semaphorePool.resize( _swapchain->GetSwapchainLength() * 10 );

		VkSemaphoreCreateInfo	info = {};
		info.sType	= VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		for (auto& sem : _semaphorePool)
		{
			VK_CHECK( vkCreateSemaphore( _vulkan.GetVkDevice(), &info, null, OUT &sem ));
		}

		return true;
	}
	
/*
=================================================
	_DestroySemaphores
=================================================
*/
	void VkPlayer_v100::_DestroySemaphores ()
	{
		for (auto& sem : _semaphorePool)
		{
			vkDestroySemaphore( _vulkan.GetVkDevice(), sem, null );
		}
		_semaphorePool.clear();
	}

/*
=================================================
	_CreateQueryPools
----
	creates command pool for each queue
=================================================
*/
	bool VkPlayer_v100::_CreateQueryPools ()
	{
		CHECK_ERR( _profiling.queries.empty() );
		
		_profiling.lastUpdateTime = TimePoint_t::clock::now();

		const uint	max_queries = 16;
		const uint	max_frames	= Clamp( _swapchain->GetSwapchainLength(), 2u, uint(FrameQueries_t::capacity()) );

		_profiling.queries.resize( _vulkan.GetVkQuues().size() );

		for (size_t i = 0; i < _vulkan.GetVkQuues().size(); ++i)
		{
			VkQueryPoolCreateInfo	info = {};
			info.sType		= VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO;
			info.queryType	= VK_QUERY_TYPE_TIMESTAMP;
			info.queryCount	= max_queries * max_frames;

			auto&	query = _profiling.queries[i];
			VK_CHECK( vkCreateQueryPool( _vulkan.GetVkDevice(), &info, null, OUT &query.queryPool ));


			auto&	queue = _vulkan.GetVkQuues()[i];
			CHECK_ERR( queue.familyIndex < _commandPools.size() );

			query.queue				= queue.id;
			query.queryCount		= max_queries;
			query.cmdPool			= _commandPools[ queue.familyIndex ];
			query.supportsPresent	= EnumEq( queue.flags, VK_QUEUE_PRESENT_BIT );
			query.perFrame.resize( max_frames );

			for (auto& frame : query.perFrame) {
				frame.waitSemaphores.reserve( 10 );
				frame.signalSemaphores.reserve( 10 );
			}
		}

		CHECK_ERR( _BuildQueryCommandBuffers() );

		return true;
	}
	
/*
=================================================
	_DestroyQueryPools
=================================================
*/
	void VkPlayer_v100::_DestroyQueryPools ()
	{
		for (auto& query : _profiling.queries)
		{
			if ( query.queryPool )
				vkDestroyQueryPool( _vulkan.GetVkDevice(), query.queryPool, null );
		}

		_profiling.queries.clear();
	}

/*
=================================================
	_BuildQueryCommandBuffers
=================================================
*/
	bool VkPlayer_v100::_BuildQueryCommandBuffers ()
	{
		for (auto& query : _profiling.queries)
		{
			uint	query_offset = 0;

			for (auto& frame : query.perFrame)
			{
				// create command buffers
				if ( not (frame.beforeFrame and frame.afterFrame) )
				{
					VkCommandBuffer					cmdbufs[2]	= {};
					VkCommandBufferAllocateInfo		info		= {};

					info.sType				= VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
					info.commandPool		= query.cmdPool;
					info.commandBufferCount	= uint(CountOf( cmdbufs ));
					info.level				= VK_COMMAND_BUFFER_LEVEL_PRIMARY;

					VK_CHECK( vkAllocateCommandBuffers( _vulkan.GetVkDevice(), &info, OUT cmdbufs ));
				
					frame.beforeFrame = cmdbufs[0];
					frame.afterFrame  = cmdbufs[1];
				}

				// bake first command buffer
				{
					VkCommandBufferBeginInfo	begin = {};
					begin.sType	= VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
					begin.flags	= VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

					VK_CALL( vkBeginCommandBuffer( frame.beforeFrame, &begin ));
				
					vkCmdResetQueryPool( frame.beforeFrame, query.queryPool, query_offset, query.queryCount );
					vkCmdWriteTimestamp( frame.beforeFrame, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, query.queryPool, query_offset );

					VK_CALL( vkEndCommandBuffer( frame.beforeFrame ));
				}

				// bake second command buffer
				{
					VkCommandBufferBeginInfo	begin = {};
					begin.sType	= VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
					begin.flags	= VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

					VK_CALL( vkBeginCommandBuffer( frame.afterFrame, &begin ));
				
					vkCmdWriteTimestamp( frame.afterFrame, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, query.queryPool, query_offset+1 );

					VK_CALL( vkEndCommandBuffer( frame.afterFrame ));
				}

				query_offset += query.queryCount;
			}
		}
		return true;
	}
	
/*
=================================================
	_UpdateFrameStatistic
=================================================
*/
	bool VkPlayer_v100::_UpdateFrameStatistic (size_t queueId)
	{
		using namespace std::chrono;

		CHECK_ERR( queueId < _profiling.queries.size() );
		
		static constexpr uint	UpdateIntervalMillis	= 500;
		
		auto&		query		= _profiling.queries[queueId];
		uint		frame_index	= (query.frameIndex + 1) % query.perFrame.size();
		auto&		frame		= query.perFrame[ frame_index ];
		uint		offset		= frame_index * query.queryCount;
		String		str			= _windowSettings.title;

		
		// update FPS
		++_profiling.frameCounter;

		TimePoint_t		now			= TimePoint_t::clock::now();
		int64_t			duration	= duration_cast<milliseconds>(now - _profiling.lastUpdateTime).count();

		if ( duration > UpdateIntervalMillis )
		{
			_profiling.averageFPS		= uint((_profiling.frameCounter * 1000ull + 500) / duration);
			_profiling.averageFTime		= (_profiling.accumFTime + Nonoseconds(_profiling.frameCounter >> 1)) / _profiling.frameCounter;
			_profiling.accumFTime		= {};
			_profiling.frameCounter		= 0;
			_profiling.lastUpdateTime	= now;
		}

		str += " [FPS: ";
		str += ToString( _profiling.averageFPS );


		// update frame time
		if ( frame.counter > 0 )
		{
			//ASSERT( frame.isStarted );

			auto*	results = _perPacketAllocator.Alloc<uint64_t>( frame.counter );

			VK_CALL( vkGetQueryPoolResults( _vulkan.GetVkDevice(), query.queryPool, offset,
										    frame.counter, sizeof(uint64_t) * frame.counter, OUT results,
											sizeof(uint64_t), VK_QUERY_RESULT_64_BIT | VK_QUERY_RESULT_WAIT_BIT ));
			
			_profiling.accumFTime += (Nonoseconds{results[1]} - Nonoseconds{results[0]});
		}


		str += ", FT: ";
		str += ToString( _profiling.averageFTime );

		str += ", ID: ";
		str += ToString( _profiling.frameId );	// you can use frame ID to convert trace into c++ code or visualize graph

		str += "]";
		_window->SetTitle( str );

		++_profiling.frameId;
		return true;
	}
	
/*
=================================================
	_InsertQueryOnAcquireImage
=================================================
*/
	bool VkPlayer_v100::_InsertQueryOnAcquireImage (INOUT VkSemaphore &semaphore)
	{
		if ( _semaphorePool.empty() )
			return true;	// can't acquire new semaphore

		for (auto& query : _profiling.queries)
		{
			if ( not query.supportsPresent )
				continue;

			auto&			frame	= query.perFrame[ query.frameIndex ];
			VkSemaphore		signal	= _semaphorePool.back();	_semaphorePool.pop_back();

			ASSERT( not frame.isStarted );

			frame.counter	 = 0;
			frame.isStarted = true;
			frame.signalSemaphores.push_back( signal );


			// insert before rendering new frame
			PendingQueueSubmit	pending;

			pending.target	= query.queue;
			pending.commandBuffers.push_back( frame.beforeFrame );

			if ( semaphore )
				pending.signalSemaphores.push_back( semaphore );

			pending.waitDstStageMask.push_back( VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT );
			pending.waitSemaphores.push_back( signal );

			_pendingSubmits.push_back( std::move(pending) );

			semaphore = signal;
			return true;
		}

		return false;
	}

/*
=================================================
	_InsertQueryOnPresent
=================================================
*/
	bool VkPlayer_v100::_InsertQueryOnPresent (OUT VkSubmitInfo &submit, size_t queueId)
	{
		CHECK_ERR( queueId < _profiling.queries.size() );

		auto&	query		= _profiling.queries[queueId];
		auto&	frame		= query.perFrame[ query.frameIndex ];
		auto*	stage_mask	= frame.waitSemaphores.empty() ? null : _perPacketAllocator.Alloc<VkPipelineStageFlags>( frame.waitSemaphores.size() );
		auto*	semaphores	= frame.waitSemaphores.empty() ? null : _perPacketAllocator.Alloc<VkSemaphore>( frame.waitSemaphores.size() );

		for (size_t i = 0; i < frame.waitSemaphores.size(); ++i) {
			stage_mask[i] = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			semaphores[i] = frame.waitSemaphores[i];
		}

		ASSERT( not frame.waitSemaphores.empty() );	// must contains at least 1 semaphore
		ASSERT( frame.isStarted );

		// insert after presenting
		submit = {};
		submit.sType				= VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submit.commandBufferCount	= 1;
		submit.pCommandBuffers		= &frame.afterFrame;
		submit.waitSemaphoreCount	= uint(frame.waitSemaphores.size());
		submit.pWaitSemaphores		= semaphores;
		submit.pWaitDstStageMask	= stage_mask;

		// reset
		_semaphorePool.insert( _semaphorePool.end(), frame.waitSemaphores.begin(), frame.waitSemaphores.end() );
		_semaphorePool.insert( _semaphorePool.end(), frame.signalSemaphores.begin(), frame.signalSemaphores.end() );

		frame.waitSemaphores.clear();
		frame.signalSemaphores.clear();

		frame.counter	= FrameQueries::InitialCounter;
		frame.isStarted = false;
		
		query.frameIndex = (query.frameIndex + 1) % query.perFrame.size();
		return true;
	}

/*
=================================================
	_CreateSwapchain
=================================================
*/
	bool VkPlayer_v100::_CreateSwapchain (VulkanCreateInfo &ci)
	{
		if ( _vulkanSettings.swapchain.compositeAlpha < VK_COMPOSITE_ALPHA_FLAG_BITS_MAX_ENUM_KHR )
			ci.swapchainCompositeAlpha = _vulkanSettings.swapchain.compositeAlpha;

		if ( _vulkanSettings.swapchain.presentMode < VK_PRESENT_MODE_MAX_ENUM_KHR )
			ci.swapchainPresentMode = _vulkanSettings.swapchain.presentMode;

		if ( _vulkanSettings.swapchain.transform < VK_SURFACE_TRANSFORM_FLAG_BITS_MAX_ENUM_KHR )
			ci.swapchainPreTransform = _vulkanSettings.swapchain.transform;

		if ( _IsIndirectSwapchainEnabled() )
			return _InitIndirectSwapchain( ci );
		else
			return _InitDirectSwapchain( ci );
	}
	
/*
=================================================
	_InitDirectSwapchain
=================================================
*/
	bool  VkPlayer_v100::_InitDirectSwapchain (const VulkanCreateInfo &ci)
	{
		VkFormat			color_format	= ci.swapchainColorFormat;
		VkColorSpaceKHR		color_space		= ci.swapchainColorSpace;
		const uint2			surface_size	{ ci.swapchainImageWidth, ci.swapchainImageHeight };

		_window->SetSize( surface_size );

		CHECK_ERR( not _swapchain );
		_swapchain.reset( new VulkanSwapchain{ _vulkan });

		CHECK_ERR( _swapchain->ChooseColorFormat( INOUT color_format, INOUT color_space ));

		CHECK_ERR( _swapchain->Create( surface_size, color_format, color_space,
										ci.swapchainMinImageCount, ci.swapchainImageArrayLayers,
										ci.swapchainPreTransform, ci.swapchainPresentMode,
										ci.swapchainCompositeAlpha, ci.swapchainColorImageUsage ));
		
		_swapchainId = size_t(ci.swapchainID);
		_vkResources[VkResourceIndex<VkSwapchainKHR>][_swapchainId] = ResourceID(_swapchain->GetVkSwapchain());

		CHECK_ERR( _swapchain->GetSwapchainLength() == ci.swapchainImageCount );

		for (uint i = 0; i < _swapchain->GetSwapchainLength(); ++i) {
			_vkResources[VkResourceIndex<VkImage>][size_t(ci.swapchainImageIDs[i])] = ResourceID(_swapchain->GetImage(i));
		}
		return true;
	}
	
/*
=================================================
	_InitIndirectSwapchain
=================================================
*/
	bool  VkPlayer_v100::_InitIndirectSwapchain (const VulkanCreateInfo &ci)
	{
		// create swapchain
		{
			VkFormat			color_format	= ci.swapchainColorFormat;
			VkColorSpaceKHR		color_space		= ci.swapchainColorSpace;
			VkImageUsageFlags	image_usage		= ci.swapchainColorImageUsage | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
		
			CHECK_ERR( not _swapchain );
			_swapchain.reset( new VulkanSwapchain{ _vulkan });

			CHECK_ERR( _swapchain->ChooseColorFormat( INOUT color_format, INOUT color_space ));

			CHECK_ERR( _swapchain->Create( _window->GetSize(), color_format, color_space,
											ci.swapchainMinImageCount, ci.swapchainImageArrayLayers,
											ci.swapchainPreTransform, ci.swapchainPresentMode,
											ci.swapchainCompositeAlpha, image_usage ));
		
			_swapchainId = size_t(ci.swapchainID);
			_vkResources[VkResourceIndex<VkSwapchainKHR>][_swapchainId] = ResourceID(_swapchain->GetVkSwapchain());
		}

		// create images
		CHECK_ERR( _indirectSwapchain.images.empty() );
		CHECK_ERR( not _indirectSwapchain.memory );
		_indirectSwapchain.images.resize( ci.swapchainImageCount );
		_indirectSwapchain.dimension = { ci.swapchainImageWidth, ci.swapchainImageHeight };

		VkDeviceSize	total_size		= 0;
		VkDeviceSize	image_size		= 0;
		VkDeviceSize	image_align		= 0;
		uint			mem_type_bits	= 0;

		for (size_t i = 0; i < _indirectSwapchain.images.size(); ++i)
		{
			VkImageCreateInfo	info = {};
			info.sType			= VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
			info.flags			= 0;
			info.imageType		= VK_IMAGE_TYPE_2D;
			info.format			= _swapchain->GetColorFormat();		// TODO: check is supported for optimal tiling
			info.extent			= { ci.swapchainImageWidth, ci.swapchainImageHeight, 1 };
			info.mipLevels		= 1;
			info.arrayLayers	= 1;
			info.samples		= VK_SAMPLE_COUNT_1_BIT;
			info.tiling			= VK_IMAGE_TILING_OPTIMAL;
			info.usage			= ci.swapchainColorImageUsage | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
			info.sharingMode	= VK_SHARING_MODE_EXCLUSIVE;
			info.initialLayout	= VK_IMAGE_LAYOUT_UNDEFINED;
			info.queueFamilyIndexCount	= 0;
			info.pQueueFamilyIndices	= null;

			VkImage		image;
			VK_CHECK( vkCreateImage( _vulkan.GetVkDevice(), &info, null, &image ));
			_indirectSwapchain.images[i].image = image;


			VkMemoryRequirements	mem_req;
			vkGetImageMemoryRequirements( _vulkan.GetVkDevice(), image, OUT &mem_req );

			mem_type_bits |= mem_req.memoryTypeBits;

			if ( i == 0 ) {
				total_size	= image_size = mem_req.size;
				image_align	= mem_req.alignment;
			}
			else {
				CHECK_ERR( image_size == mem_req.size );
				CHECK_ERR( image_align == mem_req.alignment );

				total_size	= AlignToLarger( total_size, image_align ) + image_size;
			}
		}

		// allocate memory
		{
			VkMemoryAllocateInfo	info = {};
			info.sType				= VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			info.pNext				= null;
			info.allocationSize		= total_size;
			info.memoryTypeIndex	= 0;

			CHECK_ERR( _vulkan.GetMemoryTypeIndex( mem_type_bits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, OUT info.memoryTypeIndex ));

			VK_CHECK( vkAllocateMemory( _vulkan.GetVkDevice(), &info, null, OUT &_indirectSwapchain.memory ));
		}

		// bind image memory
		total_size = 0;

		for (size_t i = 0; i < _indirectSwapchain.images.size(); ++i)
		{
			VK_CHECK( vkBindImageMemory( _vulkan.GetVkDevice(), _indirectSwapchain.images[i].image, _indirectSwapchain.memory, total_size ));

			total_size = AlignToLarger( total_size, image_align ) + image_size;
		}

		// create semaphore
		{
			VkSemaphoreCreateInfo	info = {};
			info.sType	= VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

			VK_CHECK( vkCreateSemaphore( _vulkan.GetVkDevice(), &info, null, OUT &_indirectSwapchain.renderFinished ));
		}

		// remap image ids
		for (uint i = 0; i < _indirectSwapchain.images.size(); ++i)
		{
			_indirectSwapchain.images[i].id = size_t(ci.swapchainImageIDs[i]);
			_vkResources[VkResourceIndex<VkImage>][size_t(ci.swapchainImageIDs[i])] = ResourceID(_indirectSwapchain.images[i].image);
		}
		
		return true;
	}
	
/*
=================================================
	_DestroyIndirectSwapchain
=================================================
*/
	void  VkPlayer_v100::_DestroyIndirectSwapchain ()
	{
		if ( _indirectSwapchain.memory ) {
			vkFreeMemory( _vulkan.GetVkDevice(), _indirectSwapchain.memory, null );
			_indirectSwapchain.memory = VK_NULL_HANDLE;
		}

		if ( _indirectSwapchain.renderFinished ) {
			vkDestroySemaphore( _vulkan.GetVkDevice(), _indirectSwapchain.renderFinished, null );
			_indirectSwapchain.renderFinished = VK_NULL_HANDLE;
		}

		for (auto& item : _indirectSwapchain.images) {
			if ( item.image ) vkDestroyImage( _vulkan.GetVkDevice(), item.image, null );
		}
		_indirectSwapchain.images.clear();
	}

/*
=================================================
	_CreateAllocator
----
	memory allocator required for memory remapping and
	if image/buffer capturing enabled
=================================================
*/
	bool  VkPlayer_v100::_CreateAllocator (VkDeviceSize pageSize)
	{
		CHECK_ERR( _memAllocator == null );

		if ( not _IsOriginMemoryModel() )
		{
			_imageAlloc.resize( _vkResources[VkResourceIndex<VkImage>].size() );
			_bufferAlloc.resize( _vkResources[VkResourceIndex<VkBuffer>].size() );
		}

		VmaVulkanFunctions		funcs = {};
		funcs.vkGetPhysicalDeviceProperties			= vkGetPhysicalDeviceProperties;
		funcs.vkGetPhysicalDeviceMemoryProperties	= vkGetPhysicalDeviceMemoryProperties;
        funcs.vkAllocateMemory						= BitCast<PFN_vkAllocateMemory>(vkGetDeviceProcAddr( _vulkan.GetVkDevice(), "vkAllocateMemory" ));
        funcs.vkFreeMemory							= BitCast<PFN_vkFreeMemory>(vkGetDeviceProcAddr( _vulkan.GetVkDevice(), "vkFreeMemory" ));
        funcs.vkMapMemory							= BitCast<PFN_vkMapMemory>(vkGetDeviceProcAddr( _vulkan.GetVkDevice(), "vkMapMemory" ));
        funcs.vkUnmapMemory							= BitCast<PFN_vkUnmapMemory>(vkGetDeviceProcAddr( _vulkan.GetVkDevice(), "vkUnmapMemory" ));
        funcs.vkBindBufferMemory					= BitCast<PFN_vkBindBufferMemory>(vkGetDeviceProcAddr( _vulkan.GetVkDevice(), "vkBindBufferMemory" ));
        funcs.vkBindImageMemory						= BitCast<PFN_vkBindImageMemory>(vkGetDeviceProcAddr( _vulkan.GetVkDevice(), "vkBindImageMemory" ));
        funcs.vkGetBufferMemoryRequirements			= BitCast<PFN_vkGetBufferMemoryRequirements>(vkGetDeviceProcAddr( _vulkan.GetVkDevice(), "vkGetBufferMemoryRequirements" ));
        funcs.vkGetImageMemoryRequirements			= BitCast<PFN_vkGetImageMemoryRequirements>(vkGetDeviceProcAddr( _vulkan.GetVkDevice(), "vkGetImageMemoryRequirements" ));
		funcs.vkCreateBuffer						= null;
		funcs.vkDestroyBuffer						= null;
		funcs.vkCreateImage							= null;
		funcs.vkDestroyImage						= null;
        funcs.vkGetBufferMemoryRequirements2KHR		= BitCast<PFN_vkGetBufferMemoryRequirements2KHR>(vkGetDeviceProcAddr( _vulkan.GetVkDevice(), "vkGetBufferMemoryRequirements2KHR" ));
        funcs.vkGetImageMemoryRequirements2KHR		= BitCast<PFN_vkGetImageMemoryRequirements2KHR>(vkGetDeviceProcAddr( _vulkan.GetVkDevice(), "vkGetImageMemoryRequirements2KHR" ));
        funcs.vkFlushMappedMemoryRanges             = BitCast<PFN_vkFlushMappedMemoryRanges>(vkGetDeviceProcAddr( _vulkan.GetVkDevice(), "vkFlushMappedMemoryRanges" ));
        funcs.vkInvalidateMappedMemoryRanges        = BitCast<PFN_vkInvalidateMappedMemoryRanges>(vkGetDeviceProcAddr( _vulkan.GetVkDevice(), "vkInvalidateMappedMemoryRanges" ));

		VmaAllocatorCreateInfo	info = {};
		info.flags			= VMA_ALLOCATOR_CREATE_EXTERNALLY_SYNCHRONIZED_BIT;
		info.physicalDevice	= _vulkan.GetVkPhysicalDevice();
		info.device			= _vulkan.GetVkDevice();

		info.preferredLargeHeapBlockSize	= pageSize;
		info.pAllocationCallbacks			= null;
		info.pDeviceMemoryCallbacks			= null;
		//info.frameInUseCount	// ignore
		info.pHeapSizeLimit					= null;		// TODO
		info.pVulkanFunctions				= &funcs;

		VK_CHECK( vmaCreateAllocator( &info, OUT &_memAllocator ));
		return true;
	}
	
/*
=================================================
	_ImageCapture
=================================================
*/
	bool VkPlayer_v100::_ImageCapture (VUnpacker &)
	{
		ASSERT(false);
		return false;
	}
	
/*
=================================================
	_BufferCapture
=================================================
*/
	bool VkPlayer_v100::_BufferCapture (VUnpacker &)
	{
		ASSERT(false);
		return false;
	}
	
/*
=================================================
	_Initializeresource
=================================================
*/
	bool VkPlayer_v100::_Initializeresource (VUnpacker &unpacker)
	{
		uint		index	= unpacker.Get<uint>();
		uint64_t	count	= unpacker.Get<uint64_t>();

		CHECK_ERR( index < _vkResources.size() );

		_vkResources[index].resize( size_t(count) );
		return true;
	}
	
/*
=================================================
	_QueueSubmit
=================================================
*/
	bool VkPlayer_v100::_QueueSubmit (VUnpacker &unpacker)
	{
		auto	queue_id	= unpacker.Get< NearUInt<VkQueue> >();
		auto	queue		= VkQueue(_vkResources[VkResourceIndex<VkQueue>][queue_id]);
		auto	submitCount	= unpacker.Get<uint32_t>();
		auto*	pSubmits	= unpacker.Get<const VkSubmitInfo *>(submitCount);
		auto	fence		= unpacker.Get<VkFence>();

		auto&	query		= _profiling.queries[ queue_id ];
		auto&	frame		= query.perFrame[ query.frameIndex ];

		VkSubmitInfo*	submits = _perPacketAllocator.Alloc<VkSubmitInfo>( submitCount + _pendingSubmits.size() );
		size_t			j		= 0;

		for (auto& pending : _pendingSubmits)
		{
			if ( pending.target != queue )
				continue;

			submits[j].sType				= VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submits[j].pNext				= null;
			submits[j].commandBufferCount	= uint(pending.commandBuffers.size());
			submits[j].pCommandBuffers		= pending.commandBuffers.data();
			submits[j].signalSemaphoreCount	= uint(pending.signalSemaphores.size());
			submits[j].pSignalSemaphores	= pending.signalSemaphores.data();
			submits[j].waitSemaphoreCount	= uint(pending.waitSemaphores.size());
			submits[j].pWaitSemaphores		= pending.waitSemaphores.data();
			submits[j].pWaitDstStageMask	= pending.waitDstStageMask.data();
			++j;

			ASSERT( pending.waitDstStageMask.size() == pending.waitSemaphores.size() );
		}

		for (uint i = 0; i < submitCount; ++i, ++j)
		{
			submits[j] = pSubmits[i];

			if ( _semaphorePool.empty() )
				continue;	// can't acquire new semaphore

			// add semaphore
			submits[j].signalSemaphoreCount += 1;
			auto*	signal_semaphores = _perPacketAllocator.Alloc<VkSemaphore>( submits[j].signalSemaphoreCount );

			signal_semaphores[ pSubmits[i].signalSemaphoreCount ] = _semaphorePool.back();

			frame.waitSemaphores.push_back( _semaphorePool.back() );
			_semaphorePool.pop_back();

			memcpy( signal_semaphores, pSubmits[i].pSignalSemaphores, sizeof(VkSemaphore) * pSubmits[i].signalSemaphoreCount );
			submits[j].pSignalSemaphores = signal_semaphores;
		}

		VK_CALL( vkQueueSubmit( queue, uint(j), submits, fence ));


		// remove if submited
		for (auto iter = _pendingSubmits.begin(); iter != _pendingSubmits.end();)
		{
			if ( iter->target == queue )
				iter = _pendingSubmits.erase( iter );
			else
				++iter;
		}
		return true;
	}
	
/*
=================================================
	_OverridePacketProcessor
=================================================
*/
	bool VkPlayer_v100::_OverridePacketProcessor (EVulkanPacketID packetId, VUnpacker &unpacker)
	{
		if ( packetId == EVulkanPacketID::VQueueSubmit and _IsProfilingEnabled() )
		{
			CHECK_ERR( _QueueSubmit( unpacker ));
			return true;
		}

		return false;
	}

}	// VTPlayer
//-----------------------------------------------------------------------------


#ifndef FG_ENABLE_VULKAN_MEMORY_ALLOCATOR
# ifdef COMPILER_GCC
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wmissing-field-initializers"
# endif

# ifdef COMPILER_MSVC
#	pragma warning (push)
#	pragma warning (disable: 4100)
#	pragma warning (disable: 4127)
# endif

# define VMA_IMPLEMENTATION				1
# define VMA_USE_STL_CONTAINERS			1
# define VMA_STATIC_VULKAN_FUNCTIONS	0
# include "external/VulkanMemoryAllocator/src/vk_mem_alloc.h"

# ifdef COMPILER_GCC
#   pragma GCC diagnostic pop
# endif

# ifdef COMPILER_MSVC
#	pragma warning (pop)
# endif
#endif	// FG_ENABLE_VULKAN_MEMORY_ALLOCATOR
