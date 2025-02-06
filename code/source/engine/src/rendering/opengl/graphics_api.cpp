#include "graphics_api.hpp"

#include "index_buffer.hpp"
#include "shader.hpp"
#include "shader_program.hpp"
#include "tangram/engine/rendering/graphics_api.hpp"
#include "texture.hpp"
#include "uniform_buffer.hpp"
#include "vertex_array.hpp"
#include "vertex_buffer.hpp"

#include <cstdio>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

namespace tangram::engine
{
    void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length,
                                const char* message, const void* userParam)
    {
        if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
            return;
        std::printf("[%d %d] OPENGL DEBUG (%d) > %s\n", severity, id, type, message);
    }

    std::shared_ptr<VertexArray> OpenglGraphicsAPI::createVertexArray(VertexArrayDescription desc)
    {
        return std::make_shared<OpenGlVertexArray>(desc);
    }

    std::shared_ptr<VertexBuffer> OpenglGraphicsAPI::createVertexBuffer(size_t size, void* data)
    {
        return std::make_shared<OpenGlVertexBuffer>(size, data);
    }

    std::shared_ptr<IndexBuffer> OpenglGraphicsAPI::createIndexBuffer(size_t count, void* data)
    {
        return std::make_shared<OpenGlIndexBuffer>(count, data);
    }

    std::shared_ptr<UniformBuffer> OpenglGraphicsAPI::createUniformBuffer(size_t size, void* data)
    {
        return std::make_shared<OpenGlUniformBuffer>(size, data);
    }

    std::shared_ptr<Shader> OpenglGraphicsAPI::createShader(ShaderType type, const std::string& source)
    {
        return std::make_shared<OpenGlShader>(type, source);
    }

    std::shared_ptr<ShaderProgram> OpenglGraphicsAPI::createShaderProgram(const ShaderProgramDescription& desc)
    {
        return std::make_shared<OpenGlShaderProgram>(desc);
    }

    std::shared_ptr<Texture> OpenglGraphicsAPI::createTexture(TextureType type,
                                                              std::shared_ptr<TextureDescription> desc)
    {
        return std::make_shared<OpenGlTexture>(type, desc);
    }

    void OpenglGraphicsAPI::useShaderProgram(std::shared_ptr<ShaderProgram> program)
    {
        auto openglProgram = std::static_pointer_cast<OpenGlShaderProgram>(program);
        glUseProgram(openglProgram->id());
    }

    void OpenglGraphicsAPI::bindVertexBuffer(std::shared_ptr<VertexBuffer> buffer)
    {
        auto openglBuffer = std::static_pointer_cast<OpenGlVertexBuffer>(buffer);
        glBindBuffer(GL_ARRAY_BUFFER, openglBuffer->id());
    }

    void OpenglGraphicsAPI::bindVertexArray(std::shared_ptr<VertexArray> vertexArray)
    {
        auto openglVertexArray = std::static_pointer_cast<OpenGlVertexArray>(vertexArray);
        glBindVertexArray(openglVertexArray->id());
    }

    void OpenglGraphicsAPI::bindIndexBuffer(std::shared_ptr<IndexBuffer> buffer)
    {
        auto openglBuffer = std::static_pointer_cast<OpenGlIndexBuffer>(buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, openglBuffer->id());
    }

    void OpenglGraphicsAPI::bindUniformBuffer(std::shared_ptr<UniformBuffer> buffer)
    {
        auto openglBuffer = std::static_pointer_cast<OpenGlUniformBuffer>(buffer);
        glBindBuffer(GL_UNIFORM_BUFFER, openglBuffer->id());
    }

    void OpenglGraphicsAPI::bindTexture(std::shared_ptr<Texture> texture, int unit)
    {
        auto openglTexture = std::static_pointer_cast<OpenGlTexture>(texture);
        glBindTextureUnit(unit, openglTexture->id());
    }

    void OpenglGraphicsAPI::uniformBufferSubData(std::shared_ptr<UniformBuffer> buffer, size_t offset, size_t size,
                                                 const void* data)
    {
        auto openglBuffer = std::static_pointer_cast<OpenGlUniformBuffer>(buffer);
        openglBuffer->subData(offset, size, data);
    }

    void OpenglGraphicsAPI::clearColor(glm::vec4 color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenglGraphicsAPI::clearBackground()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    void OpenglGraphicsAPI::drawTriangles(size_t vertexCount)
    {
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertexCount));
    }

    void OpenglGraphicsAPI::drawElements(std::shared_ptr<IndexBuffer> ibo)
    {
        auto openglIndexBuffer = std::static_pointer_cast<OpenGlIndexBuffer>(ibo);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(openglIndexBuffer->count()), GL_UNSIGNED_INT,
                       reinterpret_cast<GLvoid*>(0));
    }

    void OpenglGraphicsAPI::drawElementsBaseVertex(uint32_t count, void* indices, int32_t baseVertex)
    {
        glDrawElementsBaseVertex(GL_TRIANGLES, static_cast<GLsizei>(count), GL_UNSIGNED_INT, indices,
                                 static_cast<GLint>(baseVertex));
    }

    void OpenglGraphicsAPI::setViewport(int x, int y, size_t width, size_t height)
    {
        glViewport(x, y, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
    }

    void OpenglGraphicsAPI::setUniform4f(std::shared_ptr<ShaderProgram> program, const std::string& loc, glm::vec4 vec)
    {
        auto openglProgram = std::static_pointer_cast<OpenGlShaderProgram>(program);
        GLint location = glGetUniformLocation(openglProgram->id(), loc.c_str());
        glUniform4fv(location, 1, glm::value_ptr(vec));
    }

    void OpenglGraphicsAPI::setUniformMat4(std::shared_ptr<ShaderProgram> program, const std::string& loc,
                                           glm::mat4 mat)
    {
        auto openglProgram = std::static_pointer_cast<OpenGlShaderProgram>(program);
        GLint location = glGetUniformLocation(openglProgram->id(), loc.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
    }

    void OpenglGraphicsAPI::setUniform1i(std::shared_ptr<ShaderProgram> program, const std::string& loc, int value)
    {
        auto openglProgram = std::static_pointer_cast<OpenGlShaderProgram>(program);
        GLint location = glGetUniformLocation(openglProgram->id(), loc.c_str());
        glUniform1i(location, value);
    }

    void OpenglGraphicsAPI::setUniform3f(std::shared_ptr<ShaderProgram> program, const std::string& loc,
                                         glm::vec3 value)
    {
        auto openglProgram = std::static_pointer_cast<OpenGlShaderProgram>(program);
        GLint location = glGetUniformLocation(openglProgram->id(), loc.c_str());
        glUniform3fv(location, 1, glm::value_ptr(value));
    }

    void OpenglGraphicsAPI::setUniform1f(std::shared_ptr<ShaderProgram> program, const std::string& loc, float value)
    {
        auto openglProgram = std::static_pointer_cast<OpenGlShaderProgram>(program);
        GLint location = glGetUniformLocation(openglProgram->id(), loc.c_str());
        glUniform1f(location, value);
    }

    void OpenglGraphicsAPI::enableDebugging()
    {
        mDebugguingEnabled = true;
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }

    bool OpenglGraphicsAPI::debugEnabled() const
    {
        return mDebugguingEnabled;
    }

    void OpenglGraphicsAPI::setCullFace(CullFace face) const
    {
        switch (face)
        {
        case CullFace::FRONT:
            glCullFace(GL_FRONT);
            break;

        case CullFace::BACK:
            glCullFace(GL_BACK);
            break;
        }
    }

    void OpenglGraphicsAPI::depthFunc(DepthFunc dephtFunc) const
    {
        switch (dephtFunc)
        {
        case DepthFunc::LESS:
            glDepthFunc(GL_LESS);
            break;

        case DepthFunc::LEQUAL:
            glDepthFunc(GL_LEQUAL);
            break;
        }
    }
} // namespace tangram::engine
