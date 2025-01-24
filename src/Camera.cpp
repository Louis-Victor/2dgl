#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Camera.h"

Camera::Camera() : Camera::Camera(glm::vec3(0.0f,0.0f,3.0f),glm::vec3(0.0f,1.0f,0.0f),YAW,PITCH){}

// constructor with vectors
Camera::Camera(glm::vec3 m_position, glm::vec3 m_up, float m_yaw, float m_pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
{
    position = m_position;
    worldUp = m_up;
    yaw = m_yaw;
    pitch = m_pitch;
    updateCameraVectors();
}


// returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(position, position + front, up);
}

// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::processKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = movementSpeed * deltaTime;
    if (direction == FORWARD)
        position += front * velocity;
    if (direction == BACKWARD)
        position -= front * velocity;
    if (direction == LEFT)
        position -= right * velocity;
    if (direction == RIGHT)
        position += right * velocity;
    if(direction == UP)
        position += up * velocity;
    if(direction == DOWN)
        position -= up * velocity;
}

void Camera::processMouseMovement(float xoffset, float yoffset){
    Camera::processMouseMovement(xoffset,yoffset,true);
}
// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::processMouseMovement(float m_xoffset, float m_yoffset, GLboolean constrainPitch)
{

    m_xoffset *= mouseSensitivity;
    m_yoffset *= mouseSensitivity;


    yaw   += m_xoffset;
    pitch += m_yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::processMouseScroll(float yoffset)
{
    zoom -= (float)yoffset;
    if (zoom < 1.0f)
        zoom = 1.0f;
    if (zoom > 45.0f)
        zoom = 45.0f;
}

// calculates the front vector from the Camera's (updated) Euler Angles
void Camera::updateCameraVectors()
{
    // calculate the new Front vector
    //glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(front, worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up = glm::normalize(glm::cross(right, front));
}
