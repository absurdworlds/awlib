/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_pp_macro_h
#define aw_pp_macro_h
#include <aw/config.h>

/*! Stringize */
#define TO_STR(x) TO_STR1(x)
#define TO_STR1(x) #x

/*! Concatenate */
#define CONCAT(x, y)   CONCAT1(x, y)
#define CONCAT1(x, y)  CONCAT2(x, y)
#define CONCAT2(x, y)  x##y

/*! Expand tokens — some preprocessors glue __VA_ARGS__ */
#define EXPAND(x) x


#endif//aw_pp_macro_h
