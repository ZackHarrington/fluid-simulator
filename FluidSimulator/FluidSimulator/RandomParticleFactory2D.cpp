#include "RandomParticleFactory2D.h"

RandomParticleFactory2D::RandomParticleFactory2D(const float speedFactor, const bool useLogicalMass)
{
	this->speedFactor = speedFactor;
	this->useLogicalMass = useLogicalMass;
	this->averageRadius = 0.0f;

	// Use current time as the seed for random generator
	std::srand(std::time(nullptr));
}

/* Member Functions */
DynamicArray<Particle2D>* RandomParticleFactory2D::generate(const unsigned int numParticles)
{
	DynamicArray<Particle2D>* newParticleArray = new DynamicArray<Particle2D>(numParticles);

	float radius = 1.0f;
	float mass = 1.0f;
	FVector position(2U, new float[] {0.0f, 0.0f});
	FVector velocity(2U, new float[] {0.0f, 0.0f});
	FVector color(3U, new float[] {1.0f, 1.0f, 1.0f});
	Particle2D particle(radius, mass, position, velocity, color);
	
	// Fill the array
	bool touching = false;
	float scalingFactor = 0;
	float offset = 0;
	for (int i = 0; i < numParticles; i++)
	{
		// Random radius
		scalingFactor = 0.03f;
		offset = 0.01f;
		radius = (((float)std::rand() / (float)RAND_MAX) * scalingFactor + offset);
		averageRadius = (offset * 2 + scalingFactor) / 2;					// average of the lowest possible, offset, and the highest, offset + scaling factor
		particle.setRadius(radius);

		// Random mass
		if (useLogicalMass)
			mass = 2 * 3.14159 * pow(radius, 2);
		else
			mass = (((float)std::rand() / (float)RAND_MAX) * 0.03f + 0.01f);
		particle.setMass(mass);

		// Random position
		touching = false;
		scalingFactor = 2 - 2 * radius;										// Keeps the particles from generating on an edge
		offset = 1 - radius;												// ^
		do
		{
			// Get a position between -1 and 1
			position.getValues()[0] = ((float)std::rand() / (float)RAND_MAX) * scalingFactor - offset;
			position.getValues()[1] = ((float)std::rand() / (float)RAND_MAX) * scalingFactor - offset;
			touching = false;
			// Check that there isn't another particle in the way
			for (int j = 0; j < i; j++)
			{
				if (position.getDistance((*newParticleArray)[j].getPosition()) < (2 * radius))
					touching = true;
			}
		} while (touching);
		particle.setPosition(position);

		// Random velocity (that's slow enough to not be annoying)
		velocity.getValues()[0] = (std::rand() > (RAND_MAX / 2) ? 1 : -1) *	// positive or negative
			(((float)std::rand() / (float)RAND_MAX) * 0.3f + 0.1f);			// between 0.1 and 0.4
		velocity.getValues()[1] = (std::rand() > (RAND_MAX / 2) ? 1 : -1) * 
			(((float)std::rand() / (float)RAND_MAX) * 0.3f + 0.1f);
		if (useLogicalMass)
			// since mass is related to radius this ensures we don't set the velocity to a very small number for small radii
			velocity = velocity * (mass/averageRadius) * speedFactor;
		particle.setVelocity(velocity);

		// Random color (RGB)
		color.getValues()[0] = ((float)std::rand() / (float)RAND_MAX);
		color.getValues()[1] = ((float)std::rand() / (float)RAND_MAX);
		color.getValues()[2] = ((float)std::rand() / (float)RAND_MAX);
		particle.setColor(color);

		newParticleArray->insert(particle);
	}

	return newParticleArray;
}