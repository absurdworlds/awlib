#ifndef aw_io_wait_status_h
#define aw_io_wait_status_h

namespace aw::io {

enum class wait_status {
	finished,
	timeout,
	failed,
};

} // namespace aw::io


#endif // aw_io_wait_status_h
