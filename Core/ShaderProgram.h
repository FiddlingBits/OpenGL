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
#include "Library/glm/glm/glm.hpp"
#include "Library/glm/glm/gtc/type_ptr.hpp"
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
        void SetFloat(const std::string& Name, const float Value) const;
        void SetInt(const std::string& Name, const int Value) const;
        void SetMat4(const std::string& Name, const glm::mat4& Mat4) const;
        void SetVec3(const std::string& name, const float X, const float Y, const float Z) const;
        void Use() const;
};
