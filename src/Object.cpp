#include "Object.hpp"
#include "Camera.hpp"
#include "Error.hpp"

Object::Object(){}

Object::~Object(){}

/**
 * Load the given object file
 *
 * @param objectFilePath
 */
void Object::LoadObjectModel(OBJModel* model) {

    std::cout<<"Loading Vertex Data"<<std::endl;

    // Load vertex and index data from model
    for (int i = 0; i < model->getVertexData().size(); i += 8) {
        m_geometry.AddVertex8f(model->getVertexData()[i],
                             model->getVertexData()[i + 1],
                             model->getVertexData()[i + 2],
                             model->getVertexData()[i + 3],
                             model->getVertexData()[i + 4],
                             model->getVertexData()[i + 5],
                             model->getVertexData()[i + 6],
                             model->getVertexData()[i + 7]);
    }

    std::cout<<"Loading Index Data"<<std::endl;

    for (int i = 0; i < model->getIndexData().size(); i += 3) {
        m_geometry.MakeTriangle(model->getIndexData()[i],
                                model->getIndexData()[i + 1],
                                model->getIndexData()[i + 2]);
    }

    std::cout<<"Generating Geometry"<<std::endl;

    m_geometry.Gen();

    // Create a layout buffer information
    m_vertexBufferLayout.CreateNormalBufferLayout(m_geometry.GetBufferDataSize(),
                                                  m_geometry.GetIndicesSize(),
                                                  m_geometry.GetBufferDataPtr(),
                                                  m_geometry.GetIndicesDataPtr());

    // Load our texture
    if (model->hasTexture()) {
        m_hasTexture = true;
        m_textureDiffuse.LoadTexture(model->getTextureFilePath());
    } else {
        m_hasTexture = false;
    }
}

/**
 * Return a boolean indicating whether this object has an associated texture
 *
 * @return
 */
bool Object::HasTexture() {
    return m_hasTexture;
}

/**
 * Load the given texture file
 *
 * It may be good to think about loading a 'default' texture if none is provided
 *
 * @param fileName
 */
void Object::LoadTexture(std::string fileName){
    if (m_hasTexture) {
        m_textureDiffuse.LoadTexture(fileName);
    }
}

/**
 * Bind to vertex buffer and texture
 */
void Object::Bind(){
        // Make sure we are updating the correct 'buffers'
        m_vertexBufferLayout.Bind();
        // Diffuse map is 0 by default, but it is good to set it explicitly
        if (m_hasTexture) {
            m_textureDiffuse.Bind(0);
        }
}

/**
 * Render geometry stored in m_vertexBufferLayout
 */
void Object::Render(){
    // Bind the current VBO and texture to OpenGL
    Bind();
    glDrawElements(GL_TRIANGLES, m_geometry.GetIndicesSize(), GL_UNSIGNED_INT, nullptr);
}


