#include "glfw_window.hpp"

#include <GLFW/glfw3.h>
#include <cstdlib>
#include <glad/glad.h>
#include <iostream>
#include <tangram/engine/input/input.hpp>
#include <tangram/engine/rendering/graphics_api.hpp>

namespace tangram::engine
{
    static int mouseButtonToGLFW(MouseButton button)
    {
        switch (button)
        {
        case MouseButton::LEFT:
            return GLFW_MOUSE_BUTTON_LEFT;
        }
        std::cerr << "Invalid MouseButton!" << std::endl;
        std::abort();
    }

    static int keyboardKeyToGLFW(KeyboardKey key)
    {
        switch (key)
        {
        case KeyboardKey::LEFT:
            return GLFW_KEY_LEFT;
        case KeyboardKey::RIGHT:
            return GLFW_KEY_RIGHT;
        case KeyboardKey::C:
            return GLFW_KEY_C;
        case KeyboardKey::P:
            return GLFW_KEY_P;
        default:
            return -1;
        }
    }

    GlfwWindow::GlfwWindow(int width, int height, const std::string& title)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, 4);
#ifdef DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif
        mWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        setupCallbacks();
        glfwMakeContextCurrent(mWindow);
        gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        mGraphicsApi = GraphicsAPI::create();
#ifdef DEBUG
        mGraphicsApi->enableDebugging();
#endif
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_MULTISAMPLE);
        glDepthFunc(GL_LEQUAL);
        glDepthMask(GL_TRUE);
        glDepthRange(0.0, 1.0);
        glClearDepth(1.0);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
    }

    GlfwWindow::~GlfwWindow()
    {
        glfwDestroyWindow(mWindow);
    }

    void GlfwWindow::setTitle(const std::string& title) const
    {
        glfwSetWindowTitle(mWindow, title.c_str());
    }

    bool GlfwWindow::shouldClose() const
    {
        return glfwWindowShouldClose(mWindow);
    }

    glm::ivec2 GlfwWindow::getSize() const
    {
        int width, height;
        glfwGetWindowSize(mWindow, &width, &height);
        return {width, height};
    }

    void GlfwWindow::swapBuffers() const
    {
        glfwSwapBuffers(mWindow);
    }

    void GlfwWindow::pollEvents()
    {
        mScrollDelta = glm::vec2{0.0f};
        glfwPollEvents();
    }

    glm::vec2 GlfwWindow::mousePos() const
    {
        double x, y;
        glfwGetCursorPos(mWindow, &x, &y);
        return {static_cast<float>(x), static_cast<float>(y)};
    }

    bool GlfwWindow::isMouseButtonDown(MouseButton button) const
    {
        return glfwGetMouseButton(mWindow, mouseButtonToGLFW(button)) == GLFW_PRESS;
    }

    bool GlfwWindow::isKeyDown(KeyboardKey key) const
    {
        int glfwKey = keyboardKeyToGLFW(key);
        return glfwGetKey(mWindow, glfwKey) == GLFW_PRESS;
    }

    bool GlfwWindow::isKeyReleased(KeyboardKey key) const
    {
        int glfwKey = keyboardKeyToGLFW(key);
        return glfwGetKey(mWindow, glfwKey) == GLFW_RELEASE;
    }

    glm::vec2 GlfwWindow::scrollDelta() const
    {
        return mScrollDelta;
    }

    float GlfwWindow::time() const
    {
        return static_cast<float>(glfwGetTime());
    }

    void GlfwWindow::setupCallbacks()
    {
        static GlfwWindow* thisWindow = this;
        glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double x, double y) {
            thisWindow->mScrollDelta = glm::vec2{static_cast<float>(x), static_cast<float>(y)};
        });
    }
} // namespace tangram::engine
