#pragma once

#include <filesystem>

namespace tangram::engine
{
    struct Image
    {
        int width = 0;
        int height = 0;
        int nrChannels = 0;
        std::shared_ptr<unsigned char> pixels = nullptr;

        Image(std::filesystem::path path, bool flipVertically = true);

        Image(std::filesystem::path path, int desiredChannels, bool flipVertically = true);

        Image(int width, int height, int nrChannels, std::shared_ptr<unsigned char> pixels);

        void saveImage(const std::string& filename);
    };
} // namespace tangram::engine
