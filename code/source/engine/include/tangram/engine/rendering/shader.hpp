#pragma once

namespace tangram::engine
{
    enum class ShaderType
    {
        VERTEX_SHADER,
        FRAGMENT_SHADER
    };

    class Shader
    {
    public:
        Shader(ShaderType type);

        ShaderType type() const;

    private:
        ShaderType mType;
    };
} // namespace tangram::engine
