#ifndef aw_platform_windows_h
#define aw_platform_windows_h

#include <aw/config.h>

#ifdef AW_SUPPORT_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN 1
#define NOMINMAX
#include <windows.h>
#endif // AW_SUPPORT_PLATFORM_WIN32

#endif // aw_platform_windows_h
