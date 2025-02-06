#include <tangram/engine/rendering/texture_description.hpp>

namespace tangram::engine
{
    Texture2DDescription::Texture2DDescription(Image image)
        : mImage(image)
    {
    }

    Image Texture2DDescription::getImage() const
    {
        return mImage;
    }

    CubeMapDescription::CubeMapDescription(std::array<Image, 6> images)
        : mImages(images)
    {
    }

    std::array<Image, 6> CubeMapDescription::getImages() const
    {
        return mImages;
    }

    Texture2DArrayDescription::Texture2DArrayDescription(std::vector<Image> images)
        : mImages(images)
    {
    }
    std::vector<Image> Texture2DArrayDescription::getImages() const
    {
        return mImages;
    }
} // namespace tangram::engine
