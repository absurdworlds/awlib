#include <aw/utility/string/strto.h>
#include <aw/test/test.h>
#include <cerrno>
#include <limits>

TestFile( "string::strto" );

namespace aw {
/*!
 * A value which fits the requested type is returned exactly.
 */
Test(strto_parses_integers)
{
	char* end = nullptr;
	TestEqual(strto<int>("42", &end, 10), 42);
	TestEqual(strto<unsigned>("7", &end, 10), 7u);
	TestEqual(strto<short>("-3", &end, 10), short(-3));
}

/*!
 * A value too big for the requested type is clamped to its limit, and the
 * overflow is reported through errno.
 */
Test(strto_clamps_out_of_range)
{
	char* end = nullptr;

	errno = 0;
	TestEqual(strto<short>("99999", &end, 10), std::numeric_limits<short>::max());
	TestEqual(errno, ERANGE);

	errno = 0;
	TestEqual(strto<short>("-99999", &end, 10), std::numeric_limits<short>::min());
	TestEqual(errno, ERANGE);
}

/*!
 * An errno set by an earlier call is not reported by the next one:
 * a parse which succeeds leaves no error set.
 */
Test(strto_clears_stale_errno)
{
	char* end = nullptr;

	errno = 0;
	TestEqual(strto<int>("9999999999", &end, 10), std::numeric_limits<int>::max());
	TestEqual(errno, ERANGE);

	TestEqual(strto<int>("5", &end, 10), 5);
	TestEqual(errno, 0);
}
} // namespace aw
