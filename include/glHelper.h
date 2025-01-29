#ifndef __GLHELPER__
#define __GLHELPER__
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#include "Shader.h"

//#include <GLES2/gl2.h>
//#include <EGL/egl.h>

extern float xoffset;
extern float yoffset;

extern Shader shader;

// print file and line number
void  pLine(const std::string f, const int l);

// Window resize function
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// GLFW set up function
bool setUpGL();

std::string importShader(const char* filename);

unsigned int compileShader(const char* sourceCode, GLenum shaderType);

unsigned int compileShaderFromSource(const char* filename);

bool createShaderProgram(unsigned int& program, const unsigned int* shaders, const unsigned int  shaderCount);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

#endif
