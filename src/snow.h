#include "main.h"

#ifndef SNOW_H
#define SNOW_H


class Snow {
public:
    Snow() {}
    Snow(float x, float y, float up, float down, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float speedx;
    float speedy;
    float uprange;
    float downrange;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // SNOW_H
