#ifndef _hrengin_SoundSample_
#define _hrengin_SoundSample_

#include <hrengin/common/hrengintypes.h>

namespace hrengin {
namespace sound {

struct SoundSample {
	u32 channels;
	u32 sampleRate;
	u32 bitsPerSample;
	u32 size;
	i8* data;
};

}
}

#endif