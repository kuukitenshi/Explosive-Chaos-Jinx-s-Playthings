#include "glfw_window.hpp"

#include <tangram/engine/window/window.hpp>

namespace tangram::engine
{
    std::unique_ptr<Window> Window::create(int width, int height, const std::string& title)
    {
        return std::make_unique<GlfwWindow>(width, height, title);
    }

    std::unique_ptr<GraphicsAPI>& Window::graphicsApi()
    {
        return mGraphicsApi;
    }
} // namespace tangram::engine
