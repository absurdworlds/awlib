/*
 * Copyright (C) 2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_Sound3D_
#define _awrts_Sound3D_
#include <awengine/common/types.h>
#include <awengine/math/Vector3d.h>

#include <awrts/sound/Sound.h>

namespace awrts {
namespace audio {

//! Represents a sound positioned in 3D space
class Sound3D : public Sound {
public:
	/*! Play sound */
	virtual bool play () = 0;

	/*! Stop playing sound */
	virtual bool stop () = 0;

	/*! Move sound to position \a `pos`, calculating velocity */
	virtual void move(Vector3d pos, f32 timeStep) = 0;

	/*! Set sound to `pos` and reset velocity */
	virtual void setPosition (Vector3d pos) = 0;
};

} // namespace audio
} // namespace awrts
#endif//_awrts_Sound3D_
