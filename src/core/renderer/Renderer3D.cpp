#include "Crunch/core/renderer/Matrix/Matrix.hpp"
#include "Crunch/core/renderer/MeshRegistry.hpp"
#include <Crunch/core/Window.hpp>
#include <Crunch/core/Camera.hpp>
#include <Crunch/core/renderer/Mesh.hpp>
#include <Crunch/core/renderer/Renderer3D.hpp>
#include <Crunch/core/renderer/Shader.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdint>

namespace Crunch {

bool Renderer3D::Init(uint32_t vs, uint32_t fs) {

    vertexShader = vs;
    fragmentShader = fs;

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    char log[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, log);
        printf("shader link error: %s\n", log);
    }

    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    modlLoc = glGetUniformLocation(shaderProgram, "model");
    viewLoc = glGetUniformLocation(shaderProgram, "view");
    projLoc = glGetUniformLocation(shaderProgram, "projection");

    return true;
}

void Renderer3D::Draw(Matrix::RenderList* list) {
    glUseProgram(shaderProgram);

    for (int i = 0; i < list->id_count; i++) {
        glUniformMatrix4fv(modlLoc, 1, GL_FALSE, glm::value_ptr(list->commands[i].model));
        
        uint32_t idx_count = Registry::MeshRegistry::resolveIDX(list->commands[i].meshID);

        glBindVertexArray(Registry::MeshRegistry::resolveVAO(list->commands[i].meshID));
        glDrawElements(GL_TRIANGLES, idx_count, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(list->frame_data->view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(list->frame_data->projection));
}

};
