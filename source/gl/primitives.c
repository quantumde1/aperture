#ifdef _arch_dreamcast
#include "GL/glkos.h"
#include "GL/glu.h"
#include "GL/glext.h"
#include "kos.h"
#else
#include "GL/gl.h"
#endif

#include "../../include/base.h"

void DrawRectangle(float x, float y, float width, float height, Color color) {
    glEnable(GL_BLEND);
    glColor4f(color.r/255.0f, color.g/255.0f, color.b/255.0f, color.a/255.0f);
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
    glEnd();
}