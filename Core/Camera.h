/****************************************************************************************************
 * Pragma
 ****************************************************************************************************/

#pragma once

/****************************************************************************************************
 * Include
 ****************************************************************************************************/

#include "Library/glm/glm/glm.hpp"
#include "Library/glm/glm/gtc/matrix_transform.hpp"

/****************************************************************************************************
 * Class
 ****************************************************************************************************/

class Camera
{
    private:
        /*** Constant ***/
        const double PitchDefault = 0.0;
        const double MouseSensitivityDefault = 0.1;
        const double MovementSpeedDefault = 2.5;
        const double YawDefault = -90.0;
        const double ZoomDefault = 45.0;

        /*** Method ***/
        void Update();

        /*** Variable ***/
        /* Angle */
        double pitch;
        double yaw;

        /* Attribute */
        glm::vec3 front;
        glm::vec3 position;
        glm::vec3 right;
        glm::vec3 up;
        glm::vec3 worldUp;
        
        /* Option */
        double mouseSensitivity;
        double movementSpeed;
        double zoom;

    public:
        /*** Constructor ***/
        Camera();

        /*** Enumeration ***/
        enum class Movement
        {
            Backward,
            Down,
            Forward,
            Left,
            Right,
            Up
        };

        /*** Method ***/
        void Look(const double X, const double Y);
        void Move(const Movement Type, const double ElapsedTime);
        glm::mat4 GetView();
        double GetZoom() const;
        void Zoom(double Amount);
};
