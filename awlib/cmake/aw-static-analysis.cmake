#
# Static analysis.
#
# Every analyser here is off by default: they cost anywhere from a little
# to a lot of build time, and are meant to be run by CI or on demand
# rather than on every local build.
#
# Usage:
#     cmake -S . -B build -DAW_CLANG_TIDY=ON -DCMAKE_CXX_COMPILER=clang++
#     cmake -S . -B build -DAW_GCC_ANALYZER=ON
#     cmake -S . -B build -DAW_CPPCHECK=ON
#
# This module has to be included before the first add_subdirectory().
#
include_guard(GLOBAL)

option(AW_CLANG_TIDY   "Run clang-tidy (which includes the clang static analyser) while compiling" OFF)
option(AW_GCC_ANALYZER "Run GCC's -fanalyzer while compiling" OFF)
option(AW_CPPCHECK     "Run cppcheck while compiling" OFF)
option(AW_IWYU         "Run include-what-you-use while compiling" OFF)

option(AW_ANALYZER_WERROR "Turn analyser findings into build errors" OFF)

# Wanted by clang-tidy, run-clang-tidy, iwyu and every editor going. Only
# a default: -DCMAKE_EXPORT_COMPILE_COMMANDS=OFF still wins.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Write compile_commands.json")

if (AW_CLANG_TIDY)
	find_program(AW_CLANG_TIDY_PROGRAM NAMES clang-tidy REQUIRED)

	# clang-tidy parses the compile command with clang's own driver, so a
	# GCC-only flag in there makes it complain about every single file.
	if (NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
		message(WARNING
			"AW_CLANG_TIDY works best with clang; building with "
			"${CMAKE_CXX_COMPILER_ID} may produce spurious diagnostics.")
	endif()

	set(clang_tidy_command "${AW_CLANG_TIDY_PROGRAM}")
	# The checks themselves live in .clang-tidy at the top of the tree.
	list(APPEND clang_tidy_command "--extra-arg=-Wno-unknown-warning-option")
	if (AW_ANALYZER_WERROR)
		list(APPEND clang_tidy_command "--warnings-as-errors=*")
	endif()

	set(CMAKE_CXX_CLANG_TIDY ${clang_tidy_command})
	message(STATUS "clang-tidy: ${AW_CLANG_TIDY_PROGRAM}")
endif()

if (AW_GCC_ANALYZER)
	if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		message(FATAL_ERROR "AW_GCC_ANALYZER needs GCC, not ${CMAKE_CXX_COMPILER_ID}")
	endif()

	# GCC's analyser was written for C and is still labelled experimental
	# for C++, so it is worth being precise about what it cannot do here.
	# Measured over this tree, one check accounts for every false positive
	# and the rest are clean:
	#
	#   use-of-uninitialized-value
	#       The analyser does not know that a libc function fills in the
	#       buffer it is handed, so a struct passed to uname(), or the
	#       string returned by __cxa_demangle(), reads as uninitialised.
	#
	#   null-argument
	#       Converting a captureless lambda to a function pointer makes GCC
	#       synthesise a _FUN thunk that calls operator() with a null
	#       `this` -- which is fine, as operator() cannot touch it, but the
	#       analyser sees a null argument to a non-null parameter. The
	#       lambdas in aw::lua bind to Lua's C API exactly this way.
	#
	# The memory-pairing checks (malloc-leak, double-free,
	# mismatching-deallocation, use-after-free) and the null-dereference
	# ones were each checked against the library sources with the
	# suppression lifted, and reported nothing -- they stay on.
	add_compile_options(
		-fanalyzer
		-Wno-analyzer-use-of-uninitialized-value
		-Wno-analyzer-null-argument
	)

	# The analyser gives up on code above a complexity budget and says so.
	# On C++ templates it says so often, and it is a statement about the
	# analyser rather than about the code, so it is never an error.
	add_compile_options(-Wno-analyzer-too-complex)

	if (AW_ANALYZER_WERROR)
		# GCC has no -Werror=analyzer-*, and a blanket -Werror would
		# promote every unrelated compiler warning as well, so the
		# analyser's diagnostics are promoted one at a time. The list is
		# `g++ --help=warnings | grep -o '\-Wanalyzer-[a-z-]*'`, less the
		# three above that are not findings about awlib's code.
		set(analyzer_warnings
			allocation-size deref-before-check double-fclose double-free
			exposure-through-output-file exposure-through-uninit-copy
			fd-access-mode-mismatch fd-double-close fd-leak
			fd-phase-mismatch fd-type-mismatch fd-use-after-close
			fd-use-without-check file-leak free-of-non-heap
			infinite-recursion jump-through-null malloc-leak
			mismatching-deallocation null-dereference
			out-of-bounds possible-null-argument possible-null-dereference
			putenv-of-auto-var shift-count-negative shift-count-overflow
			stale-setjmp-buffer tainted-allocation-size tainted-array-index
			tainted-divisor tainted-offset tainted-size
			unsafe-call-within-signal-handler use-after-free
			use-of-pointer-in-stale-stack-frame va-arg-type-mismatch
			va-list-exhausted va-list-leak va-list-use-after-va-end
			write-to-const write-to-string-literal)

		foreach (warning IN LISTS analyzer_warnings)
			add_compile_options(-Werror=analyzer-${warning})
		endforeach()
	endif()

	message(STATUS "GCC analyzer: enabled")
endif()

if (AW_CPPCHECK)
	find_program(AW_CPPCHECK_PROGRAM NAMES cppcheck REQUIRED)

	# cppcheck does not inherit the compiler's built-in macros, so without
	# this <aw/config.h> picks no compiler at all, never includes the
	# aw/config/*.h that defines AW_ATTRIBUTE, and every use of an export
	# macro becomes an "unknown macro" error. Clang defines __GNUC__ too,
	# and the gcc and clang variants define AW_ATTRIBUTE identically.
	if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		set(cppcheck_compiler "-D_MSC_VER")
	elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
		set(cppcheck_compiler "-D__clang__" "-D__GNUC__")
	else()
		set(cppcheck_compiler "-D__GNUC__")
	endif()

	set(cppcheck_command
		"${AW_CPPCHECK_PROGRAM}"
		${cppcheck_compiler}
		"--enable=warning,performance,portability"
		# Without this, everything the headers pull in is reported as
		# "cannot be resolved", drowning the actual findings.
		"--suppress=missingIncludeSystem"
		# cppcheck otherwise re-analyses each file once per combination of
		# the #ifdefs it contains, which on this codebase is thousands of
		# passes and a "too many configs" complaint for nearly every file.
		"--max-configs=1"
		# Honour // cppcheck-suppress comments in the source.
		"--inline-suppr"
		"--suppressions-list=${CMAKE_CURRENT_LIST_DIR}/cppcheck-suppressions.txt"
		"--library=std"
		"--quiet")

	if (AW_ANALYZER_WERROR)
		list(APPEND cppcheck_command "--error-exitcode=1")
	endif()

	set(CMAKE_CXX_CPPCHECK ${cppcheck_command})
	message(STATUS "cppcheck: ${AW_CPPCHECK_PROGRAM}")
endif()

if (AW_IWYU)
	find_program(AW_IWYU_PROGRAM NAMES include-what-you-use iwyu REQUIRED)
	set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "${AW_IWYU_PROGRAM}")
	message(STATUS "include-what-you-use: ${AW_IWYU_PROGRAM}")
endif()
