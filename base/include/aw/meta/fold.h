/*
 * Copyright (C) 2023  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_meta_fold_h
#define aw_meta_fold_h
namespace aw {
namespace meta {

template<
	template<typename A, typename B> typename Op,
	typename Init,
	typename T,
	typename...Ts>
struct fold {
	using type = typename fold<Op, Op<Init, T>, Ts...>::type;
};

template<
	template<typename A, typename B> typename Op,
	typename Init,
	typename T>
struct fold<Op, Init, T> {
	using type = Op<Init, T>;
};

template<
	template<typename A, typename B> typename Op,
	typename Init,
	typename T,
	typename...Ts>
struct fold_apply {
	using type = typename fold<Op, typename Op<Init, T>::type, Ts...>::type;
};

template<
	template<typename A, typename B> typename Op,
	typename Init,
	typename T>
struct fold_apply<Op, Init, T> {
	using type = typename Op<Init, T>::type;
};

} // namespace meta

/*!
 * For each of Ts, applies the binary Opto the result of the
 * previous application (or Init for the first application)
 * and the T.
 *
 * For example:
 *
 * given
 *
 *     template<typename L, typename R>>
 *     using op_t = typename op<L,R>::type;
 *
 * the
 *
 *     fold<op_t, None, A, B, C, D>
 *
 * is the same as
 *
 *     op_t<op_t<op_t<op_t<None, A>, B>, C>, D>
 *
 * Note that the op_t<> here is a type alias that returns a concrete type,
 * not a wrapper with ::type in it. If you don't want to declare a type alias,
 * use the fold_apply<>.
 */
template<
	// Operation to apply to each pair
	template<typename A, typename B> typename Op,
	// Initial value
	typename Init,
	// List of types
	typename...Ts>
using fold = typename meta::fold<Op, Init, Ts...>::type;

template<
	// Operation to apply to each pair
	template<typename A, typename B> typename Op,
	// Initial value
	typename Init,
	// List of types
	typename...Ts>
using fold_apply = typename meta::fold<Op, Init, Ts...>::type;

template<
	template<typename A, typename B> typename Op,
	typename Init,
	typename...Ts>
constexpr inline auto fold_v = fold<Op, Init, Ts...>::value;

} // namespace aw
#endif//aw_meta_fold_h
