#pragma once

#include "base.h"

extern const char font6x8_ascii[128][6];

void DrawText(const char* text, float x, float y, float scale, Color color);
void DrawTextWithFont(unsigned char* text, int x, int y, float fontSize, Color color);
void LoadFont(char* pathToFolder);
void UnloadFont();