#include "vertex_buffer.hpp"

#include <glad/glad.h>
#include <tangram/engine/rendering/graphics_api.hpp>

namespace tangram::engine
{
    OpenGlVertexBuffer::OpenGlVertexBuffer(size_t size, void* data)
    {
        glGenBuffers(1, &mId);
        glBindBuffer(GL_ARRAY_BUFFER, mId);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(size), data, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    OpenGlVertexBuffer::~OpenGlVertexBuffer()
    {
        glDeleteBuffers(1, &mId);
    }

    GLuint OpenGlVertexBuffer::id() const
    {
        return mId;
    }
} // namespace tangram::engine
