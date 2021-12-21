#pragma once

#ifndef ABSTRACTSIMULATION_H
#define ABSTRACTSIMULATION_H

#include "OpenGLWindow.h"
#include "AbstractParticle.h"
// OpenGL Mathematics
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

class AbstractSimulation
{
public:
	/* Description: Initializes the basic objects used by all simulations
	 *				Leaves the lists to be defined by derived classes
	 * Parameters: useIndices defines whether or not the EBO should be initialized
	 */
	AbstractSimulation(bool useIndices, bool fullScreen, const char* title, 
		unsigned int scrWidth = 512U, unsigned int scrHeight = 512U);

	/* Description: Updates and draws the particles
	 */
	virtual void update() = 0;		// Makes the class pure virtual

	/* Description: Deallocated the space used by the variables
	 */
	void deallocate();

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
	AbstractParticle** particles;
	// Particle Generator
};


#endif