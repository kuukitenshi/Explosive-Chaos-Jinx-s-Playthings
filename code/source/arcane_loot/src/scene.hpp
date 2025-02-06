#pragma once

#include "nodes/cristal_ball_node.hpp"
#include "nodes/normal_object_node.hpp"
#include "nodes/object_node.hpp"
#include "nodes/skybox_node.hpp"

#include <memory>
#include <tangram/engine/api.hpp>

std::shared_ptr<SceneNode> loadMonkey(const std::unique_ptr<GraphicsAPI>& graphics, const std::shared_ptr<Light> light,
                                      const std::shared_ptr<ShaderProgram> blinnShader);

std::shared_ptr<SceneNode> loadCristalBall(const std::unique_ptr<GraphicsAPI>& graphics,
                                           const std::shared_ptr<Light> light,
                                           const std::shared_ptr<ShaderProgram> celShader,
                                           const std::shared_ptr<ShaderProgram> silhouetteShader,
                                           const std::shared_ptr<Camera> camera);

std::shared_ptr<SceneNode> loadFloor(const std::unique_ptr<GraphicsAPI>& graphics, const std::shared_ptr<Light> light,
                                     const std::shared_ptr<ShaderProgram> blinnShader);

std::shared_ptr<SceneNode> loadBase(const std::unique_ptr<GraphicsAPI>& graphics, const std::shared_ptr<Light> light,
                                    const std::shared_ptr<ShaderProgram> blinnShader);

std::shared_ptr<SceneNode> loadBullet(const std::unique_ptr<GraphicsAPI>& graphics, const std::shared_ptr<Light> light,
                                      const std::shared_ptr<ShaderProgram> blinnShader);

std::shared_ptr<SceneNode> loadGranade(const std::unique_ptr<GraphicsAPI>& graphics, const std::shared_ptr<Light> light,
                                       const std::shared_ptr<ShaderProgram> blinnShader);

std::shared_ptr<SceneNode> loadBazuka(const std::unique_ptr<GraphicsAPI>& graphics, const std::shared_ptr<Light> light,
                                      const std::shared_ptr<ShaderProgram> blinnShader);

std::shared_ptr<SceneNode> loadPistol(const std::unique_ptr<GraphicsAPI>& graphics, const std::shared_ptr<Light> light,
                                      const std::shared_ptr<ShaderProgram> blinnShader);

std::shared_ptr<SceneNode> loadShimmer(const std::unique_ptr<GraphicsAPI>& graphics, const std::shared_ptr<Light> light,
                                       const std::shared_ptr<ShaderProgram> blinnShader);

std::shared_ptr<SceneNode> loadSkyBox(const std::unique_ptr<GraphicsAPI>& graphics,
                                      const std::shared_ptr<ShaderProgram> skyboxShader,
                                      const std::shared_ptr<Camera> camera);
