/*
 * Crunch Engine 3
 * Copyright 2026 Dodwell Industries
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <Crunch/core/renderer/MeshRegistry.hpp>
#include <cstdint>

namespace Crunch::Registry::MeshRegistry {

std::vector<struct Mesh_GPU_Data> mesh_data;        // The actual mesh registry
int mesh_data_count = 0;

void appendToRegistry(uint32_t vao, uint32_t ebo, uint32_t vbo, uint32_t idx, uint32_t vdx) {
    struct Mesh_GPU_Data newMeshGpuData;
    newMeshGpuData.id = mesh_data_count++;

    newMeshGpuData.vao = vao;
    newMeshGpuData.ebo = ebo;
    newMeshGpuData.vbo = vbo;

    newMeshGpuData.idx_count = idx;
    newMeshGpuData.vdx_count = vdx;

    mesh_data.push_back(newMeshGpuData);
}

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
