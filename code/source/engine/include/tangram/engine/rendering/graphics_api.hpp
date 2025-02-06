#pragma once

#include "tangram/engine/rendering/image.hpp"

#include <cstddef>
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <tangram/engine/rendering/shader.hpp>
#include <tangram/engine/rendering/texture.hpp>
#include <tangram/engine/rendering/vertex_layout.hpp>
#include <vector>

namespace tangram::engine
{
    class IndexBuffer
    {
    };
    class ShaderProgram
    {
    };
    class VertexBuffer
    {
    };
    class VertexArray
    {
    };
    class UniformBuffer
    {
    };

    struct ShaderProgramDescription
    {
        std::shared_ptr<Shader> vertex;
        std::shared_ptr<Shader> fragment;
    };

    struct VertexArrayDescription
    {
        std::vector<std::shared_ptr<VertexBuffer>> vertexBufers;
        std::vector<VertexLayout> layouts;
        std::shared_ptr<IndexBuffer> indexBuffer;
    };

    enum class CullFace
    {
        FRONT,
        BACK
    };

    enum class DepthFunc
    {
        LESS,
        LEQUAL
    };

    class GraphicsAPI
    {
    public:
        static std::unique_ptr<GraphicsAPI> create();

        virtual ~GraphicsAPI() = default;

        virtual std::shared_ptr<VertexArray> createVertexArray(VertexArrayDescription desc) = 0;

        virtual std::shared_ptr<VertexBuffer> createVertexBuffer(size_t size, void* data) = 0;

        virtual std::shared_ptr<IndexBuffer> createIndexBuffer(size_t size, void* data) = 0;

        virtual std::shared_ptr<UniformBuffer> createUniformBuffer(size_t size, void* data) = 0;

        virtual std::shared_ptr<Shader> createShader(ShaderType type, const std::string& source) = 0;

        virtual std::shared_ptr<ShaderProgram> createShaderProgram(const ShaderProgramDescription& desc) = 0;

        virtual std::shared_ptr<Texture> createTexture(TextureType type, std::shared_ptr<TextureDescription> desc) = 0;

        virtual void useShaderProgram(std::shared_ptr<ShaderProgram> program) = 0;

        virtual void bindVertexBuffer(std::shared_ptr<VertexBuffer> buffer) = 0;

        virtual void bindVertexArray(std::shared_ptr<VertexArray> vertexArray) = 0;

        virtual void bindIndexBuffer(std::shared_ptr<IndexBuffer> buffer) = 0;

        virtual void bindUniformBuffer(std::shared_ptr<UniformBuffer> buffer) = 0;

        virtual void bindTexture(std::shared_ptr<Texture> texture, int unit) = 0;

        virtual void uniformBufferSubData(std::shared_ptr<UniformBuffer> buffer, size_t offset, size_t size,
                                          const void* data) = 0;

        virtual void clearColor(glm::vec4 color) = 0;

        virtual void clearBackground() = 0;

        virtual void drawTriangles(size_t vertexcount) = 0;

        virtual void drawElements(std::shared_ptr<IndexBuffer> ibo) = 0;

        virtual void drawElementsBaseVertex(uint32_t count, void* indices, int32_t baseVertex) = 0;

        virtual void setViewport(int x, int y, size_t width, size_t height) = 0;

        virtual void setUniform4f(std::shared_ptr<ShaderProgram> program, const std::string& loc, glm::vec4 vec) = 0;

        virtual void setUniformMat4(std::shared_ptr<ShaderProgram> program, const std::string& loc, glm::mat4 mat) = 0;

        virtual void setUniform1i(std::shared_ptr<ShaderProgram> program, const std::string& loc, int value) = 0;

        virtual void setUniform3f(std::shared_ptr<ShaderProgram> program, const std::string& loc, glm::vec3 value) = 0;

        virtual void setUniform1f(std::shared_ptr<ShaderProgram> program, const std::string& loc, float value) = 0;

        virtual void enableDebugging() = 0;

        virtual bool debugEnabled() const = 0;

        virtual void setCullFace(CullFace face) const = 0;

        virtual void depthFunc(DepthFunc dephtFunc) const = 0;
    };
} // namespace tangram::engine
