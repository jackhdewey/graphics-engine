#include "SDLGraphicsProgram.hpp"
#include "Sphere.hpp"
#include "glm/glm.hpp"

#include <iostream>
#include <string>
#include <sstream>

SDLGraphicsProgram::SDLGraphicsProgram(int w, int h) {

    // Initialization flag
	bool success = true;

    // String to hold any errors that occur.
	std::stringstream errorStream;

    // The window we'll be rendering to
	m_window = NULL;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
		success = false;
	} else {
		//Use OpenGL 3.3 core
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
		// We want to request a double buffer for smooth updating.
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		// Create window
		m_window = SDL_CreateWindow( "Lab",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                w,
                                h,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

		// Check if Window did not create
		if (m_window == NULL){
			errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

		// Initialize OpenGL
		if (!InitGL(errorStream)){
			errorStream << "Unable to initialize OpenGL!\n";
			success = false;
		}

        // Initialize our renderer
        InitRender(w, h);
  	}

    // If initialization did not work, then print out a list of errors in the constructor.
    if (!success) {
        errorStream << "SDLGraphicsProgram::SDLGraphicsProgram - Failed to initialize!\n";
        std::string errors = errorStream.str();
        SDL_Log("%s\n", errors.c_str());
    } else {
        SDL_Log("SDLGraphicsProgram::SDLGraphicsProgram - No SDL, GLAD, or OpenGL, errors detected during initialization\n\n");
    }

	// SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN); // Uncomment to enable extra debug support!
	GetOpenGLVersionInfo();
}

SDLGraphicsProgram::~SDLGraphicsProgram(){
    if (m_renderer != nullptr) {
        delete m_renderer;
    }
    // Destroy window
	SDL_DestroyWindow(m_window);
	// Point m_window to NULL
	m_window = nullptr;
	// Quit SDL subsystems
	SDL_Quit();
}

bool SDLGraphicsProgram::InitGL(std::stringstream& errorStream){
    bool success = true;
    // Create an OpenGL Graphics Context
    m_openGLContext = SDL_GL_CreateContext(m_window);
    if (m_openGLContext == NULL){
        errorStream << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << "\n";
        success = false;
    }
    // Initialize GLAD Library
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)){
        errorStream << "Failed to initialize GLAD\n";
        success = false;
    }
    return success;
}

void SDLGraphicsProgram::InitRender(int w, int h) {
    // glm::vec3 position(0.0f, 0.0f, 0.0f);
    // glm::vec3 direction(0.0f, 0.0f, -1.0f);
    // glm::vec3 up(0.0f, 1.0f, 0.0f);
    // Camera* camera = new Camera(w, h, position, direction, up);
    m_renderer = new Renderer(w, h);
}

void SDLGraphicsProgram::InitScene() {
    Object* floor = new Object();
    OBJModel* model = new OBJModel("../objects/base_surface/base_surface.obj");
    floor->LoadObjectModel(model);
    SceneNode* floor_node = new SceneNode(floor, false);

    m_sceneTree = &SceneTree::Instance(floor_node);

    Object* platform = new Object();
    model = new OBJModel("../objects/platform_one/platform_one.obj");
    platform->LoadObjectModel(model);
    SceneNode* platform_node = new SceneNode(platform, floor_node, false);

    Object* sphere = new Sphere();
    SceneNode* sphere_node = new SceneNode(sphere, floor_node, false);

    platform_node->SetPosition(0.0, 5.0, 0.0);
    platform_node->SetOrientation(.5);
    sphere_node->SetPosition(0.0, 8.0, 0.0);

    m_renderer->SetRoot(m_sceneTree->GetRoot());
}

void SDLGraphicsProgram::Loop(){

    // Set a default position for our camera
    m_renderer->GetCamera()->SetCameraEyePosition(0.0f,0.0f,30.0f);

    // If quit = 'true' then the program terminates.
    bool quit = false;
    bool pause = false;
    bool ready = false;
    bool change = false;

    // SDL Event Handler
    SDL_Event e;

    // Enable text input
    SDL_StartTextInput();

    // Set the camera speed for how fast we move.
    float cameraSpeed = 1.0f;

    // While application is running
    while(!quit){

        //Handle events on queue
        while(SDL_PollEvent( &e ) != 0){
            // User posts an event to quit
            // An example is hitting the "x" in the corner of the window.
            if(e.type == SDL_QUIT){
                quit = true;
            }
            // Handle keyboard input for the camera class
            if(e.type==SDL_MOUSEWHEEL){
                // Handle mouse movements
                int mouseX = e.wheel.x;
                int mouseY = e.wheel.y;
                m_renderer->GetCamera()->MouseLook(mouseX, mouseY);
            }
            switch(e.type){
                // Handle keyboard presses
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym) {
                        case SDLK_LEFT:
                            m_renderer->GetCamera()->MoveLeft(cameraSpeed);
                            break;
                        case SDLK_RIGHT:
                            m_renderer->GetCamera()->MoveRight(cameraSpeed);
                            break;
                        case SDLK_UP:
                            m_renderer->GetCamera()->MoveForward(cameraSpeed);
                            break;
                        case SDLK_DOWN:
                            m_renderer->GetCamera()->MoveBackward(cameraSpeed);
                            break;
                        case SDLK_RETURN:
                            m_renderer->GetCamera()->MoveUp(cameraSpeed);
                            break;
                        case SDLK_RSHIFT:
                            m_renderer->GetCamera()->MoveDown(cameraSpeed);
                            break;
                        case SDLK_SPACE:
                            ready = true;
                    }
                break;
                case SDL_KEYUP:
                    switch(e.key.keysym.sym) {
                        case SDLK_SPACE:
                            ready = false;
                            change = true;
                            break;
                    }
                    break;
            }
        } // End SDL_PollEvent loop.

        if (change) {
            pause = !pause;
            change = false;
        }

        // Update our scene through our renderer
        m_sceneTree->Update(m_renderer->GetCamera(), pause);

        // Render our scene using our selected renderer
        m_renderer->Render();

        // Delay to slow things down just a bit!
        SDL_Delay(25);  // You can change this or implement a frame
                        // independent movement method if you like.
      	//Update screen of our specified window
      	SDL_GL_SwapWindow(GetSDLWindow());
	}
    //Disable text input
    SDL_StopTextInput();
}


// Get Pointer to Window
SDL_Window* SDLGraphicsProgram::GetSDLWindow(){
  return m_window;
}

// Helper Function to get OpenGL Version Information
void SDLGraphicsProgram::GetOpenGLVersionInfo(){
	SDL_Log("(Note: If you have two GPUs, make sure the correct one is selected)");
	SDL_Log("Vendor: %s",(const char*)glGetString(GL_VENDOR));
	SDL_Log("Renderer: %s",(const char*)glGetString(GL_RENDERER));
	SDL_Log("Version: %s",(const char*)glGetString(GL_VERSION));
	SDL_Log("Shading language: %s",(const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
}
