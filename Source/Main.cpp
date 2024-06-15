/****************************************************************************************************
 * Include
 ****************************************************************************************************/

#include <format>
#include <glad/glad.h> // Must Be Included Before glfw3.h
#include <GLFW/glfw3.h>
#include <iostream>

/****************************************************************************************************
 * Constant
 ****************************************************************************************************/

const char* const FragmentShaderSource =
    "#version 460 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
    "}\n";
const unsigned int ScreenHeight = 600;
const unsigned int ScreenWidth = 800;
const char* const VertexShaderSource =
    "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}";

/****************************************************************************************************
 * Function Prototype
 ****************************************************************************************************/

static void framebufferSizecallback(GLFWwindow* window, int width, int height);
static void processInput(GLFWwindow* window);

/****************************************************************************************************
 * Function Definition (Public)
 ****************************************************************************************************/

/*** Main ***/
int main()
{
    /*** GLFW (Graphics Library Framework) ***/
    /* Initialize */
    (void)glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Window */
    GLFWwindow* window = glfwCreateWindow(ScreenWidth, ScreenHeight, "OpenGL", NULL, NULL);
    if(window == NULL)
    {
        const char* description;
        int error = glfwGetError(&description);
        std::cout << std::format("glfwCreateWindow Error: {} ({})", error, description);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    (void)glfwSetFramebufferSizeCallback(window, framebufferSizecallback);

    /*** GLAD (Multi-Language GL/GLES/EGL/GLX/WGL Loader-Generator) ***/
    /* Load */
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << std::format("gladLoadGLLoader Error: {}", glGetError());
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    /*** Vertex Shader ***/
    /* Compile */
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &VertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    /* Status */
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);
        std::cout << std::format("glCompileShader(vertexShader) Error: {} ({})", success, infoLog);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    /*** Fragment Shader ***/
    /* Compile */
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &FragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    /* Status */
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
        std::cout << std::format("glCompileShader(fragmentShader) Error: {} ({})", success, infoLog);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    /*** Shader Program ***/
    /* Link */
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    /* Status */
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
        std::cout << std::format("glGetProgramiv(shaderProgram) Error: {} ({})", success, infoLog);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    /* Clean Up */
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    /*** Rectangle ***/
    /* Vertices */
    float vertices[] =
    {
        0.5f, 0.5f, 0.0f,   // Top Right
        0.5f, -0.5f, 0.0f,  // Bottom Right
        -0.5f, -0.5f, 0.0f, // Bottom Left
        -0.5f, 0.5f, 0.0f   // Top Left
    };

    /* Indices */
    unsigned int indices[] =
    {
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };

    /* Vertex Array Object */
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    /* Vertex Buffer Object*/
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /* Element Buffer Object */
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    /* Unbind */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    /*** Render Loop ***/
    glfwSetTime(0.0);
    while(!glfwWindowShouldClose(window))
    {
        /*** Render Loop ***/
        /* Input */
        processInput(window);

        /* Render */
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        double time = glfwGetTime();
        if(time < 1.0)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else if(time < 2.0)
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        else
            glfwSetTime(0.0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        /* Update */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    /*** Clean Up ***/
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

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
