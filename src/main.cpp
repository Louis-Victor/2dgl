#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "stb_image.h"

// GLFW & GLEW include
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include </usr/include/GLFW/glfw3.h>
//#include <GLES2/gl2.h>
//#include <EGL/egl.h>
// OpenGL Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glHelper.h"
#include "Window.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Geometry.h"


using namespace std;
const float screen = 1920.0f/1080.0f;


const unsigned int shaderCount = 2;
const char* shaderList[shaderCount] = {
    "main.vert",
    "main.frag"
};


int main(int argc, char** argv){

    glfwTerminate();

    // Starts glfw
    if(setUpGL()){
        cout << "INIT SUCCESSFUL\n"; 
    }else{
        cout << "FAILED INIT\n"; 
        return 1;
    }

    // Create Window object
    // 1920x1080
    Window mainWindow(800*screen,800,"mainWindow");
    cout << mainWindow.getWidth() << "x" << mainWindow.getHeight() << "\n";
    if(mainWindow.getWindow() == NULL){
        glfwTerminate();
        return 1;
    }

    // Initiate GLEW
    if (glewInit() != GLEW_OK) {
        cerr << "Failed to initialize GLEW\n";
        return 1;
    }
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    LineVec lines;
    for(int i=0;i<3;i++){
        Line aline(Point(glm::vec2(0.0f,0.0f)),Point(glm::vec2((float)(10-i),0.0f)));
        lines.add(aline);
    }
    lines.print();
    lines.sort();
    lines.print();
    return 1;


    //init random numbers
    srand(time(nullptr));

    Line line1(Point(),Point(glm::vec2(0.25f * mainWindow.getWidthF(),0.25f * mainWindow.getHeightF())));
    Line line2(Point(),Point(glm::vec2(0.25f * mainWindow.getWidthF(),-0.25f * mainWindow.getHeightF())));

    
    line1.print();
    line1.getCenter().print();
    line2.print();
    line2.getCenter().print();

    // point(s) to make a triangle
    const int numPoints = 4;
    //float points[6*numPoints];
    float points[] = {
        // x    // y    // r    // g    // b    // a
         0.0f,    0.5f,   1.0f,   0.0f,   0.0f,   1.0f,
        -0.5f,   -0.5f,   0.0f,   1.0f,   0.0f,   1.0f,
         0.5f,   -0.5f,   0.0f,   0.0f,   1.0f,   1.0f,
         0.0f,    0.5f,   1.0f,   0.0f,   0.0f,   1.0f
    };

   /* for(int i=0;i<numPoints;i++){
        for(int j=0;j<5;j++){
            if(j<2)
                points[i*6+j] = ((float)(2.0*rand()-RAND_MAX))/(float)(RAND_MAX);
            else
                points[i*6+j] = (float)(rand())/(float)(RAND_MAX);
        }
        points[i*6+5] = 1.0f;
    }

    
    for(int i=0;i<numPoints;i++){
        for(int j=0;j<6;j++){
            cout<< points[i*6+j] << " | ";
        }
        cout << "\n";
    }*/

    for(int i = 0; i<numPoints; i++){
        points[i*6] *= mainWindow.getWidthF()/2;
        points[i*6+1] *= mainWindow.getHeightF()/2;
    }
    for(int i=0;i<numPoints;i++){
        for(int j=0;j<6;j++){
            cout<< points[i*6+j] << " | ";
        }
        cout << "\n";
    }

    // Set up buffers
    unsigned int VAO, VBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    /*glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    //  use  points from here
    glBufferData(GL_ARRAY_BUFFER,sizeof(points),points,GL_STATIC_DRAW);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // end of used points
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glEnableVertexAttribArray(0);*/

    Shader shader(shaderList,shaderCount);


    // matrix transformations
    // to world coord
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model,glm::vec3(0.0f,0.0f,0.0f));
    //model = glm::scale(model,glm::vec3(800.0f*screen, 800.0f, 1.0f));

    // view matrix
    Camera camera;

    // projection matrix
    glm::mat4 projection;

    //projection = glm::mat4(1.0f);

    unsigned int modelLoc = glGetUniformLocation(shader.get(),"model");
    unsigned int viewLoc = glGetUniformLocation(shader.get(),"view");
    unsigned int projectionLoc = glGetUniformLocation(shader.get(),"projection");

    // deltaTime
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    //float xlastOff = xoffset;
    //float ylastOff = yoffset;

    /* Render loop */
    bool isFill = true;
    bool spaceFlag = false;

    //line.bind(VAO,VBO);

    std::cout << "Entering draw loop\n";
    // Check if window has closed
    while(!mainWindow.isClosed()){
        // calculate deltaTime
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;


        // input processing
        if(mainWindow.getInput(GLFW_KEY_ESCAPE) == GLFW_PRESS){
            mainWindow.close();
            cout << "Closed\n";
        }
        if(mainWindow.getInput(GLFW_KEY_SPACE) == GLFW_RELEASE && spaceFlag){
            spaceFlag = false;
            if(isFill) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            isFill = !isFill;
        }
        else if(mainWindow.getInput(GLFW_KEY_SPACE) == GLFW_PRESS) spaceFlag = true;

        // camera movement wasd
        if(mainWindow.getInput(GLFW_KEY_W) == GLFW_PRESS){
            camera.processKeyboard(UP,deltaTime);
        }
        if(mainWindow.getInput(GLFW_KEY_S) == GLFW_PRESS){
            camera.processKeyboard(DOWN,deltaTime);
        }
        if(mainWindow.getInput(GLFW_KEY_D) == GLFW_PRESS){
            camera.processKeyboard(RIGHT,deltaTime);
        }
        if(mainWindow.getInput(GLFW_KEY_A) == GLFW_PRESS){
            camera.processKeyboard(LEFT,deltaTime);
        }

        // camera rotation
        /*
        camera.processMouseMovement(xoffset,yoffset);

        if(xoffset == xlastOff) xoffset = 0;
        if(yoffset == ylastOff) yoffset = 0;
        xlastOff  = xoffset;
        ylastOff  = yoffset;
        */

        mainWindow.clear(0.2f,0.3f,0.3f);

        // use shader
        shader.use();

        // set transforms
        // Model matrices
        //model = glm::rotate(glm::mat4(1.0f),(float)glfwGetTime(),glm::vec3(0.0f,0.0f,1.0f));
        //cout << glfwGetTime() << "\n";
        model = glm::mat4(1.0f);
        // view matrix
        glm::mat4 view = glm::mat4(1.0f);
        
        //projection matrix
        float w = mainWindow.getWidthF();
        float h = mainWindow.getHeightF();
        projection = glm::ortho(-w/2.0f, w/2.0f, -h/2.0f, h/2.0f, -1.0f, 1.0f);
        glUniformMatrix4fv(modelLoc,1,GL_FALSE,glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc,1,GL_FALSE,glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc,1,GL_FALSE,glm::value_ptr(projection));


        /*cout << "POINT TRANSFORMATIONS\n";
        for(int i=0;i<numPoints;i++){
            glm::vec4 avec = glm::vec4(points[i*6],points[i*6+1],0.0f,0.0f);
            cout << "\t(" << avec.x << ", " << avec.y << ", " << avec.z << ")\n";
            avec = projection * view * model * avec;
            cout << "\t(" << avec.x << ", " << avec.y << ", " << avec.z << ")\n";
            
        }*/


        // draw stuff
        //glBindVertexArray(VAO);
        //glLineWidth(5.0f);
        //glDrawArrays(GL_LINE_STRIP,0,numPoints);
        //glDrawArrays(GL_LINES,0,numPoints);
        //glDrawArrays(GL_POINTS,0,numPoints);
        //glDrawArrays(GL_TRIANGLES,0,3);
        
        line1.draw(VAO,VBO,shader);
        line2.draw(VAO,VBO,shader);

        mainWindow.render();

    }

    // Clean glfw resources
    cout << "Closing GLFW\n";
    glfwTerminate();
    cout << "GLFW Closed\n";

    return 0;
}
