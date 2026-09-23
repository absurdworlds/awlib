// This header is obsolete. Please use this one instead:
#include <aw/process/win32.h>

#if !defined(aw_io_win32_process_h_warned) &&  __cplusplus >= 202302L
#define aw_io_win32_process_h_warned
#warning "<aw/io/win32/process.h> is obsolete and will be removed soon. Please use <aw/process/win32.h> instead."
#endif

#if defined(AW_PROCESS_HAS_HANDLE_COUNT)
#define AW_IO_HAS_HANDLE_COUNT AW_PROCESS_HAS_HANDLE_COUNT
#endif

namespace aw::io {
using process::wait_status;
using process::wait_result;
using process::timeout_spec_ms;
namespace win32 {
using process::win32::process_handle;
using process::win32::invalid_process_handle;
using process::win32::process_holder;
using process::win32::close_handle;
using process::win32::spawn;
using process::win32::wait;
using process::win32::kill;
using process::win32::terminate;
using process::win32::run;
using process::win32::executable_name;
#if defined(AW_PROCESS_HAS_HANDLE_COUNT)
using process::win32::handle_count;
#endif
namespace current_process = process::win32::self;
} // namespace win32
} // namespace aw::io
