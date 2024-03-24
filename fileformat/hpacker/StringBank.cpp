/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <limits>

#include "StringBank.h"

namespace aw {
namespace itd {
StringBank::StringBank()
	: stringTally(0)
{
}

u64 StringBank::add(std::string const & str)
{
	u64 prevTally = stringTally;
	u16 const limit = std::numeric_limits<u16>::max();

	strings.push_back(str.substr(0, limit));

	u16 const length = strings.back().size();

	stringTally += length + 3;
	return prevTally;
}

void StringBank::putStrings(std::ostream & target)
{
	for(auto const & str : strings) {
		u16 length = str.size();
		target.write((char *)&length, 2);
		target.write(str.c_str(), length + 1);
	}
}

std::string const & StringBank::operator [](size_t index) const
{
	return strings[index];
}
std::string const & StringBank::back() const
{
	return strings.back();
}
} //namespace itd
} //namespace aw
