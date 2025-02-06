#pragma once

#include <cstddef>
#include <vector>

namespace tangram::engine
{
    enum class ElementType
    {
        FLOAT,
        INT
    };

    struct LayoutElement
    {
        ElementType type;
        size_t count;
        size_t offset;
    };

    class VertexLayout
    {
    public:
        VertexLayout();

        template <typename T>
        void push(size_t count);

        const std::vector<LayoutElement>& elements() const;

        size_t stride() const;

    private:
        std::vector<LayoutElement> mElements;
        size_t mStride;
    };
} // namespace tangram::engine
