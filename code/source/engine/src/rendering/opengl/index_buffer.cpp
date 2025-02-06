#include "index_buffer.hpp"

#include <cstdint>

namespace tangram::engine
{
    OpenGlIndexBuffer::OpenGlIndexBuffer(size_t count, void* data)
    {
        mCount = count;
        glGenBuffers(1, &mId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(count * sizeof(uint32_t)), data, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    OpenGlIndexBuffer::~OpenGlIndexBuffer()
    {
        glDeleteBuffers(1, &mId);
    }

    GLuint OpenGlIndexBuffer::id() const
    {
        return mId;
    }

    size_t OpenGlIndexBuffer::count() const
    {
        return mCount;
    }
} // namespace tangram::engine
