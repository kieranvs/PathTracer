#pragma once

#include "Ray.h"

#include <array>

struct Triangle
{
    std::array<glm::vec3, 3> points;
    size_t material_index;
};

struct Sphere
{
    glm::vec3 center;
    float radius;
    size_t material_index;
};

struct IntersectionPoint
{
    bool is_valid;
    float depth;
    glm::vec3 position;
    glm::vec3 normal;
    size_t material_index;
};

namespace Intersection
{
    IntersectionPoint rayTriangleIntersect(const Ray& ray, const Triangle& tri);
    IntersectionPoint raySphereIntersects(const Ray& ray, const Sphere& sphere);
}