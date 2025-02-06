#include "object_node.hpp"

using namespace tangram::engine;

ObjectNode::ObjectNode(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, std::shared_ptr<Light> light,
                       std::shared_ptr<Material> material)
    : mModel(model)
    , mTexture(texture)
    , mLight(light)
    , mMaterial(material)
{
}

const std::shared_ptr<Model> ObjectNode::getModel() const
{
    return mModel;
}

void ObjectNode::setModel(const std::shared_ptr<Model> model)
{
    mModel = model;
}

const std::shared_ptr<Texture> ObjectNode::getTexture() const
{
    return mTexture;
}

void ObjectNode::setTexture(const std::shared_ptr<Texture> texture)
{
    mTexture = texture;
}

const std::shared_ptr<Light> ObjectNode::getLight() const
{
    return mLight;
}

void ObjectNode::setLight(const std::shared_ptr<Light> light)
{
    mLight = light;
}

const std::shared_ptr<Material> ObjectNode::getMaterial() const
{
    return mMaterial;
}

void ObjectNode::setMaterial(const std::shared_ptr<Material> material)
{
    mMaterial = material;
}

void ObjectNode::draw(const std::unique_ptr<GraphicsAPI>& graphics)
{
    std::shared_ptr<ShaderProgram> shaderProgram = getHierarchyShader();
    Transform fullTransform = getHierarchyTransform();

    graphics->bindTexture(mTexture, 0);

    graphics->useShaderProgram(shaderProgram);
    graphics->setUniformMat4(shaderProgram, "u_model", fullTransform.matrix());

    graphics->setUniform1i(shaderProgram, "u_texture", 0);

    graphics->setUniform3f(shaderProgram, "u_light_dir", mLight->direction);
    graphics->setUniform3f(shaderProgram, "u_light_color", mLight->color);
    graphics->setUniform1f(shaderProgram, "u_ka", mLight->ka);
    graphics->setUniform1f(shaderProgram, "u_kd", mLight->kd);
    graphics->setUniform1f(shaderProgram, "u_ks", mLight->ks);
    graphics->setUniform1f(shaderProgram, "u_shininess", mLight->shininess);

    graphics->setUniform3f(shaderProgram, "u_material.ambient", mMaterial->ambient);
    graphics->setUniform3f(shaderProgram, "u_material.diffuse", mMaterial->diffuse);
    graphics->setUniform3f(shaderProgram, "u_material.specular", mMaterial->specular);
    graphics->setUniform1f(shaderProgram, "u_material.shininess", mMaterial->shininess);

    mModel->draw(graphics);
    SceneNode::draw(graphics);
}
