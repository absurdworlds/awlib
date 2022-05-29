/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_meta_steal_h
#define aw_meta_steal_h
namespace aw {
// based on:
// https://bloglitb.blogspot.com/2011/12/access-to-private-members-safer.html
namespace steal {
/*! Provides access to class's private and protected members */
template<typename Tag, typename Tag::type Value>
struct steal {
	friend constexpr typename Tag::type member(Tag)
	{
		return Value;
	}
};

/*!
 * \class steal
 * To access private members of class X:
 * ```
 *	class X {
 *		int  data;
 *		void func(int);
 *	};
 * ```
 * You need to declare corresponding tags and explicit instantiation
 * of this template (in namespace steal):
 * ```
 *	struct x_data {
 *		using type = X::int*;
 *		friend constexpr type member(x_data);
 *	} x_data_tag;
 *	template steal<x_data, &X::data>;
 *	struct x_func {
 *		using type = void(X::*)(int);
 *		friend constexpr type member(x_func);
 *	} x_func_tag;
 *	template steal<x_func, &X::func>;
 * ```
 * Afterward, you can refer to members of X as pointer-to-member:
 * ```
 * 	using namespace steal;
 * 	X x_inst;
 * 	int value = x_inst.*(member(x_data_tag));
 * 	(x_inst.*(member(x_func_tag)))(value);
 * ```
 */
} // namespace steal
} // namespace aw
#endif//aw_meta_steal_h
