#pragma once

#include "tangram/engine/rendering/graphics_api.hpp"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace tangram::engine
{
    struct Mesh
    {
        uint32_t indexCount;
        uint32_t baseIndex;
        uint32_t baseVertex;
    };

    class Model
    {
    public:
        Model(const std::unique_ptr<GraphicsAPI>& graphics, const std::string& path);

        void draw(const std::unique_ptr<GraphicsAPI>& graphics) const;

    private:
        std::vector<Mesh> mMeshes;
        std::shared_ptr<VertexArray> mVertexArray;
    };
} // namespace tangram::engine
