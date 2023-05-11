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

    csvFile << currentFrame << "frame,";
    csvFile << xposi << "x,";
    csvFile << yposi << "y,";
    csvFile << xposi - lastX << "deltax,";
    csvFile << yposi - lastY << "deltay,";
    csvFile << currentTime << "time,";
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
    
    //lastMouseTime = glfwGetTime();

    /*csvFile<<currentFrame<<",";
    csvFile << xpos<<"," ;
    csvFile << ypos<<",";
    csvFile << xpos-lastX << ",";
    csvFile << ypos-lastY << ",";
    csvFile << "\n";

    lastX = xpos;
    lastY = ypos;*/
    
}

int main() {
    csvFile.open("mouseFromProgram.csv");
    
    // Initialize the profiler
    /*cudaProfilerStart();*/

    // Enable profiling for the main thread
    //nvtxRangePushA("Main Thread");

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
    //int i = 0;
    //double time1 = glfwGetTime();*/
    while (!glfwWindowShouldClose(window)) {
    //while(i<50000){
        // Calculate FPS
        updateFPS(window);

        // Clear the screen
        //glClear(GL_COLOR_BUFFER_BIT);

        // Draw graphics here
        // ...
        // Swap buffers
        //glfwSwapBuffers(window);

        // Poll for events
        glfwPollEvents();
        currentFrame++;
    }
    csvFile.close();
    // Clean up
    glfwTerminate();

    // Disable profiling for the main thread
    //nvtxRangePop();
    /*cudaProfilerStop();*/
    /*double time2 = glfwGetTime();
    printf("\n\n\n%f\n\n\n", time2 - time1);*/

    return EXIT_SUCCESS;
}
