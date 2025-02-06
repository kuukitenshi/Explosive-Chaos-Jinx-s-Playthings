#include "normal_object_node.hpp"

using namespace tangram::engine;

NormalObjectNode::NormalObjectNode(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture,
                                   std::shared_ptr<Texture> normalTexture, std::shared_ptr<Texture> metallicTexture,
                                   std::shared_ptr<Light> light, std::shared_ptr<Material> material,
                                   std::shared_ptr<Texture> emissionTexture)
    : mModel(model)
    , mTexture(texture)
    , mNormalTexture(normalTexture)
    , mMetallicTexture(metallicTexture)
    , mLight(light)
    , mMaterial(material)
    , mEmissionTexture(emissionTexture)
{
}

const std::shared_ptr<Model> NormalObjectNode::getModel() const
{
    return mModel;
}

void NormalObjectNode::setModel(const std::shared_ptr<Model> model)
{
    mModel = model;
}

const std::shared_ptr<Texture> NormalObjectNode::getTexture() const
{
    return mTexture;
}

void NormalObjectNode::setTexture(const std::shared_ptr<Texture> texture)
{
    mTexture = texture;
}

const std::shared_ptr<Texture> NormalObjectNode::getNormalTexture() const
{
    return mNormalTexture;
}

void NormalObjectNode::setNormalTexture(const std::shared_ptr<Texture> normalTexture)
{
    mNormalTexture = normalTexture;
}

const std::shared_ptr<Texture> NormalObjectNode::getMetallicTexture() const
{
    return mMetallicTexture;
}

void NormalObjectNode::setMetallicTexture(const std::shared_ptr<Texture> metallicTexture)
{
    mMetallicTexture = metallicTexture;
}

const std::shared_ptr<Texture> NormalObjectNode::getEmissionTexture() const
{
    return mEmissionTexture;
}

void NormalObjectNode::setEmissionTexture(const std::shared_ptr<Texture> emissionTexture)
{
    mEmissionTexture = emissionTexture;
}

const std::shared_ptr<Light> NormalObjectNode::getLight() const
{
    return mLight;
}

void NormalObjectNode::setLight(const std::shared_ptr<Light> light)
{
    mLight = light;
}

const std::shared_ptr<Material> NormalObjectNode::getMaterial() const
{
    return mMaterial;
}

void NormalObjectNode::setMaterial(const std::shared_ptr<Material> material)
{
    mMaterial = material;
}

void NormalObjectNode::draw(const std::unique_ptr<GraphicsAPI>& graphics)
{
    std::shared_ptr<ShaderProgram> shaderProgram = getHierarchyShader();
    Transform fullTransform = getHierarchyTransform();

    graphics->bindTexture(mTexture, 0);
    graphics->bindTexture(mNormalTexture, 1);
    graphics->bindTexture(mMetallicTexture, 2);

    graphics->useShaderProgram(shaderProgram);
    graphics->setUniformMat4(shaderProgram, "u_model", fullTransform.matrix());

    graphics->setUniform1i(shaderProgram, "u_texture", 0);
    graphics->setUniform1i(shaderProgram, "u_normal_texture", 1);
    graphics->setUniform1i(shaderProgram, "u_metalic_texture", 2);

    if (mEmissionTexture)
    {
        graphics->bindTexture(mEmissionTexture, 3);
        graphics->setUniform1i(shaderProgram, "u_emission_texture", 3);
        graphics->setUniform1i(shaderProgram, "u_has_emissive", 1); // true
    }
    else
    {
        graphics->setUniform1i(shaderProgram, "u_has_emissive", 0);
    }

    graphics->setUniform3f(shaderProgram, "u_light_dir", mLight->direction);
    graphics->setUniform3f(shaderProgram, "u_light_color", mLight->color);
    graphics->setUniform1f(shaderProgram, "u_ka", mLight->ka);
    graphics->setUniform1f(shaderProgram, "u_kd", mLight->kd);
    graphics->setUniform1f(shaderProgram, "u_ks", mLight->ks);
    graphics->setUniform1f(shaderProgram, "u_shininess", mLight->shininess);

    graphics->setUniform3f(shaderProgram, "u_material.ambient", mMaterial->ambient);
    graphics->setUniform3f(shaderProgram, "u_material.diffuse", mMaterial->diffuse);
    graphics->setUniform3f(shaderProgram, "u_material.specular", mMaterial->specular);
    graphics->setUniform1f(shaderProgram, "u_material.emissive", mMaterial->emissive);
    graphics->setUniform1f(shaderProgram, "u_material.shininess", mMaterial->shininess);

    mModel->draw(graphics);
    SceneNode::draw(graphics);
}