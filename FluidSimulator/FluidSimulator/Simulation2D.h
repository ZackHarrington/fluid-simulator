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
	 * Parameters:
	 */
	Simulation2D(bool fullScreen, const char* title = "2D Fluid Simulation",
		unsigned int scrWidth = 512U, unsigned int scrHeight = 512U) :
		AbstractSimulation<Particle2D>(true, fullScreen, title, scrWidth, scrHeight)
	{
		particleFactory = new RandomParticleFactory2D();
		particles = particleFactory->generate(100);
	}

	/* Description: Updates and draws the particles
	 */
	virtual void update() override;
private:
	/* Description: Updates the particles and checks for collisions
	 */
	void updateParticles();

	/* Description: Updates the vertices based on the particle's locations
	 */
	void updateVertices(unsigned int resolution);
};


#endif