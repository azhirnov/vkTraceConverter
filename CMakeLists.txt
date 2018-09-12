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
add_subdirectory( "external" "external" )


link_directories( "${LUNARG_VULKANTOOLS_INSTALL_DIR}" )
link_directories( "${FRAMEGRAPH_INSTALL_DIR}/lib" )
link_directories( "${BROTLI_INSTALL_DIR}/lib" )
add_subdirectory( "vktrace_conv" "vktrace_conv" )

add_subdirectory( "engine" "engine" )

message( STATUS "project 'VkTraceConverter' generation ended" )
message( STATUS "\n==========================================================================" )

