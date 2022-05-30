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


add_library(awassert SHARED
	source/assert_fail.c++
	source/assert_handler.c++
)
target_compile_definitions(awassert
	PRIVATE
	    AW_MODULE_ASSERT)

target_link_libraries(awassert
	PUBLIC
	    awassert_interface
	)

add_subdirectory(tests)
