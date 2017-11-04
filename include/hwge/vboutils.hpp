#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <map>
#include <stdio.h>

namespace HWGE {
    namespace Utils {
        namespace VBO {
            void indexVBO(std::vector<glm::vec3> &inVertices, std::vector<glm::vec2> &inUVs, std::vector<glm::vec3> &inNormals, std::vector<unsigned short> &outIndices, std::vector<glm::vec3> &outVertices, std::vector<glm::vec2> &outUVs, std::vector<glm::vec3> &outNormals);
        };
    };
};