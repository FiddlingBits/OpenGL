/****************************************************************************************************
 * Pragma
 ****************************************************************************************************/

#pragma once

/****************************************************************************************************
 * Include
 ****************************************************************************************************/

#include <cmath>
#include "Core/Application.h"
#include "Core/Camera.h"
#include "Core/ShaderProgram.h"
#include <format>
#include "glad/glad.h" // Must Be Included Before glfw3.h
#include "GLFW/glfw3.h"
#include <format>
#include <iostream>
#include "Library/glm/glm/glm.hpp"
#include "Library/glm/glm/gtc/matrix_transform.hpp"
#include "Library/glm/glm/gtc/type_ptr.hpp"

/****************************************************************************************************
 * Class
 ****************************************************************************************************/

class LightingMap : public Application
{
    private:
        /*** Variable ***/
        /* Camera */
        Camera camera;

        /* Movement */
        bool backward;
        bool down;
        bool forward;
        bool left;
        bool right;
        bool up;

        /* OpenGL */
        GLuint map[2];
        ShaderProgram shaderProgram[2];
        GLuint vao[2];
        GLuint vbo;

    public:
        /*** Constructor ***/
        LightingMap();

        /*** Method ***/
        void HandleKeyPress(const int Key, const int ScanCode, const int Action, const int Mods) override;
        void HandleMouseCursorPosition(const double X, const double Y) override;
        void HandleMouseScroll(const double XOffset, const double YOffset) override;
        GLuint LoadTexture(const char * const Path) const;
        void SetUp(void) override;
        void TearDown(void) override;
        void Update(void) override;
};