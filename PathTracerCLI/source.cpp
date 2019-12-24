#include <PathTracer/Scene.h>
#include <PathTracer/Material.h>
#include <PathTracer/Radiance.h>

#include <vector>
#include <iostream>

int main()
{
    /* initial test scene 
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
    scene.addSphere({ -0.3f, 0.4f, 0.3f}, 0.39f, 3);

    std::vector<Material> materials;
    materials.push_back({{1.0f, 1.0f, 1.0f}, false});
    materials.push_back({{0.5f, 0.0f, 1.0f}, false});
    materials.push_back({{1.0f, 0.0f, 0.0f}, false});
    materials.push_back({{1.0f, 1.0f, 1.0f}, true});
    */

    /* cornell */
    Scene scene;
    //floor
    scene.addQuad({552.8f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 559.2f}, {549.6f, 0.0f, 559.2f}, 0);
    //light
    scene.addQuad({343.0f, 544.8f, 227.0f},{343.0f, 544.8f, 332.0f},{213.0f, 544.8f, 332.0f},{213.0f, 544.8f, 227.0f}, 1); //lowered y from 548.8
    //ceiling, white
    scene.addQuad({556.0f, 548.8f, 0.0f},{556.0f, 548.8f, 559.2f},{0.0f, 548.8f, 559.2f},{0.0f, 548.8f, 0.0f}, 0);
    //wall, white
    scene.addQuad({549.6, 0.0f, 559.2f},{0.0f, 0.0f, 559.2f},{0.0f, 548.8f, 559.2f},{556.0f, 548.8f, 559.2f}, 0);
    //wall, green
    scene.addQuad({0.0f, 0.0f, 559.2f},{0.0f, 0.0f, 0.0f},{0.0f, 548.8f, 0.0f},{0.0f, 548.8f, 559.2f}, 2);
    //wall, red
    scene.addQuad({552.8f, 0.0f, 0.0f},{549.6, 0.0f, 559.2f},{556.0f, 548.8f, 559.2f},{556.0f, 548.8f, 0.0f}, 3);
    //block, white
    scene.addQuad({130.0f, 165.0f, 65.0f},{82.0f, 165.0f, 225.0f},{240.0f, 165.0f, 272.0f},{290.0f, 165.0f, 114.0f}, 0);
    scene.addQuad({290.0f, 0.0f, 114.0f},{290.0f, 165.0f, 114.0f},{240.0f, 165.0f, 272.0f},{240.0f, 0.0f, 272.0f}, 0);
    scene.addQuad({130.0f, 0.0f, 65.0f},{130.0f, 165.0f, 65.0f},{290.0f, 165.0f, 114.0f},{290.0f, 0.0f, 114.0f}, 0);
    scene.addQuad({82.0f, 0.0f, 225.0f},{82.0f, 165.0f, 225.0f},{130.0f, 165.0f, 65.0f},{130.0f, 0.0f, 65.0f}, 0);
    scene.addQuad({240.0f, 0.0f, 272.0f},{240.0f, 165.0f, 272.0f},{82.0f, 165.0f, 225.0f},{82.0f, 0.0f, 225.0f}, 0);
    //block, white
    scene.addQuad({423.0f, 330.0f, 247.0f},{265.0f, 330.0f, 296.0f},{314.0f, 330.0f, 456.0f},{472.0f, 330.0f, 406.0f}, 0);
    scene.addQuad({423.0f, 0.0f, 247.0f},{423.0f, 330.0f, 247.0f},{472.0f, 330.0f, 406.0f},{472.0f, 0.0f, 406.0f}, 0);
    scene.addQuad({472.0f, 0.0f, 406.0f},{472.0f, 330.0f, 406.0f},{314.0f, 330.0f, 456.0f},{314.0f, 0.0f, 456.0f}, 0);
    scene.addQuad({314.0f, 0.0f, 456.0f},{314.0f, 330.0f, 456.0f},{265.0f, 330.0f, 296.0f},{265.0f, 0.0f, 296.0f}, 0);
    scene.addQuad({265.0f, 0.0f, 296.0f},{265.0f, 330.0f, 296.0f},{423.0f, 330.0f, 247.0f},{423.0f, 0.0f, 247.0f}, 0);

    std::vector<Material> materials;
    materials.push_back({{1.0f, 1.0f, 1.0f}, false});
    const float b = 48.0f;
    materials.push_back({{b, b, b}, true});
    materials.push_back({{0.0f, 1.0f, 0.0f}, false});
    materials.push_back({{1.0f, 0.0f, 0.0f}, false});

    Ray camera_ray{{278.0f, 273.0f, -800.0f}, glm::normalize(glm::vec3{0.0f, 0.0f, 1.0f})};
    glm::vec3 offset_y_dir = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 offset_x_dir = glm::cross(camera_ray.direction, offset_y_dir);

    int image_width = 1024;
    int image_height = image_width * 3 / 4;
    glm::vec3* output = new glm::vec3[image_width * image_height];

    std::cout << image_width << "x" << image_height << " (" << (image_width*image_height/1000000.f) << "MP)" << std::endl;

    using clock = std::chrono::system_clock;
    const auto before = clock::now();

    Radiance radiance;

    for (int dx = 0; dx < image_width; dx++)
    {
        float progress = (float(dx) / float(image_width)) * 100.0f;
        std::cout << "\rProgress: " << progress << "%" << std::flush;
        float dxp = (float(dx) / float(image_width)) - 0.5f;
        for (int dy = 0; dy < image_height; dy++)
        {
            float dyp = -((float(dy) / float(image_height)) - 0.5f);

            glm::vec3 pixel_ray_dir = glm::normalize(camera_ray.direction + offset_x_dir * dxp + offset_y_dir * dyp);
            Ray pixel_ray{camera_ray.origin, pixel_ray_dir};
            output[dy * image_width + dx] = radiance.finalColour(scene, materials, pixel_ray, 0);
        }
    }

    const std::chrono::duration<double> duration = clock::now() - before;

    double seconds_dur = duration.count();
    double pxpersec = (double)(image_width * image_height) / seconds_dur;
    std::cout << "\rFinished in " << seconds_dur << "s (" << pxpersec << " px/sec)" << std::endl;

    auto toInt = [](float x)
    {
        int ret = (int)(x * 255.0f);
        if (ret > 255) ret = 255;
        if (ret < 0) ret = 0;
        return ret;
    };

    FILE *f = fopen("image.ppm", "w");
    fprintf(f, "P3\n%d %d\n%d\n", image_width, image_height, 255);
    for (int i = 0; i < image_width * image_height; i++)
    {
        fprintf(f, "%d %d %d ", toInt(output[i].x), toInt(output[i].y), toInt(output[i].z));
    }

    delete[] output;
}