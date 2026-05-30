#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstdint>
#include <vector>
#include <glm/glm.hpp>
#include <Crunch/core/renderer/Mesh.hpp>

namespace Crunch::Matrix {

typedef struct {
    glm::mat4 model;
    uint32_t meshID;
    uint32_t materialID;
} DrawCommand;


// FrameData
// This structure gets passed onto the renderer
// The render backend has no idea about any camera matrices, since Matrix computes these
struct FrameData {
    glm::mat4 view;             // What is the camera looking at
    glm::mat4 projection;       // How are we looking at the view
};


// RenderList
// This is the list passed to the renderer so that it actually knows what to draw
// Includes a list of commands to execute, and a pointer 
//  to the FrameData so the GPU can actually make the user see something
struct RenderList {
    std::vector<DrawCommand> commands;          // Draw commands for the backend
    const struct FrameData* frame_data;
    int id_count;
};

RenderList Build(const std::vector<Mesh*> meshes, const FrameData* frame);

};

#endif      // MATRIX_HPP
