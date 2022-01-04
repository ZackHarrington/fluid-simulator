#pragma once

#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
// OpenGL Mathematics
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
// Cpp includes
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


class ShaderProgram
{
public:
    // Reads in files and builds shader
    ShaderProgram(const char* vertexPath, const char* fragmentPath);
    
    // Activates the shader program
    void use();

    // Getters / Setters - for uniforms
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec2(const std::string& name, const glm::vec2& value) const;
    void setVec2(const std::string& name, float x, float y) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    void setVec4(const std::string& name, const glm::vec4& value) const;
    void setVec4(const std::string& name, float x, float y, float z, float w) const;
    void setMat2(const std::string& name, const GLboolean transpose, const glm::mat2& matrix) const;
    void setMat3(const std::string& name, const GLboolean transpose, const glm::mat3& matrix) const;
    void setMat4(const std::string& name, const GLboolean transpose, const glm::mat4& matrix) const;

    // Deallocate at end of the program
    void deallocate();
private:
    unsigned int programID;

    // Check for compile errors
    void checkCompileErrors(unsigned int* shader, std::string type);
};

#endif