#pragma once

#ifndef PARTICLE2D_H
#define PARTICLE2D_H

#include "FVector.h"
#include <math.h>

class Particle2D 
{
public:
	/* Description: Initializes a 2D particle
	 * Parameters: color is in RGB, defaults to white if not specified
	 */
	Particle2D(float radius, float mass, FVector* position, FVector* velocity, 
		FVector* color = new FVector(3U, new float[] {1.0f, 1.0f, 1.0f}));

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

	// need some sort of time step? maybe the list of particles? or maybe thats for something else to handle not the particle itself, add a bounce off vector that calls calculate after it's activated
	void update();

	/* Description: Creates an array of vertices, and indices if specified, that can be used to draw the particle in OpenGL
	   Parameters: resolution defines the number of sides the particle will have, 3 is the minimum resolution
					includeColor specifies whether or not to add an RGB value to each vertex
	 */
	void generateOpenGLVertices(int resolution, bool includeColor, float* vertices,
		bool useIndices = false, unsigned int* indices = nullptr);

private:
	float radius;
	float mass;
	FVector position;
	FVector velocity;
	FVector color;
};

/* Description: Does the necessary compution behind a particle collision
 */
void collision(Particle2D* p1, Particle2D* p2);


#endif