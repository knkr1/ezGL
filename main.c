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

    Size windowSize = generateSize(800, 600);

    setupWindow(windowSize, "hi");
    setupGLAD();
    setupViewport(windowSize);

    const char *VertexSource = readShaderFromFile("./shader/vertex.glsl");
    unsigned int vertexShader = CompileShader(VertexSource, GL_VERTEX_SHADER);
    //shader 1
    const char *OrangeFragmentSource = readShaderFromFile("./shader/fragment1.glsl");
    unsigned int OrangefragmentShader = CompileShader(OrangeFragmentSource, GL_FRAGMENT_SHADER);
    unsigned int OrangeShaders[] = {vertexShader, OrangefragmentShader};
    unsigned int shaderProgramOrange = CreateShaderProgram(OrangeShaders, 2);

    //shader 2
    const char *YellowFragmentSource = readShaderFromFile("./shader/fragment2.glsl");
    unsigned int YellowfragmentShader = CompileShader(YellowFragmentSource, GL_FRAGMENT_SHADER);
    unsigned int YellowShaders[] = {vertexShader, YellowfragmentShader};
    unsigned int shaderProgramYellow = CreateShaderProgram(YellowShaders, 2);

    float firstTriangle[] = {
        -0.9f, -0.5f, 0.0f,  // left 
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top 
    };
    float secondTriangle[] = {
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top 
    };

    unsigned int VBO1, VAO1;
    glGenVertexArrays(1, &VAO1); // lets create vao
    glGenBuffers(1, &VBO1);      // vertex created
    glBindVertexArray(VAO1);     // first vao

    glBindBuffer(GL_ARRAY_BUFFER, VBO1);                                        // then vertexes
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW); // ok vertexes got writted

    // noting!
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    unsigned int VBO2, VAO2;
    glGenVertexArrays(1, &VAO2); // lets create vao
    glGenBuffers(1, &VBO2);      // vertex created
    glBindVertexArray(VAO2);     // first vao

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);                                        // then vertexes
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW); // ok vertexes got writted

    // noting!
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        setWindowColorRGBA(30, 144, 255, 0);
        glUseProgram(shaderProgramOrange);

        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glUseProgram(shaderProgramYellow);
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        updateWindow();
    }

    glfwTerminate();
    return 0;
}