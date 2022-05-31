file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_library(awassert_interface INTERFACE ${HEADERS})

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
