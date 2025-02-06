#include <cassert>
#include <stb_image.h>
#include <stb_image_write.h>
#include <tangram/engine/rendering/image.hpp>

namespace tangram::engine
{
    Image::Image(std::filesystem::path path, bool flipVertically)
    {
        stbi_set_flip_vertically_on_load(flipVertically);
        auto pPixels = stbi_load(path.string().c_str(), &width, &height, &nrChannels, 0);
        pixels = std::shared_ptr<unsigned char>(pPixels, stbi_image_free);
        assert(pixels != nullptr);
    }

    Image::Image(std::filesystem::path path, int desiredChannels, bool flipVertically)
    {
        stbi_set_flip_vertically_on_load(flipVertically);
        auto pPixels = stbi_load(path.string().c_str(), &width, &height, &nrChannels, desiredChannels);
        pixels = std::shared_ptr<unsigned char>(pPixels, stbi_image_free);
        assert(pixels != nullptr);
    }

    Image::Image(int width, int height, int nrChannels, std::shared_ptr<unsigned char> pixels)
        : width(width)
        , height(height)
        , nrChannels(nrChannels)
        , pixels(pixels)
    {
    }

    void Image::saveImage(const std::string& filename)
    {
        stbi_write_jpg(filename.c_str(), width, height, nrChannels, pixels.get(), 100);
    }

} // namespace tangram::engine
