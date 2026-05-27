#ifndef RIGID_BODY_HPP
#define RIGID_BODY_HPP

#include <glm/glm.hpp>
#include <Crunch/physics/AABB.hpp>

namespace Crunch::Physics {

class RigidBody {
public:
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    glm::vec3 total_forces;

    float mass;
    float inv_mass;
    float restitution;

    AABB local_aabb;

    RigidBody();
    void ApplyForce(const glm::vec3& force);
    AABB GetWorldAABB() const;
};

}

#endif      // RIGID_BODY_HPP
