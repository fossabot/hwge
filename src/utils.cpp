#include <stdio.h>
#include <hwge/utils.hpp>
#include <GL/glew.h>
#include <hwge/status_codes.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <glm/glm.hpp>

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

void HWGE::Utils::displayOpenGLVersions() {
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    
    printf("Renderer: %s\n", renderer);
    printf("OpenGL Version: %s\n", version);
}

std::string HWGE::Utils::loadFileAsString(std::string filename) {
    std::string res = "";

    std::ifstream file;
    std::string line;
    std::stringstream stream;

    file.open(filename);

    while(std::getline(file, line))
        stream << line << "\n";

    return stream.str();
}