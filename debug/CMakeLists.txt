
aw_add_library(awdebug SHARED
	GLOB_HEADERS
	SOURCES
		demangle.c++
	EXPORT_NAME
		debug
)

target_compile_definitions(awdebug PRIVATE AW_MODULE_DEBUG)
target_link_libraries(awdebug
	PUBLIC
		awconfig
		awbase)

if (AW_CAPABILITIES_POSIX)
	target_sources(awdebug PRIVATE posix/debugger.c++)
endif()

if (AW_CAPABILITIES_WIN32)
	target_sources(awdebug PRIVATE win32/debugger.c++)
endif()

if (WIN32)
	# lowercase: mingw ships libdbghelp.a, and cross-linking on Linux
	# is case-sensitive
	target_link_libraries(awdebug
	PRIVATE
		dbghelp
	)
endif()
