#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <Crunch/physics/RigidBody.hpp>

namespace Crunch::Physics {

class PhysicsHandler {
public:
    void UpdatePhysics(RigidBody* body, float dt);
};

}

#endif      // PHYSICS_HPP
