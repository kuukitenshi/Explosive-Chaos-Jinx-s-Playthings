#include <algorithm>
#include <array>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <iostream>
#include <tangram/engine/rendering/noise.hpp>

// ------------------------- utils -------------------------
glm::vec2 randomGradient(int ix, int iy)
{
    // pseudo random vector gradient
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2;
    unsigned a = ix, b = iy;
    a *= 3284157443;

    b ^= a << s | a >> (w - s);
    b *= 1911520717;

    a ^= b << s | b >> (w - s);
    a *= 2048419325;
    float random = a * (3.14159265 / ~(~0u >> 1)); // normalize in [0, 2*Pi]

    return glm::vec2{sin(random), cos(random)};
}

float dotGradient(int xi, int yi, float x, float y)
{   // smooth gradient
    glm::vec2 gradient = randomGradient(xi, yi);
    glm::vec2 distance = {x - xi, y - yi};
    return glm::dot(distance, gradient);
}

float cubicInterpolation(float a0, float a1, float w)
{
    return (a1 - a0) * (3.0f - w * 2.0f) * w * w + a0;
}

float fade(float t)
{
    return t * t * t * (t * (t * 6 - 15) + 10); // polinom of 5th degree
}

int hash(int x)
{
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

float grad(int hash, float x, float y)
{
    int h = hash & 7;
    float u = h < 4 ? x : y;
    float v = h < 4 ? y : x;
    return ((h & 1) ? -u : u) + ((h & 2) ? -2.0f * v : 2.0f * v);
}
// ------------------------- perlin noise -------------------------

float perlin(float x, float y)
{
    int xi = static_cast<int>(x);
    int yi = static_cast<int>(y);
    float xf = x - xi;
    float yf = y - yi;
    // dot product for the 4 corners
    float n0 = dotGradient(xi, yi, x, y);
    float n1 = dotGradient(xi + 1, yi, x, y);
    float n2 = dotGradient(xi, yi + 1, x, y);
    float n3 = dotGradient(xi + 1, yi + 1, x, y);
    // cubic interpolation
    float top = cubicInterpolation(n0, n1, xf);
    float bottom = cubicInterpolation(n2, n3, xf);
    return cubicInterpolation(top, bottom, yf);
}

float multiPerlin(int x, int y, const NoiseAttributes& attributes)
{
    float freq = 1;
    float amp = 1;
    float value = 0;
    for (int i = 0; i < attributes.octaves; i++)
    {
        value += perlin(x * freq / attributes.gridSize, y * freq / attributes.gridSize) * amp;
        freq *= attributes.frequency;
        amp *= attributes.amplitude;
    }
    return std::clamp(value, -1.0f, 1.0f);
}

float perlin2D(float x, float y, const NoiseAttributes& attributes)
{
    float frequency = attributes.frequency;
    float amplitude = attributes.amplitude;
    float total = 0.0f;
    float maxAmplitude = 0.0f;

    for (int i = 0; i < attributes.octaves; ++i)
    {
        float fx = (x * frequency) / attributes.gridSize;
        float fy = (y * frequency) / attributes.gridSize;
        // get the 4 corners
        int x0 = static_cast<int>(std::floor(fx));
        int y0 = static_cast<int>(std::floor(fy));
        int x1 = (x0 + 1);
        int y1 = (y0 + 1);
        // dist inside the cell
        float dx = fx - std::floor(fx);
        float dy = fy - std::floor(fy);
        // smooth
        float u = fade(dx);
        float v = fade(dy);
        // hashes
        int hash00 = hash(x0 + y0);
        int hash01 = hash(x0 + y1);
        int hash10 = hash(x1 + y0);
        int hash11 = hash(x1 + y1);
        // gradients
        float grad00 = grad(hash00, dx, dy);
        float grad01 = grad(hash01, dx, dy - 1.0f);
        float grad10 = grad(hash10, dx - 1.0f, dy);
        float grad11 = grad(hash11, dx - 1.0f, dy - 1.0f);
        // linear interpolation
        float lerpX0 = grad00 + u * (grad10 - grad00);
        float lerpX1 = grad01 + u * (grad11 - grad01);
        float lerpY = lerpX0 + v * (lerpX1 - lerpX0);

        total += lerpY * amplitude;
        maxAmplitude += amplitude;
        frequency *= attributes.frequency;
        amplitude *= attributes.amplitude;
    }
    return total / maxAmplitude;
}
