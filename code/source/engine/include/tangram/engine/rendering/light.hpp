#pragma once

#include <glm/glm.hpp>

struct Light
{
    glm::vec3 direction;
    glm::vec3 color;
    float ka;
    float kd;
    float ks;
    float shininess;
};
