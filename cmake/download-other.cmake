# download and install other external dependencies


# Vulkan-EZ
if (FALSE)
	ExternalProject_Add( "External.Vulkan-EZ"
		LIST_SEPARATOR		"${VT_LIST_SEPARATOR}"
		# download
		GIT_REPOSITORY		https://github.com/GPUOpen-LibrariesAndSDKs/V-EZ.git
		GIT_TAG				master
		EXCLUDE_FROM_ALL	1
		LOG_DOWNLOAD		1
		# update
		PATCH_COMMAND		""
		UPDATE_DISCONNECTED	1
		# configure
		SOURCE_DIR			"${VT_EXTERNALS_PATH}/Vulkan-EZ"
		CMAKE_GENERATOR		"${CMAKE_GENERATOR}"
		CMAKE_GENERATOR_TOOLSET	"${CMAKE_GENERATOR_TOOLSET}"
		CMAKE_ARGS			"-DCMAKE_CONFIGURATION_TYPES=${VT_EXTERNAL_CONFIGURATION_TYPES}"
							"-DCMAKE_SYSTEM_VERSION=${CMAKE_SYSTEM_VERSION}"
							"-DCMAKE_DEBUG_POSTFIX="
							"-DCMAKE_RELEASE_POSTFIX="
							${VT_BUILD_TARGET_FLAGS}
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
	
	set_property( TARGET "External.Vulkan-EZ" PROPERTY FOLDER "External" )
endif ()


#[[ brotli
if (FALSE)
	FetchContent_Declare( ExternalDownloadBrotli
		GIT_REPOSITORY		https://github.com/google/brotli.git
		GIT_TAG				master
		SOURCE_DIR			"${VT_EXTERNALS_PATH}/brotli"
	)
	
	FetchContent_GetProperties( ExternalDownloadBrotli )
	if (NOT ExternalDownloadBrotli_POPULATED)
		FetchContent_Populate( ExternalDownloadBrotli )
	endif ()
	
	add_subdirectory( "${VT_EXTERNALS_PATH}/brotli" "brotli" )
endif ()]]


# brotli
if (FALSE)
	set( BROTLI_INSTALL_DIR "${VT_EXTERNAL_INSTALL_DIR}/brotli" CACHE INTERNAL "" FORCE )

	ExternalProject_Add( "External.brotli"
		LIST_SEPARATOR		"${VT_LIST_SEPARATOR}"
		# download
		GIT_REPOSITORY		https://github.com/google/brotli.git
		GIT_TAG				master
		EXCLUDE_FROM_ALL	1
		LOG_DOWNLOAD		1
		# update
		PATCH_COMMAND		""
		UPDATE_DISCONNECTED	1
		# configure
		SOURCE_DIR			"${VT_EXTERNALS_PATH}/brotli"
		CMAKE_GENERATOR		"${CMAKE_GENERATOR}"
		CMAKE_GENERATOR_TOOLSET	"${CMAKE_GENERATOR_TOOLSET}"
		CMAKE_ARGS			"-DCMAKE_CONFIGURATION_TYPES=${VT_EXTERNAL_CONFIGURATION_TYPES}"
							"-DCMAKE_SYSTEM_VERSION=${CMAKE_SYSTEM_VERSION}"
							"-DCMAKE_DEBUG_POSTFIX="
							"-DCMAKE_RELEASE_POSTFIX="
							"-DCMAKE_INSTALL_PREFIX=${BROTLI_INSTALL_DIR}"
							${VT_BUILD_TARGET_FLAGS}
		LOG_CONFIGURE 		1
		# build
		BINARY_DIR			"${CMAKE_BINARY_DIR}/build-brotli"
		BUILD_COMMAND		"${CMAKE_COMMAND}"
							--build .
							--target ALL_BUILD
							--config $<CONFIG>
		LOG_BUILD 			1
		# install
		INSTALL_DIR 		"${BROTLI_INSTALL_DIR}"
		#INSTALL_COMMAND	""
		LOG_INSTALL 		1
		# test
		TEST_COMMAND		""
	)
	
	set_property( TARGET "External.brotli" PROPERTY FOLDER "External" )
	set( VT_BUILD_TARGET_FLAGS "${VT_BUILD_TARGET_FLAGS}" "-DBROTLI_INSTALL_DIR=${BROTLI_INSTALL_DIR}" )
	
	set( VT_CONVERTER_INCLUDE_DIRS "${VT_CONVERTER_INCLUDE_DIRS}" "${BROTLI_INSTALL_DIR}/include" )
	set( VT_CONVERTER_LIBRARIES "${VT_CONVERTER_LIBRARIES}" "brotlidec-static" "brotlienc-static" "brotlicommon-static" )
	set( VT_CONVERTER_DEPENDENCIES "${VT_CONVERTER_DEPENDENCIES}" "External.brotli" )
endif ()


# blake2
if (FALSE)
	add_library( "External.blake2" STATIC
			"BLAKE2/sse/blake2.h"
			"BLAKE2/sse/blake2b.c"
			"BLAKE2/sse/blake2s.c"
			"BLAKE2/sse/blake2bp.c"
			"BLAKE2/sse/blake2sp.c"
		)

	target_include_directories( "External.blake2" PUBLIC "BLAKE2/sse" )
	target_compile_definitions( "External.blake2" PUBLIC "-D__SSE2__" )

	set_property( TARGET "External.blake2" PROPERTY FOLDER "External" )
	
	set( VT_CONVERTER_LIBRARIES "${VT_CONVERTER_LIBRARIES}" "External.blake2" )
endif ()

