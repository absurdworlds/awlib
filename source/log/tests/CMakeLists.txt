
set(SOURCES
    log_filter.c++
    log_tester.h)

add_executable(test_log ${SOURCES})
target_link_libraries(test_log awlog awplatform)
