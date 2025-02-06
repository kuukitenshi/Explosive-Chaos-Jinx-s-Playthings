#pragma once

#include "tangram/engine/rendering/image.hpp"

#include <array>
#include <vector>

namespace tangram::engine
{
    class TextureDescription
    {
    };

    class Texture2DDescription : public TextureDescription
    {
    public:
        Texture2DDescription(Image image);
        Image getImage() const;

    private:
        Image mImage;
    };

    class CubeMapDescription : public TextureDescription
    {
    public:
        CubeMapDescription(std::array<Image, 6> images);
        std::array<Image, 6> getImages() const;

    private:
        std::array<Image, 6> mImages;
    };

    class Texture2DArrayDescription : public TextureDescription
    {
    public:
        Texture2DArrayDescription(std::vector<Image> images);
        std::vector<Image> getImages() const;

    private:
        std::vector<Image> mImages;
    };

} // namespace tangram::engine
