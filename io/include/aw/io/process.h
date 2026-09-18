// This header is obsolete. Please use this one instead:
#include <aw/process.h>

#if !defined(aw_io_process_h_warned) &&  __cplusplus >= 202302L
#define aw_io_process_h_warned
#warning "<aw/io/process.h> is obsolete and will be removed soon. Please use <aw/process.h> instead."
#endif

namespace aw::io {
using process::wait_status;
using process::wait_result;
using process::timeout_spec_ms;
#if (AW_PLATFORM == AW_PLATFORM_POSIX) || (AW_PLATFORM == AW_PLATFORM_WIN32)
using process::process_handle;
using process::invalid_process_handle;
using process::spawn;
using process::kill;
using process::terminate;
using process::wait;
using process::run;
using process::executable_name;
#endif
} // namespace aw::io
