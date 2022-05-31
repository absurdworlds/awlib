
set(SOURCES os_version.c++)


if (AW_CAPABILITIES_POSIX) # TODO
	list(APPEND SOURCES demangle.x86_64abi.c++)
endif()


add_executable(test_platform ${SOURCES})
target_link_libraries(test_platform
	PRIVATE
		awplatform
		awtest)
