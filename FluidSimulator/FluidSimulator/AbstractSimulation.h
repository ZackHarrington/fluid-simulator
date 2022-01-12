#pragma once

#ifndef ABSTRACTSIMULATION_H
#define ABSTRACTSIMULATION_H

#include "DynamicArray.h"
#include "AbstractParticleFactory.h"
#include "ColoringStyle.h"
#include "Line.h"

template <typename ParticleType>
class AbstractSimulation
{
public:
	/* Description: Initializes the common simulation variables
	 */
	AbstractSimulation(const ColoringStyle coloringStyle = ColoringStyle::DEFAULT_WHITE, 
		const unsigned int numParticles = 0, AbstractParticleFactory<ParticleType>* particleFactory = nullptr)
	{
		if (particleFactory != nullptr)
			particles = *(particleFactory->generate(numParticles));

		// Temporary - will move to an obstacle factory? maybe, might leave in derived classes? or might not
		this->lines.insert(Line(FVector(2U, new float[] {1.0f, 1.0f}), 
			FVector(2U, new float[] {-1.0f, 1.0f}), FVector(3U, new float[] {1.0f, 1.0f, 1.0f})));	// Top
		this->lines.insert(Line(FVector(2U, new float[] {-1.0f, 1.0f}),
			FVector(2U, new float[] {-1.0f, -1.0f}), FVector(3U, new float[] {1.0f, 1.0f, 1.0f})));	// Left
		this->lines.insert(Line(FVector(2U, new float[] {-1.0f, -1.0f}),
			FVector(2U, new float[] {1.0f, -1.0f}), FVector(3U, new float[] {1.0f, 1.0f, 1.0f})));	// Bottom
		this->lines.insert(Line(FVector(2U, new float[] {1.0f, -1.0f}),
			FVector(2U, new float[] {1.0f, 1.0f}), FVector(3U, new float[] {1.0f, 1.0f, 1.0f})));	// Right
		//this->lines.insert(Line(FVector(2U, new float[] {0.25f, -0.25f}),
			//FVector(2U, new float[] {-0.25f, 0.25f}), FVector(3U, new float[] {1.0f, 1.0f, 1.0f})));	// Right


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

	// Temporary
	/* Description: Returns a 'read only' pointer to the array of line data
	 */
	const ParticleType* getLineData() const						{ return lines.getArray(); }
	unsigned int getNumLines() const							{ return lines.getSize(); }


	/* Description: Returns the size of the particle array
	 */
	unsigned int getNumParticles() const						{ return particles.getSize(); }
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
		lines.deallocate();
	}

protected:
	DynamicArray<ParticleType> particles;	// Defaults to a capacity of 10 to start
	DynamicArray<Line> lines;
	AbstractParticleFactory<ParticleType>* particleFactory;
	ColoringStyle coloringStyle;
};


#endif