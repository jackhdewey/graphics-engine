#include "Cube.hpp"

Cube::Cube() : Object() {
    MakeCube();
}

void Cube::MakeCube(){

    // Vertices in the cube
    std::vector<float> m_vertices = {
            -10.0f, -10.0f,  10.0f,
            10.0f, -10.0f,  10.0f,
            10.0f,  10.0f,  10.0f,
            -10.0f,  10.0f,  10.0f,
            // back vertices
            -10.0f, -10.0f, -10.0f,
            10.0f, -10.0f, -10.0f,
            10.0f,  10.0f, -10.0f,
            -10.0f,  10.0f, -10.0f,
    };

    // Three indices in a row indicate a triangle.
    std::vector<unsigned int> m_indices = {
            // front face
            0, 1, 2,
            2, 3, 0,
            // right face
            1, 5, 6,
            6, 2, 1,
            // back face
            7, 6, 5,
            5, 4, 7,
            // left face
            4, 0, 3,
            3, 7, 4,
            // bottom face
            4, 5, 1,
            1, 0, 4,
            // top face
            3, 2, 6,
            6, 7, 3
    };

    // Create a buffer and set the stride of information
    m_vertexBufferLayout.CreatePositionBufferLayout(m_vertices.size() * sizeof(GL_FLOAT),
                                                    m_indices.size() * sizeof(GL_FLOAT),
                                                    m_vertices.data(),
                                                    m_indices.data());
}