/** @file Renderer.hpp
 *  @brief Renderer is responsible for drawing.
 *
 * 	The renderer is responsible for drawing the entire scene.
 * 	It contains a pointer to the root of the scene graph and a camera.
 *
 *  @author Mike
 *  @bug No known bugs.
 */

// TODO: Relocate camera to scene graph

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <glad/glad.h>

#include "SceneNode.hpp"
#include "Camera.hpp"

#include <vector>

/**
 * This class renders the scene.
 */
class Renderer {

public:

    /**
     * Initialize the renderer
     *
     * @param w the window width
     * @param h the window height
     */
    Renderer(unsigned int w, unsigned int h);

    /**
     * Free up memory used for camera(s)
     */
    ~Renderer();

    /**
     * Update the scene tree
     */
    void Update(bool pause);

    /**
     * Render the scene.
     */
    void Render();

    /**
     * Returns the camera at an index
     */
    Camera*& GetCamera(){
        return m_camera;
    }

    void SetRoot(SceneNode* root) {
        m_root = root;
    }

protected:

    SceneNode* m_root;

    // One camera per renderer
    Camera* m_camera;

private:

    // Screen dimensions
    int m_screenHeight;
    int m_screenWidth;

};

#endif
