#include <GL/glew.h>
#include <string>
#include <iostream>
#include <stb_image.h>
#include "glHelper.h"
#include "Texture.h"
#include "Shader.h"

const char* textureDir = "resources/textures/";

Texture::Texture(const char* filename, std::string m_textureName) : Texture::Texture(filename, m_textureName, false){}

Texture::Texture(const char* filename, std::string m_textureName, bool hasAlpha) : Texture::Texture(filename, m_textureName, hasAlpha, false){}

Texture::Texture(const char* filename, std::string m_textureName, bool hasAlpha, bool flip) : Texture::Texture(filename, m_textureName, hasAlpha, flip, 0){}

Texture::Texture(const char* filename, std::string m_textureName, bool hasAlpha, bool flip, unsigned int m_textureId) : Texture::Texture(filename, m_textureName, hasAlpha, flip, m_textureId, GL_REPEAT){}

/*
 * GL_REPEAT: The default behavior for textures. Repeats the texture image.
 * GL_MIRRORED_REPEAT: Same as GL_REPEAT but mirrors the image with each repeat.
 * GL_CLAMP_TO_EDGE: Clamps the coordinates between 0 and 1. The result is that higher coordinates become clamped to the edge, resulting in a stretched edge pattern.
 * GL_CLAMP_TO_BORDER: Coordinates outside the range are now given a user-specified border color
*/
Texture::Texture(const char* filename, std::string m_textureName, bool hasAlpha, bool flip, unsigned int m_textureId,GLint wrapParam) : textureId(m_textureId), textureName(m_textureName){
    // GL texture object
    glGenTextures(1,&ID);
    glBindTexture(GL_TEXTURE_2D,ID);

    // texture param
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapParam);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapParam);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
            GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load image
    std::string imagePath = std::string(textureDir) + std::string(filename);

    if(flip) stbi_set_flip_vertically_on_load(true);
    else stbi_set_flip_vertically_on_load(false);

    unsigned char* data = stbi_load(imagePath.c_str(),&width,&height,&nChannels,0);
    if(data){
        glTexImage2D(GL_TEXTURE_2D,0, 
                hasAlpha ? GL_RGBA : GL_RGB,
                width,height,0, 
                hasAlpha ? GL_RGBA : GL_RGB, 
                GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        std::cout << "Failed to load " << imagePath << "\n";
    }
    // free image from memory
    stbi_image_free(data);

    std::cout << "Texture " << filename << " done\n";
}

void Texture::setShaderId(Shader shader){
    shader.setInt(textureName.c_str(),textureId);
}

void Texture::use(){
    glActiveTexture(GL_TEXTURE0+textureId);
    glBindTexture(GL_TEXTURE_2D,ID);
}
