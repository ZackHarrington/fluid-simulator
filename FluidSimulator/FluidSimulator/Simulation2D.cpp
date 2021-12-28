#include "Simulation2D.h"

/* Public Member Functions */
void Simulation2D::update()
{
    float timeSinceLastUpdate = glfwGetTime() - lastUpdateTime;
    lastUpdateTime = glfwGetTime();
    updateParticles(timeSinceLastUpdate);

    unsigned int resolution = 16;
    //updateVertices(resolution);

    glm::vec3* particlePositions = new glm::vec3[particles.getSize()];
    for (unsigned int i = 0; i < particles.getSize(); i++)
    {
        particlePositions[i] = glm::vec3(particles[i].getPosition().getValues()[0],
            particles[i].getPosition().getValues()[1], 0.0f);
    }

    // Place vertices into the VAO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexDataSize, vertexData, GL_STREAM_DRAW);

    if (indices != nullptr)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indicesSize, indices, GL_STATIC_DRAW);
    }

    // stride is now 6, color offset is 3
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Allows safe unbinding if we have multiple buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Not directly necessary; it's just bad if you forget to bind the VAO you're using and another is bound
    glBindVertexArray(0);


    // Draw to the screen
    window->draw(shaderProgram, VAO, (indices != nullptr), resolution * 3, particlePositions, particles.getSize());
}


/* Private Member Functions */
void Simulation2D::updateParticles(float timeSinceLastUpdate)
{
    float totalSpeed = 0;
    for (int i = 0; i < particles.getSize(); i++)
    {
        FVector newPosition = particles[i].getNextUpdatePosition(timeSinceLastUpdate);

        totalSpeed += pow(particles[i].getVelocity().getLength(), 2);

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
        
        particles[i].update(timeSinceLastUpdate);
        //particles[i].setPosition(newPosition);
    }

    std::cout << totalSpeed << std::endl;
}

void Simulation2D::checkEdgeCollisions(int particleIndex, const FVector& newPosition)
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

void Simulation2D::updateVertices(unsigned int resolution)
{
    
}