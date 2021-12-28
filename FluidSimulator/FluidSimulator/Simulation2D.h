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
		particles = *(particleFactory->generate(100));

		/*float radius = 0.02;
		FVector position(2U, new float[] {0.0f, -0.005f});
		FVector velocity(2U, new float[] {-0.5f, 0.0f});
		FVector color(3U, new float[] {1.0f, 1.0f, 1.0f});
		Particle2D particle(radius, 1.0f, position, velocity, color);
		particles.insert(particle);
		particle.setPosition(FVector(2U, new float[] {0.5f, 0.016f}));
		particle.setVelocity(FVector(2U, new float[] {-1.0f, 0.0f}));
		particles.insert(particle);*/

		// Temporary - assuming radius are the same size
		FVector zeroVec2D(2U, new float[] {0.0f, 0.0f});
		FVector color2(3U, new float[] {1.0f, 1.0f, 1.0f});
		Particle2D particle2(particles[0].getRadius(), 1.0f, zeroVec2D, zeroVec2D, color2);
		vertexData = particle2.generateOpenGLVertices(
			16, true, &vertexDataSize, true, &indicesSize, &indices);
	}

	/* Description: Updates and draws the particles
	 */
	virtual void update() override;
private:
	/* Description: Updates the particles and checks for collisions
	 */
	void updateParticles(float timeSinceLastUpdate);

	/* Description: Checks for collisions with the border and adjust's the velocity accordingly
	 */
	void checkEdgeCollisions(int particleIndex, const FVector& newPosition);

	/* Description: Updates the vertices based on the particle's locations
	 */
	void updateVertices(unsigned int resolution);
};


#endif