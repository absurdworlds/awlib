/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_ISound_
#define _hrengin_ISound_

namespace hrengin {
namespace audio {
//! Represents a sound
class ISound {
public:
	/*! play sound */
	virtual bool play() = 0;

	/*! Stop playing sound */
	virtual bool stop() = 0;
};

} // namespace audio
} // namespace hrengin
#endif//_hrengin_ISound_
