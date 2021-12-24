#include "OpenGLWindow.h"

/* Constructor */
OpenGLWindow::OpenGLWindow(bool fullScreen, const char* title, unsigned int scrWidth, unsigned int scrHeight)
{
    // Initialize our variables
    this->scrWidth = scrWidth;
    this->scrHeight = scrWidth;
    this->model = glm::mat4(1.0f);

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
}


/* Public member functions */
void OpenGLWindow::draw(ShaderProgram* shaderProgram, unsigned int VAO, bool useIndices, unsigned int numVertices)
{
    // Input
    processInput(window);

    // Rendering commands
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);                               // color to clear the screen with
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                 // clear the screen

    // Activate shader
    shaderProgram->use();

    // Apply 3d transformations
    shaderProgram->set4x4Matrix("model", GL_FALSE, &model);

    // Draw
    glBindVertexArray(VAO);
    if (useIndices)
        glDrawElements(GL_TRIANGLES, numVertices, GL_UNSIGNED_INT, 0);
    else
        glDrawArrays(GL_TRIANGLES, 0, numVertices);

    // Check events and swap buffers
    glfwPollEvents();                       // checks if any events were tiggered (resizing, etc.)
    glfwSwapBuffers(window);                // swap the front and back buffers
}
void OpenGLWindow::draw(ShaderProgram* shaderProgram, unsigned int VAO, bool useIndices, 
    unsigned int numVertices, glm::vec3* elementPositions, unsigned int numElements)
{
    // Input
    processInput(window);

    // Rendering commands
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);                               // color to clear the screen with
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                 // clear the screen

    // Activate shader
    shaderProgram->use();

    glBindVertexArray(VAO);
    for (int i = 0; i < numElements; i++)
    {
        // Apply 3d transformations
        model = glm::mat4(1.0f);
        model = glm::translate(model, elementPositions[i]);
        shaderProgram->set4x4Matrix("model", GL_FALSE, &model);

        // Draw
        if (useIndices)
            glDrawElements(GL_TRIANGLES, numVertices, GL_UNSIGNED_INT, 0);
        else
            glDrawArrays(GL_TRIANGLES, 0, numVertices);
    }

    // Check events and swap buffers
    glfwPollEvents();                       // checks if any events were tiggered (resizing, etc.)
    glfwSwapBuffers(window);                // swap the front and back buffers
}

bool OpenGLWindow::shouldClose() const
{
    return glfwWindowShouldClose(window);
}

void OpenGLWindow::deallocate() 
{
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