#include <aw/utility/fallback/filesystem.h>
#include <utility>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
namespace aw {
namespace filesystem {
namespace fallback {
namespace _impl {
namespace win32 {

template<typename...Args>
void set_error( std::error_code* out, std::error_code code, Args&&...args)
{
	if (!out)
		throw filesystem_error{ std::forward<Args>(args)..., code };
	*out = code;
}

void clear_error(std::error_code* out)
{
	if (out) (*out).clear();
}

std::error_code last_error()
{
	auto code = static_cast<int>( GetLastError() );
	return {code, std::system_category()};
}

AW_IO_EXP uintmax_t file_size( path const& p, std::error_code* out )
{
	WIN32_FILE_ATTRIBUTE_DATA info;
	auto name = p.wstring().data();

	if (!GetFileAttributesExW(name, GetFileExInfoStandard, &info)) {
		set_error(out, last_error(), "cannot get file size", p);
		return -1;
	}

	if (info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		auto code = std::make_error_code(std::errc::is_a_directory);
		set_error(out, code, "operation not supported", p);
		return -1;
	}

	clear_error(out);

	return (uintmax_t(info.nFileSizeHigh) << 32) | info.nFileSizeLow;
}

AW_IO_EXP bool exists( path const& p, std::error_code* out)
{
	auto attrib = GetFileAttributesW(p.wstring().data());

	if (attrib == INVALID_FILE_ATTRIBUTES) {
		auto error = last_error();
		switch (error.value()) {
		default:
			set_error(out, error, "error reading attributes", p);
			[[fallthrough]];
		case ERROR_PATH_NOT_FOUND:
		case ERROR_FILE_NOT_FOUND:
		//case ERROR_BAD_PATHNAME:
			return false;
		case ERROR_SHARING_VIOLATION:
			return true; // exists, no access
		}
	}

	return true;
}

bool remove( path const& p, std::error_code* out )
{
	if (!exists(p, out))
		return false;
	if (!DeleteFileW(p.wstring().data())) {
		set_error(out, last_error(), "cannot remove file", p);
		return false;
	}

	clear_error(out);

	return true;
}

} // namespace _impl
} // namespace win32
} // namespace fallback
} // namespace filesystem
} // namespace aw
