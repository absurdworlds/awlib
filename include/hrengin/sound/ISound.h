#ifndef _hrengin_ISound_
#define _hrengin_ISound_

namespace hrengin {
namespace audio {

class ISound {
public:
	/* play sound */
	virtual bool play() = 0;

	/* stop playing sound */
	virtual bool stop() = 0;
};


} // namespace audio
} // namespace hrengin

#endif//_hrengin_ISound_