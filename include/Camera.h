#ifndef __CAMERA__
#define __CAMERA__
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include  <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

class Camera
{
    private:
        // camera Attributes
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 worldUp;
        // euler Angles
        float yaw;
        float pitch;
        // camera options
        float movementSpeed;
        float mouseSensitivity;
        float zoom;
        void updateCameraVectors();
    public:
        Camera();
        Camera(glm::vec3 m_position, glm::vec3 m_up, float m_yaw, float m_pitch);
        glm::mat4 getViewMatrix();
        void processKeyboard(Camera_Movement direction, float deltaTime);
        void processMouseMovement(float xoffset, float yoffset);
        void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch);
        void processMouseScroll(float yoffset);
};
#endif
