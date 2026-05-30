#include <Crunch/core/renderer/MeshRegistry.hpp>
#include <cstdint>

namespace Crunch::Registry::MeshRegistry {

std::vector<struct Mesh_GPU_Data> mesh_data;        // The actual mesh registry

uint32_t resolveVAO(uint32_t id) {
    // Loop over every mesh entry to find the mesh with correct ID
    // Once found, return the VAO back to the user
    for (auto& mesh : mesh_data) {
        if (mesh.id == id) {
            return mesh.vao;
        }
    }

    return 0;       // Not found
}

uint32_t resolveIDX(uint32_t id) {
    // Loop over every mesh entry to find the mesh with correct ID
    // Once found, return the index count back to the user
    for (auto& mesh : mesh_data) {
        if (mesh.id == id) {
            return mesh.idx_count;
        }
    }

    return 0;       // Not found
}

}
