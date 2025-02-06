#pragma once

#include <memory>
#include <tangram/engine/rendering/camera.hpp>
#include <tangram/engine/rendering/graphics_api.hpp>
#include <tangram/engine/scene/scene_node.hpp>
#include <tangram/engine/scene/transform.hpp>

namespace tangram::engine
{
    class Scene
    {
    public:
        Scene(const std::unique_ptr<GraphicsAPI>& graphics);

        SceneNode& getRoot();

        std::shared_ptr<Camera> getCamera();
        void setCamera(std::shared_ptr<Camera> camera);

        void updateCameraBuffer(const std::unique_ptr<GraphicsAPI>& graphics) const;

        void update();

        void draw(const std::unique_ptr<GraphicsAPI>& graphics);

    private:
        SceneNode mRoot;
        std::shared_ptr<Camera> mCamera;
        std::shared_ptr<UniformBuffer> mCameraBuffer;
    };
} // namespace tangram::engine
