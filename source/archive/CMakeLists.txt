
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_library(awarchive INTERFACE ${HEADERS})
target_include_directories(awarchive INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(awarchive
    INTERFACE
        awtypes)

add_subdirectory(test) #TODO: rename to tests for consistency
