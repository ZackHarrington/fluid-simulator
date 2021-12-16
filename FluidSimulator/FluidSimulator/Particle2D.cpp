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

void Particle2D::generateOpenGLVertices(unsigned int resolution, bool includeColor, float* vertices, bool useIndices, unsigned int* indices)
{
	unsigned int resolutionToUse = resolution;
	if (resolution < 3) {
		std::cout << "Illegal Argument: Resolution must be three or greater!" << std::endl;
		resolutionToUse = 3;
	}

	// The circles are sliced up like a pie where each slice cooresponds to a triangle
	unsigned int numVertices = 0;
	unsigned int numFloats = 0;
	float radiansPerSlice = (2 * 3.14159265) / resolutionToUse;	// 2pi/resolution
	if (useIndices)
	{
		// With indices we only need to specify the center and each of the outer points around the 'circle'
		// Then, with indices, we can specify how to draw each pie slice
		// (center + each outer point) * 3 because they are 3D vectors (z filled with 0)
		// The last part says if we are including color information we'll need an additional 3D vector per point for RGB information
		numVertices = (1 + resolutionToUse);
		numFloats = numVertices * 3 * (includeColor ? 2 : 1);
		vertices = new float[numFloats];

		// Add center vertex
		vertices[0] = position.getValues()[0];				// x
		vertices[1] = position.getValues()[1];				// y
		vertices[2] = 0.0f;									// z
		if (includeColor)
		{
			vertices[3] = color.getValues()[0];				// R
			vertices[4] = color.getValues()[1];				// G
			vertices[5] = color.getValues()[2];				// B
		}

		// Fill vertices loop
		for (int i = 1; i <= numVertices; i++)				// start at 1 because we already added the center
		{
			vertices[6 * i]		= position.getValues()[0] + cos(radiansPerSlice * (i - 1));
			vertices[6 * i + 1] = position.getValues()[1] + sin(radiansPerSlice * (i - 1));
			vertices[6 * i + 2] = 0.0f;
			if (includeColor)
			{
				vertices[6 * i + 3] = color.getValues()[0];
				vertices[6 * i + 4] = color.getValues()[1];
				vertices[6 * i + 5] = color.getValues()[2];
			}
		}

		// Fill indices loop
		indices = new unsigned int[resolutionToUse * 3];	// each triangle has 3 points
		for (int i = 0; i < resolutionToUse; i++)
		{
			indices[3 * i] = 0;								// center
			indices[3 * i] = 1 + i;							// first outer vertex
			indices[3 * i] = 2 + i;							// second outer vertex
		}
	}
	else
	{
		// Without indices we have to specify each pie slice individually with three points
		numVertices = (3 * resolutionToUse);
		numFloats = numVertices * 3 * (includeColor ? 2 : 1);
		vertices = new float[numFloats];

		// Fill vertices loop
		for (int i = 0; i < numVertices; i++)
		{
			switch (i % 3)
			{
			case 0:											// first vertex is the center
				vertices[6 * i] = position.getValues()[0];
				vertices[6 * i + 1] = position.getValues()[1];
				vertices[6 * i + 2] = 0.0f;
				break;
			case 1:											// second is the first outer vertex
				vertices[6 * i] = position.getValues()[0] + cos(radiansPerSlice * i);
				vertices[6 * i + 1] = position.getValues()[1] + sin(radiansPerSlice * i);
				vertices[6 * i + 2] = 0.0f;
				break;
			case 2:											// third is the second outer vertex
				vertices[6 * i] = position.getValues()[0] + cos(radiansPerSlice * (i + 1));
				vertices[6 * i + 1] = position.getValues()[1] + sin(radiansPerSlice * (i + 1));
				vertices[6 * i + 2] = 0.0f;
				break;
			}
			if (includeColor)
			{
				vertices[6 * i + 3] = color.getValues()[0];
				vertices[6 * i + 4] = color.getValues()[1];
				vertices[6 * i + 5] = color.getValues()[2];
			}
		}
	}
}


/* Non-Member Functions */

void collision(Particle2D* p1, Particle2D* p2)
{
	//
}