#include <Crunch/physics/RigidBody.hpp>
#include <Crunch/physics/AABB.hpp>

namespace Crunch::Physics {

RigidBody::RigidBody() {
    position = glm::vec3(0.0f);
    velocity = glm::vec3(0.0f);
    acceleration = glm::vec3(0.0f);
    total_forces = glm::vec3(0.0f);

    mass = 1.0f;
    inv_mass = 1.0f;        // 1.0 / mass
    restitution = 0.4f;     // Bounciness (0.0 = mud, 1.0 = superball)
}

void RigidBody::ApplyForce(const glm::vec3& force) {
    total_forces += force;
}

AABB RigidBody::GetWorldAABB() const {
    return AABB { local_aabb.min, local_aabb.max + position };
}

}
