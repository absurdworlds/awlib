
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_library(aw INTERFACE ${HEADERS})
target_include_directories(aw INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
