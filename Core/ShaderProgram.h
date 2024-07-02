/****************************************************************************************************
 * Pragma
 ****************************************************************************************************/

#pragma once

/****************************************************************************************************
 * Include
 ****************************************************************************************************/

#include <format>
#include <fstream>
#include "glad/glad.h"
#include <iostream>
#include <sstream>
#include <string>

/****************************************************************************************************
 * Class
 ****************************************************************************************************/

class ShaderProgram
{
    private:
        /*** Method ***/
        GLuint CompileShader(const std::string FileName, const GLenum Type) const;
        std::string ReadFile(const std::string FileName) const;

        /*** Variable ***/
        GLuint programId;

    public:
        /*** Constructor ***/
        ShaderProgram();

        /*** Destructor ***/
        ~ShaderProgram();

        /*** Method ***/
        void CreateProgram(const std::string FragmentShaderFileName, const std::string VertexShaderFileName);
        GLint GetAttributeLocation(const std::string Name) const;
        GLint GetUniformLocation(const std::string Name) const;
        void Use() const;
};
