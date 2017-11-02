#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace HWGE {
    namespace Image {
        class BMP {
        private:
            std::uint32_t width, height;
            std::uint16_t bitsPerPixel;
            std::vector<std::uint8_t> pixels;
        
        public:
            BMP(std::string filename);
            std::vector<std::uint8_t> getPixels() const { return this->pixels; };
            std::uint32_t getWidth() const { return this->width; };
            std::uint32_t getHeight() const { return this->height; };
            bool hasAlphaChannel() { return bitsPerPixel == 32; }
            GLuint openGLTexture();
        };
    };
};