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
#include "Library/glm/glm/glm.hpp"
#include "Library/glm/glm/gtc/matrix_transform.hpp"
#include "Library/glm/glm/gtc/type_ptr.hpp"

/****************************************************************************************************
 * Class
 ****************************************************************************************************/

class Transformation : public Application
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
        Transformation();

        /*** Method ***/
        void SetUp(void) override;
        void TearDown(void) override;
        void Update(void) override;
};
