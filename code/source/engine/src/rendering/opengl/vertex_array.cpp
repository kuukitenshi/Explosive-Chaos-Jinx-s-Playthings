#include "vertex_array.hpp"

#include "index_buffer.hpp"
#include "tangram/engine/rendering/vertex_layout.hpp"
#include "vertex_buffer.hpp"

#include <iostream>
#include <memory>

namespace tangram::engine
{
    static GLenum elementTypeToGlType(const ElementType& type)
    {
        switch (type)
        {
        case ElementType::FLOAT:
            return GL_FLOAT;
        case ElementType::INT:
            return GL_INT;
        default:
            std::cerr << "Invalid element type!" << std::endl;
            std::abort();
            return GL_NONE;
        };
    }

    OpenGlVertexArray::OpenGlVertexArray(VertexArrayDescription desc)
    {
        glGenVertexArrays(1, &mId);
        glBindVertexArray(mId);
        uint32_t attribIndex = 0;
        for (size_t i = 0; i < desc.vertexBufers.size(); i++)
        {
            auto buffer = desc.vertexBufers[i];
            auto oglBuffer = std::static_pointer_cast<OpenGlVertexBuffer>(buffer);
            glBindBuffer(GL_ARRAY_BUFFER, oglBuffer->id());
            const VertexLayout& layout = desc.layouts[i];
            for (const LayoutElement& elem : layout.elements())
            {
                auto index = static_cast<GLuint>(attribIndex);
                auto count = static_cast<GLint>(elem.count);
                auto stride = static_cast<GLsizei>(layout.stride());
                auto offset = reinterpret_cast<void*>(elem.offset);
                glEnableVertexAttribArray(index);
                glVertexAttribPointer(index, count, elementTypeToGlType(elem.type), GL_FALSE, stride, offset);
                attribIndex++;
            }
        }
        if (desc.indexBuffer != nullptr)
        {
            auto buffer = std::static_pointer_cast<OpenGlIndexBuffer>(desc.indexBuffer);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->id());
        }
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    OpenGlVertexArray::~OpenGlVertexArray()
    {
        glDeleteVertexArrays(1, &mId);
    }

    GLuint OpenGlVertexArray::id() const
    {
        return mId;
    }
} // namespace tangram::engine
