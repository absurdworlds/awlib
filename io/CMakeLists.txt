
set(WIN32_SOURCES
    win32/file.cpp
    win32/mmap.cpp
    win32/winapi_category.cpp
    win32/error_codes.cpp
    win32/path.h
    win32/winapi_helpers.h)

set(POSIX_SOURCES
    posix/file.cpp
    posix/mmap.cpp
    posix/helpers.h)

if (AW_CAPABILITIES_WIN32)
	list(APPEND SOURCES ${WIN32_SOURCES})
endif()

if (AW_CAPABILITIES_POSIX)
	list(APPEND SOURCES ${POSIX_SOURCES})
endif()

aw_add_library(awio SHARED
	GLOB_HEADERS
	SOURCES
		${SOURCES}
	EXPORT_NAME
		io
)

target_compile_definitions(awio PRIVATE AW_MODULE_IO)
target_link_libraries(awio
	awutils
	awstd)
