set(SOURCES os_version.c++ demangle.c++)

set(WIN32_SOURCES
	win32/debugger.c++
	win32/error_codes.c++
	win32/file.c++
	win32/mmap.c++
	win32/path.h
	win32/process.c++
	win32/winapi_category.c++
	win32/winapi_helpers.h)

set(POSIX_SOURCES
	posix/debugger.c++
	posix/file.c++
	posix/helpers.h
	posix/mmap.c++)

# There are no processes in WASM
if(NOT EMSCRIPTEN)
	list(APPEND POSIX_SOURCES posix/process.c++)
endif()

if (AW_CAPABILITIES_WIN32)
	list(APPEND SOURCES ${WIN32_SOURCES})
endif()

if (AW_CAPABILITIES_POSIX)
	list(APPEND SOURCES ${POSIX_SOURCES})
endif()

aw_add_library(awplatform SHARED
	GLOB_HEADERS
	SOURCES
		${SOURCES}
	EXPORT_NAME
		platform
)

target_compile_definitions(awplatform PRIVATE AW_MODULE_PLATFORM)
target_link_libraries(awplatform
	PUBLIC
		awconfig
		awbase
	PRIVATE
		awutils)

if (WIN32)
	# lowercase: mingw ships libdbghelp.a, and cross-linking on Linux
	# is case-sensitive
	target_link_libraries(awplatform
	PRIVATE
		dbghelp
	)
endif()
