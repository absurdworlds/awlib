# Sanity checks on freshly generated loader sources, run by the regen-gl
# target. These hold no matter which GL version was generated, so they keep
# working when the registry is updated.
#
#   cmake -DSOURCE=<gl_NN.c++> -P check-generated.cmake

if (NOT SOURCE)
	message(FATAL_ERROR "check-generated.cmake needs -DSOURCE=<file>")
endif()

file(STRINGS "${SOURCE}" loaderLines REGEX "core_load_func\\(")

set(names)
set(glNames)
foreach (line IN LISTS loaderLines)
	# core_load_func(blend_func, "glBlendFunc");
	if (line MATCHES "core_load_func\\(([A-Za-z_0-9]+), \"([A-Za-z0-9_]+)\"")
		list(APPEND names   "${CMAKE_MATCH_1}")
		list(APPEND glNames "${CMAKE_MATCH_2}")
	endif()
endforeach()

list(LENGTH names total)
if (total EQUAL 0)
	message(FATAL_ERROR "${SOURCE}: no entry points were loaded at all")
endif()

# Two names collapsing into one would leave an entry point silently
# unreachable, which is what a bad to_snake rule looks like.
set(uniqueNames ${names})
list(REMOVE_DUPLICATES uniqueNames)
list(LENGTH uniqueNames uniqueTotal)
if (NOT total EQUAL uniqueTotal)
	set(dupes ${names})
	list(SORT dupes)
	message(FATAL_ERROR
		"${SOURCE}: ${total} entry points loaded but only ${uniqueTotal} "
		"distinct names -- two GL functions were given the same name")
endif()

# And the other direction: one GL function reached through two names.
set(uniqueGl ${glNames})
list(REMOVE_DUPLICATES uniqueGl)
list(LENGTH uniqueGl uniqueGlTotal)
if (NOT total EQUAL uniqueGlTotal)
	message(FATAL_ERROR
		"${SOURCE}: ${total} entry points loaded but only ${uniqueGlTotal} "
		"distinct GL functions -- one of them is loaded twice")
endif()

message(STATUS "${total} entry points, each name and GL function used once")
