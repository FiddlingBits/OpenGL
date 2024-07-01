/****************************************************************************************************
 * Pragma
 ****************************************************************************************************/

#pragma once

/****************************************************************************************************
 * Include
 ****************************************************************************************************/

#include <format>
#include <glad/glad.h> // Must Be Included Before glfw3.h
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

/****************************************************************************************************
 * Class
 ****************************************************************************************************/

class Application
{
    private:
        /*** Variable ***/
        double elapsedTime;
        double time;
        GLFWwindow* window;

    public:
        /*** Constructor ***/
        Application();

        /*** Method ***/
        double GetElapsedTime() const;
        double GetTime() const;
        void Run(const std::string Title, const int Width, const int Height);
        virtual void SetUp(void);
        virtual void TearDown(void);
        virtual void Update(void);
};
