#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <thread>
#include <chrono>
//#include <nvToolsExt.h>
//#include <cuda_profiler_api.h>


double lastTime = 0;
int nbFrames = 0;

void updateFPS(GLFWwindow* window) {
    double currentTime = glfwGetTime();
    nbFrames++;
    if (currentTime - lastTime >= 1.0) {
        char title[256];
        snprintf(title, sizeof(title), "OpenGL Program | FPS: %d", nbFrames);
        glfwSetWindowTitle(window, title);
        nbFrames = 0;
        lastTime += 1.0;
    }
}
double lastMouseTime = 0;
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    printf("Mouse Position: (%f, %f, %f)\n", xpos, ypos, (glfwGetTime()-lastMouseTime)*1000);
    lastMouseTime = glfwGetTime();
}

int main() {
    // Initialize the profiler
    /*cudaProfilerStart();*/

    // Enable profiling for the main thread
    //nvtxRangePushA("Main Thread");

    // Initialize GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW.\n");
        return EXIT_FAILURE;
    }

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
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw graphics here
        // ...
        Sleep(0);
        // Swap buffers
        glfwSwapBuffers(window);

        // Poll for events
        glfwPollEvents();
        //i++;
    }

    // Clean up
    glfwTerminate();

    // Disable profiling for the main thread
    //nvtxRangePop();
    /*cudaProfilerStop();*/
    /*double time2 = glfwGetTime();
    printf("\n\n\n%f\n\n\n", time2 - time1);*/

    return EXIT_SUCCESS;
}
