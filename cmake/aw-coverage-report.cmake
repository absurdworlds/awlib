#
# Builds the coverage report. Run by the `coverage` target, after ctest,
# via `cmake -P`; not meant to be included.
#
# Expects: AW_COV_TOOLCHAIN (llvm|gcov), AW_COV_BUILD_DIR,
# AW_COV_SOURCE_DIR, AW_COV_OUTPUT_DIR, AW_COV_EXCLUDE, and the tool paths
# for whichever toolchain is in use.
#
cmake_minimum_required(VERSION 3.19)

if (AW_COV_TOOLCHAIN STREQUAL "llvm")
	# One raw profile per test process, written where LLVM_PROFILE_FILE said.
	file(GLOB profraw "${AW_COV_OUTPUT_DIR}/*.profraw")
	if (NOT profraw)
		message(FATAL_ERROR
			"No .profraw files in ${AW_COV_OUTPUT_DIR}. Did the tests run?")
	endif()

	set(profdata "${AW_COV_OUTPUT_DIR}/merged.profdata")
	execute_process(
		COMMAND ${AW_COV_PROFDATA} merge -sparse ${profraw} -o ${profdata}
		RESULT_VARIABLE result)
	if (NOT result EQUAL 0)
		message(FATAL_ERROR "llvm-profdata merge failed: ${result}")
	endif()

	# awlib builds shared by default, so the counters for the library live
	# in the .so files rather than in the test binaries that ran. Both have
	# to be handed to llvm-cov, or the report covers only the test sources.
	# Static libraries are not listed: llvm-cov does not read archives, and
	# it does not need to -- a static library's code, and its coverage
	# mapping with it, is copied into whichever executable links it. A
	# static library that no test links has no coverage anywhere, which is
	# the honest answer for it.
	file(GLOB binaries "${AW_COV_BUILD_DIR}/bin/*")
	file(GLOB libraries
		"${AW_COV_BUILD_DIR}/lib/*.so"
		"${AW_COV_BUILD_DIR}/lib/*.dylib")

	# The tests leave artefacts of their own next to the binaries, and
	# llvm-cov stops at the first thing that is not an object file. Decide
	# by the magic number rather than by name: ELF, or Mach-O in any of the
	# forms it comes in.
	set(objects "")
	foreach (candidate IN LISTS binaries libraries)
		if (IS_DIRECTORY "${candidate}")
			continue()
		endif()
		file(READ "${candidate}" magic LIMIT 4 HEX)
		if (magic MATCHES "^(7f454c46|cffaedfe|cefaedfe|feedfacf|feedface|cafebabe)")
			list(APPEND objects "${candidate}")
		endif()
	endforeach()
	if (NOT objects)
		message(FATAL_ERROR "No instrumented binaries under ${AW_COV_BUILD_DIR}")
	endif()

	# llvm-cov takes the first object positionally and the rest with -object
	list(POP_FRONT objects first)
	set(object_args "")
	foreach (obj IN LISTS objects)
		list(APPEND object_args -object ${obj})
	endforeach()

	set(ignore_args "")
	foreach (pattern IN LISTS AW_COV_EXCLUDE)
		list(APPEND ignore_args "-ignore-filename-regex=${pattern}")
	endforeach()
	# Nobody is trying to raise coverage of libstdc++.
	list(APPEND ignore_args "-ignore-filename-regex=^/usr/.*")

	execute_process(
		COMMAND ${AW_COV_LLVM_COV} show ${first} ${object_args}
			-instr-profile=${profdata}
			${ignore_args}
			-format=html
			-show-branches=count
			-output-dir=${AW_COV_OUTPUT_DIR}/html
		RESULT_VARIABLE result)
	if (NOT result EQUAL 0)
		message(FATAL_ERROR "llvm-cov show failed: ${result}")
	endif()

	execute_process(
		COMMAND ${AW_COV_LLVM_COV} report ${first} ${object_args}
			-instr-profile=${profdata}
			${ignore_args}
		RESULT_VARIABLE result)
	if (NOT result EQUAL 0)
		message(FATAL_ERROR "llvm-cov report failed: ${result}")
	endif()

	set(report_path "${AW_COV_OUTPUT_DIR}/html/index.html")
else()
	set(exclude_args "")
	foreach (pattern IN LISTS AW_COV_EXCLUDE)
		list(APPEND exclude_args --exclude "${pattern}")
	endforeach()

	execute_process(
		COMMAND ${AW_COV_GCOVR}
			--root ${AW_COV_SOURCE_DIR}
			${AW_COV_BUILD_DIR}
			--gcov-executable ${AW_COV_GCOV}
			${exclude_args}
			# Counters from headers included in many places are attributed
			# to each of them; without this gcovr calls that a conflict and
			# drops the file.
			--merge-mode-functions=merge-use-line-min
			--decisions
			--print-summary
			--html-details ${AW_COV_OUTPUT_DIR}/index.html
		RESULT_VARIABLE result)
	if (NOT result EQUAL 0)
		message(FATAL_ERROR "gcovr failed: ${result}")
	endif()

	set(report_path "${AW_COV_OUTPUT_DIR}/index.html")
endif()

message(STATUS "Coverage report: ${report_path}")
