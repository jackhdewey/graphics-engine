/** @file VertexBufferLayout.hpp
 *  @brief Sets up a variety of Vertex Buffer Object (VBO) layouts.
 *
 *
 *  @author Mike
 *  @bug No known bugs.
 */

#ifndef VERTEX_BUFFER_LAYOUT_HPP
#define VERTEX_BUFFER_LAYOUT_HPP

#include "glad/glad.h"

/**
 * THis class represents the Vertex Buffer Object (VBO) for an object
 */
class VertexBufferLayout{ 
public:
    /**
     * Constructor
     */
    VertexBufferLayout();

    /**
     * Destructor
     */
    ~VertexBufferLayout();

    /**
     * Bind to this buffer in OpenGL when rendering
     */
    void Bind();

    /**
     * Unbind this buffer in OpenGL
     */
    void Unbind();

    /**
     * Creates vertex and index buffer objects using the given data.
     * Format is: x,y,z
     *
     * @param vcount the number of vertices
     * @param icount the number of indices
     * @param vdata pointer to an array of data for vertices
     * @param idata pointer to an array of data for indices
     */
    void CreatePositionBufferLayout(unsigned int vcount, unsigned int icount, float* vdata, unsigned int* idata);

    /**
     * Creates vertex and index buffer objects, including texture data.
     * Format is: x,y,z,s,t
     *
     * @param vcount
     * @param icount
     * @param vdata
     * @param idata
     */
    void CreateTextureBufferLayout(unsigned int vcount, unsigned int icount, float* vdata, unsigned int* idata);

    /**
     * Creates vertex and index buffer objects including texture, normal, tangent and bitangent data
     * Format is x,y,z,s,t,xn,yn,zn,t_x, t_y, t_z, b_x, b_y, b_z
     *
     * @param vcount
     * @param icount
     * @param vdata
     * @param idata
     */
    void CreateNormalBufferLayout(unsigned int vcount,unsigned int icount, float* vdata, unsigned int* idata);

private:
    // Vertex Array Object
    GLuint m_VAOId;
    // Vertex Buffer
    GLuint m_vertexBufferObject;
    // Index Buffer
    GLuint m_indexBufferObject;
    // Stride of data (how do I get to the next vertex)
    unsigned int m_stride{0};
};


#endif
