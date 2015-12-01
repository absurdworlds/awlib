/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_Sound_
#define _aw_Sound_

namespace aw {
namespace audio {
//! Represents a sound
class Sound {
public:
	/*! play sound */
	virtual bool play () = 0;

	/*! Stop playing sound */
	virtual bool stop () = 0;
};

} // namespace audio
} // namespace aw
#endif//_aw_Sound_
