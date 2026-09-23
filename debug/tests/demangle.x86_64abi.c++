#include <aw/debug/demangle.h>
#include <aw/types/string_view.h>

/* WARNING! Very long string(s). */

#include <aw/ranges/paired.h>
#include <aw/test/test.h>

#include "demangle.x86_64abi.h"

TestFile("debug::demangle");

namespace aw::debug {
Test( demangle )
{
	for (auto&& [man, dem] : paired(mangled, demangled))
		TestEqual( demangle( man ), dem );
#if 0 // https://gcc.gnu.org/bugzilla/show_bug.cgi?id=96345
	TestEqual( demangle( mangled_verylong ), demangled_verylong );
#endif
}

} // namespace aw::debug

