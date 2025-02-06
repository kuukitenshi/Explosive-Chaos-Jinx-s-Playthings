#include "skybox_node.hpp"

using namespace tangram::engine;

SkyBoxNode::SkyBoxNode(const std::unique_ptr<GraphicsAPI>& graphics, std::array<Image, 6> images,
                       std::shared_ptr<Camera> camera)
    : mImages(images)
    , mCamera(camera)
{
    auto cubeDesc = std::make_shared<CubeMapDescription>(images);
    mTexture = graphics->createTexture(TextureType::CubeMap, cubeDesc);

    float SkyBoxNodeVertices[] = {-1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,
                                  -1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f};
    uint32_t SkyBoxNodeIndices[] = {// Right
                                    1, 2, 6, 6, 5, 1,
                                    // Left
                                    0, 4, 7, 7, 3, 0,
                                    // Top
                                    4, 5, 6, 6, 7, 4,
                                    // Bottom
                                    0, 3, 2, 2, 1, 0,
                                    // Back
                                    0, 1, 5, 5, 4, 0,
                                    // Front
                                    3, 7, 6, 6, 2, 3};

    std::shared_ptr<VertexBuffer> vertexBuffer =
        graphics->createVertexBuffer(sizeof(SkyBoxNodeVertices), SkyBoxNodeVertices); //VBO
    mIBO = graphics->createIndexBuffer(sizeof(SkyBoxNodeIndices) / sizeof(uint32_t), SkyBoxNodeIndices);

    VertexLayout layout{};
    layout.push<float>(3);

    VertexArrayDescription desc{
        .vertexBufers = {vertexBuffer},
        .layouts = {layout},
        .indexBuffer = mIBO,
    };
    mVAO = graphics->createVertexArray(desc);
}

std::array<Image, 6> SkyBoxNode::getImages() const
{
    return mImages;
}

void SkyBoxNode::setImages(const std::array<Image, 6>& images)
{
    mImages = images;
}

std::shared_ptr<Texture> SkyBoxNode::getTexture() const
{
    return mTexture;
}

void SkyBoxNode::draw(const std::unique_ptr<GraphicsAPI>& graphics)
{
    graphics->depthFunc(DepthFunc::LEQUAL);
    graphics->setCullFace(CullFace::FRONT);

    graphics->bindVertexArray(mVAO);
    graphics->bindTexture(mTexture, 0);

    std::shared_ptr<ShaderProgram> shaderProgram = getHierarchyShader();
    graphics->useShaderProgram(shaderProgram);

    graphics->setUniform1i(shaderProgram, "u_skybox", 0);
    glm::mat4 projection = mCamera->projection;
    graphics->setUniformMat4(shaderProgram, "projection", projection);
    glm::mat4 view = mCamera->viewMatrix();
    view = glm::mat4(glm::mat3(view));
    graphics->setUniformMat4(shaderProgram, "view", view);

    graphics->drawElements(mIBO);

    graphics->depthFunc(DepthFunc::LESS);
    graphics->setCullFace(CullFace::BACK);

    SceneNode::draw(graphics);
}
