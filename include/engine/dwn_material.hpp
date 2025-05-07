#pragma once
#include <string>
#include <glm/vec3.hpp>

struct DwnMaterial {
    std::string tag;
    float shininess;
    float reflectivity;
    float refractive_index;

    glm::vec3 ambient_color;
    glm::vec3 diffuse_color;
    glm::vec3 specular_color;

    DwnMaterial(const std::string& tag, float shininess, float reflectivity, float refractive_index,
                const glm::vec3& ambient_color, const glm::vec3& diffuse_color, const glm::vec3& specular_color)
        : tag(tag), shininess(shininess), reflectivity(reflectivity), refractive_index(refractive_index),
          ambient_color(ambient_color), diffuse_color(diffuse_color), specular_color(specular_color) {}

    

};