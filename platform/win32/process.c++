#include <aw/process/win32.h>
#include <aw/process/limits.h>

#include <aw/types/string_view.h>
#include <aw/string/escape.h>
#include <aw/utility/unicode/convert.h>
#include <aw/algorithm/in.h>

#include "path.h"
#include "winapi_helpers.h"

#include <cassert>
#include <csignal>
#include <memory>
#include <new>
#include <utility>
#include <vector>

namespace aw::process::win32 {
using platform::win32::convert_handle;
using platform::win32::set_error;
using platform::win32::set_error_if;
using platform::win32::winapi_path;

namespace self {
process_handle handle()
{
	return convert_handle<process_handle>(GetCurrentProcess());
}

fs::path path(std::error_code& ec)
{
	std::vector<WCHAR> buf(MAX_PATH);
	while (true) {
		auto len = ::GetModuleFileNameW(nullptr, buf.data(), DWORD(buf.size()));
		if (len == 0) {
			set_error(ec);
			return {};
		}
		if (len < buf.size()) {
			ec.clear();
			// wchar_t is 32-bit on winelib, so go through char16_t
			auto* text = reinterpret_cast<char16_t const*>(buf.data());
			return fs::path{ std::u16string_view{ text, len } };
		}
		buf.resize(buf.size() * 2);
	}
}
} //namespace self

#if defined(AW_PROCESS_HAS_HANDLE_COUNT)
u32 handle_count(process_handle handle)
{
	DWORD count = 0;
	GetProcessHandleCount(HANDLE(handle), &count);
	return count;
}
#endif

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

namespace {
//! Handles that the child gets: its standard streams and the inherited ones
struct child_streams {
	explicit child_streams(stdio const& streams) noexcept
	{
		const io::win32::file_descriptor given[] = { streams.in, streams.out, streams.err };
		for (auto fd : given)
			redirected |= (fd != io::win32::invalid_fd);

		if (redirected && !copy_std_handles(given))
			return;

		for (auto fd : streams.inherit) {
			if (!share(HANDLE(fd)))
				return;
		}

		if (!list.empty())
			make_attributes();
	}

	~child_streams()
	{
		if (attributes)
			DeleteProcThreadAttributeList(attributes);
		// the child has its own copies by now
		for (auto handle : copies)
			CloseHandle(handle);
		for (auto [handle, flags] : shared)
			SetHandleInformation(handle, HANDLE_FLAG_INHERIT, flags);
	}

	child_streams(child_streams const&) = delete;
	child_streams& operator=(child_streams const&) = delete;

	//! Whether any of the standard streams is redirected
	bool redirected = false;
	//! Handles for the child's stdin, stdout and stderr; null where it gets none
	HANDLE handles[3] = {};
	//! All handles that the child inherits
	std::vector<HANDLE> list;

	LPPROC_THREAD_ATTRIBUTE_LIST attributes = nullptr;

	std::error_code error;

private:
	//! A redirected child needs to be told about all three
	bool copy_std_handles(io::win32::file_descriptor const (&given)[3]) noexcept
	{
		const DWORD std_ids[] = { STD_INPUT_HANDLE, STD_OUTPUT_HANDLE, STD_ERROR_HANDLE };
		const HANDLE self = GetCurrentProcess();
		for (int i = 0; i < 3; ++i) {
			const bool chosen = given[i] != io::win32::invalid_fd;
			const HANDLE source = chosen ? HANDLE(given[i]) : GetStdHandle(std_ids[i]);
			if (source == nullptr || source == INVALID_HANDLE_VALUE)
				continue;

			HANDLE copy = nullptr;
			if (!DuplicateHandle(self, source, self, &copy, 0, true, DUPLICATE_SAME_ACCESS)) {
				// the caller's own streams are passed on if they can be
				if (chosen) {
					set_error(error);
					return false;
				}
				continue;
			}
			copies.push_back(copy);
			list.push_back(copy);
			handles[i] = copy;
		}
		return true;
	}

	/*!
	 * Make \a handle inheritable for this spawn. It can't be duplicated
	 * instead, since the child expects the same value.
	 */
	bool share(HANDLE handle) noexcept
	{
		for (auto& entry : shared) {
			if (entry.first == handle)
				return true;
		}

		DWORD flags = 0;
		if (!GetHandleInformation(handle, &flags) ||
		    !SetHandleInformation(handle, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT)) {
			set_error(error);
			return false;
		}
		shared.push_back({ handle, flags & HANDLE_FLAG_INHERIT });
		list.push_back(handle);
		return true;
	}

	/*!
	 * Limit the inheritance to the handles in the list, so that the
	 * child doesn't get every inheritable handle the caller has open
	 */
	void make_attributes() noexcept
	{
		SIZE_T size = 0;
		InitializeProcThreadAttributeList(nullptr, 1, 0, &size);
		buffer.reset(new (std::nothrow) char[size]);
		if (!buffer) {
			error = std::make_error_code(std::errc::not_enough_memory);
			return;
		}

		auto attribute_list = LPPROC_THREAD_ATTRIBUTE_LIST(buffer.get());
		if (!InitializeProcThreadAttributeList(attribute_list, 1, 0, &size)) {
			set_error(error);
			return;
		}
		attributes = attribute_list;

		if (!UpdateProcThreadAttribute(attribute_list, 0, PROC_THREAD_ATTRIBUTE_HANDLE_LIST,
		                               list.data(), list.size() * sizeof(HANDLE), nullptr, nullptr))
			set_error(error);
	}

	//! Duplicates of the standard handles, closed afterwards
	std::vector<HANDLE> copies;
	//! Handles made inheritable, and their inheritance flags before that
	std::vector<std::pair<HANDLE, DWORD>> shared;

	std::unique_ptr<char[]> buffer;
};
} // namespace

process_holder spawn(const char* path, aw::array_view<const char*> argv, stdio const& streams, spawn_flags flags, std::error_code& ec) noexcept
{
	// enforce `nullptr` at the end of `argv` for consistency between platforms
	if (!argv.empty()) {
		assert( argv.back() == nullptr );
		argv.remove_suffix(1);
	}

	STARTUPINFOEXW startup_info = {};
	PROCESS_INFORMATION process_info = {};

	GetStartupInfoW(&startup_info.StartupInfo);

	DWORD creation_flags = 0;
	if (!!(flags & spawn_flags::detached))
		creation_flags |= DETACHED_PROCESS | CREATE_NEW_PROCESS_GROUP;

	child_streams child{ streams };
	if (child.error) {
		ec = child.error;
		return invalid_process_handle;
	}

	if (child.redirected) {
		startup_info.StartupInfo.dwFlags   |= STARTF_USESTDHANDLES;
		startup_info.StartupInfo.hStdInput  = child.handles[0];
		startup_info.StartupInfo.hStdOutput = child.handles[1];
		startup_info.StartupInfo.hStdError  = child.handles[2];
	}

	if (child.attributes) {
		startup_info.StartupInfo.cb = sizeof(startup_info);
		startup_info.lpAttributeList = child.attributes;
		creation_flags |= EXTENDED_STARTUPINFO_PRESENT;
	}

	const bool inherit = !child.list.empty();

	auto ret = CreateProcessW(
		path ? winapi_path(path) : nullptr,
		format_command_line(path, argv),
		nullptr, nullptr, inherit, creation_flags, nullptr, nullptr,
		&startup_info.StartupInfo, &process_info );

	set_error_if(!ret, ec);

	if (process_info.hThread)
		CloseHandle(process_info.hThread);

	const auto handle = process_info.hProcess;
	if (handle)
		return convert_handle<process_handle>(process_info.hProcess);

	return invalid_process_handle;
}

process_holder spawn(aw::array_view<const char*> argv, stdio const& streams, spawn_flags flags, std::error_code& ec) noexcept
{
	return spawn( nullptr, argv, streams, flags, ec );
}

process_holder spawn(std::string path, aw::array_view<std::string> argv, stdio const& streams, spawn_flags flags, std::error_code& ec)
{
	std::vector<const char*> args;
	args.push_back(path.data());
	for (const auto& arg : argv)
		args.push_back(arg.data());
	args.push_back(nullptr);

	return spawn(path.data(), args, streams, flags, ec);
}


wait_result wait(process_handle hprocess, std::error_code& ec, timeout_spec_ms timeout) noexcept
{
	// TODO: add is_handle_valid()
	if( in( hprocess, process_handle(0), process_handle(-1) ) ) {
		ec = make_error_code( std::errc::invalid_argument );
		return { .status = wait_status::failed };
	};

	auto ret = WaitForSingleObject( HANDLE(hprocess), timeout ? timeout->count() : INFINITE );

	set_error_if(ret == WAIT_FAILED, ec);

	switch (ret) {
	case WAIT_TIMEOUT:
		return { .status = wait_status::timeout };
	case WAIT_FAILED:
		return { .status = wait_status::failed };
	default:
	case WAIT_OBJECT_0:
	case WAIT_ABANDONED:
		break;
	}

	DWORD code = 0;
	if (!GetExitCodeProcess( HANDLE(hprocess), &code )) {
		set_error( ec );
		return { .status = wait_status::failed };
	}

	return { .status = wait_status::finished, .code = int(code) };
}

int kill(process_handle hprocess, int signal, std::error_code& ec) noexcept
{
	// TODO: add is_handle_valid()
	if( in( hprocess, process_handle(0), process_handle(-1) ) ) {
		ec = make_error_code( std::errc::invalid_argument );
		return -1;
	};

	switch (signal) {
	// TODO: SIGINT, SIGBREAK, SIGSTOP/SIGCONT
	case SIGTERM:
#ifdef SIGKILL
	// SIGKILL is not defined on MSVC, and mingw defines it only
	// under _POSIX
	case SIGKILL:
#endif
		return terminate(hprocess, ec);
	default:
		ec = make_error_code( std::errc::not_supported );
		return -1;
	}
}

int terminate(process_handle hprocess, std::error_code& ec) noexcept
{
	// TODO: add is_handle_valid()
	if( in( hprocess, process_handle(0), process_handle(-1) ) ) {
		ec = make_error_code( std::errc::invalid_argument );
		return -1;
	};

	auto ret = TerminateProcess( HANDLE(hprocess), 1 );

	set_error_if(!ret, ec);

	return ret ? 0 : -1;
}

// TODO: job objects can cap the memory and the CPU time of a process
AW_PLATFORM_EXP
bool is_supported(resource) noexcept
{
	return false;
}

namespace self {
AW_PLATFORM_EXP
int set_limit(resource, uintmax_t, std::error_code& ec) noexcept
{
	ec = std::make_error_code(std::errc::not_supported);
	return -1;
}

AW_PLATFORM_EXP
uintmax_t get_limit(resource, std::error_code& ec) noexcept
{
	ec = std::make_error_code(std::errc::not_supported);
	return unlimited;
}
} // namespace self
} // namespace aw::process::win32
