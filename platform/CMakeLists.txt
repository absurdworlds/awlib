set(SOURCES os_version.c++ demangle.c++)
if (AW_CAPABILITIES_WIN32)
   # list(APPEND SOURCES win32/process.c++)
endif()

if (AW_CAPABILITIES_POSIX)
    list(APPEND SOURCES posix/process.c++)
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
		aw
		awtypes
	PRIVATE
		awalgo
		awutils)
