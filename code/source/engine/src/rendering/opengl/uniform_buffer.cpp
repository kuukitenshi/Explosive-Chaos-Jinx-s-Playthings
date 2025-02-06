#include "uniform_buffer.hpp"

#include <cstddef>

namespace tangram::engine
{
    OpenGlUniformBuffer::OpenGlUniformBuffer(size_t size, void* data)
    {
        glGenBuffers(1, &mId);
        glBindBuffer(GL_UNIFORM_BUFFER, mId);
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, mId);
        glBufferData(GL_UNIFORM_BUFFER, static_cast<GLsizeiptr>(size), data, GL_STREAM_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    OpenGlUniformBuffer::~OpenGlUniformBuffer()
    {
        glDeleteBuffers(1, &mId);
    }

    GLuint OpenGlUniformBuffer::id() const
    {
        return mId;
    }

    void OpenGlUniformBuffer::subData(size_t offset, size_t size, const void* data) const
    {
        glBindBuffer(GL_UNIFORM_BUFFER, mId);
        glBufferSubData(GL_UNIFORM_BUFFER, static_cast<GLintptr>(offset), static_cast<GLsizeiptr>(size), data);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

} // namespace tangram::engine
