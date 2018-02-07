/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_fileformat_wav_wav_reader_h
#define aw_fileformat_wav_wav_reader_h
#include <aw/fileformat/wav/data.h>

#include <aw/sound/export.h>

#include <aw/io/input_stream.h>

#include <aw/types/optional.h>

namespace aw {
namespace wav {
/*!
 * Load a wave file from stream \a stream.
 * \return
 *    Upon success, returns std::optional containing wave data
 * obtained from stream. On failure, returns empty optional,
 * and reports error to log.
 */
AW_SND_EXP optional<wave_data> read(io::input_stream& stream) noexcept;

/*!
 * Same as previous overload, but instead loads data
 * into user-provided \a sample.
 * \return
 *    true on success, false on failure.
 * \note
 *    If this function fails, \a sample will be partially loaded.
 *    (this behavior is subject to change in the future)
 */
AW_SND_EXP bool read(io::input_stream& stream, wave_data& sample) noexcept;
} // namespace wav
} // namespace aw
#endif//aw_fileformat_wav_wav_reader_h
