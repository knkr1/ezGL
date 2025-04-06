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
    setupGLAD();
    
    Size windowSize = generateSize(800,600);

    setupWindow(windowSize,"hi");
    setupGLAD();
    setupViewport(windowSize);
    windowColorRGBA(30,144,255,0);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}