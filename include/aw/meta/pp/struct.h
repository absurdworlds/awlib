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

#define DEFINE_STRUCT_MEMBERS(NAME,...)\
	FOR_EACH(SEP_SEMI, SEP_SPACE DEFER, __VA_ARGS__ )
#define DEFINE_STRUCT_TYPES(NAME,...)\
	FOR_EACH( SEP_COMMA, FIRST DEFER, __VA_ARGS__ )
#define DEFINE_STRUCT_TUPLE_TYPE(NAME,...)\
	using tuple_type = std::tuple< DEFINE_STRUCT_TYPES(__VA_ARGS__) >
#define DEFINE_STRUCT_TUPLE_OPERATOR(NAME,...)\
	constexpr operator tuple_type() { \
		return { DEFINE_STRUCT_NAMES( __VA_ARGS__ ) };\
	}
#define DEFINE_STRUCT_NAMES(NAME,...)\
	FOR_EACH( SEP_COMMA, SECOND DEFER, __VA_ARGS__ )
#define DEFINE_STRUCT_NAME_STRINGS(NAME,...)\
	FOR_EACH( SEP_COMMA, SECOND DEFER, __VA_ARGS__ )
	

#define DEFINE_STRUCT(NAME,...) \
struct NAME { \
	DEFINE_STRUCT_MEMBERS(NAME,__VA_ARGS__);\
	DEFINE_STRUCT_TUPLE_TYPE(NAME,__VA_ARGS__);\
	DEFINE_STRUCT_TUPLE_OPERATOR(NAME,__VA_ARGS__);\
}


#endif//aw_meta_pp_struct_h
