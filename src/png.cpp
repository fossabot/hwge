#include <hwge/png.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <png.h>

HWGE::Image::PNG::PNG(std::string filename) {
    this->filename = filename;
}

GLuint HWGE::Image::PNG::load() {
    png_structp pngPtr;
    png_infop infoPtr, endInfo;
    png_byte header[8];
    
    FILE* file = fopen(filename.c_str(), "rb");

    if(file == NULL) {
        std::cout << "error: could not open PNG file." << std::endl;
        return false;
    }

    fread(header, 1, 8, file);

    if(png_sig_cmp(header, 0, 8)) {
        std::cout << "error: file is not a PNG." << std::endl;
        fclose(file);
        return false;
    }

    pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(pngPtr == NULL) {
        std::cout << "error: png_create_read_struct returned NULL." << std::endl;
        fclose(file);
        return false;
    }
    
    infoPtr = png_create_info_struct(pngPtr);
    if(infoPtr == NULL) {
        std::cout << "error: png_create_info_struct returned NULL." << std::endl;
        fclose(file);
        png_destroy_read_struct(&pngPtr, NULL, NULL);
        return false;
    }

    endInfo = png_create_info_struct(pngPtr);
    if(endInfo == NULL) {
        std::cout << "error: png_create_info_struct returned NULL." << std::endl;
        fclose(file);
        png_destroy_read_struct(&pngPtr, &infoPtr, NULL);
        return false;
    }

    if(setjmp(png_jmpbuf(pngPtr))) {
        std::cout << "error from libpng." << std::endl;
        png_destroy_read_struct(&pngPtr, &infoPtr, &endInfo);
        fclose(file);
        return false;
    }

    png_init_io(pngPtr, file);

    png_set_sig_bytes(pngPtr, 8);

    png_read_info(pngPtr, infoPtr);

    png_uint_32 tmpWidth, tmpHeight;
    int colorType, bitDepth;
    png_get_IHDR(pngPtr, infoPtr, &tmpWidth, &tmpHeight, &bitDepth, &colorType, NULL, NULL, NULL);

    //if(width) { *width = tmpWidth; }
    //if(height) { *height = tmpHeight; }
    this->width = tmpWidth;
    this->height = tmpHeight;

    printf("Bit depth: %d\n", bitDepth);

    GLint format;
    switch(colorType) {
        case PNG_COLOR_TYPE_RGB:
            format = GL_RGB;
            break;
        case PNG_COLOR_TYPE_RGB_ALPHA:
            format = GL_RGBA;
            break;
        default:
            return false;
    }

    this->format = format;
    png_read_update_info(pngPtr, infoPtr);
    int rowBytes = png_get_rowbytes(pngPtr, infoPtr);

    rowBytes += 3 - ((rowBytes - 1) % 4);
    
    imageData = (png_byte*) malloc(rowBytes * tmpHeight * sizeof(png_byte) + 15);
    if(imageData == NULL) {
        std::cout << "error: could not allocate memory for PNG image data." << std::endl;
        png_destroy_read_struct(&pngPtr, &infoPtr, &endInfo);
        fclose(file);
        return false;
    }
    
    png_byte** rowPointers = (png_byte**) malloc(tmpHeight * sizeof(png_byte*));
    if(rowPointers == NULL) {
        std::cout << "error: could not allocate memory for PNG row pointers." << std::endl;
        png_destroy_read_struct(&pngPtr, &infoPtr, &endInfo);
        free(imageData);
        fclose(file);
        return false;
    }

    for(int i = 0; i < tmpHeight; i++) {
        //memcpy(*imageData + (rowBytes * (height - 1 - i)), rowPointers[i], rowBytes);
        rowPointers[tmpHeight - 1 - i] = imageData + i * rowBytes;
    }

    
    //png_read_png(pngPtr, infoPtr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_EXPAND, NULL);
    png_read_image(pngPtr, rowPointers);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, format, tmpWidth, tmpHeight, 0, format, GL_UNSIGNED_BYTE, imageData);
    
    glGenerateMipmap(GL_TEXTURE_2D);

    // cleanup
    png_destroy_read_struct(&pngPtr, &infoPtr, &endInfo);
    free(imageData);
    free(rowPointers);
    fclose(file);

    std::cout << "Loaded png." << std::endl;

    return texture;
}