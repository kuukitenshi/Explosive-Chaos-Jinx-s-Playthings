#pragma once

#include <glad/glad.h>
#include <tangram/engine/rendering/image.hpp>
#include <tangram/engine/rendering/texture.hpp>

namespace tangram::engine
{
    class OpenGlTexture : public Texture
    {
    public:
        OpenGlTexture(TextureType type, std::shared_ptr<TextureDescription> description);

        ~OpenGlTexture();

        GLuint id() const;

        GLenum glType() const;

    private:
        GLuint mId;
    };

} // namespace tangram::engine
