#pragma once
#include "texture_description.hpp"

namespace tangram::engine
{

    enum class TextureType
    {
        Texture2D,
        Texture2DArray,
        CubeMap
    };

    class Texture
    {
    public:
        Texture(TextureType type, std::shared_ptr<TextureDescription> desc);

        TextureType type() const;

        std::shared_ptr<TextureDescription> description() const;

    private:
        TextureType mType;
        std::shared_ptr<TextureDescription> mDescription;
    };

} // namespace tangram::engine
