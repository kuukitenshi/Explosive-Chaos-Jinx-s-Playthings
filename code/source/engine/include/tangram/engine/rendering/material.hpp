#pragma once

#include <glm/glm.hpp>

struct Material
{
    glm::vec3 ambient = glm::vec3(0.1f);
    glm::vec3 diffuse = glm::vec3(0.6f);
    glm::vec3 specular = glm::vec3(0.5f);
    float emissive = 1.0f;
    float shininess = 32.0f;
};
