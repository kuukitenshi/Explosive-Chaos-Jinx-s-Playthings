#pragma once

#include <memory>
#include <tangram/engine/rendering/graphics_api.hpp>
#include <tangram/engine/scene/transform.hpp>
#include <vector>

namespace tangram::engine
{
    class SceneNode
    {
    public:
        Transform transform{};

        SceneNode();

        void addChild(std::shared_ptr<SceneNode> child);

        const std::vector<std::shared_ptr<SceneNode>>& children() const;

        SceneNode* parent() const;

        std::shared_ptr<ShaderProgram> getShader() const;

        std::shared_ptr<ShaderProgram> getHierarchyShader() const;

        Transform getHierarchyTransform() const;

        void setShader(std::shared_ptr<ShaderProgram> shader);

        virtual void update();

        virtual void draw(const std::unique_ptr<GraphicsAPI>& graphics);

    private:
        SceneNode* mParent = nullptr;
        std::vector<std::shared_ptr<SceneNode>> mChilds;
        std::shared_ptr<ShaderProgram> mShader;
    };
} // namespace tangram::engine
