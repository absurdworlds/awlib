#include <aw/platform/demangle.h>
#include <aw/types/string_view.h>

/* WARNING! Very long string(s). */

#include <aw/utility/ranges/paired.h>
#include <aw/utility/test.h>

#include "demangle.x86_64abi.h"

TestFile("platform::demangle");

namespace aw {
Test( demangle )
{
	for (auto&& [man, dem] : paired(mangled, demangled))
		TestEqual( demangle( man ), dem );
#if 0 // bug in __cxa_demangle
	TestEqual( demangle( mangled_verylong ), demangled_verylong );
#endif
}

} // namespace aw

RunTests();
