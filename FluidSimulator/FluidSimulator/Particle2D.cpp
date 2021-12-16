#include "Particle2D.h"

/* Constructor */
Particle2D::Particle2D(float radius, float mass, FVector* position, FVector* velocity, FVector* color)
{
	this->radius = radius;
	this->mass = mass;
	this->position = *position;
	this->velocity = *velocity;
	this->color = *color;
}


/* Public Member Functions */
float Particle2D::getRadius() const				{ return radius; }
float Particle2D::getMass() const				{ return mass; }
FVector Particle2D::getPosition() const			{ return position; }
FVector Particle2D::getVelocity() const			{ return velocity; }

void Particle2D::setRadius(float radius)		{ this->radius = radius; }
void Particle2D::setRadius(int radius)			{ this->radius = (float)radius; }
void Particle2D::setRadius(double radius)		{ this->radius = (float)radius; }
void Particle2D::setMass(float mass)			{ this->mass = mass; }
void Particle2D::setMass(int mass)				{ this->mass = (float)mass; }
void Particle2D::setMass(double mass)			{ this->mass = (float)mass; }
void Particle2D::setPosition(FVector position)	{ this->position = position; }
void Particle2D::setVelocity(FVector velocity)	{ this->velocity = velocity; }

void Particle2D::update()
{
	//
}

void Particle2D::generateOpenGLVertices(int resolution, bool includeColor, float* vertices, bool useIndices, unsigned int* indices)
{
	// The circles are sliced up like a pie where each slice cooresponds to a triangle
	unsigned int numVertices = 0;
	if (useIndices)
	{
		// With indices we only need to specify the center and each of the outer points around the 'circle'
		// Then, with indices, we can specify how to draw each pie slice
		// (center + each outer point) * 3 because they are 3D vectors (z filled with 0)
		// The last part says if we are including color information we'll need an additional 3D vector per point for RGB information
		numVertices = (1 + resolution) * 3 * (includeColor ? 2 : 1);
		// ...
	}
	else
	{
		// Without indices we have to specify each pie slice individually with three points
		numVertices = (3 * resolution) * 3;
		// ...
	}
}


/* Non-Member Functions */

void collision(Particle2D* p1, Particle2D* p2)
{
	//
}