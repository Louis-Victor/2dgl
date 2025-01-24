#ifndef __SHADER__
#define __SHADER__

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader{
    private:
        unsigned int ID;

    public:
        Shader(const char** shaderList, const unsigned int shaderCount);
        // use shader
        void use();
        // uniform utils
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        // get shader
        unsigned int get();
};

#endif
