#include <GLFW/glfw3.h>
#include <SDL.h> // TODO: Fix the SDL include dirs.
#include <hwge/input.hpp>
#include <hwge/keycodes.hpp>

// Should only be used by the engine, do not use this function.
void hwgeInputHandleSDL(const SDL_Event &event) {
    switch(event.type) {
        default:
            break;
        case SDL_KEYDOWN:
            HWGE::Input::keys[HWGE::Input::sdlToHWGEKey(event.key.keysym.sym)] = true;
            break;
        case SDL_KEYUP:
            HWGE::Input::keys[HWGE::Input::sdlToHWGEKey(event.key.keysym.sym)] = false;
            break;
    }
}

// Should only be used by the engine, do not use this function.
void hwgeInputHandleGLFW(GLFWwindow* window, int key, int scancode, int action, int mods) {
    int keyTmp = HWGE::Input::glfwToHWGEKey(key);

    switch(action) {
        default:
            break;
        case GLFW_PRESS:
            HWGE::Input::keys[keyTmp] = true;
            break;
        case GLFW_RELEASE:
            HWGE::Input::keys[keyTmp] = false;
            break;
    }
}

bool HWGE::Input::getKey(int key) {
    return HWGE::Input::keys[key];
}

// TODO: Add all keys from https://wiki.libsdl.org/SDLKeycodeLookup
int HWGE::Input::sdlToHWGEKey(int key) {
    switch(key) {
        case SDLK_UNKNOWN:
            return HWGE_KEY_UNKNOWN;
        case SDLK_BACKSPACE:
            return HWGE_KEY_BACKSPACE;
        case SDLK_TAB:
            return HWGE_KEY_TAB;
        case SDLK_RETURN:
            return HWGE_KEY_ENTER;
        case SDLK_ESCAPE:
            return HWGE_KEY_ESCAPE;
        case SDLK_DELETE:
            return HWGE_KEY_DELETE;
        case SDLK_CAPSLOCK:
            return HWGE_KEY_CAPS_LOCK;
        case SDLK_F1:
            return HWGE_KEY_F1;
        case SDLK_F2:
            return HWGE_KEY_F2;
        case SDLK_F3:
            return HWGE_KEY_F3;
        case SDLK_F4:
            return HWGE_KEY_F4;
        case SDLK_F5:
            return HWGE_KEY_F5;
        case SDLK_F6:
            return HWGE_KEY_F6;
        case SDLK_F7:
            return HWGE_KEY_F7;
        case SDLK_F8:
            return HWGE_KEY_F8;
        case SDLK_F9:
            return HWGE_KEY_F9;
        case SDLK_F10:
            return HWGE_KEY_F10;
        case SDLK_F11:
            return HWGE_KEY_F11;
        case SDLK_F12:
            return HWGE_KEY_F12;
        case SDLK_PRINTSCREEN:
            return HWGE_KEY_PRINT_SCREEN;
        case SDLK_SCROLLLOCK:
            return HWGE_KEY_SCROLL_LOCK;
        case SDLK_PAUSE:
            return HWGE_KEY_PAUSE;
        case SDLK_INSERT:
            return HWGE_KEY_INSERT;
        case SDLK_HOME:
            return HWGE_KEY_HOME;
        case SDLK_PAGEUP:
            return HWGE_KEY_PAGE_UP;
        case SDLK_END:
            return HWGE_KEY_END;
        case SDLK_PAGEDOWN:
            return HWGE_KEY_PAGE_DOWN;
        case SDLK_RIGHT:
            return HWGE_KEY_RIGHT;
        case SDLK_LEFT:
            return HWGE_KEY_LEFT;
        case SDLK_DOWN:
            return HWGE_KEY_DOWN;
        case SDLK_UP:
            return HWGE_KEY_UP;
        case SDLK_NUMLOCKCLEAR:
            return HWGE_KEY_NUM_LOCK;
        case SDLK_KP_DIVIDE:
            return HWGE_KEY_KP_DIVIDE;
        case SDLK_KP_MULTIPLY:
            return HWGE_KEY_KP_MULTIPLY;
        case SDLK_KP_MINUS:
            return HWGE_KEY_KP_SUBTRACT;
        case SDLK_KP_PLUS:
            return HWGE_KEY_KP_ADD;
        case SDLK_KP_ENTER:
            return HWGE_KEY_KP_ENTER;
        case SDLK_KP_0:
            return HWGE_KEY_KP_0;
        case SDLK_KP_1:
            return HWGE_KEY_KP_1;
        case SDLK_KP_2:
            return HWGE_KEY_KP_2;
        case SDLK_KP_3:
            return HWGE_KEY_KP_3;
        case SDLK_KP_4:
            return HWGE_KEY_KP_4;
        case SDLK_KP_5:
            return HWGE_KEY_KP_5;
        case SDLK_KP_6:
            return HWGE_KEY_KP_6;
        case SDLK_KP_7:
            return HWGE_KEY_KP_7;
        case SDLK_KP_8:
            return HWGE_KEY_KP_8;
        case SDLK_KP_9:
            return HWGE_KEY_KP_9;
        case SDLK_KP_PERIOD:
            return HWGE_KEY_KP_DECIMAL;
        case SDLK_APPLICATION:
            return SDLK_APPLICATION;
        case SDLK_POWER:
            return SDLK_POWER;
        case SDLK_KP_EQUALS:
            return HWGE_KEY_KP_EQUAL;
        case SDLK_F13:
            return HWGE_KEY_F13;
        case SDLK_F14:
            return HWGE_KEY_F14;
        case SDLK_F15:
            return HWGE_KEY_F15;
        case SDLK_F16:
            return HWGE_KEY_F16;
        case SDLK_F17:
            return HWGE_KEY_F17;
        case SDLK_F18:
            return HWGE_KEY_F18;
        case SDLK_F19:
            return HWGE_KEY_F19;
        case SDLK_F20:
            return HWGE_KEY_F20;
        case SDLK_F22:
            return HWGE_KEY_F22;
        case SDLK_F23:
            return HWGE_KEY_F23;
        case SDLK_F24:
            return HWGE_KEY_F24;
        default:
            break;
    }

    if(key >= 96 && key <= 122) {
        key += 32;
    }

    return key;
}

// Not needed but just for it having the same syntax as for sdl
int HWGE::Input::glfwToHWGEKey(int key) {
    return key;
}