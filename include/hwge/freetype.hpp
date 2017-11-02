#pragma once

#include <string>
#include <vector>
#include <GL/glew.h>

namespace HWGE {
    namespace FreeType {
        struct FontData {
            float h;
            GLuint* textures;
            GLuint listBase;

            void init(std::string filename, unsigned int h);
            void clean();
        };

        void print(const FontData &ftFont, float x, float y, const char *fmt, ...);
    };
};