#include "Crunch/core/renderer/MeshRegistry.hpp"
#include "glm/trigonometric.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Crunch/core/renderer/Mesh.hpp>
#include <cstdint>
#include <vector>
#include <cstddef>

namespace Crunch {

void Mesh::create(std::vector<struct Vertex> verts, std::vector<uint32_t> idxs, glm::vec3 pos, glm::vec2 color) {
    // Create the mesh here, and fill in the vertices and indices
    vertices = verts;
    indices = idxs;

    vcount = vertices.size();
    icount = indices.size();

    model = glm::mat4(1.0f);
    model = glm::translate(model, pos);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

    // Position attribute (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // Color attribute (location = 1)
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    // Texture attribute (location = 2)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Registry::MeshRegistry::appendToRegistry(VAO, EBO, VBO, icount, vcount);
}

void Mesh::setTexture(Texture* tex, uint32_t prog) {
    glUniform1i(glGetUniformLocation(prog, "tex"), 0);
    glActiveTexture(GL_TEXTURE0);
    tex->bind();
}

void Mesh::setRotation(float degrees, glm::vec3 axis) {
    model = glm::rotate(model, glm::radians(degrees), axis);
}

void Mesh::setPosition(glm::vec3 newPos) {
    model = glm::translate(model, newPos);
}

void Mesh::setScale(glm::vec3 newScale) {
    model = glm::scale(model, newScale);
}

};
