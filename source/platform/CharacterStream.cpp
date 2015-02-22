/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include "CharacterStream.h"

namespace hrengin {
namespace io {
// TODO: add 'copy' specifier // wait, what?
CharacterStream* createCharacterStream(char const* source)
{
	return new impl_::CharacterStream(source);
}

bool impl_::CharacterStream::getCurrent(char& c)
{
	if(pos_ == 0xFFFFFFF) {
		c = 0;
		return false;
	}
	c = source_[pos_];
	return true;
}

bool impl_::CharacterStream::getNext(char& c)
{
	++ pos_;
	if(source_[pos_] == 0) {
		c = 0;
		pos_ = 0xFFFFFFF;
		return false;
	}
	c = source_[pos_];
	return true;
}

} //namespace io
} //namespace hrengin
