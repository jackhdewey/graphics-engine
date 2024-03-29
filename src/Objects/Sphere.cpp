#include "Objects/Sphere.hpp"

/**
 * Calls the initialization routine
 */
Sphere::Sphere() : Object() {
    Init();
}

/**
 * Algorithm for rendering a sphere
 * The algorithm was obtained here: http://learningwebgl.com/blog/?p=1253
 */
void Sphere::Init(){
    unsigned int latitudeBands = 30;
    unsigned int longitudeBands = 30;
    float radius = 1.0f;
    double PI = 3.14159265359;

    for (unsigned int latNumber = 0; latNumber <= latitudeBands; latNumber++){
        float theta = latNumber * PI / latitudeBands;
        float sinTheta = sin(theta);
        float cosTheta = cos(theta);

        for (unsigned int longNumber = 0; longNumber <= longitudeBands; longNumber++){
            float phi = longNumber * 2 * PI / longitudeBands;
            float sinPhi = sin(phi);
            float cosPhi = cos(phi);

            float x = cosPhi * sinTheta;
            float y = cosTheta;
            float z = sinPhi * sinTheta;
            // Why is this "1-" Think about the range of texture coordinates
            float u = 1 - ((float)longNumber / (float)longitudeBands);
            float v = 1 - ((float)latNumber / (float)latitudeBands);

            // Setup geometry
            m_geometry.AddVertex5f(radius*x,radius*y,radius*z,u,v);   // Position
        }
    }

    // Now that we have all of our vertices generated,
    // we need to generate our indices for our index element buffer.
    // This diagram shows it nicely visually
    // http://learningwebgl.com/lessons/lesson11/sphere-triangles.png
    for (unsigned int latNumber1 = 0; latNumber1 < latitudeBands; latNumber1++){
        for (unsigned int longNumber1 = 0; longNumber1 < longitudeBands; longNumber1++){
            unsigned int first = (latNumber1 * (longitudeBands + 1)) + longNumber1;
            unsigned int second = first + longitudeBands + 1;
            m_geometry.AddIndex(first);
            m_geometry.AddIndex(second);
            m_geometry.AddIndex(first+1);

            m_geometry.AddIndex(second);
            m_geometry.AddIndex(second+1);
            m_geometry.AddIndex(first+1);
        }
    }

    // Generate a simple 'array of bytes' that contains everything for our buffer to work with.
    m_geometry.Gen();

    // Create a buffer and set the stride of information
    m_vertexBufferLayout.CreateNormalBufferLayout(m_geometry.GetBufferDataSize(),
                                                  m_geometry.GetIndicesSize(),
                                                  m_geometry.GetBufferDataPtr(),
                                                  m_geometry.GetIndicesDataPtr());
}
