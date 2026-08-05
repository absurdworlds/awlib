/*
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include "gl_context.h"

// awgl's headers have to come before any header that pulls in the system
// GL/gl.h, whose GL_* macros would clobber the enum of the same names.
#include <aw/gl/api/gl_33.h>
#include <aw/gl/api/gl_46.h>

namespace aw::test {
namespace {
bool loaded_entry_points(int& missing, char const*& error)
{
	auto result = gl::sys::load_functions_3_3();
	if (!result) {
		error = "could not load the GL 3.3 entry points";
		return false;
	}
	missing = result.num_missing();
	return true;
}
} // namespace
} // namespace aw::test

// EGL without a surface: no window, and no display server of any kind.
#include <EGL/egl.h>
#include <EGL/eglext.h>

namespace aw::test {
namespace {
EGLDisplay display = EGL_NO_DISPLAY;
EGLContext context = EGL_NO_CONTEXT;
} // namespace

gl_context::gl_context() noexcept
{
	display = eglGetPlatformDisplay(EGL_PLATFORM_SURFACELESS_MESA,
	                                EGL_DEFAULT_DISPLAY, nullptr);
	if (display == EGL_NO_DISPLAY) {
		_error = "no surfaceless EGL display";
		return;
	}

	if (!eglInitialize(display, nullptr, nullptr)) {
		_error = "eglInitialize failed";
		return;
	}

	// EGL defaults to OpenGL ES, awlib wants desktop GL.
	if (!eglBindAPI(EGL_OPENGL_API)) {
		_error = "EGL does not offer desktop OpenGL";
		return;
	}

	EGLint const config_attrs[] = {
		EGL_SURFACE_TYPE,    EGL_PBUFFER_BIT,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
		EGL_NONE
	};

	EGLConfig config;
	EGLint    num_configs = 0;
	if (!eglChooseConfig(display, config_attrs, &config, 1, &num_configs)
	    || num_configs == 0) {
		_error = "no usable EGLConfig";
		return;
	}

	EGLint const context_attrs[] = {
		EGL_CONTEXT_MAJOR_VERSION,        3,
		EGL_CONTEXT_MINOR_VERSION,        3,
		EGL_CONTEXT_OPENGL_PROFILE_MASK,  EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT,
		EGL_NONE
	};

	context = eglCreateContext(display, config, EGL_NO_CONTEXT, context_attrs);
	if (context == EGL_NO_CONTEXT) {
		_error = "no GL 3.3 core context";
		return;
	}

	// Binding a context with no surface needs EGL_KHR_surfaceless_context.
	if (!eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, context)) {
		_error = "could not make a surfaceless context current";
		return;
	}

	_ok = loaded_entry_points(_missing, _error);
}

gl_context::~gl_context()
{
	if (display == EGL_NO_DISPLAY)
		return;
	eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	if (context != EGL_NO_CONTEXT)
		eglDestroyContext(display, context);
	eglTerminate(display);
}
} // namespace aw::test


namespace aw::test {
gl_context& shared_gl_context()
{
	static gl_context ctx;
	return ctx;
}
} // namespace aw::test
