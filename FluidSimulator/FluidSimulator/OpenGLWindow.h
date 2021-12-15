#pragma once

#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include "ShaderProgram.h"

class OpenGLWindow {
public:
	/* Description: initializes the window to the desired screen size
	 * Parameters: if fullScreen is true, width and height don't need to be specified
	 */
	OpenGLWindow(bool fullScreen, unsigned int scrWidth = 0, unsigned int scrHeight = 0);

	/* Description: updates the window and appropriate shaders
	 */
	void update();

	// Getters / Setters
	/* Description: returns whether the window should close or not
	 */
	bool shouldClose() const;

	/* Description: deallocates resources used
	 */
	void deallocate();
private:
	unsigned int scrWidth;
	unsigned int scrHeight;
	GLFWwindow* window;
	ShaderProgram* shaderProgram;
	//float* vertices; // Objects?
	//unsigned int* indeces;

	/* Description: called when an input device is used while the window is active
	 */
	void processInput(GLFWwindow* window);
};

/* Description: called whenever the user resizes the window
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height);


#endif