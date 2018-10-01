// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "VkPlayer.h"
#include "stl/Algorithms/StringUtils.h"
#include "stl/Algorithms/EnumUtils.h"
#include <thread>
#include <variant>
#include "VUnpacker.h"

namespace VTPlayer
{
#	include "IDs/EVulkanPacketIDs.h"
#	include "Types/VulkanCreateInfo.h"

/*
=================================================
	constructor
=================================================
*/
	VkPlayer_v100::VkPlayer_v100 (const VulkanSettings &vulkanSettings, const WindowSettings &windowSettings,
								  const SharedPtr<RFile> &traceFile, const SharedPtr<RFile> &dataFile) :
		_trace{ traceFile },				_dataFile{ dataFile },
		_currFrameId{ 0 },					_sourceFPS{ 0 },
		_isPaused{ false },					_isFinished{ false },
		_vulkanSettings{ vulkanSettings },	_windowSettings{ windowSettings }
	{
		VulkanDeviceFn_Init( _vulkan );

		_resRemappingBuf.reserve( 4u << 10 );
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
	Draw
=================================================
*/
	bool VkPlayer_v100::Draw ()
	{
		if ( _isFinished )
			return false;

		if ( not _window->Update() or _isPaused )
		{
			std::this_thread::sleep_for( std::chrono::milliseconds(10) );
			return true;
		}

		CHECK_ERR( _PrepareData( _currFrameId ));

		if ( not _ProcessFrame() )
			return false;

		return true;
	}
	
/*
=================================================
	OnResize
=================================================
*/
	void VkPlayer_v100::OnResize (const uint2 &)
	{
		// TODO
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
	_Destroy
=================================================
*/
	void VkPlayer_v100::_Destroy ()
	{
		if ( _vulkan.GetVkDevice() )
			VK_CALL( vkDeviceWaitIdle( _vulkan.GetVkDevice() ));

		if ( _memAllocator ) {
			vmaDestroyAllocator( _memAllocator );
		}

		if ( _swapchain ) {
			_swapchain->Destroy();
			_swapchain.reset();
		}

		_vulkan.Destroy();

		if ( _window )
			_window->RemoveListener( this );

		_window = null;
	}

/*
=================================================
	_ProcessFrame
=================================================
*/
	bool VkPlayer_v100::_ProcessFrame ()
	{
		if ( not _trace.ReadNext() )
			return false;

		_resRemappingBuf.clear();

		VUnpacker	unpacker{ _trace.GetPacketData(), _trace.GetPacketSize(), _trace.GetPacketOffset(), _vkResources, _resRemappingBuf };

		ENABLE_ENUM_CHECKS();
		switch ( EVulkanPacketID(_trace.GetPacketID()) )
		{
			case EVulkanPacketID::End :									_isFinished = true;										break;
			case EVulkanPacketID::SetSourceFPS :						CHECK( _SetSourceFPS( unpacker ));						break;
			case EVulkanPacketID::SetData :								CHECK( _SetData( unpacker ));							break;
			case EVulkanPacketID::VMapMemory :							CHECK( _MapMemory( unpacker ));							break;
			case EVulkanPacketID::VUnmapMemory :						CHECK( _UnmapMemory( unpacker ));						break;
			case EVulkanPacketID::VLoadDataToMappedMemory :				CHECK( _LoadDataToMappedMemory( unpacker ));			break;
			case EVulkanPacketID::VCreateShaderModule :					CHECK( _CreateShaderModule( unpacker ));				break;
			case EVulkanPacketID::VCreatePipelineCache :				CHECK( _CreatePipelineCache( unpacker ));				break;
			case EVulkanPacketID::VCmdUpdateBuffer :					CHECK( _CmdUpdateBuffer( unpacker ));					break;
			case EVulkanPacketID::VAcquireNextImageKHR :				CHECK( _AcquireNextImage( unpacker ));					break;
			case EVulkanPacketID::VQueuePresentKHR :					CHECK( _QueuePresent( unpacker ));						break;
			case EVulkanPacketID::VAllocateBufferMemory :				CHECK( _AllocateBufferMemory( unpacker ));				break;
			case EVulkanPacketID::VAllocateImageMemory :				CHECK( _AllocateImageMemory( unpacker ));				break;
			case EVulkanPacketID::VFreeBufferMemory :					CHECK( _FreeBufferMemory( unpacker ));					break;
			case EVulkanPacketID::VFreeImageMemory :					CHECK( _FreeImageMemory( unpacker ));					break;
			case EVulkanPacketID::VLoadDataToBuffer :					CHECK( _LoadDataToBuffer( unpacker ));					break;
			case EVulkanPacketID::VLoadDataToImage :					CHECK( _LoadDataToImage( unpacker ));					break;
			case EVulkanPacketID::VCmdPushDescriptorSetWithTemplate :	CHECK( _CmdPushDescriptorSetWithTemplate( unpacker ));	break;
			case EVulkanPacketID::VUpdateDescriptorSetWithTemplate :	CHECK( _UpdateDescriptorSetWithTemplate( unpacker ));	break;
			case EVulkanPacketID::VCreateDevice :						CHECK( _CreateDevice( unpacker ));						break;
			case EVulkanPacketID::VImageCapture :						CHECK( _ImageCapture( unpacker ));						break;
			case EVulkanPacketID::VBufferCapture :						CHECK( _BufferCapture( unpacker ));						break;
			case EVulkanPacketID::VInitializeResource :					CHECK( _Initializeresource( unpacker ));				break;

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
	VkPlayer_v100::DataBuffer_t  VkPlayer_v100::_LoadData (DataID id) const
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
	_SetSourceFPS
=================================================
*/
	bool VkPlayer_v100::_SetSourceFPS (VUnpacker &unpacker)
	{
		_sourceFPS = unpacker.Get<uint>();
		return true;
	}

/*
=================================================
	CalcFirstFrame
=================================================
*/
	ND_ static VkPlayer_v100::FrameID  CalcFirstFrame (VkPlayer_v100::FrameID frameId, uint64_t dataSize)
	{
		return VkPlayer_v100::FrameID( uint64_t(frameId) - Max( uint64_t(frameId), (dataSize >> 24) ));
	}
	
/*
=================================================
	_SetSourceFPS
=================================================
*/
	bool VkPlayer_v100::_SetData (VUnpacker &unpacker)
	{
		FilePart	part;
		part.id << unpacker;
		part.offset << unpacker;
		part.size << unpacker;
		part.firstFrame << unpacker;
		part.lastFrame << unpacker;
		
		FrameID		first_frame = CalcFirstFrame( part.firstFrame, part.size );
		FrameID		last_frame	= part.lastFrame + 1;

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

		VK_CALL( _swapchain->AcquireNextImage( semaphore ));

		_vkResources[VkResourceIndex<VkImage>][image_id] = ResourceID(_swapchain->GetCurrentImage());
		return true;
	}
	
/*
=================================================
	_QueuePresent
=================================================
*/
	bool VkPlayer_v100::_QueuePresent (VUnpacker &unpacker)
	{
		auto	queue				= unpacker.Get<VkQueue>();
		auto	image				= unpacker.Get<VkImage>();
		auto	semaphores_count	= unpacker.Get<uint>();
		auto*	wait_semaphores		= unpacker.Get<VkSemaphore const*>();

		ASSERT( image == _swapchain->GetCurrentImage() );

		CHECK( _swapchain->Present( queue, {wait_semaphores, semaphores_count} ));

		++_currFrameId;
		_window->SetTitle( _windowSettings.title + "[FPS: "s + ToString(uint(_swapchain->GetFramesPerSecond())) + "]"s );

		return true;
	}
	
/*
=================================================
	_AllocateBufferMemory
=================================================
*/
	bool VkPlayer_v100::_AllocateBufferMemory (VUnpacker &unpacker)
	{
		auto	device			= unpacker.Get<VkDevice>();
		auto	buffer_id		= unpacker.Get< NearUInt<VkBuffer> >();
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

		mem.mappedPtr	= alloc_info.pMappedData;
		mem.size		= alloc_info.size;
		mem.memId		= alloc_info.deviceMemory;
		mem.isCoherent	= !!(_vulkan.GetDeviceMemoryProperties().memoryTypes[alloc_info.memoryType].propertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		return true;
	}
	
/*
=================================================
	_AllocateImageMemory
=================================================
*/
	bool VkPlayer_v100::_AllocateImageMemory (VUnpacker &unpacker)
	{
		auto	device			= unpacker.Get<VkDevice>();
		auto	image_id		= unpacker.Get< NearUInt<VkImage> >();
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

		mem.mappedPtr	= alloc_info.pMappedData;
		mem.size		= alloc_info.size;
		mem.memId		= alloc_info.deviceMemory;
		mem.isCoherent	= !!(_vulkan.GetDeviceMemoryProperties().memoryTypes[alloc_info.memoryType].propertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		return true;
	}
	
/*
=================================================
	_FreeBufferMemory
=================================================
*/
	bool VkPlayer_v100::_FreeBufferMemory (VUnpacker &unpacker)
	{
		auto	device		= unpacker.Get<VkDevice>();
		auto	buffer_id	= unpacker.Get< NearUInt<VkBuffer> >();
		
		CHECK_ERR( buffer_id < _bufferAlloc.size() );

		auto&	mem = _bufferAlloc[buffer_id];
		CHECK_ERR( mem.alloc );

		vmaFreeMemory( _memAllocator, mem.alloc );

		mem = {};
		return true;
	}
	
/*
=================================================
	_FreeImageMemory
=================================================
*/
	bool VkPlayer_v100::_FreeImageMemory (VUnpacker &unpacker)
	{
		auto	device		= unpacker.Get<VkDevice>();
		auto	image_id	= unpacker.Get< NearUInt<VkImage> >();
		
		CHECK_ERR( image_id < _imageAlloc.size() );

		auto&	mem = _imageAlloc[image_id];
		CHECK_ERR( mem.alloc );

		vmaFreeMemory( _memAllocator, mem.alloc );

		mem = {};
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

		CHECK_ERR( (offset + size) <= mem.size );

		memcpy( mem.mappedPtr + BytesU(offset), data->second.data(), size );

		if ( not mem.isCoherent )
		{
			VkMappedMemoryRange	range = {};
			range.sType		= VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
			range.memory	= mem.memId;
			range.offset	= offset;
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
		auto	device		= unpacker.Get<VkDevice>();
		auto	buffer_id	= unpacker.Get< NearUInt<VkBuffer> >();
		auto	data_id		= unpacker.Get<DataID>();
		auto	offset		= unpacker.Get<VkDeviceSize>();
		auto	size		= unpacker.Get<VkDeviceSize>();
		
		CHECK_ERR( buffer_id < _bufferAlloc.size() );

		auto&	mem = _bufferAlloc[buffer_id];
		CHECK_ERR( mem.mappedPtr );
	
		return _LoadDataToVMAMemory( device, mem, data_id, offset, size );
	}
	
/*
=================================================
	_LoadDataToImage
=================================================
*/
	bool VkPlayer_v100::_LoadDataToImage (VUnpacker &unpacker)
	{
		auto	device		= unpacker.Get<VkDevice>();
		auto	image_id	= unpacker.Get< NearUInt<VkImage> >();
		auto	data_id		= unpacker.Get<DataID>();
		auto	offset		= unpacker.Get<VkDeviceSize>();
		auto	size		= unpacker.Get<VkDeviceSize>();
		
		CHECK_ERR( image_id < _imageAlloc.size() );

		auto&	mem = _imageAlloc[image_id];
		CHECK_ERR( mem.mappedPtr );
	
		return _LoadDataToVMAMemory( device, mem, data_id, offset, size );
	}
	
/*
=================================================
	_CmdPushDescriptorSetWithTemplate
=================================================
*/
	bool VkPlayer_v100::_CmdPushDescriptorSetWithTemplate (VUnpacker &)
	{
		ASSERT(false);
		return false;
	}
	
/*
=================================================
	_UpdateDescriptorSetWithTemplate
=================================================
*/
	bool VkPlayer_v100::_UpdateDescriptorSetWithTemplate (VUnpacker &)
	{
		ASSERT(false);
		return false;
	}
	
/*
=================================================
	_CreateDevice
=================================================
*/
	bool VkPlayer_v100::_CreateDevice (VUnpacker &unpacker)
	{
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
		ci.swapchainID				= VkSwapchainKHR( unpacker.Get< NearUInt<VkSwapchainKHR> >());
		ci.swapchainType			<< unpacker;
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
		ci.swapchainImageCount		<< unpacker;
		ci.swapchainImageIDs		= BitCast<VkImage *>( unpacker.Get< NearUInt<VkImage> *>( ci.swapchainImageCount ));

		CHECK_ERR( _CreateDevice( ci ));
		CHECK_ERR( _CreateSwapchain( ci ));
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
		Array<const char*>						instance_layers			{ VulkanDevice::GetRecomendedInstanceLayers() };
		Array<const char*>						instance_extensions		{ VulkanDevice::GetRecomendedInstanceExtensions() };
		Array<const char*>						device_extensions		{ VulkanDevice::GetRecomendedDeviceExtensions() };
		Array<VulkanDevice::QueueCreateInfo>	queue_ci;

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

		CHECK_ERR( _vulkan.Create( _window->GetVulkanSurface(), "", "VTPlayer", ci.instanceVersion,
								   _vulkanSettings.device.preferredGPUName, queue_ci,
								   instance_layers, instance_extensions, device_extensions ));

		CHECK_ERR( queue_ci.size() == _vulkan.GetVkQuues().size() );

		_vulkan.CreateDebugCallback( VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT | VK_DEBUG_REPORT_ERROR_BIT_EXT );
		

		// map resource IDs
		_vkResources[VkResourceIndex<VkInstance>][size_t(ci.instanceID)]			= ResourceID(_vulkan.GetVkInstance());
		_vkResources[VkResourceIndex<VkPhysicalDevice>][size_t(ci.physicalDeviceID)]= ResourceID(_vulkan.GetVkPhysicalDevice());
		_vkResources[VkResourceIndex<VkDevice>][size_t(ci.deviceID)]				= ResourceID(_vulkan.GetVkDevice());

		for (size_t i = 0; i < queue_ci.size(); ++i) {
			_vkResources[VkResourceIndex<VkQueue>][size_t(ci.queueIDs[i])] = ResourceID(_vulkan.GetVkQuues()[i].id);
		}

		CHECK_ERR( _CreateAllocator( 64ull << 20 ));
		return true;
	}
	
/*
=================================================
	_CreateSwapchain
=================================================
*/
	bool VkPlayer_v100::_CreateSwapchain (const VulkanCreateInfo &ci)
	{
		CHECK_ERR( not _swapchain );
		_swapchain.reset( new VulkanSwapchain{ _vulkan });

		VkFormat		color_format	= ci.swapchainColorFormat;
		VkColorSpaceKHR	color_space		= ci.swapchainColorSpace;

		CHECK_ERR( _swapchain->ChooseColorFormat( INOUT color_format, INOUT color_space ));

		CHECK_ERR( _swapchain->Create( _window->GetSize(), color_format, color_space,
										ci.swapchainMinImageCount, ci.swapchainImageArrayLayers,
										ci.swapchainPreTransform, ci.swapchainPresentMode,
										ci.swapchainCompositeAlpha, ci.swapchainColorImageUsage ));
		
		
		uint	count = 0;
		VK_CHECK( vkGetSwapchainImagesKHR( _vulkan.GetVkDevice(), _swapchain->GetVkSwapchain(), OUT &count, null ));
		CHECK_ERR( count > 0 );
		
		Array<VkImage>	images;		images.resize( count );
		VK_CHECK( vkGetSwapchainImagesKHR( _vulkan.GetVkDevice(), _swapchain->GetVkSwapchain(), OUT &count, OUT images.data() ));

		CHECK_ERR( count == ci.swapchainImageCount );

		for (size_t i = 0; i < images.size(); ++i) {
			_vkResources[VkResourceIndex<VkImage>][size_t(ci.swapchainImageIDs[i])] = ResourceID(images[i]);
		}
		
		_vkResources[VkResourceIndex<VkSwapchainKHR>][size_t(ci.swapchainID)] = ResourceID(_swapchain->GetVkSwapchain());
		return true;
	}

/*
=================================================
	_CreateAllocator
=================================================
*/
	bool  VkPlayer_v100::_CreateAllocator (VkDeviceSize pageSize)
	{
		CHECK_ERR( _memAllocator == null );

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
		
		if ( index == VkResourceIndex<VkImage> )	_imageAlloc.resize( size_t(count) );
		if ( index == VkResourceIndex<VkBuffer> )	_bufferAlloc.resize( size_t(count) );

		return true;
	}

}	// VTPlayer
//-----------------------------------------------------------------------------


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
