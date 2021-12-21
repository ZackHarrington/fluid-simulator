#include "AbstractSimulation.h"

/* Constructor */
AbstractSimulation::AbstractSimulation(bool useIndices, bool fullScreen, 
    const char* title, unsigned int scrWidth, unsigned int scrHeight)
{
    // The window must be defined first so an OpenGL context exists
    window = new OpenGLWindow(fullScreen, title, scrWidth, scrHeight);
    // Initialize Shaders using local file paths
    this->shaderProgram = new ShaderProgram("vertexShader.vs", "fragmentShader.fs");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    if (useIndices)
        glGenBuffers(1, &EBO);
    else
        EBO = NULL;

    vertexData = nullptr;
    vertexDataSize = 0;
    indices = nullptr;
    indicesSize = 0;

    particles = nullptr;
}

/* Public Member Functions */
void AbstractSimulation::deallocate()
{
    window->deallocate();
    shaderProgram->deallocate();

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    if (EBO != NULL)
        glDeleteBuffers(1, &EBO);

    if (vertexData != nullptr)
        delete[] vertexData;
    if (indices != nullptr)
        delete[] indices;

    if (particles != nullptr)
        delete[] particles;
}