#include "texture.hpp"

#include <cassert>
#include <iostream>

namespace tangram::engine
{
    static GLenum textureTypeToGlType(TextureType type)
    {
        switch (type)
        {
        case TextureType::Texture2D:
            return GL_TEXTURE_2D;

        case TextureType::Texture2DArray:
            return GL_TEXTURE_2D_ARRAY;

        case TextureType::CubeMap:
            return GL_TEXTURE_CUBE_MAP;
        }
        std::cerr << "Not impleted texture type" << std::endl;
        std::abort();
    }

    OpenGlTexture::OpenGlTexture(TextureType type, std::shared_ptr<TextureDescription> description)
        : Texture(type, description)
    {
        GLenum glType = textureTypeToGlType(type);
        glGenTextures(1, &mId);
        glBindTexture(glType, mId);
        switch (type)
        {
        case TextureType::Texture2D: {
            glTexParameteri(glType, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(glType, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(glType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(glType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            auto text2d = std::static_pointer_cast<Texture2DDescription>(description);
            Image image = text2d->getImage();
            assert(image.nrChannels == 1 || image.nrChannels == 3 || image.nrChannels == 4);
            GLenum srcFormat = image.nrChannels == 3 ? GL_RGB : image.nrChannels == 4 ? GL_RGBA : GL_RED;

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, srcFormat, GL_UNSIGNED_BYTE,
                         image.pixels.get());
            glGenerateMipmap(GL_TEXTURE_2D);
            break;
        }
        case TextureType::Texture2DArray: {
            glTexParameteri(glType, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(glType, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(glType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(glType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            auto text2dArray = std::static_pointer_cast<Texture2DArrayDescription>(description);
            std::vector<Image> images = text2dArray->getImages();
            for (int i = 0; i < images.size(); i++)
            {
                Image image = images[i];
                assert(image.nrChannels == 1 || image.nrChannels == 3 || image.nrChannels == 4);
                GLenum srcFormat = image.nrChannels == 3 ? GL_RGB : image.nrChannels == 4 ? GL_RGBA : GL_RED;
                glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, image.width, image.height, i, 0, srcFormat,
                             GL_UNSIGNED_BYTE, image.pixels.get());
            }
            glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
            break;
        }
        case TextureType::CubeMap: {
            glTexParameteri(glType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(glType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(glType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(glType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(glType, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

            auto cubeDesc = std::static_pointer_cast<CubeMapDescription>(description);
            std::array<Image, 6> images = cubeDesc->getImages();
            for (int i = 0; i < 6; i++)
            {
                Image image = images[i];
                assert(image.nrChannels == 3 || image.nrChannels == 4);
                GLenum srcFormat = image.nrChannels == 3 ? GL_RGB : GL_RGBA;
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, image.width, image.height, 0, srcFormat,
                             GL_UNSIGNED_BYTE, image.pixels.get());
            }
            break;
        }
        }
        glBindTexture(glType, 0);
    }

    OpenGlTexture::~OpenGlTexture()
    {
        glDeleteTextures(1, &mId);
    }

    GLuint OpenGlTexture::id() const
    {
        return mId;
    }

    GLenum OpenGlTexture::glType() const
    {
        return textureTypeToGlType(this->type());
    }
} // namespace tangram::engine
