#include "main.h"
#include "timer.h"
#include "ball.h"
#include "block.h"
#include "platform.h"
#include "water.h"
#include "death.h"
#include "snow.h"
#include <time.h>       /* time */
#include <stdlib.h>     /* srand, rand */

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Block blck[10];
Platform pf;
Water water;
Death death;
Snow snow[16];
int level=1;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ball1.draw(VP);
    pf.draw(VP);

    for(int i=0;i<10;i++)
        blck[i].draw(VP);

    death.draw(VP);
    water.draw(VP);

    for(int i=0;i<16;i++)
        snow[i].draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);

    if(ball1.position.x<-3.8 && ball1.speedx<0 || ball1.position.x>3.8 && ball1.speedx>0)
    {
        ball1.speedx = 0;
        ball1.kick = 0;
    }
    else if(ball1.position.y<=-3.0  && ball1.kick==1)
    {
        ball1.speedx = 0;
        ball1.kick = 0;
    }
    if(ball1.kick==0 && (!left && !right))
        ball1.speedx=0;

    if (left) {
        if(ball1.side==0 && ball1.position.x>=-3.8)
        {
            if(level==1){
            if(ball1.position.x >= -1.5 && ball1.position.x <= 1.5 && ball1.position.y<=-3.0){ball1.speedx=-0.005;}
            else if((!(ball1.position.x >= -1.5 && ball1.position.x <= 1.5)) || ball1.position.y>-3.0){ball1.speedx=-0.01;}
            }
            else
                ball1.speedx=-0.01;
            ball1.kick = 0;
            //if(level==1)
            //ball1.position.x -= ball1.speedx;

//            if(level==2)
//                ball1.speedx = ball1.speedx/2;
        }// Do something
        else
        {
            if(ball1.kick==0)
            {
                cout<<"here"<<endl;
                ball1.speedx=0.0;
            }
        }
    }
    if (right) {

        if(ball1.side==0 && ball1.position.x<=3.8)
        {
            if(level==1){
            if(ball1.position.x >= -1.5 && ball1.position.x <= 1.5 && ball1.position.y<=-3.0){ball1.speedx=0.005;}
            else if((!(ball1.position.x >= -1.5 && ball1.position.x <= 1.5)) || ball1.position.y>-3.0){ball1.speedx=0.01;}
            }
            else
                ball1.speedx=0.01;
            ball1.kick = 0;
            //if(level==1)
            //ball1.position.x += ball1.speedx;

//            if(level==2)
//               ball1.speedx = (3*ball1.speedx)/2;

        }// Do something
        else
        {
            if(ball1.kick==0)
            {
                cout<<"here"<<endl;
                ball1.speedx=0.0;
            }
        }
    }
//    else
//        ball1.speedx=0.0;

    if (up) {
       //cout<<ball1.tramp<<" "<<detect_collision(ball1.bounding_box(), blck[ball1.tramp].bounding_box())<<" "<<ball1.position.y - blck[ball1.tramp].position.y<<endl;
        if(ball1.position.x >= -1.5 && ball1.position.x <= 1.5 && ball1.position.y<=-3.0 && ball1.jump==0 && ball1.fall==0)
        {
            ball1.jumpup(0.015);
        }
        else if(((!(ball1.position.x >= -1.5 && ball1.position.x <= 1.5)) || ball1.position.y>-3.0) && ball1.jump==0 && ball1.fall==0)
        {
            if(!(ball1.tramp!=-1 && detect_collision(ball1.bounding_box(), blck[ball1.tramp].bounding_box()) && ball1.position.y - blck[ball1.tramp].position.y <= 0.4 && ball1.position.y - blck[ball1.tramp].position.y >= 0.345))
                ball1.jumpup(0.05);
            else
                ball1.jumpup(0.075);

        }
        // Do something
    }
    if (down && ball1.tramp==-1) {
        //cout <<" "<< abs(ball1.position.x - blck[9].position.x) * 2 <<" "<< 0.8 <<" "<< abs(ball1.position.y - blck[9].position.y) * 2 <<" "<< 0.8 << endl;
        for(int i=0;i<10;i++)
        {
            //cout<<i<<" ";
            if (detect_collision(ball1.bounding_box(), blck[i].bounding_box()))
            {
                if(ball1.position.y - blck[i].position.y > 0)
                {

                    blck[i].tramp = 1;

                    ball1.tramp = i;

                    float posx = blck[ball1.tramp].position.x;
                    float posy = blck[ball1.tramp].position.y;
                    //cout<<blck[i].position.x<<" "<<blck[i].position.y<<endl;
                    blck[ball1.tramp]   = Block(posx, posy, 1, 1, COLOR_TRAMP);
                    //cout<<"done: "<<blck[i].tramp<<endl;

                }
            }
        }
        // Do somethingj
    }
}

void tick_elements() {

//    window = initGLFW(1000, 1000, ball1.score);
    char scor[40]={0};
    sprintf(scor, "%d", ball1.score);
    glfwSetWindowTitle(window, scor);

    if(ball1.score==100 && ball1.position.y>=3.75 && level==1){screen_center_y=8;reset_screen();initLevel2();level=2;}
    else if(ball1.score>=250 && ball1.position.y>=3.75+8 && level==2){quit(window);}

    if(level==1)
    {ball1.tick();}

    else if(level==2)
    {
        ball1.tick2();
        death.tick();
        if (detect_collision(ball1.bounding_box(), death.bounding_box()))
            quit(window);
        for(int i=0;i<3;i++)
        {
            for(int j=1;j<3;j++)
            {
                if (detect_collision(blck[i*3].bounding_box(), blck[i*3+j].bounding_box()))blck[i*3].speedx = -blck[i*3].speedx;
            }
            if (detect_collision(blck[i*3 + 1].bounding_box(), blck[i*3+2].bounding_box()))blck[i*3+1].speedx = -blck[i*3+1].speedx;
        }
        for(int i=0;i<16;i++)
        {
            snow[i].tick();
            if (detect_collision(ball1.bounding_box(), snow[i].bounding_box()))
            {
                snow[i].position.x = -4-(rand()%4 + 1);
                ball1.score += 5;
            }
        }
    }

    //cout<<blck[0].position.x<<endl;
    int sideflag=0;
    int fallflag=0;
    //cout<<ball1.position.y<<endl;
    //cout<<"tramp: "<<blck[ball1.tramp].tramp<<endl;
    for(int i=0;i<10;i++)
    {
        if(level==2)
            blck[i].tick();

        if (detect_collision(ball1.bounding_box(), blck[i].bounding_box()))
        {
            //cout<<i<<" "<<ball1.speedx<<endl;
            //ball1.speedy = 0;
            ball1.speedx = 0;
            ball1.kick = 0;
            //cout<<i<<"x:"<<blck[i].position.x - ball1.position.x<<endl;
            //cout<<i<<"y:"<<blck[i].position.y - ball1.position.y<<endl;

            if(ball1.position.y - blck[i].position.y  > 0.0)
            {
                if(blck[i].hit==0)
                {
                     float posx = blck[i].position.x;
                     float posy = blck[i].position.y;
                     //cout<<blck[i].position.x<<" "<<blck[i].position.y<<endl;
                     blck[i]   = Block(posx, posy, 0, 1, COLOR_YELLOW);
                                    //cout<<"on block"<<endl;
                                    //cout<<blck[i].position.x<<" "<<blck[i].position.y<<endl;
                     blck[i].hit = 1;
                     ball1.score += 10;
                }
                ball1.jump = 0;
                ball1.fall = 0;
                if(i!=ball1.tramp)
                ball1.jumpup(0.05);
                else
                ball1.jumpup(0.075);

                float tan0 = abs(blck[i].position.x - ball1.position.x)/abs(blck[i].position.y - ball1.position.y);
                ball1.speedx = tan0 * 0.01;

                if(ball1.speedx > 0.05)ball1.speedx=0.05;

                ball1.kick=1;
                if(blck[i].position.x > ball1.position.x)ball1.speedx = -ball1.speedx;

            }
            else if(blck[i].position.y - ball1.position.y > 0.0)
            {
                  if(ball1.jump==1)
                       ball1.speedy = 0;
                  ball1.jump=0;
                  ball1.fall=1;
                  ball1.kick=1;
                  fallflag=1;

                  float tan0 = abs(blck[i].position.x - ball1.position.x)/abs(blck[i].position.y - ball1.position.y);
                  ball1.speedx = tan0 * 0.01;

                  if(ball1.speedx > 0.05)ball1.speedx=0.05;

                  if(blck[i].position.x > ball1.position.x)ball1.speedx = -ball1.speedx;
            }


            //cout<<"gchgchgcjgc: "<<i<<" "<<ball1.position.y - blck[i].position.y<<endl;
//            if(blck[i].position.y - ball1.position.y >= 0.363)
//            {
//                ball1.position.y = blck[i].position.y - 0.4;
//                if(ball1.jump==1)
//                    ball1.speedy = 0;
//                ball1.jump=0;
//                ball1.fall=1;
//                fallflag=1;
//                //ball1.ay=0;
//            }
//            else if(ball1.position.y - blck[i].position.y <= 0.4 && ball1.position.y - blck[i].position.y >= 0.32)
//            {
//                if(blck[i].hit==0)
//                {
//                    float posx = blck[i].position.x;
//                    float posy = blck[i].position.y;
//                    //cout<<blck[i].position.x<<" "<<blck[i].position.y<<endl;
//                    blck[i]   = Block(posx, posy, 0, 1, COLOR_YELLOW);
//                    //cout<<"on block"<<endl;
//                    //cout<<blck[i].position.x<<" "<<blck[i].position.y<<endl;
//                    blck[i].hit = 1;
//                    ball1.score += 10;
//                }
//                ball1.position.y = blck[i].position.y + 0.39999;
//                ball1.speedy = 0;
//                ball1.jump = 0;
//                ball1.fall = 0;
//                if(i!=ball1.tramp)
//                ball1.jumpup(0.05);
//                else
//                ball1.jumpup(0.075);
//                //ball1.drop=1;
//            }
//            else if(abs(blck[i].position.x - ball1.position.x) <= 0.39)
//            {
//                //cout<<"gchgchgcjgc"<<endl;
//                //if(blck[i].position.x > ball1.position.x)ball1.position.x=blck[i].position.x - 0.4;
//                //else ball1.position.x=blck[i].position.x + 0.4;
//                ball1.side=1;
//                sideflag=1;
//            }
//            else
//            {
//                //ball1.drop=0;
//                if(!sideflag)
//                ball1.side=0;
//            }
            //cout<<"y:"<<blck[i].position.y - ball1.position.y<<endl;


            //else if
        }
        else
        {
             ball1.drop=1;
             if(!sideflag)
             ball1.side=0;
        }
    }
}

void snowinit(int i)
{
    int k = rand()%4 + 1;
    if(i==0)snow[i]          = Snow(-k-3, -1.5+8, -1.3+8, -1.7+8, COLOR_SNOW);
    else if(i==1)snow[i]     = Snow(-k-4, -1.00+8, -0.8+8, -1.2+8, COLOR_SNOW);
    else if(i==2)snow[i]     = Snow(-k-3, -0.00+8,  0.2+8, -0.2+8, COLOR_SNOW);
    else if(i==3)snow[i]     = Snow(-k-4,  0.50+8, 0.7+8, 0.3+8, COLOR_SNOW);
    else if(i==4)snow[i]     = Snow(-k-3,  1.50+8, 1.7+8, 1.3+8, COLOR_SNOW);
    else if(i==5)snow[i]     = Snow(-k-4,  2.00+8, 2.2+8, 1.8+8, COLOR_SNOW);
    else if(i==6)snow[i]     = Snow(-k-3,  3.00+8, 3.2+8, 2.8+8, COLOR_SNOW);
    else if(i==7)snow[i]     = Snow(-k-4,  3.50+8, 3.7+8, 3.3+8, COLOR_SNOW);
    else if(i==8)snow[i]     = Snow(-k-6, -1.5+8, -1.3+8, -1.7+8, COLOR_SNOW);
    else if(i==9)snow[i]     = Snow(-k-7, -1.00+8, -0.8+8, -1.2+8, COLOR_SNOW);
    else if(i==10)snow[i]     = Snow(-k-6, -0.00+8,  0.2+8, -0.2+8, COLOR_SNOW);
    else if(i==11)snow[i]     = Snow(-k-7,  0.50+8, 0.7+8, 0.3+8, COLOR_SNOW);
    else if(i==12)snow[i]     = Snow(-k-6,  1.50+8, 1.7+8, 1.3+8, COLOR_SNOW);
    else if(i==13)snow[i]     = Snow(-k-7,  2.00+8, 2.2+8, 1.8+8, COLOR_SNOW);
    else if(i==14)snow[i]     = Snow(-k-6,  3.00+8, 3.2+8, 2.8+8, COLOR_SNOW);
    else if(i==15)snow[i]     = Snow(-k-7,  3.50+8, 3.7+8, 3.3+8, COLOR_SNOW);
}

void initLevel2()
{
    ball1       = Ball(-2, 5, 0.01, COLOR_RED);
    pf          = Platform(0, 4.5, COLOR_SNOW);
    for(int i=0;i<10;i++)
    {
        float posx = blck[i].position.x;
        float posy = blck[i].position.y;
        blck[i]     = Block(posx, posy+8, 0, 0, COLOR_BLACK);
    }
    death       = Death(2, 5, COLOR_DEATH);

    for(int i=0;i<16;i++)snowinit(i);
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1       = Ball(-2, -3, 0.01, COLOR_RED);
    pf          = Platform(0, -3.5, COLOR_GREEN);

    water       = Water(0, -3.2, COLOR_WATER);




    for(int i=0;i<3;i++)
        blck[i]     = Block(2*i-1.5, -2, 0, 0, COLOR_BLACK);

    for(int i=0;i<3;i++)
        blck[i+3]   = Block(1.9*i-2.5, -0.5, 0, 0, COLOR_BLACK);

    for(int i=0;i<3;i++)
        blck[i+6]   = Block(2.3*i-1.4, 1, 0, 0, COLOR_BLACK);

        blck[9]     = Block(0, 2.5, 0, 0, COLOR_BLACK);


        death       = Death(2, 5, COLOR_DEATH);

    for(int i=0;i<4;i++)
        snow[i]     = Snow(-5, 5, 0, 0, COLOR_SNOW);


    for(int i=0;i<4;i++)
        snow[i+4]   = Snow(-5, 5, 0, 0, COLOR_SNOW);


    for(int i=0;i<4;i++)
        snow[i+8]   = Snow(-5, 5, 0, 0, COLOR_SNOW);


    for(int i=0;i<4;i++)
        snow[i+12]   = Snow(-5, 5, 0, 0, COLOR_SNOW);



    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1000;
    int height = 1000;

    window = initGLFW(width, height, ball1.score);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

//bool detect_collision(bounding_box_t a, bounding_box_t b) {
//    //cout<<" "<<abs(a.x - b.x)<<" "<<abs(a.y - b.y)<<" "<<(a.width + b.width)<<" "<<(a.height + b.height)<<" "<< ((abs(a.x - b.x) * 2 <= (a.width + b.width)) && (abs(a.y - b.y) * 2 <= (a.height + b.height)))<<endl;
//    return ((abs(a.x - b.x) * 2 <= 0.8) &&
//           (abs(a.y - b.y) * 2 <= 0.8));
//}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    //cout<<a.x<<" "<<b.x<<" "<<a.y<<" "<<b.y<<endl;
    return ((((abs(a.x - b.x)) * (abs(a.x - b.x)))) + (((abs(a.y - b.y)) * (abs(a.y - b.y))))) <= ((a.width/2 + b.width/2) * (a.width/2 + b.width/2));
//    return (abs(a.x - b.x) * 2 <= (a.width + b.width)) &&
//           (abs(a.y - b.y) * 2 <= (a.height + b.height));
}

void reset_screen() {
    //if(ball1.score>=0 && ball1.position.y>=3.5){screen_center_y+=4;}
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
