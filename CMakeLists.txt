# auto generated file
cmake_minimum_required (VERSION 3.6.0)

message( STATUS "==========================================================================\n" )
message( STATUS "project 'VkTraceConverter' generation started" )

project( "VkTraceConverter" LANGUAGES C CXX )
set_property( GLOBAL PROPERTY USE_FOLDERS ON )
message( STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} (${CMAKE_CXX_COMPILER_VERSION})" )
message( STATUS "Compiler name: ${DETECTED_COMPILER}" )
message( STATUS "target system: ${CMAKE_SYSTEM_NAME} (${CMAKE_SYSTEM_VERSION})" )
message( STATUS "host system: ${CMAKE_HOST_SYSTEM_NAME} (${CMAKE_HOST_SYSTEM_VERSION})" )

include( "cmake/compilers.cmake" )

set( VTC_STABLE OFF CACHE BOOL "disable code generation and some external projects" )
set( VTC_ENABLE_BROTLI ON CACHE BOOL "use brotli compression" )
set( VTC_ENABLE_SPIRVCROSS OFF CACHE BOOL "use SPIRV-Cross for shader reflection" )
set( VTC_ENABLE_SPIRVREFLECT ON CACHE BOOL "use SPIRV-Reflect for shader reflection" )

set( MAIN_BINARY_DIR "${CMAKE_BINARY_DIR}/bin" CACHE INTERNAL "" FORCE )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${MAIN_BINARY_DIR}" )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${MAIN_BINARY_DIR}" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${MAIN_BINARY_DIR}" )
add_subdirectory( "external" "external" )

include( "cmake/attach_fg.cmake" )

link_directories( "${LUNARG_VULKANTOOLS_INSTALL_DIR}" )
link_directories( "${FRAMEGRAPH_INSTALL_DIR}/lib" )
link_directories( "${BROTLI_INSTALL_DIR}/lib" )
add_subdirectory( "converter" "converter" )

add_subdirectory( "engine" "engine" )

add_subdirectory( "player" "player" )

message( STATUS "project 'VkTraceConverter' generation ended" )
message( STATUS "\n==========================================================================" )

