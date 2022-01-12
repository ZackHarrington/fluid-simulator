#pragma once

#ifndef SIMULATION2D
#define SIMULATION2D

#include "AbstractSimulation.h"
#include "Particle2D.h"
#include "RandomParticleFactory2D.h"

#include <math.h>

class Simulation2D : public AbstractSimulation<Particle2D>
{
public:
	/* Description: Initializes the 2D simulation
	 */
	Simulation2D(const ColoringStyle coloringStyle = ColoringStyle::DEFAULT_WHITE, 
		const unsigned int numParticles = 0, AbstractParticleFactory<Particle2D>* particleFactory = nullptr) :
		AbstractSimulation<Particle2D>(coloringStyle, numParticles, particleFactory)
	{
		//// Defines particle factory here instead of in base class
		//particleFactory = new RandomParticleFactory2D(1.0f, true);
		//particles = *(particleFactory->generate(numParticles));
		
		/*float radius = 0.02;
		FVector position(2U, new float[] {-0.5f, -0.0f});
		FVector velocity(2U, new float[] {0.0f, 0.0f});
		FVector color(3U, new float[] {1.0f, 1.0f, 1.0f});
		Particle2D particle(radius, 1.0f, position, velocity, color);
		particles.insert(particle);
		particle.setRadius(0.03f);
		particle.setMass(10.0f);
		particle.setPosition(FVector(2U, new float[] {0.5f, 0.01f}));
		particle.setVelocity(FVector(2U, new float[] {-1.0f, 0.0f}));
		particles.insert(particle);*/

		/*for (int i = 0; i < particles.getSize(); i++)
		{
			initialEnergy += 0.5f * particles[i].getMass() * pow(particles[i].getVelocity().getLength(), 2);
		}
		energyCount = 0;
		energySinceStart = 0.0f;*/
	}

	/* Description: Updates the particles
	 * Parameters: Time since the last update was called
	 */
	virtual void update(const float deltaTime) override;
private:
	/*float initialEnergy;
	float energySinceStart;
	int energyCount;*/

	/* Description: Returns the time until two particles will collide
	 */
	float getCollisionTime(const Particle2D& p1, const Particle2D& p2);
	/* Description: Returns the time until a particle and line will collide
	 */
	float getCollisionTime(const Particle2D& p, const Line& l);

	/* Description: Computes the new velocities for colliding particles
	 */
	void collide(Particle2D& p1, Particle2D& p2);
	/* Description: Computes the new velocity for a particle colliding with a line
	 */
	void collide(Particle2D& p, Line& l);

	/* Description: Applies the quadratic formula to a binomial
	 * Parameters: returnPlus specifies whether to return the b + ... or b - ... value
	 * Return: Returns NULL if the value would be imaginary, or if a is 0
	 */
	float quadraticFormula(float a, float b, float c, bool returnPlus);
};


#endif