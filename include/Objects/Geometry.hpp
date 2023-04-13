/** @file Geometry.hpp
 *  @brief Organizes vertex and triangle information.
 *  @author Jack Dewey
 *  @bug No known bugs.
 */

#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <vector>

/**
 * This class stores vertex and triangle information for a mesh
 */
class Geometry{
public:
	// Constructor
	Geometry();
	// Destructor
	~Geometry();

    // Add a new vertex with only geometry and texture data
    void AddVertex5f(float x, float y, float z, float s, float t);
	// Add a new vertex with geometry, texture, and normal data
	void AddVertex8f(float x, float y, float z, float s, float t, float xn, float yn, float zn);
	// Add a new index
	void AddIndex(unsigned int i);

	// Creates a triangle from 3 indices
	// When a triangle is made, the tangents and bi-tangents are also computed
	void MakeTriangle(unsigned int vert0, unsigned int vert1, unsigned int vert2);
    // Collect all vertex attributes into a single vector
    void Gen();

    // Return the buffer size in bytes
    unsigned int GetBufferSizeInBytes();
    // Return the buffer data size
    unsigned int GetBufferDataSize();
    // Return a pointer to the buffer data
    float* GetBufferDataPtr();
    // Return how many indices there are
	unsigned int GetIndicesSize();
    // Return a pointer to the indices
	unsigned int* GetIndicesDataPtr();

private:

    // Individual components
	std::vector<float> m_vertexPositions;
	std::vector<float> m_textureCoords;
	std::vector<float> m_normals;
	std::vector<float> m_tangents;
	std::vector<float> m_bitangents;

    // all the information that should be sent to the Vertex Buffer Object
    std::vector<float> m_bufferData;

	// The indices for an indexed-triangle mesh
	std::vector<unsigned int> m_indices;

};

#endif
