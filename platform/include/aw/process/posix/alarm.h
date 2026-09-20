#ifndef aw_process_posix_alarm_h
#define aw_process_posix_alarm_h
#include <aw/platform/export.h>

#include <chrono>

namespace aw::process::posix {
namespace self {
/*!
 * Sets an alarm for the calling process, replacing any alarm set
 * earlier. It delivers SIGALRM after the set \a delay.
 * A zero \a delay cancels the alarm.
 *
 * \return Time left on the previous alarm, zero if there was no alarm.
 *
 * \note Primary use in awlib is for unit tests: testing a signal arriving during a syscall,
 *       and setting a timeout on child processes.
 */
AW_PLATFORM_EXP std::chrono::microseconds alarm(std::chrono::microseconds delay) noexcept;
} // namespace self
} // namespace aw::process::posix
#endif // aw_process_posix_alarm_h
