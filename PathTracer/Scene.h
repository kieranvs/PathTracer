#pragma once

#include "Ray.h"
#include "Intersection.h"

#include <glm/glm.hpp>

#include <vector>

class Scene
{
public:
    void addTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, size_t material_index);
    void addQuad(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, size_t material_index);
    void addCube(glm::vec3 low, glm::vec3 high, size_t material);
    void addSphere(glm::vec3 c, float radius, size_t material);

    IntersectionPoint castRay(Ray ray);
private:
    std::vector<Triangle> triangles;
    std::vector<Sphere> spheres;
};