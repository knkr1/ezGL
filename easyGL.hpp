#pragma once

#include <cstdint>
#include <array>
#include <cmath>
#include <string>
#include "easyGLMath.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Size
{
    uint16_t x, y;

    std::array<uint16_t, 2> array()
    {
        return {x, y};
    }
};

struct Color
{
    uint8_t r, g, b, a;

    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}

    static Color FromRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        return Color(mapRgbaToFloat(r), mapRgbaToFloat(g), mapRgbaToFloat(b), mapRgbaToFloat(a));
    }
};

class Window
{
private:
    GLFWwindow *window;
    void glfwInitalization()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    void gladInitalization()
    {
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }
    }

    static void WindowSizeFeedback(GLFWwindow *window, int width, int height){
        glViewport(0, 0, width, height);
    }
    
    static void viewportSetup(GLFWwindow *window, Size size, bool feedback = false){
        if(feedback){
            glViewport(0,0,size.x,size.y);
            glfwSetFramebufferSizeCallback(window, WindowSizeFeedback);
        }
    }



public:
    Size size;
    std::string windowTitle;
    Window(Size size, std::string str, bool canResize = true, bool isFeedback = false)
    {
        glfwInitalization();
        canResize ? void() : glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        this->size = size;
        this->windowTitle = str;

        window = glfwCreateWindow(size.x, size.y, str.c_str(), NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent(window);
        gladInitalization();
        viewportSetup(window,size,isFeedback);
    }

    GLFWwindow* getWindow(){
        return window;
    }

    int shouldClose(){
        return glfwWindowShouldClose(window);
    }

    void update(){
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    
};

void BackgroundColor(Color color){
    glClearColor(color.r,color.g,color.b,color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}