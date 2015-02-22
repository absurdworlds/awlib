/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_StringBank_
#define _hrengin_StringBank_
#include <string>
#include <vector>
#include <ostream>

#include <hrengin/common/types.h>

namespace hrengin {
namespace itd {

class StringBank {
public:
	StringBank ();
	u64 add (std::string const & str);
	void putStrings (std::ostream & target);

	std::string const & operator [] (size_t index) const;
	std::string const & back () const;
private:
	std::vector<std::string> strings_;
	u64 stringTally_;
};
} //namespace itd
} //namespace hrengin
#endif//_hrengin_StringBank_
