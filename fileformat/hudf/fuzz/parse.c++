/*
 * Fuzz target for the HuDF parse entry points.
 *
 * The hand-written cases in ../tests/hardening.c++ are the same idea
 * reached by guesswork: malformed input must be rejected rather than
 * hang, exhaust memory or run off the end of the buffer. Anything this
 * finds belongs in corpus/ afterwards, which turns it into a regression.
 */
#include <aw/hudf/parser.h>
#include <aw/hudf/utility.h>

#include <aw/io/input_memory_stream.h>

#include <cstddef>
#include <cstdint>

namespace {
aw::io::input_memory_stream stream_of(const uint8_t* data, size_t size)
{
	auto begin = reinterpret_cast<char const*>(data);
	return aw::io::input_memory_stream{begin, begin + size};
}
} // namespace

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
	{
		auto stream = stream_of(data, size);
		auto doc = aw::hudf::parse_file(stream);
		(void)doc;
	}
	// find_value and find_node skip over nodes instead of building them,
	// so they walk the input by a different path than parse_file does.
	{
		auto stream = stream_of(data, size);
		auto val = aw::hudf::find_value(stream, "a/b");
		(void)val;
	}
	{
		auto stream = stream_of(data, size);
		auto node = aw::hudf::find_node(stream, "a");
		(void)node;
	}
	return 0;
}
