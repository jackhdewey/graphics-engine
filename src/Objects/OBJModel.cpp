/** @file OBJModel.cpp
 *  @brief Implementation for OBJModel class.
 *
 *  Implements class for loading and rendering .obj models specifically.
 *
 *  @author Jack Dewey
 *  @bug No known bugs.
 */

#include "OBJModel.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

/**
 * New data type for holding vertex data
 */
struct VertexData{
    float x,y,z;
    float xn,yn,zn;
    float s,t;

    VertexData(float _x, float _y, float _z, float _s, float _t, float _xn, float _yn, float _zn):
                x(_x),y(_y),z(_z),s(_s),t(_t),xn(_xn),yn(_yn),zn(_zn) { }

    // Tests if two VertexData are equal
    bool operator== (const VertexData &rhs){
        if( (x == rhs.x) && (y == rhs.y) && (z == rhs.z)
            && (s == rhs.s) && (t == rhs.t)
            && (xn == rhs.xn) && (yn == rhs.yn) && (zn == rhs.zn)){
            return true;
        }
        return false;
    }
};

/**
 * Constructor loads a filename with the .obj extension
 */
OBJModel::OBJModel(std::string objectFilePath){

    // Create an input stream and open the file
    std::ifstream inFile;
    inFile.open(objectFilePath);
    std::string filePath = objectFilePath.substr(0, objectFilePath.find_last_of('/') + 1);

    // If the file opened correctly, read the file one line at a time
    if (inFile.is_open()) {

        std::string line;
        int count = 0;
        std::string first_token, token;
        float float_value;
        std::string delimiter = "/";
        int first_delimiter, second_delimiter;
        std::string vertex_index, texture_index, normal_index;
        unsigned int int_index;
        float x, y, z, xn, yn, zn, s, t;
        std::vector<VertexData> test_vertices;
        bool contains = false;
        int location;

        while (getline(inFile, line)) {

            // Split the line into string tokens and extract the first token
            std::stringstream stream(line);
            stream >> first_token;

            // Depending on the first token, either skip this line or place the remaining line items in appropriate vector
            while (stream >> token) {

                if (first_token == "mtllib") {

                    m_mtlFilePath = filePath + token;
                    ParseMTL();

                } else if (first_token == "v") {

                    float_value = std::stof(token);
                    positions.push_back(float_value);

                } else if (first_token == "vt") {

                    float_value = std::stof(token);
                    texture_coords.push_back(float_value);

                } else if (first_token == "vn") {

                    float_value = std::stof(token);
                    normals.push_back(float_value);

                } else if (first_token == "f") {

                    // Use '/' as delimiter to split token into two new sub-tokens
                    first_delimiter = token.find(delimiter);
                    second_delimiter = token.find(delimiter, first_delimiter + 1);

                    // Convert first index to an int and use it to look up position coordinates
                    vertex_index = token.substr(0, first_delimiter);
                    int_index = (unsigned int) std::stoi(vertex_index);
                    int_index = 3 * (int_index - 1);
                    x = positions.at(int_index);
                    y = positions.at(int_index + 1);
                    z = positions.at(int_index + 2);

                    // Convert second index to an int and use it to look up texture coordinates
                    texture_index = token.substr(first_delimiter + 1, second_delimiter);
                    int_index = (unsigned int) std::stoi(texture_index);
                    int_index = 2 * (int_index - 1);
                    s = texture_coords.at(int_index);
                    t = texture_coords.at(int_index + 1);

                    // Convert third index to an int and use it to look up normals
                    normal_index = token.substr(second_delimiter + 1);
                    int_index = (unsigned int) std::stoi(normal_index);
                    int_index = 3 * (int_index - 1);
                    xn = normals.at(int_index);
                    yn = normals.at(int_index + 1);
                    zn = normals.at(int_index + 2);

                    // Store those coordinates in a temporary VertexData struct
                    VertexData temp_vertex = VertexData(x,y,z,s,t,xn,yn,zn);

                    // If we've seen this vertex before, don't add it again
                    // Instead, note the index of the existing vertex as location
                    for (int i = 0; i < test_vertices.size(); i++) {
                        if (temp_vertex == test_vertices.at(i)) {
                            contains = true;
                            location = i;
                        }
                    }

                    // If we haven't seen it before, add it to vertex_data and store its index
                    if (!contains) {
                        test_vertices.push_back(temp_vertex);
                        vertex_data.push_back(x);
                        vertex_data.push_back(y);
                        vertex_data.push_back(z);
                        vertex_data.push_back(s);
                        vertex_data.push_back(t);
                        vertex_data.push_back(xn);
                        vertex_data.push_back(yn);
                        vertex_data.push_back(zn);
                        indices.push_back(count);
                        count++;
                    } else {
                        indices.push_back(location);
                    }

                    // Reset contains
                    contains = false;

                } else {
                    continue;
                }
            }
        }
    }
    inFile.close();
}

/**
 * Destructor deletes(delete or delete[]) any memory that has been allocated
 * or otherwise calls any 'shutdown' or 'destroy' routines for this deletion to occur.
 */
OBJModel::~OBJModel(){
    positions.clear();
    texture_coords.clear();
    vertex_data.clear();
    indices.clear();
}

void OBJModel::ParseMTL() {

    // Creates an input stream and opens the file
    std::ifstream inFile;
    inFile.open(m_mtlFilePath);
    std::string filePath = m_mtlFilePath.substr(0, m_mtlFilePath.find_last_of('/') + 1);
    std::cout<<"Parsing MTL"<<std::endl;

    // If the file opened correctly, reads the file one line at a time
    if (inFile.is_open()) {
        std::string line;

        while (getline(inFile, line)) {

            // Split the line into tokens and extract the first token
            std::stringstream stream(line);
            std::string first_token;
            stream >> first_token;

            // Depending on the first token, either skip this line or parse the remaining line items
            std::string token;
            while (stream >> token) {
                if (first_token == "map_Kd") {
                    m_textureFilePath = filePath + token;
                    std::cout<<"Texture found"<<std::endl;
                    m_hasTexture = true;
                } else if (first_token == "map_Bump") {
                    m_normalMapFilePath = filePath + token;
                    std::cout<<"Normal map found"<<std::endl;
                } else {
                    continue;
                }
            }
        }
    }

    inFile.close();

    if (!m_hasTexture) {
        std::cout<<"No texture data found"<<std::endl;
    }
}

std::vector<float> OBJModel::getVertexData() {
    return vertex_data;
}

std::vector<unsigned int> OBJModel::getIndexData() {
    return indices;
}

bool OBJModel::hasTexture() {
    return m_hasTexture;
}

std::string OBJModel::getTextureFilePath() {
    return m_textureFilePath;
}

std::string OBJModel::getNormalMapFilePath() {
    return m_normalMapFilePath;
}



