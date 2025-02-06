#pragma once

#include "tangram/engine/rendering/graphics_api.hpp"

#include <cstddef>
#include <glad/glad.h>

namespace tangram::engine
{
    class OpenGlUniformBuffer : public UniformBuffer
    {
    public:
        OpenGlUniformBuffer(size_t size, void* data);

        ~OpenGlUniformBuffer();

        GLuint id() const;

        void subData(size_t offset, size_t size, const void* data) const;

    private:
        GLuint mId;
    };
} // namespace tangram::engine
