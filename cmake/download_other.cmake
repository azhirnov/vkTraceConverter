# download and install other external dependencies


# blake2
if (TRUE)
	add_library( "Extern.blake2" STATIC
			"BLAKE2/sse/blake2.h"
			"BLAKE2/sse/blake2b.c"
			"BLAKE2/sse/blake2s.c"
			"BLAKE2/sse/blake2bp.c"
			"BLAKE2/sse/blake2sp.c"
		)

	target_include_directories( "Extern.blake2" PUBLIC "BLAKE2/sse" )
	target_compile_definitions( "Extern.blake2" PUBLIC "-D__SSE2__" )

	set_property( TARGET "Extern.blake2" PROPERTY FOLDER "External" )
	
    set( VTC_CONVERTER_LIBRARIES "${VTC_CONVERTER_LIBRARIES}" "Extern.blake2" )
endif ()

