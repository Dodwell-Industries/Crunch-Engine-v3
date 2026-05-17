#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include <Crunch/core/Camera.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace Crunch {

bool Camera::init(int type) {
    if (type == CRUNCH_CAMERA_TYPE_PERSPECTIVE) {
        // Use the perespective camera
        projection = glm::perspective(30.f, 1.0f, 0.1f, 1000.f);
    } else if (type == CRUNCH_CAMERA_TYPE_ORTHO) {
        // Use the orthographic camera
        std::cout << "warning: camera type not yet available: " << CRUNCH_CAMERA_TYPE_ORTHO << std::endl;
    } else {
        // The user specified an unavailable camera type
        return false;
    }

    view = glm::lookAt(glm::vec3(1.0f, -5.0f, -5.0f), glm::vec3(0), glm::vec3(0, 1.0f, 0));
    return true;
}

};
