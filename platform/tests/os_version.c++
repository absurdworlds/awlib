/*
 * Copyright (C) 2016 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/platform/os_version.h>
#include <iostream>
int main()
{
#if defined(AW_SUPPORT_PLATFORM_POSIX)
	{
		auto ver = aw::platform::posix::get_os_version();
		std::cout << ver.sysname << " / " << ver.machine << " / " << ver.version << " / " << ver.version << '\n';
	}
#endif
#if defined(AW_SUPPORT_PLATFORM_WIN32)
	{
		auto ver = aw::platform::win32::get_os_version();
		std::cout << ver.sysname << " / " << ver.machine << " / " << ver.version << " / " << ver.version << '\n';
	}
#endif
}
