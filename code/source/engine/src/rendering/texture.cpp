#include <tangram/engine/rendering/texture.hpp>

namespace tangram::engine
{

    Texture::Texture(TextureType type, std::shared_ptr<TextureDescription> desc)
        : mType(type)
        , mDescription(desc)
    {
    }

    TextureType Texture::type() const
    {
        return mType;
    }

    std::shared_ptr<TextureDescription> Texture::description() const
    {
        return mDescription;
    }
} // namespace tangram::engine
