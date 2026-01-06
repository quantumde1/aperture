#pragma once

#include "stdio.h"

typedef struct {
    float r;
    float g;
    float b;
    float a;
} Color;

#define LIGHTGRAY   (Color){ 200, 200, 200, 255 }
#define WHITE       (Color){ 255, 255, 255, 255 }
#define BLACK       (Color){ 0, 0, 0, 255 }
#define GRAY        (Color){ 130, 130, 130, 255 }
#define DARKGRAY    (Color){ 80, 80, 80, 255 }
#define YELLOW      (Color){ 253, 249, 0, 255 }
#define GOLD        (Color){ 255, 203, 0, 255 }
#define RED         (Color){ 255, 0, 0, 255 }
#define BLUE        (Color){ 0, 0, 255, 255 }
#define GREEN       (Color){ 0, 255, 0, 255 }

extern float screenWidth;
extern float screenHeight;

#ifdef _arch_dreamcast
#define ASSETS_PATH "/cd/assets/"
#else
#define ASSETS_PATH "assets/"
#endif

void glInit(int* pargc, char** argv, int width, int height, const char* title);
void glSwapBuffers();

char* concat_strings(const char* str1, const char* str2);

float GetScreenWidth();
float GetScreenHeight();

void BeginDrawing();
void EndDrawing();

void ClearBackground(Color color);

void InitWindow(int argc, char** argv, int width, int height, const char* title);

void SetWindowShouldClose(int shouldClose);
int WindowShouldClose();

void PollWindowEvents();