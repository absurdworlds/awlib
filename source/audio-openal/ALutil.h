/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_ALutil_
#define _hrengin_ALutil_

#include <al.h>

#include <hrengin/common/types.h>

inline ALenum toAlEnum(short channels, short samples)
{
	bool stereo = (channels > 1);

	switch (samples) {
	case 16:
		if (stereo) {
			return AL_FORMAT_STEREO16;
		} else {
			return AL_FORMAT_MONO16;
		}
	case 8:
		if (stereo) {
			return AL_FORMAT_STEREO8;
		} else {
			return AL_FORMAT_MONO8;
		}
	default:
		return -1;
	}
}

#endif//_hrengin_ALutil_
