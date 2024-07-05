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
#include <format>
#include "glad/glad.h" // Must Be Included Before glfw3.h
#include "GLFW/glfw3.h"
#include <iostream>

/****************************************************************************************************
 * Class
 ****************************************************************************************************/

class Texture : public Application
{
    private:
        /*** Variable ***/
        GLuint ebo;
        ShaderProgram shaderProgram;
        GLuint texture;
        GLuint vao;
        GLuint vbo;

    public:
        /*** Constructor ***/
        Texture();

        /*** Method ***/
        void SetUp(void) override;
        void TearDown(void) override;
        void Update(void) override;
};
