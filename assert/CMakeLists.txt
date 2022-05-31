
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

# awassert interface library
set(HEADERS
	include/aw/assert/assert_action.h
	include/aw/assert/assert_handler.h
	include/aw/assert/debugger.h
	include/aw/assert/export.h
	include/aw/assert.h)

if (AW_ENABLE_ASSERT)
	set(INTERFACE_LIB awassert_interface)
else()
	set(INTERFACE_LIB awassert)
endif()

add_library(awassert_interface INTERFACE ${HEADERS})

target_compile_definitions(${INTERFACE_LIB}
	INTERFACE
		aw_default_assert_level=${AW_DEFAULT_ASSERT_LEVEL}
		aw_maximum_assert_level=${AW_MAXIMUM_ASSERT_LEVEL})

target_include_directories(awassert_interface
	INTERFACE
	    ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(awassert_interface
	INTERFACE
	    aw
		awutils
		awtypes
		awplatform)


# awassert implementation
add_library(awassert SHARED
	source/assert_fail.c++
	source/assert_handler.c++
)
target_compile_definitions(awassert
	PRIVATE
	    AW_MODULE_ASSERT)

if (AW_CAPABILITIES_WIN32)
	target_sources(awassert PRIVATE source/win32/debugger.c++)
endif()

if (AW_CAPABILITIES_POSIX)
	target_sources(awassert PRIVATE source/posix/debugger.c++)
endif()

target_link_libraries(awassert
	PUBLIC
	    awassert_interface
	)

add_subdirectory(tests)
