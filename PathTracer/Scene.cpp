#include "Scene.h"
#include "Intersection.h"

void Scene::addTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, size_t material_index)
{
    triangles.push_back({ { a, b, c}, material_index });
}

void Scene::addQuad(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, size_t material_index)
{
    addTriangle(a, b, c, material_index);
    addTriangle(a, c, d, material_index);
}

void Scene::addCube(glm::vec3 low, glm::vec3 high, size_t material)
{
    glm::vec3 lll = glm::vec3(low.x, low.y, low.z);
    glm::vec3 llh = glm::vec3(low.x, low.y, high.z);
    glm::vec3 lhl = glm::vec3(low.x, high.y, low.z);
    glm::vec3 lhh = glm::vec3(low.x, high.y, high.z);

    glm::vec3 hll = glm::vec3(high.x, low.y, low.z);
    glm::vec3 hlh = glm::vec3(high.x, low.y, high.z);
    glm::vec3 hhl = glm::vec3(high.x, high.y, low.z);
    glm::vec3 hhh = glm::vec3(high.x, high.y, high.z);

    addQuad(lll, llh, lhh, lhl, material);
    addQuad(hll, hlh, hhh, hhl, material);
    addQuad(lll, llh, hlh, hll, material);
    addQuad(lhl, lhh, hhh, hhl, material);
    addQuad(lll, lhl, hhl, hll, material);
    addQuad(llh, lhh, hhh, hlh, material);
}

void Scene::addSphere(glm::vec3 c, float radius, size_t material)
{
    spheres.push_back({c, radius, material});
}

IntersectionPoint Scene::castRay(Ray ray) const
{
    IntersectionPoint p;
    p.is_valid = false;

    for (auto tri : triangles)
    {
        IntersectionPoint ip = Intersection::rayTriangleIntersect(ray, tri);
        if (ip.is_valid && (!p.is_valid || ip.depth < p.depth) && ip.depth > 0)
            p = ip;
    }

    for (auto& sphere : spheres)
    {
        IntersectionPoint ip = Intersection::raySphereIntersects(ray, sphere);
        if (ip.is_valid && (!p.is_valid || ip.depth < p.depth) && ip.depth > 0)
            p = ip;
    }

    return p;
}