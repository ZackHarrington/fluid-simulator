#pragma once

#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include "ShaderProgram.h"

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
// OpenGL Mathematics
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
// Cpp includes
#include <iostream>

class OpenGLWindow {
public:
	/* Description: Initializes the window to the desired screen size
	 * Parameters: If fullScreen is true, width and height don't need to be specified
	 */
	OpenGLWindow(bool fullScreen, const char* title = "Fluid Simulation", unsigned int scrWidth = 0U, unsigned int scrHeight = 0U);

	/* Description: Updates the window and appropriate shaders
	 */
	void update();

	// Getters / Setters
	/* Description: Returns whether the window should close or not
	 */
	bool shouldClose() const;

	/* Description: Deallocates resources used
	 */
	void deallocate();
private:
	unsigned int scrWidth;
	unsigned int scrHeight;
	GLFWwindow* window;
	ShaderProgram* shaderProgram;
	//float* vertices; // Objects?
	//unsigned int* indeces;

	/* Description: Called when an input device is used while the window is active
	 */
	void processInput(GLFWwindow* window);
};

/* Description: Called whenever the user resizes the window
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height);


#endif