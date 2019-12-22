#include "Ray.h"
#include "Scene.h"

#include <glm/glm.hpp>

namespace Intersection
{

IntersectionPoint rayTriangleIntersect(const Ray& ray, const Triangle& tri)
{
    float u, v;
    IntersectionPoint ip;
    ip.is_valid = false;

    glm::vec3 v0v1 = tri.points[1] - tri.points[0]; 
    glm::vec3 v0v2 = tri.points[2] - tri.points[0];
    glm::vec3 pvec = glm::cross(ray.direction, v0v2);
    float det = glm::dot(v0v1, pvec);
    const float kEpsilon = 0.0001f;
#ifdef CULLING 
    // if the determinant is negative the triangle is backfacing
    // if the determinant is close to 0, the ray misses the triangle
    if (det < kEpsilon) return ip; 
#else 
    // ray and triangle are parallel if det is close to 0
    if (fabs(det) < kEpsilon) return ip; 
#endif 
    float invDet = 1 / det; 
 
    glm::vec3 tvec = ray.origin - tri.points[0];
    u = glm::dot(tvec, pvec) * invDet;
    if (u < 0 || u > 1) return ip; 
 
    glm::vec3 qvec = glm::cross(tvec, v0v1);
    v = glm::dot(ray.direction, qvec) * invDet;
    if (v < 0 || u + v > 1) return ip; 
 
    ip.is_valid = true;
    ip.depth = glm::dot(v0v2, qvec) * invDet;
    ip.material_index = tri.material_index;
    ip.position = ray.origin + ip.depth * ray.direction;
    ip.normal = glm::normalize(glm::cross(v0v1, v0v2));
    if (det < kEpsilon)
        ip.normal = -ip.normal;
 
    return ip;
} 

IntersectionPoint raySphereIntersects(const Ray& ray, const Sphere& sphere)
{
    IntersectionPoint ip;
    ip.is_valid = false;
    float t0, t1;
    float radius2 = sphere.radius * sphere.radius;

    glm::vec3 L = sphere.center - ray.origin;
    float tca = glm::dot(L, ray.direction);
    // if (tca < 0) return false;
    float d2 = glm::dot(L, L) - tca * tca;
    if (d2 > radius2) return ip;
    float thc = sqrt(radius2 - d2);
    t0 = tca - thc;
    t1 = tca + thc;

    if (t0 > t1) std::swap(t0, t1);

    if (t0 < 0)
    {
        t0 = t1;
        if (t0 < 0) return ip;
    }

    ip.is_valid = true;
    ip.depth = t0;
    ip.material_index = sphere.material_index;
    ip.position = ray.origin + t0 * ray.direction;
    ip.normal = glm::normalize(ip.position - sphere.center);

    return ip;

}
}