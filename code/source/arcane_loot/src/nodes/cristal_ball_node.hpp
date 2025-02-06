#pragma once

#include "tangram/engine/rendering/model.hpp"

#include <tangram/engine/api.hpp>
#include <tangram/engine/rendering/light.hpp>
#include <tangram/engine/rendering/model.hpp>
#include <tangram/engine/scene/scene_node.hpp>

using namespace tangram::engine;

class CristalBallNode : public SceneNode
{
public:
    // cel + shilhouette + rim + no texture
    CristalBallNode(std::shared_ptr<Model> model, std::shared_ptr<Light> light);

    const std::shared_ptr<Model> getModel() const;
    void setModel(const std::shared_ptr<Model> model);

    const std::shared_ptr<Light> getLight() const;
    void setLight(const std::shared_ptr<Light> light);

    const glm::vec3& getColor() const;
    void setColor(const glm::vec3& color);

    const glm::vec3& getRimColor() const;
    void setRimColor(const glm::vec3& rimColor);

    const glm::vec3& getShilhouetteColor() const;
    void setShilhouetteColor(const glm::vec3& shilhouetteColor);

    const glm::vec3& getViewPos() const;
    void setViewPos(const glm::vec3& viewPos);

    void draw(const std::unique_ptr<GraphicsAPI>& graphics) override;

private:
    std::shared_ptr<Model> mModel;
    std::shared_ptr<Light> mLight;
    glm::vec3 mViewPos;

    glm::vec3 mRimColor = Color::fromRGB(3, 255, 255).rgb();
    glm::vec3 mShilhouetteColor = Color::fromRGB(3, 17, 36).rgb();
    glm::vec3 mColor = Color::fromRGB(0, 142, 250).rgb();
};
