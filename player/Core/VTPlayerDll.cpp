// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#include "Public/VTPlayer.h"
#include "IPlayerInstance.h"
#include "PlayerInstance_vLatest.h"

#undef  FG_DLL_EXPORT
#define FG_DLL_EXPORT

namespace VTPlayer
{

/*
=================================================
	ConvertPlayerSettings
=================================================
*/
	static PlayerSettings  ConvertPlayerSettings (const VTPlayerSettings *settings)
	{
		if ( not settings )
			return {};

		PlayerSettings	result;
		result.version			= settings->playerVersion;
		result.traceFilename	= settings->playerTraceFile;
		result.dataFilename		= settings->playerDataFile;

		if ( settings->playerBenchmarkMode )
			result.flags |= EPlayerFlags::EnableCpuBenchmark | EPlayerFlags::EnableGpuBenchmark;

		if ( settings->playerDebugMode )
			result.flags |= EPlayerFlags::DebugMode;

		if ( settings->playerTestMode )
			result.flags |= EPlayerFlags::TestMode;

		return result;
	}
	
/*
=================================================
	ConvertWindowSettings
=================================================
*/
	static WindowSettings  ConvertWindowSettings (const VTPlayerSettings *settings)
	{
		if ( not settings )
			return {};

		WindowSettings	result;
		result.position	= { settings->windowPositionX, settings->windowPositionY };
		result.size		= { uint(settings->windowWidth), uint(settings->windowHeight) };
		result.title	= settings->windowTitle;

		if ( settings->windowFPSinTitle )
			result.flags |= EWindowFlags::ShowFPS;

		if ( settings->windowFullscreen )
			result.flags |= EWindowFlags::Fullscreen;

		if ( settings->windowResizable )
			result.flags |= EWindowFlags::Resizable;

		return result;
	}
	
/*
=================================================
	ConvertVulkanSettings
=================================================
*/
	static VulkanSettings  ConvertVulkanSettings (const VTPlayerSettings *settings)
	{
		if ( not settings )
			return {};

		VulkanSettings	result;
		result.instance.version = settings->instanceVkApiVersion;

		for (uint i = 0; i < settings->instanceVkLayerCount; ++i) {
			result.instance.layers.push_back( settings->instanceVkLayers[i] );
		}
		for (uint i = 0; i < settings->instanceVkExtensionCount; ++i) {
			result.instance.extensions.push_back( settings->instanceVkExtensions[i] );
		}

		if ( settings->preferredGPUName )
			result.device.preferredGPUName = settings->preferredGPUName;

		for (uint i = 0; i < settings->deviceVkExtensionCount; ++i) {
			result.device.extensions.push_back( settings->deviceVkExtensions[i] );
		}

		result.swapchain.colorFormat	= BitCast<VkFormat>( settings->swapchainVkColorFormat );
		result.swapchain.colorSpace		= BitCast<VkColorSpaceKHR>( settings->swapchainVkColorSpace );
		result.swapchain.minImageCount	= settings->swapchainVkMinImageCount;
		//result.swapchain.imageArrayLayers
		result.swapchain.transform		= BitCast<VkSurfaceTransformFlagBitsKHR>( settings->swapchainVkPreTransform );
		result.swapchain.presentMode	= BitCast<VkPresentModeKHR>( settings->swapchainVkPresentMode );
		result.swapchain.compositeAlpha	= BitCast<VkCompositeAlphaFlagBitsKHR>( settings->swapchainVkCompositeAlpha );
		//result.swapchain.colorImageUsage
		return result;
	}

/*
=================================================
	CreateLatestPlayerVersion
=================================================
*/
	static bool CreateLatestPlayerVersion (const VTPlayerSettings *settings, OUT VTPlayerInstance *outInstance)
	{
		*outInstance = BitCast<VTPlayerInstance>( static_cast<IPlayerInstance *>(
			new PlayerInstance_vLatest{ ConvertPlayerSettings(settings), ConvertWindowSettings(settings), ConvertVulkanSettings(settings) }
		));

		return true;
	}

/*
=================================================
	CreatePlayer
=================================================
*/
	extern "C" FG_DLL_EXPORT int VTPLAYER_CALL  CreatePlayer (const struct VTPlayerSettings *settings, OUT VTPlayerInstance *outInstance)
	{
		if ( settings )
		{
			CHECK_ERR( sizeof(*settings) == settings->structSize );

			switch ( settings->playerVersion )
			{
				case VTPLAYER_VERSION_LATEST :
					return CreateLatestPlayerVersion( settings, OUT outInstance );

				default :
					FG_LOGE( "unsupported player version" );
					return CreateLatestPlayerVersion( settings, OUT outInstance );
			}
		}
		
		// create default
		return CreateLatestPlayerVersion( null, OUT outInstance );
	}
	
/*
=================================================
	DestroyPlayer
=================================================
*/
	extern "C" FG_DLL_EXPORT void VTPLAYER_CALL  DestroyPlayer (VTPlayerInstance instance)
	{
		CHECK_ERR( instance, void() );

		BitCast<IPlayerInstance *>( instance )->Release();
	}
	
/*
=================================================
	PlayerStart
=================================================
*/
	extern "C" FG_DLL_EXPORT int VTPLAYER_CALL  PlayerStart (VTPlayerInstance instance)
	{
		CHECK_ERR( instance );

		CHECK_ERR( BitCast<IPlayerInstance *>( instance )->Play() );
		return true;
	}
	
/*
=================================================
	PlayerIsActive
=================================================
*/
	extern "C" FG_DLL_EXPORT int VTPLAYER_CALL  PlayerIsActive (VTPlayerInstance instance)
	{
		CHECK_ERR( instance );

		return BitCast<IPlayerInstance *>( instance )->IsRunning();
	}

/*
=================================================
	PlayerPause
=================================================
*/
	extern "C" FG_DLL_EXPORT int VTPLAYER_CALL  PlayerPause (VTPlayerInstance instance)
	{
		CHECK_ERR( instance );

		CHECK_ERR( BitCast<IPlayerInstance *>( instance )->Pause() );
		return true;
	}
	
/*
=================================================
	SetPlayerVulkanEventListener
=================================================
*/
	extern "C" FG_DLL_EXPORT int VTPLAYER_CALL  SetPlayerVulkanEventListener (VTPlayerInstance instance, const struct VulkanEventListener *listener)
	{
		CHECK_ERR( instance and listener );

		// TODO
		return true;
	}
	
/*
=================================================
	SetFileReader
=================================================
*/
	extern "C" FG_DLL_EXPORT int VTPLAYER_CALL  SetFileReader (VTPlayerInstance instance, const struct FileReader *fileReader)
	{
		CHECK_ERR( instance );
		CHECK_ERR( not BitCast<IPlayerInstance *>( instance )->IsInitialized() );

		// TODO
		return true;
	}
	
/*
=================================================
	AddPipelineCache
=================================================
*/
	extern "C" FG_DLL_EXPORT int VTPLAYER_CALL  AddPipelineCache (VTPlayerInstance instance, const void* data, size_t dataSize)
	{
		CHECK_ERR( instance );
		CHECK_ERR( data and dataSize );
		
		CHECK_ERR( BitCast<IPlayerInstance *>( instance )->LoadVkPipelineCache( data, dataSize ));
		return true;
	}
	
/*
=================================================
	GetPipelineCache
=================================================
*/
	extern "C" FG_DLL_EXPORT int VTPLAYER_CALL  GetPipelineCache (VTPlayerInstance instance, OUT void const** data, OUT size_t *dataSize)
	{
		CHECK_ERR( instance );
		CHECK_ERR( data and dataSize );
		CHECK_ERR( BitCast<IPlayerInstance *>( instance )->IsInitialized() );
		
		CHECK_ERR( BitCast<IPlayerInstance *>( instance )->GetVkPipelineCache( OUT *data, OUT *dataSize ));
		return true;
	}

/*
=================================================
	validation
=================================================
*/
	STATIC_ASSERT( IsSameTypes<decltype(&CreatePlayer), PFN_CreatePlayer> );
	STATIC_ASSERT( IsSameTypes<decltype(&DestroyPlayer), PFN_DestroyPlayer> );
	STATIC_ASSERT( IsSameTypes<decltype(&PlayerStart), PFN_PlayerStart> );
	STATIC_ASSERT( IsSameTypes<decltype(&PlayerPause), PFN_PlayerPause> );
	STATIC_ASSERT( IsSameTypes<decltype(&PlayerIsActive), PFN_PlayerIsActive> );
	STATIC_ASSERT( IsSameTypes<decltype(&SetPlayerVulkanEventListener), PFN_SetPlayerVulkanEventListener> );
	STATIC_ASSERT( IsSameTypes<decltype(&SetFileReader), PFN_SetFileReader> );
	STATIC_ASSERT( IsSameTypes<decltype(&AddPipelineCache), PFN_AddPipelineCache> );
	STATIC_ASSERT( IsSameTypes<decltype(&GetPipelineCache), PFN_GetPipelineCache> );

}	// VTPlayer
