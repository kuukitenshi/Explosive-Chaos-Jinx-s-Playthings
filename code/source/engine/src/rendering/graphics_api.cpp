#include "opengl/graphics_api.hpp"

#include <tangram/engine/rendering/graphics_api.hpp>

namespace tangram::engine
{
    std::unique_ptr<GraphicsAPI> GraphicsAPI::create()
    {
        return std::make_unique<OpenglGraphicsAPI>();
    }
} // namespace tangram::engine
