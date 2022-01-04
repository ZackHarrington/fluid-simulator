#include "ShaderProgram.h"

// Reads in files and builds shader
ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // Enable exceptions to be thrown
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
    // Read in the files
    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        // Read in the buffers as streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // Close files when complete
        vShaderFile.close();
        fShaderFile.close();

        // Convert stream to string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    // Convert strings into c strings (char*) for use with OpenGL
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // Compile the shaders
    unsigned int vertex, fragment;

    // Vertex
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(&vertex, "VERTEX");

    // Fragment
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(&fragment, "FRAGMENT");

    // Shader Program
    programID = glCreateProgram();
    glAttachShader(programID, vertex);
    glAttachShader(programID, fragment);
    glLinkProgram(programID);
    checkCompileErrors(nullptr, "PROGRAM");

    // Delete shaders
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

// *** Public Member Functions ***
// Activates the shader program
void ShaderProgram::use()
{
    glUseProgram(programID);
}

// Getters / Setters - for uniforms
void ShaderProgram::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
}
void ShaderProgram::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}
void ShaderProgram::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}
void ShaderProgram::setVec2(const std::string& name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
}
void ShaderProgram::setVec2(const std::string& name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(programID, name.c_str()), x, y);
}
void ShaderProgram::setVec3(const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
}
void ShaderProgram::setVec3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(programID, name.c_str()), x, y, z);
}
void ShaderProgram::setVec4(const std::string& name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
}
void ShaderProgram::setVec4(const std::string& name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(programID, name.c_str()), x, y, z, w);
}
void ShaderProgram::setMat2(const std::string& name, const GLboolean transpose, const glm::mat2& mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(programID, name.c_str()), 1, transpose, &mat[0][0]);
}
void ShaderProgram::setMat3(const std::string& name, const GLboolean transpose, const glm::mat3& mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(programID, name.c_str()), 1, transpose, &mat[0][0]);
}
void ShaderProgram::setMat4(const std::string& name, const GLboolean transpose, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, transpose, &mat[0][0]);
}

// Deallocate at end of program
void ShaderProgram::deallocate()
{
    glDeleteProgram(programID);
}


// *** Private member functions ***
// Check for compile errors
void ShaderProgram::checkCompileErrors(unsigned int* shader, std::string type)
{
    int success;
    char infoLog[512];

    if (type == "PROGRAM") 
    {
        glGetProgramiv(programID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(programID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::" << type << "::LINKING_FAILED\n" << infoLog << std::endl;
        }
    }
    else if (type == "VERTEX" || type == "FRAGMENT")
    {
        glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(*shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        };
    }
    else 
    {
        std::cout << "ERROR::SHADER::INVALID_TYPE" << std::endl;
    }
}