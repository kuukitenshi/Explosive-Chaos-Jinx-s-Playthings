#pragma once

#include <glad/glad.h>
#include <tangram/engine/rendering/graphics_api.hpp>

namespace tangram::engine
{
    class OpenGlShader : public Shader
    {
    public:
        OpenGlShader(ShaderType type, const std::string& source);

        ~OpenGlShader();

        GLuint id() const;

    private:
        GLuint mId;
    };
} // namespace tangram::engine
