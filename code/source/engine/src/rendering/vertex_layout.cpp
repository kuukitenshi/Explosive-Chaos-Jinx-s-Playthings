#include <tangram/engine/rendering/vertex_layout.hpp>

namespace tangram::engine
{
    VertexLayout::VertexLayout()
        : mElements({})
        , mStride(0)
    {
    }

    template <>
    void VertexLayout::push<float>(size_t count)
    {
        size_t offset = mStride;
        mElements.push_back(LayoutElement{.type = ElementType::FLOAT, .count = count, .offset = offset});
        mStride += count * sizeof(float);
    }

    template <>
    void VertexLayout::push<int>(size_t count)
    {
        size_t offset = mStride;
        mElements.push_back(LayoutElement{.type = ElementType::INT, .count = count, .offset = offset});
        mStride += count * sizeof(int);
    }

    const std::vector<LayoutElement>& VertexLayout::elements() const
    {
        return mElements;
    }

    size_t VertexLayout::stride() const
    {
        return mStride;
    }

} // namespace tangram::engine
