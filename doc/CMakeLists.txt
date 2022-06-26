
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB SOURCES lexer.c++ parser.c++ writer.c++ utility.c++ document.c++)

add_library(awdoc SHARED ${HEADERS} ${SOURCES})
target_compile_definitions(awdoc PRIVATE AW_MODULE_DOC)
target_include_directories(awdoc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(awdoc PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(awdoc
    PUBLIC
        awlog_interface
        awutils
        awio)

if (AW_MAKE_TESTS)
	add_subdirectory(tests)
endif()
