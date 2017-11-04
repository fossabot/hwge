#pragma once

#include <GL/glew.h>
#include <string>

namespace HWGE {
    namespace ShaderUtils {
        GLuint loadShaders(std::string vertexShader, std::string fragmentShader);
        GLuint load(std::string vsFile, std::string fsFile);
    };
};