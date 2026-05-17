#include "glm/fwd.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <Crunch/core/renderer/Mesh.hpp>
#include <cstdint>
#include <vector>

namespace Crunch {

void Mesh::create(std::vector<struct Vertex> verts, std::vector<uint32_t> idxs) {
    // Create the mesh here, and fill in the vertices and indices
    vertices = verts;
    indices = idxs;

    vcount = vertices.size();
    icount = indices.size();

    model = glm::mat4(1.0f);        // Identity matrix. No transforms

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

};
