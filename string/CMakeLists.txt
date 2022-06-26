
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
set(SOURCES compose.cpp)

add_library(awstring SHARED ${HEADERS} ${SOURCES})

set_target_properties(awstring PROPERTIES LINKER_LANGUAGE CXX)

target_compile_definitions(awstring PRIVATE AW_MODULE_STRING)
target_include_directories(awstring PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(awstring
    PUBLIC
        awalgo
        awutils # TODO: move string headers here
        awtypes)

if (AW_MAKE_TESTS)
	add_subdirectory(tests)
endif()
