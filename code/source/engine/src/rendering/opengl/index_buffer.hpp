#pragma once

#include <glad/glad.h>
#include <tangram/engine/rendering/graphics_api.hpp>

namespace tangram::engine
{
    class OpenGlIndexBuffer : public IndexBuffer
    {
    public:
        OpenGlIndexBuffer(size_t count, void* data);

        ~OpenGlIndexBuffer();

        GLuint id() const;

        size_t count() const;

    private:
        GLuint mId;
        size_t mCount;
    };
} // namespace tangram::engine
