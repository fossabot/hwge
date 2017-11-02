#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace HWGE {
    namespace Utils {
        void displayOpenGLVersions();
        std::string loadFileAsString(std::string filename);
    };
};