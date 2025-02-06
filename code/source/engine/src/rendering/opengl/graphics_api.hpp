#pragma once

#include <cstddef>
#include <glm/glm.hpp>
#include <memory>
#include <tangram/engine/rendering/graphics_api.hpp>

namespace tangram::engine
{
    class OpenglGraphicsAPI : public GraphicsAPI
    {
    public:
        std::shared_ptr<VertexArray> createVertexArray(VertexArrayDescription desc) override;

        std::shared_ptr<VertexBuffer> createVertexBuffer(size_t size, void* data) override;

        std::shared_ptr<IndexBuffer> createIndexBuffer(size_t size, void* data) override;

        std::shared_ptr<UniformBuffer> createUniformBuffer(size_t size, void* data) override;

        std::shared_ptr<Shader> createShader(ShaderType type, const std::string& source) override;

        std::shared_ptr<ShaderProgram> createShaderProgram(const ShaderProgramDescription& desc) override;

        std::shared_ptr<Texture> createTexture(TextureType type, std::shared_ptr<TextureDescription> desc) override;

        void useShaderProgram(std::shared_ptr<ShaderProgram> program) override;

        void bindVertexBuffer(std::shared_ptr<VertexBuffer> buffer) override;

        void bindVertexArray(std::shared_ptr<VertexArray> vertexArray) override;

        void bindIndexBuffer(std::shared_ptr<IndexBuffer> buffer) override;

        void bindUniformBuffer(std::shared_ptr<UniformBuffer> buffer) override;

        void bindTexture(std::shared_ptr<Texture> texture, int unit) override;

        void uniformBufferSubData(std::shared_ptr<UniformBuffer> buffer, size_t offset, size_t size,
                                  const void* data) override;

        void clearColor(glm::vec4 color) override;

        void clearBackground() override;

        void drawTriangles(size_t vertexCount) override;

        void drawElements(std::shared_ptr<IndexBuffer> ibo) override;

        void drawElementsBaseVertex(uint32_t count, void* indices, int32_t baseVertex) override;

        void setViewport(int x, int y, size_t width, size_t height) override;

        void setUniformMat4(std::shared_ptr<ShaderProgram> program, const std::string& loc, glm::mat4 mat) override;

        void setUniform1i(std::shared_ptr<ShaderProgram> program, const std::string& loc, int value) override;

        void setUniform3f(std::shared_ptr<ShaderProgram> program, const std::string& loc, glm::vec3 value) override;

        void setUniform4f(std::shared_ptr<ShaderProgram> program, const std::string& loc, glm::vec4 vec) override;

        void setUniform1f(std::shared_ptr<ShaderProgram> program, const std::string& loc, float value) override;

        void enableDebugging() override;

        bool debugEnabled() const override;

        void setCullFace(CullFace face) const override;

        void depthFunc(DepthFunc dephtFunc) const override;

    private:
        bool mDebugguingEnabled{false};
    };
} // namespace tangram::engine
