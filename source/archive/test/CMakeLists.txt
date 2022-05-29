
set(SOURCES
    archive.c++
    test_archive.h)

add_executable(test_archive ${SOURCES})
target_link_libraries(test_archive awarchive)
