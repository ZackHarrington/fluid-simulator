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
    void set4x4Matrix(const std::string& name, GLboolean transpose, glm::mat4* matrix) const;

    // Deallocate at end of the program
    void deallocate();
private:
    unsigned int programID;

    // Check for compile errors
    void checkCompileErrors(unsigned int* shader, std::string type);
};

#endif