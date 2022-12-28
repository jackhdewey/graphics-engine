/** @file OBJModel.h
 *  @brief Class for working with .obj models
 *
 *  @author Jack Dewey
 *  @bug No known bugs.
 */

#ifndef MONOREPO_JACKHDEWEY_OBJMODEL_HPP
#define MONOREPO_JACKHDEWEY_OBJMODEL_HPP

#include <string>
#include <vector>

class OBJModel{
public:
    /**
     * Constructor loads a filename with the .obj extension
     */
    OBJModel(std::string objectFilePath);

    /**
     * Destructor
     */
    ~OBJModel();

    /**
     * Extract texture and normal map file paths from .mtl file
     */
    void ParseMTL();

    /**
     * Return vertex data as vector
     */
    std::vector<float> getVertexData();

    /**
     * Return index data as vector
     * @return
     */
    std::vector<unsigned int> getIndexData();

    /**
     * Returns a boolean indicating whether this object model has a texture
     * @return
     */
    bool hasTexture();

    /**
     * Get texture file path
     * @return
     */
    std::string getTextureFilePath();

    /**
     * Get normal map file path
     *
     * @return
     */
    std::string getNormalMapFilePath();

private:

    std::vector<float> positions;
    std::vector<float> texture_coords;
    std::vector<float> normals;

    std::vector<float> vertex_data;
    std::vector<unsigned int> indices;

    std::string m_mtlFilePath;

    bool m_hasTexture = false;
    bool m_hasNormalMap = false;

    std::string m_textureFilePath;
    std::string m_normalMapFilePath;

};

#endif