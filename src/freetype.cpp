#include <string>
#include <vector>
#include <hwge/freetype.hpp>
#include <iostream>
#include <GL/glew.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

using namespace std;

inline int nextP2(int a) {
    int rval = 1;
    while(rval < a) rval <<= 1;
    return rval;
}

void makeDlist(FT_Face face, char ch, GLuint listBase, GLuint* texBase) {
    if(FT_Load_Glyph(face, FT_Get_Char_Index(face, ch), FT_LOAD_DEFAULT)) {
        throw runtime_error("Failed to load freetype glyph.");
    }

    FT_Glyph glyph;
    if(FT_Get_Glyph(face->glyph, &glyph)) {
        throw runtime_error("Failed to get freetype glyph.");
    }

    FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
    FT_BitmapGlyph bitmapGlyph = (FT_BitmapGlyph) glyph;

    FT_Bitmap& bitmap = bitmapGlyph->bitmap;

    int width = nextP2(bitmap.width);
    int height = nextP2(bitmap.rows);

    GLubyte* expandedData = new GLubyte[2 * width * height];

    for(int j = 0; j < height; j++) {
        for(int i = 0; i < width; i++) {
            expandedData[2 * (i + j * width)] = expandedData[2 * (i + j * width) + 1] = (i >= bitmap.width || j >= bitmap.rows) ? 0 : bitmap.buffer[i + bitmap.width * j];
        }
    }

    glBindTexture(GL_TEXTURE_2D, texBase[ch]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expandedData);

    delete[] expandedData;

    glNewList(listBase + ch, GL_COMPILE);
    glBindTexture(GL_TEXTURE_2D, texBase[ch]);
    glPushMatrix();

    glTranslatef(bitmapGlyph->left, 0, 0);
    glTranslatef(0, bitmapGlyph->top - bitmap.rows, 0);

    float x = (float) bitmap.width / (float) width;
    float y = (float) bitmap.rows / (float) height;

    glBegin(GL_QUADS);
    glTexCoord2d(0, 0);
    glVertex2f(0, bitmap.rows);
    glTexCoord2d(0, y);
    glVertex2f(0, 0);
    glTexCoord2d(x, y);
    glVertex2f(bitmap.width, bitmap.rows);
    glTexCoord2d(x, 0);
    glVertex2f(bitmap.width, bitmap.rows);
    glEnd();

    glPopMatrix();
    glTranslatef(face->glyph->advance.x >> 6, 0, 0);

    glEndList();
}

void HWGE::FreeType::FontData::init(std::string filename, unsigned int h) {
    textures = new GLuint[128];
    this->h = h;

    FT_Library library;
    if(FT_Init_FreeType(&library)) {
        throw runtime_error("Failed to initialize freetype.");
    }

    FT_Face face;

    if(FT_New_Face(library, filename.c_str(), 0, &face)) {
        throw runtime_error("Failed to initialize freetype face.");
    }

    FT_Set_Char_Size(face, h << 6, h << 6, 96, 96);

    listBase = glGenLists(128);
    glGenTextures(128, textures);

    for(unsigned char i = 0; i < 128; i++) {
        makeDlist(face, i, listBase, textures);
    }

    FT_Done_Face(face);
    FT_Done_FreeType(library);
}

void HWGE::FreeType::FontData::clean() {
    glDeleteLists(listBase, 128);
    glDeleteTextures(128, textures);
    delete[] textures;
}

inline void pushScreenCoordinateMatrix() {
    glPushAttrib(GL_TRANSFORM_BIT);
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(viewport[0], viewport[1], viewport[2], viewport[3], -1, 1);
    glPopAttrib();
}

inline void popProjectionMatrix() {
    glPushAttrib(GL_TRANSFORM_BIT);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
}

void HWGE::FreeType::print(const HWGE::FreeType::FontData &ftFont, float x, float y, const char* fmt, ...) {
    pushScreenCoordinateMatrix();

    GLuint font = ftFont.listBase;

    float h = ftFont.h / 0.63f;
    char text[256];
    va_list ap;

    if(fmt == NULL) {
        *text = 0;
    } else {
        va_start(ap, fmt);
        vsprintf(text, fmt, ap);
        va_end(ap);
    }

    const char* startLine = text;
    vector<string> lines;
    for(const char* c = text; *c; c++) {
        if(*c == '\n') {
            string line;
            for(const char* n = startLine; n < c; n++) {
                line.append(1, *n);
            }
            lines.push_back(line);
            startLine = c + 1;
        }

        if(startLine) {
            string line;
            for(const char* n = startLine; n < c; n++) {
                line.append(1, *n);
            }
            lines.push_back(line);
        }
    }

    glPushAttrib(GL_LIST_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT |GL_TRANSFORM_BIT);
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glListBase(font);

    float modelviewMatrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, modelviewMatrix);

    for(int i = 0; i < lines.size(); i++) {
        glPushMatrix();
        glLoadIdentity();
        glTranslatef(x, y - h * i, 0);
        glMultMatrixf(modelviewMatrix);
        
        glCallLists(lines[i].length(), GL_UNSIGNED_BYTE, lines[i].c_str());
        glPopMatrix();
    }

    glPopAttrib();
    popProjectionMatrix();
}