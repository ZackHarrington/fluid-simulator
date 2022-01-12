#pragma once

#pragma once

#ifndef ABSTRACTPARTICLE_H
#define ABSTRACTPARTICLE_H

#include "FVector.h"

class AbstractParticle
{
public:
	/* Description: Default constructor; initializes the partical to basic values
	 */
	AbstractParticle();
	/* Description: Initializes a particle
	 * Parameters: color is in RGB
	 */
	AbstractParticle(const float radius, const float mass, 
		const FVector position, const FVector velocity, const FVector color);
	/* Description: Deallocates resources
	 */
	virtual ~AbstractParticle();

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
	void setRadius(const float radius);
	void setRadius(const int radius);
	void setRadius(const double radius);
	/* Description: Sets the particle's mass
	 */
	void setMass(const float mass);
	void setMass(const int mass);
	void setMass(const double mass);
	/* Description: Sets the particle's position as a float vector
	 */
	void setPosition(const FVector position);
	/* Description: Sets the particle's velocity as a float vector
	 */
	void setVelocity(const FVector velocity);
	/* Description: Sets the particle's color as a float vector
	 */
	void setColor(const FVector color);

	/* Description: Returns the position the particle will end up at, should nothing change
	 */
	virtual FVector nextUpdatePosition(const float timeMultiplier);
	/* Description: Updates the particle based on it's velocity and the time elapsed
	 * Note: Calls nextUpdatePosition by default so update doesn't need to be overridden if not necessary
	 */
	virtual void update(const float timeMultiplier);

	/* Description: Creates an array of vertices, and indices, if specified, that can be used to draw the particle in OpenGL
	 * Parameters: resolution defines the number of sides the particle will have, minimum resolution is defined by the particle class
	 *				includeColor specifies whether or not to add a RGB value to each vertex
	 *				includeIndices specifies whether or not to build an indices array at the desired location
	 * Returns: A pointer to the vertexData is returned, it's size is placed into the specified variable, same goes for indices
	 */
	virtual float* generateOpenGLVertices(const unsigned int resolution, const bool includeColor, 
		unsigned int* vertexDataSize, const bool includeIndices = false, 
		unsigned int* indicesSize = nullptr, unsigned int** indices = nullptr) const = 0;

protected:
	float radius;
	float mass;
	FVector position;
	FVector velocity;
	FVector color;
};


#endif