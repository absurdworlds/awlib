#ifndef aw_process_limits_h
#define aw_process_limits_h
#include <aw/platform/export.h>

#include <cstdint>
#include <system_error>

namespace aw::process {
/*!
 * Resources that can be limited for a process.
 * \note Not all resources are supported on all platforms.
 */
enum class resource {
	address_space, //!< bytes of virtual memory
	stack,         //!< bytes of the main thread's stack
	core_file,     //!< bytes of a core dump, 0 disables dumps
	cpu_time,      //!< seconds of CPU time, SIGXCPU when exceeded
	open_files,    //!< number of file descriptors
};

//! Limit value that means "no limit"
constexpr uintmax_t unlimited = ~uintmax_t(0);

#if defined(AW_SUPPORT_PLATFORM_POSIX)
namespace posix {
/*!
 * POSIX resource limits:
 * - the soft limit is enforced,
 * - the hard limit is the ceiling on the soft limit.
 *
 * \note Unprivileged process can not raise hard limits, so after
 * lowering the hard limit, the process cannot raise it again afterwards.
 */
struct limit {
	uintmax_t soft = unlimited;
	uintmax_t hard = unlimited;
};

/*!
 * \return Whether \a res is supported by set_limit/get_limit
 */
AW_PLATFORM_EXP bool is_supported(resource res) noexcept;

namespace self {
/*!
 * Set both limits on \a res, see setrlimit(2).
 *
 * \return 0 on success or -1 on failure.
 */
AW_PLATFORM_EXP int set_limits(resource res, limit value, std::error_code& ec) noexcept;
inline int set_limits(resource res, limit value)
{
	std::error_code ec;
	return set_limits(res, value, ec);
}

/*!
 * Current limits on \a res.
 *
 * \return The limits; if they could not be read, \a ec is set and
 *         both are `unlimited`.
 */
AW_PLATFORM_EXP limit get_limits(resource res, std::error_code& ec) noexcept;
inline limit get_limits(resource res)
{
	std::error_code ec;
	return get_limits(res, ec);
}

/*!
 * Limits \a res to \a value.
 *
 * \return 0 on success or -1 on failure.
 *
 * \note Not every platform can limit every resource. For the resources
 *       that cannot be limited \a ec is `std::errc::not_supported`.
 *
 * \note An unprivileged process can't raise the limit back up.
 * \note The limit is also inherited by the children.
 */
inline int set_limit(resource res, uintmax_t value, std::error_code& ec) noexcept
{
	return set_limits(res, { value, value }, ec);
}

inline int set_limit(resource res, uintmax_t value)
{
	std::error_code ec;
	return set_limit(res, value, ec);
}

/*!
 * The limit currently enforced on \a res.
 *
 * \return The limit, or `unlimited` if there is no limit
 *         or it could not be read (\a ec tells which).
 */
inline uintmax_t get_limit(resource res, std::error_code& ec) noexcept
{
	return get_limits(res, ec).soft;
}

inline uintmax_t get_limit(resource res)
{
	std::error_code ec;
	return get_limit(res, ec);
}
} // namespace self
} // namespace posix
#endif

#if defined(AW_SUPPORT_PLATFORM_WIN32)
namespace win32 {
/*!
 * \return Whether \a res is supported set_limit/get_limit
 */
AW_PLATFORM_EXP bool is_supported(resource res) noexcept;

namespace self {
/*!
 * Limits \a res to \a value.
 *
 * \return 0 on success or -1 on failure.
 *
 * \note Not every platform can limit every resource. For the resources
 *       that cannot be limited \a ec is `std::errc::not_supported`.
 *
 * \note The limit also applies to the children.
 */
AW_PLATFORM_EXP int set_limit(resource res, uintmax_t value, std::error_code& ec) noexcept;
inline int set_limit(resource res, uintmax_t value)
{
	std::error_code ec;
	return set_limit(res, value, ec);
}

/*!
 * The limit currently enforced on \a res.
 *
 * \return The limit, or `unlimited` if there is no limit
 *         or it could not be read (\a ec tells which).
 */
AW_PLATFORM_EXP uintmax_t get_limit(resource res, std::error_code& ec) noexcept;
inline uintmax_t get_limit(resource res)
{
	std::error_code ec;
	return get_limit(res, ec);
}
} // namespace self
} // namespace win32
#endif

#if   (AW_PLATFORM == AW_PLATFORM_POSIX)
using posix::is_supported;
namespace self {
using posix::self::set_limit;
using posix::self::get_limit;
} // namespace self
#elif (AW_PLATFORM == AW_PLATFORM_WIN32)
using win32::is_supported;
namespace self {
using win32::self::set_limit;
using win32::self::get_limit;
} // namespace self
#endif
} // namespace aw::process
#endif // aw_process_limits_h
