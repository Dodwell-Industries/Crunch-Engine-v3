#include <Crunch/Crunch.hpp>
#include <Crunch/core/Window.hpp>
#include <Crunch/core/renderer/Renderer3D.hpp>
#include <Crunch/core/renderer/Mesh.hpp>
#include <Crunch/core/renderer/Shader.hpp>
#include <Crunch/core/Camera.hpp>
#include <cstdint>

int main() {
    Crunch::Window window;
    if (!window.init()) return -1;
    window.create(800, 600, "Crunch Engine Version 3 | Demo");

    Crunch::Renderer3D renderer;
    Crunch::Shader loader;

    const char* vss = loader.load("assets/vertex.glsl");
    const char* fss = loader.load("assets/fragment.glsl");

    uint32_t vs = loader.createShader(GL_VERTEX_SHADER, vss);
    uint32_t fs = loader.createShader(GL_FRAGMENT_SHADER, fss);

    renderer.init(vs, fs);

    Crunch::Mesh mesh;
    Crunch::Camera camera;
    camera.init(CRUNCH_CAMERA_TYPE_PERSPECTIVE, 800.f / 600.f, 45.f, 0.01f, 1000.f);

    std::vector<struct Crunch::Vertex> vertices;
    std::vector<uint32_t> indices;

    struct Crunch::Vertex v1 = { glm::vec3(0.5f, 0.5f, 0) };
    struct Crunch::Vertex v2 = { glm::vec3(0.5f, -0.5f, 0) };
    struct Crunch::Vertex v3 = { glm::vec3(-0.5f, -0.5f, 0) };
    struct Crunch::Vertex v4 = { glm::vec3(-0.5f, 0.5f, 0) };
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    vertices.push_back(v4);

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(3);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(3);

    mesh.create(vertices, indices);

    while (!window.windowShouldClose()) {
        window.clear(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

        renderer.draw(&mesh, &camera);

        window.update();
    }

    return 0;
}
