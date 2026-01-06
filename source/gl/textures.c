#ifdef _arch_dreamcast
#include "GL/glkos.h"
#include "GL/glu.h"
#include "GL/glext.h"
#include "kos.h"
#else
#include "GL/gl.h"
#endif

#include <stdio.h>
#include "../../include/base.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "../../include/textures.h"

Texture LoadTexture(const char* filename) {
    Texture texture = {0};
    stbi_set_flip_vertically_on_load(1);
    unsigned char* data = stbi_load(filename, &texture.width, &texture.height, &texture.channels, 0);
    
    GLenum format;
    if (texture.channels == 4) {
        format = GL_RGBA;
    } else if (texture.channels == 3) {
        format = GL_RGB;
    } else {
        stbi_image_free(data);
        fprintf(stderr, "unsupported number of channels %d in texture\n", texture.channels);
        return texture;
    }
    
    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, format, texture.width, texture.height, 
                 0, format, GL_UNSIGNED_BYTE, data);
    
    stbi_image_free(data);

    texture.list_id = glGenLists(1);

    glNewList(texture.list_id, GL_COMPILE);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture.id);
        
        if (texture.channels == 4) {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
            glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, 0.0f);
            glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
            glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, 1.0f);
        glEnd();
        
        if (texture.channels == 4) {
            glDisable(GL_BLEND);
        }
        glDisable(GL_TEXTURE_2D);

    glEndList();
    
    return texture;
}

void DrawTexture(Texture texture, float x, float y, float scale, Color tint) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(texture.width * scale, texture.height * scale, 1.0f);
    glTranslatef(-0.5f, -0.5f, 0.0f);
    glColor4f(tint.r / 255.0f, tint.g / 255.0f, tint.b / 255.0f, tint.a / 255.0f);
    glCallList(texture.list_id);
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glPopMatrix();
}

// i do not recommend using this because of immediate mode.
void DrawTexturePro(Texture texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint) {
    float texWidth = (float)texture.width;
    float texHeight = (float)texture.height;
    float texLeft = source.x / texWidth;
    float texRight = (source.x + source.width) / texWidth;
    float texTop = source.y / texHeight;
    float texBottom = (source.y + source.height) / texHeight;
    texTop = 1.0f - texTop; // for inverting
    texBottom = 1.0f - texBottom; // too
    glPushMatrix();
    glTranslatef(dest.x, dest.y, 0.0f);
    if (rotation != 0.0f) {
        glTranslatef(origin.x, origin.y, 0.0f);
        glRotatef(rotation, 0.0f, 0.0f, 1.0f);
        glTranslatef(-origin.x, -origin.y, 0.0f);
    }
    glScalef(dest.width, dest.height, 1.0f);
    
    glColor4f(tint.r / 255.0f, tint.g / 255.0f, tint.b / 255.0f, tint.a / 255.0f);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture.id);
    
    if (texture.channels == 4) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    
    glBegin(GL_QUADS);
        glTexCoord2f(texLeft, texTop);
        glVertex2f(0.0f, 0.0f);
        glTexCoord2f(texRight, texTop);
        glVertex2f(1.0f, 0.0f);
        glTexCoord2f(texRight, texBottom);
        glVertex2f(1.0f, 1.0f);
        glTexCoord2f(texLeft, texBottom);
        glVertex2f(0.0f, 1.0f);
    glEnd();
    
    if (texture.channels == 4) {
        glDisable(GL_BLEND);
    }
    
    glDisable(GL_TEXTURE_2D);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glPopMatrix();
}

void UnloadTexture(Texture texture) {
    if (texture.id != 0) {
        glDeleteTextures(1, &texture.id);
    }
    if (texture.list_id != 0) {
        glDeleteLists(texture.list_id, 1);
    }
}