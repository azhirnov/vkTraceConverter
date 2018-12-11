# download and install LunarG VulkanTools and dependend projects

# Vulkan-Headers
if (TRUE)
    set( VULKAN_HEADERS_INSTALL_DIR "${VTC_EXTERNAL_INSTALL_DIR}/Vulkan-Headers" CACHE INTERNAL "" FORCE )

	ExternalProject_Add( "Extern.Vulkan-Headers"
        LIST_SEPARATOR		"${VTC_LIST_SEPARATOR}"
		# download
		GIT_REPOSITORY		https://github.com/KhronosGroup/Vulkan-Headers.git
		GIT_TAG				master
		EXCLUDE_FROM_ALL	1
		LOG_DOWNLOAD		1
		# update
		PATCH_COMMAND		""
		UPDATE_DISCONNECTED	1
		# configure
        SOURCE_DIR			"${VTC_EXTERNALS_PATH}/Vulkan-Headers"
		CMAKE_GENERATOR		"${CMAKE_GENERATOR}"
		CMAKE_GENERATOR_TOOLSET	"${CMAKE_GENERATOR_TOOLSET}"
        CMAKE_ARGS			"-DCMAKE_CONFIGURATION_TYPES=${VTC_EXTERNAL_CONFIGURATION_TYPES}"
							"-DCMAKE_SYSTEM_VERSION=${CMAKE_SYSTEM_VERSION}"
							"-DCMAKE_DEBUG_POSTFIX="
							"-DCMAKE_RELEASE_POSTFIX="
							"-DCMAKE_INSTALL_PREFIX=${VULKAN_HEADERS_INSTALL_DIR}"
                            ${VTC_BUILD_TARGET_FLAGS}
		LOG_CONFIGURE 		1
		# build
		BINARY_DIR			"${CMAKE_BINARY_DIR}/build-Vulkan-Headers"
		BUILD_COMMAND		"${CMAKE_COMMAND}"
							--build .
							--target ALL_BUILD
							--config $<CONFIG>
		LOG_BUILD 			1
		# install
		INSTALL_DIR 		"${VULKAN_HEADERS_INSTALL_DIR}"
		#INSTALL_COMMAND	""
		LOG_INSTALL 		1
		# test
		TEST_COMMAND		""
	)
	
	set_property( TARGET "Extern.Vulkan-Headers" PROPERTY FOLDER "External" )
    set( VTC_BUILD_TARGET_FLAGS "${VTC_BUILD_TARGET_FLAGS}" "-DVULKAN_HEADERS_INSTALL_DIR=${VULKAN_HEADERS_INSTALL_DIR}" )
	
    set( VTC_CONVERTER_INCLUDE_DIRS "${VTC_CONVERTER_INCLUDE_DIRS}" "${VULKAN_HEADERS_INSTALL_DIR}/include" )
    set( VTC_PLAYER_INCLUDE_DIRS "${VTC_PLAYER_INCLUDE_DIRS}" "${VULKAN_HEADERS_INSTALL_DIR}/include" )
endif ()


# Vulkan-Loader
if (TRUE)
    set( VULKAN_LOADER_INSTALL_DIR "${VTC_EXTERNAL_INSTALL_DIR}/Vulkan-Loader" CACHE INTERNAL "" FORCE )

	ExternalProject_Add( "Extern.Vulkan-Loader"
        LIST_SEPARATOR		"${VTC_LIST_SEPARATOR}"
		DEPENDS				"Extern.Vulkan-Headers"
		# download
		GIT_REPOSITORY		https://github.com/KhronosGroup/Vulkan-Loader.git
		GIT_TAG				master
		EXCLUDE_FROM_ALL	1
		LOG_DOWNLOAD		1
		# update
		PATCH_COMMAND		""
		UPDATE_DISCONNECTED	1
		# configure
        SOURCE_DIR			"${VTC_EXTERNALS_PATH}/Vulkan-Loader"
		CMAKE_GENERATOR		"${CMAKE_GENERATOR}"
		CMAKE_GENERATOR_TOOLSET	"${CMAKE_GENERATOR_TOOLSET}"
        CMAKE_ARGS			"-DCMAKE_CONFIGURATION_TYPES=${VTC_EXTERNAL_CONFIGURATION_TYPES}"
							"-DCMAKE_SYSTEM_VERSION=${CMAKE_SYSTEM_VERSION}"
							"-DCMAKE_DEBUG_POSTFIX="
							"-DCMAKE_RELEASE_POSTFIX="
							"-DCMAKE_INSTALL_PREFIX=${VULKAN_LOADER_INSTALL_DIR}"
                            ${VTC_BUILD_TARGET_FLAGS}
		LOG_CONFIGURE 		1
		# build
		BINARY_DIR			"${CMAKE_BINARY_DIR}/build-Vulkan-Loader"
		BUILD_COMMAND		"${CMAKE_COMMAND}"
							--build .
							--target ALL_BUILD
							--config $<CONFIG>
		LOG_BUILD 			1
		# install
		INSTALL_DIR 		"${VULKAN_LOADER_INSTALL_DIR}"
		#INSTALL_COMMAND	""
		LOG_INSTALL 		1
		# test
		TEST_COMMAND		""
	)
	
	set_property( TARGET "Extern.Vulkan-Loader" PROPERTY FOLDER "External" )
    set( VTC_BUILD_TARGET_FLAGS "${VTC_BUILD_TARGET_FLAGS}" "-DVULKAN_LOADER_INSTALL_DIR=${VULKAN_LOADER_INSTALL_DIR}" )
endif ()


# GLSLANG
if (TRUE)
	# SPIRV-Tools require Python 2.7 for building
	find_package( PythonInterp 2.7 REQUIRED )
	find_package( PythonLibs 2.7 REQUIRED )

	ExternalProject_Add( "Extern.glslang"
		# download
		GIT_REPOSITORY		https://github.com/KhronosGroup/glslang.git
		GIT_TAG				master
		GIT_PROGRESS		1
		EXCLUDE_FROM_ALL	1
		LOG_DOWNLOAD		1
		# update
		PATCH_COMMAND		""
		UPDATE_DISCONNECTED	1
		LOG_UPDATE			1
		# configure
        SOURCE_DIR            "${VTC_EXTERNALS_PATH}/glslang"
		CONFIGURE_COMMAND	""
		# build
		BINARY_DIR			""
		BUILD_COMMAND		""
		INSTALL_COMMAND		""
		TEST_COMMAND		""
	)
	
	ExternalProject_Add( "Extern.SPIRV-Tools"
		DEPENDS				"Extern.glslang"
		# download
		GIT_REPOSITORY		https://github.com/KhronosGroup/SPIRV-Tools.git
		GIT_TAG				master
		GIT_PROGRESS		1
		EXCLUDE_FROM_ALL	1
		LOG_DOWNLOAD		1
		# update
		PATCH_COMMAND		""
		UPDATE_DISCONNECTED	1
		LOG_UPDATE			1
		# configure
        SOURCE_DIR            "${VTC_EXTERNALS_PATH}/glslang/External/SPIRV-Tools"
		CONFIGURE_COMMAND	""
		# build
		BINARY_DIR			""
		BUILD_COMMAND		""
		INSTALL_COMMAND		""
		TEST_COMMAND		""
	)
	
	ExternalProject_Add( "Extern.SPIRV-Headers"
		DEPENDS				"Extern.glslang"
							"Extern.SPIRV-Tools"
		# download
		GIT_REPOSITORY		https://github.com/KhronosGroup/SPIRV-Headers.git
		GIT_TAG				master
		GIT_PROGRESS		1
		EXCLUDE_FROM_ALL	1
		LOG_DOWNLOAD		1
		# update
		PATCH_COMMAND		""
		UPDATE_DISCONNECTED	1
		LOG_UPDATE			1
		# configure
        SOURCE_DIR            "${VTC_EXTERNALS_PATH}/glslang/External/SPIRV-Tools/external/SPIRV-Headers"
		CONFIGURE_COMMAND	""
		# build
		BINARY_DIR			""
		BUILD_COMMAND		""
		INSTALL_COMMAND		""
		TEST_COMMAND		""
	)
	
    set( GLSLANG_INSTALL_DIR "${VTC_EXTERNAL_INSTALL_DIR}/glslang" CACHE INTERNAL "" FORCE )

	ExternalProject_Add( "Extern.glslang-main"
        LIST_SEPARATOR      "${VTC_LIST_SEPARATOR}"
		DEPENDS				"Extern.glslang"
							"Extern.SPIRV-Tools"
							"Extern.SPIRV-Headers"
		# configure
        SOURCE_DIR          "${VTC_EXTERNALS_PATH}/glslang"
		CMAKE_GENERATOR		"${CMAKE_GENERATOR}"
		CMAKE_GENERATOR_TOOLSET	"${CMAKE_GENERATOR_TOOLSET}"
        CMAKE_ARGS            "-DCMAKE_CONFIGURATION_TYPES=${VTC_EXTERNAL_CONFIGURATION_TYPES}"
							"-DCMAKE_SYSTEM_VERSION=${CMAKE_SYSTEM_VERSION}"
							"-DCMAKE_DEBUG_POSTFIX="
							"-DCMAKE_RELEASE_POSTFIX="
							"-DCMAKE_INSTALL_PREFIX=${GLSLANG_INSTALL_DIR}"
							"-DENABLE_AMD_EXTENSIONS=ON"
							"-DENABLE_NV_EXTENSIONS=ON"
							"-DENABLE_HLSL=ON"
							"-DENABLE_OPT=ON"
							"-DENABLE_SPVREMAPPER=ON"
							"-DENABLE_GLSLANG_BINARIES=ON"
							"-DSKIP_GLSLANG_INSTALL=OFF"
							"-DSKIP_SPIRV_TOOLS_INSTALL=OFF"
							"-DSPIRV_SKIP_EXECUTABLES=OFF"
							"-DSPIRV_SKIP_TESTS=ON"
							"-DBUILD_TESTING=OFF"
                            ${VTC_BUILD_TARGET_FLAGS}
		LOG_CONFIGURE 		1
		# build
		BINARY_DIR			"${CMAKE_BINARY_DIR}/build-glslang2"
		BUILD_COMMAND		"${CMAKE_COMMAND}"
							--build .
							--target ALL_BUILD
							--config $<CONFIG>
		LOG_BUILD 			1
		# install
		INSTALL_DIR 		"${GLSLANG_INSTALL_DIR}"
		#INSTALL_COMMAND	""
		LOG_INSTALL 		1
		# test
		TEST_COMMAND		""
	)

	set_property( TARGET "Extern.SPIRV-Headers" PROPERTY FOLDER "External" )
	set_property( TARGET "Extern.SPIRV-Tools" PROPERTY FOLDER "External" )
	set_property( TARGET "Extern.glslang" PROPERTY FOLDER "External" )
	set_property( TARGET "Extern.glslang-main" PROPERTY FOLDER "External" )
	
	# Vulkan-ValidationLayers requires both debug and release libraries
	if (TRUE)
		add_custom_command (
			TARGET "Extern.glslang-main" POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different	"${GLSLANG_INSTALL_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SPIRV-Tools${CMAKE_STATIC_LIBRARY_SUFFIX}"
															"${GLSLANG_INSTALL_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SPIRV-Toolsd${CMAKE_STATIC_LIBRARY_SUFFIX}"
			VERBATIM
		)
		add_custom_command (
			TARGET "Extern.glslang-main" POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different	"${GLSLANG_INSTALL_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SPIRV-Tools-opt${CMAKE_STATIC_LIBRARY_SUFFIX}"
															"${GLSLANG_INSTALL_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SPIRV-Tools-optd${CMAKE_STATIC_LIBRARY_SUFFIX}"
			VERBATIM
		)
	endif ()

    set( VTC_BUILD_TARGET_FLAGS "${VTC_BUILD_TARGET_FLAGS}" "-DGLSLANG_INSTALL_DIR=${GLSLANG_INSTALL_DIR}" )
endif ()


# Vulkan-ValidationLayers
if (TRUE)
    set( VULKAN_VALIDATIONLAYERS_INSTALL_DIR "${VTC_EXTERNAL_INSTALL_DIR}/Vulkan-ValidationLayers" CACHE INTERNAL "" FORCE )

	ExternalProject_Add( "Extern.Vulkan-ValidationLayers"
        LIST_SEPARATOR      "${VTC_LIST_SEPARATOR}"
		DEPENDS				"Extern.Vulkan-Loader"
							"Extern.glslang-main"
		# download
		GIT_REPOSITORY		https://github.com/KhronosGroup/Vulkan-ValidationLayers.git
		GIT_TAG				master
		GIT_PROGRESS		1
		EXCLUDE_FROM_ALL	1
		LOG_DOWNLOAD		1
		# update
		PATCH_COMMAND		""
		UPDATE_DISCONNECTED	1
		# configure
        SOURCE_DIR          "${VTC_EXTERNALS_PATH}/Vulkan-ValidationLayers"
		CMAKE_GENERATOR		"${CMAKE_GENERATOR}"
		CMAKE_GENERATOR_TOOLSET	"${CMAKE_GENERATOR_TOOLSET}"
        CMAKE_ARGS            "-DCMAKE_CONFIGURATION_TYPES=${VTC_EXTERNAL_CONFIGURATION_TYPES}"
							"-DCMAKE_SYSTEM_VERSION=${CMAKE_SYSTEM_VERSION}"
							"-DCMAKE_DEBUG_POSTFIX="
							"-DCMAKE_RELEASE_POSTFIX="
							"-DCMAKE_INSTALL_PREFIX=${VULKAN_VALIDATIONLAYERS_INSTALL_DIR}"
                            ${VTC_BUILD_TARGET_FLAGS}
		LOG_CONFIGURE 		1
		# build
		BINARY_DIR			"${CMAKE_BINARY_DIR}/build-Vulkan-ValidationLayers"
		BUILD_COMMAND		"${CMAKE_COMMAND}"
							--build .
							--target ALL_BUILD
							--config $<CONFIG>
		LOG_BUILD 			1
		# install
		INSTALL_DIR 		"${VULKAN_VALIDATIONLAYERS_INSTALL_DIR}"
		#INSTALL_COMMAND	""
		LOG_INSTALL 		1
		# test
		TEST_COMMAND		""
	)
	
	set_property( TARGET "Extern.Vulkan-ValidationLayers" PROPERTY FOLDER "External" )
    set( VTC_BUILD_TARGET_FLAGS "${VTC_BUILD_TARGET_FLAGS}" "-DVULKAN_VALIDATIONLAYERS_INSTALL_DIR=${VULKAN_VALIDATIONLAYERS_INSTALL_DIR}" )
	
    set( VTC_CONVERTER_INCLUDE_DIRS "${VTC_CONVERTER_INCLUDE_DIRS}" "${VULKAN_VALIDATIONLAYERS_INSTALL_DIR}/include" )
endif ()


# Vulkan-Tools
if (TRUE)
    set( VULKAN_TOOLS_INSTALL_DIR "${VTC_EXTERNAL_INSTALL_DIR}/Vulkan-Tools" CACHE INTERNAL "" FORCE )

	ExternalProject_Add( "Extern.Vulkan-Tools"
        LIST_SEPARATOR      "${VTC_LIST_SEPARATOR}"
		DEPENDS				"Extern.Vulkan-ValidationLayers"
		# download
		GIT_REPOSITORY		https://github.com/KhronosGroup/Vulkan-Tools.git
		GIT_TAG				master
		GIT_PROGRESS		1
		EXCLUDE_FROM_ALL	1
		LOG_DOWNLOAD		1
		# update
		PATCH_COMMAND		""
		UPDATE_DISCONNECTED	1
		# configure
        SOURCE_DIR          "${VTC_EXTERNALS_PATH}/Vulkan-Tools"
		CMAKE_GENERATOR		"${CMAKE_GENERATOR}"
		CMAKE_GENERATOR_TOOLSET	"${CMAKE_GENERATOR_TOOLSET}"
        CMAKE_ARGS            "-DCMAKE_CONFIGURATION_TYPES=${VTC_EXTERNAL_CONFIGURATION_TYPES}"
							"-DCMAKE_SYSTEM_VERSION=${CMAKE_SYSTEM_VERSION}"
							"-DCMAKE_DEBUG_POSTFIX="
							"-DCMAKE_RELEASE_POSTFIX="
							"-DCMAKE_INSTALL_PREFIX=${VULKAN_TOOLS_INSTALL_DIR}"
                            ${VTC_BUILD_TARGET_FLAGS}
		LOG_CONFIGURE 		1
		# build
		BINARY_DIR			"${CMAKE_BINARY_DIR}/build-Vulkan-Tools"
		BUILD_COMMAND		"${CMAKE_COMMAND}"
							--build .
							--target ALL_BUILD
							--config $<CONFIG>
		LOG_BUILD 			1
		# install
		INSTALL_DIR 		"${VULKAN_TOOLS_INSTALL_DIR}"
		#INSTALL_COMMAND	""
		LOG_INSTALL 		1
		# test
		TEST_COMMAND		""
	)
	
	set_property( TARGET "Extern.Vulkan-Tools" PROPERTY FOLDER "External" )
    set( VTC_BUILD_TARGET_FLAGS "${VTC_BUILD_TARGET_FLAGS}" "-DVULKAN_TOOLS_INSTALL_DIR=${VULKAN_TOOLS_INSTALL_DIR}" )
endif ()


# LunarG VulkanTools
if (TRUE)
    set( LUNARG_VULKANTOOLS_INSTALL_DIR "${VTC_EXTERNAL_INSTALL_DIR}/LunarG-VulkanTools" CACHE INTERNAL "" FORCE )

    set( JSONCPP_INSTALL_DIR "${VTC_EXTERNAL_INSTALL_DIR}/jsoncpp" CACHE INTERNAL "" FORCE )
    set( VTC_BUILD_TARGET_FLAGS "${VTC_BUILD_TARGET_FLAGS}" "-DJSONCPP_INSTALL_DIR=${JSONCPP_INSTALL_DIR}" )

	if (WIN32)
        set( LUNARG_VULKANTOOLS_UPDATE_EXTERNAL_SOURCES "cmd //C \"${VTC_EXTERNALS_PATH}/LunarG-VulkanTools/update_external_sources.bat\"" )
	else ()
		set( LUNARG_VULKANTOOLS_UPDATE_EXTERNAL_SOURCES "" )	# TODO
	endif ()

	ExternalProject_Add( "Extern.LunarG-VulkanTools"
        LIST_SEPARATOR		"${VTC_LIST_SEPARATOR}"
		DEPENDS				"Extern.Vulkan-ValidationLayers"
		# download
		GIT_REPOSITORY		https://github.com/LunarG/VulkanTools.git
		GIT_TAG				master
		GIT_PROGRESS		1
		EXCLUDE_FROM_ALL	1
		LOG_DOWNLOAD		1
		# update
		PATCH_COMMAND		${LUNARG_VULKANTOOLS_UPDATE_EXTERNAL_SOURCES}
		UPDATE_DISCONNECTED	1
		# configure
        SOURCE_DIR			"${VTC_EXTERNALS_PATH}/LunarG-VulkanTools"
		CMAKE_GENERATOR		"${CMAKE_GENERATOR}"
		CMAKE_GENERATOR_TOOLSET	"${CMAKE_GENERATOR_TOOLSET}"
        CMAKE_ARGS            "-DCMAKE_CONFIGURATION_TYPES=${VTC_EXTERNAL_CONFIGURATION_TYPES}"
							"-DCMAKE_SYSTEM_VERSION=${CMAKE_SYSTEM_VERSION}"
							"-DCMAKE_DEBUG_POSTFIX="
							"-DCMAKE_RELEASE_POSTFIX="
							"-DCMAKE_INSTALL_PREFIX=${LUNARG_VULKANTOOLS_INSTALL_DIR}"
							"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=${LUNARG_VULKANTOOLS_INSTALL_DIR}"
							"-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY=${LUNARG_VULKANTOOLS_INSTALL_DIR}"
							"-DCMAKE_RUNTIME_OUTPUT_DIRECTORY=${LUNARG_VULKANTOOLS_INSTALL_DIR}"
							"-DBUILD_LAYERSVT=OFF"
							"-DBUILD_VIA=OFF"
							"-DBUILD_VKTRACEVIEWER=OFF"
							"-DBUILD_VLF=OFF"
                            ${VTC_BUILD_TARGET_FLAGS}
		LOG_CONFIGURE 		1
		# build
		BINARY_DIR			"${CMAKE_BINARY_DIR}/build-LunarG-VulkanTools"
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

	set_property( TARGET "Extern.LunarG-VulkanTools" PROPERTY FOLDER "External" )
    set( VTC_BUILD_TARGET_FLAGS "${VTC_BUILD_TARGET_FLAGS}" "-DLUNARG_VULKANTOOLS_INSTALL_DIR=${LUNARG_VULKANTOOLS_INSTALL_DIR}" )
	
    set( VTC_CONVERTER_INCLUDE_DIRS "${VTC_CONVERTER_INCLUDE_DIRS}"
                                    "${VTC_EXTERNALS_PATH}/LunarG-VulkanTools/vktrace/vktrace_common"
                                    "${VTC_EXTERNALS_PATH}/LunarG-VulkanTools/vktrace/vktrace_replay"
									"${CMAKE_BINARY_DIR}/build-LunarG-VulkanTools/vktrace" )

    set( VTC_CONVERTER_DEPENDENCIES "${VTC_CONVERTER_DEPENDENCIES}" "Extern.LunarG-VulkanTools" )
endif ()
