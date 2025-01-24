#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include  "glHelper.h"
#include <Shader.h>

Shader::Shader(const char** shaderList, const unsigned int shaderCount){
    unsigned int shaders[shaderCount];
    for(unsigned int i=0;i<shaderCount;i++){
        shaders[i] = compileShaderFromSource(shaderList[i]);
    }

    ID = glCreateProgram();
    for(unsigned int i=0;i<shaderCount;i++){
        glAttachShader(ID,shaders[i]);
    }
    glLinkProgram(ID);

    // Check for errors
    int success;
    char infoLog[512];
    glGetProgramiv(ID,GL_LINK_STATUS,&success);
    if(!success){
        glGetProgramInfoLog(ID,512,NULL,infoLog);
        std::cout << "ERROR:SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << "\n";
    }

    for(unsigned int i=0;i<shaderCount;i++){
        glDeleteShader(shaders[i]);
        std::cout << "Shader " << shaderList[i] << " done\n";
    }
}

void Shader::use(){
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

unsigned int Shader::get(){
    return ID;
}
