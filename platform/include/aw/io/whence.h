#ifndef aw_io_whence_h
#define aw_io_whence_h
#include <aw/io/file_mode.h>

#include <cassert>
#include <cstdio>

namespace aw::io {
/*!
 * Convert \a mode to the `whence` argument of lseek() and fseek().
 * Both take the same SEEK_SET, SEEK_CUR and SEEK_END constants.
 */
inline int get_whence(seek_mode mode)
{
	switch (mode) {
	case seek_mode::set:
		return SEEK_SET;
	case seek_mode::end:
		return SEEK_END;
	case seek_mode::cur:
		return SEEK_CUR;
	}

	assert(!"Invalid seek value");
	// intentionally invalid value, lseek and fseek should fail with EINVAL
	return -1;
}
} // namespace aw::io
#endif//aw_io_whence_h
