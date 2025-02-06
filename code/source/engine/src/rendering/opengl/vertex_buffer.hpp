#pragma once

#include <glad/glad.h>
#include <tangram/engine/rendering/graphics_api.hpp>

namespace tangram::engine
{
    class OpenGlVertexBuffer : public VertexBuffer
    {
    public:
        OpenGlVertexBuffer(size_t size, void* data);

        ~OpenGlVertexBuffer();

        GLuint id() const;

    private:
        GLuint mId;
    };
} // namespace tangram::engine
