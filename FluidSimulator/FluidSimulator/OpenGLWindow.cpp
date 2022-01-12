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
    const bool setOneToRed, const ColoringStyle coloringStyle)
{
    // Input
    processInput(window);

    // Rendering commands
    glClearColor(0.0f, 0.0625f, 0.125f, 1.0f);              // color to clear the screen with
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // clear the screen

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
            setColor(particles[i], coloringStyle);
        }

        // Draw
        glBindVertexArray(VAO);
        if (useIndices)
            glDrawElements(GL_TRIANGLES, numElementsToDraw, GL_UNSIGNED_INT, 0);
        else
            glDrawArrays(GL_TRIANGLES, 0, numElementsToDraw);
    }

    // Check events and swap buffers
    glfwPollEvents();                                       // checks if any events were tiggered (resizing, etc.)
    glfwSwapBuffers(window);                                // swap the front and back buffers
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

void OpenGLWindow::setColor(const AbstractParticle& particle, const ColoringStyle coloringStyle)
{
    // Just so visual studio doesn't get mad if I need to declare a variable in a case statement
    float value = 0.0f;
    switch (coloringStyle)
    {
    case ColoringStyle::DEFAULT_WHITE:
        shaderProgram->setVec3("color", 1.0f, 1.0f, 1.0f);
        break;
    case ColoringStyle::DEFAULT_FACTORY:
        shaderProgram->setVec3("color", particle.getColor().toGLMvec3());
        break;
    case ColoringStyle::SPEED_BLUE:
        value = particle.getVelocity().getLength();
        clamp(value, 0.0f, 1.0f);
        /* Squares the value to get a greater fall off,
         * thus causing only the fastest to be whiter, with the rest more blue
         * and the slowest to be darker (lower value)
         */
        shaderProgram->setVec3("color",
            toRGB(glm::vec3(((1.0f - value) * 20.0f + 200.0f),
                1.0f - pow(value, 2),
                1.0f - (pow((1.0f - value), 2) * 0.75f))));
        break;
    case ColoringStyle::SPEED_FACTORY:
        value = particle.getVelocity().getLength();
        clamp(value, 0.0f, 1.0f);
        shaderProgram->setVec3("color",
            toRGB(glm::vec3(getHue(particle.getColor().toGLMvec3()),
                1.0f - pow(value, 2),
                1.0f - (pow((1.0f - value), 2) * 0.75f))));
        break;
    default:
        shaderProgram->setVec3("color", 0.0f, 0.0f, 0.0f);
        break;
    }
}

glm::vec3 OpenGLWindow::toHSV(const glm::vec3 RGB)
{
    float Hue = 0.0f, Saturation = 0.0f;
    float max = fmax(fmax(RGB.r, RGB.g), RGB.b);
    float min = fmin(fmin(RGB.r, RGB.g), RGB.b);
    // Hue
    if (RGB.r == max)
        Hue = 0.0f + (RGB.g - RGB.b) / (max - min);
    else if (RGB.g == max)
        Hue = 2.0f + (RGB.b - RGB.r) / (max - min);
    else // blue is max
        Hue = 4.0f + (RGB.r - RGB.g) / (max - min);
    Hue *= 60;
    if (Hue < 0)
        Hue += 360;
    // Saturation
    if (max == 0)
        Saturation = 0;
    else
        Saturation = (max - min) / max;
    // Value = max

    return glm::vec3(Hue, Saturation, max);
}
float OpenGLWindow::getHue(const glm::vec3 RGB)
{
    float Hue = 0;
    float max = fmax(fmax(RGB.r, RGB.g), RGB.b);
    float min = fmin(fmin(RGB.r, RGB.g), RGB.b);

    if (RGB.r == max)       
        Hue = 0.0f + (RGB.g - RGB.b) / (max - min);
    else if (RGB.g == max)  
        Hue = 2.0f + (RGB.b - RGB.r) / (max - min);
    else // blue is max
        Hue = 4.0f + (RGB.r - RGB.g) / (max - min);

    Hue *= 60;
    if (Hue < 0)
        Hue += 360;

    return Hue;
}
glm::vec3 OpenGLWindow::toRGB(const glm::vec3 HSV)
{
    float H = HSV.x, S = HSV.y, V = HSV.z;
    float C = V * S;
    // X = C * (1 - |(H / 60) % 2 - 1|), when 0 <= H <= 360,
    float X = C * (1 - abs(fmod(H/60, 2) - 1));             // mod needs integer division
    float m = V - C;
    float Rprime, Gprime, Bprime;
    if (H < 60)         { Rprime = C; Gprime = X; Bprime = 0; }
    else if (H < 120)   { Rprime = X; Gprime = C; Bprime = 0; }
    else if (H < 180)   { Rprime = 0; Gprime = C; Bprime = X; }
    else if (H < 240)   { Rprime = 0; Gprime = X; Bprime = C; }
    else if (H < 300)   { Rprime = X; Gprime = 0; Bprime = C; }
    else                { Rprime = C; Gprime = 0; Bprime = X; }
    // (R,G,B) = ((R'+ m)*255, (G'+ m)*255, (B'+ m)*255)    but we don't care about the * 255 because we need 0 <= x <= 1
    return  glm::vec3(Rprime + m, Gprime + m, Bprime + m);
}

float& OpenGLWindow::clamp(float& value, const float& low, const float& high)
{
    if (value < low)
        value = low;
    if (value > high)
        value = high;
    return value;
}


/* Non member functions */
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}