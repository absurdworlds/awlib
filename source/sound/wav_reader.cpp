/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include "chunks.h"
#include <aw/fileformat/wav/lowlevel.h>
#include <aw/types/optional.h>

namespace aw {
namespace wav {
log_provider log;

struct reader {
	reader(io::input_stream& stream, wave_data& sample)
		: stream{stream}, sample{sample}
	{}

	// TODO: Instead of adding methods to 'reader', make it a struct
	// passed to functions
	void read_riff_header();
	void read_format_chunks();
	tag read_misc_chunks();
	void read_wave_data( format_chunk const& fmt );
	void read_pcm_chunks( format_chunk_header& hdr );
	void read_ima_adpcm_chunks( format_chunk_header& hdr );

	optional<tag> read_tag()
	{
		u32 id;
		if (read_le(stream, id))
			return tag(id);
		return nullopt;
	}

	void check_size();
	void expect_chunk( tag id, string_view name );
	void skip_chunk( tag id );
	void skip_chunk( chunk const& c )
	{
		size_check += c.length();
		//stream.skip(c.size);
	}



private:
	io::input_stream& stream;
	wave_data& sample;
	uintmax_t size_check;
};

void reader::skip_chunk( tag id )
{
	switch( id ) {
	case tag::list:
		skip_chunk( list_chunk{ stream } );
		break;
	case tag::fact:
		skip_chunk( fact_chunk{ stream } );
		break;
	case tag::format:
		throw format_error{ "extra fmt subchunk" };
	case tag::riff:
		throw format_error{ "extra RIFF chunk" };
	default:
		throw format_error{ "unknown subchunk" };
	}
}

void reader::expect_chunk( tag expect, string_view name )
{
	using namespace std::string_literals;
	u32 id;
	read_le(stream, id);
	if (wav::tag(id) != expect)
		throw format_error{ "expected "s + std::string(name) + " chunk"s };
}

void reader::read_riff_header()
{
	expect_chunk( tag::riff, "RIFF" );
	riff_header riff{ stream };
	size_check = riff.size - sizeof(tag);
}

void reader::read_format_chunks()
{
	expect_chunk( tag::format, "format" );
	format_chunk_header fmt{ stream };
	size_check -= fmt.length();

	sample.format = fmt.id;

	switch ( sample.format ) {
	default:
		throw format_error{ "unknown wave format" };
	case format::pcm:
		read_pcm_chunks( fmt );
		break;
	case format::ima_adpcm:
		read_ima_adpcm_chunks( fmt );
		break;
	case format::ieee:
	case format::alaw:
	case format::mulaw:
	case format::itu_g721_adpcm:
	case format::yamaha_itu_g723_adpcm:
	case format::gsm610:
	case format::mpeg:
	case format::extensible:
		throw format_error{ "unsupported wave format" };
	};
}

tag reader::read_misc_chunks( )
{
	tag id;
	while ( auto opt = read_tag() ) {
		id = *opt;
		if (id == tag::data)
			break;
		/*if (id == tag::fact) {
			fact_chunk fact{ stream };
			//sample.num_samples = fact.num_samples;
			continue;
		}*/
		skip_chunk( id );
	}

	return id;
}

void reader::read_wave_data( format_chunk const& fmt )
{
	data_chunk data{stream};
	size_check -= data.length();

	sample.channels    = fmt.num_channels;
	sample.sample_rate = fmt.sample_rate;
	sample.block_align = fmt.block_align;
	sample.data = std::move( data.samples );
}

//------------------------------------------------------------------------------
void reader::read_pcm_chunks( format_chunk_header& hdr )
{
	pcm_format pcm{ hdr, stream };

	tag id = read_misc_chunks();

	if (tag(id) != tag::data)
		throw format_error{ "Expected \"data\" chunk." };

	read_wave_data( pcm );

	u32 bytes_per_sample = pcm.bits_per_sample / 8;

	check_equal( pcm.block_align, pcm.num_channels * bytes_per_sample,
	            "block_align doesn't match expected value");
	check_equal( pcm.byte_rate, pcm.sample_rate * pcm.block_align,
	            "byte_rate doesn't match expected value");
}

void reader::read_ima_adpcm_chunks( format_chunk_header& hdr )
{
	ima_adpcm_format pcm{ hdr, stream };

	tag id = read_misc_chunks();

	if (tag(id) != tag::data)
		throw format_error{ "Expected \"data\" chunk." };

	read_wave_data( pcm );

	auto samples_per_block = ima_adpcm_samples_per_block( sample );

	check_equal( samples_per_block, pcm.samples_per_block,
	            "samples_per_block doens't match expected value" );
}

void reader::check_size()
{
	check_equal(size_check, 0, "chunk_size doesn't match actual file size");
}

bool read(io::input_stream& stream, wave_data& sample) noexcept
try {
	reader wv{stream, sample};
	wv.read_riff_header();
	wv.read_format_chunks();
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

//------------------------------------------------------------------------------
u16 wave_data::bits_per_sample() const noexcept
{
	switch (format) {
	case wav::format::pcm:
		return block_align / channels * 8;
	case wav::format::ima_adpcm:
		return ima_adpcm_bits_per_sample;
	}	
}

u16 wave_data::samples_per_block() const noexcept
{
	switch (format) {
	case wav::format::pcm:
		return channels;
	case wav::format::ima_adpcm:
		return ima_adpcm_samples_per_block( *this );
	}
}
} // namespace wav
} // namespace aw
