/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_PhysicsPhantom_
#define _aw_PhysicsPhantom_
#include <aw/physics/CollisionObject.h>

namespace aw {
namespace physics {
/*!
 * Collision phantom is ignored by other bodies,
 * useful for callbacks
 */
class CollisionPhantom : public CollisionObject {
public:
protected:
};

} // namespace physics
} // namespace aw
#endif//_aw_PhysicsPhantom_
