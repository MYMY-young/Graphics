#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Shaders/LoadShaders.h"
GLuint h_ShaderProgram; // handle to shader program
GLint loc_ModelViewProjectionMatrix, loc_primitive_color; // indices of uniform variables

                                            // include glm/*.hpp only if necessary
                                            //#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> //translate, rotate, scale, ortho, etc.
glm::mat4 ModelViewProjectionMatrix;
glm::mat4 ViewMatrix, ProjectionMatrix, ViewProjectionMatrix;

#define TO_RADIAN 0.01745329252f  
#define TO_DEGREE 57.295779513f
#define BUFFER_OFFSET(offset) ((GLvoid *) (offset))

#define LOC_VERTEX 0


int win_width = 0, win_height = 0;
float centerx = 0.0f, centery = 0.0f, rotate_angle = 0.0f;

#include "objects.h"

unsigned int timestamp = 0;

int leftbuttonpressed = 0;
void timer(int value) {
    timestamp = (timestamp + 1) % UINT_MAX;
    glutPostRedisplay();
    glutTimerFunc(10, timer, 0);
}


void display(void) {
    glm::mat4 ModelMatrix;
    glm::mat4 Mm(1.0f);
    glm::mat4 Model(1.0f);
    glClear(GL_COLOR_BUFFER_BIT);



    //draw_house(); // in MC

    glClearColor(153 / 255.0f, 204 / 255.0f, 255 / 255.0f, 1.0f);

  
    
    int house_clock = (timestamp % 1442) / 2 - 360; // -360 <= house_clock <= 360 
    //int cocktail_clock = (timestamp % 1442) / 2 - 360;
    float rotation_angle_house = atanf(100.0f * TO_RADIAN * cosf(house_clock * TO_RADIAN));
    float rotation_angle_robot = atanf(100.0f * TO_RADIAN * cosf(house_clock * TO_RADIAN));
    float scaling_factor_house = 5.0f * (1.0f - fabs(sinf(house_clock * TO_RADIAN)));
    float scaling_large_house =  3.0f*(fabs(timestamp * TO_RADIAN));
    float scaling_cake1 = 5.0f * (1.0f - fabs(cosf(timestamp * TO_RADIAN)));
    float scaling_cake2 = 5.0f * (1.0f - fabs(sinf(timestamp * TO_RADIAN)));
    float scaling_factor_cocktail = 5.0f * (1.0f - fabs(sinf(house_clock * TO_RADIAN)));
    // in WC
    


    if (timestamp >= 500 && timestamp<800) {
        ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(centerx, centery + 180.0f, 0.0f));
        ModelMatrix = glm::scale(ModelMatrix, glm::vec3(scaling_large_house, scaling_large_house, 1.0f));
        ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
        glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
        draw_house();
       
    }
    else if (timestamp >= 800) {
        //house 없애기
        glClearColor(255.0f/255.0f, 255.0f/255.0f, 204.0f/255.0f, 1.0f);
        ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, 200.0f, 0.0f));
        ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
        glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
       // draw_cocktail();
        ModelMatrix = glm::mat4(1.0f);
        ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-200.0f, 150.0f, 0.0f));
        ModelMatrix = glm::scale(ModelMatrix, glm::vec3(10.0f, 10.0f, 1.0f));
        ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
        glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
        draw_window();
        //첫번째 window
        ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(200.0f, 150.0f, 0.0f));
        ModelMatrix = glm::scale(ModelMatrix, glm::vec3(10.0f, 10.0f, 1.0f));
        ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
        glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
        draw_window();
        //두번째 window
    }
    else {
        ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(centerx, centery, 0.0f));
       // ModelMatrix = glm::translate(ModelMatrix, glm::vec3((float)house_clock,
        //    100.0f * sinf(house_clock * TO_RADIAN), 0.0f));
        ModelMatrix = glm::scale(ModelMatrix, glm::vec3(scaling_factor_house, scaling_factor_house, 1.0f));
       // ModelMatrix = glm::rotate(ModelMatrix, rotation_angle_house, glm::vec3(0.0f, 0.0f, 1.0f));
        ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
        glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
        draw_house();
    }
    int cocktail_clock = timestamp % 30; // 0 <= airplane_clock <= 719 
    if (timestamp >= 800) {
      
       
      //  ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, COCKTAIL_ROTATION_RADIUS, 0.0f));
    //    ModelMatrix = glm::rotate(ModelMatrix, cocktail_clock * TO_RADIAN, glm::vec3(0.0f, 0.0f, 0.0f));
     //   ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, -COCKTAIL_ROTATION_RADIUS, 0.0f));
        if (leftbuttonpressed == 1 || flag == 1) {
            ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-20.0f, 15.0f, 0.0f));
            ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.5f, -0.5f, 0.5f));
            ModelMatrix = glm::rotate(ModelMatrix, -(cocktail_clock)*TO_RADIAN, glm::vec3(0.0f, 1.0f, 1.0f));


            ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
            glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
            draw_cocktail();
       
            ModelMatrix = glm::rotate(ModelMatrix, (cocktail_clock)*TO_RADIAN, glm::vec3(0.0f, 1.0f, 1.0f));
            ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
            glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
            draw_cocktail();
           

            ModelMatrix = glm::scale(ModelMatrix, glm::vec3(-1.0f, 1.0f, 1.0f));   
            ModelMatrix = glm::rotate(ModelMatrix, -(cocktail_clock)*TO_RADIAN, glm::vec3(-1.0f, -1.0f, 1.0f));


            ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
            glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
            draw_cocktail();
            flag = 1;
        }
        ModelMatrix = glm::mat4(1.0f);
        ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-200.0f, 150.0f, 0.0f));
        ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
        glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
        draw_floor();
        draw_room_line();

     //   ModelMatrix = glm::mat4(1.0f);
      //  ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-200.0f, -300.0f, 0.0f));
      //  ModelMatrix = glm::scale(ModelMatrix, glm::vec3(10.0f, 10.0f, 1.0f));
      //  ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
      //  glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
      //  draw_robot();

        int robot_clock = timestamp % 650; // 0 <= airplane_clock <= 719 
        if (robot_clock <= 360) {
            ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-200.0f, -300.0f, 0.0f));
            ModelMatrix = glm::translate(ModelMatrix, glm::vec3((float)robot_clock,
                0.001f * (1-sinf(robot_clock * TO_RADIAN)), 0.0f));
            ModelMatrix = glm::scale(ModelMatrix, glm::vec3(10.0f, 10.0f, 1.0f));
            ModelMatrix = glm::rotate(ModelMatrix, 0.5f*rotation_angle_robot, glm::vec3(0.0f, 0.0f, 1.0f));
            
           
        }
        else {
            ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(300.0f, -300.0f, 0.0f));
            ModelMatrix = glm::translate(ModelMatrix, glm::vec3((float)-robot_clock,
                0.001f * (1 - sinf(-robot_clock * TO_RADIAN)), 0.0f));
            ModelMatrix = glm::scale(ModelMatrix, glm::vec3(10.0f, 10.0f, 1.0f));
            ModelMatrix = glm::rotate(ModelMatrix, 0.5f * rotation_angle_robot, glm::vec3(0.0f, 0.0f, 1.0f));

 
        }

        ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
        glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
        draw_robot();

    }
    if (timestamp < 800) {
        int airplane_clock = timestamp % 820; 
        if (airplane_clock <= 360) {
            ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(AIRPLANE_ROTATION_RADIUS, 200.0f, 0.0f));
            ModelMatrix = glm::rotate(ModelMatrix, airplane_clock * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
            ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-AIRPLANE_ROTATION_RADIUS, 0.0f, 0.0f));
        }
        else {
            ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-AIRPLANE_ROTATION_RADIUS, 300.0f, 0.0f));
            ModelMatrix = glm::rotate(ModelMatrix, -(airplane_clock)*TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
            ModelMatrix = glm::translate(ModelMatrix, glm::vec3(AIRPLANE_ROTATION_RADIUS, 0.0f, 0.0f));

            if (airplane_clock <= 560)
                airplane_s_factor = (airplane_clock - 360.0f) / 180.0f + 1.0f;
            else
                airplane_s_factor = -(airplane_clock - 540.0f) / 180.0f + 2.0f;
            ModelMatrix = glm::scale(ModelMatrix, glm::vec3(airplane_s_factor, airplane_s_factor, 1.0f));

        }

        ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
        glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
        draw_airplane();

    }

    if (timestamp > 800 && timestamp<1200) {
        ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-300.0f, 0.0f, 0.0f));
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3((float)house_clock,
            100.0f * sinf(house_clock * TO_RADIAN), 0.0f));
        ModelMatrix = glm::scale(ModelMatrix, glm::vec3(scaling_cake1,scaling_cake1, 1.0f));
        ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
        glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
        draw_cake();
    }
    else if (timestamp > 1200 && timestamp < 1600) {
        ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-300.0f, 0.0f, 0.0f));
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3((float)house_clock,
            100.0f * sinf(house_clock * TO_RADIAN), 0.0f));
        ModelMatrix = glm::scale(ModelMatrix, glm::vec3(scaling_cake2, scaling_cake2, 1.0f));
        ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
        glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
        draw_cake();
    }
    
 //   if(timestamp>=1600 ) {
     //   ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
      //  glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
       // draw_airplane();
  //      ModelMatrix = glm::scale(ModelMatrix, glm::vec3(2.0f, 2.0f, 1.0f));
   //     ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
    //    glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
     //   draw_cake();

 //   }
    int shirt_clock = timestamp % 360;
    if (timestamp < 800) {
        Model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        Model = glm::translate(Model, glm::vec3(-300.0f, 300.0f, 0.0f));
        Model = glm::scale(Model, glm::vec3(3.0f, 3.0f, 1.0f));
        Model = glm::translate(Model, glm::vec3(100.0f, (shirt_clock % 50)*0.1f, 0.0f));
        ModelViewProjectionMatrix = ViewProjectionMatrix * Model;
        glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
        draw_shirt();

        
        Model = glm::scale(glm::mat4(1.0f), glm::vec3(3.0f,-3.0f, 1.0f));
        Model = glm::translate(Model, glm::vec3(-100.0f, -90.0f, 0.0f));
        Model = glm::translate(Model, glm::vec3(100.0f, (shirt_clock % 50) * 0.1f, 0.0f));
        ModelViewProjectionMatrix = ViewProjectionMatrix * Model;
        glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
        draw_shirt();

        Model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        Model = glm::translate(Model, glm::vec3(-350.0f, 300.0f, 0.0f));
        Model = glm::scale(Model, glm::vec3(3.0f, 3.0f, 1.0f));
        Model = glm::translate(Model, glm::vec3(100.0f, (shirt_clock % 50) * 0.1f, 0.0f));
        ModelViewProjectionMatrix = ViewProjectionMatrix * Model;
        glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
        draw_shirt();


        Model = glm::scale(glm::mat4(1.0f), glm::vec3(3.0f, -3.0f, 1.0f));
        Model = glm::translate(Model, glm::vec3(-117.0f, -90.0f, 0.0f));
        Model = glm::translate(Model, glm::vec3(100.0f, (shirt_clock % 50) * 0.1f, 0.0f));
        ModelViewProjectionMatrix = ViewProjectionMatrix * Model;
        glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
        draw_shirt();

        Model = glm::translate(glm::mat4(1.0f), glm::vec3(40.0f, 580.0f, 0.0f));
        Model = glm::scale(Model, glm::vec3(3.0f, 3.0f, 1.0f));
        Model = glm::rotate(Model, -90.0f * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
        Model = glm::translate(Model, glm::vec3(100.0f, (shirt_clock % 50)*0.1f, 0.0f));
        ModelViewProjectionMatrix = ViewProjectionMatrix * Model;
        glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
        draw_shirt();

        Model = glm::translate(glm::mat4(1.0f), glm::vec3(-80.0f, -20.0f, 0.0f));
        Model = glm::scale(Model, glm::vec3(3.0f, 3.0f, 1.0f));
        Model = glm::rotate(Model, 90.0f * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
        Model = glm::translate(Model, glm::vec3(100.0f, (shirt_clock % 50) * 0.1f, 0.0f));
        ModelViewProjectionMatrix = ViewProjectionMatrix * Model;
        glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
        draw_shirt();

        //   Model = glm::rotate(Model, (cocktail_clock)*TO_RADIAN, glm::vec3(0.0f, 1.0f, 1.0f));
        //   ModelViewProjectionMatrix = ViewProjectionMatrix * Model;
        //   glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
        //   draw_shirt();

         //  Model = glm::scale(Model, glm::vec3(-2.0f, -2.0f, 1.0f));
          // Model = glm::rotate(Model, -(cocktail_clock)*TO_RADIAN, glm::vec3(-1.0f, -1.0f, 1.0f));
          // ModelViewProjectionMatrix = ViewProjectionMatrix * Model;
          // glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
          // draw_shirt();
    }



    int hat_clock = timestamp % 720;


    if (timestamp < 800) {

        ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-HAT_ROTATION_RADIUS + 600.0f, 240.0f, 0.0f));
        ModelMatrix = glm::rotate(ModelMatrix, -(hat_clock)*TO_RADIAN * 5.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(HAT_ROTATION_RADIUS * 0.1f, 50.0f, 0.0f));
        ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
        glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
        draw_hat();


        ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-HAT_ROTATION_RADIUS + 600.0f, 240.0f, 0.0f));
        ModelMatrix = glm::rotate(ModelMatrix, -(hat_clock)*TO_RADIAN * 5.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(HAT_ROTATION_RADIUS * 0.1f * 0.5f, 50.0f * 0.5f, 0.0f));
        ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
        glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
        draw_hat();


        ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-HAT_ROTATION_RADIUS + 600.0f, 240.0f, 0.0f));
        ModelMatrix = glm::rotate(ModelMatrix, -(hat_clock + 10) * TO_RADIAN * 5.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(HAT_ROTATION_RADIUS * 0.1f, 50.0f, 0.0f));
        ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
        glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
        draw_hat();


        ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-HAT_ROTATION_RADIUS + 600.0f, 240.0f, 0.0f));
        ModelMatrix = glm::rotate(ModelMatrix, -(hat_clock + 10) * TO_RADIAN * 5.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(HAT_ROTATION_RADIUS * 0.1f * 0.5f, 50.0f * 0.5f, 0.0f));
        ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
        glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
        draw_hat();

        ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-HAT_ROTATION_RADIUS + 600.0f, 240.0f, 0.0f));
        ModelMatrix = glm::rotate(ModelMatrix, -(hat_clock + 20) * TO_RADIAN * 5.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(HAT_ROTATION_RADIUS * 0.1f, 50.0f, 0.0f));
        ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
        glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
        draw_hat();


        ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-HAT_ROTATION_RADIUS + 600.0f, 240.0f, 0.0f));
        ModelMatrix = glm::rotate(ModelMatrix, -(hat_clock + 20) * TO_RADIAN * 5.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(HAT_ROTATION_RADIUS * 0.1f * 0.5f, 50.0f * 0.5f, 0.0f));
        ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
        glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
        draw_hat();

        ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-HAT_ROTATION_RADIUS + 600.0f, 240.0f, 0.0f));
        ModelMatrix = glm::rotate(ModelMatrix, -(hat_clock + 30) * TO_RADIAN * 5.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(HAT_ROTATION_RADIUS * 0.1f, 50.0f, 0.0f));
        ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
        glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
        draw_hat();


        ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-HAT_ROTATION_RADIUS + 600.0f, 240.0f, 0.0f));
        ModelMatrix = glm::rotate(ModelMatrix, -(hat_clock + 30) * TO_RADIAN * 5.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(HAT_ROTATION_RADIUS * 0.1f * 0.5f, 50.0f * 0.5f, 0.0f));
        ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
        glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
        draw_hat();


        ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-HAT_ROTATION_RADIUS + 600.0f, 240.0f, 0.0f));
        ModelMatrix = glm::rotate(ModelMatrix, -(hat_clock + 40) * TO_RADIAN * 5.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(HAT_ROTATION_RADIUS * 0.1f, 50.0f, 0.0f));
        ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
        glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
        draw_hat();


        ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-HAT_ROTATION_RADIUS + 600.0f, 240.0f, 0.0f));
        ModelMatrix = glm::rotate(ModelMatrix, -(hat_clock + 40) * TO_RADIAN * 5.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(HAT_ROTATION_RADIUS * 0.1f * 0.5f, 50.0f * 0.5f, 0.0f));
        ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
        glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
        draw_hat();

        ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-HAT_ROTATION_RADIUS + 600.0f, 240.0f, 0.0f));
        ModelMatrix = glm::rotate(ModelMatrix, -(hat_clock + 50) * TO_RADIAN * 5.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(HAT_ROTATION_RADIUS * 0.1f, 50.0f, 0.0f));
        ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
        glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
        draw_hat();


        ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-HAT_ROTATION_RADIUS + 600.0f, 240.0f, 0.0f));
        ModelMatrix = glm::rotate(ModelMatrix, -(hat_clock + 50) * TO_RADIAN * 5.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(HAT_ROTATION_RADIUS * 0.1f * 0.5f, 50.0f * 0.5f, 0.0f));
        ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
        glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
        draw_hat();


        ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-HAT_ROTATION_RADIUS + 600.0f, 240.0f, 0.0f));
        ModelMatrix = glm::rotate(ModelMatrix, -(hat_clock + 60) * TO_RADIAN * 5.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(HAT_ROTATION_RADIUS * 0.1f, 50.0f, 0.0f));
        ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
        glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
        draw_hat();


        ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-HAT_ROTATION_RADIUS + 600.0f, 240.0f, 0.0f));
        ModelMatrix = glm::rotate(ModelMatrix, -(hat_clock + 60) * TO_RADIAN * 5.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(HAT_ROTATION_RADIUS * 0.1f * 0.5f, 50.0f * 0.5f, 0.0f));
        ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
        glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
        draw_hat();

    }
    


    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27: // ESC key
        glutLeaveMainLoop(); // Incur destuction callback for cleanups.
        break;
    }
}

void mouse(int button, int state, int x, int y) {
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
        leftbuttonpressed = 1;
    else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP))
        leftbuttonpressed = 0;
}

void motion(int x, int y) {
    if (leftbuttonpressed) {
        centerx = x - win_width / 2.0f, centery = (win_height - y) - win_height / 2.0f;
        glutPostRedisplay();
    }


}




void reshape(int width, int height) {
    win_width = width, win_height = height;

    glViewport(0, 0, win_width, win_height);
    ProjectionMatrix = glm::ortho(-win_width / 2.0, win_width / 2.0,
        -win_height / 2.0, win_height / 2.0, -1000.0, 1000.0);
    ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;

    update_axes();
    update_line();

    glutPostRedisplay();
}

void cleanup(void) {
    glDeleteVertexArrays(1, &VAO_axes);
    glDeleteBuffers(1, &VBO_axes);

    glDeleteVertexArrays(1, &VAO_line);
    glDeleteBuffers(1, &VBO_line);

    glDeleteVertexArrays(1, &VAO_airplane);
    glDeleteBuffers(1, &VBO_airplane);

    // Delete others here too!!!
}

void register_callbacks(void) {
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutReshapeFunc(reshape);
    glutTimerFunc(10, timer, 0);
    glutCloseFunc(cleanup);
   
}


void prepare_shader_program(void) {
    ShaderInfo shader_info[3] = {
       { GL_VERTEX_SHADER, "Shaders/simple.vert" },
       { GL_FRAGMENT_SHADER, "Shaders/simple.frag" },
       { GL_NONE, NULL }
    };

    h_ShaderProgram = LoadShaders(shader_info);
    glUseProgram(h_ShaderProgram);

    loc_ModelViewProjectionMatrix = glGetUniformLocation(h_ShaderProgram, "u_ModelViewProjectionMatrix");
    loc_primitive_color = glGetUniformLocation(h_ShaderProgram, "u_primitive_color");
}

void initialize_OpenGL(void) {
    glEnable(GL_MULTISAMPLE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glClearColor(250 / 255.0f, 128 / 255.0f, 114 / 255.0f, 1.0f);
    ViewMatrix = glm::mat4(1.0f);
}

void prepare_scene(void) {
    prepare_axes();
    prepare_line();
    prepare_airplane();
    prepare_shirt();
    prepare_house();
    prepare_car();
    prepare_cocktail();
    prepare_car2();
    prepare_hat();
    prepare_sword();
    prepare_window();
    prepare_floor();
    prepare_room_line();
    prepare_robot();
}

void initialize_renderer(void) {
    register_callbacks();
    prepare_shader_program();
    initialize_OpenGL();
    prepare_scene();
}




void initialize_glew(void) {
    GLenum error;

    glewExperimental = GL_TRUE;

    error = glewInit();
    if (error != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(error));
        exit(-1);
    }
    fprintf(stdout, "*********************************************************\n");
    fprintf(stdout, " - GLEW version supported: %s\n", glewGetString(GLEW_VERSION));
    fprintf(stdout, " - OpenGL renderer: %s\n", glGetString(GL_RENDERER));
    fprintf(stdout, " - OpenGL version supported: %s\n", glGetString(GL_VERSION));
    fprintf(stdout, "*********************************************************\n\n");
}

void greetings(char* program_name, char messages[][256], int n_message_lines) {
    fprintf(stdout, "**************************************************************\n\n");
    fprintf(stdout, "  PROGRAM NAME: %s\n\n", program_name);
    fprintf(stdout, "    This program was coded for CSE4170 students\n");
    fprintf(stdout, "      of Dept. of Comp. Sci. & Eng., Sogang University.\n\n");

    for (int i = 0; i < n_message_lines; i++)
        fprintf(stdout, "%s\n", messages[i]);
    fprintf(stdout, "\n**************************************************************\n\n");

    initialize_glew();
}

#define N_MESSAGE_LINES 1
void main(int argc, char* argv[]) {
    char program_name[64] = "Sogang CSE4170 2DObjects_GLSL_3.0.1.3";
    char messages[N_MESSAGE_LINES][256] = {
       "    - Keys used: 'ESC' "
    };

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_MULTISAMPLE);
    glutInitWindowSize(1200 * 0.95, 800 * 0.95);
    glutInitContextVersion(3, 3);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow(program_name);

    greetings(program_name, messages, N_MESSAGE_LINES);
    initialize_renderer();

    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    glutMainLoop();
}

