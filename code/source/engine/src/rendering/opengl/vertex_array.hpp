#pragma once

#include "vertex_buffer.hpp"

#include <glad/glad.h>
#include <tangram/engine/rendering/graphics_api.hpp>

namespace tangram::engine
{
    class OpenGlVertexArray : public VertexArray
    {
    public:
        OpenGlVertexArray(VertexArrayDescription desc);

        ~OpenGlVertexArray();

        GLuint id() const;

    private:
        GLuint mId;
    };
} // namespace tangram::engine
