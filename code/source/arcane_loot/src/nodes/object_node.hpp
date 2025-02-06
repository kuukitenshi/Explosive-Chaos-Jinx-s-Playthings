#pragma once

#include "tangram/engine/rendering/model.hpp"

#include <tangram/engine/api.hpp>
#include <tangram/engine/rendering/light.hpp>
#include <tangram/engine/rendering/material.hpp>
#include <tangram/engine/rendering/model.hpp>
#include <tangram/engine/scene/scene_node.hpp>

using namespace tangram::engine;

class ObjectNode : public SceneNode
{
public:
    // Blinn-Phong + texture
    ObjectNode(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, std::shared_ptr<Light> light,
               std::shared_ptr<Material> material);

    const std::shared_ptr<Model> getModel() const;
    void setModel(const std::shared_ptr<Model> model);

    const std::shared_ptr<Texture> getTexture() const;
    void setTexture(const std::shared_ptr<Texture> texture);

    const std::shared_ptr<Light> getLight() const;
    void setLight(const std::shared_ptr<Light> light);

    const std::shared_ptr<Material> getMaterial() const;
    void setMaterial(const std::shared_ptr<Material> material);

    void draw(const std::unique_ptr<GraphicsAPI>& graphics) override;

private:
    std::shared_ptr<Model> mModel;
    std::shared_ptr<Texture> mTexture;
    std::shared_ptr<Light> mLight;
    std::shared_ptr<Material> mMaterial;
};
