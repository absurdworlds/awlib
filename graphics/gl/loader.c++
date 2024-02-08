/*
 * Code in this file is placed in public domain.
 * Contact: Hedede <Haddayn@gmail.com>
 */
#include <aw/graphics/gl/loader.h>

#ifdef AW_SUPPORT_PLATFORM_APPLE
#include <dlfcn.h>

namespace aw::gl::apple {
unknown_fn* get_proc_address(const char* name)
{
	static void* image = nullptr;

	if (image == nullptr) {
		image = dlopen("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL", RTLD_LAZY);
		if (image == nullptr)
			return nullptr;
	}

	auto* symaddr = dlsym(image, name);
	return reinterpret_cast<unknown_fn*>(symaddr);
}
} // namespace aw::gl::apple
#endif//AW_SUPPORT_PLATFORM_APPLE

#ifdef AW_SUPPORT_PLATFORM_SUN
#include <dlfcn.h>
#include <stdio.h>

namespace aw::gl::sun {
unknown_fn* get_proc_address(const char* name)
{
	using gpasig = void*(const GLubyte*);

	static void*   image = nullptr;
	static gpasig* gpa   = nullptr;

	if (image == nullptr) {
		image = dlopen(nullptr, RTLD_LAZY | RTLD_LOCAL);
		if (image == nullptr)
			return nullptr;
		gpa = dlsym(image, "glXGetProcAddress");
	}

	if (gpa == nullptr)
		return dlsym(image, name);
	return gpa((const GLubyte*)name);
}
} // namespace aw::gl::sun
#endif /* __sgi || __sun */

#ifdef AW_SUPPORT_PLATFORM_WIN32
#include <aw/algorithm/in.h>
#include <aw/platform/windows.h>

#ifdef _MSC_VER
#pragma warning(disable: 4055)
#pragma warning(disable: 4054)
#pragma warning(disable: 4996)
#endif

namespace aw::wgl {
namespace {
bool TestPointer(PROC ptr)
{
	if (!ptr)
		return false;

	const auto test = intptr_t(ptr);

	return !in(test, 1, 2, 3, -1);
}
} // namespace

unknown_fn* get_proc_address(const char* name)
{
	HMODULE glMod = nullptr;
	PROC    pFunc = wglGetProcAddress((LPCSTR)name);
	if (TestPointer(pFunc))
		return (unknown_fn*)pFunc;
	glMod = GetModuleHandleA("OpenGL32.dll");
	return (unknown_fn*)GetProcAddress(glMod, (LPCSTR)name);
}
} // namespace aw::wgl
#endif//AW_SUPPORT_PLATFORM_WIN32

#ifdef AW_SUPPORT_PLATFORM_X11
#include <GL/glx.h>
namespace aw::glx {
unknown_fn* get_proc_address(const char* name)
{
	return (unknown_fn*)(*glXGetProcAddressARB)((const GLubyte*)name);
}
} // namespace aw::glx
#endif
