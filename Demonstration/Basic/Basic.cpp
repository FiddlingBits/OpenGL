/****************************************************************************************************
 * Include
 ****************************************************************************************************/

#include "Demonstration/Basic/Basic.h"

/****************************************************************************************************
 * Function Definition
 ****************************************************************************************************/

int main()
{
    /*** Run ***/
    Basic basic;
    basic.Run("Basic", 512, 512);
}

/****************************************************************************************************
 * Class
 ****************************************************************************************************/

/*** Constructor ***/
Basic::Basic()
    : Application(), ebo {}, shaderProgram {}, vao {}, vbo {}
{
}

/*** Method ***/
void Basic::SetUp(void)
{
    /*** Shader Program ***/
    shaderProgram.CreateProgram("Demonstration\\Basic\\FragmentShader.txt", "Demonstration\\Basic\\VertexShader.txt");
    shaderProgram.Use();

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
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    /* Vertex Buffer Object*/
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    GLint location {shaderProgram.GetAttributeLocation("position")};
    glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(location);

    /* Element Buffer Object */
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    /* Unbind */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Basic::TearDown(void)
{
    /*** Clean Up ***/
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    /*** Terminate ***/
    glfwTerminate();
}

void Basic::Update(void)
{
    /*** Update ***/
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(vao);
    double red = (sin(GetTime()) / 2.0) + 0.5;
    glUniform3f(shaderProgram.GetUniformLocation("color"), red, 0.0, 0.0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
 