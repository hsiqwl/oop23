#ifndef GAME_MAP_GENERATOR_H
#define GAME_MAP_GENERATOR_H
#include <cstddef>

struct dimensions_generation_settings{
    size_t min_dimensions;
    size_t max_dimensions;
    size_t width;
    size_t height;
    dimensions_generation_settings(size_t min, size_t max, size_t width, size_t height)
        : min_dimensions(min), max_dimensions(max), width(width), height(height){}
};

struct point{
    size_t x;
    size_t y;
    point(size_t x, size_t y): x(x), y(y){}
};

struct rectangle{
    point centre;
    size_t width;
    size_t height;
    rectangle(point& centre, size_t width, size_t height): centre(centre.x, centre.y), width(width), height(height){}
};

class Dimension{
    rectangle* room;
    Dimension* left_child;
    Dimension* right_child;
};





#endif //GAME_MAP_GENERATOR_H
