/** @file SDLGraphicsProgram.hpp
 *  @brief SDL Class used to setup input and setup of OpenGL.
 *  
 *  This class is used for the initialization of SDL.
 *
 *  @author Mike
 *  @bug No known bugs.
 */
#ifndef SDLGRAPHICSPROGRAM_HPP
#define SDLGRAPHICSPROGRAM_HPP

// ==================== Libraries ==================
// Depending on the operating system we use the paths to SDL are actually different.
// The #define statement should be passed in when compiling using the -D argument.
// This gives an example of how a programmer may support multiple platforms with different dependencies.
#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif

#include "glad/glad.h"

#include "./Scene/Renderer.hpp"
#include "./Scene/SceneTree.hpp"
#include "./Scene/Camera.hpp"

/**
 * This class contains an SDL graphics program
 */
class SDLGraphicsProgram{
public:

    /**
     * Constructor
     *
     * @param w the width of the window
     * @param h the height of the window
     */
    SDLGraphicsProgram(int w, int h);

    /**
     * Destructor
     */
    ~SDLGraphicsProgram();

    /**
     * Initialize OpenGL
     *
     * @return boolean indicating whether initialization was successful
     */
    bool InitGL(std::stringstream& errorStream);

    /**
     * Create renderer
     */
    void InitRender(int w, int h);

    /**
     * Create an object from a .obj filepath.
     *
     * @param filename
     * @return
     */
    SceneNode* CreateGameObject(std::string filename, SceneNode* parent, float x, float y, float z);

    /**
     * Set up the initial scene.
     */
    void InitScene();

    /**
     * Main program loop
     */
    void Loop();

    /**
     * Retrieve a pointer to the SDL window.
     * @return
     */
    SDL_Window* GetSDLWindow();

    /**
     * Retrieve OpenGL information.
     */
    void GetOpenGLVersionInfo();

private:

    // The window we'll be rendering to
    SDL_Window* m_window;
    // OpenGL context
    SDL_GLContext m_openGLContext;

    // The renderer is responsible for drawing objects in OpenGL
    Renderer* m_renderer;
    // The scene tree stores the objects and their positions in a scene
    SceneTree* m_sceneTree;

};

#endif
