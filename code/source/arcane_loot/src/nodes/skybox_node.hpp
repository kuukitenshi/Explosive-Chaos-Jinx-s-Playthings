#pragma once

#include <tangram/engine/api.hpp>

using namespace tangram::engine;

class SkyBoxNode : public SceneNode
{
public:
    SkyBoxNode(const std::unique_ptr<GraphicsAPI>& graphics, std::array<Image, 6> images,
               std::shared_ptr<Camera> camera);

    std::array<Image, 6> getImages() const;
    void setImages(const std::array<Image, 6>& images);

    std::shared_ptr<Texture> getTexture() const;

    void draw(const std::unique_ptr<GraphicsAPI>& graphics) override;

private:
    std::array<Image, 6> mImages;
    std::shared_ptr<Texture> mTexture;
    std::shared_ptr<VertexArray> mVAO;
    std::shared_ptr<IndexBuffer> mIBO;
    std::shared_ptr<Camera> mCamera;
};
