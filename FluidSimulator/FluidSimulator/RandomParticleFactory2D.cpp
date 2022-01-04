#include "RandomParticleFactory2D.h"

RandomParticleFactory2D::RandomParticleFactory2D()
{
	// Use current time as the seed for random generator
	std::srand(std::time(nullptr));
}

/* Member Functions */
DynamicArray<Particle2D>* RandomParticleFactory2D::generate(const unsigned int numParticles)
{
	DynamicArray<Particle2D>* newParticleArray = new DynamicArray<Particle2D>(numParticles);

	float radius = 0.02f;
	FVector position(2U, new float[] {0.0f, 0.0f});
	FVector velocity(2U, new float[] {0.0f, 0.0f});
	FVector color(3U, new float[] {1.0f, 1.0f, 1.0f});
	Particle2D particle(radius, 1.0f, position, velocity, color);
	
	// Fill the array
	bool touching = false;
	float scalingFactor = 2 - 2 * radius;									// Keeps the particles from generating on an edge
	float offset = 1 - radius;												// ^
	for (int i = 0; i < numParticles; i++)
	{
		do
		{
			// Get a random position between -1 and 1
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

		// Get a random velocity (that's slow enough to not be annoying)
		velocity.getValues()[0] = (std::rand() > (RAND_MAX / 2) ? -1 : 1) *	// Negative or positive
			(((float)std::rand() / (float)RAND_MAX) * 0.3f + 0.1f);			// between 0.1 and 0.4
		velocity.getValues()[1] = (std::rand() > (RAND_MAX / 2) ? -1 : 1) * 
			(((float)std::rand() / (float)RAND_MAX) * 0.3f + 0.1f);
		particle.setVelocity(velocity);

		// Give the particles a random color
		color.getValues()[0] = ((float)std::rand() / (float)RAND_MAX);
		color.getValues()[1] = ((float)std::rand() / (float)RAND_MAX);
		color.getValues()[2] = ((float)std::rand() / (float)RAND_MAX);
		particle.setColor(color);

		(*newParticleArray).insert(particle);
	}

	return newParticleArray;
}