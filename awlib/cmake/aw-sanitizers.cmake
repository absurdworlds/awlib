include_guard(GLOBAL)

include(CheckCXXSourceCompiles)

set(AW_SANITIZERS "" CACHE STRING
	"Sanitizers to build with. Allowed options: address, undefined, thread, memory, leak")
option(AW_SANITIZER_FAIL_FAST "Make all sanitizer diagnostics fatal" OFF)

# List of known sanitizers
set(AW_SANITIZERS_KNOWN address undefined thread memory leak)
# List of sanitizers that don't play well with each other
set(AW_SANITIZERS_EXCLUSIVE address thread memory)
# List of actually supported sanitizers
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set(AW_SANITIZERS_SUPPORTED address)
else()
	set(AW_SANITIZERS_SUPPORTED ${AW_SANITIZERS_KNOWN})
endif()

# For the ctest side: aw_add_test() puts this into the tests' ENVIRONMENT.
set(AW_SANITIZER_TEST_ENVIRONMENT "" CACHE INTERNAL "Runtime options for the sanitizers in use")

# Resolved while this file is read, so that it survives being used from a
# function and does not depend on who included the module.
set(AW_SANITIZER_SUPPRESSION_DIR "${CMAKE_CURRENT_LIST_DIR}/sanitizers")


# Parses AW_SANITIZERS, check it for errors, and store the normalised
# list of sanitizers in ${out_var}.
function(_aw_validate_sanitizers out_var)
	# Accept "address,undefined" as well as "address;undefined"
	string(REPLACE "," ";" sanitizers "${AW_SANITIZERS}")

	if (NOT sanitizers)
		return()
	endif()

	foreach (san IN LISTS sanitizers)
		if (NOT san IN_LIST AW_SANITIZERS_KNOWN)
			message(FATAL_ERROR
				"Unknown sanitizer '${san}'. Allowed options: ${AW_SANITIZERS_KNOWN}")
		endif()
		if (NOT san IN_LIST AW_SANITIZERS_SUPPORTED)
			message(FATAL_ERROR
				"${CMAKE_CXX_COMPILER_ID} does not support '${san}'. Supported sanitizers: ${AW_SANITIZERS_SUPPORTED}")
		endif()
	endforeach()

	# Check for mutually exclusive sanitizers
	set(exclusive "")
	foreach (san IN LISTS AW_SANITIZERS_EXCLUSIVE)
		if (san IN_LIST sanitizers)
			list(APPEND exclusive ${san})
		endif()
	endforeach()
	list(LENGTH exclusive exclusive_count)
	if (exclusive_count GREATER 1)
		message(FATAL_ERROR
			"Sanitizers ${exclusive} are mutually exclusive, build them one at a time.")
	endif()

	# ASan already contains LeakSanitizer, asking for both makes clang unhappy
	if ("leak" IN_LIST sanitizers AND "address" IN_LIST sanitizers)
		list(REMOVE_ITEM sanitizers "leak")
	endif()

	set(${out_var} "${sanitizers}" PARENT_SCOPE)
endfunction()

function(_aw_configure_sanitizers)
	_aw_validate_sanitizers(sanitizers)

	if (NOT sanitizers)
		return()
	endif()

	message(STATUS "Sanitizers: ${sanitizers}")

	set(compile_flags)
	set(link_flags)
	if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		foreach (san IN LISTS sanitizers)
			list(APPEND compile_flags /fsanitize=${san})
		endforeach()
	else()
		string(REPLACE ";" "," sanitizer_list "${sanitizers}")

		set(compile_flags
			-fsanitize=${sanitizer_list}
			-fno-omit-frame-pointer
			-g)

		set(link_flags -fsanitize=${sanitizer_list})

		if (AW_SANITIZER_FAIL_FAST)
			    list(APPEND compile_flags -fno-sanitize-recover=all)
		endif()

		if ("memory" IN_LIST sanitizers)
			# MSan reports an uninitialised value where it is *used*;
			# without this the report does not say where it came from.
			list(APPEND compile_flags -fsanitize-memory-track-origins=2)
		endif()
	endif()

	# AW_SANITIZERS_SUPPORTED above says what the compiler implements; this
	# says whether the runtime is actually installed. -fsanitize= is
	# accepted by the driver either way, and clang keeps its runtimes in a
	# separate package, so without this the failure is a wall of link
	# errors at the end of a full build. The cache entry is named after the
	# set it was checked with, so it is not reused for another.
	string(MAKE_C_IDENTIFIER "AW_SANITIZERS_USABLE_${sanitizers}" usable_var)
	list(JOIN compile_flags " " CMAKE_REQUIRED_FLAGS)
	set(CMAKE_REQUIRED_LINK_OPTIONS ${link_flags})
	check_cxx_source_compiles("int main() { return 0; }" ${usable_var})
	if (NOT ${usable_var})
		message(FATAL_ERROR
			"${CMAKE_CXX_COMPILER_ID} cannot build with '${AW_SANITIZERS}'. "
			"The runtime library for it is most likely not installed.")
	endif()

	add_compile_options(${compile_flags})
	add_link_options(${link_flags})

	if ("undefined" IN_LIST sanitizers)
		# UBSan has no predefined macro of its own, see <aw/config.h>
		add_compile_definitions(AW_SANITIZE_UNDEFINED=1)
	endif()

	_aw_sanitizer_runtime_options("${sanitizers}")
endfunction()

# Options handed to the sanitizer runtimes when a test runs. The defaults
# are sensible; these turn on a few checks that are off by default and
# point each runtime at its suppression file.
function(_aw_sanitizer_runtime_options sanitizers)
	set(environment "")

	if ("address" IN_LIST sanitizers)
		set(asan_options "detect_stack_use_after_return=1")
		# Static initialisation order fiasco, which awlib has a helper for.
		string(APPEND asan_options ":check_initialization_order=1")
		string(APPEND asan_options ":strict_init_order=1")
		# str*() reading past a buffer that is not a C string.
		string(APPEND asan_options ":strict_string_checks=1")
		list(APPEND environment "ASAN_OPTIONS=${asan_options}")
	endif()

	if ("address" IN_LIST sanitizers OR "leak" IN_LIST sanitizers)
		list(APPEND environment
			"LSAN_OPTIONS=suppressions=${AW_SANITIZER_SUPPRESSION_DIR}/lsan.supp")
	endif()

	if ("undefined" IN_LIST sanitizers)
		list(APPEND environment
			"UBSAN_OPTIONS=print_stacktrace=1:halt_on_error=1:suppressions=${AW_SANITIZER_SUPPRESSION_DIR}/ubsan.supp")
	endif()

	if ("thread" IN_LIST sanitizers)
		list(APPEND environment
			"TSAN_OPTIONS=halt_on_error=1:second_deadlock_stack=1:suppressions=${AW_SANITIZER_SUPPRESSION_DIR}/tsan.supp")
	endif()

	if ("memory" IN_LIST sanitizers)
		list(APPEND environment "MSAN_OPTIONS=halt_on_error=1")
	endif()

	set(AW_SANITIZER_TEST_ENVIRONMENT "${environment}" CACHE INTERNAL
		"Runtime options for the sanitizers in use")
endfunction()

_aw_configure_sanitizers()
