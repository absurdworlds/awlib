
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_library(awmeta INTERFACE ${HEADERS})
target_include_directories(awmeta INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)


#add_subdirectory(tests) TODO
