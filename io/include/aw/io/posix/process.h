// This header is obsolete. Please use this one instead:
#include <aw/process/posix.h>

#if !defined(aw_io_posix_process_h_warned) &&  __cplusplus >= 202302L
#define aw_io_posix_process_h_warned
#warning "<aw/io/posix/process.h> is obsolete and will be removed soon. Please use <aw/process/posix.h> instead."
#endif

namespace aw::io {
using process::wait_status;
using process::wait_result;
using process::timeout_spec_ms;
namespace posix {
using process::posix::process_handle;
using process::posix::invalid_process_handle;
using process::posix::spawn;
using process::posix::wait;
using process::posix::kill;
using process::posix::terminate;
using process::posix::run;
using process::posix::executable_name;
} // namespace posix
} // namespace aw::io
