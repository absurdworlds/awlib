/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_types_wrap_h
#define aw_types_wrap_h
namespace aw {
/*!
 * \example
 *   void func(_t<void(*)()> callback);
 *   void func(T* object, _t<void(T::*)()> callback);
 */
template<typename T>
using _t = T;
} // namespace aw
#endif//aw_types_wrap_h
