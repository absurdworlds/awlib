#include <aw/platform/debugger.h>
#include <aw/types/string_view.h>

#include <aw/test/test.h>

TestFile("platform::debugger");

namespace aw::platform {
Test( debugger_present )
{
	bool is_present = false;
	if (auto* dbg = std::getenv("AW_TEST_DEBUGGER")) {
		string_view const str = dbg;
		is_present = !str.empty() && str != "0";
	}

	TestEqual( is_debugger_present(), is_present );
}

} // namespace aw::platform
