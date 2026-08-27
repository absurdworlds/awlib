# Cross-compile for Windows with mingw-w64.
#
#   cmake -S . -B build-mingw -G Ninja \
#         -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/mingw-w64.cmake

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

set(AW_MINGW_TARGET x86_64-w64-mingw32 CACHE STRING "mingw-w64 target triple")

set(CMAKE_C_COMPILER   ${AW_MINGW_TARGET}-gcc)
set(CMAKE_CXX_COMPILER ${AW_MINGW_TARGET}-g++)
set(CMAKE_RC_COMPILER  ${AW_MINGW_TARGET}-windres)

set(CMAKE_FIND_ROOT_PATH /usr/${AW_MINGW_TARGET})

# Look for programs on the host, but headers and libraries in the target root
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
