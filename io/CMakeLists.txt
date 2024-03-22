
set(WIN32_SOURCES
	win32/error_codes.c++
	win32/file.c++
	win32/mmap.c++
	win32/path.h
	win32/process.c++
	win32/winapi_category.c++
	win32/winapi_helpers.h)

set(POSIX_SOURCES
	posix/file.c++
	posix/helpers.h
	posix/mmap.c++
	posix/process.c++)

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
target_link_libraries(awio awutils)
