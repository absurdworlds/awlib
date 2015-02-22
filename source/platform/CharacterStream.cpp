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
// todo: add 'copy' specifier

CharacterStream* createCharacterStream(char const* source)
{
	return new impl_::CharacterStream(source);
}

} //namespace io
} //namespace hrengin
