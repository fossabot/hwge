#pragma once

#if HWGE_USE_SDL
#include <SDL.h> // TODO: Fix the SDL include dirs.
#elif HWGE_USE_GLFW
#include <GLFW/glfw3.h>
#endif

#if HWGE_USE_SDL
void hwgeInputHandleSDL(const SDL_Event &event);
#elif HWGE_USE_GLFW
void hwgeInputHandleGLFW(GLFWwindow* window, int key, int scancode, int action, int mods);
#endif

namespace HWGE {
    namespace Input {
        #if HWGE_USE_SDL
        int sdlToHWGEKey(int key);
        #elif HWGE_USE_GLFW
        int glfwToHWGEKey(int key);
        #endif
        
        bool getKey(int key);
    };
};