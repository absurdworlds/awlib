/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef AW_WAV_INTERNAL_CHUNKS_H
#define AW_WAV_INTERNAL_CHUNKS_H
#include <aw/io/input_stream.h>
#include <aw/io/endian.h>
#include <aw/utility/endian.h>
#include <aw/math/numeric.h>

#include <aw/fileformat/wav/reader.h>
#include <aw/fileformat/wav/log.h>

namespace aw {
namespace wav {

enum class tag : u32 {
	riff   = "RIFF"_le32,
	wave   = "WAVE"_le32,
	format = "fmt "_le32,
	data   = "data"_le32,
	list   = "list"_le32,
	fact   = "fact"_le32
};

//------------------------------------------------------------------------------
// Error-reporting utilities
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

void check_equal(u32 value, u32 expected, std::string const& msg)
{
	if (value != expected)
		log.warning("aw::wav", msg);
}

//------------------------------------------------------------------------------
// Common chunks

//! Base class for all chunks,
//! exists solely for the purpose of skipping chunks
struct chunk {
	chunk(io::input_stream& stream)
	{
		read_le(stream, size);
	}

	chunk(chunk const& other)
		: size{other.size}
	{
	}

	//! Chunk length ncludeing tag and size
	size_t length() const
	{
		return sizeof(tag) + sizeof(size) + size;
	}

	u32 size;
};

struct riff_header : chunk {
	static constexpr wav::tag tag = wav::tag::riff;

	riff_header(io::input_stream& stream)
		: chunk{stream}
	{
		read_le(stream, format);

		/*if (tag(chunk_id) != tag::riff)
			throw format_error{ "not a RIFF file" };*/
		if (wav::tag(format) != tag::wave)
			throw format_error{ "not a WAVE file" };
	}

	u32 format;
};

struct format_chunk_header : chunk {
	static constexpr wav::tag tag = wav::tag::format;
	format_chunk_header( io::input_stream& stream )
		: chunk{stream}
	{
		u16 tmp;
		read_le(stream, tmp);
		id = format(tmp);
	}

	format_chunk_header( format_chunk_header const& other )
		: chunk{other}, id{other.id}
	{
	}

	wav::format id;
};

struct format_chunk : format_chunk_header {
	static constexpr size_t min_size = 16;

	u16 num_channels;
	u32 sample_rate;
	u32 byte_rate;
	u16 block_align;
	u16 bits_per_sample;
	u16 extra_data = 0;

protected:
	format_chunk(format_chunk_header const& hdr, io::input_stream& stream)
		: format_chunk_header{hdr}
	{
		if (size < min_size)
			throw format_error{ "format header is too short" };
		read_le(stream, num_channels);
		read_le(stream, sample_rate);
		read_le(stream, byte_rate);
		read_le(stream, block_align);
		read_le(stream, bits_per_sample);

		if (size > min_size) {
			if ( size < min_size + sizeof(extra_data) )
				throw format_error{ "incorrect format chunk size" };
			read_le(stream, extra_data);
			check_equal(
				extra_data, size - min_size,
				"extra_data length doesn't match");
		}
	}
};


struct list_chunk : chunk {
	static constexpr wav::tag tag = wav::tag::list;

	list_chunk(io::input_stream& stream)
		: chunk{stream}
	{
		// TODO:
		stream.skip(size);
	}
};

struct fact_chunk : chunk {
	static constexpr wav::tag tag = wav::tag::list;

	fact_chunk(io::input_stream& stream)
		: chunk{stream}
	{
		read_le( stream, num_samples );
	}

	u32 num_samples;
};

struct data_chunk : chunk {
	static constexpr wav::tag tag = wav::tag::data;

	data_chunk(io::input_stream& stream)
		: chunk{stream}
	{
		samples.resize(size);
		size_t count = stream.read(samples.data(), samples.size());

		check_equal( count, size, "data is shorter than expected" );

		samples.resize( size );
	}

	std::vector<char> samples;
};

//------------------------------------------------------------------------------
// PCM chunks
struct pcm_format : format_chunk {
	pcm_format(format_chunk_header const& hdr, io::input_stream& stream)
		: format_chunk{ hdr, stream }
	{
		check_equal( size, min_size, "extra data in format chunk");
		if (size > min_size)
			stream.skip(size - min_size);
	}
};

//------------------------------------------------------------------------------
// IMA ADPCM chunks
struct ima_adpcm_format : format_chunk {
	ima_adpcm_format(format_chunk_header const& hdr, io::input_stream& stream)
		: format_chunk{ hdr, stream }
	{
		if (bits_per_sample != 4)
			throw format_error{ "Unsupported bits per sample value" };
		if (num_channels > 2)
			throw format_error{ "Unsupported number of channels" };

		if (extra_data < sizeof(samples_per_block))
			throw format_error{ "IMA ADPCM format chunk is too short" };

		read_le( stream, samples_per_block );

		constexpr u32 expected_size = 20;
		check_equal( size, expected_size, "extra data in format chunk");
		if (size > expected_size)
			stream.skip(size - expected_size);
	}

	u16 samples_per_block;
};
} // namespace wav
} // namespace aw
#endif//AW_WAV_INTERNAL_CHUNKS_H
