
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB SOURCES  argv_parser.c++ murmur_hash3.c++ pool/c++)

add_library(awutils SHARED ${HEADERS} ${SOURCES})
set_target_properties(awutils PROPERTIES LINKER_LANGUAGE CXX)
target_compile_definitions(awutils PRIVATE AW_MODULE_UTILS)
target_include_directories(awutils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(awutils
    PUBLIC awalgo)

add_subdirectory(tests)
