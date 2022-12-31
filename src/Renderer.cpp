#include <string>
#include <iostream>

#include "Renderer.hpp"

Renderer::Renderer(unsigned int w, unsigned int h){

    // Store height and width
    m_screenWidth = w;
    m_screenHeight = h;

    // Create one camera per render
    // Alternatively, we could create a camera as a scene node
    Camera* defaultCamera = new Camera(w, h);

    // Add our single camera
    m_camera = defaultCamera;

}

Renderer::~Renderer(){
    delete m_camera;
}

/*
void CreateProgram(const std::string& vertSource, const std::string& fragSource) {
    std::string vertexShader = m_shader->LoadShader(vertSource);
    std::string fragmentShader = m_shader->LoadShader(fragSource);
    m_shader->CreateProgram(vertexShader, fragmentShader);
}
 */

void Renderer::Update(bool pause){
    if (m_root != nullptr) {
        m_root->Update(m_camera, pause);
    }
}

void Renderer::Render() {

    // Tell OpenGL to create a depth (or 'Z') buffer
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    // This is the background of the screen.
    glViewport(0, 0, m_screenWidth, m_screenHeight);
    glClearColor( 0.01f, 0.01f, 0.01f, 1.f );

    // Clear Color Buffer and Depth Buffer
    // Remember that our z-buffer figures out how far away items
    // are every frame - and we have to do this every frame!
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // Nice way to debug your scene in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    
    // Now we render our objects from our scene graph
    if (m_root != nullptr){
        m_root->Render();
    }
}


