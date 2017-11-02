#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <png.h>

namespace HWGE {
    namespace Image {
        class PNG {
        private:
            int width, height;
            bool alphaChannel = false;
            std::string filename;
            png_byte* imageData;
            GLint format;
        
        public:
            PNG(std::string filename);
            int getWidth() const { return this->width; };
            int getHeight() const { return this->height; };
            bool hasAlphaChannel() { return alphaChannel; }
            //GLuint openGLTexture();
            GLuint load();
        };
    };
};