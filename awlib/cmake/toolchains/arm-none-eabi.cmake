# Cross-compile for bare-metal ARM (Cortex-M, e.g. STM32) with arm-none-eabi-gcc.
#
#   cmake -S . -B build-stm32 -G Ninja \
#         -DCMAKE_TOOLCHAIN_FILE=awlib/cmake/toolchains/arm-none-eabi.cmake \
#         -DAW_ARM_CPU=cortex-m4 -DAW_ARM_FPU=fpv4-sp-d16 -DAW_ARM_FLOAT_ABI=hard
#
# The defaults target an STM32F4 (Cortex-M4F). For Cortex-M0/M3 pass
# -DAW_ARM_FPU=none -DAW_ARM_FLOAT_ABI=soft.

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# There is no runtime to link a test executable against, so probe the
# compiler with a static library instead.
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(AW_ARM_PREFIX    arm-none-eabi   CACHE STRING "Toolchain program prefix")
set(AW_ARM_CPU       cortex-m4       CACHE STRING "Value for -mcpu")
set(AW_ARM_FPU       fpv4-sp-d16     CACHE STRING "Value for -mfpu, or 'none'")
set(AW_ARM_FLOAT_ABI hard            CACHE STRING "Value for -mfloat-abi")

set(CMAKE_C_COMPILER   ${AW_ARM_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${AW_ARM_PREFIX}-g++)
set(CMAKE_ASM_COMPILER ${AW_ARM_PREFIX}-gcc)

set(AW_ARM_FLAGS "-mcpu=${AW_ARM_CPU} -mthumb -mfloat-abi=${AW_ARM_FLOAT_ABI}")
if (NOT AW_ARM_FPU STREQUAL "none")
	string(APPEND AW_ARM_FLAGS " -mfpu=${AW_ARM_FPU}")
endif()

# Sections are split so that the firmware link can garbage-collect
# everything the application does not actually pull in.
string(APPEND AW_ARM_FLAGS " -ffunction-sections -fdata-sections")

set(CMAKE_C_FLAGS_INIT   "${AW_ARM_FLAGS}")
# Bare-metal firmware usually runs without exceptions and RTTI.
set(CMAKE_CXX_FLAGS_INIT "${AW_ARM_FLAGS} -fno-exceptions -fno-rtti")

# Shared libraries and PIC make no sense when linking into a firmware image.
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(CMAKE_POSITION_INDEPENDENT_CODE OFF)

# Look for programs on the host, but headers and libraries in the target root
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
