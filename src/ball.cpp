#include "ball.h"
#include "main.h"
#include <bits/stdc++.h>
using namespace std;

Ball::Ball(float x, float y, float sp, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speedx = 0;
    speedn = 0;
    speedw = 0;
    speedy = 0;
    ax = 0;
    ay = -0.05;
    jump = 0;
    fall=0;
    side=0;
    drop=0;
    tramp=-1;
    score=0;
    kick=0;
//    static const GLfloat vertex_buffer_data[] = {
//        -0.2, -0.2, 0, // vertex 1
//        0.2,  -0.2, 0, // vertex 2
//        0.2,  0.2, 0, // vertex 3

//        0.2,  0.2, 0, // vertex 3
//        -0.2, 0.2, 0, // vertex 4
//        -0.2, -0.2, 0 // vertex 1
//    };

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

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::jumpup(float sp)
{
    speedy = sp;
    jump = 1;
}

void Ball::tick() {
//    screen_zoom = 1.5;
//    screen_center_x =this->position.x;
//    screen_center_y =this->position.y;
//    reset_screen();
//    cout<<speedx<<endl;
    if(this->position.x >= -1.4 && this->position.x <= 1.4)
    {
        if(this->position.y>-3.2)
        {
            this->position.y-=0.001;
        }
    }

//    if(this->position.x >= -1.5 && this->position.x <= 1.5 && this->position.y<=-3.0){speedx=0.005;}
//    else if((!(this->position.x >= -1.5 && this->position.x <= 1.5)) || this->position.y>-3.0){speedx=0.01;}

    this->position.x += speedx;

    this->position.y += speedy;
    //cout<<side<<endl;
    //cout<<jump<<fall<<drop<<endl;

    if(jump==1)
    {
        if(this->position.y<=-3.0 && !(this->position.x >= -1.4 && this->position.x <= 1.4))
        {
            jump=0;speedy=0;
            this->position.y=-3.0;
            goto jumpy;
        }
        else if(this->position.y<=-3.2 && (this->position.x >= -1.4 && this->position.x <= 1.4))
        {
            jump=0;speedy=0;
            this->position.y=-3.2;
            goto jumpy;
        }
        drop=0;
        speedy += ay/60;
      //cout<<"speedy: "<<speedy<<endl;
        jumpy:
        (1==1);
    }
    if(fall==1)
    {
        if(this->position.y<=-3.0/* && !(this->position.x >= -1.5 && this->position.x <= 1.5)*/)
        {
            fall=0;speedy=0;
            this->position.y=-3.0;
            goto jmpy;
        }
        speedy += ay/60;
        jmpy:
        (1==1);
    }
    if(drop==1)
    {
        if(this->position.y<=-3.0 && !(this->position.x >= -1.4 && this->position.x <= 1.4))
        {
            drop=0;speedy=0;
            this->position.y=-3.0;
            goto jpy;
        }
        else if(this->position.y<=-3.2 && (this->position.x >= -1.4 && this->position.x <= 1.4))
        {
            drop=0;speedy=0;
            this->position.y=-3.2;
            goto jpy;

        }
        speedy += ay/60;
        jpy:
        (1==1);
    }
    //
}

void Ball::tick2() {

    this->position.x += speedx;


    this->position.x += 0.005;

//    if(side==0 && this->position.x<=3.8)
//        this->position.x += abs(speedx)/3;

    //if(this->position.x >= -1.5 && this->position.x <= 1.5 && this->position.y<=-3.0){speedx=speedw;}
    //else if((!(this->position.x >= -1.5 && this->position.x <= 1.5)) || this->position.y>-3.0){speedx=speedn;}

//    if(side==0 && this->position.x<=3.8)
//        this->position.x += speedx/3;
    this->position.y += speedy;
    //cout<<side<<endl;
    //cout<<jump<<fall<<drop<<endl;
    if(jump==1)
    {
        if(this->position.y<=-3.0+8){jump=0;speedy=0;this->position.y=-3.0+8;goto jumpy;}
        drop=0;
        speedy += ay/60;
      //cout<<"speedy: "<<speedy<<endl;
        jumpy:
        (1==1);
    }
    if(fall==1)
    {
        if(this->position.y<=-3.0+8){fall=0;speedy=0;this->position.y=-3.0+8;goto jmpy;}
        speedy += ay/60;
        jmpy:
        (1==1);
    }
    if(drop==1)
    {
        if(this->position.y<=-3.0+8){drop=0;speedy=0;this->position.y=-3.0+8;goto jpy;}
        speedy += ay/60;
        jpy:
        (1==1);
    }
    //
}

bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
