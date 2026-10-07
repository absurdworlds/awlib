#ifndef aw_process_spawn_flags_h
#define aw_process_spawn_flags_h
#include <aw/types/support/enum.h>

namespace aw::process {
/*!
 * Options that change how spawn() starts the child.
 */
enum class spawn_flags : unsigned {
	none = 0,
	/*!
	 * Detach the child from the caller's terminal and process group,
	 * so that the signals sent to them (e.g. Ctrl+C) do not reach it.
	 *
	 * - On POSIX the child is started in a new session.
	 * - On Windows the child gets no console and a new process group.
	 *
	 * \note On POSIX the child still has to be wait()ed on, otherwise
	 * it lingers as a zombie after it exits, until the caller exits.
	 */
	detached = 1 << 0,
};

constexpr spawn_flags operator|(spawn_flags a, spawn_flags b)
{
	return spawn_flags(underlying(a) | underlying(b));
}

constexpr spawn_flags operator&(spawn_flags a, spawn_flags b)
{
	return spawn_flags(underlying(a) & underlying(b));
}

constexpr bool operator!(spawn_flags a)
{
	return !underlying(a);
}
} // namespace aw::process
#endif // aw_process_spawn_flags_h
