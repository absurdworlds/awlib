/*
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_graphics_tests_gl_context_h
#define aw_graphics_tests_gl_context_h
namespace aw::test {
/*!
 * A current GL 3.3 core context, with the awgl entry points loaded into it.
 *
 * Always from surfaceless EGL, so there is no window and no display server
 * involved. That holds even when awgl loads through GLX, because
 * glXGetProcAddress does not care which context is current.
 *
 * A machine with no usable driver gives a reason rather than crashing, so
 * tests check ok() first.
 */
struct gl_context {
	gl_context() noexcept;
	~gl_context();

	gl_context(gl_context const&) = delete;
	gl_context& operator=(gl_context const&) = delete;

	bool ok() const noexcept { return _ok; }
	//! Why the context could not be created; empty when ok().
	char const* error() const noexcept { return _error; }
	int missing_entry_points() const noexcept { return _missing; }

private:
	bool        _ok      = false;
	char const* _error   = "";
	int         _missing = 0;
};

/*!
 * Shared by every test in the binary: a context is current per-thread and the
 * libraries under it keep process-global state. Made on first use.
 */
gl_context& shared_gl_context();
} // namespace aw::test
#endif//aw_graphics_tests_gl_context_h
