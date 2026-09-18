/*
 * Copyright (C) 2026  Hedede <dev@hedede.me>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_io_tests_temp_file_h
#define aw_io_tests_temp_file_h
#include <aw/io/filesystem.h>
#include <aw/io/native_file.h>

#include <string>
#include <string_view>
#include <vector>

namespace aw::test {
/*!
 * A file for one test to work on, removed when the test leaves.
 */
struct temp_file {
	explicit temp_file(std::string_view name)
		: path{ "~temp_" + std::string{name} + ".bin" }
	{
		// clear anything a previous run left behind
		fs::remove(path);
	}

	~temp_file() { fs::remove(path); }

	temp_file(temp_file const&) = delete;
	temp_file& operator=(temp_file const&) = delete;

	/*!
	 * Give the file \a content, replacing whatever it held.
	 * \return number of bytes written
	 */
	intmax_t write(std::string_view content)
	{
		using fm = io::file_mode;

		io::native::file file{ path, fm::write|fm::create|fm::truncate };
		return file.write(content.data(), content.size());
	}

	intmax_t write(std::vector<char> const& content)
	{
		return write(std::string_view{ content.data(), content.size() });
	}

	//! Read everything the file holds now
	std::vector<char> read() const
	{
		io::native::file file{ path, io::file_mode::read };

		std::vector<char> content( size() );
		if (!content.empty())
			file.read(content.data(), content.size());

		return content;
	}

	size_t size() const
	{
		std::error_code ec;
		auto bytes = fs::file_size(path, ec);
		return ec ? 0 : size_t(bytes);
	}

	bool exists() const { return fs::exists(path); }

	fs::path path;
};
} // namespace aw::test
#endif//aw_io_tests_temp_file_h
