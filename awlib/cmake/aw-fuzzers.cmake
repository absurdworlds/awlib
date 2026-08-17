#
# libFuzzer targets.
#
# Coverage instrumentation has to be on for the whole build, so this
# module has to be included before the first add_subdirectory().
#
# Usage, with the sanitisers on -- a fuzzer without them finds only the
# crashes bad enough to fault on their own:
#     cmake -S . -B build-fuzz -DAW_FUZZERS=ON \
#           -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ \
#           -DAW_SANITIZERS=address,undefined
#     cmake --build build-fuzz
#     ctest --test-dir build-fuzz -R fuzz
#
# ctest replays each target's committed corpus and exits: fast,
# deterministic, and it is what turns a crash found once into a
# regression test. Actual fuzzing is a separate, longer run:
#     build-fuzz/bin/fuzz_hudf fileformat/hudf/fuzz/corpus -max_total_time=60
#
include_guard(GLOBAL)

include(CheckCXXSourceCompiles)

option(AW_FUZZERS "Build libFuzzer fuzz targets" OFF)

if (NOT AW_FUZZERS)
	return()
endif()

if (NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	message(FATAL_ERROR
		"AW_FUZZERS needs clang for -fsanitize=fuzzer, not ${CMAKE_CXX_COMPILER_ID}")
endif()

set(CMAKE_REQUIRED_FLAGS "-fsanitize=fuzzer")
check_cxx_source_compiles([[
	extern "C" int LLVMFuzzerTestOneInput(const unsigned char*, unsigned long) { return 0; }
]] AW_FUZZERS_USABLE)
unset(CMAKE_REQUIRED_FLAGS)
if (NOT AW_FUZZERS_USABLE)
	message(FATAL_ERROR
		"clang cannot build with -fsanitize=fuzzer. On Debian and Ubuntu the "
		"runtime is in libclang-rt-<version>-dev.")
endif()

# The whole library needs the coverage instrumentation, or the fuzzer is
# guessing blind: it is the edge counters that tell it an input reached
# somewhere new. `-no-link` because only the fuzz targets get libFuzzer's
# main(); everything else keeps its own.
add_compile_options(-fsanitize=fuzzer-no-link)

message(STATUS "Fuzzers: enabled")

# aw_add_fuzzer(NAME SOURCES <list> [CORPUS <dir>])
#
# Builds a libFuzzer target and registers a ctest test that replays
# CORPUS through it. The corpus doubles as the seed for real fuzzing runs
# and as the regression suite for whatever fuzzing has already found.
function(aw_add_fuzzer NAME)
	set(options)
	set(arguments CORPUS)
	set(multivalue SOURCES)
	cmake_parse_arguments(PARSE_ARGV 1 ARG "${options}" "${arguments}" "${multivalue}")

	add_executable(${NAME} ${ARG_SOURCES})
	target_link_options(${NAME} PRIVATE -fsanitize=fuzzer)

	if (NOT ARG_CORPUS)
		return()
	endif()

	set(corpus "${CMAKE_CURRENT_SOURCE_DIR}/${ARG_CORPUS}")
	if (NOT IS_DIRECTORY "${corpus}")
		message(FATAL_ERROR "aw_add_fuzzer(${NAME}): no corpus at ${corpus}")
	endif()

	# Publish it under a predictable name, so that a longer fuzzing run --
	# CI's, or one by hand -- can pair each binary with its corpus without
	# knowing which module the target came from. A link rather than a copy,
	# so that adding a file to the corpus does not need a reconfigure.
	set(published "${CMAKE_BINARY_DIR}/fuzz-corpus/${NAME}")
	file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/fuzz-corpus")
	file(CREATE_LINK "${corpus}" "${published}" SYMBOLIC RESULT link_result)
	if (NOT link_result EQUAL 0)
		file(COPY "${corpus}/" DESTINATION "${published}")
	endif()

	# Handing libFuzzer a directory runs every file in it once and exits,
	# rather than starting to fuzz. -runs=0 keeps it from generating any
	# input of its own, so the test is the same on every machine.
	add_test(
		NAME ${NAME}
		COMMAND ${NAME} "${corpus}" -runs=0
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

	if (AW_SANITIZER_TEST_ENVIRONMENT)
		set_property(TEST ${NAME} APPEND
			PROPERTY ENVIRONMENT ${AW_SANITIZER_TEST_ENVIRONMENT})
	endif()
endfunction()
