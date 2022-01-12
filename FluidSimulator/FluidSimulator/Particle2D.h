#pragma once

#ifndef PARTICLE2D_H
#define PARTICLE2D_H

#include "AbstractParticle.h"
#include "Line.h"

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
	Particle2D(const float radius, const float mass, 
		const FVector position, const FVector velocity, const FVector color) :
		AbstractParticle(radius, mass, position, velocity, color) {}

	/* Description: Creates an array of vertices, and indices, if not a nullptr, that can be used to draw the particle in OpenGL
	 * Parameters: resolution defines the number of sides the particle will have, minimum resolution is defined by the particle class
	 *				includeColor specifies whether or not to add a RGB value to each vertex
	 * Returns: A pointer to the vertexData is returned, it's size is placed into the specified variable, same goes for indices
	 */
	virtual float* generateOpenGLVertices(const unsigned int resolution, const bool includeColor, 
		unsigned int* vertexDataSize, const bool includeIndices = false, 
		unsigned int* indicesSize = nullptr, unsigned int** indices = nullptr) const override;

	// Overloaded operators
	bool operator== (const Particle2D& p);
	bool operator!= (const Particle2D& p);
};


#endif