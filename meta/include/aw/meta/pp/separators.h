/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_pp_separators_h
#define aw_pp_separators_h

/*! Insert both arguments separated by space */
#define AW_SEP_SPACE(x, y) x y
/*! Insert both arguments separated by semicolon */
#define AW_SEP_SEMI(x, y) x; y
/*! Insert both arguments separated by comma */
#define AW_SEP_COMMA(x, y) x, y

/*! Insert comma before __VA_ARGS__ */
#define AW_VA_COMMA(...) __VA_OPT__(,) __VA_ARGS__
/*! Insert comma before __VA_ARGS__ */
#define AW_VA_SEMI(...) __VA_OPT__(;) __VA_ARGS__

#endif//aw_pp_separators_h
