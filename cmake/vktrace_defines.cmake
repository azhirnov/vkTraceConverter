# copied from vktrace/CMakeLists.txt

set( VTC_VKTRACE_DEFINES "" )

# Make sure we're using 64-bit versions of stat, fopen, etc.
# Large File Support extensions:
#   http://www.gnu.org/software/libc/manual/html_node/Feature-Test-Macros.html#Feature-Test-Macros
set( VTC_CONVERTER_DEFINES "${VTC_CONVERTER_DEFINES}" "_LARGEFILE_SOURCE" "_FILE_OFFSET_BITS=64" "_LARGE_FILES" "NOMINMAX" )

# support for inttypes.h macros
set( VTC_CONVERTER_DEFINES "${VTC_CONVERTER_DEFINES}" "__STDC_LIMIT_MACROS" "__STDC_FORMAT_MACROS" "__STDC_CONSTANT_MACROS" )

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	set( VTC_VKTRACE_DEFINES "${VTC_VKTRACE_DEFINES}" "VK_USE_PLATFORM_WIN32_KHR" "WIN32_LEAN_AND_MEAN" )
	set(DisplayServer Win32)

elseif(CMAKE_SYSTEM_NAME STREQUAL "Android")
	set( VTC_VKTRACE_DEFINES "${VTC_VKTRACE_DEFINES}" "VK_USE_PLATFORM_ANDROID_KHR" )

elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")

	if (BUILD_WSI_XCB_SUPPORT)
		set( VTC_VKTRACE_DEFINES "${VTC_VKTRACE_DEFINES}" "VK_USE_PLATFORM_XCB_KHR" )
	endif()

	if (BUILD_WSI_XLIB_SUPPORT)
		set( VTC_VKTRACE_DEFINES "${VTC_VKTRACE_DEFINES}" "VK_USE_PLATFORM_XLIB_KHR" )
	endif()

	if (BUILD_WSI_WAYLAND_SUPPORT)
		set( VTC_VKTRACE_DEFINES "${VTC_VKTRACE_DEFINES}" "VK_USE_PLATFORM_WAYLAND_KHR" )
	endif()

	if (BUILD_WSI_MIR_SUPPORT)
		# TODO Add Mir Support
		# set( VTC_VKTRACE_DEFINES "${VTC_VKTRACE_DEFINES}" "VK_USE_PLATFORM_MIR_KHR" )
		# include_directories(${MIR_INCLUDE_DIR})
	endif()

elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	# Only vktrace is supported on macOS
else()
	message(FATAL_ERROR "Unsupported Platform!")
endif()

set( VTC_VKTRACE_DEFINES ${VTC_VKTRACE_DEFINES} CACHE INTERNAL "" FORCE )
