#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <vector>
#include <iostream>
#include <fstream>



using namespace std;

double lastTime = 0;
int nbFrames = 0;
int currentFrame = 0;
double currentTime = glfwGetTime();
double lastX = 0;
double lastY = 0;

ofstream csvFile;


double xposi, yposi;


void updateFPS(GLFWwindow* window) {
    
    glfwGetCursorPos(window, &xposi, &yposi);

    nbFrames++;
    currentTime = glfwGetTime();

    csvFile << currentFrame << ",";
    csvFile << xposi << ",";
    csvFile << yposi << ",";
    csvFile << xposi - lastX << ",";
    csvFile << yposi - lastY << ",";
    csvFile << currentTime << ",";
    csvFile << "\n";

    lastX = xposi;
    lastY = yposi;

    
    if (currentTime - lastTime >= 1.0) {
        
        printf("fps: (%d)\n", nbFrames);
        nbFrames = 0;
        lastTime += 1.0;
    }
}
double lastMouseTime = 0;

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    //printf("Mouse Position: (%f, %f)\n", xpos, ypos);
}

int main() {
    csvFile.open("mouseFromProgram.csv");
    
    // Initialize GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW.\n");
        return EXIT_FAILURE;
    }
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);

    // Create a window and OpenGL context
    GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL Program", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create window.\n");
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    // Register callback functions
    glfwSetCursorPosCallback(window, mouse_callback);

    // Enable vsync
    glfwSwapInterval(0);

    // Loop until the user closes the window

    while (!glfwWindowShouldClose(window)) {
        // Calculate FPS and update csvFile
        updateFPS(window);
   
        // Poll for events
        glfwPollEvents();
        currentFrame++;
    }
    csvFile.close();
    // Clean up
    glfwTerminate();

    return EXIT_SUCCESS;
}
