#include "OpenGLWindow.h"

/* Constructor */
OpenGLWindow::OpenGLWindow(bool fullScreen, const char* title, unsigned int scrWidth, unsigned int scrHeight)
{
    // Initialize our variables
    this->scrWidth = scrWidth;
    this->scrHeight = scrWidth;

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

    // Initialize Shaders using local file paths
    this->shaderProgram = new ShaderProgram("vertexShader.vs", "fragmentShader.fs");
}


/* Public member functions */
void OpenGLWindow::update()
{
    // Input
    processInput(window);

    // Rendering commands
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);                               // color to clear the screen with
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                 // clear the screen

    // Activate shader
    shaderProgram->use();

    // Apply 3d transformations

    // Draw
    //glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLES, 0, 36);

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
    // Deallocate resources
    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);
    shaderProgram->deallocate();

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