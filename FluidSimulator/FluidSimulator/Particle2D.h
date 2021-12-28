#pragma once

#ifndef PARTICLE2D_H
#define PARTICLE2D_H

#include "AbstractParticle.h"
#include <math.h>

class Particle2D : public AbstractParticle
{
public:
	/* Description: Default constructor
	 */
	Particle2D() : AbstractParticle() {}
	/* Description: Initializes a 2D particle
	 * Parameters: position and velocity are two dimensional vertors, color is three dimensional in RGB
	 */
	Particle2D(float radius, float mass, FVector position, FVector velocity, FVector color) :
		AbstractParticle(radius, mass, position, velocity, color) {}

	/* Description: Creates an array of vertices, and indices, if not a nullptr, that can be used to draw the particle in OpenGL
	 * Parameters: resolution defines the number of sides the particle will have, minimum resolution is defined by the particle class
	 *				includeColor specifies whether or not to add a RGB value to each vertex
	 * Returns: A pointer to the vertexData is returned, it's size is placed into the specified variable, same goes for indices
	 */
	virtual float* generateOpenGLVertices(unsigned int resolution, bool includeColor, unsigned int* vertexDataSize,
		bool includeIndices = false, unsigned int* indicesSize = nullptr, unsigned int** indices = nullptr) override;

	// Temporary
	FVector getNextUpdatePosition(float timeMultiplier);

	/* Description: Computes the new velocities for the two colliding particles 
	 */
	void particleCollision(Particle2D& p);

	//void lineCollision()

	// Overloaded operators
	bool operator== (const Particle2D& p);
	bool operator!= (const Particle2D& p);
};


#endif