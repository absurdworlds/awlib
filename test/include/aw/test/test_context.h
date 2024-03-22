#ifndef aw_test_test_context_h
#define aw_test_test_context_h

#include <aw/types/string_view.h>

namespace aw::test {

struct test_context {
	std::string_view exe_dir;
};
} // namespace aw::test
#endif // aw_test_test_context_h
