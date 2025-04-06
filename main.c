#define GLFW_DLL

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ez.h"


int main(int argc, char **argv)
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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