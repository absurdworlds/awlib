#include <aw/meta/pp/paren.h>
#include <tuple>


//#define APPLY_PAREN(...) APPLY(APPLY_PAREN2, PAD __VA_ARGS__ )
#define APPLY_PAREN2(MACRO, ...) AW_APPLY(MACRO AW_DEFER, __VA_ARGS__)

#define APPLY_PAREN(MACRO, ...) AW_EXPAND(AW_APPLY(MACRO AW_DEFER, __VA_ARGS__))

void f()
{
	std::tuple<AW_REMOVE_PAREN( (int,int) )> tu;
	std::tuple<AW_REMOVE_PAREN(int)> tu2;
}
