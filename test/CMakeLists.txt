
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_library(awtest INTERFACE ${HEADERS})
target_include_directories(awplatform PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(awtest
    INTERFACE
        awutils
        awplatform)
