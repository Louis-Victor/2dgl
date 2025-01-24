#ifndef __TEXTURE__
#define __TEXTURE__

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "glHelper.h"
#include "Shader.h"

class Texture{
    private:
        unsigned int ID;
        unsigned int textureId; // shader id
        std::string textureName; // shader var. name
        // image parameters
        int width, height, nChannels;

    public:
        Texture(const char* filename, std::string m_textureName);
        Texture(const char* filename, std::string m_textureName, bool hasAlpha);
        Texture(const char* filename, std::string m_textureName, bool hasAlpha, bool flip);
        Texture(const char* filename, std::string m_textureName, bool hasAlpha, bool flip, unsigned int m_textureId);
        Texture(const char* filename, std::string m_textureName, bool hasAlpha, bool flip, unsigned int m_textureId,GLint wrapParam);

        void use();

        void setShaderId(Shader shader);
};

#endif
