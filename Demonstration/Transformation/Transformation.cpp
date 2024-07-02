/****************************************************************************************************
 * Include
 ****************************************************************************************************/

#include "Demonstration/Transformation/Transformation.h"
#include "Library/stb/stb_image.h" // Must Be Included Here

/****************************************************************************************************
 * Class
 ****************************************************************************************************/

/*** Constructor ***/
Transformation::Transformation()
    : Application(), ebo {}, shaderProgram {}, texture {}, vao {}, vbo {}
{
}

/*** Method ***/
void Transformation::SetUp(void)
{
    /*** Shader Program ***/
    shaderProgram.CreateProgram("Demonstration\\Transformation\\FragmentShader.txt", "Demonstration\\Transformation\\VertexShader.txt");
    shaderProgram.Use();

    /*** Rectangle ***/
    /* Positions */
    float positions[] =
    {
        1.0, 1.0, // Texture Coordinate: Top Right
        1.0, 0.0, // Texture Coordinate: Bottom Right
        0.0, 0.0, // Texture Coordinate: Bottom Left
        0.0, 1.0, // Texture Coordinate: Top Left
        0.5f, 0.5f, 0.0f,   // Vertex: Top Right
        0.5f, -0.5f, 0.0f,  // Vertex: Bottom Right
        -0.5f, -0.5f, 0.0f, // Vertex: Bottom Left
        -0.5f, 0.5f, 0.0f   // Vertex: Top Left
    };

    /* Vertex Array Object */
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    /* Vertex Buffer Object*/
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
    GLint location {shaderProgram.GetAttributeLocation("vi_textureCoordinates")};
    glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(location);
    location = shaderProgram.GetAttributeLocation("vi_position");
    glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(location);

    /* Indices */
    unsigned int indices[] =
    {
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };

    /* Element Buffer Object */
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    /* Texture */
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    stbi_uc* data {stbi_load("Demonstration\\Transformation\\Texture.png", &width, &height, &nrChannels, STBI_rgb)};
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << std::format("[ERROR] Load Texture File\n");
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Transformation::TearDown(void)
{
    /*** Clean Up ***/
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    /*** Terminate ***/
    glfwTerminate();
}

void Transformation::Update(void)
{
    /*** Update ***/
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glm::mat4 transform(1.0);
    transform = glm::rotate(transform, static_cast<float>(GetTime()), glm::vec3(0.0, 0.0, 1.0));
    glUniformMatrix4fv(shaderProgram.GetUniformLocation("vu_transform"), 1, GL_FALSE, glm::value_ptr(transform));
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
 