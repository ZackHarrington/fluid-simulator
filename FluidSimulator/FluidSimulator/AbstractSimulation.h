#pragma once

#ifndef ABSTRACTSIMULATION_H
#define ABSTRACTSIMULATION_H

#include "OpenGLWindow.h"
#include "DynamicArray.h"
#include "AbstractParticleFactory.h"

template <typename ParticleType>
class AbstractSimulation
{
public:
	/* Description: Initializes the basic objects used by all simulations
	 *				Leaves the OpenGL lists and the particle generator to be defined by derived classes
	 * Parameters: useIndices defines whether or not the EBO should be initialized
	 */
	AbstractSimulation(bool useIndices, bool fullScreen, const char* title,
		unsigned int scrWidth = 512U, unsigned int scrHeight = 512U)
	{
		// The window must be defined first so an OpenGL context exists
		window = new OpenGLWindow(fullScreen, title, scrWidth, scrHeight);
		// Initialize Shaders using local file paths
		shaderProgram = new ShaderProgram("vertexShader.vs", "fragmentShader.fs");

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		if (useIndices)
			glGenBuffers(1, &EBO);
		else
			EBO = NULL;

		vertexData = nullptr;
		vertexDataSize = 0;
		indices = nullptr;
		indicesSize = 0;
	}

	/* Description: Updates and draws the particles
	 */
	virtual void update() = 0;				// Makes the class pure virtual

	/* Description: Returns whether or not the OpenGLWindow has been closed or not
	 */
	bool shouldClose() { return window->shouldClose(); }

	/* Description: Deallocated the space used by the variables
	 */
	void deallocate()
	{
		window->deallocate();
		shaderProgram->deallocate();

		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		if (EBO != NULL)
			glDeleteBuffers(1, &EBO);

		if (vertexData != nullptr)
			delete[] vertexData;
		if (indices != nullptr)
			delete[] indices;

		particles->deallocate();
	}

protected:
	// OpenGL variables
	OpenGLWindow* window;
	ShaderProgram* shaderProgram;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	float* vertexData;
	unsigned int vertexDataSize;
	unsigned int* indices;
	unsigned int indicesSize;

	// Simulation variables
	DynamicArray<ParticleType>* particles;	// Defaults to a capacity of 10 to start
	AbstractParticleFactory<ParticleType>* particleFactory;
};


#endif