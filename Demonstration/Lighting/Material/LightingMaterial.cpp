/****************************************************************************************************
 * Include
 ****************************************************************************************************/

#include "Demonstration/Lighting/Material/LightingMaterial.h"

/****************************************************************************************************
 * Class
 ****************************************************************************************************/

/*** Constructor ***/
LightingMaterial::LightingMaterial()
    : Application(),
      camera {},
      backward {false}, down {false}, forward {false}, left {false}, right {false}, up {false},
      shaderProgram {}, vao {}, vbo {}
{
}

/*** Method ***/
void LightingMaterial::HandleKeyPress(const int Key, const int ScanCode, const int Action, const int Mods)
{
    switch(Key)
    {
        case GLFW_KEY_A:
            if(Action == GLFW_PRESS)
                left = true;
            else if(Action == GLFW_RELEASE)
                left = false;
            break;
        case GLFW_KEY_D:
            if(Action == GLFW_PRESS)
                right = true;
            else if(Action == GLFW_RELEASE)
                right = false;
            break;
        case GLFW_KEY_DOWN:
            if(Action == GLFW_PRESS)
                down = true;
            else if(Action == GLFW_RELEASE)
                down = false;
            break;
        case GLFW_KEY_S:
            if(Action == GLFW_PRESS)
                backward = true;
            else if(Action == GLFW_RELEASE)
                backward = false;
            break;
        case GLFW_KEY_UP:
            if(Action == GLFW_PRESS)
                up = true;
            else if(Action == GLFW_RELEASE)
                up = false;
            break;
        case GLFW_KEY_W:
            if(Action == GLFW_PRESS)
                forward = true;
            else if(Action == GLFW_RELEASE)
                forward = false;
            break;
    }        
}

void LightingMaterial::HandleMouseCursorPosition(const double X, const double Y)
{
    static double lastX {X}, lastY {Y};
    double xOffset = X - lastX;
    double yOffset = lastY - Y;
    lastX = X;
    lastY = Y;
    camera.Look(xOffset, yOffset);
}

void LightingMaterial::HandleMouseScroll(const double XOffset, const double YOffset)
{
    camera.Zoom(YOffset);
}

void LightingMaterial::SetUp(void)
{
    /*** OpenGL ***/
    glEnable(GL_DEPTH_TEST);

    /*** Shader Program ***/
    /* Lighting */
    shaderProgram[0].CreateProgram("Demonstration\\Lighting\\Material\\LightingFragmentShader.txt", "Demonstration\\Lighting\\Material\\LightingVertexShader.txt");
    
    /* Light Cube */
    shaderProgram[1].CreateProgram("Demonstration\\Lighting\\Material\\LightCubeFragmentShader.txt", "Demonstration\\Lighting\\Material\\LightCubeVertexShader.txt");

    /*** Rectangle ***/
    /* Positions */
    float positions[] =
    {
        /* Normal: Side 1 */
        0.0, 0.0, -1.0,
        0.0, 0.0, -1.0,
        0.0, 0.0, -1.0,
        0.0, 0.0, -1.0,
        0.0, 0.0, -1.0,
        0.0, 0.0, -1.0,

        /* Normal: Side 2 */
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,

        /* Normal: Side 3 */
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,

        /* Normal: Side 4 */
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,

        /* Normal: Side 5 */
        0.0, -1.0, 0.0,
        0.0, -1.0, 0.0,
        0.0, -1.0, 0.0,
        0.0, -1.0, 0.0,
        0.0, -1.0, 0.0,
        0.0, -1.0, 0.0,

        /* Normal: Side 6 */
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,

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

    /* Vertex Array Object (Lighting) */
    glGenVertexArrays(1, &vao[0]);
    glBindVertexArray(vao[0]);

    /* Vertex Buffer Object (Shared) */
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
    GLint location = shaderProgram[0].GetAttributeLocation("vi_normal");
    glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(location);
    location = shaderProgram[0].GetAttributeLocation("vi_position");
    glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(108 * sizeof(float)));
    glEnableVertexAttribArray(location);

    /* Vertex Array Object (Light Cube) */
    glGenVertexArrays(1, &vao[1]);
    glBindVertexArray(vao[1]);

    /* Vertex Buffer Object (Shared; Set Above) */
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    location = shaderProgram[1].GetAttributeLocation("vi_position");
    glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(108 * sizeof(float)));
    glEnableVertexAttribArray(location);
}

void LightingMaterial::TearDown(void)
{
    /*** Clean Up ***/
    glDeleteVertexArrays(2, vao);
    glDeleteBuffers(1, &vbo);

    /*** Terminate ***/
    glfwTerminate();
}

void LightingMaterial::Update(void)
{
    /*** Update ***/
    /* Set Up */
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Light */
    glm::vec3 lightPosition(2.0, 2.0, -5.0);
    glm::vec3 lightColor;
    lightColor.x = sin(2.0 * GetTime());
    lightColor.y = sin(0.7 * GetTime());
    lightColor.z = sin(1.3 * GetTime());
    glm::vec3 ambientColor = glm::vec3(0.2) * lightColor; // Decrease Influence
    glm::vec3 diffuseColor = glm::vec3(0.5) * lightColor; // Decrease Influence

    /* Shader */
    shaderProgram[0].Use();
    
    /* Color */
    shaderProgram[0].SetVec3("fu_light.position", lightPosition.x, lightPosition.y, lightPosition.z);
    shaderProgram[0].SetVec3("fu_light.ambient", ambientColor.r, ambientColor.g, ambientColor.b);
    shaderProgram[0].SetVec3("fu_light.diffuse", diffuseColor.r, diffuseColor.g, diffuseColor.b);
    shaderProgram[0].SetVec3("fu_light.specular", 1.0, 1.0, 1.0); // White

    /* Material */
    shaderProgram[0].SetFloat("fu_material.shininess", 32.0);
    shaderProgram[0].SetVec3("fu_material.ambient", 1.0, 0.5, 0.31);
    shaderProgram[0].SetVec3("fu_material.diffuse", 1.0, 0.5, 0.31);
    shaderProgram[0].SetVec3("fu_material.specular", 0.5, 0.5, 0.5);

    /* View Position */
    glm::vec3 position = camera.GetPosition();
    shaderProgram[0].SetVec3("fu_viewPosition", position.x, position.y, position.z);

    /* Model */
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(0.0, 0.0, -5.0));
    model = glm::rotate(model, static_cast<float>(GetTime()), glm::vec3(0.5, 1.0, 0.0));
    shaderProgram[0].SetMat4("vu_model", model);

    /* Camera Movement */
    if(backward)
        camera.Move(Camera::Movement::Backward, GetElapsedTime());
    if(down)
        camera.Move(Camera::Movement::Down, GetElapsedTime());
    if(forward)
        camera.Move(Camera::Movement::Forward, GetElapsedTime());
    if(left)
        camera.Move(Camera::Movement::Left, GetElapsedTime());
    if(right)
        camera.Move(Camera::Movement::Right, GetElapsedTime());
    if(up)
        camera.Move(Camera::Movement::Up, GetElapsedTime());

    /* View */
    glm::mat4 view {camera.GetView()};
    shaderProgram[0].SetMat4("vu_view", view);

    /* Projection */
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glm::mat4 projection = glm::mat4(1.0);
    projection = glm::perspective(glm::radians(camera.GetZoom()), static_cast<double>(width) / static_cast<double>(height), 0.1, 100.0);
    shaderProgram[0].SetMat4("vu_projection", projection);

    /* Draw */
    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    /* Shader */
    shaderProgram[1].Use();

    /* Model */
    model = glm::mat4(1.0);
    model = glm::translate(model, lightPosition);
    model = glm::scale(model, glm::vec3(0.2)); // Smaller
    shaderProgram[1].SetMat4("vu_model", model);

    /* View */
    shaderProgram[1].SetMat4("vu_view", view);

    /* Projection */
    shaderProgram[1].SetMat4("vu_projection", projection);

    /* Draw */
    glBindVertexArray(vao[1]);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
 