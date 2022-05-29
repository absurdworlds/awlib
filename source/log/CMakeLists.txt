
file(GLOB_RECURSE HEADERS ${AW_HEADER_DIR}/aw/log/*.h)
file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c++)

add_definitions(-DAW_MODULE_LOG)

add_library(awlog SHARED ${HEADERS} ${SOURCES})
set_target_properties(awlog PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(awlog
    PUBLIC awalgo awutils)

add_subdirectory(tests)
