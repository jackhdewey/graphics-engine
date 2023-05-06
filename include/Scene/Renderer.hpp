/** @file Renderer.hpp
 *  @brief Renderer is responsible for drawing.
 *
 * 	The renderer is responsible for drawing the entire scene.
 * 	It contains a camera and a pointer to the root of the scene graph.
 *
 *  @author Mike Shah
 *  @bug No known bugs.
 */

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "glad/glad.h"

#include "Shader.hpp"
#include "Camera.hpp"
#include "SceneNode.hpp"

#include <vector>

/**
 * This class renders the scene.
 */
class Renderer {

private:
    // Screen dimensions
    int m_screenHeight;
    int m_screenWidth;
    // Perspective camera
    Camera* m_camera;
    // Shader program
    Shader m_shader;
    // Root of the scene tree
    SceneNode* m_root;

public:

    /**
     * Constructor
     *
     * @param w the window width
     * @param h the window height
     */
    Renderer(unsigned int w, unsigned int h);

    /**
     * Destructor
     */
    ~Renderer();

    /**
     * Renders the scene.
     */
    void Render();

    /**
     * Sets the root to the given scene node.
     * @param root
     */
    void SetRoot(SceneNode* root) {
        m_root = root;
    }

    /**
     * Returns a pointer to the camera.
     */
    Camera*& GetCamera(){
        return m_camera;
    }

};

#endif
