#include "Simulation2D.h"

/* Public Member Functions */
void Simulation2D::update(const float deltaTime)
{
    //float totalSpeed = 0;
    for (int i = 0; i < particles.getSize(); i++)
    {
        FVector newPosition = particles[i].getNextUpdatePosition(deltaTime);

        //totalSpeed += pow(particles[i].getVelocity().getLength(), 2);

        // Check particle collisions
        for (int j = i + 1; j < particles.getSize(); j++)
        {
            // Check if the two particles are touching
            if (newPosition.getDistance(particles[j].getPosition()) <
                particles[i].getRadius() + particles[j].getRadius())
            {
                particles[i].particleCollision(particles[j]);
            }
        }

        // Check edge collisions
        checkEdgeCollisions(i, newPosition);

        // Update the particle
        particles[i].update(deltaTime);
    }

    //std::cout << totalSpeed << std::endl;
}


/* Private Member Functions */
void Simulation2D::checkEdgeCollisions(const int particleIndex, const FVector& newPosition)
{
    float radius = particles[particleIndex].getRadius();
    if (newPosition.getValues()[0] < -1 + radius)                                // Left
    {
        // Invert the x direction of the velocity
        particles[particleIndex].setVelocity(
            FVector(2U, new float[] {-particles[particleIndex].getVelocity().getValues()[0],
                particles[particleIndex].getVelocity().getValues()[1]}));
    }
    else if (newPosition.getValues()[0] > 1 - radius)                            // Right
    {
        // Invert the x direction of the velocity
        particles[particleIndex].setVelocity(
            FVector(2U, new float[] {-particles[particleIndex].getVelocity().getValues()[0],
                particles[particleIndex].getVelocity().getValues()[1]}));
    }
    else if (newPosition.getValues()[1] < -1 + radius)                           // Top
    {
        // Invert the y direction of the velocity
        particles[particleIndex].setVelocity(
            FVector(2U, new float[] {particles[particleIndex].getVelocity().getValues()[0],
                -particles[particleIndex].getVelocity().getValues()[1]}));
    }
    else if (newPosition.getValues()[1] > 1 - radius)                            // Bottom
    {
        // Invert the y direction of the velocity
        particles[particleIndex].setVelocity(
            FVector(2U, new float[] {particles[particleIndex].getVelocity().getValues()[0],
                -particles[particleIndex].getVelocity().getValues()[1]}));
    }
}