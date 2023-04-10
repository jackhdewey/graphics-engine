/** @file Object.hpp
 *  @brief
 *
 *  @author Mike
 *  @bug No known bugs.
 */

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <glad/glad.h>

#include <vector>
#include <string>

#include "VertexBufferLayout.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "Geometry.hpp"
#include "OBJModel.hpp"

#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

/**
 * An abstraction to create 3D objects
 */
class Object {

public:

    // Constructor
    Object();
    // Destructor
    ~Object();
    // Load an object file
    void LoadObjectModel(OBJModel* model);
    // Return a boolean indicating whether this object has a texture
    bool HasTexture();
    // Load a texture
    void LoadTexture(std::string fileName);
    // Draw the object
    virtual void Render();

protected:

    // Helper method for when we are ready to draw or update our object
    void Bind();

    // Geometry data for this object
    Geometry m_geometry;
    // Vertex buffer for this object
    VertexBufferLayout m_vertexBufferLayout;
    // Stores the object's texture data
    Texture m_textureDiffuse;
    // Indicates whether this object has a texture
    bool m_hasTexture;

};

#endif
