// This header is obsolete. Please use this one instead:
#include <aw/process/wait_status.h>

#if !defined(aw_io_wait_status_h_warned) &&  __cplusplus >= 202302L
#define aw_io_wait_status_h_warned
#warning "<aw/io/wait_status.h> is obsolete and will be removed soon. Please use <aw/process/wait_status.h> instead."
#endif

namespace aw::io {
using process::wait_status;
using process::wait_result;
using process::timeout_spec_ms;
} // namespace aw::io
