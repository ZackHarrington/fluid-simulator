#pragma once

#ifndef RANDOMPARTICLEFACTORY2D_H
#define RANDOMPARTICLEFACTORY2D_H

#include "AbstractParticleFactory.h"
#include "Particle2D.h"

#include <iostream>
#include <math.h>

class RandomParticleFactory2D : public AbstractParticleFactory<Particle2D>
{
public:
	/* Description: Default constructor
	 * Parameters: The speed factor is how much to multiply the generated velocity by, thereby allowing you to speed up or slow down the simulation
	 *				You may specify to implement mass logically, not randomly
	 *				this makes mass based on size and gives heavier objects a slower initial velocity
	 */
	RandomParticleFactory2D(const float speedFactor = 1.0f, const bool useLogicalMass = false);

	/* Description: Generates and returns a particle array of the specified size to be used at the start of a simulation
	 */
	virtual DynamicArray<Particle2D>* generate(const unsigned int numParticles) override;

private:
	float speedFactor;
	bool useLogicalMass;
	float averageRadius;
};





#endif