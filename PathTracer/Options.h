#pragma once

struct Options
{
    int image_width = 1024;
    int image_height = 768;

    bool ray_depth_cutoff = 4;
    bool use_russian_roulette = true;
    float russian_roulette_survive_prob = 0.25;
};