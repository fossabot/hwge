#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <map>
#include <hwge/shader.hpp>

namespace HWGE {
    namespace Graphics {
        class Text2D {
        private:
            struct Character {
                GLuint textureID;
                glm::ivec2 size;
                glm::ivec2 bearing;
                GLuint advance;
            };

            std::map<GLchar, Character> characters;
            GLuint vao, vbo;
            glm::mat4 projection;
            HWGE::Graphics::Shader& shader;
            int windowWidth, windowHeight;
        
        public:
            Text2D(HWGE::Graphics::Shader& shader, std::string filename, int windowWidth, int windowHeight);
            void renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
        };
        /*class Text2D {
        private:
            std::string filename;
            unsigned int textureID, shaderID, uniformID;
            unsigned int vbo, uvbo;
            int width, height;
            void load();
        public:
            Text2D(int width, int height, std::string filename);
            void loadPNG();
            void printString(std::string text, int x, int y, int size);
            void print(const char* text, int x, int y, int size);
            void cleanup();
        };*/
    };
};