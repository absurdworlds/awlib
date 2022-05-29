
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/aw/platform/*.h)
if (AW_CAPABILITIES_WIN32)
    set(SOURCES os_version.c++ demangle.c++)
endif()

if (AW_CAPABILITIES_POSIX)
    set(SOURCES os_version.c++ demangle.c++ posix/process.c++)
endif()

add_definitions(-DAW_MODULE_PLATFORM)

add_library(awplatform SHARED ${HEADERS} ${SOURCES})
target_link_libraries(awplatform
    PUBLIC awutils)

add_subdirectory(tests)
