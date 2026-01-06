#pragma once
#ifdef _arch_dreamcast
#include "GL/glkos.h"
#include "GL/glu.h"
#include "GL/glext.h"
#include "kos.h"
#else
#include "GL/gl.h"
#endif

#include "../include/base.h"

#ifndef _WIN32
typedef struct {
    GLuint id;
    GLuint list_id;
    int width;
    int height;
    int channels;
} Texture;
#else
//TODO add Windows DirectX at least 9.0c support.
#endif

void DrawTexture(Texture texture, float x, float y, float scale, Color color);
Texture LoadTexture(const char* filename);
void UnloadTexture(Texture texture);
void DrawTexturePro(Texture texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint);