#include "Scene.h"

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

bool rayTriangleIntersect(const Ray& ray, const Triangle& tri, float&t, float& u, float& v)
{
    glm::vec3 v0v1 = tri.points[1] - tri.points[0]; 
    glm::vec3 v0v2 = tri.points[2] - tri.points[0];
    glm::vec3 pvec = glm::cross(ray.direction, v0v2);
    float det = glm::dot(v0v1, pvec);
    const float kEpsilon = 0.0001f;
#ifdef CULLING 
    // if the determinant is negative the triangle is backfacing
    // if the determinant is close to 0, the ray misses the triangle
    if (det < kEpsilon) return false; 
#else 
    // ray and triangle are parallel if det is close to 0
    if (fabs(det) < kEpsilon) return false; 
#endif 
    float invDet = 1 / det; 
 
    glm::vec3 tvec = ray.origin - tri.points[0];
    u = glm::dot(tvec, pvec) * invDet;
    if (u < 0 || u > 1) return false; 
 
    glm::vec3 qvec = glm::cross(tvec, v0v1);
    v = glm::dot(ray.direction, qvec) * invDet;
    if (v < 0 || u + v > 1) return false; 
 
    t = glm::dot(v0v2, qvec) * invDet;
 
    return true;
} 

IntersectionPoint Scene::castRay(Ray ray)
{
    IntersectionPoint p;
    p.is_valid = false;
    float depth_nearest;

    for (auto tri : triangles)
    {
        float t, u, v;
        if (rayTriangleIntersect(ray, tri, t, u, v))
        {
            if (!p.is_valid || t < depth_nearest)
            {
                p.is_valid = true;
                p.material_index = tri.material_index;
                depth_nearest = t;
            }
        }
    }

    return p;
}