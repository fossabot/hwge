#include <hwge/text2D.hpp>
#include <hwge/png.hpp>
#include <hwge/shader_utils.hpp>
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <ft2build.h>
#include <vector>
#include <map>
#include <iostream>
#include <hwge/shader.hpp>
#include FT_FREETYPE_H

HWGE::Graphics::Text2D::Text2D(std::string filename, int windowWidth, int windowHeight) {
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    FT_Library ft;
    if(FT_Init_FreeType(&ft)) {
        std::cout << "error: could not initialize freetype." << std::endl;
    }

    FT_Face face;
    if(FT_New_Face(ft, filename.c_str(), 0, &face)) {
        std::cout << "error: failed to load freetype font." << std::endl;
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for(GLubyte c = 0; c < 128; c++) {
        if(FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "error: failed to load glyph." << std::endl;
            continue;
        }

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        HWGE::Graphics::Text2D::Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };

        HWGE::Graphics::Text2D::characters.insert(std::pair<GLchar, Character>(c, character));
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo),
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void HWGE::Graphics::Text2D::renderText(HWGE::Graphics::Shader& shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color) {
    shader.use();

    glUniform3f(glGetUniformLocation(shader.getID(), "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vao);

    std::string::const_iterator c;
    for(c = text.begin(); c != text.end(); c++) {
        HWGE::Graphics::Text2D::Character ch = HWGE::Graphics::Text2D::characters[*c];

        GLfloat xPos = x + ch.bearing.x * scale;
        GLfloat yPos = y - (ch.size.y - ch.bearing.y) * scale;

        GLfloat w = ch.size.x * scale;
        GLfloat h = ch.size.y * scale;

        GLfloat vertices[6][4] = {
            {xPos, yPos + h, 0.0, 0.0},
            {xPos, yPos, 0.0, 1.0},
            {xPos + w, yPos, 1.0, 1.0},
            {xPos, yPos + h, 0.0, 0.0},
            {xPos + w, yPos, 1.0, 1.0},
            {xPos + w, yPos + h, 1.0, 0.0}
        };

        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (ch.advance >> 6) * scale;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

/*HWGE::Graphics::Text2D::Text2D(int width, int height, std::string filename) {
    this->filename = filename;
    this->width = width;
    this->height = height;
};

void HWGE::Graphics::Text2D::loadPNG() {
    HWGE::Image::PNG png(filename);
    textureID = png.load();
    load();
}

void HWGE::Graphics::Text2D::load() {
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &uvbo);

    shaderID = HWGE::ShaderUtils::load("assets/shaders/text.vs", "assets/shaders/text.fs");
    uniformID = glGetUniformLocation(shaderID, "texSampler");
}

void HWGE::Graphics::Text2D::printString(std::string text, int x, int y, int size) {
    this->print(text.c_str(), x, y, size);
}

void HWGE::Graphics::Text2D::print(const char* text, int x, int y, int size) {
    unsigned int length = strlen(text);

    std::vector<glm::vec2> vertices;
    std::vector<glm::vec2> uvs;

    for(unsigned int i = 0; i < length; i++) {
        glm::vec2 vertexUpLeft = glm::vec2(x + i * size, y + size);
        glm::vec2 vertexUpRight = glm::vec2(x + i * size + size, y + size);
        glm::vec2 vertexDownLeft = glm::vec2(x + i * size + size, y);
        glm::vec2 vertexDownRight = glm::vec2(x + i * size, y);

        vertices.push_back(vertexUpLeft);
        vertices.push_back(vertexDownLeft);
        vertices.push_back(vertexUpRight);

        vertices.push_back(vertexDownRight);
        vertices.push_back(vertexUpRight);
        vertices.push_back(vertexDownLeft);

        char character = text[i];
        float uvX = (character % 16) / 16.0f;
        float uvY = (character / 16) / 16.0f;

        glm::vec2 uvUpLeft = glm::vec2(uvX, uvY);
        glm::vec2 uvUpRight = glm::vec2(uvX + 1.0f / 16.0f, uvY);
        glm::vec2 uvDownLeft = glm::vec2(uvX + 1.0f / 16.0f, (uvY + 1.0f / 16.0f));
        glm::vec2 uvDownRight = glm::vec2(uvX, (uvY + 1.0f / 16.0f));

        uvs.push_back(uvUpLeft);
        uvs.push_back(uvDownLeft);
        uvs.push_back(uvUpRight);

        uvs.push_back(uvDownRight);
        uvs.push_back(uvUpRight);
        uvs.push_back(uvDownLeft);
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, uvbo);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

    // Bind shader
    glUseProgram(shaderID);

    // Bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glUniform1i(uniformID, 0);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /*glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_CULL_FACE);

    glClear(GL_DEPTH_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    glEnable(GL_CULL_FACE);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    //glDisable(GL_BLEND);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void HWGE::Graphics::Text2D::cleanup() {
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &uvbo);

    glDeleteTextures(1, &textureID);

    glDeleteProgram(shaderID);
}*/