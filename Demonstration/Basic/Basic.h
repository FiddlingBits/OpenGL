/****************************************************************************************************
 * Pragma
 ****************************************************************************************************/

#pragma once

/****************************************************************************************************
 * Include
 ****************************************************************************************************/

#include <cmath>
#include "Core/Application.h"
#include "Core/ShaderProgram.h"
#include <glad/glad.h> // Must Be Included Before glfw3.h
#include <GLFW/glfw3.h>

/****************************************************************************************************
 * Class
 ****************************************************************************************************/

class Basic : public Application
{
    private:
        /*** Variable ***/
        GLuint ebo;
        ShaderProgram shaderProgram;
        GLuint vao;
        GLuint vbo;

    public:
        /*** Constructor ***/
        Basic();

        /*** Method ***/
        void SetUp(void) override;
        void TearDown(void) override;
        void Update(void) override;
};
