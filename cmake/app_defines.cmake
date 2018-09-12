# pass path to framegraph and application to the source code

add_definitions( "-DVT_FRAMEGRAPH_SOURCE_PATH=\"${VT_FRAMEGRAPH_PATH}\"" )
add_definitions( "-DVT_FRAMEGRAPH_LIBRARY_PATH=\"${FRAMEGRAPH_INSTALL_DIR}/lib\"" )
add_definitions( "-DVT_FRAMEGRAPH_EXTERNAL_PATH=\"${VT_FRAMEGRAPH_EXTERNAL_PATH}\"" )

add_definitions( "-DVT_APPLICATION_SOURCE_PATH=\"${CMAKE_CURRENT_SOURCE_DIR}/..\"" )
add_definitions( "${FRAMEGRAPH_DEFINES}" )
