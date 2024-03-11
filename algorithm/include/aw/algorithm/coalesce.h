#ifndef aw_algorithm_coalesce_h
#define aw_algorithm_coalesce_h

namespace aw {
/*!
 * Returns first non-null pointer, similar to
 * the COALESCE function in SQL.
 */
template <typename T, typename... Ts>
T* coalesce(T* first, Ts*... args)
{
	if constexpr (sizeof...(Ts) > 0)
		return first ? first : coalesce(args...);
	return first;
}
} // namespace aw

#endif // aw_algorithm_coalesce_h
