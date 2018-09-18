# auto generated file
cmake_minimum_required (VERSION 3.6.0)

set( VkTraceConverter_VERSION_MAJOR 0 )
set( VkTraceConverter_VERSION_MINOR 1 )

#==================================================================================================
# project: Generator
#==================================================================================================
set( SOURCES 
	"../generator/CMakeLists.txt"
	"../generator/GenEnumToString.cpp"
	"../generator/Generator.cpp"
	"../generator/Generator.h"
	"../generator/GenRawVulkanCalls.cpp"
	"../generator/GenResourceBookmarks.cpp"
	"../generator/GenStructToString.cpp"
	"../generator/GenStructTypeHelpers.cpp"
	"../generator/GenUnpacker.cpp"
	"../generator/HeaderParser.cpp"
	"../generator/MarkRequiredTypes.cpp"
	"../generator/StringParser.cpp"
	"../generator/StringParser.h" )
add_executable( "Generator" ${SOURCES} )
source_group( "" FILES "../generator/CMakeLists.txt" "../generator/GenEnumToString.cpp" "../generator/Generator.cpp" "../generator/Generator.h" "../generator/GenRawVulkanCalls.cpp" "../generator/GenResourceBookmarks.cpp" "../generator/GenStructToString.cpp" "../generator/GenStructTypeHelpers.cpp" "../generator/GenUnpacker.cpp" "../generator/HeaderParser.cpp" "../generator/MarkRequiredTypes.cpp" "../generator/StringParser.cpp" "../generator/StringParser.h" )
target_include_directories( "Generator" PRIVATE "${FRAMEGRAPH_INCLUDE_DIR}" )
target_include_directories( "Generator" PRIVATE "${VULKAN_HEADERS_INSTALL_DIR}/include" )
target_include_directories( "Generator" PRIVATE "../generator" )
target_link_libraries( "Generator" "STL" )
# compiler
target_compile_definitions( "Generator" PRIVATE $<$<CONFIG:Debug>: ${PROJECTS_SHARED_DEFINES_DEBUG}> )
set_target_properties( "Generator" PROPERTIES LINK_FLAGS_RELEASE ${PROJECTS_SHARED_LINKER_FLAGS_RELEASE} )
target_compile_definitions( "Generator" PRIVATE $<$<CONFIG:Profile>: ${PROJECTS_SHARED_DEFINES_PROFILE}> )
target_compile_options( "Generator" PRIVATE $<$<CONFIG:Release>: ${PROJECTS_SHARED_CXX_FLAGS_RELEASE}> )
set_target_properties( "Generator" PROPERTIES LINK_FLAGS_DEBUG ${PROJECTS_SHARED_LINKER_FLAGS_DEBUG} )
target_compile_options( "Generator" PRIVATE $<$<CONFIG:Profile>: ${PROJECTS_SHARED_CXX_FLAGS_PROFILE}> )
set_target_properties( "Generator" PROPERTIES LINK_FLAGS_PROFILE ${PROJECTS_SHARED_LINKER_FLAGS_PROFILE} )
target_compile_options( "Generator" PRIVATE $<$<CONFIG:Debug>: ${PROJECTS_SHARED_CXX_FLAGS_DEBUG}> )
target_compile_definitions( "Generator" PRIVATE $<$<CONFIG:Release>: ${PROJECTS_SHARED_DEFINES_RELEASE}> )

#-----------------------------------

if ( CONFIGURATION_DEPENDENT_PATH )
	set( GENERATOR_EXE "${MAIN_BINARY_DIR}/$<CONFIG>/Generator${CMAKE_EXECUTABLE_SUFFIX}" CACHE INTERNAL "" FORCE )
else ()
	set( GENERATOR_EXE "${MAIN_BINARY_DIR}/Generator${CMAKE_EXECUTABLE_SUFFIX}" CACHE INTERNAL "" FORCE )
endif ()

#-----------------------------------


#==================================================================================================
# project: VkTraceConverter
#==================================================================================================
set( SOURCES 
	"Parser/AppTrace.cpp"
	"Parser/AppTrace.h"
	"Parser/TraceRange.cpp"
	"Parser/TraceRange.h"
	"Parser/VkObjectsTracker.cpp"
	"Analyzer/old/DeviceAnalyzer2.cpp"
	"Analyzer/old/DeviceAnalyzer2.h"
	"Analyzer/old/DrawCallAnalyzer.h"
	"Converters/FrameGraph/FrameGraphConverter.h"
	"Analyzer/Ext/ExtensionAnalyzer.cpp"
	"Analyzer/Ext/ExtensionAnalyzer.h"
	"Converters/Utils/BasicTypesConverter.h"
	"Converters/Utils/NameSerializer.cpp"
	"Converters/Utils/NameSerializer.h"
	"Converters/Utils/ResRemapper.cpp"
	"Converters/Utils/ResRemapper.h"
	"Converters/Data/Block.h"
	"Converters/Data/IResourceDataManager.h"
	"Converters/Data/ResourceDataManager.cpp"
	"Converters/Data/ResourceDataManager.h"
	"Converters/CppVulkan/CppVulkanConverter.cpp"
	"Converters/CppVulkan/CppVulkanConverter.h"
	"Converters/CppVulkan/CppVulkanConverter2.cpp"
	"Converters/CppVulkan/CppVulkanConverter_MemRemap.cpp"
	"Analyzer/AnalyzerUtils.h"
	"Analyzer/IAnalyzer.h"
	"Analyzer/ResourceTracker.h"
	"CMakeLists.txt"
	"Common.h"
	"main.cpp"
	"VkTraceCommon.h"
	"Generated/BuildFunctionResourceBookmarks.h"
	"Generated/BuildRawVulkanCalls.h"
	"Generated/BuildStructResourceBookmarks.h"
	"Generated/UnpackPacket.h"
	"Generated/VkEnumToString.h"
	"Generated/VkEnumToStringImpl.h"
	"Generated/VkStructToString.h"
	"Generated/VkStructToStringImpl.h"
	"Generated/VkStructTypes.h"
	"Analyzer/Default/AllResourcesBookmarks.cpp"
	"Analyzer/Default/AllResourcesBookmarks.h"
	"Analyzer/Default/BufferAnalyzer.cpp"
	"Analyzer/Default/BufferAnalyzer.h"
	"Analyzer/Default/DeviceAnalyzer.cpp"
	"Analyzer/Default/DeviceAnalyzer.h"
	"Analyzer/Default/ImageAnalyzer.cpp"
	"Analyzer/Default/ImageAnalyzer.h"
	"Analyzer/Default/MemoryObjAnalyzer.cpp"
	"Analyzer/Default/MemoryObjAnalyzer.h"
	"Analyzer/Default/MemoryTransferAnalyzer.cpp"
	"Analyzer/Default/MemoryTransferAnalyzer.h"
	"Analyzer/Default/SwapchainAnalyzer.cpp"
	"Analyzer/Default/SwapchainAnalyzer.h"
	"Converters/Converter.h"
	"Converters/ConverterConfig.h" )
add_executable( "VkTraceConverter" ${SOURCES} )
source_group( "Parser" FILES "Parser/AppTrace.cpp" "Parser/AppTrace.h" "Parser/TraceRange.cpp" "Parser/TraceRange.h" "Parser/VkObjectsTracker.cpp" )
source_group( "Analyzer\\old" FILES "Analyzer/old/DeviceAnalyzer2.cpp" "Analyzer/old/DeviceAnalyzer2.h" "Analyzer/old/DrawCallAnalyzer.h" )
source_group( "Converters\\FrameGraph" FILES "Converters/FrameGraph/FrameGraphConverter.h" )
source_group( "Analyzer\\Ext" FILES "Analyzer/Ext/ExtensionAnalyzer.cpp" "Analyzer/Ext/ExtensionAnalyzer.h" )
source_group( "Converters\\Utils" FILES "Converters/Utils/BasicTypesConverter.h" "Converters/Utils/NameSerializer.cpp" "Converters/Utils/NameSerializer.h" "Converters/Utils/ResRemapper.cpp" "Converters/Utils/ResRemapper.h" )
source_group( "Converters\\Data" FILES "Converters/Data/Block.h" "Converters/Data/IResourceDataManager.h" "Converters/Data/ResourceDataManager.cpp" "Converters/Data/ResourceDataManager.h" )
source_group( "Converters\\CppVulkan" FILES "Converters/CppVulkan/CppVulkanConverter.cpp" "Converters/CppVulkan/CppVulkanConverter.h" "Converters/CppVulkan/CppVulkanConverter2.cpp" "Converters/CppVulkan/CppVulkanConverter_MemRemap.cpp" )
source_group( "Analyzer" FILES "Analyzer/AnalyzerUtils.h" "Analyzer/IAnalyzer.h" "Analyzer/ResourceTracker.h" )
source_group( "" FILES "CMakeLists.txt" "Common.h" "main.cpp" "VkTraceCommon.h" )
source_group( "Generated" FILES "Generated/BuildFunctionResourceBookmarks.h" "Generated/BuildRawVulkanCalls.h" "Generated/BuildStructResourceBookmarks.h" "Generated/UnpackPacket.h" "Generated/VkEnumToString.h" "Generated/VkEnumToStringImpl.h" "Generated/VkStructToString.h" "Generated/VkStructToStringImpl.h" "Generated/VkStructTypes.h" )
source_group( "Analyzer\\Default" FILES "Analyzer/Default/AllResourcesBookmarks.cpp" "Analyzer/Default/AllResourcesBookmarks.h" "Analyzer/Default/BufferAnalyzer.cpp" "Analyzer/Default/BufferAnalyzer.h" "Analyzer/Default/DeviceAnalyzer.cpp" "Analyzer/Default/DeviceAnalyzer.h" "Analyzer/Default/ImageAnalyzer.cpp" "Analyzer/Default/ImageAnalyzer.h" "Analyzer/Default/MemoryObjAnalyzer.cpp" "Analyzer/Default/MemoryObjAnalyzer.h" "Analyzer/Default/MemoryTransferAnalyzer.cpp" "Analyzer/Default/MemoryTransferAnalyzer.h" "Analyzer/Default/SwapchainAnalyzer.cpp" "Analyzer/Default/SwapchainAnalyzer.h" )
source_group( "Converters" FILES "Converters/Converter.h" "Converters/ConverterConfig.h" )
target_include_directories( "VkTraceConverter" PRIVATE "${VT_CONVERTER_INCLUDE_DIRS}" )
target_include_directories( "VkTraceConverter" PRIVATE "" )
target_link_libraries( "VkTraceConverter" "${VT_CONVERTER_LIBRARIES}" )
# compiler
target_compile_definitions( "VkTraceConverter" PRIVATE $<$<CONFIG:Debug>: ${PROJECTS_SHARED_DEFINES_DEBUG}> )
set_target_properties( "VkTraceConverter" PROPERTIES LINK_FLAGS_RELEASE ${PROJECTS_SHARED_LINKER_FLAGS_RELEASE} )
target_compile_definitions( "VkTraceConverter" PRIVATE $<$<CONFIG:Profile>: ${PROJECTS_SHARED_DEFINES_PROFILE}> )
target_compile_options( "VkTraceConverter" PRIVATE $<$<CONFIG:Release>: ${PROJECTS_SHARED_CXX_FLAGS_RELEASE}> )
set_target_properties( "VkTraceConverter" PROPERTIES LINK_FLAGS_DEBUG ${PROJECTS_SHARED_LINKER_FLAGS_DEBUG} )
target_compile_options( "VkTraceConverter" PRIVATE $<$<CONFIG:Profile>: ${PROJECTS_SHARED_CXX_FLAGS_PROFILE}> )
set_target_properties( "VkTraceConverter" PROPERTIES LINK_FLAGS_PROFILE ${PROJECTS_SHARED_LINKER_FLAGS_PROFILE} )
target_compile_options( "VkTraceConverter" PRIVATE $<$<CONFIG:Debug>: ${PROJECTS_SHARED_CXX_FLAGS_DEBUG}> )
target_compile_definitions( "VkTraceConverter" PRIVATE $<$<CONFIG:Release>: ${PROJECTS_SHARED_DEFINES_RELEASE}> )

#-----------------------------------

include( "../cmake/vktrace_defines.cmake" )
include( "../cmake/app_defines.cmake" )

foreach (DEP ${VT_CONVERTER_DEPENDENCIES})
	add_dependencies( "VkTraceConverter" "${DEP}" )
endforeach ()

if (NOT VTC_STABLE)
	if (NOT DEFINED GENERATOR_EXE)
		message( FATAL_ERROR "GENERATOR_EXE is not defined" )
	endif ()
	add_custom_target( "VkTraceConverterDeps"
		COMMAND ${GENERATOR_EXE} 
			-vulkan "${VULKAN_HEADERS_INSTALL_DIR}/include/vulkan"
			-vktrace "${VT_EXTERNALS_PATH}/LunarG-VulkanTools/vktrace/vktrace_common/vktrace_trace_packet_identifiers.h"
			-output "${CMAKE_CURRENT_SOURCE_DIR}/Generated"
		COMMENT "Generate helper sources..."
		VERBATIM
	)
	add_dependencies( "VkTraceConverterDeps" "Generator" )
endif ()
#-----------------------------------


