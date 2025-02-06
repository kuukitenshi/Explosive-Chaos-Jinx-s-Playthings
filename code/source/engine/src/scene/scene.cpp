
#include <glm/gtc/type_ptr.hpp>
#include <tangram/engine/scene/scene.hpp>

namespace tangram::engine
{
    Scene::Scene(const std::unique_ptr<GraphicsAPI>& graphics)
    {
        mCamera = std::make_shared<Camera>();
        mCameraBuffer = graphics->createUniformBuffer(sizeof(glm::mat4) * 2, nullptr);
    }

    SceneNode& Scene::getRoot()
    {
        return mRoot;
    }

    std::shared_ptr<Camera> Scene::getCamera()
    {
        return mCamera;
    }

    void Scene::setCamera(std::shared_ptr<Camera> camera)
    {
        mCamera = camera;
    }

    void Scene::updateCameraBuffer(const std::unique_ptr<GraphicsAPI>& graphics) const
    {
        graphics->uniformBufferSubData(mCameraBuffer, 0, sizeof(glm::mat4), glm::value_ptr(mCamera->viewMatrix()));
        graphics->uniformBufferSubData(mCameraBuffer, sizeof(glm::mat4), sizeof(glm::mat4),
                                       glm::value_ptr(mCamera->projection));
    }

    void Scene::update()
    {
        mRoot.update();
    }

    void Scene::draw(const std::unique_ptr<GraphicsAPI>& graphics)
    {
        mRoot.draw(graphics);
    }

} // namespace tangram::engine
