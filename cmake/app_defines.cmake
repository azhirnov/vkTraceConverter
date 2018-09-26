# pass path to framegraph and application to the source code

set( VTC_CONVERTER_DEFINES	"${VTC_CONVERTER_DEFINES}"
							"VTC_FRAMEGRAPH_SOURCE_PATH=\"${VTC_FRAMEGRAPH_PATH}\""
							"VTC_FRAMEGRAPH_LIBRARY_PATH=\"${FRAMEGRAPH_INSTALL_DIR}/lib\""
							"VTC_FRAMEGRAPH_EXTERNAL_PATH=\"${VTC_FRAMEGRAPH_EXTERNAL_PATH}\""
							"VTC_APPLICATION_SOURCE_PATH=\"${CMAKE_CURRENT_SOURCE_DIR}/..\""
	)
