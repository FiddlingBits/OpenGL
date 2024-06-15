/****************************************************************************************************
 * Include
 ****************************************************************************************************/

#include <format>
#include <glad/glad.h> // Must Be Included Before glfw3.h
#include <GLFW/glfw3.h>
#include <iostream>

/****************************************************************************************************
 * Function Prototype
 ****************************************************************************************************/

static void framebufferSizecallback(GLFWwindow* window, int width, int height);
static void processInput(GLFWwindow* window);

/****************************************************************************************************
 * Function Definition (Public)
 ****************************************************************************************************/

/*** Main ***/
int main(int argc, char* argv[])
{
    /*** GLFW (Graphics Library Framework) ***/
    /* Initialize */
    (void)glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Window */
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
    if(window == NULL)
    {
        const char* description;
        int error = glfwGetError(&description);
        std::cout << std::format("glfwCreateWindow Error: {} ({})", error, description);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    /*** GLAD (Multi-Language GL/GLES/EGL/GLX/WGL Loader-Generator) ***/
    /* Load */
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << std::format("gladLoadGLLoader Error: {}", glGetError());
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    /* Viewport */
    glViewport(0, 0, 800, 600);
    (void)glfwSetFramebufferSizeCallback(window, framebufferSizecallback);

    /*** Render Loop ***/
    while(!glfwWindowShouldClose(window))
    {
        /*** Render Loop ***/
        /* Process Input */
        processInput(window);

        /* Render */
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Update */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    /*** Exit ***/
    glfwTerminate();
}

/****************************************************************************************************
 * Function Definition (Private)
 ****************************************************************************************************/

/*** Framebuffer Size Callback ***/
static void framebufferSizecallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

/*** Process Input ***/
void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
