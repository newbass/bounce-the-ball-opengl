#include "main.h"

#ifndef DEATH_H
#define DEATH_H


class Death {
public:
    Death() {}
    Death(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float speedx;
    float speedy;
    float ax;
    float ay;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // DEATH_H
