/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_fileformat_wav_lowlevel_h
#define aw_fileformat_wav_lowlevel_h
#include <aw/fileformat/wav/data.h>

namespace aw {
namespace wav {
constexpr auto ima_adpcm_bits_per_sample = 4;
inline u32 ima_adpcm_samples_per_block( wave_data const& wav )
{
	// IMA ADPCM block consists out of header
	// followed by a even number of compressed samples
	constexpr auto init_sample_size = 2;
	constexpr auto init_index_size = 1;
	constexpr auto padding_size = 1;
	// header consists of:
	// - [2 bytes] initial predictor
	// - [1 byte ] initial index
	// - [1 byte ] reserved (always zero)
	constexpr auto header_size = init_sample_size + init_index_size + padding_size;

	auto bytes_per_channel = wav.block_align / wav.channels;

	auto compressed_samples_size = bytes_per_channel - header_size;
	auto compressed_samples_bits = compressed_samples_size * 8;

	auto num_compressed_samples = compressed_samples_bits / ima_adpcm_bits_per_sample;

	// + the first sample from header
	return num_compressed_samples + 1;
}

} // namespace wav
} // namespace aw
#endif//aw_fileformat_wav_lowlevel_h
