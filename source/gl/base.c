#include "../../include/base.h"

#ifdef _arch_dreamcast
#include "GL/glkos.h"
#include "GL/glu.h"
#include "GL/glext.h"
#include "kos.h"
#else
#include "GLFW/glfw3.h"
#include "GL/glu.h"
GLFWwindow* window = NULL;
#endif

#include <time.h>
#include <unistd.h>

static double frameTime = 0.0;
static double lastFrameTime = 0.0;
static double startTime = 0.0;

void glSwapBuffers() {
    #ifdef _arch_dreamcast
    glKosSwapBuffers();
    #else
    glfwSwapBuffers(window);
    #endif
}


float GetTime(void) {
    #ifdef _arch_dreamcast
    return (float)(clock() / (double)CLOCKS_PER_SEC - startTime);
    #else
    return (float)(glfwGetTime() - startTime);
    #endif
}

void glInit(int* pargc, char** argv, int width, int height, const char* title) {
    #ifdef _arch_dreamcast
    glKosInit(pargc, argv);
    startTime = clock() / (double)CLOCKS_PER_SEC;
    #else
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return;
    }
    
    // Указываем OpenGL 1.1
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);
    
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return;
    }
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    
    startTime = glfwGetTime();
    #endif
    
    lastFrameTime = GetTime();
}

float screenWidth;
float screenHeight;

float GetScreenWidth() {
    return screenWidth;
}

float GetScreenHeight() {
    return screenHeight;
}

float GetFrameTime(void) {
    return (float)frameTime;
}

void BeginDrawing() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, screenWidth, 0, screenHeight);
}

void EndDrawing() {
    glSwapBuffers();
    
    double currentTime = GetTime();
    frameTime = currentTime - lastFrameTime;
    lastFrameTime = currentTime;
}

void SetTargetFPS(int targetFPS) {
    static clock_t lastTime = 0;
    clock_t currentTime = clock();
    
    double frameTime = 1000.0 / targetFPS;
    double elapsedTime = (double)(currentTime - lastTime) / CLOCKS_PER_SEC * 1000.0;
    
    if (elapsedTime < frameTime) {
        usleep((frameTime - elapsedTime) * 1000);
    }
    
    lastTime = currentTime;
}

void ClearBackground(Color color) {
    glClearColor(color.r / 255, color.g / 255, color.b / 255, color.a / 255);
}

void InitWindow(int argc, char** argv, int width, int height, const char* title) {
    glInit(&argc, argv, width, height, title);
    screenWidth = width;
    screenHeight = height;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, height, 0);
    glMatrixMode(GL_MODELVIEW);
}

#ifndef _arch_dreamcast
int WindowShouldClose() {
    return glfwWindowShouldClose(window);
}

void PollWindowEvents() {
    glfwPollEvents();
}

void CloseWindow() {
    glfwDestroyWindow(window);
    glfwTerminate();
}
#endif