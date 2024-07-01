/****************************************************************************************************
 * Include
 ****************************************************************************************************/

#include "Core/ShaderProgram.h"

/****************************************************************************************************
 * Class
 ****************************************************************************************************/

/*** Constructor ***/
ShaderProgram::ShaderProgram()
    : programId {}
{
}

/*** Destructor ***/
ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(programId);
}

/*** Method (Private) ***/
GLuint ShaderProgram::CompileShader(const std::string FileName, const GLenum Type) const
{
    /*** Compile Shader ***/
    /* Read File */
    std::string file {ReadFile(FileName)};

    /* Compile */
    GLuint shaderId {glCreateShader(Type)};
    const GLchar* const code {file.c_str()};
    glShaderSource(shaderId, 1, &code, NULL);
    glCompileShader(shaderId);

    /* Check Success */
    std::string name {};
    switch(Type)
    {
        case GL_FRAGMENT_SHADER:
            name = "Fragment";
            break;
        case GL_VERTEX_SHADER:
            name = "Vertex";
            break;
        default:
            name = "Unknown";
            break;
    }
    GLint success {};
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if(success)
        std::cout << std::format("[INFO] Compile {} Shader (ID = {})\n", name, shaderId);
    else
        std::cout << std::format("[ERROR] Compile {} Shader\n", name);

    /* Print Error Message */
    if(success == GL_FALSE)
    {
        GLint maxLength {};
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);
        std::string infoLog {};
        infoLog.resize(maxLength);
        glGetShaderInfoLog(shaderId, maxLength, &maxLength, &infoLog[0]);
        std::cout << std::format("{}", infoLog);
        glDeleteShader(shaderId);
    }

    return shaderId;
}

std::string ShaderProgram::ReadFile(const std::string FileName) const
{
    std::string fileContents {};

    /*** Read File ***/
    /* Open File */
    std::ifstream file {};
    file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    file.open(FileName);
    if(!file.is_open())
    {
        std::cout << std::format("[ERROR] Open File \"{}\"\n", FileName);
        return fileContents;
    }

    /* Read File */
    std::stringstream ss {};
    ss << file.rdbuf();
    file.close();

    return ss.str();
}

/*** Method (Public) ***/
void ShaderProgram::CreateProgram(const std::string FragmentShaderFileName, const std::string VertexShaderFileName)
{
    /*** Create Program ***/
    /* Compile */
    GLuint fragmentShaderId {CompileShader(FragmentShaderFileName, GL_FRAGMENT_SHADER)};
    GLuint vertexShaderId {CompileShader(VertexShaderFileName, GL_VERTEX_SHADER)};

    /* Link */
    programId = glCreateProgram();
    glAttachShader(programId, fragmentShaderId);
    glAttachShader(programId, vertexShaderId);
    glLinkProgram(programId);

    /* Success */
    GLint success {};
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if(success)
        std::cout << std::format("[INFO] Link Shader Program (ID = {})\n", programId);
    else
        std::cout << std::format("[ERROR] Link Shader Program\n");

    /* Print Error Message */
    if(success == GL_FALSE)
    {
        GLint maxLength {};
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &maxLength);
        std::string infoLog {};
        infoLog.resize(maxLength);
        glGetProgramInfoLog(programId, maxLength, &maxLength, &infoLog[0]);
        std::cout << std::format("{}", infoLog);
        glDeleteProgram(programId);
    }

    /* Clean Up */
    glDeleteShader(fragmentShaderId);
    glDeleteShader(vertexShaderId);
}

GLint ShaderProgram::GetAttributeLocation(const std::string Name) const
{
    return glGetAttribLocation(programId, Name.c_str());
}

GLint ShaderProgram::GetUniformLocation(const std::string Name) const
{
    return glGetUniformLocation(programId, Name.c_str());
}

void ShaderProgram::Use() const
{
    glUseProgram(programId);
}
