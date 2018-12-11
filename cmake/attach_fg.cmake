# find and attach FrameGraph

set( VTC_FRAMEGRAPH_PATH "${CMAKE_SOURCE_DIR}/external/FrameGraph" CACHE PATH "Path to FrameGraph library" )
message( STATUS "VTC_FRAMEGRAPH_PATH: ${VTC_FRAMEGRAPH_PATH}" )

if (NOT EXISTS "${VTC_FRAMEGRAPH_PATH}/framegraph/VFG.h")
	message( FATAL_ERROR "VTC_FRAMEGRAPH_PATH with \"${VTC_FRAMEGRAPH_PATH}\" doesn't contains correct path to FrameGraph source!" )
endif ()

#option( FG_ENABLE_STDALLOC "" OFF )
#option( FG_ENABLE_GLSLANG "" ON )
#option( FG_ENABLE_VMA "" ON )
option( FG_ENABLE_TESTS "" OFF )
option( FG_ENABLE_SAMPLES "" OFF )
#option( FG_ENABLE_GLFW "" ON )
#option( FG_ENABLE_SDL2 "" OFF )
option( FG_ENABLE_SFML "" OFF )
option( FG_ENABLE_LODEPNG "" OFF )
option( FG_ENABLE_IMGUI "" OFF )
option( FG_ENABLE_ASSIMP "" OFF )
option( FG_ENABLE_GLM "" OFF )
option( FG_ENABLE_DEVIL "" OFF )
option( FG_ENABLE_FREEIMAGE "" OFF )

add_subdirectory( "${VTC_FRAMEGRAPH_PATH}" "build-FrameGraph" )

set_property( TARGET "FrameGraph" PROPERTY FOLDER "External" )
set_property( TARGET "STL" PROPERTY FOLDER "External" )

set( VTC_CONVERTER_LIBRARIES "${VTC_CONVERTER_LIBRARIES}" "STL" "VulkanLoader" "FrameGraph" )

set( VTC_PLAYER_INCLUDE_DIRS "${VTC_PLAYER_INCLUDE_DIRS}" "${VTC_FRAMEGRAPH_PATH}" "${VTC_FRAMEGRAPH_PATH}/extensions" )
set( VTC_PLAYER_LIBRARIES "${VTC_PLAYER_LIBRARIES}" "STL" "VulkanLoader" "Framework" "FrameGraph" "PipelineCompiler" )
