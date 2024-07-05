/****************************************************************************************************
 * Include
 ****************************************************************************************************/

#include "Core/Application.h"

/****************************************************************************************************
 * Function
 ****************************************************************************************************/

static void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

static void KeyPressCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Application* application = static_cast<Application*>(glfwGetWindowUserPointer(window));
    application->HandleKeyPress(key, scancode, action, mods);
}

static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    Application* application = static_cast<Application*>(glfwGetWindowUserPointer(window));
    application->HandleMouseButton(button, action, mods);
}

static void MouseCursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    Application* application = static_cast<Application*>(glfwGetWindowUserPointer(window));
    application->HandleMouseCursorPosition(xpos, ypos);
}

static void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    Application* application = static_cast<Application*>(glfwGetWindowUserPointer(window));
    application->HandleMouseScroll(xoffset, yoffset);
}

/****************************************************************************************************
 * Class
 ****************************************************************************************************/

/*** Constructor ***/
Application::Application()
    : elapsedTime {}, time {}, window {}
{
}

/*** Method (Public) ***/
double Application::GetElapsedTime() const
{
    return elapsedTime;
}

double Application::GetTime() const
{
    return time;
}

void Application::HandleKeyPress(const int Key, const int ScanCode, const int Action, const int Mods)
{
}

void Application::HandleMouseButton(const int Button, const int Action, const int Mods)
{
}

void Application::HandleMouseCursorPosition(const double X, const double Y)
{
}

void Application::HandleMouseScroll(const double XOffset, const double YOffset)
{
}

void Application::Run(const std::string Title, const int Width, const int Height)
{
    /*** GLFW (Graphics Library Framework) ***/
    /* Initialize */
    std::cout << std::format("[INFO] Initialize Application: {}\n", Title);
    (void)glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Window */
    window = glfwCreateWindow(Width, Height, Title.c_str(), NULL, NULL);
    if(window == NULL)
    {
        const char* description {};
        int error = glfwGetError(&description);
        std::cout << std::format("[ERROR] Create Window: {} ({})", error, description);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    (void)glfwSetCursorPosCallback(window, MouseCursorPositionCallback);
    (void)glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
    (void)glfwSetKeyCallback(window, KeyPressCallback);
    (void)glfwSetMouseButtonCallback(window, MouseButtonCallback);
    (void)glfwSetScrollCallback(window, MouseScrollCallback);
    glfwSetWindowUserPointer(window, this);

    /*** GLAD (Multi-Language GL/GLES/EGL/GLX/WGL Loader-Generator) ***/
    /* Load OpenGL Functions */
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << std::format("[ERROR] Load OpenGL Functions: {}", glGetError());
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    /*** Set Up ***/
    SetUp();

    /*** Render Loop ***/
    glfwSetTime(0.0);
    while(!glfwWindowShouldClose(window))
    {
        /*** Render Loop ***/
        /* Time */
        elapsedTime = time - glfwGetTime();
        time = glfwGetTime();

        /* Update */
        Update();

        /* Update */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    /*** Tear Down ***/
    TearDown();
}

void Application::SetUp(void)
{
}

void Application::TearDown(void)
{
}

void Application::Update(void)
{
}
