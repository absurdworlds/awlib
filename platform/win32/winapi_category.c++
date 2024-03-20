#include <aw/utility/unicode/convert.h>
#include <aw/utility/string/trim.h>
#include <aw/algorithm/in.h>
#include <aw/platform/export.h>
#include <system_error>
#include <windows.h>
namespace aw {
namespace win32 {
std::errc map_error_code(int code);
}
namespace _impl {
namespace {

struct winapi_error_category final : std::error_category {
	char const* name() const noexcept override
	{
		return "winapi";
	}

	std::string message(int code) const override;
	
	std::error_condition default_error_condition( int code ) const noexcept override
	{
		return std::make_error_condition( win32::map_error_code(code) );
	}
};

auto winapi_error_category::message(int code) const -> std::string
{
	constexpr size_t buffer_size = 256;

	wchar_t buf[buffer_size];
	//std::wstring buf(buffer_size,L'\0');

	auto err = static_cast<DWORD>(code);
	auto flags = FORMAT_MESSAGE_FROM_SYSTEM;
	const void* source = nullptr;
	auto len = ::FormatMessageW(flags, source, err, 0, buf, buffer_size, nullptr);
	if (len == 0)
		return "Unknown error";

	auto msg = aw::unicode::narrow(buf);
	aw::string::rtrim( msg, [] (char c) { return in(c,'\r','\n'); } );
	return msg;
}
} // namespace
} // namespace _impl

AW_PLATFORM_EXP std::error_category const& winapi_error_category()
{
  static aw::_impl::winapi_error_category cat;
  return cat;
}

} // namespace aw
