#include <Crunch/core/renderer/Matrix/Matrix.hpp>

namespace Crunch::Matrix {

RenderList Build(const std::vector<Mesh*> meshes, const struct FrameData* frame) {
    RenderList list;
    list.id_count = 0;

    for (auto& mesh : meshes) {
        DrawCommand newCommand;
        newCommand.model = mesh->model;
        newCommand.meshID = list.id_count++;
        newCommand.materialID = 0;

        list.commands.push_back(newCommand);
    }

    list.frame_data = frame;
    return list;
}

}
