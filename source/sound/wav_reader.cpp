#include <aw/fileformat/wav/reader.h>
#include <aw/fileformat/wav/log.h>

#include <aw/io/endian.h>
#include <aw/utility/endian.h>

namespace aw {
namespace wav {
log_provider log;

enum class tag : u32 {
	riff   = "RIFF"_le32,
	wave   = "WAVE"_le32,
	format = "fmt "_le32,
	data   = "data"_le32,
	list   = "list"_le32,
};

enum class format {
	pcm       = 0x01,
	ieee      = 0x03,
	alaw      = 0x06,
	mulaw     = 0x07,
	ima_adpcm = 0x11,
	yamaha_itu_g723_adpcm = 0x16,
	gsm610    = 0x31,
	itu_g721_adpcm = 0x40,
	mpeg       = 0x50,
	extensible = 0xfffe
};


struct format_error : std::logic_error {
	format_error(std::string const& what)
		: std::logic_error(what)
	{}

	char const* what() const noexcept override
	{
		return what_str.data();
	}

private:
	std::string what_str = [this] {
		using namespace std::string_literals;
		return "invalid file format: "s + std::logic_error::what();
	}();
};

struct reader {
	reader(io::input_stream& stream, wave_data& sample)
		: stream{stream}, sample{sample}
	{}

	void read_riff_header();
	void read_format_chunk();
	void read_data_chunk();

	void check_equal(u32 value, u32 expected, std::string const& msg)
	{
		if (value != expected)
			log.warning("aw::wav", msg);
	}

private:
	io::input_stream& stream;
	wave_data& sample;
	uintmax_t size_check;
};

void reader::read_riff_header()
{
	u32 chunk_id;
	u32 file_size;
	u32 format;

	read_le(stream, chunk_id);
	read_le(stream, file_size);
	read_le(stream, format);

	if (tag(chunk_id) != tag::riff)
		throw format_error{ "Not a RIFF file." };
	if (tag(format) != tag::wave)
		throw format_error{ "Not a WAVE file." };

	size_check = file_size - 4;
}

void reader::read_format_chunk()
{
	u32 format_tag;
	read_le(stream, format_tag);
	if (tag(format_tag) != tag::format)
		throw format_error{ "Expected \"fmt \"." };

	u32 header_length;
	u16 type;
	u16 num_channels;
	u32 sample_rate;
	u32 byte_rate;
	u16 bytes_per_sample;
	u16 bits_per_sample;

	read_le(stream, header_length);
	read_le(stream, type);
	read_le(stream, num_channels);
	read_le(stream, sample_rate);
	read_le(stream, byte_rate);
	read_le(stream, bytes_per_sample);
	read_le(stream, bits_per_sample);

	constexpr size_t min_size = 16;
	stream.skip(header_length - min_size);
	size_check -= 8 + header_length;

	check_equal(byte_rate, sample_rate * bytes_per_sample, "incorrect byte_rate");
	check_equal(bytes_per_sample, num_channels * bits_per_sample/8,
	            "bps doesn't match expected value");
	
	sample.bits_per_sample = bits_per_sample;
	sample.channels    = num_channels;
	sample.sample_rate = sample_rate;

	// Check with -Wswitch-enum that all cases are covered
	switch(format(type)) {
	default:
		throw format_error{ "Unknown wave format." };
	case format::pcm:
		break;
	case format::ieee:
	case format::alaw:
	case format::mulaw:
	case format::ima_adpcm:
	case format::itu_g721_adpcm:
	case format::yamaha_itu_g723_adpcm:
	case format::gsm610:
	case format::mpeg:
	case format::extensible:
		throw format_error{ "Unsupported wave format." };
	}
}

void reader::read_data_chunk()
{
	u32 data_tag;
	read_le(stream, data_tag);
	if (tag(data_tag) == tag::list) {
		u32 chunk_size;
		read_le(stream, chunk_size);
		stream.skip(chunk_size);
		read_le(stream, data_tag);
	}

	if (tag(data_tag) != tag::data)
		throw format_error{ "Expected \"data\"." };

	u32 data_size;
	read_le(stream, data_size);
	sample.data.resize(data_size);
	size_t count = stream.read(sample.data.data(), data_size);

	check_equal(count, data_size, "data is shorter than expected");
	size_check -= 8 + count;
	check_equal(size_check, 0, "chunk_size doesn't match actual file size");
}

bool read(io::input_stream& stream, wave_data& sample) noexcept
try {
	reader wv{stream, sample};
	wv.read_riff_header();
	wv.read_format_chunk();
	wv.read_data_chunk();
	return true;
} catch(format_error& e) {
	log.error("aw::wav", e.what());
	return false;
} catch(std::exception& e) {
	log.error("aw::wav", e.what());
	return false;
}

optional<wave_data> read(io::input_stream& stream) noexcept
{
	wave_data data;
	if (!read(stream, data))
		return nullopt;
	return data;
}
} // namespace wav
} // namespace aw
