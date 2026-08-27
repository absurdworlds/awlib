#include "aw/meta/fold.h"

#include <aw/meta/list_ops.h>

namespace aw {


template<typename L, typename T>
struct append;

template<typename... Ls, typename T>
struct append<meta::list<Ls...>, T>
{
	using type = meta::list<Ls...,T>;
};

template<typename L, typename T>
using append_t = typename append<L,T>::type;

static_assert( std::is_same_v<
	fold<
		append_t,
		meta::list<>,
		int,int,int>,
	meta::list<int,int,int>
>);

static_assert( std::is_same_v<
	fold<
		append_t,
		meta::list<float>,
		int,int,int
	>,
	meta::list<float,int,int,int>
>);

template<typename I, typename T>
struct count_ints;

template<size_t I, typename T>
struct count_ints<std::integral_constant<size_t, I>, T>
{
	using type = std::integral_constant<size_t, I + std::is_integral_v<T>>;
};

template<typename I, typename T>
using count_ints_t = typename count_ints<I,T>::type;

static_assert(
	fold_v<
		count_ints_t,
		std::integral_constant<size_t, 0>,
		int,int,float,int,int,float,int,float
	> == 5
);

} // namespace aw
