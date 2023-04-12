
if (CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
	set(LEVEL "debug")
else()
	set(LEVEL "release")
endif()

set(LEVELS "off;release;debug;audit")

set(AW_MAXIMUM_ASSERT_LEVEL "${LEVEL}" CACHE STRING "Override assert level")
set(AW_DEFAULT_ASSERT_LEVEL "release"  CACHE STRING "Override assert level for aw_assert macro")

set_property(CACHE AW_MAXIMUM_ASSERT_LEVEL PROPERTY STRINGS ${LEVELS})
set_property(CACHE AW_DEFAULT_ASSERT_LEVEL PROPERTY STRINGS ${LEVELS})

aw_add_library(awassert SHARED
	HEADERS
		include/aw/assert/assert_action.h
		include/aw/assert/assert_handler.h
		include/aw/assert/debugger.h
		include/aw/assert/export.h
		include/aw/assert.h
	SOURCES
		source/assert_fail.c++
		source/assert_handler.c++
	EXPORT_NAME
		assert
)

if (AW_CAPABILITIES_WIN32)
	target_sources(awassert
		PRIVATE
			source/win32/debugger.c++
			source/win32/assert_fail.c++
	)
endif()

if (AW_CAPABILITIES_POSIX)
	target_sources(awassert
		PRIVATE
			source/posix/debugger.c++)
endif()

target_compile_definitions(awassert
	INTERFACE
		aw_default_assert_level=${AW_DEFAULT_ASSERT_LEVEL}
		aw_maximum_assert_level=${AW_MAXIMUM_ASSERT_LEVEL}
	PRIVATE
		AW_MODULE_ASSERT
	)

target_link_libraries(awassert
	PUBLIC
		aw
		awutils
		awtypes
		awstring
		awstd
	PRIVATE
		awplatform # TODO: remove dependency on awplatform
	)
