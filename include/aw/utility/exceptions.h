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
/*!
 * \{
 * Set of macros to remove exception handling code
 * when exceptions are disabled.
 */
#if __cpp_exceptions
#define aw_try        try
#define aw_catch(...) catch(_VA_ARGS_)
#define aw_throw      throw
#define aw_rethrow    throw
#else
#define aw_try        if (true)
#define aw_catch(...) else
#define aw_throw
#define aw_rethrow
#endif//__cpp_exceptions
/*! \} */
#endif//aw_utility_exceptions_h
