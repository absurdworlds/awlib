
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_library(awsignals INTERFACE ${HEADERS})
target_include_directories(awsignals INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(awsignals
    INTERFACE
        awtypes)
