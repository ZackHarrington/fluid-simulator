#pragma once

#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include "ShaderProgram.h"
#include "FVector.h"

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
	/* Description: Initializes the window to the desired screen size, defaults to 512x512
	 * Parameters: If fullScreen is true, width and height don't need to be specified
	 */
	OpenGLWindow(bool fullScreen, const char* title, unsigned int scrWidth = 512U, unsigned int scrHeight = 512U);

	/* Description: Draws / redraws the window with the specified vertex array and shader program
	 * Parameters: numVertices should be the number of triangles * 3
	 */
	void draw(ShaderProgram* shaderProgram, unsigned int VAO, bool useIndices, unsigned int numVertices);
	/* Description: Draws / redraws the window with the specified vertex array, shader program, and element array
	 * Parameters: numVertices should be the number of triangles * 3, numElements should be 
	 */
	void draw(ShaderProgram* shaderProgram, unsigned int VAO, bool useIndices, 
		unsigned int numVertices, glm::vec3* elementPositions, unsigned int numElements);

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
	glm::mat4 model;

	/* Description: Called when an input device is used while the window is active
	 */
	void processInput(GLFWwindow* window);
};

/* Description: Called whenever the user resizes the window
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height);


#endif