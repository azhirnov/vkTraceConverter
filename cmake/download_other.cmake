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

