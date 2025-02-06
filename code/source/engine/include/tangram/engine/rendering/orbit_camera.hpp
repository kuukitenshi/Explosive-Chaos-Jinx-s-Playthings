#pragma once

#include "tangram/engine/rendering/camera.hpp"
namespace tangram::engine
{
    class OrbitCamera : public Camera
    {
    public:
        void move(const glm::vec2& movement);

        void zoom(float zoom);
    };
} // namespace tangram::engine
