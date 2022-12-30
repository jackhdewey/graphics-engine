/** @file Texture.hpp
 *  @brief Loads an image and creates an OpenGL texture on the GPU..
 *  
 *  More...
 *
 *  @author Mike
 *  @bug No known bugs.
 */
#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Image.hpp"

#include <glad/glad.h>
#include <string>

class Texture{
public:
    // Constructor
    Texture();
    // Destructor
    ~Texture();
	// Loads the texture file and creates VBO on GPU
    void LoadTexture(const std::string filepath);
	// Bind to the specified texture slot - by default 0
    void Bind(unsigned int slot = 0) const;
    // Unbind texture
    void Unbind();
private:
    // Unique ID for this texture
    GLuint m_textureID;
    // Raw image data for this texture
    Image* m_image;
};

#endif