#pragma once

#include <SDL.h> // TODO: Fix the SDL include dirs.
#include <GLFW/glfw3.h>

void hwgeInputHandleSDL(const SDL_Event &event);
void hwgeInputHandleGLFW(GLFWwindow* window, int key, int scancode, int action, int mods);

namespace HWGE {
    namespace Input {
        bool keys[1024];

        int sdlToHWGEKey(int key);
        int glfwToHWGEKey(int key);
        bool getKey(int key);
    };
};