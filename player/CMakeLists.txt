# auto generated file
cmake_minimum_required (VERSION 3.6.0)

#==================================================================================================
# project: Player
#==================================================================================================
set( SOURCES 
	"Reader/DataLoader.h"
	"Reader/TraceReader.cpp"
	"Reader/TraceReader.h"
	"Public/VTPlayer.h"
	"Vulkan/VkPlayer.cpp"
	"Vulkan/VkPlayer.h"
	"Vulkan/VUnpacker.h"
	"FrameGraph/FGPlayer.cpp"
	"FrameGraph/FGPlayer.h"
	"FrameGraph/FGPlayer2.cpp"
	"FrameGraph/FGUnpacker.h"
	"VulkanEZ/VezPlayer.cpp"
	"VulkanEZ/VezPlayer.h"
	"Core/IPlayer.h"
	"Core/IPlayerInstance.h"
	"Core/PlayerInstance_v100.h"
	"Core/PlayerInstance_vLatest.cpp"
	"Core/PlayerInstance_vLatest.h"
	"Core/Settings.h"
	"Core/VTPlayerDll.cpp"
	"CMakeLists.txt" )
add_library( "Player" STATIC ${SOURCES} )
source_group( "Reader" FILES "Reader/DataLoader.h" "Reader/TraceReader.cpp" "Reader/TraceReader.h" )
source_group( "Public" FILES "Public/VTPlayer.h" )
source_group( "Vulkan" FILES "Vulkan/VkPlayer.cpp" "Vulkan/VkPlayer.h" "Vulkan/VUnpacker.h" )
source_group( "FrameGraph" FILES "FrameGraph/FGPlayer.cpp" "FrameGraph/FGPlayer.h" "FrameGraph/FGPlayer2.cpp" "FrameGraph/FGUnpacker.h" )
source_group( "VulkanEZ" FILES "VulkanEZ/VezPlayer.cpp" "VulkanEZ/VezPlayer.h" )
source_group( "Core" FILES "Core/IPlayer.h" "Core/IPlayerInstance.h" "Core/PlayerInstance_v100.h" "Core/PlayerInstance_vLatest.cpp" "Core/PlayerInstance_vLatest.h" "Core/Settings.h" "Core/VTPlayerDll.cpp" )
source_group( "" FILES "CMakeLists.txt" )
target_include_directories( "Player" PRIVATE "" )
target_include_directories( "Player" PRIVATE "${VTC_PLAYER_INCLUDE_DIRS}" )
target_include_directories( "Player" PRIVATE "${CMAKE_SOURCE_DIR}/shared" )
target_link_libraries( "Player" "${VTC_PLAYER_LIBRARIES}" )
target_compile_definitions( "Player" PUBLIC "${VTC_CONVERTER_DEFINES}" )
add_dependencies( "Player" ${VTC_PLAYER_DEPENDENCIES} )
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



#==================================================================================================
# project: Tests.Player
#==================================================================================================
set( SOURCES 
	"../tests/player/Common.h"
	"../tests/player/main.cpp"
	"../tests/player/mgf_events.vktrace"
	"../tests/player/Test_BrotliStream.cpp"
	"../tests/player/Test_FGPacker.cpp"
	"../tests/player/Test_VPacker.cpp" )
add_executable( "Tests.Player" ${SOURCES} )
source_group( "" FILES "../tests/player/Common.h" "../tests/player/main.cpp" "../tests/player/mgf_events.vktrace" "../tests/player/Test_BrotliStream.cpp" "../tests/player/Test_FGPacker.cpp" "../tests/player/Test_VPacker.cpp" )
set_property( TARGET "Tests.Player" PROPERTY FOLDER "Tests" )
target_include_directories( "Tests.Player" PRIVATE "${VTC_CONVERTER_INCLUDE_DIRS}" )
target_include_directories( "Tests.Player" PRIVATE "${CMAKE_SOURCE_DIR}/converter" )
target_include_directories( "Tests.Player" PRIVATE "${CMAKE_SOURCE_DIR}/shared" )
target_link_libraries( "Tests.Player" "STL" )
target_link_libraries( "Tests.Player" "Utils" )
target_compile_definitions( "Tests.Player" PUBLIC "${VTC_CONVERTER_DEFINES}" )
target_compile_definitions( "Tests.Player" PUBLIC "${VTC_VKTRACE_DEFINES}" )
# compiler
target_compile_definitions( "Tests.Player" PRIVATE $<$<CONFIG:Debug>: ${PROJECTS_SHARED_DEFINES_DEBUG}> )
set_target_properties( "Tests.Player" PROPERTIES LINK_FLAGS_RELEASE ${PROJECTS_SHARED_LINKER_FLAGS_RELEASE} )
target_compile_definitions( "Tests.Player" PRIVATE $<$<CONFIG:Profile>: ${PROJECTS_SHARED_DEFINES_PROFILE}> )
target_compile_options( "Tests.Player" PRIVATE $<$<CONFIG:Release>: ${PROJECTS_SHARED_CXX_FLAGS_RELEASE}> )
set_target_properties( "Tests.Player" PROPERTIES LINK_FLAGS_DEBUG ${PROJECTS_SHARED_LINKER_FLAGS_DEBUG} )
target_compile_options( "Tests.Player" PRIVATE $<$<CONFIG:Profile>: ${PROJECTS_SHARED_CXX_FLAGS_PROFILE}> )
set_target_properties( "Tests.Player" PROPERTIES LINK_FLAGS_PROFILE ${PROJECTS_SHARED_LINKER_FLAGS_PROFILE} )
target_compile_options( "Tests.Player" PRIVATE $<$<CONFIG:Debug>: ${PROJECTS_SHARED_CXX_FLAGS_DEBUG}> )
target_compile_definitions( "Tests.Player" PRIVATE $<$<CONFIG:Release>: ${PROJECTS_SHARED_DEFINES_RELEASE}> )



