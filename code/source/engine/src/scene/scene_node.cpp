
#include <iostream>
#include <tangram/engine/scene/scene_node.hpp>

namespace tangram::engine
{
    SceneNode::SceneNode()
    {
    }

    void SceneNode::addChild(std::shared_ptr<SceneNode> child)
    {
        mChilds.push_back(child);
        child->mParent = this;
    }

    const std::vector<std::shared_ptr<SceneNode>>& SceneNode::children() const
    {
        return mChilds;
    }

    SceneNode* SceneNode::parent() const
    {
        return mParent;
    }

    std::shared_ptr<ShaderProgram> SceneNode::getShader() const
    {
        return mShader;
    }

    void SceneNode::setShader(std::shared_ptr<ShaderProgram> shader)
    {
        mShader = shader;
    }

    std::shared_ptr<ShaderProgram> SceneNode::getHierarchyShader() const
    {
        if (mShader != nullptr)
        {
            return mShader;
        }
        SceneNode* parent = mParent;
        while (parent != nullptr)
        {
            if (parent->mShader != nullptr)
            {
                return parent->mShader;
            }
            parent = parent->mParent;
        }
        std::cerr << "No valid shader to use" << std::endl;
        std::exit(1);
        return nullptr;
    }

    Transform SceneNode::getHierarchyTransform() const
    {
        glm::vec3 position = transform.position;
        glm::quat rotation = transform.rotation;
        glm::vec3 scale = transform.scale;
        SceneNode* parent = mParent;
        while (parent != nullptr)
        {
            position += parent->transform.position;
            rotation = parent->transform.rotation * rotation;
            scale *= parent->transform.scale;
            parent = parent->mParent;
        }
        return Transform{.position = position, .scale = scale, .rotation = rotation};
    };

    void SceneNode::update()
    {
        for (auto& child : mChilds)
        {
            child->update();
        }
    }

    void SceneNode::draw(const std::unique_ptr<GraphicsAPI>& graphics)
    {
        for (auto& child : mChilds)
        {
            child->draw(graphics);
        }
    }
} // namespace tangram::engine
