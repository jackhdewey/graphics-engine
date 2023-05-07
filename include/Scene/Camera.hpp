/** @file Camera.hpp
 *  @brief An OpenGL camera
 *
 *  Contains view and projection matrices.
 *
 *  @author Mike Shah
 *  @bug No known bugs.
 */

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glm/glm.hpp"

/**
 * This class represents a camera for a scene.
 */
class Camera{
public:
	// Constructor
    Camera(unsigned int screenWidth, unsigned int screenHeight);
    // Alternative constructor
    Camera(unsigned int w, unsigned int h, glm::vec3 position, glm::vec3 direction, glm::vec3 up);
    // Orient (rotate) the camera
    void MouseLook(int mouseX, int mouseY);
    // Translate the camera in space
    void MoveForward(float speed);
    void MoveBackward(float speed);
    void MoveLeft(float speed);
    void MoveRight(float speed);
    void MoveUp(float speed);
    void MoveDown(float speed);
    // Set the position for the camera
    void SetCameraEyePosition(float x, float y, float z);
    // Returns the Camera X Position where the eye is 
    float GetEyeXPosition();
    // Returns the Camera Y Position where the eye is 
    float GetEyeYPosition();
    // Returns the Camera Z Position where the eye is 
    float GetEyeZPosition();
	// Returns the X 'view' direction
    float GetViewXDirection();
    // Returns the Y 'view' direction
    float GetViewYDirection();
    // Returns the Z 'view' direction
    float GetViewZDirection();
    // Return a 'view' matrix with our camera transformation applied.
    glm::mat4 GetWorldToViewMatrix() const;
    // Return a 'view' matrix with our camera transformation applied.
    glm::mat4 GetProjectionMatrix() const;

private:

    // Camera location
    glm::vec3 m_eyePosition;
    // Direction the camera is pointed
    glm::vec3 m_viewDirection;
    // Which direction is 'up'
    glm::vec3 m_upVector;

    // Store the projection matrix for our camera
    glm::mat4 m_projectionMatrix;

};


#endif
