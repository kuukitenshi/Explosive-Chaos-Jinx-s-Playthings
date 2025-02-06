#include "scene.hpp"

using namespace tangram::engine;

std::shared_ptr<Texture> load2DTexture(const std::unique_ptr<GraphicsAPI>& graphics, const std::string& filepath)
{
    auto descImg = std::make_shared<Texture2DDescription>(Image{filepath});
    return graphics->createTexture(TextureType::Texture2D, descImg);
}

std::shared_ptr<SceneNode> loadMonkey(const std::unique_ptr<GraphicsAPI>& graphics, const std::shared_ptr<Light> light,
                                      const std::shared_ptr<ShaderProgram> blinnShader)
{
    // texture
    std::shared_ptr<Texture> monkeyTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/monkey/textures/default.png");
    std::shared_ptr<Texture> monkeyNormalTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/monkey/textures/normal.png");
    std::shared_ptr<Texture> monkeyMetallicTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/monkey/textures/metalic.png");
    std::shared_ptr<Texture> monkeyEmissionTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/monkey/textures/emisive.png");
    // material
    std::shared_ptr<Material> monkeyMaterial = std::make_shared<Material>(Material{
        .ambient = glm::vec3(0.2f), .diffuse = glm::vec3(1.0f), .specular = glm::vec3(2.0f),.emissive = 4.0f, .shininess = 50.0f});
    // monkey
    std::shared_ptr<Model> monkeyModel =
        std::make_shared<Model>(graphics, "assets/arcane_loot_models/monkey/monkey.obj");
    // node
    std::shared_ptr<NormalObjectNode> monkeyNode =
        std::make_shared<NormalObjectNode>(monkeyModel, monkeyTexture, monkeyNormalTexture, monkeyMetallicTexture,
                                           light, monkeyMaterial, monkeyEmissionTexture);
    monkeyNode->setMaterial(monkeyMaterial);
    monkeyNode->setShader(blinnShader);
    return monkeyNode;
}

std::shared_ptr<SceneNode> loadCristalBall(const std::unique_ptr<GraphicsAPI>& graphics,
                                           const std::shared_ptr<Light> light,
                                           const std::shared_ptr<ShaderProgram> celShader,
                                           const std::shared_ptr<ShaderProgram> silhouetteShader,
                                           const std::shared_ptr<Camera> camera)
{
    std::shared_ptr<Model> ballModel = std::make_shared<Model>(graphics, "assets/arcane_loot_models/ball/ball.obj");
    // silhouette node
    std::shared_ptr<CristalBallNode> silhouetteNode = std::make_shared<CristalBallNode>(ballModel, light);
    silhouetteNode->setShader(silhouetteShader);
    silhouetteNode->setViewPos(camera->eye);
    // cristal ball node
    std::shared_ptr<CristalBallNode> cristalBallNode = std::make_shared<CristalBallNode>(ballModel, light);
    cristalBallNode->setShader(celShader);
    cristalBallNode->setViewPos(camera->eye);
    cristalBallNode->addChild(silhouetteNode);
    // positions
    cristalBallNode->transform.position = glm::vec3(0.614268f, 0.392001f, 0.169368f);
    return cristalBallNode;
}

std::shared_ptr<SceneNode> loadFloor(const std::unique_ptr<GraphicsAPI>& graphics, const std::shared_ptr<Light> light,
                                     const std::shared_ptr<ShaderProgram> blinnShader)
{
    // texture
    std::shared_ptr<Texture> floorTexture = load2DTexture(graphics, "assets/procedural/brick.jpeg");
    // material
    std::shared_ptr<Material> floorMaterial = std::make_shared<Material>(Material{
        .ambient = glm::vec3(0.2f), .diffuse = glm::vec3(1.0f), .specular = glm::vec3(0.7f), .shininess = 8.0f});
    // floor
    std::shared_ptr<Model> floorModel = std::make_shared<Model>(graphics, "assets/arcane_loot_models/floor/floor.obj");
    // node
    std::shared_ptr<ObjectNode> floorNode =
        std::make_shared<ObjectNode>(floorModel, floorTexture, light, floorMaterial);
    floorNode->setShader(blinnShader);
    return floorNode;
}

std::shared_ptr<SceneNode> loadBase(const std::unique_ptr<GraphicsAPI>& graphics, const std::shared_ptr<Light> light,
                                    const std::shared_ptr<ShaderProgram> blinnShader)
{
    // texture
    std::shared_ptr<Texture> baseBotTexture = load2DTexture(graphics, "assets/procedural/wood.jpeg");
    std::shared_ptr<Texture> baseTopTexture = load2DTexture(graphics, "assets/procedural/marble.jpeg");
    // material
    std::shared_ptr<Material> baseBotMaterial = std::make_shared<Material>(Material{
        .ambient = glm::vec3(0.2f), .diffuse = glm::vec3(1.0f), .specular = glm::vec3(0.4f), .shininess = 10.0f});
    std::shared_ptr<Material> baseTopMaterial = std::make_shared<Material>(Material{
        .ambient = glm::vec3(0.2f), .diffuse = glm::vec3(1.0f), .specular = glm::vec3(1.0f), .shininess = 250.0f});
    // bases
    std::shared_ptr<Model> baseBotModel =
        std::make_shared<Model>(graphics, "assets/arcane_loot_models/base/base_bot.obj");
    std::shared_ptr<Model> baseTopModel =
        std::make_shared<Model>(graphics, "assets/arcane_loot_models/base/base_top.obj");
    // nodes
    std::shared_ptr<ObjectNode> baseBotNode =
        std::make_shared<ObjectNode>(baseBotModel, baseBotTexture, light, baseBotMaterial);
    std::shared_ptr<ObjectNode> baseTopNode =
        std::make_shared<ObjectNode>(baseTopModel, baseTopTexture, light, baseTopMaterial);
    baseBotNode->setShader(blinnShader);
    baseTopNode->setShader(blinnShader);
    baseBotNode->addChild(baseTopNode);
    return baseBotNode;
}

std::shared_ptr<NormalObjectNode> createNormalBulletNode(
    std::shared_ptr<Model> topModel, std::shared_ptr<Texture> topTexture, std::shared_ptr<Texture> topNormalTexture,
    std::shared_ptr<Texture> topMetallicTexture, std::shared_ptr<Model> midModel, std::shared_ptr<Texture> midTexture,
    std::shared_ptr<Texture> midNormalTexture, std::shared_ptr<Texture> midMetallicTexture,
    std::shared_ptr<Model> botModel, std::shared_ptr<Texture> botTexture, std::shared_ptr<Texture> botNormalTexture,
    std::shared_ptr<Texture> botMetallicTexture, const std::shared_ptr<Light> light, std::shared_ptr<Material> material,
    const std::shared_ptr<ShaderProgram> shader)
{
    std::shared_ptr<NormalObjectNode> bulletTopNode =
        std::make_shared<NormalObjectNode>(topModel, topTexture, topNormalTexture, topMetallicTexture, light, material);
    std::shared_ptr<NormalObjectNode> bulletMidNode =
        std::make_shared<NormalObjectNode>(midModel, midTexture, midNormalTexture, midMetallicTexture, light, material);
    std::shared_ptr<NormalObjectNode> bulletBotNode =
        std::make_shared<NormalObjectNode>(botModel, botTexture, botNormalTexture, botMetallicTexture, light, material);
    bulletTopNode->setShader(shader);
    bulletMidNode->setShader(shader);
    bulletBotNode->setShader(shader);

    bulletMidNode->addChild(bulletBotNode);
    bulletMidNode->addChild(bulletTopNode);
    return bulletMidNode;
}

std::shared_ptr<SceneNode> loadBullet(const std::unique_ptr<GraphicsAPI>& graphics, const std::shared_ptr<Light> light,
                                      const std::shared_ptr<ShaderProgram> blinnShader)
{
    // texture
    // base
    std::shared_ptr<Texture> bulletTopTexture = load2DTexture(graphics, "assets/arcane_loot_models/bullet/textures/"
                                                                        "Jinx's_Bulet_Bulet_BaseColor.png");
    std::shared_ptr<Texture> bulletMidTexture = load2DTexture(graphics, "assets/arcane_loot_models/bullet/textures/"
                                                                        "Jinx's_Bulet_Gilze_BaseColor.png");
    std::shared_ptr<Texture> bulletBotTexture = load2DTexture(graphics, "assets/arcane_loot_models/bullet/textures/"
                                                                        "Jinx's_Bulet_Hiter_BaseColor.png");
    // normal
    std::shared_ptr<Texture> bulletTopNormalTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/bullet/textures/"
                                "Jinx's_Bulet_Bulet_Normal.png");
    std::shared_ptr<Texture> bulletMidNormalTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/bullet/textures/"
                                "Jinx's_Bulet_Gilze_Normal.png");
    std::shared_ptr<Texture> bulletBotNormalTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/bullet/textures/"
                                "Jinx's_Bulet_Hiter_Normal.png");
    // metalic
    std::shared_ptr<Texture> bulletTopMetallicTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/bullet/textures/"
                                "Jinx's_Bulet_Bulet_Metallic.png");
    std::shared_ptr<Texture> bulletMidMetallicTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/bullet/textures/"
                                "Jinx's_Bulet_Gilze_Metallic.png");
    std::shared_ptr<Texture> bulletBotMetallicTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/bullet/textures/"
                                "Jinx's_Bulet_Hiter_Metallic.png");
    // material
    std::shared_ptr<Material> bulletMaterial = std::make_shared<Material>(Material{
        .ambient = glm::vec3(0.2f), .diffuse = glm::vec3(1.0f), .specular = glm::vec3(0.9f), .shininess = 10.0f});
    // models
    std::shared_ptr<Model> bulletTopModel =
        std::make_shared<Model>(graphics, "assets/arcane_loot_models/bullet/bullet_top.obj");
    std::shared_ptr<Model> bulletMidModel =
        std::make_shared<Model>(graphics, "assets/arcane_loot_models/bullet/bullet_mid.obj");
    std::shared_ptr<Model> bulletBotModel =
        std::make_shared<Model>(graphics, "assets/arcane_loot_models/bullet/bullet_bot.obj");
    // nodes
    std::shared_ptr<NormalObjectNode> bulletMidNode1 = createNormalBulletNode(
        bulletTopModel, bulletTopTexture, bulletTopNormalTexture, bulletTopMetallicTexture, bulletMidModel,
        bulletMidTexture, bulletMidNormalTexture, bulletMidMetallicTexture, bulletBotModel, bulletBotTexture,
        bulletBotNormalTexture, bulletBotMetallicTexture, light, bulletMaterial, blinnShader);
    std::shared_ptr<NormalObjectNode> bulletMidNode2 = createNormalBulletNode(
        bulletTopModel, bulletTopTexture, bulletTopNormalTexture, bulletTopMetallicTexture, bulletMidModel,
        bulletMidTexture, bulletMidNormalTexture, bulletMidMetallicTexture, bulletBotModel, bulletBotTexture,
        bulletBotNormalTexture, bulletBotMetallicTexture, light, bulletMaterial, blinnShader);
    std::shared_ptr<NormalObjectNode> bulletMidNode3 = createNormalBulletNode(
        bulletTopModel, bulletTopTexture, bulletTopNormalTexture, bulletTopMetallicTexture, bulletMidModel,
        bulletMidTexture, bulletMidNormalTexture, bulletMidMetallicTexture, bulletBotModel, bulletBotTexture,
        bulletBotNormalTexture, bulletBotMetallicTexture, light, bulletMaterial, blinnShader);
    std::shared_ptr<NormalObjectNode> bulletMidNode4 = createNormalBulletNode(
        bulletTopModel, bulletTopTexture, bulletTopNormalTexture, bulletTopMetallicTexture, bulletMidModel,
        bulletMidTexture, bulletMidNormalTexture, bulletMidMetallicTexture, bulletBotModel, bulletBotTexture,
        bulletBotNormalTexture, bulletBotMetallicTexture, light, bulletMaterial, blinnShader);
    // positions
    bulletMidNode1->transform.position = glm::vec3(-0.478698f, 0.085f, 0.610347f);
    bulletMidNode1->transform.rotation = glm::angleAxis(glm::radians(180.0f), glm::vec3{0.0f, 1.0f, 0.0f});

    bulletMidNode2->transform.rotation = glm::angleAxis(glm::radians(-55.0f), glm::vec3{0.0f, 1.0f, 0.0f});
    bulletMidNode2->transform.rotation *= glm::angleAxis(glm::radians(15.0f), glm::vec3{1.0f, 0.0f, 0.0f});
    bulletMidNode2->transform.rotation *= glm::angleAxis(glm::radians(90.0f), glm::vec3{0.0f, 0.0f, 1.0f});
    bulletMidNode2->transform.position = glm::vec3(-0.4f, 0.043f, 0.95f);

    bulletMidNode3->transform.rotation = glm::angleAxis(glm::radians(62.0f), glm::vec3{0.0f, 1.0f, 0.0f});
    bulletMidNode3->transform.rotation *= glm::angleAxis(glm::radians(-15.0f), glm::vec3{1.0f, 0.0f, 0.0f});
    bulletMidNode3->transform.rotation *= glm::angleAxis(glm::radians(90.0f), glm::vec3{0.0f, 0.0f, 1.0f});
    bulletMidNode3->transform.position = glm::vec3(-0.38f, 0.043f, 0.58f);

    bulletMidNode4->transform.rotation = glm::angleAxis(glm::radians(15.0f), glm::vec3{0.0f, 1.0f, 0.0f});
    bulletMidNode4->transform.rotation *= glm::angleAxis(glm::radians(190.0f), glm::vec3{1.0f, 0.0f, 0.0f});
    bulletMidNode4->transform.rotation *= glm::angleAxis(glm::radians(90.0f), glm::vec3{0.0f, 0.0f, 1.0f});
    bulletMidNode4->transform.position = glm::vec3(-0.65f, 0.043f, 0.95f);
    // final node
    std::shared_ptr<SceneNode> bulletsNode = std::make_shared<SceneNode>();
    bulletsNode->addChild(bulletMidNode1);
    bulletsNode->addChild(bulletMidNode2);
    bulletsNode->addChild(bulletMidNode3);
    bulletsNode->addChild(bulletMidNode4);
    return bulletsNode;
}

std::shared_ptr<NormalObjectNode> createGranadeNode(
    std::shared_ptr<Model> bodyModel, std::shared_ptr<Texture> bodyTexture, std::shared_ptr<Texture> bodyNormalTexture,
    std::shared_ptr<Texture> bodyMetallicTexture, std::shared_ptr<Texture> bodyEmissionTexture,
    std::shared_ptr<Model> topModel, std::shared_ptr<Texture> topTexture, std::shared_ptr<Texture> topNormalTexture,
    std::shared_ptr<Texture> topMetallicTexture, std::shared_ptr<Texture> topEmissionTexture,
    std::shared_ptr<Model> botModel, std::shared_ptr<Texture> botTexture, std::shared_ptr<Texture> botNormalTexture,
    std::shared_ptr<Texture> botMetallicTexture, std::shared_ptr<Texture> botEmissionTexture,
    const std::shared_ptr<Light> light, std::shared_ptr<Material> material, const std::shared_ptr<ShaderProgram> shader)
{
    std::shared_ptr<NormalObjectNode> granadeBodyNode = std::make_shared<NormalObjectNode>(
        bodyModel, bodyTexture, bodyNormalTexture, bodyMetallicTexture, light, material, bodyEmissionTexture);
    std::shared_ptr<NormalObjectNode> granadeTopNode = std::make_shared<NormalObjectNode>(
        topModel, topTexture, topNormalTexture, topMetallicTexture, light, material, topEmissionTexture);
    std::shared_ptr<NormalObjectNode> granadeBotNode = std::make_shared<NormalObjectNode>(
        botModel, botTexture, botNormalTexture, botMetallicTexture, light, material, botEmissionTexture);
    granadeBodyNode->setShader(shader);
    granadeTopNode->setShader(shader);
    granadeBotNode->setShader(shader);

    granadeBodyNode->addChild(granadeTopNode);
    granadeBodyNode->addChild(granadeBotNode);
    return granadeBodyNode;
}

std::shared_ptr<SceneNode> loadGranade(const std::unique_ptr<GraphicsAPI>& graphics, const std::shared_ptr<Light> light,
                                       const std::shared_ptr<ShaderProgram> blinnShader)
{
    // texture
    // base
    std::shared_ptr<Texture> granadeTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/granade/textures/lambert1_albedo.jpeg");
    std::shared_ptr<Texture> granadeTopTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/granade/textures/upper_mouth_albedo.jpeg");
    std::shared_ptr<Texture> granadeBotTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/granade/textures/lower_mouth_albedo.jpeg");
    // normal
    std::shared_ptr<Texture> granadeNormalTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/granade/textures/lambert1_normal.png");
    std::shared_ptr<Texture> granadeTopNormalTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/granade/textures/upper_mouth_normal.png");
    std::shared_ptr<Texture> granadeBotNormalTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/granade/textures/lower_mouth_normal.png");
    // metallic
    std::shared_ptr<Texture> granadeMetallicTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/granade/textures/lambert1_metallic.jpeg");
    std::shared_ptr<Texture> granadeTopMetallicTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/granade/textures/upper_mouth_metallic.jpeg");
    std::shared_ptr<Texture> granadeBotMetallicTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/granade/textures/lower_mouth_metallic.jpeg");
    // emission
    std::shared_ptr<Texture> granadeEmissionTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/granade/textures/lambert1_emissive.jpeg");
    std::shared_ptr<Texture> granadeTopEmissionTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/granade/textures/upper_mouth_emissive.jpeg");
    std::shared_ptr<Texture> granadeBotEmissionTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/granade/textures/lower_mouth_emissive.jpeg");
    // material
    std::shared_ptr<Material> granadeMaterial = std::make_shared<Material>(Material{
        .ambient = glm::vec3(0.2f), .diffuse = glm::vec3(1.0f), .specular = glm::vec3(0.6f), .emissive = 4.0f, .shininess = 8.0f});
    // models
    std::shared_ptr<Model> granadeModel =
        std::make_shared<Model>(graphics, "assets/arcane_loot_models/granade/bomb.obj");
    std::shared_ptr<Model> granadeTopModel =
        std::make_shared<Model>(graphics, "assets/arcane_loot_models/granade/bomb_top.obj");
    std::shared_ptr<Model> granadeBotModel =
        std::make_shared<Model>(graphics, "assets/arcane_loot_models/granade/bomb_bot.obj");
    // nodes
    std::shared_ptr<NormalObjectNode> granadeNode1 = createGranadeNode(
        granadeModel, granadeTexture, granadeNormalTexture, granadeMetallicTexture, granadeEmissionTexture,
        granadeTopModel, granadeTopTexture, granadeTopNormalTexture, granadeTopMetallicTexture,
        granadeTopEmissionTexture, granadeBotModel, granadeBotTexture, granadeBotNormalTexture,
        granadeBotMetallicTexture, granadeBotEmissionTexture, light, granadeMaterial, blinnShader);
    std::shared_ptr<NormalObjectNode> granadeNode2 = createGranadeNode(
        granadeModel, granadeTexture, granadeNormalTexture, granadeMetallicTexture, granadeEmissionTexture,
        granadeTopModel, granadeTopTexture, granadeTopNormalTexture, granadeTopMetallicTexture,
        granadeTopEmissionTexture, granadeBotModel, granadeBotTexture, granadeBotNormalTexture,
        granadeBotMetallicTexture, granadeBotEmissionTexture, light, granadeMaterial, blinnShader);
    // positions
    granadeNode1->transform.rotation = glm::angleAxis(glm::radians(20.0f), glm::vec3{0.0f, 0.0f, 1.0f});
    granadeNode1->transform.rotation *= glm::angleAxis(glm::radians(-32.0f), glm::vec3{1.0f, 0.0f, 0.0f});
    granadeNode1->transform.rotation *= glm::angleAxis(glm::radians(45.0f), glm::vec3{0.0f, 1.0f, 0.0f});
    granadeNode1->transform.position = glm::vec3(-0.66f, 0.235f, 0.14f);

    granadeNode2->transform.rotation = glm::angleAxis(glm::radians(-30.0f), glm::vec3{1.0f, 0.0f, 0.0f});
    granadeNode2->transform.rotation *= glm::angleAxis(glm::radians(-100.0f), glm::vec3{0.0f, 0.0f, 1.0f});
    granadeNode2->transform.position = glm::vec3(-0.28f, 0.200121f, 0.0f);
    // final node
    std::shared_ptr<SceneNode> granadeNode = std::make_shared<SceneNode>();
    granadeNode->addChild(granadeNode1);
    granadeNode->addChild(granadeNode2);
    return granadeNode;
}

std::shared_ptr<SceneNode> loadBazuka(const std::unique_ptr<GraphicsAPI>& graphics, const std::shared_ptr<Light> light,
                                      const std::shared_ptr<ShaderProgram> blinnShader)
{
    // texture
    // base
    std::shared_ptr<Texture> bazukaBodyTexture = load2DTexture(graphics, "assets/arcane_loot_models/bazuka/textures/"
                                                                         "low_poly_unwrapped_main_body_BaseColor.png");
    std::shared_ptr<Texture> bazukaArmorTexture = load2DTexture(graphics, "assets/arcane_loot_models/bazuka/textures/"
                                                                          "low_poly_unwrapped_armour_BaseColor.png");
    std::shared_ptr<Texture> bazukaBeltsTexture = load2DTexture(graphics, "assets/arcane_loot_models/bazuka/textures/"
                                                                          "low_poly_unwrapped_belts_BaseColor.png");
    std::shared_ptr<Texture> bazukaHandlesTexture = load2DTexture(graphics, "assets/arcane_loot_models/bazuka/textures/"
                                                                            "low_poly_unwrapped_handles_BaseColor.png");
    std::shared_ptr<Texture> bazukaJawsTexture = load2DTexture(graphics, "assets/arcane_loot_models/bazuka/textures/"
                                                                         "low_poly_unwrapped_jaws_BaseColor.png");
    std::shared_ptr<Texture> bazukaTeethTexture = load2DTexture(graphics, "assets/arcane_loot_models/bazuka/textures/"
                                                                          "low_poly_unwrapped_teeth_BaseColor.png");
    // normal
    std::shared_ptr<Texture> bazukaBodyNormalTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/bazuka/textures/"
                                "low_poly_unwrapped_main_body_Normal.png");
    std::shared_ptr<Texture> bazukaArmorNormalTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/bazuka/textures/"
                                "low_poly_unwrapped_armour_Normal.png");
    std::shared_ptr<Texture> bazukaBeltsNormalTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/bazuka/textures/"
                                "low_poly_unwrapped_belts_Normal.png");
    std::shared_ptr<Texture> bazukaHandlesNormalTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/bazuka/textures/"
                                "low_poly_unwrapped_handles_Normal.png");
    std::shared_ptr<Texture> bazukaJawsNormalTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/bazuka/textures/"
                                "low_poly_unwrapped_jaws_Normal.png");
    std::shared_ptr<Texture> bazukaTeethNormalTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/bazuka/textures/"
                                "low_poly_unwrapped_teeth_Normal.png");
    // metalic
    std::shared_ptr<Texture> bazukaBodyMetallicTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/bazuka/textures/"
                                "low_poly_unwrapped_main_body_Metallic.png");
    std::shared_ptr<Texture> bazukaArmorMetallicTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/bazuka/textures/"
                                "low_poly_unwrapped_armour_Metallic.png");
    std::shared_ptr<Texture> bazukaBeltsMetallicTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/bazuka/textures/"
                                "low_poly_unwrapped_belts_Metallic.png");
    std::shared_ptr<Texture> bazukaHandlesMetallicTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/bazuka/textures/"
                                "low_poly_unwrapped_handles_Metallic.png");
    std::shared_ptr<Texture> bazukaJawsMetallicTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/bazuka/textures/"
                                "low_poly_unwrapped_jaws_Metallic.png");
    std::shared_ptr<Texture> bazukaTeethMetallicTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/bazuka/textures/"
                                "low_poly_unwrapped_teeth_Metallic.png");
    // material
    std::shared_ptr<Material> bazukaBodyMaterial = std::make_shared<Material>(Material{
        .ambient = glm::vec3(0.2f), .diffuse = glm::vec3(1.0f), .specular = glm::vec3(0.4f), .shininess = 4.0f});
    std::shared_ptr<Material> bazukaMaterial = std::make_shared<Material>(Material{
        .ambient = glm::vec3(0.2f), .diffuse = glm::vec3(1.0f), .specular = glm::vec3(0.65f), .shininess = 16.0f});
    // models
    std::shared_ptr<Model> bazukaBodyModel =
        std::make_shared<Model>(graphics, "assets/arcane_loot_models/bazuka/body.obj");
    std::shared_ptr<Model> bazukaArmorModel =
        std::make_shared<Model>(graphics, "assets/arcane_loot_models/bazuka/armor.obj");
    std::shared_ptr<Model> bazukaBeltsModel =
        std::make_shared<Model>(graphics, "assets/arcane_loot_models/bazuka/belts.obj");
    std::shared_ptr<Model> bazukaHandlesModel =
        std::make_shared<Model>(graphics, "assets/arcane_loot_models/bazuka/handles.obj");
    std::shared_ptr<Model> bazukaJawsModel =
        std::make_shared<Model>(graphics, "assets/arcane_loot_models/bazuka/jaws.obj");
    std::shared_ptr<Model> bazukaTeethModel =
        std::make_shared<Model>(graphics, "assets/arcane_loot_models/bazuka/teeth.obj");
    // nodes
    std::shared_ptr<NormalObjectNode> bazukaBodyNode =
        std::make_shared<NormalObjectNode>(bazukaBodyModel, bazukaBodyTexture, bazukaBodyNormalTexture,
                                           bazukaBodyMetallicTexture, light, bazukaBodyMaterial);
    std::shared_ptr<NormalObjectNode> bazukaArmorNode =
        std::make_shared<NormalObjectNode>(bazukaArmorModel, bazukaArmorTexture, bazukaArmorNormalTexture,
                                           bazukaArmorMetallicTexture, light, bazukaMaterial);
    std::shared_ptr<NormalObjectNode> bazukaBeltsNode =
        std::make_shared<NormalObjectNode>(bazukaBeltsModel, bazukaBeltsTexture, bazukaBeltsNormalTexture,
                                           bazukaBeltsMetallicTexture, light, bazukaMaterial);
    std::shared_ptr<NormalObjectNode> bazukaHandlesNode =
        std::make_shared<NormalObjectNode>(bazukaHandlesModel, bazukaHandlesTexture, bazukaHandlesNormalTexture,
                                           bazukaHandlesMetallicTexture, light, bazukaMaterial);
    std::shared_ptr<NormalObjectNode> bazukaJawsNode = std::make_shared<NormalObjectNode>(
        bazukaJawsModel, bazukaJawsTexture, bazukaJawsNormalTexture, bazukaJawsMetallicTexture, light, bazukaMaterial);
    std::shared_ptr<NormalObjectNode> bazukaTeethNode =
        std::make_shared<NormalObjectNode>(bazukaTeethModel, bazukaTeethTexture, bazukaTeethNormalTexture,
                                           bazukaTeethMetallicTexture, light, bazukaMaterial);
    bazukaBodyNode->setShader(blinnShader);
    bazukaArmorNode->setShader(blinnShader);
    bazukaBeltsNode->setShader(blinnShader);
    bazukaHandlesNode->setShader(blinnShader);
    bazukaJawsNode->setShader(blinnShader);
    bazukaTeethNode->setShader(blinnShader);

    bazukaBodyNode->addChild(bazukaArmorNode);
    bazukaBodyNode->addChild(bazukaBeltsNode);
    bazukaBodyNode->addChild(bazukaHandlesNode);
    bazukaBodyNode->addChild(bazukaJawsNode);
    bazukaBodyNode->addChild(bazukaTeethNode);
    return bazukaBodyNode;
}

std::shared_ptr<SceneNode> loadPistol(const std::unique_ptr<GraphicsAPI>& graphics, const std::shared_ptr<Light> light,
                                      const std::shared_ptr<ShaderProgram> blinnShader)
{
    // texture
    // base
    std::shared_ptr<Texture> pistolTopTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/pistol/textures/lambert1_albedo.jpeg");
    std::shared_ptr<Texture> pistolBotTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/pistol/textures/lambert2_albedo.jpeg");
    std::shared_ptr<Texture> pistolRopeTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/pistol/textures/lambert3_albedo.jpeg");
    // normal
    std::shared_ptr<Texture> pistolTopNormalTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/pistol/textures/lambert1_normal.png");
    std::shared_ptr<Texture> pistolBotNormalTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/pistol/textures/lambert2_normal.png");
    std::shared_ptr<Texture> pistolRopeNormalTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/pistol/textures/lambert3_normal.png");
    // metalLic
    std::shared_ptr<Texture> pistolTopMetallicTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/pistol/textures/lambert1_metallic.jpeg");
    std::shared_ptr<Texture> pistolBotMetallicTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/pistol/textures/lambert2_metallic.jpeg");
    std::shared_ptr<Texture> pistolRopeMetallicTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/pistol/textures/lambert3_metallic.jpeg");
    // material
    std::shared_ptr<Material> pistolTopMaterial = std::make_shared<Material>(Material{
        .ambient = glm::vec3(0.2f), .diffuse = glm::vec3(1.0f), .specular = glm::vec3(0.6f), .shininess = 20.0f});
    std::shared_ptr<Material> pistolBotMaterial = std::make_shared<Material>(Material{
        .ambient = glm::vec3(0.2f), .diffuse = glm::vec3(1.0f), .specular = glm::vec3(0.8f), .shininess = 8.0f});
    std::shared_ptr<Material> pistolRopeMaterial = std::make_shared<Material>(Material{
        .ambient = glm::vec3(0.2f), .diffuse = glm::vec3(1.0f), .specular = glm::vec3(0.05f), .shininess = 4.0f});
    // models
    std::shared_ptr<Model> pistolTopModel =
        std::make_shared<Model>(graphics, "assets/arcane_loot_models/pistol/pistol_top.obj");
    std::shared_ptr<Model> pistolBotModel =
        std::make_shared<Model>(graphics, "assets/arcane_loot_models/pistol/pistol_bot.obj");
    std::shared_ptr<Model> pistolRopeModel =
        std::make_shared<Model>(graphics, "assets/arcane_loot_models/pistol/pistol_rope.obj");
    // nodes
    std::shared_ptr<NormalObjectNode> pistolTopNode = std::make_shared<NormalObjectNode>(
        pistolTopModel, pistolTopTexture, pistolTopNormalTexture, pistolTopMetallicTexture, light, pistolTopMaterial);
    std::shared_ptr<NormalObjectNode> pistolBotNode = std::make_shared<NormalObjectNode>(
        pistolBotModel, pistolBotTexture, pistolBotNormalTexture, pistolBotMetallicTexture, light, pistolBotMaterial);
    std::shared_ptr<NormalObjectNode> pistolRopeNode =
        std::make_shared<NormalObjectNode>(pistolRopeModel, pistolRopeTexture, pistolRopeNormalTexture,
                                           pistolRopeMetallicTexture, light, pistolRopeMaterial);
    pistolTopNode->setShader(blinnShader);
    pistolBotNode->setShader(blinnShader);
    pistolRopeNode->setShader(blinnShader);

    pistolTopNode->addChild(pistolBotNode);
    pistolTopNode->addChild(pistolRopeNode);
    return pistolTopNode;
}

std::shared_ptr<SceneNode> loadShimmer(const std::unique_ptr<GraphicsAPI>& graphics, const std::shared_ptr<Light> light,
                                       const std::shared_ptr<ShaderProgram> blinnShader)
{
    // texture
    std::shared_ptr<Texture> shimmerTexture =
        load2DTexture(graphics, "assets/arcane_loot_models/shimmer/textures/default.png");
    // material
    std::shared_ptr<Material> shimmerMaterial = std::make_shared<Material>(Material{
        .ambient = glm::vec3(0.2f), .diffuse = glm::vec3(1.0f), .specular = glm::vec3(1.0f), .shininess = 20.0f});
    // model
    std::shared_ptr<Model> shimmerModel =
        std::make_shared<Model>(graphics, "assets/arcane_loot_models/shimmer/shimmer.obj");
    // nodes
    std::shared_ptr<ObjectNode> shimmerNode1 =
        std::make_shared<ObjectNode>(shimmerModel, shimmerTexture, light, shimmerMaterial);
    std::shared_ptr<ObjectNode> shimmerNode2 =
        std::make_shared<ObjectNode>(shimmerModel, shimmerTexture, light, shimmerMaterial);
    shimmerNode1->setShader(blinnShader);
    shimmerNode2->setShader(blinnShader);
    // positions
    shimmerNode1->transform.rotation = glm::angleAxis(glm::radians(15.0f), glm::vec3{0.0f, 1.0f, 0.0f});
    shimmerNode1->transform.rotation *= glm::angleAxis(glm::radians(45.0f), glm::vec3{1.0f, 0.0f, 0.0f});
    shimmerNode1->transform.rotation *= glm::angleAxis(glm::radians(-90.0f), glm::vec3{0.0f, 1.0f, 0.0f});
    shimmerNode1->transform.position = glm::vec3(0.127612f, 0.065956f, 0.514526f);

    shimmerNode2->transform.rotation = glm::angleAxis(glm::radians(24.8f), glm::vec3{1.0f, 0.0f, 0.0f});
    shimmerNode2->transform.rotation *= glm::angleAxis(glm::radians(-25.0f), glm::vec3{0.0f, 1.0f, 0.0f});
    shimmerNode2->transform.rotation *= glm::angleAxis(glm::radians(55.0f), glm::vec3{0.0f, 0.0f, 1.0f});
    shimmerNode2->transform.position = glm::vec3(0.20f, 0.148f, 0.491468f);
    // final node
    std::shared_ptr<SceneNode> shimmerNode = std::make_shared<SceneNode>();
    shimmerNode->addChild(shimmerNode1);
    shimmerNode->addChild(shimmerNode2);
    return shimmerNode;
}

std::shared_ptr<SceneNode> loadSkyBox(const std::unique_ptr<GraphicsAPI>& graphics,
                                      const std::shared_ptr<ShaderProgram> skyboxShader,
                                      const std::shared_ptr<Camera> camera)
{
    std::array<Image, 6> skyboxImages = {Image{"assets/skybox/px.png", false}, Image{"assets/skybox/nx.png", false},
                                         Image{"assets/skybox/py.png", false}, Image{"assets/skybox/ny.png", false},
                                         Image{"assets/skybox/pz.png", false}, Image{"assets/skybox/nz.png", false}};
    std::shared_ptr<SkyBoxNode> skybox = std::make_shared<SkyBoxNode>(graphics, skyboxImages, camera);
    skybox->setShader(skyboxShader);
    return skybox;
}
