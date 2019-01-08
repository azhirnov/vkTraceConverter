// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#include "stl/Algorithms/StringUtils.h"
#include "stl/Algorithms/EnumUtils.h"
#include "engine/Application.h"
#include "framework/Window/WindowGLFW.h"
#include "framework/Window/WindowSDL2.h"


namespace VTC
{

/*
=================================================
	constructor
=================================================
*/
	VApp::VApp ()
	{
#	 if defined(FG_ENABLE_GLFW)
		_window.reset( new WindowGLFW() );

#	 elif defined(FG_ENABLE_SDL2)
		_window.reset( new WindowSDL2() );
		
#	 elif defined(FG_ENABLE_SFML)
		_window.reset( new WindowSFML() );

#	 else
#		error unknown window library!
#	 endif

		VulkanDeviceFn_Init( _vulkan );
	}
	
/*
=================================================
	destructor
=================================================
*/
	VApp::~VApp ()
	{
		if ( _vulkan.GetVkDevice() )
			VK_CALL( vkDeviceWaitIdle( _vulkan.GetVkDevice() ));

		#if VTC_MEMORY_REMAPPING
		if ( _memAllocator ) {
			vmaDestroyAllocator( _memAllocator );
		}
		#endif

		if ( _swapchain ) {
			_swapchain->Destroy();
			_swapchain.reset();
		}

		_vulkan.Destroy();

		if ( _window ) {
			_window->Destroy();
			_window.reset();
		}
	}
	
/*
=================================================
	OnResize
=================================================
*/
	void VApp::OnResize (const uint2 &size)
	{
		ASSERT(false);

		_swapchain->Recreate( size );
	}
	
/*
=================================================
	OnRefrash
=================================================
*/
	void VApp::OnRefrash ()
	{
	}
	
/*
=================================================
	OnDestroy
=================================================
*/
	void VApp::OnDestroy ()
	{
	}
	
/*
=================================================
	OnUpdate
=================================================
*/
	void VApp::OnUpdate ()
	{
	}

/*
=================================================
	CreateWindow
=================================================
*/
	bool VApp::CreateWindow (uint width, uint height, StringView title)
	{
		CHECK_ERR( _window );

		CHECK_ERR( _window->Create( uint2{width, height}, title ));
		_window->AddListener( this );

		_windowTitle	= title;
		_surfaceSize	= uint2{width, height};
		return true;
	}
	
/*
=================================================
	CreateDevice
=================================================
*/
	bool VApp::CreateDevice (InstanceID				instance,
							 PhysicalDeviceID		physicalDevice,
							 DeviceID				logicalDevice,
							 StringView				gpuDeviceName,
							 uint					apiVersion,
							 ArrayView<QueueInfo>	queues,
							 ArrayView<const char*>	instanceLayers,
							 ArrayView<const char*>	instanceExtensions,
							 ArrayView<const char*>	deviceExtensions)
	{
		FixedArray< VulkanDevice::QueueCreateInfo, 16 >		queue_ci;
		for (auto& q : queues) {
			queue_ci.push_back({ q.flags, q.priority });
		}

		CHECK_ERR( _vulkan.Create( _window->GetVulkanSurface(), "", apiVersion, gpuDeviceName, queue_ci,
								   instanceLayers, instanceExtensions, deviceExtensions ));

		CHECK_ERR( queues.size() == _vulkan.GetVkQuues().size() );

		_vulkan.CreateDebugCallback( VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT | VK_DEBUG_REPORT_ERROR_BIT_EXT );


		// map resource IDs
		EditResource( instance )		= _vulkan.GetVkInstance();
		EditResource( physicalDevice )	= _vulkan.GetVkPhysicalDevice();
		EditResource( logicalDevice )	= _vulkan.GetVkDevice();

		for (size_t i = 0; i < queues.size(); ++i) {
			EditResource(queues[i].id) = _vulkan.GetVkQuues()[i].id;
		}

		#if VTC_MEMORY_REMAPPING
		CHECK_ERR( _CreateAllocator( 64ull << 20 ));
		#endif

		return true;
	}

/*
=================================================
	CreateSwapchain
=================================================
*/
	bool VApp::CreateSwapchain (SwapchainKHRID						swapchain,
								ArrayView<ImageID>					swapchainImages,
								VkFormat							colorFormat,
								VkColorSpaceKHR						colorSpace,
								const uint							minImageCount,
								const uint							imageArrayLayers,
								const VkSurfaceTransformFlagBitsKHR	transform,
								const VkPresentModeKHR				presentMode,
								const VkCompositeAlphaFlagBitsKHR	compositeAlpha,
								const VkImageUsageFlags				colorImageUsage)
	{
		CHECK_ERR( not _swapchain );
		
		_swapchain.reset( new VulkanSwapchain{ _vulkan });

		CHECK_ERR( _swapchain->ChooseColorFormat( INOUT colorFormat, INOUT colorSpace ));

		CHECK_ERR( _swapchain->Create( _surfaceSize, colorFormat, colorSpace, minImageCount, imageArrayLayers,
									   transform, presentMode, compositeAlpha, colorImageUsage ));
		
		
		uint	count = 0;
		VK_CHECK( vkGetSwapchainImagesKHR( _vulkan.GetVkDevice(), _swapchain->GetVkSwapchain(), OUT &count, null ));
		CHECK_ERR( count > 0 );
		
		FixedArray< VkImage, FG_MaxSwapchainLength >	images;
		images.resize( count );
		VK_CHECK( vkGetSwapchainImagesKHR( _vulkan.GetVkDevice(), _swapchain->GetVkSwapchain(), OUT &count, OUT images.data() ));

		CHECK_ERR( count == swapchainImages.size() );

		for (size_t i = 0; i < images.size(); ++i)
		{
			EditResource( swapchainImages[i] ) = images[i];
		}

		EditResource( swapchain ) = _swapchain->GetVkSwapchain();
		return true;
	}
	
/*
=================================================
	Run
=================================================
*/
	bool VApp::Run (const FrameID firstFrameId, ArrayView<VDrawFrame_t> frames)
	{
		CHECK_ERR( _window and _swapchain and _vulkan.GetVkDevice() );

		for (size_t i = 0; i < frames.size(); ++i)
		{
			if ( not _window->Update() )
				return true;

			_window->SetTitle( _windowTitle + "[FPS: "s + ToString(uint(_swapchain->GetFramesPerSecond())) + "]"s );

			_PrepareData( FrameID(size_t(firstFrameId) + i) );

			frames[i]( *this );
		}

		return true;
	}
	
/*
=================================================
	LoadData
=================================================
*/
	ArrayView<uint8_t>  VApp::LoadData (DataID id) const
	{
		auto	data = _loadableData.find( id );
		CHECK_ERR( data != _loadableData.end() );

		return data->second;
	}
	
/*
=================================================
	AcquireImage
=================================================
*/
	bool VApp::AcquireImage (ImageID image, SemaphoreID imageAvailableSemaphore) const
	{
		CHECK_ERR( _swapchain );
		VK_CHECK( _swapchain->AcquireNextImage( GetResource(imageAvailableSemaphore) ));		// TODO: handle errors

		ASSERT( GetResource(image) == _swapchain->GetCurrentImage() );
		return true;
	}
	
/*
=================================================
	Present
=================================================
*/
	bool VApp::Present (QueueID queue, ImageID image, SemaphoreID renderFinishedSemaphore) const
	{
		CHECK_ERR( _swapchain );
		ASSERT( GetResource(image) == _swapchain->GetCurrentImage() );
		
		CHECK_ERR( _swapchain->Present( GetResource(queue), GetResource(renderFinishedSemaphore) ));
		return true;
	}
	
/*
=================================================
	CalcFirstFrame
=================================================
*/
	ND_ static FrameID  CalcFirstFrame (FrameID frameId, uint64_t dataSize)
	{
		return FrameID( uint64_t(frameId) - Max( uint64_t(frameId), (dataSize >> 24) ));
	}

/*
=================================================
	AddExternalData
=================================================
*/
	bool VApp::AddExternalData (const String &filename, ArrayView<FilePart> parts)
	{
		auto	file_iter = _files.find( filename );

		// open file
		if ( file_iter == _files.end() )
		{
			RStreamPtr	file{ new FileRStream{ filename }};

			file_iter = _files.insert({ filename, file }).first;
		}

		// add load & unload events
		for (auto& part : parts)
		{
			// add 'load' event
			FrameID	first_frame = CalcFirstFrame( part.firstFrame, part.size );

			auto	load_ev = _loadEvents.find( first_frame );

			if ( load_ev == _loadEvents.end() ) {
				load_ev = _loadEvents.insert({ first_frame, {} }).first;
			}
			load_ev->second.push_back(FilePartExt{ part, file_iter->second });

			// add 'unload' event
			auto	unload_ev = _unloadEvents.find( part.lastFrame );

			if ( unload_ev == _unloadEvents.end() ) {
				unload_ev = _unloadEvents.insert({ part.lastFrame, {} }).first;
			}

			unload_ev->second.push_back( part.id );
		}

		return true;
	}
	
/*
=================================================
	PreloadAllData
=================================================
*/
	bool  VApp::PreloadAllData ()
	{
		for (auto& load_ev : _loadEvents)
		{
			for (auto& part : load_ev.second)
			{
				CHECK_ERR( _LoadDataPart( part ));
			}
		}

		_loadEvents.clear();
		_unloadEvents.clear();
		return true;
	}
	
/*
=================================================
	_LoadDataPart
=================================================
*/
	bool  VApp::_LoadDataPart (FilePartExt &part)
	{
		CHECK_ERR( part.size < ~size_t(0) );

		auto	iter = _loadableData.insert({ part.id, {} });
		ASSERT( iter.second );	// all IDs must be unique

		auto&	buffer = iter.first->second;

		buffer.resize( size_t(part.size) );		// TODO: check for bad alloc exception

		CHECK_ERR( part.file->SeekSet( BytesU(part.offset) ));
		CHECK_ERR( part.file->Read( buffer.data(), BytesU(buffer.size()) ));

		return true;
	}

/*
=================================================
	_PrepareData
=================================================
*/
	bool  VApp::_PrepareData (FrameID frameId)
	{
		// load required data
		auto	load_ev = _loadEvents.find( frameId );

		if ( load_ev != _loadEvents.end() )
		{
			for (auto& part : load_ev->second) {
				CHECK_ERR( _LoadDataPart( part ));
			}
		}

		// unload data
		auto	unload_ev = _unloadEvents.find( frameId );

		if ( unload_ev != _unloadEvents.end() )
		{
			for (auto& id : unload_ev->second) {
				_loadableData.erase( id );
			}
		}

		return true;
	}
//-----------------------------------------------------------------------------
	


#if VTC_MEMORY_REMAPPING
/*
=================================================
	_CreateAllocator
=================================================
*/
	bool  VApp::_CreateAllocator (VkDeviceSize pageSize)
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
	AllocateBufferMemory
=================================================
*/
	bool  VApp::AllocateBufferMemory (BufferID id, VmaAllocationCreateFlags flags, VmaMemoryUsage usage, VkMemoryPropertyFlags propertyFlags) const
	{
		CHECK_ERR( size_t(id) < _bufferAlloc.size() );

		auto&	mem = _bufferAlloc[size_t(id)];
		CHECK_ERR( mem.alloc == null );

		VmaAllocationCreateInfo		info = {};
		info.flags			= flags;
		info.usage			= usage;
		info.requiredFlags	= 0;
		info.preferredFlags	= propertyFlags;
		info.memoryTypeBits	= 0;
		info.pool			= VK_NULL_HANDLE;
		info.pUserData		= null;

		VK_CHECK( vmaAllocateMemoryForBuffer( _memAllocator, GetResource(id), &info, OUT &mem.alloc, null ));
		VK_CHECK( vmaBindBufferMemory( _memAllocator, mem.alloc, GetResource(id) ));
		
		VmaAllocationInfo	alloc_info = {};
		vmaGetAllocationInfo( _memAllocator, mem.alloc, OUT &alloc_info );

		mem.mappedPtr	= alloc_info.pMappedData;
		mem.size		= alloc_info.size;

		return true;
	}
	
/*
=================================================
	AllocateImageMemory
=================================================
*/
	bool  VApp::AllocateImageMemory (ImageID id, VmaAllocationCreateFlags flags, VmaMemoryUsage usage, VkMemoryPropertyFlags propertyFlags) const
	{
		CHECK_ERR( size_t(id) < _imageAlloc.size() );

		auto&	mem = _imageAlloc[size_t(id)];
		CHECK_ERR( mem.alloc == null );

		VmaAllocationCreateInfo		info = {};
		info.flags			= flags;
		info.usage			= usage;
		info.requiredFlags	= 0;
		info.preferredFlags	= propertyFlags;
		info.memoryTypeBits	= 0;
		info.pool			= VK_NULL_HANDLE;
		info.pUserData		= null;

		VK_CHECK( vmaAllocateMemoryForImage( _memAllocator, GetResource(id), &info, OUT &mem.alloc, null ));
		VK_CHECK( vmaBindImageMemory( _memAllocator, mem.alloc, GetResource(id) ));
		
		VmaAllocationInfo	alloc_info = {};
		vmaGetAllocationInfo( _memAllocator, mem.alloc, OUT &alloc_info );

		mem.mappedPtr	= alloc_info.pMappedData;
		mem.size		= alloc_info.size;

		return true;
	}
	
/*
=================================================
	FreeBufferMemory
=================================================
*/
	bool  VApp::FreeBufferMemory (BufferID id) const
	{
		CHECK_ERR( size_t(id) < _bufferAlloc.size() );

		auto&	mem = _bufferAlloc[size_t(id)];
		CHECK_ERR( mem.alloc );

		vmaFreeMemory( _memAllocator, mem.alloc );

		mem = {};
		return true;
	}
	
/*
=================================================
	FreeImageMemory
=================================================
*/
	bool  VApp::FreeImageMemory (ImageID id) const
	{
		CHECK_ERR( size_t(id) < _imageAlloc.size() );

		auto&	mem = _imageAlloc[size_t(id)];
		CHECK_ERR( mem.alloc );

		vmaFreeMemory( _memAllocator, mem.alloc );

		mem = {};
		return true;
	}
	
/*
=================================================
	LoadDataToBuffer
=================================================
*/
	bool  VApp::LoadDataToBuffer (BufferID bufferId, DataID dataId, VkDeviceSize offset, VkDeviceSize size) const
	{
		CHECK_ERR( size_t(bufferId) < _bufferAlloc.size() );

		auto&	mem = _bufferAlloc[size_t(bufferId)];
		CHECK_ERR( mem.mappedPtr );
		
		auto	data = _loadableData.find( dataId );
		CHECK_ERR( data != _loadableData.end() );
		CHECK_ERR( data->second.size() == size );

		CHECK_ERR( (offset + size) <= mem.size );

		memcpy( mem.mappedPtr + BytesU(offset), data->second.data(), size );
		return true;
	}
	
/*
=================================================
	LoadDataToImage
=================================================
*/
	bool  VApp::LoadDataToImage (ImageID imageId, DataID dataId, VkDeviceSize offset, VkDeviceSize size) const
	{
		CHECK_ERR( size_t(imageId) < _imageAlloc.size() );

		auto&	mem = _imageAlloc[size_t(imageId)];
		CHECK_ERR( mem.mappedPtr );
		
		auto	data = _loadableData.find( dataId );
		CHECK_ERR( data != _loadableData.end() );
		CHECK_ERR( data->second.size() == size );

		CHECK_ERR( (offset + size) <= mem.size );

		memcpy( mem.mappedPtr + BytesU(offset), data->second.data(), size );
		return true;
	}

#endif	// VTC_MEMORY_REMAPPING
//-----------------------------------------------------------------------------


	
#if not VTC_MEMORY_REMAPPING
/*
=================================================
	OnMapMemory
=================================================
*/
	bool VApp::OnMapMemory (DeviceMemoryID memId, void *ptr, VkDeviceSize offset, VkDeviceSize size) const
	{
		auto&	mem = _mappedMemory.insert({ memId, {} }).first->second;
		CHECK( mem.mappedPtr == null );

		mem = { ptr, offset, size };
		return true;
	}
	
/*
=================================================
	OnUnmapMemory
=================================================
*/
	bool VApp::OnUnmapMemory (DeviceMemoryID memId) const
	{
		auto	mem = _mappedMemory.find( memId );
		CHECK_ERR( mem != _mappedMemory.end() );
		CHECK( mem->second.mappedPtr != null );

		mem->second = {};
		return true;
	}
	
/*
=================================================
	LoadDataToMappedMemory
=================================================
*/
	bool VApp::LoadDataToMappedMemory (DeviceMemoryID memId, DataID dataId, VkDeviceSize offset, VkDeviceSize size) const
	{
		auto	mem = _mappedMemory.find( memId );
		CHECK_ERR( mem != _mappedMemory.end() );
		CHECK_ERR( mem->second.mappedPtr != null );
		
		auto	data = _loadableData.find( dataId );
		CHECK_ERR( data != _loadableData.end() );
		CHECK_ERR( data->second.size() == size );

		CHECK_ERR( (offset + size) <= mem->second.size );

		memcpy( mem->second.mappedPtr + BytesU(offset), data->second.data(), size );
		return true;
	}

#endif	// not VTC_MEMORY_REMAPPING


}	// VTC


#if VTC_MEMORY_REMAPPING

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

#endif	// VTC_MEMORY_REMAPPING
