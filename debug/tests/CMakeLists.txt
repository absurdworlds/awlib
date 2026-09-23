
set(SOURCES
	debugger.c++
)

if (AW_CAPABILITIES_POSIX) # TODO
	list(APPEND SOURCES demangle.x86_64abi.c++)
endif()

aw_add_test(test_debug
	SOURCES
		${SOURCES}
)

target_link_libraries(test_debug
	PRIVATE
		awdebug
		awtest
		awtest_main)
