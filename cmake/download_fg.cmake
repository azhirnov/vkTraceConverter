# download and install FrameGraph library

set( VTC_FRAMEGRAPH_PATH "C:\\Projects\\VkFrameGraph" CACHE PATH "Path to FrameGraph library" FORCE )
message( STATUS "VTC_FRAMEGRAPH_PATH: ${VTC_FRAMEGRAPH_PATH}" )

set( VTC_FRAMEGRAPH_DEPS "" )
set( VTC_FRAMEGRAPH_EXTERNAL_PATH "${VTC_FRAMEGRAPH_PATH}/external" )


# download Vulkan FrameGraph
if (NOT EXISTS "${VTC_FRAMEGRAPH_PATH}")

    set( VTC_FRAMEGRAPH_PATH "${VTC_EXTERNALS_PATH}/FrameGraph" )

	ExternalProject_Add( "External.Download.FrameGraph"
		# download
		GIT_REPOSITORY		https://github.com/azhirnov/FrameGraph.git
		GIT_TAG				master
		EXCLUDE_FROM_ALL	1
		LOG_DOWNLOAD		1
		# update
		PATCH_COMMAND		""
		UPDATE_DISCONNECTED	1
		LOG_UPDATE			1
		# configure
        SOURCE_DIR			"${VTC_FRAMEGRAPH_PATH}"
		CONFIGURE_COMMAND	""
		# build
		BINARY_DIR			""
		BUILD_COMMAND		""
		INSTALL_COMMAND		""
		TEST_COMMAND		""
	)
	
	set_property( TARGET "External.Download.FrameGraph" PROPERTY FOLDER "External" )
    set( VTC_FRAMEGRAPH_DEPS "External.Download.FrameGraph" )
    set( VTC_FRAMEGRAPH_EXTERNAL_PATH "${VTC_EXTERNALS_PATH}/FG-External" )
endif ()


set( VTC_FRAMEGRAPH_EXTERNAL_PATH "${VTC_FRAMEGRAPH_EXTERNAL_PATH}" CACHE INTERNAL "" FORCE )
set( FRAMEGRAPH_INSTALL_DIR "${VTC_EXTERNAL_INSTALL_DIR}/FrameGraph" CACHE INTERNAL "" FORCE )
set( FRAMEGRAPH_INCLUDE_DIR "${VTC_FRAMEGRAPH_PATH}" CACHE INTERNAL "" FORCE )

if (${VTC_ENABLE_GLFW})
	set( VTC_CONVERTER_DEFINES "${VTC_CONVERTER_DEFINES}" "FG_ENABLE_GLFW" )
endif ()
if (${VTC_ENABLE_SDL2})
	set( VTC_CONVERTER_DEFINES "${VTC_CONVERTER_DEFINES}" "FG_ENABLE_SDL2" )
endif ()

ExternalProject_Add( "External.FrameGraph"
    LIST_SEPARATOR		"${VTC_LIST_SEPARATOR}"
    DEPENDS				${VTC_FRAMEGRAPH_DEPS}
	# configure
    SOURCE_DIR			"${VTC_FRAMEGRAPH_PATH}"
	CMAKE_GENERATOR		"${CMAKE_GENERATOR}"
	CMAKE_GENERATOR_TOOLSET	"${CMAKE_GENERATOR_TOOLSET}"
    CMAKE_ARGS			"-DCMAKE_CONFIGURATION_TYPES=${VTC_EXTERNAL_CONFIGURATION_TYPES}"
						"-DCMAKE_SYSTEM_VERSION=${CMAKE_SYSTEM_VERSION}"
						"-DCMAKE_DEBUG_POSTFIX="
						"-DCMAKE_RELEASE_POSTFIX="
						"-DFG_ENABLE_GLSLANG=OFF"
						"-DFG_ENABLE_GLFW=${VTC_ENABLE_GLFW}"
						"-DFG_ENABLE_SDL2=${VTC_ENABLE_SDL2}"
						"-DFG_ENABLE_SFML=OFF"
						"-DFG_ENABLE_VMA=ON"
						"-DFG_ENABLE_LODEPNG=OFF"
						"-DFG_ENABLE_TESTS=OFF"
						"-DFG_ENABLE_SAMPLES=OFF"
						"-DCMAKE_INSTALL_PREFIX=${FRAMEGRAPH_INSTALL_DIR}"
                        "-DFG_EXTERNALS_PATH=${VTC_FRAMEGRAPH_EXTERNAL_PATH}"
                        ${VTC_BUILD_TARGET_FLAGS}
	LOG_CONFIGURE 		1
	# build
	BINARY_DIR			"${CMAKE_BINARY_DIR}/build-FrameGraph"
	BUILD_COMMAND		"${CMAKE_COMMAND}"
						--build .
						--target ALL_BUILD
						--config $<CONFIG>
	LOG_BUILD 			1
	# install
	INSTALL_DIR 		"${FRAMEGRAPH_INSTALL_DIR}"
	#INSTALL_COMMAND	""
	LOG_INSTALL 		1
	# test
	TEST_COMMAND		""
)
	
set_property( TARGET "External.FrameGraph" PROPERTY FOLDER "External" )


set( VTC_CONVERTER_INCLUDE_DIRS "${VTC_CONVERTER_INCLUDE_DIRS}" "${VTC_FRAMEGRAPH_PATH}" "${VTC_FRAMEGRAPH_PATH}/extensions" )
set( VTC_CONVERTER_LIBRARIES "${VTC_CONVERTER_LIBRARIES}" "STL" "VulkanLoader" )
set( VTC_CONVERTER_DEPENDENCIES "${VTC_CONVERTER_DEPENDENCIES}" "External.FrameGraph" )
