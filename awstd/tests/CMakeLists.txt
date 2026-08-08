function(awstd_add_test NAME)
	set(TARGET test_awstd_${NAME})

	add_executable(${TARGET} ${ARGN})

	target_link_libraries(${TARGET} PRIVATE awstd)
	target_include_directories(${TARGET} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

	set_target_properties(${TARGET}
		PROPERTIES
			CXX_STANDARD ${AWSTD_CXX_STANDARD}
			CXX_STANDARD_REQUIRED ON
			CXX_EXTENSIONS OFF
	)

	add_test(
		NAME ${TARGET}
		COMMAND ${TARGET}
		WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
endfunction()

awstd_add_test(nullptr     nullptr.c++)
awstd_add_test(string_view string_view.c++)
awstd_add_test(unicode     unicode.c++)
awstd_add_test(filesystem  filesystem.c++)

# since C++17 <string_view> and <filesystem> are provided by the standard
# library itself, so the shims cannot (and need not) be used
if (AWSTD_CXX_YEAR LESS 2017)
	awstd_add_test(shims shims.c++)
	target_link_libraries(test_awstd_shims PRIVATE awstd_shims)
endif()
