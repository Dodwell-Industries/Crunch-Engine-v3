#ifndef AABB_HPP
#define AABB_HPP

#include <glm/glm.hpp>

namespace Crunch::Physics {

typedef struct {
    glm::vec3 min;          // Bottom left corner
    glm::vec3 max;          // Top left corner
} AABB;

bool Intersects(const AABB& other);

}

#endif      // AABB_HPP
