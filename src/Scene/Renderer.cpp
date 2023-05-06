#include <string>

#include "Scene/Renderer.hpp"

Renderer::Renderer(unsigned int w, unsigned int h) : m_camera(new Camera(w,h)),
                                                    m_screenHeight(h), m_screenWidth(w){

    std::string vertexShader = m_shader.LoadShader("../shaders/vert.glsl");
    std::string fragmentShader = m_shader.LoadShader("../shaders/depthmap.glsl");
    m_shader.CreateProgram(vertexShader, fragmentShader);
    m_shader.Bind();
    m_shader.SetUniformMatrix4fv("projection", &m_camera->GetProjectionMatrix()[0][0]);
}

Renderer::~Renderer(){
    delete m_camera;
}

void Renderer::Render() {

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    // Reset the background of the screen
    glViewport(0, 0, m_screenWidth, m_screenHeight);
    glClearColor(0.01f, 0.01f, 0.01f, 1.f);

    // Clear color and depth buffers
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // Optionally debug scene in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Send camera position
    m_shader.SetUniform3f("cameraPosition", m_camera->GetEyeXPosition(),m_camera->GetEyeYPosition(),
                          m_camera->GetEyeZPosition());
    m_shader.SetUniformMatrix4fv("view", &m_camera->GetWorldToViewMatrix()[0][0]);

    // Send light information
    m_shader.SetUniform3f("lightPos", 0.0f, 10.0f, 0.0f);
    m_shader.SetUniform3f("lightColor", 1.0f, 1.0f, 1.0f);
    m_shader.SetUniform1f("ambientIntensity", 0.6f);
    m_shader.SetUniform1f("specularStrength", 0.5f);
    
    // Begin to recursively render the scene starting at root
    if (m_root != nullptr){
        m_root->Render(m_shader);
    }
}


