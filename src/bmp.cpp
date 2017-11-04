#include <hwge/bmp.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

HWGE::Image::BMP::BMP(std::string filename) {
    std::fstream file(filename, std::ios::in | std::ios::binary);

    if(!file.is_open()) {
        throw std::invalid_argument("BMP file not found!");
    }

    file.seekg(0, std::ios::end);
    std::size_t length = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<std::uint8_t> fileInfo(length);
    file.read(reinterpret_cast<char*>(fileInfo.data()), 54);

    if(fileInfo[0] != 'B' && fileInfo[1] != 'M') {
        file.close();
        throw std::invalid_argument("Invalid file format, Bitmap is required.");
    }

    if(fileInfo[28] != 24 && fileInfo[28] != 32) {
        file.close();
        throw std::invalid_argument("Invalid file format, 24 or 32 bit image required.");
    }

    bitsPerPixel = fileInfo[28];
    width = fileInfo[18] + (fileInfo[19] << 8);
    height = fileInfo[22] + (fileInfo[23] << 8);
    std::uint32_t pixelsOffset = fileInfo[10] + (fileInfo[11] << 8);
    std::uint32_t size = ((width * bitsPerPixel + 31) / 32) * 4 * height;
    pixels.resize(size);

    file.seekg(pixelsOffset, std::ios::beg);
    file.read(reinterpret_cast<char*>(pixels.data()), size);
    file.close();
}

GLuint HWGE::Image::BMP::openGLTexture() {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, hasAlphaChannel() ? GL_RGBA : GL_RGB, width, height, 0, hasAlphaChannel() ? GL_BGRA : GL_BGR, GL_UNSIGNED_BYTE, pixels.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    return texture;
}