
file(GLOB_RECURSE HEADERS ${AW_HEADER_DIR}/aw/doc/*.h)
file(GLOB SOURCES lexer.c++ parser.c++ writer.c++ utility.c++ document.c++)

add_library(awdoc SHARED ${HEADERS} ${SOURCES})
target_compile_definitions(awdoc PRIVATE AW_MODULE_DOC)
set_target_properties(awdoc PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(awdoc
    PUBLIC awutils awio)

add_subdirectory(tests)
