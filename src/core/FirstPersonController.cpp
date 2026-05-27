#include <Crunch/core/FirstPersonController.hpp>
#include <Crunch/core/Camera.hpp>
#include <Crunch/core/Window.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

namespace Crunch {

FirstPersonController::FirstPersonController(Camera* c, Window* w, float x, float y) {

    camera = c;
    window = w;
    aspect.x = x;
    aspect.y = y;

    coredata.cameraPos = glm::vec3(0, 2.0f, 3.0f);
    coredata.cameraTarget = glm::vec3(0);
    coredata.cameraDirection = glm::normalize(coredata.cameraPos - coredata.cameraTarget);

    coredata.up = glm::vec3(0, 1.0f, 0);
    coredata.cameraRight = glm::normalize(glm::cross(coredata.up, coredata.cameraDirection));
    // coredata.cameraUp = glm::cross(coredata.cameraDirection, coredata.cameraRight);

    coredata.cameraFront = glm::vec3(0, 0, -1.0f);
    coredata.cameraUp = coredata.up;
    coredata.velocity = glm::vec3(0.0f);

    camera->cdata.view = glm::lookAt(coredata.cameraPos, coredata.cameraPos + coredata.cameraFront, coredata.cameraUp);

    // Start on the ground
    // isOnGround = true;

    // Initialize the keymap to the defaults
    keymap.forward = GLFW_KEY_W;
    keymap.backwards = GLFW_KEY_S;
    keymap.left = GLFW_KEY_A;
    keymap.right = GLFW_KEY_D;
    keymap.up = GLFW_KEY_SPACE;
    keymap.down = GLFW_KEY_LEFT_SHIFT;


    glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    coredata.yaw = -90.0f;
    coredata.pitch = 0.0f;
    coredata.firstMouse = true;
    coredata.lastX = aspect.x / 2;
    coredata.lastY = aspect.y / 2;

    // Register the mouse callback with GLFW
    glfwSetWindowUserPointer(window->getWindow(), this);
    glfwSetCursorPosCallback(window->getWindow(), [](GLFWwindow* w, double xpos, double ypos) {
        auto* fpc = static_cast<FirstPersonController*>(glfwGetWindowUserPointer(w));
        if (fpc) fpc->mouseCallback(xpos, ypos);
    });

    // Setup the rigid body for proper physics and collisions
    body = new Physics::RigidBody();
    body->mass = 1.0f;
    body->inv_mass = 1.0f;
    body->position = coredata.cameraPos;
}

void FirstPersonController::update(float dt, float speed) {
    glm::vec3 wishDir(0.0f);

    if (glfwGetKey(window->getWindow(), keymap.forward) == GLFW_PRESS) {
        wishDir += glm::vec3(coredata.cameraFront.x, 0.f, coredata.cameraFront.z);
    }
    if (glfwGetKey(window->getWindow(), keymap.backwards) == GLFW_PRESS) {
        wishDir -= glm::vec3(coredata.cameraFront.x, 0.f, coredata.cameraFront.z);
    }
    if (glfwGetKey(window->getWindow(), keymap.left) == GLFW_PRESS) {
        wishDir -= glm::normalize(glm::cross(coredata.cameraFront, coredata.cameraUp));
    }
    if (glfwGetKey(window->getWindow(), keymap.right) == GLFW_PRESS) {
        wishDir += glm::normalize(glm::cross(coredata.cameraFront, coredata.cameraUp));
    }
    if (glm::length(wishDir) > 0.0f) {
        wishDir = glm::normalize(wishDir);
    }


    // Sprint
    float oldSpeed = speed;
    if (glfwGetKey(window->getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        oldSpeed = speed;
        speed *= 2;
    } else {
        speed = oldSpeed;
    }

    // Jump
    if (glfwGetKey(window->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS && isOnGround) {
        body->velocity.y = jumpForce;
        isOnGround = false;
    }

    if (body->position.y <= 0.0f) {
        isOnGround = true;
    } else {
        isOnGround = false;
    }

    // Calculate & apply force
    glm::vec3 force = wishDir * speed * 10.0f;
    body->ApplyForce(force);

    // Update the cameras view matrix every frame
    // Without this, values will update but nothing will move!
    coredata.cameraPos = body->position;
    coredata.cameraPos.y = body->position.y + 1.8f;
    camera->cdata.view = glm::lookAt(coredata.cameraPos, coredata.cameraPos + coredata.cameraFront, coredata.cameraUp);
}

void FirstPersonController::mouseCallback(double xpos, double ypos) {
    if (coredata.firstMouse) {
        coredata.lastX = xpos;
        coredata.lastY = ypos;
        coredata.firstMouse = false;
    }

    float xoffset = xpos - coredata.lastX;
    float yoffset = coredata.lastY - ypos; // Reversed since y goes bottom to top
    coredata.lastX = xpos;
    coredata.lastY = ypos;

    const float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    coredata.yaw   += xoffset;
    coredata.pitch += yoffset;

    // Clamp pitch so screen doesn't flip
    if (coredata.pitch >  89.0f) coredata.pitch =  89.0f;
    if (coredata.pitch < -89.0f) coredata.pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(coredata.yaw)) * cos(glm::radians(coredata.pitch));
    direction.y = sin(glm::radians(coredata.pitch));
    direction.z = sin(glm::radians(coredata.yaw)) * cos(glm::radians(coredata.pitch));
    coredata.cameraFront = glm::normalize(direction);
}

};
