#include <aw/string/strto.h>
#include <aw/test/test.h>
#include <cerrno>
#include <limits>
#include <system_error>

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
 * A parse which succeeds leaves errno as it found it, so an error
 * belonging to an earlier call is not destroyed.
 */
Test(strto_preserves_errno)
{
	char* end = nullptr;

	errno = ERANGE;
	TestEqual(strto<int>("5", &end, 10), 5);
	TestEqual(errno, ERANGE);

	errno = 0;
	TestEqual(strto<long>("5", &end, 10), 5L);
	TestEqual(errno, 0);
}

/*!
 * The error_code overload reports the range error itself, and errno is
 * left alone whether the parse succeeds or overflows.
 */
Test(strto_reports_error_code)
{
	char* end = nullptr;
	std::error_code ec;

	errno = EDOM;
	TestEqual(strto<short>("99999", &end, ec, 10), std::numeric_limits<short>::max());
	TestAssert(ec == std::errc::result_out_of_range);
	TestEqual(errno, EDOM);

	TestEqual(strto<int>("5", &end, ec, 10), 5);
	TestAssert(!ec);
	TestEqual(errno, EDOM);
}
} // namespace aw
