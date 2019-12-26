#include "Radiance.h"

void createCoordinateSystem(const glm::vec3& N, glm::vec3& Nt, glm::vec3& Nb) 
{ 
    if (std::fabs(N.x) > std::fabs(N.y)) 
        Nt = glm::vec3(N.z, 0, -N.x) / sqrtf(N.x * N.x + N.z * N.z); 
    else 
        Nt = glm::vec3(0, -N.z, N.y) / sqrtf(N.y * N.y + N.z * N.z); 
    Nb = glm::cross(N, Nt);
}

glm::vec3 uniformSampleHemisphere(float r1, float r2) 
{ 
    // cos(theta) = r1 = y
    // cos^2(theta) + sin^2(theta) = 1 -> sin(theta) = srtf(1 - cos^2(theta))
    float sinTheta = sqrtf(1 - r1 * r1); 
    float phi = 2 * M_PI * r2; 
    float x = sinTheta * cosf(phi); 
    float z = sinTheta * sinf(phi); 
    return glm::vec3(x, r1, z);
} 

glm::vec3 Radiance::finalColour(const Scene& scene, const std::vector<Material>& materials, const Ray& pixel_ray, int depth)
{
    const bool use_russian_roulette = true;
    if (depth > 4)
    {
        if (use_russian_roulette)
        {
            float r = distribution(generator);
            if (r < 0.25)
                return glm::vec3(0.0f, 0.0f, 0.0f);
        }
        else
        {
            return glm::vec3(0.0f, 0.0f, 0.0f);
        }
    }

    IntersectionPoint point = scene.castRay(pixel_ray);

    // miss
    if (!point.is_valid || point.depth < 0)
        return glm::vec3(0.0f, 0.0f, 0.0f);
    
    const Material& material = materials[point.material_index];

    // hit a light right away
    if (material.is_emissive)
        return material.colour;

    glm::vec3 normal_x, normal_z; 
    createCoordinateSystem(point.normal, normal_x, normal_z); 

    glm::vec3 result{};

    int samples = 1;
    if (depth == 0) samples = 256;
    if (depth == 1) samples = 1;
    if (depth == 2) samples = 1;

    for (uint32_t samples_i = 0; samples_i < samples; samples_i++)
    {
        float r1 = distribution(generator); // cos(theta) = N.Light Direction 
        float r2 = distribution(generator); 
        glm::vec3 sample = uniformSampleHemisphere(r1, r2); 
    glm::vec3 new_dir{ 
        sample.x * normal_x.x + sample.y * point.normal.x + sample.z * normal_z.x, 
        sample.x * normal_x.y + sample.y * point.normal.y + sample.z * normal_z.y, 
        sample.x * normal_x.z + sample.y * point.normal.z + sample.z * normal_z.z}; 
        new_dir = glm::normalize(new_dir);
        Ray new_ray{point.position + new_dir * 0.01f, new_dir};

        glm::vec3 nrfc = finalColour(scene, materials, new_ray, depth + 1);
        result += material.colour * ((r1 * nrfc) / (1.0f / 2.0f * 3.1415926f));
    }
    
    if (samples != 0) result /= samples; 
    
    return result;
}