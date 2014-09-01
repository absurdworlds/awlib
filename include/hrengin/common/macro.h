#ifndef _hrengin_hrenginmacro_
#define _hrengin_hrenginmacro_

#include <hrengin/common/config.h>

/* Make a bit mask of a desired bit */
#define BIT(x) (1<<(x))

#define __FUNC__ __func__ 

/* Stringize */
#define TO_STR(x) TO_STR1(x)
#define TO_STR1(x) #x

/* Concatenate */
#define CONCAT(arg1, arg2)   CONCAT1(arg1, arg2)
#define CONCAT1(arg1, arg2)  CONCAT2(arg1, arg2)
#define CONCAT2(arg1, arg2)  arg1##arg2

/* Expand tokens — stupid MSVC glues __VA_ARGS__ */
#define MSVC_DEVELOPERS_MUST_BE_FUCKED_BY_KEYMAN_TEN_TIMES_EACH(x) x
#define FUCK_MSVC_DEVELOPERS(x) x
#define EXPAND(x) x

/* Vararg processing macros
   Uses the trick: depending on number of arguments, the desired macro shifts
   to a NAME position.

   Use FOR_EACH macro, other macros are to be used only internally by FOR_EACH.
   To process more arguments, add another FE_ macro and add more arguments to 
   GET_MACRO
 */
#define GET_MACRO(_1,_2,_3,_4,_5,_6,NAME,...) NAME

#define FE_1(DO, X, ...) EXPAND(DO(X))
#define FE_2(DO, X, ...) EXPAND(DO(X)FE_1(DO, __VA_ARGS__))
#define FE_3(DO, X, ...) EXPAND(DO(X)FE_2(DO, __VA_ARGS__))
#define FE_4(DO, X, ...) EXPAND(DO(X)FE_3(DO, __VA_ARGS__))
#define FE_5(DO, X, ...) EXPAND(DO(X)FE_4(DO, __VA_ARGS__))
#define FE_6(DO, X, ...) EXPAND(DO(X)FE_5(DO, __VA_ARGS__))
#define FE_7(DO, X, ...) EXPAND(DO(X)FE_6(DO, __VA_ARGS__))
#define FE_8(DO, X, ...) EXPAND(DO(X)FE_7(DO, __VA_ARGS__))

#define FOR_EACH(NAME,...) \
	EXPAND(GET_MACRO(__VA_ARGS__, FE_6, FE_5, FE_4, FE_3, FE_2, FE_1)(NAME, __VA_ARGS__))


#endif//_hrengin_hrenginmacro_