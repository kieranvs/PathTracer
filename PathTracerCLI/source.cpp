#include <PathTracer/Scene.h>
#include <PathTracer/Material.h>

#include <vector>
#include <iostream>

int main()
{
    Scene scene;
    
    scene.addCube({ -0.1f, 0.0f, -0.1f},
                  {  0.1f, 0.2f,  0.1f},
                  1);
    scene.addQuad({ -0.5f, 0.0f, -0.5f },
                  {  0.5f, 0.0f, -0.5f },
                  {  0.5f, 0.0f,  0.5f },
                  { -0.5f, 0.0f,  0.5f },
                  0);
    scene.addCube({  0.0f, 0.0f,  0.2f},
                  {  0.2f, 0.2f,  0.4f},
                  2);
    scene.addSphere({ -0.3f, 0.2f, 0.3f}, 0.05f, 0);


    std::vector<Material> materials;
    materials.push_back({{1.0f, 1.0f, 1.0f}});
    materials.push_back({{0.5f, 0.0f, 1.0f}});
    materials.push_back({{1.0f, 0.0f, 0.0f}});

    Ray camera_ray{{0.0f, 1.0f, -2.0f}, glm::normalize(glm::vec3{0.0f, -1.0f, 2.0f})};
    glm::vec3 offset_y_dir = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 offset_x_dir = glm::cross(camera_ray.direction, offset_y_dir);

    int image_width = 1024;
    int image_height = image_width * 3 / 4;
    glm::vec3* output = new glm::vec3[image_width * image_height];

    std::cout << image_width << "x" << image_height << " (" << (image_width*image_height/1000000.f) << "MP)" << std::endl;

    using clock = std::chrono::system_clock;
    const auto before = clock::now();

    for (int dx = 0; dx < image_width; dx++)
    {
        float dxp = (float(dx) / float(image_width)) - 0.5f;
        for (int dy = 0; dy < image_height; dy++)
        {
            float dyp = -((float(dy) / float(image_height)) - 0.5f);

            glm::vec3 pixel_ray_dir = glm::normalize(camera_ray.direction + offset_x_dir * dxp + offset_y_dir * dyp);

            Ray pixel_ray{camera_ray.origin, pixel_ray_dir};

            IntersectionPoint point = scene.castRay(pixel_ray);

            glm::vec3 col{0.0f, 0.0f, 0.0f};
            if (point.is_valid)
            {
                col = materials[point.material_index].colour;
            }

            output[dy * image_width + dx] = col;
        }
    }

    const std::chrono::duration<double> duration = clock::now() - before;

    double seconds_dur = duration.count();
    double pxpersec = (double)(image_width * image_height) / seconds_dur;
    std::cout << "Finished in " << seconds_dur << "s (" << pxpersec << " px/sec)" << std::endl;

    auto toInt = [](float x) { return (int)(x * 255.0f); };

    FILE *f = fopen("image.ppm", "w");
    fprintf(f, "P3\n%d %d\n%d\n", image_width, image_height, 255);
    for (int i = 0; i < image_width * image_height; i++)
    {
        fprintf(f, "%d %d %d ", toInt(output[i].x), toInt(output[i].y), toInt(output[i].z));
    }

    delete[] output;
}