#pragma once

#include "Scene.h"
#include "Material.h"
#include "Ray.h"
#include "Options.h"

#include <random>

class Radiance
{
public:
    Radiance(const Options& options) : options{options} {}

    glm::vec3 finalColour(const Scene& scene, const std::vector<Material>& materials, const Ray& pixel_ray, int depth);

private:
    std::default_random_engine generator; 
    std::uniform_real_distribution<float> distribution{0, 1}; 

    const Options& options;
};