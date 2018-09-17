# copied from vktrace/CMakeLists.txt

# Make sure we're using 64-bit versions of stat, fopen, etc.
# Large File Support extensions:
#   http://www.gnu.org/software/libc/manual/html_node/Feature-Test-Macros.html#Feature-Test-Macros
add_definitions(-D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -D_LARGE_FILES -DNOMINMAX)

# support for inttypes.h macros
add_definitions(-D__STDC_LIMIT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_CONSTANT_MACROS)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	add_definitions(-DVK_USE_PLATFORM_WIN32_KHR -DWIN32_LEAN_AND_MEAN)
	set(DisplayServer Win32)

elseif(CMAKE_SYSTEM_NAME STREQUAL "Android")
	add_definitions(-DVK_USE_PLATFORM_ANDROID_KHR)

elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")

	if (BUILD_WSI_XCB_SUPPORT)
		add_definitions(-DVK_USE_PLATFORM_XCB_KHR)
	endif()

	if (BUILD_WSI_XLIB_SUPPORT)
		add_definitions(-DVK_USE_PLATFORM_XLIB_KHR)
	endif()

	if (BUILD_WSI_WAYLAND_SUPPORT)
		add_definitions(-DVK_USE_PLATFORM_WAYLAND_KHR)
	endif()

	if (BUILD_WSI_MIR_SUPPORT)
		# TODO Add Mir Support
		# add_definitions(-DVK_USE_PLATFORM_MIR_KHR)
		# include_directories(${MIR_INCLUDE_DIR})
	endif()

elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	# Only vktrace is supported on macOS
else()
	message(FATAL_ERROR "Unsupported Platform!")
endif()
