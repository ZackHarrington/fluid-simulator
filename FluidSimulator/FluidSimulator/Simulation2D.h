#pragma once

#ifndef SIMULATION2D
#define SIMULATION2D

#include "AbstractSimulation.h"
#include "Particle2D.h"

class Simulation2D : public AbstractSimulation
{
public:
	/* Description: Initializes the 2D simulation
	 * Parameters:
	 */
	Simulation2D(bool fullScreen, const char* title = "2D Fluid Simulation",
		unsigned int scrWidth = 512U, unsigned int scrHeight = 512U) :
		AbstractSimulation(true, fullScreen, title, scrWidth, scrHeight)
	{
		// Temporary Particle Generator
		particles = new AbstractParticle*[1];										// Store as base class pointers
		FVector position(2U, new float[] {0.0f, 0.0f});
		FVector velocity(2U, new float[] {1.0f, 1.0f});
		FVector color(3U, new float[] {1.0f, 1.0f, 1.0f});
		for (int i = 0; i < 1; i++)
		{
			particles[i] = new Particle2D(0.1f, 1.0f, position, velocity, color);	// Save as derived class variables
		}
	}

	/* Description: Updates and draws the particles
	 */
	virtual void update() override;

	// Temporary
	bool shouldClose() { return window->shouldClose(); }

private:
	/* Description: Updates the particles and checks for collisions
	 */
	void updateParticles();

	/* Description: Updates the vertices based on the particle's locations
	 */
	void updateVertices(unsigned int resolution);
};


#endif