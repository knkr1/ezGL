#include <stdint.h>

typedef struct RGBA
{
    uint8_t r,g,b,a;
} RGBA;

typedef struct floatRGBA
{
    float r,g,b,a;
} floatRGBA;

typedef struct Size 
{
    uint16_t x,y;
} Size;

Size generateSize(uint16_t x,uint16_t y){
    return (Size){x,y};
}

RGBA generateRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
double clamp(double d, double min, double max);
float mapRGBA(double x);
void windowColor(uint8_t r,uint8_t b,uint8_t g,uint8_t a);

int setupGLAD();
int setupWindow(Size size, char* name);
void setupViewport(Size size);


void setupGLFW(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow *window;
void setEzWindow(GLFWwindow *x){
    window = x;
}

int setupWindow(Size size, char* name){
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

int setupGLAD(){
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

void setupViewport(Size size){
    glViewport(0, 0, size.x, size.y);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

RGBA generateRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    return (RGBA){r,g,b,a};
}

floatRGBA generateFloatRGBA(RGBA color){
    return (floatRGBA){mapRGBA(color.r),mapRGBA(color.g),mapRGBA(color.b),mapRGBA(color.a)};
}

void windowColorRGBA(uint8_t r,uint8_t g,uint8_t b,uint8_t a)
{
    floatRGBA color1 = generateFloatRGBA(generateRGBA(r,g,b,a));
    glClearColor(color1.r,color1.g,color1.b,color1.a);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
}

double map(double x, double inMin, double inMax, double outMin, double outMax) {
    return outMin + (x - inMin) * (outMax - outMin) / (inMax - inMin);
}

float mapRGBA(double x){
    return (float)map(x,0,255,0,1);
}