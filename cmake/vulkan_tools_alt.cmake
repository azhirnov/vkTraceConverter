# use saved copy of LunarG VulkanTools

#if (NOT CMAKE_VERSION VERSION_LESS 3.7.0)
#	find_package( Vulkan )
#endif ()


if (NOT Vulkan_FOUND)
	if (EXISTS "${VTC_EXTERNALS_PATH}/vulkan/vulkan_core.h")
		set( Vulkan_INCLUDE_DIRS "${VTC_EXTERNALS_PATH}" )
		set( Vulkan_FOUND TRUE )

	elseif (EXISTS "${VTC_EXTERNALS_PATH}/vulkan/include/vulkan/vulkan_core.h")
		set( Vulkan_INCLUDE_DIRS "${VTC_EXTERNALS_PATH}/vulkan/include" )
		set( Vulkan_FOUND TRUE )

	elseif (EXISTS "${VTC_EXTERNALS_PATH}/Vulkan-Headers/include/vulkan/vulkan_core.h")
		set( Vulkan_INCLUDE_DIRS "${VTC_EXTERNALS_PATH}/Vulkan-Headers/include" )
		set( Vulkan_FOUND TRUE )
	endif ()
endif ()

if (NOT Vulkan_FOUND)
	message( FATAL_ERROR "Vulkan headers is not found! Install VulkanSDK or download from https://github.com/KhronosGroup/Vulkan-Headers" )
endif ()


set( VTC_CONVERTER_INCLUDE_DIRS "${VTC_CONVERTER_INCLUDE_DIRS}" "${VTC_EXTERNALS_PATH}/include" "${Vulkan_INCLUDE_DIRS}" )
