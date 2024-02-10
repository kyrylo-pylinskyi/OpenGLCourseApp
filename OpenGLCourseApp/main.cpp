#include <stdio.h>

#include <GL/glew.h>
#include <GLFW\glfw3.h>

const GLint WIDTH = 300, HEIGHT = 300;

int main()
{
    // Initialise GLFW
    if (!glfwInit()) {
        printf("GLFW Initialization failed!");
        glfwTerminate();
        return 1;
    }

    // Setup GLFW window properties
    // OpenGL version

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Core profile == no backwards compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Allow forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "TestWindow", NULL, NULL);
    if (!mainWindow) {
        printf("GLFW window creation failed!");
        glfwTerminate();
        return 1;
    }
    
    // Get buffer size information
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    // Set context for GLEW to use
    glfwMakeContextCurrent(mainWindow);

    // Alow modern extension feature
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        printf("GLEW initialisation failed!");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    // Setup viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);

    // Loop until window closed
    while (!glfwWindowShouldClose(mainWindow)) {
        // Get and Handle user input events
        glfwPollEvents();

        // Clear window
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap buffers
        glfwSwapBuffers(mainWindow);
    }

    return 0;
}