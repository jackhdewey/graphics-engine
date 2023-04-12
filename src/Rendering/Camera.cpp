#include "Camera.hpp"

#include "glm/gtx/transform.hpp"
#include "glm/gtx/rotate_vector.hpp"

Camera::Camera(unsigned int screenWidth, unsigned int screenHeight){
    // Position us at the origin.
    m_eyePosition = glm::vec3(0.0f, 0.0f, 0.0f);
    // Looking down along the z-axis initially.
    // Remember, this is negative because we are looking 'into' the scene.
    m_viewDirection = glm::vec3(0.0f,0.0f, -1.0f);
    // Up vector points along the y-axis
    m_upVector = glm::vec3(0.0f, 1.0f, 0.0f);
    // Set the default projection matrix for our camera
    m_projectionMatrix = glm::perspective(45.0f, ((float) screenWidth) / ((float) screenHeight), 0.2f, 42.0f);
}

Camera::Camera(unsigned int w, unsigned int h, glm::vec3 position, glm::vec3 direction, glm::vec3 up){
    // Position us at the origin.
    m_eyePosition = position;
    // Looking down along the z-axis initially.
    // Remember, this is negative because we are looking 'into' the scene.
    m_viewDirection = direction;
    // Up vector points along the y-axis
    m_upVector = up;
    // Set the default projection matrix for our camera
    m_projectionMatrix = glm::perspective(45.0f, ((float) w) / ((float) h), 0.2f, 42.0f);
}

void Camera::MouseLook(int mouseX, int mouseY){
    float xRot = .05f * mouseX;
    float yRot = -(.05f * mouseY);
    m_viewDirection = glm::rotate(m_viewDirection, yRot, glm::cross(m_viewDirection, m_upVector));
    m_viewDirection = glm::rotate(m_viewDirection, xRot, m_upVector);
}

void Camera::MoveForward(float speed){
    m_eyePosition += speed * m_viewDirection;
}

void Camera::MoveBackward(float speed){
    m_eyePosition -= speed * m_viewDirection;
}

void Camera::MoveUp(float speed){
    m_eyePosition += speed * m_upVector;
}

void Camera::MoveDown(float speed){
    m_eyePosition -= speed * m_upVector;
}

void Camera::MoveLeft(float speed){
    m_eyePosition -= glm::normalize(glm::cross(m_viewDirection, m_upVector)) * speed;
}

void Camera::MoveRight(float speed){
    m_eyePosition += glm::normalize(glm::cross(m_viewDirection, m_upVector)) * speed;
}

void Camera::SetCameraEyePosition(float x, float y, float z){
    m_eyePosition.x = x;
    m_eyePosition.y = y;
    m_eyePosition.z = z;
}

float Camera::GetEyeXPosition(){
    return m_eyePosition.x;
}

float Camera::GetEyeYPosition(){
    return m_eyePosition.y;
}

float Camera::GetEyeZPosition(){
    return m_eyePosition.z;
}

float Camera::GetViewXDirection(){
    return m_viewDirection.x;
}

float Camera::GetViewYDirection(){
    return m_viewDirection.y;
}

float Camera::GetViewZDirection(){
    return m_viewDirection.z;
}

glm::mat4 Camera::GetWorldToViewMatrix() const {
    return glm::lookAt( m_eyePosition,
                        m_eyePosition + m_viewDirection,
                        m_upVector);
}

glm::mat4 Camera::GetProjectionMatrix() const {
    return m_projectionMatrix;
}
