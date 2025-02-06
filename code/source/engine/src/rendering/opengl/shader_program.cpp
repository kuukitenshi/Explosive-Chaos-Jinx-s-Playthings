#include "shader_program.hpp"

#include "shader.hpp"

#include <array>
#include <cstdlib>
#include <iostream>

namespace tangram::engine
{
    OpenGlShaderProgram::OpenGlShaderProgram(const ShaderProgramDescription& desc)
    {
        mId = glCreateProgram();
        auto vertex = std::static_pointer_cast<OpenGlShader>(desc.vertex);
        auto frag = std::static_pointer_cast<OpenGlShader>(desc.fragment);
        glAttachShader(mId, vertex->id());
        glAttachShader(mId, frag->id());
        glLinkProgram(mId);
        GLint success;
        glGetProgramiv(mId, GL_LINK_STATUS, &success);
        if (!success)
        {
            std::array<char, 1024> infoLog;
            glGetProgramInfoLog(mId, 1024, nullptr, infoLog.data());
            std::cout << "Program Link error: " << infoLog.data() << std::endl;
            std::abort();
        }
        GLuint index = glGetUniformBlockIndex(mId, "Camera");
        if (index == GL_INVALID_INDEX)
        {
            std::cerr << "Invalid index" << std::endl;
        }
        glUniformBlockBinding(mId, index, 0);
    }

    OpenGlShaderProgram::~OpenGlShaderProgram()
    {
        glDeleteProgram(mId);
    }

    GLuint OpenGlShaderProgram::id() const
    {
        return mId;
    }
} // namespace tangram::engine
