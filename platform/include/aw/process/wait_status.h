#ifndef aw_process_wait_status_h
#define aw_process_wait_status_h

#include <chrono>
#include <optional>

namespace aw::process {

enum class wait_status {
	finished,
	timeout,
	failed,
};

constexpr int no_signal = 0;

/*!
 * Result of a wait() or run() call.
 */
struct wait_result {
	wait_status status = wait_status::failed;

	//! Exit code that the process returned (passed to exit())
	int code = 0;

	//! Signal that killed the process, or `no_signal` if it exited on its own.
	//! \note Meaningful only on POSIX. Always `no_signal` on Windows.
	int signal = no_signal;

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

} // namespace aw::process


#endif // aw_process_wait_status_h
