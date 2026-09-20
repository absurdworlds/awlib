#ifndef aw_process_posix_fork_h
#define aw_process_posix_fork_h
#include <aw/platform/export.h>
#include <aw/process/posix.h>

#include <concepts>
#include <system_error>
#include <type_traits>

namespace aw::process::posix {
//! What fork() returns on the child side
constexpr auto child_process_handle = process_handle(0);

/*!
 * Fork the calling process.
 *
 * \return In the parent, the handle of the child;
 *         in the child, `child_process_handle`;
 *         on failure, `invalid_process_handle`.
 */
AW_PLATFORM_EXP process_handle fork(std::error_code& ec) noexcept;
inline process_handle fork()
{
	std::error_code ec;
	return fork(ec);
}

namespace current_process {
/*!
 * Exit the calling process immediately with \a code.
 * Does not run destructors, atexit handlers, and does not flush any streams.
 *
 * Meant for the child side of a fork(), which must not run the parent's cleanup.
 */
[[noreturn]] AW_PLATFORM_EXP void exit_now(int code) noexcept;
} // namespace current_process

/*!
 * Run \a body in a forked child, which then exits with the value it
 * returns (0 if it returns nothing). The child never returns to the caller.
 *
 * \note
 * Only the forking thread exists in the child, so \a body must not depend
 * on other threads or on locks they might be holding.
 *
 * \return Handle of the child, or `invalid_process_handle` if the fork failed.
 */
template<std::invocable Body>
process_handle fork(Body&& body, std::error_code& ec) noexcept
{
	auto handle = fork(ec);
	if (handle == child_process_handle) {
		if constexpr (std::is_void_v<std::invoke_result_t<Body>>) {
			body();
			current_process::exit_now(0);
		} else {
			current_process::exit_now( body() );
		}
	}
	return handle;
}

template<std::invocable Body>
process_handle fork(Body&& body) noexcept
{
	std::error_code ec;
	return fork(std::forward<Body>(body), ec);
}
} // namespace aw::process::posix
#endif // aw_process_posix_fork_h
