/** @file Renderer.hpp
 *  @brief Renderer is responsible for drawing.
 *
 * 	The renderer is responsible for drawing the entire scene.
 * 	It contains a pointer to the root of the scene graph and a camera.
 *
 *  @author Mike Shah
 *  @bug No known bugs.
 */

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
     * Updates the scene tree.
     */
    void Update(bool pause);

    /**
     * Renders the scene.
     */
    void Render();

    /**
     * Returns the camera.
     */
    Camera*& GetCamera(){
        return m_camera;
    }

    /**
     * Sets the root to the given scene node.
     * @param root
     */
    void SetRoot(SceneNode* root) {
        m_root = root;
    }

protected:

    SceneNode* m_root;
    Camera* m_camera;

private:

    // Screen dimensions
    int m_screenHeight;
    int m_screenWidth;

};

#endif
