#ifndef aw_io_wait_status_h
#define aw_io_wait_status_h

#include <chrono>
#include <optional>

namespace aw::io {

enum class wait_status {
	finished,
	timeout,
	failed,
};

/*!
 * Result of a wait() or run() call.
 */
struct wait_result {
	wait_status status = wait_status::failed;

	//! Exit code that the process returned (passed to exit())
	int code = 0;

	//! Signal that killed the process, or 0 if it exited on its own.
	//! \note Meaningful only on POSIX. Always 0 on Windows.
	int signal = 0;

	//! Whether the wait ended with the process gone
	explicit constexpr operator bool() const
	{
		return status == wait_status::finished;
	}

	//! So that `run(...) == wait_status::finished` keeps working
	constexpr bool operator==(wait_status other) const
	{
		return status == other;
	}
};

//! How long to wait for a process; no value means indefinitely
using timeout_spec_ms = std::optional<std::chrono::milliseconds>;

} // namespace aw::io


#endif // aw_io_wait_status_h
