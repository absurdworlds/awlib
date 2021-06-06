#ifndef aw_utility_assert_h
#define aw_utility_assert_h
#include <source_location>

#include <aw/meta/pp/macro.h>
#include <aw/meta/pp/tuple.h>

#define aw_assert_level_default 1
#define aw_assert_level_normal aw_assert_level_default
#define aw_assert_level_develop 2
#define aw_assert_level_audit 3

#ifndef aw_current_assert_level
#define aw_current_assert_level aw_assert_level_default
#endif

namespace aw {

enum class assert_level {
	off,
	normal  = aw_assert_level_default,
	develop = aw_assert_level_develop,
	audit   = aw_assert_level_audit,
	current = aw_current_assert_level,
};

void assert_fail(const char* assertion, std::source_location location = std::source_location::current());

template <assert_level level = assert_level::normal>
bool assert_check(bool cond, const char* msg, std::source_location loc = std::source_location::current())
{
	if constexpr(level < assert_level::current)
		return true;

	if (!cond)
		assert_fail(msg, loc);
	return cond;
}
} // namespace aw

#if (aw_current_assert_level >= aw_assert_level_default)
#define aw_assert_eval_default(...) (__VA_ARGS__)
#else
#define aw_assert_eval_default(...) (true || __VA_ARGS__)
#endif

#if (aw_current_assert_level >= aw_assert_level_develop)
#define aw_assert_eval_develop(...) (__VA_ARGS__)
#else
#define aw_assert_eval_develop(...) (true || __VA_ARGS__)
#endif

#if (aw_current_assert_level >= aw_assert_level_audit)
#define aw_assert_eval_audit(...) (__VA_ARGS__)
#else
#define aw_assert_eval_audit(...) (true || __VA_ARGS__)
#endif

#define aw_assert_eval_normal(cond) aw_assert_eval_default(cond)

#define aw_assert_eval(level, cond) APPLY(CONCAT(aw_assert_eval_, level), cond)

#if 0
#define aw_assert_default(cond) ::aw::assert_check<::aw::assert_level::normal>(cond, #cond);
#define aw_assert_develop(cond) ::aw::assert_check<::aw::assert_level::develop>(cond, #cond);
#define aw_assert_audit(cond)   ::aw::assert_check<::aw::assert_level::audit>(cond, #cond);
#define aw_assert_(cond) aw_assert_default(cond)
#define aw_assert_select(...) APPLY(CONCAT, aw_assert_, FIRST(__VA_ARGS__))
#define aw_assert(cond, ...) EXPAND( aw_assert_select(__VA_ARGS__) APPLY( aw_assert_eval(__VA_ARGS__), cond))
#endif


#define aw_assert_select_level_audit   ::aw::assert_level::audit
#define aw_assert_select_level_develop ::aw::assert_level::develop
#define aw_assert_select_level_default ::aw::assert_level::normal
#define aw_assert_select_level_normal  ::aw::assert_level::normal

#define aw_assert_select(level) ::aw::assert_check< CONCAT( aw_assert_select_level_, level ) >

#define aw_assert_get_level(default, ...) FIRST(__VA_ARGS__ __VA_OPT__(,) default)
#define aw_assert_get_message(default, ...) SECOND(__VA_ARGS__ __VA_OPT__(,) default, default)

#define aw_assert(cond, ...) \
	aw_assert_select(aw_assert_get_level(default, __VA_ARGS__)) \
	( \
	  aw_assert_eval(aw_assert_get_level(default, __VA_ARGS__), cond), \
	  aw_assert_get_message(#cond, __VA_ARGS__) \
	)


#endif//aw_utility_assert_h
