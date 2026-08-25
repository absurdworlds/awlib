# Cross-compile for bare-metal ARM (Cortex-M, e.g. STM32) with arm-none-eabi-gcc.
#
#   # STM32G0B1 (Cortex-M0+, no FPU)
#   cmake -S . -B build-g0 -G Ninja \
#         -DCMAKE_TOOLCHAIN_FILE=awlib/cmake/toolchains/arm-none-eabi.cmake \
#         -DAW_ARM_CPU=cortex-m0plus
#
#   # STM32F405 (Cortex-M4F, single-precision FPU)
#   cmake -S . -B build-f4 -G Ninja \
#         -DCMAKE_TOOLCHAIN_FILE=awlib/cmake/toolchains/arm-none-eabi.cmake \
#         -DAW_ARM_CPU=cortex-m4 -DAW_ARM_FPU=fpv4-sp-d16 -DAW_ARM_FLOAT_ABI=hard
#
# AW_ARM_CPU has no default and cannot be detected: nothing about the host,
# the compiler or the build tree says which chip the image will be flashed
# onto, and arm-none-eabi-gcc invoked without -mcpu silently targets ARMv4T
# (ARM7TDMI), which no Cortex-M part can execute. So it has to be stated.
#
# If the flags already come from somewhere else -- a CubeMX export, an
# stm32-cmake toolchain, PlatformIO, Zephyr, or a parent project that puts
# -mcpu in CMAKE_C_FLAGS -- do not use this file at all. awlib selects its
# bare-metal configuration from CMAKE_SYSTEM_NAME=Generic, so it builds
# correctly under any toolchain that sets that.

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# There is no runtime to link a test executable against, so probe the
# compiler with a static library instead.
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(AW_ARM_PREFIX    arm-none-eabi CACHE STRING "Toolchain program prefix")
set(AW_ARM_CPU       ""            CACHE STRING "Value for -mcpu, e.g. cortex-m0plus. Required.")
set(AW_ARM_FPU       "auto"        CACHE STRING "Value for -mfpu; 'auto' lets -mcpu decide")
set(AW_ARM_FLOAT_ABI "soft"        CACHE STRING "Value for -mfloat-abi")

# try_compile() re-runs this file in a scratch project that inherits only a
# fixed set of variables, so the cache entries above have to be named here or
# the compiler probe is configured with different flags than the real build.
list(APPEND CMAKE_TRY_COMPILE_PLATFORM_VARIABLES
	AW_ARM_PREFIX AW_ARM_CPU AW_ARM_FPU AW_ARM_FLOAT_ABI
	CMAKE_C_FLAGS CMAKE_CXX_FLAGS)

set(CMAKE_C_COMPILER   ${AW_ARM_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${AW_ARM_PREFIX}-g++)
set(CMAKE_ASM_COMPILER ${AW_ARM_PREFIX}-gcc)

# Respect an -mcpu that was passed in directly rather than adding a second one.
if ("${CMAKE_C_FLAGS} ${CMAKE_CXX_FLAGS}" MATCHES "-mcpu=")
	set(AW_ARM_FLAGS "")
elseif (AW_ARM_CPU STREQUAL "")
	message(FATAL_ERROR
		"AW_ARM_CPU is not set, and no -mcpu was given in CMAKE_C_FLAGS or "
		"CMAKE_CXX_FLAGS.\n"
		"Without it the compiler targets ARMv4T, which will not boot on a "
		"Cortex-M part.\n"
		"Pass the core of the chip you are building for, for example:\n"
		"  -DAW_ARM_CPU=cortex-m0plus                     (STM32C0/G0/L0)\n"
		"  -DAW_ARM_CPU=cortex-m0                         (STM32F0)\n"
		"  -DAW_ARM_CPU=cortex-m3                         (STM32F1/F2/L1)\n"
		"  -DAW_ARM_CPU=cortex-m4 -DAW_ARM_FPU=fpv4-sp-d16 -DAW_ARM_FLOAT_ABI=hard\n"
		"                                                 (STM32F3/F4/G4/L4)")
else()
	set(AW_ARM_FLAGS "-mcpu=${AW_ARM_CPU} -mthumb -mfloat-abi=${AW_ARM_FLOAT_ABI}")
	# 'auto' omits -mfpu, leaving the choice to -mcpu. Naming an FPU that the
	# selected core does not have is an error, so there is no safe default
	# other than saying nothing.
	if (NOT AW_ARM_FPU STREQUAL "auto" AND NOT AW_ARM_FPU STREQUAL "none")
		string(APPEND AW_ARM_FLAGS " -mfpu=${AW_ARM_FPU}")
	endif()
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
