/*
 * Copyright (C) 2017  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_pp_paren_h
#define aw_pp_paren_h

#include "macro.h"
#include "tuple.h"

#define EAT_UNPAREN UNPAREN ,
#define UNPAREN(...) UNPAREN __VA_ARGS__

#define REMOVE_PAREN2(...) APPLY_EXPAND2(TAIL, EAT_##__VA_ARGS__)
#define REMOVE_PAREN(...)  APPLY_EXPAND(REMOVE_PAREN2, UNPAREN __VA_ARGS__)

#endif//aw_pp_tupl_h
