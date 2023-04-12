#include <aw/config.h>

#if __cplusplus >= 201103L
#define aw_constexpr constexpr
#else
#define aw_constexpr const
#endif
