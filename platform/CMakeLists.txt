
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
set(SOURCES os_version.c++ demangle.c++)
if (AW_CAPABILITIES_WIN32)
   # list(APPEND SOURCES win32/process.c++)
endif()

if (AW_CAPABILITIES_POSIX)
    list(APPEND SOURCES posix/process.c++)
endif()


add_library(awplatform SHARED ${HEADERS} ${SOURCES})
target_include_directories(awplatform PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_definitions(awplatform PRIVATE AW_MODULE_PLATFORM)
target_link_libraries(awplatform
    PUBLIC
        awutils)

add_subdirectory(tests)
