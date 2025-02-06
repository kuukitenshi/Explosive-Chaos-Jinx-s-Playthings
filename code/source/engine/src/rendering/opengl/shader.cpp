#include "shader.hpp"

#include <array>
#include <cstdlib>
#include <iostream>

namespace tangram::engine
{
    static GLenum shaderTypeToGlType(ShaderType type)
    {
        switch (type)
        {
        case ShaderType::FRAGMENT_SHADER:
            return GL_FRAGMENT_SHADER;
        case ShaderType::VERTEX_SHADER:
            return GL_VERTEX_SHADER;
        default:
            std::cerr << "Invalid shader type!" << std::endl;
            std::abort();
            return GL_NONE;
        }
    }

    OpenGlShader::OpenGlShader(ShaderType type, const std::string& source)
        : Shader(type)
    {
        mId = glCreateShader(shaderTypeToGlType(type));
        const char* str = source.c_str();
        glShaderSource(mId, 1, &str, nullptr);
        glCompileShader(mId);
        GLint success;
        glGetShaderiv(mId, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            std::array<char, 1024> infoLog;
            glGetShaderInfoLog(mId, 1024, nullptr, infoLog.data());
            std::cerr << "Shader Compile error: " << infoLog.data() << std::endl;
            std::abort();
        }
    }

    OpenGlShader::~OpenGlShader()
    {
        glDeleteShader(mId);
    }

    GLuint OpenGlShader::id() const
    {
        return mId;
    }
} // namespace tangram::engine
