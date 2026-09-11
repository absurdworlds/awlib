#include "aw/assert/assert_handler.h"

#include <cstddef>
#include <cstdio>
#include <cstring>

namespace aw {
namespace {
void append(char*& pos, char* end, string_view str)
{
	auto size = std::size_t(end - pos);
	if (size > str.size())
		size = str.size();
	std::memcpy(pos, str.data(), size);
	pos += size;
}

void append_uint(char*& pos, char* end, unsigned long value)
{
	char  digits[24];
	char* first = digits + sizeof digits;
	do {
		*--first = char('0' + value % 10);
		value /= 10;
	} while (value);
	append(pos, end, string_view(first, std::size_t(digits + sizeof digits - first)));
}
} // namespace

/*!
 * Reporter used when no handler has been installed.
 *
 * Writes the assertion to stderr and asks for the process to be aborted.
 * The message is built in a fixed buffer, because the invariant that just
 * failed may well be the allocator's, and is truncated rather than grown.
 */
assert_action default_assert_fail(string_view assertion, source_location location)
{
	char  buffer[1024];
	char* pos = buffer;
	char* end = buffer + sizeof buffer;

	append(pos, end, location.file_name());
	append(pos, end, ":");
	append_uint(pos, end, location.line());
	append(pos, end, ": assertion failed: ");
	append(pos, end, assertion);
	append(pos, end, "\n  in ");
	append(pos, end, location.function_name());
	append(pos, end, "\n");

	std::fwrite(buffer, 1, std::size_t(pos - buffer), stderr);
	std::fflush(stderr);

	return assert_action::abort;
}
} // namespace aw
