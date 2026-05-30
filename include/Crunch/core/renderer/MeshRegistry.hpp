#ifndef MESH_REGISTRY_HPP
#define MESH_REGISTRY_HPP

#include <cstdint>
#include <vector>

namespace Crunch::Registry::MeshRegistry {

struct Mesh_GPU_Data {
    uint32_t id;
    uint32_t vao;
    uint32_t vbo;
    uint32_t ebo;

    uint32_t idx_count;         // Mesh specific indice count
    uint32_t vdx_count;         // Mesh specific vertex count
};

extern std::vector<struct Mesh_GPU_Data> mesh_data;
extern int mesh_data_count;

uint32_t resolveVAO(uint32_t id);
uint32_t resolveIDX(uint32_t id);
void appendToRegistry(uint32_t vao, uint32_t ebo, uint32_t vbo, uint32_t idx, uint32_t vdx);

};

#endif      // MESH_REGISTRY_HPP
