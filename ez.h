#include <stdint.h>
#include <stdlib.h>

typedef struct RGBA
{
    uint8_t r, g, b, a;
} RGBA;

typedef struct floatRGBA
{
    float r, g, b, a;
} floatRGBA;

typedef struct Size
{
    uint16_t x, y;
} Size;

/**
 * Returns a Size type that expected to include pixels for scaling purposes
 * @param x The x dimension of the size (uint16_t)
 * @param y The y dimension of the size (uint16_t)
 * @warning uint16_t supports the numbers between 0 and 65535
 */
Size generateSize(uint16_t x, uint16_t y)
{
    return (Size){x, y};
}

RGBA generateRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
double clamp(double d, double min, double max);
float mapRGBA(uint8_t x);
void setWindowColorRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

char *readShaderFromFile(const char *filePath);

int setupGLAD();
int setupWindow(Size size, char *name);
void setupViewport(Size size);

/**
 * Runs glfwInit() and some WindowHints (You may need to change them by yourself)
 */
void setupGLFW()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow *window;
void setEzWindow(GLFWwindow *x)
{
    window = x;
}

void updateWindow()
{
    glfwPollEvents();
    glfwSwapBuffers(window);
}

/**
 * Initializing the window
 * @param size The Size type that has x and y for scaling
 * @param name Window title
 */
int setupWindow(Size size, char *name)
{
    GLFWwindow *window = glfwCreateWindow(size.x, size.y, name, NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    setEzWindow(window);
}

/**
 * Setups glad and returns -1 if it fails
 */
int setupGLAD()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        return -1;
    }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

/**
 * Setups the viewport of the glViewport
 * @param size The Size type that includes the x and y for scaling
 * Also calls the framebuffer_size_callback for feedback (from ez.h)
 */
void setupViewport(Size size)
{
    glViewport(0, 0, size.x, size.y);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

/**
 * Generating RGBA typedef
 * @param all unsigned int, a number between 0 and 255
 */
RGBA generateRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    return (RGBA){r, g, b, a};
}

/**
 * Convert RGBA type to floatRGBA type
 * @param color The RGBA type that will get converted
 */
floatRGBA generateFloatRGBA(RGBA color)
{
    return (floatRGBA){mapRGBA(color.r), mapRGBA(color.g), mapRGBA(color.b), mapRGBA(color.a)};
}

/**
 * Set window background with simple RGBA
 * @param all RGBA parameters which require a number between 0 and 255
 */
void setWindowColorRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    floatRGBA color1 = generateFloatRGBA(generateRGBA(r, g, b, a));
    glClearColor(color1.r, color1.g, color1.b, color1.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

/**
 * Simple math function to map a number
 * @param x The number you want to map
 * @param inMin Minimum value of your number
 * @param inMax Maxmimum value of your number
 * @param outMin Minimum value of output
 * @param outMax Maximum value of output
 */
double map(double x, double inMin, double inMax, double outMin, double outMax)
{
    return outMin + (x - inMin) * (outMax - outMin) / (inMax - inMin);
}

/**
 * Map an RGBA parameter (uint8_t), which is between 0 and 255 to be between 0 and 1
 *
 * @param x uint8_t thats needed to be converted
 *
 */
float mapRGBA(uint8_t x)
{
    return (float)map(x, 0, 255, 0, 1);
}

char *readShaderFromFile(const char *fileName)
{
    FILE *file = fopen(fileName, "rb");
    if (!file)
    {
        perror("Failed to open file");
        return NULL;
    }

    // Seek to the end to find the file size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the shader text
    char *shaderCode = (char *)malloc(fileSize + 1);
    if (!shaderCode)
    {
        perror("Failed to allocate memory");
        fclose(file);
        return NULL;
    }

    // Read the file into the buffer
    fread(shaderCode, 1, fileSize, file);
    shaderCode[fileSize] = '\0'; // Null-terminate the string

    fclose(file);
    return shaderCode;
}

unsigned int CompileShader(const char *source, int type)
{
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %c", infoLog);
    }
    return shader;
}

unsigned int CreateShaderProgram(unsigned int ids[],int count)
{
    unsigned int program = glCreateProgram();
    for (int i = 0; i < count; i++)
    {
        glAttachShader(program, ids[i]);
    }
    glLinkProgram(program);
    for (int i = 0; i < count; i++)
    {
        glDeleteShader(ids[i]);
    }
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        printf("ERROR::SHADER::COMPILE::FAILED\n %c", infoLog);
        
    }

    return program;
}