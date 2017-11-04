#if HWGE_USE_GLFW

#pragma once

#include <GLFW/glfw3.h>
#include <string>

namespace HWGE {
    namespace GLFW {
        bool init();
        GLFWwindow* createWindow(int width, int height, std::string title);
    };
};

#endif