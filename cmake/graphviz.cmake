# find command line GraphViz program that supports dot language.

set( VTC_GRAPHVIZ_ROOT "" CACHE PATH "Path to GraphViz binaries" )


# search installed GraphViz application
if (WIN32)
	list( APPEND searchdirs ${VTC_GRAPHVIZ_ROOT} ${CMAKE_SYSTEM_PREFIX_PATH} )
	  
	foreach (path ${searchdirs})
		file( GLOB filelist RELATIVE ${path} ${path}/* )

		foreach	(subath ${filelist})
			if (IS_DIRECTORY "${path}/${subath}")
								
				string( TOLOWER ${subath} outLowerCaseSubPath )
				string( FIND ${outLowerCaseSubPath} "graphviz" outPos )
				if (outPos GREATER -1)
					set( GRAPHVIZ_PATH "${path}/${subath}" )
				endif ()
				
			endif ()
		endforeach ()
		
	endforeach ()
	
	if (GRAPHVIZ_PATH)
		find_file( VTC_GRAPHVIZ_DOT_EXECUTABLE NAMES "bin/dot.exe" PATHS "${GRAPHVIZ_PATH}" )
		
		if (NOT VTC_GRAPHVIZ_DOT_EXECUTABLE)
			message( WARNING "GraphViz found in ${GRAPHVIZ_PATH}, but 'dot.exe' is not found!" )
		endif ()
	endif ()
endif ()

if (UNIX)
# TODO
endif ()


if (VTC_GRAPHVIZ_DOT_EXECUTABLE)
	set( VTC_CONVERTER_DEFINES "${VTC_CONVERTER_DEFINES}" "VTC_GRAPHVIZ_DOT_EXECUTABLE=\"${VTC_GRAPHVIZ_DOT_EXECUTABLE}\"" )
else ()
	message( WARNING "GraphViz is not found, download and instal library from https://www.graphviz.org/" )
endif ()
