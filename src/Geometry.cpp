#include "Geometry.hpp"
#include <assert.h>
#include <iostream>
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/glm.hpp"

// Constructor
Geometry::Geometry(){

}

// Destructor
Geometry::~Geometry(){

}

/**
 * Adds a vertex and associated texture coordinates and normals
 * Generates default values for tangent and bi-tangent
 */
void Geometry::AddVertex5f(float x, float y, float z, float s, float t) {
    m_vertexPositions.push_back(x);
    m_vertexPositions.push_back(y);
    m_vertexPositions.push_back(z);
    // Add texture coordinates
    m_textureCoords.push_back(s);
    m_textureCoords.push_back(t);
    // Push back placeholders for m_normals
    m_normals.push_back(0.0f);
    m_normals.push_back(0.0f);
    m_normals.push_back(1.0f);
    // Push back placeholders for tangents
    m_tangents.push_back(0.0f);
    m_tangents.push_back(0.0f);
    m_tangents.push_back(1.0f);
    // push back placeholders for bi-tangents
    m_biTangents.push_back(0.0f);
    m_biTangents.push_back(0.0f);
    m_biTangents.push_back(1.0f);
}

/**
 * Adds a vertex and associated texture coordinates
 * Generates default values for normal, tangent, and bi-tangent
 */
void Geometry::AddVertex8f(float x, float y, float z, float s, float t, float xn, float yn, float zn){
	m_vertexPositions.push_back(x);
	m_vertexPositions.push_back(y);
	m_vertexPositions.push_back(z);
    // Add texture coordinates
	m_textureCoords.push_back(s);
	m_textureCoords.push_back(t);
	// Add normal vectors
	m_normals.push_back(xn);
	m_normals.push_back(yn);
	m_normals.push_back(zn);
	// Push back placeholders for tangents
	m_tangents.push_back(0.0f);
	m_tangents.push_back(0.0f);
	m_tangents.push_back(1.0f);
	// push back placeholders for bi-tangents
	m_biTangents.push_back(0.0f);
	m_biTangents.push_back(0.0f);
	m_biTangents.push_back(1.0f);
}

/**
 * Allows for adding one index at a time manually if you know which vertices are needed to make a triangle.
 *
 * @param i
 */
void Geometry::AddIndex(unsigned int i){
    // Simple bounds check to make sure a valid index is added.
    if(i >= 0 && i <= m_vertexPositions.size()/3){
        m_indices.push_back(i);
    }else{
        std::cout << "(Geometry.cpp) ERROR, invalid index\n";
    }
}

/**
 * Given a set of three vertices, 'assembles' them into a triangle.
 * Effectively, we compute tangents and bi-tangents.
 *
 * @param vert0 index of first vertex
 * @param vert1 index of second vertex
 * @param vert2 index of third vertex
 */
void Geometry::MakeTriangle(unsigned int vert0, unsigned int vert1, unsigned int vert2) {

    // Add these indices to m_indices
	m_indices.push_back(vert0);	
	m_indices.push_back(vert1);	
	m_indices.push_back(vert2);	

	// Look up the vertex positions
	glm::vec3 pos0(m_vertexPositions[vert0*3 +0], m_vertexPositions[vert0*3 + 1], m_vertexPositions[vert0*3 + 2]); 
	glm::vec3 pos1(m_vertexPositions[vert1*3 +0], m_vertexPositions[vert1*3 + 1], m_vertexPositions[vert1*3 + 2]); 
	glm::vec3 pos2(m_vertexPositions[vert2*3 +0], m_vertexPositions[vert2*3 + 1], m_vertexPositions[vert2*3 + 2]); 

	// Look up the texture coordinates
	glm::vec2 tex0(m_textureCoords[vert0*2 +0], m_textureCoords[vert0*2 + 1]); 
	glm::vec2 tex1(m_textureCoords[vert1*2 +0], m_textureCoords[vert1*2 + 1]); 
	glm::vec2 tex2(m_textureCoords[vert2*2 +0], m_textureCoords[vert2*2 + 1]);

    // Look up the normals of each vertex
    glm::vec3 normal1{m_normals[vert0*3+0] ,m_normals[vert0*3+1], m_normals[vert0*3+2]};
    glm::vec3 normal2{m_normals[vert1*3+0] ,m_normals[vert1*3+1], m_normals[vert1*3+2]};
    glm::vec3 normal3{m_normals[vert2*3+0] ,m_normals[vert2*3+1], m_normals[vert2*3+2]};

	// This section is inspired by: https://learnopengl.com/Advanced-Lighting/Normal-Mapping
	glm::vec3 edge0 = pos1 - pos0;
	glm::vec3 edge1 = pos2 - pos0;

	// Find the difference between the two corresponding texture coordinates
	glm::vec2 deltaUV0 = tex1-tex0;
	glm::vec2 deltaUV1 = tex2-tex0;

	float f = 1.0f / (deltaUV0.x * deltaUV1.y - deltaUV1.x * deltaUV0.y);

	glm::vec3 tangent;
	glm::vec3 bitangent;

    // Compute a tangent
	tangent.x = f * (deltaUV1.y * edge0.x - deltaUV0.y * edge1.x);
	tangent.y = f * (deltaUV1.y * edge0.y - deltaUV0.y * edge1.y);
	tangent.z = f * (deltaUV1.y * edge0.z - deltaUV0.y * edge1.z);
	tangent = glm::normalize(tangent);

    // Compute a bi-tangent
	bitangent.x = f * (-deltaUV1.x * edge0.x + deltaUV0.x * edge1.x);
	bitangent.y = f * (-deltaUV1.x * edge0.y + deltaUV0.x * edge1.y);
	bitangent.z = f * (-deltaUV1.x * edge0.z + deltaUV0.x * edge1.z);
	bitangent = glm::normalize(bitangent);
		
	// Add calculated tangent back to m_tangents
	m_tangents[vert0*3+0] = tangent.x; m_tangents[vert0*3+1] = tangent.y; m_tangents[vert0*3+2] = tangent.z;	
	m_tangents[vert1*3+0] = tangent.x; m_tangents[vert1*3+1] = tangent.y; m_tangents[vert1*3+2] = tangent.z;	
	m_tangents[vert2*3+0] = tangent.x; m_tangents[vert2*3+1] = tangent.y; m_tangents[vert2*3+2] = tangent.z;

    // Add calculated bi-tangent back to m_tangents
	m_biTangents[vert0*3+0] = bitangent.x; m_biTangents[vert0*3+1] = bitangent.y; m_biTangents[vert0*3+2] = bitangent.z;	
	m_biTangents[vert1*3+0] = bitangent.x; m_biTangents[vert1*3+1] = bitangent.y; m_biTangents[vert1*3+2] = bitangent.z;	
	m_biTangents[vert2*3+0] = bitangent.x; m_biTangents[vert2*3+1] = bitangent.y; m_biTangents[vert2*3+2] = bitangent.z;	
}

/**
 * Push all of our data into a single vector.
 */
void Geometry::Gen(){
    assert((m_vertexPositions.size()/3) == (m_textureCoords.size()/2));

    int coordsPos =0;
    for (int i =0; i < m_vertexPositions.size()/3; ++i) {
        // vertices
        m_bufferData.push_back(m_vertexPositions[i*3+ 0]);
        m_bufferData.push_back(m_vertexPositions[i*3+ 1]);
        m_bufferData.push_back(m_vertexPositions[i*3+ 2]);
        // texture information
        m_bufferData.push_back(m_textureCoords[coordsPos*2+0]);
        m_bufferData.push_back(m_textureCoords[coordsPos*2+1]);
        // Note separate counter because we only have two dimensions
        coordsPos++;
        // normals
        m_bufferData.push_back(m_normals[i*3+0]);
        m_bufferData.push_back(m_normals[i*3+1]);
        m_bufferData.push_back(m_normals[i*3+2]);
        // tangents
        m_bufferData.push_back(m_tangents[i*3+0]);
        m_bufferData.push_back(m_tangents[i*3+1]);
        m_bufferData.push_back(m_tangents[i*3+2]);
        // bi-tangents
        m_bufferData.push_back(m_biTangents[i*3+0]);
        m_bufferData.push_back(m_biTangents[i*3+1]);
        m_bufferData.push_back(m_biTangents[i*3+2]);
    }
}

// Retrieves a pointer to our data.
float* Geometry::GetBufferDataPtr(){
    return m_bufferData.data();
}

// Retrieves the size of our data
unsigned int Geometry::GetBufferDataSize(){
    return m_bufferData.size();
}

// Retrieves the number of bytes of our data
unsigned int Geometry::GetBufferSizeInBytes(){
    return m_bufferData.size()*sizeof(float);
}

// Retrieves the number of indices that we have.
unsigned int Geometry::GetIndicesSize(){
	return m_indices.size();
}

// Retrieves a pointer to the indices that we have
unsigned int* Geometry::GetIndicesDataPtr(){
	return m_indices.data();
}
