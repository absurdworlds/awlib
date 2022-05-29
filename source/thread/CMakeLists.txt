
file(GLOB_RECURSE HEADERS ${AW_HEADER_DIR}/aw/thread/*.h)
set(SOURCES worker.c++)

add_definitions(-DAW_MODULE_THREAD)

add_library(awthread SHARED ${HEADERS} ${SOURCES})
set_target_properties(awthread PROPERTIES LINKER_LANGUAGE CXX)

#add_subdirectory(tests)
