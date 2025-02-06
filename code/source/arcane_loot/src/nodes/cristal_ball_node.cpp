
#include "cristal_ball_node.hpp"

#include <tangram/engine/rendering/graphics_api.hpp>

using namespace tangram::engine;

CristalBallNode::CristalBallNode(std::shared_ptr<Model> model, std::shared_ptr<Light> light)
    : mModel(model)
    , mLight(light)
{
}

const std::shared_ptr<Model> CristalBallNode::getModel() const
{
    return mModel;
}

void CristalBallNode::setModel(const std::shared_ptr<Model> model)
{
    mModel = model;
}

const std::shared_ptr<Light> CristalBallNode::getLight() const
{
    return mLight;
}

void CristalBallNode::setLight(const std::shared_ptr<Light> light)
{
    mLight = light;
}

const glm::vec3& CristalBallNode::getColor() const
{
    return mColor;
}

void CristalBallNode::setColor(const glm::vec3& color)
{
    mColor = color;
}

const glm::vec3& CristalBallNode::getRimColor() const
{
    return mRimColor;
}

void CristalBallNode::setRimColor(const glm::vec3& rimColor)
{
    mRimColor = rimColor;
}

const glm::vec3& CristalBallNode::getShilhouetteColor() const
{
    return mShilhouetteColor;
}

void CristalBallNode::setShilhouetteColor(const glm::vec3& shilhouetteColor)
{
    mShilhouetteColor = shilhouetteColor;
}

const glm::vec3& CristalBallNode::getViewPos() const
{
    return mViewPos;
}

void CristalBallNode::setViewPos(const glm::vec3& viewPos)
{
    mViewPos = viewPos;
}

void CristalBallNode::draw(const std::unique_ptr<GraphicsAPI>& graphics)
{
    std::shared_ptr<ShaderProgram> shaderProgram = getHierarchyShader();
    Transform fullTransform = getHierarchyTransform();

    graphics->useShaderProgram(shaderProgram);
    graphics->setUniformMat4(shaderProgram, "u_model", fullTransform.matrix());
    graphics->setUniform3f(shaderProgram, "u_objectColor", mColor);
    graphics->setUniform3f(shaderProgram, "u_lightDir", mLight->direction);
    graphics->setUniform3f(shaderProgram, "u_lightColor", mLight->color);
    graphics->setUniform3f(shaderProgram, "u_viewPos", mViewPos);
    graphics->setUniform3f(shaderProgram, "u_rimColor", mRimColor);
    graphics->setUniform3f(shaderProgram, "u_silhouetteColor", mShilhouetteColor);
    graphics->setUniform1i(shaderProgram, "u_texture", 0);

    mModel->draw(graphics);
    graphics->setCullFace(CullFace::FRONT);
    SceneNode::draw(graphics); // draw children
    graphics->setCullFace(CullFace::BACK);
}
