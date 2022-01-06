#pragma once

#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include "ShaderProgram.h"
#include "DynamicArray.h"
#include "AbstractParticle.h"
#include "ColoringStyle.h"

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
	OpenGLWindow(const bool fullScreen, const char* title, 
		const unsigned int scrWidth = 512U, const unsigned int scrHeight = 512U);
	/* Description: Deallocates resources
	 */
	~OpenGLWindow();

	/* Description: Draws the specified particles to the window
	 */
	void draw(const AbstractParticle* particles, const unsigned int numParticles,
		const bool setOneToRed = false, ColoringStyle coloringStyle = ColoringStyle::DEFAULT_WHITE);

	// Getters / Setters
	/* Description: Returns whether the window should close or not
	 */
	bool shouldClose() const;
	/* Description: Updates the screen width to the specified size
	 */
	void setScreenWidth(const unsigned int scrWidth);
	/* Description: Updates the screen height to the specifed size
	 */
	void setScreenHeight(const unsigned int scrHeight);
	/* DescriptionL Updates the screen to the specifed size
	 */
	void setScreenSize(const unsigned int scrWidth, const unsigned int scrHeight);
	/* Description: Sets the VBO with a default particle
	 * Parameters: To draw properly the particle should be centered at the origin and have a radius of 1.0,
					all particles will be drawn as a scaled and mapped version of this particle
	 */
	void setVBOFromParticle(const AbstractParticle* particle, const unsigned int resolution, const bool useIndices = false);

	/* Description: Deallocates resources used
	 */
	void deallocate();
private:
	// Window objects
	unsigned int scrWidth;
	unsigned int scrHeight;
	GLFWwindow* window;

	// Draw objects
	ShaderProgram* shaderProgram;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	bool useIndices;				// Defined in setVBOFromParticle function
	unsigned int numElementsToDraw;	// ^
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	/* Description: Called when an input device is used while the window is active
	 */
	void processInput(GLFWwindow* window);

	/* Description: Converts a RGB value to HSV
	 */
	glm::vec3 toHSV(const glm::vec3 RGB);
	/* Description: Returns the corresponding Hue value of a RGB color
	 */
	float getHue(const glm::vec3 RGB);
	/* Description: Converts a HSV value to RGB
	 */
	glm::vec3 toRGB(const glm::vec3 HSV);

	/* Description: Clamps values outside of the range to the high and low values
	 * Couldn't get visual studio to recognise std::clamp as a function so here's my implementation
	 */
	void clamp(float& value, const float& low, const float& high);
};

/* Description: Called whenever the user resizes the window
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height);


#endif