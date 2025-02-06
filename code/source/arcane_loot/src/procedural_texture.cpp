
#include "procedural_texture.hpp"

#include <tangram/engine/rendering/noise.hpp>
#include <tangram/engine/rendering/procedural_textures.hpp>

using namespace tangram::engine;

void genMarbleTexture()
{
    auto imageMarble =
        std::make_shared<Image>(1024, 1024, 3, std::shared_ptr<unsigned char>(new unsigned char[1024 * 1024 * 3]));
    NoiseAttributes marbleAttributes{.frequency = 3.0f, .amplitude = 0.42f, .octaves = 10, .gridSize = 120};
    marbleTexturePerlin(imageMarble, marbleAttributes, "assets/procedural/marble.jpeg");
}

void genWoodTexture()
{
    auto imageWood =
        std::make_shared<Image>(2048, 2048, 3, std::shared_ptr<unsigned char>(new unsigned char[2048 * 2048 * 3]));
    NoiseAttributes woodAttributes{.frequency = 2.8f, .amplitude = 0.5f, .octaves = 4, .gridSize = 1};
    woodTexturePerlin(imageWood, woodAttributes, "assets/procedural/wood.jpeg");
}

void genBrickTexture()
{
    auto imageBrick =
        std::make_shared<Image>(1024, 1024, 3, std::shared_ptr<unsigned char>(new unsigned char[1024 * 1024 * 3]));
    NoiseAttributes brickAttributes{.frequency = 10.0f, .amplitude = 0.8f, .octaves = 5, .gridSize = 70};
    NoiseAttributes mortarAttributes{.frequency = 20.0f, .amplitude = 0.6f, .octaves = 6, .gridSize = 80};
    brickTexturePerlin(imageBrick, brickAttributes, mortarAttributes, "assets/procedural/brick.jpeg");
}
