include_guard(GLOBAL)

option(AW_CLANG_TIDY   "Run clang-tidy while compiling" OFF)


if (AW_CLANG_TIDY)
	find_program(AW_CLANG_TIDY_PROGRAM NAMES clang-tidy REQUIRED)

	if (NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
		message(WARNING
			"AW_CLANG_TIDY works best with clang; building with "
			"${CMAKE_CXX_COMPILER_ID} may produce spurious diagnostics.")
	endif()

	set(CMAKE_CXX_CLANG_TIDY ${AW_CLANG_TIDY_PROGRAM})

	message(STATUS "AW_CLANG_TIDY_PROGRAM: ${AW_CLANG_TIDY_PROGRAM}")
endif()
