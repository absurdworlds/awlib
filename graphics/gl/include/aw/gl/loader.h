/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_gl_loader_h
#define aw_gl_loader_h
#include <aw/types/unknown.h>
#include <aw/config.h>
#include <type_traits>
namespace aw {
namespace gl {

#if (AW_SUPPORT_PLATFORM_APPLE)
namespace apple {
unknown_fn* get_proc_address(const char* name);
}
#endif//AW_SUPPORT_PLATFORM_APPLE

#if (AW_SUPPORT_PLATFORM_SUN)
namespace sun {
unknown_fn* get_proc_address(const char* name);
}
#endif//AW_SUPPORT_PLATFORM_SUN

} // namespace gl


#if (AW_SUPPORT_PLATFORM_WIN32)
namespace wgl {
unknown_fn* get_proc_address(const char* name);
}
#endif//AW_SUPPORT_PLATFORM_WIN32

// TODO: __has_include(<GL/glx.h>)
#if (AW_SUPPORT_PLATFORM_X11)
namespace glx {
unknown_fn* get_proc_address(const char* name);
}
#endif//AW_SUPPORT_PLATFORM_X11

namespace gl {
template <typename Function>
	requires std::is_function_v<Function>
void get_proc(Function*& func, char const* name)
{
#if AW_SUPPORT_PLATFORM_APPLE
	using apple::get_proc_address;
#elif AW_SUPPORT_PLATFORM_WIN32
	using wgl::get_proc_address;
#elif AW_SUPPORT_PLATFORM_X11
	using glx::get_proc_address;
#endif
	func = reinterpret_cast<Function*>( get_proc_address(name) );
};
} // namespace gl
} // namespace aw
#endif//aw_gl_loader_h
