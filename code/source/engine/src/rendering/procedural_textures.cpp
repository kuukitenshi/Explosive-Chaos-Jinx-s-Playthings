#include <algorithm>
#include <cmath>
#include <glm/glm.hpp>
#include <tangram/engine/rendering/procedural_textures.hpp>

// ------------------------------ utils ------------------------------
float smoothStep(float t)
{
    return t * t * (3.0f - 2.0f * t);
}

void applyMortarTexture(std::shared_ptr<Image>& image, int x, int y, const NoiseAttributes& attributesMortar,
                        const glm::vec3& mortarColor)
{
    float mortarNoise = std::clamp(mortarNoise, -1.0f, 1.0f);
    mortarNoise = smoothStep(mortarNoise);

    unsigned char r = static_cast<unsigned char>(mortarColor[0] + mortarNoise * 30);
    unsigned char g = static_cast<unsigned char>(mortarColor[1] + mortarNoise * 30);
    unsigned char b = static_cast<unsigned char>(mortarColor[2] + mortarNoise * 40);

    int index = (y * image->width + x) * 3;
    image->pixels.get()[index] = r;
    image->pixels.get()[index + 1] = g;
    image->pixels.get()[index + 2] = b;
}

// ------------------------------ generate procedural textures ------------------------------
void woodTexturePerlin(std::shared_ptr<Image> image, const NoiseAttributes& attributes, const std::string& outPath)
{
    float xScale = 8.5f;
    float yScale = 1.5f;
    float frequencyPattern = 17.0f;

    for (int y = 0; y < image->height; ++y)
    {
        for (int x = 0; x < image->width; ++x)
        {
            float normalx = static_cast<float>(x) / image->width;
            float normaly = static_cast<float>(y) / image->height;
            float xCoord = normalx * xScale;
            float yCoord = normaly * yScale;

            float grain = perlin2D(xCoord, yCoord, attributes);
            float pattern = std::sin((xCoord + grain) * frequencyPattern) * 0.5f + 0.5f;
            float value = smoothStep(pattern) * 0.6f + 0.4f; // contrast -- luminosity

            unsigned char r = static_cast<unsigned char>(value * 50 + 56);
            unsigned char g = static_cast<unsigned char>(value * 40 + 33);
            unsigned char b = static_cast<unsigned char>(value * 30 + 27);

            int index = (y * image->width + x) * 3;
            image->pixels.get()[index + 0] = r;
            image->pixels.get()[index + 1] = g;
            image->pixels.get()[index + 2] = b;
        }
    }
    image->saveImage(outPath);
}

void marbleTexturePerlin(std::shared_ptr<Image> image, const NoiseAttributes& attributes, const std::string& outPath)
{
    float waveFrequency = 0.022f;
    float pattern = 9.0f;
    for (int y = 0; y < image->height; y++)
    {
        for (int x = 0; x < image->width; x++)
        {
            float baseNoise = multiPerlin(x, y, attributes);
            baseNoise = std::clamp(baseNoise, -1.0f, 1.0f);
            float k = std::cos(x * waveFrequency + baseNoise * pattern) * 0.5f + 0.5f;

            glm::vec3 marble_color = glm::vec3(232, 232, 232);
            glm::vec3 vein_color = glm::vec3(154, 154, 154);
            glm::vec3 color = glm::mix(marble_color, vein_color, k);

            unsigned char r = static_cast<unsigned char>(color.r);
            unsigned char g = static_cast<unsigned char>(color.g);
            unsigned char b = static_cast<unsigned char>(color.b);

            int index = (y * image->width + x) * 3;
            image->pixels.get()[index + 0] = r;
            image->pixels.get()[index + 1] = g;
            image->pixels.get()[index + 2] = b;
        }
    }
    image->saveImage(outPath);
}

void brickTexturePerlin(std::shared_ptr<Image> image, const NoiseAttributes& attributesBrick,
                        const NoiseAttributes& attributesMortar, const std::string& outPath)
{
    int brickWidth = 45;
    int brickHeight = 21;
    int mortarThickness = 3;
    glm::vec3 mortarColor = {105, 105, 127};

    for (int y = 0; y < image->height; y++)
    {
        for (int x = 0; x < image->width; x++)
        {
            float baseNoise = multiPerlin(x, y, attributesBrick);
            baseNoise = std::clamp(baseNoise, -1.0f, 1.0f);

            unsigned char r = static_cast<unsigned char>(35 + baseNoise * 20);
            unsigned char g = static_cast<unsigned char>(35 + baseNoise * 20);
            unsigned char b = static_cast<unsigned char>(50 + baseNoise * 30);

            int index = (y * image->width + x) * 3;
            image->pixels.get()[index] = r;
            image->pixels.get()[index + 1] = g;
            image->pixels.get()[index + 2] = b;
        }
    }
    // vertical mortar
    int lineThickness = brickHeight + mortarThickness;
    int numLines = std::ceil(image->height / (brickHeight + mortarThickness)) + 1;
    for (int i = 0; i < numLines; i++)
    {
        int startX = i % 2 == 0 ? brickWidth : (brickWidth - mortarThickness) / 2;
        int startY = i * lineThickness;
        for (int y = startY; y < startY + brickHeight && y < image->height; y++)
        {
            for (int x = startX; x < image->width; x += brickWidth + mortarThickness)
            {
                for (int j = 0; j < mortarThickness && x + mortarThickness < image->width; j++)
                {
                    float mortarNoise = multiPerlin(x + j, y, attributesMortar);
                    applyMortarTexture(image, x + j, y, attributesMortar, mortarColor);
                }
            }
        }
        // horizontal mortar
        for (int y = startY + brickHeight; y < startY + brickHeight + mortarThickness && y < image->height; y++)
        {
            for (int x = 0; x < image->width; x++)
            {
                float mortarNoise = multiPerlin(x, y, attributesMortar);
                applyMortarTexture(image, x, y, attributesMortar, mortarColor);
            }
        }
    }
    image->saveImage(outPath);
}
