/****************************************************************************************************
 * Pragma
 ****************************************************************************************************/

#pragma once

/****************************************************************************************************
 * Include
 ****************************************************************************************************/

#include <format>
#include "glad/glad.h" // Must Be Included Before glfw3.h
#include "GLFW/glfw3.h"
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

    protected:
        /*** Variable ***/
        GLFWwindow* window;

    public:
        /*** Constructor ***/
        Application();

        /*** Method ***/
        double GetElapsedTime() const;
        double GetTime() const;
        virtual void HandleKeyPress(const int Key, const int ScanCode, const int Action, const int Mods);
        virtual void HandleMouseButton(const int Button, const int Action, const int Mods);
        virtual void HandleMouseCursorPosition(const double X, const double Y);
        virtual void HandleMouseScroll(const double XOffset, const double YOffset);
        void Run(const std::string Title, const int Width, const int Height);
        virtual void SetUp(void);
        virtual void TearDown(void);
        virtual void Update(void);
};
