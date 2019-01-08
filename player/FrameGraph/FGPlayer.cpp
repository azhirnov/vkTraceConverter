// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#include "FGPlayer.h"
#include "FGUnpacker.h"
#include "extensions/pipeline_compiler/VPipelineCompiler.h"
#include "stl/Algorithms/StringUtils.h"
#include "extensions/graphviz/GraphViz.h"
#include <thread>

namespace VTPlayer
{
#	include "Types/VulkanCreateInfo.h"

/*
=================================================
	constructor
=================================================
*/
	FGPlayer_v100::FGPlayer_v100 (const VulkanSettings &vulkanSettings, const WindowSettings &windowSettings, const PlayerSettings &playerSettings,
								  const SharedPtr<RStream> &traceFile, const SharedPtr<RStream> &dataFile) :
		_trace{ traceFile },				_dataFile{ dataFile },
		_vulkanSettings{ vulkanSettings },	_windowSettings{ windowSettings },
		_playerSettings{ playerSettings }
	{
		_perPacketAllocator.SetBlockSize( 4_Mb );
	}
	
/*
=================================================
	destructor
=================================================
*/
	FGPlayer_v100::~FGPlayer_v100 ()
	{
		_Destroy();
	}
	
/*
=================================================
	Play
=================================================
*/
	bool FGPlayer_v100::Play ()
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
	bool FGPlayer_v100::Pause ()
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
	bool FGPlayer_v100::Init (IWindow *wnd)
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
	void FGPlayer_v100::OnResize (const uint2 &size)
	{
		VulkanSwapchainCreateInfo	swapchain_info;
		swapchain_info.surface		= BitCast<SurfaceVk_t>( _vulkan.GetVkSurface() );
        swapchain_info.surfaceSize  = size;

		for (auto& fg : _frameGraphThreads)
		{
			if ( not EnumEq( fg.thread->GetThreadUsage(), EThreadUsage::Present ) )
				continue;

			CHECK_FATAL( fg.thread->RecreateSwapchain( swapchain_info ));
		}
	}
	
/*
=================================================
	OnDestroy
=================================================
*/
	void FGPlayer_v100::OnDestroy ()
	{
		_Destroy();
	}
	
/*
=================================================
	OnKey
=================================================
*/
	void FGPlayer_v100::OnKey (StringView key, EKeyAction action)
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

		if ( key == "V" )
			_visualizeGraph = 1;

		if ( key == "escape" )
			_isFinished = true;
	}

/*
=================================================
	_Destroy
=================================================
*/
	void FGPlayer_v100::_Destroy ()
	{
		_isFinished = true;
		
		for (auto& fg : _frameGraphThreads)
		{
			if ( not fg.thread )
				continue;

			if ( &fg == _frameGraphThreads.data() )
			{
				for (auto& id : _resources.gpipelines) {
					fg.thread->ReleaseResource( id );
				}
				for (auto& id : _resources.cpipelines) {
					fg.thread->ReleaseResource( id );
				}
				for (auto& id : _resources.mpipelines) {
					fg.thread->ReleaseResource( id );
				}
				for (auto& id : _resources.rtpipelines) {
					fg.thread->ReleaseResource( id );
				}
				for (auto& id : _resources.samplers) {
					fg.thread->ReleaseResource( id );
				}
				for (auto& id : _resources.images) {
					fg.thread->ReleaseResource( id );
				}
				for (auto& id : _resources.buffers) {
					fg.thread->ReleaseResource( id );
				}
				for (auto& mod : _resources.shaders) {
					_vulkan.vkDestroyShaderModule( _vulkan.GetVkDevice(), Cast<ShaderModule>( mod )->_module, null );
				}
		
				_resources = Default;
			}

			fg.thread->Deinitialize();
			fg = Default;
		}

		if ( _fgInstance )
		{
			_fgInstance->Deinitialize();
			_fgInstance = null;
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
	bool FGPlayer_v100::Draw ()
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
	bool FGPlayer_v100::_RunCommand ()
	{
		_perPacketAllocator.Discard();

		if ( not _trace.ReadNext() ) {
			_isFinished = true;
			return false;
		}

		FGUnpacker	unpacker{ _trace.GetPacketData(), _trace.GetPacketSize(), _trace.GetPacketOffset() };

		return _RunCommand2( EFrameGraphPacketID(_trace.GetPacketID()), unpacker );
	}
	
/*
=================================================
	_RunCommand2
=================================================
*/
	bool FGPlayer_v100::_RunCommand2 (EFrameGraphPacketID packetId, FGUnpacker &unpacker)
	{
		ENABLE_ENUM_CHECKS();
		switch ( packetId )
		{
			case EFrameGraphPacketID::End :									_isFinished = true;								break;
			case EFrameGraphPacketID::SetData :								CHECK( _SetData( unpacker ));					break;

			case EFrameGraphPacketID::CreateVkDevice :						CHECK( _CreateDevice( unpacker ));				break;

			case EFrameGraphPacketID::FgCreateGraphicsPipeline :			CHECK( _CreateGraphicsPipeline( unpacker ));	break;
			case EFrameGraphPacketID::FgCreateComputePipeline :				CHECK( _CreateComputePipeline( unpacker ));		break;
			case EFrameGraphPacketID::FgCreateMeshPipeline :				CHECK( _CreateMeshPipeline( unpacker ));		break;
			case EFrameGraphPacketID::FgCreateRayTracingPipeline :			CHECK( _CreateRayTracingPipeline( unpacker ));	break;
			case EFrameGraphPacketID::FgCreateSampler :						CHECK( _CreateSampler( unpacker ));				break;
			case EFrameGraphPacketID::FgCreateImage :						CHECK( _CreateImage( unpacker ));				break;
			case EFrameGraphPacketID::FgCreateBuffer :						CHECK( _CreateBuffer( unpacker ));				break;
			case EFrameGraphPacketID::FgCreateShaderModule :				CHECK( _CreateShaderModule( unpacker ));		break;
			case EFrameGraphPacketID::FgDestroyGraphicsPipeline :			CHECK( _DestroyGraphicsPipeline( unpacker ));	break;
			case EFrameGraphPacketID::FgDestroyComputePipeline :			CHECK( _DestroyComputePipeline( unpacker ));	break;
			case EFrameGraphPacketID::FgDestroyMeshPipeline :				CHECK( _DestroyMeshPipeline( unpacker ));		break;
			case EFrameGraphPacketID::FgDestroyRayTracingPipeline :			CHECK( _DestroyRayTracingPipeline( unpacker ));	break;
			case EFrameGraphPacketID::FgDestroySampler :					CHECK( _DestroySampler( unpacker ));			break;
			case EFrameGraphPacketID::FgDestroyImage :						CHECK( _DestroyImage( unpacker ));				break;
			case EFrameGraphPacketID::FgDestroyBuffer :						CHECK( _DestroyBuffer( unpacker ));				break;
			case EFrameGraphPacketID::FgCreateRenderPass :					CHECK( _CreateRenderPass( unpacker ));			break;
			case EFrameGraphPacketID::FgCreateThread :						CHECK( _CreateFrameGraphThread( unpacker ));	break;
				
			case EFrameGraphPacketID::FgSubmitRenderPass :					CHECK( _SubmitRenderPass( unpacker ));			break;
			case EFrameGraphPacketID::FgDispatchCompute :					CHECK( _DispatchCompute( unpacker ));			break;
			case EFrameGraphPacketID::FgDispatchComputeIndirect :			CHECK( _DispatchComputeIndirect( unpacker ));	break;
			case EFrameGraphPacketID::FgCopyBuffer :						CHECK( _CopyBuffer( unpacker ));				break;
			case EFrameGraphPacketID::FgCopyImage :							CHECK( _CopyImage( unpacker ));					break;
			case EFrameGraphPacketID::FgCopyBufferToImage :					CHECK( _CopyBufferToImage( unpacker ));			break;
			case EFrameGraphPacketID::FgCopyImageToBuffer :					CHECK( _CopyImageToBuffer( unpacker ));			break;
			case EFrameGraphPacketID::FgBlitImage :							CHECK( _BlitImage( unpacker ));					break;
			case EFrameGraphPacketID::FgResolveImage :						CHECK( _ResolveImage( unpacker ));				break;
			case EFrameGraphPacketID::FgFillBuffer :						CHECK( _FillBuffer( unpacker ));				break;
			case EFrameGraphPacketID::FgClearColorImage :					CHECK( _ClearColorImage( unpacker ));			break;
			case EFrameGraphPacketID::FgClearDepthStencilImage :			CHECK( _ClearDepthStencilImage( unpacker ));	break;
			case EFrameGraphPacketID::FgUpdateBuffer :						CHECK( _UpdateBuffer( unpacker ));				break;
			case EFrameGraphPacketID::FgReadBuffer :						CHECK( _ReadBuffer( unpacker ));				break;
			case EFrameGraphPacketID::FgUpdateImage :						CHECK( _UpdateImage( unpacker ));				break;
			case EFrameGraphPacketID::FgReadImage :							CHECK( _ReadImage( unpacker ));					break;
			case EFrameGraphPacketID::FgPresent :							CHECK( _Present( unpacker ));					break;
			case EFrameGraphPacketID::FgPresentVR :							CHECK( _PresentVR( unpacker ));					break;
			case EFrameGraphPacketID::FgBeginFrame :						CHECK( _BeginFrame( unpacker ));				break;
			case EFrameGraphPacketID::FgEndFrame :							CHECK( _EndFrame( unpacker ));					break;
			case EFrameGraphPacketID::FgBeginThread :						CHECK( _BeginThread( unpacker ));				break;
			case EFrameGraphPacketID::FgEndThread :							CHECK( _EndThread( unpacker ));					break;
			case EFrameGraphPacketID::FgUpdateHostBuffer :					CHECK( _UpdateHostBuffer( unpacker ));			break;

			case EFrameGraphPacketID::FgDrawVertices :						CHECK( _DrawVertices( unpacker ));				break;
			case EFrameGraphPacketID::FgDrawIndexed :						CHECK( _DrawIndexed( unpacker ));				break;
			case EFrameGraphPacketID::FgDrawMeshes :						CHECK( _DrawMeshes( unpacker ));				break;
			case EFrameGraphPacketID::FgDrawVerticesIndirect :				CHECK( _DrawVerticesIndirect( unpacker ));		break;
			case EFrameGraphPacketID::FgDrawIndexedIndirect :				CHECK( _DrawIndexedIndirect( unpacker ));		break;
			case EFrameGraphPacketID::FgDrawMeshesIndirect :				CHECK( _DrawMeshesIndirect( unpacker ));		break;
			case EFrameGraphPacketID::FgClearAttachments :					CHECK( _ClearAttachments( unpacker ));			break;

			case EFrameGraphPacketID::FgSetGraphicsPipelineCount :
			case EFrameGraphPacketID::FgSetComputePipelineCount :
			case EFrameGraphPacketID::FgSetMeshPipelineCount :
			case EFrameGraphPacketID::FgSetRayTracingPipelineCount :
			case EFrameGraphPacketID::FgSetSamplerCount :
			case EFrameGraphPacketID::FgSetImageCount :
			case EFrameGraphPacketID::FgSetBufferCount :
			case EFrameGraphPacketID::FgSetShaderModuleCount :
			case EFrameGraphPacketID::FgSetLogicalPassCount :
			case EFrameGraphPacketID::FgSetThreadCount :					CHECK( _InitializeResource( packetId, unpacker ));	break;

			case EFrameGraphPacketID::_FrameGraphApi :
			case EFrameGraphPacketID::_V100 :
			case EFrameGraphPacketID::_CustomBit :
			case EFrameGraphPacketID::FgBuildRayTracingGeometry :
			case EFrameGraphPacketID::FgBuildRayTracingScene :
			case EFrameGraphPacketID::FgTraceRays :
			default :
				RETURN_ERR( "unsupported instruction" );
		}
		DISABLE_ENUM_CHECKS();

		return true;
	}
	
/*
=================================================
	_InitializeResource
=================================================
*/
	bool FGPlayer_v100::_InitializeResource (EFrameGraphPacketID packetId, FGUnpacker &unpacker)
	{
		CHECK_ERR( _currFrameId == 0 );

		uint	count = 0;
		count << unpacker;

		switch ( packetId )
		{
			case EFrameGraphPacketID::FgSetThreadCount :
				_frameGraphThreads.resize( count );
				break;

			case EFrameGraphPacketID::FgSetGraphicsPipelineCount :
				_resources.gpipelines.resize( count );
				break;

			case EFrameGraphPacketID::FgSetComputePipelineCount :
				_resources.cpipelines.resize( count );
				break;

			case EFrameGraphPacketID::FgSetMeshPipelineCount :
				_resources.mpipelines.resize( count );
				break;

			case EFrameGraphPacketID::FgSetRayTracingPipelineCount :
				_resources.rtpipelines.resize( count );
				break;

			case EFrameGraphPacketID::FgSetSamplerCount :
				_resources.samplers.resize( count );
				break;

			case EFrameGraphPacketID::FgSetImageCount :
				_resources.images.resize( count );
				break;

			case EFrameGraphPacketID::FgSetBufferCount :
				_resources.buffers.resize( count );
				break;
				
			case EFrameGraphPacketID::FgSetShaderModuleCount :
				_resources.shaders.resize( count );
				break;

			case EFrameGraphPacketID::FgSetLogicalPassCount :
				_resources.logicalPasses.resize( count );
				break;

			default :
				RETURN_ERR( "unknown resource type!" );
		}
		return true;
	}
	
/*
=================================================
	_CreateDevice
=================================================
*/
	bool FGPlayer_v100::_CreateDevice (FGUnpacker &unpacker)
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
		CHECK_ERR( _CreateFrameGraph() );

		++_currFrameId;
		return true;
	}
	
/*
=================================================
	_CreateDevice
=================================================
*/
	bool FGPlayer_v100::_CreateDevice (const VulkanCreateInfo &ci)
	{
		// initialize
		Array<const char*>						instance_layers;
		Array<const char*>						instance_extensions;
		Array<const char*>						device_extensions;
		Array<VulkanDevice::QueueCreateInfo>	queue_ci;

		instance_extensions.assign( VulkanDevice::GetRecomendedInstanceExtensions().begin(), VulkanDevice::GetRecomendedInstanceExtensions().end() );
		device_extensions.assign( VulkanDevice::GetRecomendedDeviceExtensions().begin(), VulkanDevice::GetRecomendedDeviceExtensions().end() );

		if ( EnumEq( _playerSettings.flags, EPlayerFlags::DebugMode ) )
			instance_layers.assign( VulkanDevice::GetRecomendedInstanceLayers().begin(), VulkanDevice::GetRecomendedInstanceLayers().end() );

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
		CHECK_ERR( _vulkan.Create( _window->GetVulkanSurface(), "", "VTPlayer", VK_API_VERSION_1_1,
								   _vulkanSettings.device.preferredGPUName, queue_ci,
								   instance_layers, instance_extensions, device_extensions ));

		CHECK_ERR( queue_ci.size() == _vulkan.GetVkQuues().size() );
		

		// create debug callback
		if ( EnumEq( _playerSettings.flags, EPlayerFlags::DebugMode ) )
		{
			//_vulkan.CreateDebugReportCallback( DebugReportFlags_All );
			_vulkan.CreateDebugUtilsCallback( DebugUtilsMessageSeverity_All );
			_vulkan.SetBreakOnValidationError( false );
		}

		_lastPresentTime = TimePoint_t::clock::now();
		return true;
	}
	
/*
=================================================
	_CreateFrameGraph
=================================================
*/
	bool FGPlayer_v100::_CreateFrameGraph ()
	{
		// setup device info
		VulkanDeviceInfo	vulkan_info;
		{
			vulkan_info.instance		= BitCast<InstanceVk_t>( _vulkan.GetVkInstance() );
			vulkan_info.physicalDevice	= BitCast<PhysicalDeviceVk_t>( _vulkan.GetVkPhysicalDevice() );
			vulkan_info.device			= BitCast<DeviceVk_t>( _vulkan.GetVkDevice() );

			for (auto& q : _vulkan.GetVkQuues())
			{
				VulkanDeviceInfo::QueueInfo	qi;
				qi.id			= BitCast<QueueVk_t>( q.id );
				qi.familyFlags	= BitCast<QueueFlagsVk_t>( q.flags );
				qi.familyIndex	= q.familyIndex;
				qi.priority		= q.priority;
				qi.debugName	= "";

				vulkan_info.queues.push_back( qi );
			}
		}

		// initialize framegraph
		{
			_fgInstance = FrameGraphInstance::CreateFrameGraph( vulkan_info );
			CHECK_ERR( _fgInstance );
			CHECK_ERR( _fgInstance->Initialize( 2 ));
			//_fgInstance->SetCompilationFlags( ECompilationFlags::EnableDebugger, ECompilationDebugFlags::Default );
		}

		// add glsl pipeline compiler
		{
			auto	ppln_compiler = MakeShared<VPipelineCompiler>( vulkan_info.physicalDevice, vulkan_info.device );

			ppln_compiler->SetCompilationFlags( EShaderCompilationFlags::AlwaysWriteDiscard | EShaderCompilationFlags::AlwaysBufferDynamicOffset );

			_fgInstance->AddPipelineCompiler( ppln_compiler );
		}
		return true;
	}

/*
=================================================
	_LoadDataPart
=================================================
*/
	bool FGPlayer_v100::_LoadDataPart (FilePart &part)
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
	bool FGPlayer_v100::_PrepareData (FrameID frameId)
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
	_LoadData
=================================================
*/
	ArrayView<uint8_t>  FGPlayer_v100::_LoadData (DataID id) const
	{
		auto	data = _loadableData.find( id );
		CHECK_ERR( data != _loadableData.end() );

		return data->second;
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
	_SetData
=================================================
*/
	bool FGPlayer_v100::_SetData (FGUnpacker &unpacker)
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
	_BeginFrame
----
	see packer in 'FrameGraphConverter::_OnBeginFrame'
=================================================
*/
	bool FGPlayer_v100::_BeginFrame (FGUnpacker &unpacker)
	{
		SubmissionGraph		submission_graph;
		const auto			count	= unpacker.Get<uint>();

		for (uint i = 0; i < count; ++i)
		{
			CommandBatchID	batch_id;		batch_id << unpacker;
			const auto		thread_count	= unpacker.Get<uint>();

			submission_graph.AddBatch( batch_id, thread_count );
		}

		if ( _visualizeGraph == 1 )
		{
			_visualizeGraph = 2;
			_fgInstance->SetCompilationFlags( ECompilationFlags::EnableDebugger, ECompilationDebugFlags::Default );

			for (auto& fg : _frameGraphThreads) {
				fg.thread->SetCompilationFlags( ECompilationFlags::EnableDebugger, ECompilationDebugFlags::Default );
			}
		}

		CHECK( _fgInstance->BeginFrame( submission_graph ));
		return true;
	}
	
/*
=================================================
	_EndFrame
----
	see packer in 'FrameGraphConverter::_OnEndFrame'
=================================================
*/
	bool FGPlayer_v100::_EndFrame (FGUnpacker &unpacker)
	{
		auto	frame_time	= Nonoseconds{unpacker.Get<uint64_t>()};

		CHECK( _fgInstance->EndFrame() );

		for (auto& pass : _resources.logicalPasses) {
			pass = LogicalPassID{};
		}

		for (auto& fg : _frameGraphThreads) {
			ASSERT( fg.task == null );
		}

		++_currFrameId;

		_UpdateFrameStatistic();
		
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

		if ( _visualizeGraph == 2 )
		{
#		if defined(FG_GRAPHVIZ_DOT_EXECUTABLE) and defined(FG_STD_FILESYSTEM)
			GraphViz::Visualize( _fgInstance, "FrameGraph_" + ToString(++_graphCounter) + ".dot" );
#		endif
			
			for (auto& fg : _frameGraphThreads) {
				fg.thread->SetCompilationFlags( ECompilationFlags::Unknown );
			}
			_fgInstance->SetCompilationFlags( ECompilationFlags::Unknown );
			_visualizeGraph = 0;
		}
		return true;
	}
	
/*
=================================================
	_BeginThread
----
	see packer in 'FrameGraphConverter::_OnBeginFrame'
=================================================
*/
	bool FGPlayer_v100::_BeginThread (FGUnpacker &unpacker)
	{
		const auto		index		= unpacker.Get<uint>();
		CommandBatchID	batch_id;	batch_id << unpacker;
		const auto		subbatch	= unpacker.Get<uint>();
		const auto		usage		= unpacker.Get<EThreadUsage>();

		CHECK( _frameGraphThreads[index].thread->Begin( batch_id, subbatch, usage ));
		return true;
	}
	
/*
=================================================
	_EndThread
----
	see packer in 'FrameGraphConverter::_OnEndFrame'
=================================================
*/
	bool FGPlayer_v100::_EndThread (FGUnpacker &unpacker)
	{
		const auto	index	= unpacker.Get<uint>();
		auto&		fg		= _frameGraphThreads[index];

		fg.task = null;

		CHECK( fg.thread->Execute() );
		return true;
	}
	
/*
=================================================
	_UpdateFrameStatistic
=================================================
*/
	bool FGPlayer_v100::_UpdateFrameStatistic ()
	{
		using namespace std::chrono;
		
		static constexpr uint	UpdateIntervalMillis	= 500;

		String		str = _windowSettings.title;

		// update FPS
		++_profiling.frameCounter;
		
		FrameGraphInstance::Statistics	stat;
		_fgInstance->GetStatistics( OUT stat );
		_profiling.accumFTime += stat.renderer.frameTime;

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
		
		str += ", FT: ";
		str += ToString( _profiling.averageFTime );

		str += ", ID: ";
		str += ToString( _profiling.frameId );	// you can use frame ID to convert trace into c++ code or visualize graph

		str += "]";
		_window->SetTitle( str );

		++_profiling.frameId;
		return true;
	}


}	// VTPlayer
