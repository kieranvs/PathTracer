#include <glm/glm.hpp>

struct Ray
{
    glm::vec3 origin;
    glm::vec3 direction;
};

struct IntersectionPoint
{
    bool is_valid;
    size_t material_index;
};