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

//! How long to wait for a process; no value means indefinitely
using timeout_spec_ms = std::optional<std::chrono::milliseconds>;

} // namespace aw::io


#endif // aw_io_wait_status_h
