# download and install other external dependencies


#[[ brotli
if (TRUE)
	FetchContent_Declare( ExternalDownloadBrotli
		GIT_REPOSITORY		https://github.com/google/brotli.git
		GIT_TAG				master
        SOURCE_DIR            "${VTC_EXTERNALS_PATH}/brotli"
	)
	
	FetchContent_GetProperties( ExternalDownloadBrotli )
	if (NOT ExternalDownloadBrotli_POPULATED)
		FetchContent_Populate( ExternalDownloadBrotli )
	endif ()
	
    add_subdirectory( "${VTC_EXTERNALS_PATH}/brotli" "brotli" )
endif ()]]


# brotli
if (TRUE)
    set( BROTLI_INSTALL_DIR "${VTC_EXTERNAL_INSTALL_DIR}/brotli" CACHE INTERNAL "" FORCE )

	ExternalProject_Add( "External.brotli"
        LIST_SEPARATOR		"${VTC_LIST_SEPARATOR}"
		# download
		GIT_REPOSITORY		https://github.com/google/brotli.git
		GIT_TAG				master
		EXCLUDE_FROM_ALL	1
		LOG_DOWNLOAD		1
		# update
		PATCH_COMMAND		""
		UPDATE_DISCONNECTED	1
		# configure
        SOURCE_DIR			"${VTC_EXTERNALS_PATH}/brotli"
		CMAKE_GENERATOR		"${CMAKE_GENERATOR}"
		CMAKE_GENERATOR_TOOLSET	"${CMAKE_GENERATOR_TOOLSET}"
        CMAKE_ARGS            "-DCMAKE_CONFIGURATION_TYPES=${VTC_EXTERNAL_CONFIGURATION_TYPES}"
							"-DCMAKE_SYSTEM_VERSION=${CMAKE_SYSTEM_VERSION}"
							"-DCMAKE_DEBUG_POSTFIX="
							"-DCMAKE_RELEASE_POSTFIX="
							"-DCMAKE_INSTALL_PREFIX=${BROTLI_INSTALL_DIR}"
                            ${VTC_BUILD_TARGET_FLAGS}
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
    set( VTC_BUILD_TARGET_FLAGS "${VTC_BUILD_TARGET_FLAGS}" "-DBROTLI_INSTALL_DIR=${BROTLI_INSTALL_DIR}" )
	
    set( VTC_CONVERTER_INCLUDE_DIRS "${VTC_CONVERTER_INCLUDE_DIRS}" "${BROTLI_INSTALL_DIR}/include" )
    set( VTC_CONVERTER_LIBRARIES "${VTC_CONVERTER_LIBRARIES}" "brotlidec-static" "brotlienc-static" "brotlicommon-static" )
    set( VTC_CONVERTER_DEPENDENCIES "${VTC_CONVERTER_DEPENDENCIES}" "External.brotli" )
endif ()


# blake2
if (TRUE)
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
	
    set( VTC_CONVERTER_LIBRARIES "${VTC_CONVERTER_LIBRARIES}" "External.blake2" )
endif ()

