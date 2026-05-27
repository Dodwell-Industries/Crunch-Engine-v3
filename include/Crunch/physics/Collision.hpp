#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <Crunch/physics/AABB.hpp>
#include <Crunch/physics/RigidBody.hpp>
#include <glm/glm.hpp>

namespace Crunch::Physics {

typedef struct CollisionInfo {
    bool intersected;
    glm::vec3 normal;
    float depth;
} CollisionInfo;

class CollisionHandler {
public:
    CollisionInfo GetAABBCollision(const AABB* a, const AABB* b);
    void ResolveCollision(RigidBody& a, RigidBody& b, const CollisionInfo& info);
};

};

#endif      // COLISION_HPP
