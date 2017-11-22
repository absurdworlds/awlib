/*
 * Copyright (C) 2017  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_meta_pp_struct_h
#define aw_meta_pp_struct_h
#include "for_each.h"
#include "tuple.h"

#define DEFINE_STRUCT(NAME,...) \
struct NAME { \
	FOR_EACH(SEP_SEMI, SEP_SPACE DEFER, __VA_ARGS__ ); \
	using tuple_type = std::tuple< \
		FOR_EACH( SEP_COMMA, FIRST DEFER, __VA_ARGS__ ) \
	>; \
	constexpr operator tuple_type() \
	{ \
		return { FOR_EACH( SEP_COMMA, SECOND DEFER, __VA_ARGS__ ) }; \
	} \
}

#endif//aw_meta_pp_struct_h
