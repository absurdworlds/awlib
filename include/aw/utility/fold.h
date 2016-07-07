/*
 * Copyright (C) 2015-2016  absurdworlds
 * Copyright (C) 2015-2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_fold_h
#define aw_fold_h
namespace aw {
#if __cplusplus >= 201500L
#define AW_FOLD(expr) (void(expr), ...);
#else
using fold_dummy = int[];
#define AW_FOLD(expr) (void) fold_dummy { 0, (void(expr), 0)...  };
#endif
} // namespace aw
#endif//aw_fold_h
