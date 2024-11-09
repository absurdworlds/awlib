/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_fileformat_png_reader_h
#define aw_fileformat_png_reader_h
#include <aw/io/input_stream.h>
#include <aw/types/optional.h>
#include <vector>
namespace aw {
namespace png {
struct image {
	std::vector<std::byte> data;
	unsigned width, height;
};

optional<image> read(io::input_stream& stream) noexcept;

} // namespace png
} // namespace aw
#endif//aw_fileformat_png_reader_h
