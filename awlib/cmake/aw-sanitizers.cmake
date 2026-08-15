include_guard(GLOBAL)


set(AW_SANITIZERS "" CACHE STRING
	"Sanitizers to build with. Allowed options: address, undefined, thread, memory, leak")
set(AW_SANITIZERS_KNOWN address undefined thread memory leak)
option(AW_SANITIZER_FAIL_FAST "Make all sanitizer diagnostics fatal" OFF)

function(_aw_configure_sanitizers)
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
