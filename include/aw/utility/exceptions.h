/*
 * Copyright (C) 2016  absurdworlds
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_exceptions_h
#define aw_utility_exceptions_h
#if __cpp_exceptions
#define AW__try try
#define AW__catch(...) catch(_VA_ARGS_)
#define AW__throw throw
#define AW__rethrow throw
#else
#define AW__try if (true)
#define AW__catch(...) else
#define AW__throw
#define AW__rethrow
#endif
#endif//aw_utility_exceptions_h
