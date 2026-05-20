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

    camera->cdata.view = glm::lookAt(coredata.cameraPos, coredata.cameraPos + coredata.cameraFront, coredata.cameraUp);

    // Start on the ground
    isOnGround = true;

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
}

void FirstPersonController::update(float dt, float speed) {
    // Controller speed
    // Update as required
    const float cameraSpeed = speed;

    if (glfwGetKey(window->getWindow(), keymap.forward) == GLFW_PRESS) {
        // Move the camera forward
        // Multiple by delta time (dt), so that movement is frame independant
        coredata.cameraPos += cameraSpeed * glm::vec3(coredata.cameraFront.x, 0.f, coredata.cameraFront.z) * dt;
    }
    if (glfwGetKey(window->getWindow(), keymap.backwards) == GLFW_PRESS) {
        // Move the camera backwards
        // Multiple by delta time (dt), so that movement is frame independant
        coredata.cameraPos -= cameraSpeed * glm::vec3(coredata.cameraFront.x, 0.f, coredata.cameraFront.z) * dt;
    }
    if (glfwGetKey(window->getWindow(), keymap.left) == GLFW_PRESS) {
        // Move the camera left
        // Multiple by delta time (dt), so that movement is frame independant
        // Normalize the value, so that we don't move in weird directions and it feels more natural
        coredata.cameraPos -= glm::normalize(glm::cross(coredata.cameraFront, coredata.cameraUp)) * cameraSpeed * dt;
    }
    if (glfwGetKey(window->getWindow(), keymap.right) == GLFW_PRESS) {
        // Move the camera right
        // Multiple by delta time (dt), so that movement is frame independant
        // Normalize the value, so that we don't move in weird directions and it feels more natural
        coredata.cameraPos += glm::normalize(glm::cross(coredata.cameraFront, coredata.cameraUp)) * cameraSpeed * dt;
    }
    // if (glfwGetKey(window->getWindow(), keymap.up) == GLFW_PRESS) {
    //     // Move the camera up
    //     // Multiple by delta time (dt), so that movement is frame independant
    //     coredata.cameraPos.y += cameraSpeed * dt;
    // }
    // if (glfwGetKey(window->getWindow(), keymap.down) == GLFW_PRESS) {
    //     // Move the camera down
    //     // Multiple by delta time (dt), so that movement is frame independant
    //     coredata.cameraPos.y -= cameraSpeed * dt;
    // }

    /*
        Jump and gravity controller
    */
    if (isOnGround) {
        if (glfwGetKey(window->getWindow(), keymap.up) == GLFW_PRESS) {
            // Jump
        }
    }

    // Update the cameras view matrix every frame
    // Without this, values will update but nothing will move!
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
