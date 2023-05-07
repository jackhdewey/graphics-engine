/**
 *  @file SDLGraphicsProgram.hpp
 *  @brief Class used to set up SDL and OpenGL and initialize a scene.
 *
 *  @author Jack Dewey
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

/**
 * This class contains an SDL graphics program
 */
class SDLGraphicsProgram{

private:
    // Output window
    SDL_Window* m_window;
    // OpenGL context
    SDL_GLContext m_openGLContext;
    // Draws objects in OpenGL
    Renderer* m_renderer;
    // Stores and organizes scene nodes based on their locations
    SceneTree* m_sceneTree;

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

};

#endif
