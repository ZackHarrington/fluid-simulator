#pragma once

#pragma once

#ifndef ABSTRACTPARTICLE_H
#define ABSTRACTPARTICLE_H

#include "FVector.h"

class AbstractParticle
{
public:
	/* Description: Initializes a particle
	 * Parameters: color is in RGB
	 */
	AbstractParticle(float radius, float mass, FVector position, FVector velocity, FVector color);

	// Getters / Setters
	/* Description: Returns the particle's radius
	 */
	float getRadius() const;
	/* Description: Returns the particle's mass
	 */
	float getMass() const;
	/* Description: Returns the particle's position as a float vector
	 */
	FVector getPosition() const;
	/* Description: Returns the particle's velocity as a float vector
	 */
	FVector getVelocity() const;
	/* Description: Returns the particle's color as a float vector
	 */
	FVector getColor() const;

	/* Description: Sets the particle's radius
	 */
	void setRadius(float radius);
	void setRadius(int radius);
	void setRadius(double radius);
	/* Description: Sets the particle's mass
	 */
	void setMass(float mass);
	void setMass(int mass);
	void setMass(double mass);
	/* Description: Sets the particle's position as a float vector
	 */
	void setPosition(FVector position);
	/* Description: Sets the particle's velocity as a float vector
	 */
	void setVelocity(FVector velocity);
	/* Description: Sets the particle's color as a float vector
	 */
	void setColor(FVector color);

	/* Description: Creates an array of vertices, and indices, if specified, that can be used to draw the particle in OpenGL
	 * Parameters: resolution defines the number of sides the particle will have, minimum resolution is defined by the particle class
	 *				includeColor specifies whether or not to add a RGB value to each vertex
	 *				includeIndices specifies whether or not to build an indices array at the desired location
	 * Returns: A pointer to the vertexData is returned, it's size is placed into the specified variable, same goes for indices
	 */
	virtual float* generateOpenGLVertices(unsigned int resolution, bool includeColor, unsigned int* vertexDataSize, 
		bool includeIndices = false, unsigned int* indicesSize = nullptr, unsigned int** indices = nullptr) = 0;

protected:
	float radius;
	float mass;
	FVector position;
	FVector velocity;
	FVector color;
};


#endif