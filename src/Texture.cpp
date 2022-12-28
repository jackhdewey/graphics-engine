#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif

#include "Texture.hpp"

#include <stdio.h>
#include <string.h>

#include <fstream>
#include <iostream>
#include <glad/glad.h>
#include <memory>

Texture::Texture(){

}

Texture::~Texture(){
	// Remove our texture from the GPU
	glDeleteTextures(1, &m_textureID);

    // Delete texture locally
    if (m_image != nullptr) {
        delete m_image;
    }
}

void Texture::LoadTexture(const std::string filepath){

    // Load our color data from a .ppm file
    m_image = new Image(filepath);
    m_image->LoadPPM(true);

    glEnable(GL_TEXTURE_2D); 
	// Generate a buffer for our texture
    glGenTextures(1, &m_textureID);
    // Bind to the target
    glBindTexture(GL_TEXTURE_2D, m_textureID);
	// Set up some information about our textures.
	// GL_TEXTURE_MIN_FILTER - How texture filters (linearly, etc.)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	// Wrap mode describes what to do if we go outside the boundaries of texture.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
	// Send image data to OpenGL
	glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB,
                 m_image->GetWidth(),
                 m_image->GetHeight(),
                 0,
                 GL_RGB,
                 GL_UNSIGNED_BYTE,
                 m_image->GetPixelDataPtr()); // Here is the raw pixel data
    // Generate a mipmap
    glGenerateMipmap(GL_TEXTURE_2D);
	// We are done with our texture data, so we can unbind.
	glBindTexture(GL_TEXTURE_2D, 0);
}

// Select the active texture slot that we want to occupy
void Texture::Bind(unsigned int slot) const{
    glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0+slot);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::Unbind(){
	glBindTexture(GL_TEXTURE_2D, 0);
}


