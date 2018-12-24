# download and install brotli library

if (${VTC_ENABLE_BROTLI})
	set( VTC_EXTERNAL_BROTLI_PATH "" CACHE PATH "path to brotli source" )
    set( BROTLI_INSTALL_DIR "${VTC_EXTERNAL_INSTALL_DIR}/brotli" CACHE INTERNAL "" FORCE )
	
	# reset to default
	if (NOT EXISTS "${VTC_EXTERNAL_BROTLI_PATH}/c/include/brotli")
		message( STATUS "brotli is not found in \"${VTC_EXTERNAL_BROTLI_PATH}\"" )
		set( VTC_EXTERNAL_BROTLI_PATH "${VTC_EXTERNALS_PATH}/brotli" CACHE PATH "" FORCE )
		set( VTC_BROTLI_REPOSITORY "https://github.com/google/brotli.git" )
	else ()
		set( VTC_BROTLI_REPOSITORY "" )
	endif ()

	ExternalProject_Add( "Extern.brotli"
        LIST_SEPARATOR		"${VTC_LIST_SEPARATOR}"
		# download
		GIT_REPOSITORY		${VTC_BROTLI_REPOSITORY}
		GIT_TAG				master
		EXCLUDE_FROM_ALL	1
		LOG_DOWNLOAD		1
		# update
		PATCH_COMMAND		""
		UPDATE_DISCONNECTED	1
		# configure
        SOURCE_DIR			"${VTC_EXTERNAL_BROTLI_PATH}"
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
		BINARY_DIR			"${CMAKE_BINARY_DIR}/build2-brotli"
		BUILD_COMMAND		"${CMAKE_COMMAND}"
							--build .
							--target ALL_BUILD
							--config $<CONFIG>
		LOG_BUILD 			1
		# install
		INSTALL_DIR 		"${BROTLI_INSTALL_DIR}"
		LOG_INSTALL 		1
		# test
		TEST_COMMAND		""
	)
	
	set_property( TARGET "Extern.brotli" PROPERTY FOLDER "External" )
    set( VTC_BUILD_TARGET_FLAGS "${VTC_BUILD_TARGET_FLAGS}" "-DBROTLI_INSTALL_DIR=${BROTLI_INSTALL_DIR}" )
	
    set( VTC_CONVERTER_LIBRARIES "${VTC_CONVERTER_LIBRARIES}"
									"${BROTLI_INSTALL_DIR}/lib/brotlidec-static${CMAKE_STATIC_LIBRARY_SUFFIX}"
									"${BROTLI_INSTALL_DIR}/lib/brotlienc-static${CMAKE_STATIC_LIBRARY_SUFFIX}"
									"${BROTLI_INSTALL_DIR}/lib/brotlicommon-static${CMAKE_STATIC_LIBRARY_SUFFIX}" )

    set( VTC_CONVERTER_INCLUDE_DIRS "${VTC_CONVERTER_INCLUDE_DIRS}" "${BROTLI_INSTALL_DIR}/include" )
    set( VTC_CONVERTER_DEPENDENCIES "${VTC_CONVERTER_DEPENDENCIES}" "Extern.brotli" )
	set( VTC_CONVERTER_DEFINES "${VTC_CONVERTER_DEFINES}" "VTC_ENABLE_BROTLI" )

    set( VTC_PLAYER_INCLUDE_DIRS "${VTC_PLAYER_INCLUDE_DIRS}" "${BROTLI_INSTALL_DIR}/include" )
    set( VTC_PLAYER_LIBRARIES "${VTC_PLAYER_LIBRARIES}" "brotlidec-static" "brotlienc-static" "brotlicommon-static" )
    set( VTC_PLAYER_DEPENDENCIES "${VTC_PLAYER_DEPENDENCIES}" "Extern.brotli" )
endif ()
