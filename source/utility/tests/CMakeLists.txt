
set(SOURCES
    utf8toutf16.c++ MurmurHash3.c++ hash_combine.c++
    functional.c++ static_object.c++ on_scope_exit.c++
    ranges_slice.c++ ranges_ipairs.c++ ranges_zip.c++)

add_executable(test_utility ${SOURCES})
target_link_libraries(test_utility
    PRIVATE awutils awplatform awtest)
