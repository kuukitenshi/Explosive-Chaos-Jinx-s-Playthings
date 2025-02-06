#include "nodes/cristal_ball_node.hpp"
#include "nodes/object_node.hpp"
#include "nodes/skybox_node.hpp"
#include "procedural_texture.hpp"
#include "scene.hpp"

#include <chrono>
#include <fstream>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <sstream>
#include <tangram/engine/api.hpp>

using namespace tangram::engine;
using namespace std::chrono;

std::string readTextfile(const std::string& filepath)
{
    std::ifstream file(filepath);
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

void updateCameraViewport(std::shared_ptr<Camera> camera, glm::ivec2 viewport)
{
    float aspect = static_cast<float>(viewport.x) / static_cast<float>(viewport.y);
    float fov;
    if (aspect >= 1)
    {
        fov = glm::radians(45.0f);
    }
    else
    {
        fov = std::min(glm::radians(45.0f) / aspect, 2.5f);
    }
    camera->projection = glm::perspective(fov, aspect, 0.1f, 1000.0f);
}

std::array<std::shared_ptr<ShaderProgram>, 5> loadShaders(const std::unique_ptr<GraphicsAPI>& graphics)
{
    // blinn phong
    std::string vertexSource = readTextfile("assets/shaders/blinnphong.vert");
    std::string fragmentSource = readTextfile("assets/shaders/blinnphong.frag");
    std::shared_ptr<Shader> vertex = graphics->createShader(ShaderType::VERTEX_SHADER, vertexSource);
    std::shared_ptr<Shader> fragment = graphics->createShader(ShaderType::FRAGMENT_SHADER, fragmentSource);
    std::shared_ptr<ShaderProgram> programBlinn =
        graphics->createShaderProgram({.vertex = vertex, .fragment = fragment});
    // blinn phong + normal mapping
    std::string vertexBlinnMapSource = readTextfile("assets/shaders/blinn_mapping.vert");
    std::string fragmentBlinnMapSource = readTextfile("assets/shaders/blinn_mapping.frag");
    std::shared_ptr<Shader> vertexBlinnMap = graphics->createShader(ShaderType::VERTEX_SHADER, vertexBlinnMapSource);
    std::shared_ptr<Shader> fragmentBlinnMap =
        graphics->createShader(ShaderType::FRAGMENT_SHADER, fragmentBlinnMapSource);
    std::shared_ptr<ShaderProgram> programBlinnMapping =
        graphics->createShaderProgram({.vertex = vertexBlinnMap, .fragment = fragmentBlinnMap});
    // cel shading
    std::string vertexCelSource = readTextfile("assets/shaders/cel.vert");
    std::string fragmentCelSource = readTextfile("assets/shaders/cel.frag");
    std::shared_ptr<Shader> vertexCel = graphics->createShader(ShaderType::VERTEX_SHADER, vertexCelSource);
    std::shared_ptr<Shader> fragmentCel = graphics->createShader(ShaderType::FRAGMENT_SHADER, fragmentCelSource);
    std::shared_ptr<ShaderProgram> programCel =
        graphics->createShaderProgram({.vertex = vertexCel, .fragment = fragmentCel});
    // silhouette + rim
    std::string vertexSilhSource = readTextfile("assets/shaders/shilhouette.vert");
    std::string fragmentSilhSource = readTextfile("assets/shaders/shilhouette.frag");
    std::shared_ptr<Shader> vertexSilhouette = graphics->createShader(ShaderType::VERTEX_SHADER, vertexSilhSource);
    std::shared_ptr<Shader> fragmentSilhouette =
        graphics->createShader(ShaderType::FRAGMENT_SHADER, fragmentSilhSource);
    std::shared_ptr<ShaderProgram> programSilhouette =
        graphics->createShaderProgram({.vertex = vertexSilhouette, .fragment = fragmentSilhouette});
    // skybox
    std::string vertexSkyboxSource = readTextfile("assets/shaders/skybox.vert");
    std::string fragmentSkyboxSource = readTextfile("assets/shaders/skybox.frag");
    std::shared_ptr<Shader> vertexSkybox = graphics->createShader(ShaderType::VERTEX_SHADER, vertexSkyboxSource);
    std::shared_ptr<Shader> fragmentSkybox = graphics->createShader(ShaderType::FRAGMENT_SHADER, fragmentSkyboxSource);
    std::shared_ptr<ShaderProgram> programSkybox =
        graphics->createShaderProgram({.vertex = vertexSkybox, .fragment = fragmentSkybox});

    return {programBlinn, programBlinnMapping, programCel, programSilhouette, programSkybox};
}

void genProceduralTextures()
{
    genMarbleTexture();
    genWoodTexture();
    genBrickTexture();
}

int main()
{
    std::unique_ptr<Window> window = Window::create(800, 800, "Arcane Loot");
    auto& graphics = window->graphicsApi();
    graphics->clearColor(Color::fromRGB(126, 193, 221).rgba());
    // ------------------------------- Camera -----------------------------------------------
    std::shared_ptr<OrbitCamera> camera = std::make_shared<OrbitCamera>();
    camera->eye = glm::vec3(-0.535867, 1.413376, 3.156770);
    camera->up = glm::vec3(0.039555, 0.914473, -0.402709);
    // ------------------------- gen procedural textures -------------------------------------
    genProceduralTextures();
    // ------------------------------- Load shaders ------------------------------------------
    auto shaders = loadShaders(graphics);
    std::shared_ptr<ShaderProgram> programBlinn = shaders[0];
    std::shared_ptr<ShaderProgram> programBlinnMapping = shaders[1];
    std::shared_ptr<ShaderProgram> programCel = shaders[2];
    std::shared_ptr<ShaderProgram> programSilhouette = shaders[3];
    std::shared_ptr<ShaderProgram> programSkybox = shaders[4];
    // ------------------------------ Setup scene -------------------------------------------
    Scene scene{graphics};
    scene.setCamera(camera);
    scene.updateCameraBuffer(graphics);
    // light
    std::shared_ptr<Light> light = std::make_shared<Light>(Light{.direction = glm::vec3(-1.0f, -1.0f, -1.0f),
                                                                 .color = glm::vec3(1.0f),
                                                                 .ka = 0.5f,
                                                                 .kd = 1.0f,
                                                                 .ks = 1.0f,
                                                                 .shininess = 32.0f});
    // ------------------------------ Load models -------------------------------------------
    auto skyboxNode = loadSkyBox(graphics, programSkybox, camera);
    auto monkeyNode = loadMonkey(graphics, light, programBlinnMapping);
    auto cristalBallNode = loadCristalBall(graphics, light, programCel, programSilhouette, camera);
    auto floorNode = loadFloor(graphics, light, programBlinn);
    auto baseNode = loadBase(graphics, light, programBlinn);
    auto bazukaNode = loadBazuka(graphics, light, programBlinnMapping);
    auto pistolNode = loadPistol(graphics, light, programBlinnMapping);
    auto bulletNode = loadBullet(graphics, light, programBlinnMapping);
    auto shimmerNode = loadShimmer(graphics, light, programBlinn);
    auto granadeNode = loadGranade(graphics, light, programBlinnMapping);
    // ------------------------------- Add nodes to scene ----------------------------------
    SceneNode& root = scene.getRoot();
    root.addChild(skyboxNode);
    root.addChild(monkeyNode);
    root.addChild(cristalBallNode);
    root.addChild(floorNode);
    root.addChild(baseNode);
    root.addChild(bazukaNode);
    root.addChild(pistolNode);
    root.addChild(bulletNode);
    root.addChild(shimmerNode);
    root.addChild(granadeNode);
    // ----------------------------------- Main loop -----------------------------------------
    milliseconds lastTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    milliseconds now = lastTime;
    glm::vec2 prevMousePos{0.0f};
    glm::vec2 currMousePos{0.0f};
    glm::ivec2 prevViewport{0};
    bool dirtyCamera = false;
    const float camSpeed = 20.0f;
    const float zoomSpeed = 10.0f;
    while (!window->shouldClose())
    {
        window->pollEvents();
        glm::ivec2 size = window->getSize();
        graphics->setViewport(0, 0, static_cast<size_t>(size.x), static_cast<size_t>(size.y));
        lastTime = now;
        now = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
        float delta = (now - lastTime).count() / 1000.0f;
        prevMousePos = currMousePos;
        currMousePos = window->mousePos();
        glm::vec2 scroll = window->scrollDelta();
        if (prevViewport != size)
        {
            updateCameraViewport(camera, size);
            dirtyCamera = true;
        }
        if (fabs(scroll.y) > 0)
        {
            float zoomLevel = scroll.y * delta * zoomSpeed;
            camera->zoom(zoomLevel);
            dirtyCamera = true;
        }
        if (window->isMouseButtonDown(MouseButton::LEFT))
        {
            glm::vec2 mov = currMousePos - prevMousePos;
            if (fabs(mov.x) > 0 || fabs(mov.y) > 0)
            {
                mov *= delta * camSpeed;
                camera->move(mov);
                dirtyCamera = true;
            }
        }
        if (dirtyCamera)
        {
            scene.updateCameraBuffer(graphics);
        }
        // update view pos ball
        std::static_pointer_cast<CristalBallNode>(cristalBallNode)->setViewPos(camera->eye);
        std::shared_ptr<CristalBallNode> cristalBallSilhouetteNode =
            std::static_pointer_cast<CristalBallNode>(cristalBallNode->children()[0]);
        cristalBallSilhouetteNode->setViewPos(camera->eye);

        // rotate ball
        float angle = glm::radians(window->time() * 50.0f);
        cristalBallNode->transform.rotation = glm::angleAxis(angle, glm::vec3{0.0f, 1.0f, 0.0f});

        graphics->clearBackground();
        scene.draw(graphics);
        window->swapBuffers();
    }
    return 0;
}
