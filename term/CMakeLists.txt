
set(SOURCES
	csi_parser.c++
)

set(WIN32_SOURCES)

set(POSIX_SOURCES)

if (AW_CAPABILITIES_WIN32)
	list(APPEND SOURCES ${WIN32_SOURCES})
endif()

if (AW_CAPABILITIES_POSIX)
	list(APPEND SOURCES ${POSIX_SOURCES})
endif()

aw_add_library(awterm SHARED
	GLOB_HEADERS
	SOURCES
		${SOURCES}
	EXPORT_NAME
		term
)

target_compile_definitions(awterm PRIVATE AW_MODULE_TERM)
#target_link_libraries(awterm awutils)
