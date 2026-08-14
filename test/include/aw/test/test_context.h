#ifndef aw_test_test_context_h
#define aw_test_test_context_h

#include <aw/types/string_view.h>

namespace aw::test {

struct test_context {
	//! Directory containing the running test executable
	std::string_view exe_dir;
	//! Name of the running test, as given to Test()
	std::string_view name;
};
} // namespace aw::test
#endif // aw_test_test_context_h
