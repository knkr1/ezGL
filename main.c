#define GLFW_DLL

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ez.h"


int main(int argc, char **argv)
{

    setupGLFW();
    
    Size windowSize = generateSize(800,600);

    setupWindow(windowSize,"hi");
    setupGLAD();
    setupViewport(windowSize);

    while (!glfwWindowShouldClose(window))
    {
        windowColorRGBA(30,144,255,0);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}