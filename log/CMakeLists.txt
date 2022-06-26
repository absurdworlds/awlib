
# awlog interface library: linking with awlog is optional in case user
# wants to provide their own logger implementation
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
add_library(awlog_interface INTERFACE ${HEADERS})
target_include_directories(awlog_interface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# awlog shared library: provides common logger implementations
add_library(awlog SHARED
    log_base.c++
    ostream_logger.c++)

target_compile_definitions(awlog PRIVATE AW_MODULE_LOG)
target_link_libraries(awlog
    PUBLIC
        awlog_interface
        awalgo
        awutils)

if (AW_MAKE_TESTS)
	add_subdirectory(tests)
endif()
