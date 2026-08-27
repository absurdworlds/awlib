#include "aw/meta/expand.h"
#include "aw/meta/list.h"

#include "aw/types/traits/basic_traits.h"
#include "aw/types/types.h"

namespace aw {

static_assert( is_same_v<
	expand<
		std::is_same<_1, i32>,
		i32
	>,
	std::is_same<i32, i32>
>);

static_assert( is_same_v<
	expand<
		std::is_same<_1, _2>,
		i32, i64
	>,
	std::is_same<i32, i64>
>);

static_assert( is_same_v<
	expand<
		meta::list<_1, _2, i32>,
		i32, f32
	>,
	meta::list<i32, f32, i32>
>);

static_assert( is_same_v<
	expand<
		meta::list<_2, _1, i32>,
		i32, f32
	>,
	meta::list<f32, i32, i32>
>);

static_assert( is_same_v<
	expand<
		meta::list<_2, _1, _3>,
		i32, f32, f64
	>,
	meta::list<f32, i32, f64>
>);

static_assert( is_same_v<
	expand<
		meta::list<_3, _3, _3>,
		i32, f32, f64
	>,
	meta::list<f64, f64, f64>
>);

static_assert( is_same_v<
	expand<
		meta::list<_3, _3, meta::list<_1>>,
		i32, f32, f64
	>,
	meta::list<f64, f64, meta::list<_1>>
>);

static_assert( is_same_v<
	expand_r<
		meta::list<_3, _3, meta::list<_1>>,
		i32, f32, f64
	>,
	meta::list<f64, f64, meta::list<i32>>
>);
} // namespace aw
