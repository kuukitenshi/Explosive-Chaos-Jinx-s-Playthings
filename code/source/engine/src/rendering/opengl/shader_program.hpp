#pragma once

#include <glad/glad.h>
#include <tangram/engine/rendering/graphics_api.hpp>

namespace tangram::engine
{
    class OpenGlShaderProgram : public ShaderProgram
    {
    public:
        OpenGlShaderProgram(const ShaderProgramDescription& desc);

        ~OpenGlShaderProgram();

        GLuint id() const;

    private:
        GLuint mId;
    };
} // namespace tangram::engine
