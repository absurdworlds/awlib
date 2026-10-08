#ifndef aw_io_pipe_h
#define aw_io_pipe_h
#include <aw/io/native_file.h>
#include <aw/platform/export.h>

#include <system_error>

namespace aw::io {
#if defined(AW_SUPPORT_PLATFORM_POSIX)
namespace posix {
//! Two ends of a pipe: what is written into \a write can be read from \a read
struct pipe_ends {
	file read;
	file write;
};

/*!
 * Create an anonymous pipe.
 *
 * \note The ends are not inherited by child processes,
 * unless passed to the child explicitly (see process::stdio).
 *
 * \return The ends of the pipe; on failure, both are closed.
 */
AW_PLATFORM_EXP pipe_ends pipe(std::error_code& ec) noexcept;
inline pipe_ends pipe() noexcept
{
	std::error_code ec;
	return pipe(ec);
}
} // namespace posix
#endif

#if defined(AW_SUPPORT_PLATFORM_WIN32)
namespace win32 {
//! Two ends of a pipe: what is written into \a write can be read from \a read
struct pipe_ends {
	file read;
	file write;
};

/*!
 * Create an anonymous pipe.
 *
 * \note The ends are not inherited by child processes,
 * unless passed to the child explicitly (see process::stdio).
 *
 * \return The ends of the pipe; on failure, both are closed.
 */
AW_PLATFORM_EXP pipe_ends pipe(std::error_code& ec) noexcept;
inline pipe_ends pipe() noexcept
{
	std::error_code ec;
	return pipe(ec);
}
} // namespace win32
#endif

namespace native {
#if   (AW_PLATFORM == AW_PLATFORM_POSIX)
using posix::pipe_ends;
using posix::pipe;
#elif (AW_PLATFORM == AW_PLATFORM_WIN32)
using win32::pipe_ends;
using win32::pipe;
#endif
} // namespace native
} // namespace aw::io
#endif // aw_io_pipe_h
