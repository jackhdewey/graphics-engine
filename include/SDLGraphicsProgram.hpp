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

#include "Renderer.hpp"
#include "ObjectManager.hpp"
#include "SceneTree.hpp"

/**
 * This class sets up a full graphics program using SDL
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
     * Return a boolean indicating whether initialization was successful
     *
     * @return a boolean
     */
    bool InitGL();

    /**
     * Set up the initial scene.
     */
    void InitScene();

    /**
     * Set up the renderer.
     */
     void InitRender(int w, int h);

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
     * Helper Function to Query OpenGL information.
     */
    void GetOpenGLVersionInfo();

private:

    // The window we'll be rendering to
    SDL_Window* m_window;
    // OpenGL context
    SDL_GLContext m_openGLContext;

    // Object manager stores the objects making up this scene
    ObjectManager* m_objectManager;
    // The scene tree stores the relationships between objects in this scene
    SceneTree* m_sceneTree;
    // The Renderer responsible for drawing objects in OpenGL
    Renderer* m_renderer;

};

#endif
