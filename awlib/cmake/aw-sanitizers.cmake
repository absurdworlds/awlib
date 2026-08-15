include_guard(GLOBAL)


set(AW_SANITIZERS "" CACHE STRING
	"Sanitizers to build with. Allowed options: address, undefined, thread, memory, leak")
# List of supported sanitizers
set(AW_SANITIZERS_KNOWN address undefined thread memory leak)
# List of sanitizers that don't play well with each other
set(AW_SANITIZERS_EXCLUSIVE address thread memory)
option(AW_SANITIZER_FAIL_FAST "Make all sanitizer diagnostics fatal" OFF)

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

	set(compile_flags)
	set(link_flags)
	if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		#TODO
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

	endif()

	add_compile_options(${compile_flags})
	add_link_options(${link_flags})
endfunction()

_aw_configure_sanitizers()
