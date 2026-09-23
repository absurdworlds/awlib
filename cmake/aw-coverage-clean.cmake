#
# Discards coverage data from earlier runs. Run by the `coverage-clean`
# target via `cmake -P`; not meant to be included.
#
# Expects: AW_COV_BUILD_DIR, AW_COV_OUTPUT_DIR.
#
cmake_minimum_required(VERSION 3.19)

file(REMOVE_RECURSE "${AW_COV_OUTPUT_DIR}")
file(MAKE_DIRECTORY "${AW_COV_OUTPUT_DIR}")

# gcov counters are cumulative by design -- that is how several runs are
# merged into one report -- so a stale .gcda next to an object file would
# be added to this run instead of replaced. They live in the build tree
# rather than in the report directory removed above.
file(GLOB_RECURSE gcda "${AW_COV_BUILD_DIR}/*.gcda")
if (gcda)
	file(REMOVE ${gcda})
	list(LENGTH gcda count)
	message(STATUS "Discarded ${count} stale .gcda files")
endif()
