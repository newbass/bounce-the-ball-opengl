#include "main.h"

#ifndef BLOCK_H
#define BLOCK_H


class Block {
public:
    Block() {}
    Block(float x, float y, int hi, int tram, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void jumpup(float sp);
    float speedx;
    float speedy;
    float leftrange;
    float rightrange;
    float ax;
    float ay;
    int hit;
    int tramp;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
