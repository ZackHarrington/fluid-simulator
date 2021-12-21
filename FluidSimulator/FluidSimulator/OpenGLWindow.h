#pragma once

#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include "ShaderProgram.h"

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
// Cpp includes
#include <iostream>

class OpenGLWindow {
public:
	/* Description: Initializes the window to the desired screen size, defaults to 512x512
	 * Parameters: If fullScreen is true, width and height don't need to be specified
	 */
	OpenGLWindow(bool fullScreen, const char* title, unsigned int scrWidth = 512U, unsigned int scrHeight = 512U);

	/* Description: Draws / redraws the window with the specified vertex array and shader program
	 * Parameters: numElements should be the number of vertices when useIndices is false, and the number of triangles when true
	 */
	void draw(ShaderProgram* shaderProgram, unsigned int VAO, bool useIndices, unsigned int numElememts);

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

	/* Description: Called when an input device is used while the window is active
	 */
	void processInput(GLFWwindow* window);
};

/* Description: Called whenever the user resizes the window
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height);


#endif