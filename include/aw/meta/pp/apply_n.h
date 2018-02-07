/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_meta_pp_apply_n_h
#define aw_meta_pp_apply_n_h
#include "macro.h"
#include "nargs.h"
/*
 * Suffix NAME with number of arguments
 */
#define SUFFIX_N(NAME, ...) CONCAT(NAME,N_ARGS(__VA_ARGS__))

/*!
 * Similar to APPLY, but suffixes the macro with number of arguments
 */
#define APPLY_N(NAME, ...) APPLY(SUFFIX_N(NAME,__VA_ARGS__), __VA_ARGS__)

#endif//aw_meta_pp_apply_n_h
