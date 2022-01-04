#pragma once

#ifndef ABSTRACTPARTICLEFACTORY_H
#define ABSTRACTPARTICLEFACTORY_H

#include "DynamicArray.h"

template <typename ParticleType>
class AbstractParticleFactory
{
public: 
	/* Description: Default constructor
	 */
	AbstractParticleFactory()
	{
		;
	}
	/* Description: Default destructor
	 */
	virtual ~AbstractParticleFactory()
	{
		;
	}

	/* Description: Generates and returns the initial particle array to be used at the start of a simulation
	 */
	virtual DynamicArray<ParticleType>* generate(const unsigned int numParticles = 0) = 0;

	/* Description: Generates and adds more particles to the array throughout the simulation
	 *				Timing is controlled by the simulation
	 */
	virtual void generateMore(DynamicArray<ParticleType>* particles)
	{
		// Does nothing by default 
		// This way the simulations which don't generate more particles don't have to override the function
		;
	}
};



#endif
