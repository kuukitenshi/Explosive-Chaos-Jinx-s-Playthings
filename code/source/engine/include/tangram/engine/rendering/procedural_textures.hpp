#pragma once

#include <memory>
#include <string>
#include <tangram/engine/rendering/image.hpp>
#include <tangram/engine/rendering/noise.hpp>

using namespace tangram::engine;

void woodTexturePerlin(std::shared_ptr<Image> image, const NoiseAttributes& attributes, const std::string& outPath);

void marbleTexturePerlin(std::shared_ptr<Image> image, const NoiseAttributes& attributes, const std::string& outPath);

void brickTexturePerlin(std::shared_ptr<Image> image, const NoiseAttributes& attributesBrick,
                        const NoiseAttributes& attributesMortar, const std::string& outPath);
