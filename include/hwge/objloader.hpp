#pragma once

#include <GL/glew.h>
#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace HWGE {
    namespace OBJLoader {
        bool loadOBJ(std::string filename, std::vector<glm::vec3> &out_vertices, std::vector<glm::vec2> &out_uvs, std::vector<glm::vec3> &out_normals);
    };
};