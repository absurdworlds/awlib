
#include "CCharacterStream.h"

namespace hrengin {
namespace io {
// todo: add 'copy' specifier

ICharacterStream* createCharacterStream(const char* source)
{
	return new CCharacterStream(source);
}


} //namespace io
} //namespace hrengin
