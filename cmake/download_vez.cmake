# download and install Vulkan-EZ library

if (FALSE)
	ExternalProject_Add( "Extern.Vulkan-EZ"
        LIST_SEPARATOR		"${VTC_LIST_SEPARATOR}"
		# download
		GIT_REPOSITORY		https://github.com/GPUOpen-LibrariesAndSDKs/V-EZ.git
		GIT_TAG				master
		EXCLUDE_FROM_ALL	1
		LOG_DOWNLOAD		1
		# update
		PATCH_COMMAND		""
		UPDATE_DISCONNECTED	1
		# configure
        SOURCE_DIR			"${VTC_EXTERNALS_PATH}/Vulkan-EZ"
		CMAKE_GENERATOR		"${CMAKE_GENERATOR}"
		CMAKE_GENERATOR_TOOLSET	"${CMAKE_GENERATOR_TOOLSET}"
        CMAKE_ARGS			"-DCMAKE_CONFIGURATION_TYPES=${VTC_EXTERNAL_CONFIGURATION_TYPES}"
							"-DCMAKE_SYSTEM_VERSION=${CMAKE_SYSTEM_VERSION}"
							"-DCMAKE_DEBUG_POSTFIX="
							"-DCMAKE_RELEASE_POSTFIX="
                            ${VTC_BUILD_TARGET_FLAGS}
		LOG_CONFIGURE 		1
		# build
		BINARY_DIR			"${CMAKE_BINARY_DIR}/build-Vulkan-EZ"
		BUILD_COMMAND		"${CMAKE_COMMAND}"
							--build .
							--target ALL_BUILD
							--config $<CONFIG>
		LOG_BUILD 			1
		# install
		INSTALL_DIR 		""
		INSTALL_COMMAND		""
		LOG_INSTALL 		1
		# test
		TEST_COMMAND		""
	)
	
	set_property( TARGET "Extern.Vulkan-EZ" PROPERTY FOLDER "External" )
endif ()
