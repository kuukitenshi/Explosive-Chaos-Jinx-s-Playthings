#include <tangram/engine/rendering/color.hpp>

namespace tangram::engine
{
    glm::vec3 Color::rgb() const
    {
        return {r, g, b};
    }

    glm::vec4 Color::rgba() const
    {
        return {r, g, b, a};
    }

    Color Color::fromRGB(uint8_t r, uint8_t g, uint8_t b)
    {
        return Color{.r = r / 255.0f, .g = g / 255.0f, .b = b / 255.0f, .a = 1.0f};
    }

    Color Color::fromRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        return Color{.r = r / 255.0f, .g = g / 255.0f, .b = b / 255.0f, .a = a / 255.0f};
    }
} // namespace tangram::engine
