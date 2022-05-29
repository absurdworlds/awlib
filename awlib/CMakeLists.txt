
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_library(awlib INTERFACE ${HEADERS})
target_include_directories(awlib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
