#include <Crunch/physics/Physics.hpp>
#include <Crunch/physics/RigidBody.hpp>

namespace Crunch::Physics {

void PhysicsHandler::UpdatePhysics(RigidBody* body, float dt) {
    if (body->inv_mass == 0.0f) return;

    // Gravity force
    glm::vec3 gravityForce = glm::vec3(0.0f, -100.81f, 0.0f) * body->mass;

    // Apply gravity
    body->ApplyForce(gravityForce);

    // F = ma
    glm::vec3 acceleration = body->total_forces * body->inv_mass;

    // Integrate velocity
    body->velocity += acceleration * dt;

    // Damping
    body->velocity *= 0.90f;

    // Integrate position
    body->position += body->velocity * dt;

    // Floor collision
    if (body->position.y < 0.0f) {
        body->position.y = 0.0f;
        body->velocity.y = 0.0f;
    }

    // Reset forces
    body->total_forces = glm::vec3(0.0f);
}

}
