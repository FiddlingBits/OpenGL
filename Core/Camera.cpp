/****************************************************************************************************
 * Include
 ****************************************************************************************************/

#include "Core/Camera.h"

/****************************************************************************************************
 * Class
 ****************************************************************************************************/

/*** Constructor ***/
Camera::Camera()
    : pitch {PitchDefault}, yaw {YawDefault},
      front {}, position {glm::vec3(0.0, 0.0, 0.0)}, right {}, up {}, worldUp {glm::vec3(0.0, 1.0, 0.0)},
      mouseSensitivity {MouseSensitivityDefault}, movementSpeed {MovementSpeedDefault}, zoom {ZoomDefault}
{
}

/*** Method (Private) ***/
void Camera::Update()
{
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::Look(const double X, const double Y)
{
    yaw += X * mouseSensitivity;
    pitch += Y * mouseSensitivity;
    if(pitch > 89.0)
        pitch = 89.0;
    if(pitch < -89.0)
        pitch = -89.0;
}

/*** Method (Public) ***/
void Camera::Move(const Movement Type, const double ElapsedTime)
{
    float velocity = movementSpeed * ElapsedTime;
    switch(Type)
    {
        case Movement::Backward:
            position += front * velocity;
            break;
        case Movement::Down:
            position += up * velocity;
            break;
        case Movement::Forward:
            position -= front * velocity;
            break;
        case Movement::Left:
            position += right * velocity;
            break;
        case Movement::Right:
            position -= right * velocity;
            break;
        case Movement::Up:
            position -= up * velocity;
            break;
    }
}

glm::mat4 Camera::GetView()
{
    Update();
    return glm::lookAt(position, position + front, up);
}

double Camera::GetZoom() const
{
    return zoom;
}

void Camera::Zoom(double Amount)
{
    zoom -= Amount;
    if(zoom < 1.0)
        zoom = 1.0;
    if(zoom > 45.0)
        zoom = 45.0;
}
