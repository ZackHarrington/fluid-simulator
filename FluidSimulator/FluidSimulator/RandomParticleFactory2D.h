#pragma once

#ifndef RANDOMPARTICLEFACTORY2D_H
#define RANDOMPARTICLEFACTORY2D_H

#include "AbstractParticleFactory.h"
#include "Particle2D.h"

#include <iostream>

class RandomParticleFactory2D : public AbstractParticleFactory<Particle2D>
{
public:
	/* Description: Default constructor
	 */
	RandomParticleFactory2D();

	/* Description: Generates and returns a particle array of the specified size to be used at the start of a simulation
	 */
	virtual DynamicArray<Particle2D>* generate(const unsigned int numParticles) override;
};





#endif