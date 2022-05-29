/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_types_unknown_h
#define aw_types_unknown_h
namespace aw {
/*!
 * Undefined class for use as placeholder.
 */
class unknown_class;
/*!
 * Undefined function for use as a storage type
 */
using unknown_fn = void (unknown_class&);
/*!
 * undefined member function for use as a storage type
 */
using unknown_member = int (unknown_class::*);
/*!
 * Undefined member function for use as a storage type
 */
using unknown_mem_fn = void (unknown_class::*)();
} // namespace aw
#endif//aw_types_unknown_h
