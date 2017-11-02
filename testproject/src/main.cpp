#include <iostream>
#include <vector>
#include <stdio.h>
#include <hwge/hwge.hpp>
#include <hwge/status_codes.hpp>
#include <hwge/shader.hpp>
#include <hwge/glew.hpp>
#include <hwge/utils.hpp>
#include <hwge/vboutils.hpp>
#include <hwge/objloader.hpp>
#include <hwge/glfw.hpp>
#include <hwge/bmp.hpp>
#include <hwge/png.hpp>
#include <hwge/args.hpp>
#include <hwge/freetype.hpp>
#include <hwge/text2D.hpp>
#include <string>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace HWGE;

glm::mat4 viewMatrix, projectionMatrix;
glm::vec3 position = glm::vec3(0, 0, 5);
float horizontalAngle = 3.14f;
float verticalAngle = 0.0f;
float initalFoV = 45.0f;
float speed = 3.0f;
float mouseSpeed = 0.0005f;

bool useControls = false;

void computeMatFromInput(GLFWwindow* window, int width, int height) {
    static double lastTime = glfwGetTime();

    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);

    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);

    glfwSetCursorPos(window, width / 2, height / 2);

    horizontalAngle += mouseSpeed * float(width / 2 - xPos);
    verticalAngle += mouseSpeed * float(height / 2 - yPos);

    glm::vec3 direction(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * sin(horizontalAngle)
    );

    glm::vec3 right(
        sin(horizontalAngle - 3.14f / 2.0f),
        0,
        cos(horizontalAngle - 3.14f / 2.0f)
    );

    glm::vec3 up = glm::cross(right, direction);

    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        position += direction * deltaTime * speed;
    }

    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        position -= direction * deltaTime * speed;
    }

    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        position += right * deltaTime * speed;
    }

    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        position -= right * deltaTime * speed;
    }

    float fov = initalFoV;

    projectionMatrix = glm::perspective(glm::radians(fov), (float) width / (float) height, 0.1f, 100.0f);
    viewMatrix = glm::lookAt(
        position,
        position + direction,
        up
    );

    lastTime = currentTime;
}

int main(int argc, char** argv) {
    HWGE::Args args(argc, argv);
    HWGE::init();
    
    if(args.hasOption("--use-controls")) {
        useControls = true;
    }

    if(!GLFW::init()) return HWGE_STATUS_ERROR;

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int width = 800;
    int height = 600;

    GLFWwindow* window = GLFW::createWindow(width, height, "HWGE Version: " + HWGE::version());
    glfwMakeContextCurrent(window);

    if(!GLEW::init()) return HWGE_STATUS_ERROR;

    int glutArgc = 1;
    char *glutArgv[1] = { (char*)"Something" };
    glutInit(&glutArgc, glutArgv);

    Utils::displayOpenGLVersions();

    glViewport(0, 0, width, height);

    glfwPollEvents();
    glfwSetCursorPos(window, width / 2, height / 2);

    glClearColor(0.0f, 0.75f, 1.0f, 0.0f);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    if(useControls) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //glfwPollEvents();
    //glfwSetCursorPos(window, width / 2, height / 2);

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    Graphics::Shader shader("assets/shaders/tex.vs", "assets/shaders/tex_transparent.fs");
    shader.load();
    
    GLuint matrixID = shader.getUniformLocation("MVP");
    GLuint viewMatrixID = shader.getUniformLocation("V");
    GLuint modelMatrixID = shader.getUniformLocation("M");
    GLuint textureID = shader.getUniformLocation("texSampler");
    GLuint lightID = shader.getUniformLocation("lightPos");

    Image::PNG png("assets/textures/thing.png");
    GLuint texture = png.load();
    
    vector<glm::vec3> vertices;
    vector<glm::vec2> uvs;
    vector<glm::vec3> normals;

    cout << "Loading objects..." << endl;
    bool res = OBJLoader::loadOBJ("assets/models/cube.obj", vertices, uvs, normals);

    vector<unsigned short> indices;
    vector<glm::vec3> indexedVertices;
    vector<glm::vec2> indexedUVs;
    vector<glm::vec3> indexedNormals;

    cout << "VBO indexing..." << endl;
    Utils::VBO::indexVBO(vertices, uvs, normals, indices, indexedVertices, indexedUVs, indexedNormals);

    cout << "Creating buffer objects..." << endl;
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, indexedVertices.size() * sizeof(glm::vec3), &indexedVertices[0], GL_STATIC_DRAW);

    GLuint uvbo;
    glGenBuffers(1, &uvbo);
    glBindBuffer(GL_ARRAY_BUFFER, uvbo);
    glBufferData(GL_ARRAY_BUFFER, indexedUVs.size() * sizeof(glm::vec2), &indexedUVs[0], GL_STATIC_DRAW);

    GLuint nbo;
    glGenBuffers(1, &nbo);
    glBindBuffer(GL_ARRAY_BUFFER, nbo);
    glBufferData(GL_ARRAY_BUFFER, indexedNormals.size() * sizeof(glm::vec3), &indexedNormals[0], GL_STATIC_DRAW);

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);

    Graphics::Shader textShader("assets/shaders/text2d.vs", "assets/shaders/text2d.fs");
    textShader.load();
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(width), 0.0f, static_cast<GLfloat>(height));
    textShader.use();
    glUniformMatrix4fv(glGetUniformLocation(textShader.getID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    Graphics::Text2D text2d("assets/fonts/opensans.ttf", width, height);

    double lastTime = glfwGetTime();
    int nbFrames = 0;

    string fpsText = "FPS: ";
    cout << "Starting game loop..." << endl;
    do {
        char* tmpText;
        double currentTime = glfwGetTime();
        nbFrames++;
        if(currentTime - lastTime >= 1.0) {
            fpsText = "FPS: " + to_string(nbFrames);
            nbFrames = 0;
            lastTime = currentTime;
        }

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_CULL_FACE);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //glBindVertexArray(vao);

        //glUseProgram(programID);

        if(useControls) {
            computeMatFromInput(window, width, height);
        } else {
            viewMatrix = glm::lookAt(
                glm::vec3(4, 3, 3),
                glm::vec3(0, 0, 0),
                glm::vec3(0, 1, 0)
            );

            projectionMatrix = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 0.1f, 100.0f);
        }
        glm::mat4 modelMatrix(1.0);
        glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;

        glBindVertexArray(vao);
        shader.use();

        glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);
        glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
        glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);

        glm::vec3 lightPos(4, 4, 4);
        glUniform3f(lightID, lightPos.x, lightPos.y, lightPos.z);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(textureID, 0);

        // Start draw

        // Vertex Buffer
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0); // (attribute, size, type, normalized?, stride)

        // UVs
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbo);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

        // normals
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, nbo);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, (void*) 0);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        // End Draw

        glDisable(GL_DEPTH_TEST);
        text2d.renderText(textShader, fpsText, 25.0f, 25.0f, 1.0f, glm::vec3(0.5f, 0.8f, 0.2f));
        glEnable(GL_DEPTH_TEST);

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while(!glfwWindowShouldClose(window));

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &uvbo);
    glDeleteBuffers(1, &nbo);
    shader.deleteShader();
    glDeleteTextures(1, &texture);
    glDeleteVertexArrays(1, &vao);

    glfwTerminate();
    return HWGE_STATUS_OK;
}