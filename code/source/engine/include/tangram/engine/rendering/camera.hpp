#pragma once

#include <glm/glm.hpp>

namespace tangram::engine
{
    struct Camera
    {
        glm::mat4 projection{1.0f};
        glm::vec3 up{0.0f, 1.0f, 0.0f};
        glm::vec3 center{0.0f};
        glm::vec3 eye{0.0f, 0.0f, -1.0f};

        glm::mat4 viewMatrix() const;
    };
} // namespace tangram::engine
