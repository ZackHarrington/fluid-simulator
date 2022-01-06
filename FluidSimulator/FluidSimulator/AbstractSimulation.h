#pragma once

#ifndef ABSTRACTSIMULATION_H
#define ABSTRACTSIMULATION_H

#include "DynamicArray.h"
#include "AbstractParticleFactory.h"
#include "ColoringStyle.h"

template <typename ParticleType>
class AbstractSimulation
{
public:
	/* Description: Initializes the common simulation variables
	 * Parameters: useIndices defines whether or not the EBO should be initialized
	 */
	AbstractSimulation(const ColoringStyle coloringStyle = ColoringStyle::DEFAULT_WHITE, 
		const unsigned int numParticles = 0, AbstractParticleFactory<ParticleType>* particleFactory = nullptr)
	{
		if (particleFactory != nullptr)
			particles = *(particleFactory->generate(numParticles));
		this->particleFactory = particleFactory;
		this->coloringStyle = coloringStyle;
	}
	/* Description: Deallocates resources
	 */
	virtual ~AbstractSimulation()
	{
		deallocate();
	}

	// Getters / setters
	/* Description: Returns the coloring style used by the simulation
	 */
	ColoringStyle getColoringStyle() const						{ return coloringStyle; }
	/* Description: Returns a 'read only' pointer to the array of particle data
	 */
	const ParticleType* getParticleData() const					{ return particles.getArray(); }
	/* Description: Returns the size of the particle array
	 */
	unsigned int getNumParticles() const					{ return particles.getSize(); }
	/* Description: Sets the coloring style to be used by the simulation
	 */
	void setColoringStyle(const ColoringStyle coloringStyle)	{ this->coloringStyle = coloringStyle; }
	/* Description: Sets the particle factory to be used for particle generation
	 */
	void setParticleFactory(const AbstractParticleFactory<ParticleType>* particleFactory)
	{ 
		this->particleFactory = particleFactory; 
	}

	/* Description: Updates the particles
	 * Parameters: Time since the last update was called
	 */
	virtual void update(const float deltaTime) = 0;				// Makes the class pure virtual

	/* Description: Deallocated the space used by the variables
	 */
	void deallocate()
	{
		particles.deallocate();
	}

protected:
	DynamicArray<ParticleType> particles;	// Defaults to a capacity of 10 to start
	AbstractParticleFactory<ParticleType>* particleFactory;
	ColoringStyle coloringStyle;
};


#endif