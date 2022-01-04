#pragma once

#ifndef SIMULATION2D
#define SIMULATION2D

#include "AbstractSimulation.h"
#include "Particle2D.h"
#include "RandomParticleFactory2D.h"

class Simulation2D : public AbstractSimulation<Particle2D>
{
public:
	/* Description: Initializes the 2D simulation
	 */
	Simulation2D(const ColoringStyle coloringStyle = ColoringStyle::DEFAULT_WHITE, const unsigned int numParticles = 0) : 
		AbstractSimulation<Particle2D>(coloringStyle, numParticles)
	{
		// Defines particle factory here instead of in base class
		particleFactory = new RandomParticleFactory2D();
		particles = *(particleFactory->generate(numParticles));

		/*float radius = 0.02;
		FVector position(2U, new float[] {0.0f, -0.005f});
		FVector velocity(2U, new float[] {-0.5f, 0.0f});
		FVector color(3U, new float[] {1.0f, 1.0f, 1.0f});
		Particle2D particle(radius, 1.0f, position, velocity, color);
		particles.insert(particle);
		particle.setPosition(FVector(2U, new float[] {0.5f, 0.016f}));
		particle.setVelocity(FVector(2U, new float[] {-1.0f, 0.0f}));
		particles.insert(particle);*/
	}

	/* Description: Updates the particles
	 * Parameters: Time since the last update was called
	 */
	virtual void update(const float deltaTime) override;
private:

	/* Description: Checks for collisions with the border and adjust's the velocity accordingly
	 */
	void checkEdgeCollisions(const int particleIndex, const FVector& newPosition);
};


#endif