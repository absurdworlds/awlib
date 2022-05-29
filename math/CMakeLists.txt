
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_library(awmath INTERFACE ${HEADERS})
target_include_directories(awmath INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(awmath
    INTERFACE
        awtypes)

#set_target_properties(awalgorithm PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(tests)
