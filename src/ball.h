#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, float sp, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void tick2();
    void jumpup(float sp);
    float speedx;
    float speedw;
    float speedn;
    float speedy;
    float ax;
    float ay;
    int jump;
    int fall;
    int side;
    int drop;
    int tramp;
    int kick;
    int score;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
