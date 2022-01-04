#include "OpenGLWindow.h"

/* Constructor */
OpenGLWindow::OpenGLWindow(const bool fullScreen, const const char* title,
    const unsigned int scrWidth, const unsigned int scrHeight)
{
    // Initialize OpenGL and the window object ---
    // Initialize GLFW
    glfwInit();
    // Configure GLFW with Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window to draw on
    if (fullScreen)
    {
        this->window = glfwCreateWindow(scrWidth, scrHeight, title, glfwGetPrimaryMonitor(), NULL);
    }
    else
    {
        this->window = glfwCreateWindow(scrWidth, scrHeight, title, NULL, NULL);
    }
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    // Sets the function to call when the window is resized by the user
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Get the OpenGL OS-specific pointer
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    // Don't want no pesky back triangles overwriting the front ones
    glEnable(GL_DEPTH_TEST);
    // ---


    // Initialize object variables ---
    this->scrWidth = scrWidth;
    this->scrHeight = scrWidth;

    // Initialize Shaders using local file paths
    shaderProgram = new ShaderProgram("vertexShader.vs", "fragmentShader.fs");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    useIndices = false;
    numElementsToDraw = 0;

    this->model = glm::mat4(1.0f);
    this->view = glm::mat4(1.0f);
    this->projection = glm::mat4(1.0f);
}
OpenGLWindow::~OpenGLWindow()
{
    deallocate();
}


void OpenGLWindow::draw(const AbstractParticle* particles, const unsigned int numParticles, 
    bool setOneToRed, ColoringStyle coloringStyle)
{
    // Input
    processInput(window);

    // Rendering commands
    glClearColor(0.0f, 0.0625f, 0.125f, 1.0f);                            // color to clear the screen with
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                 // clear the screen

    // Activate shader
    shaderProgram->use();

    for (int i = 0; i < numParticles; i++)
    {
        // Apply 3d transformations
        model = glm::mat4(1.0f);
        model = glm::translate(model, particles[i].getPosition().toGLMvec3());
        model = glm::scale(model, glm::vec3(particles[i].getRadius()));
        shaderProgram->setMat4("model", GL_FALSE, model);
        shaderProgram->setMat4("view", GL_FALSE, view);
        shaderProgram->setMat4("projection", GL_FALSE, projection);

        // Set color
        if (setOneToRed && (i == 0))
            shaderProgram->setVec3("color", 1.0f, 0.0f, 0.0f);
        else
        {
            switch (coloringStyle)
            {
            case ColoringStyle::DEFAULT_WHITE:
                shaderProgram->setVec3("color", 1.0f, 1.0f, 1.0f);
                break;
            case ColoringStyle::DEFAULT_FACTORY:
                shaderProgram->setVec3("color", particles[i].getColor().toGLMvec3());
                break;
            case ColoringStyle::SPEED_BLUE:
                shaderProgram->setVec3("color", glm::vec3(0.5f) + glm::vec3(1.0f) - 
                    (1 - particles[i].getVelocity().getLength()) * (glm::vec3(1.0f) - glm::vec3(0.0f, 1.0f, 1.0f)));
                break;
            case ColoringStyle::SPEED_FACTORY:
                break;
            default:
                shaderProgram->setVec3("color", 0.0f, 0.0f, 0.0f);
                break;
            }
        }

        // Draw
        glBindVertexArray(VAO);
        if (useIndices)
            glDrawElements(GL_TRIANGLES, numElementsToDraw, GL_UNSIGNED_INT, 0);
        else
            glDrawArrays(GL_TRIANGLES, 0, numElementsToDraw);
    }

    // Check events and swap buffers
    glfwPollEvents();                       // checks if any events were tiggered (resizing, etc.)
    glfwSwapBuffers(window);                // swap the front and back buffers
}

bool OpenGLWindow::shouldClose() const { return glfwWindowShouldClose(window); }
void OpenGLWindow::setScreenWidth(const unsigned int scrWidth) 
{ 
    this->scrWidth = scrWidth;
    glViewport(0, 0, this->scrWidth, this->scrHeight);
}
void OpenGLWindow::setScreenHeight(const unsigned int scrHeight) 
{ 
    this->scrHeight = scrHeight;
    glViewport(0, 0, this->scrWidth, this->scrHeight);
}
void OpenGLWindow::setScreenSize(const unsigned int scrWidth, const unsigned int scrHeight)
{
    this->scrWidth = scrWidth;
    this->scrHeight = scrHeight;
    glViewport(0, 0, this->scrWidth, this->scrHeight);
}
void OpenGLWindow::setVBOFromParticle(const AbstractParticle* particle, const unsigned int resolution, const bool useIndices)
{
    // Set draw variables
    this->useIndices = useIndices;
    this->numElementsToDraw = resolution * 3;

    // Get vertex and index data
    unsigned int* indices = nullptr;
    unsigned int indicesSize = 0;
    unsigned int vertexDataSize = 0;
    float* vertexData = particle->generateOpenGLVertices(
        resolution, false, &vertexDataSize, useIndices, &indicesSize, &indices);

    // Place vertices into the VAO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexDataSize, vertexData, GL_STREAM_DRAW);

    if (useIndices)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indicesSize, indices, GL_STATIC_DRAW);
    }

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void OpenGLWindow::deallocate() 
{
    shaderProgram->deallocate();

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // Properly cleans and deletes all resources allocated to GLFW after the window is closed
    glfwTerminate();
}


/* Private member functions */
void OpenGLWindow::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  // Returns GLFW_RELEASE if not pressed
        glfwSetWindowShouldClose(window, true);

    // Bind wireframe toggle to the Z key
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


/* Non member functions */
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}