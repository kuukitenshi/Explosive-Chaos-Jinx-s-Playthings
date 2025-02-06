#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <tangram/engine/input/input.hpp>
#include <tangram/engine/rendering/graphics_api.hpp>

namespace tangram::engine
{
    class Window
    {
    public:
        virtual ~Window() = default;

        static std::unique_ptr<Window> create(int width, int height, const std::string& title);

        virtual void setTitle(const std::string& title) const = 0;

        virtual bool shouldClose() const = 0;

        virtual glm::ivec2 getSize() const = 0;

        virtual void swapBuffers() const = 0;

        virtual void pollEvents() = 0;

        virtual glm::vec2 mousePos() const = 0;

        virtual bool isMouseButtonDown(MouseButton button) const = 0;

        virtual bool isKeyDown(KeyboardKey key) const = 0;

        virtual bool isKeyReleased(KeyboardKey key) const = 0;

        virtual glm::vec2 scrollDelta() const = 0;

        virtual float time() const = 0;

        std::unique_ptr<GraphicsAPI>& graphicsApi();

    protected:
        std::unique_ptr<GraphicsAPI> mGraphicsApi;
    };
} // namespace tangram::engine
