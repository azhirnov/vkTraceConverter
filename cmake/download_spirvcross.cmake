# download and install SPIRV-Cross

if (${VTC_ENABLE_SPIRVCROSS})
	set( VTC_EXTERNAL_SPIRVCROSS_PATH "" CACHE PATH "path to SPIRV-Cross source" )
    set( SPIRVCROSS_INSTALL_DIR "${VTC_EXTERNAL_INSTALL_DIR}/SPIRV-Cross" CACHE INTERNAL "" FORCE )
	
	# reset to default
	if (NOT EXISTS "${VTC_EXTERNAL_SPIRVCROSS_PATH}/include/spirv_cross")
		message( STATUS "SPIRV-Cross is not found in \"${VTC_EXTERNAL_SPIRVCROSS_PATH}\"" )
		set( VTC_EXTERNAL_SPIRVCROSS_PATH "${VTC_EXTERNALS_PATH}/SPIRV-Cross" CACHE PATH "" FORCE )
		set( VTC_SPIRVCROSS_REPOSITORY "https://github.com/KhronosGroup/SPIRV-Cross.git" )
	else ()
		set( VTC_SPIRVCROSS_REPOSITORY "" )
	endif ()


	ExternalProject_Add( "Extern.SPIRV-Cross"
        LIST_SEPARATOR		"${VTC_LIST_SEPARATOR}"
		# download
		GIT_REPOSITORY		${VTC_SPIRVCROSS_REPOSITORY}
		GIT_TAG				master
		EXCLUDE_FROM_ALL	1
		LOG_DOWNLOAD		1
		# update
		PATCH_COMMAND		""
		UPDATE_DISCONNECTED	1
		# configure
        SOURCE_DIR			"${VTC_EXTERNAL_SPIRVCROSS_PATH}"
		CMAKE_GENERATOR		"${CMAKE_GENERATOR}"
		CMAKE_GENERATOR_TOOLSET	"${CMAKE_GENERATOR_TOOLSET}"
        CMAKE_ARGS			"-DCMAKE_CONFIGURATION_TYPES=${VTC_EXTERNAL_CONFIGURATION_TYPES}"
							"-DCMAKE_SYSTEM_VERSION=${CMAKE_SYSTEM_VERSION}"
							"-DCMAKE_DEBUG_POSTFIX="
							"-DCMAKE_RELEASE_POSTFIX="
							"-DSPIRV_CROSS_EXCEPTIONS_TO_ASSERTIONS=ON"
							"-DCMAKE_INSTALL_PREFIX=${SPIRVCROSS_INSTALL_DIR}"
                            ${VTC_BUILD_TARGET_FLAGS}
		LOG_CONFIGURE 		1
		# build
		BINARY_DIR			"${CMAKE_BINARY_DIR}/build2-SPIRV-Cross"
		BUILD_COMMAND		"${CMAKE_COMMAND}"
							--build .
							--target ALL_BUILD
							--config $<CONFIG>
		LOG_BUILD 			1
		# install
		INSTALL_DIR 		"${SPIRVCROSS_INSTALL_DIR}"
		LOG_INSTALL 		1
		# test
		TEST_COMMAND		""
	)
	
	set_property( TARGET "Extern.SPIRV-Cross" PROPERTY FOLDER "External" )
	
    set( VTC_CONVERTER_LIBRARIES "${VTC_CONVERTER_LIBRARIES}"
									"${SPIRVCROSS_INSTALL_DIR}/lib/spirv-cross-core${CMAKE_STATIC_LIBRARY_SUFFIX}"
									"${SPIRVCROSS_INSTALL_DIR}/lib/spirv-cross-glsl${CMAKE_STATIC_LIBRARY_SUFFIX}" )

    set( VTC_CONVERTER_INCLUDE_DIRS "${VTC_CONVERTER_INCLUDE_DIRS}" "${SPIRVCROSS_INSTALL_DIR}/include" )
    set( VTC_CONVERTER_DEPENDENCIES "${VTC_CONVERTER_DEPENDENCIES}" "Extern.SPIRV-Cross" )
	set( VTC_CONVERTER_DEFINES "${VTC_CONVERTER_DEFINES}" "VTC_ENABLE_SPIRVCROSS" )
endif ()
