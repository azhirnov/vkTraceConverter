# auto generated file
cmake_minimum_required (VERSION 3.6.0)

#==================================================================================================
# project: Generator
#==================================================================================================
set( SOURCES 
	"CMakeLists.txt"
	"GenEnumToString.cpp"
	"Generator.cpp"
	"Generator.h"
	"GenRawVulkanCalls.cpp"
	"GenResourceBookmarks.cpp"
	"GenStructToString.cpp"
	"GenStructTypeHelpers.cpp"
	"GenUnpacker.cpp"
	"HeaderParser.cpp"
	"MarkRequiredTypes.cpp"
	"StringParser.cpp"
	"StringParser.h" )
add_executable( "Generator" ${SOURCES} )
source_group( "" FILES "CMakeLists.txt" "GenEnumToString.cpp" "Generator.cpp" "Generator.h" "GenRawVulkanCalls.cpp" "GenResourceBookmarks.cpp" "GenStructToString.cpp" "GenStructTypeHelpers.cpp" "GenUnpacker.cpp" "HeaderParser.cpp" "MarkRequiredTypes.cpp" "StringParser.cpp" "StringParser.h" )
target_include_directories( "Generator" PRIVATE "" )
target_include_directories( "Generator" PRIVATE "${FRAMEGRAPH_INCLUDE_DIR}" )
target_include_directories( "Generator" PRIVATE "${VULKAN_HEADERS_INSTALL_DIR}/include" )
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


