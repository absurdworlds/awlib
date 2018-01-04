/*
 * Copyright (C) 2016 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/platform/os_version.h>
#include <aw/types/string_view.h>

namespace aw::platform {
namespace {
// Functions velow should never fail, but there *is* a possibility for them to fail
const os_name unknown_os{"Unknown", "Unknown", "Unknown", "Unknown"};
}
} // namespace aw::platform

#if defined(AW_SUPPORT_PLATFORM_POSIX)
#include <sys/utsname.h>
namespace aw::platform::posix {
os_name get_os_version()
{
	struct utsname un;
	if (uname(&un) == -1)
		return unknown_os;

	return {
		un.sysname,
		un.machine,
		un.release,
		un.version
	};
}
} // namespace posix
#endif

#if defined(AW_SUPPORT_PLATFORM_WIN32)
#include <aw/utility/unicode/convert.h>
#include <aw/utility/to_string.h>
#include <windows.h>
namespace aw::platform::win32 {
namespace {
string_view get_os_name(OSVERSIONINFOEXW& info)
{
	using namespace std::string_view_literals;
	if (info.dwPlatformId < VER_PLATFORM_WIN32_NT) {
		if (info.dwMajorVersion == 4 && info.dwMinorVersion == 0)
			return "Windows 95"sv;
		if (info.dwMajorVersion == 4 && info.dwMinorVersion == 10)
			return "Windows 98"sv;
		if (info.dwMajorVersion == 4 && info.dwMinorVersion == 90)
			return "Windows Me"sv;
		return "Windows";
	}

	if (info.dwMajorVersion >= 10) {
		bool win_server = info.wProductType != VER_NT_WORKSTATION;
		return win_server ? "Windows Server 2016"sv : "Windows 10"sv;
	}
	if (info.dwMajorVersion >= 6) {
		bool win_server = info.wProductType != VER_NT_WORKSTATION;
		if (info.dwMinorVersion == 3)
			return win_server ? "Windows Server 2012 R2"sv : "Windows 8.1"sv;
		if (info.dwMinorVersion == 2)
			return win_server ? "Windows Server 2012"sv : "Windows 8"sv;
		if (info.dwMinorVersion == 1)
			return win_server ? "Windows Server 2008 R2"sv : "Windows 7"sv;
		if (info.dwMinorVersion == 0)
			return win_server ? "Windows Server 2008"sv : "Windows Vista"sv;
	}
	if (info.dwMajorVersion >= 5) {
		if (info.dwMinorVersion == 2)	{
			if (GetSystemMetrics(SM_SERVERR2) != 0)
				return "Windows Server 2003 R2"sv;
			if (info.wSuiteMask & VER_SUITE_WH_SERVER)
				return "Windows Home Server"sv;
			if (info.wSuiteMask & VER_SUITE_WH_SERVER)
				return "Windows Server 2003"sv;
			return "Windows XP Professional"sv;
		}
		if (info.dwMinorVersion == 1)
			return "Windows XP"sv;
		if (info.dwMinorVersion == 0)
			return "Windows 2000"sv;
	}
	return "Windows NT"sv;
}

string_view get_architecture()
{
	using GETSYSTEMINFO = void(WINAPI*) (LPSYSTEM_INFO);

	GETSYSTEMINFO GetSystemInfo = (GETSYSTEMINFO)GetProcAddress(GetModuleHandleW(L"kernel32.dll"), "GetNativeSystemInfo");
	if (GetSystemInfo == NULL) GetSystemInfo = ::GetSystemInfo;

	SYSTEM_INFO sys;
	GetSystemInfo(&sys);

	using namespace std::string_view_literals;
	switch (sys.wProcessorArchitecture) {
	case PROCESSOR_ARCHITECTURE_AMD64:
		return "x86_64"sv;
	case PROCESSOR_ARCHITECTURE_ARM:
		return "arm"sv;
	case PROCESSOR_ARCHITECTURE_IA64:
		return "ia64"sv;
	case PROCESSOR_ARCHITECTURE_INTEL:
		return "x86"sv;
	};
	return "Unknown"sv;
}

std::string get_version(OSVERSIONINFOEXW& info)
{
	format::pretty_print fmt;
	fmt.convert(info.dwMajorVersion);
	fmt.literal(".");
	fmt.convert(info.dwMinorVersion);
	return fmt;
}

std::string get_version_full(OSVERSIONINFOEXW& info)
{
	format::pretty_print fmt;
	fmt.convert(info.dwMajorVersion);
	fmt.literal(".");
	fmt.convert(info.dwMinorVersion);
	fmt.literal(".");
	fmt.convert(info.dwBuildNumber);
	return fmt;
}

std::string get_service_pack_ver(OSVERSIONINFOEXW& info)
{
	return unicode::narrow(wstring_view{info.szCSDVersion});
}

std::string get_service_pack_ver_ex(OSVERSIONINFOEXW& info)
{
	format::pretty_print fmt;
	fmt.convert(info.wServicePackMajor);
	if (info.wServicePackMinor > 0) {
		fmt.literal(".");
		fmt.convert(info.wServicePackMinor);
	}
	return fmt;
}

std::string get_build(OSVERSIONINFOEXW& info)
{
	std::string ver;
	ver += get_version_full( info );
	auto sp = get_service_pack_ver( info );
	if (!sp.empty()) {
		ver += ' ';
		ver += sp;
	}
	return ver;
}

std::string get_build_ex(OSVERSIONINFOEXW& info)
{
	std::string ver;
	ver += get_version_full( info );
	if (info.wServicePackMajor > 0) {
		ver += " Service Pack ";
		ver += get_service_pack_ver_ex( info );
	}
	return ver;
}

} // namespace

os_name get_os_version()
{
	OSVERSIONINFOEXW osvi;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEXW));

	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXW);
	if ( GetVersionExW( (OSVERSIONINFOW*) &osvi ) )
		return {
			std::string( get_os_name( osvi ) ),
			std::string( get_architecture() ),
			get_version( osvi ),
			get_build_ex( osvi )
		};

	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOW);
	if ( GetVersionExW( (OSVERSIONINFOW*) &osvi ) )
		return {
			std::string( get_os_name( osvi ) ),
			std::string( get_architecture() ),
			get_version( osvi ),
			get_build( osvi )
		};

	return unknown_os;
}
} // namespace win32
#endif
