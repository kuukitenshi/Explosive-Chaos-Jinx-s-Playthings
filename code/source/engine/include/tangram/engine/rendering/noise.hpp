#pragma once

struct NoiseAttributes
{
    float frequency = 2.0f;
    float amplitude = 0.5f;
    int octaves = 8;
    int gridSize = 400;
};

float multiPerlin(int x, int y, const NoiseAttributes& attributes);

float perlin2D(float x, float y, const NoiseAttributes& attributes);
