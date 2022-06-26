
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
set(SOURCES worker.c++)

add_library(awthread SHARED ${HEADERS} ${SOURCES})
target_include_directories(awthread PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_definitions(awthread PRIVATE AW_MODULE_THREAD)

if (AW_MAKE_TESTS)
	#add_subdirectory(tests)
endif()
