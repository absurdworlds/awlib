#include "aw/io/win32/process.h"

#include <aw/types/string_view.h>
#include <aw/utility/string/escape.h>
#include <aw/utility/unicode/convert.h>
#include <aw/algorithm/in.h>

#include "path.h"
#include "winapi_helpers.h"

#include <cassert>
#include <vector>

namespace aw::io::win32 {
namespace detail {
void close_handle( uintptr_t handle )
{
	CloseHandle(HANDLE(handle));
}
} // namespace detail

winapi_path format_command_line(const char* path, aw::array_view<const char*> argv)
{
	bool first = true;
	std::wstring result;
	for (auto* arg : argv) {
		if (first)
			first = false;
		else
			result += L' ';
		result += L'"';
		result += aw::unicode::widen(string::escape_quotes(arg));
		result += L'"';
	}
	return result;
}

process_holder spawn(const char* path, aw::array_view<const char*> argv, std::error_code& ec) noexcept
{
	/*! enforce `nullptr` at the end of `argv` */
	if (!argv.empty()) {
		assert( argv.back() == nullptr );
		argv.remove_suffix(1);
	}

	STARTUPINFOW startup_info = {};
	PROCESS_INFORMATION process_info = {};

	GetStartupInfoW(&startup_info);

	auto ret = CreateProcessW(
		path ? winapi_path(path) : nullptr,
		format_command_line(path, argv),
		nullptr, nullptr, false, 0, nullptr, nullptr,
		&startup_info, &process_info );

	set_error_if(!ret, ec);

	const auto handle = process_info.hProcess;
	if (handle)
		return convert_handle<process_handle>(process_info.hProcess);

	return invalid_process_handle;
}

process_holder spawn(aw::array_view<const char*> argv, std::error_code& ec) noexcept
{
	return spawn( nullptr, argv, ec );
}

process_holder spawn(std::string path, aw::array_view<std::string> argv, std::error_code& ec)
{
	std::vector<const char*> args;
	args.push_back(path.data());
	for (const auto& arg : argv)
		args.push_back(arg.data());
	args.push_back(nullptr);

	return spawn(path.data(), args, ec);
}


wait_status wait(process_handle hprocess, std::error_code& ec, timeout_spec_ms timeout) noexcept
{
	// TODO: add is_handle_valid()
	if( in( hprocess, process_handle(0), process_handle(-1) ) ) {
		ec = make_error_code( std::errc::invalid_argument );
		return wait_status::failed;
	};

	auto ret = WaitForSingleObject( HANDLE(hprocess), timeout ? timeout->count() : INFINITE );

	set_error_if(ret == WAIT_FAILED, ec);

	switch (ret) {
		using enum wait_status;
	default:
	case WAIT_OBJECT_0:
	case WAIT_ABANDONED:
		return finished;
	case WAIT_TIMEOUT:
		return timeout;
	case WAIT_FAILED:
		return failed;
	}
}

int kill(process_handle hprocess, int signal, std::error_code& ec) noexcept
{
	// TODO: add is_handle_valid()
	if( in( hprocess, process_handle(0), process_handle(-1) ) ) {
		ec = make_error_code( std::errc::invalid_argument );
		return -1;
	};

	auto ret = TerminateProcess( HANDLE(hprocess), 1 );

	set_error_if(!ret, ec);

	return ret;
}
} // namespace aw::platform::win32
