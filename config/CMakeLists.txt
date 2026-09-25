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

option(AW_NO_BUILTINS "Build without compiler built-in functions." OFF)
if (AW_NO_BUILTINS)
	target_compile_definitions(awconfig
		INTERFACE
			AW_NO_BUILTINS=1)
endif()

option(AW_NO_EXTENSIONS "Build without compiler language extensions." OFF)
if (AW_NO_EXTENSIONS)
	target_compile_definitions(awconfig
		INTERFACE
			AW_NO_EXTENSIONS=1)
endif()
