aw_add_library(awconfig INTERFACE
	GLOB_HEADERS
	EXPORT_NAME
		config
)

if (NOT BUILD_SHARED_LIBS)
	target_compile_definitions(awconfig
		INTERFACE
			AW_STATIC_BUILD)
endif()
