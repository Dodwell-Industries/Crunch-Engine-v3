#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/trigonometric.hpp"
#include <Crunch/core/Camera.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace Crunch {

bool Camera::init(int type, float aspect, float fov, float zn, float zf) {
    cdata.aspect = aspect;
    cdata.fovy = fov;
    cdata.zNear = zn;
    cdata.zFar = zf;

    if (type == CRUNCH_CAMERA_TYPE_PERSPECTIVE) {
        // Use the perespective camera
        cdata.projection = glm::perspective(glm::radians(cdata.fovy), cdata.aspect, cdata.zNear, cdata.zFar);
    } else if (type == CRUNCH_CAMERA_TYPE_ORTHO) {
        // Use the orthographic camera
        std::cout << "warning: camera type not yet available: " << CRUNCH_CAMERA_TYPE_ORTHO << std::endl;
    } else {
        // The user specified an unavailable camera type
        std::cout << "warning: unknown camera type. some things may not render." << std::endl;
        return false;
    }

    cdata.view = glm::lookAt(glm::vec3(5.0f, 0.0f, 5.0f), glm::vec3(0), glm::vec3(0, 1.0f, 0));
    return true;
}

};
