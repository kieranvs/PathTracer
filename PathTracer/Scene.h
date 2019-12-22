#include "Ray.h"

#include <glm/glm.hpp>

#include <array>
#include <vector>

struct Triangle
{
    std::array<glm::vec3, 3> points;
    size_t material_index;
};

class Scene
{
public:
    void addTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, size_t material_index);
    void addQuad(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, size_t material_index);
    void addCube(glm::vec3 low, glm::vec3 high, size_t material);

    IntersectionPoint castRay(Ray ray);
private:
    std::vector<Triangle> triangles;
};