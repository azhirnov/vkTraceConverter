# auto generated file
cmake_minimum_required (VERSION 3.6.0)

set( VkTraceConverter_VERSION_MAJOR 0 )
set( VkTraceConverter_VERSION_MINOR 1 )

#==================================================================================================
# project: VkTraceConverter
#==================================================================================================
set( SOURCES 
	"Parser/AppTrace.cpp"
	"Parser/AppTrace.h"
	"Parser/TraceRange.cpp"
	"Parser/TraceRange.h"
	"Converters/Utils/BasicTypesConverter.h"
	"Converters/Utils/NameSerializer.cpp"
	"Converters/Utils/NameSerializer.h"
	"Converters/Data/Block.h"
	"Converters/Data/IResourceDataManager.h"
	"Converters/Data/ResourceDataManager.cpp"
	"Converters/Data/ResourceDataManager.h"
	"Converters/RawVulkan/CppRawVulkanConverter.cpp"
	"Converters/RawVulkan/CppRawVulkanConverter.h"
	"Analyzer/AllResourcesBookmarks.cpp"
	"Analyzer/AllResourcesBookmarks.h"
	"Analyzer/AnalyzerUtils.h"
	"Analyzer/DeviceAnalyzer.cpp"
	"Analyzer/DeviceAnalyzer.h"
	"Analyzer/DrawCallAnalyzer.h"
	"Analyzer/IAnalyzer.h"
	"Analyzer/ImageUsageAnalyzer.cpp"
	"Analyzer/ImageUsageAnalyzer.h"
	"Analyzer/SwapchainAnalyzer.cpp"
	"Analyzer/SwapchainAnalyzer.h"
	"CMakeLists.txt"
	"Common.h"
	"main.cpp"
	"VkTraceCommon.h"
	"Generated/BuildFunctionResourceBookmarks.h"
	"Generated/BuildRawVulkanCalls.h"
	"Generated/BuildStructResourceBookmarks.h"
	"Generated/UnpackPacket.h"
	"Generated/VkEnumToString.h"
	"Generated/VkStructToString.h"
	"Generated/VkStructTypes.h"
	"Converters/Converter.h"
	"Converters/ConverterConfig.h" )
add_executable( "VkTraceConverter" ${SOURCES} )
source_group( "Parser" FILES "Parser/AppTrace.cpp" "Parser/AppTrace.h" "Parser/TraceRange.cpp" "Parser/TraceRange.h" )
source_group( "Converters\\Utils" FILES "Converters/Utils/BasicTypesConverter.h" "Converters/Utils/NameSerializer.cpp" "Converters/Utils/NameSerializer.h" )
source_group( "Converters\\Data" FILES "Converters/Data/Block.h" "Converters/Data/IResourceDataManager.h" "Converters/Data/ResourceDataManager.cpp" "Converters/Data/ResourceDataManager.h" )
source_group( "Converters\\RawVulkan" FILES "Converters/RawVulkan/CppRawVulkanConverter.cpp" "Converters/RawVulkan/CppRawVulkanConverter.h" )
source_group( "Analyzer" FILES "Analyzer/AllResourcesBookmarks.cpp" "Analyzer/AllResourcesBookmarks.h" "Analyzer/AnalyzerUtils.h" "Analyzer/DeviceAnalyzer.cpp" "Analyzer/DeviceAnalyzer.h" "Analyzer/DrawCallAnalyzer.h" "Analyzer/IAnalyzer.h" "Analyzer/ImageUsageAnalyzer.cpp" "Analyzer/ImageUsageAnalyzer.h" "Analyzer/SwapchainAnalyzer.cpp" "Analyzer/SwapchainAnalyzer.h" )
source_group( "" FILES "CMakeLists.txt" "Common.h" "main.cpp" "VkTraceCommon.h" )
source_group( "Generated" FILES "Generated/BuildFunctionResourceBookmarks.h" "Generated/BuildRawVulkanCalls.h" "Generated/BuildStructResourceBookmarks.h" "Generated/UnpackPacket.h" "Generated/VkEnumToString.h" "Generated/VkStructToString.h" "Generated/VkStructTypes.h" )
source_group( "Converters" FILES "Converters/Converter.h" "Converters/ConverterConfig.h" )
target_include_directories( "VkTraceConverter" PRIVATE "${VT_CONVERTER_INCLUDE_DIRS}" )
target_include_directories( "VkTraceConverter" PRIVATE "" )
target_link_libraries( "VkTraceConverter" "${VT_CONVERTER_LIBRARIES}" )
if (UNIX)
	target_link_libraries( "VkTraceConverter" "dl;pthread" )
endif()
# compiler
target_compile_options( "VkTraceConverter" PRIVATE $<$<CONFIG:DebugAnalyze>: ${PROJECTS_SHARED_CXX_FLAGS_DEBUGANALYZE}> )
target_compile_definitions( "VkTraceConverter" PRIVATE $<$<CONFIG:Debug>: ${PROJECTS_SHARED_DEFINES_DEBUG}> )
target_compile_definitions( "VkTraceConverter" PRIVATE $<$<CONFIG:DebugAnalyze>: ${PROJECTS_SHARED_DEFINES_DEBUGANALYZE}> )
set_target_properties( "VkTraceConverter" PROPERTIES LINK_FLAGS_RELEASE ${PROJECTS_SHARED_LINKER_FLAGS_RELEASE} )
target_compile_definitions( "VkTraceConverter" PRIVATE $<$<CONFIG:Profile>: ${PROJECTS_SHARED_DEFINES_PROFILE}> )
target_compile_options( "VkTraceConverter" PRIVATE $<$<CONFIG:Release>: ${PROJECTS_SHARED_CXX_FLAGS_RELEASE}> )
set_target_properties( "VkTraceConverter" PROPERTIES LINK_FLAGS_DEBUG ${PROJECTS_SHARED_LINKER_FLAGS_DEBUG} )
set_target_properties( "VkTraceConverter" PROPERTIES LINK_FLAGS_DEBUGANALYZE ${PROJECTS_SHARED_LINKER_FLAGS_DEBUGANALYZE} )
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

#-----------------------------------


