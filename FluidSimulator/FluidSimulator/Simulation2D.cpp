#include "Simulation2D.h"

/* Public Member Functions */
void Simulation2D::update()
{
    //updateParticles();

    unsigned int resolution = 8;
    //updateVertices(resolution);
    // Temporary - assuming radius are the same size
    FVector position(2U, new float[] {0.0f, 0.0f});
    FVector velocity(2U, new float[] {1.0f, 1.0f});
    FVector color(3U, new float[] {1.0f, 1.0f, 1.0f});
    Particle2D particle((*particles)[0].getRadius(), 1.0f, position, velocity, color);
    vertexData = particle.generateOpenGLVertices(
        resolution, true, &vertexDataSize, true, &indicesSize, &indices);

    glm::vec3* particlePositions = new glm::vec3[particles->getSize()];
    for (unsigned int i = 0; i < particles->getSize(); i++)
    {
        particlePositions[i] = glm::vec3((*particles)[i].getPosition().getValues()[0],
            (*particles)[i].getPosition().getValues()[1], 0.0f);
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
    window->draw(shaderProgram, VAO, (indices != nullptr), resolution * 3, particlePositions, particles->getSize());
}


/* Private Member Functions */
void Simulation2D::updateParticles()
{
    // Temporary
    for (int i = 0; i < 1; i++)
    {
        //particles[i]->setPosition(particles[i]->getPosition());
    }
}

void Simulation2D::updateVertices(unsigned int resolution)
{
    
}