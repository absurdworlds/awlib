
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_library(awtypes INTERFACE ${HEADERS})
target_include_directories(awtypes INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(awtypes
    INTERFACE
        awmeta)

add_subdirectory(tests)
