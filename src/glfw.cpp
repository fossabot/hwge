#if HWGE_USE_GLFW

#include <hwge/glfw.hpp>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string>

bool HWGE::GLFW::init() {
    if(!glfwInit()) {
        fprintf(stderr, "ERROR: could not start glfw!");
        return false;
    }

    return true;
}

GLFWwindow* HWGE::GLFW::createWindow(int width, int height, std::string title) {
    GLFWwindow* win = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if(!win) {
        fprintf(stderr, "ERROR: could not create glfw window!");
        glfwTerminate();
        return NULL;
    }

    return win;
}

#endif