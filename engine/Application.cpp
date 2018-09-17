// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "stl/include/StringUtils.h"
#include "engine/Application.h"
#include "framework/Window/WindowGLFW.h"
#include "framework/Window/WindowSDL2.h"

#ifdef PLATFORM_WINDOWS
#	define Ftell	_ftelli64
#	define Fseek	_fseeki64
#endif


namespace VTC
{

/*
=================================================
	constructor
=================================================
*/
	VApp::VApp ()
	{
#	if defined(FG_ENABLE_GLFW)
		_window.reset( new WindowGLFW() );

#	elif defined(FG_ENABLE_SDL2)
		_window.reset( new WindowSDL2() );

#	else
#		error unknown window library!
#	endif

		VulkanDeviceFn_Init( _vulkan );
	}
	
/*
=================================================
	destructor
=================================================
*/
	VApp::~VApp ()
	{
		for (auto& file : _files)
		{
			fclose( file.second );
		}

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

		CHECK_ERR( _window->Create( uint2{width, height}, title, this ));

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
		return true;
	}

/*
=================================================
	CreateSwapchain
=================================================
*/
	bool VApp::CreateSwapchain (SwapchainKHRID						swapchain,
								ArrayView<ImageID>					swapchainImages,
								SemaphoreID							, //imageAvailableSemaphore,
								SemaphoreID							, //renderFinishedSemaphore,
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

		//CHECK_ERR( imageAvailableSemaphore != renderFinishedSemaphore );
		//EditResource( imageAvailableSemaphore )	= _swapchain->GetImageAvailableSemaphore();
		//EditResource( renderFinishedSemaphore ) = _swapchain->GetRenderFinishedSemaphore();

		return true;
	}
	
/*
=================================================
	Run
=================================================
*/
	bool VApp::Run (ArrayView<VDrawFrame_t> frames)
	{
		CHECK_ERR( _window and _swapchain and _vulkan.GetVkDevice() );

		for (size_t i = 0; i < frames.size(); ++i)
		{
			if ( not _window->Update() )
				return true;

			_window->SetTitle( _windowTitle + "[FPS: "s + ToString(uint(_swapchain->GetFramesPerSecond())) + "]"s );

			_PrepareData( FrameID(i) );

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
	OnMapMemory
=================================================
*/
	bool VApp::OnMapMemory (DeviceMemoryID memId, void *ptr, VkDeviceSize offset, VkDeviceSize size) const
	{
		CHECK_ERR( size_t(memId) < _mappedMemory.size() );
		ASSERT( _mappedMemory[size_t(memId)].mappedPtr == null );

		_mappedMemory[size_t(memId)] = { ptr, offset, size };
		return true;
	}
	
/*
=================================================
	OnUnmapMemory
=================================================
*/
	bool VApp::OnUnmapMemory (DeviceMemoryID memId) const
	{
		CHECK_ERR( size_t(memId) < _mappedMemory.size() );
		ASSERT( _mappedMemory[size_t(memId)].mappedPtr != null );

		_mappedMemory[size_t(memId)] = {};
		return true;
	}
	
/*
=================================================
	GetMappedMemory
=================================================
*
	bool VApp::GetMappedMemory (DeviceMemoryID memId, OUT void* &ptr, OUT VkDeviceSize &size) const
	{
		CHECK_ERR( size_t(memId) < _mappedMemory.size() );
		CHECK_ERR( _mappedMemory[size_t(memId)].mappedPtr != null );

		const auto&	mem = _mappedMemory[size_t(memId)];

		ptr		= mem.mappedPtr;
		size	= mem.size;
		return true;
	}
	
/*
=================================================
	LoadDataToMappedMemory
=================================================
*/
	bool VApp::LoadDataToMappedMemory (DeviceMemoryID memId, DataID dataId, VkDeviceSize offset, VkDeviceSize size) const
	{
		CHECK_ERR( size_t(memId) < _mappedMemory.size() );
		CHECK_ERR( _mappedMemory[size_t(memId)].mappedPtr != null );
		
		auto	data = _loadableData.find( dataId );
		CHECK_ERR( data != _loadableData.end() );
		CHECK_ERR( data->second.size() == size );

		const auto&	mem = _mappedMemory[size_t(memId)];
		CHECK_ERR( (offset + size) <= mem.size );

		memcpy( mem.mappedPtr + BytesU(offset), data->second.data(), size );
		return true;
	}

/*
=================================================
	AcquireImage
=================================================
*/
	bool VApp::AcquireImage (ImageID image, SemaphoreID imageAvailableSemaphore) const
	{
		CHECK_ERR( _swapchain );
		//CHECK_ERR( GetResource(imageAvailableSemaphore) == _swapchain->GetImageAvailableSemaphore() );
		
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
		//CHECK_ERR( GetResource(renderFinishedSemaphore) == _swapchain->GetRenderFinishedSemaphore() );
		ASSERT( GetResource(image) == _swapchain->GetCurrentImage() );
		
		CHECK_ERR( _swapchain->Present( GetResource(queue), GetResource(renderFinishedSemaphore) ));
		return true;
	}
	
/*
=================================================
	GetMemoryTypeIndex
=================================================
*/
	uint  VApp::GetMemoryTypeIndex (uint memoryTypeBits, VkMemoryPropertyFlags flags) const
	{
		uint	index;
		CHECK( _vulkan.GetMemoryTypeIndex( memoryTypeBits, flags, OUT index ));		// TODO: emulate required memory type?
		return index;
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
			FILE*	file = null;
			CHECK_ERR( fopen_s( OUT &file, filename.c_str(), "rb" ) == 0 );

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

			// add 'unload' event
			load_ev->second.push_back(FilePartExt{ part, file_iter->second });

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

		CHECK_ERR( Fseek( part.file, part.offset, SEEK_SET ) == 0 );
		CHECK_ERR( fread( buffer.data(), sizeof(buffer[0]), buffer.size(), part.file ) == buffer.size() );

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


}	// VTC

