#pragma once

#include <GL/glew.h>
#include <string>

namespace HWGE {
    namespace Graphics {
        class Shader {
        private:
            std::string vertexFile, fragmentFile;
            GLuint shaderID;

        public:
            Shader(std::string vsFile, std::string fsFile);
            void load();
            void use();
            void deleteShader();
            GLuint getID();
            GLuint getUniformLocation(std::string name);
        };
    };
};