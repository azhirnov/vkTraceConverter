# auto generated file
cmake_minimum_required (VERSION 3.6.0)

#==================================================================================================
# project: Engine
#==================================================================================================
set( SOURCES 
	"Application.cpp"
	"Application.h"
	"CMakeLists.txt"
	"Common.h"
	"FIValue.h"
	"ResourceIDs.h" )
add_library( "Engine" STATIC ${SOURCES} )
source_group( "" FILES "Application.cpp" "Application.h" "CMakeLists.txt" "Common.h" "FIValue.h" "ResourceIDs.h" )
target_include_directories( "Engine" PRIVATE "${FRAMEGRAPH_INCLUDE_DIR}/extensions" )
target_include_directories( "Engine" PRIVATE "${VTC_FRAMEGRAPH_EXTERNAL_PATH}" )
target_include_directories( "Engine" PRIVATE "${FRAMEGRAPH_INCLUDE_DIR}" )
target_include_directories( "Engine" PRIVATE ".." )
target_include_directories( "Engine" PRIVATE "${VULKAN_HEADERS_INSTALL_DIR}/include" )
target_compile_definitions( "Engine" PUBLIC "${VTC_CONVERTER_DEFINES}" )
# compiler
target_compile_definitions( "Engine" PRIVATE $<$<CONFIG:Debug>: ${PROJECTS_SHARED_DEFINES_DEBUG}> )
set_target_properties( "Engine" PROPERTIES LINK_FLAGS_RELEASE ${PROJECTS_SHARED_LINKER_FLAGS_RELEASE} )
target_compile_definitions( "Engine" PRIVATE $<$<CONFIG:Profile>: ${PROJECTS_SHARED_DEFINES_PROFILE}> )
target_compile_options( "Engine" PRIVATE $<$<CONFIG:Release>: ${PROJECTS_SHARED_CXX_FLAGS_RELEASE}> )
set_target_properties( "Engine" PROPERTIES LINK_FLAGS_DEBUG ${PROJECTS_SHARED_LINKER_FLAGS_DEBUG} )
target_compile_options( "Engine" PRIVATE $<$<CONFIG:Profile>: ${PROJECTS_SHARED_CXX_FLAGS_PROFILE}> )
set_target_properties( "Engine" PROPERTIES LINK_FLAGS_PROFILE ${PROJECTS_SHARED_LINKER_FLAGS_PROFILE} )
target_compile_options( "Engine" PRIVATE $<$<CONFIG:Debug>: ${PROJECTS_SHARED_CXX_FLAGS_DEBUG}> )
target_compile_definitions( "Engine" PRIVATE $<$<CONFIG:Release>: ${PROJECTS_SHARED_DEFINES_RELEASE}> )



