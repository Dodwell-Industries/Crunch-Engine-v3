#ifndef RENDERER3D_HPP
#define RENDERER3D_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <Crunch/core/renderer/Mesh.hpp>
#include <Crunch/core/renderer/Shader.hpp>
#include <Crunch/core/Camera.hpp>
#include <Crunch/core/renderer/Matrix/Matrix.hpp>

namespace Crunch {

class Renderer3D {
private:
public:
    bool Init(uint32_t vs, uint32_t fs);
    void Draw(Matrix::RenderList* list);

    unsigned int shaderProgram;
    unsigned int vertexShader;
    unsigned int fragmentShader;

    unsigned int viewLoc;
    unsigned int modlLoc;
    unsigned int projLoc;
};

}

#endif      // RENDERER3D_HPP
