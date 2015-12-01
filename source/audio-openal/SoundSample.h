/*
 * Copyright (C) 2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_SoundSample_
#define _aw_SoundSample_
#include <aw/common/types.h>

namespace aw {
namespace audio {

struct SoundSample {
	u32 channels;
	u32 sampleRate;
	u32 bitsPerSample;
	u32 size;
	i8* data;
};

} // namespace audio
} // namespace aw
#endif//_aw_SoundSample_
