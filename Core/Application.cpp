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

static void ProcessInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
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
    (void)glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

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

        /* Input */
        ProcessInput(window);

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
