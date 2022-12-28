/** @file Camera.hpp
 *  @brief Sets up an OpenGL camera.
 *  
 *  Sets up an OpenGL Camera. The camera is what
 *  sets up our 'view' matrix.
 *
 *  @author Mike
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

    // Where is our camera positioned
    glm::vec3 m_eyePosition;
    // What direction is the camera looking
    glm::vec3 m_viewDirection;
    // Which direction is 'up' in our world
    // If you wanted to 'rock' or 'rattle' the camera you might play with modifying this value.
    glm::vec3 m_upVector;
    // Store the projection matrix for our camera.
    glm::mat4 m_projectionMatrix;

};


#endif
