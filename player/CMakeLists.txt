# auto generated file
cmake_minimum_required (VERSION 3.6.0)

#==================================================================================================
# project: Player
#==================================================================================================
set( SOURCES 
	"OpenGL/GLPlayer.h"
	"Public/VTPlayer.h"
	"Vulkan/VkPlayer.cpp"
	"Vulkan/VkPlayer.h"
	"FrameGraph/FGPlayer.cpp"
	"FrameGraph/FGPlayer.h"
	"VulkanEZ/VezPlayer.cpp"
	"VulkanEZ/VezPlayer.h"
	"CMakeLists.txt"
	"Generated/VulkanTraceFuncUnpacker.h"
	"Generated/VulkanTraceStructUnpacker.h"
	"Generated/VulkanTraceStructUnpackerImpl.h"
	"Player/BasePlayer.h"
	"Player/Player_v100.h"
	"Player/Player_vLatest.h" )
add_library( "Player" SHARED ${SOURCES} )
source_group( "OpenGL" FILES "OpenGL/GLPlayer.h" )
source_group( "Public" FILES "Public/VTPlayer.h" )
source_group( "Vulkan" FILES "Vulkan/VkPlayer.cpp" "Vulkan/VkPlayer.h" )
source_group( "FrameGraph" FILES "FrameGraph/FGPlayer.cpp" "FrameGraph/FGPlayer.h" )
source_group( "VulkanEZ" FILES "VulkanEZ/VezPlayer.cpp" "VulkanEZ/VezPlayer.h" )
source_group( "" FILES "CMakeLists.txt" )
source_group( "Generated" FILES "Generated/VulkanTraceFuncUnpacker.h" "Generated/VulkanTraceStructUnpacker.h" "Generated/VulkanTraceStructUnpackerImpl.h" )
source_group( "Player" FILES "Player/BasePlayer.h" "Player/Player_v100.h" "Player/Player_vLatest.h" )
target_include_directories( "Player" PRIVATE "${FRAMEGRAPH_INCLUDE_DIR}/extensions" )
target_include_directories( "Player" PRIVATE "${VTC_FRAMEGRAPH_EXTERNAL_PATH}" )
target_include_directories( "Player" PRIVATE "${FRAMEGRAPH_INCLUDE_DIR}" )
target_include_directories( "Player" PRIVATE ".." )
target_include_directories( "Player" PRIVATE "${VULKAN_HEADERS_INSTALL_DIR}/include" )
target_link_libraries( "Player" "Framework" )
target_compile_definitions( "Player" PUBLIC "${VTC_CONVERTER_DEFINES}" )
# compiler
target_compile_definitions( "Player" PRIVATE $<$<CONFIG:Debug>: ${PROJECTS_SHARED_DEFINES_DEBUG}> )
set_target_properties( "Player" PROPERTIES LINK_FLAGS_RELEASE ${PROJECTS_SHARED_LINKER_FLAGS_RELEASE} )
target_compile_definitions( "Player" PRIVATE $<$<CONFIG:Profile>: ${PROJECTS_SHARED_DEFINES_PROFILE}> )
target_compile_options( "Player" PRIVATE $<$<CONFIG:Release>: ${PROJECTS_SHARED_CXX_FLAGS_RELEASE}> )
set_target_properties( "Player" PROPERTIES LINK_FLAGS_DEBUG ${PROJECTS_SHARED_LINKER_FLAGS_DEBUG} )
target_compile_options( "Player" PRIVATE $<$<CONFIG:Profile>: ${PROJECTS_SHARED_CXX_FLAGS_PROFILE}> )
set_target_properties( "Player" PROPERTIES LINK_FLAGS_PROFILE ${PROJECTS_SHARED_LINKER_FLAGS_PROFILE} )
target_compile_options( "Player" PRIVATE $<$<CONFIG:Debug>: ${PROJECTS_SHARED_CXX_FLAGS_DEBUG}> )
target_compile_definitions( "Player" PRIVATE $<$<CONFIG:Release>: ${PROJECTS_SHARED_DEFINES_RELEASE}> )



