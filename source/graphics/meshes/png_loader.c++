/*
 * Copyright (C) 2017  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/fileformat/png/log.h>
#include <aw/fileformat/png/reader.h>
#include <aw/utility/on_scope_exit.h>
#include <aw/algorithm/in.h>
#include <png.h>

namespace aw {
namespace png {

log_provider log;

namespace {
void convert_16_to_8(png_structp png_ptr)
{
#ifdef PNG_READ_SCALE_16_TO_8_SUPPORTED
	png_set_scale_16(png_ptr);
#else
	png_set_strip_16(png_ptr);
#endif
}
} // namespace

image try_read(io::input_stream& stream)
{
	auto warn_fn  = [] (png_structp png_ptr, png_const_charp msg)
	{
		log.warning( "png", msg );
	};
	auto error_fn = [] (png_structp png_ptr, png_const_charp msg)
	{
		log.error( "png", msg );
		longjmp( png_jmpbuf(png_ptr), 1);
	};
	auto read_fn  = [] (png_structp png_ptr, png_bytep data, png_size_t len)
	{
		auto io_ptr  = png_get_io_ptr( png_ptr );
		auto& stream = *static_cast<io::input_stream*>( io_ptr );

		try {
			size_t read = stream.read((char*)data, len);
			if (read != len)
				png_error( png_ptr, "unexpected end of file" );
		} catch(...) {
			png_error( png_ptr, "cannot read file" );
		}
	};

	png_byte sig[8];
	if (!stream.read(sig))
		throw std::runtime_error{"file is too short"};

	if ( png_sig_cmp(sig, 0, sizeof(sig)) )
		throw std::runtime_error{"not a PNG file (invalid signature)"};

	png_struct* png_ptr  = nullptr;
	png_info*   info_ptr = nullptr;

	png_ptr = png_create_read_struct(
		PNG_LIBPNG_VER_STRING, nullptr, +error_fn, +warn_fn
	);
	if (png_ptr == nullptr)
		throw std::runtime_error{"png_create_read_struct failed"};

	/*on_scope_exit guard{[&] {
		png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
	}};*/

	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == nullptr)
		throw std::runtime_error{"png_create_info_struct failed"};

	if (setjmp(png_jmpbuf(png_ptr)))
		throw std::runtime_error{"failed to read image"};

	png_set_read_fn(png_ptr, static_cast<void*>(&stream), +read_fn);
	png_set_sig_bytes(png_ptr, sizeof(sig));
	png_read_info(png_ptr, info_ptr);

	png_uint_32 width, height;
	int bit_depth, color_type;
	png_get_IHDR(
		png_ptr, info_ptr,
		&width, &height, &bit_depth, &color_type,
		nullptr, nullptr, nullptr
	);

	if (width == 0 || height == 0)
		throw std::runtime_error{"image with zero size"};

	if (color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png_ptr);

	if (bit_depth > 8)
		convert_16_to_8(png_ptr);

	if (bit_depth < 8) {
		if (color_type == PNG_COLOR_TYPE_GRAY)
			png_set_expand_gray_1_2_4_to_8(png_ptr);
		else
			png_set_packing(png_ptr);
	}

	if ( in(color_type, PNG_COLOR_TYPE_GRAY, PNG_COLOR_TYPE_GRAY_ALPHA) )
		png_set_gray_to_rgb(png_ptr);

	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(png_ptr);	

	int intent;

	constexpr double screen_gamma = 2.2;
	double image_gamma = 0.45455;

	if (!png_get_sRGB(png_ptr, info_ptr, &intent))
		png_get_gAMA(png_ptr, info_ptr, &image_gamma);
	png_set_gamma(png_ptr, screen_gamma, image_gamma);

	auto row_bytes = png_get_rowbytes(png_ptr, info_ptr);
	std::vector<std::byte> vec(height * row_bytes);

	std::vector<png_byte*> row_pointers;
	for (int i = 0; i < height; ++i)
		row_pointers.push_back(reinterpret_cast<png_byte*>(vec.data() + i*row_bytes));

	if (setjmp(png_jmpbuf(png_ptr)))
		throw std::runtime_error{"failed to read image"};

	png_read_update_info(png_ptr, info_ptr);
	png_read_image(png_ptr, row_pointers.data());
	png_read_end(png_ptr, info_ptr);

	return { std::move(vec), width, height };
}

optional<image> read(io::input_stream& stream) noexcept
{
	try {
		return try_read(stream);
	} catch( std::exception& ex ) {
		log.error( "png", ex.what() );
		return nullopt;
	}
}


} // namespace png
} // namespace aw

#ifdef AW_MANUAL_TEST
#include <aw/io/input_file_stream.h>
#include <aw/log/ostream_logger.h>
#include <iostream>
#include <fstream>

int main(int, char**argv)
{
	using namespace aw;
	io::input_file_stream file{ argv[1] ? argv[1] : "test.png" };

	ostream_logger logger{std::cout};
	png::log.set_logger(&logger);


	auto image = aw::png::read( file );

	if (image) {
		std::cout << "loaded\n";
		std::ofstream out{ "test.data" };
		out.write((char*)image->data(), image->size());
	}
}
#endif
