/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_fileformat_wav_data_h
#define aw_fileformat_wav_data_h
#include <aw/types/types.h>
#include <vector>
namespace aw {
namespace wav {
/*! List of wave coding formats */
enum class format : u16 {
	pcm       = 0x01,
	ms_adpcm  = 0x02,
	ieee      = 0x03,
	alaw      = 0x06,
	mulaw     = 0x07,
	ima_adpcm = 0x11,
	gsm610    = 0x31,
	mpeg      = 0x50,
	yamaha_itu_g723_adpcm = 0x16,
	itu_g721_adpcm = 0x40,
	extensible = 0xfffe
};

/*! Raw wave data */
struct wave_data {
	wav::format format;

	//! Number of audio channels
	u16 channels;
	//! Number of samples per second
	u32 sample_rate;
	//! Size of one coding block
	u16 block_align;

	size_t size()     { return data.size(); }
	const char* ptr() { return data.data(); }

	//! Calculate number of bits per sample (format-dependent)
	u16 bits_per_sample( ) const noexcept;
	//! Calculate number of samples per block (format-dependent)
	u16 samples_per_block( ) const noexcept;

	std::vector<char> data;
};
} // namespace wav
} // namespace aw
#endif//aw_fileformat_wav_data_h
