#include "Terrain.hpp"
#include "Image.hpp"

#include <iostream>

Terrain::Terrain(unsigned int xSegs, unsigned int zSegs, std::string fileName) :
        m_xSegments(xSegs), m_zSegments(zSegs) {

    std::cout << "(Terrain.cpp) Constructor called \n";

    // Load up some image data
    Image heightMap(fileName);
    heightMap.LoadPPM(true);

    // Set the height data equal to the grayscale value of the heightmap
    // Because the R,G,B will all be equal in a grayscale image, we can just grab one of the color components.
    // Note: In this case there is a 1-1 mapping between a pixel and a vertex
    // If there are more segments than pixels, you might consider interpolating values

    float scale = 0.2f; // Scales down the values to make the image a bit more flat
    m_heightData = new int[m_xSegments * m_zSegments];

    for (int z = 0; z < m_zSegments; z++) {
        for (int x = 0; x < m_xSegments; x++) {
            m_heightData[z * m_xSegments + x] = heightMap.GetPixelR(z, x) * scale;
        }
    }

    Init();
}

Terrain::~Terrain(){
    // Delete our allocated height map data
    if (m_heightData != nullptr){
        delete m_heightData;
    }
}

void Terrain::Init(){

    // Create the initial grid of vertices
    for (int z = 0; z < m_zSegments; z++) {
        for (int x = 0; x < m_xSegments; x++) {
            float u = 1.0f - ((float) x / (float) m_xSegments);
            float v = 1.0f - ((float) z / (float) m_zSegments);
            m_geometry.AddVertex5f(x, m_heightData[z * m_zSegments + x], z, u, v);
        }
    }

    // Populate indices making up each triangle
    for (int z = 0; z < m_zSegments - 1; z++) {
        for (int x = 0; x < m_zSegments - 1; x++) {
            m_geometry.AddIndex((z * m_zSegments) + x);
            m_geometry.AddIndex((z * m_zSegments) + m_xSegments + x);
            m_geometry.AddIndex((z * m_zSegments) + x + 1);

            m_geometry.AddIndex((z * m_zSegments) + x + 1);
            m_geometry.AddIndex((z * m_zSegments) + m_xSegments + x);
            m_geometry.AddIndex((z * m_zSegments) + m_xSegments + x + 1);
        }
    }

    // Generate a simple 'array of bytes' that contains everything for our buffer to work with.
    m_geometry.Gen();

    // Create a buffer and set the stride of information
    m_vertexBufferLayout.CreateNormalBufferLayout(m_geometry.GetBufferDataSize(), m_geometry.GetIndicesSize(),
                                                  m_geometry.GetBufferDataPtr(), m_geometry.GetIndicesDataPtr());
}

// Loads an image and uses it to set the heights of the terrain.
void Terrain::LoadHeightMap(Image heightMap){

}
