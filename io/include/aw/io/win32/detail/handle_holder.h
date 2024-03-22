#ifndef aw_io_handle_holder_h
#define aw_io_handle_holder_h

#include <aw/types/types.h>

#include <aw/io/export.h>

#include <utility>

namespace aw::io::win32::detail {

AW_IO_EXP
void close_handle( uintptr_t handle );

template<typename Handle>
class handle_holder {
public:
	handle_holder( Handle handle )
		: handle( handle )
	{}

	handle_holder(const handle_holder& other) = delete;
	handle_holder(handle_holder&& other)
		: handle(std::exchange(other.handle, Handle(0)))
	{
	}

	~handle_holder() { close_handle(handle); }

	handle_holder& operator=(const handle_holder& other) = delete;
	handle_holder& operator=(handle_holder&& other)
	{
		close_handle(handle);
		handle = std::exchange(other.handle, Handle(0));
		return *this;
	}

	operator Handle() { return static_cast<Handle>(handle); }

private:
	Handle handle;
};


} // namespace aw::io::win32::detail

#endif // aw_io_handle_holder_h
