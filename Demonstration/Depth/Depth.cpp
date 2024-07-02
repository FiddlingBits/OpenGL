/****************************************************************************************************
 * Include
 ****************************************************************************************************/

#include "Demonstration/Depth/Depth.h"
#include "Library/stb/stb_image.h" // Must Be Included Here

/****************************************************************************************************
 * Class
 ****************************************************************************************************/

/*** Constructor ***/
Depth::Depth()
    : Application(), ebo {}, shaderProgram {}, texture {}, vao {}, vbo {}
{
}

/*** Method ***/
void Depth::SetUp(void)
{
    /*** OpenGL ***/
    glEnable(GL_DEPTH_TEST);

    /*** Shader Program ***/
    shaderProgram.CreateProgram("Demonstration\\Depth\\FragmentShader.txt", "Demonstration\\Depth\\VertexShader.txt");
    shaderProgram.Use();

    /*** Rectangle ***/
    /* Positions */
    float positions[] =
    {
        /* Texture Coordinates: Side 1 */
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        1.0, 1.0,
        0.0, 1.0,
        0.0, 0.0,

        /* Texture Coordinates: Side 2 */
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        1.0, 1.0,
        0.0, 1.0,
        0.0, 0.0,

        /* Texture Coordinates: Side 3 */
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        1.0, 1.0,
        0.0, 1.0,
        0.0, 0.0,

        /* Texture Coordinates: Side 4 */
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        1.0, 1.0,
        0.0, 1.0,
        0.0, 0.0,

        /* Texture Coordinates: Side 5 */
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        1.0, 1.0,
        0.0, 1.0,
        0.0, 0.0,

        /* Texture Coordinates: Side 6 */
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        1.0, 1.0,
        0.0, 1.0,
        0.0, 0.0,

        /* Vertex: Side 1 */
        -0.5, -0.5, -0.5,
        0.5, -0.5, -0.5,
        0.5, 0.5, -0.5,
        0.5, 0.5, -0.5,
        -0.5, 0.5, -0.5,
        -0.5, -0.5, -0.5,

        /* Vertex: Side 2 */
        -0.5, -0.5, 0.5,
        0.5, -0.5, 0.5,
        0.5, 0.5, 0.5,
        0.5, 0.5, 0.5,
        -0.5, 0.5, 0.5,
        -0.5, -0.5, 0.5,

        /* Vertex: Side 3 */
        -0.5, 0.5, 0.5,
        -0.5, 0.5, -0.5,
        -0.5, -0.5, -0.5,
        -0.5, -0.5, -0.5,
        -0.5, -0.5, 0.5,
        -0.5, 0.5, 0.5,

        /* Vertex: Side 4 */
        0.5, 0.5, 0.5,
        0.5, 0.5, -0.5,
        0.5, -0.5, -0.5,
        0.5, -0.5, -0.5,
        0.5, -0.5, 0.5,
        0.5, 0.5, 0.5,

        /* Vertex: Side 5 */
        -0.5, -0.5, -0.5,
        0.5, -0.5, -0.5,
        0.5, -0.5, 0.5,
        0.5, -0.5, 0.5,
        -0.5, -0.5, 0.5,
        -0.5, -0.5, -0.5,

        /* Vertex: Side 6 */
        -0.5, 0.5, -0.5,
        0.5, 0.5, -0.5,
        0.5, 0.5, 0.5,
        0.5, 0.5, 0.5,
        -0.5, 0.5, 0.5,
        -0.5, 0.5, -0.5
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
    glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(72 * sizeof(float)));
    glEnableVertexAttribArray(location);

    /* Texture */
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    stbi_uc* data {stbi_load("Demonstration\\Depth\\Texture.png", &width, &height, &nrChannels, STBI_rgb)};
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

void Depth::TearDown(void)
{
    /*** Clean Up ***/
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    /*** Terminate ***/
    glfwTerminate();
}

void Depth::Update(void)
{
    /*** Update ***/
    /* Set Up */
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Model */
    glm::mat4 model = glm::mat4(1.0);
    model = glm::rotate(model, static_cast<float>(GetTime()), glm::vec3(0.5, 1.0, 0.0));
    shaderProgram.SetMat4("vu_model", model);

    /* View */
    glm::mat4 view = glm::mat4(1.0);
    view = glm::translate(view, glm::vec3(0.0, 0.0, -3.0));
    shaderProgram.SetMat4("vu_view", view);

    /* Projection */
    glm::mat4 projection = glm::mat4(1.0);
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    projection = glm::perspective(glm::radians(45.0), static_cast<double>(width) / static_cast<double>(height), 0.1, 100.0);
    shaderProgram.SetMat4("vu_projection", projection);

    /* Draw */
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
 