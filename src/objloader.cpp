#include <hwge/objloader.hpp>
#include <string>
#include <string.h>
#include <vector>
#include <iostream>

using namespace std;

bool HWGE::OBJLoader::loadOBJ(std::string filename, std::vector<glm::vec3> &out_vertices, std::vector<glm::vec2> &out_uvs, std::vector<glm::vec3> &out_normals) {
    vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    vector<glm::vec3> tmpVertices;
    vector<glm::vec2> tmpUVs;
    vector<glm::vec3> tmpNormals;

    FILE* file = fopen(filename.c_str(), "r");

    if(file == NULL) {
        cout << "Impossible to open the file!" << endl;
        return false;
    }

    while(true) {
        char lineHeader[128];

        int res = fscanf(file, "%s", lineHeader);
        if(res == EOF) {
            break;
        }

        if(strcmp(lineHeader, "v") == 0) {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            tmpVertices.push_back(vertex);
        } else if(strcmp(lineHeader, "vt") == 0) {
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            tmpUVs.push_back(uv);
        } else if(strcmp(lineHeader, "vn") == 0) {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            tmpNormals.push_back(normal);
        } else if(strcmp(lineHeader, "f") == 0) {
            string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, " %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

            if(matches != 9) {
                cout << "Failed to parse the model." << endl;
                return false;
            }

            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        } else {
            char tmpBuffer[1024];
            fgets(tmpBuffer, 1024, file);
        }

        for(unsigned int i = 0; i < vertexIndices.size(); i++) {
            unsigned int vertexIndex = vertexIndices[i];
            unsigned int uvIndex = uvIndices[i];
            unsigned int normalIndex = normalIndices[i];

            glm::vec3 vertex = tmpVertices[vertexIndex - 1];
            glm::vec2 uv = tmpUVs[uvIndex - 1];
            glm::vec3 normal = tmpNormals[normalIndex - 1];

            out_vertices.push_back(vertex);
            out_uvs.push_back(uv);
            out_normals.push_back(normal);
        }
    }

    return true;
}