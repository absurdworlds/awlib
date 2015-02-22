/*
 * Copyright (C) 2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_SoundSample_
#define _hrengin_SoundSample_

#include <hrengin/common/hrengintypes.h>

namespace hrengin {
namespace audio {

struct SoundSample {
	u32 channels;
	u32 sampleRate;
	u32 bitsPerSample;
	u32 size;
	i8* data;
};

}
}
#endif//_hrengin_SoundSample_
