#pragma once

#include <GLFW/glfw3.h>
#include <tangram/engine/rendering/graphics_api.hpp>
#include <tangram/engine/window/window.hpp>

namespace tangram::engine
{
    class GlfwWindow : public Window
    {
    public:
        GlfwWindow(int width, int height, const std::string& title);

        ~GlfwWindow() override;

        void setTitle(const std::string& title) const override;

        bool shouldClose() const override;

        glm::ivec2 getSize() const override;

        void swapBuffers() const override;

        void pollEvents() override;

        glm::vec2 mousePos() const override;

        bool isMouseButtonDown(MouseButton button) const override;

        bool isKeyDown(KeyboardKey key) const override;

        bool isKeyReleased(KeyboardKey key) const override;

        glm::vec2 scrollDelta() const override;

        float time() const override;

    private:
        void setupCallbacks();
        glm::vec2 mScrollDelta;
        GLFWwindow* mWindow;
    };
} // namespace tangram::engine
