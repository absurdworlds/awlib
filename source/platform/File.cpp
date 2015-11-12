/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2015       hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <awengine/io/filesystem.h>
#include <awengine/io/File.h>
#include <awengine/io/ReadFile.h>
#include <awengine/io/WriteFile.h>

namespace awrts {
namespace io {
File::File(std::string const& path, FileMode mode)
	: filename(path), file(nullptr)
{
	if (path.size() == 0) {
		return;
	}

	char const* m = mode == FileMode::Read   ? "rb" :
	                mode == FileMode::Write  ? "wb" :
	                mode == FileMode::Append ? "ab" : nullptr;

	if (!m) {
		return;
	}

	file = fopen(path.c_str(), m);
}

File::~File()
{
	if(isOpen()) {
		close();
	}
}


File::File(File&& other)
{
	filename = std::move(other.filename);
	file = std::move(other.file);
}

File& operator = (File&& other)
{
	filename = std::move(other.filename);
	file = std::move(other.file);
	return *this;
}

diff_t File::read(void* buffer, diff_t count)
{
	if (!isOpen()) {
		return -1;
	}

	return (diff_t)fread(buffer, 1, count, file);
}

diff_t File::write(void const* buffer, diff_t count)
{
	if (!isOpen()) {
		return -1;
	}

	return (i32)fwrite(buffer, 1, count, file);
}

diff_t File::seek(diff_t offset, SeekMode mode)
{
	if (!isOpen()) {
		return -1;
	}

	auto m = mode == SeekMode::Set     ? SEEK_SET :
	         mode == SeekMode::Reverse ? SEEK_END : SEEK_CUR;

	return fseek(file, offset, m);
}

diff_t File::tell() const
{
	if (!isOpen()) {
		return -1;
	}

	return ftell(file);
}

size_t File::getSize() const
{
	size_t size = fileSize(filename);
	return size;
}

std::string const& File::getPath() const
{
	return filename;
}

bool File::isOpen() const
{
	return file != 0;
}

void File::close()
{
	if (!isOpen())
		return;

	fclose(file);
	file = 0;
}
} // namespace io
} // namespace awrts
