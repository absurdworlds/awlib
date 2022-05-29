
set(SOURCES
    traits_promote.c++ traits_is_iterable.c++
    variant.c++ queue.c++ flat_map.c++
    circular_buffer.c++
    string_view.c++ array_view.c++
    tmpflag.c++)

add_executable(test_types ${SOURCES})
target_link_libraries(test_types
    PRIVATE awtypes awtest)
