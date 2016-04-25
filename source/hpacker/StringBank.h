/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_StringBank_
#define _aw_StringBank_
#include <string>
#include <vector>
#include <ostream>

#include <aw/common/types.h>

namespace aw {
namespace itd {
// This class is used to collect strings,
// referred by filename pointers, together
class StringBank {
public:
	StringBank();
	~StringBank() = default;

	u64 add(std::string const & str);
	void putStrings(std::ostream & target);

	std::string const & operator [](size_t index) const;
	std::string const & back() const;
private:
	std::vector<std::string> strings;
	u64 stringTally;
};
} //namespace itd
} //namespace aw
#endif//_aw_StringBank_
