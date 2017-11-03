#include <hwge/shader.hpp>
#include <hwge/shader_utils.hpp>

HWGE::Graphics::Shader::Shader(std::string vsFile, std::string fsFile) {
    this->vertexFile = vsFile;
    this->fragmentFile = fsFile;
}

void HWGE::Graphics::Shader::load() {
    this->shaderID = HWGE::ShaderUtils::load(vertexFile, fragmentFile);
}

void HWGE::Graphics::Shader::use() {
    glUseProgram(shaderID);
}

void HWGE::Graphics::Shader::deleteShader() {
    glDeleteProgram(shaderID);
}

GLuint HWGE::Graphics::Shader::getID() {
    return shaderID;
}

GLuint HWGE::Graphics::Shader::getUniformLocation(std::string name) {
    return glGetUniformLocation(shaderID, name.c_str());
}