#include "block.h"
#include "main.h"
#include <bits/stdc++.h>
using namespace std;

Block::Block(float x, float y, int hi, int tram, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speedx = 0.003;
    speedy = 0;
    leftrange = x-0.5;
    rightrange = x+0.5;
    ax = 0;
    ay = 0;
    hit=hi;
    tramp=tram;/*
    static const GLfloat vertex_buffer_data[] = {
        -0.2, -0.2, 0, // vertex 1
        0.2,  -0.2, 0, // vertex 2
        0.2,  0.2, 0, // vertex 3

        0.2,  0.2, 0, // vertex 3
        -0.2, 0.2, 0, // vertex 4
        -0.2, -0.2, 0 // vertex 1
    };*/
    GLfloat vertex_buffer_data[10000] = { };
        int i=0,j=0;
        float radi=0.2;
        double ra= ((double)M_PI)/360.00;
        for(i=0;i<720;i++)
        {
            double rad= ra*i;
            vertex_buffer_data[9*(i)+0]= 0.0f;
            vertex_buffer_data[9*(i)+1]= 0.0f;
            vertex_buffer_data[9*(i)+2]= 0.0f;
            vertex_buffer_data[9*(i)+3]= radi*cos(rad);
            vertex_buffer_data[9*(i)+4]= radi*sin(rad);
            vertex_buffer_data[9*(i)+5]= 0.0f;
            rad = ra*(1+i);
            vertex_buffer_data[9*(i)+6]= radi*cos(rad);
            vertex_buffer_data[9*(i)+7]= radi*sin(rad);
            vertex_buffer_data[9*(i)+8]= 0.0f;
        }

    this->object = create3DObject(GL_TRIANGLES, 720*3, vertex_buffer_data, color, GL_FILL);
}

void Block::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Block::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Block::tick() {

    this->position.x += speedx;
    if(this->position.x+speedx > rightrange || this->position.x+speedx < leftrange)
        speedx = -speedx;

    //
}

bounding_box_t Block::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
