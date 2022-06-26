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

#define AW_EAT_UNPAREN AW_UNPAREN ,
#define AW_UNPAREN(...) AW_UNPAREN __VA_ARGS__

#define AW_REMOVE_PAREN2(...) AW_APPLY_EXPAND2(AW_TAIL, AW_EAT_##__VA_ARGS__)
#define AW_REMOVE_PAREN(...)  AW_APPLY_EXPAND(AW_REMOVE_PAREN2, AW_UNPAREN __VA_ARGS__)

#endif//aw_pp_tupl_h
