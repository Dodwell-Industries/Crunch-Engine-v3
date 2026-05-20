#include <Crunch/core/renderer/Shapes.hpp>

namespace Crunch::Shapes {

Quad::Quad(float w, float h, glm::vec3 p, glm::vec4 c) {
    color = c;
    width = w;
    height = h;

    size.x = width;
    size.y = height;

    position = p;

    // Create the vertices and push them into the vertices structure
    struct Crunch::Vertex v1 = { glm::vec3(0.5f, 0.5f, 0), c, glm::vec2(1.0f, 1.0f) };
    struct Crunch::Vertex v2 = { glm::vec3(0.5f, -0.5f, 0), c, glm::vec2(1.0f, 0) };
    struct Crunch::Vertex v3 = { glm::vec3(-0.5f, -0.5f, 0), c, glm::vec2(0, 0) };
    struct Crunch::Vertex v4 = { glm::vec3(-0.5f, 0.5f, 0), c, glm::vec2(0, 1.0f) };
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    vertices.push_back(v4);

    // Add the indices
    // These are critical, because they define which vertex connects to each other
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(0);
}

}
