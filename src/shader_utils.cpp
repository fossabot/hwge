#include <GL/glew.h>
#include <hwge/shader_utils.hpp>
#include <hwge/utils.hpp>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

GLuint HWGE::ShaderUtils::loadShaders(string vertexShader, string fragmentShader) {
    GLuint vsID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fsID = glCreateShader(GL_FRAGMENT_SHADER);

    GLint res = GL_FALSE;
    int infoLogLength;

    // Compile vertex shader
    cout << "Compiling vertex shader..." << endl;
    char const* vsSource = vertexShader.c_str();
    glShaderSource(vsID, 1, &vsSource, NULL);
    glCompileShader(vsID);

    // Check vertex shader
    glGetShaderiv(vsID, GL_COMPILE_STATUS, &res);
    glGetShaderiv(vsID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if(infoLogLength > 0) {
        std::vector<char> vertexShaderError(infoLogLength + 1);
        glGetShaderInfoLog(vsID, infoLogLength, NULL, &vertexShaderError[0]);
        cout << &vertexShaderError[0] << endl;
    }

    // Compile fragment shader
    cout << "Compiling fragment shader..." << endl;
    char const* fsSource = fragmentShader.c_str();
    glShaderSource(fsID, 1, &fsSource, NULL);
    glCompileShader(fsID);

    // Check fragment shader
    glGetShaderiv(fsID, GL_COMPILE_STATUS, &res);
    glGetShaderiv(fsID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if(infoLogLength > 0) {
        std::vector<char> fragmentShaderError(infoLogLength + 1);
        glGetShaderInfoLog(fsID, infoLogLength, NULL, &fragmentShaderError[0]);
        cout << &fragmentShaderError[0] << endl;
    }

    // Link the program
    cout << "Linking program" << endl;
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vsID);
    glAttachShader(programID, fsID);
    glLinkProgram(programID);

    // Check the program
    glGetProgramiv(programID, GL_LINK_STATUS, &res);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if(infoLogLength > 0) {
        std::vector<char> programShaderError(infoLogLength + 1);
        glGetProgramInfoLog(programID, infoLogLength, NULL, &programShaderError[0]);
        cout << &programShaderError[0] << endl;
    }

    glDetachShader(programID, vsID);
    glDetachShader(programID, fsID);

    glDeleteShader(vsID);
    glDeleteShader(fsID);

    return programID;
}

GLuint HWGE::ShaderUtils::load(std::string vsFile, std::string fsFile) {
    std::string vsStr = HWGE::Utils::loadFileAsString(vsFile);
    std::string fsStr = HWGE::Utils::loadFileAsString(fsFile);
    return HWGE::ShaderUtils::loadShaders(vsStr, fsStr);
}