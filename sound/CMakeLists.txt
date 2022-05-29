
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
set(SOURCES
    wav_reader.cpp
    chunks.h)


add_library(awaudio SHARED ${HEADERS} ${SOURCES})
set_target_properties(awaudio PROPERTIES LINKER_LANGUAGE CXX)
target_compile_definitions(awaudio PRIVATE AW_MODULE_SOUND)
target_include_directories(awaudio PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(awaudio
    PUBLIC
        awlog_interface
        awio)

add_subdirectory(tests)
