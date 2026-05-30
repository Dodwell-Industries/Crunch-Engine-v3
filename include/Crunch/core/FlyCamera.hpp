#ifndef FLY_CAMERA_HPP
#define FLY_CAMERA_HPP

#include <Crunch/core/Camera.hpp>
#include <Crunch/core/Window.hpp>
#include <glm/glm.hpp>

namespace Crunch {

class FlyCamera {
public:
    FlyCamera(Camera* cam, Window* win, float width, float height);

    void update(float dt, float speed = 10.0f);

private:
    void mouseCallback(double xpos, double ypos);

    Camera* camera;
    Window* window;

    struct {
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;

        float yaw;
        float pitch;

        bool firstMouse;
        float lastX;
        float lastY;
    } data;
};

}

#endif
