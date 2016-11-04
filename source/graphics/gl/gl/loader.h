/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_internal_gl_loader_h
#define aw_internal_gl_loader_h
#include <aw/types/unknown.h>
#include <aw/config.h>
namespace aw {
namespace gl {

#if (AW_SUPPORT_PLATOFRM_APPLE)
namespace apple {
unknown_fn* get_proc_address(const char* name);
}
#endif//AW_SUPPORT_PLATOFRM_APPLE

#if (AW_SUPPORT_PLATOFRM_SUN)
namespace sun {
unknown_fn* get_proc_address(const char* name);
}
#endif//AW_SUPPORT_PLATOFRM_SUN

} // namespace gl


#if (AW_SUPPORT_PLATOFRM_WIN32)
namespace wgl {
unknown_fn* get_proc_address(const char* name);
}
#endif//AW_SUPPORT_PLATOFRM_WIN32

// TODO: __has_include(<GL/glx.h>)
#if (AW_SUPPORT_PLATFORM_X11)
namespace glx {
unknown_fn* get_proc_address(const char* name);
}
#endif//AW_SUPPORT_PLATOFRM_X11

namespace gl {
template <typename R, typename...Args>
void get_proc(R(*& func)(Args...), char const* name)
{
#if (AW_PLATFORM_SPECIFIX == AW_PLATFORM_APPLE)
	using apple::get_proc_address;
#elif (AW_PLATFORM == AW_PLATFORM_WIN32)
	using wgl::get_proc_address;
#elif (AW_PLATFORM == AW_PLATFORM_POSIX)
	using glx::get_proc_address;
#endif
	func = reinterpret_cast<R(*)(Args...)>( get_proc_address(name) );
};
} // namespace gl
} // namespace aw
#endif//aw_internal_gl_loader_h
