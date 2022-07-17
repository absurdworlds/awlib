#include <aw/assert/assert_handler.h>
#include <iostream>

#include <aw/utility/unicode/convert.h>
#include <aw/platform/windows.h>

namespace aw {
namespace win32 {

struct winapi_module {
	wchar_t const* name;
	bool    loaded = false;
	HMODULE handle = nullptr;
};

struct {
	winapi_module api_ms_win_rtcore_ntuser_window_l1_1_0 = { L"api_ms_win_rtcore_ntuser_window_l1_1_0" };
	winapi_module ext_ms_win_ntuser_dialogbox_l1_1_0 = { L"ext_ms_win_ntuser_dialogbox_l1_1_0" };

	winapi_module user32 = { L"user32" };
} static winapi_modules;

struct winapi_function {
	char const* name;

	winapi_module& module;
	winapi_module& fallback_module;

	bool  loaded  = false;
	void* pointer = nullptr;
};


struct winapi_functions {
	winapi_function MessageBoxW =
	{
		"MessageBoxW",
		winapi_modules.ext_ms_win_ntuser_dialogbox_l1_1_0,
		winapi_modules.user32,
	};
	winapi_function GetActiveWindow =
	{
		"GetActiveWindow",
		winapi_modules.api_ms_win_rtcore_ntuser_window_l1_1_0,
		winapi_modules.user32,
	};
} static winapi_functions;


HMODULE load_module(winapi_module& module, winapi_module& fallback_module)
{
	auto load = [] (winapi_module& module)
	{
		if (!module.loaded)
		{
			module.loaded = true;
			module.handle = LoadLibraryW(module.name);
		}
	};

	load(module);

	if (!module.handle && &module != &fallback_module)
	{
		load(fallback_module);
		return fallback_module.handle;
	}

	return module.handle;
}

void* load_function(winapi_function& winapi_function)
{
	if (!winapi_function.loaded) {
		auto module = load_module(winapi_function.module, winapi_function.fallback_module);
		auto* proc  = GetProcAddress(module, winapi_function.name);
		// reinterpret_cast to silence -Wms-extensions
		winapi_function.pointer = reinterpret_cast<void*>(proc);
	}
	return winapi_function.pointer;
}

void* load_function(winapi_function winapi_functions::*index)
{
	return load_function(winapi_functions.*index);
}

// TODO: Hmm... I like this, maybe I should make an API generator
#define aw_load_winapi_func(name) reinterpret_cast<decltype(::name)*>(load_function(&aw::win32::winapi_functions::name))


assert_action assert_fail(string_view assertion, source_location location)
{
	const auto MessageBoxW = aw_load_winapi_func(MessageBoxW);
	if (MessageBoxW)
	{
		const auto GetActiveWindow = aw_load_winapi_func(GetActiveWindow);

		auto* active_window = (GetActiveWindow) ? GetActiveWindow() : nullptr;

		constexpr string_view message_template =
R"(Assertion failed: "{}"

In file: {}

Function: {}

Line: {}, column: {}

Press:
- "Retry" to debug (if debugger is attached)
- "Ignore" to continue execution (application may crash)
- "Abort" to exit the application)";

		const auto message = format(
		    message_template,
		    assertion,
		    location.file_name(),
		    location.function_name(),
		    location.line(),
		    location.column());

		const auto res = MessageBoxW(
		    active_window,
		    unicode::widen(message).data(),
		    L"ASSERTION FAILED",
		    MB_ICONERROR | MB_ABORTRETRYIGNORE | MB_SETFOREGROUND | MB_TASKMODAL);

		if (res == IDIGNORE)
			return assert_action::ignore;
		if (res == IDRETRY)
			return assert_action::stop;
		if (res == IDABORT)
			return assert_action::abort;
	}

	return assert_action::abort;
}
} // namespace win32
} // namespace aw
