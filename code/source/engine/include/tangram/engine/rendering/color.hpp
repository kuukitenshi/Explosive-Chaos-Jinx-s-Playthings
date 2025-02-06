#pragma once

#include <glm/glm.hpp>

namespace tangram::engine
{
    struct Color
    {
        float r{0.0f};
        float g{0.0f};
        float b{0.0f};
        float a{1.0f};

        glm::vec4 rgba() const;

        glm::vec3 rgb() const;

        static Color fromRGB(uint8_t r, uint8_t g, uint8_t b);

        static Color fromRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    };
} // namespace tangram::engine
