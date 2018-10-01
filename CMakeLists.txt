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


set( VTC_STABLE OFF CACHE BOOL "disable code generation and some external projects" )
set( VTC_ENABLE_GLFW ON CACHE BOOL "use GLFW" )
set( VTC_ENABLE_SDL2 OFF CACHE BOOL "use SDL2" )

set( MAIN_BINARY_DIR "${CMAKE_BINARY_DIR}/bin" CACHE INTERNAL "" FORCE )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${MAIN_BINARY_DIR}" )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${MAIN_BINARY_DIR}" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${MAIN_BINARY_DIR}" )

link_directories( "${LUNARG_VULKANTOOLS_INSTALL_DIR}" )
link_directories( "${FRAMEGRAPH_INSTALL_DIR}/lib" )
link_directories( "${BROTLI_INSTALL_DIR}/lib" )
add_subdirectory( "converter" "converter" )

add_subdirectory( "engine" "engine" )

add_subdirectory( "player" "player" )
add_subdirectory( "player_exe" "player_exe" )

message( STATUS "project 'VkTraceConverter' generation ended" )
message( STATUS "\n==========================================================================" )

