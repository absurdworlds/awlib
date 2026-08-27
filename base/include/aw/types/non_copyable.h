/*
 * Copyright (C) 2015  absurdworlds
 * Copyright (C) 2015  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_non_copyable_h
#define aw_non_copyable_h
namespace aw {
/*!
 * Utility class, deriving from which renders the derived class
 * non-copyable.
 */
class non_copyable {
protected:
	non_copyable() = default;
	~non_copyable() = default;
private:
	non_copyable(non_copyable const&) = delete;
	non_copyable& operator = (non_copyable const&) = delete;
};
} // namespace aw
#endif//aw_non_copyable_h
