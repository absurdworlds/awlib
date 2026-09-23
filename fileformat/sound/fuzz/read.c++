/*
 * Fuzz target for the WAV reader.
 *
 * A binary format parser reading attacker-controlled headers is the
 * classic case for this: chunk sizes, channel counts and sample rates
 * all come straight off the wire. read() is declared noexcept, so an
 * exception escaping it terminates -- which the fuzzer will find.
 */
#include <aw/fileformat/wav/reader.h>

#include <aw/io/input_memory_stream.h>

#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
	auto begin = reinterpret_cast<char const*>(data);
	auto stream = aw::io::input_memory_stream{begin, begin + size};

	aw::wav::wave_data out;
	if (aw::wav::read(stream, out)) {
		// Touch what a caller would, so a header claiming more than the
		// file holds shows up as a bad read rather than passing quietly.
		volatile size_t n = out.data.size();
		(void)n;
	}
	return 0;
}
