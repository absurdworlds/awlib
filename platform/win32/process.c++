#include <aw/platform/process.h>
#include <aw/platform/windows.h>

#include <aw/types/string_view.h>
#include <aw/utility/string/escape.h>
#include <aw/algorithm/in.h>

#include "path.h"

#include <iostream>
#include <vector>

#include <cassert>
namespace aw::platform::win32 {

std::wstring format_command_line(const char* path, aw::array_ref<const char*> argv)
{
	std::wstring result = path;
	for (auto* arg : argv) {
		result += " \"";
		result += string::escape_quotes(arg);
		result += '"';
	}
	return result;
}

AW_PLATFORM_EXP
process_handle spawn(const char* path, aw::array_ref<const char*> argv, std::error_code& ec) noexcept
{
	/*! enforce `nullptr` at the end of `argv` */
	assert( argv.empty() || argv.back() == nullptr );

	CreateProcessW( nullptr, format_command_line(path, argv),  );
	pid_t pid;
	int rc = posix_spawn(&pid, path, nullptr, nullptr, argv.data(), environ);
	if (rc == 0)
		return process_handle( pid );

	ec.assign( rc, std::generic_category() );
	return invalid_process_handle;
}

AW_PLATFORM_EXP
process_handle spawn(aw::array_ref<const char*> argv, std::error_code& ec) noexcept
{
	return spawn( argv[0], argv, ec );
}

AW_PLATFORM_EXP
process_handle spawn(std::string path, aw::array_ref<std::string> argv)
{
	std::error_code ec;
	std::vector<char*> args;
	args.push_back(path.data());
	for (std::string& arg : argv)
		args.push_back(arg.data());
	args.push_back(nullptr);

	return spawn(path.data(), args, ec);
}

AW_PLATFORM_EXP
int kill(process_handle pid, int signal, std::error_code& ec) noexcept
{
	// TODO: don't accept -1 or 0 as pid, add separate functions for that
	if( in( pid, process_handle(0), process_handle(-1) ) ) {
		ec = make_error_code( std::errc::invalid_argument );
		return -1;
	};

	auto ret = ::kill( pid_t(pid), signal);
	if (ret < 0)
		ec.assign( errno, std::generic_category() );
	return ret;
}
} // namespace aw::platform::win32
