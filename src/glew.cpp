#include <hwge/glew.hpp>
#include <GL/glew.h>
#include <stdio.h>

bool HWGE::GLEW::init() {
    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK) {
        fprintf(stderr, "ERROR: could not start glew!");
        return false;
    }

    return true;
}