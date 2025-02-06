#pragma once

#include "tangram/engine/rendering/model.hpp"
#include <tangram/engine/api.hpp>
#include <tangram/engine/rendering/light.hpp>
#include <tangram/engine/rendering/material.hpp>
#include <tangram/engine/rendering/model.hpp>
#include <tangram/engine/scene/scene_node.hpp>

using namespace tangram::engine;

class NormalObjectNode : public SceneNode
{
public:
    // Blinn-Phong + normal mapping + metallic + emission + texture
    NormalObjectNode(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture,
                     std::shared_ptr<Texture> normalTexture, std::shared_ptr<Texture> metallicTexture,
                     std::shared_ptr<Light> light, std::shared_ptr<Material> material,
                     std::shared_ptr<Texture> emissionTexture = nullptr);

    const std::shared_ptr<Model> getModel() const;
    void setModel(const std::shared_ptr<Model> model);

    const std::shared_ptr<Texture> getTexture() const;
    void setTexture(const std::shared_ptr<Texture> texture);

    const std::shared_ptr<Texture> getNormalTexture() const;
    void setNormalTexture(const std::shared_ptr<Texture> normalTexture);

    const std::shared_ptr<Texture> getMetallicTexture() const;
    void setMetallicTexture(const std::shared_ptr<Texture> metallicTexture);

    const std::shared_ptr<Texture> getEmissionTexture() const;
    void setEmissionTexture(const std::shared_ptr<Texture> emissionTexture);

    const std::shared_ptr<Light> getLight() const;
    void setLight(const std::shared_ptr<Light> light);

    const std::shared_ptr<Material> getMaterial() const;
    void setMaterial(const std::shared_ptr<Material> material);

    void draw(const std::unique_ptr<GraphicsAPI>& graphics) override;

private:
    std::shared_ptr<Model> mModel;
    std::shared_ptr<Texture> mTexture;
    std::shared_ptr<Texture> mNormalTexture;
    std::shared_ptr<Texture> mMetallicTexture;
    std::shared_ptr<Texture> mEmissionTexture;
    std::shared_ptr<Light> mLight;
    std::shared_ptr<Material> mMaterial;
};

