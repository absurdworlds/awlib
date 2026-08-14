#ifndef aw_io_handle_holder_h
#define aw_io_handle_holder_h

#include <aw/types/types.h>

#include <aw/io/export.h>

#include <utility>

namespace aw::io::win32::detail {

AW_IO_EXP
void close_handle( uintptr_t handle );

//! A wrapper that owns the handle and automatically closes it
template<typename Handle>
class handle_holder {
public:
	//! Equivalent to NULL handle, can't be closed
	static constexpr Handle null = Handle(0);
	//! Equivalent to INVALID_HANDLE_VALUE, can't be closed
	static constexpr Handle invalid = Handle(-1);

	handle_holder( Handle handle )
		: handle( handle )
	{}

	handle_holder(const handle_holder& other) = delete;
	handle_holder(handle_holder&& other)
		: handle(std::exchange(other.handle, invalid))
	{
	}

	~handle_holder() { release(); }

	handle_holder& operator=(const handle_holder& other) = delete;
	handle_holder& operator=(handle_holder&& other)
	{
		if (this == &other)
			return *this;

		release();
		handle = std::exchange(other.handle, invalid);
		return *this;
	}

	operator Handle() const { return handle; }

private:
	void release()
	{
		if (handle == invalid || handle == null)
			return;

		close_handle(handle);
		handle = invalid;
	}

	Handle handle;
};


} // namespace aw::io::win32::detail

#endif // aw_io_handle_holder_h
