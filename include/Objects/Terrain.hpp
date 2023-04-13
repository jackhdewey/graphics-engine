/** @file Terrain.hpp
 *  @brief Create a terrain
 *  
 *  More...
 *
 *  @author Mike
 *  @bug No known bugs.
 */
#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "VertexBufferLayout.hpp"
#include "Texture.hpp"
#include "Objects/Image.hpp"
#include "Objects/Object.hpp"

#include <vector>
#include <string>

/**
 * The class represents a simple terrain using triangle strips
 */
class Terrain : public Object {
public:

    /**
     * Terrain Constructor
     *
     * @param xSegs the number of segments (vertices) along the x axis
     * @param zSegs the number of segments (vertices) along the z axis
     * @param fileName the name of the height map file
     */
    Terrain (unsigned int xSegs, unsigned int zSegs, std::string fileName);

    /**
     * Destructor - deletes allocated heightmap data
     */
    ~Terrain ();

    /**
     * Creates a grid of segments
     * This article has a pretty handy illustration of what we are trying to do:
     * http://www.learnopengles.com/wordpress/wp-content/uploads/2012/05/vbo.png
     */
    void Init();

    /**
     * Loads a heightmap based on a PPM image
     * @param image the PPM image storing the height map
     */
    void LoadHeightMap(Image image);

private:

    // data
    unsigned int m_xSegments;
    unsigned int m_zSegments;

    // Store the height data in a multidimensional array
    int* m_heightData;

    // Textures for this terrain
    // (terrains often have multiple textures)
    std::vector<Texture> m_textures;
};

#endif
