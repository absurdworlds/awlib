#include <aw/meta/pp/paren.h>
#include <tuple>


//#define APPLY_PAREN(...) APPLY(APPLY_PAREN2, PAD __VA_ARGS__ )
#define APPLY_PAREN2(MACRO, ...) APPLY(MACRO DEFER, __VA_ARGS__)

#define APPLY_PAREN(MACRO, ...) EXPAND(APPLY(MACRO DEFER, __VA_ARGS__))

void f()
{
	std::tuple<REMOVE_PAREN( (int,int) )> tu;
	std::tuple<REMOVE_PAREN(int)> tu2;
}
