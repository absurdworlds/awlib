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
#include "macro.h"
#include "foldr.h"
#include "tuple.h"

#include <tuple>
#include <aw/meta/void_t.h>
/*!
 * A function-macro to turn preprocessor "tuple" (TYPE,NAME) into a
 * variable declaration.
 *
 * type_t is required to correctly handle pesky c-style arrays and function pointers:
 *
 * `AW_DECLARE_VAR(char[8], name);` will expand to:
 * without type_t  ---> `char[8]         name;` // ERROR
 * with    type_t  ---> `type_t<char[8]> name;` // OK, equivalent to `char name[8]`
 */
#define AW_DECLARE_VAR(TYPE,NAME) ::aw::type_t<TYPE> NAME

/*!
 * Turns a list of preprocessor "tuples" into list of variable declarations
 */
#define AW_DEFINE_STRUCT_MEMBERS(NAME,...)\
	AW_FOLD_RIGHT( AW_SEP_SEMI, AW_DECLARE_VAR AW_DEFER, __VA_ARGS__ )

/*!
 * Expands list of preprocessor "tuples" (type, name)
 * into comma-separated list of types
 */
#define AW_LIST_MEMBER_TYPES(NAME,...)\
	AW_FOLD_RIGHT( AW_SEP_COMMA, AW_FIRST AW_DEFER , __VA_ARGS__ )
#define AW_LIST_MEMBER_NAMES(NAME,...)\
	AW_FOLD_RIGHT( AW_SEP_COMMA, AW_SECOND AW_DEFER, __VA_ARGS__ )
#define AW_DEFINE_STRUCT_TUPLE_TYPE(NAME,...)\
	using tuple_type = std::tuple< AW_LIST_MEMBER_TYPES( __VA_ARGS__ ) >
#define AW_DEFINE_STRUCT_TUPLE_OPERATOR(NAME,...)\
	constexpr operator tuple_type() { \
		return { AW_LIST_MEMBER_NAMES( __VA_ARGS__ ) };\
	}

#define AW_LIST_MEMBER_NAME_STRINGS(NAME,...)\
	AW_FOLD_RIGHT( AW_SEP_COMMA, AW_SECOND AW_DEFER, __VA_ARGS__ )
	

#define AW_DEFINE_STRUCT(NAME,...) \
struct NAME { \
	AW_DEFINE_STRUCT_MEMBERS(NAME,__VA_ARGS__);\
	AW_DEFINE_STRUCT_TUPLE_TYPE(NAME,__VA_ARGS__);\
	AW_DEFINE_STRUCT_TUPLE_OPERATOR(NAME,__VA_ARGS__);\
}

#endif//aw_meta_pp_struct_h
