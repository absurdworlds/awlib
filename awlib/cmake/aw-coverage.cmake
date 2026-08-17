#
# Coverage instrumentation.
#
# Instrumentation is a property of the whole build, so this module has to
# be included before the first add_subdirectory().
#
# Usage:
#     cmake -S . -B build-cov -DAW_COVERAGE=ON
#     cmake --build build-cov --target coverage
#
# The `coverage` target runs the tests and writes a report to
# <build>/coverage, printing a summary as it goes.
#
# GCC and clang each get their own instrumentation and their own report
# tool -- gcov/gcovr and llvm-cov respectively -- rather than clang being
# pushed through gcov emulation, where the .gcno format has to match
# whichever gcov happens to be installed.
#
include_guard(GLOBAL)

option(AW_COVERAGE "Build with coverage instrumentation" OFF)

set(AW_COVERAGE_EXCLUDE ".*/tests?/.*" CACHE STRING
	"Regexes for paths to leave out of the coverage report")

# For the ctest side: aw_add_test() puts this into the tests' ENVIRONMENT.
set(AW_COVERAGE_TEST_ENVIRONMENT "" CACHE INTERNAL "Per-test coverage options")

if (NOT AW_COVERAGE)
	return()
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	message(FATAL_ERROR "AW_COVERAGE supports GCC and clang, not MSVC")
endif()

# Coverage of optimised code maps back to source lines only loosely: the
# inliner and the branch folder rewrite exactly what is being counted.
if (CMAKE_BUILD_TYPE AND NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
	message(WARNING
		"AW_COVERAGE with CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}: the report "
		"will be measuring optimised code. Debug is the useful setting.")
endif()

set(coverage_dir "${CMAKE_BINARY_DIR}/coverage")
file(MAKE_DIRECTORY "${coverage_dir}")

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	# The raw profile format is tied to the compiler that wrote it, so the
	# tools matching this clang are preferred over whatever `llvm-profdata`
	# happens to point at.
	string(REGEX MATCH "^[0-9]+" clang_major "${CMAKE_CXX_COMPILER_VERSION}")
	find_program(AW_LLVM_PROFDATA
		NAMES llvm-profdata-${clang_major} llvm-profdata REQUIRED)
	find_program(AW_LLVM_COV
		NAMES llvm-cov-${clang_major} llvm-cov REQUIRED)

	add_compile_options(-fprofile-instr-generate -fcoverage-mapping -O0 -g)
	add_link_options(-fprofile-instr-generate)

	# Every test writes its own raw profile; %p keeps two tests running
	# under `ctest -j` from writing over each other.
	set(AW_COVERAGE_TEST_ENVIRONMENT
		"LLVM_PROFILE_FILE=${coverage_dir}/%p.profraw"
		CACHE INTERNAL "Per-test coverage options")

	set(report_args
		-DAW_COV_TOOLCHAIN=llvm
		-DAW_COV_PROFDATA=${AW_LLVM_PROFDATA}
		-DAW_COV_LLVM_COV=${AW_LLVM_COV})
else()
	find_program(AW_GCOVR NAMES gcovr REQUIRED)
	find_program(AW_GCOV  NAMES gcov  REQUIRED)

	add_compile_options(--coverage -O0 -g)
	add_link_options(--coverage)

	set(report_args
		-DAW_COV_TOOLCHAIN=gcov
		-DAW_COV_GCOVR=${AW_GCOVR}
		-DAW_COV_GCOV=${AW_GCOV})
endif()

message(STATUS "Coverage: ${CMAKE_CXX_COMPILER_ID}, report in ${coverage_dir}")

# Stale counters from an earlier run would be merged into this one.
add_custom_target(coverage-clean
	COMMAND ${CMAKE_COMMAND}
		-DAW_COV_BUILD_DIR=${CMAKE_BINARY_DIR}
		-DAW_COV_OUTPUT_DIR=${coverage_dir}
		-P "${CMAKE_CURRENT_LIST_DIR}/aw-coverage-clean.cmake"
	VERBATIM
	COMMENT "Discarding previous coverage data")

add_custom_target(coverage
	COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
	COMMAND ${CMAKE_COMMAND}
		-DAW_COV_BUILD_DIR=${CMAKE_BINARY_DIR}
		-DAW_COV_SOURCE_DIR=${CMAKE_SOURCE_DIR}
		-DAW_COV_OUTPUT_DIR=${coverage_dir}
		"-DAW_COV_EXCLUDE=${AW_COVERAGE_EXCLUDE}"
		${report_args}
		-P "${CMAKE_CURRENT_LIST_DIR}/aw-coverage-report.cmake"
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	DEPENDS coverage-clean
	USES_TERMINAL
	VERBATIM
	COMMENT "Running tests and building the coverage report")
