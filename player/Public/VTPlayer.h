// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#ifdef __cplusplus
extern "C" {
#endif
	
#if defined(_WIN32)
#	define VTPLAYER_CALL	__stdcall
#else
#	define VTPLAYER_CALL
#endif

#ifndef OUT
#	define OUT
#endif

#include <stdint.h>


namespace VTPlayer
{

	enum VTPlayerVersion
	{
		//VTPLAYER_VERSION_1_0	= 0x10000,

		VTPLAYER_VERSION_LATEST	= 0x00001,
	};





	//
	// Player Settings
	//

	struct VTPlayerSettings
	{
		uint32_t				structSize;					// must be sizeof(VTPlayerSettings)

		// player
		uint32_t				playerVersion;				// VTPlayerVersion
		const char *			playerTraceFile;
		const char *			playerDataFile;				// can be null if all data presented in trace file.
		uint32_t				playerDebugMode : 1;		// may enable debug report.
		uint32_t				playerTestMode : 1;			// capture rendering output (render targets and writable images/buffers),
															// you can handle this capture by EventListener and capare with reference captures.
		uint32_t				playerBenchmarkMode : 1;	// enables CPU and GPU benchmarks, you can handle results by EventListener.

		// window
		int						windowWidth;
		int						windowHeight;
		int						windowPositionX;
		int						windowPositionY;
		const char *			windowTitle;
		uint32_t				windowFPSinTitle : 1;
		uint32_t				windowFullscreen : 1;

		// vulkan instance
		uint32_t				instanceApiVersion;			// the current api version will be calculated as 'Max( settings.instanceApiVersion, trace.apiVersion )'
		const char * const*		instanceLayers;				// you can specify validation layers, by default all layers are disable.
		uint32_t				instanceLayerCount;
		const char * const*		instanceExtensions;			// additional extensions for user code, all required by trace extensions will be enable anyway.
		uint32_t				instanceExtensionCount;

		// physical device
		const char *			preferredGPUName;			// recomendations for physical device slector.
		uint32_t				preferDescreteGPU : 1;
		uint32_t				preferIntegratedGPU : 1;

		// vulkan device
		const char * const*		deviceExtensions;			// additional extensions for user code, all required by trace extensions will be enable anyway.
		uint32_t				deviceExtensionCount;

		// vulkan swapchain
		uint32_t				swapchainVkColorFormat;		// VkFormat
		uint32_t				swapchainVkColorSpace;		// VkColorSpaceKHR
		uint32_t				swapchainVkMinImageCount;
		uint32_t				swapchainVkPreTransform;	// VkSurfaceTransformFlagBitsKHR
		uint32_t				swapchainVkPresentMode;		// VkPresentModeKHR
		uint32_t				swapchainVkCompositeAlpha;	// VkCompositeAlphaFlagBitsKHR

		// opengl ...

		// framegraph ...
	};


	//
	// Vulkan Event Listener
	//

	struct VulkanEventListener
	{
		typedef void (VTPLAYER_CALL *PFN_OnImageCapture) (/*todo*/);
		typedef void (VTPLAYER_CALL *PFN_OnBufferCapture) (/*todo*/);
		typedef void (VTPLAYER_CALL *PFN_OnDebugReport) (/*TODO*/);
		typedef void (VTPLAYER_CALL *PFN_OnBenckmarkResult) (/*TODO*/);

	};


	//
	// File Reader
	//

	struct FileReader
	{
		typedef uint64_t Bytes;
		typedef void*    Handle;

		typedef int   (VTPLAYER_CALL *PFN_Open)  (void* userData, const char* filename, OUT Handle* file);
		typedef int   (VTPLAYER_CALL *PFN_Close) (void* userData, Handle file);
		typedef Bytes (VTPLAYER_CALL *PFN_Read)  (void* userData, Handle file, Bytes offset, void* buffer, Bytes bufferSize);

		PFN_Open	open;
		PFN_Close	close;
		PFN_Read	read;
		void*		userData;
	};

	
	typedef struct VTPlayerInstance_t*  VTPlayerInstance;

	typedef int  (VTPLAYER_CALL *PFN_CreateVTPlayer) (const struct VTPlayerSettings *, OUT VTPlayerInstance *);
	typedef void (VTPLAYER_CALL *PFN_DestroyVTPlayer) (VTPlayerInstance);

	typedef int  (VTPLAYER_CALL *PFN_PlayerStart) (VTPlayerInstance);
	typedef int  (VTPLAYER_CALL *PFN_PlayerPause) (VTPlayerInstance);

	typedef int  (VTPLAYER_CALL *PFN_SetPlayerVulkanEventListener) (VTPlayerInstance, const struct VulkanEventListener *);
	typedef int  (VTPLAYER_CALL *PFN_SetFileReader) (VTPlayerInstance, const struct FileReader *);
	typedef int  (VTPLAYER_CALL *PFN_AddPipelineCache) (VTPlayerInstance, const void*, size_t);

}	// VTPlayer


#ifdef __cplusplus
} // extern "C"
#endif