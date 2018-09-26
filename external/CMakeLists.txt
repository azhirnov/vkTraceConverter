# download and install all external dependencies

cmake_policy( SET CMP0022 NEW )
cmake_minimum_required (VERSION 3.6.0)

include( ExternalProject )

set( VTC_EXTERNALS_PATH "${CMAKE_CURRENT_SOURCE_DIR}" CACHE PATH "Path to external projects sources" )
set( VTC_EXTERNAL_INSTALL_DIR "${CMAKE_BINARY_DIR}/install" )
message( STATUS "VTC_EXTERNALS_PATH: ${VTC_EXTERNALS_PATH}" )


# init converter dependencies
set( VTC_CONVERTER_INCLUDE_DIRS "" )
set( VTC_CONVERTER_DEPENDENCIES "" )
set( VTC_CONVERTER_LIBRARIES "" )
set( VTC_CONVERTER_DEFINES "" )


# configure
set( VTC_LIST_SEPARATOR "|" )
string( REPLACE ";" "${VTC_LIST_SEPARATOR}" VTC_EXTERNAL_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" )
set( VTC_BUILD_TARGET_FLAGS "" )

foreach ( CONFIG ${CMAKE_CONFIGURATION_TYPES} )
	string( TOUPPER ${CONFIG} OUT_CONFIG )

    set( VTC_BUILD_TARGET_FLAGS
        "${VTC_BUILD_TARGET_FLAGS}"
		"-DCMAKE_C_FLAGS_${OUT_CONFIG}=${CMAKE_C_FLAGS_${OUT_CONFIG}}"
		"-DCMAKE_CXX_FLAGS_${OUT_CONFIG}=${CMAKE_CXX_FLAGS_${OUT_CONFIG}}"
		"-DCMAKE_EXE_LINKER_FLAGS_${OUT_CONFIG}=${CMAKE_EXE_LINKER_FLAGS_${OUT_CONFIG}}"
		"-DCMAKE_STATIC_LINKER_FLAGS_${OUT_CONFIG}=${CMAKE_STATIC_LINKER_FLAGS_${OUT_CONFIG}}"
		"-DCMAKE_SHARED_LINKER_FLAGS_${OUT_CONFIG}=${CMAKE_SHARED_LINKER_FLAGS_${OUT_CONFIG}}"
	)
endforeach ()


if (VTC_STABLE)
	include( "${CMAKE_SOURCE_DIR}/cmake/vulkan_tools_alt.cmake" )
else ()
	include( "${CMAKE_SOURCE_DIR}/cmake/download_vulkan_tools.cmake" )
endif ()

include( "${CMAKE_SOURCE_DIR}/cmake/download_other.cmake" )
include( "${CMAKE_SOURCE_DIR}/cmake/download_fg.cmake" )
include( "${CMAKE_SOURCE_DIR}/cmake/graphviz.cmake" )
include( "${CMAKE_SOURCE_DIR}/cmake/vktrace_defines.cmake" )
include( "${CMAKE_SOURCE_DIR}/cmake/app_defines.cmake" )


set( VTC_CONVERTER_INCLUDE_DIRS "${VTC_CONVERTER_INCLUDE_DIRS}" CACHE INTERNAL "" FORCE )
set( VTC_CONVERTER_DEPENDENCIES "${VTC_CONVERTER_DEPENDENCIES}" CACHE INTERNAL "" FORCE )
set( VTC_CONVERTER_LIBRARIES "${VTC_CONVERTER_LIBRARIES}" CACHE INTERNAL "" FORCE )
set( VTC_CONVERTER_DEFINES "${VTC_CONVERTER_DEFINES}" CACHE INTERNAL "" FORCE )
